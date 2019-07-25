

#ifndef _PTW3300_H_
#define _PTW3300_H_

#include "controller.h"

#define FRAME_LEN_PTW3300				332


//���վ�ΪUNICODE���ʽ ���ܲ��Բ�ȫ�棬��������

#define FRAME_HEAD_FIRE_PTW3300			0x70	//�� 70 6B 70 7E 62 A5 8B 66 ���ֱ���
#define FRAME_HEAD_FAULT_PTW3300		0x6D	//���� 6D 88 96 32 65 45 96 9C �������� 6D 88 96 32 8B BE 59 07 62 16 53 3A 57 DF 4E 0D 80 FD 5D E5 4F 5C 5D F2 6E 05 96 64 �����豸�������ܹ��������(�������)
#define FRAME_HEAD_MONITER_PTW3300 	0x76	//��� 76 D1 63 A7 7A D9 76 D1 63 A7 4F E1 53 F7 ���վ����ź�
#define FRAME_HEAD_SHIELD_PTW3300		0x97	//���� 97 5E 6D 88 96 32 8B BE 59 07 96 94 79 BB �������豸����
#define FRAME_HEAD_RESET_PTW3300    0x7C  //��λ 7C FB 7E DF 59 0D 4F 4D ϵͳ��λ
#define FRAME_HEAD_VERIFY_PTW3300   0x78  //ȷ�� 78 6E 8B A4 98 84 8B 66 ȷ��Ԥ��
#define FRAME_HEAD_RESUME_PTW3300		0x98	//�ָ� 98 84 62 A5 8B 66 5D F2 89 E3 96 64 Ԥ�����ѽ��
#define FRAME_HEAD_RELEASE_PTW3300		0x5B	//���5B F9 97 5E 6D 88 96 32 8B BE 59 07 76 84 96 94 79 BB 5D F2 6E 05 96 64    �Է������豸�ĸ��������

  
#define FRAME_TAIL_PTW3300                0x0A  //֡β

#define FRAME_TAIL_LEN_PTW3300           0x01  //֡β����


void Com_Task_PTW3300_Jt(CONTR_IF *buf);

#endif
