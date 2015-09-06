#include <stdio.h>
#include <diag.h>
#include <FreeRTOS.h>
#include <task.h>
#include <assert.h>
#include <system.h>
#include <diag.h>
#include "tskmgr.h"

int main()
{
    /* hardware initialization. An error here is unrecoverable */
    system_init();
    /* start tasks as needed */
    taskmgr_start();
    DIAG("START: %s, %s", REPOVERSION, REPOBRANCH);
    DIAG("Starting Scheduler");
    vTaskStartScheduler();
    return 0;
}

void vAssertCalled(const char* fileName, unsigned long lineNo)
{
    DIAG("FreeRTOS: %s, %ld\n", fileName, lineNo);
    while (1);
}

void vApplicationIdleHook(void)
{
    hal_sys_idle();
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, signed char *pcTaskName)
{
    DIAG("%s", pcTaskName);
    assert(0);
    while (1);
}

void vApplicationMallocFailedHook()
{
    DIAG("");
    assert(0);
    while (1);
}