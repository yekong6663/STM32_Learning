#include  "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "USART.h"
#include  "LED.h"
#include  <string.h>

int main(void)
{	
	OLED_Init();
	MyUSART_Init();
	Led_Init();
	OLED_ShowString(1,1,"LED State:");
	while(1)
	{
		if( USART_GetRxFlag() )
		{
			if(strcmp(RxArray,"LED_ON")==0)
			{
				Led_On();
				USART_SendString("ON");
				OLED_ShowString(2,1,"             ");
				OLED_ShowString(2,1,"LED ON");
			}
			else if(strcmp(RxArray,"LED_OFF")==0)
			{
				Led_Off();
				OLED_ShowString(2,1,"             ");
				USART_SendString("OFF");
				OLED_ShowString(2,1,"LED OFF");
			}
			else
			{
				OLED_ShowString(2,1,"             ");
				USART_SendString("Error");
				OLED_ShowString(2,1,"Error Command");
			}
		}
	}
}

