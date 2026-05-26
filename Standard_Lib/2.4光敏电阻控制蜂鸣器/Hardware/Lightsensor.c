#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void LightsensorInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef Key;
	Key.GPIO_Mode = GPIO_Mode_IPU;
	Key.GPIO_Pin = GPIO_Pin_13;
	Key.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&Key);

}

uint8_t LightGet(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
