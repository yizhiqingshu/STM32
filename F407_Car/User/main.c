/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.8.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "jianlai_.h"
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
		/* ��������main����֮ǰ�������ļ���statup_stm32f4xx.s�Ѿ�����
		* SystemInit()������ϵͳʱ�ӳ�ʼ����168MHZ
		* SystemInit()��system_stm32f4xx.c�ж���
		* ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
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

