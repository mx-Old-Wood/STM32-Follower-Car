#include "Headfile.h"

uint16_t Dis = 0, Modes = 0, Stop = 1,Dis_t = 0, Modes_t = 0, Stop_t = 0, Distance = 0;
uint16_t Local_Distance = 0, Remote_Distance  = 0;
uint8_t Local_Valid = 0, Remote_Valid = 0;
uint8_t Last_Phase = 10, Car_Found = 0;
unsigned char Set1 = 40, Set2 = 40;

void Display(void)
{
	int8_t Text[11];
	if (Serial_GetRxFlag() == 1)
	{
		OLED_ShowString_Receive(4, 5, 2, 14, 2, 6, Serial_RxPacket);
		for (uint8_t i = 0; i < 8; i++)
		{
			if (i <= 3)
				Dis_t += (Serial_RxPacket[i] - '0') * pow(10, (3 - i));
			else if (i <=5 )
				Modes_t += (Serial_RxPacket[i] - '0') * pow(10, (5 - i));
			else
				Stop_t += (Serial_RxPacket[i] - '0') * pow(10, (7 - i));
		}
		Dis = Dis_t;
		Modes = Modes_t;
		Stop = Stop_t;
		Dis_t = 0;
		Modes_t = 0;
		Stop_t = 0;
		if (Dis >= DISTANCE_MIN && Dis <= DISTANCE_MAX)
		{
			Remote_Distance = Dis;
			Remote_Valid = 1;
		}
		else
			Remote_Valid = 0;
	}
	sprintf((uint8_t*)Text, "S1:%.1f ", Speed1);
	OLED_ShowString(3, 1, Text);
	sprintf((uint8_t*)Text, "S2:%.1f ", Speed2);
	OLED_ShowString(3, 9, Text);
	OLED_ShowNum(1, 7, Distance, 4);
}

void Local_Distance_Update(void)
{
	Distance = Ultrasound_Get();
    if (Distance >= DISTANCE_MIN && Distance <= DISTANCE_MAX)
    {
        Local_Distance = Distance;
        Local_Valid = 1;
    }
    else
        Local_Valid = 0;
}

void Distance_Phase_Update(void)
{
    uint8_t Phase;
    if (finish == 0)
        Phase = 0;
    else if (finish == 1)
        Phase = 1;
    else
        Phase = 2;
    if (Phase != Last_Phase)
    {
        Last_Phase = Phase;
        Car_Found = 0;
        if (Phase == 1)
            Remote_Valid = 0;
        else
            Local_Valid = 0;
    }
}

uint8_t Distance_Control(void)
{
    uint16_t Control_Distance;
    int Error;
    int Speed_Set;
    if (Modes == 2)
        Distance_Phase_Update();
    else
    {
        Last_Phase = 10;
        Car_Found = 0;
    }
	if (Modes == 2 && finish == 1)
	{
		if (Remote_Valid == 0)
		{
			if (Car_Found == 0)
			{
                Set1 = OVERTAKE_SPEED;
                Set2 = OVERTAKE_SPEED;
			}
			else
			{
                Set1 = BASE_SPEED;
                Set2 = BASE_SPEED;
			}
			return 1;
		}
		Car_Found = 1;
		Control_Distance = Remote_Distance;
		Error = (int)Control_Distance - DISTANCE_AIM;
		Speed_Set = BASE_SPEED - DISTANCE_KP * Error;
	}
	else
	{
		if (Local_Valid == 0)
		{
            if (Modes == 2 && finish >= 2 && Car_Found == 0)
            {
                Set1 = YIELD_SPEED;
                Set2 = YIELD_SPEED;
            }
			else
			{
				Set1 = BASE_SPEED;
				Set2 = BASE_SPEED;
			}
			return 1;
		}
		if (Modes == 2)
			Car_Found = 1;
        Control_Distance = Local_Distance;
        if (Control_Distance <= 180)
        {
            Cease();
            return 0;
        }
		Error = (int)Control_Distance - DISTANCE_AIM;
		Speed_Set = BASE_SPEED + DISTANCE_KP * Error;
	}
    if (Speed_Set > MAX_SPEED)
        Speed_Set = MAX_SPEED;
    else if (Speed_Set < MIN_SPEED)
        Speed_Set = MIN_SPEED;
    Set1 = Speed_Set;
    Set2 = Speed_Set;
    return 1;
}

uint8_t Detection(void)
{
	if (Stop == 0 && Remote_Distance  <= 250 && Remote_Valid == 1)
	{
		Cease();
		while (Stop == 0 && Remote_Distance  <= 250 && Remote_Valid == 1)
		{
			Display();
			Buzzer_Set(1);
		}
		return 0;
	}
	else if (Stop == 2)
	{
		Cease();
		while (Stop == 2)
			Display();
		return 0;
	}
	return Distance_Control();
}

void Mode(uint8_t Choose, int set1, int set2)
{
	if (Choose == 1)
	{
		Infrared_Judgment_Outside(set1, set2);
		Local_Distance_Update();
	}
	else if (Choose == 2)
	{
        if (finish == 1)
            Infrared_Judgment_Inside(set1, set2);
        else
            Infrared_Judgment_Outside(set1, set2);
        if (finish != 1)
            Local_Distance_Update();
	}
	else if (Choose == 3)
	{
		Infrared_Judgment_Outside(set1, set2);
		Local_Distance_Update();
	}
}
