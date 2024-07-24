/*
 * TempSensor_config.h
 *
 *  Created on: Oct 14, 2023
 *      Author: mkank
 */

#ifndef TEMPSENSOR_CONFIG_H
#define TEMPSENSOR_CONFIG_H

#include "ADC_interface.h"


#define TempSensor_Channel     DIO_Pin0
#define ADC_ChannelsPort       DIO_GroupA



#define SingleEnded_Channel_1            0x00
#define SingleEnded_Channel_2            0x01
#define SingleEnded_Channel_3            0x02
#define SingleEnded_Channel_4            0x03
#define SingleEnded_Channel_5            0x04
#define SingleEnded_Channel_6            0x05
#define SingleEnded_Channel_7            0x06
#define SingleEnded_Channel_8            0x07
#define No_Channel                       0x1f



#define ADC_Step                        0.005
#define AVref_mv                        5000
#define Resolution                      10
#define TempSensor_Step_mv              10




#endif /* HAL_TEMPERATURE_SENSOR_LM35_TEMPSENSOR_CONFIG_H_ */
