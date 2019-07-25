#ifndef __GST200_H__
#define __GST200_H__

#include "global.h"
#include "controller.h"
#include "record_manage.h"


//֡����
//֡��ʽ:0x5x len data cs
//֡����: ����Ϊ�������ݳ���
//cs               : ����������У��

#define FRAME_MIN_LEN_GST200            5
#define FRAME_MAX_LEN_GST200            51

#define FRAME_HEAD_GST200               CTR_NUMBER_L  //֡ͷ:0x5+��������ַ
#define FRAME_HEAD_LEN_GST200           0x01  //֡ͷ����
#define FRAME_LEN_OFFSET_GST200         0x01  //֡����ƫ��λ��;֡���Ȱ������������Լ�У��
#define FRAME_LEN_BYTE_NUM_GST200       0x01     
#define FRAME_CS_LEN_GST200             0x01  //cs����
//#define FRAME_TAIL_GST200                        //��֡β
//#define FRAME_TAIL_LEN_GST200                 0x00  //֡β����
//#define FRAME_OTHER_LEN_GST200            0x00
#define FRAME_EXCEPT_DATA_LEN_GST200    0 //(FRAME_HEAD_LEN_GST200+FRAME_LEN_OFFSET_GST200+FRAME_CS_LEN_GST200)

#define FRAME_CS_INIT_VALUE_GST200    0x00  //У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_GST200  0x00  //У����ʼƫ��λ��,��֡ͷ��ʼ


//������������
#define GST200_CONTR_ANSWER           0x50
#define GST200_CONTR_POLL             0x30

#define GST_POLL_PERIOD300MS          37  //1000/8
#define GST_POLL_PERIOD600MS          75


//GST�¼�����
#define GST200_FIRE          0X15   //��
#define GST200_ANSWER        0X22   //����
#define GST200_RESUME        0X11   //�ָ�
#define GST200_START         0X02   //����
#define GST200_STOP          0X03   //ͣ��
#define GST200_FAULT         0X21   //����
#define GST200_SHIELD        0XDE   //����
#define GST200_RELEASE       0XDF   //�ͷ�
#define GST200_DELAY         0X23   //��ʱ
#define GST200_CANCEL        0X24   //��ʱ����
#define GST200_ELIMINATE     0X20   //�ų�


#define GST200_CTRSELF       0X31   //����������
#define GST200_RESET         0X04   //��������λ
#define GST200_SILENCE       0X61   //����������



//GST�豸����
#define GST_GRAT_TEMPER_MEASURE      1   //��դ����
#define GST_SPOT_HEAT                2   //���͸���
#define GST_SPOT_SMOKE               3   //���͸���
#define GST_ALARM_INTERFACE          4   //�����ӿ�
#define GST_COMPOSITE_FLAME          5   //���ϻ���
#define GST_BEAM_SMOKE               6   //��������
#define GST_ULTRAVIOLET_FLAME        7   //�������
#define GST_LINEAR_HEAT              8   //���͸���
#define GST_SUCTION_SMOKE            9   //��������
#define GST_COMPOSITE_FIRE           10   //����̽��
#define GST_MANUAL_POINT             11   //�ֶ���ť
#define GST_FIRE_BROADCAST           12   //�����㲥
#define GST_ACOUSTIC                 13   //Ѷ����
#define GST_FIRE_TELEPHONE           14   //�����绰
#define GST_FIRE_HYDRANT             15   //����˨
#define GST_FIRE_HYDRANT_PUMP        16   //����˨��
#define GST_SPRAY_PUMP               17   //���ܱ�
#define GST_STABILIZED_PUMP          18   //��ѹ��
#define GST_SMOKE_VENTILATOR         19   //���̻�
#define GST_PRESSURE_FAN             20   //�ͷ��
#define GST_NEW_FAN                  21   //�·��
#define GST_FRD                      22   //����
#define GST_SMOKE_EXHAUST_DAMPER     23   //���̷�
#define GST_BLOW_VALVE               24   //�ͷ緧
#define GST_SOLENOID_VALVE           25   //��ŷ�
#define GST_ROLLING_DOOR_MID         26   //��������
#define GST_ROLLING_DOOR_DOW         27   //��������
#define GST_FIREPROOF_DOOR           28   //������
#define GST_PRESS_SWITCH             29   //ѹ������
#define GST_WATER_FLOW_INDICATOR     30   //ˮ��ָʾ
#define GST_ELEVATOR                 31   //����
#define GST_AIR_CONDITIONING_UNIT    32   //�յ�����
#define GST_DIESEL_GENERATOR         33   //���ͷ���
#define GST_LIGHT_DISTRIBUTION       34   //�������
#define GST_POWER_DISTRIBUTION       35   //�������
#define GST_WATER_ELECTROMAGNETIC    36   //ˮĻ���
#define GST_GAS_START                37   //��������
#define GST_GAS_STOP                 38   //����ͣ��
#define GST_SLAVE                    39   //�ӻ�
#define GST_FIRE_DISPLAY_PANEL       40   //����ʾ��
#define GST_SLUICE_VALVE             41   //բ��
#define GST_DRY_POWDER               42   //�ɷ����
#define GST_FOAM_PUMP                43   //��ĭ��
#define GST_FIRE_CONTROL_POWER       44   //������Դ
#define GST_EMERGENCY_LIGHTING       45   //��������
#define GST_GUIDANCE_INSTRUCTIONS    46   //�赼ָʾ
#define GST_SPRAYING_INSTRUCTIONS    47   //����ָʾ
#define GST_SECURITY_MODULE          48   //����ģ��
#define GST_SIGNAL_VALVE             49   //�źŵ���
#define GST_SMOKE_CONTROL_VALVE      50   //�����̷�
#define GST_WATER_PUMP               51   //ˮĻ��
#define GST_FLOOR_LAMP               52   //��ƺ�
#define GST_EQUIPMENT_STOP           53   //�豸ͣ��
#define GST_PUMP_FAILURE             54   //�ù���
#define GST_EMERGENCY_START_BUTTON   55   //������ť
#define GST_EMERGENCY_STOP_BUTTON    56   //��ͣ��ť
#define GST_RAIN_PUMP                57   //���ܱ�
#define GST_UPPER_COMPUTER           58   //��λ��
#define GST_LOOP                     59   //��·
#define GST_AIR_COMPRESSOR           60   //��ѹ��
#define GST_LINKAGE_POWER            61   //������Դ
#define GST_TELEPHONE_JACK           62   //�绰���
#define GST_PART_EQUIPMENT           63   //�����豸
#define GST_DRENCH_VALVE             64   //���ܷ�
#define GST_HEAT_RODS                65   //���°�
#define GST_FAULT_OUTPUT             66   //�������
#define GST_MANUAL_ALLOW             67   //�ֶ�����
#define GST_AUTO_ALLOW               68   //�Զ�����
#define GST_COMBUSTIBLE_GAS          69   //��ȼ����
#define GST_STANDBY_INDICATOR        70   //����ָʾ
#define GST_DOOR_LAMP                71   //�ŵ�
#define GST_BACKUP_WORK              72   //���ù���
#define GST_EQUIPMENT_TROUBLE        73   //�豸����
#define GST_EMERGENCY_CALLING        74   //��������
#define GST_CLOCK_POWER              75   //ʱ�ӵ�Դ
#define GST_SOUND_LIGHT_ALARM        76   //���⾯��
#define GST_ALARM_TRANSMISSION       77   //��������
#define GST_LOOP_SWITCH              78   //��·����
#define GST_UNDEFINED                79   //δ����
#define GST_DELAY_OUTPUT             80   //��ʱ���
#define GST_FIRE_HYDRANT_2           81   //����˨
#define GST_CABLE_HEAT               82   //��ʽ����
#define GST_BREATHE_SMOKE            83   //��������
#define GST_BREATHE_FIRE             84   //������
#define GST_BREATHE_WARNING          85   //����Ԥ��
#define GST_DETECTOR_DIRTY           86   //̽������
#define GST_MULTI_WIRE               87   //��������
#define GST_SIMULATR_HEAT            88   //ģ�����
#define GST_ELECTRIC_ALARM           89   //©�籨��
#define GST_BUS                      90   //����

enum GST200_SEND_COMM
{
	GST200_COM_HEAD=0,
	GST200_COM,
};


enum GST200_CRC_INIT
{
	NO_INIT=0,
	MARK,
	SPACE,
};

typedef struct 
{
  UINT8 src_type;
  UINT8 dest_type;
}Gst_Device_Type;



typedef struct 
{
	UINT8 init_mode;
	UINT8 infor_index;
	UINT8 gst200_com;
    UINT8 gst500_poll_process;
    UINT8 gst500_timeout;
	UINT8 delay;
	
}GST;
extern GST Gst;



void Send_Answer_Frame_GST200(CONTR_IF *buf,UINT8 type);
void Send_Command_Frame_GST200(CONTR_IF *buf,UINT8 type);
UINT16 Change_Event_Type_GST200(UINT8 src_event,UINT8 *record_type);
UINT16 Change_UC_Type_GST200(UINT8 sevent_type);
void Save_Component_Info_GST200(UINT8 *buf);
void Save_Other_Info_GST200(UINT8 *buf);
void GST200_Save_Reset_Infor(UINT8 *buf);
UINT8 Analyse_GST200(CONTR_IF *buf);
void Handle_GST200_Zj(CONTR_IF *buf);
void Handle_GST200_Jt(CONTR_IF *buf);
void Com_Task_GST200_Zj(CONTR_IF *buf);
void Com_Task_GST200_Jt(CONTR_IF *buf);
void GST_Uart_Init_Change(UINT8 type);
#endif
