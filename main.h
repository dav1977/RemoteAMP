

#define acon 20000;//время включения АС при подаче питания
#define MAXFUNC 23  //последний(включительно)действующий tekfunc(кол-во фукций)
#define AC_ON    SET(PORTD,6)
#define AC_OFF   RES(PORTD,6)


void diag(void);
void led_all(bool a);
void resled(void);
void source(void);
void resOUT(void);  
void gro(uchar a);
void main_logic(void);
void main_power(uchar pult);
void writeCOD(void);
uchar analizCOD(void);
void programming(uchar rez);
uchar getadr(void);


extern bool mode_programming, on; 
extern uchar pr;



//-----------------------------