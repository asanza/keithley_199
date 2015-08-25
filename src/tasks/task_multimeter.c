/*
 * task_multimeter.c
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
 * Created on July 17, 2015, 10:43 PM
 */

#include <diag.h>
#include <system.h>
#include "settings.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <dispkyb.h>
#include <disfmt.h>

#include "semphr.h"



void task_multimeter(void *params){
    DIAG("Loaded");
    char buff[NUMBER_OF_CHARACTERS];
    while(1){
        adc_input val = settings_get_input();
        hal_disp_adci_toggle();
        switch(val){
            case ADC_INPUT_VOLTAGE_AC: display_puts("VOLT AC"); continue;
            //case ADC_INPUT_VOLTAGE_DC: display_puts("VOLT DC"); break;
            case ADC_INPUT_CURRENT_AC: display_puts("AMP  AC"); continue;
            //case ADC_INPUT_CURRENT_DC: display_puts("AMP DC"); continue;
            case ADC_INPUT_RESISTANCE_2W: display_puts("RES 2W"); continue;
            case ADC_INPUT_RESISTANCE_4W: display_puts("RES 4W"); continue;
            default: break;
        }
        double value = system_read_input();
        printf("%f\n",value);
        fmt_format_string(buff, NUMBER_OF_CHARACTERS, settings_get_range(),value);
        fmt_append_scale(buff,settings_get_input(), settings_get_range());
        display_puts(buff);
    }
}
