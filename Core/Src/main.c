#include "main.h"
#include "pn532.h"
#include "string.h"
#include "lcd.h"
#include <stdio.h> 

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

uint8_t cardID[4];
char lcdMessage[32];

#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void) {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    LCD_Init(); 
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print("Initializing...");
    HAL_Delay(2000);
    LCD_Clear();
    printf("NFC Module Test Starting...\n");

    while (1) {
        if (PN532_ReadCardID(&hi2c1, cardID)) {
            snprintf(lcdMessage, sizeof(lcdMessage), "ID: %02X %02X %02X %02X", 
                     cardID[0], cardID[1], cardID[2], cardID[3]);
            printf("Card ID: %02X %02X %02X %02X\n", 
                   cardID[0], cardID[1], cardID[2], cardID[3]);

            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_Print("Card Detected:");
            LCD_SetCursor(1, 0);
            LCD_Print(lcdMessage);
        } else {
            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_Print("No Card Found");
            printf("No NFC card detected.\n");
        }
        HAL_Delay(1000);
    }
}