/*
 * hc_sr04.h
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "time.h"

/*******************************************************************************
 * Configurations
 ******************************************************************************/
#define SW_IRQ_A GPIO1_Combined_0_15_IRQn
#define SW_IRQ_B GPIO1_Combined_16_31_IRQn
#define HC_SR04_IRQHandler_A GPIO1_Combined_0_15_IRQHandler
#define HC_SR04_IRQHandler_B GPIO1_Combined_16_31_IRQHandler

#define MAX_WAIT_DURATION_US 1000000
#define MICROSECONDS_TO_CM_DEVIDER 58

/*******************************************************************************
 * Initialisation
 ******************************************************************************/
void HC_SR04_initialize();
void HC_SR04_initializePins(uint32_t echoPin, uint32_t triggerPin );
void HC_SR04_initializeD14Pin(uint32_t echoPin);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Measures distance between sensor and an object
 *
 * @param gpio NXP have 4 groups of GPIO (arduino will use GPIO1 and GPIO3)
 * @param triggerPin gpio attached to sensor trigger
 * @retval distance in cm
 */
uint32_t HC_SR04_measure(GPIO_Type *gpio, uint32_t triggerPin);

#endif /* HC_SR04_H_ */
