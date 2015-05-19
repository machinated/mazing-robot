/*
 * Serial port settings:
 * 4800 8N1
 */
#ifndef SERIAL_H
#define SERIAL_H

#include "def.h"

//#define BAUD 4800
#define USART_UBRR F_CPU/16/BAUD-1

void initSerial(unsigned int ubrr);
void serialSendChar(char data);
void serialSendStr(char* str);
void serialSendInt(int reg, int8_t last);
void sendSensors();

#endif	// SERIAL_H
