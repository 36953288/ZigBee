/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       LED1��˸3�κ����˯��״̬��ͨ�����°���K2�����ⲿ�жϽ��л���
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;

//����IO��
#define LED1 P1_0            //P1.0�ڿ���LED
#define KEY2 P2_0            //P2.0�ڿ���KEY2

/**��������*********************************************************************/
void DelayMS(uint msec);
void InitLed(void);
void InitKey();
void SysPowerMode(uchar mode) ;

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{   
    uchar i=0;  
      
    InitLed();		        //����LED����Ӧ��IO��     
    InitKey();               //����KEY��Ӧ��IO��
    
    while(1)
    {
        for (i=0; i<6; i++)  //LED��˸3�������û�������˯��ģʽ
        {
            LED1 = ~LED1;
            DelayMS(500);
        }

        SysPowerMode(3);     //����˯��ģʽPM3,���°���K1�жϻ���ϵͳ 
    }
}

/**
  * @brief     ��ʱ����,��Լ1����
  * @param     msec ��ʱ��С
  * @retval    None
  */
void DelayMS(uint msec)
{ 
    uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

/**
  * @brief     LED����IO�ڳ�ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0����Ϊ�����
    LED1 = 1;                //LED���ϵ�Ĭ��ΪϨ�� 
}

/**
  * @brief     ��������IO�ڳ�ʼ������
  * @param     None
  * @retval    None
  */
void InitKey()
{
    P2IEN |= 0x1;    // P2.0 ����Ϊ�жϷ�ʽ 1���ж�ʹ��
    PICTL |= 0x8;    //�½��ش���   
    IEN2 |= 0x2;     //����P2���ж�; 
    P2IFG = 0x00;    //��ʼ���жϱ�־λ
    EA = 1;          //�����ж�
}

/**
  * @brief     ϵͳ����ģʽѡ����
  * @param     None
  * @retval    None
  * @attention
  *            para1  0 	1	2	3									
  *            mode 	PM0	PM1	PM2	PM3													
  */
void SysPowerMode(uchar mode) 
{ 
    if(mode > 0 && mode < 4) 
    {  
        SLEEPCMD |= mode;    //����ϵͳ˯��ģʽ 
        PCON = 0x01;         //����˯��ģʽ ,ͨ���жϻ���
    } 
    else 
        PCON = 0x00;         //����/����ģ   ͨ���жϻ���ϵͳ 
}

/**
  * @brief     �жϴ�����-ϵͳ����
  * @param     None
  * @retval    None
  */
#pragma vector = P2INT_VECTOR    
__interrupt void P2_ISR(void) 
{ 
    if(P2IFG > 0) 
    { 
        P2IFG = 0;           //���־λ
    } 
    
    P2IF = 0; 
    SysPowerMode(4);         //��������ģʽ
} 

