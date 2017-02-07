
#include <stdbool.h>//поддержка bool
#include "iom8.h"//<ioavr.h>
#include <inavr.h>
#include <intrinsics.h>
#include "init.h"
#include "SoftTimers.h"

//***************************************************************************
//
//***************************************************************************
timers tm1,tm2;
static uchar raz;
static uchar port;
static uchar razct;

/*
#pragma vector = TIMER0_OVF_vect 
__interrupt void funTIMER0_OVF_vect(void)
{
   
 
}
*/

void TimerSet(timers *t, uint tm)
{
  t->out=0;
  t->ct=0;
  t->time=tm;
  t->x=0;
}

void TimerTick( timers *t)
{
  if (t->out) return;
  t->x++;
  if (t->x>=CALIBR) { t->x=0; t->ct++;}
  if (t->ct >t->time ) t->out=1;
}
//**************************************************************
//**************************************************************
//void ResetT1(void)/
//{
//  T1=0;T1x=0;  T1out=0;
//}
  

//void iniT1(ulong max)
//{
 //инициализаци€ таймера “0 - прерывани€ каждую ms
 // TIMSK = (1<<OCIE0);
 // TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(0<<COM00)|(0<<CS02)|(1<<CS01)|(1<<CS00);
 // TCNT0 = 0;
 // OCR0 = 0x7d;

  //T1max=max; ResetT1();
//}


//void WorkT1(void)
//{
//  if (T1out) return;
//  T1x++; if (T1x>=CALIBR) { T1x=0; T1++; }
//  if (T1>=T1max) T1out=1;
//}

//**************************************************************
//**************************************************************
/*
//void ResetT2(void)/
{
  T2=0;T2x=0;  T2out=0;
}
  

void iniT2(ulong max)
{
 //инициализаци€ таймера “0 - прерывани€ каждую ms
 // TIMSK = (1<<OCIE0);
 // TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(0<<COM00)|(0<<CS02)|(1<<CS01)|(1<<CS00);
 // TCNT0 = 0;
 // OCR0 = 0x7d;

  T2max=max; ResetT2();
}


void WorkT2(void)
{
  if (T2out) return;
  T2x++; if (T2x>=(CALIBR/1000)) { T2x=0; T2++; }
  if (T2>=T2max) T2out=1;
}


|*/







void migINI(uchar sel,  uchar razp, bool prton)//мигание sel - кол-во раз
{
  SET(PORTB,sel);//вкл-ем дл€ ускорени€ индикации
  
  
  if (port!=255) {  //если все еще мигает
     
    if (prton)SET(PORTB,port); //фиксируем чтобы горел
    else RES(PORTB,port);
                }
  
  
  raz=razp;  port=sel; razct=0;
  
  
  TimerSet(&tm2,5);
  tm2.out=1;
  //iniT2(5);
  //T2out=1;
  
}

void migWORK(void)//мигание 
{
  static bool sost=0;
  TimerTick(&tm2); // WorkT2();
  if (tm2.out==1 && port!=255)  {
       if (sost!=1)  {sost=1; TimerSet(&tm2,200); SET(PORTB,port); razct++;}
  else if (sost!=0)  {sost=0; TimerSet(&tm2,200); RES(PORTB,port);}
                              }
  if (razct>=raz) {  tm2.out=1; port=255;}
}
//uchar migSEL(void){ return(port);} //возвращает текущий мигающий порт
//**************************************************************
//**************************************************************