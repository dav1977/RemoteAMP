//***************************************************************************
//  
//  Author(s)...: dav COBRA 
//  Target(s)...: ATMega8
//  Compiler....: 6 40
//  ����1
//  Description.: �������  ����������  ���  ���������  ��������   V-����
//  v1.1 - ��������� ��������� ��������� ��������� ������� ������� ������ Source5
//       - �������� ��������� auto off
//  v1.2 - ������ �� ����� �������(������ Source) �����������  ������� ������ ��������������
//       - ����� ������� ������ - ������� � ���������� source
//       - ������� ������ ����� �������������� �� ������ ������, �.�. �� ������ ������� 2 ������ ������
//       - ������ ��������� ��������� ����� ����������� ���������� ������
//       - ����������� ��������
//       - �������� �������� �����������
// v1.22 - ���������� ������ �������� ��� AC
// v1.23 - ��������� ��� ��������� ���������� SOURCE1 
// v1.24 - ��������� ��� AUTOOFF �� 30 ����� 
// v1.25 - ��������� ��� AUTOOFF ��� ����������� ������� 
//
//  Data........: 04 2016
//
//   - ��������� ����� clustering of variables � optimization compilator !!!!
//***************************************************************************
#include <stdbool.h>//��������� bool
#include <iom8.h>//<ioavr.h>
//#include <inavr.h>  
#include <intrinsics.h>
#include "init.h"
#include "du.h"  
#include "SoftTimers.h" 
#include "keys.h"
//#include <stdlib.h>
//#include <math.h> 
#include "usart.h"
//#include <stdarg.h>
//************************************************************************* 
#define AC_ON    SET(PORTD,6)
#define AC_OFF   RES(PORTD,6)
void diag(void);
void led_all(bool a);
void resled(void);
void source(void);
void resOUT(void);  
void gro(uchar a);
void normal(uchar rez);
void writeCOD(void);
uchar analizCOD(void);
void programming(uchar rez);
uchar getadr(void);
#define acon 20000;//����� ��������� �� ��� ������ �������
uint tON=acon; 
#define MAXFUNC 23  //���������(������������)����������� tekfunc(���-�� ������)
//uint kbuf[MAXEEP];
uchar write;
uchar pr;
static bool get=0;
bool onok;  
bool on,mute;
bool zader,aoff;
uint timerzad; 
uchar pultadr; uchar rez;
extern   bool u=0,til=0; 
extern  uchar mode=0,tekfunc=0; 
static uchar lastsel=1,sel=1,gro1=0,gro2=0,regaoff=0;
//***************************************************************************
//                  M  A  I  N
//***************************************************************************
int main( void )
{//main
  
   aoff=0; onok=0; pr=0; on=0; mute=0; zader=0;  til=0;
  iniPORTS();    
 //----------------------------------
   if (keyONsm) u=1;//�������� UART
 // u=1; 
  USART_Init(u);
//----------------------------------
  mode=fmode; //����� ������ ������
  if (mode!=1 && mode!=0) { fmode=0; mode=0;   }//ini
  if (modegro!=1 && modegro!=0) { modegro=0; p1;   }//ini
  
  if (keyMUTE && !keyAOFFsm) {
  if (mode==0 && modegro==0)   {  fmode=1; p5;   SET(PORTB,4);  while(1) {}   }
  if (mode==1 && modegro==0)   {  modegro=1; p5; SET(PORTB,2);  SET(PORTB,3);  SET(PORTB,4);  while(1) {}  }
  if (mode==1 && modegro==1)   {  fmode=0; p5; SET(PORTB,2);  SET(PORTB,3);    while(1) {}  } 
  if (mode==0 && modegro==1)   {  modegro=0; p5;  led_all(1);    while(1) {}   }
  
                              }
  
 // modegro=1; mode=1;
//-----------------------------------
  
   if (keySELsm) {write=1; }//�������� ���������������� ������
   if (keySELsm==1 && keyAOFFsm==1)//�������
      {
        write=1; cod1=0;cod2=0;cod3=0;
        for (uchar i=0; i<=MAXFUNC; i++) {writeCOD();tekfunc++;}
        tekfunc=0;
        led_all(1); while(1) {} //��������
      }

   if (write==1) //������� ������� ����������������
   {
     for (uchar i=0; i<3; i++) {getadr(); p3;led_all(0); p3;}
    
     getadr();
   }
           
   //---------------------------------------
 //   for (uchar i=0; i<MAXEEP-1; i++) kbuf[i]=k[i];//������ ��prom
  //-----------------------------------------
  //---------------------------------- 

     __enable_interrupt(); 
  
  
  
   
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  while(1){//-----------------------------------����������� ����

   rez=du_main(pr);//����� ����������� ������
   
   if (write==0)  {//------------------------------------- 
    
     pultadr=0; 
     if (rez) pultadr=analizCOD();  
     
     if ((keyON||pultadr==25 || pultadr==90) && on==1 && zader!=1) { rprintfStr("OFF>adr="); rprintfFloat(9, pultadr ); ent;
                    on=0;onok=0; p5; zader=0;  til=0; gro1=0; gro2=0; pultadr=0;  }//OFF
     if ((keyON||pultadr==25 || pultadr==90) && on==0) {rprintfStr("ON>adr="); rprintfFloat(9, pultadr ); ent;
                    SET(PORTD,4); SET(PORTD,7);p5; on=1; mute=0; zader=1;timerzad=0;source();pultadr=0;  }//ON
     
    //����������
    if (on==0 && onok==0) { on=0; aoff=0; p5; zader=0; regaoff=0; AC_OFF; delay_s(1); tON=acon; 
    						PORTB=0; RES(PORTD,7);RES(PORTD,4); resOUT(); RES(PORTC,5); RES(PORTC,0);RES(PORTD,3); onok=1;
                          }
                                  
  
    pultadr=0;  if (on==1) normal(rez);
   
                  }//------------------------------------- 
  
   if (write==1) programming(rez);
   
   diag();  
     
    
   
  }//-------------------------------------------����������� ����
  
}//main
//***************************************************************************











 

uchar getadr()//������  ������
{
  uchar adr=0;
  if (tekfunc==0) {adr=1; SET(PORTB,0);}//s1
  if (tekfunc==1) {adr=5; SET(PORTB,1);}
  if (tekfunc==2) {adr=10;SET(PORTB,2);}
  if (tekfunc==3) {adr=15;SET(PORTB,3);}
  if (tekfunc==4) {adr=20;SET(PORTB,4);}//s5 ��� ON���
  if (tekfunc==5) {adr=55;SET(PORTB,0);SET(PORTB,2);SET(PORTB,4);}//command return
  if (tekfunc==6) {adr=25;SET(PORTD,7);}//on standby
  if (tekfunc==7) {adr=30;SET(PORTB,5);}//aoff
  if (tekfunc==8) {adr=35;AC_ON;}//mute
  if (tekfunc==9) {adr=40; }//select
  if (tekfunc==10) {adr=45; }//��������� ���������
  if (tekfunc==11) {adr=50; }//��������� ���������
  
  //������������ ������
   if (tekfunc==12) {adr=60; SET(PORTB,0);}//s1
  if (tekfunc==13) {adr=65; SET(PORTB,1);}
  if (tekfunc==14) {adr=70;SET(PORTB,2);}
  if (tekfunc==15) {adr=75;SET(PORTB,3);}
  if (tekfunc==16) {adr=80;SET(PORTB,4);}//s5 ��� ON���
  if (tekfunc==17) {adr=85;SET(PORTB,0);SET(PORTB,2);SET(PORTB,4);}//command return
  if (tekfunc==18) {adr=90;SET(PORTD,7);}//on standby
  if (tekfunc==19) {adr=95;SET(PORTB,5);}//aoff
  if (tekfunc==20) {adr=100;AC_ON;}//mute
  if (tekfunc==21) {adr=105; }//select
  if (tekfunc==22) {adr=110; }//��������� ���������
  if (tekfunc==23) {adr=115; }//��������� ���������
  return(adr);
}


void pult() 
{
   tON=1500; zader=1;timerzad=0; source(); p2;   //����� ��������� �� ��� �������������
}

void normal(uchar rez)//-----------------------������� ������ --------------------
{   
   pultadr=0; 
  
   migWORK();
   
  
   if (rez)
   {//���� ���� ������� � ������
     
     pultadr=analizCOD();
     
     if (pultadr==0){  RES(PORTD,7); delay_ms(100); SET(PORTD,7);
      rprintfStr("normal>no find command ");  ent;}
     else { rprintfStr("normal>command find  adr= ");
      rprintfFloat(6, pultadr ); ent;}
     
     if (pultadr==1 || pultadr==60) {if (sel!=1)  { AC_OFF; lastsel=sel; sel=1; pult(); } else   migINI(sel-1, 3 ,0); 
 }
     if (pultadr==5 || pultadr==65) {if (sel!=2)  {AC_OFF; lastsel=sel;sel=2; pult(); }  else  migINI(sel-1, 3 ,0); 
}
     if (pultadr==10 || pultadr==70) {if (sel!=3) {AC_OFF; lastsel=sel;sel=3; pult(); } else    migINI(sel-1, 3 ,0); 
}
     if (pultadr==15 || pultadr==75) {if (sel!=4) {AC_OFF; lastsel=sel;sel=4; pult(); } else   migINI(sel-1, 3 ,0); 
 }
     if ((pultadr==20  || pultadr==80) && mode!=1) { if (sel!=5) {AC_OFF; lastsel=sel;sel=5; pult();}  else  migINI(sel-1, 3 ,0); 
}
     
     
     //�������  ------------------------------------------------------
     if ((  pultadr==20  || pultadr==80) && mode==1) {  
         
       if (til==0) { SET(PORTC,5);til=1;  
               for (uchar i=0; i<2; i++) {SET(PORTB,4);p2;RES(PORTB,4);p2;}  SET(PORTB,4);  pultadr=0;  p1;}
       else 
       if (til==1) {   RES(PORTC,5); RES(PORTB,4); til=0; pultadr=0; p1; }
     
                                                     }
   }//���� ���� ������� � ������
   
  //--------------- mute -------------------
  if (mute==1) AC_OFF; else { if (zader==0) AC_ON; }
  if (zader==1) {timerzad++;  if (timerzad> tON)  {zader=0;timerzad=0; if (mute!=1)AC_ON;} }//�������� ���������
  
   if ((keyMUTE ||pultadr==35 || pultadr==100) && mute==0) { AC_OFF; mute=1; p5; pultadr=0;}
   if ((keyMUTE ||pultadr==35 || pultadr==100) && mute==1) { AC_ON; mute=0; p5; pultadr=0; }   
   
   
  //--------------- aoff --------------------
 
   
   if ((keyAOFF || pultadr==30 || pultadr==95) && aoff==1 && regaoff>=3)  {  RES(PORTB,5);  p5; aoff=0; regaoff=0; pultadr=0;}//������ aoff 
   
  if ((keyAOFF || pultadr==30 || pultadr==95) && regaoff==0) { aoff=1; regaoff++; iniT1(60*60*2)/*2 ����*/; pultadr=0;  for (uchar i=0; i<3; i++)  {SET(PORTB,5);p2;RES(PORTB,5);p2;}  SET(PORTB,5); }
  if ((keyAOFF || pultadr==30 || pultadr==95) && regaoff==1) { aoff=1; regaoff++; iniT1(60*60*1)/*1 ����*/; pultadr=0; for (uchar i=0; i<2; i++)  {SET(PORTB,5);p2;RES(PORTB,5);p2;}  SET(PORTB,5); }
  if ((keyAOFF || pultadr==30 || pultadr==95) && regaoff==2) { aoff=1; regaoff++; iniT1(60*60*0.5)/*0.5 ����*/; pultadr=0; for (uchar i=0; i<1; i++)  {SET(PORTB,5);p2;RES(PORTB,5);p2;}  SET(PORTB,5); }
  
   
 //  if ((keyAOFF || pultadr==30 || pultadr==95) && aoff==0) 
 //     {   aoff=1;  iniT1(60*60*2)/*2 ����*/; pultadr=0;
 //         for (uchar i=0; i<2; i++)  {SET(PORTB,5);p2;RES(PORTB,5);p2;}  SET(PORTB,5);
  //   
  //        
 //         for (uint i=0; i<1000; i++)
 //         {   char rez=du_main(0);  if (rez==1) { pultadr=analizCOD();break; }}
 //         
  //    //���� user ���������� ����������
  //    if ((keyAOFF || pultadr==30 || pultadr==95) ) { iniT1(60*30);/*30 ���*/
 //      for (uchar i=0; i<4; i++)  {SET(PORTB,5);p2;p2;p2;p2;p2;RES(PORTB,5);p2;}  SET(PORTB,5);
  //                                    }
  //    
   //   }
                                                        
   
  
 
  if (aoff==1)  {    WorkT1(); if (T1end) { on=0; onok=0;  aoff=0; p5; zader=0; regaoff=0;}
                } 
                
 //--------------- select -------------------
                if ( u!=1) {//��� �� �� ����� ������ UART �� ����������
   uchar kol;  if  (mode==1) kol=4; else kol=5;
   if (keySEL ||pultadr==40 || pultadr==105) 
                { 
                        if (sel<=(kol-1)) { AC_OFF; p2; RES(PORTB,(sel-1));lastsel=sel; sel++; pult(); } 
                       else { AC_OFF;  RES(PORTB,(sel-1)); sel=1; pult(); }
              
                }
                         
  //--------------- return sel -------------------  ������� � ���������� source                 
   if ( pultadr==55 || pultadr==85) {
     
     if (sel!=lastsel) {
       AC_OFF;  RES(PORTB,(sel-1)); uchar tmp1=sel; sel=lastsel;  lastsel=tmp1; pultadr=0;  pult();
     }
                                      }
              
                          }//��� �� �� ����� ������ UART �� ����������
                           
                          
                 
 //--------------- ��������� -------------------
   if (pultadr==45 || pultadr==110) { gro(1); p5;  pultadr=0; }  
   if (pultadr==50 || pultadr==115) { gro(2); p5;  pultadr=0; }  
   
   
                
 
                          
                          
   
   
}
 //------------------------------------------
void source()
{  
 
  
   
  if (sel==1){ resOUT(); resled(); SET(PORTC,1);}
  if (sel==2){ resOUT(); resled(); SET(PORTC,2);}
  if (sel==3){ resOUT(); resled(); SET(PORTC,3);}
  if (sel==4){ resOUT(); resled();SET(PORTC,4);}
  if (sel==5 && mode==0 ){  resOUT(); resled();SET(PORTC,5);}
  
  if (mute!=1 ) if (zader==0) AC_ON;//��� ��
 
   migINI(sel-1, 5 ,0); 
 
}
















void programming (uchar rez)
{  
   if (tekfunc==255) return;
   if (!get)  { getadr(); get=1; }//�������� ����� � �������� ��������������� �������
   if (rez==1)
   {
     writeCOD();
     tekfunc++;  get=0;
    if (tekfunc==12) {  for (uchar i=0; i<10;i++) 
                           {led_all(1); p4; led_all(0);p4; }
                      }
     if (tekfunc>MAXFUNC) {tekfunc=255;led_all(1);}

   }
   
   
   if (keyONsm) { 
                led_all(1); delay_s(1); 
                led_all(0); 
                tekfunc++;  get=0;
                   if (tekfunc==12) {  for (uchar i=0; i<10;i++) 
                           {led_all(1); p4; led_all(0);p4; }
                      }
                if (tekfunc>MAXFUNC) {tekfunc=255;led_all(1);}
               
                 }
     
}
//--------------------------------------------------------------------

void writeCOD()
{
  rprintfStr("write ..");
  led_all(1);delay_s(3);
  uchar adr=getadr();
  led_all(0);
  
       
       k[adr]=cod1; delay_ms(30);
       k[adr+1]=cod2; delay_ms(30);
       k[adr+2]=cod3; delay_ms(30);
       
       rprintfStr("OK !   "); ent;
   
}



 
uchar analizCOD ()
{
 uint i;
  for (i=0; i<MAXEEP-4; i++) 
  {
   // if ((kbuf[i])==cod1)  if ((kbuf[i+1])==cod2) if ((kbuf[i+2])==cod3) return(i);
    if ((k[i])==cod1)  if ((k[i+1])==cod2) if ((k[i+2])==cod3) return(i);   
  }

return(0);
}



void resled(void)
{
  RES(PORTB,0);RES(PORTB,1);RES(PORTB,2);RES(PORTB,3); if (mode==0)RES(PORTB,4);
}


void resOUT(void)
{
  RES(PORTC,1);RES(PORTC,2);RES(PORTC,3);RES(PORTC,4); if (mode==0)RES(PORTC,5);
  p2;//��� �� �� ���� ���������� ����������
}


 
void led_all(bool a)
{
 if (a)
 {
   SET(PORTB,0);SET(PORTB,1);SET(PORTB,2);SET(PORTB,3);SET(PORTB,4);SET(PORTB,5);
   /*AC_ON; */SET(PORTD,7);
 }
 else
  {
   RES(PORTB,0);RES(PORTB,1);RES(PORTB,2);RES(PORTB,3);RES(PORTB,4);RES(PORTB,5);
   AC_OFF; RES(PORTD,7);
 } 
}


void gro(uchar a)
{
  if (modegro!=1) {
  if (a==1) {SET(PORTC,0); delay_us(100);RES(PORTC,0);}
  if (a==2) {SET(PORTD,3); delay_us(100);RES(PORTD,3);}  
                  }
  else  { 
    if (a==1) { if (gro1)  { gro1=0; RES(PORTC,0);  } else { gro1=1; SET(PORTC,0);  } }
    if (a==2) { if (gro2)  { gro2=0; RES(PORTD,3);  } else { gro2=1; SET(PORTD,3);  } }
        }
}






//������������� ������
void iniPORTS()
{
  
 
  //DDRx=0 - �����   PORTx = 0xFF; //���������� ����������� ���������
 //---------------------------------------------------------------
 //DDRx=0xFF - ������    PORTx = 0; //������������� 0 �� ������
 
  
 DDRD = b(11011000);// 0xD8;  //PD3 4 6 7 ������  b11011000
 PORTD = (uchar)~(b(11011000)); 

 
 DDRB = 0x3F; //���� B - �����    6,7-�����
 PORTB = 0x00; 
  
  
  DDRC =0xFF; 
  PORTC = 0x00; //������������� 0 �� ������
  
 
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;  
TCNT0=0x00;
OCR1A=0x00;
OCR1B=0x00;
TCCR1A=0x00;
  SET(TIMSK,TOIE1);//������ ���������� ��� ������������
   TCCR1B=0; TIFR = 0xFF;  
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
//GIMSK=0x00;
//MCUCR=0x00;

SET(MCUCR,0); RES(MCUCR,1);//���������� �� ��������� ������ INT0
SET(GICR,6);//��������� ���������� INT0




// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
//DIDR=0x00;

} 
//************************************************************************
 

void diag()
{
  
  uchar sym = USART_GetChar(); //������ �����
  if (sym=='0') { pr=1;  rprintfStr("-------------- vkluchen kratkiy viviod -------------");  ent;   }

  if (sym=='e') {
    ent;rprintfStr(" ==  EEPROM read == ");ent;
    for (uchar i=0; i<MAXEEP-1; i++) { 
      rprintfFloat(4, i );   rprintfStr(" > ");
       rprintfFloat(9, k[i] ); ent;
                                      }
                }
  
  if (sym) {             //���� ���-�� �������, �� 
      rprintfStr(" get: ");
      USART_SendChar(sym); 

      if (mode==1) rprintfStr("  regim  no source5 >");  
if (write==1) rprintfStr("  regim  PROGRAMMING !!  READY >");  
else rprintfStr("  regim  normal  READY >");  


   

       ent;
     
   
           }
}

