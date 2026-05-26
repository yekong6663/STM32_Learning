#ifndef __USART_H
#define __USART_H
void MyUSART_Init(void);
void USART_SendByte(uint8_t Byte);
void USART_SendArray(uint8_t *Array,uint16_t Length);
void USART_SendString(uint8_t *Array);
void USART_SendNumber(uint16_t Number);
uint8_t USART_GetRxFlag(void);
uint8_t USART_GetRxData(void);
void USART1_IRQHandler(void);
#endif
