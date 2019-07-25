 
#include "ld128en.h"
#include "controller.h"
#include "xycnbus.h"
#include "basic.h"	
#include "record_manage.h"
#include "record_status.h"
#include "sys_init.h"
#include "led.h"

CHANGE_EVENT_TYPE const C_EVENT_CHANGE_LIST_LD128EN[]=
{
	{LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT,		    RECORD_FAULT,		 INT_TYPE_REG_DEV_OFFLINE},
	{LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT,		    RECORD_FAULT,		 INT_TYPE_SMOKE_SENSOR_FAU},
	{LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT,	    RECORD_FAULT,		 INT_TYPE_START_FAIL},
	{LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER,		RECORD_ELIMINATE,	 INT_TYPE_REG_DEV_ONLINE},
	{LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER,		RECORD_ELIMINATE,	 INT_TYPE_REG_DEV_ONLINE},
	{LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT,		RECORD_FAULT,		 INT_TYPE_REG_DEV_OFFLINE},
	{LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER,   RECORD_ELIMINATE,	 INT_TYPE_REG_DEV_ONLINE},
	{LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_FAULT,	    RECORD_FAULT,		 INT_TYPE_INPUT_POWER_OPEN_CIRCUIT},
	{LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_RECOVER,	    RECORD_ELIMINATE,	 INT_TYPE_MAINPOW_RECOVER},
	{LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_FAULT,	    RECORD_FAULT,		 INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT},
	{LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_RECOVER,	RECORD_ELIMINATE,	 INT_TYPE_BACKUP_POWER_RECOVER},
	{LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_START,	RECORD_START,    	 INT_TYPE_REQ_START},
	{LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_STOP,   RECORD_STOP,    	 INT_TYPE_REQ_STOP},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST,	        RECORD_START,   	 INT_TYPE_REQ_START},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST,		    RECORD_START,   	 INT_TYPE_REQ_START},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP,				RECORD_OTHERS,       INT_TYPE_STOP_SUCESS},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP,				RECORD_OTHERS,       INT_TYPE_STOP_SUCESS},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK0_START,			RECORD_OTHERS,	     INT_TYPE_START_SUCESS},
	{LD128EN_CRT_ZJ_EV_TYPE_LINK1_START,			RECORD_OTHERS,	     INT_TYPE_START_SUCESS},	
};




void Save_Component_Info_LD128EN(UINT8 *buf)
{
    UINT8 uc[3];
	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	//����,��·,��ַ
	
	record.EventType.word = INT_TYPE_FIRE_ALARM;		
	record.Type = RECORD_FIRE;		

	uc[0] = System.ctr_addr[0];     //����
	uc[1] = *(buf+1);  //��· 
	uc[2] = *(buf+2);//��ַ��
	Hex_To_BasicUC(&record.Uc[1],&uc[0],3);
	MemoryCpyInvert(&record.Uc[1],&record.Uc[1],LEN_REG_UC-1);
	
	
	Record_Controler_If_Event(&record);	
}

void Save_Other_Info_LD128EN(UINT8 *buf)  
{
	UINT8 uc[3];
    UINT8 source_event;
	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	record.Sta = RECORD_STA_INIT; 
	record.Mode = RMODE_CONTR_UC; 

	source_event = *(buf);

	record.EventType.word = Change_Event_Type_LD128EN(source_event,&record.Type);	
	if(record.EventType.word != INT_TYPE_NULL)
	{
		//record.Type = Get_EventTypeGroup(record.EventType.word);
		
		if((source_event >= LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_FAULT) 
		  && (source_event <= LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_RECOVER))
		{
			MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
		}
		else if((source_event == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_START) 
			|| (source_event == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_STOP))
		{
			uc[0] = System.ctr_addr[0];  //����
			uc[1] = 0x00;				 //��ʱ����
			uc[2] = *(buf+1);			 //��ַ��
			Hex_To_BasicUC(&record.Uc[1],&uc[0],3);
			MemoryCpyInvert(&record.Uc[1],&record.Uc[1],LEN_REG_UC-1);
		}
		else
		{
			uc[0] = System.ctr_addr[0];  //����
			uc[1] = *(buf+1);  //��· 
			uc[2] = *(buf+2);  //��ַ��
			Hex_To_BasicUC(&record.Uc[1],&uc[0],3);
			MemoryCpyInvert(&record.Uc[1],&record.Uc[1],LEN_REG_UC-1);
		}
			
		Record_Controler_If_Event(&record);
	}
}

//����Ϊ�ӿڳ���������ú���
//===============================================================================
//�޸�����: 2017-07
//��������: ����ת���¼�
//����            : src_event���������ݵ��¼� ;record_typeת�����¼����;
//����ֵ      : Ϊ��ϸ�¼�����
//�޸���Ա: ����
//===============================================================================

UINT16 Change_Event_Type_LD128EN(UINT8 src_event,UINT8 *record_type)
{
	UINT16 dest_event = 0xffff;
	UINT16 k,eventNum;

	eventNum = sizeof(C_EVENT_CHANGE_LIST_LD128EN)/sizeof(CHANGE_EVENT_TYPE);
	for(k=0; k < eventNum; k++)
	{
		if(C_EVENT_CHANGE_LIST_LD128EN[k].SrcEventType == src_event)
		{
			dest_event = C_EVENT_CHANGE_LIST_LD128EN[k].DestEventType;
			break;
		}
	}
	if(k == eventNum)
	{ 
		dest_event = INT_TYPE_NULL;
	}
	else
	{
		(*record_type) = C_EVENT_CHANGE_LIST_LD128EN[k].RecordType;//Get_EventTypeGroup(dest_event);
	}
	return dest_event;
}


void Send_Poll_Contr_LD128EN(CONTR_IF *buf)
{
	buf->T.Buf[buf->T.Tail] = 0x20;
	buf->T.Tail += 1;
}


UINT8 Analyse_LD128EN_JT(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_head,fr_end_loc=0; 
	UINT8 j,ope_flag=0;
	
	if(buf->R.Clev == buf->R.Head) return 0;

	if(buf->R.Clev >= CONTR_BUF_LEN)  buf->R.Clev=0;
	i = buf->R.Clev;
	
	Watch_Dog();

	while(i != buf->R.Head)
	{
		if(buf->R.Buf[i] == 0x20)
		{
			buf->R.Clev = i;
			break;
		}
		if(++i == CONTR_BUF_LEN)
		{
			i = 0;
		}
	}
	//����һȦδ�ҵ���Ч��
	if(i == buf->R.Head)
	{
		buf->R.Clev = buf->R.Head;
		buf->R.FrameEndLoc = buf->R.Head;
		return ope_flag;
	}
	
	fr_head = buf->R.Clev + 1;
	if(fr_head >= CONTR_BUF_LEN)
	{
		fr_head -= CONTR_BUF_LEN;
	}

	if(buf->R.Head == fr_head) return ope_flag;
	
	//�յ�Ѳ��Ӧ��
	if(buf->R.Buf[fr_head] == LD128EN_CRT_ZJ_EV_TYPE_POLL_RETURN)
	{
		buf->DAT_Return[0] = buf->R.Buf[fr_head];
		buf->R.Clev += 2;
		if(buf->R.Clev >= CONTR_BUF_LEN)
		{
			buf->R.Clev -= CONTR_BUF_LEN;
		}
		buf->R.FrameEndLoc = buf->R.Clev;

		Contr.ComFault.Count = 0;
		ope_flag = TRUE;
	}
	//�յ��¼�
	else
	{	
		//��λ���𾯡����ϡ����ϻָ������硢����
		if((buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_ALARM_EV) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_MAIN_POWER) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_BACKUP_POWER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_REG_DEV_REQUEST) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_SILENCE)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_START) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_START)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_RESET) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_RESET_LINK))
		{
			fr_end_loc = buf->R.Clev + 4;
			//�ж�����תȦ
			if(fr_end_loc >= CONTR_BUF_LEN)
			{
				fr_end_loc -= CONTR_BUF_LEN;
			}
			buf->R.FrameEndLoc = fr_end_loc;
			//ȷ������һ֡
			if(fr_end_loc > buf->R.Clev)//û��תȦ
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head < fr_end_loc)) return ope_flag;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head < fr_end_loc)) return ope_flag;
			}
			data_loc = fr_head;
			for(j=0;j<3;j++)
			{
				buf->DAT_Return[j] = buf->R.Buf[data_loc];
				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж�����תȦ
			}
			
			Contr.ComFault.Count = 0;
			ope_flag = TRUE;
		}

		else
		{
			buf->R.Clev++;
			memset(buf->DAT_Return,0x00,sizeof(buf->DAT_Return));
		}
	}
	return ope_flag;
}



UINT8 Analyse_LD128EN_ZJ(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_end_loc=0; 
	UINT8 j,ope_flag=0;
	
	if(buf->R.Clev == buf->R.Head) return 0;

	if(buf->R.Clev >= CONTR_BUF_LEN)  buf->R.Clev=0;
	i = buf->R.Clev;
	
	Watch_Dog();

	while(i != buf->R.Head)
	{
		if(buf->R.Buf[i] != 0)
		{
			buf->R.Clev = i;
			break;
		}
		if(++i == CONTR_BUF_LEN)
		{
			i = 0;
		}
	}
	//����һȦδ�ҵ���Ч��
	if(i == buf->R.Head)
	{
		buf->R.Clev = buf->R.Head;
		buf->R.FrameEndLoc = buf->R.Head;
		return ope_flag;
	}
	//�յ�Ѳ��Ӧ��
	if(buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_POLL_RETURN)
	{
		buf->DAT_Return[0] = buf->R.Buf[buf->R.Clev];
		buf->R.Clev++;
		if(buf->R.Clev >= CONTR_BUF_LEN)
		{
			buf->R.Clev = 0;
		}
		buf->R.FrameEndLoc = buf->R.Clev;

		Contr.ComFault.Count = 0;
		ope_flag = TRUE;
	}
	//�յ��¼�
	else
	{	
		//��λ���𾯡����ϡ����ϻָ������硢����
		if((buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_ALARM_EV) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_MAIN_POWER) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_BACKUP_POWER)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_REG_DEV_REQUEST) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_SILENCE)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK0_START) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_EV_TYPE_LINK1_START)
			|| (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_RESET) || (buf->R.Buf[buf->R.Clev] == LD128EN_CRT_ZJ_COMMAND_TYPE_RESET_LINK))
		{
			fr_end_loc = buf->R.Clev + 3;
			//�ж�����תȦ
			if(fr_end_loc >= CONTR_BUF_LEN)
			{
				fr_end_loc -= CONTR_BUF_LEN;
			}
			buf->R.FrameEndLoc = fr_end_loc;
			//ȷ������һ֡
			if(fr_end_loc > buf->R.Clev)//û��תȦ
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head < fr_end_loc)) return ope_flag;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head < fr_end_loc)) return ope_flag;
			}
			
			data_loc = buf->R.Clev;
			for(j=0;j<3;j++)
			{
				buf->DAT_Return[j] = buf->R.Buf[data_loc];
				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж�����תȦ
			}
			
			Contr.ComFault.Count = 0;
			ope_flag = TRUE;
		}

		else
		{
			buf->R.Clev++;
			memset(buf->DAT_Return,0x00,sizeof(buf->DAT_Return));
		}
	}

	return ope_flag;
}


void Handle_LD128EN(CONTR_IF *buf)
{
	UINT8 command_type;		//��������

	Watch_Dog();

	command_type = buf->DAT_Return[0];

	switch(command_type)
	{
		//��
		case LD128EN_CRT_ZJ_COMMAND_TYPE_ALARM_EV:
			Save_Component_Info_LD128EN(&buf->DAT_Return[0]);
			break;
		//�����¼�
		case LD128EN_CRT_ZJ_COMMAND_TYPE_MAIN_POWER:
			if(buf->DAT_Return[1] == 0x00)
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_RECOVER;
			}
			else
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_FAULT;
			}
			Save_Other_Info_LD128EN(&buf->DAT_Return[1]);
			break;
		//�����¼�
		case LD128EN_CRT_ZJ_COMMAND_TYPE_BACKUP_POWER:
			if(buf->DAT_Return[1] == 0x00)
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_RECOVER;
			}
			else
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_FAULT;
			}
			Save_Other_Info_LD128EN(&buf->DAT_Return[1]);
			break;
		//�ڵ��豸����
		case LD128EN_CRT_ZJ_COMMAND_TYPE_REG_DEV_REQUEST:
			if(buf->DAT_Return[1] == 0x00)
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_START;
			}
			else
			{
				buf->DAT_Return[1] = LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_STOP;
			}
			Save_Other_Info_LD128EN(&buf->DAT_Return[1]);
			break;
		//ע���豸�¼�
		case LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT:
		case LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT:
		case LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT:
		case LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER:
		case LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER:
		case LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT:
		case LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK0_START:
		case LD128EN_CRT_ZJ_EV_TYPE_LINK1_START:
			Save_Other_Info_LD128EN(&buf->DAT_Return[0]);
			break;
		//��������λ
		case LD128EN_CRT_ZJ_COMMAND_TYPE_RESET:
		case LD128EN_CRT_ZJ_COMMAND_TYPE_RESET_LINK:
			Save_Controller_Self_Info(RECORD_RESET,INT_TYPE_RESET_SUCESS);
			break;
		//����������
		case LD128EN_CRT_ZJ_EV_TYPE_SILENCE:
			Save_Controller_Self_Info(RECORD_OTHERS,INT_TYPE_DEVICE_SILENCE);
			break;
		//Ѳ��Ӧ��
		case LD128EN_CRT_ZJ_EV_TYPE_POLL_RETURN:
			Poll_Controller_Init(buf);
			break;

		default:
			Poll_Controller_Init(buf);
			break;
	}

	buf->R.Clev = buf->R.FrameEndLoc;

	Monitor_Controller_Fault_Eliminate();
	Poll_Controller_Init(buf);
}

//===============================================================================
//��������: ���������ͨѶ����
//�������: ��
//�������: ��
//�޸�����: 2016-10-29
//�޸���Ա: ����
//===============================================================================

void Com_Task_LD128EN_Zj(CONTR_IF *buf)
{
	if(Analyse_LD128EN_ZJ(buf))
	{
		Handle_LD128EN(buf);
		On_Led_Contor();
	}
	
	if(B_Poll_Ctr)
	{
		Send_Poll_Contr_LD128EN(buf); 
		B_Poll_Ctr = 0;
	}
}

void Com_Task_LD128EN_Jt(CONTR_IF *buf)
{
	if(Analyse_LD128EN_JT(buf))
	{
		Handle_LD128EN(buf);
		On_Led_Contor();
	}
}


