/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32l0xx_hal.h"

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
#define LED_R_Pin GPIO_PIN_13
#define LED_R_GPIO_Port GPIOC
#define LED_Y_Pin GPIO_PIN_14
#define LED_Y_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_15
#define LED_G_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_2
#define SW1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_3
#define SW2_GPIO_Port GPIOC
#define SENSOR_Pin GPIO_PIN_6
#define SENSOR_GPIO_Port GPIOA
#define SPI_RES_Pin GPIO_PIN_4
#define SPI_RES_GPIO_Port GPIOC
#define SPI_DC_Pin GPIO_PIN_5
#define SPI_DC_GPIO_Port GPIOC
#define NT23_Pin GPIO_PIN_13
#define NT23_GPIO_Port GPIOB
#define NT22_Pin GPIO_PIN_14
#define NT22_GPIO_Port GPIOB
#define NT21_Pin GPIO_PIN_15
#define NT21_GPIO_Port GPIOB
#define NT20_Pin GPIO_PIN_6
#define NT20_GPIO_Port GPIOC
#define NT13_Pin GPIO_PIN_7
#define NT13_GPIO_Port GPIOC
#define NT12_Pin GPIO_PIN_8
#define NT12_GPIO_Port GPIOC
#define NT11_Pin GPIO_PIN_9
#define NT11_GPIO_Port GPIOC
#define NT10_Pin GPIO_PIN_8
#define NT10_GPIO_Port GPIOA
#define NT03_Pin GPIO_PIN_9
#define NT03_GPIO_Port GPIOA
#define NT02_Pin GPIO_PIN_10
#define NT02_GPIO_Port GPIOA
#define NT01_Pin GPIO_PIN_11
#define NT01_GPIO_Port GPIOA
#define NT00_Pin GPIO_PIN_12
#define NT00_GPIO_Port GPIOA
#define NT30_Pin GPIO_PIN_15
#define NT30_GPIO_Port GPIOA
#define NT31_Pin GPIO_PIN_10
#define NT31_GPIO_Port GPIOC
#define NT32_Pin GPIO_PIN_11
#define NT32_GPIO_Port GPIOC
#define NT33_Pin GPIO_PIN_12
#define NT33_GPIO_Port GPIOC
#define NT40_Pin GPIO_PIN_2
#define NT40_GPIO_Port GPIOD
#define NT41_Pin GPIO_PIN_3
#define NT41_GPIO_Port GPIOB
#define NT42_Pin GPIO_PIN_4
#define NT42_GPIO_Port GPIOB
#define NT43_Pin GPIO_PIN_5
#define NT43_GPIO_Port GPIOB
#define NT50_Pin GPIO_PIN_6
#define NT50_GPIO_Port GPIOB
#define NT51_Pin GPIO_PIN_7
#define NT51_GPIO_Port GPIOB
#define NT52_Pin GPIO_PIN_8
#define NT52_GPIO_Port GPIOB
#define NT53_Pin GPIO_PIN_9
#define NT53_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
