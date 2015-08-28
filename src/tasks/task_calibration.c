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
#include<disfmt.h>
#include "tskmgr.h"
#include "settings.h"
#include <system.h>
#include <strutils.h>
#include "fitlinear.h"

#define CAL_FILTER_SIZE  50.0

static double do_measure()
{
    display_clear();
    display_puts(" WORKING ");
    int i;
    double value = 0;
    for (i = 0; i < CAL_FILTER_SIZE; i++) {
        value += system_read_input() / CAL_FILTER_SIZE;
    }
    return value;
}

void task_calibration(void* params)
{
    double refvals[3];
    double measval[3];
    int mpoints = 0;
    double gain = 1;
    double offset = 0;

    system_get_lock();
    system_set_configuration(settings_get_input(), settings_get_range(),
        settings_get_integration_period(), ADC_CHANNEL_0, gain, offset);
    system_release_lock();

    refvals[0] = fmt_get_refval(ADC_MAX_VALUE, settings_get_input(),
        settings_get_range());
    measval[0] = do_measure();
    mpoints++;
    
    refvals[1] = fmt_get_refval(0, settings_get_input(),
        settings_get_range());
    measval[1] = do_measure();
    mpoints++;

    if (settings_get_input() == ADC_INPUT_VOLTAGE_DC ||
        settings_get_input() == ADC_INPUT_CURRENT_DC) {
        refvals[2] = fmt_get_refval(ADC_MIN_VALUE, settings_get_input(),
            settings_get_range());
        measval[2] = do_measure();
        mpoints ++;
    }

    fit_linear(measval, refvals, mpoints, &offset, &gain);
    int i = 0;
    char buffa[15], buffb[15];
    for (i = 0; i < mpoints; i++) {
        utils_dtostr(buffa, 10, refvals[i]);
        utils_dtostr(buffb, 10, measval[i]);
        DIAG("refvals[%d]: %s, measval[%d]: %s", i, buffa, i, buffb);
    }
    utils_dtostr(buffa, 10, offset);
    utils_dtostr(buffb, 10, gain);
    DIAG("offset %f, gain %f", buffa, buffb);
    calibration_save(gain, offset);

    system_get_lock();
    system_set_configuration(settings_get_input(), settings_get_range(),
        settings_get_integration_period(), ADC_CHANNEL_0, calibration_gain(),
        calibration_offset());
    system_release_lock();


    taskmgr_delete();
}
