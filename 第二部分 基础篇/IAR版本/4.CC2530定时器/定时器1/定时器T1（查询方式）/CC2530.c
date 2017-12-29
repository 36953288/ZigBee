/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ͨ����ʱ��T1��ѯ��ʽ����LED1��������˸
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���

/**��������*********************************************************************/
void InitLed(void);		//��ʼ��P1��
void InitT1();                  //��ʼ����ʱ��T1


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
  uchar count=0;
  InitLed();		//���ó�ʼ������
  InitT1();
  while(1)
  {
    if(T1IF>0)
    {
      T1IF=0;
      if(++count==1)      //Լ1s��������˸
      {
        count=0;
        LED1 = !LED1;        //LED1��˸        
      }
    }
  }
}


/**
  * @brief     ��ʼ��IO
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
  P1DIR |= 0x03;  //P1_0����Ϊ���
  LED1 = 1;       //LED1�Ƴ�ʼ��Ϩ��
    
}

/**
  * @brief     ��ʱ������
  * @param     None
  * @retval    None
  */
void InitT1() //ϵͳ�����ù���ʱ��ʱĬ����2��Ƶ����16MHz
{
  T1CTL = 0x0d;          //128��Ƶ���Զ���װ 0X0000-0XFFFF 
  T1STAT= 0x21;          //ͨ��0, �ж���Ч   
}
