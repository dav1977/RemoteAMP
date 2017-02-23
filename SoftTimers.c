
#include <stdbool.h>//поддержка bool
#include "iom8.h"//<ioavr.h>
#include <inavr.h>
#include <intrinsics.h>
#include "init.h"
#include "SoftTimers.h"
#include "main.h"
//***************************************************************************
//
//***************************************************************************
timers tm1,tm2,tm3;
static uchar raz;
static uchar port;
static uchar razct;


#pragma vector = TIMER2_OVF_vect
__interrupt void TIMER2ovf(void)
{
 TimerTick(&tm3); // Work
 TCNT2 = 0;
  TimerTick(&tm2);
 

 static bool state=0;
 
 if (tm3.out ) { 
 //if (!state) {RES(PORTB,5); state=1; }   else {SET(PORTB,5); state=0;}
 //       TimerSet(&tm3,3000);       
              }
}





void TimerSet(timers *t, uint tm)
{
  t->out=0;
  t->ct=0;
  //F_CPU/4/100; 1-сек
  t->time=F_CPU/4/100000   *tm;
  t->x=0;
}

void TimerTick( timers *t)
{
  if (t->out) return;
 // t->x++;
  //if (t->x>=CALIBR) { t->x=0; t->ct++;}
  t->ct++;
  if (t->ct  >  t->time ) t->out=1;
}
//**************************************************************
//**************************************************************


void migINI(uchar sel,  uchar razp, bool prton)//мигание sel - кол-во раз
{
  SET(PORTB,sel);//вкл-ем для ускорения индикации
  
  
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
 // TimerTick(&tm2); // WorkT2();
  if (tm2.out==1 && port!=255)  {
       if (sost!=1)  {sost=1; TimerSet(&tm2,200); SET(PORTB,port); razct++;}
  else if (sost!=0)  {sost=0; TimerSet(&tm2,200); RES(PORTB,port);}
                              }
  if (razct>=raz) {  tm2.out=1; port=255;}
}
//uchar migSEL(void){ return(port);} //возвращает текущий мигающий порт
//**************************************************************
//**************************************************************