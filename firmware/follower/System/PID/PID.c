#include "Headfile.h"

PID_Inc Speed_Compute1, Speed_Compute2;

/**
  *  @brief  PID增量式公式
  *  @param  无
  *  @retval 传入要运算的PID对象指针
  *  @memo   增量式中,P-稳定性,I-快速性,D-准确性,一般按顺序给I,P
  **/

void PID_Increment(PID_Inc *PID)         //括号内是指将PID_Inc结构体变量指向指针变量PID,所以下属代码使用->指向指针变量的子个体,而不是使用正常结构体所使用的.来指向结构体
{
	PID -> err = PID -> set - PID -> actual;                                           //误差 = 设置 - 实际
	 
	PID -> proportion = PID -> p * (PID -> err - PID -> l_err);                        //比例 = PID控制系数p(比例) * (误差 - 上次的误差)
	 
	PID -> integral = PID -> i * PID -> err;                                           //积分 = PID控制系数i(积分) * 误差
	
	PID -> differential = PID -> d * (PID -> err - 2 * PID -> l_err + PID -> ll_err);  //微分 = PID控制系数d(微分) * (误差 - 2 * 上次的误差 + 上上次的误差)
	
	PID -> increment = PID -> proportion + PID -> integral + PID -> differential;      //增量 = 比例 + 微分 + 积分
	
	PID -> out += PID -> increment; //输出 = 增量求和
	if (PID -> out > PID -> point_limits)
		PID -> out = PID -> point_limits;
	else if (PID -> out < -PID -> point_limits)
		PID -> out = -PID -> point_limits;
	
	PID -> ll_err = PID -> l_err;   //误差交换
	
	PID -> l_err = PID -> err;
}//PID增量式



/*
 *「期望值是什么，与控制器没有关系」，而是与物理对象有关。更直接的原因是因为你使用了这个物理量做反馈，而期望值需要与反馈做差，此时期望值才有了物理意义。「期望值是什么取决于反馈值是什么。」
 * PID 控制作用中，比例作用是基础控制；微分作用是 用于加快系统控制速度；积分作用是用于消除静差。
 *
 */
