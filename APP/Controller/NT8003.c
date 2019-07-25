 
#include "NT8003.h"
#include "controller.h"
#include "xycnbus.h"
#include "basic.h"	
#include "record_manage.h"
#include "record_status.h"
#include "sys_init.h"
#include "led.h"
//�������¼�ת����
CHANGE_EVENT_TYPE const C_EVENT_CHANGE_LIST_NT8003[]=
{
//�����౨��
	{NT_EV_FIRE,					RECORD_FIRE,				INT_TYPE_FIRE_ALARM},//��
	{NT_EV_START,					RECORD_START,				INT_TYPE_START_SUCESS},//����
	{NT_EV_FEEDBACK,				RECORD_ANSWER,				INT_TYPE_DEVICE_START_FEED_SUC},//����
	{NT_EV_MONITOR,					RECORD_MONITER,				INT_TYPE_MONITOR_ALARM},//���
	{NT_EV_COMPONENT_FAULT,			RECORD_FAULT,				INT_TYPE_REG_DEV_OFFLINE},//�豸����
	{NT_EV_MODULE_FAULT,			RECORD_FAULT,				INT_TYPE_REG_DEV_OFFLINE},//�豸����
	{NT_EV_MODULE_STOP,				RECORD_STOP,				INT_TYPE_STOP_SUCESS},//ֹͣ
	{NT_EV_FEEDBACK_CANCLE,			RECORD_CLEAR,				INT_TYPE_DEVICE_STOP_FEED_SUC},//����ֹͣ
	{NT_EV_MONITOR_CANCLE,			RECORD_FREE,				INT_TYPE_MONITOR_ALARM_FREE},//����ͷ�
	{NT_EV_FAULT_ELIMINALE,			RECORD_ELIMINATE,			INT_TYPE_REG_DEV_ONLINE},//�豸����
	
//��·����
	

//��������

};


//�������豸����ת����
NT_DEV_TYPE const C_DEV_CHANGE_LIST_NT8003[]=
{
	{NT_DEV_TEMPERATURE,						0x1f},//����
	{NT_DEV_SMOKE,								0x2a},//����
	{NT_DEV_TEMPERATURE_SMOKE,					0x33},//���¸���
	{NT_DEV_INFRARED,							0x3e},//���ͺ���
	{NT_DEV_ULTRAVIOLET,						0x3d},//��������
	{NT_DEV_GAS,								0x0b},//��ȼ����
	{NT_DEV_INFRARED_LIGHT,						0x2b},//�������
	{NT_DEV_LINEAR_TEMPERATURE,					0x22},//���Ը���
	{NT_DEV_INPUT,								0x00},//��������ģ��
	{NT_DEV_MANNUAL_BUTTON,						0x17},//�ֱ�
	{NT_DEV_SIGNAL_INPUT,						0x55},//�ź�����
	{NT_DEV_PULSE_OUTPUT,						0x56},//�������
	{NT_DEV_VOLTAGE_OUTPUT,						0x56},//��ƽ���
	{NT_DEV_BROADCAST,							0x94},//�㲥
	{NT_DEV_ALARM,								0x7d},//����
	{NT_DEV_HYDRANT_PUMP,						0x5b},//����˨��
	{NT_DEV_SPRAY_PUMP,							0x5f},//���ܱ�
	{NT_DEV_STABILIZING_PUMP,					0x64},//��ѹ��
	{NT_DEV_WATER_CURTAIN_PUMP,					0xbf},//ˮĻ��
	{NT_DEV_DELUGE_PUMP,						0xc0},//���ܱ�
	{NT_DEV_FOAM_PUMP,							0x69},//��ĭ��
	{NT_DEV_DRAFT_FAN,							0x6e},//���̻�
	{NT_DEV_FORCED_DRAFT_FAN,					0xc3},//�ͷ��
	{NT_DEV_NEW_FAN,							0xc2},//�·��
	{NT_DEV_AIR_PUMP,							0xbc},//��ѹ��
	{NT_DEV_FIRE_DAMPER,						0xb2},//����
	{NT_DEV_SMOKE_DAMPER,						0xc5},//���̷�
	{NT_DEV_BLOW_VALVE,							0x00},//�ͷ緧
	{NT_DEV_ELECTROMAGNETIC_VALVE,				0xb6},//��ŷ�
	{NT_DEV_SMOKE_CONREOL_VALVE,				0x00},//�����̷�
	{NT_DEV_WATER_CURTAIN_ELECTROMAGNETIC,		0xb9},//ˮĻ���
	{NT_DEV_DELUGE_VALVE,						0xba},//���ܷ�
	{NT_DEV_ELEVATOR,							0x77},//����
	{NT_DEV_AIR_CONDITION_UNIT,					0x96},//�յ�����
	{NT_DEV_DIESEL_GENERATOR,					0x97},//���ͷ���
	{NT_DEV_LIGHT_DSITRIBUTION,					0x98},//�������
	{NT_DEV_MOTIVE_ELECTRICITY,					0x99},//�������
	{NT_DEV_FLOOR_LIGHT,						0x00},//��ŵ�
	{NT_DEV_EMERHENCY_LIGHT,					0xb5},//Ӧ������
	{NT_DEV_EVACUATION_INSTRUCTION,				0x7c},//��ɢָʾ
	{NT_DEV_HARF_FIRE_CURTAIN,					0xb3},//�뽵����
	{NT_DEV_FIRE_CURTAIN,						0xb4},//ȫ������
	{NT_DEV_FIRE_DOOR,							0x66},//������
	{NT_DEV_MULTILINE_DISK,						0x00},//������
	{NT_DEV_ALARM_OUTPUT,						0x00},//�������
	{NT_DEV_BROADCAST_MODULE,					0x00},//�㲥ģ��
	{NT_DEV_REGULAR_PULSE_MODULE,				0x57},//��������
	{NT_DEV_REGULAR_VOLTAGE_MODULE,				0x57},//�����ƽ
	{NT_DEV_REGULAR_BROADCAST,					0x00},//����㲥
	{NT_DEV_START_BUTTON,						0x00},//������ť
	{NT_DEV_STOP_BUTTON,						0x00},//ֹͣ��ť
	{NT_DEV_SPRAY_MODULE,						0xa6},//����ģ��
	{NT_DEV_GAS_FIRE_EXTINGUISHING_CONTROLL,	0x00},//���������
	{NT_DEV_BURGLAR_DETECTOR,					0x00},//����̽����
	{NT_DEV_FIRE_DISPLAY_PANEL,					0x16},//������ʾ��
	{NT_DEV_FIRE_HYDRANT_BUTTOON,				0x18},//����˨��ť
	{NT_DEV_MONITOR_INPUT_MODULE,				0x00},//�������ģ��
	{NT_DEV_PRESSURE_SWITCH,					0x63},//ѹ������
	{NT_DEV_WATER_FLOW_INDICATOR,				0x60},//ˮ��ָʾ
	{NT_DEV_OVERHEAD_WATER_TANK,				0x5c},//��λˮ��
	{NT_DEV_SIGNAL_VALVE,						0x61},//�źŵ���
	{NT_DEV_FIRE_POWER,							0x00},//������Դ
	{NT_DEV_CONTR_POWER,						0x1a},//������Դ
};


//�豸����ת��
UINT8 NT8003_Change_DeviceType(UINT8 nt_device)
{
	UINT8 i,device_num,ts_type;

	device_num = sizeof(C_DEV_CHANGE_LIST_NT8003)/sizeof(NT_DEV_TYPE);
	for(i=0;i<device_num;i++)
	{
		if(C_DEV_CHANGE_LIST_NT8003[i].nt_dev_type == nt_device)
		{
			ts_type = C_DEV_CHANGE_LIST_NT8003[i].ts_dev_type;
			break;
		}
	}

	if(i >= device_num)//δ֪�豸
	{
		ts_type = 0x00;
	}

	return ts_type;
}

//����Ϊ�������:��ͬ�ӿڳ���洢������

void Save_Component_Info_NT8003(UINT8 *buf)
{
	UINT8 uc[3];
	UINT8 dev_type;
	RECORD_STRUCT record;

	memset(&record.Sta, 0xFF, sizeof(record));

	dev_type = NT8003_Change_DeviceType(*(buf+FRAME_DEV_TYPE_OFFSET_NT8003));
	record.EventType.word = Change_Event_Type_NT8003(*(buf+FRAME_EV_OFFSET_NT8003),&record.Type);
	if(record.EventType.word != INT_TYPE_NULL) 
	{
		//record.Type = Get_EventTypeGroup(record.EventType.word);		

		uc[0] = *(buf+FRAME_CONTR_NUM_OFFSET_NT8003);  //����
		uc[1] = *(buf+FRAME_LOOP_NUM_OFFSET_NT8003);  //��· 
		uc[2] = *(buf+FRAME_LA_OFFSET_NT8003);//��ַ��
		Hex_To_BasicUC(&record.Uc[1],&uc[0],3);
		MemoryCpyInvert(&record.Uc[1],&record.Uc[1],LEN_REG_UC-1);
		record.Uc[0] = dev_type;

		Record_Controler_If_Event(&record);
	}
}


void Save_Other_Info_NT8003(UINT8 *buf)  
{
	RECORD_STRUCT record;
		

	memset(&record.Sta, 0xFF, sizeof(record));
	
	if(*(buf+FRAME_EV_OFFSET_NT8003) == NT_EV_OTHER_FAULT)//�������¼�
	{
		if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_TRANSMIT)//�����豸
		{
			record.EventType.word = INT_TYPE_REG_DEV_OFFLINE;
			memcpy(&(record.Time),(buf+FRAME_EV_TIME_OFFSET_NT8003),6);//�����豸���߹���ʱ���֡����ȡ
			MemoryCpyInvert(&record.Time[0],&record.Time[0],6);
		}
		else if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_MAINPOWER_VOLTAGE_LOW)//����Ƿѹ
		{
			record.EventType.word = INT_TYPE_INPUT_POWER_VOLTAGE_L;
		}
		else if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_MAINPOWER)//����
		{
			record.EventType.word = INT_TYPE_INPUT_POWER_OPEN_CIRCUIT;
		}
		else if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_BACKUP_POWER)//����
		{
			record.EventType.word = INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT;
		}
	}
	else if(*(buf+FRAME_EV_OFFSET_NT8003) == NT_EV_OTHER_FAULT_ELIMINALE)//���ϻָ����¼�
	{
		if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_TRANSMIT)//�����豸
		{
			record.EventType.word = INT_TYPE_REG_DEV_ONLINE;
		}
		else if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_MAINPOWER)//����
		{
			record.EventType.word = INT_TYPE_MAINPOW_RECOVER;
		}
		else if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_BACKUP_POWER)//����
		{
			record.EventType.word = INT_TYPE_BACKUP_POWER_RECOVER;
		}
	}
	
	record.Type = Get_EventTypeGroup(record.EventType.word);

	MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
	if(*(buf+FRAME_EV_OTHER_TYPE_OFFSET_NT8003) == NT_EV_TRANSMIT)
	{
		record.Uc[0] = 0xA4;
	}
	
	Record_Controler_If_Event(&record);
}


//����Ϊ�ӿڳ���������ú���
//===============================================================================
//�޸�����: 2017-07
//��������: ����ת���¼�
//����            : src_event���������ݵ��¼� ;record_typeת�����¼����;
//����ֵ      : Ϊ��ϸ�¼�����
//�޸���Ա: ����
//===============================================================================

UINT16 Change_Event_Type_NT8003(UINT8 src_event,UINT8 *record_type)
{
	UINT16 dest_event = 0xffff;
	UINT16 k,eventNum;

	eventNum = sizeof(C_EVENT_CHANGE_LIST_NT8003)/sizeof(CHANGE_EVENT_TYPE);
	for(k=0; k < eventNum; k++)
	{
		if(C_EVENT_CHANGE_LIST_NT8003[k].SrcEventType == src_event)
		{
			dest_event = C_EVENT_CHANGE_LIST_NT8003[k].DestEventType;
			break;
		}
	}
	if(k == eventNum)
	{ 
		dest_event = INT_TYPE_NULL;
	}
	else
	{
		(*record_type) = C_EVENT_CHANGE_LIST_NT8003[k].RecordType;//Get_EventTypeGroup(dest_event);
	}
	return dest_event;
}


void Send_Answer_Frame_NT8003(CONTR_IF *buf)
{
	buf->T.Buf[buf->T.Tail] = FRAME_ANSWER_NT8003;
	buf->T.Tail += 1;
}


UINT8 Analyse_NT8003(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_head2_loc,head_end_loc,fr_len_loc,fr_end_loc,cs_initial_value,xor_initial_value=0; 
	UINT8 count,data_len,frame_total_len,xor_offset_loc,cs_offset_loc,ope_flag=0;

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
				if(buf->R.Buf[i] == FRAME_HEAD1_NT8003)
				{
					buf->R.Clev = i;
					break;
				}
				if(++i == CONTR_BUF_LEN)
				{
					i = 0;
				}
			}
			//����һȦ��δ�ҵ�֡ͷ
			if(i == buf->R.Head)
			{
				buf->R.Clev = buf->R.Head;
				buf->R.FrameEndLoc = buf->R.Head;
				break;
			}
			//���ֽ�֡ͷ��ȷ������
			head_end_loc = buf->R.Clev + FRAME_HEAD_LEN_NT8003;
			if(head_end_loc >= CONTR_BUF_LEN)
			{
				head_end_loc -= CONTR_BUF_LEN;
			}

			if(head_end_loc > buf->R.Clev)
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head < head_end_loc)) break;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head < head_end_loc)) break;
			}

			fr_head2_loc = buf->R.Clev+1;
			if(fr_head2_loc >= CONTR_BUF_LEN)
			{
				fr_head2_loc -= CONTR_BUF_LEN;
			}
			if(buf->R.Buf[fr_head2_loc] == FRAME_HEAD2_NT8003)
			{
				buf->AnalyseSta = FRAME_LEN;
				Contr.ComFault.Count = 0;
			}
			else
			{
				buf->R.Clev++;
				break;
			}
						
			

		case FRAME_LEN:
			//����֡��������λ��
			fr_len_loc = buf->R.Clev+FRAME_LEN_OFFSET_NT8003;
			if(fr_len_loc >= CONTR_BUF_LEN)
			{
				fr_len_loc -= CONTR_BUF_LEN;
			}
			//ȷ���յ�֡����
			if(fr_len_loc > buf->R.Clev)
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head <= fr_len_loc)) break;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head <= fr_len_loc)) break;
			}

			//��ȡ֡����//�ɼ�����������
			data_len = buf->R.Buf[fr_len_loc];
			
			//�жϸ�֡�Ƿ���תȦ
			fr_end_loc = (buf->R.Clev+data_len+FRAME_EXCEPT_DATA_LEN_NT8003);
			if(fr_end_loc >= CONTR_BUF_LEN)
			{
				fr_end_loc -= CONTR_BUF_LEN;
			}

			frame_total_len = data_len + FRAME_EXCEPT_DATA_LEN_NT8003;
			
			buf->R.FrameLen = frame_total_len;
			buf->R.FrameEndLoc = fr_end_loc;
			buf->AnalyseSta = FRAME_DATA;

		case FRAME_DATA://ȷ��һ֡�������
			fr_end_loc = buf->R.FrameEndLoc;
			if(fr_end_loc > buf->R.Clev)//û��תȦ
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head < fr_end_loc)) break;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head < fr_end_loc)) break;
			}
			buf->AnalyseSta = FRAME_CS;

		case FRAME_CS:
			Watch_Dog();
			//����CRCУ��
			cs_initial_value = FRAME_CS_INIT_VALUE_NT8003;
			xor_initial_value = FRAME_XOR_INIT_VALUE_NT8003;
			cs_offset_loc = FRAME_CS_OFFSET_NT8003;
			xor_offset_loc = FRAME_XOR_OFFSET_NT8003;
			frame_total_len = buf->R.FrameLen;
			data_loc = buf->R.Clev;

			for(count=0; count<frame_total_len; count++)
			{
				buf->DAT_Return[count] = buf->R.Buf[data_loc];
				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ

				if((count >= FRAME_CS_XOR_START_OFFSET_NT8003) && (count < frame_total_len))
				{
					cs_initial_value += buf->DAT_Return[count];
					xor_initial_value ^= buf->DAT_Return[count];
				}
			}
			if(((UINT8)cs_initial_value == buf->DAT_Return[cs_offset_loc])
				&& ((UINT8)xor_initial_value == buf->DAT_Return[xor_offset_loc]))
			{				
				ope_flag = TRUE;
			}
			else
			{
				buf->R.Clev++;
				memset(buf->DAT_Return,0x00,sizeof(buf->DAT_Return));
			}
			buf->AnalyseSta = FRAME_HEAD;
			break;

		default:
			buf->AnalyseSta = FRAME_HEAD;
			break;
	}
	return ope_flag;
}



void Handle_NT8003_ZJ(CONTR_IF *buf)
{
	UINT8 ev_type;//��������

	ev_type = buf->DAT_Return[FRAME_EV_OFFSET_NT8003];
	switch(ev_type)
	{
		case NT_EV_FIRE:
		case NT_EV_START:
		case NT_EV_FEEDBACK:
		case NT_EV_MONITOR:
		case NT_EV_COMPONENT_FAULT:
		case NT_EV_MODULE_FAULT:
		case NT_EV_MODULE_STOP:
		case NT_EV_FEEDBACK_CANCLE:
		case NT_EV_MONITOR_CANCLE:
		case NT_EV_FAULT_ELIMINALE:
			Save_Component_Info_NT8003(&buf->DAT_Return[0]);
			break;

		case NT_EV_RESET:
			Save_Controller_Self_Info(RECORD_RESET,INT_TYPE_RESET_SUCESS);			
			break;
		
		case NT_EV_OTHER_FAULT:
		case NT_EV_OTHER_FAULT_ELIMINALE:
			Save_Other_Info_NT8003(&buf->DAT_Return[0]);
			break;

		case NT_EV_POLL://������ͳһӦ��
			break;
		
		default:
			break;

	}
	//��֡�ܳ���=���ݰ��г���+��ͷ+У��+������
	buf->R.Clev = buf->R.FrameEndLoc;
	buf->R.FrameLen = 0;

	Monitor_Controller_Fault_Eliminate();
}


//===============================================================================
//��������: ����������ͨѶ����
//�������: ��
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================

void Com_Task_NT8003_ZJ(CONTR_IF *buf)
{
	if(Analyse_NT8003(buf))
	{
		Handle_NT8003_ZJ(buf);
		Send_Answer_Frame_NT8003(buf);
		On_Led_Contor();
	}
}

