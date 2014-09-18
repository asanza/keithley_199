/* 
 * @file   eefs.h
 * @author dasanza
 * @brief  eeprom file system interface
 * This module provides a simple file system for eeprom. The filesystem
 * provides following features.
 * - save and read structures based on an id.
 * - bad block tracking
 * - data checksum
 * - automatic page write/read for max. performance.
 * Created on 19. Februar 2014, 10:06
 */

#ifndef EEFS_H
#define	EEFS_H

#include <stdint.h>
#include <stddef.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
	EEFS_OK,
	EEFS_ERR_CHK,
	EEFS_ERR_HW,
	EEFS_EMPTY,
	EEFS_FULL
}EEFS_ERROR;

/** Write an object into memory
 * @param object_id Id for this object. From 0 to 255
 * @param data pointer to the object
 * @param size size of the object
 * @return EEFS_OK if all ok.
 */
EEFS_ERROR eefs_object_save(uint8_t object_id, const void* data, size_t size);
EEFS_ERROR eefs_object_restore(uint8_t object_id, void* data, size_t size);


uint32_t crc32(uint32_t crc, void* data, size_t size);



#ifdef	__cplusplus
}
#endif

#endif	/* EEFS_H */

