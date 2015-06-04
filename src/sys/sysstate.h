/*
 * sysstate.h
 *
 * Copyright (c) ${year}, Diego F. Asanza. All rights reserved.
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
 * Created on January 24, 2015, 8:04 PM
 */
#ifndef SYSSTATE_H
#define	SYSSTATE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <adc.h>
#include <syserr.h>
#include <stddef.h>

typedef double(*conv_func)(double val, void* param, size_t param_size);
typedef void(*out_fmt)(double val, char* buff, size_t size);
typedef double(*cal_func)(double val);

typedef struct dmm_state_t{
    adc_input               input               :4 ;
    adc_channel             channel             :8 ; /* which channel is selected on the scanner */
    adc_integration_period  integration_period  :16; /* integration period used */
    adc_range               range               :4 ; /* selected range */
    bool                    auto_range          :1 ; /* auto_range selected */
    bool                    filter_enabled      :1 ; /* filter */
    uint8_t                 filter_resoln       :8 ; /* filter resolution */
    conv_func               math;                    /* selected math function */
    out_fmt                 formatter;               /* selected output format */
    cal_func                cal_function;            /* calibration function */
}__attribute__((__packed__)) dmm_state;

/** Set the dmm state */
sys_error sys_state_set(const dmm_state* state);
/** Get the actual dmm state */
sys_error sys_state_get(dmm_state* state);

#ifdef	__cplusplus
}
#endif

#endif	/* SYSSTATE_H */
