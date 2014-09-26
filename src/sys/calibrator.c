/**
 */

#include <utils.h>
#include <dmm.h>

struct calibration_t{
    adc_input input;
    adc_range range;
    double slope;
    double offset;
};

dmm_error sys_dmm_calibrate(double* real_value, double* meas_value, int size,
            calibrator* cal){
    double cov_00, cov_01, cov_11, sumsq;
    // TODO: Do calibration.
    int ret = gsl_fit_linear(real_value, 1, meas_value, 1, size, &cal->offset, &cal->slope,
            &cov_00, &cov_01, &cov_11, &sumsq);
    if(ret!=GSL_SUCCESS)
        return DMM_UNCAL;
    else
        return DMM_OK;
}