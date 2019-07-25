#ifndef __fhsj9108_H__
#define __fhsj9108_H__


#include "global.h"
#include "controller.h"

//֡����
//Ѳ��֡:	1C 2E 1B 40
//����֡:	1B 40 xxxx.xx.xx 20 20 20 xx:xx:xx 20 20 20 xxxxxxxx 0A 1C 26 �¼�0D ��ӡ��ʽ1C 26 �¼�
//				���� ��ӡ��ʽxxx ��ӡ��ʽ1C 26 �¼���ӡ��ʽ0D 0A

#define FRAME_HEAD_POLL_FHSJ9108_PRT		0x1C//Ѳ��֡֡ͷ
#define FRAME_DATA1_POLL_FHSJ9108_PRT		0x2E//Ѳ��֡����
#define FRAME_DATA2_POLL_FHSJ9108_PRT		0x1B//Ѳ��֡����
#define FRAME_TAIL_POLL_FHSJ9108_PRT		0x40//Ѳ��֡֡β
#define FRAME_POLL_LENGTH_FHSJ9108_PRT		0x04//Ѳ��֡����
#define FRAME_HEAD_DATA_FHSJ9108_PRT		0x1B//����֡֡ͷ
#define FRAME_FLAG1_FHSJ9108_PRT			0x3A//��ӡ�����е�ð��
#define FRAME_FLAG2_FHSJ9108_PRT			0x0A//��ӡ�еĻ���
#define FRAME_FLAG3_FHSJ9108_PRT			0x2E//��ӡ�еĵ��
#define FRAME_ROW_NUM_FHSJ9108_PRT			0x02//һ����Ϣ������
#define ROW1_LENGTH_FHSJ9108_PRT			0x23//�ڶ��г���
#define FRAME_FORM_PRINT1_FHSJ9108_PRT		0x1C//ȷ�ϴ�ӡ��ʽ
#define FRAME_FORM_PRINT2_FHSJ9108_PRT		0x26//ȷ�ϴ�ӡ��ʽ
#define FRAME_FORM_PRINT3_FHSJ9108_PRT		0x2E//��ӡ��ʽ
#define FRAME_UC_LOC_FHSJ9108_PRT			0x1A//UC��ʼλ��

#define POLL_FLAG_FHSJ9108_PRT				0x02//�յ�Ѳ��֡�ı�ʶ

//�¼�����
enum FHSJ_PRT_EVENT
{
	FHSJ9108_PRT_FIRE = 0,			//��
	FHSJ9108_PRT_FAULT,				//����
	FHSJ9108_PRT_FAULT_ELIMINATE,	//��������
	FHSJ9108_PRT_START,				//����
	FHSJ9108_PRT_STOP,				//ֹͣ
	
};


//�豸����

typedef struct
{
	UINT8 fhsj_type;
	UINT8 ts_type;
}FHSJ_DEV_TYPE;

void Com_Task_Fhsj9108_Prt(CONTR_IF *buf);



#endif
