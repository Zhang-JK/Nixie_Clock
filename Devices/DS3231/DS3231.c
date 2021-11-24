#include <DS3231.h>
#include <stdio.h>

Calendar calendar;

uint8_t BCDtoBinary(uint8_t bcd) {
    return bcd - 6 * (bcd >> 4);
}

uint8_t binaryToBCD(uint8_t binary) {
    return binary + 6 * (binary / 10);
}

uint8_t getDatetime(Calendar *cal) {
    uint8_t DS3231Receive[19];
    if (HAL_I2C_Mem_Read(&hi2c2, DS3231_ADD << 1, 0, I2C_MEMADD_SIZE_8BIT, DS3231Receive, 19, 100) == HAL_OK) {
        cal->sec    = BCDtoBinary(DS3231Receive[0]);
        cal->min    = BCDtoBinary(DS3231Receive[1]);
        cal->hour   = BCDtoBinary(DS3231Receive[2]);
        cal->week   = BCDtoBinary(DS3231Receive[3]);
        cal->day    = BCDtoBinary(DS3231Receive[4]);
        cal->month  = BCDtoBinary(DS3231Receive[5]);
        cal->year   = BCDtoBinary(DS3231Receive[6]);
        cal->timestamp = HAL_GetTick();
        return 1;
    }
    return 0;
}

uint8_t setDatetime(Calendar *cal) {
    uint8_t DS3231Data[7];
    DS3231Data[0] = binaryToBCD(cal->sec);
    DS3231Data[1] = binaryToBCD(cal->min);
    DS3231Data[2] = binaryToBCD(cal->hour);
    DS3231Data[3] = binaryToBCD(cal->week);
    DS3231Data[4] = binaryToBCD(cal->day);
    DS3231Data[5] = binaryToBCD(cal->month);
    DS3231Data[6] = binaryToBCD(cal->year);
    HAL_I2C_Mem_Write(&hi2c2, DS3231_ADD << 1, 0, I2C_MEMADD_SIZE_8BIT, DS3231Data, 7, 1000);
}

void calToString(Calendar* cal, char *str) {
    sprintf(str, "%2lu-%2u-%2u %2u:%2u:%2u", cal->year, cal->month, cal->day, cal->hour, cal->min, cal->sec);
}