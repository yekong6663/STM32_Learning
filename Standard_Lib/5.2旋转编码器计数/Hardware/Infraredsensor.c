#include "stm32f10x.h"                  // Device header
int16_t count_number;

void Infraredsensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	
	EXTI_InitTypeDef EXTIStruct;
	EXTIStruct.EXTI_Line = EXTI_Line1 | EXTI_Line0;
	EXTIStruct.EXTI_LineCmd = ENABLE ;
	EXTIStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTIStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVICStruct;
	NVICStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVICStruct.NVIC_IRQChannelCmd = ENABLE;
	NVICStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVICStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVICStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVICStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVICStruct.NVIC_IRQChannelCmd = ENABLE;
	NVICStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVICStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVICStruct);
}
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				count_number--;
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
	}
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
				count_number++;
			EXTI_ClearITPendingBit(EXTI_Line1);
		}
	}
}
int16_t GetCountNumber(void)
{
	int16_t temp;
	temp=count_number;
	count_number=0;
	return temp;
}
