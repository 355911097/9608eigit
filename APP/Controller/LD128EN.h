#ifndef __LD128EN_CRT_ZJ_H__
#define __LD128EN_CRT_ZJ_H__


#include "global.h"
#include "controller.h"

#define LD128EN_CRT_ZJ_COMMAND_TYPE_ALARM_EV				0x01		//��
#define LD128EN_CRT_ZJ_COMMAND_TYPE_MAIN_POWER				0x12		//�����¼�
#define LD128EN_CRT_ZJ_COMMAND_TYPE_BACKUP_POWER			0x13		//�����¼�
#define LD128EN_CRT_ZJ_COMMAND_TYPE_REG_DEV_REQUEST		0x20		//�ڵ㶯������
#define LD128EN_CRT_ZJ_COMMAND_TYPE_RESET					0x50		//��������λ
#define LD128EN_CRT_ZJ_COMMAND_TYPE_RESET_LINK				0x51		//������λ



#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT				0x02		//����ģ�����
#define LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT				0x03		//̽��������
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT			0x04		//����ִ�й���
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER				0x05		//�������ϻָ�
#define LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER			0x06		//̽�������ϻָ�
#define LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT			0x07		//���Թ���
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV0_ANSWER			0x09		//����0�ش�
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV1_ANSWER			0x0A		//����1�ش�
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV0_REMOVE			0x0B		//����0����
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV1_REMOVE			0x0C		//����1����
#define LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER		0x0D		//���Իָ�
#define LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_FAULT			0x14		//��������ϼ��ָ���ֵΪ�Ա�
#define LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_RECOVER			0x15		//����ͻ�������
#define LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_FAULT			0x16
#define LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_RECOVER		0x17
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_START		0x18		//�ڵ㶯������պ�(�ڵ㶯������Ϊ�Ա�)
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_STOP		0x19		//�ڵ㶯������Ͽ�
#define LD128EN_CRT_ZJ_EV_TYPE_SILENCE						0x30		//����������
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST				0x40		//����0����
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST				0x41		//����1����
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP					0x42		//����0ֹͣ
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP					0x43		//����1ֹͣ
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_START					0x44		//����0����
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_START					0x45		//����1����
#define LD128EN_CRT_ZJ_EV_TYPE_POLL_RETURN					0x7F

#define LD128EN_CRT_ZJ_POLL_PERIOD1S						125// 1s==125*8



void Save_Component_Info_LD128EN(UINT8 *buf);
void Save_Other_Info_LD128EN(UINT8 *buf);
UINT16 Change_Event_Type_LD128EN(UINT8 src_event,UINT8 *record_type);

void Send_Poll_Contr_LD128EN(CONTR_IF *buf);
UINT8 Analyse_LD128EN(CONTR_IF *buf);
void Handle_LD128EN_Zj(CONTR_IF *buf);
void Com_Task_LD128EN_Zj(CONTR_IF *buf);
void Com_Task_LD128EN_Jt(CONTR_IF *buf);

#endif
