/*
 * eeprom.h
 *
 * Copyright (c) ${year}, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on January 19, 2015, 10:09 PM
 */
#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define EEPROM_PAGE_SIZE 64     /* size of an eeprom page in bytes*/
#define EEPROM_SIZE      0x8000 /* total eeprom size in bytes */
    
void eeprom_read_page(uint16_t page_address, uint8_t* _data);
void eeprom_write_page(uint16_t address, uint8_t* _data);

uint8_t eeprom_read_byte(uint16_t address);
void eeprom_write_byte(uint16_t address, uint8_t byte);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

