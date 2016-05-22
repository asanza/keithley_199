/*
 * adc.h
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
 * Created on April 18, 2015, 10:39 PM
 */

#ifndef ADC_H
#define	ADC_H

#include "adcdefs.h"
#include "adcctrl.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
            ADC_ERROR_NOT_SUPPORTED,
            ADC_ERROR_NONE
}adc_error;



adc_error adc_set_range(adc_range scale);
adc_range adc_get_range(void);
adc_input adc_get_input(void);
adc_error adc_set_integration_period(adc_integration_period period);
adc_integration_period adc_get_integration_period(void);
adc_error adc_set_input(adc_input input, adc_range range);
/**
 * return the value readed by the adc.
 * @param channel the channel to be readed (may be not needed, as we can connect 
 * the scanner directly to the processor.).
 * @param flag ADC_OVERFLOW or ADC_UNDERFLOW if the measurement is over or under
 * allowed range.
 * @return the value measured by the adc.
 */
double adc_read_value(adc_channel channel, int* flag);
adc_error adc_init(adc_integration_period period, adc_input input, adc_range range);

double adc_get_max(adc_range range);
    
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

