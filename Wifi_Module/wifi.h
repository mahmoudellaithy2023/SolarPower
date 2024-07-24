	/*
	 * wifi.h
	 *
	 *  Created on: 14 Jun 2024
	 *      Author: A Store
	 */

	#ifndef WIFI_H_
	#define WIFI_H_

	//#include "uart.h"
	#include "UART.h"
	#include <util/delay.h>

	static int checkResponse(const char* expectedResponse);
	static int sendCommand(const char* command, const char* expectedResponse, int delayMs);
	void WiFi_init(void);
	void sendDataToServer(void);


	#endif /* WIFI_H_ */
