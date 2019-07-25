
#ifndef __TIMER_H__
#define __TIMER_H__

#include "global.h"

//==================ϵͳʱ�䶨��========================//
typedef struct 											
{	
	UINT32 Tick;							
	UINT8 Flag1Ms;	
	UINT8 Count1Ms;
	UINT8 Count8Ms;
	UINT8 Count1S;
	UINT8 Sec;										
	UINT8 Min;
	UINT8 Hour;										
	UINT8 Month;										
	UINT8 Data;										
	UINT8 Year;	 
}SYS_TIMER;	//����ϵͳ�ڶ�ʱ
extern SYS_TIMER  SysTimer;

/*==================RT1�ö�ʱʱ�䶨��========================*/

#define		C_TIME_1S              		999 			//ϵͳʱ��1mS�жϲ���
#define		C_TIME_1MIN             	59				//ϵͳʱ��1Min��1S����
#define		C_TIME_1HOUR              59 				//ϵͳʱ��1Hour��1Min����
#define		C_TIME_1DATA              23 				//ϵͳʱ��1DATA��1Hour����
#define		C_TIME_1MONTH             30				//ϵͳʱ��1MONTH��1DATA����
#define		C_TIME_1YEAR              11 				//ϵͳʱ��1YEAR ��1MONTH����

void Timer14_Init(UINT16 arr,UINT16 psc);

UINT32  get_systemtick(void);
void Monitor_Task(void);

#endif
