#include <stdint.h>
#include <stdbool.h>
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define PRINCIPAL_FREQUENCY 0x01000000
#define PRESCALE 0x0000ffff
#define TICKS_IN_SEC (PRINCIPAL_FREQUENCY / (PRESCALE + 1))
#define FLICKS_IN_SEC 2

#define RCC_AHB1ENR_OFFSET 12
#define RCC_APB1ENR_OFFSET 16
#define RCC_APB2ENR_OFFSET 17


#define GPIOD_MODER_OFFSET 0
#define GPIOD_ODR_OFFSET 5

#define TIM6_CR1_OFFSET 0
#define TIM6_DIER_OFFSET 3
#define TIM6_SR_OFFSET 4
#define TIM6_CNT_OFFSET 9
#define TIM6_PSC_OFFSET 10

#define EXTI_IMR_OFFSET 0
#define EXTI_EMR_OFFSET 1
#define EXTI_RTSR_OFFSET 2
#define EXTI_FTSR_OFFSET 3


void TIM6_DAC_IRQHandler(void){
  static int counter = 0;
  static bool is_on = false;

  volatile uint32_t* tim6_periph = 0x40001000;
  volatile uint32_t* gpiod_periph = 0x40020C00;

  if (0 == counter % (TICKS_IN_SEC / FLICKS_IN_SEC))
    if (is_on){
      is_on = false;
      *(gpiod_periph + GPIOD_ODR_OFFSET) &= 0xffff0fff;
    } else  {
      is_on = true;
      *(gpiod_periph + GPIOD_ODR_OFFSET) |= 0x0000f000;
    }

  *(tim6_periph + TIM6_SR_OFFSET) &= 0xfffffffe;
  ++counter;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  /* USER CODE BEGIN 2 */
 
  volatile uint32_t* rcc_periph = 0x40023800;
  // Turn on TIM6 clock enable, GPIOD enable, and.
  * (rcc_periph + RCC_APB1ENR_OFFSET) |= 0x00000010;
  * (rcc_periph + RCC_AHB1ENR_OFFSET) |= 0x00000008;
  
  // TODO: Enable in the APB2 Bus.
  volatile uint32_t* exti_periph = 0x40013C00;
  // Make line 0 available for interrupts
  *(exti_periph + EXTI_IMR_OFFSET) |= 0x00000001;
  *(exti_periph + EXTI_EMR_OFFSET) |= 0x00000001;
  *(exti_periph + EXTI_RTSR_OFFSET) |= 0x00000001;
  // TODO: see what line tim6 counter actually generates interrupts to.


  volatile uint32_t* gpiod_periph = 0x40020C00;
  // Set mode of all led lights to output.
  *(gpiod_periph + GPIOD_MODER_OFFSET) &= 0x00ffffff;
  *(gpiod_periph + GPIOD_MODER_OFFSET) |= 0x55000000;

  volatile uint32_t* tim6_periph = 0x40001000;
  //Enable Counter
  *(tim6_periph + TIM6_CR1_OFFSET) |= 0x00000001;

  // Set register prescale.
  *(tim6_periph + TIM6_PSC_OFFSET) |= PRESCALE;

  // Enable Update interrupts.
  *(tim6_periph + TIM6_DIER_OFFSET) |= 0x00000001;
  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {
    /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */
  }
  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
