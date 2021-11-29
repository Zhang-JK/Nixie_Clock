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
#include "usart.h"
#include "tim.h"

#include "NixieTube.h"
#include "DS3231.h"
#include "Buzzer.h"
#include "OLED.h"
#include "Controller.h"
#include "IFSensor.h"

#include "stdio.h"
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
uint32_t blinkBuffer[ 128 ];
osStaticThreadDef_t blinkControlBlock;
osThreadId ds3231Handle;
uint32_t ds3231Buffer[ 128 ];
osStaticThreadDef_t ds3231ControlBlock;
osThreadId NixieControllerHandle;
uint32_t NixieControllerBuffer[ 128 ];
osStaticThreadDef_t NixieControllerControlBlock;
osThreadId musicHandle;
uint32_t musicBuffer[ 128 ];
osStaticThreadDef_t musicControlBlock;
osThreadId OLEDControllerHandle;
uint32_t OLEDControllerBuffer[ 128 ];
osStaticThreadDef_t OLEDControllerControlBlock;
osThreadId bluetoothHandle;
uint32_t bluetoothBuffer[ 256 ];
osStaticThreadDef_t bluetoothControlBlock;
osThreadId CountHandle;
uint32_t CountBuffer[ 128 ];
osStaticThreadDef_t CountControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Blink(void const * argument);
void ds3231Timer(void const * argument);
void nixieControl(void const * argument);
void mucisControl(void const * argument);
void oledController(void const * argument);
void btController(void const * argument);
void counter(void const * argument);

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
  osThreadStaticDef(blink, Blink, osPriorityLow, 0, 128, blinkBuffer, &blinkControlBlock);
  blinkHandle = osThreadCreate(osThread(blink), NULL);

  /* definition and creation of ds3231 */
  osThreadStaticDef(ds3231, ds3231Timer, osPriorityHigh, 0, 128, ds3231Buffer, &ds3231ControlBlock);
  ds3231Handle = osThreadCreate(osThread(ds3231), NULL);

  /* definition and creation of NixieController */
  osThreadStaticDef(NixieController, nixieControl, osPriorityRealtime, 0, 128, NixieControllerBuffer, &NixieControllerControlBlock);
  NixieControllerHandle = osThreadCreate(osThread(NixieController), NULL);

  /* definition and creation of music */
  osThreadStaticDef(music, mucisControl, osPriorityIdle, 0, 128, musicBuffer, &musicControlBlock);
  musicHandle = osThreadCreate(osThread(music), NULL);

  /* definition and creation of OLEDController */
  osThreadStaticDef(OLEDController, oledController, osPriorityBelowNormal, 0, 128, OLEDControllerBuffer, &OLEDControllerControlBlock);
  OLEDControllerHandle = osThreadCreate(osThread(OLEDController), NULL);

  /* definition and creation of bluetooth */
  osThreadStaticDef(bluetooth, btController, osPriorityHigh, 0, 256, bluetoothBuffer, &bluetoothControlBlock);
  bluetoothHandle = osThreadCreate(osThread(bluetooth), NULL);

  /* definition and creation of Count */
  osThreadStaticDef(Count, counter, osPriorityIdle, 0, 128, CountBuffer, &CountControlBlock);
  CountHandle = osThreadCreate(osThread(Count), NULL);

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
//        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);
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
//    static volatile Calendar cal = {23, 15, 0, 21, 11, 29, 1};
//    setDatetime(&cal);

    /* Infinite loop */
    for (;;) {
        getDatetime(&calendar);
        osDelay(300);
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
    static volatile NixieTube tube[6];
    for (int i = 0; i < 6; i++)
        setGPIO(&(tube[i]), nixiePorts[i], nixiePins[i]);
    static volatile int sensorCount = 0;
    int maxLeave = 60;

    /* Infinite loop */
    for (;;) {
        if (status.lightOn && getSensorState() == 0 && sensorCount < maxLeave * 10 + 100) sensorCount++;
        else sensorCount = 0;

        if (status.lightOn && (status.autoOff == 0 || sensorCount < maxLeave * 10)) {
            if (status.displayState == 0) {
                setNumber(&(tube[0]), calendar.sec % 10);
                setNumber(&(tube[1]), calendar.sec / 10);
                setNumber(&(tube[2]), calendar.min % 10);
                setNumber(&(tube[3]), calendar.min / 10);
                setNumber(&(tube[4]), calendar.hour % 10);
                setNumber(&(tube[5]), calendar.hour / 10);
            } else {
                setNumber(&(tube[0]), countDown.sec % 10);
                setNumber(&(tube[1]), countDown.sec / 10);
                setNumber(&(tube[2]), countDown.min % 10);
                setNumber(&(tube[3]), countDown.min / 10);
                setNumber(&(tube[4]), countDown.hour % 10);
                setNumber(&(tube[5]), countDown.hour / 10);
            }
        }
        else
            for (int i = 0; i < 6; i++) setNumber(&(tube[i]), NIXIE_NULL);
        osDelay(100);
    }
  /* USER CODE END nixieControl */
}

/* USER CODE BEGIN Header_mucisControl */
/**
* @brief Function implementing the music thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_mucisControl */
void mucisControl(void const * argument)
{
  /* USER CODE BEGIN mucisControl */
    static volatile MusicPlayer player;
    setPWMOutput(&player, &htim3, TIM_CHANNEL_4);
    setMusicSheet(&player, 100, 30);
    int startCount = 0;

    /* Infinite loop */
    for (;;) {
        if ((alarm.min == calendar.min && alarm.hour == calendar.hour && status.displayState == 0) ||
            (status.displayState == 4))
            startCount = 180 * 100;

        while (startCount > 0) {
            startCount--;
            playMusic(&player);
            if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == GPIO_PIN_RESET) {
                startCount = 0;
                stopMusic(&player);
                if (status.displayState == 0)
                    while (alarm.min != calendar.min - 1) osDelay(1000);
                else
                    status.displayState = 1;
            }
            osDelay(10);
        }

        stopMusic(&player);

        osDelay(1000);
    }
  /* USER CODE END mucisControl */
}

/* USER CODE BEGIN Header_oledController */
/**
* @brief Function implementing the OLEDController thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_oledController */
void oledController(void const * argument)
{
  /* USER CODE BEGIN oledController */
    OLED_Init();
    osDelay(500);
    OLED_On();
    osDelay(500);
    OLED_Show_String(20, 10, "Nixie Clock", BIG);
    osDelay(5000);
    /* Infinite loop */
    for (;;) {
        char date[21];
        if (status.displayState == 0)
            calToString(&calendar, date);
        else
            calToString(&countDown, date);
        char alarmShow[21];
        sprintf(alarmShow, "Alarm: %s, at %2d:%2d", alarm.hour == 0 && alarm.min == 0 ? "OFF" : " ON", alarm.hour,
                alarm.min);
        OLED_Show_String(31, 0, "Nixie Clock", SMALL);
        OLED_Show_String(15, 1, date, SMALL);
//        OLED_Show_String(5, 2, "BT  : NOT Connected", SMALL);
        OLED_Show_String(5, 2, alarmShow, SMALL);
        OLED_Show_String(5, 3, "WiFi: NOT Connected", SMALL);
        OLED_Show_String(5, 4, status.displayState == 0 ? "Mode: Clock" : "Mode: Counter", SMALL);
        OLED_Show_String(5, 4, status.displayState == 0 ? "Mode: Clock" : "Mode: Counter", SMALL);
        OLED_Show_String(100, 4, getSensorState() == 0 ? "N" : "Y", SMALL);
        OLED_Show_String(5, 5, "Last Instruction: ", SMALL);
        OLED_Show_String(20, 6, msg, SMALL);
        OLED_Show_String(56, 7, "Group 22 :)", SMALL);
        osDelay(200);
    }
  /* USER CODE END oledController */
}

/* USER CODE BEGIN Header_btController */
/**
* @brief Function implementing the bluetooth thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_btController */
void btController(void const * argument)
{
  /* USER CODE BEGIN btController */
    HAL_UART_Receive_IT(&huart2, buffer, 1);
    /* Infinite loop */
    for (;;) {
        processMsg();
        osDelay(100);
    }
  /* USER CODE END btController */
}

/* USER CODE BEGIN Header_counter */
/**
* @brief Function implementing the Count thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_counter */
void counter(void const * argument)
{
  /* USER CODE BEGIN counter */
    /* Infinite loop */
    for (;;) {
        if (status.displayState == 2) {
            if (countDown.sec == 0 && countDown.min == 0 && countDown.hour == 0) {
                status.displayState = 4;
            } else if (countDown.sec == 0 && countDown.min == 0) {
                countDown.hour -= 1;
                countDown.min = 59;
                countDown.sec = 59;
            } else if (countDown.sec == 0) {
                countDown.min -= 1;
                countDown.sec = 59;
            } else {
                countDown.sec -= 1;
            }
        }
        osDelay(1000);
    }
  /* USER CODE END counter */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
