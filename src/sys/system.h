/*
 * File:   system.h
 * Author: diego
 *
 * Created on April 19, 2014, 2:58 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <FreeRTOS.h>
#include <task.h>
#include "sysstate.h"
#include "syserr.h"
#include <dispkyb.h>
    
    typedef enum {
        DMM_MEM_0 = 0x00,
        DMM_MEM_1,
        DMM_MEM_2,
        DMM_MEM_3,
        DMM_MEM_4,
        DMM_MEM_5,
        DMM_MEM_6,
        DMM_MEM_7,
        DMM_MEM_8,
        DMM_MEM_9,
        DMM_MEM_10,
        DMM_MEM_COUNT
    } dmm_memory_location;

    typedef TaskHandle_t(*DMMTaskHandler)(dmm_state *state);

    typedef struct DmmTask_t {
        key_id key_handler;
        DMMTaskHandler task;
    } dmm_task;

    void SystemTaskCreate(void);

    void SystemAddTask(dmm_task task);


    /**@brief Initializes the dmm subsystem */

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */
