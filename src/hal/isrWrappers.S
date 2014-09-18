#include <p32xxxx.h>
#include <sys/asm.h>
#include <ISR_Support.h>

	.set	nomips16
	.set 	noreorder

	.extern xISRStackTop

	.extern UARTUSBInterruptHandler
	.global	UARTUSBInterruptWrapper
    .extern OC3_handler
    .global OC3_wrapper

    .extern CT_handler
    .global CT_wrapper

	.set	noreorder
	.set 	noat

	.ent	UARTUSBInterruptWrapper
UARTUSBInterruptWrapper:
	portSAVE_CONTEXT
	jal UARTUSBInterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UARTUSBInterruptWrapper

    .ent OC3_wrapper
OC3_wrapper:
    portSAVE_CONTEXT
    jal OC3_handler
    nop
    portRESTORE_CONTEXT
    .end OC3_wrapper

    .ent CT_wrapper
CT_wrapper:
    portSAVE_CONTEXT
    jal CT_handler
    nop
    portRESTORE_CONTEXT
    .end CT_wrapper