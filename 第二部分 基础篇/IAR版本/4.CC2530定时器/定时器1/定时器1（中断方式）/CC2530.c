/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��ʱ��T1���жϷ�ʽ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//����LED1ΪP1_0�ڿ���

/**��������*********************************************************************/
void Delayms(uint xms);		//��ʱ����
void InitLed(void);		//LED_IO��ʼ������
void InitT1(void);              //Timer1�жϷ�ʽ��ʼ������

/**ȫ�ֱ���*********************************************************************/
//�������жϺ����õ���һ��Ҫ����Ϊȫ�ֱ���
uint count=0;//���ڼ�������жϵĴ���

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{	
    InitLed();		//���ó�ʼ������
    InitT1();
    while(1)
    {
    }
}

/**
  * @brief     �жϷ�����
  * @param     None
  * @retval    None
  */
#pragma vector = T1_VECTOR  //Timer1�ж�����
 __interrupt void T1_ISR(void) 
{ 
    IRCON = 0x00;           //���жϱ�־, Ҳ����Ӳ���Զ���� 
    if((++count)==1)        //1���жϺ�LEDȡ������˸һ�֣�0.5 ��ʱ�䣩 
    {          
        count = 0;          //�������� 
        LED1=~LED1;
    } 
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


/**
  * @brief     LED��ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0��Ϊ���
    LED1 = 1;       //LED1��Ϩ��
}


/**
  * @brief     Timer1�жϷ�ʽ��ʼ������
  * @param     None
  * @retval    None
  */
void InitT1(void)
{     
    T1CTL|=0X0d;               //128��Ƶ����������ģʽ 
    T1IE = 1;                  //��Timer1�ж�
    EA = 1;                    //�����ж�
}
