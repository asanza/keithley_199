/*
 * fitlinear.h
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
 * Created on January 22, 2015, 11:22 PM
 */
#ifndef FITLINEAR_H
#define	FITLINEAR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>

    /** fits into c0 + c1 X*/
int fit_linear(const double *x, const double* y, int size, double* c0, double* c1);

int
gsl_fit_linear (const double *x, const size_t xstride,
                const double *y, const size_t ystride,
                const size_t n,
                double *c0, double *c1,
                double *cov_00, double *cov_01, double *cov_11, double *sumsq);

#ifdef	__cplusplus
}
#endif

#endif	/* FITLINEAR_H */

