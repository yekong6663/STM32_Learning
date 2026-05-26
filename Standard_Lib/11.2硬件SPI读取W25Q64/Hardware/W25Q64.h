#ifndef __W25Q64__H
#define	__W25Q64__H
void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t* MID, uint16_t* DID);
void W25Q64_WriteEnable(void);
void W25Q64_WaitBusy(void);
void W25Q64_PageProgram(uint32_t Address,uint8_t Data[],uint16_t Count);
void W25Q64_PageErase(uint32_t Address);
void W25Q64_PageRead(uint32_t Address,uint8_t Data[],uint16_t Count);
#endif
