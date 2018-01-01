/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       ���Ź�
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**�궨��***********************************************************************/
//������������
#define uint unsigned int 
//����IO��
#define LED1  P1_0 
#define LED2  P1_1

/**��������*********************************************************************/
void InitLEDIO(void);
void Init_Watchdog(void);
void SET_MAIN_CLOCK(int source) ;
void FeetDog(void);
void Delay(uint xms);

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{	
  SET_MAIN_CLOCK(0) ;
  InitLEDIO();
  Init_Watchdog();
        
  Delay(1000);
        	
  LED1= 0;	       
  LED2= 0;       

  while(1)
  {
    FeetDog();	
  }	
  //ι��ָ������ϵͳ����λ��LED1��LED2������˸��
}

/**
  * @brief     LED��ʼ��
  * @param     None
  * @retval    None
  */
void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10��P11����Ϊ���
    LED1 = 1;
    LED2 = 1;
    //LED�Ƴ�ʼ��Ϊ��   
}
 
/**
  * @brief     ��ʼ�����Ź�
  * @param     None
  * @retval    None
  */
void Init_Watchdog(void)
{
  WDCTL = 0x00;
	
  //ʱ����һ�룬���Ź�ģʽ
  WDCTL |= 0x08;
}

/**
  * @brief     ����ʱ��ģʽ
  * @param     None
  * @retval    None
  */
void  SET_MAIN_CLOCK(int source) 
{                                  
      
  if(source) 
  {                             
    CLKCONCMD |= 0x40;          /*RC*/               
    while(!(CLKCONSTA &0X40));  /*����*/           
  }                                       
      
  else 
  {  
    CLKCONCMD &= ~0x47;        /*����*/             
       
    while((CLKCONSTA &0X40));  /*����*/  
  }                                       
}

/**
  * @brief     ι��
  * @param     None
  * @retval    None
  */
void FeetDog(void)
{	
  WDCTL = 0xa0;
  WDCTL = 0x50;
}

/**
  * @brief     ��ʱ����
  * @param     xms ��ʱ��С
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}



