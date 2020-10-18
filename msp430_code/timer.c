/************************************************************
  ��ʱ��������
  �ļ����ƣ�                timer.c
  �ļ�������                ��TA0���PWM�� TA1�������벶������ù���
  ������ͷ�ļ���������      timer.h ���������������ֺ궨��                         
  ����������                
                            TA0 PWM�������   ��P1.2
                            TA1 ���벶������ڣ�P2.0
//ʱ��4M 
*************************************************************/ 


#include 	"msp430f5529.h"
#include  	"timer.h"
char flag=0;                       //���ڱ�ǵ�ǰ����״̬ 0:���� 1������һ�������� 2������һ���½��� 
unsigned int pos_time=0;          //���ڼ�¼������
unsigned int period  =0;          //���ڼ�¼����

//volatile unsigned int qian_1=200;
//volatile unsigned int qian_2=200;
//volatile unsigned int hou_1=200;
//volatile unsigned int hou_2=200;

/******************

PWM����ʼ��
������ַ����PWM��

********************/
void PWM_Init( void )
{
        
        P1DIR |= BIT2; //����P1.2����Ϊ��ʱ��TA0.1
        P1SEL |= BIT2; //����P1.2Ϊ���
        P1DIR |= BIT3; //dir ����Ϊ1 ����Ϊ���� tim
        P1SEL |= BIT3;// sel ����Ϊ1 �������� tim ���
        P1DIR |= BIT4; //����P1.4����Ϊ��ʱ��TA0.3
        P1SEL |= BIT4; //����P1.4Ϊ���
        P1DIR |= BIT5;
        P1SEL |= BIT5;
        TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_0;//ʹ��SMCLKΪʱ��Դ UP����ģʽ 1��Ƶ
        TA0CCTL1 = OUTMOD_7 ; //TA0���ģʽ7
        TA0CCTL2 = OUTMOD_7 ; 
        TA0CCTL3 = OUTMOD_7 ; //TA3���ģʽ3
        TA0CCTL4 = OUTMOD_7 ; 
        TA0CCR0 = 500 ;   //��ʼ��Ƶ��8K����
        TA0CCR1 = 0 ;    //��ʼ��Ϊ ռ�ձ� 20% Ƶ�� 8k
        TA0CCR2 = 0 ;
        TA0CCR3 = 0 ;
        TA0CCR4 = 0 ;
        
}





