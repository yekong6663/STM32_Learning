#include "stm32f10x.h"                  // Device header
void BuzzerInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStruct.GPIO_Pin = GPIO_Pin_12;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);

}
void BuzzerOn(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void BuzzerOff(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

