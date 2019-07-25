
#include "controller.h"
#include "led.h"


LED Led;


/*=====================================================*/
//��������:void Init_PORT(void)
//��������:��ʼ��IO��
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��1��30��л�
/*=====================================================*/
void  Led_Init(void)
{
	GPIO_InitTypeDef      GPIO_InitStructure;  	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	//��IO�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//��ǰ��1����������ϵ�ʱ����һ��
	GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}


void Monitor_Led(void)  //����ʱ���ʱ
{
//	if(Led.gprs_light_time>0)
//	{
//		Led.gprs_light_time--;
//		if(Led.gprs_light_time==0)
//		Off_Led_SEND();
//	}
//	if(Led.contor_light_time>0)
//	{
//		Led.contor_light_time--;
//		if(Led.contor_light_time==0)
//		Off_Led_Contor();
//	}
}




void Off_Led_Error(void)
{
	if(!Debug.Led)
	{
		if((!Contr.ComFault.Flag)&&(!Compete_Event.ComFault.Flag))

		{
			LED_ERROR_OFF();
		}
	}
}

void On_Led_Error(void)
{
	LED_ERROR_ON();
}

void Off_Led_SEND(void)
{
	LED_SEND_OFF();
}

void On_Led_SEND(void)
{
	Led.trs_light_time = 40;//LED_SEND_ON();
}
void Off_Led_REC(void)
{
	LED_REC_OFF();
}

void On_Led_REC(void)
{
	Led.rec_light_time = 40;//LED_REC_ON();
}
void Off_Led_Contor()
{}
void On_Led_Contor()
{}





