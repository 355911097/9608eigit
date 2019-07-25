

#include "timer.h"
#include "controller.h"
#include "rtc.h"
#include "led.h"


SYS_TIMER  SysTimer;
UINT16  Rt_1D0mS;	
extern LED Led;



/******************************************************************
* Function Name: Timer7_Init()
* Description  : ����ʱ������ʱ��7����ʼ�������ж�ʱ��Ϊ1ms.
* Arguments    : None
* Return Value : None
* Call Relation: Extern
* Change Time  : 2014-11
********************************************************************/
void Timer14_Init(UINT16 arr,UINT16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr; 					//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������100*600Ϊ1ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  100Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure); 			//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	/* TIM IT enable */
	TIM_ITConfig(  			//ʹ�ܻ���ʧ��ָ����TIM�ж�
	TIM14, 
	TIM_IT_Update,    	//TIM �ж�Դ
	ENABLE  			//ʹ��
	);
	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;  			//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;   //��ռ���ȼ�0��
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  		//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  							//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIMx����
						 
}

void TIM14_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM14, TIM_IT_Update);    //���TIMx���жϴ�����λ:TIM �ж�Դ 

		SysTimer.Flag1Ms = 1;
		SysTimer.Tick ++;

		SysTimer.Count1Ms++;	
		switch(SysTimer.Count1Ms & 0x07)
		{
			case 0:
				//Monitor_Gprs_Timer();

			break;

			case 1: 
				Monitor_Controller_Uart_Timer_Run(&RS232);
				Monitor_Controller_Uart_Timer_Run(&RS485);
			break;
			case 2:
				Monitor_Led();
			break;
			case 3: 
				
			break;
			case 4:
				SysTimer.Count1S++;
				if(SysTimer.Count1S > 124)	//1s
				{
					SysTimer.Count1S = 0;
					//Contr.ComFault.Count++; 				
				}				
			break;
			case 5:
				if(Contr.delay)
				{
					Contr.delay --;
				}

			break;
			case 6:

			break;
			case 7:
				//Monitor_GprsLink_Close();
			break;
			
			default:
			break;
		}		

	}
}


/*********************************************************************************
* Function Name  : void Per_Second_Event_Deal(void)
* Description    : Events that need to be processed per second.
* Arguments      : None
* Return         : None
* Call Relation  : Extern
* Change Time    : 2014-11
*********************************************************************************/
void Per_Second_Event_Deal(void)
{ 
	Rt_1D0mS++;
	
	if((Rt_1D0mS %99)!=0)
	{
		  return;
	} 
	//Per_100mS_Event_Deal();
	
	switch(Rt_1D0mS/99)              //1s
	{		
		case 1:            
			break;

		case 2:
			//Per_Minute_Event_Deal();
			break;

		case 3:				
//			Monitor_Controller_Offline();
//			Monitor_Trans_Equip_Offline();
			break;
			
		case 4:	

			break;

		case 5:	

		break;

		case 6:
		break;

		case 7:			
			Get_RTC_Time(time_string);	//��ȡʵʱʱ��ʱ��
			break;	

		case 8: 
			//Monitor_System_Run_Sta();
			//UINT16 temp_adc = 0;// volt_ref_adc = 0;
			//   
			//float Vsense = 0;
			//temp (��)= {(V25 - VSENSE) / Avg_Slope} + 25 
			//V25=VSENSE��25��ʱ����ֵ,min=1.32V,typ=1.41V,max=1.50V
			//Avg_Slope = �¶���VSENSE���ߵ�ƽ��б�ʣ���λΪmV/���uV/�棩,min=4.0,typ=4.3,max=4.6 mV/��
			
			//volt_ref_adc = T_Get_Volt();//�ڲ��ο���ѹ������min=1.16V,typ=1.2V,max=1.26V
			//temp_adc = T_Get_Temp();
			//Vsense = (float)temp_adc*1.2/volt_ref_adc;//((float)temp_adc*3.3/4096);
			//Vsense = (float)temp_adc*3.24/4096;

			//temp_offset = (1.41 - Vsense) / 0.0043;//ƫ��25���ֵ�������ʱ25us
			
			//temp_offset = (AD_TEMP_25-temp_adc)*3.24/(4096*0.0043);
			//temp_offset = (AD_TEMP_25-temp_adc)*0.184;
			//temp_offset = (AD_TEMP_25-temp_adc)*3.31/(4096*0.0043);
			//temp_offset = (AD_TEMP_25-temp_adc)*0.188;
			//temp_real = ((SINT16)temp_offset + 25);
		break;	

		case 9: 
			/*static UINT8 counter_20s = 0;
			counter_20s ++;
			if(counter_20s > 19)//20���²�һ��
			{
				 counter_20s = 0;
				 RTC_Calibra();
			}*/									
//			RTC_Save_PowerOff_Time();
		break;	

		case 10: 
					
		break;

		default:
			break;
	}
	if(Rt_1D0mS >  C_TIME_1S) 								//1S	
	{
		 Rt_1D0mS = 0;
	}
}

UINT32  get_systemtick(void)
{
    return SysTimer.Tick;//1ms
}

void Monitor_Task(void)
{ 
	if(SysTimer.Flag1Ms)
	{
        SysTimer.Flag1Ms = 0;

		switch(SysTimer.Count1Ms & 0x07)
		{
			case 1:
				Monitor_Controller_Uart(&RS232);
				Monitor_Controller_Slave_Uart(&RS232);
				break;
				
			case 2:
				//Monitor_Controller_Uart(&RS485);
				//Monitor_Controller_Slave_Uart(&RS485);
			break;
			case 3:
				if(Led.rec_light_time)
				{
					Led.rec_light_time--;
					LED_REC_ON();
				}
				else
					Off_Led_REC();
				if(Led.trs_light_time)
				{
					Led.trs_light_time--;
					LED_SEND_ON();
				}
				else
					Off_Led_SEND();
				break;
			default:
				break;
		}
   
        Per_Second_Event_Deal();
	}    
}




