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
#include <math.h>
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
    char tmp[50];
    char *out = e_cvt(value, buff, digits, &decpt, &sign);
    memcpy( tmp, out, 50);
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

char *
dtostre (double val, char *sbeg, unsigned char prec, unsigned char flags){
    static const char str_nan[2][4] =
	{"nan", "NAN"};
    static const char str_inf[2][sizeof(str_nan[0])] =
	{"inf", "INF"};
    char *d;		/* dst	*/
    const char *s;		/* src	*/
    int exp, sign;
    unsigned char vtype;
    if (prec > 7) prec = 7;
    
    exp;
    e_cvt (val, sbeg, prec, &exp, &sign, 0);
    d = s = sbeg;
    vtype = *s++;
    /*if ((vtype & FTOA_MINUS) && !(vtype & FTOA_NAN))	/* like 'Glibc'	*/
	/**d++ = '-';
    else if (flags & DTOSTR_PLUS_SIGN)
	*d++ = '+';
    else if (flags & DTOSTR_ALWAYS_SIGN)
	*d++ = ' ';
    if (vtype & FTOA_NAN) {
	s = str_nan[0];
	goto copy;
    }*/
    
    /*if (vtype & FTOA_INF) {
	s = str_inf[0];
      copy:
	if (flags & DTOSTR_UPPERCASE)
	    s += sizeof(str_nan[0]);
	strcpy_P (d, s);
	goto ret;
    }*/
    
    /* mantissa	*/
    if ( (*d++ = *s++) != '1')
	//vtype &= ~FTOA_CARRY;		/* for possible exponent "-00"	*/
    if (prec) {
	unsigned char c1, c2;
	c1 = '.';
	do {
	    c2 = *s++;
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
    } else if (exp == 0 && (vtype & FTOA_CARRY) != 0) {
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