#include <stdio.h>

#include "adc.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include <dispkyb.h>
#include "HardwareProfile.h"
#include "usb_uart.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <assert.h>
#include <sys.h>
#include <math.h>

static void sysMgmTask(void *pvParameters);
extern void dmmTaskMain(void* pvParameters);
TaskHandle_t measTaskHandle;

int main()
{
    /* hardware initialization. An error here is unrecoverable */
    hal_sys_init();
    hal_i2c_init();
    usb_uart_init();
    display_kyb_init();
    xTaskCreate(dmmTaskMain,"T1",configMINIMAL_STACK_SIZE,NULL,3,&measTaskHandle);
    /* suspend measurement task until we load dmm state on management task. */
    if(measTaskHandle)
        vTaskSuspend(measTaskHandle);
    /* system management task. */
    xTaskCreate(sysMgmTask,"T2",configMINIMAL_STACK_SIZE,NULL,3,NULL);
    //xTaskCreate(doCalTask,"T3",configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    vTaskStartScheduler();
}

static void sysMgmTask(void *pvParameters){
    bool shift_key = false;
    vTaskResume(measTaskHandle);

    while(1){
        switch(display_wait_for_key())
        {
            case KEY_7: sys_state_up_scale(); continue;
            case KEY_6: sys_state_down_scale(); continue;
            case KEY_3: sys_state_toggle_acdc(); continue;
            case KEY_1: sys_state_set_mode(ADC_INPUT_RESISTANCE_2W); continue;
            case KEY_0: sys_state_set_mode(ADC_INPUT_VOLTAGE_DC); continue;
            case KEY_2: sys_state_set_mode(ADC_INPUT_CURRENT_DC); continue;
            case KEY_4: continue;
            case KEY_UP:continue;
            case KEY_5: continue;
            case KEY_8: continue;
            case KEY_9: continue;
            case KEY_DOWN: shift_key = true; continue;
            case KEY_CAL:
                vTaskSuspend(measTaskHandle);
                //vTaskStart(doCalTaskHandle);
                continue;
            default:
                Nop();
        }
        vTaskDelay(10);
    }
}

void vAssertCalled( const char* fileName, unsigned long lineNo )
{
    printf("FreeRTOS: %s, %d\n", fileName, lineNo);
    while(1);  
} 

void vApplicationIdleHook( void ){
    hal_sys_idle();
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, signed char *pcTaskName )
{
    assert(0);
    while(1);
}

void vApplicationMallocFailedHook()
{
    assert(0);
    while(1);
}