/*************************************************************************************************

File Name      :  trca_internal.h

Description    :  

Copyright(C)   :  Haier_IC 2012.05.10

Project Group  :  CA

Author(s)      :  lim

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2014-05-10     GONGQ          created              ---

**************************************************************************************************/
#ifndef _TRCA_INTERNAL_H_
#define _TRCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

//---------------全局变量---------------
//-----------------------------------------------------
//=====================================================
#define CA_MAX_PIN_LENGTH_TRCA      	6U
#define MAX_TASK_NUMBER_TRCA        	       5U
#define MAX_SEMA_NUMBER_TRCA         	25U   //最大信号量个数
#define ENTITLE_COUNT_TRCA                      300
#define EMAIL_COUNT_TRCA                          50	 //邮件，公告最多存储多少封。
#define MSG_MAX_NUM_TRCA	                     (EMAIL_COUNT_TRCA + 1)	//邮件，公告，滚动条提醒。
#define INDEX_MAX_NUM_TRCA                    511
#define SC_MAXLEN_TRCA					 30
#define MAXLEN_EMAIL_TITLE_TRCA             80
#define MAXLEN_EMAIL_CONTENT_TRCA       880
#define TRCA_MAXNUM_OPERATOR			100
#define TRCA_MAXNUM_IPPPRODUCT		20
#define TRCA_MAXNUM_IPPRECORD		100
#define PINCODE_LENGTH_TRCA  			6
#define IPP_COUNT_TRCA 					250
#define TRCA_EXPIRED_DAYS 				14  //授权过期时间
#define OPERATOR_COUNT_TRCA			320  

typedef struct
{
	uint8_t bYear[2];    	/* for example 1998, bYear[0]=19, bYear[1]=98 */
	uint8_t bMonth;      	/* 1 to 12 */
	uint8_t bDay;        	/* 1 to 31 */
	uint8_t bHour;      		 /* 0 to 23 */
	uint8_t bMinute;     	/* 0 to 59 */
	uint8_t bSecond;     	/* 0 to 59 */
} TIMESTAMP;


//卡相关
typedef struct
{
	char CAVersion[SC_MAXLEN_TRCA];
	char SCVersion[SC_MAXLEN_TRCA];
	char SCNumber[SC_MAXLEN_TRCA];
	uint8_t SCRatingLevel[4];
	uint8_t State;	
}hrtrca_scBasicInfo_t;

typedef struct
{
	uint8_t reserve;
}hrtrca_scAddedInfo_t;


//邮件相关
typedef struct{
    	uint8_t importance; 		//重要性： 0－LOW，1－MID 2-HIG  3- URGENCE 
    	uint8_t newEmail;  		//新邮件标记：0－已读邮件；1－新邮件
   	char createtime[32];  		//发送时间，格式为:2000-02-01 09:10:10
	char title[MAXLEN_EMAIL_TITLE_TRCA]; //邮件短内容
	char from_context[MAXLEN_EMAIL_CONTENT_TRCA];		 //来源
}hrtrca_emailInfo_t;

typedef struct{
	char version[32];  		//发送时间
	char emailLength[6]; 		//邮件内容长度
	char email[MAXLEN_EMAIL_CONTENT_TRCA]; //邮件内容
	uint8_t reserved[6];  		//保留
	char title[MAXLEN_EMAIL_TITLE_TRCA]; //邮件短内容
}hrtrca_emailContent_t;

typedef struct
{
   	 uint16_t wTitleLen;
   	 uint8_t  bMsgTitle[80];
  	 uint16_t wDataLen;
   	 uint8_t  bMsgData[880];
    	 uint16_t wIndex;
    	 uint8_t  bType;
    	 uint8_t  bClass;
    	 uint8_t  bPriority;
        uint16_t wPeriod;
        TIMESTAMP sMsgTime;
        TIMESTAMP sCreateTime;
} hrtrca_email_t;


//PIN码相关

//级别设置


//运营商信息
typedef struct{	 

	uint8_t reserve;
}hrtrca_operatorInfo_t; 

//授权信息
typedef struct	
{
	uint32_t prog_id;
	uint32_t prog_remain_days;
    	char prog_right_start_date[11];
    	char prog_right_end_date[11];
   	uint8_t stauts;
}hrtrca_serviceEntitles_t;  

typedef struct
{
	uint8_t reserve;
}hrtrca_detitleInfo_t;

//ipp购买弹出框
typedef struct {
	char ChannelId[6];			//频道号
	char IppRunningNum[11];		//流水号
    	uint8_t  bIppType;   			// 0:ippv; 1:ippt 
   	char  IppCharge[12]; 			// ippv: 单位为x.xx元/次，ippt:单位为x.xx元/ XX 秒,其中 XX的值为IppUnitTime 
    	uint32_t IppUnitTime;			//单位 '秒‘
    	char  PurseBalance[20];		//钱包信息
    	char  IppStart[64];			//起始日期
   	char  IppEnd[64];				//失效日期
}hrtrca_ippBuyInfo_t;

//ipp授权信息
typedef struct { 
    	uint8_t  bProductType;   		// 0:ippv; 1:ippt
    	uint32_t ulRunningNum;
    	char  ulStartTime[64];
    	char  ulEndTime[64];
}hrtrca_viewedIpp_t;

//ipp消费记录
typedef struct {
   	uint8_t  bStateFlag;             	 //状态：  0:支出  1：存入
    	char  ulExchTime[64];        	 //时间:   xxxx.xx.xx-xx:xx:xx
    	char ulExchRunningNum[11];	 //流水号: 10位 如：0000000004
    	uint32_t ulExchValue;			 //金额
    	uint8_t  bContentLen;			 //reserve
    	char  pbContent[34];			 //reserve
}hrtrca_ippRecord_t;

//钱包
typedef struct {
	uint8_t slotId;
    	uint32_t slotCreditLimit;    		 //信用度(点数) 
    	uint32_t balance;    		 	 //已花的点数
}hrtrca_slotInfo_t;

//强制换台
typedef struct {
	uint8_t  bLockFlag;
	uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
}hrtrca_SwitchChannel_t;

//全屏换台
typedef struct {
	uint8_t d_AnnoTitleBuffer[80];  
	uint8_t d_AnnoDataBuffer[1024]; 
}hrtrca_Anno_t;

//===================================================================================================================
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

/*-----------------------------------------授权信息------------------------------------*/
//购买的节目总数
extern uint8_t d_ServiceCount;
//钱包总数
extern uint8_t d_SlotCount;
//钱包ID
extern uint8_t d_SlotID[20];
//IPPV节目总数
extern uint16_t d_IPPVProNum;

#endif

