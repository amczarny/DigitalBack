/*
 * amc_max_7219.h
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 */

#ifndef AMC_MAX7219_H_
#define AMC_MAX7219_H_

#include "fsl_common.h"
#include "fsl_lpspi.h"
#include "clock_config.h"

#define TRANSFER_SIZE 16

void MAX7219_initialize(void);

void MAX7219_display4Digits(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4);

void MAX7219_display1Digit(uint32_t digit);

#endif /* AMC_MAX7219_H_ */
