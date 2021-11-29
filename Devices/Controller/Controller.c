#include "Controller.h"

int8_t index = 0;
int8_t processing = 0;
uint8_t buffer[8];
uint8_t msg[11];
Status status = {
        1,
        {0,0,0,0,0,0,0,0,0},
        0,
        {0,0,0,0,0,0,0,0,0},
        0,
        0,
        0
};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//    HAL_UART_Transmit(&huart2,buffer,1,10);
    if(processing) return;
    if(buffer[0] == '&' || index>10) index = 0;
    msg[index++] = buffer[0];
    if(buffer[0] == '.') {
        for(uint8_t i=index; i<11; i++) msg[i]='.';
        processing = 1;
    }
}

void processMsg() {
    if(!processing) return;
    switch (msg[1]) {
        case '1':
            status.lightOn = msg[3]-'0';
            break;
        case '2':
            status.time = calendar;
            status.time.hour = (msg[3]-'0')*10 + msg[4]-'0';
            status.time.min = (msg[6]-'0')*10 + msg[7]-'0';
            status.time.sec = 0;
            setDatetime(&status.time);
            break;
        case '3':
            if(status.displayState == 0)
                status.displayState = (msg[3]-'0'<2?msg[3]-'0':1);
            else
                status.displayState = msg[3]-'0'<4?msg[3]-'0':0;
            break;
        case '4':
            status.counter = countDown;
            status.counter.hour = (msg[3]-'0')*10 + msg[4]-'0';
            status.counter.min = (msg[6]-'0')*10 + msg[7]-'0';
            status.counter.sec = 0;
            countDown = status.counter;
            status.displayState = 1;
            break;
        case '5':
            status.autoOff = msg[3]-'0';
            break;
        case '6':
            break;
        case '7':
            status.time = alarm;
            status.time.hour = (msg[3]-'0')*10 + msg[4]-'0';
            status.time.min = (msg[6]-'0')*10 + msg[7]-'0';
            alarm = status.time;
            break;
    }
    HAL_UART_Transmit(&huart2, msg, index, 30);
    index = 0; processing = 0;
}