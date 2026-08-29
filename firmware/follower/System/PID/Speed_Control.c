#include "Headfile.h"

void PID_Init()
{
	Speed_Compute1.p = 1.85;              //比例系数        <= 2.65
	Speed_Compute1.i = 0.40;              //积分系数        <= 1.35
	Speed_Compute1.d = 0.0;               //微分系数--上述三个变量为PID控制系数
	Speed_Compute1.set = 0;               //设定值
	Speed_Compute1.actual = 0;            //实际值
	Speed_Compute1.err = 0;               //误差
	Speed_Compute1.l_err = 0;             //上次的误差
	Speed_Compute1.ll_err = 0;            //上上次的误差
	Speed_Compute1.increment = 0;         //增量
	Speed_Compute1.proportion = 0;        //比例
	Speed_Compute1.integral = 0;          //积分项
	Speed_Compute1.differential = 0;      //微分项
	Speed_Compute1.out = 0;               //输出
	Speed_Compute1.point_limits = 65;     //积分限度
	
	Speed_Compute2.p = 1.85;              //比例系数
	Speed_Compute2.i = 0.40;              //积分系数
	Speed_Compute2.d = 0.0;               //微分系数--上述三个变量为PID控制系数
	Speed_Compute2.set = 0;               //设定值
	Speed_Compute2.actual = 0;            //实际值
	Speed_Compute2.err = 0;               //误差
	Speed_Compute2.l_err = 0;             //上次的误差
	Speed_Compute2.ll_err = 0;            //上上次的误差
	Speed_Compute2.increment = 0;         //增量
	Speed_Compute2.proportion = 0;        //比例
	Speed_Compute2.integral = 0;          //积分项
	Speed_Compute2.differential = 0;      //微分项
	Speed_Compute2.out = 0;               //输出
	Speed_Compute2.point_limits = 65;     //积分限度
}

void Speed_Control1(int set)
{
	Speed_Compute1.set = set;
	Speed_Compute1.actual = Speed1;
	if (set == 0)
	{
		Motor_SetSpeed1(0);
		Speed_Compute1.out = 0;
		Speed_Compute1.err = 0;
		Speed_Compute1.l_err = 0;
		Speed_Compute1.ll_err = 0;
	}
	else
	{
		PID_Increment(&Speed_Compute1);
		Motor_SetSpeed1((int8_t)Speed_Compute1.out);
	}
}

void Speed_Control2(int set)
{
	Speed_Compute2.set = set;
	Speed_Compute2.actual = Speed2;
	if (set == 0)
	{
		Motor_SetSpeed2(0);
		Speed_Compute2.out = 0;
		Speed_Compute2.err = 0;
		Speed_Compute2.l_err = 0;
		Speed_Compute2.ll_err = 0;
	}
	else
	{
		PID_Increment(&Speed_Compute2);
		Motor_SetSpeed2((int8_t)Speed_Compute2.out);
	}
}

void Set(int S1, int S2)
{
	set1 = S1;
	set2 = S2;
}
