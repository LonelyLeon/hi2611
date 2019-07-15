#ifndef _UNITENDCA_INTERNAL_H_
#define _UNITENDCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_UNITENDCA       	6U

#define MAX_TASK_NUMBER_UNITENDCA         	3U

#define MAX_SEMA_NUMBER_UNITENDCA         	11U

#define MAXLEN_TVSPRIINFO_UNITENDCA  		128U

#define MAXNUM_ACLIST_UNITENDCA        		18U

#define MAXLEN_PRODUCT_NAME_IPP_UNITENDCA 	300U

#define MAXLEN_EMAIL_TITLE_UNITENDCA 		32U

#define MAXLEN_EMAIL_TITLEII_UNITENDCA 		80U

#define MAXLEN_EMAIL_CONTENT_UNITENDCA 		320U

#define MAXLEN_SN_UNITENDCA 				16U

#define EMAIL_COUNT_UNITENDCA               30U

#define OPERATOR_COUNT_UNITENDCA			4U

#define ENTITLE_COUNT_UNITENDCA				300U

#define IPP_COUNT_UNITENDCA 				250U

#define SLOTID_TOTAL_UNITENDCA              20U

#define CA_EXNO_LEN_UNITENDCA          		18U

#define CA_COREVER_LEN_UNITENDCA       		10U

#define CA_SWVER_LEN_UNITENDCA         		129U

#define CA_AERA_LEN_UNITENDCA          		12U

#define CA_CHIPID_LEN_UNITENDCA         	20U

#define CA_RATING_LEN_UNITENDCA         	20U

#define CA_WORKTIME_LEN_UNITENDCA         	20U

#define CA_PARIED_LEN_UNITENDCA         	6U

#define CA_SCTYPE_LEN_UNITENDCA         	20U

#define UNITENDCA_MAX_SLOT                  4U

#define OSD_LEN_UNITENDCA 					300U
/*---------------------------�˵�����ֵ����-------------------*/
#define UNITENDCA_TRUE	                                         1
#define CAERR_UNITENDCA_BASE		                             0x0100

#define UNITENDCA_POINTER_INVALID                     (CAERR_UNITENDCA_BASE + 2)   //��ָ��
#define UNITENDCA_CARD_INVALID                           (CAERR_UNITENDCA_BASE + 3)   //����Ч
#define UNITENDCA_CARD_PAIROTHER                      (CAERR_UNITENDCA_BASE + 4)   //�����������������
#define UNITENDCA_CARD_NOPAIR                            (CAERR_UNITENDCA_BASE + 5)   //��δ���
#define UNITENDCA_CARD_NO_ROOM                         (CAERR_UNITENDCA_BASE + 6)   //���ռ䲻��
#define UNITENDCA_CARD_STATUS_OUT                   (CAERR_UNITENDCA_BASE + 7)
#define UNITENDCA_CARD_STATUS_NOT_READY       (CAERR_UNITENDCA_BASE + 8)   //��δ׼����
#define UNITENDCA_DATA_NOT_FIND 		             (CAERR_UNITENDCA_BASE + 9)   //û���ҵ�����
#define UNITENDCA_PIN_INVALID   		             (CAERR_UNITENDCA_BASE + 10)  //pin����Ч
#define UNITENDCA_PIN_LEN_ERR 			             (CAERR_UNITENDCA_BASE + 11)  //pin�볤�ȴ���
#define UNITENDCA_PIN_LOCKED     		             (CAERR_UNITENDCA_BASE + 12)  //PIN�뱻��
#define UNITENDCA_WATCHRATING_INVALID 	      (CAERR_UNITENDCA_BASE + 13)  //�ۿ�������Ч
#define UNITENDCA_WORKTIME_INVALID 	             (CAERR_UNITENDCA_BASE + 14)  //����ʱ�δ���
#define UNITENDCA_MONEY_LACK 			             (CAERR_UNITENDCA_BASE + 15)  //Ǯ���࣬���ֵ
#define UNITENDCA_PROG_STATUS_INVALID 	      (CAERR_UNITENDCA_BASE + 16)
#define UNITENDCA_FEEDTIME_NOT_ARRIVE            (CAERR_UNITENDCA_BASE + 17)  //ι��ʱ��δ�������ӿ����ܱ�ι��

/*--------------------------------------------------------------------*/
typedef struct {
    uint16_t cat_pid;
    uint16_t pmt_pid;
    uint16_t ecm_pid;
    uint16_t emm_pid;
} unitendca_dmux_pid; 

typedef struct {
    uint8_t updateTime[8];
    uint8_t scUpdateStatus;
} unitendca_scUpdate;                       //���ܿ�����
/*
typedef struct{
    uint32_t actionId;  							//Email ID
    uint8_t newEmail;  								//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	char title[MAXLEN_EMAIL_TITLE_UNITENDCA]; 		//�ʼ�������
	uint32_t time;  							//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
	char email[MAXLEN_EMAIL_CONTENT_UNITENDCA];  	//����
}hrunitendca_emailInfo_t;							//UNITENDCAEmailContent in UNITENDCA


typedef struct{
	uint8_t version[12];  							//����ʱ�䣬ͬʱ��Ϊ�ʼ�id
	uint8_t emailLength[6]; 						//�ʼ����ݳ���
	char email[MAXLEN_EMAIL_CONTENT_UNITENDCA]; 				//�ʼ�����
	uint8_t reserved[6];  							//����
}hrunitendca_emailContent_t;		*/						//SUNITENDCAEmailContent in UNITENDCA

//----------�ʼ�
typedef struct{
	char createtime[31];  //����ʱ��
	char title[50]; //�ʼ�����
    uint8_t newEmail;  // ���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ� 
}hrunitendca_emailInfo_t;


typedef struct{
	char senderName[32];  //������21
	char title[50]; //�ʼ����� 21
	char email[320]; //�ʼ�����
}hrunitendca_emailContent_t;

typedef struct{
	char provId[4];    								//��Ӫ�̵��ⲿ���
	uint8_t provName[MAXLEN_TVSPRIINFO_UNITENDCA];			//��Ӫ����ϸ��Ϣ	
} hrunitendca_operatorInfo_t;								//SUNITENDCAOperatorInfo in UNITENDCA


typedef struct{
    char productId[12];  							//��ĿID 
	uint8_t tapingFlag;	    						//�û��Ƿ���¼��:1������¼��0��������¼�� 
	char startTime[12];  							//��Ȩ��ʼʱ�䣬��ʽΪ:2000-02-01
	char endTime[12];    							//��Ȩ����ʱ�䣬��ʽΪ:2000-02-01
	uint8_t reserved[3];    						//����   
} hrunitendca_serviceEntitles_t;							//SUNITENDCAEntitles in UNITENDCA


typedef struct{
	char productId[12];								//��Ŀ��ID
    char tvSId[6];    								//��Ӫ�̱��
    uint8_t isIppvOrIppt;							//֧��ippv��ippt  1 ippv  2  ippt  3  ippv and ippt
    uint8_t ippStatus;								//�շѽ׶�   0 ippv��ѽ׶�  1 ippv�շѽ׶�  2 ippt�շѽ׶� 
    char ippCanTapPrice[6]; 						//��¼��Ľ�Ŀ�۸�
    char ippCanNotTapPrice[6]; 						//����¼��Ľ�Ŀ�۸�
	char ippvPeriod[12]; 							//ippv��Ŀ����ʱ��
	char ipptInterval[12];							//ippt��Ŀ�շѼ��
	uint8_t	slotId;									//Ǯ��ID	
	uint8_t priceCode[2];                           //�������ͣ�priceCode[0]����¼��Ľ�Ŀ��priceCode[1]��¼��Ľ�Ŀ
}hrunitendca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//��Ŀ��ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_UNITENDCA];  	//��Ŀ����
	uint8_t	tvSId[6];    						//��Ӫ�̱��
	uint8_t ippStatus;    						//0 Ԥ���У� 1 �ѹ���
	uint8_t canTape;    						//�Ƿ����¼��  0 ����  1 ����
	char price[4];      						//��Ŀ�۸�
	char ippvPeriod[12]; 						//ippv��Ŀ����ʱ��
	uint8_t	slotId;    							//Ǯ��ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrunitendca_viewedIpp_t;


typedef struct {
    char scExno[CA_EXNO_LEN_UNITENDCA];							//�û����к�
    char areaCode[CA_COREVER_LEN_UNITENDCA];					//udrm������Ϣ
    char buildInfo[CA_SWVER_LEN_UNITENDCA];					//�汾������Ϣ

}hrunitendca_scBasicInfo_t;


typedef struct {
	char wTVSid;									//��Ӫ��id
	uint8_t paired[CA_PARIED_LEN_UNITENDCA];					//���״̬
	uint8_t pbyIsChild;								//�Ƿ����ӿ�
	uint8_t pbIsCanFeed;							//�Ƿ�ι��
	char pDelayTime[4];				    			//ι������
	char pLastFeedTime[40];							//�ϴ�ι��ʱ��
	char parentCardSN[MAXLEN_SN_UNITENDCA+1];     			//ĸ��id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrunitendca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//���ö�(����) 
    char balance[12];    							//�ѻ��ĵ���
}hrunitendca_slotInfo_t;

typedef struct {
	uint8_t Modulation;
    uint16_t VPid;
	uint16_t APid;
	uint16_t PcrPid; 	
	uint32_t Frequency;
	uint32_t symbol_rate;
}hrunitendca_SwitchChannel_t;

//extern void *pSemaRegisterTable[30];
//extern uint32_t TaskIdTable[9];
//extern uint32_t SemIndex;
//����Ȩ��Ϣ����
extern uint8_t d_DetitleCount;
//extern hrunitendca_detitleInfo_t  d_DetitleInfo_unitendca[10];
//����Ľ�Ŀ����
extern uint8_t d_ServiceCount;
//����Ľ�Ŀ��Ϣ
//extern hrunitendca_serviceEntitles_t d_ServiceEntitles_unitendca[ENTITLE_COUNT_UNITENDCA];
//��ĸ�������Ϣ
//extern hrunitendca_scAddedInfo_t d_ScAddedInfo_unitendca[OPERATOR_COUNT_UNITENDCA]; 
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
//��������ipp��Ŀ
//extern hrunitendca_ippBuyInfo_t d_IppBuyInfo_unitendca;
//IPPV��Ŀ��Ϣ
//extern hrunitendca_viewedIpp_t d_ViewedIPPV_unitendca[300];
/*--------------------------------Ǯ����Ϣ-----------------------------------------*/
//Ǯ������
extern uint8_t d_SlotCount;
//Ǯ��ID
extern uint8_t d_SlotID[20];
//��ֵ���
extern uint32_t ChargeValue;
//Ǯ����Ϣ
//extern hrunitendca_slotInfo_t  d_SlotInfo_unitendca[20];
/*-------------------------------��Ӫ����Ϣ--------------------------------------*/
//��Ӫ�̱��
extern uint16_t d_TVSId[5];
//��Ӫ������
extern uint8_t d_OperatorCount;
//��Ӫ����Ϣ
extern hrunitendca_operatorInfo_t d_OperatorInfo_unitendca[OPERATOR_COUNT_UNITENDCA];
/*-------------------------------�ʼ���Ϣ-----------------------------------------*/
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;
//�ʼ�ͷ
//extern hrunitendca_emailInfo_t d_EmailInfo_unitendca[EMAIL_COUNT_UNITENDCA];
//�ʼ�����
extern hrunitendca_emailContent_t d_EmailContent_unitendca;
/*------------------------------���ܿ���Ϣ-------------------------------------*/
//�ۿ�����
extern uint8_t d_ViewRating;
//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//���ܿ�������Ϣ
extern hrunitendca_scBasicInfo_t d_ScBasicInfo_unitendca;
/*------------------------------������Ӧ--------------------------------------*/

//������Ӧ����
//extern uint8_t  d_pNumber;

//������Ӧ�б�
//extern uint8_t d_pSTBIdList[5][13];

//������Ӧ״̬
//extern int32_t d_pairedStatue;

extern D_Bool b_parentalfram;

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

/*------------------------------����osd---------------------------------*/

//extern D_DCAOSDInfo  pOSDbuf;		
			  
/*-------------------------------����---------------------------------------*/

//ʣ���ο�����
extern uint8_t TryTimes;

//������id
//extern uint8_t d_StbId[12];    //������id

//�Ƿ����Զ����(only for DVNCA)
extern uint8_t g_bAutoPair;   

/*0�� ��ǰ���ŵĽ�ĿΪ���ӽ�Ŀ 1����ǰ���ŵĽ�ĿΪ�㲥��Ŀ*/
extern uint8_t ChangeFlag;

/*0�� ǿ�ƻ�̨ʱû�н��е��ӹ㲥��ת�� 1��ǿ�ƻ�̨ʱ�����˵��ӹ㲥��ת��*/
extern uint8_t ToChange;

//�����ɹ�״̬
//extern uint8_t g_cur_updata_time_flag;

//extern uint8_t cwctrl;

//extern uint8_t cwctrl_t;

extern unitendca_dmux_pid udrmfilterpid;
extern char  IemialTitleBuffer[MAXLEN_EMAIL_TITLEII_UNITENDCA];
extern char  IemialDataBuffer[MAXLEN_EMAIL_CONTENT_UNITENDCA];
/***********************email*******************************/
#define UNITENDCA_EMAIL_CONTENT_LEN			320
#define UNITENDCA_EMAIL_TOPIC_LEN			21
#define UNITENDCA_EMAIL_ADDR_LEN			21
#define UNITENDCA_EMAIL_TIME_LEN			31
#define UNITENDCA_EMAIL_HEAD_LEN			(EMAIL_TOPIC_LEN + EMAIL_ADDR_LEN + EMAIL_TIME_LEN + 6)
#define UNITENDCA_EMAIL_BOOT_FLAG			0x55

typedef struct unitendca_email_head_s
{
	uint8_t		topic[UNITENDCA_EMAIL_TOPIC_LEN];
	uint8_t		addr[UNITENDCA_EMAIL_ADDR_LEN];		//addresser
	uint8_t		time[UNITENDCA_EMAIL_TIME_LEN];		//0xYYYYMMDDHHMM
	uint8_t	    bRead;

	uint16_t	length;						//content length
	uint16_t	id;
 } unitendca_email_head_t;

	
typedef struct unitendca_email_s
{
	unitendca_email_head_t mailhead;
		
	uint8_t		pContent[UNITENDCA_EMAIL_CONTENT_LEN];
	
 } unitendca_email_t;

typedef struct unitendca_email_boot_s
{
	uint8_t valid_flag;		//FALSH email �洢��Ϣ��Ч��־ 0x55 ��ʾflash�е�email��Ϣ��Ч
	uint8_t nums;			//email ����
	uint8_t reserved[14];	//��������
}unitendca_email_boot_t;

typedef union unitendca_email_param_s
{
	uint8_t nums;
	uint8_t index;
	uint16_t id;

	unitendca_email_head_t head;
	
	struct
	{
		uint8_t *pHead;
		uint8_t *pBody;
	}unitendca_email;	
} unitendca_email_param_t;

typedef enum
{
	UNITENDCA_EMAIL_ALL,
	UNITENDCA_EMAIL_READ,
	UNITENDCA_EMAIL_FIRST,
	UNITENDCA_EMAIL_ID,
	UNITENDCA_EMAIL_Index
}UNITENDCA_EMAIL_DEL_TYPE;

typedef enum
{
	UNITENDCA_ERR_SUCCESS = 0,
	UNITENDCA_ERR_FAILED,	
	UNITENDCA_ERR_NO_MSG,		//��Ϣ���п�
	UNITENDCA_ERR_NO_MEM,		//�ռ䲻��
	UNITENDCA_ERR_NOT_EXIST,		//�ʼ�������
	UNITENDCA_ERR_DATA_LEN,		//�ʼ����ĳ��ȴ���
	UNITENDCA_ERR_NULL_POINTER,	//��ָ��
	UNITENDCA_ERR_SAME_EMAIL	//�ظ����ʼ�
}UNITENDCA_EMAIL_ERR;

typedef enum
{
	UNITENDCA_EMAIL_DATA_INIT = 1,
	UNITENDCA_EMAIL_GET_NUM,
	UNITENDCA_EMAIL_GET_HEAD,
	UNITENDCA_EMAIL_GET_BODY,
	UNITENDCA_EMAIL_ADD_NEW,
	UNITENDCA_EMAIL_DEL_ALL,
	UNITENDCA_EMAIL_DEL_Index,
	UNITENDCA_EMAIL_DEL_FIRST,
	UNITENDCA_EMAIL_DEL_ID,	
	UNITENDCA_EMAIL_BACKUP,
	UNITENDCA_MSG_ADD,
	UNITENDCA_MSG_GET,
}UNITENDCA_EMAIL_OP_TYPE;

/*******************************************/


#endif


