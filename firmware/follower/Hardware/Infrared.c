#include "Headfile.h"  

uint8_t detection = 0;
unsigned char finish = 0;

void Infrared_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = OUT1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = OUT2 | OUT3 | OUT4 | OUT5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Tracking_Service(void)
{
    Display();
    return Detection();
}

void Infrared_Judgment_Inside(uint8_t set1, uint8_t set2)
{
	if ((IN1 == 0 && IN3 == 0 && IN5 == 0) || (IN1 == 0 && IN2 == 0 && IN3 == 0) || (IN3 == 0 && IN4 == 0 && IN5 == 0))
	{
		Forward(set1, set2);
		while ((IN1 == 0 && IN3 == 0 && IN5 == 0) || (IN1 == 0 && IN2 == 0 && IN3 == 0) || (IN3 == 0 && IN4 == 0 && IN5 == 0));
		if ((IN1 == 1 && IN3 == 1 && IN5 == 1) || (IN1 == 1 && IN2 == 1 && IN3 == 1) || (IN3 == 1 && IN4 == 1 && IN5 == 1))
		{
			Forward(set1, set2);
			while ((IN1 == 0 && IN3 == 0 && IN5 == 0) || (IN1 == 0 && IN2 == 0 && IN3 == 0) || (IN3 == 0 && IN4 == 0 && IN5 == 0));
		}
		finish++;
	}
	else if (IN1 == 0)
	{
		Left(32, 26, 40);
		Delay_ms(20);
		while (IN2 == 1 &&  IN3 == 1)
		{
			if (Tracking_Service())
				Left(32, 26, 40);
		}
	}
	else if ((IN2 == 0 && IN3 == 1 && IN4 == 1) || (IN2 == 0 && IN3 == 0 && IN4 == 1) || (IN2 == 0 && IN3 == 1 && IN4 == 0))
	 {
		Left_Correction(35, 28, 62);
		Delay_ms(20);
		while (IN1 == 1 && IN3 == 1)
		{
			if (Tracking_Service())
				Left_Correction(35, 28, 62);
		}
	}
	else if (IN3 == 0)
	{
		Forward(set1, set2);
	}
	else if (IN4 == 0)
	{
		Right_Correction(28, 35, 118);
		Delay_ms(20);
		while (IN3 == 1 && IN5 == 1)
		{
			if (Tracking_Service())
				Right_Correction(28, 35, 118);
		}
	}
	else if (IN5 == 0)
	{
		Right(26 ,32, 140);
		Delay_ms(20);
		while (IN3 == 1 && IN4 == 1)
		{
			if (Tracking_Service())
				Right(26 ,32, 140);
		}
	}
	else if (IN1 == 1 && IN2 == 1 && IN3 == 1 && IN4 == 1 && IN5 == 1)
	{
		Forward(set1, set2);
	}
	else  
	{
		Forward(set1, set2);
	}
}

void Infrared_Judgment_Outside(uint8_t set1, uint8_t set2)
{
	if ((IN1 == 0 && IN3 == 0 && IN5 == 0) || (IN1 == 0 && IN2 == 0 && IN3 == 0) || (IN3 == 0 && IN4 == 0 && IN5 == 0))
	{
		Forward(set1, set2);
		while ((IN1 == 0 && IN3 == 0 && IN5 == 0) || (IN1 == 0 && IN2 == 0 && IN3 == 0) || (IN3 == 0 && IN4 == 0 && IN5 == 0));
		uint16_t i;
		for (i = 0; i < 50; i++)
		{
			if (Tracking_Service())
				Forward(set1, set2);

			Delay_ms(20);
		}
		finish++;
	}
	else if (IN1 == 0)
	{
		Left(32, 26, 40);
		Delay_ms(20);
		while (IN2 == 1 &&  IN3 == 1)
		{
			if (Tracking_Service())
				Left(32, 26, 40);
		}
	}
	else if (IN2 == 0 && IN3 == 1)
	{
		Left_Correction(35, 28, 62);
		Delay_ms(20);
		while (IN1 == 1 && IN3 == 1)
		{
			if (Tracking_Service())
				Left_Correction(35, 28, 62);
		}
	}
	else if (IN3 == 0)
	{
		Forward(set1, set2);
	}
	else if (IN4 == 0)
	{
		Right_Correction(28, 35, 118);
		Delay_ms(20);
		while (IN3 == 1 && IN5 == 1)
		{
			if (Tracking_Service())
				Right_Correction(28, 35, 118);
		}
	}
	else if (IN5 == 0)
	{
		Right(26 ,32, 140);
		Delay_ms(20);
		while (IN3 == 1 && IN4 == 1)
		{
			if (Tracking_Service())
				Right(26 ,32, 140);
		}
	}
	else if (IN1 == 1 && IN2 == 1 && IN3 == 1 && IN4 == 1 && IN5 == 1)
	{
		Forward(set1, set2);
	}
	else
	{
		Forward(set1, set2);
	}
}
