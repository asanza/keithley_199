/* 
 * File:   hal.h
 * Author: diego
 *
 * Created on March 9, 2014, 11:05 PM
 */

#ifndef HAL_H
#define	HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>
#include <stdbool.h>

#define SYS_CLK     80000000UL
#define PB_CLK      80000000UL

typedef enum{
    SYSERR_LED,
            SYSOK_LED,
            AUX_LED
}IO_LED;

typedef enum{
            EVT_UART_RX = 0x01, /**< Data Received */
}hal_event;

void hal_sys_init();
void hal_io_toggle_led(IO_LED led);
void hal_io_set_led(IO_LED led);
void hal_io_clear_led(IO_LED led);

void hal_io_set_debugpin();
void hal_io_clear_debugpin();
void hal_io_toggle_debugpin();

void hal_usbuart_init();
int hal_usbuart_receive(char* buffer, int size);
void hal_usbuart_readline(char* buffer, int size);

void hal_sys_idle();

void hal_timer_init();
void hal_wait();



bool hal_i2c_write_byte_array(uint8_t device_address, uint8_t* data, uint8_t size);
bool hal_i2c_read_byte_array(uint8_t device_address, uint8_t* data, uint8_t size);

/* DISPLAY INTERFACE */
typedef enum{
    KEY_VOLTS,
            KEY_OHMS,
            KEY_AMPS,
            KEY_AC,
            KEY_ZERO,
            KEY_LOCAL,
            KEY_AUTO,
            KEY_RANGE_UP,
            KEY_RANGE_DOWN,
            KEY_SCANNER,
            KEY_TRIGGER,
            KEY_NEXT,
            KEY_CAL,
            KEY_NONE
}hal_key;


typedef enum DISP_MODE{
    DISP_STO    = 0x0010,
    DISP_RCL    = 0x0004,
    DISP_FLTR   = 0x0400,
    DISP_REM    = 0x8000,
    DISP_VOLTS  = 0x0008,
    DISP_OHMS   = 0x0800,
    DISP_AMPS   = 0x0080,
    DISP_AC     = 0x4000,
    DISP_ZERO   = 0x0100,
    DISP_AUTO   = 0x0200
}disp_mode;


hal_key hal_disp_scan();
void hal_disp_init();
void hal_disp_test();
void hal_disp_clear();
void hal_disp_adci(bool value);
void hal_disp_adci_toggle();
void hal_disp_setmode(disp_mode mode);
void hal_disp_addmode(disp_mode mode);
void hal_disp_clearmode(disp_mode mode);
void hal_disp_puts(char* c);
void hal_disp_putc(char c, int pos);
hal_key hal_disp_wait_for_key();

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
    ADC_RANGE_30m,
        ADC_RANGE_300m,
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


int hal_adc_integration_sequence(unsigned char channel, uint32_t int_mux, uint32_t pause_mux, uint32_t rund_mux);
void hal_adc_init(unsigned int period);
void hal_adc_send_mux(uint8_t channel, uint32_t mux);
void hal_adc_set_integration_period(uint32_t period);

typedef struct hal_adc_integration_sequence_t hal_adc_sequence;

hal_adc_sequence* hal_adc_get_sequence(adc_input input, adc_range range);
double hal_adc_do_measurement(unsigned char channel, hal_adc_sequence* sequence);
uint32_t hal_adcseq_next(hal_adc_sequence* sequence);

#endif /*__LANGUAGE_ASSEMBLY*/
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_H */

