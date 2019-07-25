
#include "record_manage.h"
#include "record_status.h"
#include "ex_flash.h"
#include "xycnbus.h"
#include "rtc.h"
#include "basic.h"
#include "type_define.h"
#include "typeTab.h"
#include "sys_init.h"
//RECORD_STRUCT Record;
RECORD_INF RecordInf;


extern const S_EVENT_TYPE_INF   C_EVENT_ANNOTATION_LIST[];
//extern void (* this_func)(INT8U key);			//�˵��ص�����ָ�붨��

//====================================================================================

/*********************************************************************************
* �������� : Record_Get_Event
* �������� : ��ȡ�¼�������Ϊ"event_code"���¼��������ŵ�str�С������и����ͷ���1�����򷵻�0
* ������� : event_code���¼������룬
* ������� : str���¼�����
* �� �� ֵ : 1����ȡ�ɹ���0����ȡʧ��
* �޸����� ��2013-06
*********************************************************************************/
/*UINT8 Record_Get_Event(UINT16 const event_code,UINT8 * str)
{
	UINT16 i,event_counter;
	
	event_counter = sizeof(C_EVENT_ANNOTATION_LIST)/sizeof(S_EVENT_TYPE_INF);
	for(i=0; i < event_counter; i++)
	{
		if(event_code == C_EVENT_ANNOTATION_LIST[i].EventType)
		{
			strcpy((INT8 *)str,(INT8 *)(C_EVENT_ANNOTATION_LIST[i].Event_Annotaiton));
			return strlen((INT8 *)C_EVENT_ANNOTATION_LIST[i].Event_Annotaiton) ;
		}
	}
	return 0;
}*/

/*********************************************************************************
* �������� : Delete_All_Record
* �������� : ɾ�����м�¼
* ������� : ��
* ������� : ��
* �� �� ֵ     : ��
* �޸����� ��2016-01
*********************************************************************************/

void Delete_All_Record(void)
{
	uint16 i,sec; 



    //TTS_Data_Init();
	//�����ⲿflash�ļ�¼�洢����	
	sec = MAXN_FLASH_RECORD*ALEN_FLASH_RECORD/4096;
	for(i=0;i<sec;i++)
	{
        Watch_Dog();
		Flash_Erase_3Addr(ADDR_FLASH_RECORD+i*4096);
	}
	//��¼��Ϣ������0������Ϣ��ʾ
	RecordInf.StartPc = 0;
	RecordInf.SavePc  = 0;
	//RecordInf.Total = 0;
	RecordInf.ttsRecordPc = RecordInf.SavePc;
	
}



//**************************************************************************************************
//Function Name  : get_record
//Description    : ��FLASH�ж�ȡһ����¼��
//Arguments      : offset����¼��FLASH�е�ƫ��������ʼ��ַΪRECORD��
//                 record_buffer  ����ȡ���ļ�¼�ṹ�壻
//Return         : ��ȡ�ɹ�����1��ʧ�ܷ���0
//**************************************************************************************************
UINT8 get_record(UINT16 offset,RECORD_STRUCT * record_buffer)
{
	//memcpy(record_buffer,&Record[offset],sizeof(Record[0]));
	if(Flash_Load_Info(RECORD,offset,(uchar *)record_buffer))//record_buffer))
	{
		return 1;
	}
	return 0;
}


/*********************************************************************************
* �������� : Record_Save_Local
* �������� : ������Ϣ�洢��ѭ���洢
* ������� : RecordType���洢�ļ�¼����
* ������� : None
* ����ֵ   : None
* �޸����� ��2013-09
*********************************************************************************/
//��¼�洢+��ʾ��Ϣ
void Record_Save(RECORD_STRUCT *record)
{
    UINT32 addr;

    if(record->Type > RECORD_OTHERS)	//���ͳ���
    {
        return;
    }
	
	record->TranFlag = RECORD_TRAN_INIT;

    //ʱ�����:���봫���豸��ʱ��
    if(record->EventType.word == INT_TYPE_POWER_OFF)		// record time
    {
        RTC_Get_PowerOff_Time(time_string);
        memcpy(record->Time,time_string,6);
    }
    else
    {
        GET_RTC_TIME();
        memcpy((char *)record->Time,(const char *)time_string,3);
        memcpy((char *)record->Time+3,(const char *)time_string+4,3);
    }

    if(record->Ic.Loop == IC_LOOP_SYS)
    {
		MemoryCpyInvert(record->Id,System.id,LEN_REG_ID);
		MemoryCpyInvert(record->Uc,System.uc,LEN_REG_UC);
		MemoryCpyInvert(record->Cc,System.cc,LEN_REG_CC);
    }

    //�洢��FLASH��,ȷ����һ���������ǿհף�
       //��ǰ�洢λ��Ϊÿ������һ����¼λ�ã��������һ�����ǿ������
	   //ѭ���洢����һ��洢���,����µ�һ����¼��λ��

	if((RecordInf.SavePc % COUNT_RECORD_PER_SECTOR) == 0)//32 //�洢��ÿ������һ����¼λ��ʱ��������һ��������֤��һ���������Ŀհ�
    {
       if(RecordInf.SavePc == (MAXN_FLASH_RECORD - COUNT_RECORD_PER_SECTOR))//���һ��������
       {
            addr = ADDR_FLASH_RECORD;
       }
       else            
       {
            addr = ADDR_FLASH_RECORD + (RecordInf.SavePc + COUNT_RECORD_PER_SECTOR)* ALEN_FLASH_RECORD;	
       }
       if(Flash_Blank_Check(addr,SIZE_FLASH_SECTOR) == 0)	//�ǿհ����������ǵ�һ��д������ʼλ��Ϊ���¸�����
       {
    	     Flash_Erase_3Addr(addr);
    	     RecordInf.StartPc = (RecordInf.StartPc + COUNT_RECORD_PER_SECTOR) % MAXN_FLASH_RECORD;
       }
    }
	
    Flash_Save_Info(RECORD,RecordInf.SavePc,(uint8*)(record));

	//�����Ϣ	
	//Message_Add(RecordInf.SavePc,&Record);	
	
	/*if(Record.Type == RECORD_ELIMINATE)//��������������Լ����ϻָ���������������ȷ��
	{
		if(Record.Mode == RMODE_UC)   //�豸�����������
		{
			Message_Delete_Fault(RECORD_FAULT,Record.Ic,NULL,MSG_DEL_MODE_IC);
		}
     	else                          //��������������
     	{
			Message_Delete_Fault(RECORD_FAULT,NULL,Record.Uc,MSG_DEL_MODE_UC);
	 	}
	}*/

    //�洢�޸�Ϊѭ���洢 2013-09-24
    if(++RecordInf.SavePc > MAXN_FLASH_RECORD - 1)	//�߼ʴ���
    {
       RecordInf.SavePc = 0;//SavePc�ķ�Χ��0-(MAXN_FLASH_RECORD-1)
    }
    //RecordInf.Total++;//end �洢�޸�	
}
/*********************************************************************************
* �������� : Init_Record
* �������� : ��ʼ���豸��¼��������ȡ������Ϣ��λ�� �����ȴӱ��ݼĴ�����ȡ��
			 ���ʧ�ܱ������ң����ڲ����������������ģ����ڿհ׼�¼����ֻ�ܱ�����
			 ���ҷ�����Ѱ�ҵ�һ���հ׼�¼��λ�ã�������������λ���Ƿ�Ϊ�հף�����հ�����
					   ��һ�μ�¼����֮���ǽ���ѭ���洢��
* ������� : type 0�ϵ��ʼ����0x01��λ���ʼ��
* ������� : None
* ����ֵ   : None
* �޸����� ��2016-01
*********************************************************************************/
void Init_Record(uchar type)
{
	UINT16 i,blank_sector_sn,serch_sector_sn;	
    UINT8 temp1[SLEN_FLASH_RECORD],temp2[SLEN_FLASH_RECORD]={0};
    UINT32 addr;
	
	if(type)	return;			// �����λ���ض���¼��Ϣ
	/*RecordInf.Total = 0;
	for(i=0; i<MAXN_FLASH_RECORD; i++)
	{
        Watch_Dog();

		Flash_Read_3String(ADDR_FLASH_RECORD+i*ALEN_FLASH_RECORD,buffer,1);
		if(buffer[0]==0xaa)
		{
			RecordInf.Total ++;//= (i+1)%MAXN_FLASH_RECORD;
			//break;
		}
	}*/
 	RecordInf.SavePc  = 0;
    RecordInf.StartPc = 0;
    for(i = 1; i < MAX_RECORD_SECTOR; i++)
    {
    	Watch_Dog();
    	if(Flash_Blank_Check(ADDR_FLASH_RECORD + i * SIZE_FLASH_SECTOR, SIZE_FLASH_STA_VALID))	//�鵽�հ�����
    		break;
    }
    if(i >= MAX_SECTOR_COUNTER)			//�����޿հ��������������£�,�����ϵ�һ��������������
    {
    	blank_sector_sn = 0;
    	Flash_Erase_3Addr(ADDR_FLASH_RECORD);
    	RecordInf.SavePc = 0;
    }
    else
    {
    	//��ȡд��ʼ��ַ
    	blank_sector_sn = i;
    	serch_sector_sn = blank_sector_sn - 1;
    	memset(temp1,0xff,SLEN_FLASH_RECORD);
    	for(i=0; i < SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD; i++)
    	{
    		Watch_Dog();
    		addr = ADDR_FLASH_RECORD + serch_sector_sn * SIZE_FLASH_SECTOR + i * ALEN_FLASH_RECORD;
    		Flash_Read_3String(addr,temp2,SLEN_FLASH_RECORD);
    		if(memcmp(temp1,temp2,SLEN_FLASH_RECORD) == 0)	//ȡ���հ�֡
    		{
    			RecordInf.SavePc  = serch_sector_sn * (SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD) + i;
    			break;
    		}
    	}
    	if(i >= SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD)	
    	{
    		RecordInf.SavePc  = (serch_sector_sn + 1)* (SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD);	//��������д������
    	}
    }
    //��ȡ��¼��ʼ��ַ�����ڼ�¼�����ֻȡ��һ֡���ݣ���������ǵ�һ��д
    serch_sector_sn = (blank_sector_sn == (MAX_SECTOR_COUNTER - 1)) ? 0:(blank_sector_sn + 1);
    memset(temp1,0xff,SLEN_FLASH_RECORD);

    addr = ADDR_FLASH_RECORD + serch_sector_sn * SIZE_FLASH_SECTOR;
    Flash_Read_3String(addr,temp2,SLEN_FLASH_RECORD);
    if(memcmp(temp1,temp2,SLEN_FLASH_RECORD) == 0)	//�հ׼�¼����һ��洢
    {
    	RecordInf.StartPc  = 0;
    }
    else											//�ǿհ׼�¼����n��洢
    {
    	RecordInf.StartPc  = serch_sector_sn * (SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD);	//��������д������
    }
    //�������д�뱸�ݼĴ���
   
    RecordInf.ttsRecordPc = RecordInf.SavePc;
}

//=============================================================================================
//��	���� void Record_Power_On_Off(void)
//��	�ܣ� ����:���ֿ��������µ�
//��	���� ��
//�� �� ֵ:  ��
//-----------------------------------------------------------------------------------------------
//�������ڣ�  2013.1
//*==============================================================================================*/
void Record_Power_On_Off(UINT8 type)
{
	RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));

    if(type)    return ;

		//��¼�ػ� 
	record.Type = RECORD_POWERONOFF;
	record.EventType.word = INT_TYPE_POWER_OFF;//�豸�ػ�
	Record_Sys_If_Event(&record);
	
	//��¼����
	memset(&record.Sta, 0xFF, sizeof(record));

	record.Type = RECORD_POWERONOFF;
	record.EventType.word = INT_TYPE_POWER_ON;//�豸����
	Record_Sys_If_Event(&record);
		
}

void Record_Updata_Suc(void)
{
    RECORD_STRUCT record;
	memset(&record.Sta, 0xFF, sizeof(record));
	
    record.Type = RECORD_OTHERS;
    record.EventType.word = INT_TYPE_UPDATA_SUCC;
	
	Record_Sys_If_Event(&record);
}



UINT16 Get_Event_Type_Number(void)
{
	return(sizeof(C_EVENT_ANNOTATION_LIST)/sizeof(S_EVENT_TYPE_INF));
}

UINT8 Get_EventTypeGroup(UINT16 event_type)
{
	UINT8 group = RECORD_MISC;
	UINT16 k,eventNum;

	eventNum = Get_Event_Type_Number();
	if(event_type == INT_TYPE_NULL)
	{
		return group;
	}
	for(k=0; k < eventNum; k++)
	{
		if(C_EVENT_ANNOTATION_LIST[k].EventType == event_type)
		{
			group = C_EVENT_ANNOTATION_LIST[k].generic_type;
			break;
		}
	}
	return group;
}

/*********************************************************************************
* �������� : Record_Type_Is_Sel
* �������� : �жϼ�¼�����Ƿ�ѡ�У����ڴ�ӡ����TTS��������������/����
* ������� : type����¼���ͣ�����record_manage.h
* ������� : None
* �� �� ֵ : �Ƿ�����������0�������ţ�1������
* �޸����� ��2016.5.20
*********************************************************************************/
UINT8 Record_Type_Is_Sel(UINT8 type,UINT8 sel_setting)
{
	if(type > RECORD_MAX)	return 0;
	if(type <=  RECORD_EARLYFIRE)
		return 1;
	else
		return 0;
}

//=============================================================================
//��������: TTS��¼��Ϣ��ʽ��
//�������: UINT8 * str:��ʽ������Ϣ���ָ��
//�������: �豸���ͺ��¼���������
//�޸�����: 2016.5.20
//�޸���Ա: 
//=============================================================================
/*UINT8 Record_TTS_Format(UINT8 * str)
{
	UINT8 dev_type,len;	
	UINT8 temp;
	len = 0;

    if(memcmp(C_DEV_TYPE_LIST[Record.Uc[0]].BriefDescribe ,"��Ч����",8))
		dev_type = Record.Uc[0];
	else
		dev_type = DeviceId_Type(Record.Id); 	

	//len = strlen((INT8 *)C_DEV_TYPE_LIST[dev_type].DetailDescribe);//strlen((INT8 *)DEVICE_TYPE_TAB[dev_type]);
	//strcpy(str,(INT8 *)C_DEV_TYPE_LIST[dev_type].DetailDescribe);

	len = strlen((char *)C_DEV_TYPE_LIST[dev_type].DetailDescribe);//strlen((INT8 *)DEVICE_TYPE_TAB[dev_type]);
	strcpy((char *)str,(const char *)C_DEV_TYPE_LIST[dev_type].DetailDescribe);

	temp = Record_Get_Event(Record.EventType.word,(UINT8 *)(str + len));
	if(temp == 0)
	{
		strcpy((INT8 *)(str + len),"δ�����¼�");
		len += 10;
	}
	else
	{
		len += temp;
	}

	return len;
}*/



