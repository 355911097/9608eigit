#ifndef __SIMPLEX_H__
#define __SIMPLEX_H__


#include "global.h"
#include "controller.h"

//֡����
//1C seq data 17 cs1 cs2
//У�鷶ΧΪ֡ͷ��֡β֮���������

#define FRAME_HEAD_SIMPLEX              0x1C  //֡ͷ
#define FRAME_HEAD_LEN_SIMPLEX 			0x01  //֡ͷ����
#define FRAME_TAIL_SIMPLEX              0x17  //֡β
#define FRAME_SEQ_LEN_SIMPLEX 			0x01  //֡���кų���
#define FRAME_SEQ_LOC_SIMPLEX			0x01  //֡���к�λ��
#define FRAME_CS_LEN_SIMPLEX            0x02  //cs����
#define FRAME_CS_INIT_VALUE_SIMPLEX     0x0000//У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_SIMPLEX   0x01  //У����ʼƫ��λ��
#define FRAME_COMMAND_LOC_SIMPLEX		0x02  //������λ��


//���߼��ʱ��
#define SIMPLEX_CONTR_OFFLINE_TIMER     240    //240S=1S*240 


//ͨѶ������
#define FRAME_COMMAND_ACK_SIMPLEX		0x06//ACK
#define FRAME_COMMAND_POLL_SIMPLEX		0x05//Ѳ��
#define FRAME_COMMAND_ANSWER_SIMPLEX	0x02//Ѳ��Ӧ��
#define FRAME_COMMAND_START_SIMPLEX		0x11//������λ
#define FRAME_COMMAND_EVENT_SIMPLEX		0x1E//�¼��ϱ�

//��ʶ
#define FRAME_NEED_ACK_SIMPLEX			0x2D//��ҪӦ��ACK��-��ASKIIֵ
#define FRAME_ACKED_SIMPLEX				0x2A//�Ѿ��ع�ACK��*��ASKIIֵ

//�¼�����ת��
#define SIMPLEX_EV_FIRE					0x56//��
#define SIMPLEX_EV_FIRE_RESET			0x46//δ����
#define SIMPLEX_EV_EARLY_ALARM			0x60//Ԥ��
#define SIMPLEX_EV_EARLY_ALARM_RESET	0x50//Ԥ���ָ�
#define SIMPLEX_EV_FAULT				0x64//����
#define SIMPLEX_EV_FAULT_ELIMINAATE		0x54//���ϻָ�
#define SIMPLEX_EV_MONITOR				0x63//���
#define SIMPLEX_EV_MONITOR_RELEASE		0x53//����ͷ�


UINT16 Change_Event_Type_Simplex(UINT8 src_event,UINT8 *record_type);
void Com_Task_Simplex_Zj(CONTR_IF *buf);


#endif
