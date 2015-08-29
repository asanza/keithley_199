/*
 * sysdefs.h
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
 * Created on August 23, 2015, 2:18 AM
 */
#ifndef SYSDEFS_H
#define	SYSDEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
    ADC_INTEGRATION_50HZ = 20000, /**< 20mS or 50Hz */
    ADC_INTEGRATION_60HZ = 16667, /**< 16mS or 60Hz  */
}adc_integration_period;

typedef enum{
    ADC_RESOLUTION_5_5,
    ADC_RESOLUTION_6_5,
    ADC_MAX_RESOLUTION
}adc_resolution;

typedef enum {
    ADC_CHANNEL_0 = 0x00,
    ADC_CHANNEL_1 = 0x01,
    ADC_CHANNEL_2 = 0x02,
    ADC_CHANNEL_3 = 0x04,
    ADC_CHANNEL_4 = 0x08,
    ADC_CHANNEL_5 = 0x10,
    ADC_CHANNEL_6 = 0x20,
    ADC_CHANNEL_7 = 0x40,
    ADC_CHANNEL_8 = 0x80,
    ADC_NUMBER_OF_CHANNELS,
}adc_channel;
    
typedef enum {
        ADC_INPUT_VOLTAGE_DC = 0x00,
        ADC_INPUT_VOLTAGE_AC,
        ADC_INPUT_CURRENT_DC,
        ADC_INPUT_CURRENT_AC,
        ADC_INPUT_RESISTANCE_2W,
        ADC_INPUT_RESISTANCE_4W,
                ADC_INPUT_TEMP,
        ADC_NUMBER_OF_INPUTS /**< number of valid inputs */
}adc_input;

typedef enum {
    ADC_RANGE_30m = 0x00,
        ADC_RANGE_300m,
        ADC_RANGE_3,
        ADC_RANGE_30,
        ADC_RANGE_300,
        ADC_RANGE_3K,
        ADC_RANGE_30K,
        ADC_RANGE_300K,
        ADC_RANGE_3M,
        ADC_RANGE_30M,
        ADC_RANGE_300M,
        ADC_RANGE_COUNT,
} adc_range;

#define ADC_OVERFLOW  3.03
#define ADC_UNDERFLOW -3.03

#define ADC_MAX_VALUE 3.0
#define ADC_MIN_VALUE -3.0

#ifdef	__cplusplus
}
#endif

#endif	/* SYSDEFS_H */

