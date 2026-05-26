#include "stm32f10x.h"                  // Device header
#include  "Delay.h"

int main(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOStructure = {0};
	
	GPIOStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStructure.GPIO_Pin = GPIO_Pin_All;
	GPIOStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOStructure);
	
	while(1)
	{
		GPIO_Write(GPIOA,0x0001); //0000 0000 0000 0001
		Delay_ms(100);
		GPIO_Write(GPIOA,0x0002); //0000 0000 0000 0010
		Delay_ms(100);                                                                                                                                                             
		GPIO_Write(GPIOA, ~0x0004);	//0000 0000 0000 0100
		Delay_ms(100);				
		GPIO_Write(GPIOA, ~0x008);	//0000 0000 0001 0000
		Delay_ms(100);				
		GPIO_Write(GPIOA, ~0x0010);	//0000 0000 0010 0000
		Delay_ms(100);				
		GPIO_Write(GPIOA, ~0x0020);	//0000 0000 0100 0000
		Delay_ms(100);				
		GPIO_Write(GPIOA, ~0x0040);	//0000 0000 1000 0000
		Delay_ms(100);	
		GPIO_Write(GPIOA, ~0x0080);	//0000 0000 1000 0000
		Delay_ms(100);		
	}
}
 
