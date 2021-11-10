#include "Buzzer.h"

uint16_t springFes[30][2] = {
        {M3, 2}, {M2, 4}, {M3, 2}, {M5, 2}, {M5, 4}, {M6, 2},
        {H1, 4}, {M6, 2}, {H3, 2}, {H1, 8},
        {H3, 2}, {M7, 4}, {M6, 2}, {M5, 2}, {M3, 4}, {M5, 2},
        {M6, 3}, {M5, 1}, {M6, 4}, {M5, 8},
        {M5, 3}, {M6, 1}, {H1, 4}, {M6, 2}, {H1, 4}, {H2, 2},
        {H1, 4}, {M6, 2}, {M5, 2}, {M3, 8}
};

void turnPassiveBeep(TIM_HandleTypeDef *htim, uint32_t channel, int freq);

void setPWMOutput(MusicPlayer *obj, TIM_HandleTypeDef *htim, uint32_t channel) {
    obj->htim = htim;
    obj->channel = channel;
    obj->lastTick = HAL_GetTick();
    obj->index = 0;
}

void setMusicSheet(MusicPlayer *obj, uint8_t baseTime, uint32_t size) {
    obj->baseTime = baseTime;
    obj->size = size;
}

void setIndex(MusicPlayer *obj, float percentage) {
    obj->index = obj->size * percentage;
}

void playMusic(MusicPlayer *obj) {
    if (obj->index >= obj->size)
        obj->index = 0;

    if (HAL_GetTick() == obj->lastTick) {
        turnPassiveBeep(obj->htim, obj->channel, springFes[0][0]);
        return;
    }

    if (HAL_GetTick() - obj->lastTick >= obj->baseTime * springFes[obj->index][1]) {
        obj->index++;
        if (obj->index >= obj->size) {
            obj->index = 0;
            turnPassiveBeep(obj->htim, obj->channel, 0);
            osDelay(1000);
        }
        turnPassiveBeep(obj->htim, obj->channel, springFes[obj->index][0]);
        obj->lastTick = HAL_GetTick();
    }
}

void turnPassiveBeep(TIM_HandleTypeDef *htim, uint32_t channel, int freq) {
    int range;
    if (freq < 100 || freq > 5000) {
        HAL_TIM_PWM_Stop(htim, channel);
        return;
    }

    /* Set PWM clock: 32MHz/64 = 500KHz */
    htim->Init.Prescaler = 64 - 1;

    /* Set PWM frequency */
    range = 500000 / freq;
    htim->Init.Period = range;
    if (HAL_TIM_PWM_Init(htim) != HAL_OK) {
        Error_Handler();
    }
    /* Set PWM duty 50% */
    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (htim->Init.Period / 3);
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel) != HAL_OK) {
        Error_Handler();
    }
    HAL_TIM_MspPostInit(htim);
    HAL_TIM_PWM_Start(htim, channel);
}