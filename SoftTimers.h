
//***************************************************************************
//
//***************************************************************************
#define CALIBR 5500//минимальный тик (около 1сек)

 static uchar raz;
 static uchar port=255;
 static uchar razct;

 typedef struct 
   { 
      uint x;
      uint ct;
      uint time;
      bool out;
   }  timers;
 
 extern timers tm1,tm2,tm3;
 
void TimerSet(timers *t, uint tm);
void TimerTick( timers *t);
void migWORK(void);
void migINI(uchar sel,  uchar razp, bool prton);

     
//**************************************************************
//**************************************************************