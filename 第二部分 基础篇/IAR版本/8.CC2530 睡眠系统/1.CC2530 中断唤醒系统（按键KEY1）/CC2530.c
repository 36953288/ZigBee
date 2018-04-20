/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       LED1��˸5�κ����˯��״̬��ͨ�����°���K1
�����ⲿ�жϽ��л���
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
typedef unsigned char uchar;
typedef unsigned int  uint;

//����IO��
#define LED1 P1_0            //P1.0�ڿ���LED1
#define KEY1 P0_1            //P0.1�ڿ���KEY1

#define  PM0  0
#define  PM1  1
#define  PM2  2
#define  PM3  3

/**��������*********************************************************************/
void InitKey(void);
void SysWorkMode(uchar mode);
void Delayms(uint xms);
void InitLed(void);

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
    uchar count=0;  

    InitKey();  //�����жϳ�ʼ���������жϻ���
    InitLed();
    while(1)
    {
        LED1=~LED1;  //����ָʾ����
        if(++count>=10)
        {
            count=0;
            SysWorkMode(PM3); //5����˸�����˯��״̬PM3,�ȴ�����S1�жϻ���
        }
        Delayms(500);
    }
}

/**
  * @brief     �жϴ�����-ϵͳ����
  * @param     None
  * @retval    None
  */
#pragma vector = P0INT_VECTOR         //��ʽ��#pragma vector = �ж�����
    __interrupt void P0_ISR(void)     //�������жϴ������(��������������ȡ)
{
    P0IFG = 0;       //���жϱ�־
    P0IF = 0;
    PCON = 0x00;  //��0����ϵͳ������������ģʽ
}

/**
  * @brief     LED����IO�ڳ�ʼ������
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0����Ϊ�����
    LED1 = 1;                //LED���ϵ�Ĭ��ΪϨ�� 
}

/**
  * @brief     ��������IO�ڳ�ʼ������
  * @param     None
  * @retval    None
  */
void InitKey(void)
{
    P0IEN |= 0x02;  //����P0_1Ϊ�жϷ�ʽ
    PICTL |= 0x01;  //�½��ش��� 
    IEN1 |= 0x20;   //����P0���ж�
    P0IFG = 0x00;   //���жϱ�־λ
    EA = 1;         //�����ж�
}

/**
  * @brief     ϵͳ����ģʽѡ����
  * @param     None
  * @retval    None
  * @attention
  *            para1  0 	1	2	3									
  *            mode 	PM0	PM1	PM2	PM3													
  */
void SysWorkMode(uchar mode) 
{ 
    switch(mode)
    {  
    case PM0:
        SLEEPCMD |= PM0;     // ����ϵͳ����ģʽ 
        break;      
    case PM1:
        SLEEPCMD |= PM1;     // ����ϵͳ����ģʽ 
        break;
    case PM2:
        SLEEPCMD |= PM2;     // ����ϵͳ����ģʽ 
        break;
    case PM3:
        SLEEPCMD |= PM3;     // ����ϵͳ����ģʽ 
        break;        
    }
    //��1��ǿ��ϵͳ����SLEEPCMD��ָ���ĵ�Դģʽ�������ж��źŶ������������λ
    PCON = 0x01; 
}

/**
  * @brief     ��ʱ����,��Լ1����
  * @param     msec ��ʱ��С
  * @retval    None
  */
void Delayms(uint xms)  
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=587;j>0;j--);
}
