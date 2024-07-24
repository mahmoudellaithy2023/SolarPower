	/*
	 * wifi.c
	 *
	 *  Created on: 14 Jun 2024
	 *      Author: A Store
	 */



#include "wifi.h"

#define SSID "Eliwah"
#define PASSWORD "eihn8446"
#define SERVER "api.thingspeak.com"
#define PORT 80
#define MAX_RETRIES 5

static int checkResponse(const char* expectedResponse)
{
		char response[100];
		UART_receiveString_WIFI(response, sizeof(response));
		return strstr(response, expectedResponse) != NULL;
}

static int sendCommand(const char* command, const char* expectedResponse, int delayMs)
{
		UART_sendString(command);
		//_delay_ms(delayMs);
		for(int i = 1; i<delayMs; i++)
		{
			_delay_ms(1);
		}
		return checkResponse(expectedResponse);
}

void WiFi_init(void)
{
		//UART_ConfigType config;
		/*config.baud_rate=9600;
		config.bit_data=EIGHT_BIT;
		config.stop_bit=ONEBIT;
		config.parity=PARITY_OFF;*/
		
		//UART_init(&config);
		
		UART_Init(UARTConfig, 115200);
		int retries = MAX_RETRIES;
		while (retries--)
		{
			if (sendCommand("AT\r\n", "OK", 1000)) break;
		}
		if (retries <= 0) return;

		retries = MAX_RETRIES;
		while (retries--)
		{
			if (sendCommand("AT+CWMODE=0\r\n", "OK", 1000)) break;
		}
		if (retries <= 0) return;

		char connectCmd[100];
		snprintf(connectCmd, sizeof(connectCmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
		retries = MAX_RETRIES;
		while (retries--)
		{
			if (sendCommand(connectCmd, "OK", 5000)) break;
		}
}

void sendDataToServer(void)
{
		char sendCmd[100] = {12, 16, 17, 18, 19, 20};
		char requestData[200];

		snprintf(sendCmd, sizeof(sendCmd), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", SERVER, PORT);
		if (!sendCommand(sendCmd, "CONNECT", 2000)) return;

		snprintf(requestData, sizeof(requestData), "GET /update?api_key=ORROV41ETEKV21DC&field1=100\n");
		int dataLength = strlen(requestData);

		snprintf(sendCmd, sizeof(sendCmd), "AT+CIPSEND=%d\r\n", dataLength);
		if (!sendCommand(sendCmd, ">", 2000)) return;

		UART_sendString(requestData);
		_delay_ms(2000);
		if (!checkResponse("SEND OK")) return;

		char response[500];
		UART_receiveString_WIFI(response, sizeof(response));
		// Process the response if needed
}
