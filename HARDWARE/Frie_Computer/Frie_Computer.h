#ifndef _Frie_Computer_H_
#define _Frie_Computer_H_


#include "usart.h"      //����


void uart_putbuff (uint8_t *buff, uint32_t len);    //�޸Ĵ˺����ڵĴ��ں�
void vcan_sendimg(void *imgaddr, uint32_t imgsize);
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize);
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize);
void vcan_sendware(void *wareaddr, uint32_t waresize);



#endif
