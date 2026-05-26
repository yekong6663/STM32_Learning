#include "stm32f10x.h"                  // Device header
#include  "Infraredsensor.h"
#include  "OLED.h"
#include  "Delay.h"
int main(void)
{	
	OLED_Init();
	Infraredsensor_Init();
	OLED_ShowString(1,1,"CountNumber:");
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	while(1)
	{
		OLED_ShowNum(1,13,GetCountNumber(),3);
		
		OLED_ShowString(2,1,"RUNNING");
		Delay_ms(300);
		OLED_ShowString(2,1,"       ");
		Delay_ms(300);
		
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
		SystemInit();
	}
}
 
