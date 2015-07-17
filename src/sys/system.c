/*
 * sysstate.c
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
 * Created on January 23, 2015, 9:04 PM
 */

#include <hal.h>
#include <adc.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "system.h"

static adc_channel channel = 0;
cal_values_t calval;
void system_set_configuration(const settings_t* settings, const cal_values_t* cal){
    adc_error err = adc_init(settings->integration_period, settings->input, 
            settings->range);
    assert(err != ADC_ERROR_NONE);
    channel = settings->channel;
    calval.gain = cal->gain;
    calval.offset = cal->offset;
}

double system_read_input(void){
    double value = calval.gain*adc_read_value(channel)+calval.offset;
    return value;
}