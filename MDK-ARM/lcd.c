#include "stm32f1xx_hal.h"
#include "lcd.h"
#include "i2c.h"

// Function to send data to the LCD via I2C
static void LCD_Write(uint8_t value, uint8_t mode) {
    uint8_t data[2];
    
    // Format the data: mode (0x00 for command, 0x01 for data)
    data[0] = (value & 0xF0) | mode;  // High nibble
    data[1] = ((value << 4) & 0xF0) | mode;  // Low nibble

    // Send via I2C
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

// Function to initialize the LCD
void LCD_Init(void) {
    // Initialize I2C
    HAL_I2C_Init(&hi2c1);
    
    // LCD initialization
    HAL_Delay(50);  // Wait for startup
    LCD_Write(0x33, 0);  // Initialization command 1
    LCD_Write(0x32, 0);  // Initialization command 2
    LCD_Write(0x28, 0);  // 4-bit mode
    LCD_Write(0x0C, 0);  // Turn on display, cursor off
    LCD_Write(0x06, 0);  // Set entry mode
    LCD_Clear();  // Clear screen
}

// Function to clear the LCD screen
void LCD_Clear(void) {
    LCD_Write(LCD_CLEAR_CMD, 0);
    HAL_Delay(2);  // Wait for the LCD to process the clear command
}

// Function to set the cursor position on the LCD
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t cmd = 0x80 | (row + col);  // Set cursor position command
    LCD_Write(cmd, 0);
}

// Function to print a string on the LCD
void LCD_Print(char *text) {
    while (*text) {
        LCD_Write(*text++, 1);  // Send each character to display
    }
}