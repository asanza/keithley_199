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
/* input compare clock is 2.5MHz. 50000 are 20ms @2.5MHz */
#define INTEGRATION_50HZ  50000
    /* 60 Hz are 16ms @ 47 MHz */
#define INTEGRATION_60HZ  41667


int hal_adc_integration_sequence(unsigned char channel, uint32_t int_mux, uint32_t pause_mux, uint32_t rund_mux);
void hal_adc_init(unsigned int period);
void hal_adc_send_mux(uint8_t channel, uint32_t mux);
void hal_adc_set_integration_period(uint32_t period);


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_ADC_H */

