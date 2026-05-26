#include "stm32f10x.h"                  // Device header
void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	TIM_TimeBaseInitTypeDef TimeBaseStruct;
	TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseStruct.TIM_Period = 65536-1;
	TimeBaseStruct.TIM_Prescaler = 1-1;
	TimeBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TimeBaseStruct);
	
	TIM_ICInitTypeDef ICStruct;
	TIM_ICStructInit(&ICStruct);
	ICStruct.TIM_Channel = TIM_Channel_1;
	ICStruct.TIM_ICFilter = 0xF;
	ICStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInit(TIM3,&ICStruct);
	ICStruct.TIM_Channel = TIM_Channel_2;
	ICStruct.TIM_ICFilter = 0xF;
	ICStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInit(TIM3,&ICStruct);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_GetSpeed(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;
}
