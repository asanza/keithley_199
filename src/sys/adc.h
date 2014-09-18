/* 
 * File:   adc.h
 * Author: diego
 *
 * Created on April 18, 2014, 10:22 PM
 */

#ifndef ADC_H
#define	ADC_H

#include "hal.h"


#ifdef	__cplusplus
extern "C" {
#endif

    /* mux structure. These bytes are sended to mux on each conversion */
    typedef union{
        struct{
            uint8_t mux_d;
            uint8_t mux_c;
            uint8_t mux_b;
            uint8_t mux_a;
        };
        struct{
            uint32_t w;
        };
    }adc_mux;

typedef enum{
    ADC_INTEGRATION_50HZ = 50000, /**< 20mS @ 2.5MHz */
    ADC_INTEGRATION_60HZ = 41667, /**< 16mS @ 2.5MHz */
}adc_integration_period;


    typedef enum {
        ADC_INPUT_VOLTAGE_DC = 0x00,
        ADC_INPUT_VOLTAGE_AC,
        ADC_INPUT_CURRENT_DC,
        ADC_INPUT_CURRENT_AC,
        ADC_INPUT_RESISTANCE_2W,
        ADC_INPUT_RESISTANCE_4W,
        ADC_INPUT_COUNT,
    }adc_input;


    typedef enum {
        ADC_CHANNEL_0 = 0x00,
        ADC_CHANNEL_1 = 0x01,
        ADC_CHANNEL_2 = 0x02,
        ADC_CHANNEL_3 = 0x04,
        ADC_CHANNEL_4 = 0x08,
        ADC_CHANNEL_5 = 0x10,
        ADC_CHANNEL_6 = 0x20,
        ADC_CHANNEL_7 = 0x40,
        ADC_CHANNEL_8 = 0x80,
        ADC_NUMBER_OF_CHANNELS,
    }adc_channel;

    typedef enum {
        ADC_RANGE_300m = 0x00,
        ADC_RANGE_3,
        ADC_RANGE_30,
        ADC_RANGE_300,
        ADC_RANGE_3K,
        ADC_RANGE_30K,
        ADC_RANGE_300K,
        ADC_RANGE_3M,
        ADC_RANGE_30M,
        ADC_RANGE_300M,
        ADC_RANGE_COUNT,
    } adc_range;

    typedef enum{
                ADC_ERROR_NOT_SUPPORTED, 
    }adc_error;

    adc_error adc_set_range(adc_range scale);
    adc_range adc_get_range();
    adc_input adc_get_input();

    adc_error adc_set_integration_period(adc_integration_period period);
    adc_integration_period adc_get_integration_period();
    adc_error adc_set_input(adc_input input, adc_range range);
    double adc_read_value(adc_channel channel);
    adc_error adc_init(adc_integration_period period, adc_input input, adc_range range);
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

