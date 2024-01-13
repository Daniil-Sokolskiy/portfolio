/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED13_Pin GPIO_PIN_13
#define LED13_GPIO_Port GPIOC
#define ECHO_Pin GPIO_PIN_14
#define ECHO_GPIO_Port GPIOB
#define TRG_Pin GPIO_PIN_15
#define TRG_GPIO_Port GPIOB
#define DHT_11_Pin GPIO_PIN_10
#define DHT_11_GPIO_Port GPIOA
#define ST7735_BL_Pin GPIO_PIN_11
#define ST7735_BL_GPIO_Port GPIOA
#define ST7735_CS_Pin GPIO_PIN_5
#define ST7735_CS_GPIO_Port GPIOB
#define ST7735_DC_Pin GPIO_PIN_6
#define ST7735_DC_GPIO_Port GPIOB
#define ST7735_RES_Pin GPIO_PIN_7
#define ST7735_RES_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
