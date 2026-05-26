#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
int main(void)
{	
	OLED_Init();
	OLED_ShowChar(1,1,'a');
	OLED_ShowString(2,1,"I love you");
	OLED_ShowBinNum(3,1,0x11,5);

	while(1)
	{
		
	}
}
 
