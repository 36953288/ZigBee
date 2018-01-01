/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       OLED��ʾ
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "LCD.h"

/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main()
{       
    
  int i;  
  LCD_Init();                      //oled ��ʼ��    
  LCD_CLS();                       //��ȫ�� 
      
  while(1)
  {
      
    for(i=0; i<4; i++) 
    {
      DelayMS(500);
      LCD_P16x16Ch(16*(i+2), 0, i);
      if(i==100)
      {
        i=0;
      }
    }
      
    for(i=0; i<7; i++)
    {
      LCD_P16x16Ch(8+16*i, 2, 4+i);
      
    }

    DelayMS(500);
    LCD_P8x16Str(16,5, "2017-12-12");
    LCD_Clear();
  }
}   


