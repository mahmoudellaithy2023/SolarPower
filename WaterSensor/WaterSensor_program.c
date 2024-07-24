
#include "WaterSensor_interface.h"


void WaterSensor_Voidinit()
{
	// Initialize ADC Configurations
	ADC_Configuration adcConfig;
	adcConfig.AutoTriggerState= 0; // Auto-trigger disabled
	adcConfig.TriggerSource= 0;    // No trigger source
	adcConfig.DivisionFactor= 3;   // ADC prescaler division factor 8
	ADC_Init();
	//ADC_voidInitPolling(adcConfig);
}

void WaterSensor_VoidGetWaterLevelStateAsyc(uint16* WaterVal)
{
	uint16 waterSensorValue = 0; // Variable to store the sensor reading

	//Dio_SetChannelDirection(PORT_C,WATER_SENSOR_PIN,INPUT);//sensor pin
	Dio_SetChannelDirection(PORT_D,LED_Detected,OUTPUT);// led1
	Dio_SetChannelDirection(PORT_D,LED_NotDetected,OUTPUT);// led2

	// Read analog input from the water sensor
	 ADC_Read(WATER_SENSOR_PIN,&waterSensorValue);
	//ADC_Read(WATER_SENSOR_PIN,&waterSensorValue);
	
	*WaterVal = waterSensorValue;

	// Check the sensor reading and take appropriate actions
	//_delay_ms(1000); // Add a delay if needed
}


