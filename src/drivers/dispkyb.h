/*
 * dispkyb.h
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
 * Created on January 23, 2015, 9:04 PM
 */
#ifndef DISPKYB_H
#define	DISPKYB_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
    /* display keyboard driver */

/* DISPLAY INTERFACE */
    typedef enum {
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_UP,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_DOWN,
        KEY_CAL,
        KEY_NONE
    } key_id;

    typedef enum DISP_MODE {
        DISP_STO = 0x0010,
        DISP_RCL = 0x0004,
        DISP_FLTR = 0x0400,
        DISP_REM = 0x8000,
        DISP_VOLTS = 0x0008,
        DISP_OHMS = 0x0800,
        DISP_AMPS = 0x0080,
        DISP_AC = 0x4000,
        DISP_ZERO = 0x0100,
        DISP_AUTO = 0x0200
    } disp_mode;


    void display_kyb_init(void);
    void display_setmode(disp_mode mode);
    void display_addmode(disp_mode mode);
    void display_clearmode(disp_mode mode);
    void display_puts(char* c);
    void display_putc(char c, int pos);
    void display_test();
    void display_clear();
    void display_adc_indicator(bool set_value);
    void display_adc_indicator_toggle();
    key_id keyboard_wait_for_key();
    /* highlight a digit in the display. 0 = no digit is highlighted*/
    void display_highlight(int digit);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPKYB_H */

