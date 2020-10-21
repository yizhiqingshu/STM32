#ifndef BSP_TIM5_
#define BSP_TIM5_
#include "jianlai_.h"
#define ADVANCE_ICPWM_PIN             GPIO_Pin_0           
#define ADVANCE_ICPWM_GPIO_PORT       GPIOA                      
#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define ADVANCE_ICPWM_PINSOURCE		  GPIO_PinSource0
#define ADVANCE_ICPWM_AF			  GPIO_AF_TIM2
#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

/* 高级控制定时器 */
#define ADVANCE_TIM           		    TIM2
#define ADVANCE_TIM_CLK       		    RCC_APB1Periph_TIM2

/* 捕获/比较中断 */
#define ADVANCE_TIM_IRQn			  TIM2_IRQn
#define ADVANCE_TIM_IRQHandler        TIM2_IRQHandler


void TIM_PWMINPUT_Config(void);
#endif

