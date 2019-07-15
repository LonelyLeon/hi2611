#ifndef _DIVICA_INTERNAL_H_
#define _DIVICA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define DIVICA_CA_MAX_PIN_LENGTH    6U

#define DIVICA_MAX_TASK_NUMBER      4U

#define DIVICA_MAX_SEMA_NUMBER      11U

#define MAXLEN_TVSPRIINFO_DIVICA  	32U

#define MAXNUM_ACLIST_DIVICA        18U

#define MAXLEN_PRODUCT_NAME_IPP_DIVICA 	300U

#define MAXLEN_EMAIL_TITLE_DIVICA 	32U

#define MAXLEN_EMAIL_CONTENT_DIVICA 320U

#define MAXLEN_SN_DIVICA 			16U

#define EMAIL_COUNT_DIVICA			100U

#define OPERATOR_COUNT_DIVICA		4U

#define ENTITLE_COUNT_DIVICA 		300U

#define IPP_COUNT_DIVICA 			250U

#define SLOTID_TOTAL_DIVICA         20U

#define CA_EXNO_LEN_DIVICA         	24U

#define CA_COREVER_LEN_DIVICA       32U

#define CA_SWVER_LEN_DIVICA         20U

#define CA_AERA_LEN_DIVICA          12U

#define CA_CHIPID_LEN_DIVICA        20U

#define CA_RATING_LEN_DIVICA        20U

#define CA_WORKTIME_LEN_DIVICA      20U

#define CA_PARIED_LEN_DIVICA        6U

#define CA_SCTYPE_LEN_DIVICA        20U


/*-------------------------------------ipp购买信息-------------------------------------------*/
typedef struct{
	uint32_t IppvId;
	char	 IppvPrice[20];
}hrdivica_ippBuyInfo_t;  

/*-----------------------------------子母卡喂养状态------------------------------------------*/
typedef enum
{
	CA_DIVI_PROMT_CLEAR_F,      //0x00 清除提示
	CA_DIVI_INSERT_M,       	//0x01 请插入母
	CA_DIVI_UNEFFECTIVE_M,  	//0x02 无效的母
	CA_DIVI_INSERT_C,			//0x03 请插入子
	CA_DIVI_UNEFFECTIVE_C,		//0x04 无效的子
	CA_DIVI_NOT_MATCH,			//0x05 子母卡不
	CA_DIVI_CHECK_M,			//0x06 母卡通讯//0X1c 失败，请检查母卡
	CA_DIVI_CHECK_C,			//0x07 子卡通讯失败，请检查子卡
	CA_DIVI_NOTIN_ACTIVETIME,   //0x08不在激活时段内
	CA_DIVI_ACTIVE_SUCCESS,     //0x09激活成功，请插入下一张卡
	CA_DIVI_STOP_ACTIVE = 0x10, //0x10终止子卡激活操作
	CA_DIVI_UNKNOW_ERR_F,       //else未知错误
}hrdivica_caFeedS_t;

/*-----------------------------------智能卡信息------------------------------------------*/
typedef struct {
	char	 CardNo[18]; 	//8字节 BCD码：卡号
	uint8_t  PairStatus; 	//1:配对 2：未配对 0:操作失败
	char 	 CardType; 		//-1 错误  8 母卡 9 子卡
	char 	 CardLevel; 	//-1 失败 0：四岁以上 1：八岁以上 2：十二岁以上  3：十六岁以上
	char     WorkTime[20];	//工作时段 00:00:00-00:00:00
	char	 Region[20];	//区域信息001.002.003.004
	char	 CAVersion[6];	//V2.1
	char     M_CardNo[18];  //如果为子卡，则表示母卡卡号，如果为母卡，则改字段为空
}hrdivica_scBasicInfo_t;

/*------------------------------------邮件信息------------------------------------------*/
typedef struct{
	char		CreateTime[20];  //ymdhms
	uint8_t 	EmailLevel;		 //重要程度
	uint8_t 	IsNew;			//1  :new  0: not new
	uint16_t	EmailID;
	char   		title[36];       //邮件标题，最长为36
}hrdivica_emailInfo_t;									

typedef struct{
	char		email[128];
	char        title[36];       //邮件标题，最长为36
}hrdivica_emailContent_t;								

/*********************************************授权信息************************************/
typedef struct{
	uint8_t	PackageId; 		    //产品id
	char 	StartDate[12];
	char 	EndDate[12];
	char 	Price[8];
	char 	Description[40];    //产品描述
} hrdivica_serviceEntitles_t;							

/*********************************************运营商信息**********************************/
typedef struct{
	char provId[6];    								//运营商的外部编号
	uint8_t provName[MAXLEN_TVSPRIINFO_DIVICA];		//运营商详细信息	
} hrdivica_operatorInfo_t;						//SCDCAOperatorInfo in CDCA



/*********************************************反授权信息**********************************/
typedef struct{
    //uint8_t newDetitle;     						// 反授权标记：0－未读；1－已读
    char Detitle[12];    							//反授权
}hrdivica_detitleInfo_t;


/*********************************************目前没有用(ipp菜单)************************/
typedef struct {
	char productId[12];							    //节目的ID
    int8_t prodName[MAXLEN_PRODUCT_NAME_IPP_DIVICA];//节目名称
 	uint8_t	tvSId[6];    						    //运营商编号
 	uint8_t ippStatus;    						    //0 预定中， 1 已购买
	uint8_t canTape;    						    //是否可以录像  0 不可  1 可以
	char price[4];      						    //节目价格
	char ippvPeriod[12]; 						    //ippv节目过期时间
	uint8_t	slotId;    							    //钱包ID
	uint8_t isIppvOrIppt;    					    // 1: ippv  2: ippt  3: ippv and ippt
} hrdivica_viewedIpp_t;


/****************************************喂养信息(喂养菜单信息)**************************/
typedef struct {
	char wTVSid;									//运营商id
	uint8_t paired[CA_PARIED_LEN_DIVICA];			//配对状态
	uint8_t pbyIsChild;								//是否是子卡
	uint8_t pbIsCanFeed;							//是否喂养
	char pDelayTime[4];				    			//喂养周期
	char pLastFeedTime[40];							//上次喂养时间
	char parentCardSN[MAXLEN_SN_DIVICA+1];     		//母卡id
	uint8_t pbyFeedData;					
	uint8_t pbyLen;
}hrdivica_scAddedInfo_t;

/*****************************************钱包信息**************************************/
typedef struct {
	uint8_t slotId;
    char slotCreditLimit[12];    					//信用度(点数) 
    char balance[12];    							//已花的点数
}hrdivica_slotInfo_t;

/*****************************************强制换台*************************************/
typedef struct {
	uint8_t reserve;
}hrdivica_SwitchChannel_t;


/*****************************************引用部分*************************************/

/*----------------------------------------邮件信息-------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;
/*-----------------------------智能卡信息、观看级别、工作时段--------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

/*-----------------------------------------授权信息------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;

//授权剩余天数
extern uint32_t Expiredays[7];
#endif


