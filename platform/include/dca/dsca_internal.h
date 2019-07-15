#ifndef _DSCA_INTERNAL_H_
#define _DSCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define		OPERATOR_NAME_LEN_DSCA				(40)
#define		OPERATOR_PHONE_LEN_DSCA				(40)
#define		OPERATOR_ADDRESS_LEN_DSCA			(80)
#define		IPPV_NAME_LEN_DSCA					(32)
#define		MAIL_TITAL_LEN_DSCA					(32)


//#define CA_MAX_PIN_LENGTH       	6U

#define MAX_TASK_NUMBER_DS         	8U

#define MAX_SEMA_NUMBER         	20U

#define MAXLEN_TVSPRIINFO  			32U

#define MAXNUM_ACLIST        		18U

#define MAXLEN_PRODUCT_NAME_IPP 	300U

#define MAXLEN_EMAIL_TITLE_DSCA 			33U

#define MAXLEN_EMAIL_CONTENT_DSCA 		1025U

#define MAXLEN_SN 					16U

#define EMAIL_COUNT_DSCA					50U

#define OPERATOR_COUNT_DSCA				5U

#define ENTITLE_COUNT_DSCA 				100U //300u

#define IPP_COUNT_DSCA 					250U

#define SLOTID_TOTAL_DSCA            4U

#define CA_EXNO_LEN          		13U

#define CA_COREVER_LEN       		25U

#define CA_SWVER_LEN         		20U

#define CA_AERA_LEN          		12U

#define CA_CHIPID_LEN         		20U

#define CA_RATING_LEN         		20U

#define CA_WORKTIME_LEN         	20U

#define CA_PARIED_LEN         		6U

#define CA_SCTYPE_LEN         		20U

//ʱ����Ϣ
typedef struct
{
	uint16_t usYear;
	uint8_t ucMonth;
	uint8_t ucDay;
	uint8_t ucHour;
	uint8_t ucMinute;
	uint8_t ucSecond;
}hr_date_time_info_t;

//�ʼ�����
typedef struct{
    uint8_t actionId;  								//Email ID
    uint8_t importance; 							//��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t newEmail;  								//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
#if (defined(DSCA_56_OVERSEAS))
    char title[32*3+1]; 				//�ʼ�����
    char sender[32*3+1];	            //�ʼ�������
#else
	char title[MAXLEN_EMAIL_TITLE_DSCA]; 				//�ʼ�����
	char sender[MAXLEN_EMAIL_TITLE_DSCA];	            //�ʼ�������
#endif
	char createtime[40];  						//����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
}hrdsca_emailInfo_t;								

//�ʼ�����
typedef struct{
	uint16_t emailLength; 							//�ʼ����ݳ���
	char  email[MAXLEN_EMAIL_CONTENT_DSCA]; 			//�ʼ�����
}hrdsca_emailContent_t;							

//��Ӫ����Ϣ
typedef struct
{
#if (defined(DSCA_56_OVERSEAS))
	char provName[OPERATOR_NAME_LEN_DSCA*3];
	char provPhone[OPERATOR_PHONE_LEN_DSCA*3];
	char provAddress[OPERATOR_ADDRESS_LEN_DSCA*3];
#else
	char provName[OPERATOR_NAME_LEN_DSCA];
	char provPhone[OPERATOR_PHONE_LEN_DSCA];
	char provAddress[OPERATOR_ADDRESS_LEN_DSCA];
#endif
	uint8_t provID[30];
}hrdsca_operatorInfo_t;

//��Ʒ��Ϣ
typedef struct{
    uint16_t productId;  							//��ĿID 
	uint8_t EnableType;	    						//��Ȩģʽ 
	char startTime[40];  						//��Ȩ��ʼʱ�䣬��ʽΪ:2000-02-01
	char endTime[40];    						//��Ȩ����ʱ�䣬��ʽΪ:2000-02-01
} hrdsca_serviceEntitles_t;						


typedef struct{
    //uint8_t newDetitle;     						// ����Ȩ��ǣ�0��δ����1���Ѷ�
    char Detitle[12];    							//����Ȩ
}hrdsca_detitleInfo_t;

//IPP��Ϣ
typedef struct{
#if (defined(DSCA_56_OVERSEAS))
	char				aucIppvName[IPPV_NAME_LEN_DSCA*3+1];			//��Ŀ����
#else
	char				aucIppvName[33];			//��Ŀ����
#endif
	char				aucEventID[4];				//IPPV�¼�ID
	uint16_t			ucProviderID;     			//�ṩ��ID
	uint16_t			usPrice;  					//��Ŀ�۸�
	char				stBeginTime[40];			//��Ŀ��ʼʱ��
	char				stEndTime[40];				//��Ŀ����ʱ��			  
}hrdsca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//��Ŀ��ID
    char prodName[MAXLEN_PRODUCT_NAME_IPP];  	//��Ŀ����
	char	tvSId[6];    						//��Ӫ�̱��
	uint8_t ippStatus;    						//0 Ԥ���У� 1 �ѹ���
	uint8_t canTape;    						//�Ƿ����¼��  0 ����  1 ����
	char price[4];      						//��Ŀ�۸�
	char ippvPeriod[12]; 						//ippv��Ŀ����ʱ��
	uint8_t	slotId;    							//Ǯ��ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrdsca_viewedIpp_t;

//���ܿ���Ϣ
typedef struct {
	uint8_t wTVSid[OPERATOR_COUNT_DSCA];					//��Ӫ��id
    uint8_t scExno[CA_EXNO_LEN];						//���ܿ��ⲿ����
    uint8_t caCorever[CA_COREVER_LEN];					//CA�ں˰汾
    char scRating[CA_RATING_LEN];					//���ܿ�����
    char scWorktime[CA_WORKTIME_LEN];				//���ܿ�����ʱ��
    uint8_t  areaCode[33];								//������
	uint8_t  scstatus;								//��״̬
	uint8_t  masterCard[CA_EXNO_LEN];					//ĸ������
	uint8_t  groupNum[17];								//���
	uint8_t  LCO[9];									//Ӫҵ����
	uint8_t  cardVer[129];								//���ܿ��汾
}hrdsca_scBasicInfo_t;


typedef struct {
	char wTVSid;									//��Ӫ��id
	uint8_t paired[CA_PARIED_LEN];					//���״̬
	uint8_t pbyIsChild;								//�Ƿ����ӿ�
	uint8_t pbIsCanFeed;							//�Ƿ�ι��
	char pDelayTime[4];				    			//ι������
	char pLastFeedTime[40];							//�ϴ�ι��ʱ��
	char parentCardSN[MAXLEN_SN+1];     			//ĸ��id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrdsca_scAddedInfo_t;

//Ǯ����Ϣ
typedef struct {
	uint8_t slotId;
    uint8_t slotCreditLimit[25];    				 //���ö�(����) 
}hrdsca_slotInfo_t;

typedef struct {
    uint32_t NetWorkID;
    uint16_t TsID;
    uint16_t Service_ID;
}hrdsca_SwitchChannel_t;


extern uint16_t d_TVSId[5];
extern uint8_t d_OperatorCount;
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
extern uint16_t d_EmailCount;
extern uint16_t d_NewEmailCount;
extern uint16_t d_EmptyEmailCount;
extern uint8_t d_ViewRating;
extern uint8_t d_ServiceCount;

extern hrdsca_ippBuyInfo_t d_IppBuyInfo_dsca;

#endif


