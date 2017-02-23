
//***************************************************************************
//
//***************************************************************************
#define CALIBR 5500//����������� ��� (����� 1���)

 static uchar raz;
 static uchar port=255;
 static uchar razct;

 typedef struct 
   { 
      long x;
      long ct;
      long time;
      bool out;
   }  timers;
 
 extern timers tm1,tm2,tm3;
 
void TimerSet(timers *t, uint tm);
void TimerTick( timers *t);
void migWORK(void);
void migINI(uchar sel,  uchar razp, bool prton);

     
//**************************************************************
//**************************************************************