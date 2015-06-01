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

#define SYSTEM_TASK_STACK_SIZE 200
#define SYSTEM_TASK_PRIORITY 3

static TaskHandle_t systemTaskHandle = NULL;

/* define a system task */
struct systask{
    //function pointers.
    // after creation, tasks are registered here.
};

static struct TaskArrayElement_t AvailableTasks[4] = {0};

static void SystemTask(void *pvParameters){
    DIAG("Initializing Event System");
    bool shift_key = false;
    while(1){
        switch(display_wait_for_key())
        {
            case KEY_7: sys_state_up_scale(); continue;
            case KEY_6: sys_state_down_scale(); continue;
            case KEY_3: sys_state_toggle_acdc(); continue;
            //case KEY_1: sys_state_set_mode(ADC_INPUT_RESISTANCE_2W); continue;
            //case KEY_0: sys_state_set_mode(ADC_INPUT_VOLTAGE_DC); continue;
            //case KEY_2: sys_state_set_mode(ADC_INPUT_CURRENT_DC); continue;
            case KEY_4: continue;
            case KEY_UP:continue;
            case KEY_5: continue;
            case KEY_8: continue;
            case KEY_9: continue;
            case KEY_DOWN: shift_key = true; continue;
            case KEY_CAL:
                //vTaskSuspend(measTaskHandle);
                //vTaskStart(doCalTaskHandle);
                continue;
            default:
                Nop();
        }
        vTaskDelay(10);
    }
}

void SystemTaskCreate(void){
    if(!systemTaskHandle)
        xTaskCreate(SystemTask,"SYS",SYSTEM_TASK_STACK_SIZE,NULL,SYSTEM_TASK_PRIORITY,&systemTaskHandle);
}
