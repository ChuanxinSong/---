#include "duoji.h"
#include "delay.h"
void TIM1_PWM_Init(u32 arr,u32 psc)
 {
  	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);    

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOE9,E11����Ϊ��ʱ��1
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOE9,E11����Ϊ��ʱ��1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;           //GPIO

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����

	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PE9

  TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ

	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;//?????0

	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2

 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //?�������:TIM����Ƚϼ��Ը�

 

	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//�ڿ���ʱ����ͣ����û����䣬ͨ��һ�������


	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);


	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //???TIM1?CCR1????????,CCR???????????

	TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE?? 

	TIM_Cmd(TIM1, ENABLE);  //???TIM1

	TIM_CtrlPWMOutputs(TIM1, ENABLE);//???TIM1?PWM??,TIM1?TIM8??,?????????

 }
 
 
 void TIM8_PWM_Init(u32 arr,u32 psc)
 {
  	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);    

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); //GPIOE9,E11����Ϊ��ʱ��1
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); //GPIOE9,E11����Ϊ��ʱ��1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;           //GPIO

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����

	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PE9

  TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ

	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;//?????0

	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2

 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //?�������:TIM����Ƚϼ��Ը�

 

	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//�ڿ���ʱ����ͣ����û����䣬ͨ��һ�������


	TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);


	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //???TIM1?CCR1????????,CCR???????????

	TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE?? 

	TIM_Cmd(TIM8, ENABLE);  //???TIM1

	TIM_CtrlPWMOutputs(TIM8, ENABLE);//???TIM1?PWM??,TIM1?TIM8??,?????????

 }

void duoji1(u32 asc)//��Խ���ſ��ĽǶ�Խ��
{
	TIM_SetCompare1(TIM1,20000-asc );
}
void	duoji2(u32	asc)
{
	TIM_SetCompare2(TIM1,20000-asc );
}	
void duoji4(u32 asc)//��Խ��Խ����
{
	TIM_SetCompare3(TIM8,20000-asc );//
}
void	duoji3(u32 asc)//��ԽСԽ����
{
	TIM_SetCompare4(TIM8,20000-asc);//
}

void gaoju()//ץȡ�����������ʱ
{
	int i;
	for(i=550;i<=2000;i+=10)
	{
		duoji4(i);
		delay_ms(20);
	}
	for(i=800;i<=900;i+=10)
	{
		duoji3(i);			//(20000-1300)
		delay_ms(20);
	}
	for(i=900;i<1850;i+=10)
	{
		duoji2(i);
		delay_ms(20);
	}
	for(i=2000;i<2500;i+=10)
	{
		duoji4(i);//(20000-2500)
		delay_ms(20);
	}
	






}

void	shunazhunbei()
{
	duoji4(1800);
	delay_ms(500);
	duoji3(550);
	delay_ms(500);
		duoji4(550);
		delay_ms(500);
//	duoji3(800);
//		delay_ms(500);
	
	duoji2(820);//900
		delay_ms(500);
	duoji1(2400);
	delay_ms(500);
//	delay_ms(500);


}

void shuna()
{
	int i;
	duoji4(550);
		delay_ms(500);
	
	duoji3(800);
		delay_ms(500);

	duoji2(900);
		delay_ms(500);
		
	duoji1(2000);
	delay_ms(200);
	for(i=2000;i>=1500;i-=5)
	{
		duoji1(i);
		delay_ms(20);
	}
	

}
void fang()
{
	duoji4(2450);
	duoji3(2200);
	duoji2(900);
}
void  shufang()//14
{
	int i;
	for(i=2450;i>1500;i-=10)
	{
		duoji4(i);
		delay_ms(20);
	}
		for(i=900;i>800;i-=10)
	{
		duoji3(i);
		delay_ms(20);
	}
	for(i=1850;i>900;i-=10)
	{
		duoji2(i);
		delay_ms(20);
	}
	for(i=1500;i>550;i-=10)
	{
		duoji4(i);
		delay_ms(20);
	}
		
	

	for(i=1500;i<2100;i++)
	{
		duoji1(i);
		delay_ms(10);
	}
//	for(i=1800;i>1600;i--)
//	{
//		duoji1(i);
//		delay_ms(20);
//	}
	duoji1(2300);
		delay_ms(20);
}

void shuipingshufangzhunbei()
{
	int i;
	duoji4(1780);
		delay_ms(500);
	duoji3(2250);
		delay_ms(500);
	
	duoji2(900);
		delay_ms(500);
	
	for(i=1500;i<1800;i+=5)
	{
		duoji1(i);
		delay_ms(20);
	}
	for(i=1800;i>1600;i-=1)
	{
		duoji1(i);
		delay_ms(20);
	}
	duoji1(2300);
		delay_ms(20);
}


void shuipingshufang()
{

	int i;
	duoji4(1500);
		delay_ms(500);
	duoji3(2250);
		delay_ms(500);
	
	duoji2(900);
		delay_ms(500);
	
	for(i=1500;i<1900;i+=5)
	{
		duoji1(i);
		delay_ms(20);
	}
//	for(i=1800;i>1600;i-=1)
//	{
//		duoji1(i);
//		delay_ms(20);
//	}
	duoji1(2300);
		delay_ms(20);
}

void	hengna()
{
	//��//�������⵽ʱ
//	duoji4(2400);//(20000-2500)
//	delay_ms(500);
//	duoji3(2350);			//(20000-1300)
//	delay_ms(500);
//	
//	duoji2(1900);
//	delay_ms(500);	
//	duoji1(2300);
//	delay_ms(500);
	//Ȼ��13.5��
//	duoji4(2000);//(20000-2500)
//	delay_ms(500);
//	duoji3(2350);			//(20000-1300)
//	delay_ms(500);
//	
//	duoji2(1900);
//	delay_ms(500);	
//	duoji1(2300);
//	delay_ms(500);
	//Ȼ��6.9��6֮��
//	duoji4(1800);//(20000-2500)
//	delay_ms(500);
//	duoji3(2350);			//(20000-1300)
//	delay_ms(500);
//	
//	duoji2(1900);
//	delay_ms(500);	
//	duoji1(2300);
//	delay_ms(500);

//Ȼ��
duoji1(1550);
delay_ms(20);

//׼����
duoji4(2200);
delay_ms(20);
//����gaoju

//	

}

void	hengfang()
{
	duoji1(1600);
	duoji2(1500);
	duoji3(1500);
	duoji4(1500);	
}


