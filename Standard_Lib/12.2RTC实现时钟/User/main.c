#include  "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "RTC.h"
int main(void)
{	
	OLED_Init();
	MyRTC_Init();
	OLED_ShowString(1,1,"Date:");
	OLED_ShowString(2,1,"Time:");
	OLED_ShowString(3,1,"CNT:");

	while(1)
	{
		MyRTC_ReadTime();
		OLED_ShowNum(1,6,MyRTCArray[0],4);
		OLED_ShowNum(1,11,MyRTCArray[1],2);
		OLED_ShowNum(1,14,MyRTCArray[2],2);
		OLED_ShowNum(2,6,MyRTCArray[3],2);
		OLED_ShowNum(2,9,MyRTCArray[4],2);
		OLED_ShowNum(2,12,MyRTCArray[5],2);
		OLED_ShowNum(3,5,RTC_GetCounter(),10);
	}
}
 
