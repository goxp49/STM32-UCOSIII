#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

void USART1_Config(void);
void USART_SendMessage(uint16_t DataToSend);

#endif
