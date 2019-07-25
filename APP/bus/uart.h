/*
 * bus_dn.h
 *
 *  Created on: 2013-8-7
 *      Author: zjc
 */

#ifndef UART_H_
#define UART_H_

#include "global.h"



#define RS485_IRQHandler   USART3_4_IRQHandler
#define RS485_USART  USART3
//#define USART_IRQHandler   USART3_4_IRQHandler
#define RS232_IRQHandler   USART2_IRQHandler
#define RS232_USART  USART2

#define 	BUS_HIGH		      1
#define 	BUS_LOW			      0


#define   UART_BUFFER_LEN			      1200

#define 	UART_BAUD_921600  			52
#define 	UART_BAUD_460800  			104
#define 	UART_BAUD_230400  			208
#define  	UART_BAUD_125000			384
#define		UART_BAUD_115200		    417
#define		UART_BAUD_57600            	833
#define		UART_BAUD_38400            	1250
#define		UART_BAUD_28800            	1667
#define		UART_BAUD_19200            	2500
#define		UART_BAUD_9600            	5000
#define		UART_BAUD_4800             	10000
#define		UART_BAUD_2400             	20000



//============����ͨ�����ݽṹ����============================

#define UART_SEND_IDLE		0x00				//����
#define UART_CRC_INIT		UART_SEND_IDLE+0x01	//CRC��ʼ��
#define UART_SEND_DATA		UART_CRC_INIT+0x01	//��������
#define UART_SEND_CRCL		UART_SEND_DATA+0x01	//����CRC0
#define UART_SEND_CRCH		UART_SEND_CRCL+0x01	//����CRC1
#define UART_SEND_OVER		UART_SEND_CRCH+0x01	//���ͽ���
#define UART_SEND_ERR			0x07				//���ʹ���

#define UART_REC_IDLE			0x00				//����
#define UART_REC_HEARD		    0x01				//CRC��ʼ��
#define UART_REC_LEN			0x02				//��������
#define UART_REC_DATA			0x03				//��������
#define UART_REC_CRCL			0x04				//����CRC0
#define UART_REC_CRCH			0x05				//����CRC1
#define UART_REC_OVER			0x06				//���ս���
#define UART_REC_ERR			0x07				//���մ���

#define UART_REC_LEN2			0x20				//���ճ�������2


#define UART_STA_IDLE			0x11				  //����
#define UART_STA_COMM_PROCESS	0x33			//����ͨ��
#define UART_STA_COMM_OVER		0x55			//ͨ�����,�ҳɹ�
#define UART_STA_COMM_ERR		0xAA				//ͨ�����,�ҹ���


#define UART_BUSY				0xAA				  //æ��־

#define CHN_ERR_COUNTER_MAX		0x64			//ͨ���������������
#define BPS_ERR_COUNTER_MAX		40				//BPS�������������

#define BPS_MAX_TYPE			8					    //BPS�������
#define BPS_RS232_TYPE_DEFAULT  0				//BPSĬ����������
#define BPS_RS485_TYPE_DEFAULT  4				//BPSĬ����������
#define BPS_RS485_MAX_BPS  		2					//485ͨ���������
#define BPS_RS232_MAX_BPS  		0					//232ͨ���������



typedef struct 
{
	UINT8 Status;
	UINT8 RepeatNum;					//�ظ�����
	split Crc;
	UINT16 TotalLen;					//�ܳ���
	UINT16 ActualLen;					//ʵ���ѷ��ͳ���
	UINT8 ByteInterval;	
	UINT8 DiLoc;					  	//Diλ�� ������Ҫ����di����Ӧ����ĺ������д���	
	//UINT8 Buff[UART_BUFFER_LEN];
	UINT8 Buff[256];
}UART_SEND;


typedef struct
{
	UINT8 Status;
	UINT8 ByteInterval;					//�ֽڼ��
	split Crc;
	UINT16 TotalLen;						//�ܳ���
	UINT16 ActualLen;  					//ʵ���ѽ��յ����ݳ���
	UINT16 WaitTime;
	UINT8 Buff[UART_BUFFER_LEN];
}UART_RECEIVE;

typedef struct 
{
	UART_SEND Send;					//�������ݷ��ͻ���
	UART_RECEIVE Rec;				//�������ݽ��ջ���
	UINT8 FrameTimer;				//BUS֡��ʱ��
	UINT8 FrameIntervalTime;			//���ڷ���֡���
	UINT8 AnsFlag;					//Ӧ���ʶ TRUE Ӧ�� FALSE ��Ӧ��
	UINT8 FrameNum;					//���ڷ���֡��� ����֡��ʹ�ã���ѭ���ۼ�
UINT8 RunSta;					//UART������״̬  ��UART_BUFFER.RunSta����
}UART_BUFFER;
//============ ��������������� ===========================



extern UART_BUFFER Contr_Pro;

//============�����ط�����============================
#define UART_REPEAT_TIMES		2					    //�������ط�����	

//============���ڽ����ֽڼ��============================
#define BUS_RECEIVE_INTERVAL	10				    //�������ݽ��ռ�� ��λmS	

#define BUS_MAX_FRAME_INTERVAL	125 //			//250*8=2000ms,����֡���  ��λmS	

#define SLAVE_REC_BYTE_INTERVAL	10 				//���豸�ֽڼ��


//============  UART_BUFFER.RunSta����״̬����  ============================

#define RUN_STA_IDLE			0x00				    //����״̬ ����
#define RUN_STA_TXD			  RUN_STA_IDLE+1	//����״̬ ��
#define RUN_STA_RXD			  RUN_STA_TXD+1		//����״̬ ��
#define RUN_STA_LOG			  RUN_STA_RXD+1		//����״̬ ��¼
#define RUN_STA_DEAL			RUN_STA_LOG+1		//����״̬ ����
#define RUN_STA_WAIT			RUN_STA_DEAL+1	//����״̬ �ȴ�


//============UART����״̬====================================
#define UART_STA_CLOSE    		0x00          		//���ڹر�״̬
#define UART_STA_RECE_NO_INT    0x33          		//�������жϽ���״̬
#define UART_STA_RECE_INT     	0x55            	//�����жϽ���״̬
#define UART_STA_SEND_NO_INT	0xaa        	  	//�������жϷ���״̬
#define UART_STA_SEND_INT       0xcc         	  	//�����жϷ���״̬

void Make_Crc(split *crc ,uchar data);


void Contr_485Uart_Init(UINT8 BAND);
void RS485_Uart_Init(UINT8 type);
void  Contr_485Uart_Sta_Switch(UINT8 type) ;

void Contr_232Uart_Init(UINT8 BAND);
void RS232_Uart_Init(UINT8 type);
void Contr_232Uart_Sta_Switch(UINT8 type);

void Monitor_Master_Timer_Run(UART_BUFFER *buff);

void Monitor_Master_Uart(UART_BUFFER  *buff);

void Master_Uart_Over_With_Err(UART_BUFFER *buff);
void Master_Uart_Over_With_Succ(UART_BUFFER  *buff);


void Master_Uart_Rec_Data(UART_BUFFER *buff, USART_TypeDef *uart);
void Master_Uart_Send_Data(UART_BUFFER *buff, USART_TypeDef *uart);



#endif 



