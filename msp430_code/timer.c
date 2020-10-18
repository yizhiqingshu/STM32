/************************************************************
  定时器的设置
  文件名称：                timer.c
  文件概述：                对TA0输出PWM波 TA1进行输入捕获的配置工作
  包含的头文件及概述：      timer.h ：函数声明及部分宏定义                         
  引脚声明：                
                            TA0 PWM波输出口   ：P1.2
                            TA1 输入捕获输入口：P2.0
//时钟4M 
*************************************************************/ 


#include 	"msp430f5529.h"
#include  	"timer.h"
char flag=0;                       //用于标记当前捕获状态 0:就绪 1：捕获到一个上升沿 2：捕获到一个下降沿 
unsigned int pos_time=0;          //用于记录正脉宽
unsigned int period  =0;          //用于记录周期

//volatile unsigned int qian_1=200;
//volatile unsigned int qian_2=200;
//volatile unsigned int hou_1=200;
//volatile unsigned int hou_2=200;

/******************

PWM波初始化
输出两种反相的PWM波

********************/
void PWM_Init( void )
{
        
        P1DIR |= BIT2; //配置P1.2复用为定时器TA0.1
        P1SEL |= BIT2; //配置P1.2为输出
        P1DIR |= BIT3; //dir 设置为1 复用为外设 tim
        P1SEL |= BIT3;// sel 设置为1 复用外设 tim 输出
        P1DIR |= BIT4; //配置P1.4复用为定时器TA0.3
        P1SEL |= BIT4; //配置P1.4为输出
        P1DIR |= BIT5;
        P1SEL |= BIT5;
        TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_0;//使用SMCLK为时钟源 UP计数模式 1分频
        TA0CCTL1 = OUTMOD_7 ; //TA0输出模式7
        TA0CCTL2 = OUTMOD_7 ; 
        TA0CCTL3 = OUTMOD_7 ; //TA3输出模式3
        TA0CCTL4 = OUTMOD_7 ; 
        TA0CCR0 = 500 ;   //初始化频率8K赫兹
        TA0CCR1 = 0 ;    //初始化为 占空比 20% 频率 8k
        TA0CCR2 = 0 ;
        TA0CCR3 = 0 ;
        TA0CCR4 = 0 ;
        
}





