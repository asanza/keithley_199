/*
 * store.c
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
 * Created on July 15, 2015, 10:39 PM
 */

#include "settings.h"
#include <eefs.h>
#include <stdbool.h>

#include "adcctrl.h"
#include <FreeRTOS.h>
#include "semphr.h"
#include "portmacro.h"
#include <assert.h>
#include <string.h>
#include <diag.h>

typedef struct _settings_t{
    adc_input               input               :4 ; /* settings name */
    adc_channel             channel             :8 ; /* which channel is selected on the scanner */
    adc_integration_period  integration_period  :16; /* integration period used */
    adc_range               range               :4 ; /* selected range */
    adc_resolution          resn                :3 ;
    bool                    auto_range          :1 ; /* auto_range selected */
    bool                    filter_enabled      :1 ; /* filter */
    uint8_t                 filter_resoln       :8 ; /* filter resolution */
    conv_func               math;                    /* selected math function */
    out_fmt                 formatter;               /* selected output format */
} __attribute__((__packed__)) settings_t;

typedef struct _calibration_t{
    double gain;
    double offset;
    double temp;
}calibration_t;

#define SETTINGS_START_ADDRESS  0x0A
static calibration_t cal;

SemaphoreHandle_t slock = NULL;

static void lock(void){
    xSemaphoreTake(slock, portMAX_DELAY);
}

static void unlock(void){
    xSemaphoreGive(slock);
}

/* each input has its settings */
static settings_t settings[ADC_NUMBER_OF_INPUTS];
static settings_t* actual_settings = settings;

static void settings_set_default();

void settings_init(void){
    if(!slock){
        slock = xSemaphoreCreateMutex();
    }    
}

void settings_save(settings_location location){
    lock();
    int i;
    int addr = SETTINGS_START_ADDRESS + location*sizeof(settings);
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++)
        eefs_object_save(addr + i,&settings[i], sizeof(settings_t));
    eefs_object_save(addr + i, &actual_settings, sizeof(settings_t*));
    unlock();
}

adc_resolution settings_get_resolution(){
    adc_resolution res;
    lock();
    res = actual_settings->resn;
    unlock();
    return res;
}

void settings_set_resolution(adc_resolution res){
    lock();
    if(actual_settings->input == ADC_INPUT_TEMP) 
        actual_settings->resn = ADC_RESOLUTION_5_5;
    else
        actual_settings->resn = res;
    unlock();
}


int settings_restore(settings_location location) {
    int i;
    lock();
    EEFS_ERROR err;
    settings_set_default();
    int addr = SETTINGS_START_ADDRESS + location * sizeof (settings);
    for (i = 0; i < ADC_NUMBER_OF_INPUTS; i++) {
        err = eefs_object_restore(addr + i, &settings[i], sizeof (settings_t));
        if (err != EEFS_OK) {
            settings_set_default();
            unlock();
            return 1;
        }
    }
    err = eefs_object_restore(addr + i, &actual_settings, sizeof(settings_t*));
    if(err != EEFS_OK){
        actual_settings = settings;
    }
    unlock();
    return 0;
}

adc_integration_period settings_get_integration_period(){
    adc_integration_period p;
    lock();
    p = actual_settings->integration_period;
    unlock();
    return p;
}

adc_input settings_get_input(){
    adc_input p;
    lock();
    p = actual_settings->input;
    unlock();
    return p;
}

adc_range settings_get_range(){
    adc_range r;
    lock();
    r = actual_settings->range;
    unlock();
    return r;
}

adc_channel settings_get_channel(){
    lock();
    adc_channel c = actual_settings->channel;
    unlock();
    return c;
}

void settings_set_input(adc_input input){
    assert(input < ADC_NUMBER_OF_INPUTS);
    lock();
    actual_settings = &settings[input];
    unlock();
}

void settings_range_up(void){
    lock();
    if(actual_settings->input == ADC_INPUT_TEMP){
        unlock();
        return;
    }
    /* get the next range for this input */
    adc_range range = adcctrl_get_next_range(actual_settings->input, actual_settings->range);
    if(range == actual_settings->range){
        unlock();
        return;
    }
    actual_settings->range = range;
    unlock();
}

void settings_range_down(void){
    lock();
    if(actual_settings->input == ADC_INPUT_TEMP){
        unlock();
        return;
    }
    adc_range range = adcctrl_get_previous_range(actual_settings->input, actual_settings->range);
    if(range == actual_settings->range){
        unlock();
        return;
    }
    actual_settings->range = range;
    unlock();
}

double calibration_gain(void){
    lock();
    double c = cal.gain;
    unlock();
    return c;
}

double calibration_offset(){
    lock();
    double c = cal.offset;
    unlock();
    return c;
}

double calibration_temp(){
    lock();
    double c = cal.temp;
    unlock();
    return c;
}

bool settings_is_autorange(void){
    lock();
    bool t = actual_settings->auto_range;
    if(actual_settings->input == ADC_INPUT_TEMP)
        t = false;
    unlock();
    return t;
}
void settings_set_autorange(bool val){
    lock();
    actual_settings->auto_range = val;
    unlock();
}

void settings_set_range(adc_range range){
    lock();
    /* check if range valid */
    adc_control_sequence* id = adcctrl_get_sequence(actual_settings->input, range);
    if(id == NULL){
        unlock();
        return;
    }
    actual_settings->range = range;
    unlock();
}

void calibration_save(double gain, double offset, double temperature){
    lock();
    int id = adcctrl_get_sequence_id(actual_settings->input, actual_settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*ADC_NUMBER_OF_INPUTS + id;
    assert(id >= 0);
    assert(id > 255); //max number of objects
    cal.gain = gain;
    cal.offset = offset;
    cal.temp = temperature;
    eefs_object_save(id, &cal, sizeof(calibration_t));
    unlock();
}

int calibration_restore(){
    lock();
    if(actual_settings->input == ADC_INPUT_TEMP){
        /* temperature does not need calibration. */
        cal.gain = 1;
        cal.offset = 0;
        cal.temp = 25;
        unlock();
        return 1;
    }
    int id = adcctrl_get_sequence_id(actual_settings->input, actual_settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*ADC_NUMBER_OF_INPUTS + id;
    assert(id >= 0);
    assert(id < 255);
    EEFS_ERROR err = eefs_object_restore(id, &cal, sizeof(calibration_t));
    if(err == EEFS_OK){
        unlock();
        return 1;
    }
    cal.gain = 1;
    cal.offset = 0; 
    cal.temp = 25;
    unlock();
    return 0;
}

static void settings_set_default(){
    int i;
    for(i = 0; i < ADC_NUMBER_OF_INPUTS;i++){
        settings[i].auto_range = true;
        settings[i].channel = 0;
        settings[i].filter_enabled = 0;
        settings[i].filter_resoln = 0;
        settings[i].formatter = NULL;
        settings[i].integration_period = ADC_INTEGRATION_50HZ;
        settings[i].resn = ADC_RESOLUTION_5_5;
        settings[i].math = NULL;
    }
    settings[ADC_INPUT_CURRENT_AC].input = ADC_INPUT_CURRENT_AC;
    settings[ADC_INPUT_CURRENT_AC].range = ADC_RANGE_3;

    settings[ADC_INPUT_CURRENT_DC].input = ADC_INPUT_CURRENT_DC;
    settings[ADC_INPUT_CURRENT_DC].range = ADC_RANGE_3;

    settings[ADC_INPUT_VOLTAGE_AC].input = ADC_INPUT_VOLTAGE_AC;
    settings[ADC_INPUT_VOLTAGE_AC].range = ADC_RANGE_300;

    settings[ADC_INPUT_VOLTAGE_DC].input = ADC_INPUT_VOLTAGE_DC;
    settings[ADC_INPUT_VOLTAGE_DC].range = ADC_RANGE_300;

    settings[ADC_INPUT_RESISTANCE_2W].input = ADC_INPUT_RESISTANCE_2W;
    settings[ADC_INPUT_RESISTANCE_2W].range = ADC_RANGE_300;

    settings[ADC_INPUT_RESISTANCE_4W].input = ADC_INPUT_RESISTANCE_4W;
    settings[ADC_INPUT_RESISTANCE_4W].range = ADC_RANGE_300;
    
    settings[ADC_INPUT_TEMP].input = ADC_INPUT_TEMP;
    settings[ADC_INPUT_TEMP].range = ADC_RANGE_300;
}

/* load calibration according to settings */
calibration_t* calibration_get_default(adc_input input){
    cal.gain = 1;
    cal.offset = 0;
    cal.temp = 25.0;
    return &cal;
}
