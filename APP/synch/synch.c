#include <string.h>

#include "synch.h"
#include "sys_init.h"

#include "sys_init.h"
#include "xycnbus.H" 
#include "ex_flash.h"

#include "bus_basic_cmd.h"
#include "record_status.h"
#include "delay.h"




//===============================U�̵���/����===============================================

UINT8 Type_udisk     = 0xFF;


#define UDISK_EXPORT_START_Y		0
#define UDISK_EXPORT_DIST		    2
#define MAX_ITEM_UDISK_EXPORT		4


extern UINT8			USB_Enum_Done;
extern void (* this_func)(UINT8 key);



/*********************************************************************************
* �������� : Udisk_SetType
* �������� : ���ò������ͣ����ڸ�λ�������ͣ�
* ������� : �˵�������;
* ������� : None;
* �� �� ֵ : None;
* �޸����� ��2015-02
*********************************************************************************/
void Udisk_SetType(UINT8 type)
{
	Type_udisk = type;
}
/*********************************************************************************
* �������� : Udisk_Import_GetType
* �������� : ��ȡ��ǰ����������,����Ӧ�Ĳ˵�������ȡFlash.h�е����ͣ�
* ������� : None��
* ������� : None;
* �� �� ֵ : �˵�������
* �޸����� ��2015-02
*********************************************************************************/
UINT8 Udisk_Import_GetType(void)
{
	return Type_udisk;
}


void Usb_Keybord_Creat(void)
{
    /*UINT8 const * const udisk_cue[] = {"USB��������","Init UDisk,Please wait."};

	LCD_Show_String_Mediacy(48,udisk_cue[System.language]);
	Usb_Mode_Set(USB_KEYBOARD);
	Menu_NoKeep();
*/
}








