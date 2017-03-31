#ifndef USART_H
#define USART_H

void USART_Init(); //инициализация usart`a
void USART_SendChar(unsigned char sym); //послать символ по usart`у
unsigned char USART_GetChar(void); //прочитать приемный буфер usart`a 

void rprintfStr(char str[]);
void rprintfFloat(char numDigits, double x);

#define ent if (u) USART_SendChar(0x0D)

#endif //USART_H