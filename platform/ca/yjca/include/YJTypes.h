
/******************************************************************************
 * Copyright (c) 2008, �ɶ�Ӣ�����ӿƼ����޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ� YJTypes.h
 * 
 * ��    Ҫ:  ��������ϵͳ��̽ӿڡ�
 *            
 * 
 * ��ǰ�汾�� 	1.0.0
 *
 * ��    �ߣ� 		Matthew
 * �������ڣ� 	2008��7��30��
 *
 ******************************************************************************/
#ifndef  _YJTYPES_H_
#define   _YJTYPES_H_ 
#ifdef  __cplusplus
extern "C" {
#endif


#define true           								1                                          
#define false          								0   


#ifndef		bool
#define		bool			unsigned  char 
#endif


#ifndef		NULL
#define		NULL								0
#endif


#define 		CVer
//#define 		DVBC
//#define		DVBS
#define		DMBT
#define		PUBLIVITY_AD								/*�ҽǹ��*/
#define		SWITCH_PRO_AD								/*��̨���*/
#define		DATARADIATE
#define 		SUB_MAIN_CARD_AUTHENTICATION 				/*��ĸ����֤*/
//#define 		AREAVALIDATE			 					/*������֤*/
#define 		ONECARDBYONESTB							/*������*/
#define 		MAIL_MAX_CAPTIONLEN 				21		/*�����ʼ�ͷ����ֽ���20*/
#define 		MAIL_MAX_CONTENTLEN 				1024+1	/*�����ʼ���������ֽ���1024*/
#define 		MAX_ROLLDATA_LEN					1024		/*������Ļ��������ֽ���1024*/
#define 		STB_SERIAL_NUM_LEN				9			/*STB���кų���9B*/
#define 		CARD_ID_LEN						10			/*Smart Card ID 10B*/
#define		USER_ID_LEN						8			/*�û���ID 8B*/
#define		MAX_VIDEOPID_NUM					255			/*������Ļ��Ŀ���Ƶ������Ŀ*/


/*������Ϣ����ʾ*/
#define		MESSAGE_CANCEL_TYPE				0x00		/*ȡ����ǰ����ʾ*/
#define		MESSAGE_BADCARD_TYPE			0x01		/*�޷�ʶ�𿨣�����ʹ��*/
#define		MESSAGE_EXPICARD_TYPE			0x02		/*���ܿ��Ѿ����ڣ�������¿�*/
#define		MESSAGE_INSERTCARD_TYPE			0x03		/*��������ܿ�*/
#define		MESSAGE_STOP_SERVICE				0x04		/*�û���ͣ��*/
#define		MESSAGE_CONDITIONSTOP_TYPE		0x05		/*��������*/
#define		MESSAGE_PAIRING_TYPE				0x06		/*������ƥ��*/
#define		MESSAGE_NOENTITLE_TYPE			0x07		/*����Ч��Ȩ*/
#define		MESSAGE_DECRYPTFAIL_TYPE			0x08		/*��Ŀ����ʧ��*/
#define     	        MESSAGE_ERRREGION_TYPE          		0x09		/*���������ʹ�û�����*/
#define		MESSAGE_INSERTMAIN_CARD			0x0A		/*�����ĸ����֤*/
#define		MSSAGE_CARDINIT_SUCCE			0x0B		/*����ʼ���ɹ�*/
#define		MSSAGE_CARDINIT_FAIL				0x0C		/*����ʼ��ʧ��*/
#define		MSSAGE_CARD_AUTHENTICAT_FAIL	0x0D		/*�ֿ���֤ʧ��*/
#define		MSSAGE_CARD_AUTHENTICAT_SUCCE 	0x0E		/*�ӿ���֤�ɹ�*/
#define		MSSAGE_CARD_SUB_INSERT			0x0F		/*�������֤�ӿ�*/
#define		MSSAGE_CARD_SUB_CANCEL			0x10		/*�ӿ�ȡ���ɹ�*/
#define		MSSAGE_CARD_SUB_SETUP			0x11		/*�ӿ����óɹ�*/
#define		MSSAGE_CARD_MAIN_CONFIR_FAIL	0x12		/*ĸ��ȷ��ʧ��*/
#define		MSSAGE_CARD_MAIN_CONFIR_SUCCE	0x13		/*ĸ��ȷ�ϳɹ�*/
#define		MSSAGE_NOT_YJCA					0x14		/*��Ӣ��CA�����ܽ��ܽ�Ŀ*/
#define		MSSAGE_CARD_ERROR				0x15		/*����������������Ͳ����*/
#define		MSSAGE_STRING						0xFF

typedef unsigned long long 	UINT64;
//typedef unsigned int   		UINT32;
//typedef unsigned short 	UINT16;
//typedef unsigned char 		UINT8;


typedef long long 			INT64;
//typedef int   				INT32;
//typedef short 			INT16;
//typedef signed char		INT8;


typedef signed long long	__s64;
typedef signed int			__s32;
typedef signed short		__s16;


typedef int  				YJCA_Semaphore ;

#endif
