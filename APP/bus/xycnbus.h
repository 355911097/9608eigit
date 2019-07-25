/*
 * bus_dn.h
 *
 *  Created on: 2012-12-24
 *      Author: zjc
 */

#ifndef XYCNBUS_H_
#define XYCNBUS_H_
//------------------------------------- include -------------------------------------

#include "global.h"


#define 	DATA_LOC_TDID				19					// DATA????
#define 	DATA_LOC_TDLA				8
#define 	DATA_LOC_TDLA_LA			10					// ????????
//--------------------------------ADDRλ�ö���-----------------------------------
#define TC_LOC_HEAD 	            0				// ֡ͷλ�ö���
#define TC_LOC_LEN 		            1				// ����
#define TC_LOC_CTR 		            2				// ������
#define TC_LOC_MMADR	            3				// MMADR 
	
#define    TC_LOC_DATA_LA           7				// DATAλ�ö���

#define		S_HEAD		   			TC_LOC_HEAD		//֡ͷ
#define		S_LEN		   			TC_LOC_LEN		//����
#define		S_LEN2		   			0x02			//����1
#define		S_CTR		   			TC_LOC_CTR		//������
#define		S_MMADR		   			TC_LOC_MMADR	//MMADR λ��


//---------------- ADDR λ�ö���---------------
#define 	ADDR_LOC_LA				3				//���������ݳ��ȵ�ַλ��
#define 	ADDR_LOC_MMA_LA				4				//���������ݳ��ȵ�ַλ��
#define 	ADDR_LOC_MMA_TDLA_LA			5
#define 	ADDR_LOC_MMA_CTRLA_TDLA_LA  		6

#define 	ADDR_LOC_UC				3
#define 	ADDR_LOC_MMA_UC				4
#define 	ADDR_LOC_MMA_TDUC_UC			8
#define 	ADDR_LOC_MMA_CTRUC_TDUC_UC		12

#define 	ADDR_LOC_ID				3
#define 	ADDR_LOC_MMA_ID				4
#define 	ADDR_LOC_MMA_TDID_ID			16
#define 	ADDR_LOC_MMA_CTRID_TDID_ID		28

//---------------- SER λ�ö���----------------
#define		S_SER		   			0x03			//˳���
#define 	SER_LOC_BRO				3
#define 	SER_LOC_MMADR_BRO			4

#define	SER_LOC_LA				    (ADDR_LOC_LA+1)
#define 	SER_LOC_TDLA				(ADDR_LOC_LA+1)
#define 	SER_LOC_TDLA_LA				6
#define 	SER_LOC_CTRLA_TDLA_LA			7

#define 	SER_LOC_TDUC				8
#define 	SER_LOC_TDUC_UC				14
#define 	SER_LOC_CTRUC_TDUC_UC			16

#define 	SER_LOC_TDID				15
#define 	SER_LOC_TDID_ID				28
#define 	SER_LOC_CTRID_TDID_ID			40


//---------------- DI????----------------
#define		DI_LOC_BRO							(SER_LOC_BRO+1)
#define		DI_LOC_MMADR_BRO					(SER_LOC_MMADR_BRO+1)

#define	DI_LOC_LA                   (SER_LOC_LA+1)
#define		DI_LOC_TDLA							(SER_LOC_TDLA+1)
#define		DI_LOC_TDLA_LA						(SER_LOC_TDLA_LA+1)
#define		DI_LOC_CTRLA_TDLA_LA				(SER_LOC_CTRLA_TDLA_LA+1)

#define		DI_LOC_TDUC							(SER_LOC_TDUC+1)
#define		DI_LOC_TDUC_UC						(SER_LOC_TDUC_UC+1)
#define		DI_LOC_CTRUC_TDUC_UC				(SER_LOC_CTRUC_TDUC_UC+1)

#define		DI_LOC_TDID							(SER_LOC_TDID+1)
#define		DI_LOC_TDID_ID						(SER_LOC_TDID_ID+1)
#define		DI_LOC_CTRID_TDID_ID				(SER_LOC_CTRID_TDID_ID+1)


//---------------- DATAλ�ö���----------------
#define 	DATA_LOC_TDID				19
#define 	DATA_LOC_TDLA				8

//---------------- �ж��ϱ�λ�ö���----------------
#define 	DATA_LOC_INT_TDLA_LA		10


//=============================����֡ͷ���� ===========================
#define 	FRAME_HEADER			0x7F			//֡ͷ

#define		LEN_EXPAND_BIT		   	0x80			//������չλ
#define		MAX_LEN_1BYTE		   	0x80			//���ֽ���󳤶�
#define		MAX_LEN_2BYTE		   	MAX_LEN_1BYTE*256//˫�ֽ���󳤶�


//=============================CTR0 ���� =================================
#define		CTR_ADDR_MODE_BRO		0x07			//�㲥
#define		CTR_ADDR_MODE_LA		0x06			//LA
#define		CTR_ADDR_MODE_ID		0x05			//ID
#define		CTR_ADDR_MODE_UC		0x04			//UC

#define		CTR_ADDR_MODE			0x07			//��ַģʽ
#define		CTR_RE_OR_WR			0x08			//��д 0:�� 1:д
#define		CTR_ANSWER_STA			0x10			//Ӧ��λ 0:�쳣Ӧ�� 1:����Ӧ��
#define		CTR_MMADR				0x20			//�༶��ַ��չ 0:����չ 1:����չ
#define		CTR_TANS_DIR			0x40			//���䷽�� 0:�ӵ��� 1:������
#define		CTR_EXPAND_CTR			0x80			//��չ������ 0:����չ 1:����չ


#define		CTR_BRO_WR		   		0xE7			//�㲥д������
#define		CTR_BRO_RE		   		0xEF			//�㲥��������
#define		CTR_LA_WR		   		0xE6			//LAд������
#define		CTR_LA_RE		   		0xEE			//LA��������
#define		CTR_UC_WR		   		0xE4			//UCд������
#define		CTR_UC_RE		   		0xEC			//UC��������
#define		CTR_ID_WR		   		0xE5			//IDд������
#define		CTR_ID_RE		   		0xED			//ID��������

#define		CTR_NORMAL_ANS          0x10			//����Ӧ��

#define		CTR_MMADR_BRO_WR		0xC7			//�༶�㲥д������
#define		CTR_MMADR_BRO_RE	   	0xCF			//�㲥��������
#define		CTR_MMADR_LA_WR		   	0xC6			//LAд������
#define		CTR_MMADR_LA_RE		   	0xCE			//LA��������
#define		CTR_MMADR_UC_WR		   	0xC4			//UCд������
#define		CTR_MMADR_UC_RE		   	0xCC			//UC��������
#define		CTR_MMADR_ID_WR		   	0xC5			//IDд������
#define		CTR_MMADR_ID_RE		   	0xCD			//ID��������

#define		CTR_MMADR_UC_WR_ANS		0x92			//UC����

#define		CTR_MMADR_LA_RE_ANS		0x9E			//LA����,�ڵ���Ϣ�ϱ�
//#define		CTR_LA_RE_ANS			0xBe			//LA���룬��·��Ϣ�ϱ�
#define		CTR_LA_RE_ANS			0xBE			//LA���룬��·��Ϣ�ϱ�
#define		MMADR_INT_ANS		    0x86			//�ж��ϴ�MMADR


#define		CTR_MASK_DEV_ANS_ERR		0xAF			//�豸�����쳣Ӧ������
#define		CTR_MASK_DEV_ANS_OK			0xBF			//�豸��������Ӧ������

//=============================MMADR ���� =================================
#define		MMADR_2GRADE		   	0xE7			//MMADR��������
#define		MMADR_3GRADE		   	0xD5			//MMADR����������

#define		MMADR_1GRADE_UP		   	0x86			//MMADRһ�����д���

#define		MMADR_HAVE_TRANS_MASK	0x07			//MMADR�Ѵ�������
#define		MMADR_TO_TRANS_MASK		0x70			//MMADRҪ��������



//=============================DI �ؼ��Ӷ��� =================================
#define		DI_EXTENSION		   	0xC0			//DI��չ��
#define		DI_EXTEN_MODE_MASK		0xE0			//DI��չ�빤��ģʽ����

#define		DI_EXTEN_ADDR_MASK		0x003F			//DI��չ���ַ����

#define		DI_1BYTE_BIT_COMM		0x40			//DI���ֽ�λ����
#define		DI_2BYTE_BIT_COMM		0x20			//DI˫�ֽ�λ����

#define		DI_1BYTE_BYTE_COMM		0x80			//DI���ֽ��ֽ�����
#define		DI_2BYTE_BYTE_COMM		0x40			//DI˫�ֽ��ֽ�����

#define		DI_2BYTE_NBYTE_COMM		0x60			//DI˫�ֽ�N�ֽ�����
#define		DI_3BYTE_NBYTE_COMM		0x90			//DI���ֽ�N�ֽ��ֽ�����

#define		DI_BIT_DATA_MASK_1BYTE	0x20			//λ��������1�ֽ�

#define		DI_MUl_BLOCK_MASK		0xA0			//���ֽڿ����
#define		DI_EXTEN_DI_MASK		0x10			//��չdi





//=============================������ �ؼ��Ӷ��� =================================

#define		DATA_BYTE_MASK_ALL		0xFF			//�������ֽ�ȫ��Ч����


//=============================�������� ���� ============================
#define		DI_EVENT_INF		   				0x38		//�¼���Ϣ
#define		DI_DEBUG             				0x39		//���Բ���
#define		TYPE_DEBUG_LED						0x0B		//���


#define     DI_LA_LOG             		0x3A
#define     DI_UC_LOG      		        0x3B
#define     DI_ID_LOG            		0x3C

#define     DI_POLL_INT            		0x3F 			//Ѳ�켰�ж��ϱ�
#define	    BRO_ADDR_LA 				0xFF				//�㲥��ַ
														//һ������͸������״̬__���Ӧ��
															
#define	  BUS_ANS_TYPE_ERR 				  0					//����Ӧ�����
#define	  BUS_ANS_TYPE_OK 				  (BUS_ANS_TYPE_ERR+1)			//����Ӧ����ȷ
#define	  BUS_ANS_TYPE_SPECIAL 			(BUS_ANS_TYPE_OK+1)			//����Ӧ�����⣬ͨ��
#define	  BUS_ANS_TYPE_ABNORMAL 		(BUS_ANS_TYPE_SPECIAL+1)		//����Ӧ���쳣
#define	  BUS_ANS_TYPE_BRO 				  (BUS_ANS_TYPE_ABNORMAL+1)		//�㲥

//=============================λ�Ĵ��� ���� 20131210============================

#define     REG_BIT_ID_LOG_FLAG     	0x00    
#define     REG_BIT_LA_LOG_FLAG     	0x01  
#define     REG_BIT_UC_LOG_FLAG     	0x02  
#define     REG_BIT_CLEAR_RUN_STA  	 	0x03    

#define     REG_BIT_WP_CC				0x08    		//CCд����
#define     REG_BIT_WP_LA				0x09    		//LAд����
#define     REG_BIT_WP_UC				0x0A    		//UCд����

#define     REG_BIT_CHECK_FLAG     		0x18    		//�Լ��־
//=============================�ֽڼĴ��� ���� ============================

#define		REG_BYTE_INIT				0x00			//��ʼ��
#define		REG_BYTE_PARA_WR_EN			0x01			//����дʹ��
#define     REG_BYTE_SHIELD	     		0x02   			//����
#define     REG_BYTE_KEY_IDENTITY    	0x03  			//�ؼ���ʶ
#define     REG_BYTE_HEART_INTERVAL 	0x04    		//����֡���
#define     REG_BYTE_SYS_RUN_STA        0x05    		//�豸����״̬
#define     REG_BYTE_DUTY_ANSWER_TIME  	0x06    		//���Ӧ��ʱ��
#define     REG_BYTE_TRANS_EQUIP_CON  	0x07    		//��Ӵ����豸
#define     REG_BYTE_CTR_LOOP_START  	0x08    		//��ӿ�������ʼ��·
#define     REG_BYTE_CTR_LOOP_END  		0x09    		//��ӿ�����������·


#define     REG_DETECT_SET1             0X28           //����������ƽ
#define     REG_DETECT_SET2             0X29           //����������ƽ
#define     REG_DETECT_SET3             0X2A           //����������ƽ

#define     REG_INPUT_EVENT1            0X22           //�����������¼�����1
#define     REG_INPUT_EVENT2            0X24           //�����������¼�����2
#define     REG_INPUT_EVENT3            0X26           //�����������¼�����3


#define     REG_RECOVER_FACTORY         0X35         //�ָ���������
#define     REG_DEV_CTR     			0x38    	//�豸��¼����
#define     REG_BYTE_COM_RESULT			0x335//��ͨ�ųɹ���־

#define		REG_DEBUG	0X39//����
#define		TYPE_DEBUG_RESET 0X55	//��λ
#define		TYPE_DEBUG_UPDATE_START 0XF7	//��λ
#define		TYPE_DEBUG_UPDATE 0XFF	//��λ
#define		TYPE_DEBUG_UPDATE_OVER 0XFC	//��λ
#define     REG_BYTE_CTR_ERASE_RECARD 	 0x48						 //�������м�¼

#define     REG_MAINTENANCE   0X5A     //ά����Ϣ


#define     REG_BYTE_CTR_VERIFY_PERIOD  0x60    	//У������
#define     REG_BYTE_CTR_LANGUGE  		0x66    		//����ѡ��

#define     REG_BYTE_CTR_LCD_CONTRAST  	0x70    							//LCD �Աȶ�
#define     REG_BYTE_CTR_LCD_BRIGHTLESS (REG_BYTE_CTR_LCD_CONTRAST+1)    	//LCD ����
#define     REG_BYTE_CTR_TIME_CURSOR_UPDATA (REG_BYTE_CTR_LCD_BRIGHTLESS+1)    	//������ʱ��
#define     REG_BYTE_CTR_TIME_EXIT_FUN 	(REG_BYTE_CTR_TIME_CURSOR_UPDATA+2)    	//�˳��˵�ʱ��
#define     REG_BYTE_CTR_TIME_LOCK_SCREEN 	(REG_BYTE_CTR_TIME_EXIT_FUN+2)    	//����ʱ��
#define		REG_BYTE_CTR_RS232_PBS  	0x80    							//RS232����
#define		REG_BYTE_CTR_RS485_PBS  	(REG_BYTE_CTR_RS232_PBS+1)   


#define     REG_BYTE_CTR_POLL_CYC  			0x82    						//Ѳ������
#define     REG_BYTE_CTR_TTS_SET         	0x8F    							//TTS��������
					//�������ʱ��

#define     REG_BYTE_IP_ACQUIRE_MODE        0XB8//IP��ַ��ȡ��ʽ
#define     REG_BYTE_MESSAGE_MODE        0XB9//���ŷ���
#define		REG_BYTE_PROTOCOL_NUM			0xBE//������Э���
#define		REG_BYTE_CONTR_UC				0xBF//������UC


#define     REG_BYTE_CTR_MIMA1  	0xE0    							//һ������
#define     REG_BYTE_CTR_MIMA2  	(REG_BYTE_CTR_MIMA1+4)   			//��������
#define     REG_BYTE_CTR_MIMA3  	(REG_BYTE_CTR_MIMA2+4)    			//��������
#define     REG_BYTE_CTR_MIMA4  	(REG_BYTE_CTR_MIMA3+4)    			//�ļ�����

												//REG_BYTE_CTR_ERASE_LINK
#define     ERASE_ALL_LINK     		0xFF  			//��������������ʽ

													//REG_BYTE_CTR_ERASE_JD_INF
#define		ERASE_UC				0x3F			//����UC
#define     ERASE_CC      			0x7F  			//����CC
#define     CRT_TYPE     			0xBE  			//��ӿ�����Э���
#define     CTR_ADDR     			0xBF  			//��ӿ�����UC
#define     ERASE_UC_CC_PARA     		0xFF  			//����UC CC ���� 


#define     REG_RECORD_NUM       		0x110  					//��¼����

#define     REG_BYTE_CTR_OPERATE_AUTH  	0x120    					//����Ȩ��

#define     REG_BYTE_CTR_PRODUCT_PROCESS1  	0x130    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS2  	0x131    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS3  	0x132    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS4  	0x133    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS5  	0x134    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS6  	0x135    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS7  	0x136    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS8  	0x137    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS9  	0x138    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS10  0x139    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS11  0x13a    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS12  0x13b    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS13  0x13c    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS14  0x13d    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS15  0x13e    							//��������
#define     REG_BYTE_CTR_PRODUCT_PROCESS16  0x13f    							//��������

#define     REG_FIRE_ID       			0x162			//���������Ϣ
#define 	REG_BYTE_RANDON_DATA       	0X169
#define 	REG_BYTE_AUTH_DATA       	0X0171
#define     REG_RTC_SS       			0x179  
#define     REG_BYTE_ID       			0x180   		//ID
#define     REG_BYTE_UC       			0x18c   
#define     REG_BYTE_CC       			0x191   
#define     REG_BYTE_LA       				0x1B1 
#define 	REG_BYTE_SOFT_VER_REG       	0X01B2			
#define   	REG_BYTE_HARD_VER_REG       	0X01B5
#define   	REG_BYTE_PROTOCOL_VER_REG    	0X01B8	
#define     REG_BYTE_CTR_INFO        		0x01C0


#define     REG_BYTE_PROJECT_NAME		0x210   										//������Ϣ
#define     LEN_PROJECT_NAME			32 
#define     REG_BYTE_PROJECT_ADDR		(REG_BYTE_PROJECT_NAME+LEN_PROJECT_NAME)		//���̵�ַ
#define     LEN_PROJECT_ADDR			32
#define     REG_BYTE_PROJECT_CONTACT	(REG_BYTE_PROJECT_ADDR+LEN_PROJECT_ADDR)		//������
#define     LEN_PROJECT_CONTACT			16 
#define     REG_BYTE_PROJECT_TEL		(REG_BYTE_PROJECT_CONTACT+LEN_PROJECT_CONTACT)	//����绰
#define     LEN_PROJECT_TEL				16 
#define     REG_BYTE_PROJECT_EMAIL		(REG_BYTE_PROJECT_TEL+LEN_PROJECT_TEL)			//�ʼ�
#define     LEN_PROJECT_EMAIL			32  
//===================================����װ��ϵͳ����=======================================
#define     REG_BYTE_COM_MODE			0x83

#define     REG_BYTE_IP_ADDR_SERVER		0xA0
#define     REG_BYTE_PORT_SERVER		0xA4

#define     REG_BYTE_IP_ADDR_LOCAL		0xA6
#define     REG_BYTE_NETMASK_LOCAL		0xBA
#define     REG_BYTE_GATEWAY_LOCAL		0xAE
#define     REG_BYTE_PORT_LOCAL			0x29D
#define     REG_BYTE_MAC_LOCAL			0xB2

#define     REG_EMG_TEL_NUM1            0X290
#define     REG_EMG_TEL_NUM2            0X29B
#define     REG_EMG_TEL_NUM3            0X2A6

#define     REG_BYTE_ALARM_DELAY_AUTO	0x2B1
#define     REG_BYTE_ALARM_DELAY_MANUAL	0x2B2
#define     REG_BYTE_APN_MODE       	0x2B3
#define     REG_BYTE_RATE_MODE       	0x087
#define     REG_BYTE_SERVER_IP       	0x2B5
#define     REG_BYTE_SERVER_PORT       	0x2B9


#define     REG_RECORD       			0x400000		//�¼���¼
#define    	RECORD_LEN 					ALEN_FLASH_RECORD				//��Ϣ����
#define    	RECORD_NUM 					MAXN_FLASH_RECORD			//��¼����
#define  	RELADR_RECORD_DATA 			0x2f			//��¼����

#define    	REG_END       				(REG_RECORD+(RECORD_LEN*RECORD_NUM))	//�Ĵ�������

#define  	FLAG_DATA_BLOCK_VAILD 		0xaa			//���ݿ���Ч��־
#define  	FLAG_DATA_BLOCK_INVAILD 	0x55			//���ݿ���Ч��־



//=============================�������� ���� =================================
#define		OPSTYPE_SPECIAL_COMM		0x00			//��������
#define		OPSTYPE_BIT			0x01			//λ����
#define		OPSTYPE_BYTE			0x02			//�ֽڲ���
#define		OPSTYPE_MITI_BYTE		0x03			//���ֽڲ���

//==================֡�Ĵ�����ַ��Χ ���� ============================

#define		BIT_ADDR_RANGE_1BYTE		32				//���ֽ�λ��ַ��Χ
#define		BIT_ADDR_RANGE_2BYTE		1024			//˫�ֽ�λ��ַ��Χ

#define		BYTE_ADDR_RANGE_1BYTE		64				//���ֽ��ֽڵ�ַ��Χ
#define		BYTE_ADDR_RANGE_2BYTE		2048			//˫�ֽ��ֽڵ�ַ��Χ

#define		NBYTE_ADDR_RANGE_2BYTE		2048			//˫���ֽڵ�ַ��Χ
#define		NBYTE_ADDR_RANGE_3BYTE		65535			//���ֽ��ֽڵ�ַ��Χ
#define		NBYTE_ADDR_RANGE_4BYTE		8388608			//���ֽ��ֽڵ�ַ��Χ



//=============================���ƼĴ��� ���� ============================
#define		REG_STA_OFF		   		0x00			//�Ĵ���״̬-ֹͣ
#define		REG_STA_ON		   		0xC0			//�Ĵ���״̬-����
#define		REG_STA_ON_MK	   		0xC1			//�Ĵ���״̬-����
#define		REG_STA_PULSE		   	0x80			//�Ĵ���״̬-��˸

#define		REG_STA_SHEILD		   				(REG_STA_ON+1)		//�Ĵ���״̬-����
#define		REG_STA_RESUM				    	(REG_STA_SHEILD+1)	//�Ĵ���״̬-������

#define		REG_SG_STA_ON		   	REG_STA_ON//0xC0+1

//===========================�쳣Ӧ��������=================================
#define	NAS_ERR_LIMIT_CONDITION				0xFE			//�쳣Ӧ��-��������
#define	NAS_ERR_NOT_SUPORT				0xFD			//�쳣Ӧ��-��֧��
#define	NAS_ERR_TIMEOUT					0xFC			//�쳣Ӧ��-��վ��ʱ
#define	NAS_ERR_CRC_ERR					0xFB			//�쳣Ӧ��-��վCRC��
#define COMMUNICATION_FAULT         0xc5			   
#define	ANSWER_NO_SUPPORT       	0x01
#define	ANSWER_CONDITION_LIMIT  	0x03
#define		ANSWER_COM_ATTACK        	0x1F

//===========================��Ϣ�ϴ�����������������=======================



//����Ϊ���¼����ͱ�20150409����
//===========================�¼�����=======================
//�˹�����ʵʱ�¼����ȼ�0

//---------------------------����-----------------------------------//
//              ����������ʱ����������������¼���                  //
// -----------------------------------------------------------------//
#define     INT_TYPE_KEY_ACTION 				0x0000				//��������
//---------------------------����-----------------------------------//
//           ��Ա�����豸����ĳ���������ʱ���豸�������¼���         //
//------------------------------------------------------------------//
#define    	INT_TYPE_MANUAL_ALARM     	 		0x0100    			//�ֶ�����
//---------------------------����------------------------------------//
//			  ��Ա�����豸����ĳ������ʱ���豸�������¼���           //
//-------------------------------------------------------------------//
#define    	INT_TYPE_SET_TIME		         	0x0200    			//����ʱ��
#define    	INT_TYPE_SET_MANUAL_ENABLE   		0x0210 				//�����ֶ�����
#define    	INT_TYPE_SET_MANUAL_DISEN   		0x0211 				//�����ֶ���ֹ
#define    	INT_TYPE_SET_AUTO_ENABLE    		0x0220				//�����Զ�����
#define    	INT_TYPE_SET_AUTO_DISABLE	     	0x0221				//�����Զ���ֹ
#define    	INT_TYPE_SET_HALF_AUTO_ENABLE	    0x0230				//���ò����Զ�����
#define    	INT_TYPE_SET_HALT_AUTO_DISEN	    0x0231				//���ò����Զ���ֹ
#define    	INT_TYPE_SET_SPRAY_ENABLE    		0x0240				//������������
#define    	INT_TYPE_SET_SPRAY_DISEN    		0x0241				//����������ֹ
#define     INT_TYPE_SET_PRINT_FIRE				0X0250				//��ӡ��
#define		INT_TYPE_SET_PRINT_FIRE_AND_FEEDBACK 0x0251				//��ӡ�𾯺ͷ���
#define		INT_TYPE_SET_PINTT_ALL_EVENT		0x0252				//��ӡ������Ϣ
#define		INT_TYPE_SET_PRINT_DISEN			0x0253				//��ֹ��ӡ
#define    	INT_TYPE_SET_PRINTER        		0x0254				//��ӡŨ������
#define		INT_TYPE_SET_LCD_BACKGROUND_LIGHT	0x0255				//Һ����������
#define    	INT_TYPE_SET_PREALARM_ENABLE    	0x0260				//Ԥ����������
#define    	INT_TYPE_SET_PREALARM_DISEN    		0x0261				//Ԥ�����ܽ�ֹ
#define    	INT_TYPE_SET_PREALARM_RELATION    	0x0262				//Ԥ����������
#define    	INT_TYPE_SET_STARTUP_DIRECT_VIA_FIRE 0x0270				//��ֱ������
#define    	INT_TYPE_SET_STARTUP_VIA_LINKAGE    0x0271				//������ʽ����
#define    	INT_TYPE_SET_NETWORK_ENABLE    		0x0280				//����ͨ�ſ���
#define    	INT_TYPE_SET_NETWORK_DISEN    		0x0281				//����ͨ�Źر�
#define    	INT_TYPE_SET_ADD_LINKAGE            0x0290				//�½�������ʽ
#define    	INT_TYPE_SET_EDIT_LINKAGE    		0x0291				//�޸�������ʽ
#define    	INT_TYPE_SET_DELETE_LINKAGE         0x0292				//ɾ��������ʽ

////����������
//---------------------------��¼------------------------------------//
//�����豸����ĳ���������ʱ���������������¼���������¼�豸����        //      
//�˶�Ӧ�Ĳ�������                                                   //
//-------------------------------------------------------------------//
#define    	INT_TYPE_REQ_START		         	0x0300    			//��������
#define    	INT_TYPE_REQ_STOP     				0x0301  			//ͣ������
#define    	INT_TYPE_REQ_SHIELD  				0x0310 				//��������
#define    	INT_TYPE_REQ_RELEASE     			0x0311				//�����������
#define    	INT_TYPE_REQ_RESET					0x0320				//��λ����
#define    	INT_TYPE_REQ_SILENCE				0x0340				//��������
#define    	INT_TYPE_PARA_MODIFY 				0x0330				//�����޸�����
#define    	INT_TYPE_HELP_INF           		0x0350     			//������Ϣ 
#define    	INT_TYPE_LAN_SET_TIME           	0x0360     			//����Уʱ
#define    	INT_TYPE_LAN_READ_TIME        		0x0361     			//�����ȡʱ��


////���Ӧ���¼������ȼ�1����
////����ͨ������
#define   INT_TYPE_IDLOG_DATA           		0x2000     	//ID��¼��������
#define   INT_TYPE_LALOG_DATA	             	0x2001		//LA��¼��������
#define   INT_TYPE_UCLOG_DATA           		0x2002	    //UC��¼��������
#define   INT_TYPE_TRANSPARENT_TRANS    		0x2100     	//͸����Ϣ
#define   INT_TYPE_LINK_FORMULA_OUT	    		0x2200     	//������ʽ�����������
#define   INT_TYPE_LINK_OUT    	       			0x2201   	//������������ʽ���
#define   INT_TYPE_UC_FIND_LC           		0x2300		//�������ѯһ����
#define   INT_TYPE_MULTI_ADDRCOMM_RES			0x2400     	//�༶��ַ����Ӧ��
#define   INT_TYPE_INNER_UP_MSG				    0x2401		//�ڲ��ϱ���Ϣ:�ϱ���Ϣ:������𡢹㲥���绰
#define   INT_TYPE_WILDCOMM_EXECUTE_RIGHT     	0x2402		//ͨ��������ȷִ��
#define   INT_TYPE_WAN_UP_MSG				    0x2403		//�������ϱ���Ϣ

//#define   INT_TYPE_DEVICE_SYNCH               	0x2500		//�ڵ���Ϣͬ��


#define   INT_TYPE_EVENT_SYNCH               	0x2500		//�¼���Ϣͬ��
#define   INT_TYPE_RESET_SYNCH					0x2501		//�¼���Ϣ��λ
#define   INT_TYPE_MONITOR_PDC_SEND_DATA		0x2600      //���PDC���߷�������
#define   INT_TYPE_MONITOR_PDC_RECE_DATA     	0x2601 		//���PDC������������
#define   INT_TYPE_MONITOR_IMTMPI_SEND_DATA   	0x2602  	//���IMT/MPI���߷�������
#define   INT_TYPE_MONITOR_IMTMPI_RECE_DATA   	0x2603  	//���IMT/MPI����������
#define	  INT_TYPE_MONITOR_NODE_ID				0x2604		//��ؽڵ�ID
#define	  INT_TYPE_MONITOR_BROCAST_SEND_DATA	0x2610		//��ع㲥���߷���
#define	  INT_TYPE_MONITOR_BROCAST_RECE_DATA	0x2611		//��ع㲥��������




//---------------------------����------------------------------------//
//		�����Զ��������ܵ��豸��⵽��Ӧ����ʱ,�豸�������¼�	   	     //
//-------------------------------------------------------------------//
#define   INT_TYPE_FIRE_ALARM                	0x4000      	//���汨��
#define   INT_TYPE_TEMPERATURE_ALARM         	0x4001 			//�¶ȱ���
#define   INT_TYPE_SMOKE_ALARM               	0x4002  		//������
#define   INT_TYPE_CURRENT_LEAKAGE_ALARM     	0x4003        	//©�籨��
#define   INT_TYPE_GAS_LEAKAGE_ALARM         	0x4004          //ȼ��й©
#define   INT_TYPE_THEFT_ALARM               	0x4005  	    //����
#define   INT_TYPE_TIMEOUT_ALARM             	0x4006    		//��ʱ����
#define   INT_TYPE_ALARM                        0x400F          //�𾯱��� 
//---------------------------Ԥ��------------------------------------//
//�����Զ��������ܵ��豸�����䱨���ȼ���ֹһ������⵽�ͼ��𾯱�ʱ��    //
//�豸�������¼�                                          	   	     //
//-------------------------------------------------------------------//
#define   INT_TYPE_PRE_FIRE_ALARM				0x4100      	//��Ԥ��
#define   INT_TYPE_PRE_TEMPERATURE_ALARM        0x4101   		//�¾�Ԥ��
#define   INT_TYPE_PRE_SMOKE_ALARM              0x4102       	//�̾�Ԥ��
#define   INT_TYPE_PRE_THEFT_ALARM              0x4105       	//����Ԥ��
#define   INT_TYPE_PRE_ALARM                    0x410F          //��Ԥ��

//---------------------------���-----------------------------------//
//2016-7-19���Ӽ���¼�xt
//-------------------------------------------------------------------//
#define   INT_TYPE_MONITOR_FIRE_ALARM           0x4200			//��ػ��汨��
#define   INT_TYPE_MONITOR_TEMPERATURE_ALARM	0x4201			//����¶ȱ���
#define   INT_TYPE_MONITOR_SMOKE_ALARM			0x4202			//���������
#define   INT_TYPE_MONITOR_CURRENT_LEAKAGE_ALARM 0x4203			//���©�籨��
#define   INT_TYPE_MONITOR_GAS_LEAKAGE_ALARM	0x4204			//���ȼ��й©����
#define   INT_TYPE_MONITOR_THEFT_ALARM			0x4205			//��ص�������
#define   INT_TYPE_MONITOR_TIMEOUT_ALARM		0x4206			//��س�ʱ����
#define   INT_TYPE_MONITOR_ALARM		        0x420F			//��ܱ���
#define   INT_TYPE_MONITOR_HIGH_VOLTAGE			0x4210			//��ع�ѹ����
#define   INT_TYPE_MONITOR_LOW_VOLTAGE			0x4211			//���Ƿѹ����
#define   INT_TYPE_MONITOR_HIGH_CURRENT			0x4212			//��ع�������
#define   INT_TYPE_MONITOR_LOSE_PHASE			0x4213			//���ȱ�౨��
#define   INT_TYPE_MONITOR_FAULT_PHASE			0x4214			//��ش��౨��
#define   INT_TYPE_MONITOR_POWER_INTERRUPT		0x4215			//��ع����жϱ���
#define   INT_TYPE_MONITOR_FIRE_OUTPUT          0x422E          //��ػ����
#define   INT_TYPE_MONITOR_FAULT_OUTPUT         0x422F          //��ع������

	

//---------------------------�ɹ�------------------------------------//
//		       ���¼����������豸״̬�ı�ɹ�		                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_START_SUCESS                 0x6000      	//�豸����
#define   INT_TYPE_STOP_SUCESS                  0x6001      	//�豸ͣ��
#define   INT_TYPE_SHILED_SUCESS 	    	    0X6002			//�豸����
#define   INT_TYPE_RELEASE_SUCESS            	0x6003			//�豸�������

#define   INT_TYPE_PHONE_CALL					0x6004			//�绰����
#define   INT_TYPE_PHONE_CONNECT				0x6005			//�绰��ͨ
#define   INT_TYPE_PHONE_HUNGUP					0x6006			//�绰�Ҷ�

#define   INT_TYPE_RESET_SUCESS                 0x6007	    	//�豸��λ
#define   INT_TYPE_SET_RARA_SUCESS              0x6008	    	//�����޸ĳɹ�
#define   INT_TYPE_DEVICE_SILENCE               0x6009      	//�豸����


#define   INT_TYPE_STARTED                      0x600A      	//�豸������
#define   INT_TYPE_STOPPED                      0x600B      	//�豸��ͣ��
#define   INT_TYPE_SHILEDED                     0x600C      	//�豸������
#define   INT_TYPE_RELEASED                     0x600D      	//�豸�ѽ������

#define INT_TYPE_UPDATA_SUCC                  0x600E		//�����ɹ�



//---------------------------ʧ��------------------------------------//
//		       ���¼����������豸״̬�ı�ʧ��		                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_START_FAIL                   0x6100      	//�豸����ʧ��
#define   INT_TYPE_STOP_FAIL                    0X6101        	//�豸ͣ��ʧ��
#define   INT_TYPE_SHILED_FAIL 			        0X6102 			//�ֳ��豸����ʧ��
#define   INT_TYPE_RESUME_FAIL                  0X6103 			//�ֳ��豸�������ʧ��
#define   INT_TYPE_PHONE_CALL_FAIL            	0x6104			//�绰����ʧ��
#define   INT_TYPE_PHONE_CONNECT_FAIL          	0x6105			//�绰��ͨʧ��
#define   INT_TYPE_PHONE_HUNGUP_FAIL            0x6106			//�绰�Ҷ�ʧ��
#define   INT_TYPE_RESET_FAIL                   0X6107 			//��λʧ��
#define   INT_TYPE_SET_RARA_FAIL	            0X6108 			//�����޸�ʧ��
#define   INT_TYPE_SILENCE_FAIL          		0x6109	    	//�豸����ʧ��
#define INT_TYPE_UPDATA_FAIL                  0x610A		//����ʧ��

//---------------------------����------------------------------------//
//		       ���¼����������豸״̬��Ϊ����		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_MANUAL_CONTROL_ALLOW         0x6200      	//�ֶ���������
#define   INT_TYPE_AUTO_CONTROL_ALLOW           0x6201     		//�Զ���������
#define   INT_TYPE_SPRAY_ALLOW			        0x6202      	//��������
#define   INT_TYPE_PARTIAL_AUTO_CONTROL_ALLOW      0x6203     		//�����Զ���������
//---------------------------��ֹ------------------------------------//
//		       ���¼����������豸״̬��Ϊ��ֹ		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_MANUAL_CONTROL_FORBID        0x6300		     //�ֶ����ƽ�ֹ
#define   INT_TYPE_AUTO_CONTROL_FORBID      	0x6301			 //�Զ����ƽ�ֹ
#define   INT_TYPE_SPRAY_FORBID       		    0x6302			 //������ֹ
//---------------------------����------------------------------------//
//		       ���¼����������豸ĳ�����ӽ���		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_CHANNEL_SETUP			    0x6400	    	//ͨ������
#define   INT_TYPE_STS_PHONE_SETUP				0x6401	    	//�绰����	
#define   INT_TYPE_LINK_SETUP					0x6402	    	//��·����	

//---------------------------���Զ��㲥------------------------------//
//		       	                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_EMERGENCY_BRODCAST_AUTO		0x6500			//�Զ�Ӧ���㲥
#define   INT_TYPE_EMERGENCY_BRODCAST_MANUAL	0x6501			//�ֶ�Ӧ���㲥
#define   INT_TYPE_EMERGENCYT_OVER_AUTO			0x6502	    	//�Զ�Ӧ������
#define   INT_TYPE_EMERGENCYT_OVER_MANUAL		0x6503	    	//�ֶ��㲥����

#define   INT_TYPE_ON_SCENCE_COMMANDER			0x6510	    	//ָ�ӿ�ʼ
#define   INT_TYPE_ON_SCENCE_COMMANDER_OVER		0x6511	    	//ָ�ӽ���
#define   INT_TYPE_EXSOUND_BEGIN				0x6520	    	//��������
#define   INT_TYPE_EXSOUND_OVER			        0x6521	    	//��������
#define   INT_TYPE_EXSOUND_PAUSE			    0x6522	    	//������ͣ
#define   INT_TYPE_EXSOUND_RECOVER				0x6523	    	//�����ָ�
#define   INT_TYPE_SDCARD_INSERT				0x6530	    	//SD������
#define   INT_TYPE_SDCARD_EXTRACT				0x6531	    	//SD���γ�
#define   INT_TYPE_UDISK_INSERT				    0x6540	    	//U�̲���
#define   INT_TYPE_UDISK_EXTRACT				0x6541	    	//U�̰γ�
#define   INT_TYPE_SOUNDRECORD_BEGIN			0x6550	    	//¼����ʼ
#define   INT_TYPE_SOUNDRECORD_OVER				0x6551	    	//¼������
#define   INT_TYPE_SOUNDPLAY_BEGIN				0x6560	    	//��������
#define   INT_TYPE_SOUNDPLAY_OVER			    0x6561	    	//��������
#define   INT_TYPE_SOUNDPLAY_PAUSE			    0x6562	    	//������ͣ
#define   INT_TYPE_SOUNDPLAY_RECOVER		    0x6563	    	//�����ָ�
#define   INT_TYPE_AUDIO_LENGTH					0x6564			//����ʱ�䳤��

//---------------------------�Ͽ�------------------------------------//
//		       ���¼����������豸ĳ�����ӶϿ�		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_CHANNEL_BREAK                0x6600	   	 	//ͨ���Ͽ�
#define   INT_TYPE_STS_PHONE_HUNGUP			    0x6601	  	    //�绰�Ҷ�
#define   INT_TYPE_LINK_BREAK                   0x6602	   	 	//��·�Ͽ�
//		       ���¼����������豸����ά��״̬		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_BACKUP_POWER_MAINTENANCE     0x6610         	//����ά��
//---------------------------����------------------------------------//
//		       ���¼����������豸����״̬		                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_MAINPOW_ON				   0x6700	    	//���繤��
#define   INT_TYPE_BACKPOW_ON 				   0x6701     		//���繤��
//---------------------------�޸�------------------------------------//
//		       ���¼����������豸���Ե��޸�		                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_SOFTWARE_UPGRADE			   0x6800	    	//��������
#define   INT_TYPE_DEVICE_ADDRESS_MODIFY	   0x6801			//�豸��ַ�޸�
#define   INT_TYPE_SYSTEM_MODE_MODIFY		   0x6802	    	//ϵͳģʽ�޸�

//---------------------------����------------------------------------//
//		       �豸һЩ����״̬�ı���   		                     //
//-------------------------------------------------------------------//
#define   INT_TYPE_POWER_ON                    0x6900      	//�豸����
#define   INT_TYPE_POWER_OFF                   0x6901      	//�豸�ػ�
#define   INT_TYPE_SELFCHECK_CANCEL            0x6902		//�豸�Լ�ȡ��
#define   INT_TYPE_SELFCHECK_OVER              0x6903		//�豸�Լ����
#define   INT_TYPE_DEVICE_SELFCHECK            0x6904		//�豸�Լ�

#define   INT_TYPE_EARLY_ALARM_RESET		   0x6905	    //Ԥ���ָ�
#define   INT_TYPE_ALARM_FROM_EARLYALM	       0x6906		//Ԥ�����
#define   INT_TYPE_CACHE_OUT_RESET			   0x6907	    //ͨ���ָ�����

#define   INT_TYPE_NET_ON_LINE                  0x6A00      //ֵ��Ӧ���ڸ�
#define   INT_TYPE_NET_OFF_LINE                 0x6A01      //ֵ��Ӧ����
#define   INT_TYPE_NET_ON_LINE_AGAIN            0x6A02      //ֵ����Ա����

#define	  INT_TYPE_MONITOR_ALARM_FREE			0x6B00			//��ܱ����ͷ�

//---------------------------����------------------------------------//
//�豸������ʱ���������¼��������豸����״̬                         //                                                       
//-----------------------------------------------------------------//
#define   INT_TYPE_DEVICE_START_FEED_SUC        0x8000  	//���������ɹ� INT_TYPE_DEVICE_START_FEED_SUC
#define   INT_TYPE_DEVICE_START_FEED_FAIL       0x8001		//��������ʧ�� INT_TYPE_DEVICE_START_FEED_FAIL
//---------------------------ͣ��------------------------------------//
//�豸��ͣ��ʱ���������¼��������豸ͣ��״̬                         //                                                       
//-------------------------------------------------------------------//
#define   INT_TYPE_DEVICE_STOP_FEED_SUC         0x8100  	//ֹͣ�����ɹ� INT_TYPE_DEVICE_STOP_FEED_SUC
#define   INT_TYPE_DEVICE_STOP_FEED_FAIL	    0x8101		//ֹͣ����ʧ�� INT_TYPE_DEVICE_STOP_FEED_FAIL
//---------------------------ͬ��------------------------------------//
//�豸��ͬ��ʱ���������¼��������豸ͬ��״̬                         //                                                       
//-------------------------------------------------------------------//
#define   INT_TYPE_SYSC_DATA_SUC                 0x8200  		//��Ϣͬ���ɹ�
#define   INT_TYPE_SYSC_DATA_FAIL                0x8201  		//��Ϣͬ��ʧ��
#define   INT_TYPE_COMPARE_OVER                  0x8210        //�豸�˶����
#define   INT_TYPE_COMPARE_FAIL                  0x8211        //�豸�˶�ʧ��
//---------------------------��ʱ------------------------------------//
//������ʱ���ܵ��豸���������¼��������豸��ʱ��״̬                 //                                                       
//-------------------------------------------------------------------*/
#define   INT_TYPE_MANUAL_DELAY_START   		0x8300      //��ʱ��ʼ
#define   INT_TYPE_MANUAL_DELAY_CANCEL      	0X8301		//��ʱȡ��
#define   INT_TYPE_DELAY_SUC     				0X8302		//��ʱ�ɹ�
//---------------------------����------------------------------------//
//��������ָʾ���ܵ��豸���������¼��������豸�����״̬             //                                                       
//-------------------------------------------------------------------//
#define   INT_TYPE_SWITCH_INPUT_ON            	0x8400       //�����뿪����
#define   INT_TYPE_SWITCH_INPUT_OFF           	0x8401       //�����뿪����
#define   INT_TYPE_ANALOG_INPUT_VOLTAGE       	0x8410       //��ѹģ��������
#define   INT_TYPE_ANALOG_INPUT_CURRENT		  	0x8411		 //����ģ��������
//---------------------------У׼------------------------------------//
//���в�����У׼���ܵ��豸���������¼��������豸У׼��״̬           //                                                       
//-------------------------------------------------------------------//
#define   INT_TYPE_PARA1_CHECK_SUC				0x9000      //����1У׼�ɹ�
#define   INT_TYPE_PARA1_CHECK_FAIL      		0x9001 		//����1У׼ʧ��
#define   INT_TYPE_PARA2_CHECK_SUC    			0x9010 		//����2У׼�ɹ�
#define   INT_TYPE_PARA2_CHECK_FAIL     		0x9011 		//����2У׼ʧ��
#define   INT_TYPE_PARA3_CHECK_SUC     			0x9020 		//����3У׼�ɹ�
#define   INT_TYPE_PARA3_CHECK_FAIL    			0x9021 		//����3У׼ʧ��
#define   INT_TYPE_PARA4_CHECK_SUC    			0x9030 		//����4У׼�ɹ�
#define   INT_TYPE_PARA4_CHECK_FAIL     		0x9031 		//����4У׼ʧ��
#define   INT_TYPE_PARA5_CHECK_SUC     			0x9040 		//����5У׼�ɹ�
#define   INT_TYPE_PARA5_CHECK_FAIL     		0x9041 		//����5У׼ʧ��
#define   INT_TYPE_ACTION_FEEDBACK     		    0x90F0 		//��������

#define   INT_TYPE_AUTO_DELAY_START     		0x9110      //���������豸������ʱ��ʼ
#define   INT_TYPE_AUTO_DELAY_CANCEL   			0x9111      //���������豸������ʱ��ֹ


//������ʵʱ��Ϣ
#define   INT_TYPE_FIRE_STATE           		0xA000      //����ǿ��
#define   INT_TYPE_TEMPE_STATE         			0xA001      //�¶�
#define   INT_TYPE_SMOKE_STATE          		0xA002      //��Ũ��
#define   INT_TYPE_GAS_STATE            		0xA003      //ȼ��Ũ��
#define   INT_TYPE_THEFT_STATE          		0xA004      //����
#define   INT_TYPE_HUMIDITY_STATE       		0xA005      //ʪ��
#define   INT_TYPE_PRESSURE_STATE       		0xA006      //ѹ��
#define   INT_TYPE_CURRENT_STATE        		0xA007 		//����
#define   INT_TYPE_VOLTAGE_STATE        		0xA008 		//��ѹ
#define   INT_TYPE_CURRENT_A_STATE        		0xA009 		//A�����
#define   INT_TYPE_CURRENT_B_STATE        		0xA00A 		//B�����
#define   INT_TYPE_CURRENT_C_STATE        		0xA00B 		//C�����
#define   INT_TYPE_VOLTAGE_A_STATE        		0xA00C 		//A���ѹ
#define   INT_TYPE_VOLTAGE_B_STATE        		0xA00D 		//B���ѹ
#define   INT_TYPE_VOLTAGE_C_STATE        		0xA00E 		//C���ѹ
#define   INT_TYPE_VOLTAGE_CURRENT_STATE        0xA00F 		//��ѹ����
#define   INT_TYPE_COMMUNICATION_SUCCESSRATE    0xA100 		//ͨѶ�ɹ���
#define   INT_TYPE_AMPLIFIER_INFORM        		0xA101 		//������Ϣ
//�������¼������ȼ�6��
//�豸����Ӳ��������
//---------------------------����------------------------------------//
//		       ���¼����������豸������صĹ���		                 //
//-------------------------------------------------------------------//
#define   INT_TYPE_EEPROM_RW_FAU           		0xC000	    //EEPROM��д����
#define   INT_TYPE_RAM_RW_FAU              		0xC001      //RAM��д����
#define   INT_TYPE_FLASH_RW_FAU            		0xC002      //FLASH��д����
#define   INT_TYPE_UDISK_R_FAU            		0xC003      //U�̶�����
#define   INT_TYPE_UDISK_W_FAU            		0xC004      //U��д����
#define   INT_TYPE_EEPROM_ERASURE_FAU   	 	0xC010		//EEPROM��������
#define   INT_TYPE_FLASH_ERASURE_FAU       		0xC011    	//FLASH��������
#define   INT_TYPE_GSM_REG_FAIL      		 	0xC020		//GSM NETע��ʧ��
#define   INT_TYPE_GPRS_REG_FAIL           		0xC021    	//GPRS NETע��ʧ��
#define   INT_TYPE_SIM_LOST	             		0xC030      //SIM��ȱʧ
#define   INT_TYPE_GPRS_NACK               		0xC031	    //GPRSģ��ͨ������Ӧ
#define   INT_TYPE_PRINTER_NO_PAPER      	 	0xC040      //��ӡ��ȱֽ
#define   INT_TYPE_PRINTER_PAPER_JAM       		0xC041    	//��ӡ����ֽ
#define   INT_TYPE_PRINTER_OVER_TEMPE      		0xC042      //��ӡ������
#define   INT_TYPE_KEY_FAU              	 	0xC050    	//��������
#define   INT_TYPE_HOST_KEY_FAU            		0xC051    	//�������̹���
#define   INT_TYPE_SPEAKER_FAU          	 	0xC060      //����������
#define   INT_TYPE_AMPLIFIER_FAU        	 	0xC061      //���Ź���
#define   INT_TYPE_MIC_FAU        		 		0xC062		//MIC����
#define   INT_TYPE_BLACKBOX_FAU	         		0xC070      //���ݴ洢��Ԫ����
#define   IND_TYPE_RTC_CLOCK_FAU                0xC0B0      //RTCʱ�ӹ���
#define   IND_TYPE_ETHERNET_CONTR_FAU           0xC0C0      //��̫������������

#define   INT_TYPE_SMOKE_SENSOR_FAU     		0xC100      //������������
#define   INT_TYPE_TEMPE_SENSOR_FAU     		0xC101      //�¶ȴ���������
#define   INT_TYPE_UV_SENSOR_FAU        		0xC102      //���⴫��������
#define   INT_TYPE_INFRARED_SENSOR_FAU  		0xC103      //���⴫��������
#define   INT_TYPE_PYROELE_SENSOR_FAU   		0xC104      //���͵紫��������
#define   INT_TYPE_HUMIDITY_SENSOR_FAU  		0xC105      //ʪ�ȴ���������
#define   INT_TYPE_CURRENT_SENSOR_FAU   		0xC106      //��������������
#define   INT_TYPE_FLAMEGAS_SENSOR_FAU  		0xC107      //��ȼ���崫��������
#define   INT_TYPE_SWITCH_SENSOR_FAU			0xC108		//���ش���������
#define   INT_TYPE_DOOR_FAU						0xC109		//�Ź���
//--------------------------- ά��-----------------------------------//
//	��Ҫ����ά�����豸���������¼�����֪����Ҫ����ά��				     //
//-------------------------------------------------------------------//
#define   INT_TYPE_REQUEST_MAINTENANCE     		0xC200	   	//����ά��
#define   INT_TYPE_PASSWORD_AGING    		0xC201	   	//����ά��


////--------------------------- ����------------------------------------//
////                       ������صĹ���      	          		        //
////--------------------------------------------------------------------//
#define   INT_TYPE_INPUT_POWER_SHORT_CIRCUIT    0xC300    	//�����Դ��·
#define   INT_TYPE_INPUT_POWER_OPEN_CIRCUIT     0xC301    	//�����Դ��·
#define   INT_TYPE_INPUT_POWER_VOLTAGE_H        0xC302    	//�����Դ��ѹ
#define   INT_TYPE_INPUT_POWER_VOLTAGE_L        0xC303    	//�����ԴǷѹ
#define   INT_TYPE_INPUT_POWER_CURRENT_H        0xC304    	//�����Դ����
#define   INT_TYPE_INPUT_POWER_FAULT            0xC305    	//�����Դ����
#define   INT_TYPE_OUTPUT_POWER_SHORT_CIRCUIT   0xC310    	//�����Դ��·
#define   INT_TYPE_OUTPUT_POWER_OPEN_CIRCUIT    0xC311    	//�����Դ��·
#define   INT_TYPE_OUTPUT_POWER_VOLTAGE_H       0xC312    	//�����Դ��ѹ
#define   INT_TYPE_OUTPUT_POWER_VOLTAGE_L       0xC313    	//�����ԴǷѹ
#define   INT_TYPE_OUTPUT_POWER_CURRENT_H       0xC314    	//�����Դ����
#define   INT_TYPE_MODULE_POWER_VOLTAGE_H       0xC315    	//��Դģ�������ѹ
#define   INT_TYPE_MODULE_POWER_VOLTAGE_L       0xC316    	//��Դģ�����Ƿѹ
#define   INT_TYPE_BACKUP_POWER_SHORT_CIRCUIT   0xC320    	//�����·
#define   INT_TYPE_BACKUP_POWER_OPEN_CIRCUIT    0xC321    	//�����·
#define   INT_TYPE_BACKUP_POWER_VOLTAGE_H       0xC322    	//�����ѹ
#define   INT_TYPE_BACKUP_POWER_VOLTAGE_L       0xC323    	//����Ƿѹ
#define   INT_TYPE_BACKUP_POWER_WARNING         0xC324    	//���羯ʾ
#define   INT_TYPE_BACKUP_POWER_FAU             0xC325    	//�������
#define   INT_TYPE_BUS_SHORT_CIRCUIT            0xC330    	//���߶�·
#define   INT_TYPE_BUS_OPEN_CIRCUIT             0xC331    	//���߶�·
#define   INT_TYPE_BUS_VOLTAGE_H                0xC332    	//���߹�ѹ
#define   INT_TYPE_BUS_VOLTAGE_L                0xC333    	//����Ƿѹ
#define   INT_TYPE_BUS_CURRENT_H                0xC334    	//���߹���
#define   INT_TYPE_BLC_SHORT_H			        0xC335  	//�ز����߶�·
#define   INT_TYPE_BLC_OPEN_H			        0xC336   	//�ز����߶�·

#define   INT_TYPE_24V_OPEN_FAV			        0xC340   	//24V��·����


#define   INT_TYPE_INPUT1_SHORT_FAU     		0xC400      //����ͨ��1��·����
#define   INT_TYPE_INPUT1_OFF_FAU       		0xC401      //����ͨ��1��·����
#define   INT_TYPE_INPUT2_SHORT_FAU     		0xC410      //����ͨ��2��·����
#define   INT_TYPE_INPUT2_OFF_FAU       		0xC411      //����ͨ��2��·����
#define   INT_TYPE_INPUT3_SHORT_FAU     		0xC420      //����ͨ��3��·����
#define   INT_TYPE_INPUT3_OFF_FAU       		0xC421      //����ͨ��3��·����
#define   INT_TYPE_INPUT4_SHORT_FAU     		0xC430      //����ͨ��4��·����
#define   INT_TYPE_INPUT4_OFF_FAU       		0xC431      //����ͨ��4��·����

#define   INT_TYPE_OUTPUT1_SHORT_FAU    		0xC440     	 	//���ͨ��1��·����
#define   INT_TYPE_OUTPUT1_OFF_FAU      		0xC441      	//���ͨ��1��·����
#define   INT_TYPE_OUTPUT2_SHORT_FAU    		0xC450      	//���ͨ��2��·����
#define   INT_TYPE_OUTUT2_OFF_FAU       		0xC451      	//���ͨ��2��·����
#define   INT_TYPE_OUTPUT3_SHORT_FAU    		0xC460      	//���ͨ��3��·����
#define   INT_TYPE_OUTPUT3_OFF_FAU      		0xC461      	//���ͨ��3��·����
#define   INT_TYPE_OUTPUT4_SHORT_FAU    		0xC470      	//���ͨ��4��·����
#define   INT_TYPE_OUTPUT4_OFF_FAU      		0xC471      	//���ͨ��4��·����

#define   INT_TYPE_NET_LINE_FAULT               0xC4F0      	//������·����
#define   INT_TYPE_TCP_CONNECT_OPEN_FAU         0xC4F1      	//TCP���ӶϿ�
#define   INT_TYPE_GPRS_CONNECT_OPEN_FAU        0xC4F2      	//GPRS���ӶϿ�


//�豸ͨѶ����
#define   INT_TYPE_NODEANS_FAU          		0xC500      //�ڵ���Ӧ��
#define   INT_TYPE_NODECOMM_FAU         		0xC501      //�ڵ����֧��
#define   INT_TYPE_ANSCHECK_FAU         		0xC502      //Ӧ��У�����
#define   INT_TYPE_LIMIT_CONDITION_FAU  		0xC503      //�������޲�����ȷִ��
#define   INT_TYPE_NODE_REGISTER_FAU    		0xC504      //�ڵ�δע��
#define   INT_TYPE_NODE_OFFLINE		      		0xC505      //�ڵ�δ����
#define   INT_TYPE_ADDR_OVERRUN         		0xC506      //�Ĵ�����ַ����
#define   INT_TYPE_NODE_SHILED_STA      		0xC507      //�ڵ㱻����

#define   INT_TYPE_NODE_NUM_OVERFLOW    		0xC508      //�ڵ��������
#define   INT_TYPE_BUFFER_OVERFLOW   			0xC509      //ͨ�Ż������
//bootʹ��
#define   INT_TYPE_DATA_LOST            		0xC50A      //����֡��ʧ
#define   INT_TYPE_DATA_CRC_FAU         		0xC50B      //����֡CRC����

#define   INT_TYPE_NET_COMM_FAULT               0xC50C      	//����ͨѶ����

//--------------------------- �洢------------------------------------//
//							   �洢��صĹ���			        	 //
//-------------------------------------------------------------------//
#define   INT_TYPE_CODE_OVERFLOW              0xC600        //�û������볬��
#define   INT_TYPE_CODE_ILLEGAL               0xC601        //�û������벻�Ϸ�
#define   INT_TYPE_LINK_FORMULA_FAU     	  0xC602      	//������ʽ����
#define   INT_TYPE_DEVICE_INF_FAU             0xC603      	//�豸��Ϣ����
#define   INT_TYPE_INF_FAU                    0xC604        //��·��Ϣ����
#define   INT_TYPE_USER_PROGRAM_FAU     	  0xC605      	//�û��������
#define   INT_TYPE_FLASH_90PERCENT_FAU     	  0xC606      //¼���ڴ治�㣬�Ѵ�flash90%
#define   INT_TYPE_FLASH_FULL_FAU     	   	  0xC607      //¼����


//--------------------------- ͬ��------------------------------------//
//							   ͬ��������صĹ���					 //
//-------------------------------------------------------------------//
#define   INT_TYPE_SYSC_LINK_FAU        	    0xC700      	//������ʽͬ������
#define   INT_TYPE_SYSC_DEVICE_FAU              0xC701      	//�豸��Ϣͬ������

//--------------------------- ��------------------------------------//
//							   ����            					 //
//-------------------------------------------------------------------//
#define   INT_TYPE_UNREGGISTE_UPLOAD       	  	0xC800     		//δע���ϱ�
#define   INT_TYPE_SHIELD_UPLOAD              	0xC801      	//�����ϱ�
#define   INT_TYPE_RE_UPLOAD          		  	0xC802     	 	//�ظ��ϱ�
#define   INT_TYPE_RE_ACTION                  	0xC803     	 	//�ظ�����
#define   INT_TYPE_ALARM_ERR                    0xC805      	//�쳣����

//--------------------------- ���ϻָ� -------------------------------//
//						  ���ֹ��ϻָ��¼�					         //
//--------------------------------------------------------------------//
#define   INT_TYPE_MAINPOW_RECOVER              0xD000    		//����ָ�����
#define   INT_TYPE_BACKUP_POWER_RECOVER         0xD001    		//����ָ�����
#define   INT_TYPE_PRINTER_PAPER_RESUM      	0xD002      	//��ӡ����ֽ
#define   INT_TYPE_BUFFER_OVERFLOW_RECOVER     	0xD003     	 	//��������ָ�
#define   INT_TYPE_REG_DEV_ONLINE    			0xD004     		//ע���豸����
#define   INT_TYPE_BLC_NORMAL_H			        0xD005      	//�ز���������
#define   INT_TYPE_NET_LINE_RECOVER_NOMAL       0xD006      	//������·�ָ�����
#define   INT_TYPE_NET_COM_RECOVER_NOMAL        0xD007      	//����ͨ�Żָ�����
#define   INT_TYPE_DEV_RECOVER_NOMAL			0xD008			//�豸�ָ�
#define   INT_TYPE_TCP_CONNECT_RECOVER          0xD009     	 	//TCP���ӻָ�
#define   INT_TYPE_GPRS_CONNECT_RECOVER         0xD00A      	//GPRS���ӻָ�
#define   INT_TYPE_SIM_RECOVER         			0xD00B      //SIM���ӻָ�

#define   INT_TYPE_SENSOR_RECOVER               0xD00C      	//�������ָ�
#define   INT_TYPE_BUS_RECOVER                  0xD00D      	//�ź��߻ָ�
//#define   INT_TYPE_24V_RECOVER                  0xD00F      	//24V�ָ�
#define   INT_TYPE_OUTPUT_POWER_RECOVER    0xD010    		//�����Դ�ָ�


//��̬�ȼ�¼���¼������ȼ�7��
#define   INT_TYPE_REG_DEV_OFFLINE          	0xE001      	//ע���豸����
#define   INT_TYPE_NEW_DEV_ONLINE    			0xE002      	//�����豸���� !!!
#define   INT_TYPE_NEW_DEV_OFFLINE          	0xE003      	//�����豸����
#define   INT_TYPE_DEV_REPLACE          		0xE004     	 	//�豸�滻     !!!!
#define   INT_TYPE_REPEAT_ID_DEV    			0xE006      	//ID�ظ�
#define   INT_TYPE_REPEAT_UC_DEV    			0xE007      	//UC�ظ�
#define	  INT_TYPE_REFRESH_DELETE				0xE008			//ɾ���豸
#define   INT_TYPE_DEV_RECOVER       			0xE009      	//�豸�ָ���ֱ���̵����豸���½���
#define   INT_TYPE_DEV_TYPE_ERROR               0xE00A			//�豸���ʹ���
#define   INT_TYPE_DEV_NO_DEFINE                0xE00B			//�����豸δ����
#define   INT_TYPE_DEV_FAULT      			    0xE00F     		//�豸����

#define   INT_TYPE_GET_MAIN_TOKEN      			0xE100      	//��ȡ��վ����
#define   INT_TYPE_ONLINE_APPLIED      			0xE101      	//��������
#define   INT_TYPE_COMMUN_SUCC_RATE     		0xE102      	//�豸ͨ�ųɹ���

#define   INT_TYPE_UC_CHANGE            		0xE200      //UC�仯
#define   INT_TYPE_ID_CHANGE            		0xE201      //ID�仯
#define   INT_TYPE_CC_CHANGE            		0xE202      //CC�仯
#define   INT_TYPE_PARAMETER_CHANGE     		0xE203      //�����仯
#define   INT_TYPE_INF_CHANGE           		0xE204      //��Ϣ�任

#define   INT_TYPE_DEV_INFLOG_FINISH    		0xE300      //�豸��Ϣ��¼���
#define   INT_TYPE_LOG_DEV_INF                  0xE301      //��¼���豸��Ϣ
#define   INT_TYPE_LA_UNLAW_DEV_INF            0xE302      //LA�ظ����豸��Ϣ
#define   INT_TYPE_LOGIN_OPER                   0xE303      //ϵͳ����Ա��¼
#define   INT_TYPE_LOGIN_ADMIN                  0xE304      //ϵͳ����Ա��¼
#define   INT_TYPE_LOGIN_SUPER                  0xE305      //��������Ա��¼
#define   INT_TYPE_REG_RENEW                    0xE306      //�豸����ע��
#define   INT_TYPE_REG_REFRESH          	    0xE307		//�豸ˢ��ע��
#define   INT_TYPE_REG_AUTO                     0xE308	    //�豸�Զ�ע��
#define   INT_TYPE_REG_NETWORK                  0xE309	    //����ע��
#define   INT_TYPE_DEFINE_AUTO          	    0xE30A		//�豸�Զ�����
#define   INT_TYPE_DEFINE_ORDER                 0xE30B      //�豸�̳ж���
#define   INT_TYPE_DEFINE_SERIAL                0xE30C	    //�豸��������
#define   INT_TYPE_FEILD_DEV_DEFINE         	0xE30D     	//�ֳ��豸����
#define   INT_TYPE_BUS_PANEL_DEFINE         	0xE30E     	//�����̶���
#define   INT_TYPE_MULTI_PANEL_DEFINE           0xE30F      //�������̶���
#define   INT_TYPE_BROCAST_PANEL_DEFINE         0xE310      //�㲥�̶���
#define   INT_TYPE_CONTROLER_DEFINE             0xE311      //����������
#define   INT_TYPE_PHONEDISTRI_PANEL_DEFINE     0xE312      //�绰�����̶���
#define   INT_TYPE_PRE_ALARM_DEFINE             0xE313      //Ԥ������
#define   INT_TYPE_LA_CHANGE                    0xE400      //LA�޸�
#define   INT_TYPE_NODE_NORMAL                  0xE800      //�ڵ�����

#define   INT_TYPE_NULL						    0xFFFF		//��Ч	



#define   INT_TYPE_COMM_UNSUPPORT               INT_TYPE_NODECOMM_FAU
#define   INT_TYPE_LIMIT_PERMISSIONS            INT_TYPE_LIMIT_CONDITION_FAU

#endif /* BUS_DOWN_H_ */
