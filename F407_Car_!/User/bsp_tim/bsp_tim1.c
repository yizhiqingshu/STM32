#include "bsp_tim1.h"


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


