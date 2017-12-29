/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ���ڽ�������
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "Uart.h"

/**�궨��***********************************************************************/
//������������
#define uint unsigned int 
#define uchar unsigned char

#define LED1  P1_0    //P1_0����LED1
#define LED2  P1_1    //P1_1����LED2
#define LED3  P0_4    //P1_4����LED3

/**��������*********************************************************************/
void Send_ReceicedData(void);
void Initial_IO(void);
void Delayms(uint xms);

/**ȫ�ֱ���*********************************************************************/
//��������͵�����
char Txdata0[]={"�����Ƽ���ӭ��\n"}; //���"�����Ƽ���ӭ��"
char Txdata1[]={"This is a Uart test.\n"};
char Txdata2[]={"The data CC2530 has received is: \n"};
char Txdata3[]={"\r\n"};
char Rxdata = '\0'; 


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
    SetSysClock();               //����ϵͳʱ��Ϊ32MHz
     
    InitUART();                  //���ó�ʼ������ 
    
    Initial_IO();		 //���ó�ʼ������
    
    
    UartSend_String(Txdata0,sizeof("�����Ƽ���ӭ��\n"));
    Delayms(500);
    UartSend_String(Txdata1,sizeof("This is a Uart test.\n"));
    
    while(1)
    { 
        Send_ReceicedData();      
    }
  
}

/**
  * @brief     USART�����ж�
  * @param     None
  * @retval    None
  */
#pragma vector = URX0_VECTOR 
  __interrupt void UART0_ISR(void) 
 { 
    Rxdata = U0DBUF;   //�������ݲ�����Rxdata

    URX0IF = 0;    // ���жϱ�־ 
 }

/**
  * @brief     �����յ������ݷ��ظ�����
  * @param     None
  * @retval    None
  */
void Send_ReceicedData(void)
{  
    if ( Rxdata != '\0' ) 
    {
      UartSend_String(Txdata2,sizeof("The data CC2530 has received is: ")); //��ʾ���յ�����
      Send_char(Rxdata);
      UartSend_String(Txdata3,sizeof("\n"));
      
      if (Rxdata=='1')
      {
        LED1=0;
        Delayms(500);
        LED1=1;        
      }
      
      if (Rxdata=='2')
      {
        LED2=0;
        Delayms(500);
        LED2=1;        
      }

      if (Rxdata=='3')
      {
        LED3=0;
        Delayms(500);
        LED3=1;        
      }  
  
      Rxdata='\0';    
      
    }

}
/**
  * @brief     IO��ʼ������
  * @param     None
  * @retval    None
  */
void Initial_IO(void)
{
    P1DIR |= 0xff;     //P1Ϊ���
    P0DIR |= 0xff;
}

/**
  * @brief     ��ͨ��ʱ����
  * @param     xms ��ʱ����
  * @retval    None
  */
void Delayms(uint xms)   
{
    uint i,j;
    for(i=xms;i>0;i--)
        for(j=587;j>0;j--);
}
