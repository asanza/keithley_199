/* 
 * File:   dmm.h
 * Author: Diego F. Asanza <f.asanza[at]gmail.com>
 *
 * Created on September 27, 2014, 9:43 AM
 */

/*
 * Copyright (C) September 27, 2014 Diego F. Asanza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef DMM_H
#define	DMM_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef void (*dmm_key_handler)(void*);

    typedef struct dmm_key_handlers_t{
        dmm_key_handler _0;
        dmm_key_handler _1;
        dmm_key_handler _2;
        dmm_key_handler _3;
        dmm_key_handler _4;
        dmm_key_handler _5;
        dmm_key_handler _6;
        dmm_key_handler _7;
        dmm_key_handler _8;
        dmm_key_handler _9;
        dmm_key_handler _10;
        dmm_key_handler _11;
    }dmm_key_handlers;

#ifdef	__cplusplus
}
#endif

#endif	/* DMM_H */

