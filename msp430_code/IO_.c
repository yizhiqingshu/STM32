#include "IO_.h"
#include "IIC.h"
#include  "menu.h"

uint16_t qian_1;
uint16_t qian_2;
uint16_t hou_1;
uint16_t hou_2;

#define right_1 499
#define right_2 100
#define left_1  499
#define left_2  100
#define yanshi_1  80
#define B_C 20 //转弯 直行 补偿时间 

uint16_t jiaodu_tim2[11]={210,183,160,150,140,130,125,120,115,110,105};//10度  时间  第三题 
//uint16_t jiaodu_tim[11]={225+20,210+20,190+20,180+20,170+20,160+20,155+20,150+20,145+20,140+20,135+20};//10度 第三题 

uint16_t pingdi_2[11]={170,180,155,140,130,120,110,105,100,100,93};     //第二题的数据 

uint16_t shiwu_tim[11]={210,190,175,165,155,140,135,130,125,120,115};//


extern unsigned char list;

extern uint16_t model;
unsigned int ab=100;

volatile uint16_t  GO_PWM =140;
extern uint16_t go_pwm;

extern unsigned char Question_1;

//左
//P4.3 --AIN2
//P4.0 --AIN1
//P3.7--BIM1
//P8.2--BIN2
//P1.5--PWMB
//P1.4--PWMA

//右
//P1.2 --PWM A 
//P8.1--AIN2
//P2.3--AIN1
//P3.1--BIN1
//P2.6--BIN2
//P1.3--PWMB

void IO_config(void)
{
 //tim OUT
P2DIR |= BIT6;
P2REN |= BIT6;

P2DIR |= BIT3;
P2REN |= BIT3;

P3DIR |= BIT1;
P3REN |= BIT1;

P3DIR |= BIT7;
P3REN |= BIT7;

P4DIR |= BIT3; 
P4REN |= BIT3;

P4DIR |= BIT0;
P4REN |= BIT0;

P2DIR |= BIT0;
P2REN |= BIT0;

P8DIR |= BIT2;
P8REN |= BIT2;
// FENG MING QI

P6DIR|=BIT4;
P6REN |= BIT4;

// HONG WAI SHU RU 
//
P6DIR &=~BIT1;
P6REN &=~BIT1;

P3DIR &=~BIT3;
P3REN &=~BIT3;


P2DIR &=~BIT4;
P2REN &=~BIT4;

P2DIR &=~BIT5;
P2REN &=~BIT5;

P3DIR &=~BIT4;
P3REN &=~BIT4;

P3DIR &=~BIT5;
P3REN &=~BIT5;

P8DIR &=~BIT1;
P8REN &=~BIT1;

P7DIR &=~BIT4;
P7REN &=~BIT4;


//补偿模块
P2DIR &=~BIT2;
P2REN &=~BIT2;

P3DIR &=~BIT2;
P3REN &=~BIT2;
/////
P2DIR &=~BIT7;
P2REN &=~BIT7;

P7DIR &=~BIT0;
P7REN &=~BIT0;

P4DIR &=~BIT2;
P4REN &=~BIT2;

P3DIR &=~BIT6;
P3REN &=~BIT6;

P4DIR &=~BIT1;
P4REN &=~BIT1;

}
void ZHIXING(void)
{
  //P 1.2 在左，P1.3在右 控制前面轮子 
   //P 1.4 在左，P1.5在右 控制后面轮子 
  TA0CCR1 = GO_PWM;//p1.2 正反转 
  P2OUT&= ~BIT0;//左上电机
  P2OUT |=BIT3;// 2.3高电平 2.0 低电平 左上电机正转
  
  TA0CCR2 = GO_PWM;//p1.3
  P2OUT&=~BIT6;//左下电机
  P3OUT|= BIT1;//3.1 高电平 2.6 低电平 左下电机正转
  
  TA0CCR3 = GO_PWM;//p1.4
  P4OUT|=BIT0;//右上电机
  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
  
  TA0CCR4 = GO_PWM;//p1.5
  P8OUT|=BIT2;//右下电机
  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
}

void TURN_RIGHT(unsigned int AB_R)
{ 
  //P 1.2 在左，P1.3在右 控制前面轮子 
  //P 1.4 在左，P1.5在右 控制后面轮子 
  TA0CCR1 = AB_R;//p1.2 正反转 
  P2OUT&= ~BIT0;//左上电机
  P2OUT |=BIT3;// 2.3高电平 2.0 低电平 左上电机正转

  
  TA0CCR2 = AB_R;//p1.3
  P2OUT&=~BIT6;//左下电机
  P3OUT|= BIT1;//3.1 高电平 2.6 低电平 左下电机正转
  
  TA0CCR3 = 0;//p1.4
  P4OUT|=BIT0;//右上电机
  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
  
  TA0CCR4 = 0;//p1.5
  P8OUT|=BIT2;//右下电机
  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
}
void TURN_LEFT(unsigned int AB_L)
{
  //P 1.2 在左，P1.3在右 控制前面轮子 
   //P 1.4 在左，P1.5在右 控制后面轮子 
  TA0CCR1 = 0;//p1.2 正反转 
  P2OUT&= ~BIT3;//左上电机
  P2OUT|=BIT0;// 2.0高电平 2.3 低电平 左上电机正转
  
  TA0CCR2 = 0;//p1.3  修改 反转
  P3OUT|=BIT1;//左下电机
  P2OUT&=~BIT6;//2.6 高电平 3.1 低电平 左下电机正转

  
  TA0CCR3 = AB_L;//p1.4
  P4OUT|=BIT0;//右上电机
  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
  
  TA0CCR4 = AB_L;//p1.5
  P8OUT|=BIT2;//右下电机
  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
}

void STOP(void)
{  
  TA0CCR1 = 0;//p1.2 正反转 
  P2OUT&= ~BIT3;//左上电机
  P2OUT&=~BIT0;// 2.0高电平 2.3 低电平 左上电机正转
  
  TA0CCR2 =0;//p1.3
  P3OUT&=~BIT1;//左下电机
  P2OUT&=~BIT6;//2.6 高电平 3.1 低电平 左下电机正转
  
  TA0CCR3 = 0;//p1.4
  P4OUT&=~BIT3;//右上电机
  P4OUT&=~BIT0;//4.3高电平 4.0 低电平 右上电机正转
  
  TA0CCR4 = 0;//p1.5
  P3OUT&=~BIT7;//右下电机
  P8OUT&=~BIT2;//3.7高电平 8.2低电平 右下电机正转
          P6OUT |=BIT4;
          delay_ms(1000);
          P6OUT &=~BIT4;
          delay_ms(1000);
          P6OUT &=~BIT4;
          delay_ms(1000);
          P6OUT |=BIT4;
          delay_ms(500);
          P6OUT &=~BIT4;
          delay_ms(500);
          
          Question_2=0;
          Question_1=0;
          Question_3=0;
          Question_4=0;
}
unsigned char string1[]={"ab:"};   //当前pwm--ab
unsigned char string2[]={"model:"};//设定pwm
unsigned char string3[]={"s:"};//当前pwm--now_pwm
unsigned char string4[]={"mode"};//模式设置 
unsigned char string5[]={"n:"};//设定pwm--set_pwm
unsigned char string6[]={"tim:"};//设定tim
unsigned char string7[]={"angle"};//设定angle
unsigned char string8[]={"t15:"};//设定15度 
extern unsigned int ab;
void CAIDAN_xianshi(void)
{
//  if(list==1)
//  { 
    LCD_ShowString(0,0,string1,12);
    LCD_ShowNum(25,0,ab,3,12);//实际转弯pwm
    
    LCD_ShowString(62,0,string6,12);
    LCD_ShowNum(100,0,time,3,12);//时间设定
    
    LCD_ShowString(0,2,string2,12);
    LCD_ShowNum(50,2,model,3,12);//设置转弯 pwm
    
    LCD_ShowString(70,2,string8,12);
    LCD_ShowNum(108,2,tim_15,3,12);//设置转弯 pwm
    
    LCD_ShowString(0,4,string3,12);
    LCD_ShowNum(12,4,go_pwm,3,12);//设定zhixing pwm
    
    LCD_ShowString(50,4,string5,12);
    LCD_ShowNum(62,4,GO_PWM,3,12);//实际zhixing pwm
    
    LCD_ShowString(0,6,string4,12);
    LCD_ShowNum(30,6,list,1,12);//模式选择
    
    LCD_ShowString(62,6,string7,12);
    LCD_ShowNum(100,6,Angle,3,12);//角度
//  }
// if(list==2)
// {
//    LCD_ShowString(0,0,string1,12);
//    LCD_ShowNum(50,0,list,3,16);
//    
//    LCD_ShowString(0,2,string2,12);
//    LCD_ShowNum(50,2,model,3,16);
//    
//    LCD_ShowString(0,4,string3,12);
//    LCD_ShowNum(50,4,time,3,16);
//    
//    LCD_ShowString(0,6,string4,12);
//    LCD_ShowNum(50,6,Angle,3,16);
// }
// if(list==3)
// {
//    LCD_ShowString(0,0,string1,12);
//    LCD_ShowNum(50,0,list,3,16);
//    
//    LCD_ShowString(0,2,string2,12);
//    LCD_ShowNum(50,2,model,3,16);
//    
//    LCD_ShowString(0,4,string3,12);
//    LCD_ShowNum(50,4,time,3,16);
//    
//    LCD_ShowString(0,6,string4,12);
//    LCD_ShowNum(50,6,Angle,3,16);
// }
// if(list==4)
// {
//    LCD_ShowString(0,0,string1,12);
//    LCD_ShowNum(50,0,list,3,16);
//    
//    LCD_ShowString(0,2,string2,12);
//    LCD_ShowNum(50,2,model,3,16);
//    
//    LCD_ShowString(0,4,string3,12);
//    LCD_ShowNum(50,4,time,3,16);
//    
//    LCD_ShowString(0,6,string4,12);
//    LCD_ShowNum(50,6,Angle,3,16);
// }
}
void list_1(void)
{
   ZHIXING();
    if(P6_1_R==1)//1
    { TURN_RIGHT(right_1);
       delay_ms(yanshi_1);}
     if(P3_4_R==1)//补偿1
    { TURN_RIGHT(right_1);
      delay_ms(yanshi_1); }
    if(P2_7_L==1)
    { TURN_LEFT(left_1);
       delay_ms(yanshi_1);}
    if(P3_3_R==1)//2
    { TURN_RIGHT(right_1);
       delay_ms(120);}
   
//    if(P2_2_L==1)
//    { TURN_LEFT(left_1);
//       delay_ms(130);}
    if(P7_0_L==1)
    { TURN_LEFT(left_1);
       delay_ms(130);}
    
     if(P2_4_R==1)//3
    { TURN_RIGHT(right_1);
       delay_ms(150);}
        if(P4_2_L==1)
    { TURN_LEFT(left_1);
       delay_ms(150);}
    if(P3_2_Q==1)
    {
    TURN_LEFT(left_1);
      delay_ms(120);}
    
    
    if(P2_5_R==1)//4
    { TURN_RIGHT(right_1);
       delay_ms(200);}
     if(P3_6_L==1)
    { TURN_LEFT(left_1);
       delay_ms(200);}

    
    if(P7_4_R==1)//5
    { TURN_RIGHT(right_1);
      delay_ms(250);}
    if(P4_1_L==1)//5
    { TURN_LEFT(left_1);
      delay_ms(200);}
    if(STOP_||STOP_1)
    {STOP();}
      if(P3_5_R==1)//补偿2
    { 
      TURN_RIGHT(right_1);
      delay_ms(20);
      
      if(STOP_||STOP_1)
      {STOP();}
      delay_ms(130);}

}
void list_Angle(void)

{
     ZHIXING();
    if(P6_1_R==1)//1
    { TURN_RIGHT_1(right_1);
      delay_ms(150);}
     if(P3_4_R==1)//补偿1
    { TURN_RIGHT_1(right_1);
      delay_ms(150); }
    if(P2_7_L==1)
    { TURN_LEFT(left_1);
       delay_ms(120);}
    
    if(P3_3_R==1)//2
    { TURN_RIGHT_1(right_1);
       delay_ms(150);}
     if(P3_5_R==1)//补偿2
    { 
      TURN_RIGHT_1(right_1);
      delay_ms(20);
      if(STOP_||STOP_1||STOP_2)
      {STOP();}
      delay_ms(110);}
    if(P2_2_L==1)
    { 
      TURN_LEFT(left_1);
      delay_ms(20);
      if(STOP_||STOP_1||STOP_2)
      {STOP();}
       delay_ms(110);}
    if(P7_0_L==1)
    { TURN_LEFT_1(left_1);
       delay_ms(150);}
    
     if(P2_4_R==1)//3
    { TURN_RIGHT_1(right_1);
       delay_ms(180);}
        if(P4_2_L==1)
    { TURN_LEFT_1(left_1);
       delay_ms(180);}
    if(P3_2_Q==1)
    {
      
    TURN_LEFT_1(left_1);
    delay_ms(20);
    if(STOP_||STOP_1||STOP_2||STOP_3)
    {STOP();}
    delay_ms(140);}

    if(P2_5_R==1)//4
    { TURN_RIGHT_1(right_1);
       delay_ms(200);}
     if(P3_6_L==1)
    { TURN_LEFT_1(left_1);
       delay_ms(200);}

    
    if(P7_4_R==1)//5
    { TURN_RIGHT_1(right_1);
      delay_ms(220);}
    if(P4_1_L==1)//5
    { TURN_RIGHT_1(right_1);
      delay_ms(220);}
    if(STOP_||STOP_1||STOP_2||STOP_3)
    {STOP();}
   

}

void Mode_2(uint16_t SET_tim)
{
  uint16_t n=0;
//  n=155-(SET_tim-10)*10/1.5;
  n=SET_tim-10;
  GO_PWM=pingdi_2[n];
}

void Mode_3_jiao(uint16_t SET_tim)
{
uint16_t M=0;
M=SET_tim-10;
GO_PWM=jiaodu_tim2[M];//
}

void SHIwu_Mode(uint16_t set_tim)
{ uint16_t tim=0;
  tim=set_tim-10;
  GO_PWM=shiwu_tim[tim];
}

void TURN_RIGHT_1(unsigned int AB_R)//右转
{
  //P 1.2 在左，P1.3在右 控制前面轮子 
   //P 1.4 在左，P1.5在右 控制后面轮子 
  TA0CCR1 = AB_R;//p1.2 正反转 
  P2OUT&= ~BIT0;//左上电机
  P2OUT |=BIT3;// 2.3高电平 2.0 低电平 左上电机正转

  TA0CCR2 = AB_R;//p1.3
  P2OUT&=~BIT6;//左下电机
  P3OUT|= BIT1;//3.1 高电平 2.6 低电平 左下电机正转
  
  TA0CCR3 = ab;//p1.4
  P4OUT&=~BIT3;//右上电机
  P4OUT|=BIT0;//4.0高电平 4.3低电平 右上电机正转
  
  TA0CCR4 = ab+60;//p1.5
  P8OUT|=BIT2;//右下电机
  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
}

void TURN_LEFT_1(unsigned int AB_L)//左转
{
 //P 1.2 在左，P1.3在右 控制前面轮子 
 //P 1.4 在左，P1.5在右 控制后面轮子 
  TA0CCR1 = ab;//p1.2 正反转 
  P2OUT&= ~BIT3;//左上电机
  P2OUT|=BIT0;// 2.0高电平 2.3 低电平 左上电机正转
  
  TA0CCR2 = ab+60;//p1.3  修改 反转
  P2OUT|=BIT6;//左下电机
  P3OUT&=~BIT1;//2.6 高电平 3.1 低电平 左下电机正转

  
  TA0CCR3 = AB_L;//p1.4
  P4OUT|=BIT0;//右上电机
  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
  
  TA0CCR4 = AB_L;//p1.5
  P8OUT|=BIT2;//右下电机
  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
  
}


//void TURN_RIGHT_1(unsigned int AB_R)//右转
//{
//  //P 1.2 在左，P1.3在右 控制前面轮子 
//   //P 1.4 在左，P1.5在右 控制后面轮子 
//  TA0CCR1 = AB_R;//p1.2 正反转 
//  P2OUT&= ~BIT0;//左上电机
//  P2OUT |=BIT3;// 2.3高电平 2.0 低电平 左上电机正转
//
//  TA0CCR2 = AB_R;//p1.3
//  P2OUT&=~BIT6;//左下电机
//  P3OUT|= BIT1;//3.1 高电平 2.6 低电平 左下电机正转
//  
//  TA0CCR3 = ab;//p1.4
//  P4OUT|=BIT0;//右上电机
//  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
//  
//  TA0CCR4 = ab+40;//p1.5
//  P8OUT|=BIT2;//右下电机
//  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
//}
//
//void TURN_LEFT_1(unsigned int AB_L)//左转
//{
// //P 1.2 在左，P1.3在右 控制前面轮子 
// //P 1.4 在左，P1.5在右 控制后面轮子 
//  TA0CCR1 = ab;//p1.2 正反转 
//  P2OUT&= ~BIT3;//左上电机
//  P2OUT|=BIT0;// 2.0高电平 2.3 低电平 左上电机正转
//  
//  TA0CCR2 = ab+40;//p1.3  修改 反转
//  P3OUT|=BIT1;//左下电机
//  P2OUT&=~BIT6;//2.6 高电平 3.1 低电平 左下电机正转
//
//  
//  TA0CCR3 = AB_L;//p1.4
//  P4OUT|=BIT0;//右上电机
//  P4OUT&=~BIT3;//4.0高电平 4.3低电平 右上电机正转
//  
//  TA0CCR4 = AB_L;//p1.5
//  P8OUT|=BIT2;//右下电机
//  P3OUT&=~BIT7;//3.7低电平 8.2高电平 右下电机正转
//  
//}
