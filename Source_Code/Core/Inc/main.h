/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define LED_RED_A_Pin GPIO_PIN_0
#define LED_RED_A_GPIO_Port GPIOA
#define LED_YELLOW_A_Pin GPIO_PIN_1
#define LED_YELLOW_A_GPIO_Port GPIOA
#define LED_GREEN_A_Pin GPIO_PIN_2
#define LED_GREEN_A_GPIO_Port GPIOA
#define LED_RED_B_Pin GPIO_PIN_3
#define LED_RED_B_GPIO_Port GPIOA
#define LED_YELLOW_B_Pin GPIO_PIN_4
#define LED_YELLOW_B_GPIO_Port GPIOA
#define LED_GREEN_B_Pin GPIO_PIN_5
#define LED_GREEN_B_GPIO_Port GPIOA
#define SEG_A_Pin GPIO_PIN_7
#define SEG_A_GPIO_Port GPIOA
#define BUTTON_A_Pin GPIO_PIN_0
#define BUTTON_A_GPIO_Port GPIOB
#define BUTTON_B_Pin GPIO_PIN_1
#define BUTTON_B_GPIO_Port GPIOB
#define BUTTON_C_Pin GPIO_PIN_2
#define BUTTON_C_GPIO_Port GPIOB
#define SEG_B_Pin GPIO_PIN_8
#define SEG_B_GPIO_Port GPIOA
#define SEG_C_Pin GPIO_PIN_9
#define SEG_C_GPIO_Port GPIOA
#define SEG_D_Pin GPIO_PIN_10
#define SEG_D_GPIO_Port GPIOA
#define SEG_E_Pin GPIO_PIN_11
#define SEG_E_GPIO_Port GPIOA
#define SEG_F_Pin GPIO_PIN_12
#define SEG_F_GPIO_Port GPIOA
#define SEG_G_Pin GPIO_PIN_13
#define SEG_G_GPIO_Port GPIOA
#define SEG_EN_Pin GPIO_PIN_4
#define SEG_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
