#include "menu.h"
uint8_t list = 1;
uint16_t  model = 80;
extern volatile uint16_t  GO_PWM ;
uint16_t go_pwm=140;
unsigned int time = 10;
unsigned char Angle=10;
unsigned int tim_15=10;
extern unsigned char Question_1;
void key1_down(void)
{
	if(list == 1)
	{ 
		model+=10;
		if(model > 500)
		model = 500;
	}
	if(list==2)
        {
        go_pwm+=10;
        if(go_pwm>500)
          go_pwm=400;
        }
	if(list == 3)
	{
		time++;	
		if(time == 21)
                time = 15;
	}
        if(list == 4)
	{
		tim_15++;
		if(tim_15 == 20)
		tim_15 = 20;
	}
	if(list == 5)
	{
		Angle++;
		if(Angle == 30)
		Angle = 30;
	}
}

void key2_down(void)
{
	if(list == 1)
	{
		model --;
		if(model == 0)
		model = 0;
	}
        if(list==2)
        {
        go_pwm--;
        if(go_pwm<50)
        go_pwm=50;
        }
	if(list == 3)
	{
 
	time--;
	if(time == 10)
	time = 10;	
	}
         if(list == 4)
	{
		tim_15--;
		if(tim_15 == 10)
		tim_15 = 10;
	}
	if(list == 5)
	{
        Angle--;
        if(Angle == 10)
	Angle = 10;
	}

}
extern unsigned int ab;
void key3_down(void)
{
  if(list==1)
    {
   ab = model;
 GO_PWM=go_pwm;
    Question_0=1; 
    
}
  if(list==2)
  {
 ab = model;
 GO_PWM=go_pwm;
 Question_1=1;
  }
  if(list==3)
  {Mode_2(time);
   Question_2=1;
  }
   if(list==4)
  {SHIwu_Mode(tim_15);
   Question_4=1;
  }
  if(list==5)
  {
  Mode_3_jiao(Angle);
  Question_3=1;
  }

//    ab = model;
//    Question_1=1;
//	model = 10;
//	list = model;
}
 
void key4_down(void)
{
//   model = 20;
  list++;
  if(list>5)
  {list=1;};
//list = model;	
//	if(list == 1)
//	{
//		list = model;
//	}
//	if(list == 2)
//	{
//		Question_1=1;//问题一、二
//	}
//	if(list == 3)
//	{
//		PWM_change(time);
//	}
//	if(list == 4)
//	{
//		model = 5;
//		list = model;	
//	}
//	if(list == 5)
//	{
//		//question();
//	}
}
