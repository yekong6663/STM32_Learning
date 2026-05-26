#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "KEY.h"
#include  "Motor.h"
int main(void)
{	
	OLED_Init();
	Motor_Init();
	Key_Init();
	int16_t velocity;
	OLED_ShowString(1,1,"Velocity:");
	while(1)
	{
		if(NumberGet() == 1)
		{
			velocity +=20;
			if(velocity >= 100)
				velocity = -100;
		}
		Motor_SetVelocity(velocity);
		OLED_ShowSignedNum(2, 1, velocity, 3);
	}
}

