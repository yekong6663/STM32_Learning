#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "MyDMA.h"
int main(void)
{	
	uint8_t alignA[]= {0x01,0x02,0x03,0x04};
	uint8_t alignB[]= {0,0,0,0};

	OLED_Init();
	OLED_ShowString(1,1,"alignA:");
	OLED_ShowString(3,1,"alignB:");
	MyDMA_Init( (uint32_t)alignA,(uint32_t)alignB, 4);
	while(1)
	{
		alignA[0]++;
		alignA[1]++;
		alignA[2]++;
		alignA[3]++;
		OLED_ShowNum(2,1,alignA[0],2);
		OLED_ShowNum(2,4,alignA[1],2);
		OLED_ShowNum(2,7,alignA[2],2);
		OLED_ShowNum(2,10,alignA[3],2);
		Delay_ms(500);
		MyDMA_Transfor();
		OLED_ShowNum(4,1,alignB[0],2);
		OLED_ShowNum(4,4,alignB[1],2);
		OLED_ShowNum(4,7,alignB[2],2);
		OLED_ShowNum(4,10,alignB[3],2);
		Delay_ms(500);
	}
}
 
