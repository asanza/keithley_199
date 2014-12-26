/*
 * hal_uart.c
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
 * Created on December 27, 2014, 3:11 AM
 */


#include <hal_uart.h>
#include <peripheral/uart.h>
#include <assert.h>
#include "HardwareProfile.h"

#define BAUD_TOL 0.01  /* 1 percent */
#define MIN_BAUD(x) ((uint32_t)( x - x * BAUD_TOL ))
#define MAX_BAUD(x) ((uint32_t)( x + x * BAUD_TOL ))

static UART_MODULE port_to_module(uint8_t port)
{
    switch (port){
#ifdef HAL_UART_1
        case 1: return HAL_UART_1;break;
#endif
#ifdef HAL_UART_2
        case 2: return HAL_UART_2;break;
#endif
#ifdef HAL_UART_3
        case 3: return HAL_UART_3;break;
#endif
#ifdef HAL_UART_4
        case 4: return HAL_UART_4;break;
#endif
        default: return UART_NUMBER_OF_MODULES;
    }
}

hal_uart_error hal_uart_open(uint8_t port, uint32_t baudrate, hal_uart_parity parity,
            hal_uart_stop_bits stop_bits){
    UART_MODULE hwuart = 0x00;
    UART_LINE_CONTROL_MODE mode = 0x00;
    switch (port){
#ifdef HAL_UART_1
        case 1: hwuart = HAL_UART_1; CONFIGURE_UART1_PPS();break;
#endif
#ifdef HAL_UART_2
        case 2: hwuart = HAL_UART_2; CONFIGURE_UART2_PPS();break;
#endif
#ifdef HAL_UART_3
        case 3: hwuart = HAL_UART_3; CONFIGURE_UART3_PPS();break;
#endif
#ifdef HAL_UART_4
        case 4: hwuart = HAL_UART_4; CONFIGURE_UART4_PPS();break;
#endif
        default: return HAL_UART_ERR_PORT_NOT_AVAIL;
    }
    switch(parity){
        case HAL_UART_PARITY_EVEN: mode |= UART_PARITY_EVEN; break;
        case HAL_UART_PARITY_ODD:   mode |= UART_PARITY_ODD; break;
        case HAL_UART_PARITY_NONE: mode |= UART_PARITY_NONE; break;
        default: assert(0);
    }
    switch(stop_bits){
        case HAL_UART_STOP_BITS_1: mode |= UART_STOP_BITS_1; break;
        case HAL_UART_STOP_BITS_2: mode |= UART_STOP_BITS_2; break;
        default: assert(0);
    }
    /* Initialize Uart Module */
    UARTConfigure(hwuart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(hwuart, UART_INTERRUPT_ON_TX_BUFFER_EMPTY
            | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(hwuart, UART_DATA_SIZE_8_BITS | mode);
    uint32_t br = UARTSetDataRate(hwuart, SYS_CLK, baudrate);
    if(br < MIN_BAUD(baudrate) || br > MAX_BAUD(baudrate))
        return HAL_UART_ERR_BAUDRATE_NOT_AVAIL;
    UARTEnable(USB_UART, UART_ENABLE_FLAGS(UART_PERIPHERAL|UART_RX|UART_TX));
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_byte(uint8_t port, uint8_t byte){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    while(!UARTTransmitterIsReady(uart));
    UARTSendDataByte(uart, byte);
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_buffer(uint8_t port, uint8_t* buffer,
        uint32_t buffer_size){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;

    return HAL_UART_ERR_NONE;
}