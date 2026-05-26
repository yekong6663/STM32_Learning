#include "stm32f10x.h"                  // Device header
#include  "Infraredsensor.h"
#include  "OLED.h"
int main(void)
{	
	OLED_Init();
	Infraredsensor_Init();
	OLED_ShowString(1,1,"CountNumber:");
	while(1)
	{
		OLED_ShowNum(1,13,GetCountNumber(),3);
	}
}
 
