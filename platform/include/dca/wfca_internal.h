#ifndef WFCA_INTERNAL_H
#define WFCA_INTERNAL_H

//#include "typedef.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define DEMUX_INVALID_PID   	 0x1FFF

/*
如果定义高级安全，添加高级安全的两个库，将fun取消编译
*/
//------------------------------------
#define CA_MAX_PIN_LENGTH   	 6u //为了编译通过，实际的数值有待确认
#define IPP_COUNT 				 350u
#define OPERATOR_COUNT 			 320u 
#define EMAIL_COUNT_WFCA   		 50u
#define MAXLEN_EMAIL_CONTENT 	 1124u
#define MAXLEN_EMAIL_SENDERNAME  16u
#define ENTITLE_COUNT_WFCA  	 300u
#define MAXLEN_EMAIL_TITLE	 	 17u
#define MAX_TABLE_LEN 		     1024u
//------------------------RESERVE-------------------
typedef struct
{
	uint8_t reserve;

}hrwfca_detitleInfo_t;

//运营商信息
typedef struct{	

	uint8_t reserve;

}hrwfca_operatorInfo_t; 

//
typedef struct
{
	uint8_t reserve;

}hrwfca_scAddedInfo_t;

//IPP授权信息
typedef struct
{
	uint8_t reserve;

}hrwfca_viewedIpp_t;	
//-----------------------END RESERVE----------------

//卡相关
typedef struct
{
	char 		CASTime[64];//CAS 时间	

	uint8_t		ChildCard;/* 是否是子卡,TRUE＝是子卡, FALSE＝是母卡 */
	uint8_t		Card_No[8];/* 卡号 */
	char		Issuance_Date[64];/*开卡时间*/
	char		Expire_Date[64];/*到期时间*/
	uint8_t		Provider[32];/* String,卡的发行商 */

	 /* 以下的域只有子卡才有效 */
	uint8_t		MotherCardNo[8];/* 母卡的卡号*/
	char 		UpdateOrigination[64];/* 母卡对子卡授权时的时间起点 */
	char 		UpdateExpiration[64]; /* 母卡对子卡授权时的时间终点 */

	//VERSION
	uint16_t	Cas_Id;	/*CAS标识*/
	uint16_t	Sub_Id;	/*CAS标识*/
	char		Version[8];/*CAS版本*/
	uint8_t		Description[32];/* String,CAS的描述 */
	uint8_t		InorRemove;/*卡当前状态*/
    char		chipid[10];/*chip ID*/
    char        StbNo[10];/*机顶盒序列号*/
    uint8_t     IsPaired;

}hrwfca_scBasicInfo_t;

//电子钱包
//typedef WFCAS_Purse_t hrca_slotInfo_t;
typedef struct
{
	uint32_t	Money;/* 用户当前总金额：以最小货币单位为单位*/
	uint32_t	Balance;/*用户已消费总额: 以最小货币单位为单位*/
}hrwfca_slotInfo_t;


//IPP弹出购买框
typedef struct
{
	uint8_t IsPPV;
	uint16_t Interval;
	uint16_t UnitPrice;

}hrwfca_ippBuyInfo_t;

//授权信息
typedef struct
{
	char	Product_Id[64];/* Product identifier */
	char	Ori_Date[64];/* original date,MJD */
	char	Ori_Time[64];/* original time,UTC */
	char	Exp_Date[64];/* expire date,MJD */
	char	Exp_Time[64];/* expire time,UTC */
}hrwfca_serviceEntitles_t;

//日期
typedef struct
{
	uint16_t	Year;
	uint8_t		Month;
	uint8_t		Day;
}WFCO_Date_t;


//邮件头
typedef struct{
	uint32_t        actionId;                 //邮件唯一id号
    uint8_t          newEmail;  			//新邮件标记：0－已读邮件；1－新邮件
   	char	      createtime[32];  	    //发送时间，格式为:2000-02-01 09:10:10
    char     	 	 senderName[MAXLEN_EMAIL_SENDERNAME];   /* 消息发送者名称 */
	uint8_t          title[MAXLEN_EMAIL_TITLE]; //标题
}hrwfca_emailInfo_t;

//邮件内容
typedef struct{
	char        email[MAXLEN_EMAIL_CONTENT];           /* 消息内容    */
}hrwfca_emailContent_t;

//一封邮件
typedef struct _TEmail
{
	hrwfca_emailInfo_t 		 emailHead;
	hrwfca_emailContent_t 	 emailContent;
}TEmail;

//邮箱
typedef struct _TEmailBox
{
    char        count;    /* Email count */
    char        UnDismantleCount; /* 未读邮件数  */
    TEmail     caBmail[EMAIL_COUNT_WFCA];
}TEmailBox;

//家长锁
typedef struct 
{
	D_U8   Rating;
	D_U16  TimeOutInterval;
    D_U8   pin[5];
} D_WFCAparentlevel;

//---------------HRCA_DISPLAY.H-------------------

/*-----------------------------节目信息-------------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;

//购买的节目信息
//extern hrwfca_serviceEntitles_t d_ServiceEntitles_wfca[ENTITLE_COUNT_WFCA];

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

extern hrwfca_ippBuyInfo_t d_IppBuyInfo_wfca;


/*--------------------------------钱包信息-----------------------------------------*/

//钱包总数
extern uint8_t d_SlotCount;

//钱包ID
extern uint8_t d_SlotID[20];

//充值金额
extern uint32_t ChargeValue;

//钱包信息
//extern hrwfca_slotInfo_t  d_SlotInfo_wfca[20];

/*-------------------------------邮件信息-----------------------------------------*/

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

//邮件头
//extern hrwfca_emailInfo_t d_EmailInfo_wfca[EMAIL_COUNT_WFCA];

//邮件内容
//extern hrwfca_emailContent_t d_EmailContent_wfca;


/*------------------------------智能卡信息-------------------------------------*/
//extern hrwfca_scBasicInfo_t d_ScBasicInfo_wfca;

//---------------END HRCA_DISPLAY.H-------------------

#endif
