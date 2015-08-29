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
#include "strutils.h"
#include "tmp275.h"



void task_multimeter(void *params){
    DIAG("Loaded");
    char buff[NUMBER_OF_CHARACTERS];
    tmp245_init();
    double value;
    while(1){
        adc_input val = settings_get_input();
        hal_disp_adci_toggle();
        value = system_read_input(); //value + (system_read_input()-value)/10.0;
        utils_dtostr(buff,8,value);
        //printf("%s, ",buff);
        double temp = tmp245_read_temp_double();
        utils_dtostr(buff,8,temp);
        //printf("%s\n",buff);        
        fmt_format_string(buff, NUMBER_OF_CHARACTERS, settings_get_range(),
            settings_get_resolution(), value);
        fmt_append_scale(buff,settings_get_input(), settings_get_range());
        display_puts(buff);
    }
}
