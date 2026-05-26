#include "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "MyDMA.h"
int main(void)
{	
	
	OLED_Init();
	OLED_ShowString(1,1,"alignA:");
	OLED_ShowString(3,1,"alignB:");

	while(1)
	{
		OLED_ShowNum(1, 5, ADValue[0], 4);
		OLED_ShowNum(2, 5, ADValue[1], 4);
		OLED_ShowNum(3, 5, ADValue[2], 4);
		OLED_ShowNum(4, 5, ADValue[3], 4);
		
		Delay_ms(100);
	}
}
 
