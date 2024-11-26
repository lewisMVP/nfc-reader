/* USER CODE BEGIN Header */
/**
  *******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "pn532.h"
#include "string.h"
#include "stm32f1xx_hal_uart.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t cardID[4]; // Store the NFC card ID
char lcdMessage[32]; // Buffer for LCD messages
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#ifdef __GNUC__
    // Redirection for printf to work with USART
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
/* USER CODE END 0 */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  
  /* USER CODE BEGIN 2 */
  LCD_Init(); // Initialize the LCD
  LCD_Clear();
  LCD_SetCursor(0, 0);
  LCD_Print("Initializing...");
  HAL_Delay(2000); // Wait 2 seconds for startup
  LCD_Clear();
  printf("NFC Module Test Starting...\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if (PN532_ReadCardID(&hi2c1, cardID)) {
        // Format card ID as a string
        snprintf(lcdMessage, sizeof(lcdMessage), "ID: %02X %02X %02X %02X", 
                 cardID[0], cardID[1], cardID[2], cardID[3]);

        // Print to UART
        printf("Card ID: %02X %02X %02X %02X\n", 
               cardID[0], cardID[1], cardID[2], cardID[3]);

        // Display on LCD
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_Print("Card Detected:");
        LCD_SetCursor(1, 0);
        LCD_Print(lcdMessage);
    } else {
        // Display no card detected message
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_Print("No Card Found");
        printf("No NFC card detected.\n");
    }
    HAL_Delay(1000); // Wait 1 second before checking again
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}