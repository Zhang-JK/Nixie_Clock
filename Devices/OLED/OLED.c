#include "OLED.h"
#include "font.h"

void OLED_Write_Byte(uint8_t data, uint8_t cmd) {
    if (cmd) HAL_GPIO_WritePin(SPI_DC_GPIO_Port, SPI_DC_Pin, GPIO_PIN_RESET);
    else HAL_GPIO_WritePin(SPI_DC_GPIO_Port, SPI_DC_Pin, GPIO_PIN_SET);

    HAL_SPI_Transmit(&hspi1, &data, sizeof(data), 1000);
    HAL_GPIO_WritePin(SPI_DC_GPIO_Port, SPI_DC_Pin, GPIO_PIN_SET);                                                      // 控制脚拉高，置成写数据状态
}

void OLED_On(void)
{
    OLED_Write_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_Write_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_Write_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void OLED_Off(void)
{
    OLED_Write_Byte(0X8D,OLED_CMD);  //SET DCDC命令
    OLED_Write_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_Write_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

void OLED_Init(void)
{
    HAL_GPIO_WritePin(SPI_RES_GPIO_Port, SPI_RES_Pin, GPIO_PIN_RESET);
    osDelay(500);
    HAL_GPIO_WritePin(SPI_RES_GPIO_Port, SPI_RES_Pin, GPIO_PIN_SET);

    OLED_Write_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_Write_Byte(0x02,OLED_CMD);//---set low column address
    OLED_Write_Byte(0x10,OLED_CMD);//---set high column address
    OLED_Write_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_Write_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_Write_Byte(0xff,OLED_CMD);// Set SEG Output Current Brightness
    OLED_Write_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_Write_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_Write_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_Write_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_Write_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_Write_Byte(0x00,OLED_CMD);//-not offset
    OLED_Write_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_Write_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_Write_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_Write_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_Write_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_Write_Byte(0x12,OLED_CMD);
    OLED_Write_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_Write_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_Write_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_Write_Byte(0x02,OLED_CMD);//
    OLED_Write_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_Write_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_Write_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_Write_Byte(0xA6,OLED_CMD);// 开启正常显示 (0xA6 = 正常 / 0xA7 = 反显)
    OLED_Write_Byte(0xAF,OLED_CMD);//--turn on oled panel

    OLED_Clear();
}

void OLED_Clear(void)
{
    uint8_t i,n;
    for(i=0; i<8; i++)
    {
        OLED_Write_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_Write_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_Write_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(n=0; n<128; n++)OLED_Write_Byte(0,OLED_DATA); // 每一列都置零
    }
}

void OLCD_Set_Pos(uint8_t x, uint8_t y)
{
    OLED_Write_Byte(0xb0+y,OLED_CMD);
    OLED_Write_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_Write_Byte((x&0x0f)|0x01,OLED_CMD);
}

void OLED_Ascii_Test()
{
    uint8_t i,j;
    for(j=0; j<160; j++) {
        OLCD_Set_Pos(j*6%120,j/20); // 设置显示位置
        for(i=0; i<6; i++)
        {
            OLED_Write_Byte(F6x8[j%90][i],OLED_DATA);
        }
    }
}

void OLED_Show_Char(uint8_t x, uint8_t y , uint8_t chr , enum Font_Size size)
{
    uint8_t i=0  ,c=0;
    c = chr - ' '; // 从空字符串算起，得到偏移后的值

    switch(size)
    {
        case SMALL:
            OLCD_Set_Pos(x,y); // 设置显示位置
            for(i=0; i< size ; i++)
                OLED_Write_Byte(F6x8[c][i],OLED_DATA);
            break;
        case BIG:
            OLCD_Set_Pos(x,y); // 设置显示位置
            for(i=0; i< 8 ; i++)
                OLED_Write_Byte(F8X16[c][i],OLED_DATA);
            OLCD_Set_Pos(x,y+1); // 设置显示位置
            for(i=8; i< 16 ; i++)
                OLED_Write_Byte(F8X16[c][i],OLED_DATA);
            break;
    }
}

void OLED_Show_String(uint8_t x, uint8_t y , char *chr , enum Font_Size size)
{
    uint8_t i = 0;
    uint8_t page =  (size>8 ? size >> 3 : 1 );  // 字体大小决定翻几页
    uint8_t len = (size>8 ? size >>1 : size ) ;   // 字体宽度，最后结果对应了字体表中的每行长度索引
    uint8_t limit = MAX_LEN/len - 1 ;
    while(chr[i] != '\0') {
        OLED_Show_Char(x,y,chr[i],size);
        x+=len; // 字体宽高 6*8
        if(x>(len*limit-1))    // 如果大于了极限值 128
        {
            x = 0 ;  //  列从零开始
            y += page;  //  另起一页
        }
        i ++ ;    // 循环继续，直到字符串都写完了为止
    }
}

//void OLED_Show_Icon(uint8_t x, uint8_t y , uint8_t index)
//{
//    uint8_t i,j ;
//    uint8_t len = 16  ;
//    uint8_t page = 2 ;
//
//    for(i = 0 ; i < page ; i ++)
//    {
//        OLCD_Set_Pos(x,y+i); // 设置显示位置
//        for(j=0; j<len; j++)
//            OLED_Write_Byte(ICON16[index*page + i][j],OLED_DATA);  // 写数据
//    }
//}