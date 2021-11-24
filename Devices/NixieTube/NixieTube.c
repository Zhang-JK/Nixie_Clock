#include "NixieTube.h"

uint8_t nixieMap[11][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
};

GPIO_TypeDef *nixiePorts[6][4] = {
        {NT00_GPIO_Port, NT01_GPIO_Port, NT02_GPIO_Port, NT03_GPIO_Port},
        {NT10_GPIO_Port, NT11_GPIO_Port, NT12_GPIO_Port, NT13_GPIO_Port},
        {NT20_GPIO_Port, NT21_GPIO_Port, NT22_GPIO_Port, NT23_GPIO_Port},
        {NT30_GPIO_Port, NT31_GPIO_Port, NT32_GPIO_Port, NT33_GPIO_Port},
        {NT40_GPIO_Port, NT41_GPIO_Port, NT42_GPIO_Port, NT43_GPIO_Port},
        {NT50_GPIO_Port, NT51_GPIO_Port, NT52_GPIO_Port, NT53_GPIO_Port},
};

uint16_t nixiePins[6][4] = {
        {NT00_Pin, NT01_Pin, NT02_Pin, NT03_Pin},
        {NT10_Pin, NT11_Pin, NT12_Pin, NT13_Pin},
        {NT20_Pin, NT21_Pin, NT22_Pin, NT23_Pin},
        {NT30_Pin, NT31_Pin, NT32_Pin, NT33_Pin},
        {NT40_Pin, NT41_Pin, NT42_Pin, NT43_Pin},
        {NT50_Pin, NT51_Pin, NT52_Pin, NT53_Pin}
};

void setGPIO(NixieTube *obj, GPIO_TypeDef *ports[4], const uint16_t pins[4]) {
    for (int i = 0; i < 4; i++) {
        obj->portDef[i] = ports[i];
        obj->pinDef[i] = pins[i];
    }
}

void setNumber(NixieTube *obj, NixieState number) {
    obj->number = number;
    static volatile int test = 0;
    for (int i = 0; i < 4; i++) {
        test = nixieMap[obj->number][3 - i];
        HAL_GPIO_WritePin(obj->portDef[i], obj->pinDef[i],
                          nixieMap[obj->number][3 - i] == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
}
