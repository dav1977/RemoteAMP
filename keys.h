#include "main.h"

#define  keyON ( BIT(PIND,5)==0 && BIT(PIND,0)!=0 && BIT(PIND,1)!=0 )
#define  keyONsm BIT(PIND,5)==0
#define  keySEL ( BIT(PIND,1)==0  && BIT(PIND,5)!=0 )
#define  keySELsm BIT(PIND,1)==0 
#define  keyMUTE ( BIT(PIND,1)==0  && BIT(PIND,5)==0 )
#define  keyMUTEsm BIT(PIND,1)==0 
#define  keyAOFF ( BIT(PIND,0)==0  && BIT(PIND,5)==0 ) 
#define  keyAOFFsm BIT(PIND,0)==0 

/*

#define StartADC() ADCSR |= (1<<ADSC)  
#define StopADC() ADCSR |= (0<<ADSC)  


#define KEY_NULL  0
#define KEY_S1    1
#define KEY_S2    2
#define KEY_S3    3
#define KEY_S4    4


uchar tt;
//кнопочный буфер
volatile unsigned char KeyBuf;
 
  void inikeys(void);
  
  void inikeys()
  {
  //инициализируем АЦП
  //ион - напряжение питания, выравнивание влево, нулевой канал
  ADMUX = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
  //вкл. ацп, режим одиночного преобразования, разрешение прерывания, частота преобр. = FCPU/128
  ADCSR = (1<<ADEN)|(0<<ADSC)|(0<<ADFR)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);


  // StartADC();

  }
//////////////////////////////////////////////////////////////////////////////   
   void keys(void);
  void keys()
  {//основной цикл программы - опрос кнопочного буфера
  
    
    if (tt!=0){ rprintfFloat(10,  tt);   USART_SendChar(0x0D);}
    
    if (tmp)
    {
      tmp--;
      PORTC = ~(1<<tmp);
    }
    else
      PORTC = 0xff;



    
    
    
    
    
    
  } 
    
unsigned char comp = 0;

#pragma vector=ADC_vect
__interrupt void adc_my(void) 
{
  unsigned char AdcBuf;   
  unsigned char Key;
  static unsigned char LastState;
  
  //считываем старший регистр АЦП
  AdcBuf = ADCH;
  
  tt=AdcBuf;
  
  //опеределяем в какой диапазон он попал
  if (AdcBuf > 240) 
    Key = KEY_S4;
  else if (AdcBuf > 180) 
    Key = KEY_S3;
  else if (AdcBuf > 120) 
    Key = KEY_S2;
  else if (AdcBuf > 50) 
    Key = KEY_S1;
  else 
    Key = KEY_NULL;
  
  //защита от дребезга и не только. если нажата какая-нибудь кнопка
  //сравниваем совпадают ли текущее состояние и предыдущее
  //если совпадают - проверяем счетчик comp, если нет обнуляем его
  //кнопка считается нажатой если она удерживается в течении 100
  //преобразований АЦП
  if (Key)
  { 
    if (Key == LastState)
    {
      if (comp > 100)
      {  KeyBuf = Key;  }      
      else 
        comp++;
    }
    else
    {
      LastState = Key;
      comp = 0;
    }
  }
  else
  {
    comp = 0;
    KeyBuf = KEY_NULL;
    LastState = KEY_NULL;
  }

  //запускаем преобразование и выходим
  StartADC();
}





	
	
	
	
	
	
						
  uchar comp = 0;
  uchar Key,KeyBuf;
  static uchar LastState;
  
  uchar readkey(void);
 
  
uchar  readkey() {  
  
  if (Key)
  { 
    if (Key == LastState)
    {
      if (comp > 100)
        KeyBuf = Key;      
      else 
        comp++;
    }
    else
    {
      LastState = Key;
      comp = 0;
    }
  }
  else
  {
    comp = 0;
    KeyBuf = 0;
    LastState = 0;
  }
   return(KeyBuf);
  }
  
  */