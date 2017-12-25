#include <iocc2530.h>
#include "adc.h"
#include "uart.h"
#include "led.h"
#include <stdio.h>
#include <string.h>

/****************************************************************************
* ��    ��: DelayMS()
* ��    ��: �Ժ���Ϊ��λ��ʱ 16MʱԼΪ535,32MʱҪ����,ϵͳʱ�Ӳ��޸�Ĭ��Ϊ16M
* ��ڲ���: msec ��ʱ������ֵԽ����ʱԽ��
* ���ڲ���: ��
****************************************************************************/
void DelayMS(uint msec)
{  
  uint i,j;
  
  for (i=0; i<msec; i++)
    for (j=0; j<1070; j++);
}

/****************************************************************************
* ��    ��: ��ʼ��ʱ�Ӳ���
****************************************************************************/
void ClockInit(void)
{
    CLKCONCMD = 0x28;           //ʱ������ʱ���趨Ϊ1M Hz,  ϵͳʱ���趨Ϊ32 MHz 
    while(CLKCONSTA & 0x40);    //�Ⱦ����ȶ�
}

/****************************************************************************
* ��    ��: InitUart()
* ��    ��: ���ڳ�ʼ������
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitUart(void)
{ 
  PERCFG = 0x00;           //������ƼĴ��� USART 0��IOλ��:0ΪP0��λ��1 
  P0SEL = 0x0c;            //P0_2,P0_3�������ڣ����蹦�ܣ�
  P2DIR &= ~0XC0;          //P0������ΪUART0
  
  U0CSR |= 0x80;           //����ΪUART��ʽ
  U0GCR |= 11;				       
  U0BAUD |= 216;           //��������Ϊ115200
  UTX0IF = 0;              //UART0 TX�жϱ�־��ʼ��λ0
}

/****************************************************************************
* ���ͺ��� note: "length" is the length of one line
****************************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
  U0DBUF = 0x0A;        // ����
  while(UTX0IF == 0);
    UTX0IF = 0;
}

/****************************************************************************
* ��ʽ������ ����ѹֵת��������
****************************************************************************/
void format(float vol, char buf[6])
{
    char ge = 0;           //��λ
    char fen = 0;          //��λ
    char shifen = 0;       //ʮ��λ
    char baifen = 0;       //�ٷ�λ
    uint i = 0;
    vol = vol*1000;        //����1000��
    i = (uint)vol;         //ת��Ϊ����
    ge = (i / 1000) + 0x30;//ת���ַ�
    fen = (i / 100 % 10) + 0x30;
    shifen =(i % 100 / 10) + 0x30;
    baifen = (i % 10) + 0x30;
    buf[0] = ge;
    buf[1] = '.';
    buf[2] = fen;
    buf[3] = shifen;
    buf[4] = baifen;
    buf[5] = 'v';
}

/****************************************************************************
* ���β��������ö˿�ΪP0.6
* This funciton  is order to initialize ADC of CC2530
****************************************************************************/
float getVol(void)
{
  uchar i = 0;
  uint value = 0;
  long uint AdcValue = 0;     //��ֹ���
  float vol = 0.0;
  SET_IO_PORT_DIR(0,6,IO_IN); //����P0..6Ϊ����ģʽ
  ADC_ENABLE_CHANNEL(6);      //ʹ��ͨ��6��ΪADC�Ĳ���ͨ��
  for(i=0; i<4; i++)
  {
    ADC_SINGLE_CONVERSION(ADC_REF_AVDD | ADC_12_BIT | ADC_AIN6);//Ƭ��3.3V�ο���ѹ,12λ��6ͨ��
    ADC_SAMPLE_SINGLE(); 
    while(!(ADCCON1 & 0x80));              //�ȴ�ADת�����
    /*value =  ADCL >> 2;                  //ADCL�Ĵ�����2λ��Ч
    value |= (((uint)ADCH) << 6); */    
    value = ADCL>>4;                      
    value |= (((uint)ADCH) << 4);         
    AdcValue += value;  
  }
  AdcValue = AdcValue >> 2;                 //�ۼӳ���4���õ�ƽ��ֵ
  if(AdcValue > 4096)   // ����ĵ�ѹ0Vʱ����Ϊ�������̣���⵽AdcValue��12λֵΪ0xfff
    AdcValue = 0;
  vol = (float)(AdcValue/(float)2048)*3.3;  //����ɵ�ѹֵ

  return vol;
}


void  main(void)
{
  uchar i=0;
  char vol[6];
  float average;
  float temp;
  P1_0 = 0;
  ClockInit();
  InitUart();
  SET_IO_PORT_DIR(1,0,IO_OUT);         //����LED����ΪADC�������еı�־
  IO_FUNC_PORT_PIN(1, 0, IO_FUNC_GIO); //INIT_LED(); 
  IEN0 = IEN1 = IEN2 =0;
 
  while(1)
  { 
   for(i=0; i<16; i++)//ȡ16�ε�ѹ��ƽ��ֵ
   {
     temp = getVol();
     average += temp;
   }
   average = average / 16;
   format(average, vol);
   UartTX_Send_String(vol,6);  //�򴮿ڷ�������
   //UartTX_Send_String("\r",1); //���ͻ���
   P1_0 = ~P1_0;
   DelayMS(2000); //�����ӷ�һ��
   average = 0.0;
  }
}      
