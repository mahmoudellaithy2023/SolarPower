#ifndef TEMPSENSOR_INTERFACE_H
#define TEMPSENSOR_INTERFACE_H

#include "TempSensor_config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC_interface.h"
#include "PORT.h"


void Temp_voidInit();
void Temp_ErrStateGetReadValue(uint16* tempValue);



#endif /* HAL_TEMPERATURE_SENSOR_LM35_TEMPSENSOR_INTERFACE_H_ */
