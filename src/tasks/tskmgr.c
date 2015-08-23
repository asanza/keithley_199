/*
 * tskmgr.c
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
 * Created on August 23, 2015, 7:30 PM
 */

#include "tskmgr.h"
#include <settings.h>
#include <system.h>
#include <FreeRTOS.h>
#include <task.h>
#include <diag.h>
#include <assert.h>
#include <dispkyb.h>
#include <queue.h>

#define SYSTEM_TASK_STACK_SIZE      200
#define TASK_STACK_SIZE             200
#define SYSTEM_TASK_PRIORITY        3
#define MESSAGE_DELAY 500
#define TASK_PRIORITY               3

static void system_task(void* params);

void tskmgr_start(void)
{
    xTaskCreate(system_task, "SYS", SYSTEM_TASK_STACK_SIZE, NULL,
        SYSTEM_TASK_PRIORITY, NULL);
}

static void system_task(void* pvParameters)
{
    (void*) pvParameters;
    // Reload Sysstate from eeprom.
    //load_settings();
    bool shift_key = false;
    bool repeat_key = true;
    key_id key;
    //switch_sys_function();
    while (1) {
        key_id key = display_wait_for_key();
        DIAG("Key Pressed: %d", key);
        switch (key) {
            case KEY_0:continue;
            case KEY_1:continue;
            case KEY_2:continue;
            case KEY_3:continue;
            case KEY_4:
                shift_key = !shift_key;
                if (shift_key) {
                    display_setmode(DISP_ZERO);
                } else
                    display_clearmode(DISP_ZERO);
                continue;
            case KEY_5:
                if (shift_key) {
                    settings_set_input(ADC_INPUT_RESISTANCE_4W);
                } else {
                    settings_set_input(ADC_INPUT_RESISTANCE_2W);
                }
                shift_key = false;
                //switch_sys_function();
                continue;
            case KEY_6:
                if (shift_key) {
                    settings_set_input(ADC_INPUT_VOLTAGE_AC);
                    shift_key = false;
                } else
                    settings_set_input(ADC_INPUT_VOLTAGE_DC);
                //switch_sys_function();
                continue;
            case KEY_7:
                if (shift_key) {
                    settings_set_input(ADC_INPUT_CURRENT_AC);
                    shift_key = false;
                } else
                    settings_set_input(ADC_INPUT_CURRENT_DC);
                //switch_sys_function();
                continue;
            case KEY_8:continue;
            case KEY_9:; //continue;
            case KEY_UP:
                settings_range_up();
                //switch_sys_function();
                continue;
            case KEY_DOWN:
                settings_range_down();
                //switch_sys_function();
                continue;
            case KEY_CAL:
                //start_task(TASK_CALIBRATION);
                continue;
            case KEY_NONE:
                repeat_key = true;
                continue;
            default:
                Nop();
        }
    }
}