#include "Headfile.h"                  // Device header

/**
  *  @brief		LED初始化
  *  @param		无
  *  @retval	无
  **/

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  *  @brief		LED0控制
  *  @param		参数1:电平1或0(当参数2(Flip为0)),参数2:翻转LED电平
  *  @retval	无
  **/

void LED0_Set(uint8_t Level, uint8_t Flip)
{
	if (Flip == 0)
	{
		if (Level == 1)
			GPIO_SetBits(GPIOB, LED0);
		else if (Level == 0)
			GPIO_ResetBits(GPIOB, LED0);	
	}
	else if (Flip == 1)
	{
		if (GPIO_ReadOutputDataBit(GPIOB, LED0) == 0)
			GPIO_SetBits(GPIOB, LED0);
		else
			GPIO_ResetBits(GPIOB, LED0);
	}
}

/**
  *  @brief		LED1控制
  *  @param		参数1:电平1或0(当参数2(Flip为0)),参数2:翻转LED电平
  *  @retval	无
  **/

void LED1_Set(uint8_t Level, uint8_t Flip)
{
	if (Flip == 0)
	{
		if (Level == 1)
			GPIO_SetBits(GPIOC, LED1);
		else if (Level == 0)
			GPIO_ResetBits(GPIOC, LED1);	
	}
	else if (Flip == 1)
	{
		if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_5) == 0)
			GPIO_SetBits(GPIOC, LED1);
		else
			GPIO_ResetBits(GPIOC, LED1);		
	}
}
