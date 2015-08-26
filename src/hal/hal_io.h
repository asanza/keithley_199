/*
 * hal_io.h
 *
 * Copyright (c) ${year}, Diego F. Asanza. All rights reserved.
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
 * Created on January 23, 2015, 8:47 PM
 */
#ifndef HAL_IO_H
#define	HAL_IO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
    typedef enum{
    SYSERR_LED,
            SYSOK_LED,
            AUX_LED
}IO_LED;

void hal_io_init(void);

void hal_io_displayport_write(uint16_t segments);
uint16_t hal_io_get_segment(int segment);
int hal_io_keyboard_get_channel(void);
uint16_t hal_io_displayport_map_char_to_segments(char c);
void hal_io_toggle_led(IO_LED led);
void hal_io_set_led(IO_LED led);
void hal_io_clear_led(IO_LED led);

void hal_io_set_debugpin();
void hal_io_clear_debugpin();
void hal_io_toggle_debugpin();
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_IO_H */

