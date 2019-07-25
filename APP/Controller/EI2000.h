#ifndef __EI2000_H__
#define __EI2000_H__


#include "global.h"
#include "controller.h"

//֡����
//68 len len 68   self 0 goal 0 10 ctr num data   cs 16
//֡����: Ϊȥ����ͷ4�ֽڣ�У���֡β
//cs               : ��ȥ����ͷ4�ֽڵ�����У��

#define FRAME_MIN_LEN_EI2000            7
#define FRAME_MAX_LEN_EI2000            250

#define FRAME_HEAD_EI2000               0x68  //֡ͷ
#define FRAME_HEAD_LEN_EI2000           0x02  //֡ͷ����
#define FRAME_LEN_OFFSET_EI2000         0x01  //֡����ƫ��λ��
#define FRAME_LEN_BYTE_NUM_EI2000       0x02        
#define FRAME_CS_LEN_EI2000             0x01  //cs����
#define FRAME_TAIL_EI2000               0x16  //֡β
#define FRAME_TAIL_LEN_EI2000           0x01  //֡β����
//#define FRAME_OTHER_LEN_EI2000               0x00
#define FRAME_EXCEPT_DATA_LEN_EI2000    0x06//(FRAME_HEAD_LEN_EI2000+FRAME_LEN_BYTE_NUM_EI2000+FRAME_CS_LEN_EI2000+FRAME_TAIL_LEN_EI2000)

#define FRAME_CS_INIT_VALUE_EI2000           0x00  //У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_EI2000         0x04  //У����ʼƫ��λ��

#define EI_VERSION            0x10        //��������Ѳ��ʱʹ��

//���߼��ʱ��
#define EI_CONTR_OFFLINE_TIMER     240    //240S=1S*240 

//Ѳ��ʱ��
#define EI_POLL_PERIOD25S       3125  //25s==3125*8
#define EI_POLL_PERIOD30S       3750  //30s==3750*8
#define EI_POLL_PERIOD40S       5000  //40s==5000*8


//ͨѶ����
#define EI_COMMAND_TYPE_ALARM           135
#define EI_COMMAND_TYPE_FAULT           138
#define EI_COMMAND_TYPE_RESET           139
#define EI_COMMAND_TYPE_POLL_RETURN     140
#define EI_COMMAND_TYPE_OTHER_ALARM     141
#define EI_Refresh_CONTR                200
#define EI_POLL_CONTR                   206
#define EI_COMMAND_TYPE_ANSWER          250
#define EI_COMMAND_TYPE_UPLOAD_INF      0x3F //Ѳ���ϱ�


//�¼�����ת��
#define EI_EV_TYPE_ALARM                0x01   //��
#define EI_EV_TYPE_SMOKE_ALARM          0x16   //���̻�
#define EI_EV_TYPE_TEMPERATURE_ALARM    0x17   //���»�

#define EI_EV_TYPE_THEFT_ALARM          0x02   //����
#define EI_EV_TYPE_PRE_ALARM            0x03   //Ԥ��
#define EI_EV_TYPE_DETECTOR_FAULT       0x04   //̽ͷ����
#define EI_EV_TYPE_AGE_FAULT            0x05   //�ϻ�����
#define EI_EV_TYPE_SHORT_ISULATE_FAULT  0x07   //��·�������
#define EI_EV_TYPE_NO_FAULT             0x08   //δ�����

#define EI_EV_TYPE_ACTION               0x0A   //����
#define EI_EV_TYPE_ISOLATOR             0x0B   //����
#define EI_EV_TYPE_START                0x0C   //���� (����ģ�� )
#define EI_EV_TYPE_LEAKAGE              0x0D   //й¶
#define EI_EV_TYPE_INPUT_ALARM          0x0E   //����ģ���
#define EI_EV_TYPE_CONTROL_DELAY        0x0F   //����ģ��������ʱ
#define EI_EV_TYPE_SMOKE_SENSE_FAULT    0x18   //�̴��й���
#define EI_EV_TYPE_TEMPERATURE_FAULT    0x19   //�´��й���
#define EI_EV_TYPE_ADDR_REPEAT_FAULT    0x1A   //��ַ�ظ�
#define EI_EV_TYPE_24V_OPEN_FAULT       0x1B   //24V����
#define EI_EV_TYPE_INPUT_OR_OUTPUT_OVERSTEP_FAULT    0x2A    //���������Խ��
#define EI_EV_TYPE_SIGNAL_OPEN_FAULT    0x2B   //�ź��߶���
#define EI_EV_TYPE_MONITOR_ALARM        0x30   //��ܱ���

#define EI_EV_TYPE_MUL_START            0x34   //��������


#define EI_EV_TYPE_BUS_LOOP_SHORT_FAULT    0x10  //��·��·����
#define EI_EV_TYPE_BUS_LOOP_OPEN_FAULT     0x11  //��·��·����

#define EI_EV_MULTI_PANEL_OUTPUT_OPEN_FAULT    0x13   //ֱ�Ӱ��������·
#define EI_EV_MULTI_PANEL_OUTPUT_SHORT_FAULT   0x14   //ֱ�Ӱ��������·
#define EI_EV_24VPOWER_OUTPUT_SHORT_FAULT      0x15   //24V��Դ�����·
#define EI_EV_LCD_PANEL_FAULT                  0x1C   //Һ����ʾ���������
#define EI_EV_LINKAGE_MAIN_PANEL_FAULT         0x1F   //���������������
#define EI_EV_DIRRECT_PANEL_COM_FAULT          0x20   //ֱ�Ӱ�����ͨѶ����
#define EI_EV_LINKAGE_PANEL_COM_FAULT          0x21   //�������̰�ͨѶ����
#define EI_EV_MAIN_POWER_FAULT                 0x28   //�������
#define EI_EV_BACKUP_POWET_FAULT               0x29   //�������

#define EI_EV_AREA_ALARM                       0x33   //�����
#define EI_EV_MUL_START_SHORT_FAULT            0x36   //����������·
#define EI_EV_MUL_START_OPEN_FAULT             0x37   //����������·
#define EI_EV_MUL_STOP_SHORT_FAULT             0x38   //����ֹͣ��·
#define EI_EV_MUL_STOP_OPEN_FAULT              0x39   //����ֹͣ��·

#define EI_EV_SG_COM_FAULT                     0x3B   //����ͨѶ����
#define EI_EV_BUS_BOARD_FAULT                  0x3C   //���߰����
#define EI_EV_SG_START                         0x3E   //��������
#define EI_EV_SG_SHORT_FAULT                   0x3F   //�����·
#define EI_EV_SG_OPEN_FAULT                    0x40   //�����·




UINT16 Change_Event_Type_EI(UINT8 src_event,UINT8 *record_type);
void Save_Component_Info_EI2000(UINT8 *buf);
void Save_Loop_Fault_EI2000(UINT8 *buf);
void Save_Other_Info_EI2000(UINT8 *buf);
void EI_Save_Reset(void);

void Send_Answer_Frame_EI2000(CONTR_IF *buf,UINT8 type);
void Send_Poll_Contr_EI2000(CONTR_IF *buf);
UINT8 Analyse_EI2000(CONTR_IF *buf);
void Handle_EI2000_ZJ(CONTR_IF *buf);
void Com_Task_EI2000_Zj(CONTR_IF *buf);


#endif
