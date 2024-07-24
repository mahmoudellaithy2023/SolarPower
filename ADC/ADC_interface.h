#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "Bit_Math.h"
#include "Std_Types.h"
#include "ADC_Private.h"
#include "ADC_Config.h"
#include "PORT.h"
//information -> struct
//uint8 ADC_uint8InitInterrupt(uint8 channel);// intilization for ADC in interrrupt mode
//void ADC_voidInit(Information ADC_InitInformation);
//void ADC_voidEnableInterrupt();
//void ADC_voidDisableInterrupt();
//uint16 ADC_uint16ReadResult(uint8 channel);// polling 3shan ana dakhel function msh hakhrog mnha gher wna m3aia el function   // read from the ADC Channel


/*polling*/

// pre configuration
void ADC_voidInitPolling(ADC_Configuration ADC_Info);
void ADC_voidReadDigitalVoltPolling(uint8 channel , uint16* DigitalVolt); // ha2olo 3ala el channel kaza w ykhazen el result f digitalvolt
void ADC_Init();
void ADC_Read(uint8 channel, uint16* DigitalVolt);
/*General */
void ADC_voidDisableADC(void);


/*Interrupt*/
void ADC_voidInitInterrupt(ADC_Configuration ADC_Info);
void ADC_voidReadDigitalVoltInterrupt(uint8 channel);
void__vector_16()__attribute__((signal));

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
