/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-11-02      lim            created              ---
1.1		   2013-03-06	   lim			  modify               ---

*************************************************************************************************/

#ifndef INTERNAL_H_
#define INTERNAL_H_

#include <stdint.h>

/*复位应答*/
#define SPECIFIC_ID							0x8648	   			//新光公司的特征ID
//#define INTERFACE_VER					0x0324	   			//本卡与STB接口版本号3.24
#define NOT_REGISTER						0xff	   			//卡尚未入网注册
#define NOT_BOUNDED						0x00	   			//卡尚未绑定
#define CARD_BOUNDED					0x80	   			//卡已经绑定

//#define CA_MAX_PIN_LENGTH       		6U 					//为了编译通过，实际的数值有待确
#define EMAIL_COUNT_XGCA 				50U
#define XGMAXLEN_EMAIL_CONTENT 		1024U
#define XGMAXLEN_EMAIL_SENDERNAME 	256U
#define XGMAXLEN_EMAIL_TITLE	 		256U				
#define MAXLEN_SHORT_MSG				512U				//短消息滚动条


//reserve
#define OPERATOR_COUNT_XGCA			1U
#define ENTITLE_COUNT_XGCA				256U

//系统id
typedef struct{
 	
	uint16_t SysId;
	uint16_t SubSysId;
}systemId;


//智能卡信息
typedef struct
{
	uint8_t 	cosVersion[6];
	uint8_t 	cardId[18];
	uint8_t 	cardTag;  				//1为母卡，其他为子卡
	uint8_t     Date[16];	  			//UTC_time
	uint8_t	    Time[16];	 			//UTC_time
	uint8_t 	boundStatus;			//是否绑定：1：绑定   0：未绑定
    uint8_t 	netid[10];
	uint8_t 	casid[10];
	uint8_t 	areano[10];
	uint8_t 	groupno[10];
	uint8_t 	nitfreq[10];
	uint8_t 	status;
	uint8_t 	viewlv;
	uint8_t 	userid[10];		//Use_ID     4byte//用户的编号，所有子卡，母卡的此号相同
	uint8_t 	cardtype;		//卡的使用序号，=1为母卡，大于1为子卡
	uint8_t 	pincode[8];		//PIN     2byte 为0时不处理
}hrxgca_scBasicInfo_t;

typedef struct
{
	uint8_t 	header[2];		 //0
	uint8_t 	cardId[8];		 //2
	uint8_t 	cosversion[4];   //10				
	uint8_t     supercasid[4];	 //14
	uint8_t	    netid[4];	 	//18
	uint8_t 	areacode[4];		//22
    uint8_t 	groupno[4];		//26
	uint8_t 	nitfreq[4];		//30
	uint8_t 	pincode[2];		//34
	uint8_t 	status;			//36
	uint8_t 	userid[4];		//37Use_ID     4byte//用户的编号，所有子卡，母卡的此号相同
	uint8_t 	cardtype;		//41 卡的使用序号，=1为母卡，大于1为子卡
	uint16_t 	mcardata;		//42
	uint16_t 	mcaddhour;		//44
	uint8_t 	freserve[2];		//46
	uint8_t 	encdck[16];		//48
	uint8_t 	idctrlstatus[2];  //64
	uint8_t 	subendtime[4];	  //66 保存在&ppc33entitle[0x8b]
	uint32_t 	substbtime;	  //70
	uint8_t 	edreserve[6];	  //74
}hrxgcos_Info_t;


//IPP弹出购买框
typedef struct
{
	uint16_t price;  					//分
	uint32_t purseBalance; 			//分
	uint8_t  startDate[12];			//MJD
	uint8_t  startTime[12];			//BCD
	uint8_t  endDate[12];  			//MJD
	uint8_t  endTime[12];		      //BCD

}hrxgca_ippBuyInfo_t;

//日期
typedef struct
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
}hrxgca_Date_t;

//时间
typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}hrxgca_Time_t;

//ppc授权情况列表
typedef struct{
	uint8_t 	ppcId;
	uint8_t    ppcEndDate[16];
	uint8_t 	ppcStatus;				//为0表示正常授权，为1表示强制开通，为2表示强制关断

}hrxgca_serviceEntitles_t;

//子母卡信息
//typedef struct
//{
//	uint8_t 	cardTag;  		   //1为母卡，其他为子卡
//	uint8_t      Date[16];	  	   //UTC_time
//	uint8_t	     Time[16];	 	   //UTC_time
//	uint8_t 	boundStatus;	   //是否绑定：1：绑定   0：未绑定
//}hrca_scInfo_t;

//邮件头
typedef struct{
	uint16_t	emailId;
	uint8_t	hasRead;					      			 	// 1:已读 0：未读
	uint8_t 	createTime[24];							//UTC_time
	uint8_t 	sourceLong;								//来源长度
	uint8_t	source[XGMAXLEN_EMAIL_SENDERNAME];	//来源
	uint8_t 	captionLong;								//标题长度
	uint8_t  	title[XGMAXLEN_EMAIL_TITLE];				//标题

}hrxgca_emailInfo_t;

//邮件内容
typedef struct{
	uint16_t 	emailLong;									//内容长度
	uint8_t	email[XGMAXLEN_EMAIL_CONTENT];			//内容

}hrxgca_emailContent_t;

//邮件
typedef struct
{	
	hrxgca_emailInfo_t 	   emailHead;
	hrxgca_emailContent_t   emailContent;
}hrxgca_email_t;

//调制方式
typedef enum
{
	QPSK,	   //0
	QAM16,	   
	QAM32,	   
	QAM64,	   //3
	QAM128,	   //4
	QAM256,
}hrxgca_modulation_t;

//区域限制
typedef struct
{
	uint32_t 	Frequency;			//频率 Hz
	uint32_t 	SymbolRate;		//符号率 bps
	uint8_t	Modulation;			//调制方式

}hrxgca_zoneRestrict_t;

//-------------------------RESERVE----------------------------------


//电子钱包
typedef struct
{
	uint8_t reserve;

}hrxgca_slotInfo_t;

//运营商信息
typedef struct{	

	uint8_t reserve;

}hrxgca_operatorInfo_t; 

typedef struct
{
	uint8_t reserve;

}hrxgca_scAddedInfo_t;

//IPP授权信息
typedef struct
{
	uint8_t reserve;

}hrxgca_viewedIpp_t;	

//反授权
typedef struct
{
	uint8_t reserve;

}hrxgca_detitleInfo_t;


typedef struct {
	uint8_t reserve;
}hrxgca_SwitchChannel_t;

//------------------DEFINED IN HRCA_DISPLAY.H--------------------
//购买的节目总数
extern uint8_t d_ServiceCount;

/*extern hrxgca_serviceEntitles_t d_ServiceEntitles_xgca[ENTITLE_COUNT_XGCA];*/
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

extern hrxgca_ippBuyInfo_t d_IppBuyInfo_xgca;
//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

/*extern hrxgca_emailInfo_t d_EmailInfo_xgca[EMAIL_COUNT_XGCA];*/

/*extern hrxgca_emailContent_t d_EmailContent_xgca;*/

extern hrxgca_scBasicInfo_t d_ScBasicInfo_xgca;

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

#endif
