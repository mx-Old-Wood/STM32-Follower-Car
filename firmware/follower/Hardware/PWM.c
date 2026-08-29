#include "stm32f10x.h"                  // Device header

void PWM_SetCompare_Servos(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}

void PWM_SetCompare_Motor1(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}

void PWM_SetCompare_Motor2(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}
