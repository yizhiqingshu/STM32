#ifndef   __KEY_H_
#define   __KEY_H_
	//ȡ������
        #define   KEY1_1     (!( P1IN & BIT6 ))  //���������Ч��1
        #define   KEY2_2     (!( P6IN & BIT2 ))	//�Ҽ�
        #define   KEY3_3     (!( P6IN & BIT3 ))  
        #define   KEY4_4     (!( P6IN & BIT6 ))	
        
	//������ֵ����	
	enum	key_type{NOKEY,KEY1_,KEY2_,KEY3_,KEY4_};

	extern void	        KeyInit(void);		//���̳�ʼ��
	extern enum key_type 	KeyScan(void);	//����ɨ�躯����������ĳ�����ֵ
#endif