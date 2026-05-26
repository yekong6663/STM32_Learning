#include "stm32f10x.h"    
uint16_t MySize;
void MyDMA_Init(uint32_t ADDRA,uint32_t ADDRB,uint16_t Size)
{
	MySize = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMAStruct;
	DMAStruct.DMA_PeripheralBaseAddr = ADDRA;
	DMAStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMAStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMAStruct.DMA_MemoryBaseAddr = ADDRB;
	DMAStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMAStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMAStruct.DMA_Mode = DMA_Mode_Normal;
	DMAStruct.DMA_BufferSize = Size;
	DMAStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMAStruct.DMA_M2M = DMA_M2M_Enable;
	DMAStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMAStruct);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
}
void MyDMA_Transfor(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MySize);
	DMA_Cmd(DMA1_Channel1,ENABLE);

	while ( DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET ) ;
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
