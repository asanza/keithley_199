/*
 * adcseq.h
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
 * Created on January 18, 2015, 2:05 AM
 */

/** ADC Control is done by using sequences. 
 * The adc on the keithley 199 is controlled by a 32 bit shift register.
 * This shift register controls which input and range is selected, furthermore
 * it also controls the adc conversion.
 * 
 * A serie of shift register values used to perform an analog digital conversion
 * for a given input settings is called an adc_control_sequence
 * 
 * ADC_INPUT defines all possible input configurations on the Keithley.
 * ADC_RANGE defines all possible range configurations.
 * 
 * Of course, not all ranges are possible in some inputs. For example, when using
 * the input configuration for 3V, only ranges from 300m to 300 are available.
 * 
 * In order to get the adc_control sequence needed to perform an adc conversion 
 * for a given input configuration and range, call the function adc_ctrl_get_sequence.
 * This returns a pointer to the first element on the sequence. This sequence is used
 * by the functions in adc.c in order to perform a conversion.
 * 
 */

#ifndef ADCCTRL_H
#define	ADCCTRL_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <adcdefs.h>
    
typedef struct hal_adc_integration_sequence_t adc_control_sequence;

/* reset control sequence.*/
void adcctrl_reset(adc_control_sequence* sequence);

/* get the next control sequence for given adc settings. */
uint32_t adcctrl_get_next_sequence(adc_control_sequence* sequence);

/* get the hardware adc settings for the selected input and range. 
 * Return null if selected input and range are not supported in the 
 * hardware. */
adc_control_sequence* adcctrl_get_sequence(adc_input input, adc_range range);

/** Get a unique identifier for each supported hardware configuration, or -1 if
 * hardware configuration is not supported. */
int adcctrl_get_sequence_id(adc_input input, adc_range range);

adc_range adcctrl_get_next_range(adc_input input, adc_range actual_range);
adc_range adcctrl_get_previous_range(adc_input input, adc_range actual_range);

#ifdef	__cplusplus
}
#endif

#endif	/* ADCSEQ_H */

