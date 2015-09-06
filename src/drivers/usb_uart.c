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
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "usb_uart.h"

/** number of characters in the input queue */
#define USB_QUEUE_LENGTH 50
#define EOL '\n'
#define CR '\r'

QueueHandle_t usb_queue;

#define USB_UART HAL_UART_PORT_3

static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error);

void usb_uart_init(void){
    usb_queue = xQueueCreate(USB_QUEUE_LENGTH,sizeof(char));
    hal_uart_open(USB_UART,HAL_UART_BAUD_115200,HAL_UART_PARITY_NONE, HAL_UART_1_STOP_BITS,
        on_data_received);
}

void _mon_putc(char c){
    hal_uart_send_byte(USB_UART, c);
}



static void on_data_received(hal_uart_port port, uint8_t data, hal_uart_error error){
    portBASE_TYPE xHigherPriorityTaskWoken;
    xQueueSendFromISR(usb_queue,&data, &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

int usb_uart_readline(char* buffer, int size){
    char c;
    int i;
    for(i = 0; i < size - 1; i++){
        xQueueReceive(usb_queue,&c,portMAX_DELAY);
        buffer[i] = c;
        if(c == EOL || c == CR){
            buffer[i+1] = '\0'; // guarantee null terminator
            break;
        }
    }
    /* guarantee null terminator */
    buffer[size - 1] = '\0';
    /* reset queue */
    xQueueReset(usb_queue);
    if(i < size - 2)
        return i+1;
    else{
        return -1; // Buffer Overflow
    }
}