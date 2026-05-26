#ifndef __I2C_H
#define __I2C_H
void MyI2C_W_SCL(uint8_t BitValue);
void MyI2C_W_SDA(uint8_t BitValue);
uint8_t MyI2C_R_SCL(void);
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Data);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendACK(uint8_t AcBit);
uint8_t MyI2C_ReceiveACK(void);
#endif
