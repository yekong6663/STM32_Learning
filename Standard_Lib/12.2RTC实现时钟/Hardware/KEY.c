#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef Key;
	Key.GPIO_Mode = GPIO_Mode_IPU;
	Key.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	Key.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&Key);

}

uint8_t NumberGet(void)
{
	uint8_t key_number=0;
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0 )
	{
		Delay_ms(20);
		while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0 );
		Delay_ms(20);
		key_number=1;
	}
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0 )
	{
		Delay_ms(20);
		while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0 );
		Delay_ms(20);
		key_number=2;
	}	
	return key_number;
}

