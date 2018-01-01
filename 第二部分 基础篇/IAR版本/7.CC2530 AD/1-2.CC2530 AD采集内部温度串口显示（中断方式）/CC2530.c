/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       AD�ɼ��ڲ��¶ȴ�����ʾ���жϷ�ʽ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "InitUART_Timer.h" 
#include "stdio.h"
#include "string.h"

/**��������*********************************************************************/
void initTempSensor(void);
float getTemperature(void);

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void) 
{   
  char i; 
  char TempValue[30]={0}; 
  INT16 AvgTemp;    
  //char TempValue[6];   
  //float AvgTemp;         
       
  InitUART0();              //��ʼ������   
  initTempSensor();         //��ʼ�� ADC 
      
  while(1) 
  { 
    AvgTemp = 0;          
    for(i = 0 ; i < 64 ; i++) 
    {    
      AvgTemp += getTemperature();  
      AvgTemp=AvgTemp/2;                  //ÿ���ۼӺ�� 2 
    }
    memset(TempValue, 0, 30);
    sprintf(TempValue, "ADTestRead = %dC", (INT8)AvgTemp);
    UartTX_Send_String(TempValue,strlen(TempValue));
 
 /*   
    //�¶�ת����ascii�뷢��     
    TempValue[0] = (unsigned char)(AvgTemp)/10 + 48;          //ʮλ   
    TempValue[1] = (unsigned char)(AvgTemp)%10 + 48;          //��λ
    TempValue[2] = '.';                                       //С����         
    TempValue[3] = (unsigned char)(AvgTemp*10)%10+48;         //ʮ��λ
    TempValue[4] = (unsigned char)(AvgTemp*100)%10+48;        //�ٷ�λ      
    TempValue[5] = '\0';                                   //�ַ���������   
    UartTX_Send_String( TempValue,6); 
 */  
   Delayms(2000); //ʹ��32M���񣬹�����2000Լ����1S
       
  } 
}


/**
  * @brief     �¶ȴ�������ʼ������    
  * @param     None
  * @retval    None
  */
void initTempSensor(void)
{ 
   DISABLE_ALL_INTERRUPTS();  //�ر������ж� 
   InitClock();               //����ϵͳ��ʱ��Ϊ 32M 
   TR0=0X01;         //set '1' to connectthe temperature sensorto the SOC_ADC.
   ATEST=0X01;       // Enablesthe temperature sensor
}   

/**
  * @brief     ��ȡ�¶ȴ����� AD ֵ����  
  * @param     None
  * @retval    float
  */
float getTemperature(void)
{    
   uint  value; 
   ADCCON3  = (0x3E);    //ѡ��1.25VΪ�ο���ѹ��14λ�ֱ��ʣ���Ƭ���¶ȴ���������
   ADCCON1 |= 0x30;      //ѡ��ADC������ģʽΪ�ֶ�
   ADCCON1 |= 0x40;      //����ADת��  
   while(!(ADCCON1 & 0x80));        //�ȴ� AD ת����� 
   value =  ADCL >> 4;              //ADCL �Ĵ����� 2 λ��Ч 
   value |= (((UINT16)ADCH) << 4);
   return (value-1367.5)/4.5-5;    //���� AD ֵ�������ʵ�ʵ��¶�,оƬ�ֲ��д��¶�ϵ��Ӧ����4.5 /��
                                   //�����¶�У���������ȥ5�棨��ͬоƬ���ݾ������У����
}

