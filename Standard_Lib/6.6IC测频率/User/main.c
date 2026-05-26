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
	uint32_t i;
	PWM_SetPrescaler(720 - 1);			
	//PWM频率Freq = 72M / (PSC + 1) / 100
	PWM_SetCompare1(50);				
	//PWM占空比Duty = CCR / 100
	while(1)
	{
		for(i=0;i<=720000;i++)
		{
			PWM_SetPrescaler(i);
			OLED_ShowNum(2,1,IC_GetFrequency(),6);
		}
	}
}

