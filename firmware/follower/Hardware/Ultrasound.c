#include "Headfile.h"

uint16_t T = 0;

void Ultrasound_Init(void)                                      //Trig - B1, Echo - B0
{
	RCC_APB2PeriphClockCmd(Ultrasound_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = Trig;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = Echo;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOB, Trig);
}

void Ultrasound_Fired()
{
	GPIO_SetBits(GPIOB, Trig);
	Delay_us(45);
	GPIO_ResetBits(GPIOB, Trig);
//	Timer1_Init();
}

uint16_t Ultrasound_Get(void)
{
	Time = 0;
	Ultrasound_Fired();
	Delay_ms(20);
	return Time * 0.0001 * 340000 / 2;
}
