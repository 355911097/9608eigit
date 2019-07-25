

#include "ex_flash.h"
//#include "xycnbus.h"

#include "sys_init.h"

//------------------------------------- variable ------------------------------------

const UINT32 FLASH_ADDR[CHECK] = {	
    ADDR_FLASH_SYSCONFIG,
    ADDR_FLASH_RECORD,
};
					
const UINT16 FLASH_SLEN[CHECK] = { 				
    SLEN_FLASH_SYSCONFIG,
    SLEN_FLASH_RECORD,
};

const UINT16 FLASH_ALEN[CHECK] = { 			
    ALEN_FLASH_SYSCONFIG,
    ALEN_FLASH_RECORD,
};

//ÿһ���������
const UINT16 FLASH_MAXN[CHECK] = { 				
    MAXN_FLASH_SYSCONFIG,
    MAXN_FLASH_RECORD,
};

const UINT16 FLASH_TIMES[CHECK]	= { 						
    TIMES_FLASH_SYSCONFIG,
    TIMES_FLASH_RECORD,
};
FLASH_STA Flash;

UINT8 flash_timer;
UINT16 flash_buf[256];

//���У���
UINT8 CheckSum_Xor(UINT8 *p,UINT16 n)
{
	UINT16 i;
	UINT8 sum = 0;

	for(i=0;i<n;i++)
		sum ^= *(p+i);
	return sum;
}


// ================================================================
//  ����ԭ��         :  void SPI_Flash_Init(void)
//  ��������         :  flash���IO��SPI��ʼ��
//  �������1        :  void
//  �������         :  void
//  ����ֵ           :  void
//  ---------------------------------------------------------------------------------------
//  ���¼�¼��  2013.10.15
//  =================================================================
//��ʼ��SPI FLASH��IO��
void SPI_Flash_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	//CS��WP����
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);//CS
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//WP
	
	//SPI1����
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);//PA5����ΪSPI1_SCK
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);//PA6����ΪSPI1_MISO
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);//PA7����ΪSPI1_MOSI
	//SPI1��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	
	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����SPI����ģʽΪ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//����SPI�����ݴ�С��SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//ʱ�ӿ���Ϊ��
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;//����Ϊ�������ʹ��SSIλ������NSS�ź�
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//���岨����Ԥ��ƵֵΪ4  12MHZ
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;//��������CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
	
}
// ================================================================
//  ����ԭ��         :  void Flash_Init(void)
//  ��������         :  flash��ʼ�����ж�˫flash����״̬
//  �������1        :  void
//  �������         :  void
//  ����ֵ           :  void
//  ---------------------------------------------------------------------------------------
//  ���¼�¼��  2014.11.15
//  =================================================================
void Flash_Init(void)
{
	SPI_Flash_Init();           //flashģ���ʼ��
	Flash.Nums = 1;
}
// ================================================================
//  ����ԭ��         :  void Flash_Error(void)
//  ��������         :  flash����
//  �������1        :  void
//  �������         :  void
//  ����ֵ           :  void
//  ---------------------------------------------------------------------------------------
//  ���¼�¼��  2014.11.15
//  =================================================================
void Flash_Error(void)
{
    Flash.Err |= (1 << Flash.Cs);
}
/******************************************************************************
Name:spi_send_char()
Description  : initlize the pins about SPI bus.
Arguments    : None
Return Value : None
******************************************************************************/
//void spi_send_char(UINT8 TxData)
//{
//	UINT8 retry=0;				 	
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
//	{
//		retry++;
//		if(retry>200)	return;
//	}			  
//	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
//}
/******************************************************************************
Name:spi_send_char()
Description  : initlize the pins about SPI bus.
Arguments    : None
Return Value : readed data from SPI
******************************************************************************/
//UINT8 spi_read_char(void)
//{
//	UINT8 retry=0;

//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
//	{
//		retry++;
//		if(retry>200)return 0;
//	}	  						    
//	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
//}


/********************************************************************************
* Function Name: UINT8 SPI3_ETH_SendByte(UINT8 byte)
* Description  : SPI3 receive and send.
* Arguments    : byte-The data to be sent.
* Return Value : The received data from SPI3.
* Call Relation: External
* Change Time  : 2014-11
*********************************************************************************/
UINT8 SPI1_ReadWriteByte(UINT8 TxData)
{
	UINT16 retry=0;	

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry > 2000)
		return 0;
	}			  
	SPI_SendData8(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>2000)
		return 0;
	}
	return SPI_ReceiveData8(SPI1); //����ͨ��SPIx������յ�����		
}

/******************************************************************************
Name		 :void Flash_Read_Id(UINT8 *id)
Description  :��FlashID.
Arguments    : id���洢3�ֽ�ID��the manufacturer ID of 1-byte and followed by Device ID of 2-byte��
Return Value : None
******************************************************************************/
void Flash_Read_Id(UINT8 *id)	
{
	UINT16 i;
	Flash_CS();
	Flash_UnLock();
	for(i=0;i<3000;i++);
   SPI1_ReadWriteByte(RDID);   			 //Write Read Status command = 0x05;
	for(i = 0;i < 3;i++)
	{
		id[i] = SPI1_ReadWriteByte(0xff);       // read status from flash
	}
	Flash_Lock();
	Flash_UnCS();
}
//********************************************************************
//* Function Name: Flash_SelfCheck��
//* Description  : ���Flash
//* Arguments    : None��
//* Return Value : ���������1��OK��0������
//********************************************************************
UINT8 Flash_SelfCheck(void)
{
	UINT8 id[3]={0,0,0};
	
	Flash_Read_Id(id);
	if(id[0] != MANU_ID)			return 0;
	else if(id[1] != DEV_ID)		return 0;
	else if(id[2] != DENSITY_ID)	return 0;
	return 1;
}
/******************************************************************************
Name		 :Flash_Read_Status_Register()
Description  :read status register.
Arguments    : None
Return Value : flash_status
******************************************************************************/
UINT8 Flash_Read_Status_Register(void)	
{
	UINT8 status;
	Flash_CS();
	Flash_UnLock();
    SPI1_ReadWriteByte(RDSR);   			 //Write Read Status command = 0x05;
    status = SPI1_ReadWriteByte(0xff);       // read status from flash
	Flash_Lock();
	Flash_UnCS();
    return status;
}
/******************************************************************************
Name:Flash_Wait_Flash_Idle()
Description  :.
Arguments    : None
Return Value : None
******************************************************************************/
UINT8 Flash_Wait_Flash_Idle(void)
{
//	UINT32 time = 0;
	UINT8 StatusReg;
	UINT8 EraseOkFlag = TRUE;//,time_out = 0;            //* clear the erase ok flag to be TRUE */
	
	Flash_CS();
	Flash_UnLock();
	do
	{
		StatusReg = Flash_Read_Status_Register();
		/*if( (StatusReg & 0x01) == 0x00) // (write in progress bit)
           	break;
	    else if( time_out )
	    {
		    EraseOkFlag = FALSE;
		    break;
	    }
       	if(time++>2000000)  time_out=1; */
	}while(StatusReg & 0x01);
	Flash_Lock();
	Flash_UnCS();
	
	return EraseOkFlag;
}
/******************************************************************************
Name:Flash_Read_String()
Description  : read data from MX25L4005A.
Arguments    : data_address:start address in MX25L4005A;
			   data:buffer;
			   data_length:length of reading buffer
Return Value : None
******************************************************************************/
void Flash_Read_String(UINT32 data_address,UINT8 *data,UINT16 data_length)	
{
	UINT16 j;
	
	Flash_CS();
	Flash_UnLock();

	SPI1_ReadWriteByte(READ);	
	//3 bytes address,MSB first
	SPI1_ReadWriteByte((UINT8)((data_address>>16)&0xFF));        //Write Sector address
    SPI1_ReadWriteByte((UINT8)((data_address>>8)&0xFF));         //Write Sector address
    SPI1_ReadWriteByte((UINT8)(data_address&0xFF));              //Write Sector address
	for(j = 0;j < data_length;j++)
	{
		*(data+j) = SPI1_ReadWriteByte(0x00);
	}
	Flash_Lock();
	Flash_UnCS();
}

//******************************************************************************
void Flash_FastRead_String(UINT32 addr,UINT8 *p,UINT16 n)
{
    UINT16 i;
	Watch_Dog();
	
	Flash_CS();
	Flash_UnLock();
    (void)SPI1_ReadWriteByte(FAST_READ);                    //Write Fast Read command = 0x0B
    (void)SPI1_ReadWriteByte((UINT8)(addr>>16)&0xFF);        //Write Sector address
    (void)SPI1_ReadWriteByte((UINT8)(addr>>8)&0xFF);         //Write Sector address
    (void)SPI1_ReadWriteByte((UINT8)addr&0xFF);              //Write Sector address
    (void)SPI1_ReadWriteByte(0x00);                    		// Write dummy data
    for (i=0; i<n; i++)                 // 
    {                                   // n bytes read out until /CS goes high
        *(p+i) = SPI1_ReadWriteByte(0x00);
    }
	Flash_Lock();
    Flash_UnCS();
	
}
/******************************************************************************
Name:Flash_Enable_Write()
Description  : .
Arguments    : None
Return Value : None
******************************************************************************/
void Flash_Enable_Write(void)
{
	Flash_CS();
	Flash_UnLock();
	SPI1_ReadWriteByte(WREN);
	Flash_Lock(); 
	Flash_UnCS();
}
/******************************************************************************
Name:Flash_disable_Write()
Description  : .
Arguments    : None
Return Value : None
******************************************************************************/
void Flash_disable_Write(void)
{
	Flash_CS();
	Flash_UnLock();
	SPI1_ReadWriteByte(WRDI);
	Flash_Lock();
	Flash_UnCS();
}
/******************************************************************************
Name:Flash_Sector_Erase()
Description  : addr.
Arguments    : None
Return Value : None
******************************************************************************/
void Flash_Sector_Erase(UINT32 addr)         //Erase a sector (4K byte)
{
    //if(addr < ADDR_FLASH_SYSCONFIG)  return;         //��ֹ�ֿ⡢�����ⱻ��ɾ��
	Watch_Dog();

	Flash_Enable_Write();    
	Flash_CS();
	Flash_UnLock();
	SPI1_ReadWriteByte(SE);                    //Write Sector Erase command = 0x20;
	SPI1_ReadWriteByte((UINT8)((addr>>16)) & 0xFF);      //Write Sector address = AD1 = A23 �C A16
	SPI1_ReadWriteByte((UINT8)((addr>>8)) & 0xFF);       //Write Sector address = AD2 = A15 �C A8
	SPI1_ReadWriteByte((UINT8)(addr) & 0xFF);            //Write Sector address = AD3 A7 �C A0
	Flash_Lock();
	Flash_UnCS();    
	Flash_Wait_Flash_Idle();
	Flash_disable_Write(); 
}


// ================================================================
//  ����ԭ��         :  void Flash_Page_Program(UINT32 addr,UINT8 *p,UINT16 n)
//  ��������         :  //Program 256 byte per page
//  �������1        :  void
//  �������         :  void
//  ����ֵ           :  void
//  ---------------------------------------------------------------------------------------
//  ���¼�¼��  2014.12.15
//  =================================================================
//-------------< 256 bytes
void Flash_Page_Program(UINT32 addr,UINT8 *p,UINT16 n)  //Program 256 byte per page
{
    UINT16 i;
	UINT8 buf[256];
    
	Flash_Enable_Write();    
	Flash_CS();
	Flash_UnLock();
   
    SPI1_ReadWriteByte (WRITE);                   		// Write Page Program command
    SPI1_ReadWriteByte((UINT8)(addr>>16)&0xFF);          // Write Sector address = AD1 = A23 ?A16
    SPI1_ReadWriteByte((UINT8)(addr>>8)&0xFF);           // Write Sector address = AD2 = A15 ?A8
    SPI1_ReadWriteByte((UINT8)addr&0xFF);                // Write Sector address = AD3 A7 ?A0
    for (i=0; i<n ; i++)               				// set a loop to down load whole page data into flash�s buffer
    {                                  				// the page number is 256 bytes
    	(void)SPI1_ReadWriteByte(*(p+i));  				// WDi stands for write data 0 ~ 255 bytes
    }
   	Flash_UnLock();
	Flash_UnCS();

    Flash_Wait_Flash_Idle();
	Flash_disable_Write();
	Flash_Read_String(addr,buf,n);	//!!!!!���һ��Ҫ�ӣ�����ڶ���д����
} 

void Flash_Get_ASC16(UINT32 c,UINT8 *c_buff)
{
    c *= 60;
    Flash_FastRead_String(ADDR_ASC_START + c,c_buff,60);    
}
//---------
void Flash_Get_HZ16(UINT16 hz,UINT8 *hz_buff)
{
    UINT8 qh,wh;
    UINT32 offset;
   
    wh  = (UINT8)(hz>>8);
    wh -= 0xA0;
    //qu ma
    qh  = (UINT8)hz;
    qh -= 0xA0;
	//offset
    offset  = 94*((UINT32)qh-1);
    offset += (wh-1);
    offset *= 120;
    
    Flash_FastRead_String(ADDR_HZ_START + offset,hz_buff,120);    
}

 /*================================================================
  ����ԭ��         :  void Flash_Write_String(UINT32 data_address,UINT8 *data,UINT16 data_length)	
  ��������         :  ��ҳ��256 bytes��д
  �������1        :  data_address:д��ַ,data:д�����ַ,data_length:���ݳ���
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2013.10.16
  =================================================================*/
//write the data(data) with the lenth(data_length) to the ex_flash addr(data_address)
//deal the page edge problem, could across the page(256 bytes)
//the min unit to erase is sector(4k bytes), not is the page(256 bytes)

void Flash_Write_String(UINT32 data_address,UINT8 *data,UINT16 data_length)	
{
	UINT16 i,len = data_length;
	UINT16 left  = (UINT16)(data_address % 256);	

    //if(data_address < ADDR_FLASH_SYSCONFIG)  return;     //��ֹ�ֿ⡢�����ⱻ�����
	if((left + len) <= 256)	
	{
		Flash_Page_Program(data_address,data,len);
	}
	else
	{
		Flash_Page_Program(data_address,data,256-left);	
		len  = len + left - 256;
		left = 256 - left;
		for(i = 256;i <= len;i += 256)
		{
            Watch_Dog();
			Flash_Page_Program(data_address + left + (i - 256),data + left + (i - 256),256);
		}
		if(len % 256)
        {
			Flash_Page_Program(data_address + left + (i - 256),data + left + (i - 256),len % 256);	
        }
	}
}
 /*================================================================
  ����ԭ��         :  void Flash_Write_3String(UINT32 data_address,UINT8 *data,UINT16 data_length )	
  ��������         :  ������д
  �������1        :  data_address:д��ַ,data:д�����ַ,data_length:���ݳ���
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2013.10.16
  =================================================================*/
//write the 3 copy data
//support across the page
void Flash_Write_3String(UINT32 data_address,UINT8 *data,UINT16 data_length)	
{
	UINT8 i;
	
	for(i=0;i<3;i++)
	{
		Flash_Write_String(data_address,data,data_length);
		data_address += COPY_SIZE_FLASH;
	}
}


 /*================================================================
  ����ԭ��         :  void Flash_Read_3String(UINT32 addr, UINT8 * rd_buf, UINT16 len )
  ��������         :  �����ݶ�
  �������1        :  addr:��ַ,rd_buf:�����ַ,len:���ݳ���
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2013.10.16
  =================================================================*/

void Flash_Read_3String(UINT32 addr, UINT8 * rd_buf, UINT16 len)
{
	UINT8 a[DATA_SIZE],b[DATA_SIZE],c[DATA_SIZE];
	UINT16 i,readCounter;	
	UINT16 unRead_length,length;
	UINT32 data_address;

	memset(a,0,DATA_SIZE);
	memset(b,0,DATA_SIZE);
	memset(c,0,DATA_SIZE);
	
	data_address = addr;
	unRead_length = len;
	readCounter = 0;
	while(unRead_length)
	{
        Watch_Dog(); 
		if(unRead_length > DATA_SIZE)
		{
			length = DATA_SIZE;
			unRead_length -= DATA_SIZE;
		}
		else
		{
			length = unRead_length;
			unRead_length = 0;
		}
		Flash_Read_String(data_address,a,length);
		Flash_Read_String(data_address + COPY_SIZE_FLASH,b,length);
		Flash_Read_String(data_address + (COPY_SIZE_FLASH << 1),c,length);
		for(i = 0;i < length;i ++)
		{
			*(b+i)^=(*(a+i));
			*(c+i)&=(*(b+i));
			*(b+i)=~(*(b+i));
			*(a+i)=(*(a+i))&(*(b+i));
			*(rd_buf+(UINT16)readCounter*DATA_SIZE+(UINT16)i)=(*(a+i))|(*(c+i));	 
		}
		data_address += DATA_SIZE;
		readCounter++;
	}
}

 /*================================================================
  ����ԭ��         :  void Flash_Erase_3Addr(UINT32 data_address )
  ��������         :  �����ݲ�
  �������1        :  data_address:����ַ����Ϊ��sector�������ַ
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2013.10.16
  =================================================================*/
// ��� ָ����ַ���� �� �������ݵ�ַ���� ����
void Flash_Erase_3Addr(UINT32 data_address)
{	
	UINT8 i;
	for(i = 0;i < 3;i ++)				
	{
        Watch_Dog();

		Flash_Sector_Erase(data_address & 0xFFFFF000);
		data_address += COPY_SIZE_FLASH;	
	}
}

//********************************************************************
//* Function Name: Flash_Blank_Check��
//* Description  : Flash 3���ݿհ׼��,���Ȳ�Ҫ����4096
//* Arguments    : None��
//* Return Value : ���������1���գ�0���ǿ�
//********************************************************************
UINT8 Flash_Blank_Check(UINT32 addr,UINT16 len)
{
	UINT16 i;
	UINT8 buf[SIZE_SECTOR];
	
	Watch_Dog();

	Flash_Read_3String(addr, buf, len);
	for(i = 0; i < len; i++)
	{
		if(buf[i] != FLASH_STA_BLANK)
		{
			return 0;
		}
	}	
	return 1;	

}
 /*================================================================
  ����ԭ��         :  UINT8 Flash_Written_Check(UINT8 * souce , UINT8 * dest, UINT16 len)
  ��������         :  ��д�ж�
  �������1        :  
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2013.10.16
  =================================================================*/
UINT8 Flash_Written_Check(UINT8 * souce , UINT8 * dest, UINT16 len)
{
	UINT16 i;
	for(i = 0;i < len;i ++)
	{
		if((dest[i]^(*(souce+i)))&(*(souce+i)))	
		{
			break;
		}
	}
	if(i >= len)//could be written
	{
		return FLASH_DATA_WRITTEN_ALLOW;
	}
	return FLASH_DATA_WRITTEN_FORBID;
}


// ================================================================
//  ����ԭ��         :  void Flash_Delete_Info_Item(UINT8 type,UINT16 index)
//  ��������         :  ɾ��һ��
//  �������1        :  type:���ͣ�index:�����ľ����ַƫ��
//  �������         :  void
//  ����ֵ           :  void
//  ----------------------------------------------------------------
//  ���¼�¼��  2014.6.30
//  =================================================================
void Flash_Delete_Info_Item(UINT8 type,UINT16 index)
{
	UINT8 head = 0;
    UINT32 addr;
	if(type >= CHECK)
	{
		return;
	}
	if(index < FLASH_MAXN[type]*FLASH_TIMES[type])		// ɾ��FLASH�� -type�� -offset��������Ч��ʶ��
	{
        addr = FLASH_ADDR[type] + index * FLASH_ALEN[type];
		Flash_Read_3String(addr, &head, 1);
		if(head == FLASH_STA_VALID)
		{
            head = 0;
			Flash_Write_3String(addr, &head, 1);
		}
	}
}

 
/*================================================================
����ԭ��         :  void Flash_RWrite_String(UINT32 data_address,UINT8 *data,UINT16 data_length)
��������         :   ��дָ����ַ���ݣ����ı��������Ч(��0xaa��ͷ)���ݣ�ͬʱ������Ч����
�������1        :  data_address:��ַ��data:���棬data_length:����
�������         :  void
����ֵ           :  void
---------------------------------------------------------------------------------------
���¼�¼��  2013.10.16
=================================================================*/

void Flash_RWrite_String(UINT32 data_address,UINT8 *data,UINT16 data_length,UINT8 type)
{
	UINT32 addr_flash;
	UINT8  i;
	UINT8  buf[512];//SIZE_SECTOR
	
	addr_flash = data_address;
	if((data_address >= ADDR_FLASH_CHECK)
	||((data_address & 0xFFF) + data_length > SIZE_FLASH_SECTOR))	// ��ַ+����Խ���ж�
	{
		return ;
	}
		
	for(i = 0;i < 3;i ++)	                //3����
	{	
		Watch_Dog();

		Flash_Read_String(addr_flash, buf, data_length);
        if(FLASH_DATA_WRITTEN_FORBID == Flash_Written_Check(data, buf, data_length))
		{
            //max_group = SIZE_FLASH_SECTOR/(FLASH_TIMES[type]*FLASH_ALEN[type]);//һ��block�ڣ��ж���������
            
			//Flash_Sector_Read(addr_flash & 0xFFFFF000);           //��blcok�׵�ַ��ʼ������һ��blcok
			Flash_Sector_Erase(addr_flash & 0xFFFFF000);
           // memset(&buffer[(UINT16)(addr_flash&0x0FFF)], 0xFF, 1);//����0xAA�����,20141216//FLASH_ALEN[type]*FLASH_TIMES[type]);	//��д��Ļ�����գ������ߴ���д��

			/*if(type == RECORD)		//���ڵķ�ʽ��ʼ�ձ�����һ���հ�ҳ��д�жϵ�ʱ��ʼ��Ϊ��д�����򲻻����ô�
			{
				for(k = 0;k < ((addr_flash&0x0fff) / FLASH_ALEN[type]);k ++)//ֻ�����ӱ���¼��ǰ����Ч����
				{
					if(buffer[k*FLASH_ALEN[type]] == FLASH_STA_VALID)
					{
						Flash_Write_String((addr_flash&0xfffff000) + k * FLASH_ALEN[type],
						&buffer[k * FLASH_ALEN[type]], FLASH_ALEN[type]);	
					}
				}
			}
      else
      {
          UINT32 addr_group, addr_item,addr_buf;
          for(group = 0;group < max_group;group ++)//ÿ�鴦��
          {
              addr_group = group*FLASH_ALEN[type]*FLASH_TIMES[type];  //�ڼ��飬����ÿblock���32��ڵ���Ϣ�ĵڼ���
              for(item = 0;item < FLASH_TIMES[type];item ++)//ÿ�δ���
              {
                  addr_item = item*FLASH_ALEN[type];                 //TIMES��ĵڼ���
                  addr_buf = addr_group + addr_item;               //4k�еĵ�ַƫ��
                  if(buffer[addr_buf] == FLASH_STA_VALID)
                  {
                      //д������ĵ�һ�ε�λ��
                      Flash_Write_String((addr_flash&0xfffff000) + addr_group, &buffer[addr_buf], FLASH_ALEN[type]);
        
                    memcpy(str,&buffer[addr_buf],512);
                      break;
                  }   
              }
          }
      }*/
		}

		Flash_Write_String(addr_flash,data,data_length);		//д������Ҫ������
		addr_flash += COPY_SIZE_FLASH;							//�����ݵĵ�ַƫ����
	}
}

///**************************************next for record*********************************
 /*================================================================
  ����ԭ��         :  UINT16 Get_Item_To_Wr(UINT8 type, UINT16 offset,UINT8 *p, UINT8 * info)
  ��������         :  �õ���д�����ݵ�λ��:0,1,2,3.....
  �������1        :  offset:ƫ�ƣ�p:���棬info����д����
  �������         :  void
  ����ֵ           :  void
  ---------------------------------------------------------------------------------------
  ���¼�¼��  2014.6.24
  =================================================================*/
UINT16 Get_Item_To_Wr(UINT8 type, UINT32 addr,UINT8 * info)
{
	UINT16 item_pos=0;
	UINT8  flag=0;	
	UINT8  buf[512];//buf[SIZE_SECTOR];

    for(item_pos = 0;item_pos < FLASH_TIMES[type];item_pos ++)
    {
		Watch_Dog();

		Flash_Read_3String(addr, &flag, 1);
        //���ҵ�0xAA����info_pos��λ��0xAA��0xAA��һλ��
        //���Ҳ���0xAA����info_pos�ᶨλ�����һ��λ��+1��������
        if(flag == FLASH_STA_VALID)
        {
            Flash_Read_3String(addr+1, buf+1, FLASH_SLEN[type]+1);
            if(FLASH_DATA_WRITTEN_FORBID == Flash_Written_Check(info+1, buf+1, FLASH_SLEN[type]+1))//������ͷ������У���ֽڣ�ͷ��buffer[0]
            //����д�Ļ���info_pos��λ��0xAA����һλ��(�п��������λ��+1��������)
            //��д�Ļ���info_posͣ����0xAA��λ��
            {
                item_pos ++;                    //��֤Ҫд��λ����0xAA����һλ��
            }
            break;
        }
        addr += FLASH_ALEN[type];
    }
    return item_pos;
}
//==========================================================================
//��    ���� UINT8 Valid_FlashData(UINT16 offset)
//��    �ܣ� �õ���Ч�Ľڵ���Ϣ�洢λ��
//��    ���� �ڵ�ƫ������TDLA*64+LA
//�� �� ֵ:  0XFF:����Ч�ڵ���Ϣ��0-254������λ��
//--------------------------------------------------------------------------
//�������ڣ�  2014.6
//=========================================================================
// adjust "offset" address in FLASH is "0xaa" or not. 
// read the data to buffer [0].
// return 0,1-->offset
// retrun 0xff-->no valid data
//
UINT8 Valid_FlashData(UINT8 type, UINT16 offset)
{
    UINT32 addr = 0;
	UINT16 i;
    UINT8 flag = 0;
        
    addr = FLASH_ADDR[type] + offset * FLASH_TIMES[type] * FLASH_ALEN[type];
    if(type != RECORD)
    {
        for(i = 0;i < FLASH_TIMES[type];i ++)
        {
			Watch_Dog(); 

			Flash_Read_3String(addr, &flag, 1);
            if(flag == FLASH_STA_VALID)
            {
                break;			        //�ҵ�
            }
            addr += FLASH_ALEN[type];
        } 
        if(i >= FLASH_TIMES[type])
        {
            i = 0xFF;           //δ�ҵ�
        }
    }
    else
    {
        Flash_Read_3String(addr, &flag, 1);
        if(flag == FLASH_STA_VALID)
        {
            i = 0 ;             //�ҵ�
        }            
        else
        {
            i = 0xFF;		   //δ�ҵ�      
        }
    }
    return i;
}

/*================================================================
����ԭ��         :  UINT8 Flash_Load_Info(UINT8 type,UINT16 offset,UINT8 *p)
��������         :  Ӧ�ò�ӿڣ���
�������1        :  type:���ͣ�offset:ƫ�ƣ�p:����
�������         :  void
����ֵ           :  void
---------------------------------------------------------------------------------------
���¼�¼��  2013.10.16
=================================================================*/
// put the data into 'p',the type of data is "type"
// the length and address depending on "type".
// if 'p' is null,save the data with head and tail in"buffer".
// return vale: 1 validity
UINT8 Flash_Load_Info(UINT8 type,UINT16 offset,UINT8 *p)
{
	UINT16 cs_slen = 0;
    UINT32 addr_type;
	UINT8  buf[512];
	UINT8  offset_page,result = FALSE;
	if(type >= CHECK || offset >= FLASH_MAXN[type])
	{
		return 0;	
	}
        
    if(type == SYSCONFIG)
        offset = 0;
    
    offset_page = Valid_FlashData(type, offset);
    if(offset_page != 0xFF)
    {
        result = TRUE;
        addr_type = FLASH_ADDR[type] + ((UINT32)offset*FLASH_TIMES[type] + offset_page) * FLASH_ALEN[type];
    }

    if(result == TRUE)
    {
        //�ȵ��ζ����д�����3���ݶ�
        Flash_Read_String(addr_type+1, buf, FLASH_SLEN[type]+1);  
		if(type == RECORD)
		{
			cs_slen = FLASH_SLEN[type]-2;
		}
		else
		{
            cs_slen = FLASH_SLEN[type];		
		}
		
        if(CheckSum_Xor(buf, cs_slen) == buf[FLASH_SLEN[type]])
        {
            memcpy(p, buf, FLASH_SLEN[type]);						// ����ȥ��ͷ��β��������
        }
		else
        {
            Flash_Read_3String(addr_type+1, buf, FLASH_SLEN[type]+1);   
            if(CheckSum_Xor(buf, cs_slen) == buf[FLASH_SLEN[type]])
            {
                memcpy(p, buf, FLASH_SLEN[type]);						// ����ȥ��ͷ��β��������
            }
            else
            {
                result = FALSE;
            }
        }
    }
    return result;
}

/*================================================================
����ԭ��         :  UINT8 Flash_Save_Info(UINT8 type,UINT16 offset,UINT8 *p)
��������         :  Ӧ�ò�ӿڣ�д
�������1        :  type:���ͣ�offset:ƫ�ƣ�p:����
�������         :  void
����ֵ           :  void
---------------------------------------------------------------------------------------
���¼�¼��  2013.10.16
=================================================================*/
// ****************************************************************************
// the length of record depend on type.
//offset is the index of record whose type is "type".
void Flash_Save_Info(UINT8 type,UINT16 offset,UINT8 *p)
{
	UINT32 addr_type;
	UINT16 info_pos;
	UINT8  i,times;
	UINT8  info[512]; //���ϵͳ����512
	UINT8  buf[512];
	static UINT8 is_busy = 0;

	// �洢������Χ���˳�;��ѭ���洢���ʴ˴������Ƿ����쳣�ж�
	if(type >= CHECK || offset >= FLASH_MAXN[type])
	{
		return;
	}
    
    if(type == SYSCONFIG)
        offset = 0;
    
	if(is_busy)
		return;
	else
		is_busy = 1;
	
	//�������ͷβ
	info[0] = FLASH_STA_VALID;
	memcpy(info + 1, p, FLASH_SLEN[type]);
    
    if(type == RECORD)//��¼���ͣ��������ͺʹ����־��ı䣬�ʲ�����
    {
		info[FLASH_SLEN[type] + 1] = CheckSum_Xor(info + 1, FLASH_SLEN[type]-2);

		addr_type = FLASH_ADDR[type] + (UINT32)offset * FLASH_ALEN[type];
    }   
	else
    {

			info[FLASH_SLEN[type] + 1] = CheckSum_Xor(info + 1, FLASH_SLEN[type]);


		addr_type = FLASH_ADDR[type] + (UINT32)offset * FLASH_TIMES[type] * FLASH_ALEN[type];
        info_pos = Get_Item_To_Wr(type, addr_type, info);//���info_pos == FLASH_TIMES[type]�������������дλ�ö�λ����λ��
        addr_type += (info_pos % FLASH_TIMES[type]) * FLASH_ALEN[type];   //дλ��,�������һ��λ�ü�һ
    }

    for(i = 0;i < 2;i ++)
    {
        if(i)
        {
            if(Flash.Nums > 1)
            {
                Flash.Cs = !Flash.Cs;
            }
            else
            {
                break; 
            }
        }

        // д������Ƚϣ����3��
        times = 3;
        while(times)
        {
            Flash_RWrite_String(addr_type, info, FLASH_SLEN[type] + 2, type);     //0xaa + sizeof() + sum_xor
            Flash_Read_3String(addr_type, buf, FLASH_SLEN[type] + 2);	//0xaa + sizeof() + sum_xor
            if(memcmp(buf,info,FLASH_SLEN[type]+2) == 0)				    //0xaa + sizeof() + sum_xor
            {
                break;
            }
            else
            {
                times--;
            }			
        }	
        if(times == 0)			//3���޷�д�룬�ж�Ϊflash����
        {
            Flash_Error();
        }
        if(type != RECORD)			//�����ɵ�һ��
        {
            if((info_pos != 0) && (info_pos != FLASH_TIMES[type]))//����д��λ��Ϊ����Ļ�������ɾ������Ϣ����Ϊ����sector����
            {
                Flash_Delete_Info_Item(type, (UINT32)offset * FLASH_TIMES[type] + info_pos - 1);
            }
        }
        if(i)//����ԭ��оƬ
        {
            Flash.Cs = !Flash.Cs;
        }
    }
    
	
	is_busy = 0;
}



