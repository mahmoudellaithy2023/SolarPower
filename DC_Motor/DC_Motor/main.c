/*
 * DC_Motor.c
 *
 * Created: 20/06/2024 06:14:59 م
 * Author : Mahmoud Ellithy
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "DC_Motor.h"
#include <util/delay.h>
#include "PORT.h"

int main(void)
{
   Port_Init(Port_Config_Pins);
    while (1) 
    {
		DC_Motor_on(DC_Motor_Config,0,RIGHT);
		_delay_ms(10000);
		DC_Motor_off(DC_Motor_Config);
		_delay_ms(10000);
		DC_Motor_on(DC_Motor_Config,0,LEFT);
		_delay_ms(30000);
    }
}

