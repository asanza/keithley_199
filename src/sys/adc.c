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
 * When the problem with the jitter is under control, the rest is to send the
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
#include "adc.h"
#include "adcctrl.h"

#define SENSE_100K_BIT         (1<<28)
#define SIG_x10_BIT            (1<<22)
#define N_AC_BIT               (1<<21)


#define NCAL_BIT                (1<<7)
#define NZERO_BIT               (1<<6)
#define FAST_BIT                (1<<5)
#define NREAD_SWITCH_BIT        (1<<4)
#define SIG_BIT                 (1<<3)
#define N_FINAL_SLOPE_BIT       (1<<2)
#define SYNC_BIT                (1<<1)
#define INT_BIT                 (1<<0)

#define IS_START_INTEGRATION(x)  ((x&(N_FINAL_SLOPE_BIT|INT_BIT)) == (N_FINAL_SLOPE_BIT|INT_BIT))
#define IS_STOP_INTEGRATION(x) ((x&N_FINAL_SLOPE_BIT)== (N_FINAL_SLOPE_BIT))
#define IS_RUN_DOWN_SLOPE(x) ((x&SYNC_BIT) == SYNC_BIT)
#define IS_PRE_INT_PULSE(x) ((x&(N_FINAL_SLOPE_BIT|SYNC_BIT))==(N_FINAL_SLOPE_BIT|SYNC_BIT))
#define VREF -2.8

/* state variables */
static adc_range range;
static adc_input input;

static double adc_do_measurement(unsigned char channel, adc_control_sequence* sequence);


double adc_read_value(adc_channel channel){
    adc_control_sequence* seq = adcctrl_get_sequence(input, range);
    assert(seq);
    double value = adc_do_measurement(channel, seq);
    if(value >= ADC_MAX_VALUE) value = ADC_MAX_VALUE;
    if(value <= ADC_MIN_VALUE) value = ADC_MIN_VALUE;
    switch(range){
        case ADC_RANGE_3:
        case ADC_RANGE_3K: return value*1.0;
        case ADC_RANGE_30m:
        case ADC_RANGE_30:
        case ADC_RANGE_30K: return value*10.0;
        case ADC_RANGE_300m:
        case ADC_RANGE_300:
        case ADC_RANGE_300K: return value*100.0;
    }
}

adc_input adc_get_input(){
    return input;
}

adc_range adc_get_range(void){
    return range;
}

adc_error adc_set_range(adc_range scale){
    adc_control_sequence* seq = adcctrl_get_sequence(input,scale);
    if(!seq) return ADC_ERROR_NOT_SUPPORTED;
    range = scale;
    return ADC_ERROR_NONE;
}

adc_error adc_set_input(adc_input input_in, adc_range range_in){
    adc_control_sequence* seq = adcctrl_get_sequence(input_in,range_in);
    if(!seq) return ADC_ERROR_NOT_SUPPORTED;
    input = input_in;
    range = range_in;
    return ADC_ERROR_NONE;
}

static adc_error adc_integration_period_supported(adc_integration_period period){
    switch(period){
        case ADC_INTEGRATION_60HZ:
        case ADC_INTEGRATION_50HZ:
            return ADC_ERROR_NONE;
        default:
            return ADC_ERROR_NOT_SUPPORTED;
    }
}

adc_error adc_set_integration_period(adc_integration_period period){
    if(adc_integration_period_supported(period)!=ADC_ERROR_NONE)
        return ADC_ERROR_NOT_SUPPORTED;
    hal_adc_set_integration_period((uint32_t)period);
}

adc_error adc_init(adc_integration_period period, adc_input input_, adc_range range_){
    if(adc_integration_period_supported(period)!=ADC_ERROR_NONE)
        return ADC_ERROR_NOT_SUPPORTED;
    adc_control_sequence* seq = adcctrl_get_sequence(input_,range_);
    if(!seq) return ADC_ERROR_NOT_SUPPORTED;
    input  = input_;
    range = range_;
    hal_adc_init(period);
    return ADC_ERROR_NONE;
}

static uint32_t do_sequence(unsigned char channel, adc_control_sequence* sequence){
    uint32_t start_int_mux_cfg = hal_adcseq_next(sequence);
    /* send the start integration mux configuration */
    while(IS_RUN_DOWN_SLOPE(start_int_mux_cfg)||IS_PRE_INT_PULSE(start_int_mux_cfg)){
        /* if still in run down or pre-int get the next mux */
        hal_adc_send_mux(channel, start_int_mux_cfg);
        start_int_mux_cfg = hal_adcseq_next(sequence);
    }
    /* send the start integration command */
    assert(IS_START_INTEGRATION(start_int_mux_cfg));
    uint32_t stop_int_mux_cfg = hal_adcseq_next(sequence);
    assert(IS_STOP_INTEGRATION(stop_int_mux_cfg));
    uint32_t run_down_mux_cfg = hal_adcseq_next(sequence);
    assert(IS_RUN_DOWN_SLOPE( run_down_mux_cfg));
    /* here comes the signal integration */
    return hal_adc_integration_sequence(channel, start_int_mux_cfg,
            stop_int_mux_cfg,  run_down_mux_cfg);
}


double adc_do_measurement(unsigned char channel, adc_control_sequence* sequence){
    assert(sequence);
    adcctrl_reset(sequence); // always start at sequence start point.
    int signal_count, sigzero_count, ref_count, refzero_count;
    signal_count = do_sequence(channel, sequence);
    sigzero_count = do_sequence(channel, sequence);
    refzero_count = do_sequence(channel, sequence);
    ref_count = do_sequence(channel, sequence);
    int signal, reference;
    signal = signal_count - sigzero_count;
    reference = ref_count - refzero_count;
    assert(reference);
    return VREF*signal*1.0/reference*1.0;
}

