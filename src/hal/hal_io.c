/*
 * hal_io.c
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
 * Created on January 23, 2015, 8:47 PM
 */

#include <HardwareProfile.h>
#include <hal_io.h>

/* 14 segment display individual segments
 * aaaaaaaaaaa
 * f i  g   hb
 * f  i g  h b
 * f   ig h  b
 * f    ih   b
 * ennnnnjjjjj
 * e   ml k  c
 * e  m l  k c
 * e m  l   kc   
 * ddddddddddd   dp
 */
static uint16_t segments[] = {
    seg_a,
    seg_b,
    seg_c,
    seg_d,
    seg_e,
    seg_f,
    seg_g,
    seg_h,
    seg_j,
    seg_k,
    seg_l,
    seg_m,
    seg_n,
    seg_i,
    seg_dp
};

uint16_t hal_io_get_segment(int segment){
    return segments[segment];
}

void hal_io_displayport_init(void){
    /* initializes keyboard (keyboard is scanned with display digits */
    PORTSetPinsDigitalOut(DISPLAY_PORT,0xFFFF);
}

void hal_io_keyboard_init(void){
    PORTSetPinsDigitalIn(HAL_KYB_S0);
    PORTSetPinsDigitalIn(HAL_KYB_S1);
    PORTSetPinsDigitalIn(HAL_KYB_S2);
}

void hal_io_displayport_write(uint16_t segments){
    PORTClearBits(DISPLAY_PORT, 0xFFFF);
    PORTSetBits(DISPLAY_PORT, segments);
}

int hal_io_keyboard_get_channel(void){
    if(!PORTReadBits(HAL_KYB_S0))
        return 1;
    if(!PORTReadBits(HAL_KYB_S1))
        return 2;
    if(!PORTReadBits(HAL_KYB_S2))
        return 3;
    return 0;
}