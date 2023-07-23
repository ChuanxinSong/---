#ifndef _OLED_H
#define _OLED_H

#include "stm32f4xx.h"

//#define DC   PAout(4)	
//#define RES  PAout(5)	
//#define SDA  PAout(6)	
//#define SCL  PAout(7)	
#define OLED_GPIO    GPIOB
#define OLED_RCCEN   RCC_APB1Periph_GPIOB
#define OLED_SCL     GPIO_Pin_15      //D0		SCL接PB15
#define OLED_SDA     GPIO_Pin_10     //D1		SDA接PD10
#define OLED_RST     GPIO_Pin_8      //RST	RST接PD8
#define OLED_DC      GPIO_Pin_14      //DC		DC接PE14

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define OLED_D0_OL		GPIO_ResetBits(OLED_GPIO, OLED_SCL)	//D0 IO输出低电平
#define OLED_D0_OH		GPIO_SetBits(OLED_GPIO, OLED_SCL)  	//D0 IO输出高电平

#define OLED_D1_OL		GPIO_ResetBits(GPIOD, OLED_SDA)	//D1 IO输出低电平
#define OLED_D1_OH		GPIO_SetBits(GPIOD, OLED_SDA) 	//D1 IO输出高电平

#define OLED_RST_OL		GPIO_ResetBits(GPIOD, OLED_RST)	//RST IO输出低电平
#define OLED_RST_OH		GPIO_SetBits(GPIOD, OLED_RST) 	//RST IO输出高电平

#define OLED_DC_OL		GPIO_ResetBits(GPIOE, OLED_DC)	//DC IO输出低电平
#define OLED_DC_OH		GPIO_SetBits(GPIOE, OLED_DC) 	//DC IO输出高电平

#define OLED_RST_Clr()  GPIO_ResetBits(GPIOD, OLED_RST) //RST IO输出低电平
#define OLED_RST_Set()  GPIO_SetBits(GPIOD, OLED_RST) 	//RST IO输出高电平

#define OLED_RS_Clr()   GPIO_ResetBits(GPIOE, OLED_DC)	//DC IO输出低电平
#define OLED_RS_Set()   GPIO_SetBits(GPIOE, OLED_DC) 	  //DC IO输出高电平

#define OLED_SCLK_Clr() GPIO_ResetBits(OLED_GPIO, OLED_SCL)	//D0 IO输出低电平
#define OLED_SCLK_Set() GPIO_SetBits(OLED_GPIO, OLED_SCL)  	//D0 IO输出高电平

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOD, OLED_SDA)	//D1 IO输出低电平
#define OLED_SDIN_Set() GPIO_SetBits(GPIOD, OLED_SDA) 	//D1 IO输出高电平

void setgpio(void);
void OLED_Init(void);
void OLED_CLS(void);
void OLED_4num(unsigned char x,unsigned char y,int number);
void OLED_3num(unsigned char x,unsigned char y,unsigned int number);
void OLED_Num(unsigned char x,unsigned char y,unsigned char asc);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P14x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Print(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_PutPixel(unsigned char x,unsigned char y);
void OLED_Rectangle(int16_t acc_x,int16_t acc_y);
void Draw_Logo(void);
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char bmp[]); 
void OLED_Fill(unsigned char dat);
void Dis_String(unsigned char y, unsigned char x, unsigned char ch[]);
void Dis_Char(unsigned char y,unsigned char x,unsigned char asc);
void Dis_Num(unsigned char y, unsigned char x, unsigned int num,unsigned char N);
void Dis_Float(unsigned char Y,unsigned char X,double real,unsigned char N);
void Dis_Float2(unsigned char Y,unsigned char X,double real,unsigned char N1,unsigned char N2);
void OLED_P6x8Num_8bit(unsigned char x,unsigned char y,unsigned char Number); 
void OLED_Num5(unsigned char x,unsigned char y,unsigned int number);
void OLED_WR_Byte1(u8 dat,u8 cmd);
void OLED_Clear1(void);  
void OLED_Set_Pos1(u8 x,u8 y);
void OLED_ShowChar1(u8 x,u8 y,u8 a);
void OLED_ShowString1(u8 x,u8 y,u8 *chr);
void OLED_ShowCHinese1(u8 x,u8 y,u8 no);
void display_page1(void);
void display_page2(void);
void display_page3(void);
void display_page4(void);
			


#endif


