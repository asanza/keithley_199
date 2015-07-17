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
#include "sysstate.h"
#include "settings.h"

#define SYSTEM_TASK_STACK_SIZE      200
#define SYSTEM_TASK_PRIORITY        3
#define MAX_TASK_COUNT              6

#define MESSAGE_DELAY 500

struct systask_t {
    TaskHandle_t task_handler;
    dmm_state context;
    bool shift;
    key_id key_switch;
};

static struct systask_t tasks[MAX_TASK_COUNT];

static TaskHandle_t systemTaskHandle = NULL;
static TaskHandle_t runningTask = NULL;

static void sys_init(void);
static void load_settings(settings_t* state);

static void SystemTask(void *pvParameters) {
    (void*) pvParameters;
    sys_init();
    // Reload Sysstate from eeprom.hentai 
    settings_t last_settings;
    load_settings(&last_settings);
    display_clear();
    display_puts("** TEST **");
    bool shift_key = false;    
    key_id key;
    while (1) {
        key = display_wait_for_key();
        DIAG("Key Press: %d", key);
        /*for (i = 0; i < MAX_TASK_COUNT; i++) {
            if (tasks[i].task_handler == NULL) continue;
            if (tasks[i].key_switch != key) continue;
            if (shift_key != tasks[i].key_switch) continue;
            sys_state_set(&tasks[i].context);
            vTaskSuspend(runningTask);
            vTaskResume(tasks[i].task_handler);
            runningTask = tasks[i].task_handler;
        }
        switch (display_wait_for_key()) {
            DIAG("Key Pressed");
            case KEY_7:; //sys_state_up_scale(); continue;
            case KEY_6:; //sys_state_down_scale(); continue;
            case KEY_3:; //sys_state_toggle_acdc(); continue;
            case KEY_1:; //sys_state_set_mode(ADC_INPUT_RESISTANCE_2W); continue;
            case KEY_0:; //sys_state_set_mode(ADC_INPUT_VOLTAGE_DC); continue;
            case KEY_2:; //sys_state_set_mode(ADC_INPUT_CURRENT_DC); continue;
            case KEY_4:; //continue;
            case KEY_UP:; //continue;
            case KEY_5:; //continue;
            case KEY_8:; //continue;
            case KEY_9:; //continue;
            case KEY_DOWN: shift_key = true;
                continue;
            case KEY_CAL:
                //vTaskSuspend(measTaskHandle);
                //vTaskStart(doCalTaskHandle);
                continue;
            default:
                Nop();
        }*/
    }
}

void systask_create_main(void) {
    if (!systemTaskHandle)
        xTaskCreate(SystemTask, "SYS", SYSTEM_TASK_STACK_SIZE, NULL,
            SYSTEM_TASK_PRIORITY, &systemTaskHandle);
}

void systask_add(systask_handler task, key_id key_switch) {
    static int counter = 0;
    assert(counter < MAX_TASK_COUNT);
    int i = 0;
    for (i = 0; i < counter; i++) {
        assert(key_switch != tasks[i].key_switch); // check if not used before
    }
    xTaskCreate(task, "TSK", SYSTEM_TASK_STACK_SIZE, NULL, SYSTEM_TASK_PRIORITY,
            &tasks[counter++].task_handler);
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
        if(settings_restore(SETTINGS_LAST, settings)){
        DIAG("Bad Settings on Store. Loading defaults");
        display_puts("SETT ERROR");
        vTaskDelay(MESSAGE_DELAY/portTICK_PERIOD_MS);
        display_clear();
    }
    switch(settings->integration_period){
        case ADC_INTEGRATION_50HZ: display_puts("FREQ=50 HZ");break;
        case ADC_INTEGRATION_60HZ: display_puts("FREQ=60 HZ");break;
        default: assert(0);
    }
    vTaskDelay(MESSAGE_DELAY/portTICK_PERIOD_MS);
}
