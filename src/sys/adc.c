/* ADC Abstraction Layer
 * (c) 2014 Diego F. Asanza
 * This file implements the ADC Low level control interface
 */

/** How does keithley ADC Works:
 * The K199 uses a charge balancing adc. It is controlled through five shift-
 * registers on the analog board which controls the different switch on the input
 * multiplexer and the charge-discharge (start-stop) of the integrator.
 *
 * These shift registers are controlled through three lines  from the digital
 * board. The first line is clock, the second data, and the third the strobe (loads
 * the data shifted from the digital board on the output of the shift registers).
 *
 * The values sended to the shift registers (from now on adc sequences) should
 * be precicely timed, as the integration period should be exactly the same always.
 * this is done by precicely controlling the strobe signal, to be sended with no
 * jitter (which is not easy in a microcontroller).
 *
 * When the problem with the jitter is under controll, the rest is to send the
 * right adc sequences according to what we are triying to measure. For ac/dc
 * voltages, the k199 do four measurements at once, first signal, after that zero,
 * again zero (for reference) and finally reference voltage. The final value is
 * calculated from the formula: Vout = VREF*(signal-zero)/(ref - zero).
 *
 * The sequences I use to do all these measurements where reverse engineered from
 * a working k199 and can be seen in adcseq.c.
 *
 * This file implements the high level abstraction of the adc, where we can set
 * the desired input and range and integration period, and we get a nice number
 * which represents the value measured. It works selecting the right adc sequence
 * to work according the range and input and finally calling the low layer (hardware
 * adc) in order to perform the actual measurement.
 * 
 */

#include <stdint.h>
#include <assert.h>
#include <FreeRTOS.h>
#include "adc.h"

/* state variables */
static adc_range range;
static adc_input input; 

double adc_read_value(adc_channel channel){
    hal_adc_sequence* seq = hal_adc_get_sequence(input, range);
    assert(seq!=NULL);
    double value = hal_adc_do_measurement(channel, seq);
    switch(range){
        case ADC_RANGE_3: return value*1.0;
        case ADC_RANGE_30m:
        case ADC_RANGE_30: return value*10.0;
        case ADC_RANGE_300m:
        case ADC_RANGE_300: return value*100.0;
    }
}

adc_input adc_get_input(){
    return input;
}

adc_error adc_set_range(adc_range scale){
    portENTER_CRITICAL();
    range = scale;
    portEXIT_CRITICAL();
}

adc_error adc_set_input(adc_input input_in, adc_range range_in){
    portENTER_CRITICAL();
    input = input_in;
    range = range_in;
    portEXIT_CRITICAL();
}

adc_error adc_set_integration_period(adc_integration_period period){
    hal_adc_set_integration_period((uint32_t)period);
}

adc_error adc_init(adc_integration_period period, adc_input input_, adc_range range_){
    input  = input_;
    range = range_;
    hal_adc_init(period);
}