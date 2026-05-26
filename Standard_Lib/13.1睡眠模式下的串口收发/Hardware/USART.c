#include "stm32f10x.h"                  
uint8_t RxFlag;
uint8_t RxData;
void MyUSART_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStruct.GPIO_Pin = GPIO_Pin_10;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	USART_InitTypeDef USARTStruct;
	USARTStruct.USART_BaudRate = 9600;
	USARTStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTStruct.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;
	USARTStruct.USART_Parity = USART_Parity_No;
	USARTStruct.USART_StopBits = USART_StopBits_1;
	USARTStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USARTStruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVICStruct;
	NVICStruct.NVIC_IRQChannel = USART1_IRQn;
	NVICStruct.NVIC_IRQChannelCmd = ENABLE;
	NVICStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVICStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVICStruct);
	
	USART_Cmd(USART1,ENABLE);
}
void USART_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
void USART_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0 ;i<Length;i++)
		USART_SendByte(Array[i]);
}
void USART_SendString(uint8_t *Array)
{
	uint16_t i;
	for(i = 0 ;Array[i]!='\0';i++)
		USART_SendByte(Array[i]);
}
void USART_SendNumber(uint32_t Number)
{
	uint16_t temp=Number,constant=1;
	while(temp)
	{
		temp/=10;
		constant*=10;
	}
	constant/=10;
	while(constant)
	{
		USART_SendByte(Number/constant %10+'0');
		constant/=10;
	}
}
uint8_t USART_GetRxFlag(void)
{
	if( RxFlag==1)
	{
		RxFlag=0;
		return 1;
	}
	return 0;

}
uint8_t USART_GetRxData(void)
{
	return RxData;
}
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		RxData=USART_ReceiveData(USART1);
		RxFlag=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}

}
