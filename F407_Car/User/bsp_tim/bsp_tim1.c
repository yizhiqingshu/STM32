#include "bsp_tim1.h"

void TIM8_GPIOAF_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOA,ENABLE);/*ʹ��GPIOA C��ʱ��*/
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStructure);             

	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOE8 9����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM8); //GPIOE10 11����Ϊ��ʱ��1
}

void TIM8_PWM_Init(void)
{		 					 
	//�˲������ֶ��޸�IO������

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	TIM8_GPIOAF_Config();
	
	TIM_TimeBaseStructure.TIM_Prescaler=167;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=99;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*����PWMģʽ*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;/*��ʼ���Ϊ��*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*����ͨ��ʹ��*/
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Enable;/*����ͨ��ʹ��*/
	TIM_OCInitStructure.TIM_Pulse = 50;/*�ȽϼĴ�������*/
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;/**/
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;/*�������״̬1*/
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;/**/

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 OC1
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM1
    TIM_CtrlPWMOutputs(TIM8, ENABLE);
										  
}  


void bsp_InitTimer1GPIO(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);/*ʹ��GPIOE��ʱ��*/

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;/*����*/
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*�������*/
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;/**/
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;/**/
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
GPIO_Init(GPIOE,&GPIO_InitStructure);/*��ʼ��IO*/

GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);/*����*/
GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
}


/****************************************************************************************
*�� �� ��:
*��������:
*��    ��:
*�� �� ֵ:
*****************************************************************************************/
void bsp_Inittimer1(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
TIM_OCInitTypeDef TIM_OCInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*ʹ�ܶ�ʱ��1��ʱ��*/




bsp_InitTimer1GPIO();/*��ʼ��IO��*/

TIM_TimeBaseInitStrecture.TIM_Period = 999;/*�����Զ���װ*/
TIM_TimeBaseInitStrecture.TIM_Prescaler = 167;/*����Ƶ*/
TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/**/
TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*���ϼ���*/
TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/**/
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*��ʼ��*/



TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*����PWMģʽ*/
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;/*��ʼ���Ϊ��*/
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*����ͨ��ʹ��*/
TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Enable;/*����ͨ��ʹ��*/
TIM_OCInitStructure.TIM_Pulse = 500;/*�ȽϼĴ�������*/
TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;/**/
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;/*�������״̬1*/
TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;/**/

TIM_OC1Init(TIM1,&TIM_OCInitStructure);/*��ʼ��ͨ��1*/

TIM_OCInitStructure.TIM_Pulse = 400;/*���ñȽϼĴ���*/
TIM_OC2Init(TIM1,&TIM_OCInitStructure);/*��ʼ��ͨ��2*/

TIM_OCInitStructure.TIM_Pulse = 300;/*���ñȽϼĴ���*/
TIM_OC3Init(TIM1,&TIM_OCInitStructure);/*��ʼ��ͨ��3*/

TIM_OCInitStructure.TIM_Pulse = 200;/*���ñȽϼĴ���*/
TIM_OC4Init(TIM1,&TIM_OCInitStructure);/*��ʼ��ͨ��4*/

TIM_Cmd(TIM1,ENABLE);/*����ʹ��*/
TIM_CtrlPWMOutputs(TIM1,ENABLE);/*���ʹ��*/

}


