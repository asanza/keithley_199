/* This file generates the integration sequences which are sended to analog
 * multiplexer in multimeter.
 * They where copied from another working Keithley 199.
 * (c) 2014 Diego F. Asanza
 */

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <diag.h>
#include "adcctrl.h"

struct hal_adc_integration_sequence_t {
    uint32_t actual_value;
    uint32_t size;
    const uint32_t* mux_values;
};

#define START_SEQUENCE(seq_name) const uint32_t seq_name##__[]=

#define END_SEQUENCE(seq_name) ; static adc_control_sequence seq_name = { \
                                            .actual_value = 0, \
                                            .size = sizeof(seq_name##__), \
                                            .mux_values = seq_name##__};

START_SEQUENCE(seq_300mV)
{
    0x01BFE292, 0x01BFE29A, 0x01FFE29A, /* preset */
    0x01FFE29D, 0x01FFE29C, 0x01BFE29A, /* signal */
    0x11BFE292, 0x11FFE292, /* preset */
    0x11FFE295, 0x11FFE294, 0x11BFE292, /* signal zero */
    0x41BFE292, /* preset */
    0x41BFE295, 0x41BFE294, 0x41BFE252, /* zero */
    0x41BFE255, 0x41BFE254, 0x41BFE252 /* ref */
}
END_SEQUENCE(seq_300mV)

START_SEQUENCE(seq_3V)
{
    0x01BFE292, 0x01BFE29A, /* preset */
    0x01BFE29D, 0x01BFE29C, 0x01BFE29A, /* signal */
    0x11BFE292, /* preset */
    0x11BFE295, 0x11BFE294, 0x41BFE292, /* signal zero */
    0x41BFE295, 0x41BFE294, 0x41BFE252, /* zero */
    0x41BFE255, 0x41BFE254, 0x41BFE252 /* ref */
}
END_SEQUENCE(seq_3V)

START_SEQUENCE(seq_30V)
{
    0x29BFE092, /* preset */
    0x29BFE095, 0x29BFE094, 0x08BFE092, /* signal */
    0x08BFE095, 0x08BFE094, 0x49BFE092, /* signal zero */
    0x49BFE095, 0x49BFE094, 0x49BFE052, /* zero */
    0x49BFE055, 0x49BFE054, 0x49BFE052 /* ref */
}
END_SEQUENCE(seq_30V)

START_SEQUENCE(seq_300V)
{
    0x25BFE092, /* preset */
    0x25BFE095, 0x25BFE094, 0x15BFE092, /* signal */
    0x15BFE095, 0x15BFE094, 0x45BFE092, /* signal zero */
    0x45BFE095, 0x45BFE094, 0x45BFE052, /* zero */
    0x45BFE055, 0x45BFE054, 0x45BFE052 /* ref */
}
END_SEQUENCE(seq_300V)

START_SEQUENCE(seq_300mVAC)
{
    0xCD1FECD5, 0xCD1FECD4, 0xCD1FECD2, /* signal */
    0xCD3FEC96, /* preset */
    0xCD3FEC95, 0xCD3FEC94, 0xCD3F1CD2, /* zero */
    0xCD3FEC96, /* preset */
    0xCD3FEC95, 0xCD3FEC94, 0xCD3F1CD2, /* zero */
    0xCD3FEC56, /* preset */
    0xCD3FEC55, 0xCD3FEC54, 0xCD1FECD2, /* ref */
}
END_SEQUENCE(seq_300mVAC)

START_SEQUENCE(seq_3VAC)
{
    0xCD9DCCD5, 0xCD9DCCD4, 0xCD9DCCD2, /* signal */
    0xCDBDCC96,
    0xCDBDCC95, 0xCDBDCC94, 0xCD9DCCD2, /* zero */
    0xCDBDCC96,
    0xCDBDCC95, 0xCDBDCC94, 0xCD9DCCD2, /* zero */
    0xCDBDCC56,
    0xCDBDCC55, 0xCDBDCC54, 0xCD9DCCD2 /* ref */
}
END_SEQUENCE(seq_3VAC)

START_SEQUENCE(seq_30VAC)
{
    0xCD9DF4D5, 0xCD9DF4D4, 0xCD9DF4D2, /* signal */
    0xCDBDF496,
    0xCDBDF495, 0xCDBDF494, 0xCD9DF4D2, /* zero */
    0xCDBDF496,
    0xCDBDF495, 0xCDBDF494, 0xCD9DF4D2, /* zero */
    0xCDBDF456,
    0xCDBDF455, 0xCDBDF454, 0xCD9DF4D2, /* ref */
}
END_SEQUENCE(seq_30VAC)

START_SEQUENCE(seq_300VAC)
{
    0xCD9DE4D5, 0xCD9DE4D4, 0xCD9DE4D2, /* signal */
    0xCDBDE496,
    0xCDBDE495, 0xCDBDE494, 0xCDBDE4D2,
    0xCDBDE496,
    0xCDBDE495, 0xCDBDE494, 0xCDBDE4D2,
    0xCDBDE456,
    0xCDBDE455, 0xCDBDE454, 0xCD9DE4D2
}
END_SEQUENCE(seq_300VAC)

START_SEQUENCE(seq_30mADC)
{
    0x4DE7E0D5, 0x4DE7E0D4, 0x4DE7E0D2,
    0x4DF7E096,
    0x4DF7E095, 0x4DF7E094, 0x4DE7E0D2,
    0x4DB7E096,
    0x4DB7E095, 0x4DB7E094, 0x4DE7E0D2,
    0x4DB7E056,
    0x4DB7E055, 0x4DB7E054, 0x4DE7E0D2,
}
END_SEQUENCE(seq_30mADC)

START_SEQUENCE(seq_3ADC)
{
    0x45E7E0D5, 0x45E7E0D4, 0x45E7E0D2,
    0x45B7E096,
    0x45B7E095, 0x45B7E094, 0x45E7E0D2,
    0x45F7E096,
    0x45F7E095, 0x45F7E094, 0x45E7E0D2,
    0x45B7E056,
    0x45B7E055, 0x45B7E054, 0x45E7E0D2,
}
END_SEQUENCE(seq_3ADC)

START_SEQUENCE(seq_30mAAC)
{
    0x4D15E8D5, 0x4D15E8D4, 0x4D15E8D2,
    0x4D35E896,
    0x4D35E895, 0x4D35E894, 0x4D15E8D2,
    0x4D35E896,
    0x4D35E895, 0x4D35E894, 0x4D15E8D2,
    0x4D35E856,
    0x4D35E855, 0x4D35E854, 0x4D15E8D2,
}
END_SEQUENCE(seq_30mAAC)


START_SEQUENCE(seq_3AAC)
{
    0x4515E8D5, 0x4515E8D4, 0x4515E8D2,
    0x4535E896,
    0x4535E895, 0x4535E894, 0x4515E8D2,
    0x4535E896,
    0x4535E895, 0x4535E894, 0x4515E8D2,
    0x4535E856,
    0x4535E855, 0x4535E854, 0x4515E8D2,
}
END_SEQUENCE(seq_3AAC)

START_SEQUENCE(seq_300Ohm)
{
    0x43FAE1D5, 0x43FAE1D4, 0x43FAE1D2, // SenseLo
    0x43FAE1D5, 0x43FAE1D4, 0x23BCE192, // Nothing
    0x23BCE195, 0x23BCE194, 0x03BEE192,
    0x42BEE1D2,
    0x42BEE1D5, 0x42BEE1D4, 0x03BEE19A,
    0x03FEE19A,
    0x03FEE19D, 0x03FEE19C, 0x43FAE1D2,
}
END_SEQUENCE(seq_300Ohm)

START_SEQUENCE(seq_3KOhm)
{
    0x43BAE1D5, 0x43BAE1D4, 0x43BAE1D2,
    0x43BAE1D5, 0x43BAE1D4, 0x23BCE192,
    0x23BCE195, 0x23BCE194, 0x03BEE192,
    0x42BEE1D2,
    0x42BEE1D5, 0x42BEE1D4, 0x03BEE19A,
    0x03BEE19D, 0x03BEE19C, 0x43BAE1D2,
}
END_SEQUENCE(seq_3KOhm)
//
//START_SEQUENCE(seq_30KOhm)
//{
//    //TODO: Work on this sequence!
//    0x43BAE1D5, 0x43BAE1D4, 0x43BAE1D2,
//    0x43BAE1D5, 0x43BAE1D4, 0x43BAE1D2,
//    0x43BAE1D5, 0x43BAE1D4, 0x23BCE192,
//    0x23BCE195, 0x23BCE194, 0x03BEE192,
//    0x42BEE1D2,
//    0x42BEE1D5, 0x42BEE1D4, 0x03BEE19A,
//    0x03BEE19D, 0x03BEE19C, 0x43BAE1D2,
//}
//END_SEQUENCE(seq_30KOhm)
//
//START_SEQUENCE(seq_3MegOhm){
//    0.003387  0xCB 0xB1 0xE1 0xD5,
// 0.016401  0xCB 0xB1 0xE1 0xD4,
// 0.000333  0xCB 0xB1 0xE1 0xD2,
//
// 0.003278  0xCB 0xB1 0xE1 0xD5,
// 0.020328  0xCB 0xB1 0xE1 0xD4,
// 0.000412  0xAB 0xB5 0xE1 0x92,
//
// 0.011265  0xAB 0xB5 0xE1 0x95,
// 0.020245  0xAB 0xB5 0xE1 0x94,
// 0.000355  0x8B 0xB5 0xE1 0x92,
//
// 0.000611  0x9B 0xB5 0xE1 0x92,
//
// 0.010804  0x9B 0xB5 0xE1 0x95,
// 0.020271  0x9B 0xB5 0xE1 0x94,
// 0.000412  0x8B 0xB5 0xE1 0x9A,
//
// 0.011329  0x8B 0xB5 0xE1 0x9D,
// 0.020329  0x8B 0xB5 0xE1 0x9C,
// 0.000412  0xCB 0xB1 0xE1 0xD2,
//}END_SEQUENCE(seq_3MegOhm)
//
//
//START_SEQUENCE(seq_30MegOhm){
//    
//}END_SEQUENCE(seq_30MegOhm)
//
//START_SEQUENCE(seq_300MegOhm){
//    
//}END_SEQUENCE(seq_300MegOhm)


static adc_control_sequence* get_vdc_seq(adc_range range);
static adc_control_sequence* get_vac_seq(adc_range range);
static adc_control_sequence* get_cdc_seq(adc_range range);
static adc_control_sequence* get_cac_seq(adc_range range);
static adc_control_sequence* get_res4w_seq(adc_range range);
//static hal_adc_sequence* get_vdc_seq(adc_range range);

int adcctrl_get_sequence_id(adc_input input, adc_range range)
{
    char map[ADC_NUMBER_OF_INPUTS][ADC_RANGE_COUNT];
    assert(input < ADC_NUMBER_OF_INPUTS);
    assert(range < ADC_RANGE_COUNT);
    int i, j, id = 0;
    for (i = 0; i < ADC_NUMBER_OF_INPUTS; i++) {
        for (j = 0; j < ADC_RANGE_COUNT; j++) {
            adc_control_sequence* s = adcctrl_get_sequence(i, j);
            //TODO: Move to a better place.
            if (input == ADC_INPUT_TEMP && range == ADC_RANGE_300) map[i][j] = id++;
            if (s == NULL)
                continue;
            map[i][j] = id++;
        }
    }
    id = map[input][range];
    return id;
}

adc_control_sequence* adcctrl_get_sequence(adc_input input, adc_range range)
{
    switch (input) {
        case ADC_INPUT_VOLTAGE_DC: return get_vdc_seq(range);
        case ADC_INPUT_VOLTAGE_AC: return get_vac_seq(range);
        case ADC_INPUT_CURRENT_DC: return get_cdc_seq(range);
        case ADC_INPUT_CURRENT_AC: return get_cac_seq(range);
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W: return get_res4w_seq(range);
        case ADC_NUMBER_OF_INPUTS:
        default:
            assert(0);
    }
    return NULL;
}

static adc_control_sequence* get_res4w_seq(adc_range range)
{
    switch (range) {
        case ADC_RANGE_300: seq_300Ohm.actual_value = 0;
        return &seq_300Ohm;
        case ADC_RANGE_3K: seq_3KOhm.actual_value = 0;
        return &seq_3KOhm;
        default: return NULL;
    }
    return NULL;
}

static adc_control_sequence* get_vac_seq(adc_range range)
{
    switch (range) {
        case ADC_RANGE_300m: seq_300mVAC.actual_value = 0;
            return &seq_300mVAC;
        case ADC_RANGE_3: seq_3VAC.actual_value = 0;
            return &seq_3VAC;
        case ADC_RANGE_30: seq_30VAC.actual_value = 0;
            return &seq_30VAC;
        case ADC_RANGE_300: seq_300VAC.actual_value = 0;
            return &seq_300VAC;
        default: return NULL;
    };
    return NULL;
}

static adc_control_sequence* get_cdc_seq(adc_range range)
{
    switch (range) {
        case ADC_RANGE_30m: seq_30mADC.actual_value = 0;
            return &seq_30mADC;
        case ADC_RANGE_3: seq_3ADC.actual_value = 0;
            return &seq_3ADC;
        default: return NULL;
    }
    return NULL;
}

static adc_control_sequence* get_cac_seq(adc_range range)
{
    switch (range) {
        case ADC_RANGE_30m: seq_30mAAC.actual_value = 0;
            return &seq_30mAAC;
        case ADC_RANGE_3: seq_3AAC.actual_value = 0;
            return &seq_3AAC;
        default: return NULL;
    }
    return NULL;
}

static adc_control_sequence* get_vdc_seq(adc_range range)
{
    switch (range) {
        case ADC_RANGE_300m: seq_300mV.actual_value = 0;
            return &seq_300mV;
        case ADC_RANGE_3: seq_3V.actual_value = 0;
            return &seq_3V;
        case ADC_RANGE_30: seq_30V.actual_value = 0;
            return &seq_30V;
        case ADC_RANGE_300: seq_300V.actual_value = 0;
            return &seq_300V;
        default: return NULL;
    };
    return NULL;
}

uint32_t adcctrl_get_next_sequence(adc_control_sequence* sequence)
{
    uint32_t value;
    if (sequence->actual_value < sequence->size) {
        value = sequence->mux_values[sequence->actual_value];
        sequence->actual_value++;
    } else {
        sequence->actual_value = 0;
        value = 0;
    }
    return value;
}

void adcctrl_reset(adc_control_sequence* sequence)
{
    sequence->actual_value = 0;
}

adc_range adcctrl_get_next_range(adc_input input, adc_range actual_range)
{
    int i;
    adc_range range = actual_range;
    for (i = actual_range + 1; i < ADC_RANGE_COUNT; i++) {
        if (adcctrl_get_sequence(input, i) != NULL) {
            range = i;
            break;
        }
    }
    return range;
}

adc_range adcctrl_get_previous_range(adc_input input, adc_range actual_range)
{
    int i;
    adc_range range = actual_range;
    for (i = actual_range - 1; i >= ADC_RANGE_30m; i--) {
        if (adcctrl_get_sequence(input, i) != NULL) {
            range = i;
            break;
        }
    }
    return range;
}