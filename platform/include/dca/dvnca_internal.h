#ifndef _DVNCA_INTERNAL_H_
#define _DVNCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_DVNCA       	6U

#define MAX_TASK_NUMBER_DVNCA         	3U

#define MAX_SEMA_NUMBER_DVNCA         	11U

#define MAXLEN_TVSPRIINFO_DVNCA  		32U

#define MAXNUM_ACLIST_DVNCA        		18U

#define MAXLEN_PRODUCT_NAME_IPP_DVNCA 	300U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
#define MAXLEN_EMAIL_TITLE_DVNCA 		32U 
#else
#define MAXLEN_EMAIL_TITLE_DVNCA 		11U //如果第11个字符是非汉字的编码，则显示10个字符；否则显示10个或9个字符
#endif

#define MAXLEN_EMAIL_CONTENT_DVNCA 		1100U

#define MAXLEN_SN_DVNCA 				16U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
#define EMAIL_COUNT_DVNCA				32U//100U //100封邮件会导致内存溢出
#else
#define EMAIL_COUNT_DVNCA				50U//100U //100封邮件会导致内存溢出
#endif

#define ACCOUNT_COUNT_DVNCA             100U

#define OPERATOR_COUNT_DVNCA			4U

#define ENTITLE_COUNT_DVNCA 			300U

#define IPP_COUNT_DVNCA 				100U

#define SLOTID_TOTAL_DVNCA              20U

#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
#define CA_EXNO_LEN_DVNCA          		32U
#else
#define CA_EXNO_LEN_DVNCA          		24U 
#endif

#define CA_COREVER_LEN_DVNCA       		9U 

#define CA_SWVER_LEN_DVNCA         		20U

#define CA_AERA_LEN_DVNCA          		12U

#define CA_CHIPID_LEN_DVNCA         	20U

#define CA_RATING_LEN_DVNCA         	20U

#define CA_WORKTIME_LEN_DVNCA         	20U

#define CA_PARIED_LEN_DVNCA         	6U

#define CA_SCTYPE_LEN_DVNCA         	20U

#define CA_OSD_LEN_DVNCA         	    256U //实际有效的长度是255

#define MAXLEN_FORMAT_TEXT_DVNCA        292U //5+32+255

#define MAXLEN_FILTER_DATA_DVNCA        1024U 

typedef struct
{    
	float p;       //充值点数
    int32_t Index; //充值索引
}hrdvnca_autoChange_t;


typedef struct
{    
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS))
	uint8_t email_id;
#endif
	uint8_t status;
	char email_Time[8];    
	char body_context[MAXLEN_EMAIL_CONTENT_DVNCA+2];
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS))
	char body_text[MAXLEN_EMAIL_TITLE_DVNCA+2];
#endif 
}CA_MAIL_T; //存储邮件(有卡ca，无卡ca),显示邮件(无卡ca)时使用此结构体

typedef struct
{    
	uint8_t email_id;  //有卡ca添加email_id选项，为显示邮件时排序使用
	uint8_t status;
	char email_Time[8];    
	char body_context[MAXLEN_EMAIL_CONTENT_DVNCA+2];
}DVNCA_MAIL_T; //有卡ca显示邮件时使用此结构体

typedef struct{
    uint8_t importance; 							//重要性： 0－普通，1－重要 
    uint8_t newEmail;  								//新邮件标记：0－已读邮件；1－新邮件
	char title[MAXLEN_EMAIL_TITLE_DVNCA]; 				//邮件短内容
	char createtime[40];  							//发送时间，格式为:2000-02-01 09:10:10
}hrdvnca_emailInfo_t;									


typedef struct{
	char email[MAXLEN_EMAIL_CONTENT_DVNCA]; 	    //邮件内容
	char title[36];                                 //邮件标题，最长为36
}hrdvnca_emailContent_t;								


typedef struct{
	char provId[6];    								//运营商的外部编号
	char provName[MAXLEN_TVSPRIINFO_DVNCA];			//运营商详细信息	
} hrdvnca_operatorInfo_t;								


typedef struct{
    char productId[6];  							//授权号
	char startTime[20];  							//授权起始时间，格式为:2000-02-01 00:00:01
	char endTime[20];    							//授权过期时间，格式为:2000-02-01 00:00:01
} hrdvnca_serviceEntitles_t;							


typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrdvnca_detitleInfo_t;


typedef struct{
	uint8_t type;								    //IPPV属性
    uint8_t Product_ID[2];    						//节目号
    uint8_t Reserved[2];							//预留
    uint8_t Price[4];								//价格
    uint8_t Start_Time[8];                          //开始时间
    uint8_t End_Time[8]; 						    //结束时间
    uint8_t Trans_Time[8];                          //预览时间(当前时间)
}hrdvnca_ippBuyInfo_t;


typedef struct {
	char Product_ID[6];    						//节目号
    char Price[8];								//价格，格式为.2f
    char Start_Time[20];                        //开始时间2000-00-00  00:00:00
    char End_Time[20]; 						    //结束时间 2000-00-00  00:00:00
} hrdvnca_viewedIpp_t;


typedef struct {
    char scExno[CA_EXNO_LEN_DVNCA];					//智能卡外部卡号
    char caCorever[CA_COREVER_LEN_DVNCA];				//CA内核版本
 }hrdvnca_scBasicInfo_t;

typedef struct {
	char stbID[32 + 1];							//机顶盒号
	uint8_t paired;				                //配对状态0: 未配对, 1:已配对
	char accNo[8 + 1];				    		//账号
	char token[14];     		                //金额 , 形式为 %ld.%02d
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
	char licenceID[32 + 1];		               //licenceID, 无卡时使用
    char groupID[32 + 1];		               //groupID, 无卡时使用
#endif
}hrdvnca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char balance[12];    					    //可用的点数
    char cost[12];    						   //已花的点数
}hrdvnca_slotInfo_t;


typedef struct{
    char type[4];  							//类型
    char TransID[7];  						//交易号  
	char startTime[20];  				    //起始时间，格式为:2000-02-01 00:00:01
	char price[14];    					    //金额 , 形式为 %ld.%02d
	char confirmCode[17];                   //确认码
} hrdvnca_accountRecords_t;							

typedef struct
{
	CA_MAIL_T email_info; //email的信息
}hrdvnca_email_t; //  此结构体用于存储email使用


typedef struct {
	uint8_t reserve;
}hrdvnca_SwitchChannel_t;

//全屏osd
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1024]; 
}hrdvnca_Anno_t;


/*-----------------------------节目信息-------------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;

/*------------------------------智能卡信息-------------------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

/*-------------------------------运营商信息--------------------------------------*/
//运营商编号
extern uint16_t d_TVSId[5];
//运营商总数
extern uint8_t d_OperatorCount;

/*--------------------------------钱包信息-----------------------------------------*/
//钱包总数
extern uint8_t d_SlotCount;
//钱包ID
extern uint8_t d_SlotID[20];

/*-------------------------------邮件信息-----------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;


/*------------------------------IPP信息-----------------------------------------------*/
//IPPV节目总数
extern uint16_t d_IPPVProNum;
#endif


