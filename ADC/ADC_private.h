#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "Bit_Math.h"

#include "Std_Types.h"

//Registers
#define ADC_MUX       *((volatile uint8*)0X27)
#define ADC_SRA      *((volatile uint8*)0X26)
#define ADC_Data        *((volatile uint16*)0X24)
#define ADC_SFIOR       *((volatile uint8*)0X50)

/*Bits*/
//------------------------------------------------Pins at register ADMUX
#define ADMUX_REFS1      7
#define ADMUX_REFS0      6
#define ADMUX_ADLAR      5
#define ADMUX_MUX4       4
//-------------------------------------------------Pins at Register  ADCSRA
#define ADCSRA_ADEN       7
#define ADCSRA_ADSC       6
#define ADCSRA_ADATE      5
#define ADCSRA_ADIF       4
#define ADCSRA_ADIE       3
#define ADCSRA_ADPS2      2
#define ADCSRA_ADPS1      1
#define ADCSRA_ADPS0      0

//------------------------------------------------- Pins at Register SFIOR
#define SFIOR_ADTS0     5
#define SFIOR_ADTS1     6
#define SFIOR_ADTS2     7


/* ADC_Reference_Options*/
#define ADC_ExternalArefPin       1
#define ADC_AvccActArefPin        2 // AVCC 1- Power 2- use  as AREF
#define ADC_InternalArefPin       3 // internal AREF = 2.56

/*Adjust Result Option */
#define ADC_RightAdjustResult     1
#define ADC_LeftAdjustResult      2
// Data sheet representable for Auto Trigger Source and it's pins indicates
//Last 3 pins how these Trigger Source Works
// count thier Binary and give the result
typedef enum
{
    freeRunning,
	Analog_Comparator=32,//  32 16 8 4 2 1
	                     //   1  0 0 0 0 0 // and so on....
	External_interrupt_Request_0=64,
	Timer0CompareMatch=96,
	Timer0OverFlow=128,
	Timer1CompareMatchB=160,
	Timer1OverFlow=192,
	Timer1OCaptureEvent=192

}Trigger_Source;

typedef struct
{
   uint8 AutoTriggerState ;
   uint16 TriggerSource;
   uint8 DivisionFactor;

}ADC_Configuration;

extern ADC_Configuration ADC_Config;

#endif
