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
#include <strutils.h>
#include <math.h>
#include "semphr.h"


static void set_new_range(double value, system_flags_t flag);

void task_multimeter(void *params)
{
    DIAG("Loaded");
    char buff[NUMBER_OF_CHARACTERS];
    system_flags_t flag;
    double value;
    while (1) {
        hal_disp_adci_toggle();
        value = system_read_input(&flag); 
        if (settings_is_autorange())
            set_new_range(value,  flag);
        fmt_format_string(buff, NUMBER_OF_CHARACTERS, settings_get_range(),
            settings_get_resolution(), value, flag);
        fmt_append_scale(buff, settings_get_input(), settings_get_range());
        display_puts(buff);
        /*TODO: give some space for other tasks to call system */
        vTaskDelay(1);
    }
}

static void set_new_range(double value, system_flags_t flag)
{
    int wset = 0;
    double maxl = system_get_max(settings_get_range());
    if(fabs(value) >= maxl  || (flag&SYSTEM_OVERFLOW) ){
        settings_range_up();
        wset++;
    }else{
        settings_range_down();
        maxl = system_get_max(settings_get_range());
        if(maxl <= fabs(value)){
            settings_range_up();
        }else{
            wset++;
        }
    }
    if(wset){
        calibration_restore();
        system_set_configuration(settings_get_input(), settings_get_range(),
            settings_get_integration_period(), settings_get_channel(),
            calibration_gain(), calibration_offset(), settings_get_resolution());
    }
}