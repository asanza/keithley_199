/* 
 * File:   adc.h
 * Author: diego
 *
 * Created on April 18, 2014, 10:22 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <hal.h>
#include "adcctrl.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
            ADC_ERROR_NOT_SUPPORTED,
            ADC_ERROR_NONE
}adc_error;



adc_error adc_set_range(adc_range scale);
adc_range adc_get_range(void);
adc_input adc_get_input(void);
adc_error adc_set_integration_period(adc_integration_period period);
adc_integration_period adc_get_integration_period(void);
adc_error adc_set_input(adc_input input, adc_range range);
/**
 * return the value readed by the adc.
 * @param channel the channel to be readed (may be not needed, as we can connect 
 * the scanner directly to the processor.).
 * @param flag ADC_OVERFLOW or ADC_UNDERFLOW if the measurement is over or under
 * allowed range.
 * @return the value measured by the adc.
 */
double adc_read_value(adc_channel channel, int* flag);
adc_error adc_init(adc_integration_period period, adc_input input, adc_range range);

double adc_get_max(adc_range range);
    
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

