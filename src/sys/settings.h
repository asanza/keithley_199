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
            SETTINGS_0,
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

typedef struct _settings_t settings_t;
typedef struct _calibration_t calibration_t;


/* make sure that input, range combination are valid. */
void settings_get(adc_input input, settings_t* settings);
void settings_set_range(adc_input input, adc_range range);
void settings_save(settings_location location);
int settings_restore();

adc_integration_period settings_integration_period(const settings_t* settings);
adc_input settings_input(const settings_t* settings);
adc_range settings_range(const settings_t* settings);
adc_channel settings_channel(const settings_t* settings);

void calibration_save(const settings_t* settings, const calibration_t* cal);
int calibration_restore(const settings_t* settings, calibration_t* cal);

double calibration_gain(const calibration_t* cal);
double calibration_offset(const calibration_t* cal);


#ifdef	__cplusplus
}
#endif

#endif	/* STORE_H */

