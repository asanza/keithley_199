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
#include <FreeRTOS.h>
#include <queue.h>
#include "hal_uart.h"
#include "task.h"

static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error);
static void on_data_sent(hal_uart_port port);

static QueueHandle_t qinput;

void wlan_task(void* param){
    hal_uart_open(HAL_UART_PORT_5, HAL_UART_BAUD_9600, HAL_UART_PARITY_NONE,
        HAL_UART_1_STOP_BITS, on_data_received);
    qinput = xQueueCreate(1, sizeof(char));
    hal_uart_register_buffer_sent(HAL_UART_PORT_5, on_data_sent);
    char t;
    while(1){
        hal_uart_send_buffer_async(HAL_UART_PORT_5, "AT\r\n", 4);
        //xQueueReceive(qinput, &t, portMAX_DELAY);
        //putchar(t);
        vTaskDelay(500);
        printf("Wlan Active\n");
    }
}

static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error){
    putchar(data);
}

static void on_data_sent(hal_uart_port port){
    int i = 0;
}