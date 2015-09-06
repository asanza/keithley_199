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
#include <ctype.h>

#define SYSTEM_TASK_STACK_SIZE      200
#define WLAN_TASK_STACK_SIZE        200
#define SCPI_TASK_STACK_SIZE        400
#define TASK_STACK_SIZE             400
#define SYSTEM_TASK_PRIORITY        4
#define WLAN_TASK_PRIORITY          2
#define SCPI_TASK_PRIORITY          2
#define TASK_PRIORITY               3
#define MESSAGE_DELAY               500

typedef enum {
    TASK_MULTIMETER,
    TASK_RESISTANCE_4W,
    TASK_CALIBRATION,
    TASK_COUNT
} sys_task_t;


static void system_task(void* params);
extern void task_multimeter(void* params);
extern void task_resistance_4w(void* params);
extern void task_calibration(void* params);
extern void scpi_task(void* params);
extern void wlan_task(void* params);

static TaskHandle_t running_task = NULL;
static TaskHandle_t dmm_task;

static void sys_init(void);
static void load_settings();
static void start_task(sys_task_t task);
static void stop_running_task();
static void apply_settings();
static void poll_key(void);

void taskmgr_start(void)
{
    xTaskCreate(system_task, "SYS", SYSTEM_TASK_STACK_SIZE, NULL,
        SYSTEM_TASK_PRIORITY, NULL);
    xTaskCreate(scpi_task, "SCPI", WLAN_TASK_STACK_SIZE, NULL,
        WLAN_TASK_PRIORITY, NULL);
    xTaskCreate(task_multimeter, "MUL", TASK_STACK_SIZE, NULL, TASK_PRIORITY,
        &dmm_task);
    xTaskCreate(wlan_task, "WLAN", SCPI_TASK_STACK_SIZE, NULL, SCPI_TASK_PRIORITY,
        NULL);
    vTaskSuspend(dmm_task);
}

static void system_task(void* pvParameters)
{
    sys_init();
    // Reload Sysstate from eeprom.
    load_settings();
    while (1) {
        if (running_task) {
            vTaskDelay(10);
            continue;
        }
        poll_key();
    }
}

void taskmgr_delete(void)
{
    //TODO: This gets called from other threads... 
    // maybe is a good idea to make it thread safe.
    running_task = NULL;
    start_task(TASK_MULTIMETER);
    vTaskDelete(NULL);
}

static void start_task(sys_task_t task)
{
    switch (task) {
        case TASK_MULTIMETER: vTaskResume(dmm_task);
            break;
        case TASK_CALIBRATION:
            assert(running_task != NULL);
            xTaskCreate(task_calibration, "MUL", TASK_STACK_SIZE, NULL, TASK_PRIORITY,
                &running_task);
            break;
        default:
            assert(0);
    }
}

static void stop_running_task()
{
    system_get_lock();
    vTaskSuspend(dmm_task);
    system_release_lock();
}

static void sys_init(void)
{
    DIAG("Initializing System");
    display_kyb_init(); /* should be started after os starts */
    int i = 0;
    char* temp = REPOVERSION;
    while (temp[i] != 0) {
        display_putc(toupper(temp[i]), i);
        i++;
    }
    vTaskDelay(MESSAGE_DELAY / portTICK_PERIOD_MS); // show firmware version at startup.
}

static void load_settings()
{
    //display_puts("LOADING");
    if (settings_restore(SETTINGS_0)) {
        display_clear();
        DIAG("Bad Settings on Store. Loading defaults");
        display_puts("SETT ERROR");
        vTaskDelay(MESSAGE_DELAY / portTICK_PERIOD_MS);
    }

    switch (settings_get_integration_period()) {
            display_clear();
        case ADC_INTEGRATION_50HZ: display_puts("FREQ=50 HZ");
            break;
        case ADC_INTEGRATION_60HZ: display_puts("FREQ=60 HZ");
            break;
        default: assert(0);
    }
    vTaskDelay(MESSAGE_DELAY / portTICK_PERIOD_MS);
    display_clear();
    apply_settings();
}

static void apply_settings()
{
    stop_running_task();
    display_puts(" ------- ");
    if (!calibration_restore()) {
        display_clear();
        display_puts("CAL ERROR");
        vTaskDelay(MESSAGE_DELAY / portTICK_PERIOD_MS);
    }

    if (system_set_configuration(settings_get_input(), settings_get_range(),
        settings_get_integration_period(), settings_get_channel(),
        calibration_gain(), calibration_offset(), settings_get_resolution())) {
        display_clear();
        display_puts("NOT IMPL");
        vTaskDelay(MESSAGE_DELAY / portTICK_PERIOD_MS);
        display_clear();
    }
    if (settings_is_autorange())
        display_setmode(DISP_AC);
    else
        display_clearmode(DISP_AC);
    switch (settings_get_input()) {
        case ADC_INPUT_CURRENT_DC:
        case ADC_INPUT_CURRENT_AC:
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_VOLTAGE_DC:
        case ADC_INPUT_VOLTAGE_AC:
        case ADC_INPUT_TEMP:
            start_task(TASK_MULTIMETER);
            break;
        case ADC_INPUT_RESISTANCE_4W:
            break;
        default:
            assert(0);
    }
}

bool shift_key = false;
bool repeat_key = true;

static void poll_key(void)
{
    key_id key = display_wait_for_key();
    switch (key) {
        case KEY_0:break;
        case KEY_1:break;
        case KEY_2:break;
        case KEY_3:
            if (shift_key) {
                adc_resolution res = settings_get_resolution();
                res++;
                if (res >= ADC_MAX_RESOLUTION)
                    res = ADC_RESOLUTION_5_5;
                settings_set_resolution(res);
                shift_key = false;
            } else {
                if (settings_get_input() == ADC_INPUT_TEMP) return;
                if (settings_is_autorange()) {
                    settings_set_autorange(false);
                } else {
                    settings_set_autorange(true);
                }
            }
            apply_settings();
            break;
        case KEY_4:
            if (repeat_key == false) break;
            shift_key = !shift_key;
            if (shift_key)
                repeat_key = false;
            break;
        case KEY_5:
            if (shift_key) {
                settings_set_input(ADC_INPUT_RESISTANCE_4W);
            } else {
                settings_set_input(ADC_INPUT_RESISTANCE_2W);
            }
            shift_key = false;
            apply_settings();
            break;
        case KEY_6:
            if (shift_key) {
                settings_set_input(ADC_INPUT_VOLTAGE_AC);
                shift_key = false;
            } else
                settings_set_input(ADC_INPUT_VOLTAGE_DC);
            apply_settings();
            break;
        case KEY_7:
            if (shift_key) {
                settings_set_input(ADC_INPUT_CURRENT_AC);
                shift_key = false;
            } else
                settings_set_input(ADC_INPUT_CURRENT_DC);
            apply_settings();
            break;
        case KEY_8:
            if (shift_key) {
                shift_key = false;
            } else
                settings_set_input(ADC_INPUT_TEMP);
            settings_set_autorange(false);
            apply_settings();
            break;
        case KEY_9:
            stop_running_task();
            if (!shift_key) {
                display_puts("LOAD 0-9?");
                key = display_wait_for_key();
                key = display_wait_for_key();
                display_puts(" WORKING ");
                if (key <= 9)
                    settings_restore(key);
            } else {
                shift_key = false;
                display_puts("SAVE 0-9?");
                key = display_wait_for_key();
                key = display_wait_for_key();
                display_puts(" WORKING ");
                if (key <= 9)
                    settings_save(key);
            }
            apply_settings();
            break;
        case KEY_UP:
            settings_range_up();
            settings_set_autorange(false);
            apply_settings();
            break;
        case KEY_DOWN:
            settings_range_down();
            settings_set_autorange(false);
            apply_settings();
            break;
        case KEY_CAL:
            stop_running_task();
            start_task(TASK_CALIBRATION);
            break;
        case KEY_NONE:
            repeat_key = true;
            break;
        default:
            Nop();
    }
    if (shift_key) {
        display_setmode(DISP_ZERO);
    } else {
        display_clearmode(DISP_ZERO);
    }
}