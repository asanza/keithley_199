/* Hardware Interface to ADC
 * Keithley 199 Upgrade
 * (c) 2014 Diego F. Asanza
 * This file implements the ADC Low level control interface
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
 * pulse duration of 20mS (16mS) is only for the integration (runup ramp) impor-
 * tant.
 *
 * The conversion sequence is fixed. It starts with the run up integration period
 * of 20mS, and after exactly 20ms a stop command is sended. Counter values
 * are readed. Finally after 1mS an start rundown command will be send. There is
 * no stop rundown, as the counter automatically stops when no more pulses are
 * present (we need only to wait a timeout time (5mS). Complete conversion
 * sequence takes 26mS.
 *
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
#include "hal.h"

#include "HardwareProfile.h"

/* following are timming constants needed */
#define STROBE_LOW_TIME 63 /**< How much time should strobe pin stay low  25uS @ 2.5MHz */
#define START_WAIT_TIME 120  /**< wait time before first strobe is sended */
#define DOWN_RAMP_TIME  120 /**< wait time before down_ramp_strobe is sended */
/* variable used for the hardware (output compare) pulse generator.
 * it is set to one each time the output compare triggers, and let the oc knows
 * if actually only the start strobe was triggered or also the integration strobe
 * integration strobe is two strobe pulses with separation of exactly INTEGRATION
 * PERIOD ms
 */
static int pulsecounter = 0;
static unsigned int integration_period;
static QueueHandle_t data_sended;

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
#define IS_STOP_INTEGRATION(x) ((x&N_FINAL_SLOPE_BIT))== (N_FINAL_SLOPE_BIT))
#define IS_RUN_DOWN_SLOPE(x) ((x&SYNC_BIT) == SYNC_BIT)
#define IS_PRE_INT_PULSE(x) ((x&(N_FINAL_SLOPE_BIT|SYNC_BIT))==(N_FINAL_SLOPE_BIT|SYNC_BIT))

#define VREF -2.8  /* hardware voltage reference value in volts */

static void send_strobe_and_wait(unsigned int wait_time);
static void adc_send_mux(char channel, uint32_t mux);

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
    vTaskDelay(4);
    /* read counter */
    down_counter = hal_counter_read();
    /* make final count calculations */
    uint32_t adc_counter = up_counter*128 + down_counter;
    return adc_counter;
}



static uint32_t do_sequence(unsigned char channel, hal_adc_sequence* sequence){
    uint32_t start_int = hal_adcseq_next(sequence);
    /* send the start integration sequence */
    while(IS_RUN_DOWN_SLOPE(start_int)||IS_PRE_INT_PULSE(start_int)){
        hal_adc_send_mux(channel, start_int);
        start_int = hal_adcseq_next(sequence);
    }
    if(!IS_START_INTEGRATION(start_int)){
        /* something nasty happened. Abort. */
        assert(0);
    }
    uint32_t stop_int = hal_adcseq_next(sequence);
    if(!IS_STOP_INTEGRATION(stop_int){
        /* something nasty happened. Abort. */
        assert(0);
    }
    uint32_t run_down = hal_adcseq_next(sequence);
    if(!IS_RUN_DOWN_SLOPE(run_down)){
        /* something nasty happened. Abort. */
        assert(0);
    }
    /* here comes the signal integration */
    return hal_adc_integration_sequence(channel, start_int, stop_int, run_down);
}

double hal_adc_do_measurement(unsigned char channel, hal_adc_sequence* sequence){
    assert(sequence!=NULL);
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

void hal_adc_set_integration_period(uint32_t period){
    CloseOC3();
    integration_period = period;
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
/**@brief send the mux configuration to the adc */
static void hal_adc_sendword(char a, char b, char c, char d, char e);


/* Initializes adc and control structures. Output compare 3 is used to generate
 * the 20ms integration period, as timer interrupt have too much jitter. Timer
 * 23 (32bit) counts output compare pulses, 32 bit for better resolution. */
void hal_adc_init(unsigned int period){
    OpenTimer23(T2_OFF|T2_GATE_OFF|T2_IDLE_CON|T2_PS_1_32|T2_SOURCE_INT,
            period);
    OpenOC3(OC_ON|OC_IDLE_CON|OC_TIMER_MODE32|OC_TIMER2_SRC|OC_CONTINUE_PULSE
            |OC_LOW_HIGH,period - STROBE_LOW_TIME, 0);
    ConfigIntOC3(OC_INT_PRIOR_3|OC_INT_ON);
    PORTSetPinsDigitalOut(IOPORT_G, BIT_1);
    PPSOutput(1,RPG1,OC3);
    data_sended = xQueueCreate(1, sizeof(char));
    hal_counter_init();
    SpiChnOpen(SPI_CHANNEL1,SPI_OPEN_MSTEN|SPI_OPEN_CKE_REV|SPI_MODE8_ON
            |SPI_OPEN_DISSDI|SPI_OPEN_ON ,80);
    PPSOutput(3,RPF8,SDO1);
    PORTSetPinsDigitalOut(KMM_CLK);
    PORTSetPinsDigitalOut(KMM_DATA);
    PORTSetPinsDigitalOut(KMM_STRB);
    integration_period = period;
}

void __attribute__(( nomips16, interrupt(), vector(_OUTPUT_COMPARE_3_VECTOR)))
OC3_wrapper();

/* The strobe pin is setted/cleared in hardware, by using the output compare.
 * we use the interrupt in order to transmit the control bytes between strobe
 * activations.*/
OC3_handler(){
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

static void hal_adc_sendword(char a, char b, char c, char d, char e){
    hal_adc_sendbyte(a);
    hal_adc_sendbyte(b);
    hal_adc_sendbyte(c);
    hal_adc_sendbyte(d);
    hal_adc_sendbyte(e);
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