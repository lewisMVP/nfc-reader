#include "pn532.h"
#include "string.h"

uint8_t PN532_ReadCardID(I2C_HandleTypeDef *hi2c, uint8_t *cardID) {
    uint8_t command[] = {PN532_COMMAND_INLISTPASSIVETARGET, 0x01, 0x00};  // Command to find NFC card
    uint8_t response[16];  // Buffer to store response
    
    // Send the command to the PN532 module over I2C
    HAL_I2C_Master_Transmit(hi2c, (PN532_I2C_ADDRESS << 1), command, sizeof(command), HAL_MAX_DELAY);
    
    // Receive response from PN532
    HAL_I2C_Master_Receive(hi2c, (PN532_I2C_ADDRESS << 1) | 1, response, sizeof(response), HAL_MAX_DELAY);

    // Check the response data to ensure the card is detected
    if (response[0] == 0x00 && response[5] > 0) {
        // Copy the 4-byte card ID from the response
        memcpy(cardID, &response[6], 4);
        
        // Return 1 to indicate success
        return 1;
    }
    
    // Return 0 to indicate failure (no card detected)
    return 0;
}
