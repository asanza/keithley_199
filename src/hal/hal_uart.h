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

    /* define an opaque pointer to access the uart */
    struct _hal_uart;
    typedef struct _hal_uart hal_uart;

    typedef enum{
        HAL_UART_PORT_1
    }hal_uart_port;

    /* open an uart and get a handle to it. */
    hal_uart* hal_uart_open(hal_uart_port port);

    /* send byte */
    void hal_uart_write(hal_uart_port port, uint8_t byte);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_UART_H */

