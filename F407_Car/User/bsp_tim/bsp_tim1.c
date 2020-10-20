#include "bsp_tim1.h"

void TIM8_GPIOAF_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOA,ENABLE);/*使能GPIOA C的时钟*/
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStructure);             

	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOE8 9复用为定时器1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM8); //GPIOE10 11复用为定时器1
}

void TIM8_PWM_Init(void)
{		 					 
	//此部分需手动修改IO口设置
	uint16_t arr,ccr1;
	arr = SystemCoreClock/10000; /*10K*/
	ccr1 = arr/5;/*占空比20%*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);/*使能定时器1的时钟*/
	TIM8_GPIOAF_Config();
	
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//初始化定时器1
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*设置PWM模式*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;/*起始输出为低*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*互补通道使能*/
	TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Enable;/*互补通道使能*/
	TIM_OCInitStructure.TIM_Pulse = ccr1;/*比较寄存器设置*/
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;/**/
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;/*输出空闲状态1*/
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;/**/

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC1
	TIM_Cmd(TIM8, ENABLE);  //使能TIM1
    TIM_CtrlPWMOutputs(TIM8, ENABLE);
										  
}  


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
uint16_t arr,ccr1,ccr2,ccr3,ccr4;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
TIM_OCInitTypeDef TIM_OCInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*使能定时器1的时钟*/


arr = SystemCoreClock/10000; /*10K*/
ccr1 = arr/5;/*占空比20%*/
ccr2 = arr/4;/*占空比25%*/
ccr3 = arr/3;/*占空比33%*/
ccr4 = arr/2;/*占空比50%*/

bsp_InitTimer1GPIO();/*初始化IO口*/

TIM_TimeBaseInitStrecture.TIM_Period = arr;/*设置自动重装*/
TIM_TimeBaseInitStrecture.TIM_Prescaler = 0;/*不分频*/
TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/**/
TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/**/
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*初始化*/



TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*设置PWM模式*/
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;/*起始输出为低*/
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*互补通道使能*/
TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Enable;/*互补通道使能*/
TIM_OCInitStructure.TIM_Pulse = ccr1;/*比较寄存器设置*/
TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;/**/
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;/*输出空闲状态1*/
TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;/**/

TIM_OC1Init(TIM1,&TIM_OCInitStructure);/*初始化通道1*/

TIM_OCInitStructure.TIM_Pulse = ccr2;/*设置比较寄存器*/
TIM_OC2Init(TIM1,&TIM_OCInitStructure);/*初始化通道2*/

TIM_OCInitStructure.TIM_Pulse = ccr3;/*设置比较寄存器*/
TIM_OC3Init(TIM1,&TIM_OCInitStructure);/*初始化通道3*/

TIM_OCInitStructure.TIM_Pulse = ccr4;/*设置比较寄存器*/
TIM_OC4Init(TIM1,&TIM_OCInitStructure);/*初始化通道4*/

TIM_Cmd(TIM1,ENABLE);/*计数使能*/
TIM_CtrlPWMOutputs(TIM1,ENABLE);/*输出使能*/

}


