#include "Headfile.h"

#define K  6.5 * 3.1415926 / 0.01 / 260                              //轮直径 * Pi / 单位时间 / 电机一圈输出的脉冲数(编码器线速 * 减速比)
uint16_t Timer4_Count = 0;
float Speed1 = 0, Speed2 = 0;                                        //速度 = 轮一圈前进的距离 / 前进一圈所需的时间  = 轮周长 * (计数N / 脉冲数) / 单位时间
unsigned short int Time = 0;
int set1 = 0, set2 = 0;

void Timer1_Init(void)
{
	Time = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_InternalClockConfig(TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;               //定义Timer1对应结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //晶振时钟分频(即晶振要以多少频率向定时器输入时钟信号),此处不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //定时器计数方式,此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 7200 - 1;                 //ARR重装器的重装值(自动重装载寄存器),即定时器计数的周期(定时器重装值)计数到多少定时器重装,取值为0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;                 //PSC预分频器的值,即将晶振频率分减(输入频率=晶振频率/PSC的值),取值为0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;             //重复计数器的值(高级定时器才有)
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);              //初始化Timer1
    
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);                            //清除更新中断标志位,避免刚初始化完成就进入中断的问题
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);                       //启动更新中断到NVIC通路(打开定时器中断)
	                                                                 //100us定时中断
																	 
	NVIC_InitTypeDef NVIC_InitStructure;                             //定义NVIC结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;               //启用Timer1中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  //指定中断通道是使能还是失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;        //指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;               //指定响应优先级
	NVIC_Init(&NVIC_InitStructure);                                  //初始化NIVC
	
	TIM_Cmd(TIM1, ENABLE);                                           //使能TIM1
}

void Timer2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);             //启动APB1总线上Timer2的时钟
	TIM_InternalClockConfig(TIM2);                                   //将Timer2的时基单元由内部时钟驱动(默认情况下,自动使用内部时钟)
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;               //定义Timer2对应结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //晶振时钟分频(即晶振要以多少频率向定时器输入时钟信号),此处不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //定时器计数方式,此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                  //ARR重装器的重装值(自动重装载寄存器),即定时器计数的周期(定时器重装值)计数到多少定时器重装,取值为0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 10 - 1;                //PSC预分频器的值,即将晶振频率分减(输入频率=晶振频率/PSC的值),取值为0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;             //重复计数器的值(高级定时器才有)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);              //初始化Timer2
	
	TIM_OCInitTypeDef TIM_OCInitStructure;                           //定义输出比较结构体
	TIM_OCStructInit(&TIM_OCInitStructure);                          //将输出结构体成员全部初始化,防止因部分成员未初始化导致模块初始化失败或未完全初始化,之后再将想要修改的成员初始化即可
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                //将输出比较模式设置为PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;        //比较输出的极性,此处选择高极性,即不反转极性,以REF(参考电压)波形(设定的PWM波形)直接输出,反值则反转极性,以相反的REF波形输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    //比较输出状态,此处设置为输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                               //设置CCR(其决定PWM信号占空比)寄存器的值
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_Cmd(TIM2, ENABLE);                                           //使能TIMx外设
}

void Timer3_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);             //启动APB1总线上Timer3的时钟
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;               //定义Timer3对应结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //晶振时钟分频(即晶振要以多少频率向定时器输入时钟信号),此处不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //定时器计数方式,此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;                //ARR重装器的重装值(自动重装载寄存器),即定时器计数的周期(定时器重装值)计数到多少定时器重装,取值为0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;                //PSC预分频器的值,即将晶振频率分减(输入频率=晶振频率/PSC的值),取值为0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;             //重复计数器的值(高级定时器才有)
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);              //初始化Timer3

	TIM_OCInitTypeDef TIM_OCInitStructure;                           //定义输出比较结构体
	TIM_OCStructInit(&TIM_OCInitStructure);                          //将输出结构体成员全部初始化,防止因部分成员未初始化导致模块初始化失败或未完全初始化,之后再将想要修改的成员初始化即可
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                //将输出比较模式设置为PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;        //比较输出的极性,此处选择高极性,即不反转极性,以REF(参考电压)波形(设定的PWM波形)直接输出,反值则反转极性,以相反的REF波形输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    //比较输出状态,此处设置为输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;         	                      //设置CCR(其决定PWM信号占空比)寄存器的值
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);                         //将Timer3以比较输出结构体进行比较输出初始化
	TIM_Cmd(TIM3, ENABLE);                                           //使能TIMx外设
}

void Timer4_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;               //定义Timer4对应结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //晶振时钟分频(即晶振要以多少频率向定时器输入时钟信号),此处不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //定时器计数方式,此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                  //ARR重装器的重装值(自动重装载寄存器),即定时器计数的周期(定时器重装值)计数到多少定时器重装,取值为0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;                //PSC预分频器的值,即将晶振频率分减(输入频率=晶振频率/PSC的值),取值为0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;             //重复计数器的值(高级定时器才有)
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);              //初始化Timer4
    
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);                            //清除更新中断标志位,避免刚初始化完成就进入中断的问题
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);                       //启动更新中断到NVIC通路(打开定时器中断)
	                                                                 //100us定时中断
	NVIC_InitTypeDef NVIC_InitStructure;                             //定义NVIC结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                  //启用Timer4中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  //指定中断通道是使能还是失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;        //指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;               //指定响应优先级
	NVIC_Init(&NVIC_InitStructure);                                  //初始化NIVC
	
	TIM_Cmd(TIM4, ENABLE);                                           //使能TIM4
}

void TIM1_UP_IRQHandler()
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, Echo) == 1)
		{
			Time++;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		Timer4_Count++;
		if (Timer4_Count == 100)                                     //计数10ms 
		{
			Speed1 = Encoder_Count1 * K;
			Encoder_Count1 = 0;
			Speed2 = Encoder_Count2 * K;
			Encoder_Count2 = 0;
			if (GPIO_ReadInputDataBit(GPIOB, Q1) == 0 && Speed1 != 0)
				Speed1 = -Speed1;
			if (GPIO_ReadInputDataBit(GPIOB, Q2) == 0 && Speed2 != 0)
				Speed2 = -Speed2;
			Speed_Control1(set1);
			Speed_Control2(set2);
			Timer4_Count = 0;
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
