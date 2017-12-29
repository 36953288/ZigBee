/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��ʱ��T1��Ӧ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint   unsigned  int
#define uchar  unsigned  char

//������ƵƵĶ˿�
#define LED1   P1_0	        //����LED1ΪP10�ڿ���
#define LED2   P1_1	        //����LED2ΪP11�ڿ���
#define LED3   P0_4	        //����LED3ΪP04�ڿ���

/**ȫ�ֱ���*********************************************************************/

uint counter=0;				//ͳ���������
uint LEDFlag;				//��־�Ƿ�Ҫ��˸

/**��������*********************************************************************/
void InitialT1test(void);               //��ʼ����������


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main()
{
  InitialT1test(); 	 //���ó�ʼ������
  while(1)   	         //��ѯ���
  {
    if( T1IF> 0)
    {
      T1IF = 0;                //�������־     
      counter++;     
      if(counter==15)            //�жϼ�����Լ0.25s
      {
        counter =0;
        LEDFlag = !LEDFlag;
      }
    }    
    if(LEDFlag)
    {
      LED2 =  LED1;
      LED3 = !LED2;
      LED1 = !LED1;	   // ÿ 1s LED����˸һ�� 
      LEDFlag = !LEDFlag;   // ��˸��־������0
    }                
  }
}

/**
  * @brief     T1��ʼ������
  * @param     None
  * @retval    None
  */
void InitialT1test(void)
{
  //��ʼ��LED���ƶ˿�P1
  P1DIR = 0x03; 	         //P10 P11 Ϊ���
  P0DIR = 0x10;            //P04Ϊ���
  //��Ĭ��Ϊ��
  LED1 = 1;
  LED2 = 1;		
  LED3 = 1;
  //��ʼ��������1
  T1CTL = 0x05;	
  T1STAT= 0x21;          //ͨ��0,�ж���Ч,8��Ƶ;�Զ���װģʽ(0x0000->0xffff)        
}