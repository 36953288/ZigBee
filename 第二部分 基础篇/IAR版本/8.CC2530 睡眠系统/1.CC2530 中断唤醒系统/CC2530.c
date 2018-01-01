/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       �жϻ���ϵͳ
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int
#define uchar unsigned char

#define PM0 0
#define PM1 1
#define PM2 2
#define PM3 3

#define LED1 P1_0
#define LED2 P1_1   //LED�ƿ���IO�ڶ���

/**��������*********************************************************************/
void Delay(uint xms);
void Init_IO_AND_LED(void);
void SysWorkMode(uchar mode);
void SysPowerMode(uchar mode);

/**
  * @brief     �жϴ�����-ϵͳ����
  * @param     None
  * @retval    None
  */
#pragma vector = P0INT_VECTOR
 __interrupt void P0_ISR(void)
 {
  if(P0IFG>0)
  {
     P0IFG = 0;
  }
  
  P0IF = 0;
  //SysWorkMode(PM3);
  SysPowerMode(4);
 }


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();
  LED1 = 0 ;       //��LED1��ϵͳ����ָʾ
  Delay(500);       //��ʱ	
  while(1)
  {
    LED2 = !LED2;
    LED1 = 0;
    count++;
    if(count >= 6)
    {
      count = 0;     
      LED1 = 1;
      //SysWorkMode(PM2);
      SysPowerMode(3);
      //3����˸�����˯��״̬PM3
    }
   
    Delay(500);
    
  };
}

/**
  * @brief     ��ʱ����,��Լ1����
  * @param     xms ��ʱ��С
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/**
  * @brief     ϵͳ����ģʽѡ����
  * @param     None
  * @retval    None
  * @attention
  *            para1  0 	1	2	3									
  *            mode 	PM0	PM1	PM2	PM3													
  */
void SysPowerMode(uchar mode)
{
  uchar i,j;
  i = mode;
  if(mode<4)
  {
    SLEEPCMD &= 0xFC;     
    SLEEPCMD |= i;       //����ϵͳ˯��ģʽ
    for(j=0;j<4;j++);
    {
      PCON = 0x01;         //����˯��ģʽ
    }
  }
  else
  {
    PCON = 0x00;             //ϵͳ����
  }
}

/**
  * @brief     ����ģʽ����
  * @param     mode ����ģʽ
  * @retval    None
  */
void SysWorkMode(uchar mode)
{
  switch (mode) 
  {
  case PM0:
    SLEEPCMD |= PM0; // ����ϵͳ����ģʽ
    break;
  case PM1:
    SLEEPCMD |= PM1; // ����ϵͳ����ģʽ
    break;
  case PM2:
    SLEEPCMD |= PM2; // ����ϵͳ����ģʽ
    break;
  case PM3:
    SLEEPCMD |= PM3; // ����ϵͳ����ģʽ
    break;
  }
  //�� 1 ��ǿ��ϵͳ���� SLEEPCMD ��ָ���ĵ�Դģʽ�������ж��źŶ������������λ
  PCON = 0x01;

}

/**
  * @brief     LED����IO�ڳ�ʼ������
  * @param     None
  * @retval    None
  */
void Init_IO_AND_LED(void)
{
  P1DIR |= 0X03;
  LED1 = 1;
  LED2 = 1;
 
  P0INP &= ~0X10;   //����P0�����·ģʽΪ����/����
  P0IEN |= 0X10;     //P01����Ϊ�жϷ�ʽ
  PICTL |= 0X10;     //�½��ش���
    
  EA = 1;
  IEN1 |= 0X20;      // ��P0�����ж�
  P0IFG |= 0x00;     //���жϱ�־
}

