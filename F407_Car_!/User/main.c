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
  
extern __IO float DutyCycle;
extern __IO float Frequency ;
int main(void)
{
		/* ��������main����֮ǰ�������ļ���statup_stm32f4xx.s�Ѿ�����
		* SystemInit()������ϵͳʱ�ӳ�ʼ����168MHZ
		* SystemInit()��system_stm32f4xx.c�ж���
		* ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
		*/
		  /* add your code here ^_^. */
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_init(168);  //��ʼ����ʱ����
		uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	
	bsp_Inittimer1();
	TIM_SetCompare1(TIM1,100);
	TIM_SetCompare2(TIM1,200);
	TIM_SetCompare3(TIM1,300);
//	TIM_PWMINPUT_Config();
	TIMx_Configuration();
  	  while(1)
	  {
		 
	
	  }  
	  

}

/*********************************************END OF FILE**********************/

