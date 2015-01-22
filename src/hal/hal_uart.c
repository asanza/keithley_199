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
#include <peripheral/int.h>
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

static QueueHandle_t rx_queues[HAL_UART_COUNT];
static QueueHandle_t tx_queues[HAL_UART_COUNT];

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

hal_uart_error hal_uart_open(hal_uart_port port, uint32_t baudrate, hal_uart_parity parity,
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
    rx_queues[port] = xQueueCreate(RX_BUFFER_SIZE, sizeof(uint8_t));
    /* Initialize Uart Module */
    UARTConfigure(hwuart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(hwuart, UART_INTERRUPT_ON_TX_BUFFER_EMPTY
            | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(hwuart, UART_DATA_SIZE_8_BITS | mode);
    uint32_t br = UARTSetDataRate(hwuart, SYS_CLK, baudrate);
    if(br < MIN_BAUD(baudrate) || br > MAX_BAUD(baudrate))
        return HAL_UART_ERR_BAUDRATE_NOT_AVAIL;
    UARTEnable(hwuart, UART_ENABLE_FLAGS(UART_PERIPHERAL|UART_RX|UART_TX));
    INTSetVectorPriority(INT_VECTOR_UART(hwuart),3);
    INTClearFlag(INT_SOURCE_UART_RX(hwuart));
    INTClearFlag(INT_SOURCE_UART_TX(hwuart));
    INTEnable(INT_SOURCE_UART_RX(hwuart), INT_ENABLED);
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_byte(hal_uart_port port, uint8_t byte){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    xQueueSend(tx_queues[port],&byte,portMAX_DELAY);
    /* set flag to start transmissions */
    INTEnable(INT_SOURCE_UART_TX(uart), INT_ENABLED);
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_send_buffer(hal_uart_port port, const uint8_t* buffer,
        uint32_t buffer_size){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    uint8_t temp = 0;
    while(buffer_size--){
        if(xQueueSend(tx_queues[port],buffer++,portMAX_DELAY) == errQUEUE_FULL)
            INTEnable(INT_SOURCE_UART_TX(uart), INT_ENABLED);
    }
    /* send the last bytes if queue not yet empty */
    if(xQueuePeek(tx_queues[port],&temp, 0) == pdTRUE)
        INTEnable(INT_SOURCE_UART_TX(uart), INT_ENABLED);
    return HAL_UART_ERR_NONE;
}

hal_uart_error hal_uart_receive_buffer(hal_uart_port port, uint8_t* buffer,
           uint32_t buffer_size){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return HAL_UART_ERR_PORT_NOT_AVAIL;
    while(buffer_size --){
        xQueueReceive(rx_queues[port],buffer++,portMAX_DELAY);
    }
    return HAL_UART_ERR_NONE;
}

int hal_uart_receive(hal_uart_port port, uint8_t* buffer, uint32_t buffer_size,
        int timeout){
    UART_MODULE uart = port_to_module(port);
    if(uart == UART_NUMBER_OF_MODULES) return -1;
    int rec_bytes = 0;
    while(buffer_size--){
        if(xQueueReceive(rx_queues[port], buffer++, timeout/portTICK_PERIOD_MS)){
            rec_bytes++;
        }else{
            break;
        }
    }
    return rec_bytes;
}

static void generic_handler(hal_uart_port port){
    
    UART_MODULE uart = port_to_module(port);
    portBASE_TYPE xHigherPriorityTaskWoken;
    if(INTGetFlag(INT_SOURCE_UART_TX(uart))){
        char data;
        while(UARTTransmitterIsReady(uart)){
            if(xQueueReceiveFromISR(tx_queues[port],&data,&xHigherPriorityTaskWoken)){
                UARTSendDataByte(uart,data);
            }
            else{
                break;
            }
        }
        if(!xQueuePeekFromISR(tx_queues[port],&data))
            INTEnable(INT_SOURCE_UART_TX(uart), INT_DISABLED);
        INTClearFlag(INT_SOURCE_UART_TX(uart));
    }
    
    if(INTGetFlag(INT_SOURCE_UART_RX(uart))){
        /* get data from buffer and put in queue */
        while(UARTReceivedDataIsAvailable(uart)){
            char t = UARTGetDataByte(uart);
            xQueueSendFromISR(rx_queues[port],&t,&xHigherPriorityTaskWoken);
        }
        INTClearFlag(INT_SOURCE_UART_RX(uart));
    }

    if(INTGetFlag(INT_SOURCE_UART_ERROR(uart))){
        UART_LINE_STATUS line_status = UARTGetLineStatus(uart);
        switch(line_status){
            case UART_OVERRUN_ERROR: break;
        }
        INTClearFlag(INT_SOURCE_UART_ERROR(uart));
    }
}

#ifdef TEST
#define INTERRUPT(int_vector) void
#else
#define INTERRUPT(int_vector) void __attribute__((nomips16, interrupt(), vector(int_vector)))
#endif
/* uart interrupts */
#if defined HAL_UART_1
INTERRUPT(_UART_1_VECTOR) uart1_int_wrapper();
void uart1_int_handler(){}
#endif
#if defined HAL_UART_2
INTERRUPT(_UART_2_VECTOR) uart2_int_wrapper();
void uart2_int_handler(){}
#endif
#if defined HAL_UART_3
INTERRUPT(_UART_3_VECTOR) uart3_int_wrapper();
void uart3_int_handler(){ generic_handler(HAL_UART_PORT_3); }
#endif
#if defined HAL_UART_4
INTERRUPT(_UART_4_VECTOR) uart4_int_wrapper();
void uart4_int_handler(){}
#endif
