#ifndef __MONI_H
#define __MONI_H	
#include "sys.h" 
#include "adc.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LSENS(����������)��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////
  
#define LSENS_READ_TIMES	5		//���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
 
void Lsens_Init(void); 				//��ʼ������������
void Lsens_Get_Val1(void);
void jiance(void);
//void qianjiance(void);
void houjiance(void);
#endif 





















