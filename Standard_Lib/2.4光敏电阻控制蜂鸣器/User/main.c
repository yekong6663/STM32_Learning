#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "LED.h"
#include  "KEY.h"
#include  "Buzzer.h"
#include  "Lightsensor.h"

int main(void)
{	
	BuzzerInit();
	LightsensorInit();
	while(1)
	{
		if(LightGet()==1)
			BuzzerOn();
		else
			BuzzerOff();
	}
}
 
