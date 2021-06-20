/*
 * amc_max_7219.c
 *
 *  Created on: 12 Jun 2021
 *      Author: amc
 */

#include "amc/max7219.h"

lpspi_transfer_t lpspiTransfer;
uint8_t txData[TRANSFER_SIZE] = { 0 };

void MAX7219_transfer(size_t dataSize) {
	lpspiTransfer.dataSize = dataSize;
	LPSPI_MasterTransferBlocking(LPSPI1, &lpspiTransfer);
}

void MAX7219_displayDigit(uint8_t address, uint32_t digit) {
	uint32_t value = digit;
	bool zero = false;
	for (uint8_t i = address; i < 8; i++) {
		uint32_t quotient = value / 10;
		uint32_t reminder = value - quotient * 10;

		//set address
		txData[2 * i] = 1 + i;
		//set value
		txData[2 * i + 1] = reminder;

		if ((quotient == 0 && reminder == 0 && digit !=0) || zero) {
			//0x0f will disable specific digit
			txData[2 * i + 1] = 0x0f;
		}
		if (digit == 0) {
			zero = true;
		}
		value = quotient;
	}
}

void MAX7219_initialize(void) {
	//get default config for master SPI1
	lpspi_master_config_t  masterConfig;
	LPSPI_MasterGetDefaultConfig(&masterConfig);
	//MAX7219 requires 16 bit per frame
	masterConfig.bitsPerFrame = 16;
	//MAX7219 MAX CLK speed is 10Mhz. Set to 8Mhz (BOARD_BOOTCLOCKRUN_LPSPI_CLK_ROOT) check Clocks Diagram

	LPSPI_MasterInit(LPSPI1, &masterConfig, BOARD_BOOTCLOCKRUN_LPSPI_CLK_ROOT);

	lpspiTransfer.txData = txData;
	lpspiTransfer.rxData = NULL;
	lpspiTransfer.configFlags = kLPSPI_MasterPcs0 | kLPSPI_MasterByteSwap;

	txData[0] = 0x0f; //display test register
	txData[1] = 0x00; //test mode off

	txData[2] = 0x0c; //shutdown register
	txData[3] = 0x01; //normal operation

	txData[4] = 0x0b; //scan limit register
	txData[5] = 0x07; //display digits 0 through 7

	txData[6] = 0x0a; //intensity register
	txData[7] = 0x05; //max brightness

	txData[8] = 0x09; //decode mode register
	txData[9] = 0xff; //CodeB decode all digits

	MAX7219_transfer(10);
}

void MAX7219_display4Digits(uint8_t digit1, uint8_t digit2, uint8_t digit3,
		uint8_t digit4) {
	MAX7219_displayDigit(0, digit1);
	MAX7219_displayDigit(2, digit2);
	MAX7219_displayDigit(4, digit3);
	MAX7219_displayDigit(6, digit4);
	MAX7219_transfer(16);
}

void MAX7219_display1Digit(uint32_t digit) {
	MAX7219_displayDigit(0, digit);
	MAX7219_transfer(16);
}


