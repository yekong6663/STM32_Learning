#ifndef __SPI_H
#define __SPI_H
void MySPI_SCK(uint8_t BitValue);
void MySPI_SS(uint8_t BitValue);
void MySPI_MOSI(uint8_t BitValue);
uint8_t MySPI_MISO(void);
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_Swarp1(uint8_t ByteSend);
uint8_t MySPI_Swarp2(uint8_t ByteSend);
#endif
