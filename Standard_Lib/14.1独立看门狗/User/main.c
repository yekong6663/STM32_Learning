#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "KEY.h"
int main(void)
{	
	OLED_Init();
	Key_Init();
	
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(1, 1, "IWDGRST");
		Delay_ms(500);
		OLED_ShowString(1, 1, "       ");
		Delay_ms(100);
		
		RCC_ClearFlag();
	}
	else
	{
		OLED_ShowString(2, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "   ");
		Delay_ms(100);
	}
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2500-1);
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while(1)
	{
		
		NumberGet();
		
		IWDG_ReloadCounter();
		
		OLED_ShowString(3,1,"FEED");
		Delay_ms(500);
		OLED_ShowString(3,1,"       ");
		Delay_ms(400);
		
	}
}
 
