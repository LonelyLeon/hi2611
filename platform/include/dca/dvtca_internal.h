#ifndef _DVTCA_INTERNAL_H_
#define _DVTCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_DVTCA       8U

#define MAX_TASK_NUMBER_DVTCA         5U

#define MAX_SEMA_NUMBER_DVTCA         14U

#define MAXLEN_TVSNAME_DVTCA  		24U

#define MAXLEN_PRODUCT_NAME_IPP_DVTCA 24U

#define MAXLEN_FEEDDATA_LEN_DVTCA 	256U

#define MAXLEN_EMAIL_SENDERNAME_DVTCA 12U

#define MAXLEN_EMAIL_TITLE_DVTCA 		32U

#define MAXLEN_EMAIL_CONTENT_DVTCA 	1025U

#define EMAIL_COUNT_DVTCA		50U

#define EMAIL_COUNT_DVTCA_COS10	 20U //cos10的库最多收20封邮件

#define OPERATOR_COUNT_DVTCA	5U

#define ENTITLE_COUNT_DVTCA      300U

#define IPP_COUNT_DVTCA 				250U

#define SLOTID_TOTAL_DVTCA            20U

#define CA_INNO_LEN_DVTCA          	40U

#define CA_EXNO_LEN_DVTCA          	64U

#define CA_PCARD_LEN_DVTCA		 	24U

#define CA_COREVER_LEN_DVTCA       	20U

#define CA_SWVER_LEN_DVTCA         	21U

#define CA_AERA_LEN_DVTCA          	12U

#define CA_RATING_LEN_DVTCA         	20U

#define CA_WORKTIME_LEN_DVTCA         20U

#define CA_COS_LEN_DVTCA				4U

#define MAXLEN_PRODUCT_NAME_DVTCA 	24U

#define MAXLEN_SERVICE_NAME_DVTCA 	24U

#define CA_MAXLEN_OSD_DVTCA   		210U

#define CA_CHIPID_LEN_DVTCA		20U


typedef struct{
	char createVersion[40];                  	    //Email 发送时间
	int8_t senderName[MAXLEN_EMAIL_SENDERNAME_DVTCA];  	//发送者姓名
	uint8_t emailLength[6];                      	//邮件内容长度
	int8_t title[MAXLEN_EMAIL_TITLE_DVTCA];    			//邮件短内容 
    uint8_t importance;                          	//重要性： 0－普通，1－重要 
    uint8_t newEmail;                            	//新邮件标记：0－已读邮件；1－新邮件 
}hrdvtca_emailInfo_t;


typedef struct{
	char version[12];                        		//发送时间
	char emailLength[6];                     		//邮件内容长度
	int8_t	email[MAXLEN_EMAIL_CONTENT_DVTCA];        	//邮件内容
}hrdvtca_emailContent_t;



typedef struct{
	char provId[8];    								//运营商的外部编号
	char provName[MAXLEN_TVSNAME_DVTCA];	
}hrdvtca_operatorInfo_t;


typedef struct{
    char productId[8];     							//产品ID   (SCDCAEntitle.m_dwProductID for cdca)	
	uint8_t tapingFlag;       						//录像标识   1 可录像， 0 不可录像
	char entitleTime[40];  							//授权时间，time_t格式。
	char startTime[40];    							//开始时间，time_t格式。  (SCDCAEntitle.m_tBeginDate for cdca)
	char endTime[40];      							//结束时间，time_t格式。   (SCDCAEntitle.mExpireDate for cdca)
	char productName[MAXLEN_PRODUCT_NAME_DVTCA];   	//产品名称  (m_Entitles  for cdca) 
}hrdvtca_serviceEntitles_t;


//数码视讯没有反授权
typedef struct{
    uint8_t Detitle[2];
}hrdvtca_detitleInfo_t;


typedef struct {
	char tvSId[6];                          //运营商ID
	char productId[6];                      //产品编号
	uint8_t slotId;                         //钱包ID
	char prodName[MAXLEN_PRODUCT_NAME_DVTCA];    	//节目名称
	char progType[5];                      	//节目类型IPPV或IPPT
	char startTime[20];                    		//开始时间
	char durationTimeDay[4];               		//持续时间XXXX天XX时XX分XX秒
	char durationTimeHour[4];
	char durationTimeMin[4];
	char durationTimeSec[4];
	char serviceName[CA_SWVER_LEN_DVTCA];        //所在频道
	char curTppTapPrice[7];                //不回传可录像价格
	char curTppNoTapPrice[7];              //不回传不录像价格(目前的CA库只显示"不回传不录像"类型的价格),  单位是元                             
	char curCppTapPrice[7];                //可回传可录像价格
	char curCppNoTapPrice[7];              //可回传不录像价格
	char bookPrice[7]; 					   //订购价格,当价格值为0时，显示"无"
	uint8_t BookedPriceType;			   //订购价格类型(四种价格中的一种,目前的CA库只显示"不回传不录像"类型的价格)
	char BookedInterval[4];			       //订购价格间隔
	char CurInterval[4];				   //当前收费间隔		
	uint8_t ippStatus;					   //订购状态 1: 已订购0: 未订购
    uint8_t	unit;					//收费间隔的单位0 -分钟1-小时2-天3-月4-年
	char ipptPeriod[6];			//用户订购IPPT的观看周期数,for Philippines LongIPPT。
	uint16_t ippIndex;              //为了订购IPP时， 在sdvtcaipp[IPP_COUNT]中    找到相应的值
}hrdvtca_ippBuyInfo_t;


typedef struct {
	char provName[MAXLEN_TVSNAME_DVTCA];	                //运营商名称
	char prodName[MAXLEN_PRODUCT_NAME_IPP_DVTCA];    		//产品名称
	char startTime[20];    							//开始时间，time_t格式。
	char durationTimeDay[4];               			//持续时间XXXX天XX时XX分XX秒
	char durationTimeHour[4];
	char durationTimeMin[4];
	char durationTimeSec[4];
	char otherInfo[48];    						//ippv时为“此产品为ippv产品”，ippt时为“观看总时间：？分钟，扣钱总数：？分”
	char bookedPrice[6];    					//预订价格(分)
	int8_t bookedPriceType;    					//预订价格类型：0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap;
	char BookedInterval[4];			            //订购价格间隔 
	int8_t unit;    							//收费单位，0 -分钟1-小时2-天3-月4-年
	int8_t slotId;                             	//钱包ID
	char tvSId[4];                             	//运营商编号
	int8_t ippStatus;							//Ipp产品状态 1: 已订购0: 未订购
	uint8_t isCanTape;    						//是否可录像
	uint8_t ippType;    						// 1: ippv  2: ippt
}hrdvtca_viewedIpp_t;



typedef struct {
    char scInNo[CA_INNO_LEN_DVTCA];			  //智能卡内部卡号
    uint8_t scExNo[CA_EXNO_LEN_DVTCA];			  //智能卡外部卡号
    char scCosVer[CA_COS_LEN_DVTCA];			  //智能卡cos版本
    char casVer[CA_COREVER_LEN_DVTCA];           //机顶盒cas版本
    uint8_t casNo[CA_SWVER_LEN_DVTCA];              //cas厂商
    char scRating[CA_RATING_LEN_DVTCA];          //智能卡级别
    char scWorktime[CA_WORKTIME_LEN_DVTCA];      //智能卡工作时段
    char areaCode[CA_AERA_LEN_DVTCA];            //区域码
    char areaTime[CA_INNO_LEN_DVTCA];            //收到区域码时间
    char chipID[CA_CHIPID_LEN_DVTCA];		//芯片ID，一般是4个字节
    uint8_t areaStatus;                       //区域码锁定状态
    uint8_t isPinLocked;
}hrdvtca_scBasicInfo_t;


typedef struct {
    uint8_t scType;                           		//卡属性 0:母卡1:子卡
    char pCardNo[CA_PCARD_LEN_DVTCA];			  			//母卡卡号
    uint8_t scPscData[MAXLEN_FEEDDATA_LEN_DVTCA];   		//喂养数据
    uint8_t scDataLen;                        		//喂养数据长度
    
}hrdvtca_scAddedInfo_t;



typedef struct {
	uint8_t slotId;
	char  remainder[12];							//剩余钱数
    char  balance[12];    							//已花的点数
}hrdvtca_slotInfo_t;

typedef struct {
    uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
}hrdvtca_SwitchChannel_t;

//重要邮件弹出显示，用户不可以遥控退出
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1030]; 
}hrdvtca_Anno_t;


/*------------------------------返回值类型定义-------------------------------------*/

#undef	CA_TRUE
#define CA_TRUE	1

#undef	CA_FALSE
#define	CA_FALSE	0

//机顶盒返回值基值定义

#define CAERR_DVTCA_BASE	0x0200



//DVTCA ERR 
#define CA_BOOK_OK                     (CAERR_DVTCA_BASE + 1)   //订购成功
#define CA_UNBOOK_OK                   (CAERR_DVTCA_BASE + 2)   //退订成功
#define CA_ERR_UNBOOK_FAIL    	       (CAERR_DVTCA_BASE + 3)   //退订失败，请再次进入菜单重试
#define CA_ERR_MONEY_LACK              (CAERR_DVTCA_BASE + 4)   //订购成功，但余额不多，请及时充值
#define CA_ERR_NEED_PIN_PASS           (CAERR_DVTCA_BASE + 5)   // 需要通过PIN验证
#define CA_ERR_IC_COMMUNICATE          (CAERR_DVTCA_BASE + 6)   //与IC卡通讯参数错误
#define CA_ERR_TVS_NOT_FOUND           (CAERR_DVTCA_BASE + 7)   //运营商ID无效
#define CA_ERR_SLOT_NOT_FOUND          (CAERR_DVTCA_BASE + 8)   //钱包没有发现

#define CA_ERR_VER_EXPIRED             (CAERR_DVTCA_BASE + 9)   // 产品已经过期
#define CA_ERR_OPER_INVALID            (CAERR_DVTCA_BASE + 10)  // 产品已经存在，不能操作
#define CA_ERR_NO_SPACE                (CAERR_DVTCA_BASE + 11)  //没有空间
#define CA_ERR_PROD_NOT_FOUND          (CAERR_DVTCA_BASE + 12)  // 产品没有发现
#define CA_ERR_PRICE_INVALID           (CAERR_DVTCA_BASE + 13)  //价格无效
#define CA_ERR_PERIOD_INVLIAD          (CAERR_DVTCA_BASE + 14)  //周期数无效
#define CA_ERR_UNKNOWN                 (CAERR_DVTCA_BASE + 15)  //未知错误
#define	CA_ERR_DVT_PIN_LOCKED     	   (CAERR_DVTCA_BASE + 16)  //PIN码被锁

/*------------------------------智能卡信息-------------------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//智能卡基本信息
extern hrdvtca_scBasicInfo_t d_ScBasicInfo_dvtca;

/*------------------------------子母卡信息----------------------------------------*/

extern hrdvtca_scAddedInfo_t d_ScAddedInfo_dvtca[OPERATOR_COUNT_DVTCA]; 

/*-----------------------------节目信息-------------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;

//购买的节目信息
extern hrdvtca_serviceEntitles_t d_ServiceEntitles_dvtca[ENTITLE_COUNT_DVTCA];

/*------------------------------IPP信息-----------------------------------------------*/

//IPPV节目总数
extern uint16_t d_IPPVProNum;

//ippv ecm pid
extern uint16_t IppvECMPID;

//ippv类型
extern uint8_t IppvType;

//查看ipp 个数
extern uint16_t viewIppCount;  

//ipp订购个数
extern uint16_t bookIppCount;

//弹出框购买ipp节目
extern hrdvtca_ippBuyInfo_t d_IppBuyInfo_dvtca;

//IPPV节目信息
extern hrdvtca_viewedIpp_t d_ViewedIPPV_dvtca[300];


/*--------------------------------钱包信息-----------------------------------------*/

//钱包总数
extern uint8_t d_SlotCount;

//钱包ID
extern uint8_t d_SlotID[20];

//充值金额
extern uint32_t ChargeValue;

extern hrdvtca_slotInfo_t  d_SlotInfo_dvtca[20];


/*-------------------------------运营商信息--------------------------------------*/

//运营商编号
extern uint16_t d_TVSId[5];

//运营商总数
extern uint8_t d_OperatorCount;

extern hrdvtca_operatorInfo_t d_OperatorInfo_dvtca[OPERATOR_COUNT_DVTCA]; 

/*-------------------------------邮件信息-----------------------------------------*/

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

//邮件头

extern hrdvtca_emailInfo_t d_EmailInfo_dvtca[EMAIL_COUNT_DVTCA];

//邮件内容

extern hrdvtca_emailContent_t d_EmailContent_dvtca;


#endif

