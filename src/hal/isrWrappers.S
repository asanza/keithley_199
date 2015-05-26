/**@file uart_intwrappers_freertos.S
 * This file implements the Interrupt entry points for Interrupts that
 * need to call freertos functions.
 * In order to use interrupt handling with freertos, the context of program
 * execution must be saved before entering interrupt and restored before exiting.
 * This file performs this context saving and then calls the *_isr_handler
 * functions. Assembler is used in order to reduce excecution time.
 *
 * @author Diego F. Asanza. Portions taken from FreeRTOS Distribution.
 *
 * When interrupts are able to change the Freertos Tasks states (for example,
 * from blocked to running), it is recomended to use following entry points.
 *
 * @see USING THE FREERTOS REAL TIME KERNEL - a pic32 edition book.
 */

/* These header files are part of the compiler distribution. */
#include <p32xxxx.h>
#include <sys/asm.h>
/* ISR_Support.h is part of the FreeRTOS distribution. It contains the
implementation of the portSAVE_CONTEXT and portRESTORE_CONTEXT macros. */
#include <ISR_Support.h>
    .set nomips16
    .set noreorder

    /* The C portion of the handler is implemented in an external C file.
    The .extern directive makes the function visible from within this
    assembly file. */
    .extern hal_uart1_isr_handler
    .extern hal_uart2_isr_handler
    .extern hal_uart3_isr_handler
    .extern hal_uart4_isr_handler    
    .extern OC3_handler
    .global OC3_wrapper

    .extern CT_handler
    .global CT_wrapper

    /* Required by the save and restore macros. */
    .extern xISRStackTop

    /* Make the assembler portion of the handler visible outside of this file.
    Making the wrapper visible from C files means the C compiler key word
    extensions can be used to populate the interrupt vector table.  */
    .global hal_uart1_isr_wrapper
    .global hal_uart2_isr_wrapper
    .global hal_uart3_isr_wrapper
    .global hal_uart4_isr_wrapper
    .global hal_uart5_isr_wrapper
    .global hal_i2c1_isr_wrapper
    .global hal_ext0_isr_wrapper
    .global hal_timer1_isr_wrapper
    .global hal_timer2_isr_wrapper
    .global hal_timer3_isr_wrapper
    .global hal_cn_isr_wrapper  // Interrupt wrapper for pin change notifications

/****************************************************************************/

    .set noreorder
    .set noat
    .ent hal_uart1_isr_wrapper
hal_uart1_isr_wrapper:
    /* Save the context of the currently executing task. portSAVE_CONTEXT()
    must be called before anything else is done. */
    portSAVE_CONTEXT
    /* Call the C portion of the interrupt handler. A NOP is always required
    after a jal instruction. */
    jal hal_uart1_isr_handler
    nop
    /* Restore the context of the next task to execute - which might be a
    different task to that which was executing before this interrupt occurred
    (that would be the case if the interrupt handler caused a task to leave the
    Blocked state, and the unblocked task had a priority that was equal to or
    above the priority of the originally executing task).
    portRESTORE_CONTEXT must be called at the very end and handles returning
    from the interrupt. */
    portRESTORE_CONTEXT
    .end hal_uart1_isr_wrapper
/******************************************************************************/

    .set noreorder
    .set noat
    .ent hal_uart2_isr_wrapper
/* Start of the handler implementation. */
hal_uart2_isr_wrapper:
    /* Save the context of the currently executing task. portSAVE_CONTEXT()
    must be called before anything else is done. */
    portSAVE_CONTEXT
    /* Call the C portion of the interrupt handler. A NOP is always required
    after a jal instruction. */
    jal hal_uart2_isr_handler
    nop
    /* Restore the context of the next task to execute - which might be a
    different task to that which was executing before this interrupt occurred
    (that would be the case if the interrupt handler caused a task to leave the
    Blocked state, and the unblocked task had a priority that was equal to or
    above the priority of the originally executing task).
    portRESTORE_CONTEXT must be called at the very end and handles returning
    from the interrupt. */
    portRESTORE_CONTEXT
    .end hal_uart2_isr_wrapper

/******************************************************************************/

    .set noreorder
    .set noat
    .ent hal_uart3_isr_wrapper
/* Start of the handler implementation. */
hal_uart3_isr_wrapper:
    /* Save the context of the currently executing task. portSAVE_CONTEXT()
    must be called before anything else is done. */
    portSAVE_CONTEXT
    /* Call the C portion of the interrupt handler. A NOP is always required
    after a jal instruction. */
    jal hal_uart3_isr_handler
    nop
    /* Restore the context of the next task to execute - which might be a
    different task to that which was executing before this interrupt occurred
    (that would be the case if the interrupt handler caused a task to leave the
    Blocked state, and the unblocked task had a priority that was equal to or
    above the priority of the originally executing task).
    portRESTORE_CONTEXT must be called at the very end and handles returning
    from the interrupt. */
    portRESTORE_CONTEXT
    .end hal_uart3_isr_wrapper

/******************************************************************************/

    .set noreorder
    .set noat
    .ent hal_uart4_isr_wrapper
/* Start of the handler implementation. */
hal_uart4_isr_wrapper:
    /* Save the context of the currently executing task. portSAVE_CONTEXT()
    must be called before anything else is done. */
    portSAVE_CONTEXT
    /* Call the C portion of the interrupt handler. A NOP is always required
    after a jal instruction. */
    jal hal_uart4_isr_handler
    nop
    /* Restore the context of the next task to execute - which might be a
    different task to that which was executing before this interrupt occurred
    (that would be the case if the interrupt handler caused a task to leave the
    Blocked state, and the unblocked task had a priority that was equal to or
    above the priority of the originally executing task).
    portRESTORE_CONTEXT must be called at the very end and handles returning
    from the interrupt. */
    portRESTORE_CONTEXT
    .end hal_uart4_isr_wrapper


    .set noreorder
    .set noat
    .ent OC3_wrapper
OC3_wrapper:
    portSAVE_CONTEXT
    jal OC3_handler
    nop
    portRESTORE_CONTEXT
    .end OC3_wrapper

    .set noreorder
    .set noat
    .ent CT_wrapper
CT_wrapper:
    portSAVE_CONTEXT
    jal CT_handler
    nop
    portRESTORE_CONTEXT
    .end CT_wrapper

