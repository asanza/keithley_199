#include <hal.h>
#include "HardwareProfile.h"
#include <peripheral/system.h>
#include <peripheral/ports.h>
#include <peripheral/power.h>

void hal_sys_init(){
    SYSTEMConfigPerformance(SYS_CLK);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTDisableInterrupts();
}

void hal_sys_idle(){
    PowerSaveIdle();
}