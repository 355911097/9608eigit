#ifndef TYPE_TAB_H
#define	TYPE_TAB_H
#include "global.h"
#include "record_manage.h"

#include "xycnbus.h"
#include "type_define.h"
#include "dev_ico.h"



#define  OVER 0xFF


//-----------------------------------���豸��Ӧ�¼������б�---------------------//

//������
//UINT16 const EVENT_LIST_CONTROL[] = {INVALID};



/*-------------------------------------------�¼�ע���б�-------------------------------------------*/

//struct t9py_index const t9py_index_mb
//S_EVENT_TYPE_INF const  C_EVENT_ANNOTATION_LIST[]=  
struct event_type const  C_EVENT_ANNOTATION_LIST[]=
{

	   //-----------------------------------------�˹�����ʵʱ�¼�--------------------------------//									   
	   {INT_TYPE_KEY_ACTION,					   RECORD_OTHERS,      TYPE_CRT_RESERVE,   "��������"},
	   {INT_TYPE_MANUAL_ALARM,					   RECORD_FIRE,		   TYPE_CRT_ALARM,	   "�ֶ�����"},
	   {INT_TYPE_SET_TIME,						   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "����ʱ��"},
	   {INT_TYPE_SET_PRINT_FIRE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ӡ��"},
	   {INT_TYPE_SET_PRINT_FIRE_AND_FEEDBACK,	   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ӡ�𾯺ͷ���"},
	   {INT_TYPE_SET_PINTT_ALL_EVENT,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ӡ������Ϣ"},
	   {INT_TYPE_SET_PRINT_DISEN,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ֹ��ӡ"},
	   {INT_TYPE_SET_PRINTER,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ӡŨ������"},
	   {INT_TYPE_SET_LCD_BACKGROUND_LIGHT,		   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "Һ����������"},
	   {INT_TYPE_SET_PREALARM_ENABLE,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "Ԥ����������"},
	   {INT_TYPE_SET_PREALARM_DISEN,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "Ԥ�����ܽ�ֹ"},
	   {INT_TYPE_SET_PREALARM_RELATION, 		   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "Ԥ����������"},
	   {INT_TYPE_SET_STARTUP_DIRECT_VIA_FIRE,	   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "��ֱ������"},
	   {INT_TYPE_SET_STARTUP_VIA_LINKAGE,		   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "������ʽ����"},
	   {INT_TYPE_SET_NETWORK_ENABLE,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "����ͨ�ſ���"},
	   {INT_TYPE_SET_NETWORK_DISEN, 			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "����ͨ�Źر�"},
	   {INT_TYPE_SET_ADD_LINKAGE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "�½�������ʽ"},
	   {INT_TYPE_SET_EDIT_LINKAGE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "�޸�������ʽ"},
	   {INT_TYPE_SET_DELETE_LINKAGE,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "ɾ��������ʽ"},
	   {INT_TYPE_REQ_START, 					   RECORD_START, 	   TYPE_CRT_RESERVE,   "��������"},
	   {INT_TYPE_REQ_STOP,						   RECORD_STOP, 	   TYPE_CRT_RESERVE,   "ͣ������"},
	   {INT_TYPE_REQ_SHIELD,					   RECORD_SHIELD,	   TYPE_CRT_RESERVE,   "��������"},
	   {INT_TYPE_REQ_RELEASE,					   RECORD_RELEASE,	   TYPE_CRT_RESERVE,   "�����������"},
	   {INT_TYPE_REQ_RESET, 					   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "��λ����"},
	   {INT_TYPE_PARA_MODIFY,					   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "�����޸�����"},
	   {INT_TYPE_REQ_SILENCE,					   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "�豸��������"}, 	   
	   {INT_TYPE_HELP_INF,						   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "��������"},
	   {INT_TYPE_LAN_SET_TIME,					   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "����Уʱ"}, 	   
	   {INT_TYPE_LAN_READ_TIME,					   RECORD_LOCALCOMMAND,TYPE_CRT_RESERVE,   "�����ȡʱ��"},
	   //-----------------------------------------���Ӧ�����¼�--------------------------------//
	   {INT_TYPE_IDLOG_DATA,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "ID��¼��������"},
	   {INT_TYPE_LALOG_DATA,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "LA��¼��������"},
	   {INT_TYPE_UCLOG_DATA,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,   "UC��¼��������"},
	   {INT_TYPE_TRANSPARENT_TRANS, 			   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "͸����Ϣ"},
	   {INT_TYPE_LINK_FORMULA_OUT,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "������ʽ�����������"},
	   {INT_TYPE_LINK_OUT,						   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "������������ʽ���"},
	   {INT_TYPE_UC_FIND_LC,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "�������ѯһ����"},
	   {INT_TYPE_MULTI_ADDRCOMM_RES,			   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "���ض༶��ַ����"},
	   {INT_TYPE_INNER_UP_MSG, 			           RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "�����豸�ϱ���Ϣ"},
	   {INT_TYPE_WILDCOMM_EXECUTE_RIGHT,		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "ͨ��������ȷִ��"},
	   //{INT_TYPE_DEVICE_SYNCH,					   RECORD_MISC,		   TYPE_CRT_RESERVE,   "�豸��Ϣͬ��"},
	   {INT_TYPE_EVENT_SYNCH,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "�¼���Ϣͬ��"},
	   {INT_TYPE_MONITOR_PDC_SEND_DATA, 		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "���PDC���߷�������"},
	   {INT_TYPE_MONITOR_PDC_RECE_DATA, 		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "���PDC������������"},
	   {INT_TYPE_MONITOR_IMTMPI_SEND_DATA,		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "���IMT/MPI���߷�������"},
	   {INT_TYPE_MONITOR_IMTMPI_RECE_DATA,		   RECORD_OTHERS,  	   TYPE_CRT_RESERVE,   "���IMT/MPI������������"},
	   {INT_TYPE_MONITOR_NODE_ID,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "��ؽڵ�ID"},
	   {INT_TYPE_MONITOR_BROCAST_SEND_DATA, 	   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "��ع㲥���߷���"},
	   {INT_TYPE_MONITOR_BROCAST_RECE_DATA, 	   RECORD_OTHERS,	   TYPE_CRT_RESERVE,   "��ع㲥��������"},
	   //----------------------------------------�Զ������¼�-------------------------------------//
	   {INT_TYPE_FIRE_ALARM,					   RECORD_FIRE,		   TYPE_CRT_ALARM,	    "���汨��"},
	   {INT_TYPE_TEMPERATURE_ALARM, 			   RECORD_FIRE,		   TYPE_CRT_ALARM,	    "�¶ȱ���"},
	   {INT_TYPE_SMOKE_ALARM,					   RECORD_FIRE,		   TYPE_CRT_ALARM,	    "������"},
	   {INT_TYPE_ALARM,				        	   RECORD_FIRE, 	   TYPE_CRT_ALARM,		"�𾯱���"},

	   {INT_TYPE_PRE_FIRE_ALARM,				   RECORD_EARLYFIRE,   TYPE_CRT_EARLY_ALARM,"��Ԥ��"},
	   {INT_TYPE_PRE_TEMPERATURE_ALARM, 		   RECORD_EARLYFIRE,   TYPE_CRT_EARLY_ALARM,"�¾�Ԥ��"},
	   {INT_TYPE_PRE_SMOKE_ALARM,				   RECORD_EARLYFIRE,   TYPE_CRT_EARLY_ALARM,"�̾�Ԥ��"},
	   {INT_TYPE_PRE_ALARM,			        	   RECORD_EARLYFIRE,   TYPE_CRT_EARLY_ALARM,"��Ԥ��"},
		   	   
	   {INT_TYPE_MONITOR_FIRE_ALARM, 		   	   RECORD_MONITER,	   TYPE_CRT_MONITER,    "���汨��"},
	   {INT_TYPE_MONITOR_TEMPERATURE_ALARM, 	   RECORD_MONITER,	   TYPE_CRT_MONITER,    "�¶ȱ���"},
	   {INT_TYPE_MONITOR_SMOKE_ALARM,			   RECORD_MONITER,	   TYPE_CRT_MONITER,	"������"},
	   {INT_TYPE_MONITOR_CURRENT_LEAKAGE_ALARM,    RECORD_MONITER,	   TYPE_CRT_MONITER,	"©�籨��"},
	   {INT_TYPE_MONITOR_GAS_LEAKAGE_ALARM,   	   RECORD_MONITER,	   TYPE_CRT_MONITER,	"ȼ��й©"},
	   {INT_TYPE_MONITOR_THEFT_ALARM,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"����"},
	   {INT_TYPE_MONITOR_TIMEOUT_ALARM,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"��ʱ����"},
	   {INT_TYPE_MONITOR_ALARM,                    RECORD_MONITER,	   TYPE_CRT_MONITER,	"��ܱ���"},

	   {INT_TYPE_MONITOR_HIGH_VOLTAGE,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"��ѹ����"},
	   {INT_TYPE_MONITOR_LOW_VOLTAGE,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"Ƿѹ����"},
	   {INT_TYPE_MONITOR_HIGH_CURRENT,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"��������"},
	   {INT_TYPE_MONITOR_LOSE_PHASE,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"ȱ�����"},
	   {INT_TYPE_MONITOR_FAULT_PHASE,    		   RECORD_MONITER,	   TYPE_CRT_MONITER,	"�������"},
	   {INT_TYPE_MONITOR_POWER_INTERRUPT,    	   RECORD_MONITER,	   TYPE_CRT_MONITER,	"�жϹ���"},
	   //----------------------------------------״̬��Ϣ�¼�-------------------------------------//
	   {INT_TYPE_START_SUCESS,					   RECORD_OTHERS,	   TYPE_CRT_START,	    "�豸����"},
	   {INT_TYPE_STOP_SUCESS,					   RECORD_OTHERS,	   TYPE_CRT_START,	    "�豸ͣ��"},
	   {INT_TYPE_SHILED_SUCESS, 				   RECORD_OTHERS,	   TYPE_CRT_SHIELD,     "�豸����"},
	   {INT_TYPE_RELEASE_SUCESS, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�������"},
	   {INT_TYPE_PHONE_CALL, 			           RECORD_MONITER,	   TYPE_CRT_RESERVE,    "�绰����"},
	   {INT_TYPE_PHONE_CONNECT,			           RECORD_MONITER,	   TYPE_CRT_RESERVE,    "�绰��ͨ"},
	   {INT_TYPE_PHONE_HUNGUP,			           RECORD_FREE,	       TYPE_CRT_RESERVE,    "�绰�Ҷ�"},
	   {INT_TYPE_RESET_SUCESS,					   RECORD_RESET, 	   TYPE_CRT_RESET,	    "�豸��λ"},
	   {INT_TYPE_SET_RARA_SUCESS,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�����޸�"},
	   {INT_TYPE_DEVICE_SILENCE, 		   		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�豸����"},
	   
	   {INT_TYPE_STARTED,				   		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�����ѳɹ�"},
	   {INT_TYPE_STOPPED,				   		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ͣ���ѳɹ�"},
	   {INT_TYPE_SHILEDED,				   		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�����ѳɹ�"},
	   {INT_TYPE_RELEASED,				   		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��������ѳɹ�"},
	   {INT_TYPE_UPDATA_SUCC,				   	   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�����ɹ�"},

	   {INT_TYPE_START_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	   	   "����ʧ��"},
	   {INT_TYPE_STOP_FAIL, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	   	   "ͣ��ʧ��"},
	   {INT_TYPE_SHILED_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,		   "����ʧ��"},
	   {INT_TYPE_RESUME_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	   	   "�������ʧ��"},
	   {INT_TYPE_PHONE_CALL_FAIL,				   RECORD_FAULT, 	   TYPE_CRT_SHIELD_RESUME, "�绰����ʧ��"},
	   {INT_TYPE_PHONE_CONNECT_FAIL,			   RECORD_FAULT, 	   TYPE_CRT_SHIELD_RESUME, "�绰��ͨʧ��"},
	   {INT_TYPE_PHONE_HUNGUP_FAIL, 			   RECORD_FAULT, 	   TYPE_CRT_SHIELD_RESUME, "�绰�Ҷ�ʧ��"},
	   {INT_TYPE_RESET_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	   	   "��λʧ��"},
	   {INT_TYPE_SET_RARA_FAIL, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	  	   "�����޸�ʧ��"},
	   {INT_TYPE_SILENCE_FAIL,			   		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	   	   "�豸����ʧ��"},
	   {INT_TYPE_UPDATA_FAIL,				   	   RECORD_FAULT,	   TYPE_CRT_RESERVE,   	   "����ʧ��"},

	   {INT_TYPE_MANUAL_CONTROL_ALLOW,			   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	   	"�ֶ���������"},
	   {INT_TYPE_AUTO_CONTROL_ALLOW,			   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "�Զ���������"},
	   {INT_TYPE_SPRAY_ALLOW,					   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "��������"},
	   {INT_TYPE_PARTIAL_AUTO_CONTROL_ALLOW,	   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "�����Զ�����"},
	   
	   {INT_TYPE_MANUAL_CONTROL_FORBID, 		   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "�ֶ����ƽ�ֹ"},
	   {INT_TYPE_AUTO_CONTROL_FORBID,			   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "�Զ����ƽ�ֹ"},
	   {INT_TYPE_SPRAY_FORBID,					   REOCRD_MODE,	   	   TYPE_CRT_FAULT,	    "������ֹ"},
	   
	   {INT_TYPE_CHANNEL_SETUP, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ͨ������"},
	   {INT_TYPE_STS_PHONE_SETUP,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ͨ������"},
	   {INT_TYPE_LINK_SETUP,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��·����"},
	   
	   {INT_TYPE_EMERGENCY_BRODCAST_AUTO,		   REOCRD_MODE,	   	   TYPE_CRT_RESERVE,    "�Զ�Ӧ���㲥"},
	   {INT_TYPE_EMERGENCY_BRODCAST_MANUAL, 	   REOCRD_MODE,	   	   TYPE_CRT_RESERVE,    "�ֶ�Ӧ���㲥"},
	   {INT_TYPE_EMERGENCYT_OVER_AUTO,			   REOCRD_MODE, 	   TYPE_CRT_RESERVE,    "�Զ�Ӧ������"},
	   {INT_TYPE_EMERGENCYT_OVER_MANUAL,		   REOCRD_MODE, 	   TYPE_CRT_RESERVE,    "�ֶ�Ӧ������"},
	   
	   {INT_TYPE_ON_SCENCE_COMMANDER, 			   REOCRD_MODE,	   	   TYPE_CRT_RESERVE,    "�ֳ�ָ��"},
	   {INT_TYPE_ON_SCENCE_COMMANDER_OVER,		   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ָ�ӽ���"},
	   
	   {INT_TYPE_EXSOUND_BEGIN, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��������"},
	   {INT_TYPE_EXSOUND_OVER,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��������"},
	   {INT_TYPE_EXSOUND_PAUSE, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "������ͣ"},
	   {INT_TYPE_EXSOUND_RECOVER,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "�����ָ�"},
	   
	   {INT_TYPE_SDCARD_INSERT, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "SD������"},
	   {INT_TYPE_SDCARD_EXTRACT,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "SD���γ�"},
	   
	   {INT_TYPE_UDISK_INSERT,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "U�̲���"},
	   {INT_TYPE_UDISK_EXTRACT, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "U�̰γ�"},
	   
	   {INT_TYPE_SOUNDRECORD_BEGIN, 			   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "¼����ʼ"},
	   {INT_TYPE_SOUNDRECORD_OVER,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "¼������"},
	   
	   {INT_TYPE_SOUNDPLAY_BEGIN,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "������ʼ"}, 			   
	   {INT_TYPE_SOUNDPLAY_OVER,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��������"},
	   {INT_TYPE_SOUNDPLAY_PAUSE,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "������ͣ"},
	   {INT_TYPE_SOUNDPLAY_RECOVER, 			   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "�����ָ�"},
	   {INT_TYPE_AUDIO_LENGTH, 			   		   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��������"},
   
   
	   
	   {INT_TYPE_CHANNEL_BREAK, 				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ͨ���Ͽ�"}, 			   
	   {INT_TYPE_STS_PHONE_HUNGUP,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ͨ������"},
	   {INT_TYPE_LINK_BREAK,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "��·�Ͽ�"},
	   
	   {INT_TYPE_BACKUP_POWER_MAINTENANCE,		   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "����ά��"},
	   
	   {INT_TYPE_MAINPOW_ON,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "���繤��"},
	   {INT_TYPE_BACKPOW_ON,					   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "���繤��"},
	   
	   {INT_TYPE_SOFTWARE_UPGRADE,				   REOCRD_MODE,		   TYPE_CRT_RESERVE,	"��������"},
	   {INT_TYPE_DEVICE_ADDRESS_MODIFY, 		   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "�豸��ַ�޸�"},
	   {INT_TYPE_SYSTEM_MODE_MODIFY,			   REOCRD_MODE,		   TYPE_CRT_RESERVE,    "ϵͳģʽ����"},
	   
	   {INT_TYPE_POWER_ON,						   RECORD_POWERONOFF,  TYPE_CRT_FAULT,	    "�豸����"},
	   {INT_TYPE_POWER_OFF, 					   RECORD_POWERONOFF,  TYPE_CRT_FAULT,	    "�豸�ػ�"},
   
	   {INT_TYPE_SELFCHECK_CANCEL,			   	   REOCRD_SELFCHECK,   TYPE_CRT_RESERVE,   "�豸�Լ�ȡ��"},
	   {INT_TYPE_SELFCHECK_OVER,			   	   REOCRD_SELFCHECK,   TYPE_CRT_RESERVE,   "�豸�Լ����"},
	   {INT_TYPE_DEVICE_SELFCHECK ,		   		   REOCRD_SELFCHECK,   TYPE_CRT_RESERVE,   "�豸�Լ�"},
   
	   {INT_TYPE_EARLY_ALARM_RESET, 			   RECORD_RESUME,	   TYPE_CRT_RESERVE,    "Ԥ���ָ�"},
	   {INT_TYPE_ALARM_FROM_EARLYALM,			   RECORD_RESUME,	   TYPE_CRT_RESERVE,    "Ԥ����Ϊ��"},
	   {INT_TYPE_CACHE_OUT_RESET,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ͨ���ָ�����"},
	   
	   {INT_TYPE_NET_ON_LINE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,	"�ڸ�"},
	   {INT_TYPE_NET_OFF_LINE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,	"©��"},  
	   {INT_TYPE_NET_ON_LINE_AGAIN,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,	"����"},  

	   //----------------------------------------������Ϣ�¼�-------------------------------------//
	   {INT_TYPE_DEVICE_START_FEED_SUC,		   	   RECORD_ANSWER,	   TYPE_CRT_ANSWER,     "���������ɹ�"},
	   {INT_TYPE_DEVICE_START_FEED_FAIL, 	   	   RECORD_FAULT, 	   TYPE_CRT_ANSWER,     "��������ʧ��"},
	   
	   {INT_TYPE_DEVICE_STOP_FEED_SUC,		   	   RECORD_CLEAR, 	   TYPE_CRT_ANSWER,     "ֹͣ�����ɹ�"},
	   {INT_TYPE_DEVICE_STOP_FEED_FAIL,		   	   RECORD_FAULT, 	   TYPE_CRT_ANSWER,     "ֹͣ����ʧ��"},
	   
	   {INT_TYPE_SYSC_DATA_SUC, 				   RECORD_ANSWER,	   TYPE_CRT_DELAY,	    "��Ϣͬ���ɹ�"},
	   {INT_TYPE_SYSC_DATA_FAIL,				   RECORD_FAULT, 	   TYPE_CRT_DELAY,	    "��Ϣͬ��ʧ��"},
	   
	   {INT_TYPE_COMPARE_OVER,					   RECORD_OTHERS,	   TYPE_CRT_DELAY,	    "��Ϣ�˶Գɹ�"},
	   {INT_TYPE_COMPARE_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_DELAY,	    "��Ϣ�˶�ʧ��"},
	   
	   {INT_TYPE_MANUAL_DELAY_START,			   RECORD_DELAY, 	   TYPE_CRT_DELAY,	    "��ʱ��ʼ"},
	   {INT_TYPE_MANUAL_DELAY_CANCEL,			   RECORD_CANCEL,	   TYPE_CRT_DELAY,	    "��ʱȡ��"},
	   {INT_TYPE_DELAY_SUC, 					   RECORD_CANCEL,	   TYPE_CRT_DELAY,	    "��ʱ�ɹ�"},
	   
	   {INT_TYPE_SWITCH_INPUT_ON,				   RECORD_MONITER,	   TYPE_CRT_DELAY,	    "�����뿪����"},
	   {INT_TYPE_SWITCH_INPUT_OFF,				   RECORD_MONITER,	   TYPE_CRT_DELAY,	    "�����뿪����"},
	   {INT_TYPE_ANALOG_INPUT_VOLTAGE,			   RECORD_MONITER,	   TYPE_CRT_DELAY,	    "��ѹģ��������"},
	   {INT_TYPE_ANALOG_INPUT_CURRENT,			   RECORD_MONITER,	   TYPE_CRT_DELAY,	    "����ģ��������"},
	   
	   {INT_TYPE_PARA1_CHECK_SUC,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����1У׼�ɹ�"},
 	   {INT_TYPE_PARA1_CHECK_FAIL,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����1У׼ʧ��"},
 	   {INT_TYPE_PARA2_CHECK_SUC,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����2У׼�ɹ�"},
	   {INT_TYPE_PARA2_CHECK_FAIL,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����2У׼ʧ��"},
	   {INT_TYPE_PARA3_CHECK_SUC,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����3У׼�ɹ�"},
	   {INT_TYPE_PARA3_CHECK_FAIL,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����3У׼ʧ��"},
	   {INT_TYPE_PARA4_CHECK_SUC,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����4У׼�ɹ�"},
	   {INT_TYPE_PARA4_CHECK_FAIL,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����4У׼ʧ��"},
	   {INT_TYPE_PARA5_CHECK_SUC,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����5У׼�ɹ�"},
	   {INT_TYPE_PARA5_CHECK_FAIL,				   RECORD_ANSWER,	   TYPE_CRT_RESERVE,    "����5У׼ʧ��"},
	   //----------------------------------------������¼�-------------------------------------//
	   {INT_TYPE_FIRE_STATE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "����ǿ��"},
	   {INT_TYPE_TEMPE_STATE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�¶�"},
	   {INT_TYPE_SMOKE_STATE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��Ũ��"},
	   {INT_TYPE_GAS_STATE, 					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ȼ��Ũ��"},
	   {INT_TYPE_THEFT_STATE,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "����"},
	   {INT_TYPE_HUMIDITY_STATE,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ʪ��"},
	   {INT_TYPE_PRESSURE_STATE,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ѹ��"},
	   {INT_TYPE_CURRENT_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "����"},
	   {INT_TYPE_VOLTAGE_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��ѹ"},
	   {INT_TYPE_CURRENT_A_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "A�����"},
	   {INT_TYPE_CURRENT_B_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "B�����"},
	   {INT_TYPE_CURRENT_C_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "C�����"},
	   {INT_TYPE_VOLTAGE_A_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "A���ѹ"},
	   {INT_TYPE_VOLTAGE_B_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "B���ѹ"},
	   {INT_TYPE_VOLTAGE_C_STATE, 				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "C���ѹ"},
	   {INT_TYPE_VOLTAGE_CURRENT_STATE, 		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��ѹ����"},
	   {INT_TYPE_COMMUNICATION_SUCCESSRATE, 	   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "ͨѶ�ɹ���"},
	   {INT_TYPE_AMPLIFIER_INFORM,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "������Ϣ"},
	   
	   //----------------------------------------�������¼�-------------------------------------//
	   {INT_TYPE_EEPROM_RW_FAU, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "EEPROM��д����"},
	   {INT_TYPE_RAM_RW_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "RAM��д����"},
	   {INT_TYPE_FLASH_RW_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "FLASH��д����"},
	   {INT_TYPE_UDISK_R_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "U�̶�����"},
	   {INT_TYPE_UDISK_W_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "U��д����"},
   
	   
	   {INT_TYPE_EEPROM_ERASURE_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "EEPROM��������"},
	   {INT_TYPE_FLASH_ERASURE_FAU, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "FLASH��������"},
	   {INT_TYPE_GSM_REG_FAIL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "GSM NETע��ʧ��"},
	   {INT_TYPE_GPRS_REG_FAIL, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "GPRS NETע��ʧ��"},
	   {INT_TYPE_SIM_LOST,						   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "SIM��ȱʧ"},
	   {INT_TYPE_GPRS_NACK, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "GPRSģ��ͨ������Ӧ"},
	   {INT_TYPE_PRINTER_NO_PAPER,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "ȱֽ"},
	   {INT_TYPE_PRINTER_PAPER_JAM, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��ֽ"},
	   {INT_TYPE_PRINTER_OVER_TEMPE,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��ͷ����"},	   
	   {INT_TYPE_KEY_FAU,						   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��������"},
	   {INT_TYPE_HOST_KEY_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�������̹���"},
	   {INT_TYPE_SPEAKER_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����������"},
	   {INT_TYPE_AMPLIFIER_FAU, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���Ź���"},
	   {INT_TYPE_MIC_FAU,						   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "MIC����"},
	   {INT_TYPE_BLACKBOX_FAU,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���ݴ洢��Ԫ����"},
	   {IND_TYPE_RTC_CLOCK_FAU, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "RTCʱ�ӹ���"},
	   {IND_TYPE_ETHERNET_CONTR_FAU, 		       RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��̫������������"},

	   {INT_TYPE_SMOKE_SENSOR_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "������������"},
	   {INT_TYPE_TEMPE_SENSOR_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�¶ȴ���������"},
	   {INT_TYPE_UV_SENSOR_FAU, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���⴫��������"},
	   {INT_TYPE_INFRARED_SENSOR_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���⴫��������"},
	   {INT_TYPE_PYROELE_SENSOR_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���͵紫��������"},
	   {INT_TYPE_HUMIDITY_SENSOR_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "ʪ�ȴ���������"},
	   {INT_TYPE_CURRENT_SENSOR_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��������������"},
	   {INT_TYPE_FLAMEGAS_SENSOR_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��ȼ���崫��������"},
	   {INT_TYPE_SWITCH_SENSOR_FAU,			   	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���ش���������"},
	   {INT_TYPE_DOOR_FAU,			   			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�Ź���"},
	   
	   {INT_TYPE_REQUEST_MAINTENANCE,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����ά��"},
	   {INT_TYPE_PASSWORD_AGING,			       RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�������"},  
	   {INT_TYPE_INPUT_POWER_SHORT_CIRCUIT, 	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����Դ��·"},
	   {INT_TYPE_INPUT_POWER_OPEN_CIRCUIT,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����Դ��·"},
	   {INT_TYPE_INPUT_POWER_VOLTAGE_H, 		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����Դ��ѹ"},
	   {INT_TYPE_INPUT_POWER_VOLTAGE_L, 		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����ԴǷѹ"},
	   {INT_TYPE_INPUT_POWER_CURRENT_H, 		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����Դ����"},
	   {INT_TYPE_INPUT_POWER_FAULT,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�������"},
	   
	   {INT_TYPE_OUTPUT_POWER_SHORT_CIRCUIT,	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��Դ�����·"},
	   {INT_TYPE_OUTPUT_POWER_OPEN_CIRCUIT, 	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��Դ�����·"},
	   {INT_TYPE_OUTPUT_POWER_VOLTAGE_H,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��Դ�����ѹ"},
	   {INT_TYPE_OUTPUT_POWER_VOLTAGE_L,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��Դ���Ƿѹ"},
	   {INT_TYPE_OUTPUT_POWER_CURRENT_H,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��Դ�������"},
	   {INT_TYPE_MODULE_POWER_VOLTAGE_H,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��ѹ"},
	   {INT_TYPE_MODULE_POWER_VOLTAGE_L,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "Ƿѹ"},
	   
	   {INT_TYPE_BACKUP_POWER_SHORT_CIRCUIT,	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����·"},
	   {INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT, 	   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����·"},
	   {INT_TYPE_BACKUP_POWER_VOLTAGE_H,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����ѹ"},
	   {INT_TYPE_BACKUP_POWER_VOLTAGE_L,		   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����Ƿѹ"},
	   {INT_TYPE_BACKUP_POWER_WARNING,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���羯ʾ"},
	   {INT_TYPE_BACKUP_POWER_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�������"},
	   
   
	   
	   {INT_TYPE_BUS_SHORT_CIRCUIT, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���߶�·"},
	   {INT_TYPE_BUS_OPEN_CIRCUIT,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���߶�·"},
	   {INT_TYPE_BUS_VOLTAGE_H, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���߹�ѹ"},
	   {INT_TYPE_BUS_VOLTAGE_L, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����Ƿѹ"},
	   {INT_TYPE_BUS_CURRENT_H, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���߹���"},
	   {INT_TYPE_BLC_SHORT_H,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�ز����߶�·"},
	   {INT_TYPE_BLC_OPEN_H,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�ز����߶�·"},
	   
	   {INT_TYPE_INPUT1_SHORT_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����1��·"},
	   {INT_TYPE_INPUT1_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����1��·"},
	   {INT_TYPE_INPUT2_SHORT_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����2��·"},
	   {INT_TYPE_INPUT2_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����2��·"},
	   {INT_TYPE_INPUT3_SHORT_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����3��·"},
	   {INT_TYPE_INPUT3_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����3��·"},
	   {INT_TYPE_INPUT4_SHORT_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����4��·"},
	   {INT_TYPE_INPUT4_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "����4��·"},
	   
	   {INT_TYPE_OUTPUT1_SHORT_FAU, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���1��·"},
	   {INT_TYPE_OUTPUT1_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���1��·"},
	   {INT_TYPE_OUTPUT2_SHORT_FAU, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���2��·"},
	   {INT_TYPE_OUTUT2_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���2��·"},
	   {INT_TYPE_OUTPUT3_SHORT_FAU, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���3��·"},
	   {INT_TYPE_OUTPUT3_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���3��·"},
	   {INT_TYPE_OUTPUT4_SHORT_FAU, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���4��·"},
	   {INT_TYPE_OUTPUT4_OFF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "���4��·"},
	   {INT_TYPE_NET_LINE_FAULT,				   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "������·����"},
	   {INT_TYPE_TCP_CONNECT_OPEN_FAU,			   RECORD_FAULT,	   TYPE_CRT_FAULT,		"TCP���ӶϿ�����"},
	   {INT_TYPE_GPRS_CONNECT_OPEN_FAU,			   RECORD_FAULT,	   TYPE_CRT_FAULT,		"GPRS���ӶϿ�����"},

	   {INT_TYPE_NODEANS_FAU,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "������Ӧ��"},
	   {INT_TYPE_NODECOMM_FAU,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "���֧��"},
	   {INT_TYPE_ANSCHECK_FAU,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "Ӧ��У�����"},
	   {INT_TYPE_LIMIT_CONDITION_FAU,			   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "��������"},
	   {INT_TYPE_NODE_REGISTER_FAU, 			   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "�ڵ�δע��"},
	   {INT_TYPE_NODE_OFFLINE,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "�ڵ�δ����"},
	   {INT_TYPE_ADDR_OVERRUN,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "�Ĵ�����ַ����"},
	   {INT_TYPE_NODE_SHILED_STA,				   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "�豸������"},
	   {INT_TYPE_NODE_NUM_OVERFLOW, 			   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "�ڵ��������"},
	   {INT_TYPE_BUFFER_OVERFLOW,				   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "ͨ�Ż������"},
	   {INT_TYPE_DATA_LOST, 					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "����֡��ʧ"},
	   {INT_TYPE_DATA_CRC_FAU,					   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "����֡CRC����"},
	   {INT_TYPE_NET_COMM_FAULT,				   RECORD_FAULT,	   TYPE_CRT_FAULT,	    "����ͨ�Ź���"},
	   
   
   
	   {INT_TYPE_CODE_OVERFLOW, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�û������볬��"},
	   {INT_TYPE_CODE_ILLEGAL,					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�û������벻�Ϸ�"},
	   {INT_TYPE_LINK_FORMULA_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "������ʽ����"},
	   {INT_TYPE_DEVICE_INF_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�豸��Ϣ����"},
	   {INT_TYPE_INF_FAU,						   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "��·��Ϣ����"},
	   {INT_TYPE_USER_PROGRAM_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�û��������"},
	   {INT_TYPE_FLASH_90PERCENT_FAU,			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "¼���ڴ治��"},
	   {INT_TYPE_FLASH_FULL_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "¼����"},
	   
	   {INT_TYPE_SYSC_LINK_FAU, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "������ʽͬ������"},
	   {INT_TYPE_SYSC_DEVICE_FAU,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�豸��Ϣͬ������"},
	   {INT_TYPE_ALARM_ERR,                        RECORD_FAULT,       TYPE_CRT_FAULT,	    "�쳣����"},
	   
	   {INT_TYPE_UNREGGISTE_UPLOAD, 			   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "δע���ϱ�"},
	   {INT_TYPE_SHIELD_UPLOAD, 				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�������ϱ�"},
	   {INT_TYPE_RE_UPLOAD, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�ظ��ϱ�"},
	   {INT_TYPE_RE_ACTION, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�ظ�����"},
   
	   {INT_TYPE_MAINPOW_RECOVER,				   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "����ָ�����"},
	   {INT_TYPE_BACKUP_POWER_RECOVER,			   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "����ָ�����"},
	   {INT_TYPE_PRINTER_PAPER_RESUM,			   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "��ֽ"},
	   {INT_TYPE_BUFFER_OVERFLOW_RECOVER,		   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "��������ָ�"},
	   {INT_TYPE_REG_DEV_ONLINE,				   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "ע���豸����"},
	   {INT_TYPE_NET_LINE_RECOVER_NOMAL,		   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "������·�ָ�����"},
	   {INT_TYPE_NET_COM_RECOVER_NOMAL, 		   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "����ͨ�Żָ�����"},
	   {INT_TYPE_DEV_RECOVER_NOMAL, 		  	   RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "�豸�ָ�"},
	   {INT_TYPE_TCP_CONNECT_RECOVER,		       RECORD_ELIMINATE,	TYPE_CRT_RESERVE,	"TCP���ӻָ�����"},		   
	   {INT_TYPE_GPRS_CONNECT_RECOVER,		       RECORD_ELIMINATE,    TYPE_CRT_RESERVE,   "GPRS���ӻָ�����"},
	

	   //----------------------------------------��̬���¼�-------------------------------------//
	   
	   {INT_TYPE_REG_DEV_OFFLINE,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "ע���豸����"},
	   {INT_TYPE_NEW_DEV_ONLINE,				   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "�����豸����"},
	   {INT_TYPE_DEV_REPLACE,					   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "�滻�豸"},	   
	   {INT_TYPE_REPEAT_ID_DEV, 				   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "����ID�غ��豸"},
	   {INT_TYPE_REPEAT_UC_DEV, 				   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "����UC�غ��豸"},
	   {INT_TYPE_REFRESH_DELETE,				   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "ɾ���豸"}, 
	   {INT_TYPE_DEV_RECOVER, 		   			   RECORD_FAULT,       TYPE_CRT_RESERVE,    "�豸����"},
	   {INT_TYPE_DEV_FAULT, 		   			   RECORD_FAULT,       TYPE_CRT_RESERVE,    "�豸����"},
	   
	   {INT_TYPE_GET_MAIN_TOKEN,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��ȡ��վ����"},
	   {INT_TYPE_ONLINE_APPLIED,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��������"},
	   {INT_TYPE_COMMUN_SUCC_RATE,				   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�豸ͨ�ųɹ���"},
	   {INT_TYPE_UC_CHANGE, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "UC�仯"},
	   {INT_TYPE_ID_CHANGE, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "ID�仯"},
	   {INT_TYPE_CC_CHANGE, 					   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "CC�仯"},
	   {INT_TYPE_PARAMETER_CHANGE,				   RECORD_FAULT, 	   TYPE_CRT_FAULT,	    "�����仯"},
	   
   
	   {INT_TYPE_DEV_INFLOG_FINISH, 			   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�豸��Ϣ��¼���"},
	   {INT_TYPE_LOG_DEV_INF,					   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "��¼���豸��Ϣ"},
	   {INT_TYPE_LA_UNLAW_DEV_INF,				   RECORD_FAULT, 	   TYPE_CRT_RESERVE,    "LA�Ƿ����豸��Ϣ"},
	   {INT_TYPE_LOGIN_OPER,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "ϵͳ����Ա��¼"},
	   {INT_TYPE_LOGIN_ADMIN,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "ϵͳ����Ա��¼"},
	   {INT_TYPE_LOGIN_SUPER,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "��������Ա��¼"},
	   {INT_TYPE_REG_RENEW, 					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "����ע��"},
	   {INT_TYPE_REG_REFRESH,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "ˢ��ע��"},
	   {INT_TYPE_REG_AUTO,						   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�Զ�ע��"},
	   {INT_TYPE_REG_NETWORK,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "����ע��"},
	   {INT_TYPE_DEFINE_AUTO,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�豸�Զ�����"},
	   {INT_TYPE_DEFINE_ORDER,					   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�豸�̳ж���"},
	   {INT_TYPE_DEFINE_SERIAL, 				   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�豸��������"},
	   {INT_TYPE_FEILD_DEV_DEFINE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�ֳ��豸����"},
	   {INT_TYPE_BUS_PANEL_DEFINE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�����̶���"},
	   {INT_TYPE_MULTI_PANEL_DEFINE,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "ֱ���̶���"},
	   {INT_TYPE_BROCAST_PANEL_DEFINE,			   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�㲥�̶���"},
	   {INT_TYPE_CONTROLER_DEFINE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "����������"},
	   {INT_TYPE_PHONEDISTRI_PANEL_DEFINE,		   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "�绰�����̶���"},
	   {INT_TYPE_PRE_ALARM_DEFINE,				   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "Ԥ������"},
	   {INT_TYPE_LA_CHANGE,		                   RECORD_SETUP,	   TYPE_CRT_RESERVE,    "LA�޸�"},
	   {INT_TYPE_NODE_NORMAL,		     		   RECORD_OTHERS,	   TYPE_CRT_RESERVE,    "�ڵ�����"},
	   
	   {INT_TYPE_NULL,							   RECORD_MISC,		   TYPE_CRT_RESERVE,    "δ�����¼�"},
};
//======================================================================================================================
//

UINT8 const * const ALARM_TYPE_TAB[]=
{
    "��",           //0x00
	"���",           //0x01          
	"����",           //0x02
    "����",           //0x03
    "��ʱ",           //0x04
    "����",           //0x05
    "����",           //0x06 
    "Ԥ��",           //0x07
    "��λ",           //0x08	
    //������Ϣ��

	"�ͷ�",           //0x09
	"ֹͣ",           //0x0A
	"���",           //0x0B 
	"ȡ��",           //0x0C	
	"�ų�",           //0x0D 
	"���",           //0x0E
	"�ָ�",           //0x0F	
	//���ػ�
	"���ػ�",           //0x10
	"����",           //0x11
	
	//״̬
	"�Լ�",           //0x12
	"ģʽ",           //0x13
	
	//�û���״̬	
	"��������",           //0x14	
	"��������",           //0x15	
	"����",           //0x16
	"δ֪",           //0x17	
};
 

/*har const * const ACTION_TYPE_TAB[]=
{
	"ͣ��",
	"����",
	"��ת",
	"δ֪",
};*/



#endif
