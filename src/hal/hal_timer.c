/*
 * hal_timer.c
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
 * Created on January 23, 2015, 8:30 PM
 */


#include <HardwareProfile.h>
#include <peripheral/timer.h>
#include <hal_timer.h>

int period; 
hal_timer_callback callback;

void hal_timer_init(int period_us, hal_timer_callback callback_fn){
    callback = callback_fn;
    period = period_us*40;
    mConfigIntCoreTimer(CT_INT_ON|CT_INT_PRIOR_2|CT_INT_SUB_PRIOR_0);
    OpenCoreTimer(period);
}

void __attribute__(( nomips16, interrupt(), vector(_CORE_TIMER_VECTOR)))
CT_wrapper();

CT_handler(){
    mCTClearIntFlag();
    if(callback){
        callback();
    }
    UpdateCoreTimer(period);
}
