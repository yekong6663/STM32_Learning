#ifndef __USART_H
#define __USART_H
extern char RxArray[4];
extern char TxArray[4];
void MyUSART_Init(void);
void USART_SendByte(uint8_t Byte);
void USART_SendArray(uint8_t *Array,uint16_t Length);
void USART_SendString(uint8_t *Array);
void USART_SendNumber(uint16_t Number);
uint8_t USART_GetRxFlag(void);
void USART_SendDataBag(void);
void USART1_IRQHandler(void);
#endif
