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

#include <hal.h>
#include <hal_uart.h>
#include <peripheral/uart.h>
#include <assert.h>
#include <util_ringbuff.h>
#include "HardwareProfile.h"
#ifdef TEST
#include "os_test.h"
#else
#include "FreeRTOS.h"
#include "queue.h"
#endif

#define BAUD_TOL 0.01  /* 1 percent */
#define MIN_BAUD(x) ((uint32_t)( x - x * BAUD_TOL ))
#define MAX_BAUD(x) ((uint32_t)( x + x * BAUD_TOL ))

/* space for the rx and tx buffers */
#define RX_BUFFER_SIZE 20
#define TX_BUFFER_SIZE 20

QueueHandle_t rx_queues[HAL_UART_COUNT];
QueueHandle_t tx_queues[HAL_UART_COUNT];

static QueueHandle_t* get_rxqueue(uint8_t port){
    return &rx_queues[port];
}
static QueueHandle_t* get_txqueue(uint8_t port){
    return &tx_queues[port];
}

static UART_MODULE port_to_module(uint8_t port){
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
        case 1:
            hwuart = HAL_UART_1;
            CONFIGURE_UART1_PPS();
            break;
#endif
#ifdef HAL_UART_2
        case 2:
            hwuart = HAL_UART_2;
            CONFIGURE_UART2_PPS();
            break;
#endif
#ifdef HAL_UART_3
        case 3:
            hwuart = HAL_UART_3;
            CONFIGURE_UART3_PPS();
            break;
#endif
#ifdef HAL_UART_4
        case 4:
            hwuart = HAL_UART_4;
            CONFIGURE_UART4_PPS();
            break;
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
    /* get the next free buffer and initialize it */
    tx_queues[port] = xQueueCreate(TX_BUFFER_SIZE, sizeof(uint8_t));
    rx_queues[port] = xQueueCreate(TX_BUFFER_SIZE, sizeof(uint8_t));
    /* Initialize Uart Module */
    UARTConfigure(hwuart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(hwuart, UART_INTERRUPT_ON_TX_BUFFER_EMPTY
            | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(hwuart, UART_DATA_SIZE_8_BITS | mode);
    uint32_t br = UARTSetDataRate(hwuart, SYS_CLK, baudrate);
    if(br < MIN_BAUD(baudrate) || br > MAX_BAUD(baudrate))
        return HAL_UART_ERR_BAUDRATE_NOT_AVAIL;
    UARTEnable(HAL_UART_3, UART_ENABLE_FLAGS(UART_PERIPHERAL|UART_RX|UART_TX));
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_byte(uint8_t port, uint8_t byte){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    QueueHandle_t buffer = get_txqueue(port);
    assert(buffer);
    xQueueSend(buffer,&byte,portMAX_DELAY);
    /* set flag to start transmissions */
    INTSetFlag(INT_U1TX + uart);
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_buffer(uint8_t port, const uint8_t* buffer,
        uint32_t buffer_size){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    QueueHandle_t queue = get_txqueue(port);
    uint8_t temp = 0;
    while(buffer_size--){
        if(xQueueSend(queue,buffer++,portMAX_DELAY) == errQUEUE_FULL)
            INTSetFlag(INT_U1TX + uart);
    }
    /* send the last bytes if queue not yet empty */
    if(xQueuePeek(queue,&temp, 0) == pdTRUE)
        INTSetFlag(INT_U1TX + uart);
    return HAL_UART_ERR_NONE;
}

#ifdef TEST
#define INTERRUPT(int_vector) void
#else
#define INTERRUPT(int_vector) void __attribute__((nomips16, interrupt(), vector(int_vector)))
#endif
/* uart interrupts */
#if defined HAL_UART_1
INTERRUPT(_UART_1_VECTOR) uart1_int_wrapper();
#endif
#if defined HAL_UART_2
INTERRUPT(_UART_2_VECTOR) uart2_int_wrapper();
#endif
#if defined HAL_UART_3
INTERRUPT(_UART_3_VECTOR) uart3_int_wrapper();
#endif
#if defined HAL_UART_4
INTERRUPT(_UART_4_VECTOR) uart4_int_wrapper();
#endif

static void generic_handler(int port){
    
    UART_MODULE uart = port_to_module(port);
    QueueHandle_t queue;
    portBASE_TYPE xHigherPriorityTaskWoken;
    if(INTGetFlag(INT_SOURCE_UART_TX(uart))){
        queue = get_txqueue(port);
        char data;
        while(UARTTransmitterIsReady(uart)){
            if(xQueueReceiveFromISR(queue,&data,&xHigherPriorityTaskWoken)){
                UARTSendDataByte(uart,data);
            }
            else{
                break;
            }
        }
        if(xQueueIsQueueEmptyFromISR(queue))
            INTClearFlag(INT_SOURCE_UART_TX(uart));
    }
    
    if(INTGetFlag(INT_SOURCE_UART(uart))){
        queue = get_rxqueue(port);
        /* get data from buffer and put in queue */
        while(UARTReceivedDataIsAvailable(uart)){
            char t = UARTGetDataByte(uart);
            xQueueSendFromISR(queue,&t,&xHigherPriorityTaskWoken);
        }
        INTClearFlag(INT_SOURCE_UART_RX(uart));
    }

    if(INTGetFlag(INT_SOURCE_UART_ERROR(uart))){
        UART_LINE_STATUS line_status = UARTGetLineStatus(uart);
        switch(line_status){
            case UART_OVERRUN_ERROR: break;
        }
    }
}

void uart1_int_handler(){

}

void uart2_int_handler(){

}

void uart3_int_handler(){
    generic_handler(HAL_UART_3);
}

void uart4_int_handler(){
    
}