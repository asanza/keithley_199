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

static double read_ac(uint8_t channel, adc_range range);
static double read_dc(uint8_t channel, adc_range range);
static double read_cdc(uint8_t channel, adc_range range);

double adc_read_value(adc_channel channel){
    double value;
    switch (input)
    {
        case ADC_INPUT_VOLTAGE_AC: value = read_ac(channel, range);break;
        case ADC_INPUT_VOLTAGE_DC: value = read_dc(channel,range); break;
        case ADC_INPUT_CURRENT_DC: value = read_cdc(channel, range); break;
        case ADC_INPUT_CURRENT_AC: value = read_cdc(channel, range); break;
        default:
            assert(0); /* no input set. Input should be set. */
    }
    switch (range){
        case ADC_RANGE_3:   return value*1.0;
        case ADC_RANGE_30m:
        case ADC_RANGE_30:  return value*10.0;
        case ADC_RANGE_300m:
        case ADC_RANGE_300: return value*100.0;
        default:
            assert(0); /* no valid range set */
    }
}

double read_cdc(uint8_t channel, adc_range range){
    assert(range == ADC_RANGE_30m || range == ADC_RANGE_3);
        hal_adc_sequence* seq = hal_adc_get_sequence(input, range);
        return hal_adc_do_measurement(channel, seq);
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


/* DC Voltage Read */
double read_dc(uint8_t channel, adc_range range){
    assert(range >= ADC_RANGE_300m && range <= ADC_RANGE_300);
        hal_adc_sequence* seq = hal_adc_get_sequence(input, range);
        return hal_adc_do_measurement(channel, seq);
}



/* AC Voltage Read */

#define MUX_READ_ZERO_AC(x) (x&~NZERO_BIT)|NCAL_BIT | N_AC_BIT
#define MUX_READ_REF_AC(x) (x& ~NCAL_BIT)|NZERO_BIT | N_AC_BIT
#define MUX_READ_AC_SIGNAL(x) (( x &~N_AC_BIT)|NZERO_BIT|NCAL_BIT)

static const adc_mux ac_mux[] = {
    {0x10, 0xEC, 0x3F, 0xCD } ,  /* 300mV */
    {0x10, 0xCC, 0xBD, 0xCD } ,  /* 3V */
    {0x10, 0xF4, 0xBD, 0xCD } ,  /* 30V */
    {0x10, 0xE4, 0xBD, 0xCD } }; /* 300V */

double read_ac(uint8_t channel, adc_range range){
    assert(range>=0 && range<=4);
    /* choose the range */
    adc_mux mux = ac_mux[range];
    int zero_counter, signal_counter, ref_counter;
    uint32_t signal_mux = MUX_READ_AC_SIGNAL(mux.w);
    uint32_t zero_mux = MUX_READ_ZERO_AC(mux.w);
    uint32_t ref_mux = MUX_READ_REF_AC(mux.w);
    /* read zero */
    hal_adc_send_mux(channel, PRE_INT_PULSE(zero_mux));
    zero_counter = hal_adc_integration_sequence(channel, START_INTEGRATION(zero_mux),
            STOP_INTEGRATION(zero_mux),RUN_DOWN_SLOPE(signal_mux));
    /* read signal */
    signal_counter = hal_adc_integration_sequence(channel, START_INTEGRATION(signal_mux),
            STOP_INTEGRATION(signal_mux),RUN_DOWN_SLOPE(signal_mux));
    /* precalculate reading */
    signal_counter -= zero_counter;
    /* read zero */
    hal_adc_send_mux(channel, PRE_INT_PULSE(zero_mux));
    zero_counter = hal_adc_integration_sequence(channel, START_INTEGRATION(zero_mux),
            STOP_INTEGRATION(zero_mux),RUN_DOWN_SLOPE(signal_mux));
    /* read ref */
    hal_adc_send_mux(channel, PRE_INT_PULSE(ref_mux));
    ref_counter = hal_adc_integration_sequence(channel, START_INTEGRATION(ref_mux),
            STOP_INTEGRATION(ref_mux),RUN_DOWN_SLOPE(signal_mux));
    ref_counter -= zero_counter;
    double t = VREF * signal_counter*1.0/ref_counter*1.0;
    return t;
}

adc_error adc_set_integration_period(adc_integration_period period){
    hal_adc_set_integration_period((uint32_t)period);
}

adc_error adc_init(adc_integration_period period, adc_input input_, adc_range range_){
    input  = input_;
    range = range_;
    hal_adc_init(period);
}