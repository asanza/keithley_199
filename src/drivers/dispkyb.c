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
    xQueueReset(event_queue);
    return key;
}

static void timer_handler(void);

#define NUMBER_OF_CHARACTERS 11
#define NUMBER_OF_SEGMENTS   15


static uint16_t screen[NUMBER_OF_CHARACTERS];
static unsigned int actual_character;
static bool self_test = false;

#define REFRESH_PERIOD 200 // uS

void display_kyb_init(void){
    hal_io_displayport_init();
    hal_io_keyboard_init();
    hal_spi_init_16bit();
    event_queue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(key_id));
    hal_timer_init(REFRESH_PERIOD,timer_handler);
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
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    if(set_value)
        screen[NUMBER_OF_CHARACTERS-2] |= adci;
    else
        screen[NUMBER_OF_CHARACTERS-2] &= ~adci;
}

void hal_disp_adci_toggle(){
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    if(screen[NUMBER_OF_CHARACTERS-2]&adci)
        screen[NUMBER_OF_CHARACTERS-2]&=~adci;
    else
        screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void display_clear(){
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    adci &= screen[NUMBER_OF_CHARACTERS-2];
    memset(screen,0,sizeof(uint16_t)*NUMBER_OF_CHARACTERS);
    screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void display_putc(char c, int pos){
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    adci &= screen[NUMBER_OF_CHARACTERS-2];
    if(self_test) return;
    if(pos < 0 || pos >= (NUMBER_OF_CHARACTERS - 1)) return;
    if(c=='.' && pos > 0)
        screen[pos - 1] |= hal_io_displayport_map_char_to_segments(c);
    else
        screen[pos] = hal_io_displayport_map_char_to_segments(c);
    screen[NUMBER_OF_CHARACTERS-2]|=adci;
}

void display_test(){
    self_test = true;
    while(self_test);
}

#define TEST_MAX_DELAY 5000
static int test_segment = 0, test_delay = TEST_MAX_DELAY;
static key_id hal_disp_scan(){
    bool was_key = false;
    key_id key_pressed = KEY_NONE;
    if(actual_character >= NUMBER_OF_CHARACTERS)
        actual_character = 0;
    if(hal_io_keyboard_get_channel() == 1){
        was_key = true;
        switch(actual_character){
            case 1: key_pressed = KEY_1; break;
            case 2: key_pressed = KEY_3; break;
            case 3: key_pressed = KEY_0; break;
            case 4: key_pressed = KEY_8; break;
        }
    }
    if(hal_io_keyboard_get_channel() == 2){
        was_key = true;
        switch(actual_character){
            case 1: key_pressed = KEY_UP; break;
            case 2: key_pressed = KEY_9; break;
            case 3: key_pressed = KEY_2; break;
            case 4: key_pressed = KEY_DOWN; break;
        }
    }
    if(hal_io_keyboard_get_channel() == 3){
        was_key = true;
        switch(actual_character){
            case 1: key_pressed = KEY_7; break;
            case 2: key_pressed = KEY_6; break;
            case 3: key_pressed = KEY_5; break;
            case 4: key_pressed = KEY_CAL; break;
            case 5: key_pressed = KEY_4; break;
        }
    }
    
    display_set(screen[actual_character], actual_character++);
    if(self_test == false )
        if(was_key)
            return key_pressed;
        else
            return KEY_NONE;
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
                return KEY_NONE;
            }
        }
        test_delay = 0;
    }
    else{
        test_delay++;
    }
    return KEY_NONE;
}

void timer_handler(void){
    BaseType_t xHigherPriorityTaskWoken;
    key_id key = hal_disp_scan();
    if(key!=KEY_NONE ){
        xQueueSendToBackFromISR(event_queue,&key,&xHigherPriorityTaskWoken);
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
