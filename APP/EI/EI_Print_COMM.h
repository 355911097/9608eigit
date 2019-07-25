#ifndef __EI_PRINT_COMM__
#define __EI_PRINT_COMM__


#include "global.h"
#include "controller.h"

//��ӡ�����Ľ�֡
#define FRAME_MIN_LINE_LEN_PRINT        5           //ÿ����С���ճ��� 5�� ��Ϊ������ʶ
#define FRAME_MAX_LINE_LEN_PRINT        30          //ÿ�������ճ��� ʵ��28�� Ԥ��2��
#define FRAME_HEAD0_PRINT               0x1C        //��ӡ�����ױ�ʶ0
#define FRAME_HEAD1_PRINT               0x26        //��ӡ�����ױ�ʶ1
#define FRAME_BLANK_PRINT               0x20        //�ո�
#define FRAME_TAIL0_PRINT               0x0A        //��ӡ����β��ʶ0
#define FRAME_TAIL1_PRINT               0x0D        //��ӡ����β��ʶ1

#define Send_Heart_Poll   500

typedef struct
{
	   UINT8 Time[6];					   // ��¼ʱ��: ������ʱ����   6
	   UINT8 Id[LEN_REG_ID];			   // ID 12
	   UINT8 Uc[LEN_REG_UC];			   // �û���(user code) 5
	   UINT8 Cc[LEN_REG_CC];			   // ��������(character code) 32
	   UINT8 Type;						   // ��¼����,��ӦALARM_TYPE_TAB[]
	   UINT8 EventLen;
	   split EventType; 				   // �¼�����	4
	   UINT8 Event[LEN_RECORD_EVENT];  
}UPLOAD_STRUCT;
enum
{
	EI_PRINT_COMM_RECV_IDLE,		                //���տ���
	EI_PRINT_COMM_RECV_HEAD0,						//����ͷ0 0x1C
	EI_PRINT_COMM_RECV_HEAD1,                       //����ͷ1 0x26
	EI_PRINT_COMM_RECV_DATA,                        //��������
	EI_PRINT_COMM_RECV_OVER,                        //��ӡ�����ݽ������
	EI_PRINT_COMM_RECV_ERR                          //��ӡ���������ݴ���
};
typedef struct
{
	volatile UINT16 status;							//ͨ��״̬
	//volatile UINT16 interval;							//�ֽڼ��
	volatile UINT16 pc;								//����ָ��
	UINT16 length;										//���ݳ���
	UINT8 buff[150];										//ͨ�Ż���
	UINT16 crc;									//crcУ����
	UINT8 cs;
}COMM_BASE;
extern CONTR_IF EI_Comm;

/*typedef struct
{
	COMM_BASE recv;
	UINT8 RunSta;
	//COMM_BASE send;
}COMMUNICATE;*/

void Parallel_Init(void);
void Parall_Uart_Rec_Data(UINT8 dataRec);
void Data_Deal_Task(void);

#endif
