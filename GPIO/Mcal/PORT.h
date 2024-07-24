
#ifndef  PORT_H
#define  PORT_H


#include "Platform_Types.h"
#include "Port_Cfg.h"
#include "Port_REG.h"

#define    STD_LOW         (0U)
#define    STD_HIGH        (1U)

#define    OUTPUT          (1U)
#define    INPUT           (0U)


typedef uint8 Dio_PortType;

typedef uint8 Dio_ChannelType;

typedef uint8 Dio_LevelType;

typedef uint8 Dio_PortLevelType;

typedef uint8 Dio_DirectionType;



typedef enum
{
	INPUT_PIN,
	OUTPUT_PIN

}Pintype;



typedef enum
{
	PULL_DOWN,
	PULL_UP

}PinMode;


typedef enum
{
	LOW_LEVEL,
	HIGH_LEVEL

}PinStatus;



typedef struct Port_Config
{
	Dio_PortType               PortId;
	Dio_ChannelType            ChannelId;
	Pintype                    Pin_type;
	PinMode                    Pin_mode;
	PinStatus                  Pin_status;

}PortConfig;



extern const PortConfig  Port_Config_Pins[REQUIRD_CONFIGURED_PINS];


Dio_LevelType Dio_ReadChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);

void Dio_WriteChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);
void Dio_ClearChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);
void Dio_FlipChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);
void Dio_SetChannelDirection(Dio_PortType PortID, Dio_ChannelType ChannelId, Dio_DirectionType Level);

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
void Dio_SetPortDirection(Dio_PortType PortID, Dio_DirectionType Level);

void Port_Init(const PortConfig* ConfigPtr);

#endif