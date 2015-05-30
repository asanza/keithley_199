/*
 * usb_uart.c
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
 * Created on May 30, 2015, 9:43 PM
 */


#include <hal_uart.h>
#include <stdio.h>
#include "usb_uart.h"

#define USB_UART HAL_UART_PORT_3

void usb_uart_init(void){
    hal_uart_open(USB_UART,HAL_UART_BAUD_115200,HAL_UART_PARITY_NONE, HAL_UART_1_STOP_BITS);
}

void _mon_putc(char c){
    hal_uart_send_byte(USB_UART, c);
}