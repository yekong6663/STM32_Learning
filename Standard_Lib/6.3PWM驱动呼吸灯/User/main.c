#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "LED.h"
#include  "PWM.h"
int main(void)
{	
	OLED_Init();
	PWM_Init();
	uint16_t i;
	OLED_ShowString(1,1,"Lightness:");
	while(1)
	{
		for(i=0;i<100;i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
			OLED_ShowNum(2,1,i,3);
		}
		for(i=100;i>0;i--)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
			OLED_ShowNum(2,1,i,3);
		}
	}
}
 
