#include "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "USART.h"
#include  "KEY.h"
int main(void)
{	
	OLED_Init();
	MyUSART_Init();
	Key_Init();
	
	TxArray[0]=0x01;
	TxArray[1]=0x02;
	TxArray[2]=0x03;
	TxArray[3]=0x04;
	
	OLED_ShowString(1,1,"The Sent:");
	OLED_ShowString(3,1,"The Received:");

	while(1)
	{
		if(NumberGet())
		{
			TxArray[0]++;
			TxArray[1]++;
			TxArray[2]++;
			TxArray[3]++;
			USART_SendDataBag();
			
			OLED_ShowHexNum(2,1,TxArray[0],2);
			OLED_ShowHexNum(2,4,TxArray[1],2);
			OLED_ShowHexNum(2,7,TxArray[2],2);
			OLED_ShowHexNum(2,10,TxArray[3],2);
		}
		if( USART_GetRxFlag() )
		{
			OLED_ShowHexNum(4,1,RxArray[0],2);
			OLED_ShowHexNum(4,4,RxArray[1],2);
			OLED_ShowHexNum(4,7,RxArray[2],2);
			OLED_ShowHexNum(4,10,RxArray[3],2);
		
		}
	}
}

