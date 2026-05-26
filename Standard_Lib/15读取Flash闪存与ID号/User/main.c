#include "stm32f10x.h"                  
#include  "Delay.h"
#include  "OLED.h"
#include  "Store.h"
#include  "KEY.h"
int main(void)
{	
	OLED_Init();
	Store_Init();
	Key_Init();

	while(1)
	{
		if( NumberGet()==1 )
		{
			SRAMArray[1] +=1;
			SRAMArray[2] +=2;
			SRAMArray[3] +=3;
			SRAMArray[4] +=4;
			Store_Save();
		}
		if( NumberGet()==2 )
		{
			Store_Clear();
		}
		OLED_ShowHexNum(1,1,SRAMArray[1],4);
		OLED_ShowHexNum(1,6,SRAMArray[2],4);
		OLED_ShowHexNum(2,1,SRAMArray[3],4);
		OLED_ShowHexNum(2,6,SRAMArray[4],4);
	}
}
 
