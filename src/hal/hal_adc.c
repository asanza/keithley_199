/* Hardware Interface to ADC
 * Keithley 199 Upgrade
 *
 * This file implements the ADC Low level control interface
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */

/* Integrating adc control
 * This file is responsible for generating the control timing for
 * the ADC.
 *
 * The tolerable jitter is around 500nS (minimal) we strive to reach
 * a jitter of about 50 nS. (actual value is about 20ps.)
 *
 * Output compare generates the strobe pulses. With this method we
 * can guarantee precise, hardware controlled, pulse generation. Precise
 * pulse duration of 20mS (16mS) is only for the integration (runup ramp)
 * important.
 *
 * The conversion sequence is fixed. It starts with the run up integration period
 * of 20mS, and after exactly 20ms (16ms) a stop command is sent, and the 
 * integration counter is read. 1 ms after, an start rundown command is sent, and
 * we wait for about 5-6ms that the rundown counter stops. 
 * No stop rundown is needed, as the counter automatically stops when no more 
 * pulses are comming from the hardware integration stage. 
 * Complete conversion sequence takes 26mS.
 * 
 * The default integration period is 20ms for 50Hz and 16ms for 60Hz. Other 
 * values are possible, playing with the pulse generation.
 *
 */

#include <peripheral/outcompare.h>
#include <peripheral/timer.h>
#include <peripheral/pps.h>
#include <peripheral/ports.h>
#include <peripheral/spi.h>
#include <stdint.h>
#include <assert.h>
#ifdef TEST
#include <os_test.h>
#else
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
#endif


#include "HardwareProfile.h"

#define OSC_COMPARE_FREQ 2500000ULL //Long long required
/* following are timming constants needed */
#define STROBE_LOW_TIME 63 /**< How much time should strobe pin stay low  25uS @ 2.5MHz */
#define START_WAIT_TIME 120  /**< wait time before first strobe is sended */
#define DOWN_RAMP_TIME  120 /**< wait time before down_ramp_strobe is sended */
/* variable used for the hardware (output compare) pulse generator.
 * it is set to one each time the output compare triggers, and let the oc knows
 * if actually only the start strobe was triggered or also the integration strobe
 * integration strobe is two strobe pulses with separation of exactly INTEGRATION
 * PERIOD ms */
static int pulsecounter = 0;
#ifdef TEST
unsigned int integration_period;
#else
static unsigned int integration_period;
#endif
static QueueHandle_t data_sended = NULL;


static void send_strobe_and_wait(unsigned int wait_time);
static void adc_send_mux(char channel, uint32_t mux);

static void hal_counter_init();
static void hal_counter_restart();
static uint32_t hal_counter_read();


/* It would be nice to remove the os dependencies from this file.
 */

void hal_adc_send_mux(uint8_t channel, uint32_t mux){
    /* send this mux configuration */
    adc_send_mux(channel, mux);
    send_strobe_and_wait(START_WAIT_TIME);
    /* wait a little bit before sending the next sequence */
    vTaskDelay(1);
}


int hal_adc_integration_sequence (uint8_t channel, uint32_t int_mux, uint32_t pause_mux, uint32_t rund_mux){
    uint32_t up_counter, down_counter;
    /* reset counter integration counter  */
    hal_counter_restart();
    /* send the start integration sequence */
    adc_send_mux(channel,int_mux);
    send_strobe_and_wait(START_WAIT_TIME);
    /* wait a little bit before sending the next sequence */
    vTaskDelay(1);
    /* send the end integration sequence */
    adc_send_mux(channel, pause_mux);
    /* strobe is send automatically from the oc module. just wait for it! */
    char t;
    xQueueReceive(data_sended, &t, portMAX_DELAY);
    /* wait a little bit to receive all count pulses */
    vTaskDelay(1);
    /* read up pulses */
    up_counter = hal_counter_read();
    /* reset counter */
    hal_counter_restart();
    /* send the start rundown count sequence */
    adc_send_mux(channel, rund_mux);
    send_strobe_and_wait(START_WAIT_TIME);
    /* wait until all adc pulses are received */
    vTaskDelay(2);
    /* stop strobe from retrigger */
    T2CONbits.ON = 0; 
    /* read counter */
    down_counter = hal_counter_read();
    /* make final count calculations */
    uint32_t adc_counter = up_counter*128 + down_counter;
    return adc_counter;
}


void hal_adc_set_integration_period(uint32_t period){
    integration_period = period*OSC_COMPARE_FREQ/1000000ULL;
    CloseOC3();
    OpenOC3(OC_ON|OC_IDLE_CON|OC_TIMER_MODE32|OC_TIMER2_SRC|OC_CONTINUE_PULSE
            |OC_LOW_HIGH,period - STROBE_LOW_TIME, 0);
    ConfigIntOC3(OC_INT_PRIOR_3|OC_INT_ON);
}

static void send_strobe_and_wait(unsigned int wait_time){
    char t;
    /* start conunter and send down pulse after start_wait_time */
    WriteTimer23(integration_period - wait_time);
    pulsecounter = 0;
    T2CONbits.ON = 1;
    /* wait until strobe is high again */
    xQueueReceive(data_sended,&t,portMAX_DELAY);
}

/**@brief send a byte to the adc mux*/
static void hal_adc_sendbyte(char c);


/* Initializes adc and control structures. Output compare 3 is used to generate
 * the 20ms integration period, as timer interrupt have too much jitter. Timer
 * 23 (32bit) counts output compare pulses, 32 bit for better resolution. */
void hal_adc_init(unsigned int period){
    integration_period = period*OSC_COMPARE_FREQ/1000000ULL;
    OpenTimer23(T2_OFF|T2_GATE_OFF|T2_IDLE_CON|T2_PS_1_32|T2_SOURCE_INT,
            integration_period);
    OpenOC3(OC_ON|OC_IDLE_CON|OC_TIMER_MODE32|OC_TIMER2_SRC|OC_CONTINUE_PULSE
            |OC_LOW_HIGH,integration_period - STROBE_LOW_TIME, 0);
    ConfigIntOC3(OC_INT_PRIOR_3|OC_INT_ON);
    PORTSetPinsDigitalOut(IOPORT_G, BIT_1);
    PPSOutput(1,RPG1,OC3);
    if(!data_sended){
        data_sended = xQueueCreate(1, sizeof(char));
    }
    hal_counter_init();
    SpiChnOpen(SPI_CHANNEL1,SPI_OPEN_MSTEN|SPI_OPEN_CKE_REV|SPI_OPEN_MODE8 
            |SPI_OPEN_DISSDI|SPI_OPEN_ON ,80);
    PPSOutput(3,RPF8,SDO1);
    PORTSetPinsDigitalOut(KMM_CLK);
    PORTSetPinsDigitalOut(KMM_DATA);
    PORTSetPinsDigitalOut(KMM_STRB);
}

#ifdef TEST
void
#else
void __attribute__(( nomips16, interrupt(), vector(_OUTPUT_COMPARE_3_VECTOR)))
#endif
OC3_wrapper();

/* The strobe pin is setted/cleared in hardware, by using the output compare.
 * we use the interrupt in order to transmit the control bytes between strobe
 * activations.*/
void OC3_handler(){
    portBASE_TYPE xHigerPriorityTaskWoken;
    xQueueSendFromISR(data_sended,&pulsecounter, &xHigerPriorityTaskWoken);
    pulsecounter++;
    if(pulsecounter>1){
        /* whait a little while before setting the strobe to one again. It is ne
         * cessary because the strobe optocoupler is slow. */
        for(pulsecounter = 0; pulsecounter < 250; pulsecounter++);
        WriteTimer23(0x00); // Set strobe high again.
        T2CONbits.ON = 0; // Disable timer to prevent retriggering.
    }
    INTClearFlag(INT_OC3);
    // Switch to a waiting task.
    portEND_SWITCHING_ISR(xHigerPriorityTaskWoken);
}

static void hal_adc_sendbyte(char c){
    SpiChnPutC(1,c);
}

static void adc_send_mux(char channel, uint32_t mux){
    hal_adc_sendbyte(channel);
    char val = (mux >> 24);
    hal_adc_sendbyte(val);
    val = (mux >> 16);
    hal_adc_sendbyte(val);
    val = (mux >> 8);
    hal_adc_sendbyte(val);
    val = (mux);
    hal_adc_sendbyte(val);
}

static void hal_counter_init(){
    HW_32BIT_COUNTER_SET_INPUT();
    HW_32BIT_COUNTER_START(0xFFFFFFFF);
}


static void hal_counter_restart(){
    HW_32BIT_COUNTER_RESTART();
}

static uint32_t hal_counter_read(){
    return HW_32BIT_COUNTER_READ();
}