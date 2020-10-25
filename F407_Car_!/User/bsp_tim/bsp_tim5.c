//#include "jianlai_.h"


//void TIM_PWMINPUT_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef  TIM_ICInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM5时钟使能    
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0---对应K1按键
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); //PA0复用位定时器5 
//  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF-1; 	
//	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
//	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
//  TIM_TimeBaseStructure.TIM_Prescaler = 84-1;	
//  // 计数方式
//  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
//	// 初始化定时器TIMx, x[1,8]
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	
//	/* IC1捕获：上升沿触发 TI1FP1 */
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICFilter = 0x0;
//  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
//	
//	/* IC2捕获：下降沿触发 TI1FP2 */	
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICFilter = 0x0;
//  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
//  /* 选择定时器输入触发: TI1FP1 */
//  TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);		
//  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
//  TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
//  TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
//  TIM_ITConfig(TIM2, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2, ENABLE);
//  TIM_Cmd(TIM2, ENABLE);
//    // 设置中断组为0	
//		// 设置中断来源
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	
//		// 设置抢占优先级
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
//	  // 设置子优先级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}


//__IO uint16_t IC2Value = 0;
//__IO uint16_t IC1Value = 0;
//__IO float DutyCycle = 0;
//__IO float Frequency = 0;
//void  TIM2_IRQHandler(void)
//{
//  /* 清除定时器捕获/比较1中断 */
//  
//  
//  /* 获取输入捕获值 */
//  IC1Value = TIM_GetCapture1(TIM2);
//  IC2Value = TIM_GetCapture2(TIM2);	
//  if (IC1Value != 0)
//  {
//    /* 占空比计算 */
//    DutyCycle = (float)(IC2Value * 100) / IC1Value;

//    /* 频率计算 */
//    Frequency = 84000000/84/(float)IC1Value;
//	printf("占空比：%0.2f%%   频率：%0.2fHz\n",DutyCycle,Frequency);
//  }
//  
//  else
//  {
//    DutyCycle = 0;
//    Frequency = 0;
//  }
//  TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_CC2);
//}
#include "jianlai_.h"
static void TIM_PWMINPUT_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
    GPIO_PinAFConfig(ADVANCE_ICPWM_GPIO_PORT,ADVANCE_ICPWM_PINSOURCE,ADVANCE_ICPWM_AF); 
	GPIO_InitStructure.GPIO_Pin = ADVANCE_ICPWM_PIN;	
	GPIO_Init(ADVANCE_ICPWM_GPIO_PORT, &GPIO_InitStructure);
	// 开启TIMx_CLK,x[1,8] 
  RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE); 

	
	 NVIC_InitTypeDef NVIC_InitStructure; 		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQn; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF-1; 	
	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = 1680-1;	
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
	// 初始化定时器TIMx, x[1,8]
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* IC1捕获：上升沿触发 TI1FP1 */
  TIM_ICInitStructure.TIM_Channel = ADVANCE_IC1PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* IC2捕获：下降沿触发 TI1FP2 */	
	TIM_ICInitStructure.TIM_Channel = ADVANCE_IC2PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* 选择定时器输入触发: TI1FP1 */
  TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);		

  /* 选择从模式: 复位模式 */
  TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(ADVANCE_TIM,TIM_MasterSlaveMode_Enable);

  /* 使能高级控制定时器 */
  TIM_Cmd(ADVANCE_TIM, ENABLE);

  /* 使能捕获/比较2中断请求 */
  TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);
}


/**
  * @brief  初始化高级控制定时器定时，1ms产生一次中断
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void)
{

	TIM_PWMINPUT_Config();
}

__IO uint16_t IC2Value = 0;
__IO uint16_t IC1Value = 0;
__IO float DutyCycle = 0;
__IO float Frequency = 0;

void  ADVANCE_TIM_IRQHandler (void)
{
  /* 清除定时器捕获/比较1中断 */
  TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);

  /* 获取输入捕获值 */
  IC1Value = TIM_GetCapture1(ADVANCE_TIM);
  IC2Value = TIM_GetCapture2(ADVANCE_TIM);	
  printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
	
  if (IC1Value != 0)
  {
    /* 占空比计算 */
    DutyCycle = (float)(IC2Value * 100) / IC1Value;

    /* 频率计算 */
    Frequency = 168000000/1680/(float)IC1Value;
    printf("占空比：%0.2f%%   频率：%0.2fHz\n",DutyCycle,Frequency);
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}