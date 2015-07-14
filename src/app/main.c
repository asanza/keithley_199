#include <stdio.h>
#include <diag.h>
#include <dispkyb.h>
#include <FreeRTOS.h>
#include <task.h>
#include <assert.h>
#include <systasks.h>
#include <hal_i2c.h>
#include <usb_uart.h>

int main()
{
    /* hardware initialization. An error here is unrecoverable */
    hal_sys_init();
    hal_i2c_init();
    usb_uart_init();
    display_kyb_init();
    /* create system task */
    systask_create_main();
    DIAG("START: %s, %s", REPOVERSION, REPOBRANCH);
    DIAG("Starting Scheduler");
    vTaskStartScheduler();
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