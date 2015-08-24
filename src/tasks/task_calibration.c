/*
 * task_calibration.c
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
 * Created on July 17, 2015, 10:46 PM
 */

#include<diag.h>
#include<FreeRTOS.h>
#include<task.h>
#include<dispkyb.h>
void task_calibration(void* params)
{
    DIAG("Loaded");
    while (1) {
        key_id key = display_wait_for_key();
        DIAG("Key Pressed: %d", key);
        switch (key) {
            case KEY_0:continue;
            case KEY_1:continue;
            case KEY_2:continue;
            case KEY_3:continue;
            case KEY_4:continue;
            case KEY_5:continue;
            case KEY_6:continue;
            case KEY_7:continue;
            case KEY_8:continue;
            case KEY_9:continue; //continue;
            case KEY_UP:continue;
            case KEY_DOWN:continue;
            case KEY_CAL:
                taskmgr_delete();
                continue;
            case KEY_NONE:continue;
            default:
                Nop();
        }
    }
}
