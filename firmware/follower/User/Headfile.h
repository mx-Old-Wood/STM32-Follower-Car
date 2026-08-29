#ifndef __HEADFILE_H__
#define __HEADFILE_H__

#pragma diag_suppress 167

#define OUT1 GPIO_Pin_8
#define OUT2 GPIO_Pin_15
#define OUT3 GPIO_Pin_14
#define OUT4 GPIO_Pin_13
#define OUT5 GPIO_Pin_12                //红外循迹
#define Buzzer GPIO_Pin_5               //蜂鸣器
#define LED0 GPIO_Pin_4
#define LED1 GPIO_Pin_13
#define Motor_RCC RCC_APB2Periph_GPIOA
#define Motor_GPIO GPIOA
#define R_PH_OUT GPIO_Pin_0
#define R_EN_OUT GPIO_Pin_1
#define L_EN_OUT GPIO_Pin_2
#define L_PH_OUT GPIO_Pin_3             //电机-drv8701
#define FNA GPIO_Pin_1
#define FNB GPIO_Pin_2
#define R_IN1 GPIO_Pin_11
#define R_IN2 GPIO_Pin_12
#define L_IN3 GPIO_Pin_0
#define L_IN4 GPIO_Pin_3
#define Q1 GPIO_Pin_10
#define Q2 GPIO_Pin_11                  //D触发器
#define Ultrasound_RCC RCC_APB2Periph_GPIOB
#define Echo GPIO_Pin_0
#define Trig GPIO_Pin_1                 //超声波


#include "Speed_Control.h"
#include "Ultrasound.h"
#include "stm32f10x.h"                  // Device header
#include "Infrared.h"
#include "Encoder.h"
#include "Servos.h"
#include "Buzzer.h"
#include "stdarg.h"
#include "string.h"
#include "Serial.h"
#include "stdio.h"
#include "Motor.h"
#include "Delay.h"
#include "Timer.h"
#include "OLED.h"
#include "Mode.h"
#include "Math.h"
#include "PID.h"
#include "LED.h"
#include "PWM.h"

#endif

