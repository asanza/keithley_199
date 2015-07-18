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
double gain;
double offset;
int system_set_configuration(adc_input input, adc_range range, 
        adc_integration_period period, adc_channel _channel, double _gain, double _offset){
    adc_error err = adc_init(period, input,range);
    if(err != ADC_ERROR_NONE) return -1;
    channel = _channel;
    gain = _gain;
    offset = _offset;
    return 0;
}

double system_read_input(void){
    double value = gain*adc_read_value(channel)+offset;
    return value;
}