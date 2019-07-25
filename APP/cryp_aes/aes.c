#include "aes.h"

//����Ҳ�ǣ�ֱ��д��flash
const UINT8  AES_Key_Table[32] = {    
0xd0, 0x94, 0x3f, 0x8c, 0x29, 0x76, 0x15, 0xd8,  
0x20, 0x40, 0xe3, 0x27, 0x45, 0xd8, 0x48, 0xad,  
0xea, 0x8b, 0x2a, 0x73, 0x16, 0xe9, 0xb0, 0x49,  
0x45, 0xb3, 0x39, 0x28, 0x0a, 0xc3, 0x28, 0x3c, };

//��ʱ���������չkey,������չ����Կֱ��д��flash
UINT8 ExpandedKey[KEY_EXPAND_SIZE];


//#ifdef BACK_TO_TABLES
const UINT8 sbox[256] = {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
  0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
  0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
  0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
  0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
  0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
  0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
  0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
  0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
  0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
  0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
  0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
  0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
  0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
  0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
  0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
  0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const UINT8 sboxinv[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
  0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
  0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
  0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
  0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
  0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
  0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
  0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
  0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
  0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
  0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
  0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
  0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
  0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
  0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
  0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
  0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
/*
#define rj_sbox(x)   sbox[(x)]
#define rj_sbox_inv(x) sboxinv[(x)]
#else
UINT8 gf_alog(UINT8 x) // calculate anti-logarithm gen 3
{
  uint8_t atb = 1, z;
  while (x--) {z = atb; atb <<= 1; if (z & 0x80) atb^= 0x1b; atb ^= z;}
  return atb;
}
UINT8 gf_log(UINT8 x) // calculate logarithm gen 3
{
  UINT8 atb = 1, i = 0, z;
  do {
    if (atb == x) break;
    z = atb; atb <<= 1; if (z & 0x80) atb^= 0x1b; atb ^= z;
  } while (++i > 0);
  return i;
}
UINT8 gf_mulinv(UINT8 x) // calculate multiplicative inverse
{
  return (x) ? gf_alog(255 - gf_log(x)) : 0;
}
UINT8 rj_sbox(UINT8 x)
{
  UINT8 y, sb;
  sb = y = gf_mulinv(x);
  y = (y<<1)|(y>>7); sb ^= y; y = (y<<1)|(y>>7); sb ^= y; 
  y = (y<<1)|(y>>7); sb ^= y; y = (y<<1)|(y>>7); sb ^= y;
  return (sb ^ 0x63);
}
UINT8 rj_sbox_inv(UINT8 x)
{
  UINT8 y, sb;
  y = x ^ 0x63;
  sb = y = (y<<1)|(y>>7);
  y = (y<<2)|(y>>6); sb ^= y; y = (y<<3)|(y>>5); sb ^= y;
  return gf_mulinv(sb);
}
#endif*/



//===============================================================================
//��������: G(2)�˷�
//�������: xΪ����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
UINT8 rj_xtime(UINT8 x) 
{
  return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
}


//===============================================================================
//��������: �ֽ��û���ֱ��ʹ��S�����ԭ����
//�������: bytesΪ�û����ݣ�countΪ���ݸ���
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void SubBytes(UINT8 * bytes, UINT8 count) 
{  
    UINT8 i;
	for(i=0; i<count; i++)
	{
		// temp =  *(bytes+i);
		// *(bytes+i) = sbox[temp];
 		bytes[i] = sbox[bytes[i]];
	}
} 

//===============================================================================
//��������: ��һ����������
//�������: rowΪ��������
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void CycleLeft(UINT8 * row) 
{  
	// Cycle 4 bytes in an array left once. 
	unsigned char temp = row[0];  
	row[0] = row[1]; 
	row[1] = row[2];  
	row[2] = row[3]; 
	row[3] = temp; 
} 
//===============================================================================
//��������: ��2���������
//�������: bytes1Ϊ��Ҫ��������Լ�������
//                           bytes2Ϊ��������ݣ�
//                           countΪ���ݳ���
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void XORBytes(UINT8 * bytes1, UINT8 * bytes2, UINT8 count) 
{   
	UINT8 i;
	for(i=0;i<count;i++)
	{ 
		bytes1[i] ^= bytes2[i];
	}
}
//===============================================================================
//��������: ��չ��Կ
//�������: expandedkeyΪ������Կ
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//ԭ��: ��4��Ϊһ����չ��
//      ���� ��չ����Կ��ǰ4��������4��(�ô�-KEYLENGTH)����ó�
// ����: key[32]-k[35]��k[0]-k[4]��k[28]-k[31]���õ�
//               ����չ��ԿΪ32��������ʱ���������λ���滻�����
void KeyExpansion(UINT8 * expandedkey) 
{  
	UINT8 temp[4];  
	UINT8 i; 
	UINT8 Rcon[4] = { 0x01, 0x00, 0x00, 0x00 }; // Round constant.  
	//UINT8 * key = AES_Key_Table;   
	// Copy key to start of expanded key.
	i = KEYLENGTH;  

	memcpy(expandedkey, AES_Key_Table ,KEYLENGTH);
	expandedkey += KEYLENGTH;
	// Prepare last 4 bytes of key in temp. 
	expandedkey -= 4;	
	temp[0] = *(expandedkey++);  
	temp[1] = *(expandedkey++);
	temp[2] = *(expandedkey++);	
	temp[3] = *(expandedkey++); 
	
	// Expand key. 
	i = KEYLENGTH;	
	while( i < BLOCKSIZE*(ROUNDS+1) )	
	{	 // Are we at the start of a multiple of the key size?	 
		if( (i % KEYLENGTH) == 0 ) 
		{    
			CycleLeft( temp ); // Cycle left once.	
			SubBytes( temp, 4 ); // Substitute each byte.	 
			XORBytes( temp, Rcon, 4 ); // Add constant in GF(2).	  
			*Rcon = (*Rcon << 1) ^ (*Rcon & 0x80 ? BPOLY : 0); 
		} 
		// Keysize larger than 24 bytes, ie. larger that 192 bits?	 
		#if KEYLENGTH > 24  
		// Are we right past a block size?  
		else if( (i % KEYLENGTH) == BLOCKSIZE ) 
		{  
			SubBytes( temp, 4 ); // Substitute each byte.  
		}  
		#endif
		// Add bytes in GF(2) one KEYLENGTH away. 

		XORBytes( temp, expandedkey - KEYLENGTH, 4 ); 
		// Copy result to current 4 bytes. 
		*(expandedkey++) = temp[ 0 ];	
		*(expandedkey++) = temp[ 1 ];	
		*(expandedkey++) = temp[ 2 ];	
		*(expandedkey++) = temp[ 3 ];	 
		i += 4; // Next 4 bytes. 
	}
}

//===============================================================================
//��������: ���ܳ�ʼ��
//�������: 
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void Aes_Init(void)
{
	KeyExpansion(ExpandedKey);//��������ã��洢Ϊ����

}

//===============================================================================
//��������: �ֽ��û��Լ��������Կ��ֱ��ʹ����S���������
//�������: bytesΪ�û����ݣ�countΪ���ݸ���
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void InvSubBytesAndXOR(UINT8 * bytes, UINT8 * key, UINT8 count) 
{  
  UINT8 i;
	for(i=0;i<count;i++)
	{
		 bytes[i] = sboxinv[bytes[i]] ^key[i];
	}
}
//===============================================================================
//��������: ����λȡ����ֱ������ԭʼ�İ취���û�������ʱ���
//�������: stateΪ��Ҫ��λ��4*4����16����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//��state[0]-state[15]��16������������ʽ����
     //  0   4   8    12 
     //  1   5   9    13
     //  2   6   10  14
     //  3   7   11  15
//��һ�б��ֲ��䣬�ڶ���ѭ������8���أ�������ѭ������16���أ�������ѭ������24���ء�
	//	0	4	8	 12 
	//	13    1	5	 9
	//	10	14    2	 6	
	//	7	11	15     3

void InvShiftRows(UINT8 * state) 
{  
	UINT8 temp;  
	// Note: State is arranged column by column. 
	// Cycle second row right one time.  
	temp = state[13]; 
	state[13] = state[9];
	state[9]  = state[5]; 
	state[5]  = state[1]; 
	state[1]  = temp;   
	// Cycle third row right two times.
	temp = state[2]; 
	state[2]  = state[10]; 
	state[10] = temp;  
	temp = state[6]; 
	state[6]  = state[14]; 
	state[14] = temp;    // Cycle fourth row right three times, ie. left once. 
	
	temp = state[3];  
	state[3]  = state[7];	
	state[7]  = state[11]; 
	state[11] = state[15];	
	state[15] = temp;

}
//===============================================================================
//��������: �л��ȡ��������Ϊ��λʹ��G(2)�㷨����������
//�������: stateΪ4*4����16����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//�㷨:�ù̶���*�����������м�
//             b[0][0]  =  a[0]*col[0]+a[1]*col[1]+a[2]*col[2]+a[3]*col[3]
//             b[0][0]  = 0x0e*col[0]+0x0b*col[1]+0x0d*col[2]+0x09*col[3]

void InvMixColumns(UINT8 * state) 
{  
	/*uint8_t a[] = {0x0e, 0x0b, 0x0d, 0x09,
				   0x09, 0x0E, 0x0B, 0x0D,
				   0x0D, 0x09, 0x0E, 0x0B,
				   0x0B, 0x0D, 0x09, 0x0E};*/

	UINT8 j, col[4],mult2[4],mult4[4],mult8[4];
	for (j = 0; j < 4; j++) 
	{
		col[0] = state[j];
		col[1] = state[4+j];		
        col[2] = state[8+j];
		col[3] = state[12+j]; 
		
		mult2[0] = rj_xtime(col[0]);
		mult2[1] = rj_xtime(col[1]);
		mult2[2] = rj_xtime(col[2]);
		mult2[3] = rj_xtime(col[3]);

		mult4[0] = rj_xtime(mult2[0]);
		mult4[1] = rj_xtime(mult2[1]);
		mult4[2] = rj_xtime(mult2[2]);
		mult4[3] = rj_xtime(mult2[3]);

		mult8[0] = rj_xtime(mult4[0]);
		mult8[1] = rj_xtime(mult4[1]);
		mult8[2] = rj_xtime(mult4[2]);
		mult8[3] = rj_xtime(mult4[3]);
//state[0] = 0x0e*col[0]+0x0b*col[1]+0x0d*col[2]+0x09*col[3]
		state[j] = mult8[0] ^ mult4[0] ^ mult2[0]//14 E
				   ^ mult8[1] ^ mult2[1] ^ col[1] //11 B
				   ^ mult8[2] ^ mult4[2] ^ col[2]//13 D
				   ^ mult8[3] ^ col[3];//9

		state[4+j] = mult8[0] ^ col[0]//9
				   ^ mult8[1] ^ mult4[1] ^ mult2[1]//14 E
				   ^ mult8[2] ^ mult2[2] ^ col[2] //11 B
				   ^ mult8[3] ^ mult4[3] ^ col[3];//13 D

		state[8+j] = mult8[0] ^ mult4[0] ^ col[0]//13 D
				   ^ mult8[1] ^ col[1]//9
				   ^ mult8[2] ^ mult4[2] ^ mult2[2] //14 E
				   ^ mult8[3] ^ mult2[3] ^ col[3]; //11 B

		state[12+j] = mult8[0] ^ mult2[0] ^ col[0] //11 B
				 	^ mult8[1] ^ mult4[1] ^ col[1]//13 D
				    ^ mult8[2] ^ col[2]//9
				    ^ mult8[3] ^ mult4[3] ^ mult2[3];//14 E
	}
}
//===============================================================================
//��������: �ײ����
//�������: blockΪ�Կ�Ϊ��λ�����ģ�expandedkey��չ��Կ
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void Inv_Cipher(UINT8 * block, UINT8 * expandedkey) 
{  
	UINT8 round = ROUNDS-1; 
	UINT8 i;
	expandedkey += BLOCKSIZE * ROUNDS;   
	XORBytes( block, expandedkey, 16 ); 
	expandedkey -= BLOCKSIZE;  
 
	for(i=0;i<round;i++)
	{
		InvShiftRows( block );  
		InvSubBytesAndXOR( block, expandedkey, 16 );  
		expandedkey -= BLOCKSIZE;  
		InvMixColumns( block ); 
	}
	InvShiftRows( block ); 
	InvSubBytesAndXOR( block, expandedkey, 16 ); 
}
//ECB
/*
UINT8 Aes_Decrypt(UINT8 * buf, UINT16 length)
{
	UINT16 i,times,reminder;//,padding_size;

	//��ʱ��������
	Aes_Init();
	times    = length>>4;        //��Ϊ����BLOCKSIZE
	reminder = length&0x0F;   //�����Ƿ���Ҫ���

	if(reminder == 0)
	{
		for(i=0; i<times; i++)
		{
			Inv_Cipher(buf, ExpandedKey);
			buf += BLOCKSIZE;
		}
		return TRUE;
	}
	else  
	{
		return FALSE;
	}
}*/
//===============================================================================
//��������: AES���ܴ���
//�������: ciphertextΪ���ģ���Ҫ���ܵ����ݣ�length���ĳ���
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//CBCģʽ:����ʱ���ķ�����ʹ��ÿ��block�����ľ�������ԣ��Ӷ�������������
//                    ����ʱ�����ν��ܺ�����������һ�ֵ����ģ���������������
UINT8 Aes_Decrypt(UINT8 * ciphertext, UINT16 length)
{
	UINT16 i,times,reminder;//,padding_size;
	UINT8 temp1[BLOCKSIZE];
	UINT8 temp2[BLOCKSIZE];
	

	
	Aes_Init();//��ʱ��������
	times    = length>>4;        //��Ϊ����BLOCKSIZE
	reminder = length&0x000F;      //�����Ƿ���Ҫ���

	if(reminder == 0)            //�ж���������� ?
	{
		for(i=0; i<times; i++)
		{
			memcpy(temp1, ciphertext, BLOCKSIZE);
     		Inv_Cipher(ciphertext, ExpandedKey);
			if(i)           //����1��blockʱ������Ϊ���ν��� ^ �ϴ�����
			{
				XORBytes(ciphertext, temp2, BLOCKSIZE );
			}
            if((times > 1) && (i < (times-1) ))
            {
				memcpy(temp2, temp1, BLOCKSIZE);	
				ciphertext += BLOCKSIZE;
			}
		}
		return TRUE;
	}
	else  
	{
		return FALSE;
	}
}

//===============================================================================
//��������: �Ƚ����ĵĽ��ܳ���
//�������: ciphertext_lenΪ���ĳ���;plaintext_valid_lenΪ������Ч���ȣ����������
//�������: ���رȽϽ��:TRUE or FALSE
//�޸�����: 2017-11
//�޸���Ա: 
//===============================================================================
UINT8 Aes_Compare_Decrypt_Len(UINT16 ciphertext_len, UINT16 plaintext_valid_len)
{
	UINT16 actual_len,reminder;
	UINT8  padding_size=0;

	reminder = ciphertext_len&0x0F;   //�Ƿ�������
	if(reminder == 0) 
	{
		if(ciphertext_len == plaintext_valid_len)  //����Ҫ���
		{
			return TRUE;  
		}
		else if(ciphertext_len > plaintext_valid_len)
		{
			padding_size = BLOCKSIZE-plaintext_valid_len&0x0F;
			actual_len = padding_size+plaintext_valid_len;//������պ󳤶�
            if(ciphertext_len == actual_len) 
            {
				return TRUE;  
			}
		}
	}
	return FALSE;  
}


//�л���Լ�����Ļ����㷨
/*
uint8_t gmult(uint8_t a, uint8_t b)  //a*b = a*2 * b/2
{

	uint8_t p = 0, i = 0, hbs = 0;

	for (i = 0; i < 8; i++)
	{
		if (b & 1)
		{
			p ^= a;
		}

		hbs = a & 0x80;
		a <<= 1;
		if (hbs) a ^= 0x1b; // 0000 0001 0001 1011	
		b >>= 1;
	}

	return (uint8_t)p;
}
void coef_mult(uint8_t *a, uint8_t *b, uint8_t *d) 
{

//	d[0] = gmult(a[0],b[0])^gmult(a[3],b[1])^gmult(a[2],b[2])^gmult(a[1],b[3]);
//	d[1] = gmult(a[1],b[0])^gmult(a[0],b[1])^gmult(a[3],b[2])^gmult(a[2],b[3]);
//	d[2] = gmult(a[2],b[0])^gmult(a[1],b[1])^gmult(a[0],b[2])^gmult(a[3],b[3]);
//	d[3] = gmult(a[3],b[0])^gmult(a[2],b[1])^gmult(a[1],b[2])^gmult(a[0],b[3]);

	d[0] = gmult(a[0],b[0])^gmult(a[1],b[1])^gmult(a[2],b[2])^gmult(a[3],b[3]);
	d[1] = gmult(a[4],b[0])^gmult(a[5],b[1])^gmult(a[6],b[2])^gmult(a[7],b[3]);
	d[2] = gmult(a[8],b[0])^gmult(a[9],b[1])^gmult(a[10],b[2])^gmult(a[11],b[3]);
	d[3] = gmult(a[12],b[0])^gmult(a[13],b[1])^gmult(a[14],b[2])^gmult(a[15],b[3]);
}
void mix_columns(uint8_t *state) 
{

	//uint8_t a[] = {0x02, 0x03, 0x01, 0x01};//{0x02, 0x01, 0x01, 0x03}; // a(x) = {02} + {01}x + {01}x2 + {03}x3
	uint8_t a[] = {0x02, 0x03, 0x01, 0x01,
	               0x01, 0x02, 0x03, 0x01,
	               0x01, 0x01, 0x02, 0x03,
	               0x03, 0x01, 0x01, 0x02};

	uint8_t i, j, col[4], res[4];

	for (j = 0; j < 4; j++) 
	{
		for (i = 0; i < 4; i++) 
		{
			col[i] = state[4*i+j];
		}

		coef_mult(a, col, res);

		for (i = 0; i < 4; i++) 
		{
			state[4*i+j] = res[i];
		}
	}
}
void inv_mix_columns(uint8_t *state) 
{

	//uint8_t a[] = {0x0e, 0x0b, 0x0d, 0x09};//{0x0e, 0x09, 0x0d, 0x0b}; // a(x) = {0e} + {09}x + {0d}x2 + {0b}x3
	uint8_t a[] = {0x0e, 0x0b, 0x0d, 0x09,
				   0x09, 0x0E, 0x0B, 0x0D,
				   0x0D, 0x09, 0x0E, 0x0B,
				   0x0B, 0x0D, 0x09, 0x0E};

	uint8_t i, j, col[4], res[4];

	for (j = 0; j < 4; j++) 
	{
		for (i = 0; i < 4; i++) 
		{
			col[i] = state[4*i+j];
	 	}

		coef_mult(a, col, res);

		for (i = 0; i < 4; i++) 
		{
			state[4*i+j] = res[i];
		}
	}
}
//===============================================================================
//��������: �л��ȡ��������Ϊ��λʹ��G(2)�㷨����������
//�������: stateΪ4*4����16����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void InvMixColumn( UINT8 * column ) 
{  
	UINT8 r0, r1, r2, r3;  
	r0 = column[1] ^ column[2] ^ column[3]; 
	r1 = column[0] ^ column[2] ^ column[3]; 
	r2 = column[0] ^ column[1] ^ column[3]; 
	r3 = column[0] ^ column[1] ^ column[2];  

	column[0] = (column[0] << 1) ^ (column[0] & 0x80 ? BPOLY : 0); 
	column[1] = (column[1] << 1) ^ (column[1] & 0x80 ? BPOLY : 0); 
	column[2] = (column[2] << 1) ^ (column[2] & 0x80 ? BPOLY : 0); 
	column[3] = (column[3] << 1) ^ (column[3] & 0x80 ? BPOLY : 0);  

	r0 ^= column[0] ^ column[1]; 
	r1 ^= column[1] ^ column[2];
	r2 ^= column[2] ^ column[3]; 
	r3 ^= column[0] ^ column[3];

	column[0] = (column[0] << 1) ^ (column[0] & 0x80 ? BPOLY : 0); 
	column[1] = (column[1] << 1) ^ (column[1] & 0x80 ? BPOLY : 0);  
	column[2] = (column[2] << 1) ^ (column[2] & 0x80 ? BPOLY : 0);  
	column[3] = (column[3] << 1) ^ (column[3] & 0x80 ? BPOLY : 0);  

	r0 ^= column[0] ^ column[2];  
	r1 ^= column[1] ^ column[3]; 
	r2 ^= column[0] ^ column[2];  
	r3 ^= column[1] ^ column[3];  

	column[0] = (column[0] << 1) ^ (column[0] & 0x80 ? BPOLY : 0);  
	column[1] = (column[1] << 1) ^ (column[1] & 0x80 ? BPOLY : 0);  
	column[2] = (column[2] << 1) ^ (column[2] & 0x80 ? BPOLY : 0); 
	column[3] = (column[3] << 1) ^ (column[3] & 0x80 ? BPOLY : 0);  
	column[0] ^= column[1] ^ column[2] ^ column[3]; 

	r0 ^= column[0]; 
	r1 ^= column[0]; 
	r2 ^= column[0]; 
	r3 ^= column[0];

	column[0] = r0; 
	column[1] = r1;  
	column[2] = r2;
	column[3] = r3; 
}

*/

//===============================================================================
//��������: �л�ϣ�����Ϊ��λʹ��G(2)�㷨����������
//�������: stateΪ4*4����16����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//��֪�任����ľ���row��Ȼ����GF(2��n�η�)���б任	
//�㷨:�ù̶���*�����������м�
//			   b[0][0]	=  a[0]*col[0]+a[1]*col[1]+a[2]*col[2]+a[3]*col[3]
//			   b[0][0]	= 0x02*col[0]+0x03*col[1]+0x01*col[2]+0x01*col[3]
//			   b[0][0]	= 0x02*col[0]+(2+1)*col[1]+0x01*col[2]+0x01*col[3]

void MixColumns(UINT8 * state) 
{ 
/*	UINT8 row[] = {0x02, 0x03, 0x01, 0x01,
	                0x01, 0x02, 0x03, 0x01,
	                0x01, 0x01, 0x02, 0x03,
	                0x03, 0x01, 0x01, 0x02};*/
	UINT8 j, col[4], temp[4];

	for (j = 0; j < 4; j++) 
	{  
        col[0] = state[j];
		col[1] = state[4+j];		
        col[2] = state[8+j];
		col[3] = state[12+j]; 
		
		temp[0] = rj_xtime(col[0]);
		temp[1] = rj_xtime(col[1]);
		temp[2] = rj_xtime(col[2]);
		temp[3] = rj_xtime(col[3]);
		
		state[j] = temp[0]      //rj_xtime(col[0])
			     ^ col[1] ^ temp[1]//rj_xtime(col[1])
			     ^ col[2]
			     ^ col[3];
		state[4+j] = col[0] 
			     ^ temp[1]//rj_xtime(col[1])
			     ^ col[2] ^ temp[2]//rj_xtime(col[2])
			     ^ col[3] ;
		state[8+j] = col[0] 
				 ^ col[1]
				 ^ temp[2]//rj_xtime(col[2])
				 ^ col[3] ^ temp[3];//rj_xtime(col[3]);
		state[12+j] = col[0] ^ temp[0]//rj_xtime(col[0]) 
				 ^ col[1]
				 ^ col[2]
				 ^ temp[3];//rj_xtime(col[3]); 
	}	
}


//===============================================================================
//��������: ����λ��ֱ������ԭʼ�İ취���û�������ʱ���
//�������: stateΪ��Ҫ��λ��4*4����16����
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//��state[0]-state[15]��16��������������и�ʽ����
     //  0   4   8    12 
     //  1   5   9    13
     //  2   6   10  14
     //  3   7   11  15
//��һ�б��ֲ��䣬�ڶ���ѭ������8���أ�������ѭ������16���أ�������ѭ������24���ء�
	//	0	4	8	12 
	//	5	9	13    1	
	//	10	14    2	6	
	//	15    3	7	11	

void ShiftRows(UINT8 * state) 
{  
	UINT8 temp;  
	// Note: State is arranged column by column.  
	// Cycle second row left one time. 
	temp = state[1];//[ 1 + 0*4 ];  
	state[1]  = state[5];  
	state[5]  = state[9];
	state[9]  = state[13];
	state[13] = temp;  
	// Cycle third row left two times. 
	temp = state[2]; 
	state[2]  = state[10]; 
	state[10] = temp; 
	temp = state[6];  
	state[6]  = state[14]; 
	state[14] = temp;

	// Cycle fourth row left three times, ie. right once.  
	temp = state[15]; 
	state[15] = state[11]; 
	state[11] = state[7];  
	state[7]  = state[3];  
	state[3]  = temp; 
 
}

//===============================================================================
//��������: �ײ����
//�������: blockΪ�Կ�Ϊ��λ�����ģ�expandedkey��չ��Կ
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
void Cipher(UINT8 * block, UINT8 * expandedkey) 
{ 
	UINT8 round = ROUNDS-1;  
	UINT8 i;
	
	XORBytes( block, expandedkey, 16 ); 
	expandedkey += BLOCKSIZE;   

	for(i=0;i<round;i++)
	{
		SubBytes( block, 16 );  
		ShiftRows( block );  
		MixColumns( block );  //mix_columns(block);
		XORBytes( block, expandedkey, 16 );  
		expandedkey += BLOCKSIZE; 
	}
	SubBytes( block, 16 ); 
	ShiftRows( block ); 
	XORBytes( block, expandedkey, 16 );
}

//ECBģʽ
/*
void Aes_Encrypt(UINT8 * buf, UINT16 * length)
{
	UINT16 i,times,reminder,padding_size;

    //��ʱ��������
    Aes_Init();
	times = (*length)>>4;        //��Ϊ����BLOCKSIZE
	reminder = (*length)&0x0F;   //�����Ƿ���Ҫ���

	for(i=0; i<times; i++)
	{
		Cipher(buf, ExpandedKey);
        buf += BLOCKSIZE;
	}
	if(reminder)             //������䣬��Ĭ�����ֵΪ"0"��
	{
		padding_size = BLOCKSIZE-reminder;
        memset(buf+reminder, 0 ,padding_size);
		Cipher(buf, ExpandedKey);
		(*length) += padding_size;
	}
}*/
	
//===============================================================================
//��������: AES���ܴ���
//�������: plaintextΪ���ģ���Ҫ���ܵ����ݣ�length���ĳ���
//�������: ��
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================
//CBCģʽ:����ʱ���ķ�����ʹ��ÿ��block�����ľ�������ԣ��Ӷ�������������
//������block���ܺ�����ĺ��¸�block������������Ϊ�¸�block������
void Aes_Encrypt(UINT8 * plaintext, UINT16 * length)
{
	UINT16 i,times,reminder,padding_size;

    Aes_Init();//��ʱ��������
	times = (*length)>>4;        //��Ϊ����BLOCKSIZE
	reminder = (*length)&0x0F;   //�����Ƿ���Ҫ���


	if(reminder)             //����䣬Ĭ�����ֵΪ"0"��
	{
		padding_size = BLOCKSIZE-reminder;
		memset(plaintext+(*length), 0 ,padding_size);//ԭ�Ĵճ�block
		(*length) += padding_size;  //������

		times++;
	}
	for(i=0; i<times; i++)  //�������
	{
		Cipher(plaintext, ExpandedKey);
		if((times > 1) && (i < (times-1)))//����1��blockʱ����ʹ�ñ��ε����ĵ�����
		{
			XORBytes(plaintext+BLOCKSIZE, plaintext, BLOCKSIZE );
			plaintext += BLOCKSIZE; 
		}			
	}	
}
//===============================================================================
//��������: ����֡���ܴ���
//�������: dataΪ���ģ���Ҫ���ܵ�����
//�������: ���ܺ󽫼����õ�HEAD,LEN0,LEN1����
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================


UINT8 RecFrame_Decrypt(UINT8 *data,UINT16 start_loc)
{
	/*UINT16 len;
	
	len = (data[start_loc+2]<<8);
	len |= data[start_loc+1];
	if(len	<= CIPHERTEXT_LEN_MAX)
	{
		if(!Aes_Decrypt(data+start_loc+3, len)) 
		{
			return ERROR;
		}
		memmove(data,data+start_loc+3,len);
		return SUCCESS;
	}
	return 0x55;*/
	return SUCCESS;
}


//===============================================================================
//��������: ����֡���ܴ���
//�������: dataΪ���ģ���Ҫ���ܵ����ݣ�length���ĳ���
//�������: 
//�޸�����: 2017-10
//�޸���Ա: 
//===============================================================================


void SendFrame_Encrypt(UINT8 *data,UINT16 *length)
{

	/*memmove(data+3,data,(*length));
	Aes_Encrypt(data+3, length);
	data[0]=0x7F;
	data[1] = (UINT8)((*length)&0x00FF);
	data[2] = (UINT8)((*length)>>8);
	(*length) += 3;
	*/
}


	

