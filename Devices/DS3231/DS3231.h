#ifndef __DS3231_H
#define	__DS3231_H

#include <main.h>
#include <i2c.h>
#include <gpio.h>
#include <cmsis_os.h>

// --------------- Receive Date Def ---------------
typedef struct 
{
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;			
	uint32_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  week;
	uint16_t temperature;
    uint32_t timestamp;
}Calendar;

// --------------- Register Address --------------

/* Time */
#define		DS3231_SECOND					0x00    // second
#define		DS3231_MINUTE      			    0x01    // minute
#define		DS3231_HOUR        				0x02    // hour
#define		DS3231_WEEK         			0x03    // week
#define		DS3231_DAY          			0x04    // day
#define		DS3231_MONTH                    0x05    // month
#define     DS3231_YEAR        				0x06    // year
/* Alarm 1 */          	
#define     DS3231_ALARM1_SECOND            0x07    // second
#define 	DS3231_ALARM1_MINUTE            0x08    // minute
#define     DS3231_ALARM1_HOUR              0x09    // hour
#define 	DS3231_ALARM1_WEEK  			0x0A    // week
/* Alarm 2 */
#define 	DS3231_ALARM2_MINUTE 			0x0b    // minute
#define 	DS3231_ALARM2_HOUR              0x0c    // hour
#define 	DS3231_ALARM2_WEEK              0x0d    // week
/* Control, State */
#define 	DS3231_CONTROL                  0x0e    // Control
#define 	DS3231_STATUS                   0x0f    // Status
#define 	DS3231_AGING        			0x10    // Aging offset
#define 	DS3231_TEMPERATURE_H 			0x11    // LSB of temp
#define 	DS3231_TEMPERATURE_L 			0x12    // MSB of temp
#define     DS3231_ADD                      0x68

extern Calendar calendar;

uint8_t getDatetime(Calendar* cal);
uint8_t setDatetime(Calendar* cal);

#endif