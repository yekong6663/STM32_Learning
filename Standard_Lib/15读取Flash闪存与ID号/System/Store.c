#include "stm32f10x.h"                  // Device header
#include "Flash.h"
uint16_t SRAMArray[512];
void Store_Init(void) //初始化Flash，并且将Flash中的数据转移到SRAM数组中
{
	uint16_t i;
	if(Flash_ReadHalfWord(0x0800FC00)!= 0xA5A5)//没有标志位则写入Flash
	{
		Flash_ErasePage(0x0800FC00);//每一次要向Flash中写入数据需要先擦除
		Flash_ProgramHalfWord(0x0800FC00,0xA5A5);//在Flash中将第一个半字写为标志位
		for(i=1;i<512;i++)						 //将后续标志位全部写为1
		{
			Flash_ProgramHalfWord(0x0800FC00+i*2,0x0001);//每次i加1只是移动一个字节半个半字，所以要乘以2
		}	
	}
	for(i=0;i<512;i++)//将Flash中的数据写入SRAM中，主要是用于断电后（Flash数据不丢失但是SRAM数组会）
		{
			SRAMArray[i] = Flash_ReadHalfWord(0x0800FC00+i*2);
		}
}

void Store_Save(void)//将SRAM中的数据写入Flash中
{
	uint16_t i;
	Flash_ErasePage(0x0800FC00);
	for(i=0;i<512;i++)
	{
		Flash_ProgramHalfWord(0x0800FC00+ i*2, SRAMArray[i]);
	}
}

void Store_Clear(void)//将SRAM中的数据除了标志位全部清零，并且保存到Flash中
{
	uint16_t i;
	for(i=1;i<512;i++)
	{
		SRAMArray[i] = 0x0000;
	}
	Store_Save();
}
