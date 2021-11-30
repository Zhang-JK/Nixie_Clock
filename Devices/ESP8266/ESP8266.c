#include "ESP8266.h"
#include "usart.h"
#include "cmsis_os.h"
#include "DS3231.h"

//static volatile Calendar wifiTime;

static volatile char testDataW[200];
static volatile int testInt = 0;
char wifiData[2];
char wifiTime[15];
int wifiTimeCount = 0;
char wifiCheck[10];
int wifiCheckLen = 10;
int currectCheck = 0;
int checkTime = 0;
static volatile int flagWifi = 0;

void interruptCallback() {
    if(!checkTime) {
        testDataW[testInt++] = wifiData[0];
        if (wifiData[0] == wifiCheck[currectCheck])
            currectCheck++;
        if (currectCheck == wifiCheckLen) {
            flagWifi = 1;
            currectCheck = 0;
            testInt = 0;
        }
    }
    else if (checkTime == 1) {
        testDataW[testInt++] = wifiData[0];
        if (wifiData[0] == wifiCheck[currectCheck])
            currectCheck++;
        if (currectCheck == wifiCheckLen) {
            checkTime = 2;
        }
    }
    else if (checkTime == 2) {
        wifiTimeCount++;
        if(wifiTimeCount >= 4) wifiTime[wifiTimeCount-4] = wifiData[0];
        if(wifiTimeCount >= 22) {checkTime=1; flagWifi=1; testInt = 0;}
    }
}

int sendCommand(char *cmd, int clen, char* ack, int alen, int timeout) {
    if(HAL_UART_Transmit(&huart4, cmd, clen, clen*3) == HAL_OK) {
        for(int i=0; i<alen; i++) wifiCheck[i] = ack[i];
        wifiCheckLen = alen;
        HAL_UART_Receive_IT(&huart4, wifiData, 1);
        while (timeout--) {
            if(flagWifi) { flagWifi=0; return 1; }
            osDelay(1);
        }
    }
    return 0;
}

static volatile int connectState = 0;
int startTimeSever() {
    connectState = 0;
    while(!sendCommand("AT\r\n", 4, "OK", 2, 1)) osDelay(1);
//    connectState = 0;
//    while(!sendCommand("AT+RST\r\n", 8, "OK", 2, 5)) osDelay(1);
    connectState = 1;
    while(!sendCommand("AT+CWJAP=\"JK IPXR\",\"bzgzjrjtcsm\"\r\n", 34, "OK", 2, 10)) osDelay(1);
    connectState = 2;
    while(!sendCommand("AT+CIPMODE=1\r\n", 14, "OK", 2, 10)) osDelay(1);
    connectState = 3;
    while(!sendCommand("AT+CIPSTART=\"TCP\",\"api.k780.com\",80\r\n", 37, "OK", 2, 15)) osDelay(1);
    connectState = 4;
    while(!sendCommand("AT+CIPSEND\r\n", 12, "OK", 2, 1)) osDelay(1);
    connectState = 5;
    checkTime = 1;
}

int getTime() {
    sendCommand("GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json&HTTP/1.1\r\n", 116, "datetime_1", 10, 1);
}
