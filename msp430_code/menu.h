#ifndef MENU_H
#define MENU_H
#include "MSP430F5529.h"
#include "IO_.h"



extern unsigned char Question_0 ;  
extern unsigned char Question_1 ;  
extern unsigned char Question_2 ;  
extern unsigned char Question_3 ;  
extern unsigned char Question_4 ;  

extern unsigned char tim_last;// ��¼��һ�ε�ѹֵ ����pWM�Ӽ�

void key1_down(void);
void key2_down(void);
void key3_down(void);
void key4_down(void);
#endif

