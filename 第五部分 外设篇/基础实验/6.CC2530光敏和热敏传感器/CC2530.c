/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2018-01
  * @brief       ����ʵ�飬�й�ʱLED1�������ֵ�ס��������ʱLED1Ϩ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;

//�˿ڶ���
#define LED1 P1_0            //����P1.0��ΪLED1���ƶ�
#define DATA_PIN P0_5        //����P0.5��Ϊ�����������


/**��������*********************************************************************/
void InitLed(void);
void DelayMS(uint msec);

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{          
  P0DIR &= ~0x20;          //P0.5����Ϊ����� 
  
  InitLed();               //����LED����Ӧ��IO��

  while(1)                 //��ѭ��  
  {
    if(DATA_PIN == 1)    //���������账�ںڰ���ʱP0.5�ߵ�ƽ,LED1Ϩ��
    { 
      LED1 = 1;     
      DelayMS(1000);    
    }
    else    
    {     
      LED1 =  0;       //��⵽����ʱP0.5Ϊ�͵�ƽLED1��
      DelayMS(1000);
    }   
  }    
}

/**
  * @brief     LED��ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{  
  P1DIR |= 0x01;           //P1.0����Ϊ�����
}

/**
  * @brief     �Ժ���Ϊ��λ��ʱ 16MʱԼΪ535,ϵͳʱ�Ӳ��޸�Ĭ��Ϊ16M
  * @param     msec ��ʱ������ֵԽ����ʱԽ��
  * @retval    None
  */
void DelayMS(uint msec)
{   
  uint i,j;
     
  for (i=0; i<msec; i++)   
    for (j=0; j<535; j++);
}