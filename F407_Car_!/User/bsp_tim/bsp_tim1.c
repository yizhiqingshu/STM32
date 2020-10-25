#include "bsp_tim1.h"


void bsp_InitTimer1GPIO(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);/*使能GPIOE的时钟*/

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;/*复用*/
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*推挽输出*/
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;/**/
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;/**/
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
GPIO_Init(GPIOE,&GPIO_InitStructure);/*初始化IO*/

GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);/*复用*/
GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
}


/****************************************************************************************
*函 数 名:
*函数功能:
*形    参:
*返 回 值:
*****************************************************************************************/
void bsp_Inittimer1(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
TIM_OCInitTypeDef TIM_OCInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*使能定时器1的时钟*/
bsp_InitTimer1GPIO();/*初始化IO口*/

TIM_TimeBaseInitStrecture.TIM_Period = 999;/*设置自动重装*/
TIM_TimeBaseInitStrecture.TIM_Prescaler = 167;/*不分频*/
TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/**/
TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/**/
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*初始化*/



TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*设置PWM模式*/
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;/*起始输出为低*/
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*互补通道使能*/
TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Enable;/*互补通道使能*/
TIM_OCInitStructure.TIM_Pulse = 500;/*比较寄存器设置*/
TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;/**/
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;/*输出空闲状态1*/
TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;/**/

TIM_OC1Init(TIM1,&TIM_OCInitStructure);/*初始化通道1*/

TIM_OCInitStructure.TIM_Pulse = 400;/*设置比较寄存器*/
TIM_OC2Init(TIM1,&TIM_OCInitStructure);/*初始化通道2*/

TIM_OCInitStructure.TIM_Pulse = 300;/*设置比较寄存器*/
TIM_OC3Init(TIM1,&TIM_OCInitStructure);/*初始化通道3*/

TIM_OCInitStructure.TIM_Pulse = 200;/*设置比较寄存器*/
TIM_OC4Init(TIM1,&TIM_OCInitStructure);/*初始化通道4*/

TIM_Cmd(TIM1,ENABLE);/*计数使能*/
TIM_CtrlPWMOutputs(TIM1,ENABLE);/*输出使能*/

}


