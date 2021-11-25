#include "IFSensor.h"

uint8_t getSensorState() {
    return HAL_GPIO_ReadPin(SENSOR_GPIO_Port, SENSOR_Pin) == GPIO_PIN_SET;
}