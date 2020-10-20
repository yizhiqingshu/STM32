#ifndef BSP_TIM5_
#define BSP_TIM5_
#define ADVANCE_ICPWM_PIN             GPIO_Pin_0           
#define ADVANCE_ICPWM_GPIO_PORT       GPIOA                      
#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define ADVANCE_ICPWM_PINSOURCE		  GPIO_PinSource0
#define ADVANCE_ICPWM_AF			  GPIO_AF_TIM5
#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

/* �߼����ƶ�ʱ�� */
#define ADVANCE_TIM           		    TIM5
#define ADVANCE_TIM_CLK       		    RCC_APB1Periph_TIM5

/* ����/�Ƚ��ж� */
#define ADVANCE_TIM_IRQn			  TIM5_IRQn
#define ADVANCE_TIM_IRQHandler        TIM5_IRQHandler


void TIMx_Configuration(void);

#endif

