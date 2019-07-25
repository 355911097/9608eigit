/*
 * spi_flash.h
 *
 *  Created on: 2014-11-15
 *      Author: Administrator
 */

#ifndef SPI_FLASH_H_
#define SPI_FLASH_H_


//------------------------------------- include -------------------------------------
#include "global.h"
//------------------------------------- define --------------------------------------

#define		Flash_CS()					GPIOB->BRR = GPIO_Pin_1
#define		Flash_UnCS()				GPIOB->BSRR = GPIO_Pin_1
#define		Flash_Lock()				GPIOB->BRR = GPIO_Pin_0
#define		Flash_UnLock()				GPIOB->BSRR = GPIO_Pin_0


//=======================MX25L4006�Ĵ�����ַ�궨��=========================================
#define   READ        					0x03
#define   FAST_READ   					0x0b
#define   WRITE       					0x02  
#define   WREN        					0x06
#define   WRDI        					0x04
#define   RDSR        					0x05
#define   WRSR        					0x01 
#define   PE          					0x42 
#define   SE          					0x20	//0xD8 
#define   BE          					0xD8 
#define   CE          					0xC7 
#define   RDID        					0x9f 
#define   DPD         					0xB9
//Mx25L12855 ID����
#define   MANU_ID						0xc2
#define   DEV_ID						0x20    //0x26
#define   DENSITY_ID					0x18

//--------------------------------------------------------------------------------------
#define FLASH_STA_VALID      			0xAA 
#define FLASH_STA_BLANK      			0xFF
#define FLASH_STA_UNVALID      			0x00 

#define FLASH_DATA_UNVALID      		0xFF

#define FLASH_DATA_WRITTEN_FORBID       0
#define FLASH_DATA_WRITTEN_ALLOW        1   

#define FIRST_CHIP_FLASH    0
#define SECOND_CHIP_FLASH   1

#define DATA_SIZE                       64

#define FLASH_CHIP_ERR_MASK             0X03  
#define FLASH_CHIP0_ERR_MASK            0X01   
#define FLASH_CHIP1_ERR_MASK            0X02  

//--------------------------------------------------------------------------------------
// FLASH �洢�궨��
#define	SIZE_FLASH_SECTOR				0x01000		//4096
#define	MAX_SECTOR_COUNTER				0x01000		//4096
#define SIZE_FLASH_STA_VALID                1
// �������ļ�--������ַ���������ַ����
#define	LEN_ASCII_LIBRARY      	  0x00001000	// 4K  				

#define	LEN_HZ_LIBRARY       	  0x0003D000    // 244K  

#define ADDR_UNICODE_START        0x00040000    //UNICODE-GBK,GBK-UNICODE
#define	LEN_UNICODE_TABLE             0x00015484   //0x00015490 // 87184
#define ADDR_GBK2UNICODE_START    0x00055490 



#define  ADDR_VIOCE_ADDR     	 0x000DC800    //��С20kΪ����
#define  ADDR_VIOCE_START        (ADDR_VIOCE_ADDR+0x5000)//��������ʼ��ַ
//#define  ADDR_VIOCE_ALARM_START			(0x004CB000 + ADDR_VIOCE_ADDR)

#define	LEN_VIOCE_STORE_SPACE     0x004CB000    //�������ܳ�_ADDR+����(0x5000+4c6000)

#define	ADDR_VIOCE_ALARM_START	  (ADDR_VIOCE_ADDR+LEN_VIOCE_STORE_SPACE)
#define	ADDR_VIOCE_ALARM		  ADDR_VIOCE_ALARM_START
#define	LEN_VIOCE_ALARM		      0x00010000    //64k 

#define	ADDR_VIOCE_SKYALARM		  (ADDR_VIOCE_ALARM_START+LEN_VIOCE_ALARM)	
#define	LEN_VIOCE_SKYALARM		  0x00008000	// 32K  

#define	ADDR_VIOCE_HELP			  (ADDR_VIOCE_SKYALARM+LEN_VIOCE_SKYALARM)
#define	LEN_VIOCE_HELP			  0x0000C800    // 50K  

#define	ADDR_VIOCE_GUN			  (ADDR_VIOCE_HELP+LEN_VIOCE_HELP)
#define	LEN_VIOCE_GUN			  0x00002000    // 8K  

#define	ADDR_VIOCE_DIDI			  (ADDR_VIOCE_GUN+LEN_VIOCE_GUN)
#define	LEN_VIOCE_DIDI			  0x00000800    // 2K  

#define	ADDR_VIOCE_DUDU 		  (ADDR_VIOCE_DIDI+LEN_VIOCE_DIDI)
#define	LEN_VIOCE_DUDU 		      0x00001400    // 5K  

#define	ADDR_VIOCE_KEY 			  (ADDR_VIOCE_DUDU+LEN_VIOCE_DUDU)
#define	LEN_VIOCE_KEY 			  0x00001400    // 5K  


// �ֿ��ļ�--ASC��ͺ�����ʼ��ַ���� 
#define     ADDR_ASC_START      0x005D1000
#define     ADDR_HZ_START       0x005D3000

//�ֿ�+������+ͼ��

#define FONT_FLASH_PROGRAM              0X7FF000

//--------------------------------------------------------------------------------------

#define	COPY_SIZE_FLASH					0x200000    //2M

//	ϵͳ����4k	
#define	SYSCONFIG						0
#define	ADDR_FLASH_SYSCONFIG			0x800000
#define	SLEN_FLASH_SYSCONFIG			sizeof(CONFIG)//140
#define	ALEN_FLASH_SYSCONFIG			512
#define	MAXN_FLASH_SYSCONFIG			1	
#define TIMES_FLASH_SYSCONFIG			(4096/512)       //ÿ����Ϣ���д����

//	���м�¼2032kbyte	
#define	RECORD							(SYSCONFIG + 1)
#define	ADDR_FLASH_RECORD				(ADDR_FLASH_SYSCONFIG+4096*2)//0x802000
#define	SLEN_FLASH_RECORD				sizeof(RECORD_STRUCT)//126//���ݽṹ��RECORD_STRUCT����
#define	ALEN_FLASH_RECORD				128
#define	MAXN_FLASH_RECORD				16256//5120
#define TIMES_FLASH_RECORD			    1

//sector=4k��д32����¼
#define COUNT_RECORD_PER_SECTOR			(SIZE_FLASH_SECTOR / ALEN_FLASH_RECORD)			//ÿ������¼����
//ռ��2032k/4=508sector
#define MAX_RECORD_SECTOR				(MAXN_FLASH_RECORD / COUNT_RECORD_PER_SECTOR)	//�洢��¼����������

//	Flash��ȡ��¼������ַ
#define	CHECK							(RECORD+1)
#define	ADDR_FLASH_CHECK				(ADDR_FLASH_SYSCONFIG+0x1000)//4K

//#define	CHECK							(RECORD+1)
//#define	ADDR_FLASH_CHECK				(ADDR_FLASH_RECORD+0x1FC000)//0x1FC000=16256*128


//�������
#define PROGRAM							(CHECK+1)
#define	ADDR_FLASH_PROGRAM				0xF00000
#define	SLEN_FLASH_PROGRAM				(1024*1024)
#define	ALEN_FLASH_PROGRAM				(1024*1024) //1024K
#define	MAXN_FLASH_PROGRAM				2	
#define TIMES_FLASH_PROGRAM				1


//===========�ⲿFLASH���ݴ洢����ʱ������=================
#define SIZE_SECTOR                   0x1000

#define	ADDR_BOOTLOADER_START			 0xF00000//0xF80000		//�����β0x1000000����1Mbytes  //����������

//����Ӧ�ó��� ʱʹ��
//VALID_FLAG��LEN0��LEN1��LEN2��LEN3��CRC0��CRC1��HARD0��HARD1��HARD2��SOFT0��SOTF1��SOTF2
#define	ADDR_BOOTLOADER_LEN                 (0x1000000-SIZE_SECTOR)
#define	ADDR_BOOTLOADER_CRC				    (ADDR_BOOTLOADER_LEN+4)				//����������CRC
#define	ADDR_BOOTLOADER_FLAG                (ADDR_BOOTLOADER_CRC+2)             //��ַ�����ذ�Ӧ�ó���������־

#define	ADDR_BOOTLOADER_HARD			    (ADDR_BOOTLOADER_FLAG+4)			    //��������Ӳ���汾	
#define	ADDR_BOOTLOADER_SOFT			    (ADDR_BOOTLOADER_HARD+3)			    //��������Ӳ���汾	
#define	ADDR_BOOTLOADER_UC                  (ADDR_BOOTLOADER_SOFT+3)

//������Դ�����ʱʹ��		    //��������Ӳ���汾								//���ذ�Ӧ�ó���������־
#define POW_PROGROM_VALID_FLAG			0x55										//��ԴӦ�ó���������־
#define ADDR_POW_BOOT_FLAG            (ADDR_BOOTLOADER_FLAG)
#define POWER_LA                       1
//�����Ǳ������ļ�ʱʹ��		    //
#define ADDR_UPDATA_FILE_NAME_LEN             (ADDR_BOOTLOADER_SOFT+3)
#define ADDR_UPDATA_FILE_NAME                 (ADDR_UPDATA_FILE_NAME_LEN+1)

//====================================================================================== end
typedef struct
{
    UINT8 Cs ;                                                    //FLASH Ƭѡ(0:��FLASH 1:��FLASH) 
    UINT8 Nums;                                                   //��ЧFLASH оƬ����
    UINT8 Err;
}FLASH_STA;

extern FLASH_STA Flash;

extern UINT8 	buffer[SIZE_SECTOR];


typedef enum    
{
	ICO_TYPE_SYS_QUERY  = 0,  //ϵͳ��ѯ
	ICO_TYPE_SYS_SET,	      //ϵͳ����
	ICO_TYPE_SYS_DEBUG,	      //ϵͳ����
	ICO_TYPE_USER_SET,	      //�û���¼
	
	ICO_TYPE_UNLOCK,	      //����
	ICO_TYPE_LOCK,		      //����
	ICO_TYPE_GPRS_UNCONNECT,  //GPRSδ����
	ICO_TYPE_GPRS_CONNECT1,
	ICO_TYPE_GPRS_CONNECT2,
	ICO_TYPE_GPRS_CONNECT3,
	ICO_TYPE_GPRS_CONNECT4,	  //GPRS����
    ICO_TYPE_GPRS_MESSAGE,     //GPRS����
	ICO_TYPE_TCP_UNCONNECT,	  //TCPδ����
	ICO_TYPE_TCP_CONNECT,     //TCP����
	ICO_TYPE_LOGO,	          //��˾logo
	ICO_TYPE_TCP_gongzuozhengchang,	  //ϵͳ��������

	ICO_TYPE_MAX

}E_ICO_TYPE;

//------------------------------------- function ------------------------------------
void Flash_Init(void);
void Flash_Sector_Erase(UINT32 addr);         //Erase a sector (4K byte)
void Flash_Save_Info(UINT8 type,UINT16 offset,UINT8 *p);
UINT8 Flash_Load_Info(UINT8 type,UINT16 offset,UINT8 *p);
UINT8 Flash_SelfCheck(void);
void Flash_Read_Id(UINT8 *id);
void Flash_Erase_3Addr(UINT32 data_address);
void Flash_Read_3String(UINT32 addr, UINT8 * rd_buf, UINT16 len);
UINT8 Flash_Blank_Check(UINT32 addr,UINT16 len);
void Flash_Read_String(UINT32 data_address,UINT8 *data,UINT16 data_length);
void Flash_Write_String(UINT32 data_address,UINT8 *data,UINT16 data_length);
#endif /* SPI_FLASH_H_ */


