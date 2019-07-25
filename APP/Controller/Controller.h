#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "global.h"
#include "uart.h"
#include "basic.h"


#define RS485_COMM_TYPE   0x00
#define RS232_COMM_TYPE   0x01


#define CS_NUMBER_H        0x00
#define CS_NUMBER_L        System.uc[0]//0x00
#define CTR_NUMBER_H       0x00
#define CTR_NUMBER_L       BCD2Hex(System.ctr_addr[0])

#define CONTR_OFFLINE_TIMER     93    //93S=1S*93  


extern UINT8 Last_Uc[LEN_REG_UC];
extern UINT16 Last_Event_Type;
extern UINT32 Last_Event_Time;
extern UINT8 CenterCmd_Erease_Flash_Flag;
extern UINT8 CenterCmd_Rst_Flag;



enum COM_TYPE
{
	TS=0,				//����Э��
	GST200_CRT_ZJ,		//����200 CRT����GST200   GST-NNET-02�ӿڿ�
	GST500_CRT_ZJ,		//����500 CRT����GST500  GST5000    GST-NNET-02�ӿڿ�
	EI2000_CRT_ZJ,		//��������������EI2000G��EI6000T
	QN5010_CRT_ZJ,		//����5010����������JBF5010
	GST200_CRT_JT,		//����200 CRT����GST200   GST-NNET-02�ӿڿ�
	GST500_CRT_JT,		//����500 CRT����GST500  GST5000    GST-NNET-02�ӿڿ�
	LD128EN_CRT_485_ZJ,	//����LD128EN(M)����	LD128EN(M)
	GST200_SF_ZJ,		//����200MODBUSЭ��GST200  GST-INET-03A�ӿڿ�
	GST500_SF_ZJ,		//����500MODBUSЭ��GST500  GST5000  GST-INET-03A�ӿڿ�
	LD128EN_CRT_JT,		//����LD128EN(M)����	LD128EN(M)

	TC5120_PRT_JT,		//Ӫ����ɴ�ӡ��	TC5120
	GT603_SF_ZJ,		//��̩�����������ӿ�  GT603
	SJ9102BA_CRT_ZJ,	//�ɽ�CRT����	9102BA
	SJ9102BA_CRT_JT,	//�ɽ�CRT����	9102BA
	NT8003_CS_ZJ,		//���ش����豸����		FT8003
	TANDA3004_PRT,		//̩�Ͱ���ӡ��		TX3004
	FORSAFE_SF,			//���������ӿ�
	FHSJ9108_PRT,		//����������ӡ��	9108
	SIMPLEX_CRT_ZJ,		//������˹CRT
	LD128EN_CRT_232_ZJ,	//����CRT����

	QN_193K_SF_ZJ,		//���������ӿ� 193K�ӿڿ�
	QN5010_CRT_JT,		//����5010����������JBF5010
	LD128EN_PRT,		//�����ӡ��	LD128EN(M)
	TX3607_FW19000_485,	//��������TX3607�ӿڿ�     FW19000
	TX3607_FW19000_232,	//��������TX3607�ӿڿ�     FW19000
	N3030_OLD,			//ŵ�ٷƶ��Ͽ�3030������
	PTW3300_JT,			//�������� 3300������  ��ŵ�ٷƶ��¿�3030������
	FT8003,
	Parallel_Debug,			//�����������ģʽ
	COM_NULL,
};

enum UART_STA
{
	UART_CLOSE=0,
	UART_REC_INIT,
	UART_REC_NO_INIT,
	UART_SEND_INIT,
	UART_SEND_NO_INIT,
	UART_CLOSE_TXD,
};
enum CONTOR_LED
{
    LED_OFF = 0X00,
	LED_BLINK,
	LED_LIGHT,
};
enum RXD_INFO_ANALYSIS_STATE
{
	FRAME_HEAD=0,
	FRAME_LEN,
	FRAME_LEN_EXP,
	FRAME_DATA,
	FRAME_CS,
};

#define FRAME_LEN_LOC
enum SEND_STA
{
	SEND_IDLE = 0,
	WAITING,
	SENDING,
	//PREPARE,
};

#define CONTR_BUF_LEN   (1024*1)

typedef struct
{
    UINT16 Clev;       //���ջ��洦��λ��
	UINT16 Head;       //���ջ������λ��
	UINT16 FrameEndLoc;//�ҵ�֡ͷ�ͳ��Ⱥ󣬼������֡����λ��;
	                   //ȷ���յ�һ֡����ʱʹ��           
    UINT16 FrameCount;
	UINT16 ByteInterval;//�ֽڼ��
	UINT16 FrameLen;   //�ҵ�֡ͷ�ͳ��Ⱥ�ֵ;����У��ʱʹ��
	UINT8 Buf[CONTR_BUF_LEN];	
}RECEIVE;
typedef struct 
{
	UINT16 Clev;
	UINT16 Tail;
	UINT8 Buf[256];
	UINT8 Sta;	
	UINT8 RepNum;				//�ظ�����
	UINT8 RepFlag;              //�ظ���ʶ
	UINT16 RepCounter;          //�ظ���ʱ     		
}SEND;

typedef struct 
{
	RECEIVE R;				//�������ݽ��ջ���
	SEND T;					//�������ݷ��ͻ���
	UINT8 DAT_Return[512];  //������ȷ��һ֡���ݷ���û��棬����ȡ���Լ����������ȡ
	UINT8 AnalyseSta;
	UINT8 PollEnFlag;
	UINT16 PollTimer;
	UINT8  Poll_Ctr;
}CONTR_IF;

extern CONTR_IF RS232;
extern CONTR_IF RS485;

typedef struct
{
    UINT16 Count;  //���ϼ�ʱ
	UINT16 Time;   //����ʱ��:��ͬ����������ʱ�䰴��Ӧ������
	UINT8 Flag;    //���ϱ�־
}COM_FAULT;
typedef struct
{
	COM_FAULT ComFault;
	UINT8 Type;
	UINT8 Addr;
	UINT8 Led;
	BIT_CHAR Task;
	UINT8 delay;
}CONTR;
extern CONTR Contr;
typedef struct
{	
	COM_FAULT ComFault;
	UINT8 send_flag;
	UINT16 Event_Pc;
}COMPETE_TO_CONTR;
extern COMPETE_TO_CONTR Compete_Event;

typedef struct
{
	UINT8 Led;
	UINT8 Gprs;
}DEBUG;
extern DEBUG Debug;
typedef struct 
{
    UINT8 SrcEventType;
	UINT8 RecordType;
	UINT16 DestEventType;
}CHANGE_EVENT_TYPE;

typedef struct 
{
	UINT8 const * const  Event_Annotaiton; 
	UINT8 RecordType;
	UINT16 EventType;
}GET_EVENT_TYPE_ASCII;


typedef struct 
{
	UINT8 const * const src_type;
	UINT8 dest_type;
}GET_Device_Type_ASCII;


#define B_Upload_Self_Info        Contr.Task.b.b0
#define B_Reset_Ctr               Contr.Task.b.b1
#define B_Silence_Ctr    		  Contr.Task.b.b2
#define B_Poll_Ctr                Contr.Task.b.b3

void Monitor_Controller_Slave_Uart(CONTR_IF *buf);
UINT16 HexToBCD(UINT8 hex);
void Hex_To_BasicUC(UINT8 *uc,UINT8 *hex,UINT8 len);

void Poll_Controller_Init(CONTR_IF *buf);
void Save_Controller_Self_Info(UINT8 record_type,UINT16 detailed_type);
void Controller_Uart_Init(void);
void Controller_Data_Init(void);
void Controller485_Uart_Init(void);
void Controller485_Uart_Sta_Switch(UINT8 type) ;
void Controller232_Uart_Sta_Switch(UINT8 type);
void Monitor_Controller_Offline(void);
void  Monitor_Trans_Equip_Offline(void);
void Monitor_Controller_Fault_Eliminate(void);
void Monitor_Trans_Equip_Fault_Eliminate(void);
void Monitor_Controller_Uart(CONTR_IF *buf);
void Monitor_Controller_Uart_Timer_Run(CONTR_IF *buf);
void Controller_Uart_Rec_Data(CONTR_IF *buf, USART_TypeDef *uart);
void Controller_Uart_Send_Data(CONTR_IF *buf, USART_TypeDef *uart);
void RS485_Task(void);
void RS232_Task(void);
void Controller_Com(void);

#endif
