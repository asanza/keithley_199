/*
 * task_calibration.c
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
 * Created on July 17, 2015, 10:46 PM
 */

#include<diag.h>
#include<FreeRTOS.h>
#include<task.h>
#include<dispkyb.h>
#include<diag.h>
#include "settings.h"
#include "system.h"
#include "fitlinear.h"

void task_calibration(void* params)
{
    double refvals[3] = {ADC_MAX_VALUE, 0 , ADC_MIN_VALUE};
    double measval[3];
    
    double gain = 1;
    double offset = 0;
    
    system_get_lock();
    system_set_configuration(settings_get_input(), settings_get_range(), 
        settings_get_integration_period(), ADC_CHANNEL_0, gain, offset);
    system_release_lock();
    
    fmt_get_refval(&refvals[0], settings_get_input(), 
        settings_get_range());
    measval[0] = system_read_input();
    DIAG("refval %f", refvals[0]);
    DIAG("measval %f", measval[0]);
    
    fmt_get_refval(&refvals[1], settings_get_input(), 
        settings_get_range());
    measval[1] = system_read_input();
    DIAG("refval %f", refvals[1]);
    DIAG("measval %f", measval[1]);
    
    fmt_get_refval(&refvals[2], settings_get_input(), 
        settings_get_range());
    measval[2] = system_read_input();
    DIAG("refval %f", refvals[2]);
    DIAG("measval %f", measval[2]);

    fit_linear(refvals, measval, 3, &offset, &gain);
    int i = 0;
    for(i = 0; i < 3; i++){
        DIAG("refvals[%d]: %f, measval[%d]: %f",i, refvals[i],i, measval[i]);
    }
    DIAG("offset %f, gain %f", offset, gain);
    calibration_save(gain, offset);
    
    taskmgr_delete();
}
