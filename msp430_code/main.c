/***************************************************
����TI��˾��MSP430F5529оƬ
ʹ��MSP-EXP430F5529LP������
ʵ�ֵĹ���Ϊ��
1������MSP430�ڲ�PWM������������Ƶ��Ϊ 50~1kHz��ռ�ձ�Ϊ10%~90%��PWM���� 
2��Ҫ��Ƶ�ʺ�ռ�ձ�ͨ������S1��S2�ֱ����á�Ƶ �ʰ�50Hz������ռ�ձȰ�10%������
3������MSP430��Ƭ���Ĳ���/�Ƚ���������PWM�� ��Ƶ�ʺ�ռ�ձȣ�����ʾ��oled��Ļ�ϡ�

������ʹ�õ���ʾ���������oled12864��
���ӷ�ʽΪSDA������P6.5
          SCL������P6.0
          ͬʱʹ�õ�VCC��3V
 
 P1.2�ں�P1.4���������Ŀɵ�Ƶ�ʺ����ڵ�PWM��
 P2.0Ϊ�������룬������Ҫ����P1.2�ں�P2.0��
***************************************************/
#include "MSP430F5529.h"
#include "clk.h"
#include "key.h"
#include "timer.h"
#include "IIC.h"
#include "IO_.h"
#include "menu.h"
/****************��Ҫ��ʾ��һϵ���ַ���***************/
  unsigned char Question_1 =0;  
  unsigned char Question_2 =0;  
 unsigned char Question_3 =0;  
  unsigned char Question_4 =0; 
  unsigned char Question_0 =0;
enum key_type key; 
void  main()
{
//  enum key_type key;          
  WDTCTL = WDTPW+WDTHOLD;  // �رտ��Ź�
  ClkInit();               //ʱ�ӳ�ʼ��
  KeyInit();               //����������ʼ��
  LCD_Init();          //��ʾ����ʼ��
  IO_config();         
  PWM_Init();              //PWM�������ʼ��CAIDAN_xianshi();
  
  while(1)
  {     
    CAIDAN_xianshi();
    key = KeyScan();
    if( key != NOKEY )
    {
      switch(key)
      {
       case KEY1_ : 
          {
            key1_down();
            break;
          }      
        case KEY2_ :   
          {
           key2_down();
            break;
          }
      case KEY3_ :
        {
        key3_down();
          break;
        }
        case KEY4_:
          {
         key4_down();
          break;
          }
         }  //switch
    }  //if_1
    
      if(Question_0==1)
         {
//           list_1();
           
          list_Angle();
         }
    if(Question_1==1)
         {
//           list_1();
          list_Angle();
         }
    if(Question_2==1)
    {
   list_1();
//    list_Angle();
    }
    
    if(Question_3==1)
    {
     Mode_3_jiao(Angle);
//     list_Angle();
     list_1();
    }
    if(Question_4==1)
    {
    SHIwu_Mode(tim_15);
//    list_Angle();
    list_1();
    }
  }//while
}//main
  
  
 
  
  


