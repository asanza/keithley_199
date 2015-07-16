/*
 * store.h
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
#ifndef SETTINGS_H
#define	SETTINGS_H


#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <adc.h>
    
/* storage addresses */
typedef enum{
            SETTINGS_0= 0x0A,
            SETTINGS_1,
            SETTINGS_2,
            SETTINGS_3,
            SETTINGS_4,
            SETTINGS_5,
            SETTINGS_6,
            SETTINGS_7,
            SETTINGS_8,
            SETTINGS_9,
            SETTINGS_10,
            SETTINGS_LAST
}settings_location;    

typedef double(*conv_func)(double val, void* param, size_t param_size);
typedef void(*out_fmt)(double val, char* buff, size_t size);

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

typedef struct _cal_values_t{
    double gain;
    double offset;
}cal_values_t;

void settings_save(settings_location location, settings_t settings);
/* return 0 if ok, 1 if error.*/
int settings_restore(settings_location location, settings_t* settings);

void calibration_save(settings_t settings, cal_values_t cal);
int calibration_restore(settings_t settings, cal_values_t* cal);


#ifdef	__cplusplus
}
#endif

#endif	/* STORE_H */

