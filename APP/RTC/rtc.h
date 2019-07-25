#ifndef __RTC_H
#define __RTC_H	    

#include "global.h"

#define PPM_PER_STEP  	0.9536743 //10^6/2^20: У׼ֵΪ1,��Ӧ��PPM
#define PPM_PER_SEC   	0.3858025 //10^6/(30d*24h*3600s): ÿ30���һ���Ӧ��ppm���

#define RTC_INIT_FLAG	0x5050
//ʱ��ṹ��
//typedef struct 
//{
//	UINT8  sec;
//	UINT8  min;
//	UINT8  hour;
//	UINT8  week;			
//	UINT8  w_date;
//	UINT8  w_month;
//	UINT16 w_year;
// 
//}RTC_STRUCT;	
				
extern float temp_offset;
extern const UINT8 mon_table[12];//�·��������ݱ�
extern UINT8 		time_string[];	

//extern UINT8 calibr_mode ;
//extern UINT8 calibr_time;
void RTC_Config(void);
void RTC_User_Init(void);        	//��ʼ��RTC,����0,ʧ��;1,�ɹ�;
void RTC_Calibration(uint16 FastSecPer30days);
//UINT8 Is_Leap_Year(UINT16 year);//ƽ��,�����ж�
//void RTC_Get(void);         	//����ʱ��   
UINT8 RTC_Get_Week(UINT16 year,UINT8 month,UINT8 day);
UINT8 RTC_Set(UINT16 syear,UINT8 smon,UINT8 sday,UINT8 hour,UINT8 min,UINT8 sec);//����ʱ��

#ifdef INTERNAL_RTC

#define	GET_RTC_TIME()			Get_RTC_Time(time_string)
void Get_RTC_Time(UINT8 *rec);
void Set_RTC_Time(UINT8 *rec);
void RTC_Get_PowerOff_Time(UINT8 *time_buf);
void RTC_Save_PowerOff_Time(void);
//void RTC_SelfCheck(void);
#endif

#endif




























 
