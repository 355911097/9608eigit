

#include "NT_FT8003_PRT.h"
#include "controller.h"
#include "sys_init.h"
#include "xycnbus.h"
#include "record_manage.h"


GET_EVENT_TYPE_ASCII const C_EVENT_CHANGE_LIST_FT8003_PRT[]=
{
	{"��",		RECORD_FIRE,		 INT_TYPE_ALARM},
	{"����",		RECORD_FAULT,		 INT_TYPE_DEV_FAULT},
	{"���",	    RECORD_MONITER,		 NULL},
	{"����",		RECORD_SHIELD,	 	 INT_TYPE_REQ_SHIELD},
	{"����",		RECORD_OTHERS,	 	 NULL},
	{"����",		RECORD_START,		 INT_TYPE_REQ_START},
	{"����",   		RECORD_ANSWER,	 	 INT_TYPE_DEVICE_START_FEED_SUC},
	{"��λ",	    RECORD_RESET,		 INT_TYPE_RESET_SUCESS},
	{"����",	    RECORD_POWERONOFF,	 INT_TYPE_POWER_ON},
};
GET_Device_Type_ASCII const C_CTR_UC_CHANGE_LIST_FT8003_PRT[]=
{
	{"���̽����",		0X1F},
	{"������̽����",		0X2A},
	{"���¸���",			0X34},
	{"���ͺ���",			0X3E},
	{"��������",			0X3D},
	{"��ȼ����",			0X0A},
	{"�������",			0X2B},
	{"���µ���",			0XFF},
	{"��������ģ��",		0X55},
	{"�ֱ�",				0X17},
	{"�ź�����",			0XFF},
	{"�������ģ��",		0X56},
	{"��ƽ���ģ��",		0X56},
	{"�㲥",				0X95},
	{"�������⾯����",		0X7D},
	{"����˨��",			0X5B},
	{"���ܱ�",				0X5F},
	{"��ѹ��",				0X64},
	{"ˮĻ��",				0XBF},
	{"���ܱ�",				0XC0},
	{"��ĭ��",				0X69},
	{"���̻�",				0X6E},
	{"�ͷ��",				0XC3},
	{"�·��",				0XC2},
	{"��ѹ��",				0XBC},
	{"����",				0XAF},
	{"���̷�",				0XB2},
	{"�ͷ緧",				0XC3},
	{"��ŷ�",				0XB6},
	{"�����̷�",			0X71},
	{"ˮĻ���",			0XB9},
	{"����",				0X77},
	{"�յ�����",			0X96},
	{"���ͷ���",			0X97},
	{"�������",			0X98},
	{"�������",			0X99},
	{"��ŵ�",				0XCD},
	{"��������",			0XB5},
	{"�赼ָʾ",			0X7C},
	{"��������",			0XB3},
	{"��������",			0XB4},
	{"������",				0X67},
	{"�⾯����",			0X7D},
	{"��������",			0X7D},
	{"����ģ��",			0XA6},
	{"����˨��ť",			0X18},
	{"�������ģ��",		0X55},
	{"ѹ������",			0X63},
	{"ˮ��ָʾ",			0X60},
	{"��λˮ��",			0X5C},
	{"�źŵ���",			0X61},
	{"��Դ",				0X1A},
};


void Handle_FT8003_PRT(CONTR_IF *buf)
{
	
}

UINT8 Analyse_FT8003_PRT(CONTR_IF *buf)
{
	UINT16 i,data_loc,head1_loc,end1_loc; 
	UINT8 count,frame_total_len,ope_flag = FALSE;

	if(buf->R.Clev == buf->R.Head) return 0;

	if(buf->R.Clev >= CONTR_BUF_LEN)  
	{
		buf->R.Clev=0;
	}
	i = buf->R.Clev;
	
	switch(buf->AnalyseSta)
	{
		case FRAME_HEAD:
			Watch_Dog();
			while(i != buf->R.Head)
			{
				if(i == 0)
				{
					head1_loc = CONTR_BUF_LEN-1;
				}
				else
				{
					head1_loc = i - 1;
				}
				if((buf->R.Buf[head1_loc] == FRAME_HEAD_FT8003_PRT) && (buf->R.Buf[i] == FRAME_HEAD2_FT8003_PRT))//�¼�Ӧ��
				{
					buf->R.Clev = head1_loc; 
					break;
				}
				if(++i == CONTR_BUF_LEN) i=0;
			}
			if(i == buf->R.Head )  //����һȦ��δ�ҵ�֡ͷ    
			{
				buf->R.Clev = buf->R.Head;
        		buf->R.FrameEndLoc = buf->R.Head; 
				break;
			}
			buf->AnalyseSta = FRAME_DATA;
			
		case FRAME_DATA: //ȷ���Ƿ�����һ֡����
			Watch_Dog();
			while(i != buf->R.Head)
			{
				if(i == CONTR_BUF_LEN-1)
				{
					end1_loc = CONTR_BUF_LEN-1;
				}
				else
				{
					end1_loc = i - 1;
				}
				if((buf->R.Buf[end1_loc] == FRAME_TAIL_FT8003_PRT) && (buf->R.Buf[i] == FRAME_TAIL2_FT8003_PRT))//�¼�Ӧ��
				{
					buf->R.FrameEndLoc = i; 
					break;
				}
				if(++i == CONTR_BUF_LEN) i=0;
			}
			if(i == buf->R.Head )  //����һȦ��δ�ҵ�֡β
			{
				break;
			}

			buf->AnalyseSta = FRAME_CS;
			
		case FRAME_CS:
			
			Watch_Dog();
			if(buf->R.FrameEndLoc < buf->R.Clev)
			{
				frame_total_len = CONTR_BUF_LEN + buf->R.FrameEndLoc - buf->R.Clev + 1;
			}
			else
			{
				frame_total_len = buf->R.FrameEndLoc - buf->R.Clev + 1;
			}
			
			data_loc = buf->R.Clev;
			if((frame_total_len > FRAME_MIN_LEN_FT8003_PRT)&&(frame_total_len < FRAME_MAX_LEN_FT8003_PRT))
			{
				for(count=0; count<frame_total_len; count++)
				{
					buf->DAT_Return[count] = buf->R.Buf[data_loc];
					if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ
				}
				ope_flag = TRUE;
			}
			buf->AnalyseSta = FRAME_HEAD;
			break;
			
		default:
			buf->AnalyseSta = FRAME_HEAD;
			break;	
	}
	return ope_flag;
}



void Com_Task_FT8003_PRT(CONTR_IF *buf)
{
	if(Analyse_FT8003_PRT(buf))
	{
	    Handle_FT8003_PRT(buf);
	}
}


