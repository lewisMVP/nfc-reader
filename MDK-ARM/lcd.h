#ifndef LCD_H
#define LCD_H

#include "stm32f1xx_hal.h"  // STM32 library

// I2C Address of the LCD module (if using I2C)
#define LCD_I2C_ADDR   0x4E  // LCD I2C Address

// LCD Commands
#define LCD_CLEAR_CMD       0x01
#define LCD_RETURN_HOME_CMD 0x02
#define LCD_ENTRY_MODE_CMD  0x04
#define LCD_DISPLAY_CMD     0x08
#define LCD_FUNCTION_CMD    0x20
#define LCD_SET_CGRAM_CMD   0x40
#define LCD_SET_DDRAM_CMD   0x80

// Macro definitions for screen positions
#define LCD_LINE_1 0x00
#define LCD_LINE_2 0x40
#define LCD_LINE_3 0x14
#define LCD_LINE_4 0x54

// Function to initialize the LCD
void LCD_Init(void);

// Function to clear the LCD screen
void LCD_Clear(void);

// Function to set the cursor position on the LCD (row, column)
void LCD_SetCursor(uint8_t row, uint8_t col);

// Function to print a string on the LCD
void LCD_Print(char *text);

#endif // LCD_H