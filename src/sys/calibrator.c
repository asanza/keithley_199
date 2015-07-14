/**
 */

#include <fitlinear.h>
#include <systasks.h>

//struct calibration_t{
//    adc_input input;
//    adc_range range;
//    double slope;
//    double offset;
//};
//    typedef struct calibration_t calibrator;

//sys_error sys_dmm_calibrate(double* real_value, double* meas_value, int size,
//            calibrator* cal){
//    double cov_00, cov_01, cov_11, sumsq;
//    // TODO: Do calibration.
//    int ret = gsl_fit_linear(real_value, 1, meas_value, 1, size, &cal->offset, &cal->slope,
//            &cov_00, &cov_01, &cov_11, &sumsq);
//    if(ret)
//        return DMM_UNCAL;
//    else
//        return DMM_ERROR_NONE;
//}