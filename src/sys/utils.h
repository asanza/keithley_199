/* 
 * File:   utils.h
 * Author: diego
 *
 * Created on September 22, 2014, 1:10 AM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>

#define GSL_SUCCESS 1

int
gsl_fit_linear (const double *x, const size_t xstride,
                const double *y, const size_t ystride,
                const size_t n,
                double *c0, double *c1,
                double *cov_00, double *cov_01, double *cov_11, double *sumsq);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

