/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NixieTube.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId blinkHandle;
osThreadId ds3231Handle;
osThreadId NixieControllerHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Blink(void const * argument);
void ds3231Timer(void const * argument);
void nixieControl(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of blink */
  osThreadDef(blink, Blink, osPriorityLow, 0, 128);
  blinkHandle = osThreadCreate(osThread(blink), NULL);

  /* definition and creation of ds3231 */
  osThreadDef(ds3231, ds3231Timer, osPriorityHigh, 0, 256);
  ds3231Handle = osThreadCreate(osThread(ds3231), NULL);

  /* definition and creation of NixieController */
  osThreadDef(NixieController, nixieControl, osPriorityRealtime, 0, 256);
  NixieControllerHandle = osThreadCreate(osThread(NixieController), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Blink */
/**
  * @brief  Function implementing the blink thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Blink */
void Blink(void const * argument)
{
  /* USER CODE BEGIN Blink */
    // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    /* Infinite loop */
    for (;;) {
        // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);
        osDelay(300);
    }
  /* USER CODE END Blink */
}

/* USER CODE BEGIN Header_ds3231Timer */
/**
* @brief Function implementing the ds3231 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ds3231Timer */
void ds3231Timer(void const * argument)
{
  /* USER CODE BEGIN ds3231Timer */
    /* Infinite loop */
    for (;;) {
        HAL_I2C_Mem_Read_DMA(&hi2c1,DS3231_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,DS3231_Receivebuff,19);
        osDelay(999);
    }
  /* USER CODE END ds3231Timer */
}

/* USER CODE BEGIN Header_nixieControl */
/**
* @brief Function implementing the NixieController thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_nixieControl */
void nixieControl(void const * argument)
{
  /* USER CODE BEGIN nixieControl */
    static volatile NixieTube tube;
    setGPIO(&tube, nixiePorts[1], nixiePins[1]);
    static volatile int number=0;
    /* Infinite loop */
    for (;;) {
        setNumber(&tube, number);
        osDelay(1000);
        number = ++number % 10;
    }
  /* USER CODE END nixieControl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
