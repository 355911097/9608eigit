
#ifndef _NF_FT8003_PRT_
#define _NF_FT8003_PRT_

#include "global.h"
#include "controller.h"


//֡����
//��һ����Ϣ��1B 38 ��ͷ�����һ����Ϣ��0D 0D���� ��ӡ������ASCII�봫��

#define FRAME_MIN_LEN_FT8003_PRT              4
#define FRAME_MAX_LEN_FT8003_PRT              127


#define FRAME_HEAD_FT8003_PRT                 0x1B   	//֡ͷ
#define FRAME_HEAD2_FT8003_PRT                0x38   	//֡ͷ
#define FRAME_HEAD_LEN_FT8003_PRT             0x02   	//֡ͷ����
#define FRAME_TAIL_FT8003_PRT                 0X0D		//֡β
#define FRAME_TAIL2_FT8003_PRT                0X0D		//֡β
#define FRAME_TAIL_LEN_FT8003_PRT             0X02		//֡β����



void Com_Task_FT8003_PRT(CONTR_IF *buf);

#endif
