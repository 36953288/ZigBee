/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��ʱ��T3����ѯ��ʽ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//�������LED1�ƵĶ˿�
#define LED1 P1_0      //LED1ΪP1_0�˿ڿ���

/**��������*********************************************************************/

void InitLed(void);    //��ʼ��LED�˿�
void InitT3(void);     //��ʼ����ʱ��T3

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
    uchar count=0;
    
    InitLed();		//LED_IO��ʼ��
    InitT3();           //Timer3��ʼ��
    
    while(1)
    {
        if(T3IF>0)    //��ѯ�����־
        { 
            T3IF=0;
            if((++count)==254)      //���һ��ԼΪ0.5s
            {
                count=0;
                LED1 = ~LED1;        //LED1ȡ��   

            }
        } 
    }
}

/**
  * @brief     LED_IO��ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1�˿ڶ���Ϊ���
    LED1 = 1;       //LED�Ƴ�ʼ��Ϩ��

}

/**
  * @brief     Timer3��ʼ������
  * @param     None
  * @retval    None
  */
void InitT3(void)        
{
    T3CTL = 0xF8;   //128��Ƶ���������У���0x00��0xFF�������� 
}

