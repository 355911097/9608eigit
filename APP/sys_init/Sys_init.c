
#include "sys_init.h" 
#include "timer.h" 
#include "main.h" 
#include "Parallel_Port.h"
#include "ex_flash.h"
#include "led.h"
#include "record_manage.h"
#include "controller.h"
#include "core_cm0.h"
#include "core_cmfunc.h"


CONFIG System;//ϵͳ���ã����ױ�
RUNSTA RunSta;


const UINT8 SOFTWARE_VERSION[3] = {SOFT_V_BYTE0,SOFT_V_BYTE1,SOFT_V_BYTE2};
const UINT8 HARDWARE_VERSION[3] = {HARD_V_BYTE0,HARD_V_BYTE1,HARD_V_BYTE2};

/*=====================================================*/
//��������:void Init_WATCHDOG(void)
//��������:��ʼ�����Ź�
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:
/*=====================================================*/
void Init_WATCHDOG(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(0x0FFF);
	IWDG_ReloadCounter();
	IWDG_Enable();
}
/*=====================================================*/
//��������:void DOG(void)
//��������:�忴�Ź�
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2017��2��21����ΰ��
/*=====================================================*/
void Watch_Dog(void)
{
#ifdef WATCH_DOG_ENABLE
	IWDG_ReloadCounter();
#endif
}

/*********************************************************************************
* �������� : str_get_len
* �������� : �����λ:��SYSRESETREQ����Ϊ��Ч������λ������ִ�и�λ������������һ����ʱ��
			�ڴ���ʱ�ڼ䣬��������Ȼ������Ӧ�ж����󡣵����ǵı���������Ҫ�ô˴�ִ�е���Ϊֹ��
			��Ҫ�����κ����������ˡ����ԣ�����ڷ�����λ����ǰ���Ȱ�FAULTMASK��λ��
* ������� : None��
* ������� : None
* �� �� ֵ : None
* �޸����� ��2014-06
*********************************************************************************/
void Soft_Reset(void)
{
   // Delay_ms(40);
	//__set_FAULTMASK(1);  	//�ر������ж�
	NVIC_SystemReset();		//��λ
}


/*=====================================================*/
//��������:void Ppwer_485_Init(void)
//��������:��ʼ��PWM
//ռ�ձ�50%��������ʱ��10%      ��ռ�ձ�4:6����PWM����
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��1��31��л�
/*=====================================================*/
void Power_485_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /*GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* TIM15 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_1);								//PB14����ΪTIM15_CH1
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_3);								//PB15����ΪTIM15_CH1N
	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;									//Ԥ��Ƶ��ʵ�ʷ�Ƶϵ��Ϊ�����ֵ+1���˴�����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;					//TIM���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 100000) - 1;			//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,100k
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;									//����ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;								//�������ڼ���ֵ,�����Զ�����ռ�ձ�
	TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);
	
	/* Channel 1, 2 and 3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;								//ѡ��ʱ�����ģʽΪPWMģʽ2�������ϼ���ʱ����TIM15_CNT<TIM15_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;					//�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;				//��������Ƚ�״̬ʹ��
  //TIM_OCInitStructure.TIM_Pulse = (uint16_t) ((uint32_t) 45 * (TIM_TimeBaseStructure.TIM_Period - 1)/ 100);//ռ�ձ�����
  TIM_OCInitStructure.TIM_Pulse = (uint16_t) ((uint32_t) 5 * (TIM_TimeBaseStructure.TIM_Period - 1)/ 10);//ռ�ձ�����

  //TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;					//������Ժͻ������Ե���Ч��ƽΪ��
  //TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM15, &TIM_OCInitStructure);
  //TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM15, &TIM_OCInitStructure);
  //TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM15, &TIM_OCInitStructure);

  /* Automatic Output enable, Break, dead time and lock configuration*/
	//��������
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 48;															//����������С0-ff
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM15, &TIM_BDTRInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM15, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM15, ENABLE);//TIM15_OCͨ�����PWM
}

//==================================================================================
//��	����void McuCoreConfig(void)
//��	�ܣ�MUC �ں�����
//��	������
//��    ��:   ��
//�������ڣ�  2014.5
//==================================================================================
void McuCoreConfig(void)
{
	//SystemInit();//ʱ��48M  AHB:48M APB:48M
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource13, GPIO_AF_0);//PA13����ΪSWJIO
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource14, GPIO_AF_0);//PA14����ΪSWJCLK


#ifdef ADD_BOOT
/*
�ж����������ӳ��:48���ж�����
�ο�: http://www.51hei.com/bbs/dpj-40235-1.html
*/
	memcpy((void*)0x20000000, (void*)ADDR_MCU_PROGROM_START, 48*4);
	SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);

#endif	


}

/********************************************************************************
* Function Name: void Init_Config(UINT8 type)
* Description  : System data is initialized.
* Arguments    : type-0:initializ,Otherwise return.
* Return Value : None
* Call Relation: External
* Change Time  : 2015-5
*********************************************************************************/
void Init_Config(void)
{
    UINT8 i;

    if(!Flash_Load_Info(SYSCONFIG,0,(UINT8*)(&System)))
			
    {
        memset((UINT8*)&System,0xff,sizeof(System));	
        memset(System.id,0,sizeof(System.id));     
    }

	if((memcmp(System.software_ver,SOFTWARE_VERSION,3)) 			//???????
		|| (memcmp(System.hardware_ver,HARDWARE_VERSION,3)))
	{														
		memcpy(System.software_ver,SOFTWARE_VERSION,3);
		memcpy(System.hardware_ver,HARDWARE_VERSION,3);
	}

	
	if((System.la == 0x00) || (System.la > 0xFC))
	{
		System.la = 0x01;
	}
	System.uc[4] = DEVICE_TYPE_OF_UC_CODE;

	for(i=0;i<LEN_REG_ID;i++)
	{
	  if(System.id[i] == 0xFF)
	  {
		  memset(System.id,0,LEN_REG_ID);
		  break;
	  }
	}


	if(System.ctr_type == 0xff)
	{
	  System.ctr_type = 0;
	}
	if(System.trans_equip_connect > 0x01)//��Ӵ����豸��־
	{
	  System.trans_equip_connect = 0;
	}
	System.ctr_addr[4] = DEV_TYPE_CONTROL_UC;
	if(System.ctr_type)
	{
	  for(i=0;i<4;i++)
	  {
		  if(((0xF0&System.ctr_addr[i]) > 0x90)
			  || ((0x0F&System.ctr_addr[i]) > 0x09))
		  {
			  System.ctr_addr[i] = 0;
		  }
	  }
	}
	System.ctr_type = Parallel_Debug;
    Flash_Save_Info(SYSCONFIG,0,(UINT8*)(&System));//�������Ƿ���ͬ�жϣ���������£������ظ���дflash
}


/*=====================================================*/
//��������:void Mcu_Hard_Init(void)
//��������:�豸Ӳ����ʼ��
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��2��5��л�
/*=====================================================*/
void Mcu_Hard_Init(void)
{

  Timer14_Init(99,479); //����ʱ��,1ms*100=48MHz/(479+1)/1000
	Led_Init();
	Flash_Init();
	Power_485_Init();//100k,60%ռ�ձ�232/485�����Դ����
	Parallel_Port_Init();
	
	#ifdef WATCH_DOG_ENABLE
	Init_WATCHDOG();
	#endif
}
/*=====================================================*/
//��������:void Mcu_Hard_Init(void)
//��������:�豸Ӳ����ʼ��
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��2��5��л�
/*=====================================================*/
void Mcu_Data_Init(void)
{
  	Init_Config();
	Controller_Data_Init();//�ȶ�ȡ���������ͣ��������ͶԴ��ڳ�ʼ��
	Controller_Uart_Init();	
	
}

void Recover_Factory_Set(void)
{    	
    memset(&System.project_name,0xFF,32);
    memset(&System.project_address,0xFF,32);
    memset(&System.project_linkman,0xFF,16);
    memset(&System.project_phone,0xFF,16); 
    memset(&System.project_email,0xFF,32); 
    System.la=0x01;
	memset(&System.uc,0x00,3); 
	System.uc[3] = 0x01;
	System.uc[4] = 0x82;//����ģ��
    memset(&System.cc,0xFF,32);



    Flash_Save_Info(SYSCONFIG,0,(UINT8*)(&System));

	//�����ⲿflash�ļ�¼�洢����	
	Delete_All_Record();
}

/*=====================================================*/
//��������:void System_Initialize(void)
//��������:�豸�ϵ��ʼ��
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��2��5��л�
/*=====================================================*/
void System_Initialize(void)
{
	McuCoreConfig();
	Mcu_Hard_Init();
	Mcu_Data_Init();
}
