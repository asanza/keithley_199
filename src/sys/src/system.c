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
#include <usb_uart.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <system.h>
#include <diag.h>
#include <math.h>
#include "adc.h"
#include "strutils.h"
#include "strutils.h"
#include "tmp275.h"
#include <FreeRTOS.h>
#include <semphr.h>

static SemaphoreHandle_t syslock;

static adc_channel channel = 0;
static double gain;
static double offset;

static double acc_value;
static int filter_size;

static bool is_temp_mode;

static adc_resolution resln;
static double wn_delta;

#define RESLN_6_5_FILTER_SIZE 10.0

int system_set_configuration(adc_input input, adc_range range,
    adc_integration_period period, adc_channel _channel, double _gain, double _offset,
    adc_resolution res)
{
    xSemaphoreTake(syslock, portMAX_DELAY);
    /* try to get syslock. Syslock shall be obtained before calling this function. */
    if (xSemaphoreTake(syslock, 0) == pdTRUE) {
        /* you MUST call system_get_lock before calling this function. */
        assert(0);
    }
    if(input == ADC_INPUT_TEMP){
        is_temp_mode = true;
    }else{
        is_temp_mode = false;
        adc_error err = adc_init(period, input, range);
        if (err != ADC_ERROR_NONE) return -1;
    }
    channel = _channel;
    gain = _gain;
    offset = _offset;
    resln = res;
    switch(range){
        case ADC_RANGE_30m:
        case ADC_RANGE_30:
        case ADC_RANGE_30K:
        case ADC_RANGE_30M:
            wn_delta =  1e-4;
            break;
        case ADC_RANGE_3:
        case ADC_RANGE_3K:
        case ADC_RANGE_3M:
            wn_delta = 1e-5;
            break;
        case ADC_RANGE_300m:
        case ADC_RANGE_300:
        case ADC_RANGE_300K:
        case ADC_RANGE_300M:
            wn_delta = 1e-3;
            break;
        default: assert(0);
    }
    xSemaphoreGive(syslock);
    return 0;
}

double system_read_temp(void){
    double temperature;
    xSemaphoreTake(syslock, portMAX_DELAY);
    temperature = tmp245_read_temp_double();
    xSemaphoreGive(syslock);
    return temperature;
}

double system_read_input(system_flags_t* flag)
{
    /* get lock before doing a measurement. It guarantees that no settings changes
     * are done while using the adc. */
    double value, temperature;
    *flag = 0;
    xSemaphoreTake(syslock, portMAX_DELAY);
    temperature = tmp245_read_temp_double();
    if(is_temp_mode){
        value = temperature;
    } else{
        value = gain * adc_read_value(channel, (int*)flag) + offset;
        if(resln == ADC_RESOLUTION_6_5){
            if(fabs(value - acc_value) <= wn_delta){
                acc_value = acc_value + (value - acc_value)/RESLN_6_5_FILTER_SIZE;
                value = acc_value;
            }else{
                *flag |= SYSTEM_FILTER_OUT_WINDOW;
                acc_value = value;
            }
        }
    }
    /* release semaphore when done. */
    xSemaphoreGive(syslock);
    return value;
}

double system_get_display_value(double value, adc_range range){
    switch(range){
        case ADC_RANGE_30m:
            
            return value*1e-4;
        case ADC_RANGE_300m: return value*1e-3;
        case ADC_RANGE_3:    return value*1.0;
        case ADC_RANGE_30:   return value*1.0;
        case ADC_RANGE_300:  return value*1.0;
        case ADC_RANGE_3K:   return value*1e3;
        case ADC_RANGE_30K:  return value*1e4;
        case ADC_RANGE_300K: return value*1e5;
        default:
            assert(0);
    }
    return 1.0;
}

void system_init(void)
{
    hal_sys_init();
    hal_i2c_init();
    usb_uart_init();
    tmp245_init();
    /* initialize system lock */
    syslock = xSemaphoreCreateMutex();
}

void system_get_lock()
{
    xSemaphoreTake(syslock, portMAX_DELAY);
}

void system_release_lock(void)
{
    xSemaphoreGive(syslock);
}
