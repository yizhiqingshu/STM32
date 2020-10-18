#ifndef _IO_
#define _IO_
#include  "MSP430F5529.h"

#define CPU_F                               ((double)4000000) 
#define delay_us(x)                       __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0)) 



#define   uint16_t unsigned int
#define uint8_t unsigned char

extern uint16_t time;
extern uint16_t tim_15;
extern uint8_t  Angle;

#define  P6_1_R  (!(P6IN&BIT1))//P6.1 
#define  P3_3_R  (!(P3IN&BIT3))//P3.3
#define  P2_4_R  (!(P2IN&BIT4))//P2.4
#define  P2_5_R  (!(P2IN&BIT5))//P2.5

#define  P7_4_R  (!(P7IN&BIT4))//P7.4

#define  P3_4_R  (!(P3IN&BIT4))//P3.4
#define  P3_5_R  (!(P3IN&BIT5))//P3.5
#define  P8_1_R  (!(P8IN&BIT1))//P8.1
#define  P2_2_L  (!(P2IN&BIT2)) //P2.7
#define  P3_2_Q   (!(P3IN&BIT2))

#define  P2_7_L  (!(P2IN&BIT7)) //P2.7
#define  P7_0_L  (!(P7IN&BIT0)) //P7.0
#define  P4_2_L  (!(P4IN&BIT2)) //P4.2
#define  P3_6_L  (!(P3IN&BIT6)) //P3.6

#define  P4_1_L  (!(P4IN&BIT1)) //P4.1

#define STOP_   (!((P2IN&BIT2)||(P8IN&BIT1)))
#define STOP_1  (!((P8IN&BIT1)||(P3IN&BIT5)))
#define STOP_2  (!((P2IN&BIT2)||(P3IN&BIT2)))
#define STOP_3  (!((P6IN&BIT1)||(P2IN&BIT7)))
//#define STOP_2  (!((P2IN&BIT2)||(P8IN&BIT1)))

void IO_config(void);// IO 端口配置
void STOP(void);// 停车
void CAIDAN_xianshi(void);// 菜单显示
void ZHIXING(void);//直走
void TURN_LEFT(unsigned int AB_L);//左转
void TURN_RIGHT(unsigned int AB_R);//右转

void Mode_2(uint16_t SET_tim);
void Mode_3_jiao(uint16_t SET_tim);

void SHIwu_Mode(uint16_t set_tim);
void TURN_LEFT_1(unsigned int AB_L);//左转
void TURN_RIGHT_1(unsigned int AB_R);//右转


void list_1(void);// 正常启动循迹
void list_Angle(void);// 正常启动循迹

#endif