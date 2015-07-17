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

static void hal_io_displayport_init(void);
static void hal_io_keyboard_init(void);

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

void hal_io_init(void){
    PORTSetPinsDigitalOut(BRD_GREEN_LED);
    PORTClearBits(BRD_GREEN_LED);
    PORTSetPinsDigitalOut(BRD_AUX_LED);
    PORTClearBits(BRD_AUX_LED);
    PORTSetPinsDigitalOut(BRD_RED_LED);
    PORTSetBits(BRD_RED_LED);
    PORTSetPinsDigitalOut(DEBUG_PIN_0);
    PORTClearBits(DEBUG_PIN_0);
    hal_io_displayport_init();
    hal_io_keyboard_init();
}

static void hal_io_displayport_init(void){
    /* initializes keyboard (keyboard is scanned with display digits */
    PORTSetPinsDigitalOut(DISPLAY_PORT,0xFFFF);
}

static void hal_io_keyboard_init(void){
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

/* bits from 2^15 to 2^0. 2^0 is not connected and should be always 0.
 * n dp d l h i j k m g a f c e b x
 * aaaaaaaaaaa
 * f i  g   hb
 * f  i g  h b
 * f   ig h  b
 * f    ih   b
 * ennnnnjjjjj
 * e   ml k  c
 * e  m l  k c
 * e m  l   kc
 * ddddddddddd
 */
static uint16_t chartable[] = {
    0x823E, 0x326A, 0x2034, 0x306A, 0xA034, 0x8034, 0x223C,
    0x821E, 0x3060, 0x200E, 0x8914, 0x2014, 0x0C1E, 0x051E,
    0x203E, 0x8236, 0x213E, 0x8336, 0xA238, 0x1060, 0x201E,
    0x0894, 0x019E, 0x0D80, 0xA21A, 0x28A0, 0x203E, 0x1040,
    0xA226, 0x222A, 0x821A, 0xA238, 0xA23C, 0x002A, 0xA23E,
    0xA23A, 0x9240, 0x8200, 0x8E20, 0x920C, 0x8232, 0x0000,
    0x4000, 0xA20E, 0x1222, 0xA200, 0x9FC1, 0x0518, 0x0886
};

uint16_t hal_io_displayport_map_char_to_segments(char c){
    /* TODO: Check c inside allowed range */
    switch(c){
        case 'm': return chartable[39];
        case '+': return chartable[36];
        case '-': return chartable[37];
        case 'o': return chartable[38]; // OHms (omega)
        case 'g': return chartable[40]; // degrees 
        case ' ': return chartable[41];
        case '.': return chartable[42];
        case 'd': return chartable[43];
        case '?': return chartable[44];
        case '=': return chartable[45];
        case '*': return chartable[46];
        case '~': return chartable[47]; // Ac Symbol
        case '#': return chartable[48]; // inverted AC Symbol
    }
    if(c <= 0x39){
        return chartable[c - 22];
    }
    return chartable[c - 0x41];
}

void hal_io_toggle_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTToggleBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTToggleBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTToggleBits(BRD_AUX_LED); break;
    }
}

void hal_io_set_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTClearBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTClearBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTClearBits(BRD_AUX_LED); break;
    }
}

void hal_io_clear_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTSetBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTSetBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTSetBits(BRD_AUX_LED); break;
    }
}

void hal_io_set_debugpin(){
    PORTSetBits(DEBUG_PIN_0);
}
void hal_io_clear_debugpin(){
    PORTClearBits(DEBUG_PIN_0);
}

void hal_io_toggle_debugpin(){
    PORTToggleBits(DEBUG_PIN_0);
}
