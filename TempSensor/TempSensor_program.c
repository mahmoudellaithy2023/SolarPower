#include "TempSensor_interface.h"

void Temp_voidInit()
{
	ADC_Configuration adcConfig;
	adcConfig.AutoTriggerState= 0; // Auto-trigger disabled
	adcConfig.TriggerSource= 0;    // No trigger source
	adcConfig.DivisionFactor= 3;
	ADC_Init();
}

void Temp_ErrStateGetReadValue(uint16* tempValue)
{

	uint16 TempSensor_Vout_mv = 0; //The analog vout of temperature sensor
	uint8 Temperature_Degree  = 0;
	uint16 TempAdcRead=0;
	
	ADC_Read(PIN2, &TempAdcRead);

	TempSensor_Vout_mv = (TempAdcRead  * 4.88) ; // Convert form digital volt to analog volt

	Temperature_Degree = TempSensor_Vout_mv / TempSensor_Step_mv ;    // Convert the analog volt to Temperature Degree

	*tempValue = Temperature_Degree ; //The function return the temperature degree from temperature sensor

}
