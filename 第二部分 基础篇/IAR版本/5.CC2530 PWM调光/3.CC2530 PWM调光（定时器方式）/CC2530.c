/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       PWM����LED������(��ʱ����ʽ)
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;

//������ƵƵĶ˿�
#define LED1 P1_0       // P1.0�ڿ���LED1

/**��������*********************************************************************/
void InitLed(void);            //LED��ʼ��
void InitT1();                 //��ʱ����ʼ��
void Delay(unsigned int t);   //��ʱ����

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
    uint i;
    uint rate[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
    
    InitLed();		     //���ó�ʼ������
    InitT1();                //��ʱ����ʼ����pwm����
    
    while(1)
    {
      for(i=0;i<11;i++)
      {
        T1CC2H = 0x00;
        T1CC2L = rate[i];
        Delay(50000);
        Delay(50000);
        Delay(50000);
      }
    }

}

/**
  * @brief     ����LED����Ӧ��IO��
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0����Ϊ���
    LED1 = 0;                //ʹLED1���ϵ�Ĭ��ΪϨ��     
}

/**
  * @brief     ��ʱ����ʼ����TICKSPD ��16 MHzϵͳ������ʱĬ����2��Ƶ����16MHz
  * @param     None
  * @retval    None
  */
void InitT1()
{
    CLKCONCMD &= ~0x40;      //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40); //�ȴ������ȶ�Ϊ32M
    CLKCONCMD &= ~0x07;      //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
    CLKCONCMD |= 0x38;       //ʱ���ٶ�32 MHz ��ʱ������������[5:3]250kHz

    //��ʱ��ͨ������
    PERCFG |= 0x40;          //��ʱ��1 ��IOλ��   1:����λ��2 
    P2SEL &= ~0x10;          //��ʱ��1����
    P2DIR |= 0xC0;           //��1���ȼ�����ʱ��1ͨ��2-3

    P1DIR |= 0xff;           //�˿�1Ϊ���    
    P1SEL |= 0x01;           //timer1 ͨ��2ӳ���P1_0

    //��ʱ��ͨ��2�Ƚ�ֵ
    T1CC2H = 0x00;           //20%ռ�ձ�Ϊ200us
    //�޸�T1CC2L�ɵ���led������
    //T1CC2L = 0xF7; //1%����ռ�ձ�
    //T1CC2L = 0xE1; //10%����ռ�ձ�
    //T1CC2L = 0xC8; //20%����ռ�ձ�
    //T1CC2L = 0xAF; //30%����ռ�ձ�
    //T1CC2L = 0x96; //40%����ռ�ձ�
    T1CC2L = 0x7D; //50%����ռ�ձ�
    //T1CC2L = 0x64; //60%����ռ�ձ�
    //T1CC2L = 0x4B; //70%����ռ�ձ�
    //T1CC2L = 0x32; //80%����ռ�ձ�
    //T1CC2L = 0x19; //90%����ռ�ձ�
    //T1CC2L = 0x0A; //99%����ռ�ձ�
    //T1CC2L = 0x01; //����ͨ��2�ȽϼĴ�����ֵ

    //װ��ʱ��ͨ��0��ֵ
    T1CC0H = 0x00;           //1ms������ʱ��,Ƶ��Ϊ976.516HZ
    T1CC0L = 0xff; 
    
    T1CCTL2 = 0x1c;          // ģʽѡ�� ͨ��2�Ƚ�ģʽ
    
    //ģʽ����
    T1CTL = 0x02;            //250KHz ����Ƶ
}

/**
  * @brief     ��ʱ����
  * @param     xms ��ʱ��С
  * @retval    None
  */
void Delay(unsigned int xms)
{
 while(xms--);
}