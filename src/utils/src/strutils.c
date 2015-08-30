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
#include <diag.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "strutils.h"
#include "fcvt.h"

static double round(double x)
{
    return(x < 0.0) ? -floor(-x + 0.5) : floor(x + 0.5);
}

void utils_dtofixstr(char* buff, int digits, int dplaces, double value){
    char dstr[10];
    char* idx = buff;
    char* ids = dstr;
    int i;
    value = round(value*pow(10,dplaces)*1.0)/pow(10,dplaces)*1.0;
    utils_dtostr(dstr, digits, value);
    if(*ids == '-'){
        *idx++ = '-';
    }else{
        *idx++ = ' ';
    }
    ids = strchr(dstr, '.');
    idx += digits - dplaces;
    
    for(i = 0; i <= dplaces + 1; i++){
        if(*ids){
            *idx++=*ids++;
        }else{
            *idx++='0';
        }
    }
    
    ids = strchr(dstr, '.');
    idx = buff + digits - dplaces + 1;
    
    for(i = digits-dplaces; i >= 0; i--){
        if(*ids!=0 && *ids!='-')
            *idx--=*ids--;
        else
            *idx--='0';
    }
    
    buff[digits + 2] = '\0';
}

void utils_dtostr(char* buff, int digits, double value)
{
    int decpt;
    int sign;
    char tmp[15];
    char *out = e_cvt(value, buff, digits, &decpt, &sign);
    //TODO: Replace by a in string copy to avoid allocating tmp.
    memcpy( tmp, out, 15);
    out = tmp;
    int i = 0, j;
    if (value < 0) {
        buff[i++] = '-';
        digits++;
    }

    if (decpt <= 0) {
        buff[i++] = '0';
    }
    
    if(decpt + 1 <= -1.0*digits){
        decpt = -1.0*digits;
    }

    for (j = decpt + 1; j <= 0; j++) {
        if(j == decpt + 1)buff[i++] = '.';
        buff[i++] = '0';
    }

    j = 0;
    for (i = i; i <= digits; i++) {
        if (decpt-- == 0) buff[i++] = '.';
        if (out[j] == '\0') {
            buff[i] = '0';
        } else {
            buff[i] = out[j++];
        }
    }
    /* round if last digit + 1 > 5 */
    /* TODO: Test extreme case: round to 3, 0.04445*/
    if (out[j] != '\0') {
        char t[2] = {' ', '\0'};
        t[0] = out[j];
        int d1 = atoi(t);
        if (d1 >= 5) {
            t[0] = buff[i - 1];
            d1 = atoi(t);
            utoa(t, d1 + 1, 10);
            buff[i - 1] = t[0];
        } else if (d1 == 4) {
            if (out[j + 1] != '\0') {
                t[0] = out[j + 1];
                d1 = atoi(t);
                if (d1 >= 5) {
                    t[0] = buff[i - 1];
                    d1 = atoi(t);
                    utoa(t, d1 + 1, 10);
                    buff[i - 1] = t[0];
                } else if (d1 == 4) {
                    if (out[j + 2] != '\0') {
                        t[0] = out[j + 2];
                        d1 = atoi(t);
                        if (d1 >= 5) {
                            t[0] = buff[i - 1];
                            d1 = atoi(t);
                            utoa(t, d1 + 1, 10);
                            buff[i - 1] = t[0];
                        }
                    }
                }
            }
        }
    }
    buff[i] = '\0';
}

double utils_strtod(char* buffer)
{
    double val;
    char* se = buffer;
    while (*se != '\0')
        se++;
    val = strtod(buffer, &se);
    return val;
}

char *dtostre (double val, char *sbeg, unsigned char prec, unsigned char flags){
    char *d;		/* dst	*/
    const char *s;		/* src	*/
    int exp, sign;
    bool isNan = false, isInf = false;

    if (prec > 7) prec = 7;
    
    s = e_cvt (val, sbeg, prec, &exp, &sign);
    d = sbeg;
    if(s == sbeg) assert(0);
    
    if(strstr(s, "nan")!=NULL) isNan = true;
    if(strstr(s, "inf")!=NULL) isInf = true;
    
    if(sign){
        *d++='-';
    }else if(flags & DTOSTR_PLUS_SIGN){
        *d++='+';
    }else if(flags & DTOSTR_ALWAYS_SIGN){
        *d++ = ' ';
    }
    
    if(flags & DTOSTR_UPPERCASE){
        if(isNan) strcpy(d,"NAN");
        if(isInf) strcpy(d,"INF");
    }else{
        if(isNan) strcpy(d,"nan");
        if(isInf) strcpy(d,"inf");
    }
    
    if(isNan||isInf) goto ret;
    unsigned char c1, c2, c3;
    c3 = *s++;
    *d++ = '0';
    if (prec) {
        c1 = '.';
        do {
            c2 = c3;
            c3 = *s++;
            *d++ = c1;
            c1 = c2;
        } while (--prec);
        *d++ = c1;
    }
    /* exponent	*/
    *d++ = (flags & DTOSTR_UPPERCASE) ? 'E' : 'e';
    if (exp < 0) {
        *d++ = '-';
        exp = -exp;
    } else if (exp == 0) {
        *d++ = '-';
    } else {
        *d++ = '+';
    }
    for (prec = '0';  exp >= 10;  exp -= 10)
	prec += 1;
    *d++ = prec;
    *d++ = '0' + exp;
    *d = 0;
  ret:
    return sbeg;
}