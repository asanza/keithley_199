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
#include <sysdefs.h>
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

/* make sure that input, range combination are valid. */
void settings_set_range(adc_range range);
adc_range settings_get_range();

void settings_set_input(adc_input input);
adc_input settings_get_input();

void settings_save(settings_location location);
int settings_restore(settings_location location);

void settings_set_integration_period(adc_integration_period period);
adc_integration_period settings_get_integration_period();

void settings_set_channel(adc_channel channel);
adc_channel settings_get_channel(void);

void settings_range_up(void);
void settings_range_down(void);

void calibration_save(double gain, double offset);
int calibration_restore();

double calibration_gain();
double calibration_offset();

#ifdef	__cplusplus
}
#endif

#endif	/* STORE_H */

