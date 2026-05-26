#include "stm32f10x.h"                  // Device header
#include "SPI.h"
#include "W25Q64_String.h"
void W25Q64_Init(void)//W25Q64初始化就是SPI的初始化
{
	MySPI_Init();
}
/*
SPI时序流程：开始、输入指定、……、结束
特别地，对于写入与擦除需要事前（时序开始前）写使能，事后（时序结束后）等待非忙
对于地址，都是32位的，但是实际上只会使用24位，每一次只读取低8位
*/
void W25Q64_ReadID(uint8_t* MID, uint16_t* DID)
{
	MySPI_Start();
	MySPI_Swarp1(W25Q64_JEDEC_ID);//返回MID、DID高八位、DID低八位
	*MID = MySPI_Swarp1(W25Q64_DUMMY_BYTE);
	*DID = MySPI_Swarp1(W25Q64_DUMMY_BYTE);
	*DID = (*DID)<<8;//DID高八位位移（使用|=和<<实现）
	*DID |=MySPI_Swarp1(W25Q64_DUMMY_BYTE);//DID高低八位组合（使用|=实现）
	MySPI_Stop();
}
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_Swarp1(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}
void W25Q64_WaitBusy(void)
{
	uint8_t i;
	uint32_t TimeOut = 10000;
	MySPI_Start();
	MySPI_Swarp1(W25Q64_READ_STATUS_REGISTER_1);
	//使用TimeOut机制等待非忙
	//注意要每次更新，所以需要将MySPI_Swarp1(W25Q64_DUMMY_BYTE)放在while条件内
	//使用&取出最低位进行比较
	while ( (MySPI_Swarp1(W25Q64_DUMMY_BYTE) & 0x01)==0x01)
	{
		TimeOut--;
		if(TimeOut == 0)
			break;
	}
	MySPI_Stop();
}
void W25Q64_PageProgram(uint32_t Address,uint8_t Data[],uint16_t Count)
{
	W25Q64_WriteEnable();
	uint16_t i ;
	MySPI_Start();
	MySPI_Swarp1(W25Q64_PAGE_PROGRAM);
	MySPI_Swarp1(Address>>16);
	MySPI_Swarp1(Address>>8);
	MySPI_Swarp1(Address);
	for(i=0;i<Count;i++)//写入一个数组
	{
		MySPI_Swarp1(Data[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}
void W25Q64_PageErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_Swarp1(W25Q64_SECTOR_ERASE_4KB);
	MySPI_Swarp1(Address>>16);
	MySPI_Swarp1(Address>>8);
	MySPI_Swarp1(Address);
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}
void W25Q64_PageRead(uint32_t Address,uint8_t Data[],uint16_t Count)
{
	uint16_t i ;
	MySPI_Start();
	MySPI_Swarp1(W25Q64_READ_DATA);
	MySPI_Swarp1(Address>>16);
	MySPI_Swarp1(Address>>8);
	MySPI_Swarp1(Address);
	for(i=0;i<Count;i++)//读出一个数组
	{
		Data[i] = MySPI_Swarp1(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
