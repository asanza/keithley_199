/** temperature sensor driver */
#include <hal.h>

#include "HardwareProfile.h"

uint16_t drv_tempsens_readvalue(){
    uint8_t data;
    hal_i2c_read_byte(HAL_TEMPSENS_ADDRESS,0x01,&data);
    return data;
}