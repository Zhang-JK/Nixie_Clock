#ifndef NIXIE_CLOCK_ESP8266_H
#define NIXIE_CLOCK_ESP8266_H

// AT(OK, 1) -> AT+CWJAP="JK IPXR","bzgzjrjtcsm"(OK, 10) -> AT+CIPMODE=1(OK, 1)
// AT+CIPSTART="TCP","api.k780.com",80(OK, 5) -> AT+CIPSEND(>, 1)
// GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json&HTTP/1.1

int sendCommand(char *cmd, int clen, char* ack, int alen, int timeout);
void interruptCallback();
int startTimeSever();
int getTime();

extern char wifiData[2];
extern char wifiTime[15];

#endif //NIXIE_CLOCK_ESP8266_H
