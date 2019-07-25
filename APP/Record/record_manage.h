/*
 * record.h
 *
 *  Created on: 2012-7-31
 *      Author: Administrator
 */

#ifndef RECORD_MANAGE_H_
#define RECORD_MANAGE_H_

//------------------------------------- include -------------------------------------

#include "global.h"
//------------------------------------- define --------------------------------------bdata mode_browse_record;									//��¼���ģʽ

/*#define	RECORD_BROWSE_TIME			0
#define	RECORD_BROWSE_TYPE			1
#define	RECORD_BROWSE_AREA          2
#define	RECORD_BROWSE_LAN           3

#define	RECORD_BROWSE_LOCAL			0
#define	RECORD_BROWSE_CONTROLLER	1
*/
#define	LOCAL_RECORD_BROWSE_TIME			0
#define	LOCAL_RECORD_BROWSE_TYPE			1
#define	CONTR_RECORD_BROWSE_TIME		    2
#define	CONTR_RECORD_BROWSE_TYPE		    3



//----------------
//����
//������������������Ԥ������
//��������������λ���Զ����ֶ���������ͣ�����ֳ������������ֳ�����ͣ������������������ͣ��
//��������ʱ����ƿ��������������������������---------���ϱ�
//���ϣ���ƿ�ߡ������ߡ������ߡ���ͣ��----------���ϱ�
//----------------
//����
//���ϡ��������������ơ���ʱ����������������������
//----------------

#define	MESSAGE_TYPE_MAX_NUM			8

// ��¼���͵ĺ궨��
#define RECORD_FIRE							0x00
#define RECORD_MONITER					    0x01
#define RECORD_START						0x02
#define RECORD_ANSWER						0x03
#define RECORD_DELAY						0x04
#define RECORD_FAULT						0x05
#define RECORD_SHIELD						0x06
#define RECORD_EARLYFIRE				    0x07
#define	RECORD_RESET						0x08      // ��λ(�𾯵�������Ϣ)

#define RECORD_FREE         		        0x09      // �ͷ�(���)
#define RECORD_STOP							0x0A      // ֹͣ(����)
#define RECORD_CLEAR        		        0x0B      // ���(����)
#define	RECORD_CANCEL						0x0C      // ȡ��(��ʱ)
#define	RECORD_ELIMINATE				    0x0D      // �ų�(����)

#define	RECORD_RELEASE					    0x0E      // ���(����)
#define RECORD_RESUME       		        0x0F      // �ָ� 

#define	RECORD_POWERONOFF					0x10      //���ػ�
#define	RECORD_SETUP					    0x11      //����(�����塢ע��)

#define	REOCRD_SELFCHECK				    0x12     //�Լ�
#define	REOCRD_MODE				            0x13     // ģʽ(���Զ�)

#define RECORD_LOCALCOMMAND        		    0x14     // ��������
#define RECORD_NETCOMMAND                   0x15     //��������
#define	RECORD_OTHERS						0x16      // ����
#define	RECORD_MISC							0x17


#define RECORD_MAX              (RECORD_OTHERS)

#define	RECORD_STA_BUS_DN 			0x01

#define RECORD_MANNU_FIRE           0x01
#define RECORD_CONTROL_FIRE        0x02

// ��¼ģʽ�ĺ궨��
#define	RMODE_UC							0x00
#define	RMODE_CONTR_UC						0x01
//============ ��¼״̬����=========================================================

#define	RECORD_STA_INIT 								0xFF
#define	RECORD_STA_SUCC									0xE0//�ɹ�


//��¼�����־
#define  RECORD_TRAN_INIT   			0XFF
#define  RECORD_TRAN_SUC 				0x00

//��¼��ʾ��־
#define  RECORD_SHOW       				0XFF
#define  RECORD_NO_SHOW 				0x00

//��¼��·�豸
//#define	IC_DEV_SYS  				0x00		//������(����ϵͳ)
//#define	IC_DEV_LCD					0x01		//Һ��
//#define	IC_POWER					0xC8FB		// ���ڵ�Դ��ַ

#define IC_LOOP_CONTROL     		0xFF	  //������
#define IC_LOOP_SYS     			0xF0	  //ϵͳ�豸
#define IC_DEV_CONTROL              0xFF      //�������豸
#define	IC_DEV_SYS  				0x00	  //ϵͳ�豸
#define IC_DEV_MPOWER      			0x01      //����
#define IC_DEV_BAT          		0x02      //����
#define IC_DEV_OUT_POW          	0x03      //�����Դ
#define	IC_DEV_EXT_FLASH			0x04	  //�ⲿflash
#define	IC_DEV_NET_LINE     		0x05	  //������·
#define	IC_DEV_NET_COM	    		0x06	  //����ͨѶ
#define	IC_DEV_SIMCARD   	        0x07	  //sim��
#define	IC_DEV_OTHERS	    		0x08	  //ϵͳ�豸����


//==================	 record   ��ز����Ĵ洢λ��
//���flash�洢����Ч��־0xAA
#define FLASH_OFFSET_TIME       3
#define FLASH_OFFSET_TYPE       (UINT8)(&Record.Type-&Record.Sta)
#define FLASH_OFFSET_IC         (UINT8)(&Record.Ic.Loop-&Record.Sta)
#define FLASH_OFFSET_EVENTTYPE  (UINT8)(Record.EventType.byte-&Record.Sta)
#define FLASH_OFFSET_TRANFLAG   (UINT8)(&Record.TranFlag-&Record.Sta)
#define FLASH_OFFSET_SHOWFLAG   (UINT8)(&Record.ShowFlag-&Record.Sta)

//�¼�����ʱ���洢�ģ���record�ṹ���event�����е�Ԫ��λ��
#define  LEVEL1_COMM_SOURCE_LOC       0          //������Դ���������
#define  FRAME_ADDR_WAY_LOC           1          //����֡Ѱַ��ʽ
#define  FRAME_ADDR_UC				        2
//#define  FRAME_SER_LOC				      6          //����֡��ser�����ڿ������յ������ȶԴ���

#define  ADDR0_LOC                    3          //�豸�Ĵ�����ַ
#define  ADDR1_LOC                    4          //�豸�Ĵ�����ַ
#define  HANDLE_WAY_LOC               5          //�Ĵ���������ʽ
#define  DATA_LEN_LOC                 6          //�豸�Ĵ������ݳ���
#define  DATA_START_LOC               7          //�豸�Ĵ�������



//#define  DELAY_TIME0_LOC            56         //��ʱʱ��
//#define  DELAY_TIME1_LOC             57         //��ʱʱ��

//�ϱ������ģ�2400,2402����Ϣ
//��record�ṹ���event�����е�Ԫ��λ��
//#define	 RECORD_EVENT_CTR			0
//#define	 RECORD_EVENT_UC0			1
//#define	 RECORD_EVENT_UC1			2
//#define	 RECORD_EVENT_UC2			3
//#define	 RECORD_EVENT_UC3			4
//#define	 RECORD_EVENT_SER			5
//#define	 RECORD_EVENT_ADDR0			6
//#define	 RECORD_EVENT_ADDR1			7
//#define	 RECORD_EVENT_DATA			8

//#define  M_SOURCE_LOC       0          //������Դ���������
//#define  ADDR_WAY_LOC           1          //����֡Ѱַ��ʽ
//#define  FRAME_ADDR_UC				  2
//#define  FRAME_SER_LOC				  6          //����֡��ser�����ڿ������յ������ȶԴ���

//#define  ADDR0_LOC                    3          //�豸�Ĵ�����ַ
//#define  ADDR1_LOC                    4          //�豸�Ĵ�����ַ
//#define  HANDLE_WAY_LOC               5          //�Ĵ���������ʽ
//#define  DATA_LEN_LOC                 6          //�豸�Ĵ������ݳ���
//#define  DATA_START_LOC               7          //�豸�Ĵ�������


typedef struct 
{	
	//UINT16 Total;			//��¼��Ϣ����
	UINT16 Local_RecordSum; //ʱ�������¼��Ϣ����
	UINT16 StartPc;			//��¼��ʼƫ�����������ȴ���ļ�¼
	UINT16 SavePc;			//��¼�洢ƫ����
//	UINT16 RePc;			       //��¼��ȡָ��	
	UINT16 SheildPc;
	UINT16 P_bus;			//�Ӽ�¼�ж�ȡ��Ҫ�·�������
	UINT16 P_bro; 	        //�㲥�¼�ָ��
	UINT16 P_bus_up;		//�ϱ���ȡָ��
    UINT16 P_link;
    UINT16 Ptr_Box;			//��ϻ�Ӷ�ȡָ��
    UINT16 ttsRecordPc;
}RECORD_INF;
extern RECORD_INF RecordInf;





//extern uchar const uc_default[];
//extern uchar const uc_unknown[];

//extern uchar const * const cc_dummy_c[];

void Record_Browse(uchar type);
UINT16 Get_Event_Type_Number(void);

void Delete_All_Record(void);
void record_browse_show_info(uint16 offset);
void record_browse_detail_control(uchar key);
void record_browse_time_control(uchar key);
UINT8 Get_EventTypeGroup(UINT16 event_type);
void show_record(RECORD_STRUCT * record,uint16 line,uchar flag);
UINT8 get_record(UINT16 offset,RECORD_STRUCT * record_buffer);

void Record_Save(RECORD_STRUCT *record);
void Init_Record(uchar type);
void Record_Power_On_Off(UINT8);

void deal_record_sta(UINT16 p_record,UINT8 type_loc, UINT8 sta);

void record_clear(uint8 type);

UINT8 Record_Get_Event(UINT16 const event_code,UINT8 * str);
void record_tts(void);
UINT8 Record_Type_Is_Sel(UINT8 type,UINT8 sel_setting);
void Record_Change_Fire_Auto_Type(UINT8 tran_type);
UINT8 Record_TTS_Format(UINT8 * str);
void Record_Search_To_TTS(void);
void Record_Updata_Suc(void);



#endif

