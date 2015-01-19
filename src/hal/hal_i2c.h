/*
 * hal_i2c.h
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
 * Created on January 18, 2015, 9:40 AM
 */
#ifndef HAL_I2C_H
#define	HAL_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum{
/** defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
        HAL_I2C_READ = 1,

/** defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
        HAL_I2C_WRITE = 0
    }hal_i2c_mode;


/**
 @brief initialize the I2C master interace. Need to be called only once
 @param  void
 @return none
 */
void hal_i2c_init(void);


/**
 @brief Terminates the data transfer and releases the I2C bus
 @param void
 @return none
 */
void hal_i2c_stop(void);


/**
 @brief Issues a start condition and sends address and transfer direction

 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible
 @retval   1   failed to access device
 */
unsigned char hal_i2c_start(unsigned char addr, hal_i2c_mode mode);


/**
 @brief Issues a repeated start condition and sends address and transfer direction

 @param   addr address and transfer direction of I2C device
 @retval  0 device accessible
 @retval  1 failed to access device
 */
unsigned char hal_i2c_rep_start(unsigned char addr, hal_i2c_mode mode);


/**
 @brief Issues a start condition and sends address and transfer direction

 If device is busy, use ack polling to wait until device ready
 @param    addr address and transfer direction of I2C device
 @return   none
 */
void hal_i2c_start_wait(unsigned char addr, hal_i2c_mode mode);


/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
unsigned char hal_i2c_write(unsigned char data);


/**
 @brief    read one byte from the I2C device, request more data from device
 @return   byte read from I2C device
 */
unsigned char hal_i2c_readAck(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition
 @return   byte read from I2C device
 */
unsigned char hal_i2c_readNak(void);

/**
 @brief    read one byte from the I2C device

 Implemented as a macro, which calls either i2c_readAck or i2c_readNak

 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition
 @return   byte read from I2C device
 */
unsigned char hal_i2c_read(unsigned char ack);
#define hal_i2c_read(ack)  (ack) ? hal_i2c_readAck() : hal_i2c_readNak();



#ifdef	__cplusplus
}
#endif

#endif	/* HAL_I2C_H */

