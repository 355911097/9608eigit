

//#pragma interrupt INTST2 r_uart2_interrupt_send
//#pragma interrupt INTSR2 r_uart2_interrupt_receive

#include "uart.h"
#include "xycnbus.h"
#include "bus_basic_cmd.h"
#include "ex_flash.h"
#include "controller.h"
#include "EI2000.h"
#include "gst200.h"
#include "qn5010.h"
#include "gst500.h"
#include "ts.h"
#include "ld128en.h"

#define 	RS485_RCV()			   GPIOB->BSRR = GPIO_Pin_2
#define 	RS485_SND()			   GPIOB->BRR = GPIO_Pin_2


UART_BUFFER Contr_Pro;



const UINT8 auchCRCHi[] = {  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40  
} ; 
const UINT8 auchCRCLo[] = {  
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,  
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,  
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,  
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,  
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,  
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,  
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,  
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,  
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,  
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,  
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,  
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,  
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,  
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,  
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,  
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,  
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,  
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,  
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,  
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,  
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,  
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,  
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,  
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,  
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,  
0x43, 0x83, 0x41, 0x81, 0x80, 0x40  
};


const uint32 BAND[] = {115200,57600,38400,19200,9600,4800,1200,600};



//===============================================================================
//��������: 485���ڵײ��ʼ��
//�������: ��
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================
void Contr_485Uart_Init(UINT8 BAND)
{
	UINT16 set_baud[5]={UART_BAUD_115200,UART_BAUD_57600,UART_BAUD_38400,UART_BAUD_19200,UART_BAUD_9600};
    //GPIO_InitTypeDef GPIO_InitStructure;
	  //USART_InitTypeDef USART_InitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
     	
	/*GPIOB clocks enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	/* USART3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_4);
    
    /* NVIC configuration */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority= 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ�����̨���1?��
    NVIC_Init(&NVIC_InitStructure);	//?��?YNVIC_InitStruct?D???����?2?��y3?��??����a����NVIC??��??��USART1 
    
    /* USARTx configuration ----------------------------------------------------*/
	RS485_USART->CR1 = 0x0000;//����Ĵ���
	RS485_USART->CR3 = 0x0000;
	RS485_USART->CR1 |= (USART_WordLength_8b
								   |USART_Parity_No
								   |USART_Mode_Tx
								   |USART_Mode_Rx);
	   
		    RS485_USART->CR3 |= USART_HardwareFlowControl_None;
		    RS485_USART->BRR	= set_baud[BAND];
//	switch(Contr.Type)
//	{
//		case TS:
//		    RS485_USART->CR1 |= (USART_WordLength_9b
//								   |USART_Parity_Even
//								   |USART_Mode_Tx 
//								   |USART_Mode_Rx);
//		   
//		    RS485_USART->CR3 |= USART_HardwareFlowControl_None;
//		    RS485_USART->BRR	= set_baud[BAND]; //30M��ƵΪ125K
//		break;
//		case LD128EN_CRT_485_ZJ:
//		case FORSAFE_SF:
//		//case QN_193K_SF_ZJ:
//			RS485_USART->CR1 |= (USART_WordLength_8b
//								   |USART_Parity_No
//								   |USART_Mode_Tx 
//								   |USART_Mode_Rx);
//		   
//			RS485_USART->CR3 |= USART_HardwareFlowControl_None;
//			RS485_USART->BRR	= UART_BAUD_9600;
//		break;
//		case LD128EN_CRT_JT:
//			RS485_USART->CR1 |= (USART_WordLength_8b
//								   |USART_Parity_No
//								   |USART_Mode_Rx);
//	   
//		    RS485_USART->CR3 |= USART_HardwareFlowControl_None;
//		    RS485_USART->BRR	= UART_BAUD_9600;
//		break;
//		case TX3607_FW19000_485:
//			RS485_USART->CR1 |= (USART_WordLength_8b
//									|USART_Parity_No
//									|USART_Mode_Tx 
//									|USART_Mode_Rx);
//					
//			RS485_USART->CR3 |= USART_HardwareFlowControl_None; 
//			RS485_USART->BRR  = UART_BAUD_28800;
//		break;
//		case Parallel_Debug:
//			RS485_USART->CR1 |= (USART_WordLength_8b
//								   |USART_Parity_No
//								   |USART_Mode_Tx);
//	   
//		    RS485_USART->CR3 |= USART_HardwareFlowControl_None;
//		    RS485_USART->BRR	= set_baud[BAND];
//			break;
//		default:
//			 RS485_USART->CR1 |= (USART_WordLength_9b
//								   |USART_Parity_Even
//								   |USART_Mode_Tx 
//								   |USART_Mode_Rx);
//		   
//		    RS485_USART->CR3 |= USART_HardwareFlowControl_None;
//		    RS485_USART->BRR	= set_baud[BAND]; //30M��ƵΪ125K
//		break;
//	}

}
//===============================================================================
//��������:����5��ͬ��������
//�������: type:������������
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================
void RS485_Uart_Init(UINT8 type)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if((type == UART_SEND_INIT)||(type == UART_SEND_NO_INIT))			//����?��
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_10); 	
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; 			//
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		  	//��?������?3?
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOB,GPIO_Pin_11);
        
        RS485_SND();
        
        RS485_USART->CR1 |=  USART_Mode_Tx;
        RS485_USART->CR1 &= ~USART_Mode_Rx;
        RS485_USART->CR2 |= USART_StopBits_2;
        USART_ITConfig(RS485_USART, USART_IT_RXNE, DISABLE); 
//        if(type == UART_STA_SEND_NO_INT)                  //2��?������?��
//        {
//            USART_ITConfig(RS485_USART, USART_IT_TC, DISABLE);
//        }
//        else                                              //?D??����?��
//        {
//            USART_ITConfig(RS485_USART, USART_IT_TC, ENABLE);		//?a???����??D??2?��?
//        }
//        USART_Cmd(RS485_USART, ENABLE); 
//		RS485_USART -> CR1|=0x0049;
		RS485_USART -> CR1|=0x0009;
    }
    else if((type == UART_REC_INIT) || (type==UART_REC_NO_INIT))
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_10); 	
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; 		
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT; 			//��?������?3?
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11; 				//PB11
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;			  
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOB,GPIO_Pin_2);
        
        RS485_RCV();
        
        RS485_USART->CR1 &= ~USART_Mode_Tx;
        RS485_USART->CR1 |=  USART_Mode_Rx;
        RS485_USART->CR2 |= USART_StopBits_1;
        USART_ITConfig(RS485_USART, USART_IT_TXE, DISABLE); 			
        USART_ITConfig(RS485_USART, USART_IT_TC, DISABLE); 			
        if(type == UART_STA_RECE_NO_INT)                 //2��?��?����?
        {
            USART_ITConfig(RS485_USART, USART_IT_RXNE, DISABLE);	
        }
        else                                                     //?D???����?
        {
            USART_ITConfig(RS485_USART, USART_IT_RXNE, ENABLE);	
        }
        USART_Cmd(RS485_USART, ENABLE);							//��1?����??�� 
    }
	else if(type == UART_CLOSE_TXD)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_10); 
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;				//PB10
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;				
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		RS485_USART->CR1 &= ~USART_Mode_Tx;
		USART_ITConfig(RS485_USART, USART_IT_TXE, DISABLE);			
		USART_ITConfig(RS485_USART, USART_IT_TC, DISABLE);
		USART_Cmd(RS485_USART, ENABLE); 
	}
    else
    {
        RS485_USART->CR1 &= ~USART_Mode_Tx;
        RS485_USART->CR1 &= ~USART_Mode_Rx;
        USART_ITConfig(RS485_USART, USART_IT_RXNE, DISABLE);	
        USART_ITConfig(RS485_USART, USART_IT_TXE, DISABLE);	
        USART_ITConfig(RS485_USART, USART_IT_TC, DISABLE);	
        USART_Cmd(RS485_USART, DISABLE);	
        
        GPIO_SetBits(GPIOB,GPIO_Pin_10); 
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; 				//PB10
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		  	    //��?������?3?
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11; 				//PB11
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;			    //
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
} 
//===============================================================================
//��������: 485���ڲ�ͬ״̬�л�
//�������: type:������������
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================
void  Contr_485Uart_Sta_Switch(UINT8 type) 
{	

	if(type == UART_SEND_INIT)
	{
		  RS485_Uart_Init(UART_SEND_INIT);
	}
	else if(type == UART_SEND_NO_INIT)
	{
		  RS485_Uart_Init(UART_SEND_NO_INIT);
	}
	
	else if(type == UART_REC_INIT)									
	{
		  RS485_Uart_Init(UART_REC_INIT);
	} 
	else if(type == UART_CLOSE_TXD) 
	{
		  RS485_Uart_Init(UART_CLOSE_TXD);
	}
}
//===============================================================================
//��������: 232���ڵײ��ʼ��
//�������: ��
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================
void Contr_232Uart_Init(UINT8 BAND)//RS232
{
	UINT16 set_baud[5]={UART_BAUD_115200,UART_BAUD_57600,UART_BAUD_38400,UART_BAUD_19200,UART_BAUD_9600};
    NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;
	
	/*GPIOA clocks enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	/* USART2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


    // Connect USART pins to AF8 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
    
    // NVIC configuration 
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority=2;//���д����շ��жϣ����ȼ����
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1 
    
    // USARTx configuration ----------------------------------------------------//


    RS232_USART->CR1 = 0x0000;//����Ĵ���
   	RS232_USART->CR3 = 0x0000;
	
	RS232_USART->CR1 |= (USART_WordLength_9b
								   |USART_Parity_Even 
								   |USART_Mode_Tx
								   |USART_Mode_Rx);
	   
	RS232_USART->CR3 |= USART_HardwareFlowControl_None;
	RS232_USART->BRR	= set_baud[BAND];
//    switch(Contr.Type)
//	{
//			case TS:
//				RS232_USART->CR1 |= (USART_WordLength_9b
//									   |USART_Parity_Even
//									   |USART_Mode_Tx 
//									   |USART_Mode_Rx);
//					   
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None;
//				RS232_USART->BRR	= set_baud[BAND];
//			break;
//			case EI2000_CRT_ZJ:
//			case GT603_SF_ZJ:
//			case SJ9102BA_CRT_ZJ:
//			case LD128EN_CRT_232_ZJ:
//			case QN_193K_SF_ZJ:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_No
//										|USART_Mode_Tx 
//										|USART_Mode_Rx);
//			
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_9600;
//			break;
//			case GST200_CRT_ZJ:
//			case GST200_CRT_JT:
//			case GST500_CRT_ZJ:
//			case GST500_CRT_JT:
//				if(Gst.init_mode==MARK)//ȫ1У��(8λ����λ����У�飬2λֹͣλ)
//				{
//					RS232_USART->CR1 |= (USART_WordLength_8b
//											|USART_Parity_No
//											|USART_Mode_Tx 
//											|USART_Mode_Rx);
//		
//					RS232_USART->CR3 |= USART_HardwareFlowControl_None;
//					RS232_USART->BRR  = UART_BAUD_2400; //30M��ƵΪ125K
//				}
//				else if(Gst.init_mode==SPACE)//ȫ0У��(9λ����λ����У��)
//				{
//					RS232_USART->CR1 |= (USART_WordLength_9b
//											|USART_Parity_No
//											|USART_Mode_Tx 
//											|USART_Mode_Rx);
//		
//					RS232_USART->CR3 |= USART_HardwareFlowControl_None;
//					RS232_USART->BRR  = UART_BAUD_2400; //30M��ƵΪ125K
//				}
//			break;
//			
//			case QN5010_CRT_ZJ:
//			case QN5010_CRT_JT:
//			case NT8003_CS_ZJ:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_No
//										|USART_Mode_Tx 
//										|USART_Mode_Rx);
//			
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_2400;
//			break;
//			case GST200_SF_ZJ:
//			case GST500_SF_ZJ:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_No
//										|USART_Mode_Tx 
//										|USART_Mode_Rx);
//						
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_4800;
//			break;
//			case TC5120_PRT_JT:
//			case LD128EN_CRT_JT:
//			case SJ9102BA_CRT_JT:
//			case FHSJ9108_PRT:
//			case LD128EN_PRT:
//			case N3030_OLD:
//			case PTW3300_JT:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//									|USART_Parity_No
//									|USART_Mode_Rx);
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_9600;
//			break;
//			case TANDA3004_PRT:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_No
//										|USART_Mode_Rx);
//						
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_115200;
//			break;
//			case SIMPLEX_CRT_ZJ:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_Even
//										|USART_Mode_Tx
//										|USART_Mode_Rx);
//			
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_9600;
//			break;
//			case TX3607_FW19000_232:
//				RS232_USART->CR1 |= (USART_WordLength_8b
//										|USART_Parity_No
//										|USART_Mode_Tx 
//										|USART_Mode_Rx);
//						
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None; 
//				RS232_USART->BRR  = UART_BAUD_28800;
//			break;
//			case Parallel_Debug:
//			RS232_USART->CR1 |= (USART_WordLength_8b
//								   |USART_Parity_No
//								   |USART_Mode_Tx);
//	   
//		    RS232_USART->CR3 |= USART_HardwareFlowControl_None;
//		    RS232_USART->BRR	= set_baud[BAND];
//			break;
//			default:
//				RS232_USART->CR1 |= (USART_WordLength_9b
//									   |USART_Parity_Even
//									   |USART_Mode_Tx 
//									   |USART_Mode_Rx);
//					   
//				RS232_USART->CR3 |= USART_HardwareFlowControl_None;
//				RS232_USART->BRR	= set_baud[BAND];
//			break;
//		}

}

//===============================================================================
//��������:����3��ͬ��������
//�������: type:������������
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================

void RS232_Uart_Init(UINT8 type)
{
   GPIO_InitTypeDef GPIO_InitStructure;

    if((type == UART_SEND_INIT)||(type == UART_SEND_NO_INIT))			//����
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_2); 	
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 			//
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;		  	//�������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        RS232_USART->CR1 |=  USART_Mode_Tx;
        RS232_USART->CR1 &= ~USART_Mode_Rx;
        RS232_USART->CR2 |= USART_StopBits_2;
		USART_ITConfig(RS232_USART, USART_IT_RXNE, DISABLE); 
//       if(type == UART_STA_SEND_NO_INT)                 //��ѯ����
//        {
//            USART_ITConfig(RS232_USART, USART_IT_TC, DISABLE);
//        }
//        else                                                     //�жϷ���
//        {
//            USART_ITConfig(RS232_USART, USART_IT_TC, ENABLE);		//���������жϲ���
//        }
//        USART_Cmd(RS232_USART, ENABLE); 
		RS232_USART->CR1|=0x0009;
    }
    else if((type == UART_REC_INIT) || (type==UART_REC_NO_INIT) )
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_3); 	
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3; 			//PB10
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 				//PB11
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			    //
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        RS232_USART->CR1 &= ~USART_Mode_Tx;
        RS232_USART->CR1 |=  USART_Mode_Rx;
        RS232_USART->CR2 |= USART_StopBits_1;
        USART_ITConfig(RS232_USART, USART_IT_TXE, DISABLE); 			
        USART_ITConfig(RS232_USART, USART_IT_TC, DISABLE);
        if(type == UART_STA_RECE_NO_INT)                 //��ѯ����
        {
            USART_ITConfig(RS232_USART, USART_IT_RXNE, DISABLE);	
        }
        else                                                     //�жϽ���
        {
            USART_ITConfig(RS232_USART, USART_IT_RXNE, ENABLE);	
        }
        USART_Cmd(RS232_USART, ENABLE);							//ʹ�ܴ��� 
    }
	else if(type == UART_CLOSE_TXD)
	{
        GPIO_SetBits(GPIOA,GPIO_Pin_2); 
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 				//PB10
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		  	    //��?������?3?
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		RS232_USART->CR1 &= ~USART_Mode_Tx;
        USART_ITConfig(RS232_USART, USART_IT_TXE, DISABLE);	
        USART_ITConfig(RS232_USART, USART_IT_TC, DISABLE);
		USART_Cmd(RS232_USART, ENABLE); 
	}
    else
    {
        RS232_USART->CR1 &= ~USART_Mode_Tx;
        RS232_USART->CR1 &= ~USART_Mode_Rx;
        USART_ITConfig(RS232_USART, USART_IT_RXNE, DISABLE);	
        USART_ITConfig(RS232_USART, USART_IT_TXE, DISABLE);	
        USART_ITConfig(RS232_USART, USART_IT_TC, DISABLE);	
        USART_Cmd(RS232_USART, DISABLE);	
        
        GPIO_SetBits(GPIOA,GPIO_Pin_2); 
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 				//PB10
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;		  	    //�������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3; 				//PB11
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
} 
//===============================================================================
//��������: 232���ڲ�ͬ״̬�л�
//�������: type:������������
//�������: ��
//�޸�����: 2016-05
//�޸���Ա: 
//===============================================================================
void Contr_232Uart_Sta_Switch(UINT8 type) 
{

	if(type == UART_SEND_INIT)
	{
        RS232_Uart_Init(UART_SEND_INIT);
	}
	else if(type == UART_REC_INIT)									
	{
        RS232_Uart_Init(UART_REC_INIT);
	} 
	else if(type == UART_CLOSE_TXD) 
	{
        RS232_Uart_Init(UART_CLOSE_TXD);
	}
}

//===========================================================================================
//��    ���� void Make_Crc(split *crc ,uchar data)
//��    �ܣ� CRC
//��    ���� crc data
//�� �� ֵ:  ��
//--------------------------------------------------------------------------------------------
//�������ڣ�  2011.11
//============================================================================================
void Make_Crc(split *crc ,uchar data)
{
   UINT8  uIndex ;             				/*CRCѭ������*/

   uIndex = (*crc).byte[0] ^ (data);       	/*����CRC*/
  (*crc).byte[0] = (*crc).byte[1] ^ auchCRCHi[uIndex];
  (*crc).byte[1] = auchCRCLo[uIndex];
  
}


//===========================================================================================
//��    ���� void Slave_Uart_Over_With_Err(void)
//��    �ܣ� ������ģʽ���մ�����
//��    ���� UART_BUFFER  *buff: ����ָ��
//�� �� ֵ:  ��
//--------------------------------------------------------------------------------------------
//�������ڣ�  2016.5
//============================================================================================
void Master_Uart_Over_With_Err(UART_BUFFER *buff)
{
	if(buff->Send.RepeatNum)
	{
		buff->RunSta = RUN_STA_WAIT;
	}
	else
	{
		buff->RunSta = RUN_STA_DEAL;
	} 
	buff->Rec.Status = UART_REC_ERR; 
}
//===========================================================================================
//��    ���� void Master_Uart_Over_With_Succ(void)
//��    �ܣ� ������ģʽ���ճɹ�
//��    ���� UART_BUFFER  *buff: ����ָ��
//�� �� ֵ:  ��
//--------------------------------------------------------------------------------------------
//�������ڣ�  2016.5
//============================================================================================
void Master_Uart_Over_With_Succ(UART_BUFFER  *buff)
{
	buff->RunSta = RUN_STA_DEAL; 
	buff->Rec.Status = UART_REC_OVER;	
	buff->Send.RepeatNum = 0; 
}


//===============================================================================
//��������: ��ض�ʱ������
//�������: UART_BUFFER *buff: ����ָ��
//�������: ��
//�޸�����: 2014-07
//�޸���Ա: κ����
//===============================================================================
void Monitor_Master_Timer_Run(UART_BUFFER *buff)
{
	buff->FrameTimer++;	
	switch(buff->RunSta)
	{
		case RUN_STA_TXD:
			buff->Send.ByteInterval++;
			break;
			
		case RUN_STA_RXD:
			if(buff->Rec.WaitTime)
			{			
				buff->Rec.WaitTime--;
			}
			if(buff->Rec.ActualLen)
			{
				buff->Rec.ByteInterval++;
			}
			break;
			
		case RUN_STA_WAIT:
			buff->FrameIntervalTime++;
			break;
			
		default:
			buff->FrameIntervalTime = 0;
			break;
	}
}


//========================================================================
//��    ���� void Monitor_Master_Uart(void)
//��    �ܣ� ���ڼ��
//��    ���� ��
//�� �� ֵ:  ��
//-------------------------------------------------------------------------
//�������ڣ�  2013.3
//=========================================================================
void Monitor_Master_Uart(UART_BUFFER  *buff)
{							
    //��վʹ��
    //֡ʱ�䳬���ж�
    if(buff->RunSta > RUN_STA_IDLE)
    {	//֡�����أ�һ֡���ݽ��з��͡����յȳ�ʱ��2000ms��λ֡�շ�
        if(buff->FrameTimer > BUS_MAX_FRAME_INTERVAL)//8ms,250*8=2000ms
        {
            buff->FrameTimer= 0;
            //buff->RunSta = RUN_STA_IDLE;
        }
    }
    //���Ӷ���
	if(buff->RunSta == RUN_STA_RXD)						//�����ֽڼ��					
	{
		if(buff->Rec.WaitTime == 0)
		{
			Master_Uart_Over_With_Err(buff);
		}
		if((buff->Rec.Status > UART_REC_HEARD)&&(buff->Rec.Status < UART_REC_CRCH))
		{
			if(buff->Rec.ByteInterval > BUS_RECEIVE_INTERVAL)
			{
				buff->Rec.Status       = UART_REC_HEARD;
				buff->Rec.ByteInterval = 0;
				buff->Rec.ActualLen    = 0;
				buff->Rec.TotalLen     = 0;
				memset(buff->Rec.Buff,0x00,UART_BUFFER_LEN);
			}
		}
	}
	else if(buff->RunSta == RUN_STA_TXD)				//�����ֽڼ��		
	{
		if(buff->Send.ByteInterval > BUS_RECEIVE_INTERVAL)
		{
			buff->Send.ByteInterval = 0;
			Master_Uart_Over_With_Err(buff);
		}
	}

}



void Master_Uart_Rec_Data(UART_BUFFER *buff, USART_TypeDef *uart)
{
	UINT8 temp;

	temp = (UINT8)uart->RDR;
	buff->Rec.ByteInterval = 0;
	buff->Rec.Buff[buff->Rec.ActualLen] = temp;
	buff->Rec.ActualLen++;
	switch(buff->Rec.Status)
	{
		case UART_REC_HEARD:
			if(0x7F == temp) 									//�����ݳ���
			{
				buff->Rec.Crc.word = 0xFFFF;
				Make_Crc(&buff->Rec.Crc,temp);
				buff->Rec.Buff[0] = temp;
				buff->Rec.ActualLen = 1;
				buff->Rec.Status++;
			}
			break;

		case UART_REC_LEN:
			Make_Crc(&buff->Rec.Crc,temp);
			if((temp < 200)&&(temp > 2)) 
			{
				buff->Rec.Status++;
			}
			else
			{
				Master_Uart_Over_With_Err(buff);
				buff->Rec.Status = UART_REC_HEARD;
			}	 
			break;
			
		case UART_REC_DATA:
			if((buff->Rec.Buff[1]+2) > buff->Rec.ActualLen)
			{	
				Make_Crc(&buff->Rec.Crc,temp);
				break;
			}
			else
			{
				buff->Rec.Status++;
			}
			
		case UART_REC_CRCL:
			if(buff->Rec.Crc.byte[0] == temp)			  // Receiving
			{
				buff->Rec.Status++;
			}
			else
			{	
				Master_Uart_Over_With_Err(buff);
			}
			break;

		case UART_REC_CRCH:
			if(buff->Rec.Crc.byte[1] == temp)  
			{
				Master_Uart_Over_With_Succ(buff);
			}
			else
			{
				Master_Uart_Over_With_Err(buff);
			}
			break;

		default:
			 Master_Uart_Over_With_Err(buff);
			break;
	}	
}

//===============================================================================
//��������: �������ݷ���
//�������: UART_BUFFER *buff: ����ָ��
//          USART_TypeDef* uart: ����ָ��
//�������: ��
//�޸�����: 2014-07
//�޸���Ա: κ����
//===============================================================================
void Master_Uart_Send_Data(UART_BUFFER *buff, USART_TypeDef *uart)
{
	buff->Send.ByteInterval = 0;
	switch(buff->Send.Status)
	{	
		case UART_SEND_DATA:
			if(buff->Send.ActualLen < buff->Send.TotalLen)									//����N���ֽ�
			{
				uart->TDR = buff->Send.Buff[buff->Send.ActualLen];
				Make_Crc(&buff->Send.Crc,buff->Send.Buff[buff->Send.ActualLen]);
				buff->Send.ActualLen++;
				break;
			}
			else
			{
				buff->Send.Status = UART_SEND_CRCL;
			}
			
		case UART_SEND_CRCL:
			uart->TDR = buff->Send.Crc.byte[0];
			buff->Send.Status = UART_SEND_CRCH;
			break;
			
		case UART_SEND_CRCH:
			uart->TDR = buff->Send.Crc.byte[1];
			buff->Send.Status = UART_SEND_OVER;
			break;
				
		case UART_SEND_OVER:
			buff->RunSta = RUN_STA_RXD;
			break;

		default:
			Master_Uart_Over_With_Err(buff);
			break;
	}
}


//===============================================================================
//��������: �������ӿڣ����ڽ���
//�������: ��
//�������: ��
//�޸�����: 2016-09
//�޸���Ա: 
//===============================================================================
void Controller_Uart_Rec_Data(CONTR_IF *buf, USART_TypeDef *uart)
{
	UINT8 temp;

	temp = (UINT8)uart->RDR;

	buf->R.Buf[buf->R.Head] = temp;
	buf->R.Head++;
	buf->R.ByteInterval = 0;
	if(buf->R.Head == CONTR_BUF_LEN)
	{
		buf->R.Head = 0;
	}	
}

//===============================================================================
//��������: �������ӿڣ����ڷ���
//�������: ��
//�������: ��
//�޸�����: 2016-09
//�޸���Ա: 
//===============================================================================
void Controller_Uart_Send_Data(CONTR_IF *buf, USART_TypeDef *uart)
{
	if(buf->T.Sta == SENDING) 								//����N���ֽ�
	{
		if(buf->T.Clev < buf->T.Tail)
		{
			uart->TDR = buf->T.Buf[buf->T.Clev];
			buf->T.Clev++;
		}
		else
		{
			buf->T.Clev = 0;
			buf->T.Tail = 0;
			if(buf == &RS232)
			{
				RS232_Uart_Init(UART_STA_RECE_INT);
			}
			else if(buf == &RS485)
			{
//				RS485_Uart_Init(UART_CLOSE_TXD);
			}
			buf->T.Sta = SEND_IDLE;
		}
    }
}

//void USART_IRQHandler(void)
//{
//	__IO UINT32 temp;

//	if(USART_GetITStatus(RS232_USART, USART_IT_RXNE) != RESET)  //�����ж�
//    {
//        Controller_Uart_Rec_Data(&RS232, RS232_USART);
//    }
//    else if(USART_GetITStatus(RS232_USART, USART_IT_TC) != RESET)//��������ж�
//    {
//        Controller_Uart_Send_Data(&RS232, RS232_USART);
//    }
//	// USART3��USART4����һ���жϴ���
//	else if(USART_GetITStatus(RS485_USART, USART_IT_RXNE) != RESET)  //�����ж�
//	{
//	   Controller_Uart_Rec_Data(&RS485, RS485_USART);
//	}
//	else if(USART_GetITStatus(RS485_USART, USART_IT_TC) != RESET)//��������ж�
//	{
//	   Controller_Uart_Send_Data(&RS485, RS485_USART);
//	}   
//	else
//	{
//		temp = RS232_USART->RDR;
//		temp = RS232_USART->TDR;
//    	USART_ClearFlag(RS232_USART,0x039F);
//		temp = RS485_USART->RDR;
//		temp = RS485_USART->TDR;
//		USART_ClearFlag(RS485_USART,0x039F);
//	}
//}
 void RS232_IRQHandler(void)
 {
	 __IO UINT32 temp;
 
	 if(USART_GetITStatus(RS232_USART, USART_IT_RXNE) != RESET)  //�����ж�
	 {
		 Controller_Uart_Rec_Data(&RS232, RS232_USART);
	 }
	 else if(USART_GetITStatus(RS232_USART, USART_IT_TC) != RESET)//��������ж�
	 {
		RS232_USART->ICR |= 0x0040; 
		Controller_Uart_Send_Data(&RS232, RS232_USART);
	 }
	 else
	 {
		 temp = RS232_USART->RDR;
		 temp = RS232_USART->TDR;
		 RS232_USART->ICR |= 0x0040;
	 }
 }


 /*********************************************************************************
 * �������� :  UART5_IRQHandler
 * �������� :  ��Ƭ�� ����5�жϴ�������485����
 * ������� : 
 * ������� :  ��
 * �� �� ֵ     :  ��
 * �޸����� :  2016-01-25
 *********************************************************************************/
//void RS485_IRQHandler(void)
//{
//   __IO UINT32 temp;

//   if(USART_GetITStatus(RS485_USART, USART_IT_RXNE) != RESET)  //�����ж�
//   {
//	   Controller_Uart_Rec_Data(&RS485, RS485_USART);
//   }
//   else if(USART_GetITStatus(RS485_USART, USART_IT_TC) != RESET)//��������ж�
//   {
//		RS485_USART->ICR |= 0x0040;
//		Controller_Uart_Send_Data(&RS485, RS485_USART);   
//   }   
//   else
//   {
//	   temp = RS485_USART->RDR;
//	   temp = RS485_USART->TDR;
//	   RS485_USART->ICR |= 0x0040; 
//   }
//}






