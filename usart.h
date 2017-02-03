#ifndef USART_H
#define USART_H

#include <iom8.h>

void USART_Init(bool usarton); //������������� usart`a
void USART_SendChar(unsigned char sym); //������� ������ �� usart`�
unsigned char USART_GetChar(void); //��������� �������� ����� usart`a 

void rprintfStr(char str[]);
void rprintfFloat(char numDigits, double x);

#define ent USART_SendChar(0x0D)

#endif //USART_H