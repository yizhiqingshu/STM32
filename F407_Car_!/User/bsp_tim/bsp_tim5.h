//#ifndef BSP_TIM5_
//#define BSP_TIM5_
//#include "jianlai_.h"
//#define ADVANCE_ICPWM_PIN             GPIO_Pin_0           
//#define ADVANCE_ICPWM_GPIO_PORT       GPIOA                      
//#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
//#define ADVANCE_ICPWM_PINSOURCE		  GPIO_PinSource0
//#define ADVANCE_ICPWM_AF			  GPIO_AF_TIM2
//#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
//#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

///* 高级控制定时器 */
//#define ADVANCE_TIM           		    TIM2
//#define ADVANCE_TIM_CLK       		    RCC_APB1Periph_TIM2

///* 捕获/比较中断 */
//#define ADVANCE_TIM_IRQn			  TIM2_IRQn
//#define ADVANCE_TIM_IRQHandler        TIM2_IRQHandler


//void TIM_PWMINPUT_Config(void);
//#endif
#ifndef __GENERAL_TIM_H
#define	__GENERAL_TIM_H

#include "stm32f4xx.h"




#define ADVANCE_ICPWM_PIN             GPIO_Pin_6            
#define ADVANCE_ICPWM_GPIO_PORT       GPIOC                      
#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define ADVANCE_ICPWM_PINSOURCE				GPIO_PinSource6
#define ADVANCE_ICPWM_AF							GPIO_AF_TIM8
#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

/* 高级控制定时器 */
#define ADVANCE_TIM           		    TIM8
#define ADVANCE_TIM_CLK       		    RCC_APB2Periph_TIM8

/* 捕获/比较中断 */
#define ADVANCE_TIM_IRQn					    TIM8_CC_IRQn
#define ADVANCE_TIM_IRQHandler        TIM8_CC_IRQHandler


void TIMx_Configuration(void);

#endif /* __GENERAL_TIM_H */


