/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: 25GA370ֱ������������(L298N����)ʵ��
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
#include "stm32f1xx_hal.h"
#include "DCMotor/bsp_L298N.h"
#include "key/bsp_key.h"
#include "usart/bsp_debug_usart.h"
#include "DCMotor/bsp_encoder.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
//����PID�ṹ��
typedef struct 
{
   __IO int      SetPoint;                                 //�趨Ŀ�� Desired Value
   __IO double   Proportion;                               //�������� Proportional Const
   __IO double   Integral;                                 //���ֳ��� Integral Const
   __IO double   Derivative;                               //΢�ֳ��� Derivative Const
   __IO int      LastError;                                //Error[-1]
   __IO int      PrevError;                                //Error[-2]
}PID;

/* ˽�к궨�� ----------------------------------------------------------------*/
/*************************************/
//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/
#define  P_DATA      3.2                                 //P����
#define  I_DATA      1.1                                //I����
#define  D_DATA      -0.15                              //D����


/* ˽�б��� ------------------------------------------------------------------*/
__IO uint16_t time_count=0;        // ʱ�������ÿ1ms����һ(��ζ�ʱ��Ƶ���й�)
__IO uint32_t CaptureNumber=0;     // ���벶����
__IO uint8_t  start_flag=0;
__IO double encoder_speed=0;
static PID sPID;
static PID *sptr = &sPID;

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
void IncPIDInit(void);
int IncPIDCalc(int NextPoint);

/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  // �ⲿ����8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;  // 9��Ƶ���õ�72MHz��ʱ��
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�72MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ�72MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;               // APB1ʱ�ӣ�36MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;               // APB2ʱ�ӣ�72MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

 	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);  // ���ò�����ϵͳ�δ�ʱ��
  /* ϵͳ�δ�ʱ��ʱ��Դ */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  /* ϵͳ�δ�ʱ���ж����ȼ����� */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * ��������: ������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
int main(void)
{ 
  /* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
  HAL_Init();
  /* ����ϵͳʱ�� */
  SystemClock_Config();

  KEY_GPIO_Init();
  MX_DEBUG_USART_Init();
  
  IncPIDInit();
  
  ENCODER_TIMx_Init(); 
  HAL_TIM_Base_Start(&htimx_ENCODER);  
  
  /* �߼����ƶ�ʱ����ʼ��������PWM������� */
  L298N_TIMx_Init();
  /* ������ʱ�� */
  HAL_TIM_Base_Start(&htimx_L298N);
  
  HAL_TIM_IC_Start_IT(&htimx_ENCODER,ENCODER_TIM_CHANNELx);
  
  /* ������ʱ��ͨ���ͻ���ͨ��PWM��� */
  L298N_DCMOTOR_Contrl(1,2,0);
  start_flag=1; 
  
  printf("����ʽPID�㷨���Ƶ����ת\n");
  /* ����ѭ�� */
  while (1)
  {
    if(KEY1_StateRead()==KEY_DOWN)  // ����
    {
      /* ����Ŀ���ٶ� */
      sptr->SetPoint +=5;    
    }
    if(KEY2_StateRead()==KEY_DOWN)  // ����
    {
      /* ����Ŀ���ٶ� */
      sptr->SetPoint -=5;
    }    
  }
}

/**
  * ��������: ϵͳ�δ�ʱ���жϻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ÿ����һ�εδ�ʱ���жϽ���ûص�����һ��
  */
void HAL_SYSTICK_Callback(void)
{
  if(start_flag) // �ȴ����������ſ�ʼ��ʱ
  {
    time_count++;         // ÿ1ms�Զ���һ
    if(time_count==200)
    {
      __IO uint32_t count;
      __IO int para;
      __IO double cal;
      
      /* �õ�����������ֵ����ֵԽ��˵���ٶ�Խ�� */
      count=CaptureNumber; 
      CaptureNumber=0;    // ���㣬���㿪ʼ����
      
      /* �����õ�����ʽPID��������ֵ */
      para=IncPIDCalc(count);
      
      /* ����������ֵ������ǰ����ٶ� */
      if((para<-3)||(para>3)) // ���� PID ��������������СʱƵ�����������𵴡�
      {
        PWM_Duty +=para;  
      }        
      if(PWM_Duty>899)PWM_Duty=899;  
      
      
      // 11������������(ת��һȦ���������)
      // 34����������ȣ��ڲ����ת��Ȧ�����������ת��Ȧ���ȣ������ٳ��ֱ�      
      cal=sptr->SetPoint;
      printf("\n�趨Ŀ���ٶ� -> ��������%dsʱ�����%d������\n",time_count,sptr->SetPoint);      
      printf("                �൱��ʵ��Ŀ���ٶ�Ϊ��%0.2fȦ/s\n",cal*(1000/time_count)/11/34);
      
      cal=count;
      printf("��ǰ����ٶ�-> ��������%dsʱ�����%d������\n",time_count,count);
      printf("                �൱�ڵ�ǰʵ���ٶ�Ϊ��%0.2fȦ/s\n",cal*(1000/time_count)/11/34);
      
      printf("����ʽPID�㷨�������ֵ��%d   �����µ�ռ�ձ�Ϊ��%d\n",para,PWM_Duty);
      
      L298N_DCMOTOR_Contrl(1,2,PWM_Duty); 
      time_count=0;      
    }
  }
}

/**
  * ��������: ��ʱ�����벶���жϻص�����
  * �������: htim����ʱ�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  CaptureNumber++;
}


/**************PID������ʼ��********************************/
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //�������� Proportional Const
    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
    sptr->SetPoint=50;           //�趨Ŀ��Desired Value
}
/********************����ʽPID�������************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //��ǰ���
  iError=sptr->SetPoint-NextPoint;                    //��������
  iIncpid=(sptr->Proportion * iError)                 //E[k]��
              -(sptr->Integral * sptr->LastError)     //E[k-1]��
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]��
              
  sptr->PrevError=sptr->LastError;                    //�洢�������´μ���
  sptr->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
