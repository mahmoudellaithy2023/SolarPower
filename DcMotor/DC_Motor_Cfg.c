#include "DC_Motor.h"



/*
You can usr this struct to adjust your direction pins

Please Note That --- YOU HAVE TO MAKE THESE PINS AS OUTPUT PINS IN ADDITION TO THE OC0 PIN IN YOUR ECU IN (PORT_CFG)

Please Fill the Config struct following this order
{
   PortID
   
   Enable Pin

   ChannelID_Right

   ChannelID_Left

}

*/


const DcMotor_ConfigType   DC_Motor_Config = 
{
    PORT_B, /* Dirction Port*/
	PIN5,   /*Enable Pin*/
    PIN6,  /* Right Pin*/
    PIN7, /* Left Pin*/
};