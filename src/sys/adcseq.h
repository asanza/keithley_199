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
#ifndef ADCSEQ_H
#define	ADCSEQ_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <hal.h>

typedef struct hal_adc_integration_sequence_t adc_sequence;
void adcseq_init(adc_sequence* sequence);
uint32_t adcseq_next(adc_sequence* sequence);
adc_sequence* adcseq_get(adc_input input, adc_range range);


#ifdef	__cplusplus
}
#endif

#endif	/* ADCSEQ_H */
