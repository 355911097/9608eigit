
#ifndef __TX3607_H_
#define __TX3607_H_

#include "controller.h"
//֡����
//֡��ʽ:0x5x len data cs
//֡����: ����Ϊ�������ݳ���
//cs               : ����������У��

#define FRAME_LEN_TX3607            		32

#define FRAME_HEAD_TX3607               0x40  //֡ͷ:@
#define FRAME_HEAD_LEN_TX3607           0x01  //֡ͷ����
#define FRAME_LEN_OFFSET_TX3607         0x01  //֡����ƫ��λ��;֡���Ȱ������������Լ�У��
#define FRAME_LEN_BYTE_NUM_TX3607       0x01     
#define FRAME_CS_LEN_TX3607             0x06  //cs����
#define FRAME_TAIL_TX3607               0x23  //#
#define FRAME_TAIL_LEN_TX3607           0x01  //֡β����
//#define FRAME_OTHER_LEN_TX3607            0x00
#define FRAME_EXCEPT_DATA_LEN_TX3607    FRAME_HEAD_LEN_TX3607+FRAME_CS_LEN_TX3607+FRAME_TAIL_LEN_TX3607

#define FRAME_REPEAT_TIME_TX3607        5000  //�ظ�֡ɸѡʱ��5S



#define FRAME_CS_INIT_VALUE_TX3607    0xFFFF  //У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_TX3607  25  //У����ʼƫ��λ��,��֡ͷ��ʼ



void Com_Task_TX3607_Jt(CONTR_IF *buf);

#endif
