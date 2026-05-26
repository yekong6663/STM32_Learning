#ifndef __STORE_h
#define __STORE_H
extern uint16_t SRAMArray[512];
void Store_Init(void);

void Store_Save(void);

void Store_Clear(void);

#endif
