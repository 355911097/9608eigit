#ifndef __GT_GK603_H__
#define __GT_GK603_H__


#include "global.h"
#include "controller.h"

//֡����
//24 24 len(7D) data(121BYTE) cs(У���)
//֡����: Ϊ֡���ܳ��ȣ�����֡ͷ��֡βУ��
//cs               : ��ǰ124�ֽڽ���У�飬�ۼӺ�

//#define FRAME_MIN_LEN_EI2000            7
//#define FRAME_MAX_LEN_EI2000            250

#define FRAME_HEAD_GM647               	0x24  //֡ͷ
#define FRAME_HEAD_LEN_GM647           	0x02  //֡ͷ����
#define FRAME_LEN_OFFSET_GM647         	0x02  //֡����ƫ��λ��
#define FRAME_LEN_BYTE_NUM_GM647       	0x01        
#define FRAME_LEN_TOTAL_GM647			0x7D  //֡�ܳ���
#define FRAME_CS_LEN_GM647             	0x01  //cs����

#define FRAME_CS_INIT_VALUE_GM647		0x00//У���ʼֵ

#define FRAME_DEV_TYPE_OFFSET1_GM647		0x48//�������豸����ƫ��
#define FRAME_DEV_TYPE_OFFSET2_GM647		0x35//�����豸����ƫ��
#define FRAME_EV_OFFSET_GM647				0x54//�¼�����ƫ��
#define FRAME_CONRE_NUM_GM647				0x23//����������ƫ��
#define FRAME_LOOP_NUM_GM647				0x27//��·��ƫ��
#define FRAME_LA_NUM_GM647					0x2D//��ַ��ƫ��


//�¼�����ת��
enum GT_EVENT
{
	GT_POWEROFF = 0,				//�ػ�
	GT_POWERON,						//����
	GT_FIRE,						//��
	GT_REG_DEV_OFFLINE,				//�豸����
	GT_REG_DEV_ONLINE,				//�豸����
	GT_CONTR_RESET,					//��λ
	GT_MAINPOWER_VOLTAGE_L,			//����Ƿѹ
	GT_MAINPOWER_FAULT,				//�������
	GT_MAINPOWER_RECOVER,			//����ָ�
	GT_MAINPOWER_VOLTAGE_RECOVER,	//����Ƿѹ�ָ�
	GT_BATTERY_VOLTAGE_L,			//����Ƿѹ
	GT_BATTERY_FAULT,				//�������
	GT_BATTERY_VOLTAGE_RECOVER,		//����Ƿѹ�ָ�
	GT_BATTERY_RECOVER,				//����ָ�
	GT_MANUAL_ALLOW,				//�ֶ�����
	GT_MANUAL_FORBID,				//�ֶ���ֹ
	GT_AUTO_ALLOW,					//�Զ�����
	GT_AUTO_FORBID,					//�Զ���ֹ
	GT_FIRE_RESTORE,				//Ԥ���ָ�
	GT_MONITOR,						//���
	GT_MONITOR_CANCLE,				//��ܳ���
	GT_START,						//����
	GT_STOP,						//ͣ��
	GT_FEEDBACK,					//����
	GT_FEEDBACK_CANCLE,				//ֹͣ����
	GT_SHIELD,						//����
	GT_SHIELD_CANCLE,				//�����ͷ�

};


//�豸����
enum GT_DEVICE
{
	GT_BUTTON = 0,			//�ֱ�
	GT_SMOKE,				//����
	GT_TEMPERATURE,			//����
	GT_INOUT,				//�������ģ��
	GT_BUSDISK,				//������
};


typedef struct
{
	UINT8 gt_type;
	UINT8 ts_type;
}GT_Device_Type;


UINT8 GT603_Device_Get(CONTR_IF * buf);

void Com_Task_GT603_SF_ZJ(CONTR_IF *buf);


#endif
