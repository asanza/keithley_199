#include <hal.h>
#include <hal_timer.h>
#include <FreeRTOS.h>
#include <queue.h>
#include "task.h"
#include "hal_io.h"
#include "dispkyb.h"

#define EVENT_QUEUE_LENGTH 1
QueueHandle_t event_queue; // queue for keyboard events

key_id display_wait_for_key(){
    key_id key;
    xQueueReceive(event_queue,&key,portMAX_DELAY);
    vTaskDelay(120); // debounce delay
    xQueueReset(event_queue);
    return key;
}

void timer_handler(void);

#define NUMBER_OF_CHARACTERS 11
#define NUMBER_OF_SEGMENTS   15

static uint16_t decode(char c);

static uint16_t screen[NUMBER_OF_CHARACTERS];
static unsigned int actual_character;
static bool self_test = false;

#define REFRESH_PERIOD 200 // uS

void display_kyb_init(void){
    hal_io_displayport_init();
    hal_io_keyboard_init();
    hal_spi_init_16bit();
    event_queue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(key_id));
    hal_timer_init(200,timer_handler);
}

static void display_set(unsigned int segments, int position){
    hal_spi_write_16bit(~(0x01<<position));
    hal_io_displayport_write(segments);
}

void display_setmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]=mode;
}

void display_addmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]|=mode;
}

void display_clearmode(disp_mode mode){
    screen[NUMBER_OF_CHARACTERS-1]&=~mode;
}

void display_puts(char* c){
    int i = 0, position = 0;
    while(c[i]!=0){
        if(c[i] == '.')
            display_putc(c[i], position);
        else
            display_putc(c[i], position++);
        i++;
        if(position > (NUMBER_OF_CHARACTERS - 2)) break;
    }
}


void display_adc_indicator(bool set_value){
    uint16_t adci = decode('.');
    if(set_value)
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

void display_clear(){
    uint16_t adci = decode('.');
    adci &= screen[NUMBER_OF_CHARACTERS-2];
    memset(screen,0,sizeof(uint16_t)*NUMBER_OF_CHARACTERS);
    screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void display_putc(char c, int pos){
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

void display_test(){
    self_test = true;
    while(self_test);
}

#define TEST_MAX_DELAY 5000
static int test_segment = 0, test_delay = TEST_MAX_DELAY;
static key_id hal_disp_scan(){
    key_id key_pressed = KEY_NONE;
    if(actual_character >= NUMBER_OF_CHARACTERS)
        actual_character = 0;
    if(hal_io_keyboard_get_channel() == 1){
        switch(actual_character){
            case 1: key_pressed = KEY_OHMS; break;
            case 2: key_pressed = KEY_AC; break;
            case 3: key_pressed = KEY_VOLTS; break;
            case 4: key_pressed = KEY_SCANNER; break;
        }
    }
    if(hal_io_keyboard_get_channel() == 2){
        switch(actual_character){
            case 1: key_pressed = KEY_LOCAL; break;
            case 2: key_pressed = KEY_TRIGGER; break;
            case 3: key_pressed = KEY_AMPS; break;
            case 4: key_pressed = KEY_NEXT; break;
        }
    }
    if(hal_io_keyboard_get_channel() == 3){
        switch(actual_character){
            case 1: key_pressed = KEY_RANGE_UP; break;
            case 2: key_pressed = KEY_RANGE_DOWN; break;
            case 3: key_pressed = KEY_AUTO; break;
            case 4: key_pressed = KEY_CAL; break;
            case 5: key_pressed = KEY_ZERO; break;
        }
    }

    display_set(screen[actual_character], actual_character++);
    if(self_test == false)
        return key_pressed;;
    int i = 0;
    screen[NUMBER_OF_CHARACTERS - 1] = 0xFFFF;
    if(test_delay >= TEST_MAX_DELAY){
        if(test_segment < NUMBER_OF_SEGMENTS){
            for(i = 0; i < NUMBER_OF_CHARACTERS - 1; i++)
                screen[i] = hal_io_get_segment(test_segment);
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
    /* TODO: Check c inside allowed range */
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

void timer_handler(void){
    BaseType_t xHigherPriorityTaskWoken;
    key_id key = hal_disp_scan();
    if(key!=KEY_NONE){
        xQueueSendToBackFromISR(event_queue,&key,&xHigherPriorityTaskWoken);
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}