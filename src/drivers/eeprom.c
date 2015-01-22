/*
 * eeprom.c
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
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
 * Created on January 19, 2015, 10:16 PM
 */

#include <hal_i2c.h>
#include <eeprom.h>

#include "HardwareProfile.h"
#include "hal.h"

void eeprom_read_page(uint16_t page_address, uint8_t* _data){
    
}

void eeprom_write_page(uint16_t address, uint8_t* _data){

}

uint8_t eeprom_read_byte(uint16_t address){
    hal_i2c_start(HAL_EEPROM_ADDRESS, HAL_I2C_WRITE);
    hal_i2c_write(address >> 8);
    hal_i2c_write(address);
    hal_i2c_rep_start(HAL_EEPROM_ADDRESS, HAL_I2C_READ);
    uint8_t c = hal_i2c_readNak();
    hal_i2c_stop();
    return c;
}
void eeprom_write_byte(uint16_t address, uint8_t byte){
    hal_i2c_start(HAL_EEPROM_ADDRESS, HAL_I2C_WRITE);
    hal_i2c_write(address >> 8);
    hal_i2c_write(address);
    hal_i2c_write(byte);
    hal_i2c_stop();
    /* wait for write to be executed */
    while(hal_i2c_start(HAL_EEPROM_ADDRESS, HAL_I2C_WRITE));
    hal_i2c_stop();
}