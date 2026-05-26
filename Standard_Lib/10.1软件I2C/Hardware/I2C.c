#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void MyI2C_W_SCL(uint8_t BitValue)//时钟线SCL写入
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);//I2C需要要延迟
}
void MyI2C_W_SDA(uint8_t BitValue)//数据线SDA写入
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}
uint8_t MyI2C_R_SDA(void)//数据线SDA读出
{
	uint8_t i;
	i = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return i;
}
void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD;//配置与开漏输出
	GPIOStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOStruct);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);//参照时序图就是SDA先高，SCL再高
	MyI2C_W_SCL(1);//然后SDA先低，SCL再低
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);//参照时序图就是SCL再低，SDA先低
	MyI2C_W_SCL(1);//然后SCL先高，SDA再高
	MyI2C_W_SDA(1);//顺序与开始时序完全相反
}//但是因为一般每一个时序结束SCL都是置0所以可以省略

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)//发送：SDA先发，SCL先高后低
	{
		MyI2C_W_SDA(!!(Byte & (0x80>>i)));//第i次发送SDA的第7-i位
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i,Byte = 0x00;
	MyI2C_W_SDA(1);
	for(i=0;i<8;i++)//接收：SCL先高，SDA接收，SCL后低
	{
		MyI2C_W_SCL(1);
		if( MyI2C_R_SDA() == 1)//第i次接收SDA的第7-i位
			Byte |= 0x80>>i;
		MyI2C_W_SCL(0);
	}
	return Byte;
}
void MyI2C_SendACK(uint8_t AcBit)//只发送一个字节的发送函数
{
		MyI2C_W_SDA(AcBit);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
}
uint8_t MyI2C_ReceiveACK(void)//只接收一个字节的接收函数
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
