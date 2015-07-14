/*
 * File:   system.h
 * Author: diego
 *
 * Created on April 19, 2014, 2:58 PM
 */

#ifndef SYSTASKS_H
#define	SYSTASKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <dispkyb.h>
    
    typedef void(*systask_handler)(void*);
    void systask_create_main(void);
    void systask_add(systask_handler task, key_id key_switch);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTASKS_H */
