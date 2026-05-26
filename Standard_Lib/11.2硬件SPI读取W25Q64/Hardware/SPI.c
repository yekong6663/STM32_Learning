#include "stm32f10x.h"                  // Device header
void MySPI_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}

void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP; //输出配置为推挽输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_4 ;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	GPIOStruct.GPIO_Mode = GPIO_Mode_AF_PP; //输出配置为复用推挽输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_5 |  GPIO_Pin_7;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;//输入配置为上拉输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	SPI_InitTypeDef SPIStruct;
	//波特率预分频器SPI_SCK时钟频率 = PCLK2（72MHz）/ 128 = 562.5kHz
	SPIStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPIStruct.SPI_CPHA = SPI_CPHA_1Edge;//时钟相位
	SPIStruct.SPI_CPOL = SPI_CPOL_Low;//时钟极性
	SPIStruct.SPI_CRCPolynomial = 7;//CRC多项式（无需关注）
	SPIStruct.SPI_DataSize = SPI_DataSize_8b;//数据大小
	SPIStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//数据传输方向,双线全双工模式
	SPIStruct.SPI_FirstBit = SPI_FirstBit_MSB;// 首位顺序,高位先行
	SPIStruct.SPI_Mode = SPI_Mode_Master;//工作模式,主机
	SPIStruct.SPI_NSS = SPI_NSS_Soft;//片选信号控制,软件（无需关注）
	SPI_Init(SPI1,&SPIStruct);
	
	SPI_Cmd(SPI1,ENABLE);
	
	MySPI_SS(1);//初始化SPI要置SS为1

}
void MySPI_Start(void)//开始是SS为0，不是SCK
{
	MySPI_SS(0);
}
void MySPI_Stop(void)//结束是SS为0，不是SCK
{
	MySPI_SS(1);
}
uint8_t MySPI_Swarp1(uint8_t ByteSend)//先检验再发送，再检验最后接受
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!= SET );
	SPI_I2S_SendData(SPI1,ByteSend);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!= SET );
	return SPI_I2S_ReceiveData(SPI1);
}

