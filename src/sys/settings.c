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

#include <settings.h>
#include <eefs.h>
#include <stdbool.h>

#include <adcctrl.h>
#include <assert.h>

typedef struct _settings_t{
    adc_input               input               :4 ;
    adc_channel             channel             :8 ; /* which channel is selected on the scanner */
    adc_integration_period  integration_period  :16; /* integration period used */
    adc_range               range               :4 ; /* selected range */
    bool                    auto_range          :1 ; /* auto_range selected */
    bool                    filter_enabled      :1 ; /* filter */
    uint8_t                 filter_resoln       :8 ; /* filter resolution */
    conv_func               math;                    /* selected math function */
    out_fmt                 formatter;               /* selected output format */
} settings_t;

typedef struct _calibration_t{
    double gain;
    double offset;
}calibration_t;

#define SETTINGS_START_ADDRESS  0x0A

/* each input has its settings */
static settings_t settings[ADC_NUMBER_OF_INPUTS];
static int settings_restore(settings_location location, settings_t* state);
static void settings_set_default();

void settings_save(settings_location location){
    int i;
    int addr = SETTINGS_START_ADDRESS + location*sizeof(settings);
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++)
        eefs_object_save(addr + i,&settings[i], sizeof(settings_t));
}

static int settings_restore(settings_location location){
    int i;
    int addr = SETTINGS_START_ADDRESS + location*sizeof(settings);
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++){
        EEFS_ERROR err = eefs_object_restore(addr+i, &settings[i],sizeof(settings_t));
        if(err != EEFS_OK){
            settings_set_default();
            return 1;
        }
    }
    return 0;
}

int settings_get(adc_input input, settings_t* settings){
    
}

void calibration_save(const settings_t* settings,const calibration_t* cal){
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*sizeof(settings) + id;
    assert(id<=0);
    assert(id < 255); //max number of objects
    eefs_object_save(id, &cal, sizeof(cal_values_t));
}

int calibration_restore(const settings_t* settings, cal_values_t* cal){
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    id = SETTINGS_START_ADDRESS + SETTINGS_LAST*sizeof(settings) + id;
    assert(id<=0);
    assert(id<255);
    EEFS_ERROR err = eefs_object_restore(id, cal, sizeof(cal_values_t));
    if(err == EEFS_OK) return 0;
    calibration_get_default(settings, cal);
    return 1;
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
static void calibration_get_default(const settings_t* settings, cal_values_t* cal){
    /* look if they are supported */
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    assert(id >= 0);
    cal->gain = 1;
    cal->offset = 0;
}

void settings_set_input(settings_t* settings, adc_input input){
    
}

void settings_set_range(settings_t* settings, adc_range range){
    
}