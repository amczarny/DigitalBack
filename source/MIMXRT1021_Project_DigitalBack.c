/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MIMXRT1021_Project_DigitalBack.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
#include "fsl_lpuart.h"

#include "amc/time.h"
#include "amc/max7219.h"
#include "amc/hc_sr04.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define MAX_DSITANCE 15
/*
 * @brief   Application entry point.
 */
int main(void) {
	BOARD_InitBootClocks();
	BOARD_InitBootPins();
	BOARD_InitBootPeripherals();
	MAX7219_initialize();
	TIME_initialize();
	HC_SR04_initialize();

	//issues with display
	TIME_DelayMilli(100);

	MAX7219_display1Digit(0);

	HC_SR04_initializeD14Pin(ARDUINO_D3_PIN);
	HC_SR04_initializePins(ARDUINO_D5_PIN, ARDUINO_A0_PIN);
	HC_SR04_initializePins(ARDUINO_D7_PIN, ARDUINO_D6_PIN);
	HC_SR04_initializePins(ARDUINO_D9_PIN, ARDUINO_D8_PIN);

	lpuart_config_t config;
	LPUART_GetDefaultConfig(&config);
	config.baudRate_Bps = 9600;
	config.enableTx     = true;
	config.enableRx     = true;

	LPUART_Init(LPUART2, &config, BOARD_BOOTCLOCKRUN_UART_CLK_ROOT);

	uint8_t str[15];
	int size = 0;

	/* Enter an infinite loop, just incrementing a counter. */

	while (1) {

		//GPIO_PinWrite(ARDUINO_D4_PORT, ARDUINO_D4_PIN, 1U);
		GPIO_PinWrite(ARDUINO_D4_PORT, ARDUINO_D4_PIN, 1U);
		TIME_DelayMilli(500);
		GPIO_PinWrite(ARDUINO_D4_PORT, ARDUINO_D4_PIN, 0U);
		TIME_DelayMilli(500);

		GPIO_PinWrite(ARDUINO_A5_PORT, ARDUINO_A5_PIN, 1U);
		uint32_t distance1 = HC_SR04_measure(ARDUINO_D6_PIN, GPIO1);
		size = sprintf(str, "Distance1:%d\n", distance1);
	    LPUART_WriteBlocking(LPUART2,  str, size);
		MAX7219_display1Digit(distance1);
		TIME_DelayMilli(5000);
	    GPIO_PinWrite(ARDUINO_A5_PORT, ARDUINO_A5_PIN, 0U);


		GPIO_PinWrite(ARDUINO_A4_PORT, ARDUINO_A4_PIN, 1U);
		uint32_t distance2 = HC_SR04_measure(ARDUINO_D14_IO3_PIN, GPIO3);
		MAX7219_display1Digit(distance2);
		size = sprintf(str, "Distance2:%d\n", distance2);
	    LPUART_WriteBlocking(LPUART2,  str, size);
		TIME_DelayMilli(5000);
		GPIO_PinWrite(ARDUINO_A4_PORT, ARDUINO_A4_PIN, 0U);


		GPIO_PinWrite(ARDUINO_A3_PORT, ARDUINO_A3_PIN, 1U);
		uint32_t distance3 = HC_SR04_measure(ARDUINO_D8_PIN, GPIO1);
		MAX7219_display1Digit(distance3);
		size = sprintf(str, "Distance3:%d\n", distance3);
	    LPUART_WriteBlocking(LPUART2,  str, size);
		TIME_DelayMilli(5000);
		GPIO_PinWrite(ARDUINO_A3_PORT, ARDUINO_A3_PIN, 0U);


		GPIO_PinWrite(ARDUINO_A2_PORT, ARDUINO_A2_PIN, 1U);
		uint32_t distance4 = HC_SR04_measure(ARDUINO_A0_PIN, GPIO1);
		MAX7219_display1Digit(distance4);
		size = sprintf(str, "Distance4:%d\n", distance4);
	    LPUART_WriteBlocking(LPUART2,  str, size);
		TIME_DelayMilli(5000);
		GPIO_PinWrite(ARDUINO_A2_PORT, ARDUINO_A2_PIN, 0U);


		if (distance1 > MAX_DSITANCE || distance2 > MAX_DSITANCE || distance3 > MAX_DSITANCE || distance4 > MAX_DSITANCE) {
			GPIO_PinWrite(ARDUINO_A1_PORT, ARDUINO_A1_PIN, 1U);
			TIME_DelayMilli(200);
			GPIO_PinWrite(ARDUINO_A1_PORT, ARDUINO_A1_PIN, 0U);
			TIME_DelayMilli(200);
		}

	}
	return 0;
}
