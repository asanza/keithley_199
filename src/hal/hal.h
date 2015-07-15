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

#define SYS_CLK     80000000UL
#define PB_CLK      80000000UL

void hal_sys_init();

void hal_usbuart_init();
int hal_usbuart_receive(char* buffer, int size);
void hal_usbuart_readline(char* buffer, int size);

void hal_sys_idle();

#endif /*__LANGUAGE_ASSEMBLY*/
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_H */

