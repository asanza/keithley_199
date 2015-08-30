/* ecvt, fcvt -- convert floating-point numbers to ascii	-*- C -*-	*/

/* Copyright (c) 2009 Ian Piumarta
 * 
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the 'Software'), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to
 * do so, provided that the above copyright notice(s) and this permission
 * notice appear in all copies of the Software.  Inclusion of the above
 * copyright notice(s) and this permission notice in supporting documentation
 * would be appreciated but is not required.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS'.  USE ENTIRELY AT YOUR OWN RISK.
 */

/* This file provides replacements for the functions ecvt() and fcvt() that
 * were recently deprecated in POSIX.  The interface and behaviour is identical
 * to the functions that they replace (and faster too, at least on my machine).
 * They have been tested on 32- and 64-bit machines of both orientations.
 * 
 * For details on the use of these functions, see your ecvt(3) manual page.  If
 * you don't have one handy, there might still be one available here:
 * http://opengroup.org/onlinepubs/007908799/xsh/ecvt.html
 */

char *e_cvt(double value, char* buff, int ndigit, int *decpt, int *sign);	
char *f_cvt(double value, char* buff, int ndigit, int *decpt, int *sign);	

/* ---------------------------------------------------------------- */
