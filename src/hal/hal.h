/* 
 * File:   hal.h
 * Author: diego
 *
 * Created on March 9, 2014, 11:05 PM
 */

#ifndef HAL_H
#define	HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>
#include <stdbool.h>

#include <hal_sys.h>
#include <hal_adc.h>
#include <hal_io.h>
#include <hal_spi.h>
#include <hal_sys.h>
#include <hal_timer.h>
#include <hal_uart.h>
#include <hal_i2c.h>
    
#endif /*__LANGUAGE_ASSEMBLY*/
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_H */

