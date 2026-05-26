#include "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "ADC.h"
int main(void)
{	
	OLED_Init();
	AD_Init();
	uint16_t value,voltage;
	OLED_ShowString(1,1,"ADC:");
	OLED_ShowString(2,1,"Voltage:0.00V");

	while(1)
	{
		value=AD_GetValue();
		voltage=(float)value/4036*3.3;
		OLED_ShowNum(1,5,value,4);
		OLED_ShowNum(2,9,voltage,1);
		OLED_ShowNum(2,11,(uint16_t)voltage%100,2);
	}
}

