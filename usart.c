#include "usart.h"
//#include <math.h>
//#include <intrinsics.h>
#include "init.h"

//однобайтный буфер
volatile unsigned char usartRxBuf = 0;
volatile static bool usarton;

//инициализация usart`a
void USART_Init(bool t)
{
  usarton=t;
  if (!usarton) return;
  UBRRH = 0;
  UBRRL = ((F_CPU/9600UL)-1)/16;//    26;//78; //скорость обмена 9600 бод
  UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN); //разр. прерыв при приеме, разр приема, разр передачи.
  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //размер слова 8 разрядов
}

//отправка символа по usart`у
void USART_SendChar(unsigned char sym)
{
  if (!usarton) return;
  while(!(UCSRA & (1<<UDRE)));
  UDR = sym;
}

//чтение буфера
__monitor unsigned char USART_GetChar(void)
{
  unsigned char tmp = usartRxBuf;
  usartRxBuf = 0;
  return tmp;  
}

//прием символа по usart`у в буфер
#pragma vector=USART_RXC_vect
__interrupt void usart_rxc_my(void) 
{
  usartRxBuf = UDR; 
} 

// *** rprintfStr ***
// prints a null-terminated string stored in RAM
void rprintfStr(char str[])
{        
    if (!usarton) return;
	// send a string stored in RAM
	// check to make sure we have a good pointer
	if (!str) return;

	// print the string until a null-terminator
	while (*str)
		USART_SendChar(*str++);
}

// *** rprintfFloat ***Pascal Stang - Copyright (C) 2000-2002
// floating-point print
void rprintfFloat(char numDigits, double x)
{
    if (!usarton) return;
	unsigned char firstplace = 0;
	unsigned char negative;
	unsigned char i, digit;
	double place = 1.0;
	
	// save sign
	negative = (x<0);
	// convert to absolute value
	x = (x>0)?(x):(-x);
	
	// find starting digit place
	for(i=0; i<15; i++)
	{
		if((x/place) < 10.0)
			break;
		else
			place *= 10.0;
	}
	// print polarity character
	if(negative)
		USART_SendChar('-');
	else
		USART_SendChar('+');

	// print digits
	for(i=0; i<numDigits; i++)
	{
		digit = (unsigned char)(x/place);

		if(digit | firstplace | (place == 1.0))
		{
			firstplace = 1;
			USART_SendChar(digit+0x30);
		}
		else
			USART_SendChar(' ');
		
		if(place == 1.0)
		{
			USART_SendChar('.');
		}
		
		x -= (digit*place);
		place /= 10.0;
	}
}