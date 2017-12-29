/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��������LED����ѯ��ʽ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//LED1ΪP1.0�ڿ���
#define KEY1 P0_1       //KEY1ΪP0.1�ڿ���

/**��������*********************************************************************/
void Delayms(uint);		//��ʱ����
void InitLed(void);		//��ʼ��LED1
void InitKey();                 //������ʼ��
uchar KeyScan();                //����ɨ�����


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
  InitLed();		//���ó�ʼ������
  InitKey();
  while(1)
  {
   if(KeyScan())       //�����ı�LED״̬
     LED1=~LED1;       
  }
}

/**
  * @brief     ��ͨ��ʱ����
  * @param     xms ��ʱ����
  * @retval    None
  */
void Delayms(uint xms)   //i=xms ����ʱi����
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/**
  * @brief     LED��ʼ��
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0����Ϊ���
    LED1 = 1;       //LED1��Ϩ��     
}

/**
  * @brief     ������ʼ��
  * @param     None
  * @retval    None
  */
void InitKey()
{
  P0SEL &= ~0X02;    //����P01Ϊ��ͨIO��  
  P0DIR &= ~0X02;   //������P01 �ڣ�����Ϊ����ģʽ 
  P0INP &= ~0x02;   //��P01��������,��Ӱ��
}

/**
  * @brief     ������⺯��
  * @param     None
  * @retval    uchar
  */
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);
    if(KEY1==0)
    {
      while(!KEY1);  //���ּ��
      return 1;      //�а�������
    }
  }
  return 0;          //�ް�������
}
