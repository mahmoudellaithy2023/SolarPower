
#include <avr/io.h>
#include "ADC_Interface.h"
#include "util/delay.h"
static uint16 ResultInterrupt;


void ADC_Init(){
	//make PA0 an analog input
	DDRA &= ~(1<<PA0);	        /* Make ADC port as input */
	DDRA &= ~(1<<PA2);	        /* Make ADC port as input */
	DDRA &= ~(1<<PA4);	        /* Make ADC port as input */
	DDRA &= ~(1<<PA6);	        /* Make ADC port as input */
	
	
	//Dio_SetPortDirection(PORT_A, INPUT);
	//enable ADC module, set prescalar of 128 which gives CLK/128
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	//set the voltage reference using REFS1 and REFS0 bits and select the ADC channel using the MUX bits
	ADMUX = 0b01000000;      // set REFS1 = 0 |REFS0 = 1 (Vref as AVCC pin) | ADLAR = 0(right adjusted) |  MUX4 to MUX0 is 0000 for ADC0
}

void ADC_Read(uint8 channel, uint16* DigitalVolt)
{
	/* set input channel to read */
	ADMUX = 0x40 | (channel & 0x07);   // 0100 0000 | (channel & 0000 0100)
	/* Start ADC conversion */
	ADCSRA |= (1<<ADSC);
	/* Wait until end of conversion by polling ADC interrupt flag */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear interrupt flag */
	ADCSRA |= (1<<ADIF);
	_delay_ms(1);                      /* Wait a little bit */
	/* Return ADC word */
	
	*DigitalVolt=ADC_Data;
}

void ADC_voidInitPolling(ADC_Configuration ADC_Info)
{
	//ADMUX
	// 1-Select Ref -> REFS1   REFS0(7,6) / hytghayr wla wla ? tb during runtime or before?
	// (configure | Before Runtime |pre configuration  )
#if   ADC_Reference_Selection==ADC_ExternalArefPin
	CLEAR_BIT(ADC_MUX,ADMUX_REFS1);
	CLEAR_BIT(ADC_MUX,ADMUX_REFS0);
#elif ADC_Reference_Selection==ADC_AvccActArefPin
	CLEAR_BIT(ADC_MUX,ADMUX_REFS1);
	SET_BIT(ADC_MUX,ADMUX_REFS0);
#elif ADC_Reference_Selection== ADC_InternalArefPin
	SET_BIT(ADC_MUX,ADMUX_REFS1);
	SET_BIT(ADC_MUX,ADMUX_REFS0);

#else #error "invalid Option Error 404"
#endif

	// 2-Select adjust result -> ADLAR ->Left ,Right (5)(configure | Before Runtime |pre configuration  )

#if  ADC_OptionalAdjustResult== ADC_RightAdjustResult
	CLEAR_BIT(ADC_MUX,ADMUX_ADLAR);
#elif  ADC_OptionalAdjustResult== ADC_LeftAdjustResult
	SET_BIT(ADC_MUX,ADMUX_ADLAR);
#else #error "invalid Option Error 404"
#endif

	/*ADCSRA*/

	//1-Enable for ADC -> ADEN -> (7) must be written High(no configred)
	SET_BIT(ADC_SRA,ADCSRA_ADEN);

	//2-Select the AutoTriggerd  ->(Enable) | Select  the AutoTriggered (Disable) -> ADATE(5)

	if(ADC_Info.AutoTriggerState==1)
	{
		SET_BIT(ADC_SRA,ADCSRA_ADATE);
		//11100000->ADC_Info.AutoTriggerState
		ADC_Info.TriggerSource&=0XE0;
		//00011111 ->ADC_SFIOR
		ADC_SFIOR&=0X1F;
		ADC_SFIOR|=ADC_Info.TriggerSource;
	}
	else if (ADC_Info.AutoTriggerState==0)
	{

		CLEAR_BIT(ADC_SRA,ADCSRA_ADATE);
	}

	//3-Disable The ADIE interrupt Enable (3) 3shan ana fl polling
	CLEAR_BIT(ADC_SRA,ADCSRA_ADIE);
	//4- Selection For Division Factor ADPS2   ADPS1  ADPS0

	//00000111 taking ones that indicates what's i need and make what i do not need as zeros
	ADC_Info.DivisionFactor&=0X07;
	//11111000
	ADC_SRA&=0XF0;
	ADC_SRA|=ADC_Info.DivisionFactor;

}

void ADC_voidReadDigitalVoltPolling(uint8 channel , uint16*DigitalVolt)
{
	//Select Channel
	//00011111
	channel&=0x1f; // 3auza a7afez 3ala awel 5 a army akher 5
	//111000000 anadf w asafar ele 3auza akteb feh
	ADC_MUX&=0XE0;
	//set Channel
	ADC_MUX|=channel;
	// StartConversion

	SET_BIT(ADC_SRA,ADCSRA_ADSC );
	//waitFlag
	//while(READ_BIT(ADC_SRA,ADCSRA_ADIF)==FlagOFF)); //Time Out
	while(READ_BIT(ADC_SRA,ADCSRA_ADIF)!= FlagON);



	//ReadData
	*DigitalVolt=ADC_Data;
	//*DigitalVolt = ADCL
	//*DigitalVolt = ()
	//Clr Flag
	SET_BIT(ADC_SRA,ADCSRA_ADIF);
}

void ADC_voidInitInterrupt(ADC_Configuration ADC_Info)
{
	//ADMUX
	// 1-Select Ref -> REFS1   REFS0(7,6) / hytghayr wla wla ? tb during runtime or before?
	// (configure | Before Runtime |pre configuration  )
#if   ADC_Reference_Selection==ADC_ExternalArefPin
	CLEAR_BIT(ADC_MUX,ADMUX_REFS1);
	CLEAR_BIT(ADC_MUX,ADMUX_REFS0);
#elif ADC_Reference_Selection==ADC_AvccActArefPin
	CLEAR_BIT(ADC_MUX,ADMUX_REFS1);
	SET_BIT(ADC_MUX,ADMUX_REFS0);
#elif ADC_Reference_Selection== ADC_InternalArefPin
	SET_BIT(ADC_MUX,ADMUX_REFS1);
	SET_BIT(ADC_MUX,ADMUX_REFS0);

#else #error "invalid Option Error 404"
#endif

	// 2-Select adjust result -> ADLAR ->Left ,Right (5)(configure | Before Runtime |pre configuration  )

#if  ADC_OptionalAdjustResult== ADC_RightAdjustResult
	CLEAR_BIT(ADC_MUX,ADMUX_ADLAR);
#elif  ADC_OptionalAdjustResult== ADC_LeftAdjustResult
	SET_BIT(ADC_MUX,ADMUX_ADLAR);
#else #error "invalid Option Error 404"
#endif

	/*ADCSRA*/

	//1-Enable for ADC -> ADEN -> (7) must be written High(no configred)
	SET_BIT(ADC_SRA,ADCSRA_ADEN);

	//2-Select the AutoTriggerd  ->(Enable) | Select  the AutoTriggered (Disable) -> ADATE(5)

	if(ADC_Info.AutoTriggerState==1)
	{
		SET_BIT(ADC_SRA,ADCSRA_ADATE);
		//11100000->ADC_Info.AutoTriggerState
		ADC_Info.TriggerSource&=0XE0;
		//00011111 ->ADC_SFIOR
		ADC_SFIOR&=0X1F;
		ADC_SFIOR|=ADC_Info.TriggerSource;
	}
	else if (ADC_Info.AutoTriggerState==0)
	{

		CLEAR_BIT(ADC_SRA,ADCSRA_ADATE);
	}

	//3-Disable The ADIE intterupt Enable (3) 3shan ana fl polling
	SET_BIT(ADC_SRA,ADCSRA_ADIE);
	//4- Selecetion For Division Factor ADPS2   ADPS1  ADPS0

	//00000111 taking ones that indicates what's i need and make what i do not need as zeros

	ADC_Info.DivisionFactor&=0X07;
	//11111000
	ADC_SRA&=0XF0;
	ADC_SRA|=ADC_Info.DivisionFactor;


}
void ADC_voidReadDigitalVoltInterrupt(uint8 channel)
{
	//Select Channel
	//00011111
	channel&=0x1f; // 3auza a7afez 3ala awel 5 a army akher 5
	//111000000 anadf w asafar ele 3auza akteb feh
	ADC_MUX&=0XE0;
	//set Channel
	ADC_MUX|=channel;
	// StartConversion

	SET_BIT(ADC_SRA,ADCSRA_ADSC );

}

void __vector_16() __attribute__((signal));
void __vector_16()
{
	ResultInterrupt = ADC_Data;
}


