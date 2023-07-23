#include "timer.h"
#include "gpio.h"
#include "huidu.h"
#include "moni.h"
#include "oled.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
extern int32_t output2,output1,output3,output4;//output1:zuoqian;output2:youqian;output3:zuohou;output4:youhou

extern int va,vb,vc,vd,renwu1,moshu,renwu2,renwu3,renwu4,tansuo1,tansuo2,tansuo3,tansuo4;

extern int moni21,moni22,moni23,moni24,moni25,moni26,moni27,moni28,cha,moshi,e;

extern float pitch,roll,yaw; 		//ŷ����
extern double s,sa;

void TIM6_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM6,DISABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn ; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void TIM7_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM7,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void TIM14_PWM_Init(u32 arr,u32 psc)
{		 		
	
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); //GPIOF9����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM14
 
										  
}  
void TIM13_PWM_Init(u32 arr,u32 psc)
{
	
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM12ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM12); //GPIOB14����Ϊ��ʱ��12
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //��ʼ��PB14
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//��ʼ����ʱ��12
	
	//��ʼ��TIM12 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM13, ENABLE);  //ʹ��TIM14
 
										  
} 
void TIM9_CH1_PWM_Init(u32 arr,u32 psc)
{
	
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); //GPIOE5����Ϊ��ʱ��9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOE5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PE5
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��9
	
	//��ʼ��TIM9 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ���GAO
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM14
 
										  
}  


void TIM9_CH2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOE5����Ϊ��ʱ��9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOE5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PE5
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��9
	
	//��ʼ��TIM9 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ���GAO
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM14
 
										  
} 







void guaiwan(u16 zuoqian,u16 youqian,u16 zuohou,u16 youhou,int flag1,int flag2,int flag3,int flag4)
{
		TIM_SetCompare1(TIM14,zuoqian );//
		TIM_SetCompare1(TIM13,youqian ); //
		TIM_SetCompare1(TIM9,zuohou );//
		TIM_SetCompare2(TIM9, youhou);//

		
		if(flag1==1)//ȫ����ת16
		{	zuoqianr=1;
		 zuoqianw=0;
		}
		
		
		if(flag1==-1)//ȫ����ת16
		{	zuoqianr=0;
		 zuoqianw=1;
		}
		
		
		if(flag2==1)//ȫ����ת16
		{	youqianr=1;
		 youqianw=0;
		}
		if(flag2==-1)//ȫ����ת16
		{	youqianr=0;
		 youqianw=1;
		}
		
		
		if(flag3==1)//ȫ����ת16
		{	zuohour=1;
		 zuohouw=0;
		}
		
		
		if(flag3==-1)//ȫ����ת16
		{	zuohour=0;
		 zuohouw=1;
		}
		
		if(flag4==1)//ȫ����ת16
		{	youhour=1;
		 youhouw=0;
		}
		
		
		if(flag4==-1)//ȫ����ת16
		{	youhour=0;
		 youhouw=1;}
		
}



void houguaiwan(u16 youhou,u16 zuohou,u16 youqian,u16 zuoqian,int flag1,int flag2)
{
		TIM_SetCompare1(TIM14,zuoqian );//
		TIM_SetCompare1(TIM13,youqian ); //
		TIM_SetCompare1(TIM9,zuohou );//
		TIM_SetCompare2(TIM9, youhou);//	

		
		if(flag1==1)//ȫ����ת16
		{	youqianr=0;
		 youqianw=1;
			youhour=0;
			youhouw=1;
		}
		
		
		if(flag1==-1)//ȫ����ת16
		{	youqianr=1;
		 youqianw=0;
			youhour=1;
			youhouw=0;
		}
		
		
		if(flag2==1)//ȫ����ת16
		{	zuoqianr=0;
		 zuoqianw=1;
			zuohour=0;
			zuohouw=1;
		}
		if(flag2==-1)//ȫ����ת16
		{	zuoqianr=1;
		 zuoqianw=0;
			zuohour=1;
			zuohouw=0;
		}	
}



void zuolun(u16 pwm,int flag)
{
	TIM_SetCompare1(TIM14,pwm);
	TIM_SetCompare1(TIM9,pwm);
	if(flag==1)
	{
		zuoqianr=1;
		zuoqianw=0;
		zuohour=1;
		zuohouw=0;		
	}
	if(flag==-1)
	{
		zuoqianr=0;
		zuoqianw=1;
		zuohour=0;
		zuohouw=1;			
	}
}



void youlun(u16 pwm,int flag)
{
	TIM_SetCompare1(TIM13,pwm);
	TIM_SetCompare2(TIM9,pwm);
	if(flag==1)
	{
	 youqianr=1;
	 youqianw=0;
	 youhour=1;
	 youhouw=0;
	}
	if(flag==-1)
	{
	 youqianr=0;
	 youqianw=1;
	 youhour=0;
	 youhouw=1;
	}
}




void qiankuaixun(void)
{
	if(moni12==1&&(moni14==0)&&moni17==1)
				{	
					guaiwan(60,60,60,60,1,1,1,1);
				}
	if(moni12==1&&moni14==1&&moni15==0&&moni17==1)//youguai
				guaiwan(55,25,55,25,1,1,1,1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
	
	else if(moni14==1&&moni15==1&&moni16==0&&moni18==1)//���ҹ�
				guaiwan(50,20,50,20,1,1,1,1);

	else if(moni14==1&&moni15==1&&moni16==1&&moni17==0&&moni18==1)//da�ҹ�
	guaiwan(50,50,50,50,1,-1,1,-1);
	
	else if(moni14==1&&moni15==1&&moni16==1&&moni17==1&&moni18==0)//da�ҹ�
	guaiwan(40,80,40,80,1,-1,1,-1);
		
	else if(moni12==1&&moni13==0&&moni15==1&&moni16==1)//xiao�����
				guaiwan(20,55,20,55,1,1,1,1);
			
	else if(moni12==0&&moni14==1&&moni15==1&&moni17==1)//zhong�����
				guaiwan(70,40,70,40,-1,1,-1,1);

//			else if(moni11==0&&moni12==1&&moni13==1&&moni14==1)//da�����
//				  guaiwan(2500,2500,2500,2500,-1,1,-1,1);//guaiwan(2500,2500,2500,2500,-1,1,-1,1);			

	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(15,15,15,15,1,1,1,1);
	else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)//ֱ����̽
			guaiwan(20,20,20,20,1,1,1,1);		
//	else
//		guaiwan(60,60,60,60,1,1,1,1);
}



void qianmanxun(void)
{
	if(moni12==1&&moni13==1&&(moni14==0)&&moni16==1&&moni17==1)
				{	
					guaiwan(40,40,40,40,1,1,1,1);
				}
				else if(moni11==0&&qianzonghe==7)
				{
					guaiwan(60,30,60,30,-1,1,-1,1);	
				}
				else if(moni11==0&&moni12==0&&qianzonghe==6)
					guaiwan(60,30,60,30,-1,1,-1,1);	
				else if(moni11==0&&moni12==0&&moni13==0&&qianzonghe==5)
					guaiwan(60,30,60,30,-1,1,-1,1);	
		else if(moni12==0&&qianzonghe==7)//da zuo��
		{
			guaiwan(60,30,60,30,-1,1,-1,1);	
		}
		else if(moni12==0&&moni13==0&&qianzonghe==6)//	da zuo��
		{
			guaiwan(45,25,45,25,-1,1,-1,1);	
		}
		else if(moni13==0&&qianzonghe==7)//�����
		{
			guaiwan(40,25,40,25,-1,1,-1,1);
		}
		else if(moni13==0&&moni14==0&&qianzonghe==6)//�����
		{
			guaiwan(40,30,40,30,-1,1,-1,1);
		}
		else if(moni13==0&&moni14==0&&moni15==0&&qianzonghe==5)//zhong zuo
		{
			guaiwan(40,30,40,30,-1,1,-1,1);
		}
		else if(moni14==0&&moni15==0&&moni16==0&&qianzonghe==5)//С��
		{
			guaiwan(30,30,30,30,1,-1,1,-1);
		}
		else if(moni15==0&&qianzonghe==7)//С��
		{
			guaiwan(30,30,30,30,1,-1,1,-1);
		}
		else if(moni15==0&&moni16==0&&qianzonghe==6)//����
		{
			guaiwan(30,40,30,40,1,-1,1,-1);
		}
		else if(moni15==0&&moni16==0&&moni17==0&&qianzonghe==5)
		{
			guaiwan(25,40,25,40,1,-1,1,-1);
		}
		else if(moni16==0&&qianzonghe==7)
		{
			guaiwan(25,40,25,40,1,-1,1,-1);
		}
		else if(moni16==0&&moni17==0&&qianzonghe==6)//da you
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if(moni18==0&&moni16==0&&moni17==0&&qianzonghe==5)
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if((moni17==0||moni18==0)&&qianzonghe==7)
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if(moni18==0&&moni17==0&&qianzonghe==6)
			guaiwan(30,60,30,60,1,-1,1,-1);
		
//		if(moni12==1&&(moni14==0)&&moni17==1)
//				{	
//					guaiwan(40,40,40,40,1,1,1,1);
//				}
//	if(moni12==1&&moni14==1&&moni15==0&&moni17==1)//youguai
//				guaiwan(50,20,40,20,1,1,1,1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
//	
//	else if(moni14==1&&moni15==1&&moni16==0&&moni18==1)//���ҹ�
//				guaiwan(40,25,40,25,1,-1,1,-1);

//	else if(moni14==1&&moni15==1&&moni16==1&&moni17==0&&moni18==1)//da�ҹ�
//	guaiwan(30,30,30,30,1,-1,1,-1);
//	
//	else if(moni14==1&&moni15==1&&moni16==1&&moni17==1&&moni18==0)//da�ҹ�
//	guaiwan(40,80,40,80,1,-1,1,-1);
//	else if(moni12==1&&moni13==0&&moni15==1&&moni16==1)//xiao�����
//				guaiwan(25,40,25,40,-1,1,-1,1);
//			
//	else if(moni12==0&&moni14==1&&moni15==1&&moni17==1)//zhong�����
//				guaiwan(60,30,60,30,-1,1,-1,1);	
//	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
//		guaiwan(10,10,10,10,1,1,1,1);
//	else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)//ֱ����̽
//			guaiwan(15,15,15,15,1,1,1,1);	
//	else
//		guaiwan(40,40,40,40,1,1,1,1);
}





void qianchaomanxun(void)
{
		if(moni12==1&&moni13==1&&(moni14==0||moni15==0)&&moni16==1&&moni17==1)
				{	
					guaiwan(20,20,20,20,1,1,1,1);
				}
				else if(moni11==0&&qianzonghe==7)
				{
					guaiwan(60,30,60,30,-1,1,-1,1);	
				}
				else if(moni11==0&&moni12==0&&qianzonghe==6)
					guaiwan(60,30,60,30,-1,1,-1,1);	
				else if(moni11==0&&moni12==0&&moni13==0&&qianzonghe==5)
					guaiwan(60,30,60,30,-1,1,-1,1);	
		else if(moni12==0&&qianzonghe==7)//da zuo��
		{
			guaiwan(60,30,60,30,-1,1,-1,1);	
		}
		else if(moni12==0&&moni13==0&&qianzonghe==6)//	da zuo��
		{
			guaiwan(45,25,45,25,-1,1,-1,1);	
		}
		else if(moni13==0&&qianzonghe==7)//�����
		{
			guaiwan(40,25,40,25,-1,1,-1,1);
		}
		else if(moni13==0&&moni14==0&&qianzonghe==6)//�����
		{
			guaiwan(40,30,40,30,-1,1,-1,1);
		}
		else if(moni13==0&&moni14==0&&moni15==0&&qianzonghe==5)//zhong zuo
		{
			guaiwan(40,30,40,30,-1,1,-1,1);
		}
		else if(moni14==0&&moni15==0&&moni16==0&&qianzonghe==5)//С��
		{
			guaiwan(30,30,30,30,1,-1,1,-1);
		}
		else if(moni15==0&&qianzonghe==7)//С��
		{
			guaiwan(30,30,30,30,1,-1,1,-1);
		}
		else if(moni15==0&&moni16==0&&qianzonghe==6)//����
		{
			guaiwan(30,40,30,40,1,-1,1,-1);
		}
		else if(moni15==0&&moni16==0&&moni17==0&&qianzonghe==5)
		{
			guaiwan(25,40,25,40,1,-1,1,-1);
		}
		else if(moni16==0&&qianzonghe==7)
		{
			guaiwan(25,40,25,40,1,-1,1,-1);
		}
		else if(moni16==0&&moni17==0&&qianzonghe==6)//da you
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if(moni18==0&&moni16==0&&moni17==0&&qianzonghe==5)
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if((moni17==0||moni18==0)&&qianzonghe==7)
		{
			guaiwan(30,60,30,60,1,-1,1,-1);
		}
		else if(moni18==0&&moni17==0&&qianzonghe==6)
			guaiwan(30,60,30,60,1,-1,1,-1);
		
			
//	else if(moni12==1&&moni14==1&&moni15==0&&moni17==1)//youguai
//				guaiwan(30,30,30,30,1,-1,1,-1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
//	
//	else if(moni14==1&&moni15==1&&moni16==0&&moni18==1)//���ҹ�
//				guaiwan(30,30,30,30,1,-1,1,-1);

//	else if(moni14==1&&moni15==1&&moni16==1&&moni17==0&&moni18==1)//da�ҹ�
//					guaiwan(30,30,30,30,1,-1,1,-1);
//		else if(moni14==1&&moni15==1&&moni16==1&&moni17==1&&moni18==0)//da�ҹ�
//					guaiwan(30,60,30,60,1,-1,1,-1);
//		else if(moni14==1&&moni15==1&&moni16==1&&moni17==0&&moni18==0)
//						guaiwan(30,60,30,60,1,-1,1,-1);
//		else if(moni14==1&&moni15==1&&moni16==0&&moni17==0&&moni18==0)
//						guaiwan(30,60,30,60,1,-1,1,-1);
//	else if(moni12==1&&moni13==0&&moni15==1&&moni16==1)//xiao�����
//				guaiwan(40,40,40,40,-1,1,-1,1);
//			
//	else if(moni12==0&&moni14==1&&moni15==1&&moni17==1)//zhong�����
//				guaiwan(60,30,60,30,-1,1,-1,1);	
//	else if(moni12==0&&moni14==0&&moni15==1&&moni17==1)
//				guaiwan(60,30,60,30,-1,1,-1,1);	
	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(15,15,15,15,1,1,1,1);
	else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)//ֱ����̽
			guaiwan(15,15,15,15,1,1,1,1);	
//	else 
//		guaiwan(20,20,20,20,1,1,1,1);	
}




void houkuaixun(void)
{
	if(moni22==1&&(moni24==0)&&moni27==1)
				{	
					guaiwan(60,60,60,60,-1,-1,-1,-1);
				}
	if(moni22==1&&moni24==1&&moni25==0&&moni27==1)//youguai
	{
		houguaiwan(55,25,55,25,1,1);
	}		
	
	else if(moni24==1&&moni25==1&&moni26==0&&moni27==1&&moni28==1)//���ҹ�
	{
		houguaiwan(50,30,50,30,1,-1);		
	}		

	else if(moni24==1&&moni25==1&&moni26==1&&moni27==0&&moni28==1)//da�ҹ�
	{
		houguaiwan(50,50,50,50,1,-1);
	}
		else if(moni24==1&&moni25==1&&moni26==1&&moni27==1&&moni28==0)//da�ҹ�
	{
		houguaiwan(40,80,40,80,1,-1);
	}
		
	else if(moni22==1&&moni23==0&&moni25==1&&moni26==1)//xiao�����
				houguaiwan(25,55,25,55,1,1);
			
	else if(moni22==0&&moni24==1&&moni25==1&&moni27==1)//zhong�����
				houguaiwan(50,50,50,50,-1,1);

//			else if(moni11==0&&moni12==1&&moni13==1&&moni14==1)//da�����
//				  guaiwan(2500,2500,2500,2500,-1,1,-1,1);//guaiwan(2500,2500,2500,2500,-1,1,-1,1);			

	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(15,15,15,15,-1,-1,-1,-1);
	else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)//ֱ����̽
			guaiwan(20,20,20,20,-1,-1,-1,-1);
//	else
//	houtui();
}



void houmanxun(void)
{
	if(moni22==1&&(moni24==0)&&moni27==1)
				{	
					guaiwan(40,40,40,40,-1,-1,-1,-1);
				}	
	if(moni22==1&&moni24==1&&moni25==0&&moni27==1)//youguai
	{
		houguaiwan(40,30,40,30,1,-1);
	}		
	
	else if(moni24==1&&moni25==1&&moni26==0&&moni28==1)//���ҹ�
	{
			houguaiwan(40,30,40,30,1,-1);		
	}		

	else if(moni24==1&&moni25==1&&moni26==1&&moni27==0)//da�ҹ�
	{
		houguaiwan(30,30,30,30,1,-1);
	}
		else if(moni24==1&&moni25==1&&moni26==1&&moni27==1&&moni28==0)//da�ҹ�
	{
		houguaiwan(30,40,30,40,1,-1);
	}
		
	else if(moni22==1&&moni23==0&&moni25==1&&moni26==1)//xiao�����
				houguaiwan(30,40,30,40,-1,1);
			
	else if(moni22==0&&moni24==1&&moni25==1&&moni27==1)//zhong�����
				houguaiwan(45,30,45,30,-1,1);
	
	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(20,20,20,20,-1,-1,-1,-1);
	else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)//ֱ����̽
			guaiwan(25,25,25,25,-1,-1,-1,-1);
//	else
//		houtui();
}





void houchaomanxun(void)
{
	if(moni22==1&&(moni24==0)&&moni26==1&&moni27==1)
				{	
					houguaiwan(20,20,20,20,1,1);
				}
		else if(moni22==0&&houzonghe==6)//da zuo��
		{
			houguaiwan(40,30,40,30,-1,1);	
		}
		else if(moni22==0&&moni23==0&&houzonghe==5)//	da zuo��
		{
			houguaiwan(30,30,30,30,-1,1);	
		}
		else if(moni23==0&&houzonghe==6)//�����
		{
			houguaiwan(30,30,30,30,-1,1);
		}
		else if(moni23==0&&moni24==0&&houzonghe==5)//�����
		{
			houguaiwan(30,30,30,30,-1,1);
		}
		else if(moni23==0&&moni24==0&&moni25==0&&houzonghe==4)//zhong zuo
		{
			houguaiwan(40,30,40,30,-1,1);
		}
		else if(moni24==0&&moni25==0&&moni26==0&&houzonghe==4)//С��
		{
			houguaiwan(30,30,30,30,1,-1);
		}
		else if(moni25==0&&houzonghe==6)//С��
		{
			houguaiwan(30,30,30,30,1,-1);
		}
		else if(moni25==0&&moni26==0&&houzonghe==5)//����
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if(moni25==0&&moni26==0&&moni27==0&&houzonghe==4)
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if(moni26==0&&houzonghe==6)
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if(moni26==0&&moni27==0&&houzonghe==5)//da you
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if(moni28==0&&moni26==0&&moni27==0&&houzonghe==4)
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if((moni27==0||moni28==0)&&houzonghe==6)
		{
			houguaiwan(30,40,30,40,1,-1);
		}
		else if(moni28==0&&moni27==0&&houzonghe==5)
			houguaiwan(30,40,30,40,1,-1);
//		
//	if(moni22==1&&(moni24==0)&&moni27==1)
//				{	
//					guaiwan(20,20,20,20,-1,-1,-1,-1);
//				}	
//	if(moni22==1&&moni24==1&&moni25==0&&moni27==1)//youguai
//	{
//		houguaiwan(30,30,30,30,1,-1);
//	}		
//	
//	else if(moni24==1&&moni25==1&&moni26==0&&moni28==1)//���ҹ�
//	{
//			houguaiwan(30,30,30,30,1,-1);		
//	}		

//	else if(moni24==1&&moni25==1&&moni26==1&&moni27==0)//da�ҹ�
//	{
//		houguaiwan(30,30,30,30,1,-1);
//	}
//		else if(moni24==1&&moni25==1&&moni26==1&&moni27==1&&moni18==0)//da�ҹ�
//	{
//		houguaiwan(40,40,40,40,1,-1);
//	}
//		
//	else if(moni22==1&&moni23==0&&moni25==1&&moni26==1)//xiao�����
//				houguaiwan(30,30,30,30,-1,1);
//			
//	else if(moni22==0&&moni24==1&&moni25==1&&moni27==1)//zhong�����
//				houguaiwan(40,30,40,30,-1,1);
//	
//	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
//		guaiwan(20,20,20,20,-1,-1,-1,-1);
//	else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)//ֱ����̽
//			guaiwan(20,20,20,20,-1,-1,-1,-1);
//	else
//		houtui();
}

void jixianxun()
{
	jiance();
	if(moni12==1&&moni13==1&&(moni14==0)&&moni15==0&&moni16==1&&moni17==1)
				{	
					guaiwan(15,15,15,15,1,1,1,1);
				}
				else if(moni16==0||moni17==0||moni18==0||moni15==0)
				{
					while(moni14!=0||moni15!=0)
					{
						jiance();
						guaiwan(25,60,25,60,1,-1,1,-1);
					}
				}
				else if(moni12==0||moni13==0||moni14==0)
				{
					while(moni14!=0||moni15!=0)
					{
						jiance();
						guaiwan(60,25,60,25,-1,1,-1,1);
					}
				}
	
		else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1&&GD1==0)//������
		{
			while(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)
			{
				jiance();
				guaiwan(60,40,60,40,-1,1,-1,1);
			}
		}
		else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1&&GD2==0)//����ҹ�
		{
			while(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)
			{
				jiance();
				guaiwan(40,60,40,60,1,-1,1,-1);
			}
		}
	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(15,15,15,15,1,1,1,1);
	else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)//ֱ����̽
			guaiwan(15,15,15,15,1,1,1,1);	
	
}

void jixianxun1()
{
	if(moni12==1&&moni13==1&&(moni14==0)&&moni16==1&&moni17==1)
				{	
					guaiwan(20,20,20,20,1,1,1,1);
				}
		if(moni12==1&&moni15==0&&moni17==1)//youguai
		while(moni14!=0)
		{
			jiance();
			guaiwan(20,50,20,50,1,-1,1,-1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
		}
	else if(moni14==1&&moni16==0&&moni18==1)//���ҹ�
		while(moni14!=0)
		{	
				jiance();
			guaiwan(20,50,20,50,1,-1,1,-1);
		}
	else if(moni14==1&&moni15==1&&moni17==0&&moni18==1)//da�ҹ�
					while(moni14!=0)
					{	
							jiance();
						guaiwan(20,50,20,50,1,-1,1,-1);
					}
		else if(moni14==1&&moni15==1&&moni16==1&&moni18==0)//da�ҹ�
					while(moni14!=0)
					{
						jiance();
						guaiwan(20,55,20,55,1,-1,1,-1);
					}
		else if(moni14==1&&moni15==1&&moni16==0&&moni17==0&&moni18==0)
						while(moni14!=0)
						{
							jiance();
							guaiwan(20,50,20,50,1,-1,1,-1);
						}
else if(moni12==1&&moni13==0&&moni15==1&&moni16==1)//xiao�����
			while(moni14!=0)
			{
				jiance();
				guaiwan(40,30,40,30,-1,1,-1,1);				
			}

			
	else if(moni12==0&&moni15==1&&moni17==1)//zhong�����
			while(moni14!=0)
			{
				jiance();
				guaiwan(40,20,40,20,-1,1,-1,1);				
			}	
	else if(moni12==0&&moni14==0&&moni15==1&&moni17==1)
				while(moni14!=0)
			{
				jiance();
				guaiwan(50,20,50,20,-1,1,-1,1);				
			}
		if(moni12==1&&(moni15==0)&&moni17==1)
		while(moni12==1&&(moni15==0)&&moni17==1)
				{	
					jiance();
					guaiwan(25,25,25,25,1,1,1,1);
				}
	if(moni12==1&&moni14==1&&moni15==1&&moni16==0&&moni18==1)//youguai
		while(moni12==1&&moni14==1&&moni15==1&&moni16==0&&moni18==1)
		{
			jiance();
			guaiwan(30,55,30,55,1,-1,1,-1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
		}
	else if(moni14==1&&moni16==1&&moni17==0&&moni18==1)//���ҹ�
		while(moni14==1&&moni16==1&&moni17==0&&moni18==1)
		{			
			jiance();
			guaiwan(50,50,50,50,1,-1,1,-1);
		}
	else if(moni14==1&&moni15==1&&moni16==1&&moni17==1&&moni18==0)//da�ҹ�
		while(moni14==1&&moni15==1&&moni16==1&&moni17==1&&moni18==0)
		{
			jiance();			
			guaiwan(40,60,40,60,1,-1,1,-1);
		}
	else if(moni12==1&&moni14==0&&moni15==1&&moni16==1)//xiao�����
		while(moni12==1&&moni14==0&&moni15==1&&moni16==1)
		{		
			jiance();
			guaiwan(25,55,25,55,-1,1,-1,1);
		}
	else if(moni12==1&&moni13==0&&moni15==1&&moni17==1)//zhong�����
		while(moni12==1&&moni13==0&&moni15==1&&moni17==1)
		{
			jiance();
			guaiwan(50,50,50,50,-1,1,-1,1);
		}
	else if(moni12==0&&moni13==1&&moni15==1&&moni17==1)//da�����
		while(moni12==0&&moni13==1&&moni15==1&&moni17==1)	
		{	
			jiance();
			guaiwan(60,40,60,40,-1,1,-1,1);
		}
		else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1&&GD1==0)//������
		{
			while(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)
			{
				jiance();
				guaiwan(60,40,60,40,-1,1,-1,1);
			}
		}
		else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1&&GD2==0)//����ҹ�
		{
			while(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)
			{
				jiance();
				guaiwan(40,60,40,60,1,-1,1,-1);
			}
		}
	else if((moni12+moni13+moni14+moni15+moni16+moni17+moni18+moni22+moni23+moni24+moni25+moni26+moni27+moni28)>=14)
		guaiwan(15,15,15,15,1,1,1,1);
	else if(moni12==1&&moni13==1&&moni14==1&&moni15==1&&moni16==1&&moni17==1)//ֱ����̽
			guaiwan(20,20,20,20,1,1,1,1);	
		else
			guaiwan(20,20,20,20,1,1,1,1);	
}

void houjixianxun()
{
	if(moni22==1&&(moni25==0)&&moni27==1)
		while(moni22==1&&(moni25==0)&&moni27==1)
				{	
					jiance();
					houguaiwan(30,30,30,30,1,1);
				}
	if(moni22==1&&moni24==1&&moni25==1&&moni26==0&&moni28==1)//youguai
		while(moni22==1&&moni24==1&&moni25==1&&moni26==0&&moni28==1)
		{
			jiance();
			houguaiwan(55,25,55,25,1,-1);//xiao�ҹ���zuoqian,youqian,zuohou,youhou
		}
	else if(moni24==1&&moni26==1&&moni27==0&&moni28==1)//���ҹ�
		while(moni24==1&&moni26==1&&moni27==0&&moni28==1)
		{			
			jiance();
			houguaiwan(50,50,50,50,1,-1);
		}
	else if(moni24==1&&moni25==1&&moni26==1&&moni27==1&&moni28==0)//da�ҹ�
		while(moni24==1&&moni25==1&&moni26==1&&moni27==1&&moni28==0)
		{
			jiance();			
			houguaiwan(60,60,60,60,1,-1);
		}
	else if(moni22==1&&moni24==0&&moni25==1&&moni26==1)//xiao�����
		while(moni22==1&&moni24==0&&moni25==1&&moni26==1)
		{		
			jiance();
			houguaiwan(25,55,25,55,-1,1);
		}
	else if(moni22==1&&moni23==0&&moni25==1&&moni27==1)//zhong�����
		while(moni22==1&&moni23==0&&moni25==1&&moni27==1)
		{
			jiance();
			houguaiwan(50,50,50,50,-1,1);
		}
	else if(moni22==0&&moni23==1&&moni25==1&&moni27==1)//da�����
		while(moni22==0&&moni23==1&&moni25==1&&moni27==1)	
		{	
			jiance();
			houguaiwan(60,60,60,60,-1,1);
		}
		else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1&&GD2==0)//������
		{
			while(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)
			{
				jiance();
				houguaiwan(60,60,60,60,-1,1);
			}
		}
		else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1&&GD1==0)//����ҹ�
		{
			while(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)
			{
				jiance();
				houguaiwan(60,60,60,60,1,-1);
			}
		}
	else if((moni22+moni23+moni24+moni25+moni26+moni27+moni28+moni12+moni13+moni14+moni15+moni16+moni17+moni18)>=14)
		houguaiwan(15,15,15,15,1,1);
	else if(moni22==1&&moni23==1&&moni24==1&&moni25==1&&moni26==1&&moni27==1)//ֱ����̽
			houguaiwan(20,20,20,20,1,1);		
}




void xianshi(void)
{
		Dis_Num(0,0,moni11,1);
		Dis_Num(0,1,moni12,1);
		Dis_Num(0,2,moni13,1);
		Dis_Num(0,3,moni14,1);
		Dis_Num(0,5,moni15,1);
		Dis_Num(0,6,moni16,1);
		Dis_Num(0,7,moni17,1);
		Dis_Num(0,8,moni18,1);
////		
		Dis_Num(2,0,moni21,1);
		Dis_Num(2,1,moni22,1);
		Dis_Num(2,2,moni23,1);
		Dis_Num(2,3,moni24,1);
		Dis_Num(2,5,moni25,1);
		Dis_Num(2,6,moni26,1);
		Dis_Num(2,7,moni27,1);
		Dis_Num(2,8,moni28,1);
//		Dis_Num(2,0,(int)(s*10),3);
//	Dis_Num(2,4,(int)(sa*10),3);
//	Dis_Num(2,8,tansuo1,3);
	
//		Dis_Num(4,0,qian1,1);
//		Dis_Num(4,1,qian2,1);
//		Dis_Num(4,2,qian3,1);
//		Dis_Num(4,3,qian4,1);
//		Dis_Num(4,5,qian5,1);
//		Dis_Num(4,6,qian6,1);	
//		Dis_Num(4,7,qian7,1);
//		Dis_Num(4,8,qian8,1);

			
		Dis_Num(4,0,GDZ,1);
		Dis_Num(4,2,GDY,1);
		Dis_Num(4,4,GD1,1);
		Dis_Num(4,6,GD2,1);
		Dis_Num(4,8,GD3,1);
//		Dis_Num(4,8,GD4,1);
	Dis_Num(6,0,cha,2);
	Dis_Num(6,4,s*10,3);
	Dis_Num(6,9,moshi,1);
	}
	

	
void youguai()//������TIM2	5800
{
  guaiwan(45,90,45,90,1,-1,1,-1);  //	guaiwan(50,50,20,20,1,-1,1,-1);//guaiwan(70,70,30,30,1,-1,1,-1); 
}	



void xiaoyouguai()//������TIM2	5800
{
guaiwan(50,50,20,20,1,-1,1,-1);//guaiwan(55,45,60,50,1,-1,1,-1);
}


void xiaozuoguai()//������TIM4	2200
{
guaiwan(50,50,20,22,-1,1,-1,1);//guaiwan(45,55,50,60,-1,1,-1,1);
}


void zuoguai()//������TIM4	2200
{
  	guaiwan(90,45,90,45,-1,1,-1,1);//guaiwan(90,45,90,45,-1,1,-1,1); //guaiwan(80,55,80,55,-1,1,-1,1);//guaiwan(50,60,50,60,-1,1,-1,1);
}


void shache()
{
guaiwan(20,20,20,20,-1,-1,-1,-1);
}



void zhunbei()
{
	static int u=0;
	s=400;
	while((GDZ==1&&GDY==0)||(GDZ==0&&GDY==1))
			{

				static int q=0;
				if(q==0)
				{
					guaiwan(80,80,80,80,-1,-1,-1,-1);
					delay_ms(50);
					q++;
				}
				if(GDZ==0&&GDY!=0)//���������ֽ�
				{
				
					while(GDZ==0&&GDY!=0)
					{
						zuolun(40,-1);
						youlun(40,1);
					}
				}
//					
				if(GDY==0&&GDZ==1)//���������ֽ�
				{
					while(GDY==0&&GDZ==1)
					{
						youlun(40,-1);
						zuolun(40,1);
					}
				}
				if(GDY==0&&GDZ==0)
				{
					ting();
					delay_ms(50);
					u=1;
					break;
				}
			}					
			if((GDZ==0&&GDY==0)||u==1)
			{
				TIM_Cmd(TIM7, DISABLE);
					while(GD3==1&&GD4==1)
						qianjin();
					while((GD3==1&&GD4==0)||(GD3==0&&GD4==1))
				{
					static int q=0;
					if(q==0)
					{
						ting();
						delay_ms(100);
						q++;
					}
					if(GD3==0&&GD4==1)//���������ֽ�
					{
						zuolun(30,-1);
						youlun(30,1);
					}					
					if(GD4==0&&GD3==1)//����tui���ֽ�
					{
						youlun(30,-1);
						zuolun(30,1);
					}
				}					
				if(GD3==0&&GD4==0)
				{
					while(s>14.5&&u==2)
						{
							s=ceju();
								qianjin();
						}
			}
			}
}




void qianjin()
{
	guaiwan(20,20,20,20,1,1,1,1);
	delay_ms(15);
}	

void xiaoqianjin()
{
	guaiwan(15,15,15,15,1,1,1,1);
}

void xiaohoutui(void)
{
	guaiwan(15,15,15,15,-1,-1,-1,-1);
}
void houtui()
{
	guaiwan(20,20,20,20,-1,-1,-1,-1);
}



void	ting()
{
	guaiwan(1,1,1,1,-1,-1,-1,-1);
	delay_ms(15);
}
void jiaodu()
{
	
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0);
}
void chushihua()
{
	while(MPU_Init())
									;					//��ʼ��MPU6050
			while(mpu_dmp_init())
			{
				static int u=0;
				u++;
				if(u==20)
				{
					u=0;
					while(MPU_Init())
					{
						
					}
				}
			}
			while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0);
	
}

void SendData ( u8 addr )
{ 
 u8 i; 
 sda = 1;
 delay_ms(3);
 sda = 0;
  delay_ms( 4 );
 for ( i = 0; i < 8; i++ ) 
 { 
 sda = 1; 
 if ( addr & 0x01 ) 
 { 
  delay_us( 1350 ); 
 sda = 0; 
 delay_us( 400 ); 
 } 
 else
 { 
  delay_us ( 400 ); 
 sda = 0; 
 delay_us ( 1350 ); 
 } 
 addr >>= 1; 
 } 
 sda = 1; 

}

void laba()
{
	SendData(0x0a);
  SendData(0x03);
  SendData(0x00);
  SendData(0x0c);
	SendData(0x0a); 
  SendData(0x02); 
  SendData(0x0b); 
	SendData(0x11);
}
