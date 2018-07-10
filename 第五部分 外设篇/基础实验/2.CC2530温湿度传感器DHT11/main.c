/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2018-01
  * @brief       ��ʪ�ȴ�����Ӧ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include <string.h>
#include "UART.H" 
#include "DHT11.H" 
#include "LCD.h"

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{  
  uchar temp[3]; 
  uchar humidity[3];   
  uchar strTemp[13]="Temperature:";
  uchar strHumidity[10]="Humidity:";
    
   
  Delay_ms(1000);          //���豸�ȶ�
  InitUart();              //���ڳ�ʼ��
  LCD_Init();                 //oled ��ʼ��  
  LCD_CLS();                  //��ȫ��   
  LCD_welcome();
    
  while(1)  
  {             
    memset(temp, 0, 3);    
    memset(humidity, 0, 3);
            
    DHT11();             //��ȡ��ʪ��

        
    /*
    ����ʪ�ȵ�ת�����ַ���      
    ��ʮ������ת���� ASCII �룬0x30 ���� ASCII ����� 0 ��      
    Ȼ��ͨ�����ڽ�������ʪ��ֵ���͸�������ʾ������    
    */
        
    temp[0]=wendu_shi+0x30;    
    temp[1]=wendu_ge+0x30;
    humidity[0]=shidu_shi+0x30;
    humidity[1]=shidu_ge+0x30;
            
    //��õ���ʪ��ͨ�����������������ʾ
    UartSendString(strTemp, 12);    
    UartSendString(temp, 2);
    UartSendString("   ", 3);
    UartSendString(strHumidity, 9);
    UartSendString(humidity, 2);
    UartSendString("\n", 1);
            
    Delay_ms(500);    
    LCD_P8x16Str(16, 2, "Humidity:");    
    LCD_P8x16Str(86, 2, (unsigned char*)humidity);
           
    Delay_ms(500);       
    LCD_P8x16Str(16, 4, "Temp:");
    LCD_P8x16Str(64, 4, (unsigned char*)temp);
               
    Delay_ms(1000);                   //��ʱ����ʹ�ö�ʱ����ʽ  
  }
}
