#include <hal.h>
#include "HardwareProfile.h"
#include <peripheral/system.h>
#include <peripheral/ports.h>
#include <peripheral/power.h>

void hal_sys_init(){
    PORTSetPinsDigitalOut(BRD_GREEN_LED);
    PORTClearBits(BRD_GREEN_LED);
    PORTSetPinsDigitalOut(BRD_AUX_LED);
    PORTClearBits(BRD_AUX_LED);
    PORTSetPinsDigitalOut(BRD_RED_LED);
    PORTSetBits(BRD_RED_LED);
    PORTSetPinsDigitalOut(DEBUG_PIN_0);
    PORTClearBits(DEBUG_PIN_0);
    SYSTEMConfigPerformance(SYS_CLK);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTDisableInterrupts();
}

void hal_io_toggle_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTToggleBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTToggleBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTToggleBits(BRD_AUX_LED); break;
    }
}

void hal_io_set_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTClearBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTClearBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTClearBits(BRD_AUX_LED); break;
    }
}

void hal_io_clear_led(IO_LED led){
    switch(led){
        case SYSERR_LED: PORTSetBits(BRD_RED_LED); break;
        case SYSOK_LED: PORTSetBits(BRD_GREEN_LED); break;
        case AUX_LED: PORTSetBits(BRD_AUX_LED); break;
    }
}

void hal_io_set_debugpin(){
    PORTSetBits(DEBUG_PIN_0);
}
void hal_io_clear_debugpin(){
    PORTClearBits(DEBUG_PIN_0);
}

void hal_io_toggle_debugpin(){
    PORTToggleBits(DEBUG_PIN_0);
}

void hal_sys_idle(){
    PowerSaveIdle();
}