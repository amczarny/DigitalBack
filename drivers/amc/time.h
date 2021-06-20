/*
 * amc_time.h
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef AMC_TIME_H_
#define AMC_TIME_H_

#include "fsl_common.h"
#include "fsl_gpt.h"

/*******************************************************************************
 * Configurations
 ******************************************************************************/
#define TIME_TickHandler GPT1_IRQHandler

#define MICROSECONDS_PER_HOUR 3600000000

typedef struct TimerDurationDef {
	uint32_t microseconds;
	uint32_t hours;
} TimerDuration;

/*******************************************************************************
 * Initialisation
 ******************************************************************************/
void TIME_initialize(void);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Starts the microseconds timer. It allows to measure duration in microseconds.
 * Use TIME_StopMicroTimer to get the duration back.
 * Counter uses 2 32bit variables to store time represented by TimerDuration.
 *
 * Only one timer is available. Every call will restart the timer.
 *
 */
void TIME_StartMicroTimer(void);

/*!
 * @brief Stops and reset the microseconds timer.
 *
 * @retval TimerDuration type. It stores number of microseconds and hours since the counter has been stared.
 */
TimerDuration TIME_StopMicroTimer(void);

/*!
 * @brief delay execution by number of microseconds
 *
 * @param delayUs   delay in microseconds
 */
void TIME_DelayMicro(uint32_t delayUs);

/*!
 * @brief delay execution by number of milliseconds
 *
 * @param delayUs   delay in milliseconds
 */
void TIME_DelayMilli(uint32_t delayMs);

#endif /* AMC_TIME_H_ */
