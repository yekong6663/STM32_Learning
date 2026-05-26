#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "KEY.h"
#include  "Servo.h"
int main(void)
{	
	OLED_Init();
	Servo_Init();
	Key_Init();
	OLED_ShowString(1,1,"Angle:");
	float angle=0;
	
	while(1)
	{
		if(Key_NumberGet() == 1)
		{
			angle+= 30;
			if(angle > 180)
				angle = 0;	
		}
		Servo_SetAngle(angle);
		OLED_ShowNum(1,7,angle,3);
	}
}
 
