/***************************************************
�����ߣ� �����Ƽ�

����ƽ̨��CC2530

���ڣ�2016.1

���ݣ�AD�ɼ��ڲ��¶ȴ�����ʾ
***************************************************/
#include <ioCC2530.h>
#include "initUART_Timer.h"
#include "stdio.h"
#include "string.h"
#include "LCD.h"


INT16 AvgTemp; 

/***************************************************
�¶ȴ�������ʼ������						
****************************************************/
void initTempSensor(void)
{
   DISABLE_ALL_INTERRUPTS();            //�ر������ж�
   InitClock();                         //����ϵͳ��ʱ��Ϊ32M
   *((BYTE __xdata*) 0x624B) = 0x01;  //����TR0=0X01;  //�����¶ȴ�����,TR0�ĵ�ַΪ0x624B
   *((BYTE __xdata*) 0x61BD) = 0x01;  //����ATEST = 0x01; //���¶ȴ�������ADC��������,ATEST�ĵ�ַΪ0x61BD
}
/***************************************************
��ȡ�¶ȴ�����ADֵ����						
****************************************************/
INT8 getTemperature(void)
//float getTemperature(void)
{
/*
  //������
 uint value;
  
  ADCCON3 = (0x3E); //ѡ�� 1.25V Ϊ�ο���ѹ�� 12 λ�ֱ��ʣ���Ƭ���¶ȴ���������
  ADCCON1 |= 0x30; //ѡ�� ADC ������ģʽΪ�ֶ�
  ADCCON1 |= 0x40; //���� AD ת��
  
  while(!(ADCCON1 & 0x80)); //�ȴ� AD ת�����
  value = ADCL >> 4; //ADCL �Ĵ����� 4 λ��Ч
  value |= (((UINT16)ADCH) << 4);
  
  return (INT8)((value-1367.5)/4.5-4); 
  //���� AD ֵ�������ʵ�ʵ��¶�,оƬ��
  //�ֲ��д��¶�ϵ��Ӧ���� 4.5 /��
  //�����¶�У���������ȥ 4�棨��ͬоƬ���ݾ������У����
*/  
  //������
  UINT8   i;
  UINT16  AdcValue;
  UINT16  value;

  AdcValue = 0;
  for( i = 0; i < 4; i++ )
  {
    ADC_SINGLE_CONVERSION(ADC_REF_1_25_V | ADC_14_BIT | ADC_TEMP_SENS);    // ʹ��1.25V�ڲ���ѹ��12λ�ֱ��ʣ�ADԴΪ���¶ȴ�����
    ADC_SAMPLE_SINGLE();  //������ͨ��ADC
   
    while(!ADC_SAMPLE_READY());      //�ȴ�ADת�����
    value =  ADCL >> 2;              //ADCL�Ĵ�����2λ��Ч
    value |= (((UINT16)ADCH) << 6);    
    AdcValue += value;               //AdcValue����ֵΪ4��ADֵ֮��
  }
    value = AdcValue >> 4;           //�ۼӳ���4���õ�ƽ��ֵ
  
    return ADC14_TO_CELSIUS(value);   //����ADֵ�������ʵ�ʵ��¶�


}
/***************************************************
������	
****************************************************/
void main(void)
{	
	char i;
        char TempValue[30]={0}; 

	InitUART0();        //��ʼ������
	initTempSensor();  //��ʼ��ADC

        LCD_Init();//��ʼ��LCD        
        LCD_CLS();
        LCD_welcome();
        
        while(1)
        {
          AvgTemp = 0;
          for(i = 0 ; i < 64 ; i++)
          {
            AvgTemp += getTemperature();              
            AvgTemp >>= 1;      //ÿ���ۼӺ��2.
          }
          
          memset(TempValue, 0, 30);
          sprintf(TempValue, "ADTestRead = %dC", (INT8)AvgTemp);
          UartTX_Send_String(TempValue,strlen(TempValue));
          UartTX_Send_String("\n",1);
          LCD_P8x16Str(0, 4, (unsigned char*)TempValue);

          Delay(2000); 
        }
}


