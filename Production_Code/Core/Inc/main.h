/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWM_PERIOD 15010
#define PWM_PRESCALER 19
#define UART_EN_Pin GPIO_PIN_2
#define UART_EN_GPIO_Port GPIOE
#define ADDR_JP1_Pin GPIO_PIN_3
#define ADDR_JP1_GPIO_Port GPIOE
#define ADDR_JP2_Pin GPIO_PIN_4
#define ADDR_JP2_GPIO_Port GPIOE
#define ADDR_JP3_Pin GPIO_PIN_5
#define ADDR_JP3_GPIO_Port GPIOE
#define ADDR_JP4_Pin GPIO_PIN_6
#define ADDR_JP4_GPIO_Port GPIOE
#define RedLed_Pin GPIO_PIN_14
#define RedLed_GPIO_Port GPIOC
#define BATT1_Pin GPIO_PIN_2
#define BATT1_GPIO_Port GPIOC
#define BATT2_Pin GPIO_PIN_3
#define BATT2_GPIO_Port GPIOC
#define FuelFlow_Pin GPIO_PIN_3
#define FuelFlow_GPIO_Port GPIOA
#define FuelFlow_EXTI_IRQn EXTI3_IRQn
#define GreenLed_Pin GPIO_PIN_0
#define GreenLed_GPIO_Port GPIOB
#define RGBRLed_Pin GPIO_PIN_2
#define RGBRLed_GPIO_Port GPIOD
#define RGBGLed_Pin GPIO_PIN_3
#define RGBGLed_GPIO_Port GPIOD
#define RGBBLed_Pin GPIO_PIN_4
#define RGBBLed_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */
#define FORCE_INLINE __attribute__((always_inline)) inline
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
