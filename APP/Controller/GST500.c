#include "gst500.h"
#include "controller.h"
#include "gst200.h"
#include "xycnbus.h"
#include "record_manage.h"
#include "record_status.h"
#include "basic.h"
#include "sys_init.h"
#include "led.h"
//UINT8 LAST_EVENT[6];
UINT8 LAST_CTR_STA;
//===============================================================================
//��������: ׼��Ӧ������ 
//�������: bufΪ�������ӿ�;dataΪӦ������
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
void Send_Answer_Frame_GST500(CONTR_IF *buf,UINT8 data)
{
	buf->T.Buf[buf->T.Tail] = data;
	buf->T.Tail += 1;
}
//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
void Save_Alarm_Info_GST500(UINT8 *buf)
{
	UINT8 device_type;
	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

    if(*(buf+5)==0x01)
    {
    	if((*(buf+4)<=0x11)||((*(buf+4)<=0x90)&&(*(buf+4)>=0x80)))//��
    	{
    		record.Type = RECORD_FIRE;
			record.EventType.word = INT_TYPE_ALARM;//�𾯱���
    	}
		else if(*(buf+4)==0x29)//ѹ������
		{
			record.Type = RECORD_MONITER;
			record.EventType.word = INT_TYPE_MONITOR_HIGH_VOLTAGE;//��ѹ
		}
		else if(*(buf+4)==0x30)//ˮ��ָʾ
		{
			record.Type = RECORD_MONITER;
			record.EventType.word = INT_TYPE_MONITOR_HIGH_CURRENT;//����
		}
		else if(*(buf+4)==0x32)//�յ�����
		{
			record.Type = RECORD_MONITER;
			record.EventType.word = INT_TYPE_MONITOR_POWER_INTERRUPT;//�����ж�
		}
		else if(*(buf+4)==0x48)//��������
		{
			record.Type = RECORD_MONITER;
			record.EventType.word = INT_TYPE_MONITOR_THEFT_ALARM;//����
		}
		else if(*(buf+4)==0x69)//��ȼ����
		{
			record.Type = RECORD_MONITER;
			record.EventType.word = INT_TYPE_MONITOR_GAS_LEAKAGE_ALARM;//ȼ��й©
		}
		else//����
		{
			record.Type = RECORD_ANSWER;
			record.EventType.word = INT_TYPE_DEVICE_START_FEED_SUC;
		}
    }
	else if((*(buf+5)==0x02)&&(*(buf+4)>=0x12))//����
	{
		record.Type = RECORD_START;
		record.EventType.word = INT_TYPE_REQ_START;
	}
	else if((*(buf+5)==0x03)&&(*(buf+4)>=0x12))//ͣ��
	{
		record.Type = RECORD_STOP;
		record.EventType.word = INT_TYPE_REQ_STOP;
	}
	else if((*(buf+5)==0x00)||(*(buf+5)==0x10))//�����ų�
	{
		record.Type = RECORD_ELIMINATE;
		record.EventType.word = INT_TYPE_DEV_RECOVER_NOMAL;
	}
	
	device_type =BCD2Hex(*(buf+4));
	record.Uc[LEN_REG_UC-5] = Change_UC_Type_GST200(device_type);     //�豸����
	record.Uc[LEN_REG_UC-1] = System.ctr_addr[0];  //����
	record.Uc[LEN_REG_UC-2] = *(buf+1);  //¥���
	record.Uc[LEN_REG_UC-3] = *(buf+2);
	record.Uc[LEN_REG_UC-4] = *(buf+3);//ǰһλΪ¥�ţ�����λΪ�����
	
	Record_Controler_If_Event(&record);	
}
//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
void Save_Fault_Info_GST500(UINT8 *buf)
{
	UINT8 device_type;
	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

    if((*(buf+5)==0x00 )|| (*(buf+5)==0x20))//����
	{
		record.Type = RECORD_FAULT;
		record.EventType.word = INT_TYPE_DEV_FAULT;//�豸����
	}
	else if(*(buf+5)==0x01)//����
	{
		record.Type = RECORD_SHIELD;
		record.EventType.word = INT_TYPE_REQ_SHIELD;
	}
	else if((*(buf+5)==0x02 )||(*(buf+5)==0x10))//�������
	{
		record.Type = RECORD_RELEASE;
		record.EventType.word = INT_TYPE_REQ_RELEASE;
	}
	else if(*(buf+5)==0x03)//��ʱ
	{
		record.Type = RECORD_DELAY;
		record.EventType.word = INT_TYPE_MANUAL_DELAY_START;
	}
	else if(*(buf+5)==0x04)//��ʱȡ��
	{
		record.Type = RECORD_CANCEL;
		record.EventType.word = INT_TYPE_DELAY_SUC;
	}
	else if(*(buf+5)==0x05)//�Լ�
	{
		record.Type = REOCRD_SELFCHECK;
		record.EventType.word = INT_TYPE_DEVICE_SELFCHECK;
	}
	else if(*(buf+5)==0x06)//�Լ����
	{
		record.Type = REOCRD_SELFCHECK;
		record.EventType.word = INT_TYPE_SELFCHECK_OVER;
	}
	
	device_type =BCD2Hex(*(buf+4));
	record.Uc[LEN_REG_UC-5] = Change_UC_Type_GST200(device_type);     //�豸����
	record.Uc[LEN_REG_UC-1] = System.ctr_addr[0];  //����
	record.Uc[LEN_REG_UC-2] = *(buf+1);  //¥���
	record.Uc[LEN_REG_UC-3] = *(buf+2);
	record.Uc[LEN_REG_UC-4] = *(buf+3);//ǰһλΪ¥�ţ�����λΪ�����
	if(device_type==98)//��س���ʱGST500������Ĭ��98
	{
		MemoryCpyInvert(record.Uc,System.ctr_addr,LEN_REG_UC);
	}

	Record_Controler_If_Event(&record);
	
}


//===============================================================================
//��������: �洢������Ϣ
//�������: bufΪ��������
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
void Save_Other_Info_GST500(UINT8 *buf)
{
	if(LAST_CTR_STA != (*(buf+1)))
	{
		if(((*(buf+1)>>7)==0x01)&&((*(buf+1)>>7)!=(LAST_CTR_STA>>7)))//�Զ�����
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_AUTO_CONTROL_ALLOW);
		}
		if(((*(buf+1)>>7)==0x00)&&((*(buf+1)>>7)!=(LAST_CTR_STA>>7)))//�Զ���ֹ
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_AUTO_CONTROL_FORBID);
		}
		if((((*(buf+1)&0x40)>>6)==0x01)&&(((*(buf+1)&0x40)>>6)!=((LAST_CTR_STA&0x40)>>6)))//�ֶ�����
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_MANUAL_CONTROL_ALLOW);
		}
		if((((*(buf+1)&0x40)>>6)==0x00)&&(((*(buf+1)&0x40)>>6)!=((LAST_CTR_STA&0x40)>>6)))//�ֶ���ֹ
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_MANUAL_CONTROL_FORBID);
		}
		if((((*(buf+1)&0x20)>>5)==0x01)&&(((*(buf+1)&0x20)>>5)!=((LAST_CTR_STA&0x20)>>5)))//��������
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_SPRAY_ALLOW);
		}
		if((((*(buf+1)&0x20)>>5)==0x00)&&(((*(buf+1)&0x20)>>5)!=((LAST_CTR_STA&0x20)>>5)))//������ֹ
		{
			Save_Controller_Self_Info(REOCRD_MODE,INT_TYPE_SPRAY_FORBID);
		}

		
		if((*(buf+1)&0x0f)==0x01)//�������
		{
			Save_Controller_Self_Info(RECORD_FAULT,INT_TYPE_INPUT_POWER_OPEN_CIRCUIT);
		}
		if((*(buf+1)&0x0f)==0x02)//����ָ�
		{
			Save_Controller_Self_Info(RECORD_ELIMINATE,INT_TYPE_MAINPOW_RECOVER);
		}
		if((*(buf+1)&0x0f)==0x03)//�������
		{
			Save_Controller_Self_Info(RECORD_FAULT,INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT);
		}
		if((*(buf+1)&0x0f)==0x04)//����ָ�
		{
			Save_Controller_Self_Info(RECORD_ELIMINATE,INT_TYPE_BACKUP_POWER_RECOVER);
		}
		LAST_CTR_STA = (*(buf+1));
	}
}
//===============================================================================
//��������: �������ݷ���--����ģʽ
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
UINT8 Analyse_GST500_Zj(CONTR_IF *buf)
{
	UINT16 i,data_loc=0,fr_start_loc=0,fr_end_loc=0; 
	UINT8 data_len=0,ope_flag=0,cs=0,fr_end_flag=0,fr_start_flag=0;
	
	if(buf->R.Clev == buf->R.Head) 
	{
		if(Gst.gst500_timeout > 25)//100MS��ʱ���
		{
			Gst.gst500_poll_process = SEND_OVER;
		}
		return ope_flag;
	}
	if(buf->R.Clev >= CONTR_BUF_LEN)  buf->R.Clev=0;
	i = buf->R.Clev;

	if(Gst.gst500_poll_process == REC_CTR_ADDR)//���տ�������ַ
	{
		if(buf->R.Head == 0)//����ģʽֻ�������½���
		{
			buf->R.Clev = CONTR_BUF_LEN;
		}
		else
		{
			buf->R.Clev = buf->R.Head-1;
		}

		if(buf->R.Buf[buf->R.Clev] == CTR_NUMBER_L) 
		{
			ope_flag = POLL_ANS;
			buf->R.Clev = buf->R.Head;
		}
		else if(Gst.gst500_timeout  > 25)//���ճ�ʱ100ms
		{
		    Gst.gst500_poll_process = SEND_OVER;
			buf->R.Clev = buf->R.Head;
		}
		
	}
	else if(Gst.gst500_poll_process == REC_EVENT)//�����¼�֡
	{
		while(i != buf->R.Head)
		{
			if(!fr_start_flag)
			{
				if((buf->R.Buf[i] == 0xdd) || (buf->R.Buf[i] == 0xee))//����֡ͷ
				{
					fr_start_loc = i; 
					fr_start_flag = 1;
				}
			}
			if(buf->R.Buf[i] == FRAME_TAIL_GST500) //����֡β
			{
				fr_end_loc = i;
				fr_end_flag = 1;
				break;
			}
			if(++i >= CONTR_BUF_LEN) i=0;
		}

	    if(fr_start_flag)
		{
			if(fr_end_flag)//�ҵ�֡ͷ��֡β
			{
				if(fr_end_loc > fr_start_loc)
				     data_len = fr_end_loc - fr_start_loc - 2;
				else
					 data_len = CONTR_BUF_LEN + fr_end_loc - fr_start_loc - 2;
				if( data_len == 5)//���������֡����
				{
					buf->DAT_Return[0] = buf->R.Buf[fr_start_loc];//У����֡ͷ
					data_loc = fr_start_loc+FRAME_HEAD_LEN_GST500;
					if( data_loc >= CONTR_BUF_LEN)
					{
						data_loc -= CONTR_BUF_LEN;
					}
					for(i=0;i<data_len;i++)
					{
						cs += buf->R.Buf[data_loc]; 	
						buf->DAT_Return[i+1] = buf->R.Buf[data_loc];
						data_loc++;
						if( data_loc >= CONTR_BUF_LEN)
						{
							data_loc -= CONTR_BUF_LEN;
						}
					}
					if(cs == buf->R.Buf[data_loc])//У��
					{
						ope_flag = EVENT_ANS;
						buf->R.FrameEndLoc = fr_end_loc;
						buf->R.FrameLen = 6;
						buf->R.Clev = buf->R.Head;
					}
					else
					{
						buf->R.Clev = fr_end_loc;
						Gst.gst500_poll_process = SEND_OVER;
						buf->R.Clev = buf->R.Head;
					}
				}
				else//�����մ�
				{
					buf->R.Clev = fr_end_loc;
					Gst.gst500_poll_process = SEND_OVER;
				}
			}
			else//�ҵ�֡ͷ��û�ҵ�֡β��������֡
			{
				if(Gst.gst500_timeout  > 25)//��ʱ���
				{
					Gst.gst500_poll_process = SEND_OVER;
					buf->R.Clev = buf->R.Head;
				}
			}
		}
		else
		{
			if(fr_end_flag)//û��֡ͷ�������յ�֡β
    		{
				if(fr_end_loc < 3)
				{
					buf->DAT_Return[0] = buf->R.Buf[CONTR_BUF_LEN+fr_end_loc-3];
					if(fr_end_loc < 2)
					{
						buf->DAT_Return[1] = buf->R.Buf[CONTR_BUF_LEN+fr_end_loc - 2];
						if(fr_end_loc < 1)
						{
							buf->DAT_Return[2] = buf->R.Buf[CONTR_BUF_LEN+fr_end_loc - 1];
						}
					}
					else
					{
						buf->DAT_Return[1] = buf->R.Buf[fr_end_loc - 2];
						buf->DAT_Return[2] = buf->R.Buf[fr_end_loc - 1];
					}					
				}
				else
				{
					buf->DAT_Return[0] = buf->R.Buf[fr_end_loc - 3];
					buf->DAT_Return[1] = buf->R.Buf[fr_end_loc - 2];
					buf->DAT_Return[2] = buf->R.Buf[fr_end_loc - 1];
				}

				if(buf->DAT_Return[0] == 0xcb)
				{
					ope_flag = EVENT_ANS;
					buf->R.FrameLen = 2;
					buf->R.Clev = buf->R.Head;
				}
				else if((buf->DAT_Return[2] == 0xf0)||(buf->DAT_Return[2] == 0xaa)||(buf->DAT_Return[2] == 0xab))//������������Ϣ
	    		{
	    			buf->DAT_Return[0]= buf->DAT_Return[2];
	    			ope_flag = EVENT_ANS;
					buf->R.FrameLen = 1;
					buf->R.Clev = buf->R.Head;
	    		}
				else
				{
					Gst.gst500_poll_process = SEND_REC_SUCC;//ֱ�ӻ�Ӧ��
					buf->R.Clev  = fr_end_loc;
					buf->R.Clev = buf->R.Head;
				}
				
    		}
			else//û��֡ͷ��֡β���ȴ�֡ͷ��֡β
			{
				if(Gst.gst500_timeout  > 25)//��ʱ���
				{
					Gst.gst500_poll_process = SEND_OVER;
					buf->R.Clev = buf->R.Head;
				}
			}
		}
		
	}
	return ope_flag;
}

 
//===============================================================================
//��������: ͨѶ����--����ģʽ������500������ͨ��
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: ��ĪȻ
//===============================================================================
void Com_Task_GST500_Zj(CONTR_IF *buf)
{
	switch(Gst.gst500_poll_process)
	{
		case SEND_CTR_ADDR:
			Send_Answer_Frame_GST500(buf,CTR_NUMBER_L);
			Gst.gst500_poll_process = SEND_HEAD;
		break;
		case SEND_HEAD:
			Send_Answer_Frame_GST500(buf,0x00);
			Gst.gst500_poll_process = REC_CTR_ADDR;
			Gst.gst500_timeout  = 0;
			
		case REC_CTR_ADDR:
		if(Analyse_GST500_Zj(buf)==POLL_ANS)
		{
			GST_Uart_Init_Change(SPACE);			
		    Gst.gst500_poll_process = SEND_ANS;
			On_Led_Contor();
		}
		break;	
		case SEND_ANS:
			Send_Answer_Frame_GST500(buf,0x0F);
			Gst.gst500_poll_process = REC_EVENT;
			Gst.gst500_timeout  = 0;
		break;
		case REC_EVENT:
			if(Analyse_GST500_Zj(buf)==EVENT_ANS)
			{
			    Handle_GST500_Jt(buf);
				Monitor_Controller_Fault_Eliminate();
				//Gst.gst500_poll_process = SEND_REC_SUCC;
				Send_Answer_Frame_GST500 (buf,0x1F);//ֱ�ӻ�Ӧ��
				Gst.gst500_poll_process = SEND_OVER;
				B_Poll_Ctr = 0; 
			}
		break;
		case SEND_REC_SUCC:
			Send_Answer_Frame_GST500 (buf,0x1F);
			Gst.gst500_poll_process = SEND_OVER;
			B_Poll_Ctr = 0; 
		break;
		case SEND_OVER:
			
			if(B_Poll_Ctr)
			{
				B_Poll_Ctr =0;
			    Gst.gst500_poll_process = SEND_CTR_ADDR;
				GST_Uart_Init_Change(MARK);
			}
			else if(B_Reset_Ctr)//��������λ
			{	
				GST_Uart_Init_Change(MARK);
				Send_Answer_Frame_GST500(buf,CTR_NUMBER_L);
			    Send_Answer_Frame_GST500(buf,0x5F);
				B_Reset_Ctr = 0;
				buf->PollTimer = 0;
			}
			else if(B_Silence_Ctr)//����������
			{
				GST_Uart_Init_Change(MARK);			    
				Send_Answer_Frame_GST500(buf,CTR_NUMBER_L);
			    Send_Answer_Frame_GST500(buf,0x1B);
				B_Silence_Ctr = 0;
				buf->PollTimer = 0;
			}
		break;
	    default:
		    Gst.gst500_poll_process = SEND_CTR_ADDR;
		break;

	}
}

void Handle_GST500_Jt(CONTR_IF *buf)
{
	//if(memcmp(&buf->DAT_Return[0],LAST_EVENT,buf->R.FrameLen))
	//{
		if(buf->DAT_Return[0]==0xdd)//����
		{
			Save_Alarm_Info_GST500(&buf->DAT_Return[0]);	
		}
		else if(buf->DAT_Return[0]==0xee)//����
		{
			Save_Fault_Info_GST500(&buf->DAT_Return[0]);
		}
		else if(buf->DAT_Return[0]==0xcb)//����������
		{
			Save_Other_Info_GST500(&buf->DAT_Return[0]);
		}
		else if(buf->DAT_Return[0]==0xaa)//��λ
		{
			Save_Controller_Self_Info(RECORD_RESET,INT_TYPE_RESET_SUCESS);
		}
		else if(buf->DAT_Return[0]==0xab)//����
		{
			Save_Controller_Self_Info(RECORD_OTHERS,INT_TYPE_DEVICE_SILENCE);
		}
		//memcpy(LAST_EVENT,&buf->DAT_Return[0],buf->R.FrameLen);
		//buf->R.Clev = buf->R.FrameEndLoc;
	//}
	if(Contr.Type == GST500_CRT_JT)
	{
		buf->R.Clev = buf->R.FrameEndLoc;
	}
	Contr.ComFault.Count = 0;
	buf->R.FrameLen = 0;
	Poll_Controller_Init(buf);
}
//===============================================================================
//��������: �������ݷ���--����ģʽ
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: 
//===============================================================================
UINT8 Analyse_GST500_Jt(CONTR_IF *buf)
{
	UINT16 i,data_loc,fr_end_loc; 
	UINT8 count,data_len,frame_total_len,cs_offset_loc,ope_flag=0,cs_initial_value=0;

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
				if((buf->R.Buf[i] == 0xdd) || (buf->R.Buf[i] == 0xee)||(buf->R.Buf[i] == 0xcb)||(buf->R.Buf[i] == 0xaa)||(buf->R.Buf[i] == 0xf0)||(buf->R.Buf[i] == 0xab))//�¼�Ӧ��
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
			
			//����֡��������λ��
			if(buf->R.Buf[i] == 0xf0)
			{
				data_len = 0;
			}

			else if((buf->R.Buf[i] == 0xdd) || (buf->R.Buf[i] == 0xee))
			{
				data_len = 5;
			}
			else if(buf->R.Buf[i] == 0xcb)
			{
				data_len = 1;
			}
			else if(buf->R.Buf[i] == 0xaa)
			{
				data_len = 0;
			}
			else if(buf->R.Buf[i] == 0xab)
			{
				data_len = 0;
			}
			//��������֡
			
			//��ȡ֡����//�ɼ�����������
			if( data_len < FRAME_MAX_LEN_GST500)
			{
				//�жϸ�֡�Ƿ���תȦ
				if(data_len == 0)//��У��
				{
					fr_end_loc = (buf->R.Clev+data_len+FRAME_EXCEPT_DATA_LEN2_GST500);
				}
				else
				{
					fr_end_loc = (buf->R.Clev+data_len+FRAME_EXCEPT_DATA_LEN_GST500);
				}
				if(fr_end_loc >= CONTR_BUF_LEN)
				{
					fr_end_loc -= CONTR_BUF_LEN;
				}
	
				buf->R.FrameLen = data_len;
				buf->R.FrameEndLoc = fr_end_loc;
				buf->AnalyseSta = FRAME_DATA;
			}
			else
			{
				buf->R.Clev++;
				buf->AnalyseSta = FRAME_HEAD;
				break;
			}	
				
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
			//����CRCУ��
			if(buf->R.FrameLen==0)//��λ��������Ѳ��֡����
			{

				data_loc = buf->R.Clev;
				buf->DAT_Return[0]= buf->R.Buf[data_loc];
				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ
				if(buf->R.Buf[data_loc] == FRAME_TAIL_GST500)
				{ 
					if(data_loc == 0)
					{
						data_loc = CONTR_BUF_LEN;
					}
					else
						data_loc -- ;
					if((buf->R.Buf[data_loc] == 0xf0)||(buf->R.Buf[data_loc] == 0xaa)||(buf->R.Buf[data_loc] == 0xab))//������������Ϣ
		    		{
		    			buf->DAT_Return[0]= buf->R.Buf[data_loc];
						buf->R.FrameLen = 1;
						ope_flag = 0x55;
		    		}
					else
					{
					buf->R.Clev++;
					buf->AnalyseSta = FRAME_HEAD;
					break;
					}
				}
				else
				{
				buf->R.Clev++;
				buf->AnalyseSta = FRAME_HEAD;
				break;
				}
			}
			else//��CS�¼�֡����
			{
				cs_initial_value = FRAME_CS_INIT_VALUE_GST500;
				cs_offset_loc = buf->R.FrameLen+FRAME_HEAD_LEN_GST500;
				frame_total_len = buf->R.FrameLen+FRAME_HEAD_LEN_GST500;
				data_loc = buf->R.Clev;
				if(buf->R.Buf[data_loc]==0xcb)
				{
					if(buf->R.Buf[data_loc+FRAME_EXCEPT_DATA_LEN_GST500]!=FRAME_TAIL_GST500)
					{
						buf->R.Clev++;
						buf->AnalyseSta = FRAME_HEAD;
						break;
					}
				}
				
				if( data_loc >= CONTR_BUF_LEN)
				{
					data_loc -= CONTR_BUF_LEN;
				}
				for(count=0; count<frame_total_len; count++)
				{
					buf->DAT_Return[count] = buf->R.Buf[data_loc];
					if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ
			
					if((count >= FRAME_CS_START_OFFSET_GST500) && (count < cs_offset_loc))
					{
						cs_initial_value += buf->DAT_Return[count];
					}
				}
				if(buf->R.Buf[data_loc] == cs_initial_value)
				{
					ope_flag = 0x55;
				}
				else
				{
					buf->R.Clev++;
					memset(buf->DAT_Return,0x00,sizeof(buf->DAT_Return));
				}
			}
			buf->AnalyseSta = FRAME_HEAD;
		break;

		default:
			buf->AnalyseSta = FRAME_HEAD;
		break;	
	}
	return ope_flag;
}
//===============================================================================
//��������: ͨѶ����--����ģʽ������500������ͨ��
//�������: bufΪ�������ӿ�
//�������: ��
//�޸�����: 2016-10
//�޸���Ա: ��ĪȻ
//===============================================================================
void Com_Task_GST500_Jt(CONTR_IF *buf)
{

	if(Analyse_GST500_Jt(buf))
	{
		Handle_GST500_Jt(buf);
		Monitor_Controller_Fault_Eliminate();
		On_Led_Contor();
	}

}
