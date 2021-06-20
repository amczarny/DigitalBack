/*
 * hc_sr04.c
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 */
#include "amc/hc_sr04.h"

volatile bool wait = false;
volatile TimerDuration HC_SR04_timerDuration;
volatile bool rising = true;
volatile uint32_t pin;

void HC_SR04_IRQHandler_A(void) {
	HC_SR04_IRQHandler();
}

void HC_SR04_IRQHandler_B(void) {
	HC_SR04_IRQHandler();
}

void HC_SR04_IRQHandler(void) {
	if (wait) {
		//GPIO_PortClearInterruptFlags(GPIO1, 1U << pin);
		if (rising) {
			TIME_StartMicroTimer();
			rising = false;
		} else {
			HC_SR04_timerDuration = TIME_StopMicroTimer();
			rising = true;
			wait = false;
		}
	}
	//reset all
	GPIO_PortClearInterruptFlags(GPIO1, 0xFFFFFFFF);
	SDK_ISR_EXIT_BARRIER;
}

void HC_SR04_initialize() {
	EnableIRQ(SW_IRQ_A);
	EnableIRQ(SW_IRQ_B);
}

void HC_SR04_initializePins(uint32_t echoPin, uint32_t triggerPin) {
	gpio_pin_config_t triggerPinConfig = { kGPIO_DigitalOutput, 0,
			kGPIO_NoIntmode };
	GPIO_PinInit(GPIO1, triggerPin, &triggerPinConfig);

	gpio_pin_config_t echoPinConfig = { kGPIO_DigitalInput, 0,
			kGPIO_IntRisingOrFallingEdge };
	GPIO_PinInit(GPIO1, echoPin, &echoPinConfig);

	/* Enable GPIO pin interrupt */
	GPIO_PortEnableInterrupts(GPIO1, 1U << echoPin);

}

void HC_SR04_initializeD14Pin(uint32_t echoPin) {
	gpio_pin_config_t triggerPinConfig = { kGPIO_DigitalOutput, 0,
			kGPIO_NoIntmode };
	GPIO_PinInit(ARDUINO_D14_IO3_GPIO, ARDUINO_D14_IO3_GPIO_PIN, &triggerPinConfig);

	gpio_pin_config_t echoPinConfig = { kGPIO_DigitalInput, 0,
			kGPIO_IntRisingOrFallingEdge };
	GPIO_PinInit(GPIO1, echoPin, &echoPinConfig);

	/* Enable GPIO pin interrupt */
	GPIO_PortEnableInterrupts(GPIO1, 1U << echoPin);

}

uint32_t HC_SR04_measure(uint32_t triggerPin, GPIO_Type *gpio) {
	GPIO_PinWrite(gpio, triggerPin, 1U);
	//wait at least 10 microseconds;
	TIME_DelayMicro(15);
	GPIO_PinWrite(gpio, triggerPin, 0U);
	wait = true;
	pin = triggerPin;

	uint32_t counter = 0;
	while (wait && counter < MAX_WAIT_DURATION_US) {
		TIME_DelayMicro(100);
		counter += 100;
	}

	//in case of not interrupt - stop timer
	if (wait) {
		HC_SR04_timerDuration = TIME_StopMicroTimer();
		wait = false;
	}
	return HC_SR04_timerDuration.microseconds / MICROSECONDS_TO_CM_DEVIDER;
}
