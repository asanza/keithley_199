/**
 * @file exceptions.c
 * @brief Exception handling routines
 * This file reimplements the PIC32 _general_exception_handler.
 * The default _general_exception_handler provided by
 * microchip libraries is just a while loop. The handler implemente
 * in this file gives a little more of information, by using the board
 * leds and blinking codes.
 * @author Diego F. Asanza
 */

// pin access functions
#include <hal_io.h>

// declared static in case exception condition would prevent
// auto variable being created
static enum {
	EXCEP_IRQ = 0,			// interrupt
	EXCEP_AdEL = 4,			// address error exception (load or ifetch)
	EXCEP_AdES,				// address error exception (store)
	EXCEP_IBE,				// bus error (ifetch)
	EXCEP_DBE,				// bus error (load/store)
	EXCEP_Sys,				// syscall
	EXCEP_Bp,				// breakpoint
	EXCEP_RI,				// reserved instruction
	EXCEP_CpU,				// coprocessor unusable
	EXCEP_Overflow,			// arithmetic overflow
	EXCEP_Trap,				// trap (possible divide by zero)
	EXCEP_IS1 = 16,			// implementation specfic 1
	EXCEP_CEU,				// CorExtend Unuseable
	EXCEP_C2E				// coprocessor 2
} _excep_code;


/**
 * general exception handler for mips architecture
 * @param ulCause cause of the exception.
 * @param ulStatus status register
 */
void _general_exception_handler( unsigned long ulCause, unsigned long ulStatus )
{
    _excep_code = (ulCause & 0x0000007C) >> 2;
    /** Generate blinking codes for interrupts */
    hal_io_set_led(SYSERR_LED);
    switch(_excep_code)
    {
    case EXCEP_Trap:
        while(1);
        break;
    case EXCEP_DBE:
        while(1);
        break;
    default:
        while(1);
    }
}

