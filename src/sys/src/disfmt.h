/*
 * disfmt.h
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
 * Created on January 24, 2015, 12:13 AM
 */
#ifndef DISFMT_H
#define	DISFMT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "syserr.h"
#include <sysdefs.h>
#include <dispkyb.h>

disp_mode fmt_get_disp_mode(adc_input mode);
void fmt_format_string(char* buffer, adc_range scale, double value);
void fmt_append_scale(char* buffer, adc_input mode, adc_range range);

#ifdef	__cplusplus
}
#endif

#endif	/* DISFMT_H */

