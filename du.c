//***************************************************************************
//
//  Author(s)...: dav COBRA 
//
//  Target(s)...: ATMega8
//
//  Compiler....: 6 40
//
//  Description.: ������������� ������� �� v1.25
//
//  Data........: 2014
//
//***************************************************************************
#include <stdbool.h>//��������� bool
#include "iom8.h"//<ioavr.h>
#include <inavr.h>
#include <intrinsics.h> 
#include "init.h"
#include "usart.h"
#include "main.h"
#include "eeprom.h"
#include "du.h"

  static uchar  perepoln=0;//���-�� ������������ ��������
  static uchar t1=0,t2=0;
  static bool ini; 
  uint dim1[MAX],dim2[MAX];
  char ct=0;
  uint minimallen;    
  float len[MAX];
  static bool intok,big;
 
  bool cod_ok=0;
  uchar c1,c2,c3;
  char ind=1;

 //*****************************************************************
 // init
 //*****************************************************************
   void du_init(void)
   {
     ini=1;  intok=0;
     //TCCR1B = (0<<CS02)|(1<<CS01)|(1<<CS00); //���� �������
     TCCR1B = (0<<CS02)|(0<<CS01)|(1<<CS00); //���� �������
     ct=0;
   }
 //*****************************************************************
 //  INT
 //*****************************************************************
//���������� ��� ��������� ������� �� ����
#pragma vector = INT0_vect
__interrupt void funINT0_vect(void)
{
  intok=1; 
  //if (readint!=0){  last=TCNT1L;   readint=0; }
  t1 = TCNT1L;  t2 = TCNT1H; 
  if (t1!=0) { TCNT1H=0;TCNT1L=0;}
     
}
//*****************************************************************
//  ������ ����������
//*****************************************************************
void analiz_INT()
{
  // static bool state;
      // if (state==1) {RES(PORTB,5); state=0; }   else {SET(PORTB,5); state=1;}

        dim1[ct]=t1;  dim2[ct]=t2; ct++;
        if (ct>=MAX-1) ct--;  //������� ������� ������� ������������ ������ ��� ���������
        intok=0;


}
//*****************************************************************
//  ����� ���� �� ���������
//*****************************************************************
void PEREP()
{
 static bool state2;
 uchar i;
 
  //if (state2==1) {RES(PORTB,2); state2=0; }   else {SET(PORTB,2); state2=1;}
       
      cod1=0;cod2=0;cod3=0; 
      c1=0; c2=0; c3=0;  //sst=0;
      minimallen=65535;   
     
      if (ct>(MAX-1)) {  rprintfStr(" error ct big ="); rprintfFloat(6,  ct); }
                
      if ((ct>5 && big==0)|| big==1) 
      {//�� 5 ������� ����������� ��������� ���
        
          for (i=1; i<ct; i++) //���� ���������� �����
          {  
                len[i]=( dim1[i]+ (256*dim2[i])  );           
                if (len[i]>900  && len[i]<(float)minimallen)  minimallen=(uint)len[i];
          }
     
           for (i=1; i<ct; i++) 
           { //for 
             uint tr;
             tr=( dim1[i]+ (256*dim2[i]));
             len[i]=(float)tr/minimallen;       
             if (len[i]!=0)   coding(i, pr);
           }//for
      }//�� 5 ������� ����������� 
      
      //�������
       for (i=0; i<MAX; i++) {dim1[i]=0;dim2[i]=0;len[i]=0;}
       perepoln=0;  t1=0; t2=0; ct=0; big=0;     
       
    if (pr==1 && cod_ok!=0)     
     {//diag
              rprintfStr("  /   cod1= ");
              rprintfFloat(6,  cod1);
              rprintfStr("/   cod2= ");
              rprintfFloat(6,  cod2);
              rprintfStr("/   cod3= ");
              rprintfFloat(6,  cod3);
              ent;
                                
     }//diag
 
}

///////////////////////////////////////////////////////////////
//  main
//////////////////////////////////////////////////////////////
  bool remote_main() 
  {   
    cod_ok=0;//������� ���������� ����
    
    if (ini!=1) du_init();    
    if (intok!=0) analiz_INT();  //INT ������� ���������
    
    if (perepoln!=0 ) 
    {//�������� ������������, ������ ������ ����������
      PEREP();
    }   
     return(cod_ok);  
  }


///////////////////////////////////////////////////////////////////       
//                             ���������
///////////////////////////////////////////////////////////////////
  void coding(uint i, uchar pr)  
  {
 
    
    float v=len[i];
             
            //  sst=sst+v;
       if (i>1) {
          
  //-------------   ������  ������-������  ------------------
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
         
         
      //-----   ������ v2  �� ������������� ����� -------  
#define   set1 SET(cod1,c1);c1++   
#define   set2 SET(cod2,c2);c2++  
#define   set3 SET(cod3,c3);c3++  
         
        
       //������ �������� ����� 0.5 ������, �.�. ��� ���������
          if (ind==3) { 
            
            if (v<1.5) cod3=cod3+i;
           if (v>=1.5 && v<2) { set3; c3++;    } else
           if (v>=2 && v<3)   { set3; cod3=cod3+i;  c3++; } else
           if (v>=3 && v<5)   { set3; cod3=cod3+i+i;  c3++; if (c3<=14) {set3; cod3=cod3+i;   c3++; }  }   else                                  
           if (v>5 && v<7)    { c3++;   if (c3<=15)  c3++; }
         
            
           if (c3>=16) {ind=1; cod1=cod1<<2; cod2=cod2<<2; c1=0; c2=0; c3=0;}//����� �� �����
        
                     }
         
                
          if (ind==2) { 
          
           if (v<1.5) cod2=cod2+i;
           if (v>=1.5 && v<2) { set2; c2++;  cod2=cod2+i;  } else
           if (v>=2 && v<3)   { set2; cod2=cod2+i;  c2++; } else
           if (v>=3 && v<5)   { set2; cod2=cod2+i+i;  c2++; if (c2<=14) { set2; cod2=cod2+i;  c2++; }  }   else                                  
           if (v>5 && v<7)    { c2++;   if (c2<=15)  c2++; }
         
                if (c2>=16) ind=3;
                     }
                
         if (ind==1) { 
           
           if (v<1.5) cod1=cod1+i;
           if (v>=1.5 && v<2) { set1; c1++;  cod1=cod1+i;  } else
           if (v>=2 && v<3)   { set1; cod1=cod1+i;  c1++; } else
           if (v>=3 && v<5)   { set1; cod1=cod1+i+i;  c1++; if (c1<=14) { set1; cod1=cod1+i; c1++; }  }   else                                  
           if (v>5 && v<7)    { c1++;   if (c1<=15)  c1++; }
         
                if (c1>=16) ind=2;
                     }
          
         
        
         
      
             cod_ok=1;//��� �����         
         
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
                   ent;
                }
         
         
                   }
       
       
       
  
  }
  

 //������������ ������� ����� 130��  (1/(4000000/8)*65535)
#pragma vector = TIMER1_OVF_vect
__interrupt void funTIMER1_OVF_vect(void)
{
   //TIFR = 0xFF; - � ���������� ����������� ���
  
  perepoln=1;   
 
}


