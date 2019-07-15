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

//时间信息
typedef struct
{
	uint16_t usYear;
	uint8_t ucMonth;
	uint8_t ucDay;
	uint8_t ucHour;
	uint8_t ucMinute;
	uint8_t ucSecond;
}hr_date_time_info_t;

//邮件标题
typedef struct{
    uint8_t actionId;  								//Email ID
    uint8_t importance; 							//重要性： 0－普通，1－重要 
    uint8_t newEmail;  								//新邮件标记：0－已读邮件；1－新邮件
#if (defined(DSCA_56_OVERSEAS))
    char title[32*3+1]; 				//邮件标题
    char sender[32*3+1];	            //邮件发送人
#else
	char title[MAXLEN_EMAIL_TITLE_DSCA]; 				//邮件标题
	char sender[MAXLEN_EMAIL_TITLE_DSCA];	            //邮件发送人
#endif
	char createtime[40];  						//发送时间，格式为:2000-02-01 09:10:10
}hrdsca_emailInfo_t;								

//邮件内容
typedef struct{
	uint16_t emailLength; 							//邮件内容长度
	char  email[MAXLEN_EMAIL_CONTENT_DSCA]; 			//邮件内容
}hrdsca_emailContent_t;							

//运营商信息
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

//产品信息
typedef struct{
    uint16_t productId;  							//节目ID 
	uint8_t EnableType;	    						//授权模式 
	char startTime[40];  						//授权起始时间，格式为:2000-02-01
	char endTime[40];    						//授权过期时间，格式为:2000-02-01
} hrdsca_serviceEntitles_t;						


typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrdsca_detitleInfo_t;

//IPP信息
typedef struct{
#if (defined(DSCA_56_OVERSEAS))
	char				aucIppvName[IPPV_NAME_LEN_DSCA*3+1];			//节目名称
#else
	char				aucIppvName[33];			//节目名称
#endif
	char				aucEventID[4];				//IPPV事件ID
	uint16_t			ucProviderID;     			//提供商ID
	uint16_t			usPrice;  					//节目价格
	char				stBeginTime[40];			//节目开始时间
	char				stEndTime[40];				//节目结束时间			  
}hrdsca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//节目的ID
    char prodName[MAXLEN_PRODUCT_NAME_IPP];  	//节目名称
	char	tvSId[6];    						//运营商编号
	uint8_t ippStatus;    						//0 预定中， 1 已购买
	uint8_t canTape;    						//是否可以录像  0 不可  1 可以
	char price[4];      						//节目价格
	char ippvPeriod[12]; 						//ippv节目过期时间
	uint8_t	slotId;    							//钱包ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrdsca_viewedIpp_t;

//智能卡信息
typedef struct {
	uint8_t wTVSid[OPERATOR_COUNT_DSCA];					//运营商id
    uint8_t scExno[CA_EXNO_LEN];						//智能卡外部卡号
    uint8_t caCorever[CA_COREVER_LEN];					//CA内核版本
    char scRating[CA_RATING_LEN];					//智能卡级别
    char scWorktime[CA_WORKTIME_LEN];				//智能卡工作时段
    uint8_t  areaCode[33];								//区域码
	uint8_t  scstatus;								//卡状态
	uint8_t  masterCard[CA_EXNO_LEN];					//母卡卡号
	uint8_t  groupNum[17];								//组号
	uint8_t  LCO[9];									//营业厅号
	uint8_t  cardVer[129];								//智能卡版本
}hrdsca_scBasicInfo_t;


typedef struct {
	char wTVSid;									//运营商id
	uint8_t paired[CA_PARIED_LEN];					//配对状态
	uint8_t pbyIsChild;								//是否是子卡
	uint8_t pbIsCanFeed;							//是否喂养
	char pDelayTime[4];				    			//喂养周期
	char pLastFeedTime[40];							//上次喂养时间
	char parentCardSN[MAXLEN_SN+1];     			//母卡id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrdsca_scAddedInfo_t;

//钱包信息
typedef struct {
	uint8_t slotId;
    uint8_t slotCreditLimit[25];    				 //信用度(点数) 
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


