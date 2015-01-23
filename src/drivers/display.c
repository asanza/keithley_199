#include <hal.h>
#include <FreeRTOS.h>
#include <queue.h>
#include "task.h"
#include "hal_timer.h"

#define EVENT_QUEUE_LENGTH 1
QueueHandle_t event_queue; // queue for keyboard events

#define TEST_MAX_DELAY 5000 /* delay for the testsequence */

static void do_test_sequence(void);

hal_key hal_disp_wait_for_key(){
    hal_key key;
    xQueueReceive(event_queue,&key,portMAX_DELAY);
    vTaskDelay(120); // debounce delay
    xQueueReset(event_queue);
    return key;
}

#define NUMBER_OF_CHARACTERS 11
#define NUMBER_OF_SEGMENTS   15

static uint16_t decode(char c);

static uint16_t screen[NUMBER_OF_CHARACTERS];
static unsigned int actual_character;
static bool self_test = false;

#define REFRESH_PERIOD 200

void timer_interrupt_handler(void);

void hal_disp_init(){
    hal_io_keyboard_init();
    event_queue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(hal_key));
    hal_spi_init();
    hal_timer_init(REFRESH_PERIOD, timer_interrupt_handler);
}

/* set some segments on the display */
static void hal_disp_set(unsigned int segments, int position){
    hal_displayport_write(0xFFFF);
    hal_spi_write(~(0x01<<position));
    hal_displayport_write(segments);
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

static int test_segment = 0, test_delay = TEST_MAX_DELAY;
hal_key hal_disp_scan(){
    hal_key key_pressed = KEY_NONE;
    if(self_test){
        do_test_sequence();
        return KEY_NONE;
    }
    if(actual_character >= NUMBER_OF_CHARACTERS)
        actual_character = 0;
    if(hal_io_keyboard_read() == 1){
        switch(actual_character){
            case 1: key_pressed = KEY_OHMS; break;
            case 2: key_pressed = KEY_AC; break;
            case 3: key_pressed = KEY_VOLTS; break;
            case 4: key_pressed = KEY_SCANNER; break;
        }
    }
    if(hal_io_keyboard_read() == 2){
        switch(actual_character){
            case 1: key_pressed = KEY_LOCAL; break;
            case 2: key_pressed = KEY_TRIGGER; break;
            case 3: key_pressed = KEY_AMPS; break;
            case 4: key_pressed = KEY_NEXT; break;
        }
    }
    if(hal_io_keyboard_read() == 3){
        switch(actual_character){
            case 1: key_pressed = KEY_RANGE_UP; break;
            case 2: key_pressed = KEY_RANGE_DOWN; break;
            case 3: key_pressed = KEY_AUTO; break;
            case 4: key_pressed = KEY_CAL; break;
            case 5: key_pressed = KEY_ZERO; break;
        }
    }

    hal_disp_set(screen[actual_character], actual_character++);
    return key_pressed;
}

/* lit each individual display segment in progression to test if display is
 * working properly */
void do_test_sequence(void){
    int i = 0;
    screen[NUMBER_OF_CHARACTERS - 1] = 0xFFFF;
    if(test_delay >= TEST_MAX_DELAY){
        if(test_segment < NUMBER_OF_SEGMENTS){
            for(i = 0; i < NUMBER_OF_CHARACTERS - 1; i++)
                screen[i] = hal_io_display_segment(test_segment);
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

void timer_interrupt_handler(void){
    BaseType_t xHigherPriorityTaskWoken;
    hal_key key = hal_disp_scan();
    if(key!=KEY_NONE){
        xQueueSendToBackFromISR(event_queue,&key,&xHigherPriorityTaskWoken);
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

