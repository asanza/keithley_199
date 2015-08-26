/** @file: bbm.c
 *  @brief: EEPROM file system.
 *  @author: Diego F. Asanza
 */

#include "eefs.h"
#include <hal.h>
#include <stdint.h>
#include <string.h>
#include <eeprom.h>
#include <assert.h>
#define STATIC static


/* Internal definitions */
#define EEPROM_NUMBER_OF_PAGES 		EEPROM_SIZE/EEPROM_PAGE_SIZE
typedef uint32_t CRC32;
#define MAX_TRIALS	10               /**< Trials before returning a read/write error */
#define MAX_NUMBER_OF_OBJECTS		256 /**< maximal number of objects to be saved. */
#define MAX_OBJECT_SIZE             EEFS_PAGE_SIZE  /**< maximal size of an object */
#define EEFS_PAGE_SIZE 				(EEPROM_PAGE_SIZE - sizeof(CRC32)) //page used from eeprom

/* objects ids are saved in side by side memory slots
 * They should have max. 20 bytes size.
 */

/* the minimal datablock. Data will be written/read in multiples of this unit
 * In this implementation it is exact the size of a eeprom page */
typedef struct eefs_page_S{
	uint8_t data[EEPROM_PAGE_SIZE - sizeof(CRC32)];
	CRC32	crc;
}__attribute__((packed)) eefs_page;

/* buffer for reading and writting data */
static eefs_page page_buffer;

/* write a whole page into eeprom. Make sure that data was correctly written */
STATIC EEFS_ERROR eefs_write_page(uint16_t page_address, eefs_page* block);
/* read a whole page from eeprom. Make sure that was correctly read */
STATIC EEFS_ERROR eefs_read_page(uint16_t page_address, eefs_page* block);


EEFS_ERROR eefs_write_page(uint16_t page_address, eefs_page* page){
	assert(page_address < EEPROM_NUMBER_OF_PAGES);
	uint32_t i = 0, j=0, temp=0; bool t = false; uint8_t* p = (uint8_t*)page;
	/* append the checksum */
	temp = crc32(temp,page,EEFS_PAGE_SIZE);
	page->crc = temp;
	uint8_t bbyte;
	/* do the write */
	do{
        t = true;
		eeprom_write_page(page_address,p);
		/* read back written data */
		for(j=0; j < EEPROM_PAGE_SIZE; j++){
			bbyte = eeprom_read_byte(page_address*EEPROM_PAGE_SIZE + j);
			if(bbyte!=p[j]) {
                t = false;
                break;
            }; // write and read not match error. Retry.
		}
	}while(( i++ < MAX_TRIALS ) );
	if(t) return EEFS_OK;
	else return EEFS_ERR_HW;
}

EEFS_ERROR eefs_read_page(uint16_t page_address, eefs_page* page){
    assert(page_address < EEPROM_NUMBER_OF_PAGES);
    int i = 0; bool t = false; CRC32 crc; EEFS_ERROR err = EEFS_OK;
    do{
        crc = 0;
        eeprom_read_page(page_address, (uint8_t*)page);
        /* test checksum */
        crc = crc32(crc,(uint8_t*)page, sizeof(eefs_page) - sizeof(CRC32));
        if(crc!=page->crc){
            err = EEFS_ERR_CHK;
            continue;
        } //checksum not match, try again
        err = EEFS_OK;
    }while((i++ < MAX_TRIALS));
    return err;
}


EEFS_ERROR eefs_object_save(uint8_t object_id, const void* data, size_t size){
	int page_address, page_offset;
    /* objects should be smaller than MAX_OBJECT_SIZE */
	assert(size <= MAX_OBJECT_SIZE);
    /* calculate page_address */
   page_address = (object_id*MAX_OBJECT_SIZE)/EEFS_PAGE_SIZE;
	/* Objects are static size, no changes in runtime. So save object in
	 * requested address without further checks */
    EEFS_ERROR err = eefs_read_page(page_address, &page_buffer);
    /* calculate page offset */
    page_offset = (object_id*MAX_OBJECT_SIZE)%EEFS_PAGE_SIZE;
	/* copy object at requested page offset */
	memcpy(page_buffer.data + page_offset, data, size);
	/* save data into eeprom */
	err = eefs_write_page(page_address, &page_buffer);
	return err;
}

EEFS_ERROR eefs_object_restore(uint8_t object_id, void* data, size_t size){
    /* objects should be smaller than MAX_OBJECT_SIZE */
    assert(size <= MAX_OBJECT_SIZE);
	int page_address, page_offset;
    /* locate the page address of this object id
     * there are EEFS_PAGE_SIZE/MAX_OBJECT_SIZE objects pro page */
    page_address = (object_id*MAX_OBJECT_SIZE)/EEFS_PAGE_SIZE;
	EEFS_ERROR err = eefs_read_page(page_address, &page_buffer);
	if(err!=EEFS_OK)
        return err;
    /* locate the page offset where this object is saved */
    page_offset = (object_id*MAX_OBJECT_SIZE)%EEFS_PAGE_SIZE;
	/* copy object at requested page offset */
	memcpy(data, page_buffer.data + page_offset, size);
	return err;
}