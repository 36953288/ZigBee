/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       AD�ɼ��ڲ��¶ȴ�����ʾ����ͨ��ʽ��
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iocc2530.h>
#include <stdio.h>
#include <string.h>

/**�궨��***********************************************************************/
#define uchar unsigned char
#define uint unsigned int
#define int16 short 
#define uint16 unsigned short 
      
/**��������*********************************************************************/
void initclock(void);
void inituart0(void);
void uarttx_send_string(char *data,int len);
void Delay(uint xms);
uint gettemperature(void);

/**ȫ�ֱ���*********************************************************************/
int16 avgtemp;


/**
  * @brief     ������
  * @param     None
  * @retval    None
  */
void main(void)
{
  char i;
  char tempvalue[30];
  
  initclock();//��ʼ��ʱ��  
  inituart0();//��ʼ������
  IEN0=IEN1=IEN2=0X00;//�ر������ж�
  ATEST=0X01;//�����¶ȴ�����
  TR0=0X01;//���¶ȴ�������ADC��������
  
  while(1)
  {
    avgtemp=0;
    for(i=0;i<64;i++)
    {
      avgtemp +=gettemperature();//ȡ���¶���������ԭƽ��ֵ
      if(i>0) avgtemp>>=1;//����2��ȡ��ƽ��ֵ
    }
    
    memset(tempvalue, 0, 30);
    sprintf(tempvalue, "AD Data= %dC", (int)avgtemp);
    uarttx_send_string(tempvalue,strlen(tempvalue));
    //uarttx_send_string("\n",1);
    Delay(3000);
  }
}

/**
  * @brief     ��ʼ��ʱ��
  * @param     None
  * @retval    None
  */
void initclock(void)
{
  CLKCONCMD &=0XBF;//ϵͳʱ��Դѡ��32MHZ XOSC
  CLKCONCMD &=0XF8;//ϵͳʱ��Ƶ��Ϊ32MHZ
  
  CLKCONCMD |=0X28;
  CLKCONCMD &=0XEF;//��ʱʱ��Ƶ��Ϊ1MHZ
  while(CLKCONSTA & 0X40);//�ȴ�ʱ���ȶ�
}

/**
  * @brief     ��ʼ������0����
  * @param     None
  * @retval    None
  */
void inituart0(void)
{
  PERCFG = 0x00;		         //λ��1 P0��
  P0SEL = 0x3c;				 //P0��������
	
  P2DIR &= ~0XC0;                       //P0������ΪUART0    
  U0CSR |= 0x80;   	                //��������ΪUART��ʽ
  U0GCR |= 11;				
  U0BAUD |= 216;		       //��������Ϊ115200

  UTX0IF = 1;                          //UART0 TX�жϱ�־��ʼ��λ1  
  U0CSR |= 0X40;		       //�������
  IEN0 |= 0x84;			       //�����жϣ������ж�
}


/**
  * @brief     ���ڷ����ַ�������
  * @param     date  ���ݡ�
               len   ����
  * @retval    None
  */
void uarttx_send_string(char *data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*data++;
    while(UTX0IF==0);
    UTX0IF=0;
  }
  U0DBUF=0X0A;//����
  while(UTX0IF==0);
  UTX0IF=0;  
}

/**
  * @brief     ��ʱ����
  * @param     xms   ��ʱ��С
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/**
  * @brief     ��ȡ�¶ȴ�����ADֵ����
  * @param     None
  * @retval    None
  */
uint gettemperature(void)
{
  uint i;
  uint16 adcvalue;
  uint16 value;
  
  adcvalue=0;
  for(i=0;i<4;i++)
  {
    ADCCON3 |=0X0E;//��ͨ��ADת��ԴΪ�¶ȴ�����
    ADCCON3 &=0X3F;//��ͨ��ADת���ο���ѹΪ1.25�ڲ���ѹ
    ADCCON3 |=0X30;//��ͨ��ADת���ֱ���Ϊ512DEC��12��Ч
    ADCCON1 |=0X30;//ADC������ʽѡ��ΪADCCON1.ST=1�¼�
    ADCCON1 |=0X40;//ADC����ת��
        
    while(!ADCCON1&0X80);//�ȴ�ADת�����
    value =  ADCL >> 2; //ADCL�Ĵ�����2λ��Ч
    value |=(((uint16)ADCH)<<6);//����ADCH��ADCL������ֵ��value
    adcvalue +=value;//adcvalue����ֵΪ4��ADֵ֮��
  }
  value=adcvalue>>2;//�ۼӳ���4���õ�ƽ��ֵ
  //return (((value) >> 4) - 315)/10;     //����ADֵ�������ʵ�ʵ��¶�
  return (uint)(((value>>2)-1367.5)/4.5-5);
  
}   