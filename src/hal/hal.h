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

#endif /*__LANGUAGE_ASSEMBLY*/
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_H */

