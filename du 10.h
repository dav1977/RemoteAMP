//***************************************************************************
//
//  Author(s)...: dav COBRA
//
//  Target(s)...: ATMega8
//
//  Compiler....: 6 40
//
//  Description.: Универсальный ДЕКОДЕР ДУ v1.0
//
//  Data........: 2014
//
//***************************************************************************
#include <stdbool.h>//поддержка bool
#include "iom8.h"//<ioavr.h>
#include <inavr.h>
#include <intrinsics.h>
#include "init.h"
#include "usart.h"
#include "eeprom.h"
#define  MAX 50 //кол-во интервалов макс  РЕАЛЬНО на 2 меньше!!!
void du_init();
uint du(void);
void read(void);
char du_main(uchar pr);
bool rw(bool a,char b,uint c); 
void compr (void);

  volatile static char  sync;//
  volatile static char  perepoln;//коло-во переполнений счетчика
  uchar t1,t2;
  volatile static bool priznak;// что произошла смена полярности
  volatile static bool ini; 
  volatile char kolbit1,kolbit2,kolbit3;
  uint dim1[MAX],dim2[MAX];
  volatile static char ct;
  uint minimallen;    
  float len[MAX];
  volatile static bool intok,readint;
  static uint last;
  volatile static  char cod_ok;
 
   void du_init(void)
   {
   ini=1;  intok=0;
   //TCCR1B = (0<<CS02)|(1<<CS01)|(1<<CS00); //пуск таймера
   TCCR1B = (0<<CS02)|(0<<CS01)|(1<<CS00); //пуск таймера
   priznak=0;
   ct=0;
   }
   
//прерывание при изменении сигнала
#pragma vector = INT0_vect
__interrupt void funINT0_vect(void)
{
  intok=1; 
  if (readint!=0){  last=TCNT1L;   readint=0; }
   
     
}
///////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////
  char du_main(uchar pr) 
  {   
    cod_ok=0;
    if (ini!=1) du_init();    uint i;
  
 //////////////////////////////////////////////////////////////  
    if (intok!=0)   //INT событие произошло
        {
          if (readint==0 && last!=TCNT1L)  {
           
        t1 = TCNT1L;  t2 = TCNT1H;
         
        dim1[ct]=t1;  dim2[ct]=t2; ct++;
        if (ct>=MAX-1) ct=0;      

        if (t1!=0) {readint=1;  TCNT1H=0;TCNT1L=0;}
       intok=0;
        readint=1;
                                          }
        
        }
//////////////////////////////////////////////////////////////

cod1=0;cod2=0;cod3=0; 
//len[1]=001000;
char c1,c2,c3;
char ind=1;
c1=0; c2=0; c3=0; 


if (perepoln!=0 ) {//получили переполнение, значит сигнал закончился

      minimallen=65535;   
  
     if (ct>(MAX-2)) ct=4;
     if (ct<3) ct=2;
     
   
      for (i=1; i<ct; i++) //ищем миимальную длину
      {  
      len[i]=( dim1[i]+ (256*dim2[i])  );
      if (len[i]<(float)minimallen) minimallen=(uint)len[i];
      }
     
      if (minimallen<50) minimallen=100;//защита от суперкоротких
      
     for (i=1; i<ct; i++) { //for 
       uint tr;
       tr=( dim1[i]+ (256*dim2[i]));
       len[i]=(float)tr/minimallen;       
      
     
     if (len[i]!=0)   {///------------------
       
        float v=len[i];
       
///////////////////////////////////////////////////////////////////       
//                             кодировка
///////////////////////////////////////////////////////////////////
       if (i>1) {
          
  //-------------   версия  больше-меньше  ------------------
              //  if (len[i]>len[i-1])  cod1+=1;
         
             //  if (len[i]<=len[i-1]) cod1+=3;
   /*        
    if (ind==4) { 
                       if (len[i]>len[i-1]) { SET(cod4,c4); }
                      // else cod4<<=1;
                       c4++;
                       if (c4>=15) ind=5;
                    }
         
              

           if (ind==3) { 
                       if (len[i]>len[i-1]) { SET(cod3,c3); }
                      // else cod3<<=1;
                       c3++;
                       if (c3>=15) ind=4;
                    }
        
         
           if (ind==2) { 
                       if (len[i]>len[i-1]) { SET(cod2,c2); }
                      // else cod2<<=1;
                       c2++;
                       if (c2>=15) ind=3;
                    }
         
         if (ind==1) { 
           if (len[i]>len[i-1]) { SET(cod1,c1); }
                       //else cod1<<=1;
                       c1++;
                       if (c1>=15) ind=2;
                    }
         
      */ 
         
       /*  
         if (ind==4) { 
           if (len[i]<3) { SET(cod4,c4);c4++; }
           if (len[i]>=3 && len[i]<5)  {  c4++;  c4++;}
           if (len[i]>=5 && len[i]<25) { SET(cod4,c4); c4++;    if (c4<=15)  SET(cod4,c4);  c4++;}
           if (len[i]>=25)  {  c4++;  c4++; c4++;}
                       if (c4>=15) ind=0;
                     }
      */
         
         
      //-----   версия по относительной длине -------  
#define   set1 SET(cod1,c1);c1++   
#define   set2 SET(cod2,c2);c2++  
#define   set3 SET(cod3,c3);c3++  
          
         if (ind==3) { 
           
           if (v<1.5)         { c3++; } else
           if (v>=1.5 && v<2) { c3++;set3; } else
           if (v>=2 && v<3)   { set3;  if (c3<=15) { set3;  } } else
           if (v>=3 && v<5)   { set3;  if (c3<=15) { set3;  }
                                                  if (c3<=15) { set3; }  
                              } else
                                                    
           if (v>5 && v<7)    { c3++;   if (c3<=15)  c3++;  }
         
                       if (c3>=16) ind=1;
                     }
         
         
          if (ind==2) { 
           
           if (v<1.5)         { c2++; } else
           if (v>=1.5 && v<2) { c2++; set2; } else
           if (v>=2 && v<3)   { set2;  if (c2<=15) { set2;  } } else
           if (v>=3 && v<5)   { set2;  if (c2<=15) { set2;  }
                                                  if (c2<=15) { set2; }  
                              } else
                                                    
           if (v>5 && v<7)    { c2++;   if (c2<=15)  c2++; else c3++; }
         
                       if (c2>=16) ind=3;
                     }
          
          
         if (ind==1) { 
           
           if (v<1.5)         { c1++; } else
           if (v>=1.5 && v<2) { c1++; set1; } else
           if (v>=2 && v<3)   { set1; if (c1<=15) { set1; } } else
           if (v>=3 && v<5)   { set1; if (c1<=15) { set1;  }
                                                  if (c1<=15) {set1;}  
                              } else
                                                    
           if (v>5 && v<7)    { c1++;   if (c1<=15)  c1++; else c2++;}
         
                       if (c1>=16) ind=2;
                     }
          
             cod_ok=1;//код готов         
         
         if (pr==0) {
         rprintfFloat(2, i);
         rprintfStr("  / abslen= ");
          rprintfFloat(9, dim1[i]+ (256*dim2[i])  );
          rprintfStr("  / len= ");
      rprintfFloat(4,  len[i]);
       rprintfStr("  ");
     rprintfStr("  / cod1= ");
      rprintfFloat(6, cod1);
       rprintfStr(" / cod2= ");
      rprintfFloat(6,  cod2);
       rprintfStr(" / cod3= ");
      rprintfFloat(6,  cod3);
       rprintfStr("/ minlen=");
       rprintfFloat(9,   minimallen);

       USART_SendChar(0x0D);
         }
                   }
       
        perepoln=0;
       
      
       
     
                       }///------------------
     
    
                         }//for
     
      
      
      
      //очистка
       for (i=0; i<MAX; i++) {dim1[i]=0;dim2[i]=0;len[i]=0;}
       perepoln=0;  t1=0; t2=0; priznak=1; ct=0;
     
      
       
   
     if (pr==1 && cod1!=0)     {//diag
     rprintfStr("  / cod1= ");
      rprintfFloat(6,  cod1);
       rprintfStr("/ cod2= ");
      rprintfFloat(6,  cod2);
       rprintfStr("/ cod3= ");
      rprintfFloat(6,  cod3);
       USART_SendChar(0x0D);
                                
                               }//diag
    
     
     
     
     
     }//переполнение  ----------------------------------------
     
  
  return(cod_ok);  
  }



 //переполнился импульс более 130мс  (1/(4000000/8)*65535)
#pragma vector = TIMER1_OVF_vect
__interrupt void funTIMER1_OVF_vect(void)
{
   //TIFR = 0xFF; - в прерывании србрасывется сам
  
  perepoln=1;    sync=1;
 
}



