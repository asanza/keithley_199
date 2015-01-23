/*
 * hal_timer.h
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
 * Created on January 23, 2015, 8:30 PM
 */
#ifndef HAL_TIMER_H
#define	HAL_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef void (*hal_timer_callback)(void);

    void hal_timer_init(int period_us, hal_timer_callback callback);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_TIMER_H */

