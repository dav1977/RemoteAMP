
//***************************************************************************
//
//***************************************************************************
//#define CALIBR 5500//����������� ��� (����� 1���)

static uchar raz;
static uchar port;
static uchar razct;

 typedef struct 
   { 
    //  long x;
      long ct;
      long time;
      bool out;
   }  timers;
 
 extern timers tm1,tm2,tm3, tm4,tm5,tm6;
 
 void TimerReset(timers *t);
void TimerSet(timers *t, long tm);
void TimerTick( timers *t);
void migWORK(void);
void migINI(uchar sel,  uchar razp, bool prton);

     
//**************************************************************
//**************************************************************