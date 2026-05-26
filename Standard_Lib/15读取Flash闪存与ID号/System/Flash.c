#include "stm32f10x.h"                  
uint32_t Flash_ReadWord(uint32_t Address)
{
	return *( (__IO uint32_t*)(Address) );
}

uint16_t Flash_ReadHalfWord(uint32_t Address)
{
	return *( (__IO uint16_t*)(Address) );
}

uint8_t Flash_ReadByte(uint32_t Address)
{
	return *( (__IO uint8_t*)(Address) );
}

void Flash_EraseAllPages(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

void Flash_ErasePage(uint32_t Address)
{
	FLASH_Unlock();
	FLASH_ErasePage(Address);
	FLASH_Lock();
}

void Flash_ProgramWord(uint32_t Address,uint32_t Data)
{
	FLASH_Unlock();
    FLASH_ProgramWord(Address,Data);
    FLASH_Lock();
}

void Flash_ProgramHalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_Unlock();
    FLASH_ProgramHalfWord(Address,Data);
    FLASH_Lock();
}





