/*
 * hal_uart.h
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
#ifndef HAL_UART_H
#define	HAL_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
    
    /**@addtogroup hal_uart
     * @brief Hardware Abstraction Layer, uart interface
     * @{
     */
    #define HAL_UART_BUFFER_SIZE    56

    typedef enum{
        HAL_UART_ERR_NONE,
                HAL_UART_ERR_PARITY,
                HAL_UART_ERR_FRAMMING,
                HAL_UART_ERR_OVERRUN
    }hal_uart_error;

    /**@enum available uart ports */
    typedef enum{
        HAL_UART_PORT_1 = 0, /**< UART1 */
        HAL_UART_PORT_2, /**< UART2 */
        HAL_UART_PORT_3, /**< UART3 */
        HAL_UART_PORT_4, /**< UART4 */
        HAL_UART_PORT_5, /**< UART5 */
        HAL_UART_NUMBER_OF_PORTS
    }hal_uart_port;

    typedef enum{
        HAL_UART_BAUD_9600,
                HAL_UART_BAUD_38400,
                HAL_UART_BAUD_115200
    }hal_uart_baudrate;

    typedef enum{
        HAL_UART_PARITY_NONE,
                HAL_UART_PARITY_EVEN,
                HAL_UART_PARITY_ODD
    }hal_uart_parity;

    typedef enum{
        HAL_UART_1_STOP_BITS
    }hal_uart_stop_bits;
    
    /** Callback prototypes */
    typedef void (*hal_uart_on_buffer_sent_callback)(hal_uart_port port);
    typedef void (*hal_uart_on_data_received_callback)(hal_uart_port port, uint8_t data, hal_uart_error error);

    
    /** Open a uart port
     * @param port
     * @param baudrate
     * @param parity
     * @param stop_bits
     * @return uart port.
     */
    hal_uart_port hal_uart_open(hal_uart_port port, hal_uart_baudrate baudrate,
        hal_uart_parity parity,
        hal_uart_stop_bits stop_bits, hal_uart_on_data_received_callback data_received);


    /** Register a handler function for incomming data.
     * @param port uart port where data is expected
     * @param fn handler function
     */
    void hal_uart_register_data_received(hal_uart_port port,
            hal_uart_on_data_received_callback fn);

    /** Send a buffer asynchronously.
     * This function sends the passed buffer asynchronously. Buffer is copied
     * so it is safe to use it again. Buffer should be smaller than HAL_UART_BUFFER_SIZE.
     * @param port uart port to be used
     * @param buffer buffer to be sended.
     * @param size size of the buffer. Should be smaller than HAL_UART_BUFFER_SIZE.
     */
    void hal_uart_send_buffer_async(hal_uart_port port, uint8_t* buffer,
        uint8_t size);

    /** Send a break character (13 bits 0)
     * @param port
     */
    void hal_uart_sendbreak(hal_uart_port port);

    /** Return true if buffer is empty and ready for new data.
     * @param port
     * @return true if data was sended through buffer.
     */
    bool hal_uart_transmission_has_completed(hal_uart_port port);

    /** send a byte synchronously
     * This functions returns after the byte was sended.
     * @param port uart port
     * @param data byte to be sended
     */
    void hal_uart_send_byte(hal_uart_port port, uint8_t data);

    /**
     * Get a pointer to the underliying tx_buffer
     * @param port  the uart port to get the buffer from
     * @param buffer    pointer to the returned buffer.
     * @return size of the underliying buffer.
     */
    uint8_t hal_uart_get_tx_buffer(hal_uart_port port, uint8_t** buffer);

    /**
     * Send the underliying buffer asynchronously. The buffer should be
     * previously obtained with hal_uart_get_tx_buffer.
     * @param port the uart port to send data from.
     * @param size size of the data copied into the underlying buffer
     */
    void hal_uart_send_async(hal_uart_port port, uint8_t size);


    /**
     * Disable tx and rx interrupts for given port.
     * @param port the uart port
     */
    void hal_uart_disable_interrupts(hal_uart_port port);

    /**@}*/


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_UART_H */
