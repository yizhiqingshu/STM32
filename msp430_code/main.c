/***************************************************
采用TI公司的MSP430F5529芯片
使用MSP-EXP430F5529LP开发板
实现的功能为：
1、利用MSP430内部PWM波发生器产生频率为 50~1kHz，占空比为10%~90%的PWM波。 
2、要求频率和占空比通过按键S1和S2分别设置。频 率按50Hz步进，占空比按10%步进。
3、利用MSP430单片机的捕获/比较器测量该PWM波 的频率和占空比，且显示于oled屏幕上。

（这里使用的显示屏是四针的oled12864）
连接方式为SDA口连接P6.5
          SCL口连接P6.0
          同时使用的VCC是3V
 
 P1.2口和P1.4口输出反相的可调频率和周期的PWM波
 P2.0为捕获输入，所以需要连接P1.2口和P2.0口
***************************************************/
#include "MSP430F5529.h"
#include "clk.h"
#include "key.h"
#include "timer.h"
#include "IIC.h"
#include "IO_.h"
#include "menu.h"
/****************需要显示的一系列字符串***************/
  unsigned char Question_1 =0;  
  unsigned char Question_2 =0;  
 unsigned char Question_3 =0;  
  unsigned char Question_4 =0; 
  unsigned char Question_0 =0;
enum key_type key; 
void  main()
{
//  enum key_type key;          
  WDTCTL = WDTPW+WDTHOLD;  // 关闭看门狗
  ClkInit();               //时钟初始化
  KeyInit();               //独立按键初始化
  LCD_Init();          //显示屏初始化
  IO_config();         
  PWM_Init();              //PWM波输出初始化CAIDAN_xianshi();
  
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
  
  
 
  
  


