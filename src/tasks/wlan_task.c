/*
 * wlan_task.c
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
 * Created on September 1, 2015, 9:50 PM
 */

#include <stdio.h>
#include "hal_uart.h"

static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error);

void wlan_task(void* param){
    hal_uart_open(HAL_UART_PORT_5, HAL_UART_BAUD_9600, HAL_UART_PARITY_NONE,
        HAL_UART_1_STOP_BITS, on_data_received);
    while(1){
        //printf("Wlan Active");
        vTaskDelay(10);
    }
}

static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error){
    putchar(data);
}