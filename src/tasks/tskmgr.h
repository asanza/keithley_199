/*
 * tskmgr.h
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
 * Created on August 23, 2015, 7:30 PM
 */
#ifndef TSKMGR_H
#define	TSKMGR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef void(*task_loop)(void* param);
    typedef void(*task_fn)(void);
    
    typedef struct task_iface_T{
        void** handler;
        task_loop task;
        task_fn destroy;
        task_fn pause;
        task_fn resume;
    }task_iface_t;
    
    void taskmgr_start(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TSKMGR_H */

