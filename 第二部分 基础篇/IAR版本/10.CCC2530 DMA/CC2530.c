/***************************************************
�����ߣ������Ƽ�

����ƽ̨��CC2530

���ڣ�2016.1

���ݣ�DMA
***************************************************/

#include <ioCC2530.h>
#include "Uart.h"
#include "hal.h"

#define KEY1 P0_1 
#define KEY2 P2_0

#define LED1 P1_0
#define LED2 P1_1
#define LED3 P1_4

//��������
void Configure_DMADataStruct(void);
void DMA_Configure(void);
void Start_DMA(void);
void Data_Check(void);

//��������
DMA_DESC DMAConfigure;
char sourceString[] = "This is a test string used to demonstrate DMA transfer.";
char destString[ sizeof(sourceString) ];
uchar Flag=0;


/**************************************************
 �� �� ��  : main
 ��������  : DMA����(�ֶ�����KEY1����DMA���ԣ������Խ����������)
 �������  : NONE  
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void main(void)
{    
    SetSysClock();
    
    InitUART();
    
    memset(destString, 0, sizeof(destString) );//Clearing the destination
   
    Configure_DMADataStruct();/*1��DMAʹ�ò���һ��DMA �������ݽṹ*/
      
    DMA_Configure();/*2��DMAʹ�ò������DMA �Ĵ�������*/

    Start_DMA();
   
    Data_Check();
   
    while(1);
}


/**************************************************
 �� �� ��  : Configure_DMADataStruct
 ��������  : DMA �������ݽṹ
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void Configure_DMADataStruct(void)
{

    SET_WORD(DMAConfigure.SRCADDRH, DMAConfigure.SRCADDRL,   &sourceString); // 1��DMAͨ��Դ��ַ
    SET_WORD(DMAConfigure.DESTADDRH, DMAConfigure.DESTADDRL, &destString);   // 2��DMAͨ��Ŀ�ĵ�ַ
    SET_WORD(DMAConfigure.LENH, DMAConfigure.LENL, sizeof(sourceString));    // 3��DMA��ͨ�����ͳ���
    DMAConfigure.VLEN      = VLEN_USE_LEN;  // 4���ɱ䳤�ȴ���ģʽ
    DMAConfigure.WORDSIZE  = WORDSIZE_BYTE; // 5��ѡ��ÿ��DMA�����ǲ���8λ(0) ����16λ(1)
    DMAConfigure.TMODE     = TMODE_BLOCK;   // 6��DMAͨ������ģʽ
    DMAConfigure.TRIG      = DMATRIG_NONE;  // 7��ѡ��Ҫʹ�õ�DMA����(������ѡ�����û�ǿ�ƿ�ʼ����)
    DMAConfigure.SRCINC    = SRCINC_1;      // 8��Դ��ַ����ģʽ(ÿ�δ���֮��)
    DMAConfigure.DESTINC   = DESTINC_1;     // 9��Ŀ�ĵ�ַ����ģʽ(ÿ�δ���֮��)
    DMAConfigure.IRQMASK   = FALSE;         // 10����ͨ�����ж�����    
    DMAConfigure.M8        = M8_USE_8_BITS; // 11������VLEN�ĵ�8λģʽ��Ϊ���͵�λ���ȣ���Ӧ����WORDSIZE=0��VLEN��000��111ʱ
    DMAConfigure.PRIORITY  = PRI_HIGH;      // 12��DMAͨ�������ȼ���    
}    


/**************************************************
 �� �� ��  : DMA_Configure
 ��������  : DMA �Ĵ�������(��ʵ����DMAͨ��0)
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void DMA_Configure(void)
{
    DMA_SET_ADDR_DESC0(&DMAConfigure);//1��DMA ͨ�����빤��״̬(DMA0CFGH��DMA0CFGL)
    DMA_ABORT_CHANNEL(0);//2��ֹͣ����ͨ������ѡ��ͨ��0(DMAARM)
    DMA_ARM_CHANNEL(0);//3��ѡ��ͨ��0(DMAARM)
}


/**************************************************
 �� �� ��  : Start_DMA
 ��������  : ����DMA���ȴ����ݴ������
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void Start_DMA(void)
{
    UartSend_String("Start DMA.\n",sizeof("Start DMA.\n"));  //��������
    Delayms(100); 
    
    while(KEY1) //��⵽����KEY1���趨DMA��RAM��ת������
    
    Delayms(100);

    DMAIRQ = 0x00;//���жϱ�־
    DMA_START_CHANNEL(0);//DMAREQ0��λ---����DMA
    while(!(DMAIRQ & DMA_CHANNEL_0));//�ȴ�������ϣ��жϱ�־��λ
}


/**************************************************
 �� �� ��  : Data_Check
 ��������  : �Ƚ�Դ������Ŀ�������Ƿ�һ��
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : NONE
***************************************************/
void Data_Check(void)
{
    uchar i;
    uchar errors = 0;
    
    for(i=0;i<sizeof(sourceString);i++)
    {
        if(sourceString[i] != destString[i])
        errors++; //��¼��������ݸ���
    }

    if(errors == 0)
    {
        UartSend_String("The test of DMA is successful.\n",sizeof("The test of DMA is successful.\n"));  //��������
        LED3=1;//����ָʾ

    }
    else
    {
        UartSend_String("The test of DMA is failed.\n",sizeof("The test of DMA is failed.\n"));  //��������
    }    
}

/*********************************************END OF FILE**********************/
