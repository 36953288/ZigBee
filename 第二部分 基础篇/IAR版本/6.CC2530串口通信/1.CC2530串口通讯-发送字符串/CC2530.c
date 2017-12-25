/***************************************************
�����ߣ������Ƽ�
����ƽ̨��CC2530
���ڣ�2016.1
�޸ģ�2016.2
���ݣ�����ͨ��
***************************************************/
#include <ioCC2530.h>
#include <string.h>

#define  uint  unsigned int
#define  uchar unsigned char

//������ƵƵĶ˿�
#define LED1  P1_0

//��������
void Delay(uint);
void initUARTSEND(void);
void IO_Init(void);
void UartTX_Send_String(char *Data,int len);
char Txdata[25];

/****************************************************
    ��ʱ����											
****************************************************/
void Delay(uint xms)
{
    uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--); 
}

/****************************************************
    �˿ڳ�ʼ������											
****************************************************/
void IO_Init()
{
    	P1DIR = 0x01; //P1����LED	
        LED1 = 1;     //��LED
}

/****************************************************
   ���ڳ�ʼ������				
****************************************************/
void initUARTSEND(void)
{
    //ʱ������
    CLKCONCMD &= ~0x40;        //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);   //�ȴ������ȶ�
    CLKCONCMD &= ~0x47;        //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
    //�˿�����
    PERCFG = 0x00;	       //λ��1 P0��
    P0SEL = 0x0c;				//P0_2,P0_3��������
    P2DIR &= ~0XC0;                             //P0������ΪUART0
   //��������
    U0CSR |= 0x80;				//UART��ʽ
    U0GCR |= 11;				 //U0GCR.BAUD_E
    U0BAUD |= 216;				//��������Ϊ115200 UxBAUD.BAUD_M
    UTX0IF = 0;                                 //UART0 TX�жϱ�־��ʼ��λ0
}

/****************************************************
���ڷ����ַ�������			
****************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

/****************************************************
������						
*****************************************************/
void main(void)
{	
	//uchar i;  	
	initUARTSEND();
        IO_Init();
     
	//UartTX_Send_String(Txdata,25);	       
        //for(i=0;i<30;i++)
        // Txdata[i]=' ';
        strcpy(Txdata,"LONGCHUANGKEJI!\r\n");      //��UART0 TX test����Txdata;
	while(1)
	{
            UartTX_Send_String(Txdata,strlen(Txdata)); //���ڷ�������
            Delay(1000);                                //��ʱ
            LED1=!LED1;                                 //D1����������־����״̬
            Delay(1000);
	}
}
