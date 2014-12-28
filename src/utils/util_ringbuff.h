/*
 * util_ringbuff.h
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
 * Created on December 26, 2014, 3:12 AM
 */
#ifndef UTIL_RINGBUFF_H
#define	UTIL_RINGBUFF_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef NUMBER_OF_RINGBUFFERS
#define NUMBER_OF_RINGBUFFERS 4
#endif

#define UTIL_RINGBUFFER_IS_FULL 1
#define UTIL_RINGBUFFER_IS_EMPTY 1

    typedef struct ringbuffer_t util_ringbuffer;

    util_ringbuffer* util_ringbuffer_new(unsigned char* data_buffer,
            int buffer_size);

    int util_ringbuffer_put(util_ringbuffer* buffer, unsigned char data);

    int util_ringbuffer_get(util_ringbuffer* buffer, unsigned char* data);



#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_RINGBUFF_H */

