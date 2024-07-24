/*

 * MahmoudProject.c
 * Created: 17/02/2024 23:24:50
 * Author : Ahmed_Eliwa
 
 */ 

//#define F_CPU 1000000UL

#define MAX_WATER_SENSOR_READ    200
#define MAX_TEMP_SENSOR_READ    70


#include <avr/io.h>
#include <util/delay.h>
#include "PORT.h"
//#include "LCD.h"
#include "ADC_interface.h"
#include "WaterSensor_interface.h"
#include "TempSensor_Interface.h"
#include "LDR_Interface.h"
//#include "VoltageSensor_interface.h"
#include "DC_Motor.h"
#include "Servo.h"

void ServoSystem();

int main(void)
{
	Port_Init(Port_Config_Pins);
	WaterSensor_Voidinit();
	Temp_voidInit();
	LDR_voidInit();
	pwm_init();
	//LCD_Init(LCD_Config);

	uint16 WaterVal= 0, TempSread=0;
	uint8 Degree = 0;
	uint16 TmpLdrVal = 0;
	uint8 MaxDegree = 0;
	uint8 ProtectionFlag = TRUE;
		
	while(1)
	{	
		
		
		if(ProtectionFlag == FALSE)
		{
			//Dio_WriteChannel(PORT_D, PIN0);
			
			ServoSystem();
			_delay_ms(120000);
			
			/* Turn on Timer for 20 minutes by enabling interrupt in background */
			
		}
		
		
		WaterSensor_VoidGetWaterLevelStateAsyc(&WaterVal);
		_delay_ms(200);
		
		Temp_ErrStateGetReadValue(&TempSread);
		
		if(WaterVal > MAX_WATER_SENSOR_READ)
		{
			ProtectionFlag = TRUE;
			
			//Dio_WriteChannel(PORT_D, PIN1);
			//Dio_ClearChannel(PORT_D, PIN2);
			
			
			DC_Motor_on(DC_Motor_Config, 0, RIGHT);
			_delay_ms(2000);
			DC_Motor_off(DC_Motor_Config);
			/* Turn on DC motor */
			/*Turn off ServoMotor System*/
		}
		
		else
		{
			ProtectionFlag = FALSE;
			Dio_ClearChannel(PORT_D, PIN1);
			Dio_WriteChannel(PORT_D, PIN2);
			
		}				
	}
}


void ServoSystem()
{
	uint16 LdrReadVal= 0;
	uint8 Degree = 0;
	uint16 TmpLdrVal = 0;
	uint8 MaxDegree = 0;
	
	for(uint8 i =0; i<4; i++)
	{
		
		ServoMotor_voidSetAngle(Degree);
		_delay_ms(1000);
		AutoLightIntensity(&TmpLdrVal);
		
		
		if(TmpLdrVal > LdrReadVal)
		{
			LdrReadVal = TmpLdrVal;
			MaxDegree = Degree;
		}
		Degree += 45;	
	}
	
	ServoMotor_voidSetAngle(MaxDegree);
	_delay_ms(200);	
}