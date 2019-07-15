#ifndef _CDCA_INTERNAL_H_
#define _CDCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_CDCA       	6U

#define MAX_TASK_NUMBER_CDCA         	3U

#define MAX_SEMA_NUMBER_CDCA         	20U//11U

#define MAXLEN_TVSPRIINFO_CDCA  			32U

#define MAXNUM_ACLIST_CDCA        		18U

#define MAXLEN_PRODUCT_NAME_IPP_CDCA 	300U

#define MAXLEN_EMAIL_TITLE_CDCA 			32U

#define MAXLEN_EMAIL_CONTENT_CDCA 		320U

#define MAXLEN_SN_CDCA 					16U

#define EMAIL_COUNT_CDCA                  100U

#define OPERATOR_COUNT_CDCA		4U

#if (defined(SCPUCOS) || defined(D_CA_SUPPORT_CDCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
#define ENTITLE_COUNT_CDCA				500U
#else
#define ENTITLE_COUNT_CDCA				300U
#endif

#define IPP_COUNT_CDCA 					250U

#define SLOTID_TOTAL_CDCA                20U

#define CA_EXNO_LEN_CDCA          		24U

#define CA_COREVER_LEN_CDCA       		32U

#define CA_SWVER_LEN_CDCA         		20U

#define CA_AERA_LEN_CDCA          		12U

#define CA_CHIPID_LEN_CDCA         		20U

#define CA_RATING_LEN_CDCA         		20U

#define CA_WORKTIME_LEN_CDCA         	20U

#define CA_PARIED_LEN_CDCA         		6U

#define CA_SCTYPE_LEN_CDCA         		20U

#define CDCA_SCUPDATE_FLASH_ADD 0xFFE1	//智能卡升级存放地址偏移


/*---------------------------菜单返回值定义-------------------*/
#define CA_TRUE	                                         1
#define CAERR_CDCA_BASE		             0x0100

#define CA_POINTER_INVALID                     (CAERR_CDCA_BASE + 2)   //空指针
#define CA_CARD_INVALID                           (CAERR_CDCA_BASE + 3)   //卡无效
#define CA_CARD_PAIROTHER                      (CAERR_CDCA_BASE + 4)   //已与其它机顶盒配对
#define CA_CARD_NOPAIR                            (CAERR_CDCA_BASE + 5)   //卡未配对
#define CA_CARD_NO_ROOM                         (CAERR_CDCA_BASE + 6)   //卡空间不足
#define CA_CARD_STATUS_OUT                   (CAERR_CDCA_BASE + 7)
#define CA_CARD_STATUS_NOT_READY       (CAERR_CDCA_BASE + 8)   //卡未准备好
#define CA_DATA_NOT_FIND 		             (CAERR_CDCA_BASE + 9)   //没有找到数据
#define CA_PIN_INVALID   		             (CAERR_CDCA_BASE + 10)  //pin码无效
#define CA_PIN_LEN_ERR 			             (CAERR_CDCA_BASE + 11)  //pin码长度错误
#define CA_PIN_LOCKED     		             (CAERR_CDCA_BASE + 12)  //PIN码被锁
#define CA_WATCHRATING_INVALID 	      (CAERR_CDCA_BASE + 13)  //观看级别无效
#define CA_WORKTIME_INVALID 	             (CAERR_CDCA_BASE + 14)  //工作时段错误
#define CA_MONEY_LACK 			             (CAERR_CDCA_BASE + 15)  //钱不多，请充值
#define CA_PROG_STATUS_INVALID 	      (CAERR_CDCA_BASE + 16)
#define CA_FEEDTIME_NOT_ARRIVE            (CAERR_CDCA_BASE + 17)  //喂养时间未到，该子卡不能被喂养

/*--------------------------------------------------------------------*/

typedef struct {
    uint8_t updateTime[8];
    uint8_t scUpdateStatus;
} cdca_scUpdate;                       //智能卡升级

typedef struct{
    uint32_t actionId;  							//Email ID
    uint8_t importance; 							//重要性： 0－普通，1－重要 
    uint8_t newEmail;  								//新邮件标记：0－已读邮件；1－新邮件
	char title[MAXLEN_EMAIL_TITLE_CDCA]; 				//邮件短内容
	char createtime[40];  							//发送时间，格式为:2000-02-01 09:10:10
}hrcdca_emailInfo_t;									//SCDCAEmailHead in CDCA


typedef struct{
	uint8_t version[12];  							//发送时间，同时作为邮件id
	uint8_t emailLength[6]; 						//邮件内容长度
	char email[MAXLEN_EMAIL_CONTENT_CDCA]; 				//邮件内容
	uint8_t reserved[6];  							//保留
}hrcdca_emailContent_t;								//SCDCAEmailContent in CDCA


typedef struct{
	char provId[6];    								//运营商的外部编号
	uint8_t provName[MAXLEN_TVSPRIINFO_CDCA];			//运营商详细信息	
} hrcdca_operatorInfo_t;								//SCDCAOperatorInfo in CDCA


typedef struct{
    char productId[12];  							//节目ID 
	uint8_t tapingFlag;	    						//用户是否购买录像:1－可以录像；0－不可以录像 
	char startTime[12];  							//授权起始时间，格式为:2000-02-01
	char endTime[12];    							//授权过期时间，格式为:2000-02-01
	uint8_t reserved[3];    						//保留   
} hrcdca_serviceEntitles_t;							//SCDCAEntitles in CDCA


typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrcdca_detitleInfo_t;


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
}hrcdca_ippBuyInfo_t;


typedef struct {
	char productId[12];							//节目的ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_CDCA];  	//节目名称
	uint8_t	tvSId[6];    						//运营商编号
	uint8_t ippStatus;    						//0 预定中， 1 已购买
	uint8_t canTape;    						//是否可以录像  0 不可  1 可以
	char price[4];      						//节目价格
	char ippvPeriod[12]; 						//ippv节目过期时间
	uint8_t	slotId;    							//钱包ID
	uint8_t isIppvOrIppt;    					// 1: ippv  2: ippt  3: ippv and ippt
} hrcdca_viewedIpp_t;


typedef struct {
	char wTVSid[OPERATOR_COUNT_CDCA][5];						//运营商id
    char scExno[CA_EXNO_LEN_CDCA];							//智能卡外部卡号
    char caCorever[CA_COREVER_LEN_CDCA];						//CA内核版本
    uint8_t swVer[CA_SWVER_LEN_CDCA];						//loader版本
    uint8_t chipId[CA_CHIPID_LEN_CDCA];						//带高安时唯一
    uint8_t scRating[CA_RATING_LEN_CDCA];					//智能卡级别
    uint8_t scWorktime[CA_WORKTIME_LEN_CDCA];				//智能卡工作时段
    char areaCode[OPERATOR_COUNT_CDCA][12];					//区域码
    char bouquetId[OPERATOR_COUNT_CDCA][12];					//bouquetid
	char eigenvalue[OPERATOR_COUNT_CDCA][12 * 7];			//特征值
	uint8_t verArry[32];
}hrcdca_scBasicInfo_t;


typedef struct {
	char wTVSid;									//运营商id
	uint8_t paired[CA_PARIED_LEN_CDCA];					//配对状态
	uint8_t pbyIsChild;								//是否是子卡
	uint8_t pbIsCanFeed;							//是否喂养
	char pDelayTime[4];				    			//喂养周期
	char pLastFeedTime[40];							//上次喂养时间
	char parentCardSN[MAXLEN_SN_CDCA+1];     			//母卡id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrcdca_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//信用度(点数) 
    char balance[12];    							//已花的点数
}hrcdca_slotInfo_t;

typedef struct {
	uint8_t Modulation;
    uint16_t VPid;
	uint16_t APid;
	uint16_t PcrPid; 	
	uint32_t Frequency;
	uint32_t symbol_rate;
}hrcdca_SwitchChannel_t;

typedef struct{
    char TVnumber[12];
    char SCMnumber[24];
    char STBnumber[13];
    char AreaCode[12];
    char chipID[20];
    char cardID[10];
    char cardSN[34];
}hrcdca_scmInfo_t;

//extern void *pSemaRegisterTable[30];
//extern uint32_t TaskIdTable[9];
//extern uint32_t SemIndex;
//反授权信息总数
extern uint8_t d_DetitleCount;
extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
//购买的节目总数
extern uint8_t d_ServiceCount;
//购买的节目信息
extern hrcdca_serviceEntitles_t *d_ServiceEntitles_cdca;//[ENTITLE_COUNT_CDCA];
//子母卡配对信息
extern hrcdca_scAddedInfo_t d_ScAddedInfo_cdca[OPERATOR_COUNT_CDCA]; 
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
extern hrcdca_ippBuyInfo_t d_IppBuyInfo_cdca;
//IPPV节目信息
extern hrcdca_viewedIpp_t d_ViewedIPPV_cdca[300];
/*--------------------------------钱包信息-----------------------------------------*/
//钱包总数
extern uint8_t d_SlotCount;
//钱包ID
extern uint8_t d_SlotID[20];
//充值金额
extern uint32_t ChargeValue;
//钱包信息
extern hrcdca_slotInfo_t  d_SlotInfo_cdca[20];
/*-------------------------------运营商信息--------------------------------------*/
//运营商编号
extern uint16_t d_TVSId[5];
//运营商总数
extern uint8_t d_OperatorCount;
//运营商信息
extern hrcdca_operatorInfo_t d_OperatorInfo_cdca[OPERATOR_COUNT_CDCA];
/*-------------------------------邮件信息-----------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;
//邮件头
extern hrcdca_emailInfo_t d_EmailInfo_cdca[EMAIL_COUNT_CDCA];
//邮件内容
extern hrcdca_emailContent_t d_EmailContent_cdca;
/*------------------------------智能卡信息-------------------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//智能卡基本信息
extern hrcdca_scBasicInfo_t d_ScBasicInfo_cdca;
//scm信息
extern hrcdca_scmInfo_t d_ScmInfo_cdca;
/*------------------------------机卡对应--------------------------------------*/

//机卡对应总数
extern uint8_t  d_pNumber;

//机卡对应列表
extern uint8_t d_pSTBIdList[5][13];

//机卡对应状态
extern int32_t d_pairedStatue;


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
extern uint8_t d_StbId[12];    //机顶盒id

/*0： 当前播放的节目为电视节目 1：当前播放的节目为广播节目*/
extern uint8_t ChangeFlag;

/*0： 强制换台时没有进行电视广播的转换 1：强制换台时进行了电视广播的转换*/
extern uint8_t ToChange;

//升级成功状态
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;
#endif


