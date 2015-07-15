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
#include <assert.h>
#include <systasks.h>
#include <stddef.h>
#include <string.h>
#include "sysstate.h"

/** actual (physical) dmm state */
static dmm_state state;

sys_error sys_state_set(const dmm_state* _state){
  /* set multimeter state acordly */
  adc_error err = adc_init(_state->integration_period, _state->input,
                          _state->range);
  if(err != ADC_ERROR_NONE) return SYSERR_UNSUPORTED;
  memcpy(&state, _state, sizeof(dmm_state));
}

sys_error sys_state_get(dmm_state* _state){
  memcpy(_state, &state, sizeof(dmm_state));
}

void sys_state_set_defaults(dmm_state* state){
    state->auto_range = true;
    state->cal_function = NULL;
    state->channel = ADC_CHANNEL_0;
    state->filter_enabled = false;
    state->filter_resoln = 1;
    state->formatter = NULL;
    state->input = ADC_INPUT_VOLTAGE_DC;
    state->integration_period = ADC_INTEGRATION_50HZ;
    state->math = NULL;
    state->range = ADC_RANGE_30;
}