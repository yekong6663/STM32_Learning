#include "stm32f10x.h"                
#include  "Delay.h"
#include  "OLED.h"
#include  "Encoder.h"
#include  "Timer.h"
int16_t speed;
int main(void)
{	
	OLED_Init();
	Timer_Init();
	Encoder_Init(); 
	OLED_ShowString(1,1,"Speed:");
	while(1)
	{
		OLED_ShowSignedNum(1,7,speed,5);
	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		speed=Encoder_GetSpeed();
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
}
