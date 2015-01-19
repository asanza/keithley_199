/**
 * @file eeprom.c
 * @brief eeprom write read routines
 * @author Diego F. Asanza
 */
#include <stdint.h>
#include <stdbool.h>
#include "hal.h"
#include "HardwareProfile.h"
#include <assert.h>

bool drv_eeprom_write_page(uint16_t address, uint8_t* data, uint8_t size){
    assert(address < HAL_EEPROM_SIZE);
    assert(size <= HAL_EEPROM_PAGE_SIZE);
    return eeprom_write_page(address, data, size);
}

bool drv_eeprom_read_page(uint16_t address, uint8_t* data, uint8_t size){
    assert(address < HAL_EEPROM_SIZE);
    assert(size <= HAL_EEPROM_PAGE_SIZE);
    return eeprom_read_page(address, data, size);
}