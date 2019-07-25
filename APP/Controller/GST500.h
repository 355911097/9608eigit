#ifndef __GST500_H__
#define __GST500_H__

#include "global.h"
#include "controller.h"

//֡����
//֡��ʽ: dd data cs bb
//֡����: �治ͬ���ݳ��ȹ̶�
//cs  :��������У��
#define FRAME_MIN_LEN_GST500            0
#define FRAME_MAX_LEN_GST500            10

//#define FRAME_HEAD_GST500                        0xDD��0xEE ��0xCB,����ǰ��ĵ�һ���׷�֡ͷ
#define FRAME_HEAD_LEN_GST500           0x01  //֡ͷ����
//#define FRAME_LEN_OFFSET_GST500             0x00  //��֡ͷ
//#define FRAME_LEN_BYTE_NUM_GST500        0x00        
#define FRAME_CS_LEN_GST500             0x01  //cs����
#define FRAME_TAIL_GST500               0xBB  //֡β
#define FRAME_TAIL_LEN_GST500           0x01  //֡β����
//#define FRAME_OTHER_LEN_GST200            0x00
#define FRAME_EXCEPT_DATA_LEN_GST500    0x03//(FRAME_HEAD_LEN_GST500+FRAME_CS_LEN_GST500+FRAME_TAIL_LEN_GST500)
#define FRAME_EXCEPT_DATA_LEN2_GST500    0x02//(FRAME_HEAD_LEN_GST500+FRAME_TAIL_LEN_GST500)


#define FRAME_CS_INIT_VALUE_GST500      0x00  //У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_GST500    0x01  //У����ʼƫ��λ��

#define POLL_ANS  0x55
#define EVENT_ANS  0xAA


enum GST500_POLL_PROCESS
{
	SEND_CTR_ADDR=0,
	SEND_HEAD,
	REC_CTR_ADDR,
	SEND_ANS,
	REC_EVENT,
	SEND_REC_SUCC,
	SEND_OVER,
};
void Send_Answer_Frame_GST500(CONTR_IF *buf,UINT8 data);
void Save_Alarm_Info_GST500(UINT8 *buf);
void Save_Fault_Info_GST500(UINT8 *buf);
void Save_Other_Info_GST500(UINT8 *buf);
UINT8 Analyse_GST500_Zj(CONTR_IF *buf);
void Com_Task_GST500_Zj(CONTR_IF *buf);
void Handle_GST500_Jt(CONTR_IF *buf);
UINT8 Analyse_GST500_Jt(CONTR_IF *buf);
void Com_Task_GST500_Jt(CONTR_IF *buf);

#endif
