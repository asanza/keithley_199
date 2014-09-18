#include <hal.h>
#include <peripheral/spi.h>
#include <peripheral/pps.h>
#include <peripheral/timer.h>
#include <FreeRTOS.h>
#include <queue.h>
#include "task.h"

#include "HardwareProfile.h"

#define EVENT_QUEUE_LENGTH 1
QueueHandle_t event_queue; // queue for keyboard events

hal_key hal_disp_wait_for_key(){
    hal_key key;
    xQueueReceive(event_queue,&key,portMAX_DELAY);
    vTaskDelay(120); // debounce delay
    xQueueReset(event_queue);
    return key;
}

#define NUMBER_OF_CHARACTERS 11
#define NUMBER_OF_SEGMENTS   15

static uint16_t segments[] = {
    seg_a,
    seg_b,
    seg_c,
    seg_d,
    seg_e,
    seg_f,
    seg_g,
    seg_h,
    seg_j,
    seg_k,
    seg_l,
    seg_m,
    seg_n,
    seg_i,
    seg_dp
};

static uint16_t decode(char c);

static uint16_t screen[NUMBER_OF_CHARACTERS];
static unsigned int actual_character;
static bool self_test = false;

#define REFRESH_PERIOD 5000 // * 25nS * NUMBER_OF_CHARACTERS

void hal_disp_init(){
    PORTSetPinsDigitalOut(DISPLAY_PORT,0xFFFF);
    SpiChnOpen(SPI_CHANNEL2, SPI_OPEN_MSTEN|SPI_OPEN_MODE16|SPI_OPEN_CKP_HIGH|SPI_OPEN_CKE_REV, 100);
    PPSOutput(1,RPC1,SDO2);
    /* initializes keyboard (keyboard is scanned with display digits */
    PORTSetPinsDigitalIn(HAL_KYB_S0);
    PORTSetPinsDigitalIn(HAL_KYB_S1);
    PORTSetPinsDigitalIn(HAL_KYB_S2);
    event_queue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(hal_key));
    mConfigIntCoreTimer(CT_INT_ON|CT_INT_PRIOR_2|CT_INT_SUB_PRIOR_0);
    OpenCoreTimer(REFRESH_PERIOD);
}

static void hal_disp_set(unsigned int segments, int position){
    PORTClearBits(DISPLAY_PORT, 0xFFFF);
    SpiChnWriteC(SPI_CHANNEL2,~(0x01<<position));
    PORTSetBits(DISPLAY_PORT, segments);
}

void hal_disp_setmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]=mode;
}

void hal_disp_addmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]|=mode;
}

void hal_disp_clearmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]&=~mode;
}

void hal_disp_puts(char* c){
    int i = 0, position = 0;
    while(c[i]!=0){
        if(c[i] == '.')
            hal_disp_putc(c[i], position);
        else
            hal_disp_putc(c[i], position++);
        i++;
        if(position > (NUMBER_OF_CHARACTERS - 2)) break;
    }
}


void hal_disp_adci(bool value){
    uint16_t adci = decode('.');
    if(value)
        screen[NUMBER_OF_CHARACTERS-2] |= adci;
    else
        screen[NUMBER_OF_CHARACTERS-2] &= ~adci;
}

void hal_disp_adci_toggle(){
    uint16_t adci = decode('.');
    if(screen[NUMBER_OF_CHARACTERS-2]&adci)
        screen[NUMBER_OF_CHARACTERS-2]&=~adci;
    else
        screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void hal_disp_clear(){
    uint16_t adci = decode('.');
    adci &= screen[NUMBER_OF_CHARACTERS-2];
    memset(screen,0,sizeof(uint16_t)*NUMBER_OF_CHARACTERS);
    screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void hal_disp_putc(char c, int pos){
    uint16_t adci = decode('.');
    adci &= screen[NUMBER_OF_CHARACTERS-2];
    if(self_test) return;
    if(pos < 0 || pos >= (NUMBER_OF_CHARACTERS - 1)) return;
    if(c=='.' && pos > 0)
        screen[pos - 1] |= decode(c);
    else
        screen[pos] = decode(c);
    screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void hal_disp_test(){
    self_test = true;
    while(self_test);
}

#define TEST_MAX_DELAY 5000
static int test_segment = 0, test_delay = TEST_MAX_DELAY;
hal_key hal_disp_scan(){
    hal_key key_pressed = KEY_NONE;
    if(actual_character >= NUMBER_OF_CHARACTERS)
        actual_character = 0;
    if(!PORTReadBits(HAL_KYB_S0)){
        switch(actual_character){
            case 1: key_pressed = KEY_OHMS; break;
            case 2: key_pressed = KEY_AC; break;
            case 3: key_pressed = KEY_VOLTS; break;
            case 4: key_pressed = KEY_SCANNER; break;
        }
    }
    if(!PORTReadBits(HAL_KYB_S1)){
        switch(actual_character){
            case 1: key_pressed = KEY_LOCAL; break;
            case 2: key_pressed = KEY_TRIGGER; break;
            case 3: key_pressed = KEY_AMPS; break;
            case 4: key_pressed = KEY_NEXT; break;
        }
    }
    if(!PORTReadBits(HAL_KYB_S2)){
        switch(actual_character){
            case 1: key_pressed = KEY_RANGE_UP; break;
            case 2: key_pressed = KEY_RANGE_DOWN; break;
            case 3: key_pressed = KEY_AUTO; break;
            case 4: key_pressed = KEY_CAL; break;
            case 5: key_pressed = KEY_ZERO; break;
        }
    }

    hal_disp_set(screen[actual_character], actual_character++);
    if(self_test == false)
        return key_pressed;;
    int i = 0;
    screen[NUMBER_OF_CHARACTERS - 1] = 0xFFFF;
    if(test_delay >= TEST_MAX_DELAY){
        if(test_segment < NUMBER_OF_SEGMENTS){
            for(i = 0; i < NUMBER_OF_CHARACTERS - 1; i++)
                screen[i] = segments[test_segment];
            test_segment++;
        }else{
            for(i = 0; i < NUMBER_OF_CHARACTERS; i++)
                screen[i] = 0;
            screen[test_segment++ - NUMBER_OF_SEGMENTS] = 0xFFFF;
            if(test_segment - NUMBER_OF_SEGMENTS > NUMBER_OF_CHARACTERS){
                self_test = false;
                test_segment = 0;
                test_delay = TEST_MAX_DELAY;
                return;
            }
        }
        test_delay = 0;
    }
    else{
        test_delay++;
    }
    return KEY_NONE;
}
/* bits from 2^15 to 2^0. 2^0 is not connected and should be always 0.
 * n dp d l h i j k m g a f c e b x
 * aaaaaaaaaaa
 * f i  g   hb
 * f  i g  h b
 * f   ig h  b
 * f    ih   b
 * ennnnnjjjjj
 * e   ml k  c
 * e  m l  k c
 * e m  l   kc
 * ddddddddddd
 */
static uint16_t chartable[] = {
    0x823E, 0x326A, 0x2034, 0x306A, 0xA034, 0x8034, 0x223C,
    0x821E, 0x3060, 0x200E, 0x8914, 0x2014, 0x0C1E, 0x051E,
    0x203E, 0x8236, 0x213E, 0x8336, 0xA238, 0x1060, 0x201E,
    0x0894, 0x019E, 0x0D80, 0xA21A, 0x28A0, 0x203E, 0x1040,
    0xA226, 0x222A, 0x821A, 0xA238, 0xA23C, 0x002A, 0xA23E,
    0xA23A, 0x9240, 0x8200, 0x8E20, 0x920C, 0x8232, 0x0000,
    0x4000, 0xA20E, 0x1222
};

static uint16_t decode(char c){
    switch(c){
        case 'm': return chartable[39];
        case '+': return chartable[36];
        case '-': return chartable[37];
        case 'o': return chartable[38];
        case 'g': return chartable[40];
        case ' ': return chartable[41];
        case '.': return chartable[42];
        case 'd': return chartable[43];
        case '?': return chartable[44];
    }
    if(c <= 0x39){
        return chartable[c - 22];
    }
    return chartable[c - 0x41];
}

void __attribute__(( nomips16, interrupt(), vector(_CORE_TIMER_VECTOR)))
CT_wrapper();

CT_handler(){
    mCTClearIntFlag();
    BaseType_t xHigherPriorityTaskWoken;
    hal_key key = hal_disp_scan();
    UpdateCoreTimer(REFRESH_PERIOD);
    if(key!=KEY_NONE){
        xQueueSendToBackFromISR(event_queue,&key,&xHigherPriorityTaskWoken);
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
