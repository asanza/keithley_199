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
#include <assert.h>
#include <string.h>
#include <diag.h>

typedef struct _settings_t{
    adc_input               input               :4 ;
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
}calibration_t;

#define SETTINGS_START_ADDRESS  0x0A
static calibration_t cal;

/* each input has its settings */
static settings_t settings[ADC_NUMBER_OF_INPUTS];
static settings_t* actual_settings = settings;

static void settings_set_default();

void settings_save(settings_location location){
    int i;
    int addr = SETTINGS_START_ADDRESS + location*sizeof(settings);
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++)
        eefs_object_save(addr + i,&settings[i], sizeof(settings_t));
}

adc_resolution settings_get_resolution(){
    return actual_settings->resn;
}

void settings_set_resolution(adc_resolution res){
    actual_settings->resn = res;
}


int settings_restore(settings_location location) {
    int i;
    int addr = SETTINGS_START_ADDRESS + location * sizeof (settings);
    for (i = 0; i < ADC_NUMBER_OF_INPUTS; i++) {
        EEFS_ERROR err = eefs_object_restore(addr + i, &settings[i], sizeof (settings_t));
        if (err != EEFS_OK) {
            settings_set_default();
            return 1;
        }
    }
    return 0;
}

adc_integration_period settings_get_integration_period(){
    return actual_settings->integration_period;
}

adc_input settings_get_input(){
    return actual_settings->input;
}

adc_range settings_get_range(){
    return actual_settings->range;
}

adc_channel settings_get_channel(){
    return actual_settings->channel;
}

void settings_set_input(adc_input input){
    assert(input < ADC_NUMBER_OF_INPUTS);
    actual_settings = &settings[input];
}

void settings_range_up(void){
    /* get the next range for this input */
    adc_range range = adcctrl_get_next_range(actual_settings->input, actual_settings->range);
    if(range == actual_settings->range) return;
    actual_settings->range = range;
}

void settings_range_down(void){
    adc_range range = adcctrl_get_previous_range(actual_settings->input, actual_settings->range);
    if(range == actual_settings->range) return;
    actual_settings->range = range;
}

double calibration_gain(void){
    return cal.gain;
}

double calibration_offset(){
    return cal.offset;
}

void settings_set_range(adc_range range){
    /* check if range valid */
    adc_control_sequence* id = adcctrl_get_sequence(actual_settings->input, range);
    if(id == NULL) return;
    actual_settings->range = range;
}

void calibration_save(double gain, double offset){
    int id = adcctrl_get_sequence_id(actual_settings->input, actual_settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*ADC_NUMBER_OF_INPUTS + id;
    assert(id<=0);
    assert(id < 255); //max number of objects
    cal.gain = gain;
    cal.offset = offset;
    eefs_object_save(id, &cal, sizeof(calibration_t));
}

int calibration_restore(){
    int id = adcctrl_get_sequence_id(actual_settings->input, actual_settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*ADC_NUMBER_OF_INPUTS + id;
    assert(id >= 0);
    assert(id < 255);
    EEFS_ERROR err = eefs_object_restore(id, &cal, sizeof(calibration_t));
    if(err == EEFS_OK) return 1;
    cal.gain = 1;
    cal.offset = 0;   
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

}

/* load calibration according to settings */
calibration_t* calibration_get_default(adc_input input){
    /* look if they are supported */
    adc_control_sequence* id = adcctrl_get_sequence(settings[input].input, 
        settings[input].range);
    if(!id){
        assert(id);
    }
    cal.gain = 1;
    cal.offset = 0;
    return &cal;
}
