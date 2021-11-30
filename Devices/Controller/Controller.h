#ifndef NIXIECLOCK_CONTROLLER_H
#define NIXIECLOCK_CONTROLLER_H

#include "main.h"
#include "usart.h"
#include "DS3231.h"

typedef struct {
    uint8_t lightOn;
    Calendar time;
    // 0 for time 1 for ready 2 for start 3 for pause 4 for stop
    uint8_t displayState;
    Calendar counter;
    uint8_t autoOff;
    uint8_t netUpdate;
    uint8_t alarmUpdate;
} Status;

extern uint8_t msg[15];
extern uint8_t buffer[8];
extern Status status;

void processMsg();

#endif //NIXIECLOCK_CONTROLLER_H
