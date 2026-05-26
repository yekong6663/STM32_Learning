#include "stm32f10x.h"                  // Device header
#include  "Delay.h"
#include  "OLED.h"
#include  "W25Q64.h"
int main(void)
{	
	OLED_Init();
	W25Q64_Init();
	
//注意此处MID、DID不要定义为指针变量，否则无初始值情况下地址可能错乱
	uint8_t MID;
	uint16_t DID;
	W25Q64_ReadID(&MID,&DID);
	OLED_ShowString(1,1,"MID:");
	OLED_ShowNum(1,5,MID,5);
	OLED_ShowString(2,1,"MID:");
	OLED_ShowNum(2,5,DID,5);

	uint8_t ArrayRead[4],ArrayWrite[4]={0x01,0x02,0x03,0x04};
	W25Q64_PageErase(0x00000000);
	W25Q64_PageProgram(0x00000000,ArrayWrite,4);
	W25Q64_PageRead(0x00000000,ArrayRead,4);
	
	OLED_ShowHexNum(3,1,ArrayWrite[0],2);
	OLED_ShowHexNum(3,4,ArrayWrite[1],2);
	OLED_ShowHexNum(3,7,ArrayWrite[2],2);
	OLED_ShowHexNum(3,10,ArrayWrite[3],2);
	OLED_ShowHexNum(4,1,ArrayRead[0],2);
	OLED_ShowHexNum(4,4,ArrayRead[1],2);
	OLED_ShowHexNum(4,7,ArrayRead[2],2);
	OLED_ShowHexNum(4,10,ArrayRead[3],2);
	
	while(1)
	{
		
	}
}

