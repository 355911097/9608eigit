

#ifndef _N3030_OLD__
#define _N3030_OLD__

#include "controller.h"

//֡����
//֡��ʽ: dd data cs bb
//֡����: �治ͬ���ݳ��ȹ̶�
//cs  :��������У��
#define FRAME_LEN_N3030_OLD				164

#define FRAME_HEAD_FIRE_N3030_OLD		0x6B	//�� 6B 7E A5 66
#define FRAME_HEAD_FAULT_N3030_OLD		0x45	//����45 9C
#define FRAME_HEAD_ANSWER_N3030_OLD		0xD1	//����D1 A1
#define FRAME_HEAD_SHIELD_N3030_OLD		0xF2	//����F2 AB 94 BB
//���ν���� �������� �ȵ�
//������θ�ʽ: 05 64 + F2 AB 94 BB
#define FRAME_HEAD_RESUME_N3030_OLD		0x05	//�ָ�05 64 

  
#define FRAME_TAIL_N3030_OLD                0x0A  //֡β

#define FRAME_TAIL_LEN_N3030_OLD            0x01  //֡β����

void Com_Task_N3030_OLD_Jt(CONTR_IF *buf);

#endif
