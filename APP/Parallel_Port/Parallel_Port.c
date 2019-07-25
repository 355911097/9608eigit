#include "Parallel_Port.h"
#include "NT_FT8003_PRT.h"
#include "Led.h"
#include "EI_Print_COMM.h"




CONTR Parallel;

void Parallel_Port_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	//�������ݽ���IO�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;//PA15Ϊbusy�ţ���Ҫ��ʱ������Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	//�������ݽ���IO�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
		//�������ݽ���IO�ڳ�ʼ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_Init(GPIOC, &GPIO_InitStructure);


}

/*=====================================================*/
//��������:void EXTI15_Init(void)
//��������:��ʼ���ⲿ�ж�
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:2018��1��31��л�
/*=====================================================*/
void Parallel_Port_EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;//pc15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource15);//�ж�������PC15
	
	//�����ⲿ�ж���
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش�ӡ���ɼ���Ч����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//�����ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



void Parallel_Port_Init(void)
{
	Parallel_Port_IO_Init();
	Parallel_Port_EXTI_Init();
}

/*=====================================================*/
//��������:UINT8 Read_IO_Voltage (void)
//��������:��ȡ���нӿڵ�ƽ
//��		��:void
//��	��	 ֵ:data
//���ļ�¼:
/*=====================================================*/
UINT8 Read_IO_Voltage (void)
{
	BIT_CHAR data;
	
	//��ȡIO�ڵ�ƽ
	data.b.b7 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	data.b.b6 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	data.b.b5 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	data.b.b4 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6);
	data.b.b3 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
	data.b.b2 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
	data.b.b1 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
	data.b.b0 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	return data.byte;
}

/*=====================================================*/
//��������:UINT8 Get_Parallel_Data (void)
//��������:ȡ�ò��нӿ�����
//��		��:void
//��	��	 ֵ:data
//���ļ�¼:
/*=====================================================*/
UINT8 Get_Parallel_Data (void)
{
	UINT8 data = 0,data1,data2,data3;
		
	data1 = Read_IO_Voltage();
	data2 = Read_IO_Voltage();
	data3 = Read_IO_Voltage();
	
	if((data1 == data2) || (data1 == data3))
	{
		data = data1;
	}
	else if(data2 == data3)
	{
		data = data2;
	}
	
	return data;
}

/*=====================================================*/
//��������:void EXTI4_15_IRQHandler(void)
//��������:�ⲿ�ж��¼�����
//��		��:void
//��	��	 ֵ:void
//���ļ�¼:
/*=====================================================*/

//��ԼRAM����232���ýṹ��
void EXTI4_15_IRQHandler(void)
{
	UINT8  para_daraRec;

	para_daraRec=Get_Parallel_Data();
	Parall_Uart_Rec_Data(para_daraRec);
	On_Led_REC();
	/*RS232.R.Buf[RS232.R.Head] = Get_Parallel_Data();
	//
	RS485.T.Buf[RS485.T.Tail] = RS232.R.Buf[RS232.R.Head];
	RS485.T.Tail ++;
	if(RS485.T.Tail >= CONTR_BUF_LEN)
		RS485.T.Tail = 0;
	RS232.T.Buf[RS232.T.Tail] = RS232.R.Buf[RS232.R.Head];
	RS232.T.Tail ++;
	if(RS232.T.Tail >= CONTR_BUF_LEN)
		RS232.T.Tail = 0;
	
	On_Led_REC();
	//
	RS232.R.Head++;
	if(RS232.R.Head >= CONTR_BUF_LEN)
	{
			RS232.R.Head = 0;
	}*/
	EXTI_ClearITPendingBit(EXTI_Line15);//����жϱ�־λ����ֹ���������ж�
}
void Parallel_Data_Init(void)
{
	Parallel.Type = System.parallel_type;
}
void Parallel_Task(void)
{
//	switch(Parallel.Type)
//	{
//		case FT8003:
//			Com_Task_FT8003_PRT(&RS232);
//		break;
//		default:
//			
//		break;
//	}
}



