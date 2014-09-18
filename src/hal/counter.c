/* integrator counter */
#include <hal.h>
#include <HardwareProfile.h>

void hal_counter_init(){
    HW_32BIT_COUNTER_SET_INPUT();
    HW_32BIT_COUNTER_START(0xFFFFFFFF);
}


void hal_counter_restart(){
    HW_32BIT_COUNTER_RESTART();
}

uint32_t hal_counter_read(){
    return HW_32BIT_COUNTER_READ();
}