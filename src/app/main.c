#include <stdio.h>

#include "adc.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include <dispkyb.h>
#include "HardwareProfile.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <assert.h>
#include <sys.h>
#include <math.h>

static void sysMgmTask(void *pvParameters);
extern void dmmTaskMain(void* pvParameters);
TaskHandle_t measTaskHandle;
void _mon_putc(char c){
    hal_uart_send_byte(3,c);
}
int main()
{
    /* hardware initialization. An error here is unrecoverable */
    hal_sys_init();
    hal_uart_open(3,115200,HAL_UART_PARITY_NONE, HAL_UART_STOP_BITS_1);
    hal_i2c_init();
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
    /* Initialize system state */
    display_kyb_init();
    dmm_error err = sys_dmm_init();
    /* The default configuration cannot be loaded. Other could work. The user
     * can leave this state pressing a button. The button 1 is mem1, 2 mem2 etc.
     * if the user press zero, default settings are loaded again. */
    if(err == DMM_ERR_EEPROM){
        display_puts("MEM 0-9?");
        switch(display_wait_for_key()){
            case KEY_0: sys_dmm_default_to_factory_settings(); break;
        }
    }
    bool shift_key = false;
    vTaskResume(measTaskHandle);

    while(1){
        switch(display_wait_for_key())
        {
            case KEY_7: sys_dmm_scale_up(); continue;
            case KEY_6: sys_dmm_scale_down(); continue;
            case KEY_3: sys_dmm_toggle_acdc(); continue;
            case KEY_1:  sys_dmm_set_mode(ADC_INPUT_RESISTANCE_2W); continue;
            case KEY_0: sys_dmm_restore_voltage_mode(); continue;
            case KEY_2:  sys_dmm_restore_current_mode(); continue;
            case KEY_4: continue;
            case KEY_UP: continue;
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
    printf("%s, %d\n", fileName, lineNo);
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