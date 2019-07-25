#include  <string.h>

//#include "config.h"
//#include "system.h" 
//#include "delay.h"
#include "basic.h"
#include "record_manage.h"
#include "rtc.h" 

#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */

float temp_offset = 0;
//RTC_STRUCT	RTC_timer;			//ʱ�ӽṹ�� 	
UINT8 time_string[7];		//���ս����޸�Ϊ16λ�ģ��������RTC_timer�ϲ�
const UINT8 mon_table[12] ={31,28,31,30,31,30,31,31,30,31,30,31};//ƽ����·����ڱ�
//UINT8 calibr_mode = TRUE;
//UINT8 calibr_time	= 0;
extern UINT8 soft_reset_flag;
RTC_InitTypeDef  RTC_InitStructure;
RTC_TimeTypeDef  RTC_TimeStructure;
RTC_DateTypeDef  RTC_DateStructure;
//RTC_TimeTypeDef  RTC_TimeStampStructure;
//RTC_DateTypeDef  RTC_TimeStampDateStructure;
__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;

/******************************************************************
* Function Name: RTC_NVIC_Config()
* Description  : RTC�ж�����.
* Arguments    : None
* Return Value : None
********************************************************************/
//void RTC_NVIC_Config(void)
//{	
//    NVIC_InitTypeDef NVIC_InitStructure;
//	
//	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;				//RTCȫ���ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1λ,�����ȼ�3λ
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//��ռ���ȼ�0λ,�����ȼ�4λ
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ�ܸ�ͨ���ж�
//	NVIC_Init(&NVIC_InitStructure);								//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
//}

/******************************************************************
* Function Name: void RTC_Configuration(void)
* Description  : ����RTC�����þ���ʱ��Դ.ͬʱ���ʱ��
				 �Ƿ�������BKP->DR1���ڱ����Ƿ��һ�����õ�����
* Arguments    : None
* Return Value : None
********************************************************************/

void RTC_TimeRegulate(UINT8 year,UINT8 month,UINT8 day,UINT8 week,UINT8 hour,UINT8 minute,UINT8 second)
{
	RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
	RTC_TimeStructure.RTC_Hours = hour;
    RTC_TimeStructure.RTC_Minutes = minute;
    RTC_TimeStructure.RTC_Seconds = second;
	if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ERROR)
	{
		//Show_String(3,72,"ϵͳ��ʼ���У����Ժ�...");
	} 
	else
	{
		PWR_BackupAccessCmd(ENABLE);
		RTC_WriteBackupRegister(RTC_BKP_DR0,RTC_INIT_FLAG);
	}

	  RTC_DateStructure.RTC_WeekDay = week;
    RTC_DateStructure.RTC_Date = day;
    RTC_DateStructure.RTC_Month = month;

    RTC_DateStructure.RTC_Year = year;
	/* Configure the RTC date register */
	if(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) == ERROR)
	{
		;
	} 
	else
	{
		/* Indicator for the RTC configuration */
		PWR_BackupAccessCmd(ENABLE);
		RTC_WriteBackupRegister(RTC_BKP_DR0, RTC_INIT_FLAG);
	}

}
/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
void RTC_Config(void)
{
	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);

	/* Enable the LSE OSC */
	RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}

	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	SynchPrediv = 0xFF;
	AsynchPrediv = 0x7F;

	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();

	/* Enable The TimeStamp */
	RTC_TimeStampCmd(RTC_TimeStampEdge_Falling, ENABLE);   
	RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
	RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
   
	/* Check on RTC init */
	if (RTC_Init(&RTC_InitStructure) == ERROR)
	{
//207		Record_Save_Local(RECORD_FAULT);
	}
	/* Configure the time register */
	//RTC_TimeRegulate(14,10,10,5,8,8,8);   
}

/*********************************************************************************
* �������� : RTC_Init
* �������� : �ϵ��ʼ��RTC�������������������ǰд���RTC_INIT_FLAG��
			 ����������RTC����֮��������RTC.
* ������� : None
* ������� : None
* �� �� ֵ : None
* �޸����� ��2013-5
*********************************************************************************/
void RTC_User_Init(void)
{
//	RTC_NVIC_Config();
	
	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != RTC_INIT_FLAG)	//�Ӻ󱸼Ĵ����ж�������:�ж��Ƿ��һ��д����ʱ��
	{	 			
		RTC_Config();
	}
	else
	{
		/* Check if the Power On Reset flag is set */
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
			RCC_ClearFlag();
		}
		else if (RCC_GetFlagStatus(RCC_FLAG_SFTRST) != RESET)
		{
			RCC_ClearFlag();
		}
		/* Check if the Pin Reset flag is set */
		/*else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
		    //i = 2;
			RCC_ClearFlag();
		}*/
		/* Enable the PWR clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
		/* Allow access to RTC */
		PWR_BackupAccessCmd(ENABLE);

		/* Wait for RTC APB registers synchronisation */
		RTC_WaitForSynchro();

		/* Clear the RTC Alarm Flag */
		RTC_ClearFlag(RTC_FLAG_ALRAF);

		/* Clear the EXTI Line 17 Pending bit (Connected internally to RTC Alarm) */
		EXTI_ClearITPendingBit(EXTI_Line17);
	}
//	RTC_Calibration(100);					//RTCУ׼
}

/*********************************************************************************
* �������� : RTC_IRQHandler
* �������� : RTC�жϷ�����
* ������� : None
* ������� : None
* �� �� ֵ : None
* �޸����� ��2013-5
*********************************************************************************/
//void RTC_IRQHandler(void)
//{							    
//	if(RTC->CRL&0x0001)			//�����ж�
//	{							
//		RTC_Get();				//����ʱ�� 	 
//	}
//	if(RTC->CRL&0x0002)			//�����ж�
//	{
//		RTC->CRL&=~(0x0002);	//�������ж�
//	} 				  								 
//	RTC->CRL&=0X0FFA;         	//�������������жϱ�־
//	while(!(RTC->CRL&(1<<5)));	//�ȴ�RTC�Ĵ����������		   							 	   	 
//}

/*********************************************************************************
* �������� : Is_Leap_Year
* �������� : �ж��Ƿ������꺯������������ܱ�4���������ǲ��ܱ�400����
* ������� : year:���
* ������� : None
* �� �� ֵ : ������ǲ�������.1,��.0,����
* �޸����� ��2013-5
*********************************************************************************/
/*UINT8 Is_Leap_Year(UINT16 year)
{			  
	if(year%4 == 0) 			//�ܱ�4����
	{ 
		if(year%100 == 0) 
		{ 
			if(year%400 == 0)	//�����00��β,��Ҫ�ܱ�400���� 
				return 1;	   
			else
				return 0;   
		}
		else
			return 1;   
	}
	else
		return 0;	
}	*/


#ifdef INTERNAL_RTC
/*********************************************************************************
* �������� : Set_RTC_Time
* �������� : ʱ�����ã���ΪUINT8
* ������� : rec��������+����+ʱ����.
* ������� : None
* �� �� ֵ : None
* �޸����� ��2013-5
*********************************************************************************/
void Set_RTC_Time(UINT8 *rec)
{
	RTC_TimeRegulate(BCD2Hex(rec[6]),BCD2Hex(rec[5]),BCD2Hex(rec[4]),1,BCD2Hex(rec[2]),BCD2Hex(rec[1]),BCD2Hex(rec[0]));
}
/*********************************************************************************
* �������� : Get_RTC_Time
* �������� : ʱ�����ã���ΪUINT8
* ������� : rec��������+����+ʱ����.
* ������� : None
* �� �� ֵ : None
* �޸����� ��2013-5
*********************************************************************************/
void Get_RTC_Time(UINT8 *rec)
{
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	rec[2] = Hex2BCD(RTC_TimeStructure.RTC_Hours);
	rec[1] = Hex2BCD(RTC_TimeStructure.RTC_Minutes);
	rec[0] = Hex2BCD(RTC_TimeStructure.RTC_Seconds);   
	
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	rec[6] = Hex2BCD(RTC_DateStructure.RTC_Year);
	rec[5] = Hex2BCD(RTC_DateStructure.RTC_Month);
	rec[4] = Hex2BCD(RTC_DateStructure.RTC_Date);
	rec[3] = Hex2BCD(RTC_DateStructure.RTC_WeekDay);
}      




/*********************************************************************************
* �������� : RTC_Calibration
* �������� : RTCʱ��У׼��
* ������� : FastSecPer30days��ÿ30��ʱ��ƫ�������;
* ������� : None;
* �� �� ֵ : None
* �޸����� ��2013-12
*********************************************************************************/
void RTC_Calibration(uint16 FastSecPer30days)
{
//	float Deviation = 0.0;
//	UINT8 CalibStep = 0;
//	
//    Deviation = FastSecPer30days * PPM_PER_SEC;//�õ�ppm���
//	Deviation /= PPM_PER_STEP; 					//�õ�У׼ֵ�ĸ�����
//	CalibStep = (UINT8)Deviation; 				// �õ�У׼ֵ��������
//	if(Deviation >= (CalibStep + 0.5))
//    CalibStep  +=  1; //��������
//	if(CalibStep > 127) 
//    CalibStep = 127; 							// У׼ֵӦ��0��127֮��
//    BKP_SetRTCCalibrationValue(CalibStep);  	//���ÿ⺯��
}

/*********************************************************************************
* �������� : RTC_Save_PowerOff_Time
* �������� : �洢�ػ�ʱ�䣬ÿ�����һ�Σ�������Per_Second_Event_Deal()��
* ������� : None;
* ������� : None;
* �� �� ֵ : None
* �޸����� ��2013-12
*********************************************************************************/
void RTC_Save_PowerOff_Time(void)
{
	UINT16 temp;
	

	PWR_BackupAccessCmd(ENABLE);						//ʹ��RTC�ͺ󱸼Ĵ������� 
	
	temp =  RTC_TimeStructure.RTC_Minutes << 8;
	temp += RTC_TimeStructure.RTC_Seconds;
	RTC_WriteBackupRegister(RTC_BKP_DR2,temp);
	temp =  RTC_DateStructure.RTC_Date << 8;
	temp += RTC_TimeStructure.RTC_Hours;
	RTC_WriteBackupRegister(RTC_BKP_DR3,temp);	
	temp =  RTC_DateStructure.RTC_Year << 8;
	temp += RTC_DateStructure.RTC_Month;
	RTC_WriteBackupRegister(RTC_BKP_DR4,temp);	
}
/*********************************************************************************
* �������� : RTC_Save_PowerOff_Time
* �������� : �洢�ػ�ʱ�䣬ÿ�����һ�Σ�
* ������� : None;
* ������� : None;
* �� �� ֵ : None
* �޸����� ��2013-12
*********************************************************************************/
void RTC_Get_PowerOff_Time(UINT8 *time_buf)
{
	UINT16 temp;
	
	PWR_BackupAccessCmd(ENABLE);						//ʹ��RTC�ͺ󱸼Ĵ������� 
	
	temp = RTC_ReadBackupRegister(RTC_BKP_DR2);
	time_buf[0] = Hex2BCD((UINT8)temp);
	time_buf[1] = Hex2BCD((UINT8)(temp >> 8));
	temp = RTC_ReadBackupRegister(RTC_BKP_DR3);
	time_buf[2] = Hex2BCD((UINT8)temp);
	time_buf[3] = Hex2BCD((UINT8)(temp >> 8));	
	temp = RTC_ReadBackupRegister(RTC_BKP_DR4);
	time_buf[4] = Hex2BCD((UINT8)temp);
	time_buf[5] = Hex2BCD((UINT8)(temp >> 8));	
}
#endif	//end of #ifdef INTERNAL_RTC

