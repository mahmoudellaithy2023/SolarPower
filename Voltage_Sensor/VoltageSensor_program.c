/*
 * Voltage_Sensor.c
 *
 * Created: 29/05/2024 21:14:33
 *  Author: Ahmed_Eliwa
 */ 



#include "VoltageSensor_interface.h"


void VoltageSensor_Voidinit()
{
	// Initialize ADC Configurations
	ADC_Configuration adcConfig;
	
	adcConfig.AutoTriggerState= 0; // Auto-trigger disabled
	adcConfig.TriggerSource= 0;    // No trigger source
	adcConfig.DivisionFactor= 3;   // ADC prescaler division factor 8
	ADC_Init();
}

void VolatgeSensor_Read(float32* Volt)
{
	uint16 adcOutput = 0;
	float32 Vout  = 0, Vin = 0;
	uint16 R1 = 30000, R2 = 7500;
	
	
	ADC_Read(VoltageSenor_Pin, &adcOutput);
	
	Vout = (((float32)adcOutput / 1023) * 5);

	Vin = (Vout * ((R1 + R2) / R2));
	
	*Volt = Vin;
}
