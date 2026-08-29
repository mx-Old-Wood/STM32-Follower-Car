#include "Headfile.h"
#include "Key.h"

uint8_t KeyNum = 10;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	Key_Init();
	LED_Init();
	Encoder1_Init();
	Encoder2_Init();
	Servos_Init();
	PID_Init();
	Motor_Init();
	Buzzer_Init();
	Infrared_Init();
	Ultrasound_Init();
	Serial_Init();
	Timer1_Init();
	Timer4_Init();
	OLED_ShowString(1, 1, "S_Dis:");
	OLED_ShowString(1, 12, "mm");
	OLED_ShowString(2, 1, "Stop:");
	OLED_ShowString(2, 9, "Mode:");
	OLED_ShowString(4, 1, "Dis:");
	OLED_ShowString(4, 10, "mm");
	while(1) 
	{
		Display();
		if (Detection())
		{
			Mode(Modes, Set1, Set2);
		}
	}
}
