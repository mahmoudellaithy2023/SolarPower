#include "UART.h"



/*

Belwo is a Struct that will Hold the Configurations of the UART Module

1- Parity Bit ---- ON or OFF
2- Number of Data Bits in the Frame
3- Number of Stop Bits in the Frame


Hint --> You Have to Configure The RX(PD0) and TX(PD1) Pins in your Microcntroller as Input and Output Respectively

*/


const UART_Config   UARTConfig = 
{
    Eight_Bits_Mode,
    ParityBit_OFF,
    EvenParity_Mode,
    OneStop_Bit,
};