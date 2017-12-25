/*******************************************************************************
*�ļ���   �� Uart.h
*ʵ�ֹ��� �� USART�ײ�����
*ʵ��ƽ̨ �� ��� Zigbee ������
*Ӳ������ �� Usart0_Rx  P0_2 
             Usart0_Tx  P0_3
*����     �� ����Ŷ�
*����ʱ�� �� 2013/8/4 
*��ϵ��ʽ ��  QQ   449199327 @Cavani
             �Ա�  ��������Ƽ�
                   http://shop110226727.taobao.com
*******************************************************************************/

#ifndef __Uart_H
#define	__Uart_H

#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int 
#define uchar unsigned char

void InitUART(void);
void Send_char(uchar c);
void UartSend_String(char *Data,int len);
//void SetSysClock(void);
void Delayms(uint xms);

#endif 

/*********************************************END OF FILE**********************/
