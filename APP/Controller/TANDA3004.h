#ifndef __tanda3004_H__
#define __tanda3004_H__


#include "global.h"
#include "controller.h"

//֡����
//�¼�����3A  20 ����0A ��/��/��20 ʱ: ��
//�¼�����3A  ������20 �豸����0A ��/��/��20 ʱ3A ��

#define FRAME_FLAG1_TX3004_PRT			0x3A//��ӡ�����е�ð��
#define FRAME_FLAG2_TX3004_PRT			0x0A//��ӡ�еĻ���
#define FRAME_FLAG3_TX3004_PRT			0x2F//��ӡ�е�б��
#define FRAME_FLAG4_TX3004_PRT			0x20//��ӡ�еĿո�
#define FRAME_ROW_NUM_TX3004_PRT		0x02//һ����Ϣ������
#define ROW0_MAX_LENGTH_TX3004_PRT		0x29//��һ�������
#define ROW1_LENGTH_TX3004_PRT			0x11//�ڶ��г���


//�¼�����
enum TANDA_PRT_EVENT
{
	TANDA_POWEROFF = 0,				//�ػ�
	TANDA_POWERON,					//����
	TANDA_FIRE,						//��
	TANDA_START,					//����
	TANDA_STOP,						//ֹͣ
	TANDA_SHIELD,					//����
	TANDA_RESET,					//��λ
	TANDA_MAINPOWER_FAULT,			//�������
	TANDA_BATTERY_FAULT,			//�������
	TANDA_DEV_OFFLINE,				//�豸����
	TANDA_MANUAL_FORBID,			//��ֹ����
	TANDA_MANUAL_ALLOW,				//�ֶ�����
	TANDA_AUTO_ALLOW,				//�Զ�����
	TANDA_SHIELD_RELEASE,			//���ν��
	TANDA_OUTPUT_FAULT,				//����߹���
	TANDA_DEV_ONLINE,				//�豸����
};


//�豸����
enum TANDA_PRT_DEVICE
{
	TANDA_TEMPERATURE,				//����
	TANDA_SMOKE,					//����
	TANDA_BUTTON,					//�ֱ�
	TANDA_INOUT,					//�������ģ��
	TANDA_ALARM,					//����
};

typedef struct
{
	UINT8 tanda_type;
	UINT8 ts_type;
}TANDA_DEV_TYPE;

void Com_Task_Tanda3004_Prt(CONTR_IF *buf);



#endif
