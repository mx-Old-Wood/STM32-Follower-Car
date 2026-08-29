#ifndef __INFRARED_H__
#define __INFRARED_H__

#include "Headfile.h"

#define IN1 GPIO_ReadInputDataBit(GPIOA, OUT1)
#define IN2 GPIO_ReadInputDataBit(GPIOB, OUT2)
#define IN3 GPIO_ReadInputDataBit(GPIOB, OUT3)
#define IN4 GPIO_ReadInputDataBit(GPIOB, OUT4)
#define IN5 GPIO_ReadInputDataBit(GPIOB, OUT5)

extern unsigned char finish;

void Infrared_Init(void);
void Infrared_Judgment_Inside(uint8_t set1, uint8_t set2);
void Infrared_Judgment_Outside(uint8_t set1, uint8_t set2);

#endif
