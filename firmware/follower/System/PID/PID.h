#ifndef __PID_H__
#define __PID_H__

typedef struct PID_Increment     //PID增量式
{
	float p;           //比例系数
	float i;           //积分系数
	float d;           //微分系数--上述三个变量为PID控制系数
	float set;         //设定值
	float actual;      //实际值
	float err;         //误差
	float l_err;       //上次的误差
	float ll_err;      //上上次的误差
	float increment;   //增量
	float proportion;  //比例
	float integral;    //积分项
	float differential;//微分项
	float out;         //输出
	float point_limits;//输出限度
	
}PID_Inc;

//增量式控制量▲u(k)对应的是近几次位置误差的增量，而不是对应与实际位置的偏差,没有误差累加

typedef struct PID_Positional     //PID位置式
{
	float p;           //比例系数
	float i;           //积分系数
	float d;           //微分系数--上述三个变量为PID控制系数
	int set;           //设定值
	int actual;        //实际值
	int err;           //误差
	int l_err;         //上次的误差
	int increment;     //增量
	int proportion;    //比例
	int integral;      //积分项
	int differential;  //微分项
	int out;           //输出
	int point_limits;  //积分限度
	
}PID_Pos;

//位置式PID是当前系统的实际位置，与你想要达到的预期位置的偏差，进行PID控制

extern PID_Inc Speed_Compute1, Speed_Compute2;

void PID_Increment(PID_Inc *PID);
 

#endif
