#ifndef __L298N_TIM_H__
#define __L298N_TIM_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/

#define L298N_TIMx                         TIM1
#define L298N_TIM_RCC_CLK_ENABLE()         __HAL_RCC_TIM1_CLK_ENABLE()
#define L298N_TIM_RCC_CLK_DISABLE()        __HAL_RCC_TIM1_CLK_DISABLE()

/* �� 1 �� */
#define L298N_TIM_CH1_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()     // ���PWM���������������ĵ�EN����
#define L298N_TIM_CH1_PORT                 GPIOA                            // CH1��CH1N������������ʹ��
#define L298N_TIM_CH1_PIN                  GPIO_PIN_8                       // ������������������OUT1��OUT2������
#define L298N_TIM_CH1N_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()     // CH1��CH1N��Ӧ����EN1��EN2
#define L298N_TIM_CH1N_PORT                GPIOB                            // ������������������OUT3��OUT4������
#define L298N_TIM_CH1N_PIN                 GPIO_PIN_13                      // CH1��CH1N��Ӧ����EN3��EN4




// ���嶨ʱ��Ԥ��Ƶ����ʱ��ʵ��ʱ��Ƶ��Ϊ��72MHz/��L298N_TIMx_PRESCALER+1��
#define L298N_TIM_PRESCALER                1    // ʵ��ʱ��Ƶ��Ϊ��36MHz

// ���嶨ʱ�����ڣ�PWMƵ��Ϊ��72MHz/��L298N_TIMx_PRESCALER+1��/��L298N_TIM_PERIOD+1��
#define L298N_TIM_PERIOD                   899  // PWMƵ��Ϊ36MHz/(899+1)=40KHz

// ����߼���ʱ���ظ������Ĵ���ֵ
//ʵ��PWMƵ��Ϊ��72MHz/��L298N_TIMx_PRESCALER+1��/��L298N_TIM_PERIOD+1��/��L298N_TIM_REPETITIONCOUNTER+1��
#define L298N_TIM_REPETITIONCOUNTER        0

/* ��չ���� ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htimx_L298N;
extern __IO uint16_t PWM_Duty;
/* �������� ------------------------------------------------------------------*/

void L298N_TIMx_Init(void);
void L298N_DCMOTOR_Contrl(uint8_t number,uint8_t direction,uint16_t speed);

#endif	/* __L298N_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
