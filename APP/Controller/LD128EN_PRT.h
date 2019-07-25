
#ifndef __LD128EN_PRT_H
#define __LD128EN_PRT_H

#include "global.h"
#include "controller.h"

//֡����
//��һ����Ϣ��1B 36 ��ͷ�����һ����Ϣ��0A 0A ���� ��ӡ������ASCII�봫��

#define FRAME_MIN_LEN_LE128EN_PRT              4 
#define FRAME_MAX_LEN_LE128EN_PRT              127


#define FRAME_HEAD_LE128EN_PRT                 0x1B   //֡ͷ
#define FRAME_HEAD2_LE128EN_PRT                0x36   //֡ͷ
#define FRAME_HEAD_LEN_LE128EN_PRT             0x02   //֡ͷ����
#define FRAME_TAIL_LE128EN_PRT                 0X0A		//֡β
#define FRAME_TAIL2_LE128EN_PRT                0X0A		//֡β
#define FRAME_TAIL_LEN_LE128EN_PRT             0X02		//֡β����


typedef struct 
{
	UINT8 const * const src_type;
	UINT8 dest_type;
}LD_PRT_Device_Type;


void Com_Task_LE128EN_PRT(CONTR_IF *buf);


#endif
