#include <hal.h>
#include <hal_timer.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <assert.h>
#include "task.h"
#include "hal_io.h"
#include "dispkyb.h"

#define EVENT_QUEUE_LENGTH 1
QueueHandle_t event_queue; // queue for keyboard events

#define KYB_REPETITION_PERIOD_MS 60

key_id display_wait_for_key()
{
    key_id key;
    xQueueReceive(event_queue, &key, portMAX_DELAY);
    return key;
}

static void timer_handler(void);

#define NUMBER_OF_SEGMENTS   15


static uint16_t screen[NUMBER_OF_CHARACTERS];
static unsigned int actual_character;
static bool self_test = false;

static int highlighted_digit = 0;

#define REFRESH_PERIOD 1000 // uS per each digit
#define KEY_HOLDOF_PERIOD 500 // mS
#define KEY_REPEAT_PERIOD 100 //ms

void display_kyb_init(void)
{
    hal_io_init();
    hal_spi_init_16bit();
    event_queue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(key_id));
    hal_timer_init(REFRESH_PERIOD, timer_handler);
}

void display_evt_clear(void){
    char item;
    while(xQueueReceive(event_queue, &item, 0)!=pdTRUE);
    BaseType_t val = xQueueReset(event_queue);
    assert(val == pdPASS);
}

void display_highlight(int digit)
{
    highlighted_digit = digit;
}

static void display_set(unsigned int segments, int position)
{
    hal_spi_write_16bit(~(0x01 << position));
    hal_io_displayport_write(segments);
}

void display_setmode(disp_mode mode)
{
    screen[NUMBER_OF_CHARACTERS - 1] = mode;
}

void display_addmode(disp_mode mode)
{
    screen[NUMBER_OF_CHARACTERS - 1] |= mode;
}

void display_clearmode(disp_mode mode)
{
    screen[NUMBER_OF_CHARACTERS - 1] &= ~mode;
}

void display_puts(char* c)
{
    int i = 0, position = 0;
    while (c[i] != 0) {
        if (c[i] == '.')
            display_putc(c[i], position);
        else
            display_putc(c[i], position++);
        i++;
        if (position > (NUMBER_OF_CHARACTERS - 2)) break;
    }
}

void display_adc_indicator(bool set_value)
{
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    if (set_value)
        screen[NUMBER_OF_CHARACTERS - 2] |= adci;
    else
        screen[NUMBER_OF_CHARACTERS - 2] &= ~adci;
}

void hal_disp_adci_toggle()
{
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    if (screen[NUMBER_OF_CHARACTERS - 2] & adci)
        screen[NUMBER_OF_CHARACTERS - 2] &= ~adci;
    else
        screen[NUMBER_OF_CHARACTERS - 2] |= adci;
}

void display_clear()
{
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    adci &= screen[NUMBER_OF_CHARACTERS - 2];
    memset(screen, 0, sizeof(uint16_t) * NUMBER_OF_CHARACTERS);
    screen[NUMBER_OF_CHARACTERS - 2] |= adci;
}

void display_putc(char c, int pos)
{
    uint16_t adci = hal_io_displayport_map_char_to_segments('.');
    adci &= screen[NUMBER_OF_CHARACTERS - 2];
    if (self_test) return;
    if (pos < 0 || pos >= (NUMBER_OF_CHARACTERS - 1)) return;
    if (c == '.' && pos > 0)
        screen[pos - 1] |= hal_io_displayport_map_char_to_segments(c);
    else
        screen[pos] = hal_io_displayport_map_char_to_segments(c);
    screen[NUMBER_OF_CHARACTERS - 2] |= adci;
}

void display_test()
{
    self_test = true;
    while (self_test);
}

#define TEST_MAX_DELAY 5000
#define HIGHLIGHT_TIME 1 
static int test_segment = 0, test_delay = TEST_MAX_DELAY;
static key_id key_pressed = KEY_NONE;
static key_id last_key_pressed = KEY_NONE;
static hl_time = 0; // time to highlight a digit
static key_id hal_disp_scan()
{
    if (actual_character >= NUMBER_OF_CHARACTERS) {
        actual_character = 0;
        if (key_pressed == KEY_NONE)
            last_key_pressed = KEY_NONE;
        key_pressed = KEY_NONE;
    }
    
    if (hal_io_keyboard_get_channel() == 1) {
        switch (actual_character) {
            case 1: key_pressed = KEY_1;
                break;
            case 2: key_pressed = KEY_3;
                break;
            case 3: key_pressed = KEY_0;
                break;
            case 4: key_pressed = KEY_8;
                break;
        }
    }
    if (hal_io_keyboard_get_channel() == 2) {
        switch (actual_character) {
            case 1: key_pressed = KEY_UP;
                break;
            case 2: key_pressed = KEY_9;
                break;
            case 3: key_pressed = KEY_2;
                break;
            case 4: key_pressed = KEY_DOWN;
                break;
        }
    }
    if (hal_io_keyboard_get_channel() == 3) {
        switch (actual_character) {
            case 1: key_pressed = KEY_7;
                break;
            case 2: key_pressed = KEY_6;
                break;
            case 3: key_pressed = KEY_5;
                break;
            case 4: key_pressed = KEY_CAL;
                break;
            case 5: key_pressed = KEY_4;
                break;
        }
    }

    if (key_pressed != KEY_NONE)
        last_key_pressed = key_pressed;

    if (highlighted_digit == actual_character) {
        if (hl_time > 1) {
            hl_time = 0;
        } else {
            actual_character--;
            hl_time++;
        }
    }

    display_set(screen[actual_character], actual_character++);
    
    if (self_test == false)
        return last_key_pressed;

    int i = 0;
    screen[NUMBER_OF_CHARACTERS - 1] = 0xFFFF;
    if (test_delay >= TEST_MAX_DELAY) {
        if (test_segment < NUMBER_OF_SEGMENTS) {
            for (i = 0; i < NUMBER_OF_CHARACTERS - 1; i++)
                screen[i] = hal_io_get_segment(test_segment);
            test_segment++;
        } else {
            for (i = 0; i < NUMBER_OF_CHARACTERS; i++)
                screen[i] = 0;
            screen[test_segment++ - NUMBER_OF_SEGMENTS] = 0xFFFF;
            if (test_segment - NUMBER_OF_SEGMENTS > NUMBER_OF_CHARACTERS) {
                self_test = false;
                test_segment = 0;
                test_delay = TEST_MAX_DELAY;
                return KEY_NONE;
            }
        }
        test_delay = 0;
    } else {
        test_delay++;
    }
    return KEY_NONE;
}

static key_id last_key_interrupt = KEY_NONE;
static int holdoff_counter = 0;
static int rept_counter = 0;

void timer_handler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    key_id key = hal_disp_scan();
    if (key != last_key_interrupt) {
        xQueueSendToBackFromISR(event_queue, &key, &xHigherPriorityTaskWoken);
        last_key_interrupt = key;
        holdoff_counter = 0;
        rept_counter = 0;
    } else {
        if (key != KEY_NONE) {
            /* check if key is constantly pressed.*/
            holdoff_counter++;
            if (holdoff_counter > KEY_HOLDOF_PERIOD * 1000 / REFRESH_PERIOD) {
                holdoff_counter--; // prevent overflow
                /* if key pressed more than KEY_HOLDOFF_PERIOD, repeat key */
                if (rept_counter++ > KEY_REPEAT_PERIOD * 1000 / REFRESH_PERIOD) {
                    xQueueSendToBackFromISR(event_queue, &key, &xHigherPriorityTaskWoken);
                    rept_counter = 0;
                }
            }
        }
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
