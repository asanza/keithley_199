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

#include "tskmgr.h"


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
#include <assert.h>

static SemaphoreHandle_t task_lock;
static TaskHandle_t handle;

static void set_new_range(double value, system_flags_t flag);

static void task_multimeter(void* params);
static void pause(void);
static void resume(void);
static void destroy(void);

task_iface_t multimeter_task = {
    .handler = &handle,
    .task = &task_multimeter,
    .pause = &pause,
    .resume = &resume,
    .destroy = &destroy
};

static void pause(void){
    assert(multimeter_task.handler);
    assert(task_lock != NULL);
    xSemaphoreTake(task_lock, portMAX_DELAY);
    vTaskSuspend(*multimeter_task.handler);
}

static void resume(void){    
    assert(multimeter_task.handler);
    vTaskResume(*multimeter_task.handler);
    if(task_lock != NULL)
        xSemaphoreGive(task_lock);
}

static void destroy(void){
    xSemaphoreTake(task_lock, portMAX_DELAY);
    vTaskDelete(*multimeter_task.handler);
    xSemaphoreGive(task_lock);
}

static void task_multimeter(void *params)
{
    task_lock = xSemaphoreCreateMutex();
    DIAG("Loaded");
    char buff[NUMBER_OF_CHARACTERS];
    system_flags_t flag;
    double value;
    while (1) {
        xSemaphoreTake(task_lock, portMAX_DELAY);
        hal_disp_adci_toggle();
        value = system_read_input(&flag); 
        if (settings_is_autorange())
            set_new_range(value,  flag);
        fmt_format_string(buff, NUMBER_OF_CHARACTERS, settings_get_range(),
            settings_get_resolution(), value, flag);
        fmt_append_scale(buff, settings_get_input(), settings_get_range());
        display_puts(buff);
        xSemaphoreGive(task_lock);
        /*TODO: give some space for other tasks to call system */
        vTaskDelay(1);
    }
}

static void set_new_range(double value, system_flags_t flag)
{
    int wset = 0;
    double maxl = system_get_max(settings_get_range());
    if(fabs(value) >= maxl  || (flag&SYS_FLAG_OVERFLOW) ){
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