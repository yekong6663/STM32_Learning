#include "stm32f10x.h"                  // Device header
#include "I2C.h"
#include "MPU650_String.h"
//MPU思路：先是读写寄存器，再是初始化、获取ID、读取角速度和加速度

//读取思路：开始、发送MPU地址+接收应答、发送寄存器地址（参数）+接收应答、发送数据+接收应答、结束
void MPU650_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveACK();
	MyI2C_Stop();
}
//接收思路：开始、发送MPU地址+接收应答、发送寄存器地址（参数）+接收应答
//接着：再次开始、发送变化的MPU地址+接收应答、接收数据+发送应答、结束
uint8_t MPU650_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS| 0x01);//需要把MPU地址的最后一位修改为1
	MyI2C_ReceiveACK();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendACK(1);
	MyI2C_Stop();
	
	return Data;
}
void MPU650_Init(void)
{
	MyI2C_Init();
	MPU650_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU650_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU650_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU650_WriteReg(MPU6050_CONFIG, 0x06);
	MPU650_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU650_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
uint8_t MPU650_GetID(void)
{
	return MPU650_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
					int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;//组合数据
	
	DataH = MPU650_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU650_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;//高位数据向左移8位与低位数据组合
	
	DataH = MPU650_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU650_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU650_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU650_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU650_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU650_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU650_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU650_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU650_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU650_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
