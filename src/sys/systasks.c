/*
 * sys.c
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
 * Created on May 31, 2015, 12:26 AM
 */

#include <FreeRTOS.h>
#include <task.h>
#include <diag.h>
#include <assert.h>
#include <dispkyb.h>
#include <ctype.h>
#include "systasks.h"
#include "system.h"
#include "settings.h"

#define SYSTEM_TASK_STACK_SIZE      200
#define TASK_STACK_SIZE             200
#define SYSTEM_TASK_PRIORITY        3
#define MESSAGE_DELAY 500
#define TASK_PRIORITY               3

typedef enum{
    TASK_MULTIMETER,
            TASK_RESISTANCE_4W,
            TASK_CALIBRATION,
            TASK_COUNT
}dmm_task_t;

extern void task_multimeter(void* params);
extern void task_resistance_4w(void* params);
extern void task_calibration(void* params);

static TaskHandle_t task_list[TASK_COUNT];
static TaskHandle_t runningTask = NULL;
static void sys_init(void);
static void load_settings(settings_t* state);
static void start_task(dmm_task_t task);
static void stop_running_task();
static void switch_sys_function(const settings_t* settings);

static void SystemTask(void *pvParameters) {
    (void*) pvParameters;
    sys_init();
    // Reload Sysstate from eeprom.
    settings_t* settings;
    load_settings(settings);
    display_clear();
    bool shift_key = false; 
    bool repeat_key = true;
    key_id key;
    switch_sys_function(settings);
    while (1) {
        switch (display_wait_for_key()) {
            DIAG("Key Pressed");
            /* suspend tasks */
            stop_running_task();
            case KEY_0:;
            case KEY_1:;
            case KEY_2:;
            case KEY_3:;
            case KEY_4:; //continue;
            case KEY_5:; //continue;
            case KEY_6:;
            case KEY_7:;
            case KEY_8:; //continue;
            case KEY_9:; //continue;
            case KEY_UP:; //continue;
            case KEY_DOWN:
                break;
            case KEY_CAL:
                stop_running_task();
                start_task(TASK_CALIBRATION);
                continue;
            case KEY_NONE:
                repeat_key = true;
                continue;
            default:
                Nop();
        }
    }
}

void systask_init(void) {
        xTaskCreate(SystemTask, "SYS", SYSTEM_TASK_STACK_SIZE, NULL,
            SYSTEM_TASK_PRIORITY, NULL);
        xTaskCreate(task_multimeter, "DMM", TASK_STACK_SIZE, NULL, TASK_PRIORITY,
                &task_list[TASK_MULTIMETER]);
        xTaskCreate(task_calibration, "CAL", TASK_STACK_SIZE, NULL, TASK_PRIORITY,
                &task_list[TASK_CALIBRATION]);
        xTaskCreate(task_resistance_4w, "R4W", TASK_STACK_SIZE, NULL, TASK_PRIORITY,
                &task_list[TASK_RESISTANCE_4W]);
        int i;
        for(i = 0; i < TASK_COUNT; i++){
            vTaskSuspend(task_list[i]);
        }
}

static void start_task(dmm_task_t task){
    vTaskResume(task_list[task]);
    runningTask = task_list[task];
}
static void stop_running_task(){
    if(runningTask!=NULL)
        vTaskSuspend(runningTask);
}

static void sys_init(void){
    DIAG("Initializing System");
    display_kyb_init();
    int i = 0;
    char* temp = REPOVERSION;
    while(temp[i]!=0){
        display_putc(toupper(temp[i]), i++);
    }
    vTaskDelay(MESSAGE_DELAY/portTICK_PERIOD_MS); // show firmware version at startup.
    display_clear();
}

static void load_settings(settings_t* settings){
    if(settings_restore()){
        settings_get(ADC_INPUT_VOLTAGE_DC, settings);
        DIAG("Bad Settings on Store. Loading defaults");
        display_puts("SETT ERROR");
        vTaskDelay(MESSAGE_DELAY/portTICK_PERIOD_MS);
        display_clear();
    }
    switch(settings_integration_period(settings)){
        case ADC_INTEGRATION_50HZ: display_puts("FREQ=50 HZ");break;
        case ADC_INTEGRATION_60HZ: display_puts("FREQ=60 HZ");break;
        default: assert(0);
    }
    vTaskDelay(MESSAGE_DELAY/portTICK_PERIOD_MS);
}

static void switch_sys_function(const settings_t* settings){
    stop_running_task();
    calibration_t* cal;
    calibration_restore(settings, cal);
    system_set_configuration(settings,cal);
    switch(settings_input(settings)){
        case ADC_INPUT_CURRENT_DC:
        case ADC_INPUT_CURRENT_AC:
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_VOLTAGE_DC:
        case ADC_INPUT_VOLTAGE_AC:
            start_task(TASK_MULTIMETER);
            break;
        case ADC_INPUT_RESISTANCE_4W:
            start_task(TASK_RESISTANCE_4W);
            break;
        default:
            assert(0);
    }
}