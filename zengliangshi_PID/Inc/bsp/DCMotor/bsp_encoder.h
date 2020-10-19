#ifndef __ENCODER_TIM_H__
#define __ENCODER_TIM_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/

#define ENCODER_TIMx                         TIM3
#define ENCODER_TIM_RCC_CLK_ENABLE()         __HAL_RCC_TIM3_CLK_ENABLE()
#define ENCODER_TIM_RCC_CLK_DISABLE()        __HAL_RCC_TIM3_CLK_DISABLE()

#define ENCODER_TIM_CHANNELx                 TIM_CHANNEL_3                    // ���������벶��ͨ��

#define ENCODER_TIM_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()     // ���벶��ͨ������
#define ENCODER_TIM_PORT                     GPIOB 
#define ENCODER_TIM_PIN                      GPIO_PIN_0


// ���嶨ʱ��Ԥ��Ƶ����ʱ��ʵ��ʱ��Ƶ��Ϊ��72MHz/��ENCODER_TIMx_PRESCALER+1��
#define ENCODER_TIM_PRESCALER                11    // ʵ��ʱ��Ƶ��Ϊ��6MHz

// ���嶨ʱ�����ڣ����벶��������Ϊ��0xFFFF
#define ENCODER_TIM_PERIOD                   0xFFFF

#define ENCODER_TIMx_IRQn                    TIM3_IRQn
#define ENCODER_TIMx_IRQHandler              TIM3_IRQHandler
/* ��չ���� ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htimx_ENCODER;

/* �������� ------------------------------------------------------------------*/

void ENCODER_TIMx_Init(void);

#endif	/* __ENCODER_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
