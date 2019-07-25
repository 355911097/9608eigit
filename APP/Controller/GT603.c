 
#include "gt603.h"
#include "controller.h"
#include "xycnbus.h"
#include "basic.h"	
#include "record_manage.h"
#include "record_status.h"
#include "sys_init.h"
#include "led.h"
//�������¼�ת����
//�¼�����ת����,�ݶ���������������
CHANGE_EVENT_TYPE const GT_GM647_EVENT_CHANGE_LIST[]=
{
	{GT_POWEROFF,					RECORD_POWERONOFF,		INT_TYPE_POWER_OFF},
	{GT_POWERON,					RECORD_POWERONOFF,		INT_TYPE_POWER_ON},
	{GT_FIRE,						RECORD_FIRE,			INT_TYPE_FIRE_ALARM},
	{GT_REG_DEV_OFFLINE,			RECORD_FAULT,			INT_TYPE_REG_DEV_OFFLINE},
	{GT_REG_DEV_ONLINE,				RECORD_ELIMINATE,		INT_TYPE_REG_DEV_ONLINE},
	{GT_CONTR_RESET,				RECORD_RESET,			INT_TYPE_RESET_SUCESS},
	{GT_MAINPOWER_VOLTAGE_L,		RECORD_FAULT,			INT_TYPE_INPUT_POWER_VOLTAGE_L},
	{GT_MAINPOWER_FAULT,			RECORD_FAULT,			INT_TYPE_INPUT_POWER_OPEN_CIRCUIT},
	{GT_MAINPOWER_RECOVER,			RECORD_ELIMINATE,		INT_TYPE_MAINPOW_RECOVER},
	{GT_MAINPOWER_VOLTAGE_RECOVER,	RECORD_ELIMINATE,		INT_TYPE_MAINPOW_RECOVER},
	{GT_BATTERY_VOLTAGE_L,			RECORD_FAULT,			INT_TYPE_BACKUP_POWER_VOLTAGE_L},
	{GT_BATTERY_FAULT,				RECORD_FAULT,			INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT},
	{GT_BATTERY_VOLTAGE_RECOVER,	RECORD_ELIMINATE,		INT_TYPE_BACKUP_POWER_RECOVER},
	{GT_BATTERY_RECOVER,			RECORD_ELIMINATE,		INT_TYPE_BACKUP_POWER_RECOVER},
	{GT_FIRE_RESTORE,				RECORD_RESUME,			INT_TYPE_EARLY_ALARM_RESET},
	{GT_MONITOR,					RECORD_MONITER,			INT_TYPE_MONITOR_ALARM},
	{GT_MONITOR_CANCLE,				RECORD_FREE,			INT_TYPE_MONITOR_ALARM_FREE},//��ʱ�Լ��ӵ��¼����������������ι�ͨ
	{GT_START,						RECORD_START,			INT_TYPE_START_SUCESS},
	{GT_STOP,						RECORD_STOP,			INT_TYPE_STOP_SUCESS},
	{GT_FEEDBACK,					RECORD_ANSWER,			INT_TYPE_DEVICE_START_FEED_SUC},
	{GT_FEEDBACK_CANCLE,			RECORD_CLEAR,			INT_TYPE_DEVICE_STOP_FEED_SUC},
	{GT_SHIELD,						RECORD_SHIELD,			INT_TYPE_SHILED_SUCESS},
	{GT_SHIELD_CANCLE,				RECORD_RELEASE,			INT_TYPE_RELEASE_SUCESS},
	{GT_MANUAL_ALLOW,				REOCRD_MODE,			INT_TYPE_MANUAL_CONTROL_ALLOW},
	{GT_MANUAL_FORBID,				REOCRD_MODE,			INT_TYPE_MANUAL_CONTROL_FORBID},
	{GT_AUTO_ALLOW,					REOCRD_MODE,			INT_TYPE_AUTO_CONTROL_ALLOW},
	{GT_AUTO_FORBID,				REOCRD_MODE,			INT_TYPE_AUTO_CONTROL_FORBID},
	
};

//�豸����ת���������豸�����ڴ����
GT_Device_Type const GT_GM647_DEVICE_CHANGE_LIST[]=
{
	{GT_BUTTON,			0x17},//�ֱ�
	{GT_SMOKE,			0x2a},//����
	{GT_TEMPERATURE,	0x1f},//����
	{GT_INOUT,			0x57},//�������
	{GT_BUSDISK,		0x8d},//������
};



//����Ϊ�������:��ͬ�ӿڳ���洢������

void Save_Component_Info_GT603(CONTR_IF * buf,UINT8 record_type,UINT8 ts_event)
{
	UINT8 a,b,i,j,k,m,n;
	UINT8 uc[3];
	UINT8 device_type;
	RECORD_STRUCT record;	

	memset(&record.Sta, 0xFF, sizeof(record));
			
	record.EventType.word = ts_event;
	device_type = GT603_Device_Get(buf);
	
	if(record.EventType.word != INT_TYPE_NULL) 
	{
		record.Type = record_type;		

		a = buf->DAT_Return[FRAME_CONRE_NUM_GM647]-0x30;
		b = buf->DAT_Return[FRAME_CONRE_NUM_GM647+1]-0x30;
		uc[0] = a*10 + b;     //����

		m = buf->DAT_Return[FRAME_LOOP_NUM_GM647]-0x30;
		n = buf->DAT_Return[FRAME_LOOP_NUM_GM647+1]-0x30;
		uc[1] = m*10 + n;  //��· 

		i = buf->DAT_Return[FRAME_LA_NUM_GM647]-0x30;
		j = buf->DAT_Return[FRAME_LA_NUM_GM647+1]-0x30;
		k = buf->DAT_Return[FRAME_LA_NUM_GM647+2]-0x30;
		uc[2] = i*100 + j*10 + k;//��ַ��
		
		Hex_To_BasicUC(&record.Uc[1],&uc[0],3);
		MemoryCpyInvert(&record.Uc[1],&record.Uc[1],LEN_REG_UC-1);
		record.Uc[0] = device_type;

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


//�豸����ת��
UINT8 GT603_Change_DeviceType(UINT8 gt_device)
{
	UINT8 i,device_num,ts_type;

	device_num = sizeof(GT_GM647_DEVICE_CHANGE_LIST)/sizeof(GT_Device_Type);
	for(i=0;i<device_num;i++)
	{
		if(GT_GM647_DEVICE_CHANGE_LIST[i].gt_type == gt_device)
		{
			ts_type = GT_GM647_DEVICE_CHANGE_LIST[i].ts_type;
			break;
		}
	}

	if(i >= device_num)//δ֪�豸
	{
		ts_type = 0x00;
	}

	return ts_type;
}


//�¼�����ת��
UINT16 GT603_Change_Event_Type(UINT8 gt_type)
{
	UINT8 i,eventnum;
	UINT16 ts_event;

	eventnum = sizeof(GT_GM647_EVENT_CHANGE_LIST)/sizeof(CHANGE_EVENT_TYPE);
	for(i=0;i<eventnum;i++)
	{
		if(gt_type == GT_GM647_EVENT_CHANGE_LIST[i].SrcEventType)
		{
			ts_event = GT_GM647_EVENT_CHANGE_LIST[i].DestEventType;
			break;
		}
	}
	if(i >= eventnum)
	{
		ts_event = INT_TYPE_NULL;
	}
	return ts_event;
}

UINT8 GT603_Event_Match(CONTR_IF * buf)
{
	UINT8 i;
	signed char result;

	//�¼�ƥ����������¼����������
	UINT8 s[18][12]=
		{
			{0xB9,0xD8,0xBB,0xFA,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},//�ػ�
			{0xBF,0xAA,0xBB,0xFA,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},//����
			{0xBB,0xF0,0xBE,0xAF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20},//��
			{0xCE,0xDE,0xCF,0xEC,0xD3,0xA6,0x20,0x20,0x20,0x20,0x20,0x20},//����Ӧ
			{0xCE,0xDE,0xCF,0xEC,0xD3,0xA6,0xBB,0xD6,0xB8,0xB4,0x20,0x20},//����Ӧ�ָ�
			{0xC8,0xED,0xB8,0xB4,0xCE,0xBB,0x20,0x20,0x20,0x20,0x20,0x20},//��λ
			{0xD6,0xF7,0xB5,0xE7,0xC7,0xB7,0xD1,0xB9,0x20,0x20,0x20,0x20},//����Ƿѹ
			{0xD6,0xF7,0xB5,0xE7,0xB9,0xCA,0xD5,0xCF,0x20,0x20,0x20,0x20},//�������
			{0xD6,0xF7,0xB5,0xE7,0xBB,0xD6,0xB8,0xB4,0x20,0x20,0x20,0x20},//����ָ�
			{0xD6,0xF7,0xB5,0xE7,0xC7,0xB7,0xD1,0xB9,0xBB,0xD6,0xB8,0xB4},//����Ƿѹ�ָ�
			{0xB1,0xB8,0xB5,0xE7,0xC7,0xB7,0xD1,0xB9,0x20,0x20,0x20,0x20},//����Ƿѹ

			{0xB1,0xB8,0xB5,0xE7,0xB9,0xCA,0xD5,0xCF,0x20,0x20,0x20,0x20},//�������
			{0xB1,0xB8,0xB5,0xE7,0xC7,0xB7,0xD1,0xB9,0xBB,0xD6,0xB8,0xB4},//����Ƿѹ�ָ�
			{0xB1,0xB8,0xB5,0xE7,0xBB,0xD6,0xB8,0xB4,0x20,0x20,0x20,0x20},//����ָ�
			{0xCA,0xD6,0xB6,0xAF,0xD4,0xCA,0xD0,0xED,0x20,0x20,0x20,0x20},//�ֶ�����
			{0xCA,0xD6,0xB6,0xAF,0xBD,0xFB,0xD6,0xB9,0x20,0x20,0x20,0x20},//�ֶ���ֹ
			{0xD7,0xD4,0xB6,0xAF,0xD4,0xCA,0xD0,0xED,0x20,0x20,0x20,0x20},//�Զ�����
			{0xD7,0xD4,0xB6,0xAF,0xBD,0xFB,0xD6,0xB9,0x20,0x20,0x20,0x20},//�Զ���ֹ
		};

	for(i=0;i<18;i++)
	{
		result = memcmp(&s[i][0],&buf->DAT_Return[FRAME_EV_OFFSET_GM647],12);

		if(result == 0) break;//ƥ�䵽�¼���ֱ���˳�ƥ��
	}

	if(result != 0)//δƥ�䵽�¼�
	{
		i = 0xFF;
	}

	return i;
}


UINT8 GT603_Device_Match(CONTR_IF * buf)
{
	UINT8 i;
	signed char result;
	//�豸����ƥ����������豸�����ڴ����
	UINT8 s[5][12]=
		{
			{0xCA,0xD6,0xB6,0xAF,0xB0,0xB4,0xC5,0xA5,0x20,0x20,0x20,0x20},//�ֱ���ť
			{0xB8,0xD0,0xD1,0xCC,0xCC,0xBD,0xB2,0xE2,0xC6,0xF7,0x20,0x20},//����̽����
			{0xB8,0xD0,0xCE,0xC2,0xCC,0xBD,0xB2,0xE2,0xC6,0xF7,0x20,0x20},//����̽����
			{0xCA,0xE4,0xC8,0xEB,0xCA,0xE4,0xB3,0xF6,0xC4,0xA3,0xBF,0xE9},//�������ģ��
			{0xC1,0xAA,0xB6,0xAF,0xBF,0xD8,0xD6,0xC6,0xC5,0xCC,0x20,0x20},//����������
		};

	for(i=0;i<5;i++)
	{
		if(buf->DAT_Return[3] != 0x03)//������
		{
			result = memcmp(&s[i][0],&buf->DAT_Return[FRAME_DEV_TYPE_OFFSET1_GM647],12);
		}
		else//��������
		{
			result = memcmp(&s[i][0],&buf->DAT_Return[FRAME_DEV_TYPE_OFFSET2_GM647],12);
		}

		if(result == 0) break;
	}

	if(result != 0)
	{
		i = 0xFF;
	}

	return i;
}


UINT16 GT603_Event_Get(CONTR_IF * buf)//��ȡ�¼�������Ϣ
{
	UINT8 gt_event;
	UINT16 ts_event;
	//ȡ�¼�����
	gt_event = GT603_Event_Match(buf);
	ts_event = GT603_Change_Event_Type(gt_event);
	return ts_event;
}


UINT8 GT603_Device_Get(CONTR_IF * buf)//��ȡ�豸����
{
	UINT8 gt_device,ts_device;
	//ȡ�豸����
	gt_device = GT603_Device_Match(buf);
	ts_device = GT603_Change_DeviceType(gt_device);
	return ts_device;
}



UINT8 Frame_Compare_GT603_SF(UINT8 *buf0,UINT8 *buf1)
{
	signed char result;
	UINT8 flag = FALSE;//֡�ȽϽ����1Ϊ��֡��ͬ��0Ϊ��֡��ͬ

	result = memcmp(buf0,buf1,125);

	if(result != 0)//����֡��ͬ�������յ�֡����֡����
	{
		memcpy(buf0,buf1,125);
		flag = TRUE;
	}
	else
	{
		flag = FALSE;
	}

	return flag;
}


void Answer_GT603_SF(CONTR_IF *buf)
{
	//�յ���Ϣ����Ӧ��0x24 0x24
	buf->T.Buf[0] = FRAME_HEAD_GM647;
	buf->T.Buf[1] = FRAME_HEAD_GM647;
	buf->T.Tail = 2;
}


UINT8 Analyse_GT603_SF(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_head2_loc,fr_len_loc,fr_end_loc,cs_initial_value=0; 
	UINT8 count,frame_total_len,cs_offset_loc,ope_flag=0;

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
				if(buf->R.Buf[i] == FRAME_HEAD_GM647)
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
						
			buf->AnalyseSta = FRAME_LEN;

		case FRAME_LEN:
			//����֡��������λ��
			fr_len_loc = buf->R.Clev+FRAME_LEN_OFFSET_GM647;
			if(fr_len_loc >= CONTR_BUF_LEN)
			{
				fr_len_loc -= CONTR_BUF_LEN;
			}
			//ȷ���յ�֡����
			if(fr_len_loc > buf->R.Clev)
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head <= fr_len_loc)) break ;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head <= fr_len_loc)) break ;
			}

			//��ȡ֡����//�ɼ�����������
			frame_total_len = buf->R.Buf[fr_len_loc];
			fr_head2_loc = buf->R.Clev+1;
			if(fr_head2_loc >= CONTR_BUF_LEN)
			{
				fr_head2_loc -= CONTR_BUF_LEN;
			}
			
			if((buf->R.Buf[fr_head2_loc] == FRAME_HEAD_GM647) 
				&& (frame_total_len == FRAME_LEN_TOTAL_GM647))
			{
				//�жϸ�֡�Ƿ���תȦ
				fr_end_loc = (buf->R.Clev+frame_total_len-1);
				if(fr_end_loc >= CONTR_BUF_LEN)
				{
					fr_end_loc -= CONTR_BUF_LEN;
				}

				buf->R.FrameLen = frame_total_len;
				buf->R.FrameEndLoc = fr_end_loc;
				buf->AnalyseSta = FRAME_DATA;
			}
			else
			{
				buf->R.Clev++;
				buf->AnalyseSta = FRAME_HEAD;
				break;
			}

		case FRAME_DATA://ȷ��һ֡�������
			fr_end_loc = buf->R.FrameEndLoc;
			if(fr_end_loc > buf->R.Clev)//û��תȦ
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head <= fr_end_loc)) break;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head <= fr_end_loc)) break;
			}
			buf->AnalyseSta = FRAME_CS;

		case FRAME_CS:
			Watch_Dog();
			//����CRCУ��
			cs_initial_value = FRAME_CS_INIT_VALUE_GM647;
			cs_offset_loc = FRAME_LEN_TOTAL_GM647-1;
			frame_total_len = buf->R.FrameLen;
			data_loc = buf->R.Clev;

			for(count=0; count<frame_total_len; count++)
			{
				buf->DAT_Return[count+128] = buf->R.Buf[data_loc];
				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ

				if(count < cs_offset_loc)
				{
					cs_initial_value += buf->DAT_Return[count+128];
				}
			}
			if((UINT8)cs_initial_value == buf->DAT_Return[cs_offset_loc+128])
			{				
				ope_flag = TRUE;
			}
			else
			{
				buf->R.Clev++;
				memset(&buf->DAT_Return[128],0x00,128);
			}
			buf->AnalyseSta = FRAME_HEAD;
			break;

		default:
			buf->AnalyseSta = FRAME_HEAD;
			break;
	}
	return ope_flag;
}



void Handle_GT603_SF_ZJ(CONTR_IF *buf)
{
	UINT16 ts_event;//�¼�����
	UINT8 record_type;//�¼�����

	ts_event = GT603_Event_Get(buf);
	record_type = Get_EventTypeGroup(ts_event);
	switch(ts_event)
	{
		case INT_TYPE_FIRE_ALARM:
		//case GT_FIRE_RESTORE:
		case INT_TYPE_REG_DEV_OFFLINE:
		case INT_TYPE_REG_DEV_ONLINE:
		//case GT_START:
		//case GT_STOP:
		//case GT_FEEDBACK:
		//case GT_FEEDBACK_CANCLE:
		//case GT_SHIELD:
		//case GT_SHIELD_CANCLE:
		//case GT_MONITOR:
		//case GT_MONITOR_CANCLE:
			Save_Component_Info_GT603(buf,record_type,ts_event);
			break;

		case INT_TYPE_POWER_ON:
		case INT_TYPE_RESET_SUCESS:
		case INT_TYPE_INPUT_POWER_OPEN_CIRCUIT:
		case INT_TYPE_MAINPOW_RECOVER:
		case INT_TYPE_INPUT_POWER_VOLTAGE_L:
		case INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT:
		case INT_TYPE_BACKUP_POWER_RECOVER:
		case INT_TYPE_BACKUP_POWER_VOLTAGE_L:
		case INT_TYPE_MANUAL_CONTROL_ALLOW:
		case INT_TYPE_MANUAL_CONTROL_FORBID:
		case INT_TYPE_AUTO_CONTROL_ALLOW:
		case INT_TYPE_AUTO_CONTROL_FORBID:
			Save_Controller_Self_Info(record_type,ts_event);
			break;
		
		default:
			break;

	}
}


//===============================================================================
//��������: ����������ͨѶ����
//�������: ��
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================

void Com_Task_GT603_SF_ZJ(CONTR_IF *buf)
{
	if(Analyse_GT603_SF(buf))
	{
		if(Frame_Compare_GT603_SF(&buf->DAT_Return[0],&buf->DAT_Return[128]))
		{
			Handle_GT603_SF_ZJ(buf);
		}

		buf->R.Clev = buf->R.FrameEndLoc;
		buf->R.FrameLen = 0;
		Answer_GT603_SF(buf);
		On_Led_Contor();
	}
}

