#ifndef	__PC_COMM_H_      
#define	__PC_COMM_H_ 

#include "global.h"
#include "uart.h"



#define C_DEADLINE_TIME_10S    			10
//#define C_DEADLINE_TIME_100S    		100
//#define C_DEADLINE_TIME_200S    		200


/*==========================READ OR WRITE FLAG========================*/
#define   WRITE_REG_FLAG           0x01

/*=====================Register Access Mode===================*/
#define C_WRITE_SPECIAL_CODE_MODE   0x00        //0B00000000
#define C_READ_SPECIAL_CODE_MODE    0x01        //0B00000001
#define C_WRITE_BIT_MODE            0x20        //0B00100000
#define C_READ_BIT_MODE             0x21        //0B00100001
#define C_BIT_MODE                  0x20        //0B00100000
#define C_WRITE_BYTE_MODE           0x40        //0B01000000
#define C_READ_BYTE_MODE            0x41        //0B01000001
#define C_WRITE_MUl_BYTE_MODE       0x60        //0B01100000
#define C_READ_MUl_BYTE_MODE        0x61        //0B01100001

#define C_WRITE_MORE_BYTE_MODE      0x80        //0B10000000
#define C_READ_MORE_BYTE_MODE       0x81        //0B10000001

#define C_WRITE_MUl_BLOCK_MODE      0xA0        //0B10100000
#define C_READ_MUl_BLOCK_MODE       0xA1        //0B10100001

#define C_NO_SURPORT_MODE       	0xFF        //0B11111111


typedef struct
{
	UINT8 LogFlag;								//��¼��־
	UINT8 LogDeadLine;							//��¼ʱ��
	
    UINT8 WriteEn;           					//дʹ��
    UINT8 WriteDeadLine;						//дʹ��ʱ��
    
    UINT8 Shild;
}CTR_COMM_STA;
extern CTR_COMM_STA CtrCommSta;
#define B_INT_ENABLE    (CtrCommSta.Shild&0x02)


typedef struct
{	
    UINT8   type;
    UINT32  addr;
	split  rec_crc;
    split  wr_crc;
	UINT16  frame_num;
	UINT16  frame_num_last;
	UINT8   cmd_type;      //��������
    UINT16  data_len;
    UINT8   timer;
    //UINT8   data_buf[1080];
}STRUCT_FARAWAY_UPDATA;


typedef struct {//CTR Definition
    unsigned groupAddr      :3;
    unsigned readWrite      :1;
    unsigned anwser         :1;
    unsigned multileAddr    :1;
    unsigned frameDirection :1;
    unsigned extendCtr      :1;
} STRUCT_CTR_MERGE_BITS;

typedef union
{
    UINT8 byte;
    STRUCT_CTR_MERGE_BITS mbit;
}UNION_CONTROL_CODE;

typedef struct
{
    UINT32 addr;           								//Register Address
    UINT16 datalen;          							//���ݳ���
    UINT16 block_count;
    UINT16 valid_len;   	 							//������Ч����
    UINT16 unit_len;     								//��λ�鳤��    
	UINT16 anslen;										//Ӧ�����ݳ��� ����Ϊ0��ʶ����ҪӦ��
    UINT16 diLoc;          	 							//DI Location
    UINT16 dataLoc;         							//������λ�ã������ݴ���ʱ�����ܶ�����и���
	UINT16 answer_time;								//��ʱʱ��Ϊ0��ʾ����ҪӦ��
	UINT16 FrameLen;									//֡����  
	UINT8 mode;            							//Register mode of operation ����3λ��Ч����5λ��Ч
	UINT8 wildcardFlag;    								//ͳ���ʾ1:ͳ�� 0:��ͳ��
    UINT8 lenexpand;
	UINT8 MmadrFlag;									//�༶��ַ��ʶ
	UNION_CONTROL_CODE ctr;//CTR           
}STRUCT_DEV_COMMAND_PROCESS;
extern STRUCT_DEV_COMMAND_PROCESS DevCommPro;

#define	B_FRAME_ADDRESSING        	DevCommPro.ctr.mbit.groupAddr
#define B_READ_WRITE    	  	    DevCommPro.ctr.mbit.readWrite 
#define	B_ANSWER_STATE            	DevCommPro.ctr.mbit.anwser 
#define	B_MUL_ADDR    		  	    DevCommPro.ctr.mbit.multileAddr 
#define B_FRAME_DIRECTION         	DevCommPro.ctr.mbit.frameDirection
#define	B_EXTEND_CTR              	DevCommPro.ctr.mbit.extendCtr

#define C_DEADLINE_TIME_10S    			10


//#define C_CTR_PDC_SYSTEM    0XE0       //����չ�������޺���֡�޶༶��ַ

/***************************Ѱַ��ʽ*********************************/
#define	C_CTR_BROADCAST_ADR	             0x07
#define C_CTR_LA_ADR			         0x06
#define	C_CTR_ID_ADR				     0x05
#define C_CTR_UC_ADR				     0x02	

/*===============Status of answer===============*/
#define	C_NO_SUPPORT_ANSWER   	  	0xFE	

/*#define	C_NORMAL_ANSWER            	0x01				   
			
#define	C_CONDITION_LIMIT_ANSWET   	0xFD*/

#define         BOOT_VALID_FALG        0x3355aacc

/***************************????************************************/
void Dead_Line_1S(void);
UINT8 Operate_Level_Check_Comm(UINT8 level);
void Uart_Slaves_Init_Send(UART_BUFFER	*uart);
void Dev_Reg_Mode_1BYTE(UART_BUFFER  *uart);
void Dev_Reg_Mode_2BYTE(UART_BUFFER  *uart);
void Dev_Reg_Mode_NBYTE(UART_BUFFER  *uart);
void Dev_Reg_Mode_NBLOCK(UART_BUFFER  *uart);
void Dev_Reg_Mode(UART_BUFFER  *uart);
UINT8 Frame_Len_Anslyse(UART_BUFFER  *uart);
UINT8 Dev_Frame_Analyse(UART_BUFFER  *uart) ;
void Change_Byte(UINT8 *data,UART_BUFFER  *uart);
void Ans_Process_Normal(UART_BUFFER  *uart,UINT16 len,UINT8 *buff);
void Ans_Process_Comm_Ans(UART_BUFFER  *uart,UINT16 len,UCHAR8 *buff);
void Abnormal_Ans_Process(UINT16 answer,UART_BUFFER  *uart);
void Uart_Slave_Prepare_Send(UART_BUFFER  *uart,uchar8 len);
void Ans_Process_Poll_Normal(UART_BUFFER  *uart);
void Write_Special_Comm(UART_BUFFER  *uart);
void Read_Special_Comm(UART_BUFFER  *uart);
void Write_Bit_Reg(UART_BUFFER  *uart);
void Read_Bit_Reg(UART_BUFFER  *uart);
void Write_Byte_Reg(UART_BUFFER  *uart);
void Read_Byte_Reg(UART_BUFFER	*uart);
void Write_Mul_Byte_Reg(UART_BUFFER  *uart);
void Read_Mul_Byte_Reg_Para_Inf(UART_BUFFER  *uart);
void Read_Mul_Byte_Reg(UART_BUFFER  *uart);
UINT8 Check_Reg_Valid(UINT16 offset);
//UINT16 SaveAdrr_Dev(UINT16 offset)
void Write_MutBlock_Reg(UART_BUFFER  *uart);
void Read_MutBlock_Reg_Record(UART_BUFFER  *uart);
void Read_MutBlock_Reg(UART_BUFFER  *uart);
void Dev_Frame_Handle_Self_Comm(UART_BUFFER  *uart);
void Dev_Frame_Handle(UART_BUFFER  *uart);

#endif


