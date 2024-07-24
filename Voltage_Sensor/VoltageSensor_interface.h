/*
 * Voltage_Sensor.h
 *
 * Created: 29/05/2024 21:14:41
 *  Author: Ahmed_Eliwa
 */ 


#ifndef VOLTAGE_SENSOR_H_
#define VOLTAGE_SENSOR_H_


#include <avr/io.h>
#include <util/delay.h>
#include "ADC_interface.h"
#include "PORT.h"
#include "VoltageSensor_config.h"
#include "ADC_private.h"
#include "LCD.h"


void VoltageSensor_Voidinit();
void VolatgeSensor_Read(float32* Volt);


#endif /* VOLTAGE_SENSOR_H_ */