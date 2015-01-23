/*
 * tmp275.c
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
 * Created on January 20, 2015, 7:11 PM
 */

#include <tmp275.h>
#include <hal_i2c.h>
#include <stdbool.h>
#include <stdint.h>
#include "HardwareProfile.h"

/* device pointer register definitions */
#define TEMPERATURE_REG     0x00
#define CONFIGURATION_REG          0x01
#define TEMPERATURE_LOW     0x02
#define TEMPERATURE_HIGH    0x03

/* converter resolution */
#define RES_9BIT    0x00
#define RES_10BIT   0x01
#define RES_11BIT   0x02
#define RES_12BIT   0x03

/* configuration register values */
typedef union{
    struct{
        bool shutdown_mode:1;
        bool thermostat_mode:1;
        bool polarity:1;
        uint8_t fault_queue:2;
        uint8_t converter_resolution:2;
        bool one_shot:1;
    };
    struct{
        uint8_t byte:8;
    };
} tempsens_config;

static void tpm245_write_reg(uint8_t reg_add, uint8_t value);

void tmp245_init(){
    tempsens_config config;
    config.converter_resolution = RES_12BIT;
    config.shutdown_mode = false;
    config.thermostat_mode = false;
    config.polarity = false;
    config.fault_queue = 0;
    config.one_shot = false;
    /* write configuration register */
    tpm245_write_reg(CONFIGURATION_REG, config.byte);
}

uint16_t tmp245_read_temp(){
    hal_i2c_start(HAL_TEMPSENS_ADDRESS, HAL_I2C_WRITE);
    hal_i2c_write(TEMPERATURE_REG);
    hal_i2c_rep_start(HAL_TEMPSENS_ADDRESS, HAL_I2C_READ);
    uint16_t val;
    val = hal_i2c_readAck() << 8;
    val |= hal_i2c_readNak();
    val >>= 4;
    hal_i2c_stop();
    return val;
}

void tpm245_write_reg(uint8_t reg_add, uint8_t value){
    hal_i2c_start(HAL_TEMPSENS_ADDRESS, HAL_I2C_WRITE);
    hal_i2c_write(reg_add);
    hal_i2c_write(value);
    hal_i2c_stop();
}

double tmp245_read_temp_double(){
    return tmp245_read_temp()*0.0625;
}