/*************************************************************************************************

File Name      :  trca_internal.h

Description    :  

Copyright(C)   :  Haier_IC 2012.05.10

Project Group  :  CA

Author(s)      :  lim

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2014-05-10     GONGQ          created              ---

**************************************************************************************************/
#ifndef _TRCA_INTERNAL_H_
#define _TRCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

//---------------ȫ�ֱ���---------------
//-----------------------------------------------------
//=====================================================
#define CA_MAX_PIN_LENGTH_TRCA      	6U
#define MAX_TASK_NUMBER_TRCA        	       5U
#define MAX_SEMA_NUMBER_TRCA         	25U   //����ź�������
#define ENTITLE_COUNT_TRCA                      300
#define EMAIL_COUNT_TRCA                          50	 //�ʼ����������洢���ٷ⡣
#define MSG_MAX_NUM_TRCA	                     (EMAIL_COUNT_TRCA + 1)	//�ʼ������棬���������ѡ�
#define INDEX_MAX_NUM_TRCA                    511
#define SC_MAXLEN_TRCA					 30
#define MAXLEN_EMAIL_TITLE_TRCA             80
#define MAXLEN_EMAIL_CONTENT_TRCA       880
#define TRCA_MAXNUM_OPERATOR			100
#define TRCA_MAXNUM_IPPPRODUCT		20
#define TRCA_MAXNUM_IPPRECORD		100
#define PINCODE_LENGTH_TRCA  			6
#define IPP_COUNT_TRCA 					250
#define TRCA_EXPIRED_DAYS 				14  //��Ȩ����ʱ��
#define OPERATOR_COUNT_TRCA			320  

typedef struct
{
	uint8_t bYear[2];    	/* for example 1998, bYear[0]=19, bYear[1]=98 */
	uint8_t bMonth;      	/* 1 to 12 */
	uint8_t bDay;        	/* 1 to 31 */
	uint8_t bHour;      		 /* 0 to 23 */
	uint8_t bMinute;     	/* 0 to 59 */
	uint8_t bSecond;     	/* 0 to 59 */
} TIMESTAMP;


//�����
typedef struct
{
	char CAVersion[SC_MAXLEN_TRCA];
	char SCVersion[SC_MAXLEN_TRCA];
	char SCNumber[SC_MAXLEN_TRCA];
	uint8_t SCRatingLevel[4];
	uint8_t State;	
}hrtrca_scBasicInfo_t;

typedef struct
{
	uint8_t reserve;
}hrtrca_scAddedInfo_t;


//�ʼ����
typedef struct{
    	uint8_t importance; 		//��Ҫ�ԣ� 0��LOW��1��MID 2-HIG  3- URGENCE 
    	uint8_t newEmail;  		//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
   	char createtime[32];  		//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
	char title[MAXLEN_EMAIL_TITLE_TRCA]; //�ʼ�������
	char from_context[MAXLEN_EMAIL_CONTENT_TRCA];		 //��Դ
}hrtrca_emailInfo_t;

typedef struct{
	char version[32];  		//����ʱ��
	char emailLength[6]; 		//�ʼ����ݳ���
	char email[MAXLEN_EMAIL_CONTENT_TRCA]; //�ʼ�����
	uint8_t reserved[6];  		//����
	char title[MAXLEN_EMAIL_TITLE_TRCA]; //�ʼ�������
}hrtrca_emailContent_t;

typedef struct
{
   	 uint16_t wTitleLen;
   	 uint8_t  bMsgTitle[80];
  	 uint16_t wDataLen;
   	 uint8_t  bMsgData[880];
    	 uint16_t wIndex;
    	 uint8_t  bType;
    	 uint8_t  bClass;
    	 uint8_t  bPriority;
        uint16_t wPeriod;
        TIMESTAMP sMsgTime;
        TIMESTAMP sCreateTime;
} hrtrca_email_t;


//PIN�����

//��������


//��Ӫ����Ϣ
typedef struct{	 

	uint8_t reserve;
}hrtrca_operatorInfo_t; 

//��Ȩ��Ϣ
typedef struct	
{
	uint32_t prog_id;
	uint32_t prog_remain_days;
    	char prog_right_start_date[11];
    	char prog_right_end_date[11];
   	uint8_t stauts;
}hrtrca_serviceEntitles_t;  

typedef struct
{
	uint8_t reserve;
}hrtrca_detitleInfo_t;

//ipp���򵯳���
typedef struct {
	char ChannelId[6];			//Ƶ����
	char IppRunningNum[11];		//��ˮ��
    	uint8_t  bIppType;   			// 0:ippv; 1:ippt 
   	char  IppCharge[12]; 			// ippv: ��λΪx.xxԪ/�Σ�ippt:��λΪx.xxԪ/ XX ��,���� XX��ֵΪIppUnitTime 
    	uint32_t IppUnitTime;			//��λ '�롮
    	char  PurseBalance[20];		//Ǯ����Ϣ
    	char  IppStart[64];			//��ʼ����
   	char  IppEnd[64];				//ʧЧ����
}hrtrca_ippBuyInfo_t;

//ipp��Ȩ��Ϣ
typedef struct { 
    	uint8_t  bProductType;   		// 0:ippv; 1:ippt
    	uint32_t ulRunningNum;
    	char  ulStartTime[64];
    	char  ulEndTime[64];
}hrtrca_viewedIpp_t;

//ipp���Ѽ�¼
typedef struct {
   	uint8_t  bStateFlag;             	 //״̬��  0:֧��  1������
    	char  ulExchTime[64];        	 //ʱ��:   xxxx.xx.xx-xx:xx:xx
    	char ulExchRunningNum[11];	 //��ˮ��: 10λ �磺0000000004
    	uint32_t ulExchValue;			 //���
    	uint8_t  bContentLen;			 //reserve
    	char  pbContent[34];			 //reserve
}hrtrca_ippRecord_t;

//Ǯ��
typedef struct {
	uint8_t slotId;
    	uint32_t slotCreditLimit;    		 //���ö�(����) 
    	uint32_t balance;    		 	 //�ѻ��ĵ���
}hrtrca_slotInfo_t;

//ǿ�ƻ�̨
typedef struct {
	uint8_t  bLockFlag;
	uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
}hrtrca_SwitchChannel_t;

//ȫ����̨
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1024]; 
}hrtrca_Anno_t;

//===================================================================================================================
/*----------------------------------------�ʼ���Ϣ-------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;
/*-----------------------------���ܿ���Ϣ���ۿ����𡢹���ʱ��--------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;

/*-----------------------------------------��Ȩ��Ϣ------------------------------------*/
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;
//Ǯ������
extern uint8_t d_SlotCount;
//Ǯ��ID
extern uint8_t d_SlotID[20];
//IPPV��Ŀ����
extern uint16_t d_IPPVProNum;

#endif

