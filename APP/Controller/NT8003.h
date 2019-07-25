#ifndef __NT8003_H__
#define __NT8003_H__


#include "global.h"
#include "controller.h"

//֡����
//AA 55 DF(�豸����) XOR CS len DATA
//֡����: ��DATA��ʼ����
//cs		: ��DATA��ʼ����
//XOR		:��DATA��ʼ����

#define FRAME_HEAD1_NT8003              	0xAA  //֡ͷ
#define FRAME_HEAD2_NT8003					0x55  //֡ͷ
#define FRAME_HEAD_LEN_NT8003           	0x02  //֡ͷ����
#define FRAME_LEN_OFFSET_NT8003         	0x05  //֡����ƫ��λ��
#define FRAME_LEN_BYTE_NUM_NT8003       	0x01        
#define FRAME_CS_LEN_NT8003             	0x01  //cs����
#define FRAME_XOR_LEN_NT8003				0x01  //XOR����
//#define FRAME_TAIL_EI2000               0x16  //֡β
//#define FRAME_TAIL_LEN_EI2000           0x01  //֡β����
//#define FRAME_OTHER_LEN_EI2000               0x00
#define FRAME_EXCEPT_DATA_LEN_NT8003    	0x06//(FRAME_HEAD_LEN_EI2000+FRAME_LEN_BYTE_NUM_EI2000+FRAME_CS_LEN_EI2000+FRAME_TAIL_LEN_EI2000)

#define FRAME_CS_INIT_VALUE_NT8003      	0x00  //�ۼ�У���ʼ��ֵ
#define FRAME_XOR_INIT_VALUE_NT8003			0x00  //���У���ʼ��ֵ

#define FRAME_CS_XOR_START_OFFSET_NT8003    0x06  //У����ʼƫ��λ��
#define FRAME_XOR_OFFSET_NT8003				0x03  //����У��ֵ����λ��
#define FRAME_CS_OFFSET_NT8003				0x04  //�ۼӺ�У��ֵ����λ��
#define FRAME_EV_OFFSET_NT8003				0x06  //�¼�����ƫ�Ƶ�ַ
#define FRAME_EV_OTHER_TYPE_OFFSET_NT8003	0x09  //����������¼�����ƫ�Ƶ�ַ
#define FRAME_CONTR_NUM_OFFSET_NT8003		0x07  //����������ƫ�Ƶ�ַ
#define FRAME_LOOP_NUM_OFFSET_NT8003		0x08  //��·��ƫ�Ƶ�ַ
#define FRAME_LA_OFFSET_NT8003				0x09  //��ַ��ƫ�Ƶ�ַ
#define FRAME_DEV_TYPE_OFFSET_NT8003		0x0A  //�豸����ƫ�Ƶ�ַ
#define FRAME_EV_TIME_OFFSET_NT8003			0x0D  //�¼�ʱ��ƫ�Ƶ�ַ

#define FRAME_ANSWER_NT8003					0x66  //Ӧ��֡����

//���߼��ʱ��
#define NT_CONTR_OFFLINE_TIMER     			90    //90S=1S*90 



//�¼�����ת��
#define NT_EV_POLL					0xE6//Ѳ��
#define NT_EV_RESET					0xE1//��������λ
#define NT_EV_FIRE					0x01//��
#define NT_EV_START					0x02//����
#define NT_EV_FEEDBACK				0x03//����
#define NT_EV_MONITOR				0x04//���
#define NT_EV_COMPONENT_FAULT		0x06//��������
#define NT_EV_MODULE_FAULT			0x07//ģ�����
#define NT_EV_MODULE_STOP			0x0D//ֹͣ
#define NT_EV_FEEDBACK_CANCLE		0x0E//����ֹͣ
#define NT_EV_MONITOR_CANCLE		0x13//���ȡ��
#define NT_EV_FAULT_ELIMINALE		0x18//���ϻָ�
#define NT_EV_OTHER_FAULT			0x2D//��������
#define NT_EV_OTHER_FAULT_ELIMINALE	0x2E//�������ϻָ�

//���������¼�����
#define NT_EV_TRANSMIT				0x09//�����豸���¼�
#define NT_EV_MAINPOWER				0x1F//������ϻ�ָ�
#define NT_EV_MAINPOWER_VOLTAGE_LOW	0x20//����Ƿѹ
#define NT_EV_BACKUP_POWER			0x21//������ϻ�ָ�

//�豸����ת��
#define NT_DEV_TEMPERATURE						0x01//����
#define NT_DEV_SMOKE							0x04//����
#define NT_DEV_TEMPERATURE_SMOKE				0x05//���¸���
#define NT_DEV_INFRARED							0x06//���ͺ���
#define NT_DEV_ULTRAVIOLET						0x07//��������
#define NT_DEV_GAS								0x09//��ȼ����
#define NT_DEV_INFRARED_LIGHT					0x0A//�������
#define NT_DEV_LINEAR_TEMPERATURE				0x0B//���Ը���
#define NT_DEV_INPUT							0x0C//��������ģ��
#define NT_DEV_MANNUAL_BUTTON					0x0D//�ֱ�
#define NT_DEV_SIGNAL_INPUT						0x0E//�ź�����
#define NT_DEV_PULSE_OUTPUT						0x1F//�������
#define NT_DEV_VOLTAGE_OUTPUT					0x20//��ƽ���
#define NT_DEV_BROADCAST						0x23//�㲥
#define NT_DEV_ALARM							0x24//����
#define NT_DEV_HYDRANT_PUMP						0x25//����˨��
#define NT_DEV_SPRAY_PUMP						0x26//���ܱ�
#define NT_DEV_STABILIZING_PUMP					0x27//��ѹ��
#define NT_DEV_WATER_CURTAIN_PUMP				0x28//ˮĻ��
#define NT_DEV_DELUGE_PUMP						0x29//���ܱ�
#define NT_DEV_FOAM_PUMP						0x2A//��ĭ��
#define NT_DEV_DRAFT_FAN						0x2B//���̻�
#define NT_DEV_FORCED_DRAFT_FAN					0x2C//�ͷ��
#define NT_DEV_NEW_FAN							0x2D//�·��
#define NT_DEV_AIR_PUMP							0x2E//��ѹ��
#define NT_DEV_FIRE_DAMPER						0x2F//����
#define NT_DEV_SMOKE_DAMPER						0x30//���̷�
#define NT_DEV_BLOW_VALVE						0x31//�ͷ緧
#define NT_DEV_ELECTROMAGNETIC_VALVE			0x32//��ŷ�
#define NT_DEV_SMOKE_CONREOL_VALVE				0x33//�����̷�
#define NT_DEV_WATER_CURTAIN_ELECTROMAGNETIC	0x34//ˮĻ���
#define NT_DEV_DELUGE_VALVE						0x35//���ܷ�
#define NT_DEV_ELEVATOR							0x36//����
#define NT_DEV_AIR_CONDITION_UNIT				0x37//�յ�����
#define NT_DEV_DIESEL_GENERATOR					0x38//���ͷ���
#define NT_DEV_LIGHT_DSITRIBUTION				0x39//�������
#define NT_DEV_MOTIVE_ELECTRICITY				0x3A//�������
#define NT_DEV_FLOOR_LIGHT						0x3B//��ŵ�
#define NT_DEV_EMERHENCY_LIGHT					0x3C//Ӧ������
#define NT_DEV_EVACUATION_INSTRUCTION			0x3D//��ɢָʾ
#define NT_DEV_HARF_FIRE_CURTAIN				0x3E//�뽵����
#define NT_DEV_FIRE_CURTAIN						0x3F//ȫ������
#define NT_DEV_FIRE_DOOR						0x40//������
#define NT_DEV_MULTILINE_DISK					0x41//������
#define NT_DEV_ALARM_OUTPUT						0x42//�������
#define NT_DEV_BROADCAST_MODULE					0x43//�㲥ģ��
#define NT_DEV_REGULAR_PULSE_MODULE				0x44//��������
#define NT_DEV_REGULAR_VOLTAGE_MODULE			0x45//�����ƽ
#define NT_DEV_REGULAR_BROADCAST				0x46//����㲥
#define NT_DEV_START_BUTTON						0x4B//������ť
#define NT_DEV_STOP_BUTTON						0x4C//ֹͣ��ť
#define NT_DEV_SPRAY_MODULE						0x4D//����ģ��
#define NT_DEV_GAS_FIRE_EXTINGUISHING_CONTROLL	0x4E//���������
#define NT_DEV_BURGLAR_DETECTOR					0x4F//����̽����
#define NT_DEV_FIRE_DISPLAY_PANEL				0x50//������ʾ��
#define NT_DEV_FIRE_HYDRANT_BUTTOON				0x51//����˨��ť
#define NT_DEV_MONITOR_INPUT_MODULE				0x52//�������ģ��
#define NT_DEV_PRESSURE_SWITCH					0x53//ѹ������
#define NT_DEV_WATER_FLOW_INDICATOR				0x54//ˮ��ָʾ
#define NT_DEV_OVERHEAD_WATER_TANK				0x55//��λˮ��
#define NT_DEV_SIGNAL_VALVE						0x56//�źŵ���
#define NT_DEV_FIRE_POWER						0x57//������Դ
#define NT_DEV_CONTR_POWER						0x58//������Դ


typedef struct
{
	UINT8 nt_dev_type;
	UINT8 ts_dev_type;
}NT_DEV_TYPE;


UINT16 Change_Event_Type_NT8003(UINT8 src_event,UINT8 *record_type);
void Com_Task_NT8003_ZJ(CONTR_IF *buf);


#endif
