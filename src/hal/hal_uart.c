/*
 * File:   uart.c
 * Author: Diego F. Asanza <f.asanza@gmail.com>
 *
 * Created on December 11, 2014, 11:07 PM
 *
 * Copyright (c) 2014, Diego F. Asanza, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 *
 */

#include <hal_uart.h>
#include <stdint.h>
#include <peripheral/uart.h>
#include <HardwareProfile.h>
#include <assert.h>

/* space to store function callbacks */
hal_uart_on_buffer_sent_callback on_data_sent[HAL_UART_NUMBER_OF_PORTS];
hal_uart_on_data_received_callback on_data_received[HAL_UART_NUMBER_OF_PORTS];

/** define databuffers for tx data. */
struct txbuffer_struct{
    uint8_t buffer[HAL_UART_BUFFER_SIZE];
    int counter; /**< will be incremented with each character transmitted. */
    int nbytes;  /**< will be decremented with each character transmitted untill = 0 */
}__attribute__((__packed__)); /*packed for byte alignment*/
static struct txbuffer_struct elb_buffer[HAL_UART_NUMBER_OF_PORTS];
/* return the actual txbuffer to be used */
static struct txbuffer_struct* get_tx_buffer(hal_uart_port port);

/* private interface. Return the tx buffer according to a given port */
static struct txbuffer_struct* get_tx_buffer(hal_uart_port port){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    return &elb_buffer[port];
}

static void SetRxTxPins(UART_MODULE uart){
    switch(uart){
        case UART3: CONFIGURE_UART3_PPS();break;
        default: assert(0);
    }
}

static UART_MODULE logic_uart2phy_uart(hal_uart_port port);

/* you should not use the buffer until a notification is received */
// TODO: Maybe sanity check buffer not empty
void hal_uart_send_buffer_async(hal_uart_port port, uint8_t* buffer,
        uint8_t size){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    assert(size > 0 && size < HAL_UART_BUFFER_SIZE );
    assert(buffer != NULL);
    /* select the respective output buffer */
    struct txbuffer_struct* tx_buffer = get_tx_buffer(port);
    /* buffer should be empty before sending a new frame */
    assert(tx_buffer->nbytes == 0);
    /* copy buffer into output buffer */
    memcpy(tx_buffer->buffer, buffer, size);
   /* enable the tx interrupt. It starts the augomagically data transmision
    * from tx_buffer.
    */
    /* copy the size of the buffer.*/
    tx_buffer->nbytes = size;
    /* set the framecounter at null */
    tx_buffer->counter = 0;

    UART_MODULE uart = logic_uart2phy_uart(port);
    INTClearFlag(INT_SOURCE_UART_TX(uart));
    INTEnable(INT_SOURCE_UART_TX(uart), INT_ENABLED);
}

void hal_uart_send_async(hal_uart_port port, uint8_t size){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    /* select the respective output buffer */
    struct txbuffer_struct* tx_buffer = get_tx_buffer(port);
    tx_buffer->nbytes = size;
    tx_buffer->counter = 0;
    UART_MODULE uart = logic_uart2phy_uart(port);
    INTClearFlag(INT_SOURCE_UART_TX(uart));
    INTEnable(INT_SOURCE_UART_TX(uart), INT_ENABLED);
}

uint8_t hal_uart_get_tx_buffer(hal_uart_port port, uint8_t** buffer){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    struct txbuffer_struct* obuffer = get_tx_buffer(port);
    *buffer = obuffer->buffer;
    return HAL_UART_BUFFER_SIZE;
}

void hal_uart_sendbreak(hal_uart_port port){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    UART_MODULE uart = logic_uart2phy_uart(port);
    UARTSendBreak(uart);
}

bool hal_uart_transmission_has_completed(hal_uart_port port){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    UART_MODULE uart = logic_uart2phy_uart(port);
    return UARTTransmissionHasCompleted(uart);
}

void hal_uart_send_byte(hal_uart_port port, uint8_t data){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    UART_MODULE uart = logic_uart2phy_uart(port);
    /* block until transmiter can send data */
    while(!UARTTransmitterIsReady(uart));
    UARTSendDataByte(uart, data);
}

static int get_baudrate(hal_uart_baudrate baudrate){
    switch (baudrate){
    case HAL_UART_BAUD_9600: return 9600;
    case HAL_UART_BAUD_38400: return 38400;
    case HAL_UART_BAUD_115200: return 115200;
    default: assert(0);
    }
}

static UART_LINE_CONTROL_MODE get_parity(hal_uart_parity parity){
    switch(parity){
    case HAL_UART_PARITY_NONE: return UART_PARITY_NONE;
    case HAL_UART_PARITY_EVEN: return UART_PARITY_EVEN;
    case HAL_UART_PARITY_ODD: return UART_PARITY_ODD;
    default: assert(0);
    }
}

static UART_LINE_CONTROL_MODE get_stop_bits(hal_uart_stop_bits stop_bits){
    switch(stop_bits){
    case HAL_UART_1_STOP_BITS: return UART_STOP_BITS_1;
    default: assert(0);
    }
}

//TODO: implement sanity checks.
hal_uart_port hal_uart_open(hal_uart_port port, hal_uart_baudrate baudrate,
                    hal_uart_parity parity,
                    hal_uart_stop_bits stop_bits){
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    /* Configure uart */
    UART_MODULE uart = logic_uart2phy_uart(port);
    SetRxTxPins(uart);
    UARTConfigure(uart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(uart, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(uart, UART_DATA_SIZE_8_BITS | get_parity(parity) | get_stop_bits(stop_bits));
    UARTSetDataRate(uart, PIC32_PERIPHERALBUS_FREQ, get_baudrate(baudrate));
    UARTEnable(uart, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    INTEnable(INT_SOURCE_UART_RX(uart),INT_ENABLED);
    return port;
}

 void hal_uart_disable_interrupts(hal_uart_port port){
    UART_MODULE uart = logic_uart2phy_uart(port);
    INTEnable(INT_SOURCE_UART_RX(uart), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_TX(uart), INT_DISABLED);
 }

/* static functions to map uart ports to elb ports */
static UART_MODULE logic_uart2phy_uart(hal_uart_port port){
    switch(port){
    case HAL_UART_PORT_1:
    case HAL_UART_PORT_2:
    case HAL_UART_PORT_3:
    case HAL_UART_PORT_4:
    case HAL_UART_PORT_5:
    return (UART_MODULE)port;
    default:
        assert(0);
    }
}

void hal_uart_interrupt_handler(hal_uart_port port) {
    UART_MODULE uart = logic_uart2phy_uart(port);
    assert(port >= HAL_UART_PORT_1 && port <= HAL_UART_NUMBER_OF_PORTS );
    /* get the txbuffer to send */
    struct txbuffer_struct *buffer = get_tx_buffer(port);
    /* If the source of interrupt is the TXInterrupt, start
     * transmitting the data in output queue. */
    if (INTGetFlag(INT_SOURCE_UART_TX(uart))) {
        /* Clear interrupt to prevent reentry */
        INTClearFlag(INT_SOURCE_UART_TX(uart));
        /* if queue is not empty, send tx data to uart while available. */
        while (buffer->nbytes > 0) {
            if (UARTTransmitterIsReady(uart)) {
                UARTSendDataByte(uart, buffer->buffer[buffer->counter++]);
                /* decrement buffer count after byte was transmitted */
                buffer->nbytes --;
            } else {
                break;
            }
        }
        /* if queue is empty, disable tx interrupt. */
        if (buffer->nbytes <= 0) {
            INTEnable(INT_SOURCE_UART_TX(uart), INT_DISABLED);
            if(on_data_sent[port]!=NULL)
                on_data_sent[port](port);
        }
    }

    /* detect uart rx errors */
    if(INTGetFlag(INT_SOURCE_UART_ERROR(uart))){
        uint8_t in_byte = 0x00;
        hal_uart_error error = HAL_UART_ERR_NONE;
        volatile UART_LINE_STATUS  lineStatus = UARTGetLineStatus(uart);
        /* detect framming error. (break)*/
        /* Framing error are only valid if data is available in buffer. */
        if(UART_FRAMING_ERROR & lineStatus){
            /* trigger an on_data_received_callback */
            error = HAL_UART_ERR_FRAMMING;
        }
        /* detect uart overrun errors. */
        if(UART_OVERRUN_ERROR & lineStatus)
        {
            error = HAL_UART_ERR_OVERRUN;
            /* TODO: Not sure what to do if buffer overruns (it means data
             * arrives faster than we are able to process. So just
             * clear error and continue with our lives as nothing happened.
             */
            UARTClearOverrunError(uart);
        }
        if(UART_PARITY_ERROR & lineStatus){
            error = HAL_UART_ERR_PARITY;
        }
        if(UARTReceivedDataIsAvailable(uart)){
            in_byte = UARTGetDataByte(uart);
        }
        if(on_data_received[port]!=NULL)
            on_data_received[port](port,in_byte,error);
        /* clear the error flag. */
        INTClearFlag(INT_SOURCE_UART_ERROR(uart));
    }
    
    /* If receive interrupt was triggered, feed user apps with data. */
    if (INTGetFlag(INT_SOURCE_UART_RX(uart))) {
        /* Clear interrupt to prevent reentry */
        INTClearFlag(INT_SOURCE_UART_RX(uart));
        /* Copy the received data into input buffer */
        while (UARTReceivedDataIsAvailable(uart)) {
            uint8_t c = UARTGetDataByte(uart);
            if(on_data_received[port]!=NULL)
                on_data_received[port](port, c,HAL_UART_ERR_NONE);
        }
    }
}

void hal_uart1_isr_handler(){
    hal_uart_interrupt_handler(HAL_UART_PORT_1);
}

void hal_uart2_isr_handler(){
    hal_uart_interrupt_handler(HAL_UART_PORT_2);
}
//TODO: Remove IOLink defines
#ifndef IO_LINK
void hal_uart3_isr_handler(){
    hal_uart_interrupt_handler(HAL_UART_PORT_3);
}
#endif
void hal_uart4_isr_handler(){
    hal_uart_interrupt_handler(HAL_UART_PORT_4);
}

void hal_uart_register_data_received(hal_uart_port port,
        hal_uart_on_data_received_callback fn){
    assert(fn);
    on_data_received[port]=fn;
}

void hal_uart_register_buffer_sent(hal_uart_port port,
        hal_uart_on_buffer_sent_callback fn){
    assert(fn);
    on_data_sent[port]=fn;
}