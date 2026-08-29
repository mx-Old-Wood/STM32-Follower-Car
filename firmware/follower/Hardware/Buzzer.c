#include "Headfile.h"

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Buzzer;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Buzzer_Set(uint8_t Modes)
{
	if (Modes == 0)
		GPIO_ResetBits(GPIOB, Buzzer);
	else if (Modes == 1)
		GPIO_SetBits(GPIOB, Buzzer);
}
