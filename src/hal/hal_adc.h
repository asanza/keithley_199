/*
 * hal_adc.h
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
 * Created on January 25, 2015, 9:56 AM
 */
#ifndef HAL_ADC_H
#define	HAL_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif


int hal_adc_integration_sequence(unsigned char channel, uint32_t int_mux, uint32_t pause_mux, uint32_t rund_mux);
/**
 * @param period in us
 */
void hal_adc_init(unsigned int period);
void hal_adc_send_mux(uint8_t channel, uint32_t mux);
/**
 * @param period in us.
 */
void hal_adc_set_integration_period(uint32_t period);


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_ADC_H */

