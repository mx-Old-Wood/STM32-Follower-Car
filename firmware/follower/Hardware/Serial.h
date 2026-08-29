#ifndef _SERIAL_H
#define _SERIAL_H
#include "Headfile.h"

extern char Serial_RxPacket[100];



void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number,uint8_t Length);
void Serial_SendData(uint32_t Dis, uint32_t Flag, uint8_t D_Len, uint8_t F_Len);
void Serial_Printf(char *format,...);
uint8_t Serial_GetRxFlag(void);
void USART1_IRQHandler(void);
uint32_t transit(char*arr);



#endif

