#ifndef _ABVCA_INTERNAL_H
#define _ABVCA_INTERNAL_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//#include "abv_ca_types.h"
//---------------ȫ�ֱ���---------------

#define  abvmax_slot	         8//10 
#define  abvdmux_buffer_size          1024      //haoxw

//----------------�ʼ�------------------
#define EMAIL_COUNT_ABVCA  5
#define MAXLEN_EMAIL_FROM_CONTENT 30
#define MAXLEN_EMAIL_TITLE_ABVCA    60
#define ABVCA_MAXLEN_EMAIL_CONTENT 2048
//-----------------����-----------------


//----------------��Ӫ��------------------
#define OPERATOR_COUNT_ABVCA  3
#define MAXLEN_TVSNAME 24
#define ENTITLE_COUNT 				300U
//-----------------����-----------------

//----------------��Ȩ-----------------
#define ENTITLE_COUNT_ABVCA  100
#define FREE_ENTITLE_COUNT_ABVCA  3
#define PPC_ENTITLE_COUNT_ABVCA  1000
#define PPV_ENTITLE_COUNT_ABVCA  100
//-----------------����-----------------

//----------------������ʷ------------------
#define CONSUME_MAX_COUNT    30

//----------------STBID length------------------
#define ABV_STBID_LEN_MAX    30//20  //ABV CA�����20���Ժ�CA���б䶯�����޸Ĵ˺궨��
//----------------����-------------------

//---------------CA����������-----------------
#define MAX_TASK_NUMBER_ABVCA         	2U
//----------------����-------------------

typedef struct{
	char MailNo[5];
  uint8_t newEmail;  							//���ʼ���ǣ�0�����ʼ�;1���Ѷ��ʼ�
  char SendTime[15];  						//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
	char Title[MAXLEN_EMAIL_TITLE_ABVCA]; //�ʼ�������
	char SenderName[MAXLEN_EMAIL_FROM_CONTENT];	//��Դ
}hrabvca_emailInfo_t;


typedef struct{
	uint16_t emailLength; 					//�ʼ����ݳ���
	char email[ABVCA_MAXLEN_EMAIL_CONTENT];           //�ʼ�����
}hrabvca_emailContent_t;


typedef struct{
	char Num[17];/*Card Number*/
	char Name[8];/*Smart card Name*/
	uint8_t Version;/*Smart card version*/
	uint8_t Matl;/*Adult level*/
	char Area[9];/*Aire*/
	uint8_t paired;/*!0:paired 0:No Paired*/
	uint8_t start_time[2];/*BCD Code*/
	uint8_t end_time[2];/*BCD code*/
}hrabvca_scBasicInfo_t;


typedef struct{
	char Provider_PPID[8];  //��Ŀ��Ӧ�̱�ʾ
	char Provider_Label[9]; //��Ŀ��Ӧ������
	int32_t balance;          //��Ӧ��Ӧ�̵����ܿ����
}hrabvca_operatorInfo_t;


typedef struct{
       char Label[15];//��������
       char Entitle_start_date[15];//Ƶ����Ȩ��ʼ����
       char Entitle_end_date[15];//Ƶ����Ȩ��ֹ����
}hrabvca_freeEntitles_t;

typedef struct{
	uint16_t LinkID;
	char Label[15];//��������
       char Entitle_send_date[17];
       char Entitle_start_end_date[35];//Ƶ����Ȩ��ֹ����
}hrabvca_ppcEntitles_t;

typedef struct{
	uint16_t LinkID;
       char Label[15];//��������
       char Entitle_send_date[17];
       char Entitle_start_end_date[35];//Ƶ����Ȩ��ֹ����
}hrabvca_ppvEntitles_t;


typedef struct{
	char Consume_Time[11];
	int32_t Consume_Tokens;
}hrabvca_consumeInfo_t;

typedef struct{
	uint8_t IPPV_Type;
	char  IPPV_Time_Price[7];
	char  IPPV_View_Price[7];
	char  IPPV_Name[24];
	char  Pro_Start_Time[17];
	char  Pro_End_Time[17];
	uint8_t  IPPV_ID;	//��Ŀ���
}hrabvca_ippBuyInfo_t;


/*-----------------------------��Ŀ��Ϣ-------------------------------------------*/

//����Ľ�Ŀ����
extern uint16_t abv_ServiceCount;
//����Ľ�Ŀ��
extern hrabvca_freeEntitles_t d_FreeEntitles_abvca[FREE_ENTITLE_COUNT_ABVCA];
extern hrabvca_ppcEntitles_t d_PPCEntitles_abvca[PPC_ENTITLE_COUNT_ABVCA];
extern hrabvca_ppvEntitles_t d_PPVEntitles_abvca[PPV_ENTITLE_COUNT_ABVCA];
//��������ipp��Ŀ
extern hrabvca_ippBuyInfo_t d_IppBuyInfo_abvca[2];
//��Ӫ����Ϣ
extern uint8_t d_OperatorCount;
extern hrabvca_operatorInfo_t d_OperatorInfo_abvca[OPERATOR_COUNT_ABVCA];

/*-------------------------------�ʼ���Ϣ-----------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;
//�ʼ�ͷ
extern hrabvca_emailInfo_t d_EmailInfo_abvca[EMAIL_COUNT_ABVCA];
//�ʼ�����
extern hrabvca_emailContent_t d_EmailContent_abvca;
/*------------------------------���ܿ���Ϣ-------------------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//���ܿ�������Ϣ
extern hrabvca_scBasicInfo_t d_ScBasicInfo_abvca;

extern uint16_t  d_ConsumeCount;
extern hrabvca_consumeInfo_t d_ConsumeHistory_abvca[CONSUME_MAX_COUNT];


#endif

