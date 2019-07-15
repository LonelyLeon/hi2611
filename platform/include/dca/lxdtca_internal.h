#ifndef _LXDTCA_INTERNAL_H_
#define _LXDTCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define EXNO_LEN_LXDTCA          		24U
#define COREVER_LEN_LXDTCA      		32U
#define ATT_LEN_LXDTCA         			20U
//#define OP_COUNT_LXDTCA             	5U
#define MAXNUM_SLOT_LXDTCA          	20U   /*卡存储的最大钱包数*/
#define MAXLEN_TVSPRIINFO_LXDTCA    	20U
#define OPERATOR_COUNT_LXDTCA			4U    /*运营商的最大个数*/
#define ENTITLE_COUNT_LXDTCA			240U  /*授权信息最大个数*/
#define MAXLEN_EMAIL_TITLE_LXDTCA 		32U   /*邮件标题最大个数*/
#define MAXLEN_EMAIL_CONTENT_LXDTCA     202U  /*邮件内容最大个数*/
#define MAXNUM_IPPV_LXDTCA         		300U  /*IPPV信息最大个数*/
#define MAX_TASK_NUMBER_LXDTCA         	3U    /*库任务最大个数*/
#define MAX_SEMA_NUMBER_LXDTCA         	11U   /*库信号量最大个数*/
#define EMAIL_COUNT_LXDTCA              30U   /*邮件最大封数*/

#if 0
#define CA_MAX_PIN_LENGTH_LXDTCA       	6U



#define MAXLEN_TVSPRIINFO_LXDTCA  		32U

#define MAXNUM_ACLIST_LXDTCA        	18U

#define MAXLEN_PRODUCT_NAME_IPP_LXDTCA 	300U

#define MAXLEN_EMAIL_TITLE_LXDTCA 		32U

#define MAXLEN_EMAIL_CONTENT_LXDTCA 	320U

#define MAXLEN_SN_LXDTCA 				16U

#define EMAIL_COUNT_LXDTCA              100U





#define IPP_COUNT_LXDTCA 				250U

#define SLOTID_TOTAL_LXDTCA             20U





#define CA_SWVER_LEN_LXDTCA         	20U

#define CA_AERA_LEN_LXDTCA          	12U

#define CA_CHIPID_LEN_LXDTCA         	20U



#define CA_WORKTIME_LEN_LXDTCA         	20U

#define CA_PARIED_LEN_LXDTCA         	6U

#define CA_SCTYPE_LEN_LXDTCA         	20U

#define LXDTCA_SCUPDATE_FLASH_ADD       0xFFE1	//智能卡升级存放地址偏移


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
#endif
/*智能卡信息*/
typedef struct {
	char scExno[EXNO_LEN_LXDTCA];							//智能卡卡号
	char scMExno[EXNO_LEN_LXDTCA];							//母卡卡号(只针对子卡)
	char caCorever[COREVER_LEN_LXDTCA];						//CA内核版本
	char attTime[ATT_LEN_LXDTCA];                        	//认证时间
    uint8_t pairstate;                                      //配对状态
    uint8_t cardType;                                       //卡类型
    uint8_t scRating;										//观看级别
    uint16_t cardAreaCode;									//卡区域码
	uint16_t tsAreaCode;	                    			//流(本地)区域码
    uint16_t wTVSid[OPERATOR_COUNT_LXDTCA];					//运营商id
    uint16_t attPeriod;                                     //认证周期
}hrlxdtca_scBasicInfo_t;


/*钱包信息*/
typedef struct {
	uint8_t 	u8SlotID;        							//钱包ID
	uint8_t 	u8Ver;           							//充值版本
	uint16_t    wTVSid;          							//运营商ID
	uint16_t	u16CreditLimit;  							//剩余点数
	uint16_t	u16Balance;      							//已花的点数(已消费)
}hrlxdtca_slotInfo_t;


/*运营商信息*/
typedef struct{
	uint16_t u16OperatorID;    								//运营商的外部编号
	uint8_t  u8TVSPriInfo[MAXLEN_TVSPRIINFO_LXDTCA];		//运营商详细信息	
} hrlxdtca_operatorInfo_t;		


/*授权信息*/
typedef struct{

	uint16_t u16OperatorID;                                 //运营商ID
    uint16_t u16ProductID;                                  //节目号
	char u16ExpriData[12];								    //过期时间
} hrlxdtca_serviceEntitles_t;							


/*邮件信息*/
typedef struct{
    uint16_t actionId;  									//Email ID
    uint16_t importance; 								    //重要性： 0－普通，1－重要 
    uint8_t u8EmailFlag;    							   //0是删除邮件,1 是已读邮件, 3是新邮件
	char title[MAXLEN_EMAIL_TITLE_LXDTCA]; 				   //邮件短内容
	char createtime[40];  							       //EMAIL创建的时间
}hrlxdtca_emailInfo_t;								


/*邮件内容*/
typedef struct{
	uint8_t version[12];  									//发送时间，同时作为邮件id
	uint8_t emailLength[6]; 								//邮件内容长度
	char email[MAXLEN_EMAIL_CONTENT_LXDTCA]; 				//邮件内容
	char title[MAXLEN_EMAIL_TITLE_LXDTCA]; 					//邮件短内容
}hrlxdtca_emailContent_t;						


/*IPPV购买信息*/
typedef struct {
	uint16_t u16ProductId;									//节目的ID
	uint16_t u16OperatorID;    								//运营商的外部编号
	uint16_t u16Price;      								//节目价格
	char ippvPeriod[12]; 									//ippv节目过期时间
	uint8_t	u8SlotID;    									//钱包ID
} hrlxdtca_viewedIpp_t;

/*IPPV弹出框信息*/
typedef struct{
    uint8_t	 u8SlotID;          //钱包ID
	uint16_t u16TVSID;          //运营商ID
	uint16_t u16ProductID;      //节目的ID
	uint16_t u16Price;          //节目价格
	char u16ExpiredDate[20];	//节目过期时间
}hrlxdtca_ippBuyInfo_t;

/*反授权信息(空)*/
typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrlxdtca_detitleInfo_t;

#if 0
typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrlxdtca_detitleInfo_t;


typedef struct{
    uint8_t	 u8SlotID;          //钱包ID
	uint16_t u16TVSID;          //运营商ID
	uint16_t u16ProductID;      //节目的ID
	uint16_t u16Price;          //节目价格
	uint16_t u16ExpiredDate;	//节目过期时间
}hrlxdtca_ippBuyInfo_t;


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
} hrlxdtcaca_viewedIpp_t;





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
}hrlxdtcaca_scAddedInfo_t;




typedef struct {
	uint8_t Modulation;
    uint16_t VPid;
	uint16_t APid;
	uint16_t PcrPid; 	
	uint32_t Frequency;
	uint32_t symbol_rate;
}hrlxdtcaca_SwitchChannel_t;

//extern void *pSemaRegisterTable[30];
//extern uint32_t TaskIdTable[9];
//extern uint32_t SemIndex;
//反授权信息总数
extern uint8_t d_DetitleCount;
extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
//购买的节目总数
extern uint8_t d_ServiceCount;
//购买的节目信息
extern hrcdca_serviceEntitles_t d_ServiceEntitles_cdca[ENTITLE_COUNT_CDCA];
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

//是否是自动配对(only for DVNCA)
extern uint8_t g_bAutoPair;   

/*0： 当前播放的节目为电视节目 1：当前播放的节目为广播节目*/
extern uint8_t ChangeFlag;

/*0： 强制换台时没有进行电视广播的转换 1：强制换台时进行了电视广播的转换*/
extern uint8_t ToChange;

//升级成功状态
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;

#endif

/*授权信息*/
extern uint8_t d_ServiceCount;

/*IPPV节目总数*/
extern uint16_t d_IPPVProNum;

/*观看级别*/
extern uint8_t d_ViewRating;

/*机卡对应总数*/
extern uint8_t  d_pNumber;

/*机卡对应列表*/
extern uint8_t d_pSTBIdList[5][13];

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

#endif


