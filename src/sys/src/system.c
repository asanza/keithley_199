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
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <system.h>
#include <diag.h>
#include "adc.h"

#include <FreeRTOS.h>
#include <semphr.h>

static SemaphoreHandle_t syslock;

static adc_channel channel = 0;
double gain;
double offset;

int system_set_configuration(adc_input input, adc_range range,
    adc_integration_period period, adc_channel _channel, double _gain, double _offset)
{
    /* try to get syslock. Syslock shall be obtained before calling this function. */
    if (xSemaphoreTake(syslock, 0) == pdTRUE) {
        /* you MUST call system_get_lock before calling this function. */
        assert(0);
    }
    adc_error err = adc_init(period, input, range);
    if (err != ADC_ERROR_NONE) return -1;
    channel = _channel;
    gain = _gain;
    offset = _offset;
    return 0;
}

double system_read_input(void)
{
    /* get lock before doing a measurement. It guarantees that no settings changes
     * are done while using the adc. */
    xSemaphoreTake(syslock, portMAX_DELAY);
    double value = gain * adc_read_value(channel) + offset;
    /* release semaphore when done. */
    xSemaphoreGive(syslock);
    return value;
}

void system_init(void)
{
    hal_sys_init();
    hal_i2c_init();
    usb_uart_init();
    /* initialize system lock */
    syslock = xSemaphoreCreateMutex();
}

void system_get_lock()
{
    xSemaphoreTake(syslock, portMAX_DELAY);
    DIAG("");
}

void system_release_lock(void)
{
    xSemaphoreGive(syslock);
    DIAG("");
}