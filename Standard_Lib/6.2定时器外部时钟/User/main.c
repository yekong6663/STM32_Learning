#include "stm32f10x.h"                  // Device header
#include  "Timer.h"
#include  "OLED.h"
uint16_t Number;
int main(void)
{	
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Count:");
	while(1)
	{
		OLED_ShowNum(1,7,Number,3);
	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		Number++;
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
}
