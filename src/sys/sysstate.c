/*
 * sysstate.c
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
 * Created on January 23, 2015, 9:04 PM
 */

#include <hal.h>
#include <adc.h>
#include <eefs.h>
#include <assert.h>
#include <sys.h>

/* represents the actual dmm state. */
typedef struct input_settings{
    adc_range range:4;
}__attribute__((__packed__)) adc_input_settings;

typedef struct dmm_state_t{
    adc_input               input               :4;
    adc_channel             channel             :8; /* which channel is selected on the scanner */
    adc_integration_period  integration_period  :16; /* integration period used */
    adc_input_settings      settings[ADC_NUMBER_OF_INPUTS];
}__attribute__((__packed__)) dmm_state;

dmm_state state;

dmm_error sys_state_save(dmm_memory_location mem){
    bool err = eefs_object_save(mem, &state, sizeof(dmm_state));
    if(err) return DMM_ERR_EEPROM;
    else return DMM_ERROR_NONE;
}

dmm_error sys_state_restore(dmm_memory_location mem){
    bool err = eefs_object_restore(mem, &state, sizeof(dmm_state));
    if(err) return DMM_ERR_EEPROM;
    else return DMM_ERROR_NONE;
}

dmm_error sys_state_init(){
    /* initialize scales */
    int i; bool err;
    /* restore default states on each mode from eeprom */
    err = eefs_object_restore(DMM_MEM_0, &state, sizeof(dmm_state));
    if(err) return DMM_ERR_EEPROM;
    /* init adc and set the mode */
    if(adc_init(state.integration_period, state.input,
            state.settings[state.input].range) != ADC_ERROR_NONE)
        return DMM_NOT_SUPPORTED;
    return DMM_ERROR_NONE;
};


void sys_state_set_channel(adc_channel channel){
    state.channel = channel;
}

adc_channel sys_state_get_channel(void){
    return state.channel;
}

void sys_state_set_integration_period(adc_integration_period period){
    adc_set_integration_period(period);
    state.integration_period = period;
}

void sys_state_set_mode(adc_input mode){
    adc_range range = state.settings[mode].range;
    if(adc_set_input(mode,range)!=ADC_ERROR_NONE)
        return;
    state.input = mode;
}


dmm_error sys_state_set_range(adc_range scale){
    if( adc_set_range(scale) != ADC_ERROR_NONE ) return;
    state.settings[state.input].range = scale;
}

dmm_error sys_state_toggle_acdc(){
    switch(adc_get_input()){
        case ADC_INPUT_VOLTAGE_AC:
            state.input = ADC_INPUT_VOLTAGE_DC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_ERROR_NONE;
        case ADC_INPUT_VOLTAGE_DC:
            state.input = ADC_INPUT_VOLTAGE_AC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_ERROR_NONE;
        case ADC_INPUT_CURRENT_AC:
            state.input = ADC_INPUT_CURRENT_DC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_ERROR_NONE;
        case ADC_INPUT_CURRENT_DC:
            state.input = ADC_INPUT_CURRENT_AC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_ERROR_NONE;
        default:
            return DMM_NOT_SUPPORTED;
    }
}

adc_input sys_state_get_mode(){
    return adc_get_input();
}

adc_range sys_state_get_scale(){
    return adc_get_range();
}

void sys_state_up_scale(){
    if(adc_get_input() == ADC_INPUT_CURRENT_AC|| adc_get_input()==ADC_INPUT_CURRENT_DC){
        sys_state_set_range(state.settings[adc_get_input()].range + 2);
    }
    else
        sys_state_set_range(state.settings[adc_get_input()].range + 1);
}

void sys_state_down_scale(){
    if(adc_get_input() == ADC_INPUT_CURRENT_AC|| adc_get_input()==ADC_INPUT_CURRENT_DC)
        sys_state_set_range(state.settings[adc_get_input()].range - 2);
    else
         sys_state_set_range(state.settings[adc_get_input()].range - 1);
}

void sys_state_restore_factory_settings(){
    /* initialize scales */
    int i;
    /* restore default states on each mode from eeprom */
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++){
        state.integration_period = ADC_INTEGRATION_50HZ;
        state.channel = 0;
        switch(i){
            case ADC_INPUT_CURRENT_AC:
            case ADC_INPUT_CURRENT_DC:
                state.settings[i].range = ADC_RANGE_3;
                break;
            case ADC_INPUT_VOLTAGE_AC:
            case ADC_INPUT_VOLTAGE_DC:
                state.settings[i].range = ADC_RANGE_300;
                break;
            case ADC_INPUT_RESISTANCE_2W:
            case ADC_INPUT_RESISTANCE_4W:
                state.settings[i].range = ADC_RANGE_300;
                break;
        }
    }
    /* init the adc */
    adc_init(state.integration_period,
                ADC_INPUT_VOLTAGE_DC, ADC_RANGE_30);
    /* initialize variables */
    state.input = ADC_INPUT_VOLTAGE_DC;
    /* save the same values on eeprom */
    //TODO: remove
    eefs_object_save(DMM_MEM_0, &state, sizeof(dmm_state));
}
