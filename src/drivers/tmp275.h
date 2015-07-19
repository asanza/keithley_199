/*
 * tmp275.h
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
 * Created on January 20, 2015, 7:14 PM
 */

#ifndef TMP275_H
#define	TMP275_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
    
void tmp245_init();

uint16_t tmp245_read_temp();

double tmp245_read_temp_double();


#ifdef	__cplusplus
}
#endif

#endif	/* TMP275_H */

