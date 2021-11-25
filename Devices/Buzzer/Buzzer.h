#ifndef NIXIECLOCK_BUZZER_H
#define NIXIECLOCK_BUZZER_H

#include "tim.h"
#include "MusicSheets.h"
#include "cmsis_os.h"

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    uint8_t baseTime;
    uint32_t size;
    uint32_t index;
    uint64_t lastTick;
} MusicPlayer;

void setPWMOutput(MusicPlayer* obj, TIM_HandleTypeDef *htim, uint32_t channel);
void setMusicSheet(MusicPlayer* obj, uint8_t baseTime, uint32_t size);
void setIndex(MusicPlayer* obj, float percentage);
void playMusic(MusicPlayer* obj);
void stopMusic(MusicPlayer *obj);

#endif //NIXIECLOCK_BUZZER_H
