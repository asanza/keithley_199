/*
 * util_ringbuff.c
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
 * Created on December 26, 2014, 3:13 AM
 */

#include "util_ringbuff.h"
#include <stddef.h>
#include <stdbool.h>

struct ringbuffer_t{
    unsigned char* elems;
    unsigned char* next;
    unsigned int elem_count;
    int size;
};

util_ringbuffer buffers[NUMBER_OF_RINGBUFFERS];

static unsigned int used_buffers = 0;

util_ringbuffer* util_ringbuffer_new(unsigned char* data_buffer,
            int buffer_size){
    if(used_buffers >= NUMBER_OF_RINGBUFFERS)
        return NULL; /* No memory available */
    buffers[used_buffers].elems = data_buffer;
    buffers[used_buffers].next = data_buffer;
    buffers[used_buffers].elem_count = 0;
    buffers[used_buffers].size = buffer_size;
    used_buffers++;
    return &buffers[used_buffers - 1];
}

int util_ringbuffer_put(util_ringbuffer* buffer, unsigned char data){
    /* check if buffer is full */
    if(buffer->elem_count >= buffer->size)
        return UTIL_RINGBUFFER_IS_FULL;
    /* put elem in buffer */
    *buffer->next = data;
    /* increment element counter */
    buffer->elem_count++;
    /* increment pointer */
    buffer->next++;
    /* check if out of bounds */
    if(buffer->next >= buffer->elems + buffer->size)
        buffer->next = buffer->elems;
    return 0;
}

int util_ringbuffer_get(util_ringbuffer* buffer, char* data){
    /* check if buffer is empty */
    if(buffer->elem_count <= 0)
        return UTIL_RINGBUFFER_IS_EMPTY;
    /* get first element */
    unsigned char* first;
    first = buffer->next - buffer->elem_count;
    /* check if out of bounds */
    if(first < buffer->elems)
    {
        int t = buffer->elems - first;
        first = buffer->elems + buffer->size - t;
    }
    /* decrement counter */
    buffer->elem_count --;
    /* return first element */
    *data = *first;
    return 0;
}
