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

static double round_to_n(double x, unsigned int digits) {
    double fac = pow(10, digits);
    return rint(x*fac)/fac;
}

/* shift a number in string form n places to the right. Push zeroes to front. */
static void _shift_right_nstr(const char* c, unsigned int places);
/* shift a number string n places to the left, push zeroes to the back. */
static void _shift_left_nstr(const char* c, unsigned int places);

void utils_dtofixstr(char* buff, int digits, int dplaces, double value){
    value = round_to_n(value, dplaces);
    utils_dtostr(buff, digits, value);
    char* out = buff;
    int i=0; 
    while(*++out) i++;
    while(i++ <= digits) *out++ = '0';
    *out = 0;
    out = buff;
    /* add sign or space */
    if(*out++ != '-'){ 
        _shift_right_nstr(buff, 1);
        *buff = ' ';
    }
    /* locate the dp. */
    char* dp = strchr(out, '.');
    /* find out how many places to shift. */
    i = 0;
    if(!dp){
        /* no decimal point */
        i = dplaces;
    } else {
        while(*++dp) i++;
    }
    int shift = i - dplaces;
    if(shift > 0){
        _shift_right_nstr(out, shift);
    }else if(shift < 0){
        _shift_left_nstr(out, -1*shift);
    }
    out[digits + 1] = 0;
}

static void _shift_right_nstr(const char* c, unsigned int places) {
	char* s, c1, c2;
	while (places--) {
		s = (char*)c;
		c1 = *s;
		*s++ = '0';
		while (*s) {
			c2 = *s;
			*s++ = c1;
			c1 = c2;
		}
	}
//	}
}

static void _shift_left_nstr(const char* c, unsigned int places) {
	char* s, *d;
	while (places--) {
		s = (char*)(c + 1);
		d = (char*) c;
		while (*s) {
			*d++ = *s++;
		}
		*d++ = '0';
	}
}


void utils_dtostr(char* buff, int digits, double value)
{
	int decpt, sign;
	digits++;
	char *out = e_cvt(value, buff, digits, &decpt, &sign);
	if (decpt <= 0) {
		_shift_right_nstr(out, -1*decpt + 2);
		out[1] = '.';
	}
	else {
		out = &buff[decpt + 1];
		_shift_right_nstr(out, 1);
		buff[decpt + 1] = '.';
	}
	if (sign) {
		buff[0] = '-';
		buff[digits + 3] = 0;
	}
	else {
		_shift_left_nstr(buff, 1);
		buff[digits] = 0;
	}
}


double utils_strtod(char* buffer)
{
    char* se;
    return strtod(buffer, &se);
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