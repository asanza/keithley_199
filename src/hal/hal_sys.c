#include <hal_sys.h>
#include "HardwareProfile.h"
#include <peripheral/system.h>
#include <peripheral/uart.h>
#include <peripheral/ports.h>
#include <peripheral/power.h>

void hal_sys_init(){
    SYSTEMConfigPerformance(SYS_CLK);
    INTSetVectorPriority(INT_VECTOR_UART(UART3),3);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTDisableInterrupts();
}

void hal_sys_idle(){
    PowerSaveIdle();
}