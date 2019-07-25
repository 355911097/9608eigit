#ifndef	SYNCH_H
#define	SYNCH_H

#include "global.h"



#define		SYNCH_CUE_Y			60


#define UDISK_EXPORT_DATA		0x04    //����ϵͳ����
#define UDISK_IMPORT_MT			0x00    //�������ذ����
#define UDISK_IMPORT_PW			0x01    //�����Դ�����
#define UDISK_IMPORT_DATA		0x02    //����ϵͳ����
#define UDISK_IMPORT_FONTLAB    0x03    //�����ֿ��ļ�
#define	MAX_FILE_PERPAGE		3
#define	START_Y_FILE_BROWSE		0
#define	DIST_Y_FILE_BROWSE		2
#define BUFFER_WR_FLASH_SIZE        (512)//������2��n����




UINT8 Udisk_Import_GetType(void);
void Udisk_SetType(UINT8 type);
void Udisk_Import_Info_Cue(void);
void Udisk_Import_Info(UINT8 type);

void Udisk_Import_Info_This(UINT8 key);
void Udisk_Export_Info(UINT8 type);

void Udisk_Import_Info_This(UINT8 key);

void Udisk_Export(void);
void Udisk_Import_Info(UINT8 type);
void config_sync_this(UINT8 key);
void Config_Sync(UINT8 type);

#endif
