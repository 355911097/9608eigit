#ifndef __QN_193K_H__
#define __QN_193K_H__


#include "global.h"
#include "controller.h"


//֡����
//֡��ʽ: 82 data (22Byte) cs(�ۼӺ�) 83
//������:�¼�����+ ����+ ��·��+ la + �豸����+ ʱ��(������ʱ����)
//֡˵��:������У���ֽڲ��Ϊ2�����ֽڣ��ټ���30
//cs              : ���������ֽ�(���ǰ)�����ۼ�,�ȷ����ֽ�


#define FRAME_HEAD_QN193K               0x82	//֡ͷ
#define FRAME_CS_LOC_QN193K				0x17	//csλ��
#define FRAME_CSLEN_QN193K				0x1A	//������ͨ��֡�ܳ���
#define FRAME_CRC_LOC_QN193K			0x24 	//8λcrcλ��
#define FRAME_TAIL_QN193K               0x83	//֡β

#define FRAME_CS_INIT_VALUE_QN193K      0x00	//У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_QN193K    0x01	//У����ʼƫ��λ��
#define FRAME_EV_OFFSET_QN193k			0x01	//�¼�����λ��
#define FRAME_CONTR_NUM_OFFSET_QN193k	0x03	//����λ��
#define FRAME_LOOP_NUM_OFFSET_QN193k	0x05	//��·��λ��
#define FRAME_LA_OFFSET_QN193k			0x07	//laλ��


//�¼�����
#define QN193K_EV_POLL_ANSWER			0x09	//Ѳ��Ӧ��
#define QN193K_EV_CONTR_FAULT			0xEF	//����������
#define QN193K_EV_CONTR_RESET			0x01	//��������λ
#define QN193K_EV_CONTR_SILENCE			0x0B	//����������
#define QN193K_EV_FIRE					0x80	//��
#define QN193K_EV_FIRE1					0x0A	//��
#define QN193K_EV_FAULT					0x81	//����
#define QN193K_EV_FAULT_ELIMINATE		0x82	//���ϻָ�
#define QN193K_EV_LOOP_FAULT			0x87	//��·����
#define QN193K_EV_LOOP_FAULT_ELIMINATE	0x88	//��·���ϻָ�
#define QN193K_EV_START_AUTO			0x83	//�Զ�����
#define QN193K_EV_STOP_AUTO				0x84	//�Զ�ֹͣ
#define QN193K_EV_START_MANUAL			0x90	//�ֶ�����
#define QN193K_EV_STOP_MANUAL			0x91	//�ֶ�ֹͣ
#define QN193K_EV_DEV_ANSWER			0x85	//�豸Ӧ��
#define QN193K_EV_DEV_ANSWER_STOP		0x86	//�豸Ӧ����
#define QN193K_EV_SHIELD				0x98	//����
#define QN193K_EV_SHIELD_RELEASE		0x97	//ȡ������
#define QN193K_EV_MULTI_START_MANUAL	0x51	//�����ֶ�����
#define QN193K_EV_MULTI_STOP_MANUAL		0x52	//�����ֶ�ֹͣ
#define QN193K_EV_MULTI_ANSWER			0x53	//����Ӧ��
#define QN193K_EV_MULTI_ANSWER_STOP		0x54	//����Ӧ��ֹͣ
#define QN193K_EV_MULTI_START_AUTO		0x55	//�����Զ�����
#define QN193K_EV_MULTI_STOP_AUTO		0x56	//�����Զ�ֹͣ
#define QN193K_EV_MULTI_DELAY_START_AUTO	0x57//�����Զ�������ʱ
#define QN193K_EV_MULTI_DELAY_STOP_AUTO		0x58//����Ӧ��ȱʧ
#define QN193K_EV_MULTI_FAULT				0x59//������·����
#define QN193K_EV_MULTI_FAULT_ELIMINATE		0x5A//������·���ϻָ�
#define QN193K_EV_SIMULATED_FIRE			0x8B//ģ���
#define QN193K_EV_MONITOR					0x8C//���
#define QN193K_EV_MONITOR_RELEASE			0x8D//���ȡ��

//���ֽ���ɵ��¼�
#define QN193K_EV_FAULT1					0x80//����
#define QN193K_EV_FAULT_ELIMINATE1			0x90//���ϻָ�

#define QN193K_EV_BOARD						0x70//��·���¼�
#define QN193K_EV_MAIN_POWER				0x71//�����¼�
#define QN193K_EV_BACKUP_POWER				0x72//�����¼�


//Ѳ��ʱ��
#define QN193K_POLL_PERIOD1S       125  //1s==125*8

UINT16 Change_Event_Type_QN193k(UINT8 src_event,UINT8 * record_type);
void Com_Task_QN193k_Zj(CONTR_IF *buf);

#endif
