#ifndef PN532_H
#define PN532_H

#include "stm32f1xx_hal.h"

// Define the I2C address of the PN532 module
#define PN532_I2C_ADDRESS 0x48  // Adjusted based on the 7-bit I2C address format

// Command for LIST_PASSIVE_TARGET to find an NFC tag
#define PN532_COMMAND_INLISTPASSIVETARGET 0x4A

// Function prototype to read the NFC card ID
uint8_t PN532_ReadCardID(I2C_HandleTypeDef *hi2c, uint8_t *cardID);

#endif // PN532_H
