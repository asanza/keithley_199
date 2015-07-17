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

static void settings_get_default(settings_t* state);
static void calibration_get_default(const settings_t* settings, cal_values_t* cal);

void settings_save(settings_location location, settings_t state){
    eefs_object_save(location,&state, sizeof(settings_t));
}

int settings_restore(settings_location location, settings_t* state){
    EEFS_ERROR err = eefs_object_restore(location,state,sizeof(settings_t));
    if(err == EEFS_OK) return 0;
    settings_get_default(state);
    return 1;
}

void calibration_save(const settings_t* settings,const cal_values_t* cal){
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    assert(id<=0);
    assert(id+SETTINGS_LAST < 255); //max number of objects
    eefs_object_save(SETTINGS_LAST + id, &cal, sizeof(cal_values_t));
}

int calibration_restore(const settings_t* settings, cal_values_t* cal){
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    assert(id<=0);
    EEFS_ERROR err = eefs_object_restore(SETTINGS_LAST+id, cal, sizeof(cal_values_t));
    if(err == EEFS_OK) return 0;
    calibration_get_default(settings, cal);
    return 1;
}

static void settings_get_default(settings_t* state){
    state->auto_range = true;
    state->channel = ADC_CHANNEL_0;
    state->filter_enabled = false;
    state->filter_resoln = 1;
    state->formatter = NULL;
    state->input = ADC_INPUT_VOLTAGE_DC;
    state->integration_period = ADC_INTEGRATION_50HZ;
    state->math = NULL;
    state->range = ADC_RANGE_30;
}

/* load calibration according to settings */
static void calibration_get_default(const settings_t* settings, cal_values_t* cal){
    /* look if they are supported */
    int id = adcctrl_get_sequence_id(settings->input, settings->range);
    assert(id >= 0);
    cal->gain = 1;
    cal->offset = 0;
}