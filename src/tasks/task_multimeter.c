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

#include "settings.h"
#include <FreeRTOS.h>
#include "task.h"
#include "portmacro.h"

void task_multimeter(void *params){
    DIAG("Loaded");
    while(1){
        adc_input val = settings_get_input();
        switch(val){
            case ADC_INPUT_VOLTAGE_AC: display_puts("VOLT AC"); break;
            case ADC_INPUT_VOLTAGE_DC: display_puts("VOLT DC"); break;
            case ADC_INPUT_CURRENT_AC: display_puts("AMP AC"); break;
            case ADC_INPUT_CURRENT_DC: display_puts("AMP DC"); break;
            case ADC_INPUT_RESISTANCE_2W: display_puts("RES 2W"); break;
            case ADC_INPUT_RESISTANCE_4W: display_puts("RES 4W"); break;
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
