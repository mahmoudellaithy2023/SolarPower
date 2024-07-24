/*
 * WaterSensor_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Mahmoud Ellithy
 */

#ifndef WATERSENSOR_INTERFACE_H
#define WATERSENSOR_INTERFACE_H

#include <avr/io.h>
#include <util/delay.h>
#include "ADC_interface.h"
#include "PORT.h"
#include "WaterSensor_Config.h"
#include "ADC_private.h"

void WaterSensor_Voidinit();
void WaterSensor_VoidGetWaterLevelStateAsyc(uint16* WaterVal);

#endif /* HAL_WATER_SENSOR_WATERSENSOR_INTERFACE_H_ */
