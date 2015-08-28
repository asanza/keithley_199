/*
 * disfmt.c
 *
 * Display formatter
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
 * Created on January 24, 2015, 12:10 AM
 */

#include "disfmt.h"
#include "strutils.h"
#include <sysdefs.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <diag.h>

static double get_range_value(double value, adc_range scale);

disp_mode fmt_get_disp_mode(adc_input mode)
{
    disp_mode display_indicator = 0x00000000;
    switch (mode) {
        case ADC_INPUT_VOLTAGE_AC:
            display_indicator |= DISP_AC;
        case ADC_INPUT_VOLTAGE_DC:
            display_indicator |= DISP_VOLTS;
            break;
        case ADC_INPUT_CURRENT_AC:
            display_indicator |= DISP_AC;
        case ADC_INPUT_CURRENT_DC:
            display_indicator |= DISP_AMPS;
            break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
            display_indicator |= DISP_OHMS;
            break;
        default:
            break;
    }
    return display_indicator;
}

void fmt_format_string(char* buff, int buffsize, adc_range scale, double value)
{
    memset(buff, ' ', buffsize * sizeof(char));
    switch (scale) {
        case ADC_RANGE_3:
        case ADC_RANGE_3K:
        case ADC_RANGE_3M:
        {
            if (fabs(value) >= ADC_OVERFLOW) {
                sprintf(buff, " O.VERFL");
            }else{
                utils_dtofixstr(buff, 6, 5, value);
            }
        }
            break;
        case ADC_RANGE_30m:
        case ADC_RANGE_30:
        case ADC_RANGE_30K:
        case ADC_RANGE_30M:
        {
            if (fabs(value) >= ADC_OVERFLOW * 10) {
                sprintf(buff, " OV.ERFL");
            }else{
                utils_dtofixstr(buff, 6, 4, value);
            }
        }
            break;
        case ADC_RANGE_300:
        case ADC_RANGE_300K:
        case ADC_RANGE_300M:
        case ADC_RANGE_300m:
        {
            if (fabs(value) >= ADC_OVERFLOW * 100) {
                sprintf(buff, " OVE.RFL");
            }else{
                utils_dtofixstr(buff, 6, 3, value);
            }
        }
            break;
        default: break;
    }
}

void fmt_append_scale(char* buffer, adc_input mode, adc_range range)
{
    switch (mode) {
        case ADC_INPUT_VOLTAGE_AC:
            *buffer = '~';
        case ADC_INPUT_VOLTAGE_DC:
        {
            if (range == ADC_RANGE_300m)
                strcat(buffer, "mV");
            else
                strcat(buffer, "V");
        }
            break;
        case ADC_INPUT_CURRENT_AC:
            *buffer = '~';
        case ADC_INPUT_CURRENT_DC:
        {
            if (range == ADC_RANGE_30m)
                strcat(buffer, "mA");
            else
                strcat(buffer, "A");
        }
            break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
        {
            switch (range) {
                case ADC_RANGE_300: strcat(buffer, "o");
                    break;
                case ADC_RANGE_3K:
                case ADC_RANGE_30K:
                case ADC_RANGE_300K: strcat(buffer, "Ko");
                    break;
                case ADC_RANGE_3M:
                case ADC_RANGE_30M:
                case ADC_RANGE_300M: strcat(buffer, "Mo");
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
}

static void fmt_write_display(char* buffer, int size, adc_range range, adc_input mode,
    double value)
{
    fmt_format_string(buffer, NUMBER_OF_CHARACTERS, range, get_range_value(value, range));
    fmt_append_scale(buffer, mode, range);
    display_puts(buffer);
}

static key_id fmt_get_key()
{
    key_id val = display_wait_for_key();
    if (val == KEY_NONE) val = display_wait_for_key();
    display_wait_for_key();
    return val;
}

double fmt_get_refval(double val, adc_input mode, adc_range range)
{
    double sign;
    if(val >= 0) sign = 1;
    else sign = -1;
    key_id key = KEY_NONE;
    int hld_i = 2;
    display_evt_clear();
    char buffer[NUMBER_OF_CHARACTERS];
    do {
        if (key != KEY_NONE) {
            if (hld_i == 3) {
                if (key < 3) {
                    val = sign*key;
                } else {
                    if (key == 3) val = sign*key;
                    display_highlight(hld_i--);
                }
            } else {
                if (key <= 9) {
                    int i;
                    double dec = 1;
                    for (i = 4; i <= hld_i; i++) {
                        dec = dec * 0.1;
                    }
                    val += sign*key*dec;
                }
            }
        }
        fmt_write_display(buffer, NUMBER_OF_CHARACTERS, range, mode, val);
        if (hld_i > 7) hld_i = 2;
        display_highlight(hld_i++);
        key = fmt_get_key();
    } while (key != KEY_CAL);
    /* buffer contains the incomming user value */
    buffer[0] = ' '; // replace ac symbol.
    buffer[8] = '\0';
    val = utils_strtod(buffer);
    display_highlight(0);
    return val;
}

static double get_range_value(double value, adc_range scale)
{
    switch (scale) {
        case ADC_RANGE_3:
        case ADC_RANGE_3K:
        case ADC_RANGE_3M:
            return value;
        case ADC_RANGE_30m:
        case ADC_RANGE_30:
        case ADC_RANGE_30K:
        case ADC_RANGE_30M:
            return value * 10;
        case ADC_RANGE_300:
        case ADC_RANGE_300K:
        case ADC_RANGE_300M:
        case ADC_RANGE_300m:
            return value * 100;
        default: break;
    }
    return 0;
}