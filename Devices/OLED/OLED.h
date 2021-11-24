#ifndef NIXIECLOCK_OLED_H
#define NIXIECLOCK_OLED_H

#include "main.h"
#include "spi.h"
#include "cmsis_os.h"

#define MAX_LEN    128  // max pixels
#define OLED_CMD   1
#define OLED_DATA  0

enum Font_Size {SMALL = 6, BIG = 16};
enum Num_Size {SMALL_NUM = 24 , MEDIA_NUM = 32 , BIG_NUM = 40};
enum DIRECTION { LEFT = 0x27 , RIGHT = 0x26,UP=0x29,DAWN=0x2a};

// function phototypes
// basic operation function
void OLED_Write_Byte(uint8_t data , uint8_t cmd);
void OLED_Init(void);
void OLED_On(void);
void OLED_Off(void);
void OLCD_Set_Pos(uint8_t x, uint8_t y);

void OLED_Ascii_Test(void);

// display functions
void OLED_Clear(void);
void OLED_Show_Char(uint8_t x, uint8_t y , uint8_t chr , enum Font_Size size);
void OLED_Show_String(uint8_t x, uint8_t y , char *chr , enum Font_Size size);
void OLED_Show_Icon(uint8_t x, uint8_t y , uint8_t index);

#endif //NIXIECLOCK_OLED_H
