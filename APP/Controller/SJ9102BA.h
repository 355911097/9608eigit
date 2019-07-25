#ifndef __SJ9102BA_H__
#define __SJ9102BA_H__


#include "global.h"
#include "controller.h"

//֡����
//7E 01 contr_num 01 len data csH csL 7E
//֡����: Ϊȥ����ͷ4�ֽڣ�У���֡β
//cs               : ��ȥ����ͷ4�ֽڵ�����У��

//#define FRAME_MIN_LEN_EI2000            7
//#define FRAME_MAX_LEN_EI2000            250

#define FRAME_HEAD_SJ9102BA             0x7E  //֡ͷ
#define FRAME_HEAD_LEN_SJ9102BA         0x01  //֡ͷ����
#define FRAME_LEN_OFFSET_SJ9102BA       0x04  //֡����ƫ��λ��
#define FRAME_LEN_BYTE_NUM_SJ9102BA     0x01        
#define FRAME_CS_LEN_SJ9102BA           0x02  //cs����
#define FRAME_TAIL_SJ9102BA             0x7E  //֡β
#define FRAME_TAIL_LEN_SJ9102BA         0x01  //֡β����
//#define FRAME_OTHER_LEN_EI2000               0x00
#define FRAME_EXCEPT_DATA_LEN_SJ9102BA  0x08//(FRAME_HEAD_LEN_EI2000+FRAME_LEN_BYTE_NUM_EI2000+FRAME_CS_LEN_EI2000+FRAME_TAIL_LEN_EI2000)

#define FRAME_CS_INIT_VALUE_SJ9102BA    0xFFFF  //У���ʼ��ֵ
//#define FRAME_CS_START_OFFSET_EI2000         0x04  //У����ʼƫ��λ��

//#define EI_VERSION            0x10        //��������Ѳ��ʱʹ��

//���߼��ʱ��
//#define EI_CONTR_OFFLINE_TIMER     240    //240S=1S*240 

//Ѳ��ʱ��
//#define EI_POLL_PERIOD25S       3125  //25s==3125*8
//#define EI_POLL_PERIOD30S       3750  //30s==3750*8
//#define EI_POLL_PERIOD40S       5000  //40s==5000*8

#define SJ_EV_OFFSET					0x27//�¼�����ƫ��
#define SJ_EV_TYPE_OFFSET				0x05//�¼�����ƫ��
#define SJ_CONTR_NUM_OFFSET				0x06//����ƫ��
#define SJ_LOOP_OFFSET					0x08//��·��ƫ��
#define SJ_LA_OFFSET					0x0A//LAƫ��
#define SJ_DEV_OFFSET					0x0C//�豸����ƫ��


//ͨѶ����
#define SJ_COMMAND_POLL					0x01//Ѳ��
#define SJ_COMMAND_RESET				0x0C//��λ
#define SJ_COMMAND_POWERON				0x0A//����
#define SJ_COMMAND_FAULT				0x06//����
#define SJ_COMMAND_FIRE					0x02//��
#define SJ_COMMAND_START				0x03//����
#define SJ_COMMAND_SHIELD				0x08//����

//�¼�����ת��
#define SJ_EV_BATTERRY_OPEN				0x5E//�����·
#define SJ_EV_DEV_OFFLINE				0x62//�豸����
#define SJ_EV_DEV_START					0x5A//����
#define SJ_EV_FIRE						0x58//��
#define SJ_EV_SHIELD					0x5D//�豸����
#define SJ_EV_LOOP_OPEN					0x6F//���߶�·


//�豸����ת��
#define SJ_DEV_ALARM_INPUT					0x00//��������
#define SJ_DEV_SMOKE						0x01//���͸���
#define SJ_DEV_TEMPERATURE					0x02//���͸���
#define SJ_DEV_PARALLEL_DETECTOR			0x03//����̽ͷ
#define SJ_DEV_MANUAL_BUTTON				0x04//�ֶ���ť
#define SJ_DEV_FIRE_HYDRANT					0x05//����˨
#define SJ_DEV_LINEAR_TEMPERATURE			0x06//���Ը���
#define SJ_DEV_FIRE_DETECTOR				0x07//����̽����
#define SJ_DEV_LINEAR_LIGHT					0x08//���Թ���
#define SJ_DEV_MONITOR_INPUT				0x14//�������
#define SJ_DEV_PRESSURE_SWITCH				0x15//ѹ������
#define SJ_DEV_COMBUSTIBLE_GAS				0x16//��ȼ����
#define SJ_DEV_WATER_FLOW_INDICATOR			0x17//ˮ��ָʾ
#define SJ_DEV_RESIDUAL_CURRENT				0x18//ʣ�����
#define SJ_DEV_ELECTRIC_TEMPERATURE			0x19//��������
#define SJ_DEV_SIGNAL_VALVE					0x1A//�źŵ���
#define SJ_DEV_FIRE_DAMPER_IN				0x1B//������
#define SJ_DEV_POWER_MODULE					0x1C//��Դģ��
#define SJ_DEV_DISPLAY_PANEL				0x1D//��ʾ��
#define SJ_DEV_SPRAY_WARNING				0x1E//��������
#define SJ_DEV_BOTTLE_VALVE					0x1F//ƿͷ��
#define SJ_DEV_START_VALVE					0x20//������
#define SJ_DEV_CONTROLL_PANEL				0x21//������
#define SJ_DEV_BLEED_INDICATION				0x22//����ָʾ
#define SJ_DEV_SPRAY_START					0x23//��������
#define SJ_DEV_SPRAY_FEEFBACK				0x24//��������
#define SJ_DEV_VOLTAGE_MEASURE				0x25//��ѹ���
#define SJ_DEV_CURRENT_MEASURE				0x26//�������
#define SJ_DEV_INOUT						0x28//�������
#define SJ_DEV_SOUND_LIGHT_ALARM			0x29//���⾯��
#define SJ_DEV_BROADCAST_MODULE				0x2A//�㲥ģ��
#define SJ_DEV_ALARM_BELL					0x2B//��������
#define SJ_DEV_SMOKE_DAMPER					0x2C//���̷�
#define SJ_DEV_FIRE_DAMPER					0x2D//����
#define SJ_DEV_POSITIVE_PRESSURE_AIR_VALVE	0x2E//��ѹ�緧
#define SJ_DEV_ROLLING_DOOR_DOWN			0x2F//����ȫ��
#define SJ_DEV_ROLLING_DOOR_HARF			0x30//�����뽵
#define SJ_DEV_FIRE_DOOR					0x31//������
#define SJ_DEV_NEW_FAN						0x32//�·��
#define SJ_DEV_SMOKE_EXHAUST_FAN			0x33//���̷��
#define SJ_DEV_POSITIVE_PRESSURE_AIR_FAN	0x34//��ѹ���
#define SJ_DEV_LIGHT_INTENSITY_CUTTING		0x35//����ǿ��
#define SJ_DEV_STIMULUS_CUTTING				0x36//����ǿ��
#define SJ_DEV_FIRE_PUMP					0x37//������
#define SJ_DEV_SPRAY_PUMP					0x38//���ܱ�
#define SJ_DEV_ELEVATOR_CRASH				0x39//�����Ƚ�
#define SJ_DEV_AIR_CONDITION_CUTTING		0x3A//�յ��ж�
#define SJ_DEV_FIRE_CURTAIN					0x3B//����ˮĻ
#define SJ_DEV_DULUGE_VALVE					0x3C//���ܷ�
#define SJ_DEV_SMOKE_SCREEN					0x3D//���̴���
#define SJ_DEV_EMERGENCY_LIGHTING			0x3E//Ӧ������
#define SJ_DEV_ENTRANCE_GUARD				0x3F//�Ž�ϵͳ
#define SJ_DEV_FIRE_WATER_MONITOR			0x40//����ˮ��
#define SJ_DEV_WATER_MIST					0x41//ϸˮ��
#define SJ_DEV_ELECTROMAGNETISM_RELEASE		0x42//����ͷ�
#define SJ_DEV_ELECTRIC_DOOR_CLOSER			0x43//�綯����
#define SJ_DEV_ELECTROMAGNETIC_DOOR_HOLDER	0x44//�������
#define SJ_DEV_DOORSENSOR					0x45//�Ŵſ���
#define SJ_DEV_MULTILINE_MODULE				0x46//����ģ��
#define SJ_DEV_FEEDBACK_INPUT				0x47//���뷴��
#define SJ_DEV_LOOP							0x4F//���߻�·
#define SJ_DEV_POWER						0x72//������Դ


typedef struct
{
	UINT8 sj_dev_type;
	UINT8 ts_type;
}SJ_DEV_TYPE;


UINT16 Change_Event_Type_SJ9102BA(UINT8 src_event,UINT8 *record_type);
void Com_Task_SJ9102BA_JT(CONTR_IF *buf);



#endif
