#ifndef __NIXIETUBE_H
#define	__NIXIETUBE_H

#include <main.h>
#include <gpio.h>
#include <cmsis_os.h>

typedef enum  {
    NIXIE_0 = 0,
    NIXIE_1,
    NIXIE_2,
    NIXIE_3,
    NIXIE_4,
    NIXIE_5,
    NIXIE_6,
    NIXIE_7,
    NIXIE_8,
    NIXIE_9,
    NIXIE_NULL
} NixieState;

typedef struct
{
    GPIO_TypeDef * portDef[4];
    uint16_t pinDef[4];
    uint8_t number;
} NixieTube;

extern GPIO_TypeDef *nixiePorts[6][4];
extern uint16_t nixiePins[6][4];

void setGPIO(NixieTube* obj, GPIO_TypeDef * ports[4], const uint16_t pins[4]);
void setNumber(NixieTube* obj, NixieState number);

#endif