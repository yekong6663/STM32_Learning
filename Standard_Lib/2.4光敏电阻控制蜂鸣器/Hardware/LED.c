#include "stm32f10x.h"                  // Device header
void LedInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);

}
void LedOn(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

void LedOff(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

