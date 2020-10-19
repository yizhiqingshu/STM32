/**
  ******************************************************************************
  * �ļ�����: bsp_encoder.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: 25GA370ֱ�����ٵ���������ײ�����
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
#include "DCMotor/bsp_encoder.h" 

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
TIM_HandleTypeDef htimx_ENCODER;
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ���������ų�ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void ENCODER_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct; 
  
  /* ���Ŷ˿�ʱ��ʹ�� */
  ENCODER_TIM_GPIO_CLK_ENABLE();

  /* ���������벶������IO��ʼ�� */
  GPIO_InitStruct.Pin = ENCODER_TIM_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ENCODER_TIM_PORT, &GPIO_InitStruct);  
}

/**
  * ��������: ���������ų�ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void ENCODER_NVIC_Conf(void)
{
  /* ��������ʱ���ж����� */
  HAL_NVIC_SetPriority(ENCODER_TIMx_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(ENCODER_TIMx_IRQn);
}
/**
  * ��������: ��������ʱ����ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void ENCODER_TIMx_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;  // ��ʱ��ʱ��
  TIM_MasterConfigTypeDef sMasterConfig;      // ��ʱ����ģʽ����
  TIM_IC_InitTypeDef sConfigIC;               // ��ʱ�����벶��
  
  
  /* ʹ�ܶ�ʱ��ʱ�� */
  ENCODER_TIM_RCC_CLK_ENABLE();

  /* ���������ų�ʼ�� */
  ENCODER_GPIO_Init();
  
  /* �ж����ȼ����� */
  ENCODER_NVIC_Conf();
  
  /* ��ʱ�������������� */
  htimx_ENCODER.Instance = ENCODER_TIMx;                       // ��ʱ�����
  htimx_ENCODER.Init.Prescaler = ENCODER_TIM_PRESCALER;        // ��ʱ��Ԥ��Ƶ��
  htimx_ENCODER.Init.CounterMode = TIM_COUNTERMODE_UP;         // �����������ϼ���
  htimx_ENCODER.Init.Period = ENCODER_TIM_PERIOD;              // ��ʱ������
  htimx_ENCODER.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;   // ʱ�ӷ�Ƶ
  HAL_TIM_Base_Init(&htimx_ENCODER);

  /* ��ʱ��ʱ��Դ���� */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;  // ʹ���ڲ�ʱ��Դ
  HAL_TIM_ConfigClockSource(&htimx_ENCODER, &sClockSourceConfig);
  
  /* ��ʼ����ʱ�����벶�񻷾� */
  //HAL_TIM_IC_Init(&htimx_ENCODER);

  /* ��ʱ�������ģʽ */
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htimx_ENCODER, &sMasterConfig);

  /* ��ʱ�����벶������ */
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;   // �����ش���
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;         // ͨ�� 
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;                   // ��Ƶ
  sConfigIC.ICFilter = 0;                                   // �˲��� 
  HAL_TIM_IC_ConfigChannel(&htimx_ENCODER, &sConfigIC, ENCODER_TIM_CHANNELx);
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
