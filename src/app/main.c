#include <stdio.h>

#include "adc.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <system.h>
#include <math.h>

static void MeasurementsTask(void *pvParameters);
static void sysMgmTask(void *pvParameters);
xTaskHandle measTaskHandle = NULL;
int main()
{
    /* hardware initialization. An error here is unrecoverable */
    hal_sys_init();
    hal_usbuart_init();
    hal_i2c_init();
    xTaskCreate(MeasurementsTask,"T1",configMINIMAL_STACK_SIZE,NULL,3,&measTaskHandle);
    /* suspend measurement task until we load dmm state on management task. */
    if(measTaskHandle)
        vTaskSuspend(measTaskHandle);
    /* system management task. */
    xTaskCreate(sysMgmTask,"T2",configMINIMAL_STACK_SIZE,NULL,3,NULL);
    vTaskStartScheduler();
}

static void sysMgmTask(void *pvParameters){
    /* Initialize system state */
    hal_disp_init();
    dmm_error err = sys_dmm_init();
    /* The default configuration cannot be loaded. Other could work. The user
     * can leave this state pressing a button. The button 1 is mem1, 2 mem2 etc.
     * if the user press zero, default settings are loaded again. */
    if(err == DMM_ERR_EEPROM){
        hal_disp_puts("MEM 0-9?");
        switch(hal_disp_wait_for_key()){
            case KEY_VOLTS: sys_dmm_default_to_factory_settings(); break;
        }
    }
    bool shift_key = false;
    vTaskResume(measTaskHandle);
    while(1){
        switch(hal_disp_wait_for_key())
        {
            case KEY_RANGE_UP: sys_dmm_scale_up(); continue;
            case KEY_RANGE_DOWN: sys_dmm_scale_down(); continue;
            case KEY_AC: sys_dmm_toggle_acdc(); continue;
            case KEY_OHMS:  sys_dmm_set_mode(ADC_INPUT_RESISTANCE_2W); continue;
            case KEY_VOLTS: sys_dmm_restore_voltage_mode(); continue;
            case KEY_AMPS:  sys_dmm_restore_current_mode(); continue;
            case KEY_ZERO: continue;
            case KEY_LOCAL: continue;
            case KEY_AUTO: continue;
            case KEY_SCANNER: continue;
            case KEY_TRIGGER: continue;
            case KEY_NEXT: shift_key = true; continue;
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

void show_display_mode(){
    disp_mode display_indicator = 0x00000000;
    switch(sys_dmm_get_mode()){
        case ADC_INPUT_VOLTAGE_AC:
            display_indicator|=DISP_AC;
        case ADC_INPUT_VOLTAGE_DC:
            display_indicator|=DISP_VOLTS; break;
        case ADC_INPUT_CURRENT_AC:
            display_indicator|=DISP_AC;
        case ADC_INPUT_CURRENT_DC:
            display_indicator|=DISP_AMPS; break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
            display_indicator|=DISP_OHMS; break;
    }
    hal_disp_setmode(display_indicator);
}

void append_scale(char* buffer){

    switch(sys_dmm_get_mode()){
        case ADC_INPUT_VOLTAGE_DC:
        case ADC_INPUT_VOLTAGE_AC:
        {
            if(sys_dmm_get_scale()==ADC_RANGE_300m)
                strcat(buffer, "mV ");
            else
                strcat(buffer, " V");
        }
        break;
        case ADC_INPUT_CURRENT_DC:
        case ADC_INPUT_CURRENT_AC:
        {
            if(sys_dmm_get_scale()==ADC_RANGE_30m)
                strcat(buffer,"mA");
            else
                strcat(buffer," A");
        }
        break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
        {
            switch(sys_dmm_get_scale()){
                case ADC_RANGE_300: strcat(buffer," o");break;
                case ADC_RANGE_3K:
                case ADC_RANGE_30K:
                case ADC_RANGE_300K: strcat(buffer," Ko");break;
                case ADC_RANGE_3M:
                case ADC_RANGE_30M:
                case ADC_RANGE_300M: strcat(buffer," Mo");break;
            }
        }
        break;
    }
}

static void MeasurementsTask(void* pvParameters)
{
    char buff[10];
    while(1)
    {
          //double value = hal_tempsens_readvalue();
          hal_disp_adci_toggle();
          double value = sys_dmm_read();
          //value = 1.036423533*value+0.0003341082;
          switch(sys_dmm_get_scale()){
              case ADC_RANGE_3:
              case ADC_RANGE_3K:
              case ADC_RANGE_3M:
              {
                  if(value >= 0){
                    sprintf(buff," %06.5f",value/1.0);
                  }
                  else{
                    sprintf(buff,"%07.5f",value/1.0);
                  }
                  if(fabs(value)>3.03){
                      sprintf(buff," O.VERFL ");
                  }
              }
              break;
              case ADC_RANGE_30m:
              case ADC_RANGE_30:
              case ADC_RANGE_30K:
              case ADC_RANGE_30M:
              {
                  if(value >= 0){
                    sprintf(buff," %07.4f",value/1.0);
                  }
                  else{
                    sprintf(buff,"%08.4f",value/1.0);
                  }
                  if(fabs(value)>30.3){
                      sprintf(buff," OV.ERFL ");
                  }
              }
              break;
              case ADC_RANGE_300:
              case ADC_RANGE_300K:
              case ADC_RANGE_300M:
              case ADC_RANGE_300m:
              {
                  if(value >= 0){
                    sprintf(buff," %07.3f",value/1.0);
                  }
                  else{
                    sprintf(buff,"%08.3f",value/1.0);
                  }
                  if(fabs(value)>303){
                      sprintf(buff," OVE.RFL ");
                  }
              }
              break;
              default: break;
          }
          append_scale(buff);
          hal_disp_clear();
          show_display_mode();
          hal_disp_puts(buff);
    }
}

void vApplicationIdleHook( void ){
    hal_sys_idle();
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
    while(1);
}

void vApplicationMallocFailedHook()
{
    while(1);
}