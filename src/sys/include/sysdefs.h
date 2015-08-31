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
 * Created on August 31, 2015, 7:48 PM
 */
#ifndef SYSDEFS_H
#define	SYSDEFS_H

#include <adcdefs.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum{
        SYSTEM_OVERFLOW = ADC_OVERFLOW,
                SYSTEM_UNDERFLOW = ADC_UNDERFLOW,
                SYSTEM_FILTER_OUT_WINDOW = 0x04
    }system_flags_t;


#ifdef	__cplusplus
}
#endif

#endif	/* SYSDEFS_H */

