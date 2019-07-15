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
/*---------------------------菜单返回值定义-------------------*/
#define UNITENDCA_TRUE	                                         1
#define CAERR_UNITENDCA_BASE		                             0x0100

#define UNITENDCA_POINTER_INVALID                     (CAERR_UNITENDCA_BASE + 2)   //空指针
#define UNITENDCA_CARD_INVALID                           (CAERR_UNITENDCA_BASE + 3)   //卡无效
#define UNITENDCA_CARD_PAIROTHER                      (CAERR_UNITENDCA_BASE + 4)   //已与其它机顶盒配对
#define UNITENDCA_CARD_NOPAIR                            (CAERR_UNITENDCA_BASE + 5)   //卡未配对
#define UNITENDCA_CARD_NO_ROOM                         (CAERR_UNITENDCA_BASE + 6)   //卡空间不足
#define UNITENDCA_CARD_STATUS_OUT                   (CAERR_UNITENDCA_BASE + 7)
#define UNITENDCA_CARD_STATUS_NOT_READY       (CAERR_UNITENDCA_BASE + 8)   //卡未准备好
#define UNITENDCA_DATA_NOT_FIND 		             (CAERR_UNITENDCA_BASE + 9)   //没有找到数据
#define UNITENDCA_PIN_INVALID   		             (CAERR_UNITENDCA_BASE + 10)  //pin码无效
#define UNITENDCA_PIN_LEN_ERR 			             (CAERR_UNITENDCA_BASE + 11)  //pin码长度错误
#define UNITENDCA_PIN_LOCKED     		             (CAERR_UNITENDCA_BASE + 12)  //PIN码被锁
#define UNITENDCA_WATCHRATING_INVALID 	      (CAERR_UNITENDCA_BASE + 13)  //观看级别无效
#define UNITENDCA_WORKTIME_INVALID 	             (CAERR_UNITENDCA_BASE + 14)  //工作时段错误
#define UNITENDCA_MONEY_LACK 			             (CAERR_UNITENDCA_BASE + 15)  //钱不多，请充值
#define UNITENDCA_PROG_STATUS_INVALID 	      (CAERR_UNITENDCA_BASE + 16)
#define UNITENDCA_FEEDTIME_NOT_ARRIVE            (CAERR_UNITENDCA_BASE + 17)  //喂养时间未到，该子卡不能被喂养

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
} unitendca_scUpdate;                       //智能卡升级
/*
typedef struct{
    uint32_t actionId;  							//Email ID
    uint8_t newEmail;  								//新邮件标记：0－已读邮件；1－新邮件
	char title[MAXLEN_EMAIL_TITLE_UNITENDCA]; 		//邮件短内容
	uint32_t time;  							//发送时间，格式为:2000-02-01 09:10:10
	char email[MAXLEN_EMAIL_CONTENT_UNITENDCA];  	//内容
}hrunitendca_emailInfo_t;							//UNITENDCAEmailContent in UNITENDCA


typedef struct{
	uint8_t version[12];  							//发送时间，同时作为邮件id
	uint8_t emailLength[6]; 						//邮件内容长度
	char email[MAXLEN_EMAIL_CONTENT_UNITENDCA]; 				//邮件内容
	uint8_t reserved[6];  							//保留
}hrunitendca_emailContent_t;		*/						//SUNITENDCAEmailContent in UNITENDCA

//----------邮件
typedef struct{
	char createtime[31];  //发送时间
	char title[50]; //邮件标题
    uint8_t newEmail;  // 新邮件标记：0－已读邮件；1－新邮件 
}hrunitendca_emailInfo_t;


typedef struct{
	char senderName[32];  //发送人21
	char title[50]; //邮件标题 21
	char email[320]; //邮件内容
}hrunitendca_emailContent_t;

typedef struct{
	char provId[4];    								//运营商的外部编号
	uint8_t provName[MAXLEN_TVSPRIINFO_UNITENDCA];			//运营商详细信息	
} hrunitendca_operatorInfo_t;								//SUNITENDCAOperatorInfo in UNITENDCA


typedef struct{
    char productId[12];  							//节目ID 
	uint8_t tapingFlag;	    						//用户是否购买录像:1－可以录像；0－不可以录像 
	char startTime[12];  							//授权起始时间，格式为:2000-02-01
	char endTime[12];    							//授权过期时间，格式为:2000-02-01
	uint8_t reserved[3];    						//保留   
} hrunitendca_serviceEntitles_t;							//SUNITENDCAEntitles in UNITENDCA


typedef struct{
	char productId[12];								//节目的ID
    char tvSId[6];    								//运营商编号
    uint8_t isIppvOrIppt;							//支持ippv或ippt  1 ippv  2  ippt  3  ippv and ippt
    uint8_t ippStatus;								//收费阶段   0 ippv免费阶段  1 ippv收费阶段  2 ippt收费阶段 
    char ippCanTapPrice[6]; 						//可录像的节目价格
    char ippCanNotTapPrice[6]; 						//不可录像的节目价格
	char ippvPeriod[12]; 							//ippv节目过期时间
	char ipptInterval[12];							//ippt节目收费间隔
	uint8_t	slotId;									//钱包ID	
	uint8_t priceCode[2];                           //购买类型，priceCode[0]不可录像的节目，priceCode[1]可录像的节目
}hrunitendca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//节目的ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_UNITENDCA];  	//节目名称
	uint8_t	tvSId[6];    						//运营商编号
	uint8_t ippStatus;    						//0 预定中， 1 已购买
	uint8_t canTape;    						//是否可以录像  0 不可  1 可以
	char price[4];      						//节目价格
	char ippvPeriod[12]; 						//ippv节目过期时间
	uint8_t	slotId;    							//钱包ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrunitendca_viewedIpp_t;


typedef struct {
    char scExno[CA_EXNO_LEN_UNITENDCA];							//用户序列号
    char areaCode[CA_COREVER_LEN_UNITENDCA];					//udrm区域信息
    char buildInfo[CA_SWVER_LEN_UNITENDCA];					//版本编译信息

}hrunitendca_scBasicInfo_t;


typedef struct {
	char wTVSid;									//运营商id
	uint8_t paired[CA_PARIED_LEN_UNITENDCA];					//配对状态
	uint8_t pbyIsChild;								//是否是子卡
	uint8_t pbIsCanFeed;							//是否喂养
	char pDelayTime[4];				    			//喂养周期
	char pLastFeedTime[40];							//上次喂养时间
	char parentCardSN[MAXLEN_SN_UNITENDCA+1];     			//母卡id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrunitendca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//信用度(点数) 
    char balance[12];    							//已花的点数
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
//反授权信息总数
extern uint8_t d_DetitleCount;
//extern hrunitendca_detitleInfo_t  d_DetitleInfo_unitendca[10];
//购买的节目总数
extern uint8_t d_ServiceCount;
//购买的节目信息
//extern hrunitendca_serviceEntitles_t d_ServiceEntitles_unitendca[ENTITLE_COUNT_UNITENDCA];
//子母卡配对信息
//extern hrunitendca_scAddedInfo_t d_ScAddedInfo_unitendca[OPERATOR_COUNT_UNITENDCA]; 
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
//extern hrunitendca_ippBuyInfo_t d_IppBuyInfo_unitendca;
//IPPV节目信息
//extern hrunitendca_viewedIpp_t d_ViewedIPPV_unitendca[300];
/*--------------------------------钱包信息-----------------------------------------*/
//钱包总数
extern uint8_t d_SlotCount;
//钱包ID
extern uint8_t d_SlotID[20];
//充值金额
extern uint32_t ChargeValue;
//钱包信息
//extern hrunitendca_slotInfo_t  d_SlotInfo_unitendca[20];
/*-------------------------------运营商信息--------------------------------------*/
//运营商编号
extern uint16_t d_TVSId[5];
//运营商总数
extern uint8_t d_OperatorCount;
//运营商信息
extern hrunitendca_operatorInfo_t d_OperatorInfo_unitendca[OPERATOR_COUNT_UNITENDCA];
/*-------------------------------邮件信息-----------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;
//邮件头
//extern hrunitendca_emailInfo_t d_EmailInfo_unitendca[EMAIL_COUNT_UNITENDCA];
//邮件内容
extern hrunitendca_emailContent_t d_EmailContent_unitendca;
/*------------------------------智能卡信息-------------------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//智能卡基本信息
extern hrunitendca_scBasicInfo_t d_ScBasicInfo_unitendca;
/*------------------------------机卡对应--------------------------------------*/

//机卡对应总数
//extern uint8_t  d_pNumber;

//机卡对应列表
//extern uint8_t d_pSTBIdList[5][13];

//机卡对应状态
//extern int32_t d_pairedStatue;

extern D_Bool b_parentalfram;

/*-------------------------------应急广播---------------------------------*/

//获取当前节目的频道号
extern uint16_t g_ChNO; 

//是否禁止切台操作,TRUE:不允许切台;FALSE:允许切台
extern uint8_t forbidSwitchChannel;

//记录应急广播的持续时间长度
extern uint16_t broadcastDuration;    

//记录是否有应急广播了,TRUE:有;FALSE:无
extern uint8_t g_bUrgency; 

 //记录是否第一次有应急广播
extern uint8_t g_First_Urgency;

 //应急广播时间
extern uint32_t g_wDuration;       

/*------------------------------超级osd---------------------------------*/

//extern D_DCAOSDInfo  pOSDbuf;		
			  
/*-------------------------------其他---------------------------------------*/

//剩余插拔卡次数
extern uint8_t TryTimes;

//机顶盒id
//extern uint8_t d_StbId[12];    //机顶盒id

//是否是自动配对(only for DVNCA)
extern uint8_t g_bAutoPair;   

/*0： 当前播放的节目为电视节目 1：当前播放的节目为广播节目*/
extern uint8_t ChangeFlag;

/*0： 强制换台时没有进行电视广播的转换 1：强制换台时进行了电视广播的转换*/
extern uint8_t ToChange;

//升级成功状态
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
	uint8_t valid_flag;		//FALSH email 存储信息有效标志 0x55 表示flash中的email信息有效
	uint8_t nums;			//email 个数
	uint8_t reserved[14];	//保留备用
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
	UNITENDCA_ERR_NO_MSG,		//消息队列空
	UNITENDCA_ERR_NO_MEM,		//空间不足
	UNITENDCA_ERR_NOT_EXIST,		//邮件不存在
	UNITENDCA_ERR_DATA_LEN,		//邮件正文长度错误
	UNITENDCA_ERR_NULL_POINTER,	//空指针
	UNITENDCA_ERR_SAME_EMAIL	//重复的邮件
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


