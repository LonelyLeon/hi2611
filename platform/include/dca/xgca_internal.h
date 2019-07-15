/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-11-02      lim            created              ---
1.1		   2013-03-06	   lim			  modify               ---

*************************************************************************************************/

#ifndef INTERNAL_H_
#define INTERNAL_H_

#include <stdint.h>

/*��λӦ��*/
#define SPECIFIC_ID							0x8648	   			//�¹⹫˾������ID
//#define INTERFACE_VER					0x0324	   			//������STB�ӿڰ汾��3.24
#define NOT_REGISTER						0xff	   			//����δ����ע��
#define NOT_BOUNDED						0x00	   			//����δ��
#define CARD_BOUNDED					0x80	   			//���Ѿ���

//#define CA_MAX_PIN_LENGTH       		6U 					//Ϊ�˱���ͨ����ʵ�ʵ���ֵ�д�ȷ
#define EMAIL_COUNT_XGCA 				50U
#define XGMAXLEN_EMAIL_CONTENT 		1024U
#define XGMAXLEN_EMAIL_SENDERNAME 	256U
#define XGMAXLEN_EMAIL_TITLE	 		256U				
#define MAXLEN_SHORT_MSG				512U				//����Ϣ������


//reserve
#define OPERATOR_COUNT_XGCA			1U
#define ENTITLE_COUNT_XGCA				256U

//ϵͳid
typedef struct{
 	
	uint16_t SysId;
	uint16_t SubSysId;
}systemId;


//���ܿ���Ϣ
typedef struct
{
	uint8_t 	cosVersion[6];
	uint8_t 	cardId[18];
	uint8_t 	cardTag;  				//1Ϊĸ��������Ϊ�ӿ�
	uint8_t     Date[16];	  			//UTC_time
	uint8_t	    Time[16];	 			//UTC_time
	uint8_t 	boundStatus;			//�Ƿ�󶨣�1����   0��δ��
    uint8_t 	netid[10];
	uint8_t 	casid[10];
	uint8_t 	areano[10];
	uint8_t 	groupno[10];
	uint8_t 	nitfreq[10];
	uint8_t 	status;
	uint8_t 	viewlv;
	uint8_t 	userid[10];		//Use_ID     4byte//�û��ı�ţ������ӿ���ĸ���Ĵ˺���ͬ
	uint8_t 	cardtype;		//����ʹ����ţ�=1Ϊĸ��������1Ϊ�ӿ�
	uint8_t 	pincode[8];		//PIN     2byte Ϊ0ʱ������
}hrxgca_scBasicInfo_t;

typedef struct
{
	uint8_t 	header[2];		 //0
	uint8_t 	cardId[8];		 //2
	uint8_t 	cosversion[4];   //10				
	uint8_t     supercasid[4];	 //14
	uint8_t	    netid[4];	 	//18
	uint8_t 	areacode[4];		//22
    uint8_t 	groupno[4];		//26
	uint8_t 	nitfreq[4];		//30
	uint8_t 	pincode[2];		//34
	uint8_t 	status;			//36
	uint8_t 	userid[4];		//37Use_ID     4byte//�û��ı�ţ������ӿ���ĸ���Ĵ˺���ͬ
	uint8_t 	cardtype;		//41 ����ʹ����ţ�=1Ϊĸ��������1Ϊ�ӿ�
	uint16_t 	mcardata;		//42
	uint16_t 	mcaddhour;		//44
	uint8_t 	freserve[2];		//46
	uint8_t 	encdck[16];		//48
	uint8_t 	idctrlstatus[2];  //64
	uint8_t 	subendtime[4];	  //66 ������&ppc33entitle[0x8b]
	uint32_t 	substbtime;	  //70
	uint8_t 	edreserve[6];	  //74
}hrxgcos_Info_t;


//IPP���������
typedef struct
{
	uint16_t price;  					//��
	uint32_t purseBalance; 			//��
	uint8_t  startDate[12];			//MJD
	uint8_t  startTime[12];			//BCD
	uint8_t  endDate[12];  			//MJD
	uint8_t  endTime[12];		      //BCD

}hrxgca_ippBuyInfo_t;

//����
typedef struct
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
}hrxgca_Date_t;

//ʱ��
typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}hrxgca_Time_t;

//ppc��Ȩ����б�
typedef struct{
	uint8_t 	ppcId;
	uint8_t    ppcEndDate[16];
	uint8_t 	ppcStatus;				//Ϊ0��ʾ������Ȩ��Ϊ1��ʾǿ�ƿ�ͨ��Ϊ2��ʾǿ�ƹض�

}hrxgca_serviceEntitles_t;

//��ĸ����Ϣ
//typedef struct
//{
//	uint8_t 	cardTag;  		   //1Ϊĸ��������Ϊ�ӿ�
//	uint8_t      Date[16];	  	   //UTC_time
//	uint8_t	     Time[16];	 	   //UTC_time
//	uint8_t 	boundStatus;	   //�Ƿ�󶨣�1����   0��δ��
//}hrca_scInfo_t;

//�ʼ�ͷ
typedef struct{
	uint16_t	emailId;
	uint8_t	hasRead;					      			 	// 1:�Ѷ� 0��δ��
	uint8_t 	createTime[24];							//UTC_time
	uint8_t 	sourceLong;								//��Դ����
	uint8_t	source[XGMAXLEN_EMAIL_SENDERNAME];	//��Դ
	uint8_t 	captionLong;								//���ⳤ��
	uint8_t  	title[XGMAXLEN_EMAIL_TITLE];				//����

}hrxgca_emailInfo_t;

//�ʼ�����
typedef struct{
	uint16_t 	emailLong;									//���ݳ���
	uint8_t	email[XGMAXLEN_EMAIL_CONTENT];			//����

}hrxgca_emailContent_t;

//�ʼ�
typedef struct
{	
	hrxgca_emailInfo_t 	   emailHead;
	hrxgca_emailContent_t   emailContent;
}hrxgca_email_t;

//���Ʒ�ʽ
typedef enum
{
	QPSK,	   //0
	QAM16,	   
	QAM32,	   
	QAM64,	   //3
	QAM128,	   //4
	QAM256,
}hrxgca_modulation_t;

//��������
typedef struct
{
	uint32_t 	Frequency;			//Ƶ�� Hz
	uint32_t 	SymbolRate;		//������ bps
	uint8_t	Modulation;			//���Ʒ�ʽ

}hrxgca_zoneRestrict_t;

//-------------------------RESERVE----------------------------------


//����Ǯ��
typedef struct
{
	uint8_t reserve;

}hrxgca_slotInfo_t;

//��Ӫ����Ϣ
typedef struct{	

	uint8_t reserve;

}hrxgca_operatorInfo_t; 

typedef struct
{
	uint8_t reserve;

}hrxgca_scAddedInfo_t;

//IPP��Ȩ��Ϣ
typedef struct
{
	uint8_t reserve;

}hrxgca_viewedIpp_t;	

//����Ȩ
typedef struct
{
	uint8_t reserve;

}hrxgca_detitleInfo_t;


typedef struct {
	uint8_t reserve;
}hrxgca_SwitchChannel_t;

//------------------DEFINED IN HRCA_DISPLAY.H--------------------
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;

/*extern hrxgca_serviceEntitles_t d_ServiceEntitles_xgca[ENTITLE_COUNT_XGCA];*/
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

extern hrxgca_ippBuyInfo_t d_IppBuyInfo_xgca;
//�ʼ�����
extern uint16_t d_EmailCount;

//δ���ʼ�����
extern uint16_t d_NewEmailCount;

//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

/*extern hrxgca_emailInfo_t d_EmailInfo_xgca[EMAIL_COUNT_XGCA];*/

/*extern hrxgca_emailContent_t d_EmailContent_xgca;*/

extern hrxgca_scBasicInfo_t d_ScBasicInfo_xgca;

/*-------------------------------Ӧ���㲥---------------------------------*/

//��ȡ��ǰ��Ŀ��Ƶ����
extern uint16_t g_ChNO; 

//�Ƿ��ֹ��̨����,TRUE:��������̨;FALSE:������̨
extern uint8_t forbidSwitchChannel;

//��¼Ӧ���㲥�ĳ���ʱ�䳤��
extern uint16_t broadcastDuration;    

//��¼�Ƿ���Ӧ���㲥��,TRUE:��;FALSE:��
extern uint8_t g_bUrgency; 

 //��¼�Ƿ��һ����Ӧ���㲥
extern uint8_t g_First_Urgency;

 //Ӧ���㲥ʱ��
extern uint32_t g_wDuration;       

#endif
