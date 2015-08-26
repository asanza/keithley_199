/* 
 * File:   HardwareProfile.h
 * Author: diego
 *
 * Created on March 10, 2014, 9:15 PM
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <peripheral/ports.h>
#include <peripheral/pps.h>
#include <peripheral/timer.h>
#include <peripheral/ports.h>

#define PIC32_PERIPHERALBUS_FREQ 80000000UL
    
/* io definitions */
#define BRD_RED_LED         IOPORT_C, BIT_4
#define BRD_GREEN_LED       IOPORT_C, BIT_3
#define BRD_AUX_LED         IOPORT_B, BIT_4
#define DEBUG_PIN_0         IOPORT_A, BIT_9
    
#define I2C_SDA             IOPORT_G, BIT_3
#define I2C_SCL             IOPORT_G, BIT_2

/* map hal uarts to real uarts */
#define HAL_UART_COUNT        1   /**< Number of enabled uarts */
//#define HAL_UART_1          UART1
//#define HAL_UART_2          UART2
#define HAL_UART_3            UART3 /**< UART 3 enabled */
//#define HAL_UART_4          UART4

#if defined HAL_UART_1
#error "define pps for uart 1"
#endif
#if defined HAL_UART_3
#if defined HAL_UART_2
#error "define pps for uart 2"
#endif
#define CONFIGURE_UART3_PPS() do{ \
        PPSInput(2,U3RX,RPB3); \
        PPSOutput(1,RPB5,U3TX); \
        PORTSetPinsDigitalIn(IOPORT_B,BIT_3);\
        PORTSetPinsDigitalOut(IOPORT_B, BIT_5); }while(0)
#endif
#if defined HAL_UART_4
#error "define pps for uart 4"
#endif


/* Configure hardware counter used for read adc value */
#define HW_32BIT_COUNTER_SET_INPUT()do{ \
            PPSInput(3,T4CK,RPE3); \
            PORTSetPinsDigitalIn(KMM_COUNT); }while(0)

#define HW_32BIT_COUNTER_START( counter_period ) do{ \
    OpenTimer4(T4_ON|T4_IDLE_CON \
            |T4_GATE_OFF|T4_PS_1_1  \
            |T4_32BIT_MODE_ON|T4_SOURCE_EXT, counter_period ); \
    }while(0)

/**@brief Macro to clear hardware errors in UART Module */
#define _clroverrun(value) U##value##STAbits.OERR = 0
/**@brief Clear hardware errors from uart module */

#define UARTClearOverrunError(module_id) do{ \
        if(module_id == UART1) _clroverrun(1);\
        if(module_id == UART2) _clroverrun(2);\
        if(module_id == UART3) _clroverrun(3);\
        if(module_id == UART4) _clroverrun(4);\
        if(module_id == UART5)  _clroverrun(5);\
}while(0)
    
#define HW_32BIT_COUNTER_RESTART() WriteTimer4(0)

#define HW_32BIT_COUNTER_READ() ReadTimer4()

/* KMM Interface definitions */
#define KMM_CLK         IOPORT_F, BIT_6
#define KMM_DATA        IOPORT_F, BIT_8
#define KMM_STRB        IOPORT_G, BIT_1
#define KMM_COUNT       IOPORT_E, BIT_3

/* LCD Display */
#define DISPLAY_PORT    IOPORT_D
#define seg_a   BIT_5
#define seg_b   BIT_1
#define seg_c   BIT_3
#define seg_d   BIT_13
#define seg_e   BIT_2
#define seg_f   BIT_4
#define seg_g   BIT_6
#define seg_h   BIT_11
#define seg_i   BIT_10
#define seg_j   BIT_9
#define seg_k   BIT_8
#define seg_l   BIT_12
#define seg_m   BIT_7
#define seg_n   BIT_15 
#define seg_dp  BIT_14
    
#define dclk    IOPORT_G, BIT_6
#define ddata   IOPORT_C, BIT_1

/*EEPROM SUBSYSTEM*/
#define HAL_I2C_BUS      I2C1    /**< I2C module on chip */
#define HAL_I2C_CONFIG   I2C_ENABLE_SLAVE_CLOCK_STRETCHING|I2C_ENABLE_HIGH_SPEED /**< eeprom configuration*/

#define HAL_EEPROM_ADDRESS      0x50    /**< I2C address for the eeprom */
#define HAL_TEMPSENS_ADDRESS    0x48    /**< I2C address for temperature sensor */
#define HAL_I2C_FREQ            100000  /**< I2C bus frequency */
#define HAL_EEPROM_SIZE         0x8000  /**< EEPROM size in bytes */
#define HAL_EEPROM_PAGE_SIZE    64      /**< EEPROM page size in bytes */


    /* keyboard */
#define HAL_KYB_S0  IOPORT_G, BIT_0
#define HAL_KYB_S1  IOPORT_F, BIT_0
#define HAL_KYB_S2  IOPORT_G, BIT_14

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_H */

