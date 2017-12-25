/**********************************************
������: �����Ƽ�

����ƽ̨:CC2530

����:2016.1

�޸ģ�2016.2

���ݣ����ڽ�������
************************************************/

#include <ioCC2530.h>
#include "Uart.h"

#define uint unsigned int 
#define uchar unsigned char

#define LED1  P1_0    //P1_0����LED1
#define LED2  P1_1    //P1_1����LED2
#define LED3  P0_4    //P1_4����LED3

//��������
void Send_ReceicedData(void);
void Initial_IO(void);
void Delayms(uint xms);

//��������͵�����
char Txdata0[]={"�����Ƽ���ӭ��\n"}; //���"�����Ƽ���ӭ��"
char Txdata1[]={"This is a Uart test.\n"};
char Txdata2[]={"The data CC2530 has received is: \n"};
char Txdata3[]={"\r\n"};

char Rxdata = '\0'; 


/**************************************************
//main����
***************************************************/
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

/**************************************************
// USART�����ж�
***************************************************/
#pragma vector = URX0_VECTOR 
  __interrupt void UART0_ISR(void) 
 { 
    Rxdata = U0DBUF;   //�������ݲ�����Rxdata

    URX0IF = 0;    // ���жϱ�־ 
 }

/**************************************************
// �����յ������ݷ��ظ�����
***************************************************/
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

/**************************************************
// IO��ʼ������
***************************************************/
void Initial_IO(void)
{
    P1DIR |= 0xff;     //P1Ϊ���
    P0DIR |= 0xff;
}

/**************************************************
// ������ʱ����
***************************************************/
void Delayms(uint xms)   
{
    uint i,j;
    for(i=xms;i>0;i--)
        for(j=587;j>0;j--);
}

/*********************************************END OF FILE**********************/