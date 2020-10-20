/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用1.8.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "jianlai_.h"
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
		/* 程序来到main函数之前，启动文件：statup_stm32f4xx.s已经调用
		* SystemInit()函数把系统时钟初始化成168MHZ
		* SystemInit()在system_stm32f4xx.c中定义
		* 如果用户想修改系统时钟，可自行编写程序修改
		*/
		  /* add your code here ^_^. */
	bsp_Inittimer1();
	TIM8_PWM_Init();
	TIM_SetCompare1(TIM1,8400);
	TIM_SetCompare2(TIM1,8400);
	TIM_SetCompare3(TIM1,8400);
	
	TIM_SetCompare1(TIM8,8400);

  	  while(1);

}

/*********************************************END OF FILE**********************/

