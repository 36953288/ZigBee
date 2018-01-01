/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ���ö�ʱ����ϵͳ���趨��ʱ�䱻����,ÿ�λ���LED1��˸3����ʾ�û�
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long ulong;
//�˿ڶ���
#define LED1 P1_0            //P1.0�ڿ���LED1
#define LED2 P1_1            //P1.1�ڿ���LED2

/**��������*********************************************************************/
void DelayMS(uint msec);
void InitLed(void);
void SysPowerMode(uchar mode);
void InitSleepTimer(void);
void Set_ST_Period(uint sec);


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{  
  uchar i=0;  
      
  InitLed();		         //����LED����Ӧ��IO��     
  InitSleepTimer();        //��ʼ�����߶�ʱ��
   
    
  while(1)
  {
    for (i=0; i<6; i++)  //LED1��˸3�������û�������˯��ģʽ
    {
      LED1 = ~LED1;
      DelayMS(500);
    }

    Set_ST_Period(5);   //����˯��ʱ��,˯��5�����ϵͳ
    SysPowerMode(2);    //���½���˯��ģʽPM2
    
    LED2 = ~LED2;
  }
}

/**
  * @brief     ��ʱ����
  * @param     msec ��ʱ������ֵԽ����ʱԽ��
  * @retval    None
  */
void DelayMS(uint msec)
{ 
  uint i,j;
    
  for (i=0; i<msec; i++)
    for (j=0; j<535; j++);
}

/**
  * @brief     ����LED����Ӧ��IO��
  * @param     None
  * @retval    None
  */
void InitLed(void)
{ 
  P1DIR |= 0x03;           //P1.0����Ϊ�����
  LED1 = 1;                //LED1���ϵ�Ĭ��ΪϨ�� 
}

/**
  * @brief     ����ϵͳ����ģʽ
  * @param     mode����0ΪPM0 1ΪPM1 2ΪPM2 3ΪPM3 
  * @retval    None
  */
void SysPowerMode(uchar mode) 
{ 
    if(mode < 4) 
    {  
        SLEEPCMD |= mode;    //����ϵͳ˯��ģʽ 
        PCON = 0x01;         //����˯��ģʽ ,ͨ���жϻ���
    } 
    else 
        PCON = 0x00;         //ͨ���жϻ���ϵͳ 
}

/**
  * @brief      ST_ISR(void) �жϴ����� 
  * @param     None
  * @retval    None
  */
#pragma vector = ST_VECTOR 
__interrupt void ST_ISR(void) 
{ 
    STIF = 0;          //���־λ
    SysPowerMode(4);   //������������ģʽ
} 

/**
  * @brief     ��ʼ�����߶�ʱ��,�趨�󾭹�ָ��ʱ�����л���
  * @param     None
  * @retval    None
  */
void InitSleepTimer(void) 
{ 
    ST2 = 0X00; 
    ST1 = 0X0F; 
    ST0 = 0X0F; 
    EA = 1;     //���ж� 
    STIE = 1;   //˯�߶�ʱ���ж�ʹ�� 0�� �жϽ�ֹ     1�� �ж�ʹ��
    STIF = 0;   //˯�߶�ʱ���жϱ�־ 0�� ���ж�δ��   1�� �ж�δ��
}

/**
  * @brief     ����˯��ʱ��
  * @param     sec ˯��ʱ�� 
  * @retval    None
  */
void Set_ST_Period(uint sec) 
{ 
    ulong sleepTimer = 0; 
    
    sleepTimer |= ST0; 
    sleepTimer |= (ulong)ST1 <<  8; 
    sleepTimer |= (ulong)ST2 << 16; 
    sleepTimer += ((ulong)sec * (ulong)32768); 
    ST2 = (uchar)(sleepTimer >> 16); 
    ST1 = (uchar)(sleepTimer >> 8); 
    ST0 = (uchar) sleepTimer; 
}

