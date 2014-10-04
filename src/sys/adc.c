/*
 * ADC High Level
 */

#include <peripheral/outcompare.h>
#include <peripheral/timer.h>
#include <peripheral/pps.h>
#include <peripheral/ports.h>
#include <peripheral/spi.h>
#include <stdint.h>
#include <assert.h>

#include <FreeRTOS.h>
#include <queue.h>

#include "task.h"
#include "adc.h"

#include "HardwareProfile.h"

/* following codes are used with mux_d */
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

#define START_INTEGRATION(x)  ((x&~0x07)|N_FINAL_SLOPE_BIT|INT_BIT)
#define STOP_INTEGRATION(x) ((x&~0x07)|N_FINAL_SLOPE_BIT)
#define RUN_DOWN_SLOPE(x) ((x&~0x07)|SYNC_BIT)
#define PRE_INT_PULSE(x) ((x&~0x07)|N_FINAL_SLOPE_BIT|SYNC_BIT)

/* state variables */
static adc_range range;
static adc_input input; 

#define VREF  -2.8

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