#ifndef _MGCA_INTERNAL_H_
#define _MGCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_MGCA       6U  //为了编译通过，实际的数值有待确认

#define MAX_TASK_NUMBER_MGCA        5

#define MAX_SEMA_NUMBER_MGCA         14

#define MAXLEN_PRODUCT_NAME_IPP_MGCA 300

#define MAXLEN_FEEDDATA_LEN_MGCA 256

#define MAXLEN_EMAIL_SENDERNAME_MGCA 32

#define MAXLEN_EMAIL_SHORT_CONTENT_MGCA 50

#define MAXLEN_EMAIL_TITLE_MGCA 50

#define MAXLEN_EMAIL_CONTENT_MGCA 520

#define EMAIL_COUNT_MGCA		100U
            
#define OPERATOR_COUNT_MGCA	10

#define IPP_COUNT_MGCA 250

#define CA_EXNO_LEN_MGCA          33
#define CA_SWVER_LEN_MGCA         20
#define CA_CHIPID_LEN_MGCA         20
#define CA_SCTYPE_LEN_MGCA         20

#define CA_INNO_LEN_MGCA          20

#define MAXLEN_PRODUCT_NAME_MGCA 24
#define MAXLEN_SERVICE_NAME_MGCA 24

#define ENTITLE_COUNT_MGCA 				300U

//----------邮件
typedef struct{
	char createtime[22];  //发送时间
	char title[MAXLEN_EMAIL_SHORT_CONTENT_MGCA]; //邮件标题
    uint8_t newEmail;  // 新邮件标记：0－已读邮件；1－新邮件 
}hrmgca_emailInfo_t;


typedef struct{
	char senderName[MAXLEN_EMAIL_SENDERNAME_MGCA];  //发送人21
	char title[MAXLEN_EMAIL_SHORT_CONTENT_MGCA]; //邮件标题 21
	char email[MAXLEN_EMAIL_CONTENT_MGCA]; //邮件内容
}hrmgca_emailContent_t;


typedef struct
{
	uint8_t EMPTY;
}hrmgca_operatorInfo_t;


typedef struct{
    uint8_t EMPTY;   
}hrmgca_serviceEntitles_t;


typedef struct {
	uint8_t EMPTY;
}hrmgca_detitleInfo_t;


//---------IPPV
typedef struct {
	uint8_t ProgState; 	//订购状态 1已订购 0 未订购
	uint16_t price;  //   点/分钟
	uint32_t balance;//余额  点
}hrmgca_ippBuyInfo_t;




typedef struct {
	uint8_t	EMPTY;   
}hrmgca_viewedIpp_t;


//------智能卡信息-----
typedef struct {
	char CA_operator[20];//ca厂商									
	char CASoftver[8];//软件版本																										
    char sc_exno[CA_EXNO_LEN_MGCA];//智能卡卡号																											
	uint16_t sc_ctrlCode;//智能卡限播码 2字节					        
	uint16_t expireday;//最近授权到期（天）								
	uint8_t paired;//是否启用配对   1 启用  0未启用
    uint8_t aera_code;//区域码											 
	uint32_t balance;//电子钱包总额                                      
    uint32_t consumed;//用户已消费金额										 
	char buff[65];//特征码分两行显示，每行32个字符，已经转换成字符串																																								
}hrmgca_scBasicInfo_t;


//--------字母卡
typedef struct {
	uint8_t ismcard; //1母卡
	char    Mcardnumb[9];
	uint16_t active_day_leaving;//可观看时间
	uint16_t active_day_remain;//子卡激活时间
}hrmgca_scAddedInfo_t;



typedef struct {
	uint32_t balance;//电子钱包总额                                      
    uint32_t consumed;//用户已消费金额
}hrmgca_slotInfo_t;

typedef struct {
    uint16_t Service_ID;
}hrmgca_SwitchChannel_t;

//授权剩余天数
extern uint16_t d_NearDay;

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
extern hrmgca_ippBuyInfo_t d_IppBuyInfo_mgca;


/*-----------------------------节目信息-------------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;

/*--------------------------------钱包信息-----------------------------------------*/

//钱包总数
extern uint8_t d_SlotCount;

//钱包ID
extern uint8_t d_SlotID[20];

//充值金额
extern uint32_t ChargeValue;

/*-------------------------------运营商信息--------------------------------------*/

//运营商编号
extern uint16_t d_TVSId[5];

//运营商总数
extern uint8_t d_OperatorCount;

/*-------------------------------邮件信息-----------------------------------------*/

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

/*------------------------------智能卡信息-------------------------------------*/

//观看级别
extern uint8_t d_ViewRating;

//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//智能卡基本信息
extern hrmgca_scBasicInfo_t d_ScBasicInfo_mgca;

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
/*--------------------------------------------------------------------------*/
#endif

