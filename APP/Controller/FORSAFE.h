#ifndef __FORSAFE_H__
#define __FORSAFE_H__


#include "global.h"
#include "controller.h"

//֡����
//F0 LA len data   cs 16
//֡����: Ϊdata��ĳ���
//cs               : ��LA��data������У��

#define FRAME_DATA_MAX_LEN_FORSAFE		0x28  //ÿ֡����������󳤶�

#define FRAME_HEAD_FORSAFE              0xF0  //֡ͷ
#define FRAME_HEAD_LEN_FORSAFE			0x01  //֡ͷ����
#define FRAME_LA_LEN_FORSAFE			0x01  //LA����
#define FRAME_LEN_BYTE_LEN_FORSAFE		0x01  //�����ֽڳ���
#define FRAME_LEN_OFFSET_FORSAFE        0x02  //֡����ƫ��λ��
#define FRAME_CS_LEN_FORSAFE            0x02  //cs����
#define FRAME_CS_INIT_VALUE_FORSAFE     0x0000//У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_FORSAFE   0x01  //У����ʼƫ��λ��
#define FRAME_EXCEPT_DATA_LEN_FORSAFE	0x05  //ÿ֡��ȥ�������ĳ���(head+la+len+cs�ĳ���)

#define FRAME_EV_SOURCE_LOC_FORSAFE		0x05  //��Ϣ����λ��
#define FRAME_EV_TYPE_LOC_FORSAFE		0x06  //�¼�����λ��
#define FRAME_EV_CONTR_NUM_LOC_FORSAFE	0x08  //����λ��
#define FRAME_EV_LOOP_NUM_LOC_FORSAFE	0x0F  //��·λ��
#define FRAME_EV_LA_LOC_FORSAFE			0x10  //LAλ��
#define FRAME_DEV_TYPE_LOC_FORSAFE		0x15  //�豸����λ��


//���߼��ʱ��
#define FORSAFE_CONTR_OFFLINE_TIMER     90    //240S=1S*240 


//ͨѶ����
#define FORSAFE_COMMAND_LOC				0x03//�����ַ�λ��
#define FORSAFE_COMMAND_RESET			0xA1//������������豸��λ������Ӧ������
#define FORSAFE_COMMAND_POLL			0xA2//Ѳ�죬��Ӧ��
#define FORSAFE_COMMAND_TIME			0xA4//Уʱ�������Ӧ������
#define FORSAFE_COMMAND_EVENT			0xA5//�¼��������Ӧ��


//�¼�����ת��
#define FORSAFE_EV_DEV_ONLINE					0x00//�豸���� 	
#define FORSAFE_EV_DEV_OFFLINE					0x01//�豸����
#define FORSAFE_EV_DEV_TYPE_FAULT				0x02//�豸���ʹ���
#define FORSAFE_EV_DEV_LA_REPEAT				0x03//�豸����
#define FORSAFE_EV_DEV_START_FAIL				0x04//����ʧ��
#define FORSAFE_EV_ALARM						0x05//��
#define FORSAFE_EV_START_REQUEST				0x06//��������
#define FORSAFE_EV_START_SUCCEED				0x07//�����ɹ�
#define FORSAFE_EV_DEV_OUTPUT_FAULT				0x08//ģ���������
#define FORSAFE_EV_POWER_FAULT					0x09//���������
#define FORSAFE_EV_POWER_FAULT_ELIMINATE		0x0A//��������ϻָ�
#define FORSAFE_EV_DEV_OUTPUT_SHORT				0x0B//ģ�������·
#define FORSAFE_EV_DEV_MULTI_SHORT				0x0E//���߶�·
#define FORSAFE_EV_DEV_MULTI_CIRCUIT			0x0F//���߿�·
#define FORSAFE_EV_DEV_MULTI_FAULT				0x10//���߹���
#define FORSAFE_EV_DEV_MULTI_FAULT_ELIMINATE	0x11//���߹��ϻָ�
#define FORSAFE_EV_DEV_SELF_CHECK_FAULT			0x12//����Ϲ���
#define FORSAFE_EV_DEV_POLLUTION				0x13//��Ⱦ
#define FORSAFE_EV_COMM_FAULT					0x14//ͨ�Ź���
#define FORSAFE_EV_COMM_FAULT_ELIMINATE			0x15//ͨ�Ź��ϻָ�
#define FORSAFE_EV_FLASH_FAULT					0x16//flash����
#define FORSAFE_EV_FLASH_FAULT_ELIMINATE		0x17//flash���ϻָ�
#define FORSAFE_EV_MULTI_START_REQUEST1			0x18//������������
#define FORSAFE_EV_MULTI_STOP_REQUEST_1			0x19//����ֹͣ����
#define FORSAFE_EV_MULTI_START_SUCCEED1			0x1A//���������ɹ�
#define FORSAFE_EV_MULTI_STOP_SUCCEED1			0x1B//����ֹͣ�ɹ�
#define FORSAFE_EV_MULTI_START_SUCCEED2			0x1C//�����ֳ������ɹ�
#define FORSAFE_EV_MULTI_STOP_SUCCEED2			0x1D//�����ֳ�ֹͣ�ɹ�
#define FORSAFE_EV_MULTI_START_FAIL1			0x1E//��������ʧ��
#define FORSAFE_EV_MULTI_STOP_FAIL1				0x1F//����ֹͣʧ��
#define FORSAFE_EV_CONTR_POWERON				0x21//����
#define FORSAFE_EV_CONTR_RESET					0x22//��λ
#define FORSAFE_EV_CONTR_AUTO					0x23//�Զ�����
#define FORSAFE_EV_CONTR_ALARM					0x24//��ȷ��
#define FORSAFE_EV_CONTR_EARLY_ALARM			0x25//Ԥ��ȷ��
#define FORSAFE_EV_CONTR_EARLY_RESET			0x26//Ԥ����λ
#define FORSAFE_EV_DEV_SHIELD					0x28//����
#define FORSAFE_EV_DEV_SHIELD_RELEASE			0x29//���ν��
#define FORSAFE_EV_LOOP_SHIELD					0x2A//��·����
#define FORSAFE_EV_LOOP_SHIELD_RELEASE			0x2B//��·���ν��
#define FORSAFE_EV_DEV_MANUAL_START				0x2C//�ֶ�����
#define FORSAFE_EV_DEV_MANUAL_STOP				0x2D//�ֶ�ֹͣ
#define FORSAFE_EV_DEV_LINK_START				0x2E//��������
#define FORSAFE_EV_DEV_LINK_DELAY				0x2F//������ʱ
#define FORSAFE_EV_LOOP_SHORT					0x30//���߶�·
#define FORSAFE_EV_24VLOOP_FAULT				0x31//24V�����쳣
#define FORSAFE_EV_24VLOOP_CURRENT_FAULT		0x32//24V����©�����쳣
#define FORSAFE_EV_LOOP_VOLTAGE_FAULT			0x33//���߲ο���ѹ�쳣
#define FORSAFE_EV_5VLOOP_CURRENT_FAULT			0x34//5V����©�����쳣
#define FORSAFE_EV_5VLOOP_VOLTAGE_FAULT			0x35//5V���ߵ�ѹ�쳣
#define FORSAFE_EV_0VLOOP_VOLTAGE_FAULT			0x36//0V���ߵ�ѹ�쳣
#define FORSAFE_EV_0VLOOP_CURRENT_FAULT			0x37//0V����©�����쳣
#define FORSAFE_EV_LOOP_HIGHVOLTAGE_CIRCUIT		0x38//��ѹ�ж�
#define FORSAFE_EV_LOOP_VOLTAGE_LOW				0x39//���ߵ�ѹ��
#define FORSAFE_EV_LOOP_VOLTAGE_HIGH			0x3A//���ߵ�ѹ��
#define FORSAFE_EV_LOOP_CURRENT_FAULT			0x3B//���ߵ����쳣
#define FORSAFE_EV_LOOP_LEAKAGE_CURRENT_FAULT	0x3C//©�����쳣
#define FORSAFE_EV_LOOP_GND_FAULT				0x3D//���߸����쳣
#define FORSAFE_EV_LOOP_MAIN_FAULT				0x3E//���������쳣
#define FORSAFE_EV_LOOP_NO_POWER				0x3F//���߲����ϵ�
#define FORSAFE_EV_LOOP_FAULT_ELIMENATE			0x40//���߹��ϻָ�
#define FORSAFE_EV_EARLY_ALARM					0x41//Ԥ��
#define FORSAFE_EV_DEV_FAULT					0x42//�豸����
#define FORSAFE_EV_MULTI_START_REQUEST2			0x43//������������
#define FORSAFE_EV_MULTI_STOP_REQUEST_2			0x44//����ֹͣ����
#define FORSAFE_EV_MULTI_START_SUCCEED3			0x45//���������ɹ�
#define FORSAFE_EV_MULTI_START_FAIL2			0x46//��������ʧ��
#define FORSAFE_EV_MULTI_STOP_SUCCEED3			0x47//����ֹͣ�ɹ�
#define FORSAFE_EV_MULTI_STOP_FAIL2				0x48//����ֹͣʧ��


//��Ϣ����
#define FORSAFE_EV_SOURCE_DETECTOR				0x01//̽ͷ
#define FORSAFE_EV_SOURCE_MODULE				0x02//ģ��
#define FORSAFE_EV_SOURCE_LOOP					0x03//��·
#define FORSAFE_EV_SOURCE_MAIN_POWER			0x04//����
#define FORSAFE_EV_SOURCE_BATTERY				0x05//����
#define FORSAFE_EV_SOURCE_CRT					0x06//�����
#define FORSAFE_EV_SOURCE_PANEL					0x07//��ʾ��
#define FORSAFE_EV_SOURCE_MULTI					0x08//����
#define FORSAFE_EV_SOURCE_CONTR					0x09//������
#define FORSAFE_EV_SOURCE_NET_MODULE			0x0A//����ģ��
#define FORSAFE_EV_SOURCE_CHARGE				0x0B//���
#define FORSAFE_EV_SOURCE_SYS_BOARD				0x0C//ϵͳ��


UINT16 Change_Event_Type_Forsafe_SF(UINT8 src_event,UINT8 *record_type);
void Com_Task_Forsafe_SF_Zj(CONTR_IF *buf);


#endif
