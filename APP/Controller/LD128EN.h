#ifndef __LD128EN_CRT_ZJ_H__
#define __LD128EN_CRT_ZJ_H__


#include "global.h"
#include "controller.h"

#define LD128EN_CRT_ZJ_COMMAND_TYPE_ALARM_EV				0x01		//火警
#define LD128EN_CRT_ZJ_COMMAND_TYPE_MAIN_POWER				0x12		//主电事件
#define LD128EN_CRT_ZJ_COMMAND_TYPE_BACKUP_POWER			0x13		//备电事件
#define LD128EN_CRT_ZJ_COMMAND_TYPE_REG_DEV_REQUEST		0x20		//节点动作请求
#define LD128EN_CRT_ZJ_COMMAND_TYPE_RESET					0x50		//控制器复位
#define LD128EN_CRT_ZJ_COMMAND_TYPE_RESET_LINK				0x51		//联动复位



#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_FAULT				0x02		//联动模块故障
#define LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_FAULT				0x03		//探测器故障
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_LINK_FAULT			0x04		//联动执行故障
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_RECOVER				0x05		//联动故障恢复
#define LD128EN_CRT_ZJ_EV_TYPE_DETECTOR_RECOVER			0x06		//探测器故障恢复
#define LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_FAULT			0x07		//区显故障
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV0_ANSWER			0x09		//动作0回答
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV1_ANSWER			0x0A		//动作1回答
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV0_REMOVE			0x0B		//动作0消除
#define LD128EN_CRT_ZJ_EV_TYPE_LINK_DEV1_REMOVE			0x0C		//动作1消除
#define LD128EN_CRT_ZJ_EV_TYPE_AREA_MONITOR_RECOVER		0x0D		//区显恢复
#define LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_FAULT			0x14		//主备电故障及恢复的值为自编
#define LD128EN_CRT_ZJ_EV_TYPE_MAIN_POWER_RECOVER			0x15		//若冲突，则需改
#define LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_FAULT			0x16
#define LD128EN_CRT_ZJ_EV_TYPE_BACKUP_POWER_RECOVER		0x17
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_START		0x18		//节点动作请求闭合(节点动作请求为自编)
#define LD128EN_CRT_ZJ_EV_TYPE_REG_DEV_REQUEST_STOP		0x19		//节点动作请求断开
#define LD128EN_CRT_ZJ_EV_TYPE_SILENCE						0x30		//控制器消音
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_REQUEST				0x40		//联动0请求
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_REQUEST				0x41		//联动1请求
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_STOP					0x42		//联动0停止
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_STOP					0x43		//联动1停止
#define LD128EN_CRT_ZJ_EV_TYPE_LINK0_START					0x44		//联动0启动
#define LD128EN_CRT_ZJ_EV_TYPE_LINK1_START					0x45		//联动1启动
#define LD128EN_CRT_ZJ_EV_TYPE_POLL_RETURN					0x7F

#define LD128EN_CRT_ZJ_POLL_PERIOD1S						125// 1s==125*8



void Save_Component_Info_LD128EN(UINT8 *buf);
void Save_Other_Info_LD128EN(UINT8 *buf);
UINT16 Change_Event_Type_LD128EN(UINT8 src_event,UINT8 *record_type);

void Send_Poll_Contr_LD128EN(CONTR_IF *buf);
UINT8 Analyse_LD128EN(CONTR_IF *buf);
void Handle_LD128EN_Zj(CONTR_IF *buf);
void Com_Task_LD128EN_Zj(CONTR_IF *buf);
void Com_Task_LD128EN_Jt(CONTR_IF *buf);

#endif
