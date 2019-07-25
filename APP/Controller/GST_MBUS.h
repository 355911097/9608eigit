#ifndef __GST_MBUS_H__
#define __GST_MBUS_H__

#include "global.h"
#include "controller.h"

//֡����
//CTR_NUMBER_L  03 len data   cs0 CS1
//֡����: Ϊȥ����ͷ4�ֽڣ�У���֡β
//cs               : ��ȥ����ͷ4�ֽڵ�����У��

#define FRAME_MIN_LEN_MBUS             2
#define FRAME_MAX_LEN_MBUS             210

#define FRAME_HEAD_MBUS                CTR_NUMBER_L  //֡ͷ
#define FRAME_HEAD_LEN_MBUS            0x01  //֡ͷ����
#define FRAME_LEN_OFFSET_MBUS          0x02  //֡����ƫ��λ��
#define FRAME_LEN_BYTE_NUM_MBUS        0x01        
#define FRAME_CTR_LEN_MBUS             0x01
#define FRAME_CS_LEN_MBUS              0x02  //cs����
//#define FRAME_TAIL_MBUS                          //��֡β
//#define FRAME_TAIL_LEN_MBUS                  //֡β����
//#define FRAME_OTHER_LEN_MBUS            0x01
#define FRAME_EXCEPT_DATA_LEN_MBUS     0x05//(FRAME_HEAD_LEN_MBUS +FRAME_LEN_OFFSET_MBUS +FRAME_LEN_BYTE_NUM_MBUS +FRAME_CS_LEN_MBUS)

#define FRAME_CS_INIT_VALUE_MBUS            0xFFFF  //У���ʼ��ֵ
#define FRAME_CS_START_OFFSET_MBUS          0x00  //У����ʼƫ��λ��




#define Selsct_Count          100  //????????
#define Selsct_Total_GST200   241  //??????
#define Selsct_Total_GST5000  (System.ctr_loop_end+1)*240  //??????
#define Selsct_Start_GST200   0  //??????
#define Selsct_Start_GST5000  System.ctr_loop_start*240   //??????

extern UINT16 Selsct_Sta; //??????


void Com_Task_GST_Modbus(CONTR_IF *buf);
void GST_Modbus_Event_Sum(uint16*event_num);
UINT16 GST_Modbus_Event_Sta(uint16 start_loc,uint16 sum,uint8*event_buff);

#endif
