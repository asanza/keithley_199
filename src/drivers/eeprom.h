/* 
 * File:   eeprom.h
 * Author: diego
 *
 * Created on September 12, 2014, 10:45 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool drv_eeprom_write_page(uint16_t address, uint8_t* data, uint8_t size);
bool drv_eeprom_read_page(uint16_t address, uint8_t* data, uint8_t size);



#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

