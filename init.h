#include <stdbool.h>//поддержка bool

#define   F_CPU 4000000UL

//DDRB |= (1<<OUT1)|(1<<OUT2)|(1<<OUT3);
  //PORTB &= ~((1<<OUT1)|(1<<OUT2)|(1<<OUT3));
void iniPORTS(void);


//#define  ENABLE_BIT_DEFINITIONS  


#define _bitset(bits)\
       ((unsigned char)(\
       (bits%010)|\
       (bits/010%010)<<1|\
       (bits/0100%010)<<2|\
       (bits/01000%010)<<3|\
       (bits/010000%010)<<4|\
       (bits/0100000%010)<<5|\
       (bits/01000000%010)<<6|\
       (bits/010000000%010)<<7))
#define b(bits) _bitset(0##bits)
//Например, b(10100101) - это 0xA5.

#define   delay_s(tempfc)(__delay_cycles((tempfc * F_CPU)));
#define   delay_ms(tempfc)(__delay_cycles((tempfc * F_CPU)/1000));// 10000-max
//#define delay_s(ms) delay_ms (1000UL * ms)
//#define delay_ms(ms) delay_us (1000UL * ms) 
#define delay_us(tempfc)(__delay_cycles((tempfc * F_CPU)/1000000UL));

         
#define p1 delay_ms(100)
#define p2 delay_ms(200)
#define p3 delay_ms(300)
#define p4 delay_ms(400)
#define p5 delay_ms(500)
#define p6 delay_ms(600)
#define p7 delay_ms(700)
#define p8 delay_ms(800)
#define p9 delay_ms(900)

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define _setL(port,bit) port&=~(1<<bit)
#define _setH(port,bit) port|=(1<<bit)
#define _set(port,bit,val) _set##val(port,bit)
#define on(x) _set (x)
#define SET _setH

#define _clrL(port,bit) port|=(1<<bit)
#define _clrH(port,bit) port&=~(1<<bit)
#define _clr(port,bit,val) _clr##val(port,bit)
#define off(x) _clr (x)
#define RES _clrH


//PINC  PINB
#define _bitL(port,bit) (!(port&(1<<bit)))
#define _bitH(port,bit) (port&(1<<bit))
#define _bit(port,bit,val) _bit##val(port,bit)
#define signal(x) _bit (x)
#define BIT _bitH

#define Bit(n) (1 << (n))
#define SET2(port,bit1,bit2) port&=~(1<<bit1)(1<<bit2)  
/*
Для установки бита n в порту p:
p |= Bit(n);   PORTC|=Bit(3);
Для сброса бита:
p &= ~Bit(n); PORTC &= ~Bit(3);
Для проверки бита:
if ((p & Bit(n)) != 0) ... (PORTC & Bit(3)) != 0) 
*/

//  DDRC =0;  - входы  DDRC =255; -выходы 
//////////////////////////  ;SET(PORTD,4); CLR(PORTD,4) BIT(PINC,4)

