#include "Headfile.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(Motor_RCC, ENABLE);            //启动APB2总线上GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                  //将GPIO口的输出控制权交给定时器,因此使用复用推挽输出
	GPIO_InitStructure.GPIO_Pin = R_EN_OUT | L_EN_OUT;               //PA1-RPWM,PA2-LPWM
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 //将GPIO口的输出控制权交给定时器,因此使用复用推挽输出
	GPIO_InitStructure.GPIO_Pin = R_PH_OUT | L_PH_OUT;               //PA0-RDIR,PA3-LDIR
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO, &GPIO_InitStructure);
	//对于DRV8701其输出的PWM频率需达到16kHz以上才能正常驱动电机
	
//	RCC_APB2PeriphClockCmd(Motor_RCC, ENABLE);                       //启动APB2总线上GPIOA的时钟
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                  //将GPIO口的输出控制权交给定时器,因此使用复用推挽输出
//	GPIO_InitStructure.GPIO_Pin = FNA | FNB;                         //PA1-FNA,PA2-FNB
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(Motor_GPIO, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = R_IN1 | R_IN2 | L_IN3 | L_IN4;     //PA0-RDIR,PA3-LDIR
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(Motor_GPIO, &GPIO_InitStructure);
	
	Timer2_Init();
}

void Motor_SetSpeed1(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(Motor_GPIO, L_PH_OUT);                             //L_IN3 = 1
		PWM_SetCompare_Motor1(Speed);
	}
	else
	{
		GPIO_ResetBits(Motor_GPIO, L_PH_OUT);                           //L_IN3 = 0
		PWM_SetCompare_Motor1(-Speed);
	}
}

void Motor_SetSpeed2(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(Motor_GPIO, R_PH_OUT);                             //R_IN1 = 1
		PWM_SetCompare_Motor2(Speed);
	}
	else
	{
		GPIO_ResetBits(Motor_GPIO, R_PH_OUT);                           //R_IN1 = 0
		PWM_SetCompare_Motor2(-Speed);
	}
}

void Motor_Status(int set1, int set2)
{
	Motor_SetSpeed1(set1);
	Motor_SetSpeed2(set2);
}


void Forward(int set1, int set2)
{
	Servos_SetAngle(90);
//	Motor_Status(set1, set2);
	Set(set1, set2);
}

void Back(int set1, int set2)
{
	Servos_SetAngle(90);
//	Motor_Status(-set1, -set2);
	Set(-set1, -set2);
}

void Cease(void)
{
	Servos_SetAngle(90);
//	Motor_Status(0, 0);
	Set(0, 0);
}

void Left_Correction(int set1, int set2, float angle)
{
	Servos_SetAngle(angle);
//	Motor_Status(set1, set2);
	Set(set1, set2);
}

void Right_Correction(int set1, int set2, float angle)
{
	Servos_SetAngle(angle);
//	Motor_Status(set1, set2);
	Set(set1, set2);
}

void Left(int set1, int set2, float angle)
{
	Servos_SetAngle(angle);
//	Motor_Status(set1, 0);
	Set(set1, set2);
}

void Right(int set1, int set2, float angle)
{
	Servos_SetAngle(angle);
//	Motor_Status(0, set2);
	Set(set1, set2);
}
