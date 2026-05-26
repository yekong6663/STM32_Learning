#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "LED.h"
#include  "KEY.h"
int main(void)
{	
	LedInit();
	KeyInit();
	uint8_t keynumber=0;
	while(1)
	{
		keynumber=NumberGet();
		if(keynumber==1)
			LedOn();
		if(keynumber==2)
			LedOff();
	}
}
 
