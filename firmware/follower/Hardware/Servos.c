#include "Headfile.h"                  // Device header

void Servos_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);         //启动APB2总线上GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	Timer3_Init();
}

// 500-0°, 2500-180°

void Servos_SetAngle(float Angle)
{
	PWM_SetCompare_Servos(Angle / 180 * 2000 + 500);
}
