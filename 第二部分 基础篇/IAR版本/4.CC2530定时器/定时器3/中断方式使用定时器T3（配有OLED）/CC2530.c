/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ��ʱ��T3ͨ���жϷ�ʽ����LED1��������˸
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "lcd.h"

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;

//������ƵƵĶ˿�
#define LED1 P1_0       // P1.0�ڿ���LED1

/**��������*********************************************************************/
void InitLed(void);    //LED��ʼ��
void InitT3();          //��ʱ����ʼ��
void dispLED1State();   //LED״̬����

/**ȫ�ֱ���*********************************************************************/
uint count;             //���ڶ�ʱ������

/**
  * @brief     �жϴ�����
  * @param     None
  * @retval    None
  */
//��ʱ��T3�жϴ�����
#pragma vector = T3_VECTOR 
__interrupt void T3_ISR(void) 
{ 
    IRCON = 0x00;            //���жϱ�־, Ҳ����Ӳ���Զ���� 
    if(count++ > 245)        //245���жϺ�LEDȡ������˸һ�֣�ԼΪ0.5 ��ʱ�䣩 
    {                        //����ʾ��������ȷ����ȷ
        count = 0;           //�������� 
        LED1 = ~LED1;        //�ı�LED1��״̬
        dispLED1State();
    } 
}

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
    InitLed();		  //����LED����Ӧ��IO��
    InitT3();             //����T3��Ӧ�ļĴ���
    

    LCD_Init();//LCD��ʼ��
    LCD_CLS();//����
    LCD_welcome();
    dispLED1State();
    
    while(1)
    {};
}

/**
  * @brief     LED��ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0����Ϊ���
    LED1 = 1;                //ʹLED1���ϵ�Ĭ��ΪϨ��     
}

/**
  * @brief     ��ʱ����ʼ����ϵͳ�����ù���ʱ��ʱĬ����2��Ƶ����16MHz
  * @param     None
  * @retval    None
  */
void InitT3()
{     
    T3CTL |= 0x08 ;          //������ж�     
    T3IE = 1;                //�����жϺ�T3�ж�
    T3CTL |= 0xE0;           //128��Ƶ,128/16000000*N=0.5S,N=62500
    T3CTL &= ~0x03;          //�Զ���װ 00��>0xff  62500/255=245(��)
    T3CTL |= 0x10;           //����
    EA = 1;                  //�����ж�
}

/**
  * @brief     LED״̬����
  * @param     None
  * @retval    None
  */
void dispLED1State()
{
  if(LED1>0)
  {
    //��ʾ"D1:��"
    LCD_P8x16Str(16, 5, "D1:");
    LCD_P16x16Ch(40, 5, 15);    
  }
  else
  {
     //��ʾ"D1:��"
    LCD_P8x16Str(16, 5, "D1:");
    LCD_P16x16Ch(40, 5, 14);   
  }                

}

