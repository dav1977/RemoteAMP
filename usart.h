#ifndef USART_H
#define USART_H

#include <iom8.h>
#include "init.h"


void USART_Init(); //инициализация usart`a
void USART_SendChar(unsigned char sym); //послать символ по usart`у
unsigned char USART_GetChar(void); //прочитать приемный буфер usart`a 

extern bool usarton;

void rprintfStr(char str[]);
void rprintfFloat(char numDigits, double x);

#define ent USART_SendChar(0x0D)

#endif //USART_H