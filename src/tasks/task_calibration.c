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
#include<semphr.h>
#include<task.h>
#include<dispkyb.h>
#include<diag.h>
#include<disfmt.h>
#include "tskmgr.h"
#include "settings.h"
#include <system.h>
#include <sysdefs.h>
#include <strutils.h>
#include "fitlinear.h"
#include <assert.h>

#define CAL_FILTER_SIZE  50.0
#define ADC_CAL_POS  3.00
#define ADC_CAL_NEG -3.00

static void task_calibration(void* params);
static void pause(void);
static void resume(void);
static void destroy(void);

static SemaphoreHandle_t task_lock;
static TaskHandle_t handle;

task_iface_t calibration_task = {
    .handler = &handle,
    .task = task_calibration,
    .pause = pause,
    .resume = resume,
    .destroy = destroy,
    .has_keys = true
};

static void pause(void){
    assert(calibration_task.handler);
    assert(task_lock);
    xSemaphoreTake(task_lock, portMAX_DELAY);
    vTaskSuspend(*calibration_task.handler);
    xSemaphoreGive(task_lock);    
}

static void resume(void){
    assert(calibration_task.handler);
    assert(task_lock);
    xSemaphoreTake(task_lock, portMAX_DELAY);
    vTaskResume(*calibration_task.handler);
    xSemaphoreGive(task_lock);
}

static void destroy(void){
    xSemaphoreTake(task_lock, portMAX_DELAY);
    vTaskDelete(*calibration_task.handler);
    *calibration_task.handler = NULL;
    xSemaphoreGive(task_lock);
}

static double do_measure()
{
    display_clear();
    display_puts(" WORKING ");
    int i;
    double value = 0;
    system_flags_t flags;
    for (i = 0; i < CAL_FILTER_SIZE; i++) {
        //TODO: What to do if overflow( abort???)
        value += system_read_input(&flags) / CAL_FILTER_SIZE;
    }
    return value;
}

static void task_calibration(void* params)
{
    DIAG(": entering");
    task_lock = xSemaphoreCreateMutex();
    xSemaphoreTake(task_lock, portMAX_DELAY);
    double refvals[3];
    double measval[3];
    int mpoints = 0;
    double gain = 1;
    double offset = 0;
    double temperature = 25;

    if (settings_get_input() == ADC_INPUT_TEMP) {
        display_puts(" WORKING ");
        //do_temp_calibration();
    } else {
        system_set_configuration(settings_get_input(), settings_get_range(),
            settings_get_integration_period(), ADC_CHANNEL_0, gain, offset,
            ADC_RESOLUTION_5_5);

        refvals[0] = fmt_get_refval(ADC_CAL_POS, settings_get_input(),
            settings_get_range(), settings_get_resolution());
        measval[0] = do_measure();
        mpoints++;

        refvals[1] = fmt_get_refval(0, settings_get_input(),
            settings_get_range(), settings_get_resolution());
        measval[1] = do_measure();
        mpoints++;

        if (settings_get_input() == ADC_INPUT_VOLTAGE_DC ||
            settings_get_input() == ADC_INPUT_CURRENT_DC) {
            refvals[2] = fmt_get_refval(ADC_CAL_NEG, settings_get_input(),
                settings_get_range(), settings_get_resolution());
            measval[2] = do_measure();
            mpoints++;
        }

        system_set_configuration(ADC_INPUT_TEMP, ADC_RANGE_300, 
            settings_get_integration_period(), ADC_CHANNEL_0, 1, 0, ADC_RESOLUTION_5_5);
        
        temperature = system_read_temp();
        
        fit_linear(measval, refvals, mpoints, &offset, &gain);
    }
    assert(!isnan(gain));
    assert(!isnan(offset));
    assert(!isinf(gain));
    assert(!isinf(offset));
    calibration_save(gain, offset, temperature);
    system_set_configuration(settings_get_input(), settings_get_range(),
        settings_get_integration_period(), ADC_CHANNEL_0, calibration_gain(),
        calibration_offset(), settings_get_resolution());
    xSemaphoreGive(task_lock);
    vTaskDelete(NULL);
}
