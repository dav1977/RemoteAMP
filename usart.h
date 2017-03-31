#ifndef USART_H
#define USART_H

void USART_Init(); //������������� usart`a
void USART_SendChar(unsigned char sym); //������� ������ �� usart`�
unsigned char USART_GetChar(void); //��������� �������� ����� usart`a 

void rprintfStr(char str[]);
void rprintfFloat(char numDigits, double x);

#define ent if (u) USART_SendChar(0x0D)

#endif //USART_H