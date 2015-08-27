/*
 * strutils.c
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
 * Created on August 27, 2015, 8:37 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include "dtoa.h"

    void utils_dtostr(char* buff, int digits, double value){
        
        int decpt;
        int sign;
        char* rve;
        char *out = utils_dtoa_priv(value,4,digits, &decpt, &sign, &rve);
        int i = 0, j;
        if(value >= 0){
            buff[i++] = ' ';
        }else{
            buff[i++] = '-';
        }
        
        if(decpt < 0)
        {
            buff[i++] = '0';
            buff[i++] = '.';
        }

        for(j = decpt+1; j <= 0; j++){
            buff[i++] = '0';
        }
        j = 0;
        for (i = i; i <= digits + 1; i++){
            if(decpt-- == 0) buff[i++] = '.';
            if(out[j] == '\0'){
                buff[i] = '0';
            }else{
                buff[i] = out[j++];
            }
        }
        /* round if last digit + 1 > 5*/
        if(out[j] != '\0'){
            char t[2] = {' ', '\0'};
            t[0]=out[j];
            int d1 = atoi(t);
            if(d1 > 5){
                t[0]=buff[i-1];
                d1 = atoi(t);
                utoa(t, d1+1, 10);
                buff[i-1] = t[0];
            }
        }
        
        buff[i] = '\0';
        free(out);
    }
    
    double utils_strtod(char* buffer){
        double val;
        char* se;
        int i;
        while(buffer[i++]!='\0')
            se = &buffer[i];
        val = utils_strtod_priv(buffer,&se);
        return val;
    }