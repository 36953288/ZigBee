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
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0 //���� LED1 Ϊ P10 �ڿ���
#define LED2 P1_1 //���� LED2 Ϊ P11 �ڿ���
#define LED3 P0_4 //���� LED3 Ϊ P04 �ڿ���

/**��������*********************************************************************/
void Delay(uint);  //��ʱ����
void InitIO(void); //��ʼ�� LED ���� IO �ں���

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
  InitIO();           //��ʼ�� LED �ƿ��� IO ��
  while(1)           //��ѭ��
  {
    LED1 = !LED1;    // LED1 ����һ��
    Delay(1000);
    LED2 = !LED2;    // LED2 ����һ��
    Delay(1000);
    LED3 = !LED3;    // LED3 ����һ��
    Delay(1000);
  }
}

/**
  * @brief     ��ͨ��ʱ����
  * @param     xms ��ʱ����
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/**
  * @brief     ��ʼ��IO��
  * @param     None
  * @retval    None
  */
void InitIO(void)
{
  P1DIR |= 0x03;  //P10�� P11 ����Ϊ���
  P0DIR |= 0x10;  //P04����Ϊ���
  LED1 = 1;
  LED2 = 1;
  LED3 = 1;       //LED �Ƴ�ʼ��Ϊ��
}