#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "string.h"
#include "stdio.h"
#include <stdlib.h>
#include "stm32f0xx.h"

typedef unsigned char       UINT8;
typedef unsigned char       uchar;
typedef unsigned char       uint8;
typedef unsigned short int     UINT16;
typedef unsigned short int     uint16;
typedef unsigned long       UINT32;
typedef unsigned long       uint32;
typedef unsigned char 		UCHAR8; 
typedef unsigned char 		uchar8; 


#define BIT0 				(1u<<0)
#define BIT1 				(1u<<1)
#define BIT2 				(1u<<2)
#define BIT3 				(1u<<3)
#define BIT4 				(1u<<4)
#define BIT5 				(1u<<5)
#define BIT6 				(1u<<6)
#define BIT7 				(1u<<7)

#define		EI() 	__enable_irq()
#define		DI() 	__disable_irq()

#define		INTERNAL_RTC

#define   LEN_REG_LA       			1
#define   LEN_REG_UC       			5
#define   LEN_REG_ID       			12
#define   LEN_REG_CC       			32

#define   LEN_TEL_NUMBER            3

#define   FIRE_EXTINGUISHER_SYSTEM   0x01		//����
#define   DEVICE_TYPE                0x13		//
#define   TYPE_LEVEL                 0x34		//

#define		DEVICE_TYPE_OF_UC_CODE	 0x85	//����ģ��
#define		DEV_TYPE_CONTROL_UC      0x01   //������UC

#define 	MAX_LOOP_NUM					  4			//����·���� 
#define 	MAX_DEVICE_NUM					64			//��·������豸��


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif



typedef union 
{
    UINT8 byte;
    struct 
    {
        UINT8 b0       :1;
        UINT8 b1       :1;
        UINT8 b2       :1;
        UINT8 b3       :1;
        UINT8 b4       :1;
        UINT8 b5       :1;
        UINT8 b6       :1;
        UINT8 b7       :1; 
    }b;
}BIT_CHAR;

typedef struct 
{
    // ���̶���	
   	UINT8 project_name[32];       			//��������
    UINT8 project_address[32];			//���̵�ַ
    UINT8 project_linkman[16];			//��ϵ��
    UINT8 project_phone[16];			//��ϵ�绰
    UINT8 project_email[32];			//�ʼ���ַ


    UINT8 la;	//��Э��laλ���ڴ˴�
    UINT8 id[LEN_REG_ID];
    UINT8 uc[LEN_REG_UC];
    UINT8 cc[LEN_REG_CC];


    // �汾��Ϣ
    UINT8 software_ver[3];				//����汾
    UINT8 hardware_ver[3];				//Ӳ���汾
    UINT8 product_ver[3];				  //��Ʒ�汾

    //UINT8 calibr_value_rtc;			//rtcƵ��У׼ֵ	
   // UINT16 calibr_value_temp;			//�¶�У׼ֵ,25��ʱ��Ӧ��ADֵ	


	
	UINT8 ctr_type;
	UINT8 ctr_addr[LEN_REG_UC];
	UINT8 ctr_loop_start;			//��������ʼ��·������MODBUS���ȡ״̬
	UINT8 ctr_loop_end;			//������������·��
	UINT8 trans_equip_connect;
	UINT8 trans_addr[LEN_REG_UC];
	
	//�������
	
		UINT8 parallel_type;

	UINT8 reserve[65]; 				//Ԥ��

}CONFIG;
extern CONFIG System;



typedef union  										
{
	UINT8 two[2];
	UINT16 one;
} UWORD_UChAR;

typedef union
{
	UINT16  word;
	UINT8 byte[2];
}split;

typedef struct
{
    BIT_CHAR initialFlag; 					      							                    	    
	BIT_CHAR keyFlag; 					        										                    	    
	BIT_CHAR shieldFlag;
	BIT_CHAR wpFlag; 
    //UINT8 wp_invalid_time10s[3];
    
    UINT8 mode;					      //ϵͳ����ģʽ 0���� 1����

	UINT8 self_check;					//�Լ�

}RUNSTA;
extern RUNSTA RunSta;

typedef struct
{
	UINT8 Deadline;								//????10S
    UINT8 Random[8];           					//???
    UINT8 PasswordLevel;           				//????,???????????????????
}AUTH_DATA;
extern AUTH_DATA Auth;


typedef struct 
{	
    UINT8 Loop;
    UINT8 Dev;
}IC_STRUCT;
#define   LEN_RECORD_EVENT    58
typedef struct	
{
    UINT8 Sta;		              		// 0xff
    UINT8 Mode;							// ��¼ģʽ:����λ: 0:����ģʽ��1:����ģʽ
                                        // ����λ: 0:������¼��1:��������¼
    UINT8 Time[6];						// ��¼ʱ��: ������ʱ���� 	6
    UINT8 Id[LEN_REG_ID];				// ID 12
    UINT8 Uc[LEN_REG_UC];				// �û���(user code) 5
    UINT8 Cc[LEN_REG_CC];				// ��������(character code) 32
    IC_STRUCT Ic;                       // 2
    UINT8 Type;							// ��¼����,��ӦALARM_TYPE_TAB[]
    UINT8 EventLen;
    split EventType;					// �¼�����  4
    UINT8 Event[LEN_RECORD_EVENT];      // 58  ��һ���ֽڱ�ʾ�����¼���Դ:��һ���ֽڴ������LA
    UINT8 TranFlag;            			//0xff��ʾ�Ѿ�����,0x00��ʾδ�����
    UINT8 ShowFlag;                     //0xff��ʾ��Ҫ��ʾ,0x00��ʾ����Ҫ��ʾ
}RECORD_STRUCT;
extern RECORD_STRUCT Record;


#endif
