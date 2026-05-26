#ifndef __FLASH_h
#define __FLASH_H
uint32_t Flash_ReadWord(uint32_t Address);

uint16_t Flash_ReadHalfWord(uint32_t Address);

uint8_t Flash_ReadByte(uint32_t Address);

void Flash_EraseAllPages(void);

void Flash_ErasePage(uint32_t Address);

void Flash_ProgramWord(uint32_t Address,uint32_t Data);

void Flash_ProgramHalfWord(uint32_t Address,uint16_t Data);

#endif
