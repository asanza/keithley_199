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
#include <sys.h>
    
dmm_error sys_state_init();

/** @brief set the scanner channel
 * @param channel
 */
void sys_state_set_channel(adc_channel channel);
/**@brief set the integration period.
 * @param period
 */
void sys_state_set_integration_period(adc_integration_period period);

adc_integration_period sys_state_get_integration_period();

void sys_state_up_scale();
void sys_state_down_scale();
adc_range sys_state_get_scale();
dmm_error sys_state_set_scale(adc_range scale);

void sys_state_set_mode(adc_input mode);
adc_input sys_state_get_mode();

dmm_error sys_state_save(dmm_memory_location location);
void sys_state_restore(dmm_memory_location location);

void sys_state_restore_factory_settings();



#ifdef	__cplusplus
}
#endif

#endif	/* SYSSTATE_H */

