
#include "PTW3300.h"
#include "sys_init.h"
#include "ff.h"
#include "record_manage.h"
#include "xycnbus.h"
#include "record_status.h"
#include "led.h"
//=============================================================================
//��������: UNICODE����תΪGB2312����
//�������: dest:��Ҫת���ĵ�ַ��len:���ݳ���
//�������: ת����洢��ԭ��ַ
//�޸�����: 2018-4
//�޸���Ա:  
//=============================================================================
void PTW3300_Unicode_Change_GB2312(UINT8 *dest,UINT16 len)
{
	UINT16 data_offset=0;
	UWORD_UChAR unicode;
	UWORD_UChAR gbcode;
	
	while(data_offset<len)
	{
		unicode.two[1] = *(dest+data_offset);
		unicode.two[0] = *(dest+data_offset+1);
		if(unicode.two[1]	!=	0x00)
		{
			gbcode.one = ff_uni2oem(unicode.one ,FF_CODE_PAGE);
			*(dest+data_offset)   = gbcode.two[1];//save high
			*(dest+data_offset+1) = gbcode.two[0];//save low
			data_offset += 2;
		}
		else//ASCII�벻��ת��
		{
			data_offset +=2;
		}
	}

}

//===============================================================================
//��������: �������ݷ���--����ģʽ
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
UINT8 Analyse_PTW3300_Jt(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_end_loc,fr_tail_loc,count,frame_total_len; 
	UINT8 ope_flag=0;

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
				if((buf->R.Buf[i] == FRAME_HEAD_FIRE_PTW3300) || 
					(buf->R.Buf[i] == FRAME_HEAD_FAULT_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_MONITER_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_SHIELD_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_RESET_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_VERIFY_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_RESUME_PTW3300)||
					(buf->R.Buf[i] == FRAME_HEAD_RELEASE_PTW3300)

				
				)//�¼�Ӧ��
				{
					buf->R.Clev = i; 
					break;
				}
				if(++i >= CONTR_BUF_LEN) i=0;
			}
			if(i == buf->R.Head )  //����һȦ��δ�ҵ�֡ͷ    
			{
				buf->R.Clev = buf->R.Head;
        		buf->R.FrameEndLoc = buf->R.Head; 
				break;
			}

			buf->AnalyseSta = FRAME_LEN;
			
		case FRAME_LEN:
			

			fr_end_loc = buf->R.Clev+FRAME_LEN_PTW3300;
			
			if(fr_end_loc >= CONTR_BUF_LEN)
			{
				fr_end_loc -= CONTR_BUF_LEN;
			}

			buf->R.FrameLen = FRAME_LEN_PTW3300;
			buf->R.FrameEndLoc = fr_end_loc;
			buf->AnalyseSta = FRAME_DATA;

				
		case FRAME_DATA: //ȷ���Ƿ�����һ֡����
			//ʹ�ø�֡����λ���ж�����һ֡������������ֽ��ۼ�
			fr_end_loc = buf->R.FrameEndLoc;
			if(fr_end_loc > buf->R.Clev)
			{
				if((buf->R.Head > buf->R.Clev) && (buf->R.Head < fr_end_loc)) break ;
			}
			else
			{
				if((buf->R.Head > buf->R.Clev) || (buf->R.Head < fr_end_loc)) break ;
			}
			buf->AnalyseSta = FRAME_CS;
			
		case FRAME_CS:   //У��
			Watch_Dog();
			data_loc = buf->R.Clev;
			frame_total_len = buf->R.FrameLen;
			if(buf->R.FrameEndLoc > 0)
			{
				fr_tail_loc = buf->R.FrameEndLoc - 1;
			}
			else
			{
				fr_tail_loc = CONTR_BUF_LEN-1;
			}
				
			if(buf->R.Buf[fr_tail_loc]==FRAME_TAIL_PTW3300)
			{
				for(count=0; count<frame_total_len; count++)
				{
					buf->DAT_Return[count] = buf->R.Buf[data_loc];
					if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ
				}
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


//UC��ʽ M004L02D019 
void Get_Uc_PTW3300(UINT8 *uc,UINT8 *buf)
{
	uint16 uc_loc;
	uc_loc = 298;
	
	memset(uc,0xFF,LEN_REG_UC);

	uc_loc +=1;
	if(buf[uc_loc]=='N')
	{
		uc_loc += 2;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		uc_loc += 2;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] += (buf[uc_loc]-'0');
		}
		uc_loc += 2;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[3] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		uc_loc += 2;
	}
	if(buf[uc_loc]==0x20)//����������
	{
		uc[0] = DEV_TYPE_CONTROL_UC;
		uc[1] = System.ctr_addr[3];
		uc[2] = System.ctr_addr[2];
		uc[3] += (System.ctr_addr[1]&0x0F);
	}
	else//�ڵ�����
	{
		if(buf[uc_loc]=='L')
		{
			uc_loc += 2;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[3] += (buf[uc_loc]-'0');
			}
			uc_loc += 2;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[2] = ((buf[uc_loc]-'0')<<4)&0xF0;
			}
			uc_loc += 2;
		}
		if((buf[uc_loc] == 'M')||(buf[uc_loc] == 'D'))
		{
			if(buf[uc_loc] == 'M')
			{
				uc[0]= 0X57;
			}
			uc_loc += 2;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[2] += (buf[uc_loc]-'0');
			}
			uc_loc += 2;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[1] = ((buf[uc_loc]-'0')<<4)&0xF0;
			}
			uc_loc += 2;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[1] += (buf[uc_loc]-'0');
			}
		}
		if(strstr((const char*)&buf[218],(const char*)"�̸�")  != NULL)
		{
			uc[0]= 0X2A;
		}
		/*else if(strstr((const char*)&buf[218],(const char*)"�¸�")  != NULL)
		{
			uc[0]= 0X1F;
		}*/
		else if(strstr((const char*)&buf[218],(const char*)"�ֶ�������ť")  != NULL)
		{
			uc[0]= 0X17;
		}
		/*else if(strstr((const char*)&buf[218],(const char*)"�ð�ť")  != NULL)
		{
			uc[0]= 0X18;
		}*/
		else if(strstr((const char*)&buf[218],(const char*)"���ټ���")  != NULL)
		{
			uc[0]= 0X57;
		}
	}
}
//=============================================================================
//��������: ��ȡ�豸����ɾ��UNICODE����ASCII��00
//�������: cc:��ȡ����Ŀ�ĵ�ַ��buf:��ȡԭ��ַ
//�������: 
//�޸�����: 2018-4
//�޸���Ա:  
//=============================================================================

void Get_CC_PTW3300(UINT8 *cc,UINT8 *buf)
{
	uint8 i,data_offset=0;
	for(i=0;i < LEN_REG_CC;i++)
	{
		if(*(buf+data_offset)!=0x00)
		{
			*(cc+i)= *(buf+data_offset);
		}
		else
		{
			if(*(buf+data_offset+1)==0x20)
			{
				break;
			}
			else
			{
				data_offset++;
				*(cc+i)= *(buf+data_offset);
			}
		}
		data_offset++;
	}
	
	MemoryCpyInvert(cc,cc,LEN_REG_CC);
}
//===============================================================================
//��������: �洢����Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Fire_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"���ֱ���")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		if(record.Uc[0] == 0X2A)
		{
			record.EventType.word =INT_TYPE_SMOKE_ALARM;
			record.Type = RECORD_FIRE;
		}
		else if(record.Uc[0] == 0X1F)
		{
			record.EventType.word =INT_TYPE_TEMPERATURE_ALARM;
			record.Type = RECORD_FIRE;
		}
		else if(record.Uc[0] == 0X17)
		{
			record.EventType.word =INT_TYPE_MANUAL_ALARM;
			record.Type = RECORD_FIRE;
		}
		else
		{
			record.EventType.word =INT_TYPE_ALARM;
			record.Type = RECORD_FIRE;
		}
		Record_Controler_If_Event(&record);
	}
    else if((strstr((const char*)buf,(const char*)"�𾯹��������")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		if((strstr((const char*)buf,(const char*)"������Դ����")  != NULL))
		{
			Get_CC_PTW3300(record.Cc,&buf[164]);
			record.EventType.word =INT_TYPE_MAINPOW_RECOVER;
			record.Type = RECORD_ELIMINATE;
		}
		else if((strstr((const char*)buf,(const char*)"��·")  != NULL))
		{
		
			Get_CC_PTW3300(record.Cc,&buf[80]);
			record.EventType.word =INT_TYPE_BUS_VOLTAGE_L;
			record.Type = RECORD_ELIMINATE;
		}

		else
		{
			Get_CC_PTW3300(record.Cc,&buf[80]);
			record.EventType.word =INT_TYPE_DEV_RECOVER_NOMAL;
			record.Type = RECORD_ELIMINATE;
		}
		
		Record_Controler_If_Event(&record);
	}
}

//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Fault_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"��������")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		if((strstr((const char*)buf,(const char*)"������Դ����")  != NULL))
		{
			Get_CC_PTW3300(record.Cc,&buf[164]);
			record.EventType.word =INT_TYPE_INPUT_POWER_FAULT;
			record.Type = RECORD_FAULT;
		}
		else if((strstr((const char*)buf,(const char*)"��·")  != NULL))
		{
			Get_CC_PTW3300(record.Cc,&buf[80]);			
			record.EventType.word =INT_TYPE_BUS_VOLTAGE_L;
			record.Type = RECORD_FAULT;
		}

		else
		{
			Get_CC_PTW3300(record.Cc,&buf[80]);			
			record.EventType.word =INT_TYPE_DEV_FAULT;
			record.Type = RECORD_FAULT;
		}
		
		Record_Controler_If_Event(&record);
	}
	else if((strstr((const char*)buf,(const char*)"�����豸�������ܹ��������")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);		
		record.EventType.word =INT_TYPE_REQ_RELEASE;
		record.Type = RECORD_RELEASE;
		Record_Controler_If_Event(&record);
	}

	else if((strstr((const char*)buf,(const char*)"����")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);		
		record.EventType.word =INT_TYPE_REQ_SHIELD;
		record.Type = RECORD_SHIELD;

		Record_Controler_If_Event(&record);
	}
}


//===============================================================================
//��������: �洢�����Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Moniter_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"����ź�")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		if((strstr((const char*)buf,(const char*)"���")  != NULL))
		{
			record.EventType.word =INT_TYPE_MONITOR_ALARM_FREE;
			record.Type = RECORD_FREE;
		}
		else
		{
			record.EventType.word =INT_TYPE_MONITOR_ALARM;
			record.Type = RECORD_MONITER;
		}

		Record_Controler_If_Event(&record);
	}
}


//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Shield_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"����")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);		
		record.EventType.word =INT_TYPE_REQ_SHIELD;
		record.Type = RECORD_SHIELD;

		Record_Controler_If_Event(&record);
	}
	
	else if((strstr((const char*)buf,(const char*)"��������")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);			
		record.EventType.word =INT_TYPE_DEV_FAULT;
		record.Type = RECORD_FAULT;
		Record_Controler_If_Event(&record);
	}
	else if((strstr((const char*)buf,(const char*)"�𾯹��������")  != NULL))
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		record.EventType.word =INT_TYPE_DEV_RECOVER_NOMAL;
		record.Type = RECORD_ELIMINATE;
		Record_Controler_If_Event(&record);
	}
}


//===============================================================================
//��������: �洢��λ��Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Reset_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"ϵͳ��λ")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);		
		record.EventType.word =INT_TYPE_RESET_SUCESS;
		record.Type = RECORD_RESET;

		Record_Controler_If_Event(&record);
	}
}


//===============================================================================
//��������: �洢Ԥ����Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Verify_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"Ԥ��")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		record.EventType.word =INT_TYPE_PRE_ALARM;
		record.Type = RECORD_EARLYFIRE;

		Record_Controler_If_Event(&record);
	}
}



//===============================================================================
//��������: �洢�ָ���Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Resume_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"Ԥ�����ѽ��")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		record.EventType.word =INT_TYPE_EARLY_ALARM_RESET;
		record.Type = RECORD_RESUME;

		Record_Controler_If_Event(&record);
	}
	else
	{
		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		record.EventType.word =INT_TYPE_PRE_ALARM;
		record.Type = RECORD_EARLYFIRE;

		Record_Controler_If_Event(&record);
	}
}




//===============================================================================
//��������: �洢�ָ���Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Release_Info_PTW3300(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	PTW3300_Unicode_Change_GB2312(buf,FRAME_LEN_PTW3300);
	
	if((strstr((const char*)buf,(const char*)"���������")  != NULL))
	{

		Get_Uc_PTW3300(record.Uc,buf);
		Get_CC_PTW3300(record.Cc,&buf[80]);
		record.EventType.word =INT_TYPE_REQ_RELEASE;
		record.Type = RECORD_RELEASE;

		Record_Controler_If_Event(&record);
	}

}

void Handle_PTW3300_Jt(CONTR_IF *buf)
{

	if(buf->DAT_Return[0] == FRAME_HEAD_FIRE_PTW3300)
	{
		Save_Fire_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_FAULT_PTW3300)
	{
		Save_Fault_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_MONITER_PTW3300)
	{
		Save_Moniter_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_SHIELD_PTW3300)
	{
		Save_Shield_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_RESET_PTW3300)
	{
		Save_Reset_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_VERIFY_PTW3300)
	{
		Save_Verify_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_RESUME_PTW3300)
	{
		Save_Resume_Info_PTW3300(buf->DAT_Return);
	}
	else if(buf->DAT_Return[0] == FRAME_HEAD_RELEASE_PTW3300)
	{
		Save_Release_Info_PTW3300(buf->DAT_Return);
	}
	buf->R.Clev = buf->R.FrameEndLoc;
	buf->R.FrameLen = 0;

	
}


//===============================================================================
//��������: ͨѶ����--����ģʽ���������� PTW3300������ͨ��
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2018-04
//�޸���Ա: ��ĪȻ
//===============================================================================
void Com_Task_PTW3300_Jt(CONTR_IF *buf)
{

	if(Analyse_PTW3300_Jt(buf))
	{
		Handle_PTW3300_Jt(buf);
		On_Led_Contor();
	}

}

