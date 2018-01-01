/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��ˮ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <cc2510.h>
/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0 //���� LED1 Ϊ P10 �ڿ���
#define LED2 P1_1 //���� LED2 Ϊ P11 �ڿ���
#define LED3 P0_4 //���� LED3 Ϊ P04 �ڿ���

/**��������*********************************************************************/
void Delay(uint); //��ʱ����;
void InitIO(void); //��ʼ�� LED ���� IO �ں���

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
	InitIO(); //��ʼ�� LED �ƿ��� IO ��
	while(1) //ѭ��
	{
		LED1=!LED1; // LED1 ����һ��
		Delay(30);
		
		LED2=!LED2; // LED2 ����һ��
		Delay(30);
		
		LED3=!LED3; // LED3 ����һ��
		Delay(30);
	}
}

/**
  * @brief     ��ʱ����
  * @param     n     ��ʱ��С
  * @retval    None
  */
void Delay(uint n)
{
    uint i;
     for(i = 0;i<n;i++)
     {
       int j;
      for(j = 0;j<10000;j++);
     }
}

/**
  * @brief     ��ʼ��IO����
  * @param     None
  * @retval    None
  */
void InitIO(void)
{
  P1DIR |=0x03; //P10�� P11 ����Ϊ���
  P0DIR |= 0x10;//P04����Ϊ���
	LED1=1;
  LED2=1;
  LED3=1; //LED �Ƴ�ʼ��
}
