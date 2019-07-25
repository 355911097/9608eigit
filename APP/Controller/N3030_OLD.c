

#include "n3030_old.h"
#include "sys_init.h"
#include "xycnbus.h"
#include "record_manage.h"
#include "record_status.h"
#include "led.h"
//===============================================================================
//��������: �������ݷ���--����ģʽ
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
UINT8 Analyse_N3030_OLD_Jt(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_end_loc,fr_tail_loc; 
	UINT8 count,frame_total_len,ope_flag=0;

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
				if((buf->R.Buf[i] == FRAME_HEAD_FIRE_N3030_OLD) || 
					(buf->R.Buf[i] == FRAME_HEAD_FAULT_N3030_OLD)||
					(buf->R.Buf[i] == FRAME_HEAD_ANSWER_N3030_OLD)||
					(buf->R.Buf[i] == FRAME_HEAD_SHIELD_N3030_OLD)||
					(buf->R.Buf[i] == FRAME_HEAD_RESUME_N3030_OLD))//�¼�Ӧ��
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
			

			fr_end_loc = buf->R.Clev+FRAME_LEN_N3030_OLD;
			
			if(fr_end_loc >= CONTR_BUF_LEN)
			{
				fr_end_loc -= CONTR_BUF_LEN;
			}

			buf->R.FrameLen = FRAME_LEN_N3030_OLD;
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
				
			if(buf->R.Buf[fr_tail_loc]==FRAME_TAIL_N3030_OLD)
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
void Get_Uc_N3030_OLD(UINT8 *uc,UINT8 *buf)
{
	uint8 uc_loc;
	uc_loc = 151;
	
	memset(uc,0xFF,LEN_REG_UC);	
	if(buf[uc_loc]=='N')
	{
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] += (buf[uc_loc]-'0');
		}
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[3] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		uc_loc +=1;
		if(buf[uc_loc]=='L')
		{
			uc_loc +=1;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[3] += (buf[uc_loc]-'0');
			}
			uc_loc +=1;
			if((buf[uc_loc] >= '0') && (buf[uc_loc ] <= '9'))
			{
				uc[2] = ((buf[uc_loc]-'0')<<4)&0xF0;
			}
		}
		uc_loc +=1;
		if((buf[uc_loc] == 'M')||(buf[uc_loc] == 'D'))
		{
			if(buf[uc_loc] == 'M')
			{
				uc[0]= 0X57;
			}
			uc_loc +=1;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[2] += (buf[uc_loc]-'0');
			}
			uc_loc +=1;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[1] = ((buf[uc_loc]-'0')<<4)&0xF0;
			}
			uc_loc +=1;
			if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
			{
				uc[1] += (buf[uc_loc]-'0');
			}
		}
	}
	else if(buf[uc_loc+7]=='N')
	{
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[4] += (buf[uc_loc]-'0');
		}
		uc_loc +=1;
		if((buf[uc_loc] >= '0') && (buf[uc_loc] <= '9'))
		{
			uc[3] = ((buf[uc_loc]-'0')<<4)&0xF0;
		}
		
		uc[0] = DEV_TYPE_CONTROL_UC;
		uc[1] = System.ctr_addr[3];
		uc[2] = System.ctr_addr[2];
		uc[3] += (System.ctr_addr[1]&0x0F);

	}
	else
	{
		memset(uc,0xFF,LEN_REG_UC);
	}

}

//===============================================================================
//��������: �洢����Ϣ
//�������: bufΪ�������ݸ�ʽ 6B 7E A5 66
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Fire_Info_N3030_OLD(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	if((buf[0] == 0x6B)&&(buf[1] == 0x7E)&&(buf[2] == 0xA5)&&(buf[3] == 0x66))
	{

		Get_Uc_N3030_OLD(record.Uc,buf);

		record.EventType.word =INT_TYPE_ALARM;
		record.Type = RECORD_FIRE;
		
		Record_Controler_If_Event(&record);
	}
}
//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ�������ݸ�ʽ 45 9C
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Fault_Info_N3030_OLD(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	if((buf[0] == 0x45)&&(buf[1] == 0x9C))
	{

		Get_Uc_N3030_OLD(record.Uc,buf);

		record.EventType.word =INT_TYPE_DEV_FAULT;
		record.Type = RECORD_FAULT;
		
		Record_Controler_If_Event(&record);
	}
}
//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ�������ݸ�ʽ 45 9C
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Moniter_Info_N3030_OLD(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	if((buf[0] == 0xD1)&&(buf[1] == 0xA1))
	{

		Get_Uc_N3030_OLD(record.Uc,buf);

		record.EventType.word = INT_TYPE_MONITOR_ALARM;
		record.Type = RECORD_MONITER;
		
		Record_Controler_If_Event(&record);
	}
}

//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ�������ݸ�ʽ F2 AB 94 BB
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Shield_Info_N3030_OLD(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	if((buf[0] == 0xF2)&&(buf[1] == 0xAB)&&(buf[2] == 0x94)&&(buf[3] == 0xBB))
	{

		Get_Uc_N3030_OLD(record.Uc,buf);

		record.EventType.word =INT_TYPE_REQ_SHIELD;
		record.Type = RECORD_SHIELD;
		
		Record_Controler_If_Event(&record);
	}
}
//===============================================================================
//��������: �洢״̬ȡ����Ϣ
//�������: bufΪ�������ݸ�ʽ 05 64
//�������: ��
//�޸�����: 2018-4
//�޸���Ա: 
//===============================================================================
void Save_Resume_Info_N3030_OLD(UINT8 *buf)
{

	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

	if((buf[0] == 0x05)&&(buf[1] == 0x64))
	{
		if((buf[3] == 0xF2)&&(buf[4] == 0xAB)&&(buf[5] == 0x94)&&(buf[6] == 0xBB))
		{
			Get_Uc_N3030_OLD(record.Uc,buf);

			record.EventType.word =INT_TYPE_REQ_RELEASE;
			record.Type = RECORD_RELEASE;
			
			Record_Controler_If_Event(&record);
		}
		else if((buf[3] == 0xD1)&&(buf[4] == 0xA1))
		{
			Get_Uc_N3030_OLD(record.Uc,buf);

			record.EventType.word =INT_TYPE_MONITOR_ALARM_FREE;
			record.Type = RECORD_FREE;
			
			Record_Controler_If_Event(&record);
		}
		else 
		{
			Get_Uc_N3030_OLD(record.Uc,buf);

			record.EventType.word =INT_TYPE_DEV_RECOVER_NOMAL;
			record.Type = RECORD_ELIMINATE;
			
			Record_Controler_If_Event(&record);
		}
	}
}



void Handle_N3030_OLD_Jt(CONTR_IF *buf)
{
	UINT8 command_type;//��������
	command_type = buf->DAT_Return[0];

	if(command_type == FRAME_HEAD_FIRE_N3030_OLD)
	{
		Save_Fire_Info_N3030_OLD(buf->DAT_Return);
	}
	else if(command_type == FRAME_HEAD_FAULT_N3030_OLD)
	{
		Save_Fault_Info_N3030_OLD(buf->DAT_Return);
	}
	else if(command_type == FRAME_HEAD_ANSWER_N3030_OLD)
	{
		Save_Moniter_Info_N3030_OLD(buf->DAT_Return);
	}
	else if(command_type == FRAME_HEAD_SHIELD_N3030_OLD)
	{
		Save_Shield_Info_N3030_OLD(buf->DAT_Return);
	}
	else if(command_type == FRAME_HEAD_RESUME_N3030_OLD)
	{
		Save_Resume_Info_N3030_OLD(buf->DAT_Return);
	}
	buf->R.Clev = buf->R.FrameEndLoc;
	buf->R.FrameLen = 0;
}

//===============================================================================
//��������: ͨѶ����--����ģʽ��ŵ�ٷƶ�N3030�ϻ��Ϳ�����ͨ��
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2018-04
//�޸���Ա: ��ĪȻ
//===============================================================================
void Com_Task_N3030_OLD_Jt(CONTR_IF *buf)
{

	if(Analyse_N3030_OLD_Jt(buf))
	{
		Handle_N3030_OLD_Jt(buf);
		On_Led_Contor();
	}

}

