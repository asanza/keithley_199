/* 
 * Copyright (C) September 26, 2014 Diego F. Asanza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * File:   dmmTask.c
 * Author: Diego F. Asanza <f.asanza[at]gmail.com>
 *
 * Created on September 26, 2014, 11:35 PM
 */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <sys.h>
#include <dispkyb.h>

#include <tmp275.h>

static void show_display_mode(){
    disp_mode display_indicator = 0x00000000;
    switch(sys_dmm_get_mode()){
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
    display_setmode(display_indicator);
}

static void append_scale(char* buffer){

    switch(sys_dmm_get_mode()){
        case ADC_INPUT_VOLTAGE_DC:
        case ADC_INPUT_VOLTAGE_AC:
        {
            if(sys_dmm_get_scale()==ADC_RANGE_300m)
                strcat(buffer, "mV ");
            else
                strcat(buffer, " V");
        }
        break;
        case ADC_INPUT_CURRENT_DC:
        case ADC_INPUT_CURRENT_AC:
        {
            if(sys_dmm_get_scale()==ADC_RANGE_30m)
                strcat(buffer,"mA");
            else
                strcat(buffer," A");
        }
        break;
        case ADC_INPUT_RESISTANCE_2W:
        case ADC_INPUT_RESISTANCE_4W:
        {
            switch(sys_dmm_get_scale()){
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


void dmmTaskMain(void* pvParameters)
{
    char buff[10];
    tmp245_init();
    while(1)
    {
          hal_disp_adci_toggle();
          double value = sys_dmm_read();
          double temp = tmp245_read_temp_double();
          switch(sys_dmm_get_scale()){
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
                  if(fabs(value)>3.03){
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
                  if(fabs(value)>30.3){
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
                  if(fabs(value)>303){
                      sprintf(buff," OVE.RFL ");
                  }
              }
              break;
              default: break;
          }
          append_scale(buff);
          display_clear();
          show_display_mode();
          display_puts(buff);
          printf("%f,%f\n",value, temp);
    }
}
