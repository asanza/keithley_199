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
    adc_channel channel:8; /* which channel is selected on the scanner */
    adc_integration_period integration_period:16; /* integration period used */
    adc_range range:4;
}__attribute__((__packed__)) adc_input_settings;

typedef struct dmm_state{
    adc_input input:3;
    adc_input last_voltage_mode:3;
    adc_input last_current_mode:3;
    adc_input_settings settings[ADC_NUMBER_OF_INPUTS]; /* settings for each possible input */
    
}__attribute__((__packed__)) multimeter_state;

multimeter_state state;

dmm_error sys_state_save(dmm_memory_location mem){
    bool err = eefs_object_save(mem, &state, sizeof(multimeter_state));
    if(err) return DMM_ERR_EEPROM;
    else return DMM_OK;
}

dmm_error sys_state_init(){
    /* initialize scales */
    int i; bool err;
    /* restore default states on each mode from eeprom */
    err = eefs_object_restore(DMM_MEM_0, &state, sizeof(multimeter_state));
    if(err) return DMM_ERR_EEPROM;
    /* init adc and set the mode */
    adc_init(state.settings[state.input].integration_period, state.input, state.settings[state.input].range);
    return DMM_OK;
};


void sys_state_set_channel(adc_channel channel){
    state.settings[adc_get_input()].channel = channel;
}

void sys_state_set_integration_period(adc_integration_period period){
    adc_set_integration_period(period);
    state.settings[adc_get_input()].integration_period = period;
}

void sys_state_set_mode(adc_input mode){
    if(mode > ADC_NUMBER_OF_INPUTS) return;
    switch(adc_get_input()){
        case ADC_INPUT_VOLTAGE_AC:
            if(mode == ADC_INPUT_VOLTAGE_DC) return;
        case ADC_INPUT_VOLTAGE_DC:
            state.last_voltage_mode = adc_get_input();
            break;
        case ADC_INPUT_CURRENT_AC:
            if(mode == ADC_INPUT_CURRENT_DC) return;
        case ADC_INPUT_CURRENT_DC:
            state.last_current_mode = adc_get_input();
            break;
    }
    state.input = mode;
    adc_set_input(state.input, state.settings[state.input].range);
}



dmm_error sys_state_set_scale(adc_range scale){
    if(adc_get_input() == ADC_INPUT_VOLTAGE_AC || adc_get_input() == ADC_INPUT_VOLTAGE_DC){
        switch(scale){
            case ADC_RANGE_300m: state.settings[adc_get_input()].range = scale; break;
            case ADC_RANGE_3:    state.settings[adc_get_input()].range = scale; break;
            case ADC_RANGE_30:   state.settings[adc_get_input()].range = scale; break;
            case ADC_RANGE_300:  state.settings[adc_get_input()].range = scale; break;
            default: return DMM_NOT_SUPPORTED;
        }
    }
    
    if(adc_get_input() == ADC_INPUT_CURRENT_DC||adc_get_input() == ADC_INPUT_CURRENT_AC){
        switch(scale){
            case ADC_RANGE_30m: state.settings[adc_get_input()].range = scale; break;
            case ADC_RANGE_3:   state.settings[adc_get_input()].range = scale; break;
            default: return DMM_NOT_SUPPORTED;
        }
    }
    
    if(adc_get_input() == ADC_INPUT_RESISTANCE_2W||adc_get_input() == ADC_INPUT_RESISTANCE_4W){
        if(scale <= ADC_RANGE_30 || scale >= ADC_RANGE_COUNT)
            return DMM_NOT_SUPPORTED;
        else state.settings[adc_get_input()].range = scale;
    }
    adc_set_range(scale);
}

void sys_state_restore_voltage(){
    sys_state_set_mode(state.last_voltage_mode);
}

void sys_state_restore_current(){
    sys_state_set_mode(state.last_current_mode);
}

dmm_error sys_state_toggle_acdc(){
    switch(adc_get_input()){
        case ADC_INPUT_VOLTAGE_AC:
            state.input = ADC_INPUT_VOLTAGE_DC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_OK;
        case ADC_INPUT_VOLTAGE_DC:
            state.input = ADC_INPUT_VOLTAGE_AC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_OK;
        case ADC_INPUT_CURRENT_AC:
            state.input = ADC_INPUT_CURRENT_DC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_OK;
        case ADC_INPUT_CURRENT_DC:
            state.input = ADC_INPUT_CURRENT_AC;
            adc_set_input(state.input, state.settings[state.input].range);
            return DMM_OK;
        default:
            return DMM_NOT_SUPPORTED;
    }
}

adc_input sys_state_get_mode(){
    return adc_get_input();
}

adc_range sys_state_get_scale(){
    return state.settings[adc_get_input()].range;
}

void sys_state_up_scale(){
    if(adc_get_input() == ADC_INPUT_CURRENT_AC|| adc_get_input()==ADC_INPUT_CURRENT_DC){
        sys_state_set_scale(state.settings[adc_get_input()].range + 2);
    }
    else
        sys_state_set_scale(state.settings[adc_get_input()].range + 1);
}

void sys_state_down_scale(){
    if(adc_get_input() == ADC_INPUT_CURRENT_AC|| adc_get_input()==ADC_INPUT_CURRENT_DC)
        sys_state_set_scale(state.settings[adc_get_input()].range - 2);
    else
         sys_state_set_scale(state.settings[adc_get_input()].range - 1);
}

void sys_state_restore_factory_settings(){
    /* initialize scales */
    int i;
    /* restore default states on each mode from eeprom */
    for(i = 0; i < ADC_NUMBER_OF_INPUTS; i++){
        state.settings[i].integration_period = ADC_INTEGRATION_50HZ;
        state.settings[i].channel = 0;
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
    adc_init(state.settings[ADC_INPUT_VOLTAGE_DC].integration_period,
                ADC_INPUT_VOLTAGE_DC, ADC_RANGE_30);
    /* set the actual mode */
    adc_set_input(ADC_INPUT_VOLTAGE_DC, ADC_RANGE_30);
    /* initialize variables */
    state.input = ADC_INPUT_VOLTAGE_DC;
    state.last_current_mode = ADC_INPUT_CURRENT_DC;
    state.last_voltage_mode = ADC_INPUT_VOLTAGE_DC;
    /* save the same values on eeprom */
    eefs_object_save(DMM_MEM_0, &state, sizeof(multimeter_state));
}
