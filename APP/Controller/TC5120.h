#ifndef __tc5120_H__
#define __tc5120_H__


#include "global.h"
#include "controller.h"

//֡����
//68 len len 68   self 0 goal 0 10 ctr num data   cs 16

#define FRAME_MIN_LEN_EI2000            7
#define FRAME_MAX_LEN_EI2000            250

#define FRAME_HEAD_TC5120_PRT           0x0D  //֡ͷ
#define FRAME_HEAD_LEN_TC5120_PRT       0x01  //֡ͷ����
#define FRAME_TYPE1_LEN_TC5120_PRT		0x05//��Ϣ����1����ĳ���
#define FRAME_TYPE2_LEN_TC5120_PRT		0x3F//��Ϣ����2����ĳ���
#define FRAME_LEN1_TC5120_PRT			0x13//��֡֡��
#define FRAME_LEN2_TC5120_PRT			0x19//�еȳ���֡��֡��
#define FRAME_LEN3_TC5120_PRT			0x55//�γ�֡��֡��
#define FRAME_LEN4_TC5120_PRT			0x58//�֡��֡��
#define FRAME_TAIL_TC5120_PRT           0x0A  //֡β
#define FRAME_TAIL_LEN_TC5120_PRT       0x01  //֡β����

#define FRAME_LOOP_LOC1_TC5120_PRT		0x48//�𾯡�������ͣ�����������¼���·��Ϣ��ȡ��ַ
#define FRAME_LOOP_LOC2_TC5120_PRT		0x45//���ϵ��¼���·��Ϣ��ȡ��ַ
#define FRAME_LA_LOC1_TC5120_PRT		0x4B//�𾯵��¼�LA��Ϣ��ȡ��ַ
#define FRAME_LA_LOC2_TC5120_PRT		0x48//���ϵ��¼�LA��Ϣ��ȡ��ַ




//�豸����
#define DEV_SMOKE  			0x2A//����
#define DEV_TEMPERATURE  	0x1F//����
#define DEV_INPUT  			0x55//����ģ��
#define DEV_OUTPUT  		0x56//���ģ��
#define DEV_INOUT  			0x57//�������ģ��
#define DEV_BUTTON  		0x17//�ֱ�
#define DEV_ALARM  			0x7D//����

#define DEV_UNKNOWN  		0xFF//δ֪�豸


void Com_Task_Tc5120_Prt_JT(CONTR_IF *buf);


#endif
