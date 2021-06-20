/*
 * amc_time.c
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * idea based on led_blinky demo-apps
 * SDK_2.9.1_EVK-MIMXRT1020 (1)/boards/evkmimxrt1020/demo_apps/led_blinky
 */

#include <amc/time.h>

volatile uint32_t tick_counter = 0;

volatile TimerDuration timerDuration;
volatile bool timerEnabled = false;

void TIME_TickHandler(void) {
	/* Clear interrupt flag.*/
	GPT_ClearStatusFlags(GPT1, kGPT_OutputCompare1Flag);

	if (tick_counter != 0U) {
		tick_counter--;
	}

	if (timerEnabled) {
		timerDuration.microseconds++;
		if (timerDuration.microseconds == MICROSECONDS_PER_HOUR) {
			timerDuration.hours++;
			timerDuration.microseconds == 0;
		}
	}

	/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
	 exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
	__DSB();
#endif
}

void TIME_initialize(void) {

    gpt_config_t gptConfig;
    GPT_GetDefaultConfig(&gptConfig);

    /* Initialize GPT module */
    GPT_Init(GPT1, &gptConfig);

    GPT_SetOutputCompareValue(GPT1, kGPT_OutputCompare_Channel1, 24);
    GPT_SetOutputOperationMode(GPT1, kGPT_OutputCompare_Channel1, kGPT_OutputOperation_Disconnected);

    /* Enable GPT Output Compare1 interrupt */
    GPT_EnableInterrupts(GPT1, kGPT_OutputCompare1InterruptEnable);

    /* Enable at the Interrupt */
    EnableIRQ(GPT1_IRQn);

    GPT_StartTimer(GPT1);
}

void TIME_StartMicroTimer(void) {
	//reset duration
	timerDuration.hours = 0;
	timerDuration.microseconds = 0;
	timerEnabled = true;
}

TimerDuration TIME_StopMicroTimer(void) {
	timerEnabled = false;

	//shallow copy of TimeDuration struct
	TimerDuration result = timerDuration;

	//reset duration
	timerDuration.hours = 0;
	timerDuration.microseconds = 0;

	return result;
}

void TIME_DelayMicro(uint32_t delayUs) {
	tick_counter = delayUs;

	while (tick_counter != 0) {
	}
}

void TIME_DelayMilli(uint32_t delayMs) {
	tick_counter = delayMs * 1000;

	while (tick_counter != 0) {
	}
}
