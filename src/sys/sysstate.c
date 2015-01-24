/*
 * sysstate.c
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
 * Created on January 24, 2015, 7:52 AM
 */

#include <stdbool.h>
#include <stdint.h>
typedef enum{
    CONTINUOUS,
            INTERNAL,
            EXTERNAL
}trigger_mode;

typedef enum{
    MODE_DB,
            MODE_LINEAR
}math_mode;

typedef struct sys_state{
    bool is_volt_meas;
    bool is_ohms_meas;
    bool is_amps_meas;
    bool is_ac_mode;
    bool is_zero_mode;
    bool is_auto_mode;
    bool is_math;
    math_mode mmode;
    bool scanner_on;
    trigger_mode tmode;
}sys_state_t;
