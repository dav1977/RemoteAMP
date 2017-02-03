//***************************************************************************
//
//***************************************************************************
ulong T1,T2,T3;
bool T1end,T2end,T3end;
ulong T1max,T2max,T3max;
uint T1x,T2x,T3x;
ulong Calibr=5500;//минимальный тик (около 1сек)
 static bool sost=0;
  static uchar raz;
 static uchar port=255;
 static uchar razct;
/*
#pragma vector = TIMER0_OVF_vect 
__interrupt void funTIMER0_OVF_vect(void)
{
   
 
}
*/
//**************************************************************
//**************************************************************
void ResetT1(void)
{
  T1=0;T1x=0;  T1end=0;
}
  

void iniT1(ulong max)
{
 //инициализация таймера Т0 - прерывания каждую ms
 // TIMSK = (1<<OCIE0);
 // TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(0<<COM00)|(0<<CS02)|(1<<CS01)|(1<<CS00);
 // TCNT0 = 0;
 // OCR0 = 0x7d;

  T1max=max; ResetT1();
}


void WorkT1(void)
{
  if (T1end) return;
  T1x++; if (T1x>=Calibr) { T1x=0; T1++; }
  if (T1>=T1max) T1end=1;
}

//**************************************************************
//**************************************************************

void ResetT2(void)
{
  T2=0;T2x=0;  T2end=0;
}
  

void iniT2(ulong max)
{
 //инициализация таймера Т0 - прерывания каждую ms
 // TIMSK = (1<<OCIE0);
 // TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(0<<COM00)|(0<<CS02)|(1<<CS01)|(1<<CS00);
 // TCNT0 = 0;
 // OCR0 = 0x7d;

  T2max=max; ResetT2();
}


void WorkT2(void)
{
  if (T2end) return;
  T2x++; if (T2x>=(Calibr/1000)) { T2x=0; T2++; }
  if (T2>=T2max) T2end=1;
}

void migINI(uchar sel,  uchar razp, bool prton)//мигание sel - кол-во раз
{
  SET(PORTB,sel);//вкл-ем для ускорения индикации
  
  
  if (port!=255) {  //если все еще мигает
     
    if (prton)SET(PORTB,port); //фиксируем чтобы горел
    else RES(PORTB,port);
                }
  
  
  raz=razp;  port=sel; razct=0;
  iniT2(5);
  T2end=1;
  
}

void migWORK(void)//мигание 
{
  WorkT2();
  if (T2end==1 && port!=255)  {
       if (sost!=1)  {sost=1; iniT2(200); SET(PORTB,port); razct++;}
  else if (sost!=0)  {sost=0; iniT2(200); RES(PORTB,port);}
                              }
  if (razct>=raz) { T2end=1; port=255;}
}
//uchar migSEL(void){ return(port);} //возвращает текущий мигающий порт
//**************************************************************
//**************************************************************