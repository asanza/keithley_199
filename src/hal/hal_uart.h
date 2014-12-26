/*
 * hal_uart.h
 *
 * Copyright (c) 2014, Diego F. Asanza. All rights reserved.
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
 * Created on December 13, 2014, 11:21 PM
 */
#ifndef HAL_UART_H
#define	HAL_UART_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
    
/* Buffers is allocated statically. Adapt following lines according your
 * requeriments. */
#define RX_BUFFER_LENGTH 20 /**< RX Buffer in Bytes */
#define TX_BUFFER_LENGTH 20 /**< TX Buffer in Bytes */

/* Standard error definitions for this module */
    typedef enum{
        HAL_UART_ERR_NONE,
                HAL_UART_ERR_PORT_NOT_AVAIL,
                HAL_UART_ERR_BAUDRATE_NOT_AVAIL,
                HAL_UART_ERR_NA
    }hal_uart_error;

    typedef enum{
        HAL_UART_PARITY_NONE,
                HAL_UART_PARITY_ODD,
                HAL_UART_PARITY_EVEN
    }hal_uart_parity;

    typedef enum{
        HAL_UART_STOP_BITS_1,
                HAL_UART_STOP_BITS_2
    }hal_uart_stop_bits;

hal_uart_error hal_uart_open(uint8_t port, uint32_t baudrate, hal_uart_parity parity,
            hal_uart_stop_bits stop_bits);
    

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_UART_H */

