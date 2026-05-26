#include "stm32f10x.h"                
#include  "Delay.h"
#include  "OLED.h"
#include  "IC.h"
#include  "PWM.h"
int main(void)
{	
	OLED_Init();
	PWM_Init();
	IC_Init();
	OLED_ShowString(1,1,"Frequency:");
	OLED_ShowString(3,1,"Duty:");
	PWM_SetPrescaler(720 - 1);			
	//PWM频率Freq = 72M / (PSC + 1) / 100
	PWM_SetCompare1(50);				
	//PWM占空比Duty = CCR / 100
	while(1)
	{
		
		OLED_ShowNum(2,1,IC_GetFrequency(),6);
		OLED_ShowNum(4,1,IC_GetDuty(),6);
	}
}

