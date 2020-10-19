/**
  ******************************************************************************
  * �ļ�����: bsp_L298N.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: 25GA370ֱ�����ٵ������L298N���Ƶײ�����
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F1Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "DCMotor/bsp_L298N.h" 

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
TIM_HandleTypeDef htimx_L298N;
__IO uint16_t PWM_Duty=0;  // ռ�ձȣ�PWM_Duty/L298N_TIM_PERIOD*100%
                             // ռ�ձ�Ϊ��50%ʱ�����ת
                             // ռ�ձȲ�Ϊ��50%ʱ�����ת����50%�ľ��Բ�Խ����ת�ٶ�Ҳ��
                             // ��ת���򲻽�������йأ�Ҳ���������йأ���Ҫ�������
                             // �򵥵ķ����ǣ�������Ʒ�����Ҫ���෴����������PWM�����߽ӷ�
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: L298N���GPIO��ʼ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void L298N_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct; 
  
  /* ���Ŷ˿�ʱ��ʹ�� */
  L298N_TIM_CH1_GPIO_CLK_ENABLE();
  L298N_TIM_CH1N_GPIO_CLK_ENABLE();

/* �� 1 �� */
  /* L298N��������������IO��ʼ�� */
  GPIO_InitStruct.Pin = L298N_TIM_CH1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(L298N_TIM_CH1_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = L298N_TIM_CH1N_PIN;
  HAL_GPIO_Init(L298N_TIM_CH1N_PORT, &GPIO_InitStruct);
}

/**
  * ��������: L298N��ʱ����ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void L298N_TIMx_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;             // ��ʱ��ʱ��
  TIM_MasterConfigTypeDef sMasterConfig;                 // ��ʱ����ģʽ����
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;   // ɲ��������ʱ������
  TIM_OC_InitTypeDef sConfigOC;                          // ��ʱ��ͨ���Ƚ����
  
  /* ��ʱ�������������� */
  htimx_L298N.Instance = L298N_TIMx;                                 // ��ʱ�����
  htimx_L298N.Init.Prescaler = L298N_TIM_PRESCALER;                  // ��ʱ��Ԥ��Ƶ��
  htimx_L298N.Init.CounterMode = TIM_COUNTERMODE_UP;                  // �����������ϼ���
  htimx_L298N.Init.Period = L298N_TIM_PERIOD;                        // ��ʱ������
  htimx_L298N.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;              // ʱ�ӷ�Ƶ
  htimx_L298N.Init.RepetitionCounter = L298N_TIM_REPETITIONCOUNTER;  // �ظ�������
  HAL_TIM_Base_Init(&htimx_L298N);

  /* ��ʱ��ʱ��Դ���� */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;       // ʹ���ڲ�ʱ��Դ
  HAL_TIM_ConfigClockSource(&htimx_L298N, &sClockSourceConfig);

  /* ��ʼ����ʱ���Ƚ�������� */
  HAL_TIM_PWM_Init(&htimx_L298N);
  
  /* ��ʱ�������ģʽ */
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htimx_L298N, &sMasterConfig);
  
  /* ɲ��������ʱ������ */
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htimx_L298N, &sBreakDeadTimeConfig);

/* �� 1 �� */
  /* ��ʱ���Ƚ�������� */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;                  // �Ƚ����ģʽ����ת���
  sConfigOC.Pulse =  PWM_Duty;                         // ռ�ձ�
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;          // �������
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;        // ����ͨ���������
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;           // ����ģʽ
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;       // ���е�ƽ
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;     // ����ͨ�����е�ƽ
  HAL_TIM_PWM_ConfigChannel(&htimx_L298N, &sConfigOC, TIM_CHANNEL_1);
  
  /* L298N���GPIO��ʼ������ */
  L298N_GPIO_Init();
}

/**
  * ��������: ������ʱ��Ӳ����ʼ������
  * �������: htim_base��������ʱ���������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==L298N_TIMx)
  {
    /* ������ʱ������ʱ��ʹ�� */
    L298N_TIM_RCC_CLK_ENABLE();
  }
}

/**
  * ��������: ������ʱ��Ӳ������ʼ������
  * �������: htim_base��������ʱ���������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==L298N_TIMx)
  {
    /* ������ʱ������ʱ�ӽ��� */
    L298N_TIM_RCC_CLK_DISABLE();
    
    HAL_GPIO_DeInit(L298N_TIM_CH1_PORT,L298N_TIM_CH1_PIN);
    HAL_GPIO_DeInit(L298N_TIM_CH1N_PORT,L298N_TIM_CH1N_PIN);
  }
} 

/**
  * ��������: L298Nֱ���������
  * �������: number�������ţ�֧�������������
  *             ������1����Ӧ�߼���ʱ��ͨ��1�ͻ���ͨ��1
  *                   2�����ͣ��
  *           direction������������
  *             ������0��Ŀ����ͣ��
  *                   1����ת
  *                   2����ת
  *           speed������ٶȵ���
  *             ������0 - 900 ��ֵԽ���ٶ�Խ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void L298N_DCMOTOR_Contrl(uint8_t number,uint8_t direction,uint16_t speed)
{
  switch (number)
  {
    case 1:
      if(direction==1)
      {
        HAL_TIM_PWM_Start(&htimx_L298N,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htimx_L298N,TIM_CHANNEL_1);
      }
      else if(direction==2)
      {
        HAL_TIM_PWM_Stop(&htimx_L298N,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htimx_L298N,TIM_CHANNEL_1);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htimx_L298N,TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htimx_L298N,TIM_CHANNEL_1);
      }
      __HAL_TIM_SET_COMPARE(&htimx_L298N,TIM_CHANNEL_1,speed);;
      break;
   case 2:         // ֹͣ���PWM��ͣ��
     HAL_TIM_PWM_Stop(&htimx_L298N,TIM_CHANNEL_1);
     HAL_TIMEx_PWMN_Stop(&htimx_L298N,TIM_CHANNEL_1); 
     break;
  }
}
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
