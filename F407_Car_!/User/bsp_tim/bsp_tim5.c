//#include "jianlai_.h"


//void TIM_PWMINPUT_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef  TIM_ICInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM5ʱ��ʹ��    
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0---��ӦK1����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); //PA0����λ��ʱ��5 
//  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF-1; 	
//	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=168MHz 
//	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
//  TIM_TimeBaseStructure.TIM_Prescaler = 84-1;	
//  // ������ʽ
//  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
//	// ��ʼ����ʱ��TIMx, x[1,8]
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	
//	/* IC1���������ش��� TI1FP1 */
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICFilter = 0x0;
//  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
//	
//	/* IC2�����½��ش��� TI1FP2 */	
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICFilter = 0x0;
//  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
//  /* ѡ��ʱ�����봥��: TI1FP1 */
//  TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);		
//  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
//  TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
//  TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
//  TIM_ITConfig(TIM2, TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2, ENABLE);
//  TIM_Cmd(TIM2, ENABLE);
//    // �����ж���Ϊ0	
//		// �����ж���Դ
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	
//		// ������ռ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
//	  // ���������ȼ�
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
//  /* �����ʱ������/�Ƚ�1�ж� */
//  
//  
//  /* ��ȡ���벶��ֵ */
//  IC1Value = TIM_GetCapture1(TIM2);
//  IC2Value = TIM_GetCapture2(TIM2);	
//  if (IC1Value != 0)
//  {
//    /* ռ�ձȼ��� */
//    DutyCycle = (float)(IC2Value * 100) / IC1Value;

//    /* Ƶ�ʼ��� */
//    Frequency = 84000000/84/(float)IC1Value;
//	printf("ռ�ձȣ�%0.2f%%   Ƶ�ʣ�%0.2fHz\n",DutyCycle,Frequency);
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
	// ����TIMx_CLK,x[1,8] 
  RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE); 

	
	 NVIC_InitTypeDef NVIC_InitStructure; 		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF-1; 	
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=168MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = 1680-1;	
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* IC1���������ش��� TI1FP1 */
  TIM_ICInitStructure.TIM_Channel = ADVANCE_IC1PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* IC2�����½��ش��� TI1FP2 */	
	TIM_ICInitStructure.TIM_Channel = ADVANCE_IC2PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* ѡ��ʱ�����봥��: TI1FP1 */
  TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);		

  /* ѡ���ģʽ: ��λģʽ */
  TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(ADVANCE_TIM,TIM_MasterSlaveMode_Enable);

  /* ʹ�ܸ߼����ƶ�ʱ�� */
  TIM_Cmd(ADVANCE_TIM, ENABLE);

  /* ʹ�ܲ���/�Ƚ�2�ж����� */
  TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);
}


/**
  * @brief  ��ʼ���߼����ƶ�ʱ����ʱ��1ms����һ���ж�
  * @param  ��
  * @retval ��
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
  /* �����ʱ������/�Ƚ�1�ж� */
  TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);

  /* ��ȡ���벶��ֵ */
  IC1Value = TIM_GetCapture1(ADVANCE_TIM);
  IC2Value = TIM_GetCapture2(ADVANCE_TIM);	
  printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
	
  if (IC1Value != 0)
  {
    /* ռ�ձȼ��� */
    DutyCycle = (float)(IC2Value * 100) / IC1Value;

    /* Ƶ�ʼ��� */
    Frequency = 168000000/1680/(float)IC1Value;
    printf("ռ�ձȣ�%0.2f%%   Ƶ�ʣ�%0.2fHz\n",DutyCycle,Frequency);
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}