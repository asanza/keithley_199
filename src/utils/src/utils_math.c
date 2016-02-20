#include "utils_math.h"
#include <math.h>

double utils_roundd(double x, unsigned int digits) {
    int val;
    double p = pow(10, digits);
    x = x*p;
    val = (x >= 0) ? (int)(x + 0.5) : (int)(x - 0.5);
    return val*1.0/p;
}