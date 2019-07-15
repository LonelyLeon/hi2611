#ifndef _CTICA_INTERNAL_H
#define _CTICA_INTERNAL_H

#include "../../ca/ctica/include/ctiapi.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//---------------全局变量---------------


#define HRUSIFFUNCPOSTFIX

#define CTIMAX_TASK_NUMBER              9U

#define CA_MAX_PIN_LENGTH_CTICA       	4U

//----------------邮件------------------
#define EMAIL_COUNT_CTICA  30
#define MAXLEN_EMAIL_SENDERNAME_CTICA 32
#define MAXLEN_EMAIL_SHORT_CONTENT_CTICA 256
#define MAXLEN_EMAIL_FROM_CONTENT_CTICA 256
#define MAXLEN_EMAIL_TITLE_CTICA 32
#define MAXLEN_EMAIL_CONTENT_CTICA 2048
//-----------------结束-----------------


//----------------运营商------------------
#define OPERATOR_COUNT_CTICA     8
#define MAXLEN_TVSNAME_CTICA 24
#define ENTITLE_COUNT_CTICA         300U
//-----------------结束-----------------

//----------------IPPV------------------
#define IPP_COUNT_CTICA 					250U

#define MAXLEN_PRODUCT_NAME_IPP_CTICA 300

//----------------结束-------------------


//----------------reply------------------

typedef struct{
	uint8_t checkPinQueryReplyValue;
	uint8_t changePinQueryReplyValue;
	uint8_t ippvNotifyValue;
	uint8_t ippvQueryReplyValue;
	uint8_t scBasicInfoReplayValue;
	uint8_t ppidQueryReplyValue;
	uint8_t ppidInfoQueryReplyValue;
	uint8_t ppvListInfoQueryReplyValue;
	uint8_t ippvListInfoQueryReplyValue;
	uint8_t setParentalQueryReplyValue;
	uint8_t userViewQueryReplyValue;	
	
	uint16_t checkPinQueryReplyFlag;
	uint16_t changePinQueryReplyFlag;
	uint16_t ippvQueryReplyFlag;
	uint16_t scBasicInfoReplayFlag;
	uint16_t ppidQueryReplyFlag;
	uint16_t ppidInfoQueryReplyFlag;
	uint16_t ppvListInfoQueryReplyFlag;
	uint16_t ippvListInfoQueryReplyFlag;
	uint16_t setParentalQueryReplyFlag;
	uint16_t userViewQueryReplyFlag;
}hrctica_replyFalg_t;

//----------------结束-------------------


typedef struct{
    uint8_t importance; 						//重要性： 0－普通，1－重要 
    uint8_t newEmail;  							//新邮件标记：0－已读邮件；1－新邮件
    char createtime[40];  						//发送时间，格式为:2000-02-01 09:10:10
	char title_context[MAXLEN_EMAIL_SHORT_CONTENT_CTICA]; //邮件短内容
	char from_context[MAXLEN_EMAIL_FROM_CONTENT_CTICA];	//来源
}hrctica_emailInfo_t;


typedef struct{
	uint8_t version[12];  						//发送时间
	uint8_t emailLength[6]; 					//邮件内容长度
	char email[MAXLEN_EMAIL_CONTENT_CTICA];           //邮件内容
	uint8_t reserved[6];  						//保留
}hrctica_emailContent_t;


typedef struct{
	uint8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];
	uint8_t provName[MAXLEN_TVSNAME_CTICA];
	uint8_t id[3];
	char label[17];
	uint8_t usedstatus;
	uint8_t credit_deposit[4];
	char credit_date[11];
	uint8_t prog_right[65];
	char prog_right_start_date[11];
	char prog_right_end_date[11];
}hrctica_operatorInfo_t;


  typedef struct{
	uint8_t id[3];
	char label[17];
	uint8_t usedstatus;
	uint8_t credit_deposit[4];
	char credit_date[11];
	uint8_t prog_right[65];
	char prog_right_start_date[11];
	char prog_right_end_date[11];
}hrctica_serviceEntitles_t;


typedef struct{
    uint8_t newDetitle;     					//反授权标记：0－未读；1－已读
    uint8_t Detitle[12];    					//反授权
}hrctica_detitleInfo_t;


typedef struct{
	uint8_t ippvBuyFlag;						//标志按P(==8)或者按T(==1)购买,用于封装命令送库
	uint8_t ippvProgNum[4];						//频道号,用于封装命令送库
	int8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];			//密码
	uint8_t isIppv;
	uint8_t isIppt;
	char operatorId[10];
	char operatorLabel[17];
	char ippvPrice[13];                        //单位:元/节目
	char ipptPrice[13];                        //单位:元/分钟
}hrctica_ippBuyInfo_t;


typedef struct{
	uint8_t pinCode[CA_MAX_PIN_LENGTH_CTICA];
	uint8_t isPpv;
	uint8_t isIppv;
	uint8_t ppvListPage;						
	int8_t	ppvProgCount;
	char ppvStartProgNumber[256][4];
	char ppvEndProgNumber[256][4];    
	char ippvListPage;
	char ippvProgCount;
	char ippvProgNumber[32][4];
}hrctica_viewedIpp_t;	


typedef struct{
	char cardnumber[8];    //cardnumber[22]
    uint8_t scstatus;    //scstatusstatus：智能卡当前状态
						//. ‘0’，智能卡状态正确
						//. ‘1’，未插入智能卡
						//. ‘2’，智能卡硬件错误
						//. ‘4’，智能卡软件错误
						//. ‘6’，子卡认证失败
						//. ‘7’，子卡认证成功
						//. ‘8’，母卡验证失败
    uint8_t usedstatus;    //usedstatus0，智能卡有效；1，智能卡暂停；2，智能卡被取消。
    uint8_t systemid[2];    //CA系统标识
    uint8_t ecmsubsysid[2];    //ECM子系统标识
    uint8_t emmsubsysid[2];    //EMM子系统标识
    char cosversion[9];    //智能卡的版本号
    char cardlabel[17];    //智能卡的类型描述
    char issuetime[17];    //发卡时间
    char expiretime[17];    //智能卡有效期截止时间
    uint8_t parentalrating;    //智能卡父母锁控制级别。0，无限制；4~18为年龄
    uint8_t groupcontrol;    //节目分组收索控制代码
    uint8_t antimovectrl[3];    //区域控制代码，3字节数据
    uint8_t smartcard_type;    //0，智能卡为母卡；1，智能卡为子卡；2，智能卡类型错误
    uint8_t smartcard_matching;    //智能卡配对状态
    //‘0’，智能卡未配对
	//. ‘1’，智能卡已配对
	//. ‘5’，智能卡未注册STB Number
	//. ‘7’，智能卡与STB不匹配
    uint8_t stb_ird_matching;    //机顶盒配对状态
	//. ‘2’，STB未配对
	//. ‘3’，STB已配对
	//. ‘6’，STB未注册STB Number
}hrctica_scBasicInfo_t;


  typedef struct{
	uint8_t cardstatus;
	char childCardInfoVerifyStartTime[8];    //子卡认证时间
    char childCardInfoWorkPeriod[2];         //子卡工作周期
    char childCardInfoMotherUa[5];     	 	//子卡所属母卡UA
    char caCoreVersion[30];					//CA内核版本
	uint8_t securityInfo_id_len;    	  	 	//id_len
    uint8_t securityInfo_stb_id[16];     	   //stb_id[16]
    uint8_t securityInfo_sc_id[16];     	  //sc_id[16]
}hrctica_scAddedInfo_t;


typedef struct {
	uint8_t slotId;
    uint8_t slotCreditLimit[12];    //信用度(点数) 
    uint8_t balance[12];    		//已花的点数
}hrctica_slotInfo_t;


typedef struct{
	uint8_t id[3];				//PPID
	uint8_t password[4];		//密码
}hrctica_ppidDetailInfo_t;		//用于授权信息菜单进入某一PPID条目


typedef struct{
	int8_t ppv_start_prog_number[12];
	int8_t ppv_end_prog_number[12];
}hrctica_ppvRecord_t;


typedef struct {
	int8_t ppv_list_page[9];						//页数(四位u8数转成字符串需要9位来存)
	int8_t ppv_prog_count[9];						//PPV组数
	hrctica_ppvRecord_t ppv_record[32];	
}hrctica_ipp_t;								//ppv列表显示规范字符串结构体
//------------------------

 typedef struct
{
    int8_t ippv_prog_number[12];
}hrctica_ippRecord_t;

typedef struct {
	int8_t ippv_list_page[3];					//页数
	int8_t ippv_prog_count[3];					//节目个数
	hrctica_ippRecord_t ippv_record[32];			//节目号
}hrctica_ippv_t;									//ippv列表显示规范字符串结构体

//--------------------


typedef struct
{
	uint8_t count;
	hrctica_operatorInfo_t info[MAX_PPID_NUM];
}hrctica_operator_t;//  类似于CTI_PPidNotify_t;，用来放


//-------------------------------------

typedef struct
{
	uint8_t email_status; //email的状态，0:已读，1:未读
	CTI_CABmailInfo_t email_info; //email的信息
}hrctica_email_t; //  此结构体用于存储email使用


typedef struct {
    uint16_t LockSerID;
	uint16_t LockNetworkID;
	uint16_t LockTSID;
	uint16_t LockFre;
	uint16_t LockMode;
	uint16_t LockSymbol;
}hrctica_SwitchChannel_t;

extern uint32_t StreamNum;
extern uint8_t StreamFlag;
extern hrctica_viewedIpp_t d_ViewedIPPV_ctica;
extern hrctica_ippBuyInfo_t d_IppBuyInfo_ctica;
//观看级别
extern uint8_t d_ViewRating;
//运营商信息
extern uint8_t d_OperatorCount;
//运营商编号
extern uint16_t d_TVSId[5];
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

extern uint32_t ctiTaskIdTable[CTIMAX_TASK_NUMBER];

#endif

