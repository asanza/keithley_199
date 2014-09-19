/* This file generates the integration sequences which are sended to analog
 * multiplexer in multimeter.
 * They where copied from another working Keithley 199.
 * (c) 2014 Diego F. Asanza
 */

#include <stdint.h>
#include <stddef.h>

#include "hal.h"

struct hal_adc_integration_sequence_t{
    uint32_t actual_value;
    uint32_t size;
    const uint32_t* mux_values;
};

#define START_SEQUENCE(seq_name) const uint32_t seq_name##__[]=

#define END_SEQUENCE(seq_name) ; static hal_adc_sequence seq_name = { \
                                            .actual_value = 0, \
                                            .size = sizeof(seq_name##__), \
                                            .mux_values = seq_name##__};

START_SEQUENCE(seq_300mV){
    0x01BFE292, 0x01BFE29A,0x01FFE29A,      /* preset */
    0x01FFE29D, 0x01FFE29C, 0x01BFE29A,     /* signal */
    0x11BFE292, 0x11FFE292,                 /* preset */
    0x11FFE295, 0x11FFE294, 0x11BFE292,     /* signal zero */
    0x41BFE292,                             /* preset */
    0x41BFE295, 0x41BFE294, 0x41BFE252,     /* zero */
    0x41BFE255, 0x41BFE254, 0x41BFE252      /* ref */
}END_SEQUENCE(seq_300mV)

START_SEQUENCE(seq_3V){
    0x01BFE292, 0x01BFE29A,      /* preset */
    0x01BFE29D, 0x01BFE29C, 0x01BFE29A,     /* signal */
    0x11BFE292,                  /* preset */
    0x11BFE295, 0x11BFE294, 0x41BFE292,     /* signal zero */
    0x41BFE295, 0x41BFE294, 0x41BFE252,     /* zero */
    0x41BFE255, 0x41BFE254, 0x41BFE252      /* ref */
}END_SEQUENCE(seq_3V)

START_SEQUENCE(seq_30V){
    0x29BFE092,      /* preset */
    0x29BFE095, 0x29BFE094, 0x08BFE092,     /* signal */
    0x08BFE095, 0x08BFE094, 0x49BFE092,     /* signal zero */
    0x49BFE095, 0x49BFE094, 0x49BFE052,     /* zero */
    0x49BFE055, 0x49BFE054, 0x49BFE052      /* ref */
}END_SEQUENCE(seq_30V)

START_SEQUENCE(seq_300V){
    0x25BFE092,      /* preset */
    0x25BFE095, 0x25BFE094, 0x15BFE092,     /* signal */
    0x15BFE095, 0x15BFE094, 0x45BFE092,     /* signal zero */
    0x45BFE095, 0x45BFE094, 0x45BFE052,     /* zero */
    0x45BFE055, 0x45BFE054, 0x45BFE052      /* ref */
}END_SEQUENCE(seq_300V)

START_SEQUENCE(seq_30mADC){
    0x4DE7E0D5, 0x4DE7E0D4, 0x4DE7E0D2,
    0x4DF7E096,
    0x4DF7E095, 0x4DF7E094, 0x4DE7E0D2,
    0x4DB7E096,
    0x4DB7E095, 0x4DB7E094, 0x4DE7E0D2,
    0x4DB7E056,
    0x4DB7E055, 0x4DB7E054, 0x4DE7E0D2,
}END_SEQUENCE(seq_30mADC)

START_SEQUENCE(seq_3ADC){
    0x45E7E0D5, 0x45E7E0D4, 0x45E7E0D2,
    0x45B7E096,
    0x45B7E095, 0x45B7E094, 0x45E7E0D2,
    0x45F7E096,
    0x45F7E095, 0x45F7E094, 0x45E7E0D2,
    0x45B7E056,
    0x45B7E055, 0x45B7E054, 0x45E7E0D2,
}END_SEQUENCE(seq_3ADC)

START_SEQUENCE(seq_30mAAC){
    0x4D15E8D5, 0x4D15E8D4, 0x4D15E8D2,
            0x4D35E896,
            0x4D35E895, 0x4D35E894, 0x4D15E8D2,
            0x4D35E896,
            0x4D35E895, 0x4D35E894, 0x4D15E8D2,
            0x4D35E856,
            0x4D35E855, 0x4D35E854, 0x4D15E8D2,
}END_SEQUENCE(seq_30mAAC)


START_SEQUENCE(seq_3AAC){
    0x4515E8D5, 0x4515E8D4, 0x4515E8D2,
            0x4535E896,
            0x4535E895, 0x4535E894, 0x4515E8D2,
            0x4535E896,
            0x4535E895, 0x4535E894, 0x4515E8D2,
            0x4535E856,
            0x4535E855, 0x4535E854, 0x4515E8D2,
}END_SEQUENCE(seq_3AAC)

static hal_adc_sequence* get_vdc_seq(adc_range range);
static hal_adc_sequence* get_vac_seq(adc_range range);
static hal_adc_sequence* get_cdc_seq(adc_range range);
static hal_adc_sequence* get_cac_seq(adc_range range);
static hal_adc_sequence* get_res_seq(adc_range range);
//static hal_adc_sequence* get_vdc_seq(adc_range range);

hal_adc_sequence* hal_adc_get_sequence(adc_input input, adc_range range){
    switch(input){
        case ADC_INPUT_VOLTAGE_DC: return get_vdc_seq(range);
        case ADC_INPUT_CURRENT_DC: return get_cdc_seq(range);
        case ADC_INPUT_CURRENT_AC: return get_cac_seq(range);
    }
    return NULL;
}

hal_adc_sequence* get_cdc_seq(adc_range range){
    switch(range){
        case ADC_RANGE_30m: seq_30mADC.actual_value = 0; return &seq_30mADC;
        case ADC_RANGE_3: seq_3ADC.actual_value = 0; return &seq_3ADC;
    }
    return NULL;
}

hal_adc_sequence* get_cac_seq(adc_range range){
    switch(range){
        case ADC_RANGE_30m: seq_30mAAC.actual_value = 0; return &seq_30mAAC;
        case ADC_RANGE_3: seq_3AAC.actual_value = 0; return &seq_3AAC;
    }
    return NULL;
}

hal_adc_sequence* get_vdc_seq(adc_range range){
    switch(range){
        case ADC_RANGE_300m: seq_300mV.actual_value = 0; return &seq_300mV;
        case ADC_RANGE_3: seq_3V.actual_value = 0; return &seq_3V;
        case ADC_RANGE_30: seq_30V.actual_value = 0; return &seq_30V;
        case ADC_RANGE_300: seq_300V.actual_value = 0; return &seq_300V;
    };
    return NULL;
}

uint32_t hal_adcseq_next(hal_adc_sequence* sequence){
    uint32_t value;
    if(sequence->actual_value<sequence->size){
        value = sequence->mux_values[sequence->actual_value];
        sequence->actual_value++;
    }
    else{
        sequence->actual_value = 0;
        value = 0;
    }
    return value;
}