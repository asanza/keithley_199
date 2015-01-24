/* 
 * Copyright (C) September 26, 2014 Diego F. Asanza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * File:   dmmTask.c
 * Author: Diego F. Asanza <f.asanza[at]gmail.com>
 *
 * Created on September 26, 2014, 11:35 PM
 */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <sys.h>
#include <dispkyb.h>

#include <tmp275.h>

#include "disfmt.h"

void dmmTaskMain(void* pvParameters)
{
    char buff[10];
    tmp245_init();
    while(1)
    {
          hal_disp_adci_toggle();
          double value = sys_dmm_read();
          double temp = tmp245_read_temp_double();
          fmt_format_string(buff,sys_dmm_get_scale(),value);
          fmt_append_scale(buff, sys_dmm_get_mode());
          display_clear();
          display_setmode(fmt_get_disp_mode(adc_get_input()));
          display_puts(buff);
          printf("%f,%f\n",value, temp);
    }
}
