

#include "LD128EN_PRT.h"
#include "record_status.h"
#include "sys_init.h"
#include "xycnbus.h"
#include "record_manage.h"
#include "led.h"

GET_EVENT_TYPE_ASCII const C_EVENT_CHANGE_LIST_LD128EN_PRT[]=
{
	{"��",		RECORD_FIRE,		 INT_TYPE_ALARM},
	{"����",		RECORD_FAULT,		 INT_TYPE_DEV_FAULT},
	{"���",	    RECORD_MONITER,		 INT_TYPE_MONITOR_ALARM},
	{"����",		RECORD_SHIELD,	 	 INT_TYPE_REQ_SHIELD},
	{"����",		RECORD_OTHERS,	 	 NULL},
	{"����",		RECORD_START,		 INT_TYPE_REQ_START},
	{"����",   		RECORD_ANSWER,	 	 INT_TYPE_DEVICE_START_FEED_SUC},
	{"��λ",	    RECORD_RESET,		 INT_TYPE_RESET_SUCESS},
	{"����",	    RECORD_POWERONOFF,	 INT_TYPE_POWER_ON},
};
LD_PRT_Device_Type const C_CTR_UC_CHANGE_LIST_LD128EN_PRT[]=
{
	{"����̽����",		0X2A},
	{"����̽����",		0X1F},
	{"�ֶ�������ť",	0X17},
	{"��ȼ����",		0X0A},
	{"����",			0X3E},
	{"����ģ��",		0XFF},
	{"�����ӿ�",   		0XFF},
	{"����˨",	    	0X18},
	{"ѹ������",	    0X63},
	{"ˮ��ָʾ��",		0X60},
	{"����",			0XB2},
	{"���µ���",	    0XFF},
	{"�źŷ�",			0X61},
	{"�ӿ�",			0XFF},
	{"���¸���",		0X33},
	{"����",   			0XFF},
	{"ʣ�����",	    0X11},
	{"�¶�",	    	0XFF},
	{"�����",   		0X14},
	{"��Դ",			0X1A},
	{"������",			0X5B},
	{"���ܱ�",			0X5F},
	{"�������",		0XB8},
	{"��ĭ���",		0XB8},
	{"�ɷ����",		0XB8},
	{"������",   		0X75},
	{"������",	    	0X67},
	{"�յ��·�",	    0X68},
	{"������",			0X71},
	{"����",			0X77},
	{"�����㲥",	    0X95},
	{"Ӧ������",		0XB5},
	{"��ɢָʾ",		0X7C},
	{"���⾯��",		0X7D},
	{"©��",   			0XFF},
	{"�����",	    	0X5F},
	{"���̿�",	    	0X73},
	{"��ѹ�ͷ�",   		0X6F},
	{"��ѹ����",		0XC5},
	{"�����",			0X70},
	{"�·��",			0XC2},
	{"�ŷ��",			0XC1},
	{"Ԥ���÷�",		0XB7},
	{"ĩ�˷���",		0XFF},
	{"���̷��",   		0X6E},
	{"����",	    	0XAF},
};

UINT8 Change_UC_Type_LE128EN_PRT(CONTR_IF *buf)
{
	UINT8 dest_type = 0xff;
	UINT8 k,eventNum;

	eventNum = sizeof(C_CTR_UC_CHANGE_LIST_LD128EN_PRT)/sizeof(LD_PRT_Device_Type);
	for(k=0; k < eventNum; k++)
	{
		if(strstr((const char*)&buf->DAT_Return[0],(const char*)C_CTR_UC_CHANGE_LIST_LD128EN_PRT[k].src_type) != NULL)
		{
			dest_type = C_CTR_UC_CHANGE_LIST_LD128EN_PRT[k].dest_type;
			break;
		}
	}
	return dest_type;
}



UINT8 Analyse_LE128EN_PRT(CONTR_IF *buf)
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
				if((buf->R.Buf[head1_loc] == FRAME_HEAD_LE128EN_PRT) && (buf->R.Buf[i] == FRAME_HEAD2_LE128EN_PRT))//�¼�Ӧ��
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
				if((buf->R.Buf[end1_loc] == FRAME_TAIL_LE128EN_PRT) && (buf->R.Buf[i] == FRAME_TAIL2_LE128EN_PRT))//�¼�Ӧ��
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
			if((frame_total_len > FRAME_MIN_LEN_LE128EN_PRT)&&(frame_total_len < FRAME_MAX_LEN_LE128EN_PRT))
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
void Handle_LE128EN_PRT(CONTR_IF *buf)
{
	UINT8 k,eventNum,i,event_loc;
	RECORD_STRUCT record;
	char *p;
	Watch_Dog();
	eventNum = sizeof(C_EVENT_CHANGE_LIST_LD128EN_PRT)/sizeof(GET_EVENT_TYPE_ASCII);
	for(k=0; k < eventNum; k++)
	{
		p = strstr((const char*)&buf->DAT_Return[0],(const char*)C_EVENT_CHANGE_LIST_LD128EN_PRT[k].Event_Annotaiton);
		if( p != NULL)
		{
			record.Type= C_EVENT_CHANGE_LIST_LD128EN_PRT[k].RecordType;
			record.EventType.word= C_EVENT_CHANGE_LIST_LD128EN_PRT[k].EventType;
			break;
		}
	}
	if(k != eventNum)
	{
		if((record.Type == RECORD_RESET)||(record.Type == RECORD_POWERONOFF))
		{
			MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
		}
		else if(record.Type == RECORD_FAULT)
		{
			if(strstr((const char*)&buf->DAT_Return[0],(const char*)"����") != NULL)
			{
				MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
				record.EventType.word = INT_TYPE_BACKUP_POWER_FAU;
			}
			else if(strstr((const char*)&buf->DAT_Return[0],(const char*)"����") != NULL)
			{
				MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
				record.EventType.word = INT_TYPE_INPUT_POWER_FAULT;
			}
			else
			{
				event_loc =(UINT8)( p - (char*)buf->DAT_Return);
				for(k=event_loc;k<FRAME_MAX_LEN_LE128EN_PRT;k++)
				{
					if(buf->DAT_Return[k] == 0x3A)//�ҵ�:λ�� ��ʽ:   ��:01088
					{
						break;
					}
				}
				record.Uc[LEN_REG_UC-5] = Change_UC_Type_LE128EN_PRT(buf);
				record.Uc[LEN_REG_UC-4] = ((buf->DAT_Return[k+4]- '0' )<<4) + buf->DAT_Return[k+5]- '0' ;
				record.Uc[LEN_REG_UC-3] = ((buf->DAT_Return[k+2]- '0' )<<4) + buf->DAT_Return[k+3]- '0' ;
				record.Uc[LEN_REG_UC-2] = buf->DAT_Return[k+1]- '0';
				record.Uc[LEN_REG_UC-1] = CTR_NUMBER_L;

				for(k=0;k<FRAME_MAX_LEN_LE128EN_PRT;k++)
				{
					if((buf->DAT_Return[k] == 0x1B)&&(buf->DAT_Return[k+1] == 0x39))//�ҵ�:λ�� ��ʽ:   ��:01088
					{
						for(i=0;i<LEN_REG_CC;i++)
						{
							if(buf->DAT_Return[k+2+i] != 0x0A)
							{
								record.Cc[LEN_REG_CC-i-1] = buf->DAT_Return[k+2+i];
							}
						}
					}
				}
			}
		}
		else
		{
			event_loc =(UINT8)( p - (char*)buf->DAT_Return);
			for(k=event_loc;k<FRAME_MAX_LEN_LE128EN_PRT;k++)
			{
				if(buf->DAT_Return[k] == 0x3A)//�ҵ�:λ�� ��ʽ:   ��:01088
				{
					break;
				}
			}
			record.Uc[LEN_REG_UC-5] = Change_UC_Type_LE128EN_PRT(buf);
			record.Uc[LEN_REG_UC-4] = ((buf->DAT_Return[k+4]- '0' )<<4) + buf->DAT_Return[k+5]- '0' ;
			record.Uc[LEN_REG_UC-3] = ((buf->DAT_Return[k+2]- '0' )<<4) + buf->DAT_Return[k+3]- '0' ;
			record.Uc[LEN_REG_UC-2] = buf->DAT_Return[k+1]- '0';
			record.Uc[LEN_REG_UC-1] = CTR_NUMBER_L;

			for(k=0;k<FRAME_MAX_LEN_LE128EN_PRT;k++)
			{
				if((buf->DAT_Return[k] == 0x1B)&&(buf->DAT_Return[k+1] == 0x39))//�ҵ�:λ�� ��ʽ:   ��:01088
				{
					for(i=0;i<LEN_REG_CC;i++)
					{
						if(buf->DAT_Return[k+2+i] != 0x0A)
						{
							record.Cc[LEN_REG_CC-i-1] = buf->DAT_Return[k+2+i];
						}
					}
				}
			}
		}
		
		Record_Controler_If_Event(&record);
	}
	
	memset(buf->DAT_Return,0x00,sizeof(buf->DAT_Return));
	buf->R.Clev = buf->R.FrameEndLoc;
	buf->R.FrameLen = 0;
}
void Com_Task_LE128EN_PRT(CONTR_IF *buf)
{
	if(Analyse_LE128EN_PRT(buf))
	{
	    Handle_LE128EN_PRT(buf);
		On_Led_Contor();
	}
}

