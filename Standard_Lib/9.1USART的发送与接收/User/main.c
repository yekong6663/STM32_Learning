#include "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "USART.h"
int main(void)
{	
	OLED_Init();
	MyUSART_Init();
	uint8_t RxData;
	OLED_ShowString(1,1,"RXData");
	while(1)
	{
		if(USART_GetRxFlag()==1)
		{
			RxData=USART_GetRxData();
			USART_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,4);
		}
	}
}
 
