#include  "stm32f10x.h"                  // Device header
#include  "Infraredsensor.h"
#include  "OLED.h"
int main(void)
{	
	OLED_Init();
	Infraredsensor_Init();
	OLED_ShowString(1,1,"CountNumber:");
	int16_t number;
	while(1)
	{
		number+=GetCountNumber();
		OLED_ShowSignedNum(1,13,number,3);
	}
}
 
