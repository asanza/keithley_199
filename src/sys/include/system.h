/*
 * system.h
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
#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <sysdefs.h>

    /** Initialize system. Set up hardware. Should be called before
     * OS Starts. */
    void system_init(void);

    /**
     * configure the hardware to perform a measurement. 
     * @param settings desired hardware configuration
     * @param cal  calibration parameters
     * @return -1 in case of error.
     */
    int system_set_configuration(adc_input input, adc_range range,
            adc_integration_period period, adc_channel channel, double gain, double offset,
            adc_resolution res);

    /** read the value at the input with the configuration set with system set 
     * configuration. */
    double system_read_input(void);
    
    /** get the system lock before changing configuration. */
    void system_get_lock();
    /** dont forget to release the lock after you are done. */
    void system_release_lock();

#ifdef	__cplusplus
}
#endif

#endif	/* SYSSTATE_H */
