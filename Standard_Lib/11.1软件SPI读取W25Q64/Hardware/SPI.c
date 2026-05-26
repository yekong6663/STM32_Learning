#include "stm32f10x.h"                  // Device header
void MySPI_SCK(uint8_t BitValue) 
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}
void MySPI_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}
void MySPI_MOSI(uint8_t BitValue)		//SCK、SS、MOSI相关
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}
uint8_t MySPI_MISO(void)				//MISO相关
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP; //输出配置为推挽输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_7;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	GPIOStruct.GPIO_Mode = GPIO_Mode_IPU;//输入配置为上拉输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	MySPI_SS(1);//初始化SPI要置SS为1（代表选择），置SCK为0（代表总线空闲）
	MySPI_SCK(0);
}
void MySPI_Start(void)//开始是SS为0，不是SCK
{
	MySPI_SS(0);
}
void MySPI_Stop(void)//结束是SS为0，不是SCK
{
	MySPI_SS(1);
}
uint8_t MySPI_Swarp1(uint8_t ByteSend)//使用两个变量完成置换
{
	uint8_t i,ByteReceive = 0x00;
	for(i=0;i<8;i++)
	{
		MySPI_MOSI( !!(ByteSend & (0x80 >> i) ));//第i次输出ByteSend的第7-i位，使用&取位
		MySPI_SCK(1);	
		if(MySPI_MISO() == 1) //只有当输入为1时更新
			ByteReceive |= (0x80 >> i);//第i次输入ByteSend的第7-i位，，使用|组合
		MySPI_SCK(0);//SCK置1代表开始接收，置0代表结束接收
	}
	return ByteReceive;
}

uint8_t MySPI_Swarp2(uint8_t ByteSend)//使用一个变量完成置换
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MySPI_MOSI( !!(ByteSend & 0x80) );//每一次输出ByteSend的最高位
		ByteSend = ByteSend <<1;//将ByteSend左移
		MySPI_SCK(1);
		if(MySPI_MISO() == 1) //只有当输入为1时更新
			ByteSend |= 0x01 ;//每一次输入ByteSend的最低位
		MySPI_SCK(0);//SCK置1代表开始接收，置0代表结束接收
	}
		return ByteSend;
}
