/********************************************************************************* 
  *Copyright(C),UESTC
  *FileName:    ������������
  *Author:      Tonge
  *Version:     1.0 
  *Date:        2016.12.2
  *Description:  ����msp430f5529�Ķ�������

                  MSP430F5529
              -----------------
         /|\|                 |
         |  |                 |
         ---|RST              |
            |             P2.1|-->KEYLEFT
            |             P1.1|-->KEYRIGHT
  *Others:      None
  *Function List:  
         1.void KeyInit(void) �����������ó�ʼ�����ϵ����һ�μ��ɡ�
         2.enum key_type KeyScan(void)����ɨ����򷵻�ö���ͼ�ֵ
                  ����key_type{NOKEY,KEYLEFT,KEYRIGHT};
**********************************************************************************/  
#include 	"msp430f5529.h"
#include  	"key.h"
#include        "IO_.h"
static	enum    key_type key_value = NOKEY;
//static  int 	key_down_flag = 0;
 
enum key_type KeyScan(void)
{
  if(KEY1_1 )
  {
    delay_ms(20);
    if(KEY1_1)
    {
      key_value =KEY1_;
      while(!(KEY1_1));
    }
   }
   else if( KEY2_2 )
   {
      delay_ms(20);
      if(KEY2_2)
      {
        key_value =KEY2_;
        while(!(KEY2_2));
      }
    }
    else if( KEY3_3 )
    {
      delay_ms(20);
      if(KEY3_3)
      {
        key_value =KEY3_;
        while(!(KEY3_3));
      }
    }

  else if( KEY4_4)
  {
    delay_ms(20);
    if(KEY4_4)
    {
      key_value =KEY4_;
      while(!(KEY4_4));
    }
  }
  else 
    key_value = NOKEY;

  return        key_value;
}
//enum key_type	KeyScan(void)
//{
//        
//	if( KEY1_1 )	
//            key_value = KEY1_;
//        
//	else if(KEY2_2 )		
//            key_value = KEY2_;
//        else if(KEY3_3)
//           key_value = KEY3_;
//        else if(KEY4_4)
//           key_value = KEY4_;
//        else
//            key_value = NOKEY;
//        
//        //��ֹһ�ΰ��¶����Ӧ�����ȴ�����̧�𣬲�����ռ��CPU
//        if(key_down_flag == 0 && key_value != NOKEY)
//        {
//            key_down_flag = 1;//��һ�μ�⵽���������±�־��λ�����ش�ʱ��ֵ
//
//        }
//        else if (key_down_flag == 1 && key_value != NOKEY)
//        {
//            key_value     = NOKEY;//��һ��֮���ⰴ�����£����ؿ�ֵ
//  
//            
//        }
//        else
//        {
//            key_down_flag = 0;//��ⰴ��̧�𣬰��±�ʶ��λ��Ϊ��һ�ΰ���׼��
//        }
//	                        
//	return	key_value;
//}
void KeyInit(void)
{
/*	P1DIR	&= ~BIT1;       //���ð���IOΪ����ģʽ
	P2DIR	&= ~BIT1;
        P1REN   |= BIT1;        //ʹ�ܰ����ϡ���������
        
        P2REN   |= BIT1;
        P1OUT   |= BIT1;        //���ð���IOΪ��������ģʽ
        P2OUT   |= BIT1;
 */        
        P1DIR&=~BIT6;
        P1REN|=BIT6;
        P1OUT |= BIT6; 
        
        P6DIR&=~BIT2;
        P6REN|=BIT2;
        P6OUT |= BIT2;
        
        P6DIR&=~BIT3;
        P6REN|=BIT3;
        P6OUT |= BIT3;
        
        P6DIR&=~BIT6;
        P6REN|=BIT6;
        P6OUT|=BIT6;        

}