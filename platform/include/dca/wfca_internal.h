#ifndef WFCA_INTERNAL_H
#define WFCA_INTERNAL_H

//#include "typedef.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define DEMUX_INVALID_PID   	 0x1FFF

/*
�������߼���ȫ����Ӹ߼���ȫ�������⣬��funȡ������
*/
//------------------------------------
#define CA_MAX_PIN_LENGTH   	 6u //Ϊ�˱���ͨ����ʵ�ʵ���ֵ�д�ȷ��
#define IPP_COUNT 				 350u
#define OPERATOR_COUNT 			 320u 
#define EMAIL_COUNT_WFCA   		 50u
#define MAXLEN_EMAIL_CONTENT 	 1124u
#define MAXLEN_EMAIL_SENDERNAME  16u
#define ENTITLE_COUNT_WFCA  	 300u
#define MAXLEN_EMAIL_TITLE	 	 17u
#define MAX_TABLE_LEN 		     1024u
//------------------------RESERVE-------------------
typedef struct
{
	uint8_t reserve;

}hrwfca_detitleInfo_t;

//��Ӫ����Ϣ
typedef struct{	

	uint8_t reserve;

}hrwfca_operatorInfo_t; 

//
typedef struct
{
	uint8_t reserve;

}hrwfca_scAddedInfo_t;

//IPP��Ȩ��Ϣ
typedef struct
{
	uint8_t reserve;

}hrwfca_viewedIpp_t;	
//-----------------------END RESERVE----------------

//�����
typedef struct
{
	char 		CASTime[64];//CAS ʱ��	

	uint8_t		ChildCard;/* �Ƿ����ӿ�,TRUE�����ӿ�, FALSE����ĸ�� */
	uint8_t		Card_No[8];/* ���� */
	char		Issuance_Date[64];/*����ʱ��*/
	char		Expire_Date[64];/*����ʱ��*/
	uint8_t		Provider[32];/* String,���ķ����� */

	 /* ���µ���ֻ���ӿ�����Ч */
	uint8_t		MotherCardNo[8];/* ĸ���Ŀ���*/
	char 		UpdateOrigination[64];/* ĸ�����ӿ���Ȩʱ��ʱ����� */
	char 		UpdateExpiration[64]; /* ĸ�����ӿ���Ȩʱ��ʱ���յ� */

	//VERSION
	uint16_t	Cas_Id;	/*CAS��ʶ*/
	uint16_t	Sub_Id;	/*CAS��ʶ*/
	char		Version[8];/*CAS�汾*/
	uint8_t		Description[32];/* String,CAS������ */
	uint8_t		InorRemove;/*����ǰ״̬*/
    char		chipid[10];/*chip ID*/
    char        StbNo[10];/*���������к�*/
    uint8_t     IsPaired;

}hrwfca_scBasicInfo_t;

//����Ǯ��
//typedef WFCAS_Purse_t hrca_slotInfo_t;
typedef struct
{
	uint32_t	Money;/* �û���ǰ�ܽ�����С���ҵ�λΪ��λ*/
	uint32_t	Balance;/*�û��������ܶ�: ����С���ҵ�λΪ��λ*/
}hrwfca_slotInfo_t;


//IPP���������
typedef struct
{
	uint8_t IsPPV;
	uint16_t Interval;
	uint16_t UnitPrice;

}hrwfca_ippBuyInfo_t;

//��Ȩ��Ϣ
typedef struct
{
	char	Product_Id[64];/* Product identifier */
	char	Ori_Date[64];/* original date,MJD */
	char	Ori_Time[64];/* original time,UTC */
	char	Exp_Date[64];/* expire date,MJD */
	char	Exp_Time[64];/* expire time,UTC */
}hrwfca_serviceEntitles_t;

//����
typedef struct
{
	uint16_t	Year;
	uint8_t		Month;
	uint8_t		Day;
}WFCO_Date_t;


//�ʼ�ͷ
typedef struct{
	uint32_t        actionId;                 //�ʼ�Ψһid��
    uint8_t          newEmail;  			//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
   	char	      createtime[32];  	    //����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
    char     	 	 senderName[MAXLEN_EMAIL_SENDERNAME];   /* ��Ϣ���������� */
	uint8_t          title[MAXLEN_EMAIL_TITLE]; //����
}hrwfca_emailInfo_t;

//�ʼ�����
typedef struct{
	char        email[MAXLEN_EMAIL_CONTENT];           /* ��Ϣ����    */
}hrwfca_emailContent_t;

//һ���ʼ�
typedef struct _TEmail
{
	hrwfca_emailInfo_t 		 emailHead;
	hrwfca_emailContent_t 	 emailContent;
}TEmail;

//����
typedef struct _TEmailBox
{
    char        count;    /* Email count */
    char        UnDismantleCount; /* δ���ʼ���  */
    TEmail     caBmail[EMAIL_COUNT_WFCA];
}TEmailBox;

//�ҳ���
typedef struct 
{
	D_U8   Rating;
	D_U16  TimeOutInterval;
    D_U8   pin[5];
} D_WFCAparentlevel;

//---------------HRCA_DISPLAY.H-------------------

/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

//����Ľ�Ŀ��Ϣ
//extern hrwfca_serviceEntitles_t d_ServiceEntitles_wfca[ENTITLE_COUNT_WFCA];

/*------------------------------IPP��Ϣ-----------------------------------------------*/
//IPPV��Ŀ����
extern uint16_t d_IPPVProNum;

//ippv ecm pid
extern uint16_t IppvECMPID;

//ippv����
extern uint8_t IppvType;

//�鿴ipp ����
extern uint16_t viewIppCount;  

//ipp��������
extern uint16_t bookIppCount;

extern hrwfca_ippBuyInfo_t d_IppBuyInfo_wfca;


/*--------------------------------Ǯ����Ϣ-----------------------------------------*/

//Ǯ������
extern uint8_t d_SlotCount;

//Ǯ��ID
extern uint8_t d_SlotID[20];

//��ֵ���
extern uint32_t ChargeValue;

//Ǯ����Ϣ
//extern hrwfca_slotInfo_t  d_SlotInfo_wfca[20];

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/

//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

//�ʼ�ͷ
//extern hrwfca_emailInfo_t d_EmailInfo_wfca[EMAIL_COUNT_WFCA];

//�ʼ�����
//extern hrwfca_emailContent_t d_EmailContent_wfca;


/*------------------------------���ܿ���Ϣ-------------------------------------*/
//extern hrwfca_scBasicInfo_t d_ScBasicInfo_wfca;

//---------------END HRCA_DISPLAY.H-------------------

#endif
