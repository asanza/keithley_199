/*
 * hal_i2c.c
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
 * Created on January 18, 2015, 9:40 AM
 */
#include <peripheral/i2c.h>
#include <HardwareProfile.h>
#include <hal.h>
#include <assert.h>
#include <util_ringbuff.h>
#include "hal_i2c.h"

/** Send i2c eeprom reset sequency. Needed for Microchip eeproms :S:S*/
static void hal_eeprom_reset(){
    /* Bitbang Reset Sequence. */
    PORTSetPinsDigitalOut(I2C_SDA);
    PORTSetPinsDigitalOut(I2C_SCL);
    PORTSetBits(I2C_SDA);
    PORTSetBits(I2C_SCL);
    utils_blocking_delay_ms(3);
    /* Set Start Condition */
    PORTClearBits(I2C_SDA);
    utils_blocking_delay_ms(1);
    PORTClearBits(I2C_SCL);
    utils_blocking_delay_ms(1);
    /* send nine 1 */
    PORTSetBits(I2C_SDA);
    int i = 0;
    for(i = 0; i < 9; i ++){
        PORTSetBits(I2C_SCL);
        utils_blocking_delay_ms(1);
        PORTClearBits(I2C_SCL);
        utils_blocking_delay_ms(1);
    }
    /* send a start condition */
    PORTSetBits(I2C_SCL);
    utils_blocking_delay_ms(1);
    PORTClearBits(I2C_SDA);
    utils_blocking_delay_ms(1);
    PORTClearBits(I2C_SCL);
    /* send stop condition */
    utils_blocking_delay_ms(1);
    PORTSetBits(I2C_SCL);
    utils_blocking_delay_ms(1);
    PORTSetBits(I2C_SDA);
    utils_blocking_delay_ms(1);
}

void hal_i2c_init(void){
    /* set reset secuency before initializing i2c. This is needed for 
     * microchip eeproms (just in case they lock themselves up), which
     * happens more times than I could expect from a fine component manu-
     * factured by a fine company in a perfectly fine country >:( 
     */
	hal_eeprom_reset();
    /* HardwareProfile.h defines to which i2c port is the eeprom attached. */
    I2CConfigure(HAL_I2C_BUS,HAL_I2C_CONFIG);
    /* Set the i2c scl frequency */
    uint32_t actualClock = I2CSetFrequency(HAL_I2C_BUS, PIC32_PERIPHERALBUS_FREQ, HAL_I2C_FREQ);
    if ( abs(actualClock-HAL_I2C_FREQ) > HAL_I2C_FREQ/10 ){
        /* if the requested clock is not possible. */
        assert(0);
    }
    /* Enable the I2C bus */
    I2CEnable(HAL_I2C_BUS, TRUE);
}

void hal_i2c_stop(void){
    I2C_STATUS  status;
    /* Send the Stop signal */
    I2CStop(HAL_I2C_BUS);
    /* Wait for the signal to complete */
    do{
        status = I2CGetStatus(HAL_I2C_BUS);
    } while ( !(status & I2C_STOP) );
}

bool start_transfer(bool restart){
    I2C_STATUS  status;
    /* Send the Start (or Restart) signal */
    if(restart){
        I2CRepeatStart(HAL_I2C_BUS);
    }else{
        /* Wait for the bus to be idle, then start the transfer */
        while( !I2CBusIsIdle(HAL_I2C_BUS) );
        if(I2CStart(HAL_I2C_BUS) != I2C_SUCCESS ){
            return false;
        }
    }
    /* Wait for the signal to complete */
    do{
        status = I2CGetStatus(HAL_I2C_BUS);
    } while ( !(status & I2C_START) );
    return true;
}

bool send_byte( uint8_t data )
{
    /* Wait for the transmitter to be ready */
    while(!I2CTransmitterIsReady(HAL_I2C_BUS));
    /* Transmit the byte */
    if(I2CSendByte(HAL_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION){
        return false;
    }
    /* Wait for the transmission to finish */
    while(!I2CTransmissionHasCompleted(HAL_I2C_BUS));
    return true;
}

unsigned char hal_i2c_start(unsigned char addr, hal_i2c_mode mode){
    I2C_7_BIT_ADDRESS device_addr;
    I2C_FORMAT_7_BIT_ADDRESS(device_addr,addr,mode);
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return 1; // bus collision.
    if(!send_byte(device_addr.byte))
            return 1; // bus collision.
    if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return 1; // no acknoweledge
    return 0;
}

unsigned char hal_i2c_rep_start(unsigned char addr, hal_i2c_mode mode){
    I2C_7_BIT_ADDRESS device_addr;
    I2C_FORMAT_7_BIT_ADDRESS(device_addr,addr,mode);
    /*wait while bus is bussy*/
    if(!start_transfer(true))
        return 1; // bus collision.
    if(!send_byte(device_addr.byte))
            return 1; // bus collision.
    if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return 1; // no acknoweledge
    return 0;
}

void hal_i2c_start_wait(unsigned char addr, hal_i2c_mode mode){
    I2C_7_BIT_ADDRESS device_addr;
    I2C_FORMAT_7_BIT_ADDRESS(device_addr,addr,mode);
    /*wait while bus is busy*/
    while(1){
        if(!start_transfer(false))
            return ; // bus collision.
        if(!send_byte(device_addr.byte))
            return ; // bus collision.
        if(I2CByteWasAcknowledged(HAL_I2C_BUS))
            break;
        else
            hal_i2c_stop();
    }
}

unsigned char hal_i2c_write(unsigned char data){
    if(!send_byte(data)){
        return 1;
    }
    return 0;
}

unsigned char hal_i2c_readAck(void){
    char c;
    if(I2CReceiverEnable(HAL_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        return 0; // overflow
    while(!I2CReceivedDataIsAvailable(HAL_I2C_BUS));
    I2CAcknowledgeByte(HAL_I2C_BUS, true);
    while(!I2CAcknowledgeHasCompleted(HAL_I2C_BUS));
    c = I2CGetByte(HAL_I2C_BUS);
    return c;
}

unsigned char hal_i2c_readNak(void){
    char c;
    if(I2CReceiverEnable(HAL_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        return 0; // overflow
    while(!I2CReceivedDataIsAvailable(HAL_I2C_BUS));
    I2CAcknowledgeByte(HAL_I2C_BUS, FALSE);
    while(!I2CAcknowledgeHasCompleted(HAL_I2C_BUS));
    c = I2CGetByte(HAL_I2C_BUS);
    return c;
}
