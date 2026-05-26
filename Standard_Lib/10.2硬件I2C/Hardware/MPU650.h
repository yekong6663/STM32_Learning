#ifndef __MPU650_H
#define __MPU650_H
void MPU650_WriteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU650_ReadReg(uint8_t RegAddress);
void MPU650_Init(void);
uint8_t MPU650_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
					int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
#endif
