#include "stm32f10x.h"                  // Device header
uint16_t count_number;

void Infraredsensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStruct.GPIO_Pin = GPIO_Pin_14;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTIStruct;
	EXTIStruct.EXTI_Line = EXTI_Line14 ;
	EXTIStruct.EXTI_LineCmd = ENABLE ;
	EXTIStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTIStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVICStruct;
	NVICStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVICStruct.NVIC_IRQChannelCmd = ENABLE;
	NVICStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVICStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVICStruct);
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
		{
			count_number++;
			EXTI_ClearITPendingBit(EXTI_Line14);
		}
	}
}
uint8_t GetCountNumber(void)
{
	return count_number;
}
