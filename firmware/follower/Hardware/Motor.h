#ifndef __MOTOR_H__
#define __MOTOR_H__

void Motor_Init(void);
void Motor_SetSpeed1(int8_t Speed);
void Motor_SetSpeed2(int8_t Speed);
void Motor_Status(int set1, int set2);

void Forward(int set1, int set2);
void Back(int set1, int set2);
void Cease(void);
void Left_Correction(int set1, int set2, float angle);
void Right_Correction(int set1, int set2, float angle);
void Left(int set1, int set2, float angle);
void Right(int set1, int set2, float angle);

#endif
