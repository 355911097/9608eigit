#include "EI_Print_COMM.h"
#include "controller.h"
#include "xycnbus.h"
#include "basic.h"	
#include "sys_init.h"
#include "ts.h"
#include "Rtc.h"
#include "Record_manage.h"
#include "Uart.h"
#include "led.h"

//COMMUNICATE EI_Comm;
CONTR_IF EI_Comm;

UINT8 EventSer=0;

void Parallel_Init(void)
{
    memset(&EI_Comm,0x00,sizeof(EI_Comm));
    EI_Comm.PollEnFlag=1;
}
void TS_Send_Heart_Poll(CONTR_IF * buf)//Э��ת����
{
	UINT8 i,CS_loc;
	UINT16 CS = 0xFFFF;
	UINT8 start;
	start = buf->T.Tail;

	buf->T.Buf[start] = 0x7F;
	buf->T.Buf[start+1] = 0x06;
	buf->T.Buf[start+2] = 0xF6;
	buf->T.Buf[start+3] =0xFF;
	//EventSer++;
	buf->T.Buf[start+4]= EventSer++;
	buf->T.Buf[start+5]=0x3F;
	buf->T.Buf[start+6]= 0xFF;
	
	buf->T.Tail+= (buf->T.Buf[start+1]+3);
	//buf->T.Clev=0;
	CS_loc = buf->T.Buf[start+1]+1;

	//����CRC
	for(i=0;i<CS_loc;i++)
	{
		CS = Caculate_CRC(CS,buf->T.Buf[start+i]);
	}

	buf->T.Buf[start+CS_loc] = (UINT8)(CS&0x00FF);
	buf->T.Buf[start+CS_loc+1] = (UINT8)((CS&0xFF00)>>8);

}

void TS_Send_Event(CONTR_IF * buf,UINT8 *Record_Buffer)//Э��ת����
{
	UINT8 i,CS_loc;
	UINT16 CS = 0xFFFF;
	UINT8 uc[5]={0x00,0x00,0x00,0x00,0x05};
	UINT8 start;
	
	start = buf->T.Tail;

	buf->T.Buf[start] = 0x7F;
	buf->T.Buf[start+1] = 0x37;
	buf->T.Buf[start+2] = 0xf4;
	MemoryCpyInvert(&buf->T.Buf[start+3], uc, 5);
	//EventSer++;	
	buf->T.Buf[start+8] = EventSer++;
	buf->T.Buf[start+9] = 0x38;
	memcpy(&buf->T.Buf[start+10],&Record_Buffer[1],GET_EVENT_NOMAL_LEN);
	
	buf->T.Tail += (buf->T.Buf[start+1]+3);
	//buf->T.Clev=0;
	CS_loc = buf->T.Buf[start+1]+1;

	//����CRC
	for(i = 0;i < CS_loc;i++)
	{
		CS = Caculate_CRC(CS,buf->T.Buf[start+i]);
	}

	buf->T.Buf[start+CS_loc] = (UINT8)(CS&0x00FF);
	buf->T.Buf[start+CS_loc+1] = (UINT8)((CS&0xFF00)>>8);

}
void Do_Event_Upload(UPLOAD_STRUCT *upload,UINT8 *Date_Buffer)
{
	*Date_Buffer = GET_EVENT_NOMAL_LEN; //Ĭ����ȡ����Ч�ֽڳ���
	*(Date_Buffer+1) = upload->EventType.byte[1];
	*(Date_Buffer+2) = upload->EventType.byte[0];

	memcpy(Date_Buffer+3,upload->Uc,LEN_REG_UC);
	memcpy(Date_Buffer+8,upload->Cc,LEN_REG_CC);
	memcpy(Date_Buffer+40,&upload->Time[0],6);  //yeat month data hour minuite second,������6�ֽ�
	*(Date_Buffer+46) = upload->Event[0];  //������LA:FF��������
	*(Date_Buffer+GET_EVENT_TYPE_LOC) = upload->Type;	 
	//copy_flag = 0;	
	TS_Send_Event(&RS232,Date_Buffer);
}
void Save_Fire_Info_EI_PRT_B(UINT8 *buf,UINT16 FrameLen)
{
	UINT8 devType=0x00, i, j, k, l=0;
	UINT8 uc[3];
	UINT8 Date_Buffer[128];
	UINT8 print_line_number=0, fire_line_number=0;//��ӡ����������������������������
	UINT16 line_offset[6];//ÿ�н�βƫ�Ƶ�ַ
	UINT8 floor=0, layer=0;//¥�ţ����
	UINT16 EIla=0, EIloop=0;

	UPLOAD_STRUCT upload;
	memset(&upload.Time, 0xFF, sizeof(upload));

    	
    for(i=0;i <FrameLen ;i++)//��ѯ���������Ƿ��л�
    {
        Watch_Dog();
        if(buf[i]==0xB1&&buf[i+1]==0xA8&&buf[i+2]==0xBB&&buf[i+3]==0xF0&&buf[i+4]==0xBE&&buf[i+5]==0xAF)
        {
           if(print_line_number==0)
           {
        	  // fire_offset=i;
        	   fire_line_number=1;					  
           }
           else
           {
        	   return;
           }
        }
        if(buf[i]==0x0A&&buf[i+1]==0x0D)
        {
           line_offset[print_line_number++]=i+1;//ÿ�н�β����ֵ
        }
    }
	if(print_line_number<=6)//���6�У�print_line_number�����1
    {
        if(strstr((const char*)buf,(const char*)"�ֶ�����")	 != NULL)
        {
            upload.EventType.word=INT_TYPE_MANUAL_ALARM; 
            devType=0x17;
        }
        else if(strstr((const char*)buf,(const char*)"���")  != NULL)
        {
            upload.EventType.word=INT_TYPE_SMOKE_ALARM;
            devType=0x2A;
        }
        else if(strstr((const char*)buf,(const char*)"����")  != NULL)
        {
            upload.EventType.word=INT_TYPE_TEMPERATURE_ALARM;
            devType=0x1E;

        }
        else if(strstr((const char*)buf,(const char*)"����˨")  != NULL)
        {
            upload.EventType.word=INT_TYPE_ALARM;
            devType=0x18;
        }
        else
        {
            upload.EventType.word=INT_TYPE_ALARM;
            devType=0x00;
        }
        upload.Type = RECORD_FIRE;
		for(j=line_offset[0]+3;j<line_offset[1];j++)
        {
           if(buf[j]==0x3A&&buf[j+1]==0x20)			   //":�ո�"
           {
                if(buf[j+3]==0xBA&&buf[j+4]==0xC5) 	   //���� "��"¥
                {
                   floor=buf[j+2]-0x30;				   //��ȡ����¥��
                   if(buf[j+8]==0xB2&&buf[j+9]==0xE3)    //���� "��"
                   {
                       layer=buf[j+7]-0x30;			   //��ȡ�������
                   }
                   else if(buf[j+9]==0xB2&&buf[j+10]==0xE3)//˫�� "��"
                   {
                	   layer=((buf[j+7]-0x30)*10+(buf[j+8]-0x30)); //��ȡ˫�����
                   }
                }
                else if(buf[j+4]==0xBA&&buf[j+5]==0xC5)	  //˫�� "��"¥
                {
                   floor=((buf[j+2]-0x30)*10+(buf[j+3]-0x30));    //��ȡ˫��¥��
                   if(buf[j+9]==0xB2&&buf[j+10]==0xE3)	//���� "��"
                   {
                	   layer=buf[j+8]-0x30; 
                   }
                   else if(buf[j+10]==0xB2&&buf[j+11]==0xE3)//˫�� "��"
                   {
                      layer=(buf[j+8]-0x30)*10+(buf[j+9]-0x30); //��ȡ˫�����
                   } 
                }
                else if(buf[j+4]==0xB2&&buf[j+5]==0xE3)	  //"��"��
                {
                   floor=00;
                   if(buf[j+2]==0x2D)
                   {
                       layer=(100-(buf[j+3]-0x30));//��¥���
                   }
                   else
                   {
                       layer=((buf[j+2]-0x30)*10+(buf[j+3]-0x30)); //��ȡ˫�����
                   }
                }
                else if(buf[j+3]==0xB2&&buf[j+4]==0xE3)
                {
                    floor=00;
                    layer= buf[j+2]-0x30; 
                }
            }
        }
        if(buf[line_offset[0]+4]==0x2F)//��·��1/
        {
            EIloop=buf[line_offset[0]+3]-0x30;
            if(buf[line_offset[0]+5]<0x3A&&buf[line_offset[0]+6]==0x3A)
            {
                EIla=buf[line_offset[0]+5]-0x30;
            }
            else if(buf[line_offset[0]+5]<0x3A&&buf[line_offset[0]+6]<0x3A&&buf[line_offset[0]+7]==0x3A)
            {
                EIla=(buf[line_offset[0]+5]-0x30)*10+(buf[line_offset[0]+6]-0x30);
            }
            else if(buf[line_offset[0]+5]<0x3A&&buf[line_offset[0]+6]<0x3A&&buf[line_offset[0]+7]<0x3A&&buf[line_offset[0]+8]==0x3A)
            {
                EIla=(buf[line_offset[0]+5]-0x30)*100+(buf[line_offset[0]+6]-0x30)*10+(buf[line_offset[0]+7]-0x30);
            }
            else
            {
                EIla=0;
            }  
        }
        else if(buf[line_offset[0]+5]==0x2F) //��·��11/
        {
            EIloop=(buf[line_offset[0]+3]-0x30)*10+(buf[line_offset[0]+4]-0x30);
            if(buf[line_offset[0]+6]<0x3A&&buf[line_offset[0]+7]==0x3A)
            {
                EIla=buf[line_offset[0]+6]-0x30;
            }
            else if(buf[line_offset[0]+6]<0x3A&&buf[line_offset[0]+7]<0x3A&&buf[line_offset[0]+8]==0x3A)
            {
                EIla=(buf[line_offset[0]+6]-0x30)*10+(buf[line_offset[0]+7]-0x30);
            }
            else if(buf[line_offset[0]+6]<0x3A&&buf[line_offset[0]+7]<0x3A&&buf[line_offset[0]+8]<0x3A&&buf[line_offset[0]+9]==0x3A)
            {
                EIla=(buf[line_offset[0]+6]-0x30)*100+(buf[line_offset[0]+7]-0x30)*10+(buf[line_offset[0]+8]-0x30);
            }
            else
            {
                EIla=0;
            }
        }
        if(buf[line_offset[1]+3]==0xD7&&buf[line_offset[1]+4]==0xA2)//"ע"��
        {
            for( k=line_offset[1]+3,l=0;k<line_offset[2]-1;k++)
            {
        	    upload.Cc[l++]=buf[k];
            }
        } 
        else if(buf[line_offset[2]+3]==0xD7&&buf[line_offset[2]+4]==0xA2)//"ע"��
        {
            for( k=line_offset[2]+3,l=0;k<line_offset[3]-1;k++)
            {
                upload.Cc[l++]=buf[k];
            }
        } 
        for(j=line_offset[print_line_number-3]+3;j<line_offset[print_line_number-2];j++)
        {
        	if((buf[j]==0xC4)&&(buf[j+1]==0xEA))//��
        	upload.Time[5]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
        	else if((buf[j]==0xD4)&&(buf[j+1]==0xC2))//��
        	upload.Time[4]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
        	else if((buf[j]==0xC8)&&(buf[j+1]==0xD5))//��
        	upload.Time[3]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
        	else if((buf[j]==0xCA)&&(buf[j+1]==0xB1))//ʱ
        	upload.Time[2]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
        	else if((buf[j]==0xB7)&&(buf[j+1]==0xD6))//��
        	upload.Time[1]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
        }
        upload.Time[0]=0;
        for(k=0;k<6;k++)
        {
            upload.Time[k]=Hex2BCD(upload.Time[k]);
        }
        uc[0] = 0x01;	 //����
        uc[1] = EIloop;  //��· 
        uc[2] = EIla;//��ַ��
        Hex_To_BasicUC(&upload.Uc[1],&uc[0],3);
        MemoryCpyInvert(&upload.Uc[1],&upload.Uc[1],LEN_REG_UC-1);
        upload.Uc[0]=devType;
        Do_Event_Upload(&upload,Date_Buffer);
    }
    else
    {
        return;
    }
}

void Save_Fault_Info_EI_PRT_B(UINT8 *buf,UINT16 FrameLen)
{
    UINT8 devType = 0x00,i,j,l,k = 0;
    UINT8 uc[3];
    UINT8 Date_Buffer[128];
    UINT8	 print_line_number = 0,fault_line_number = 0;//��ӡ����������������������������
    UINT16 line_offset[6];//ÿ�н�βƫ�Ƶ�ַ
    UINT8 floor = 0,layer = 0;//¥�ţ����
    UINT16 EIla = 0,EIloop = 0;

    UPLOAD_STRUCT upload;
    memset(&upload.Time, 0xFF, sizeof(upload));


    for(i=0;i <FrameLen ;i++)//��ѯ���������Ƿ��й���
    {
        Watch_Dog();
        if(buf[i]==0xB9&&buf[i+1]==0xCA&&buf[i+2]==0xD5&&buf[i+3]==0xCF)
        {
           if(print_line_number==0)
           {
        	  // fire_offset=i;
               fault_line_number=1;					  
           }
           else
           {
               return;
           }
        }
        if(buf[i]==0x0A&&buf[i+1]==0x0D)
        {
           line_offset[print_line_number++]=i+1;//ÿ�н�β����ֵ
        }
    }
    if(print_line_number <=6)
    {
        if(print_line_number <=3)
        {
            if(strstr((const char*)buf,(const char*)"�������")  != NULL)
            {
    			memcpy(upload.Uc,System.ctr_addr,LEN_REG_UC);

    			upload.Type = RECORD_FAULT;
    			upload.EventType.word = INT_TYPE_INPUT_POWER_FAULT;
    			Get_RTC_Time(time_string);
    			memcpy((char *)upload.Time,(const char *)time_string,3);
    			memcpy((char *)upload.Time+3,(const char *)time_string+4,3);		
           }
    	   else if(strstr((const char*)buf,(const char*)"�������")  != NULL)
           {
               memcpy(upload.Uc,System.ctr_addr,LEN_REG_UC);
               upload.Type = RECORD_FAULT;
               upload.EventType.word =INT_TYPE_BACKUP_POWER_FAU;
            	//��ʱ������
               Get_RTC_Time(time_string);
               memcpy((char *)upload.Time,(const char *)time_string,3);
               memcpy((char *)upload.Time+3,(const char *)time_string+4,3);		
           }
       }	
       else
       {
            if(strstr((const char*)buf,(const char*)"�ֶ�����")  != NULL)
            {
                devType=0x17;
            }
            else if(strstr((const char*)buf,(const char*)"���")  != NULL)
            {   
                devType=0x2A;
            }
            else if(strstr((const char*)buf,(const char*)"����")  != NULL)
            {
            	devType=0x1E;
            }
            
            else if(strstr((const char*)buf,(const char*)"����˨")  != NULL)
            {
            	devType=0x18;
            }
          
            else if(strstr((const char*)buf,(const char*)"������")  != NULL)
            {
            	devType=0x55;
            }
            else if(strstr((const char*)buf,(const char*)"���")  != NULL)
            {	
               devType=0x56;
            }
            else
            {
               devType=0x00;
            }	 
        	upload.Type = RECORD_FAULT;
        	upload.EventType.word =INT_TYPE_DEV_FAULT;
        	for(j=line_offset[0]+3;j<line_offset[1];j++)
        	{
                if(buf[j]==0x3A&&buf[j+1]==0x20)			   //":�ո�"
                {
                    if(buf[j+3]==0xBA&&buf[j+4]==0xC5) 	   //���� "��"¥
                    {
                    	 floor=buf[j+2]-0x30;				   //��ȡ����¥��
                    	 
                    	 if(buf[j+8]==0xB2&&buf[j+9]==0xE3)    //���� "��"
                    	 {
                    		 layer=buf[j+7]-0x30;			   //��ȡ�������
                    	 }
                    	 else if(buf[j+9]==0xB2&&buf[j+10]==0xE3)//˫�� "��"
                    	 {
                    		 layer=((buf[j+7]-0x30)*10+(buf[j+8]-0x30)); //��ȡ˫�����
                    	 }
                     }
                     else if(buf[j+4]==0xBA&&buf[j+5]==0xC5)	  //˫�� "��"¥
                     {
                    	 floor=(buf[j+2]-0x30)*10+buf[j+3];    //��ȡ˫��¥��
                    	 
                    	 if(buf[j+9]==0xB2&&buf[j+10]==0xE3)	//���� "��"
                    	 {
                    	     layer=buf[j+8]-0x30; 
                    	 }
                    	 else if(buf[j+10]==0xB2&&buf[j+11]==0xE3)//˫�� "��"
                    	 {
                    		 layer=(buf[j+8]-0x30)*10+(buf[j+9]-0x30); //��ȡ˫�����
                    	 } 
                     }
                     else if(buf[j+4]==0xB2&&buf[j+5]==0xE3)		//"��"��
                     {
                         floor = 00;
                         if(buf[j+2]==0x2D)
                         {
                             layer = (100-(buf[j+3]-0x30));//��¥���
                         }
                         else
                         {
                             layer = ((buf[j+2]-0x30)*10+(buf[j+3]-0x30)); //��ȡ˫�����
                         }
                     }
                     else if(buf[j+3]==0xB2&&buf[j+4]==0xE3)
                     {
                         floor =00;
                    	 layer= buf[j+2]-0x30; 
                     }
                }
        	} 
            if(buf[line_offset[0]+4]==0x2F)//��·��1/
            {
                EIloop=buf[line_offset[0]+3]-0x30;
                if(buf[line_offset[0]+5]<0x3A
                  &&buf[line_offset[0]+6]==0x3A)
                {
                    EIla=buf[line_offset[0]+5]-0x30;
                }
                else if(buf[line_offset[0]+5]<0x3A
                       &&buf[line_offset[0]+6]<0x3A
                       &&buf[line_offset[0]+7]==0x3A)
                {
                    EIla=(buf[line_offset[0]+5]-0x30)*10+(buf[line_offset[0]+6]-0x30);
                }
                else if(buf[line_offset[0]+5]<0x3A
                       &&buf[line_offset[0]+6]<0x3A
                       &&buf[line_offset[0]+7]<0x3A
                       &&buf[line_offset[0]+8]==0x3A)
                {
                    EIla=(buf[line_offset[0]+5]-0x30)*100+(buf[line_offset[0]+6]-0x30)*10+(buf[line_offset[0]+7]-0x30);
                }
                else
                {
                    EIla=0;
                }
            }
            else if (buf[line_offset[0]+5] == 0x2F) //��·��11/
            {
                EIloop=(buf[line_offset[0]+3]-0x30)*10+(buf[line_offset[0]+4]-0x30);
                if (buf[line_offset[0]+6] < 0x3A
                   &&buf[line_offset[0]+7] == 0x3A)
                {
                    EIla = buf[line_offset[0]+6] - 0x30;
                }
                else if (buf[line_offset[0]+6] < 0x3A
                        &&buf[line_offset[0]+7] < 0x3A
                        &&buf[line_offset[0]+8] == 0x3A)
                {
                    EIla = (buf[line_offset[0]+6]-0x30)*10+(buf[line_offset[0]+7]-0x30);
                }
                else if(buf[line_offset[0]+6] < 0x3A
                       &&buf[line_offset[0]+7] < 0x3A
                       &&buf[line_offset[0]+8] < 0x3A
                       &&buf[line_offset[0]+9] == 0x3A)
                {
                    EIla=(buf[line_offset[0]+6]-0x30)*100+(buf[line_offset[0]+7]-0x30)*10+(buf[line_offset[0]+8]-0x30);
                }
                else
                {
                    EIla=0;
                }
            }
            if (buf[line_offset[1]+3]==0xD7&&buf[line_offset[1]+4]==0xA2)//"ע"��
            {
                for( k=line_offset[1]+3,l=0;k<line_offset[2]-1;k++)
                {
                  upload.Cc[l++]=buf[k];
                }
            } 
            else if (buf[line_offset[2]+3]==0xD7&&buf[line_offset[2]+4]==0xA2)//"ע"��
            {
                for( k=line_offset[2]+3,l=0;k<line_offset[3]-1;k++)
                {
                    upload.Cc[l++]=buf[k];
                }
            } 
            for(j=line_offset[print_line_number-3]+3;
                j<line_offset[print_line_number-2];
                j++)
            {
                if((buf[j]==0xC4)&&(buf[j+1]==0xEA))//��
                {
                    upload.Time[5]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
                }
                else if((buf[j]==0xD4)&&(buf[j+1]==0xC2))//��
                {
                    upload.Time[4]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
                }
                else if((buf[j]==0xC8)&&(buf[j+1]==0xD5))//��
                {
                    upload.Time[3]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
                }
                else if((buf[j]==0xCA)&&(buf[j+1]==0xB1))//ʱ
                {
                    upload.Time[2]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
                }
                else if((buf[j]==0xB7)&&(buf[j+1]==0xD6))//��
                {
                    upload.Time[1]=(buf[j-2]-0x30)*10+(buf[j-1]-0x30);
                }
            }
        	upload.Time[0]=0;
            for(k=0;k<6;k++)
        	{
        	   upload.Time[k]=Hex2BCD(upload.Time[k]);
        	}
        	uc[0] = 0x01;	 //����
        	uc[1] = EIloop;  //��· 
        	uc[2] = EIla;//��ַ��
        	Hex_To_BasicUC(&upload.Uc[1],&uc[0],3);
        	MemoryCpyInvert(&upload.Uc[1],&upload.Uc[1],LEN_REG_UC-1);
            upload.Uc[0]=devType;
        }
		Do_Event_Upload(&upload,Date_Buffer);
	}
}

void Handle_Ei_Pri_B(CONTR_IF *buf)
{
    //��
    if (strstr((const char*)buf->DAT_Return,(const char*)"��")  != NULL)
    {
        Save_Fire_Info_EI_PRT_B(buf->DAT_Return, buf->R.FrameLen );	
    }
    //����
    else if (strstr((const char*)buf->DAT_Return,(const char*)"����")  != NULL)
    {
        Save_Fault_Info_EI_PRT_B(buf->DAT_Return, buf->R.FrameLen);
    }
    buf->R.Clev = buf->R.FrameEndLoc;
}
void Parall_Uart_Rec_Data(UINT8 dataRec)
{
	EI_Comm.R.Buf[EI_Comm.R.Head] = dataRec;
	EI_Comm.R.Head++;
	EI_Comm.R.ByteInterval = 0;
	if(EI_Comm.R.Head == CONTR_BUF_LEN)
	{
	    EI_Comm.R.Head = 0;
	}	
}
//===============================================================================
//��������:��������ӡ�����ڻ�ȡ�����ݷ���
//�������: 
//�������: 
//�޸�����: 2019-06
//�޸���Ա: 
//===============================================================================
UINT8 Parall_Data_Analyse(CONTR_IF *buf)
{
    UINT16 i,data_loc,head1_loc,end1_loc; 
    UINT8 count,data_len,ope_flag = FALSE;

    if(buf->R.Clev == buf->R.Head) 
    {
	    return 0;
    }
    if(buf->R.Clev >= CONTR_BUF_LEN)  
    {
        buf->R.Clev=0;
    }
		
	switch(buf->AnalyseSta)
    {
        case FRAME_HEAD:
        	Watch_Dog();
        	i = buf->R.Clev;
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
        		if((buf->R.Buf[head1_loc] == FRAME_HEAD0_PRINT) && (buf->R.Buf[i] == FRAME_HEAD1_PRINT))//�¼�Ӧ��
        		{
        			
        			buf->R.Clev = head1_loc; //��֡ͷ����һ�ֽڿ�ʼ
        			break;

        		}
        		if(++i == CONTR_BUF_LEN) i=0;
        	}
        	if(i == buf->R.Head )  //����һȦ��δ�ҵ�֡ͷ	 
        	{
        		//buf->R.Clev = buf->R.Head;
        		buf->R.FrameEndLoc = buf->R.Head; 
        		break;
        	}
        	buf->AnalyseSta = FRAME_DATA;
        	break;
        	
        case FRAME_DATA: //ȷ���Ƿ�����һ֡����
        	Watch_Dog();
        	i = buf->R.Clev + 2; //Խ��֡ͷ0D 0A������һ����ʼ��
        	while(i != buf->R.Head)
        	{
        		//ѭ������
        		if(i <= 3)
        		{
        			end1_loc = CONTR_BUF_LEN-(3-i);
        		}
        		else
        		{
        			end1_loc = i - 3;
        		}
        		//����֡β
        		//
        		if((buf->R.Buf[end1_loc] ==0x26) && 
        			(buf->R.Buf[(end1_loc+1)%((UINT16)CONTR_BUF_LEN)] == 0x20) &&
        			(buf->R.Buf[(end1_loc+2)%((UINT16)CONTR_BUF_LEN)] == 0x0A) &&
        			(buf->R.Buf[i] == 0x0D))
        		{
        			buf->R.FrameEndLoc = i; 

        			data_loc = buf->R.Clev %((UINT16)CONTR_BUF_LEN);
        			if((buf->R.FrameEndLoc > buf->R.Clev) && (buf->R.FrameEndLoc <=  CONTR_BUF_LEN-1))
        			{
        				//data_len = buf->R.FrameEndLoc - buf->R.Clev -5;
        				buf->R.FrameLen = buf->R.FrameEndLoc - buf->R.Clev + 1;
        			}
        			else
        			{
        				//data_len = buf->R.FrameEndLoc+CONTR_BUF_LEN - buf->R.Clev -5;
        				buf->R.FrameLen = buf->R.FrameEndLoc+CONTR_BUF_LEN - buf->R.Clev + 1;
        			}
        			//��������
        			data_len = buf->R.FrameLen ;
        			for(count=0; count<data_len; )
        			{
        				if(buf->R.Buf[data_loc]!=0)
        				{
        				 buf->DAT_Return[count++] = buf->R.Buf[data_loc];
        				}
        				if(++data_loc >= CONTR_BUF_LEN) data_loc = 0;//�ж��Ƿ���תȦ
        			}
        			ope_flag = TRUE;
        			break;
        		}
        											
        		if(++i == CONTR_BUF_LEN) i=0;
        	}
        	if(i == buf->R.Head )  //����һȦ��δ�ҵ�֡β
        	{
        		break;
        	}

        	buf->AnalyseSta = FRAME_HEAD;
        	break;
        default:
        	buf->AnalyseSta = FRAME_HEAD;
        	break;	
    }
	return ope_flag;				
}

void Data_Deal_Task(void)
{
    if( Parall_Data_Analyse(&EI_Comm))
    {
        Handle_Ei_Pri_B(&EI_Comm);
    }
    else if(EI_Comm.Poll_Ctr==1)
    {
        TS_Send_Heart_Poll(&RS232);
        EI_Comm.Poll_Ctr = 0;
    }
}

