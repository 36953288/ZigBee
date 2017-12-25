/***************************************************
�����ߣ������Ƽ�

����ƽ̨��CC2530

���ڣ�2016.1

���ݣ������������
***************************************************/
#include "ioCC2530.h"
#include "Uart.h"
#include "hal.h"

#define KEY1 P0_4  
#define LED1 P1_0

//����˵��
void Init_RandomGenerator(void);

uint Random=0;// Random Sequence
char TX_data[4];

/**************************************************
 �� �� ��  : main
 ��������  : �����������(�ɴ��ڽ����������������ʾ)
 �������  : NONE  
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void main(void)
{    
    uint Data_H,Data_L;
  
    SetSysClock();  //����ϵͳʱ��Ϊ32MHz
    InitUART();  //��ʼ������
   
    Init_RandomGenerator(); //��ʼ�������������
   
    while(1)
    {       
        //����LFSR
        ADCCON1 |= 0x04;
        
        // Read Randomom register          
        Data_H=RNDH;  //����ؼĴ���
        Data_L=RNDL;
  
        Random = (((uint)Data_H << 8) | Data_L);//��ȡ�����
        memset(TX_data, 0, sizeof(TX_data));
        
        TX_data[0]=(char)(Random/4096);   //���ݴ���
        TX_data[1]=(char)((Random%4096)/256);
        TX_data[2]=(char)(((Random%4096)%256)/16);
        TX_data[3]=(char)(((Random%4096)%256)%16);
       
        UartSend_String(TX_data,4);  //���ڷ���������ʾ
        
        Delayms(1000);
    }
}
/**************************************************
 �� �� ��  : Init_RandomGenerator
 ��������  : ��ʼ�������������
 �������  : NONE  
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void Init_RandomGenerator(void)
{  
   /*����Ҫһ�����������ֵ��LFSR Ӧͨ��д��RNDL �������ӣ�
     ���ֵ������RF ����·����IF_ADC��Ҫ
     ʹ�����ֲ������ӵķ��������ߵ���������ϵ�*/
    RFRND = 0x04;

   // �ȴ��ϵ����
    while( RFRND & 0x10 );

   //���ߵ�Ӧ��������TX ״̬���Ա���RX ״̬���ܵ�ͬ�����
    RFST = 0xE2;
    Delayms(1);
    
    /*RCTRL[1:0]---����16 λ�����������
      [00��] �������С�(13X ��չ��)*/
    ADCCON1 &= ~0x0C;   

    RNDH = ADCTEST2;
      
    /*����LFSR ��һ�ַ�ʽ������ADCCON1.RCTRL Ϊ01��
      [01��] LFSR ��ʱ��һ��(û��չ��).*/
    ADCCON1 |= 0x04;
}

/*********************************************END OF FILE**********************/