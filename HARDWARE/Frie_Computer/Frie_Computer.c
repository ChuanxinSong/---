
/*! ɽ�����ܳ�����������λ��
 *  @brief      ��λ�����ͺ���
 *  @param      
 *  @param      
 *  @since      
 *  @date       2018.11.11
*/

#include "Frie_Computer.h"//ɽ����λ��

/*!
 *  @brief      ����ָ��len���ֽڳ������� (���� NULL Ҳ�ᷢ��)
 *  @param      
 *  @param      buff        �����ַ
 *  @param      len         ��������ĳ���
 *  @since      v5.0
 *  Sample usage:       uart_putbuff (UART3,"1234567", 3); //��Ƿ�����3���ֽ� '1','2','3'
 */
void uart_putbuff (uint8_t *buff, uint32_t len)
{
    while(len--)
    {
        putchar(0x00|(*buff));
        buff++;
    }
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ͷ��ʾ����
 *  @param      imgaddr    ͼ����ʼ��ַ
 *  @param      imgsize    ͼ��ռ�ÿռ��С
 *  @since      v5.0
 *  Sample usage:
             �����÷��ο�������:
            ��ɽ������ͷ��ӥ����λ�����̺�΢��Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6242&ctid=27
 */
void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    
    uart_putbuff(cmdf, sizeof(cmdf));    //�ȷ�������

    uart_putbuff((uint8_t *)imgaddr, imgsize); //�ٷ���ͼ��

    uart_putbuff(cmdr, sizeof(cmdr));    //�ٷ�������
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������CCD��ʾ����
 *  @param      ccdaddr    CCDͼ����ʼ��ַ
 *  @param      ccdsize    CCDͼ��ռ�ÿռ��С
 *  @since      v5.0
 *  Sample usage:
             �����÷��ο�������:
            ��ɽ������CCD����λ����ʾ���̺ͳ���ǲɼ�Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6340&ctid=27
 */
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize)
{
#define CMD_CCD     2
    uint8_t cmdf[2] = {CMD_CCD, ~CMD_CCD};    //��ͷ����
    uint8_t cmdr[2] = {~CMD_CCD, CMD_CCD};    //��β����

    uart_putbuff(cmdf, sizeof(cmdf));    //�ȷ�������

    uart_putbuff((uint8_t *)ccdaddr, ccdsize); //�ٷ���ͼ��

    uart_putbuff(cmdr, sizeof(cmdr));    //�ٷ�������
}
 

/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ʾ������ʾ����
 *  @param      wareaddr    ����������ʼ��ַ
 *  @param      waresize    ��������ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ�����ϡ������Ǻͼ��ٶ� ��λ����ʾ���� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6253&ctid=27
 */
void vcan_sendware(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_putbuff(cmdf, sizeof(cmdf));    //�ȷ�������
    uart_putbuff((uint8_t *)wareaddr, waresize);    //��������
    uart_putbuff(cmdr, sizeof(cmdr));    //���ͺ�����
}

