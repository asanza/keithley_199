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

#include <adc.h>

 /* EEFS Addresses for stored objects */
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
    }dmm_memory_location;

    typedef enum {
        DMM_OK,
                DMM_NOT_SUPPORTED,
        DMM_UNCAL,
        DMM_ERR_EEPROM,
    }dmm_error;
dmm_error sys_dmm_init_adc();
    /**@brief Initializes the dmm subsystem */
    dmm_error sys_dmm_init();
    /**@brief get the actual adc value */
    double sys_dmm_read();
    /** @brief set the scanner channel
     * @param channel
     */
    void sys_dmm_set_channel(adc_channel channel);
    /**@brief set the integration period.
     * @param period
     */
    void sys_dmm_set_integration_period(adc_integration_period period);

    adc_integration_period sys_dmm_get_integration_period();

    void sys_dmm_scale_up();
    void sys_dmm_scale_down();
    adc_range sys_dmm_get_scale();
    dmm_error sys_dmm_set_scale(adc_range scale);

    void sys_dmm_set_mode(adc_input mode);
    adc_input sys_dmm_get_mode();

    typedef struct calibration_t calibrator;
    dmm_error sys_dmm_calibrate(double* real_value, double* meas_value, int size,
            calibrator* cal );

    dmm_error sys_dmm_save_state(dmm_memory_location location);
    void sys_dmm_restore_state(dmm_memory_location location);

    void sys_dmm_default_to_factory_settings();

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

