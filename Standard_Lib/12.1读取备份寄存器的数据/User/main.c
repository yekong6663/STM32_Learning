#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "KEY.h"
int main(void)
{	
	OLED_Init();
	Key_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);

	uint16_t ArrayWrite[2]={0,1},ArrayRead[2],KeyNum;

	while(1)
	{
		KeyNum = NumberGet();
		if(KeyNum)
		{
			ArrayWrite[0]++;
			ArrayWrite[1]++;
			BKP_WriteBackupRegister(BKP_DR1,ArrayWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2,ArrayWrite[1]);
			
			OLED_ShowHexNum(1,1,ArrayWrite[0],5);
			OLED_ShowHexNum(2,1,ArrayWrite[1],5);
		}
		
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		OLED_ShowHexNum(3,1,ArrayRead[0],5);
		OLED_ShowHexNum(4,1,ArrayRead[1],5);
	}   
}
 
