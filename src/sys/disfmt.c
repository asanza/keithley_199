/*
 * disfmt.c
 *
 * Display formatter
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on January 24, 2015, 12:10 AM
 */

#include <disfmt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

disp_mode fmt_get_disp_mode(adc_input mode){
    disp_mode display_indicator = 0x00000000;
    switch(mode){
        case ADC_INPUT_VOLTAGE_AC:
            display_indicator|=DISP_AC;
        case ADC_INPUT_VOLTAGE_DC:
            display_indicator|=DISP_VOLTS; break;
        case ADC_INPUT_CURRENT_AC:
            display_indicator|=DISP_AC;
        case ADC_INPUT_CURRENT_DC:
            display_indicator|=DISP_AMPS; break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
            display_indicator|=DISP_OHMS; break;
    }
    return display_indicator;
}

void fmt_format_string(char* buff,adc_range scale, double value){
      switch(scale){
          case ADC_RANGE_3:
          case ADC_RANGE_3K:
          case ADC_RANGE_3M:
          {
              if(value >= 0){
                sprintf(buff," %06.5f",value/1.0);
              }
              else{
                sprintf(buff,"%07.5f",value/1.0);
              }
              if(fabs(value)>= ADC_MAX_VALUE){
                  sprintf(buff," O.VERFL ");
              }
          }
          break;
          case ADC_RANGE_30m:
          case ADC_RANGE_30:
          case ADC_RANGE_30K:
          case ADC_RANGE_30M:
          {
              if(value >= 0){
                sprintf(buff," %07.4f",value/1.0);
              }
              else{
                sprintf(buff,"%08.4f",value/1.0);
              }
              if(fabs(value) >= ADC_MAX_VALUE*10){
                  sprintf(buff," OV.ERFL ");
              }
          }
          break;
          case ADC_RANGE_300:
          case ADC_RANGE_300K:
          case ADC_RANGE_300M:
          case ADC_RANGE_300m:
          {
              if(value >= 0){
                sprintf(buff," %07.3f",value/1.0);
              }
              else{
                sprintf(buff,"%08.3f",value/1.0);
              }
              if(fabs(value) >= ADC_MAX_VALUE*100){
                  sprintf(buff," OVE.RFL ");
              }
          }
          break;
          default: break;
      }
}

void fmt_append_scale(char* buffer, adc_input mode){
    switch(mode){
        case ADC_INPUT_VOLTAGE_DC:
        case ADC_INPUT_VOLTAGE_AC:
        {
            if(sys_state_get_scale()==ADC_RANGE_300m)
                strcat(buffer, "mV ");
            else
                strcat(buffer, " V");
        }
        break;
        case ADC_INPUT_CURRENT_DC:
        case ADC_INPUT_CURRENT_AC:
        {
            if(sys_state_get_scale()==ADC_RANGE_30m)
                strcat(buffer,"mA");
            else
                strcat(buffer," A");
        }
        break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
        {
            switch(sys_state_get_scale()){
                case ADC_RANGE_300: strcat(buffer," o");break;
                case ADC_RANGE_3K:
                case ADC_RANGE_30K:
                case ADC_RANGE_300K: strcat(buffer," Ko");break;
                case ADC_RANGE_3M:
                case ADC_RANGE_30M:
                case ADC_RANGE_300M: strcat(buffer," Mo");break;
            }
        }
        break;
    }
}
