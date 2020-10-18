#ifndef   __KEY_H_
#define   __KEY_H_
	//取按键宏
        #define   KEY1_1     (!( P1IN & BIT6 ))  //左键按下有效是1
        #define   KEY2_2     (!( P6IN & BIT2 ))	//右键
        #define   KEY3_3     (!( P6IN & BIT3 ))  
        #define   KEY4_4     (!( P6IN & BIT6 ))	
        
	//按键键值声明	
	enum	key_type{NOKEY,KEY1_,KEY2_,KEY3_,KEY4_};

	extern void	        KeyInit(void);		//键盘初始化
	extern enum key_type 	KeyScan(void);	//键盘扫描函数返回上面的常量键值
#endif