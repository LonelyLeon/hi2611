#ifndef _ABVCA_INTERNAL_H
#define _ABVCA_INTERNAL_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//#include "abv_ca_types.h"
//---------------全局变量---------------

#define  abvmax_slot	         8//10 
#define  abvdmux_buffer_size          1024      //haoxw

//----------------邮件------------------
#define EMAIL_COUNT_ABVCA  5
#define MAXLEN_EMAIL_FROM_CONTENT 30
#define MAXLEN_EMAIL_TITLE_ABVCA    60
#define ABVCA_MAXLEN_EMAIL_CONTENT 2048
//-----------------结束-----------------


//----------------运营商------------------
#define OPERATOR_COUNT_ABVCA  3
#define MAXLEN_TVSNAME 24
#define ENTITLE_COUNT 				300U
//-----------------结束-----------------

//----------------授权-----------------
#define ENTITLE_COUNT_ABVCA  100
#define FREE_ENTITLE_COUNT_ABVCA  3
#define PPC_ENTITLE_COUNT_ABVCA  1000
#define PPV_ENTITLE_COUNT_ABVCA  100
//-----------------结束-----------------

//----------------消费历史------------------
#define CONSUME_MAX_COUNT    30

//----------------STBID length------------------
#define ABV_STBID_LEN_MAX    30//20  //ABV CA库最长是20，以后CA库有变动，再修改此宏定义
//----------------结束-------------------

//---------------CA库任务总数-----------------
#define MAX_TASK_NUMBER_ABVCA         	2U
//----------------结束-------------------

typedef struct{
	char MailNo[5];
  uint8_t newEmail;  							//新邮件标记：0－新邮件;1－已读邮件
  char SendTime[15];  						//发送时间，格式为:2000-02-01 09:10:10
	char Title[MAXLEN_EMAIL_TITLE_ABVCA]; //邮件短内容
	char SenderName[MAXLEN_EMAIL_FROM_CONTENT];	//来源
}hrabvca_emailInfo_t;


typedef struct{
	uint16_t emailLength; 					//邮件内容长度
	char email[ABVCA_MAXLEN_EMAIL_CONTENT];           //邮件内容
}hrabvca_emailContent_t;


typedef struct{
	char Num[17];/*Card Number*/
	char Name[8];/*Smart card Name*/
	uint8_t Version;/*Smart card version*/
	uint8_t Matl;/*Adult level*/
	char Area[9];/*Aire*/
	uint8_t paired;/*!0:paired 0:No Paired*/
	uint8_t start_time[2];/*BCD Code*/
	uint8_t end_time[2];/*BCD code*/
}hrabvca_scBasicInfo_t;


typedef struct{
	char Provider_PPID[8];  //节目供应商标示
	char Provider_Label[9]; //节目供应商名称
	int32_t balance;          //对应供应商的智能卡余额
}hrabvca_operatorInfo_t;


typedef struct{
       char Label[15];//类型描述
       char Entitle_start_date[15];//频道授权起始日期
       char Entitle_end_date[15];//频道授权截止日期
}hrabvca_freeEntitles_t;

typedef struct{
	uint16_t LinkID;
	char Label[15];//类型描述
       char Entitle_send_date[17];
       char Entitle_start_end_date[35];//频道授权起止日期
}hrabvca_ppcEntitles_t;

typedef struct{
	uint16_t LinkID;
       char Label[15];//类型描述
       char Entitle_send_date[17];
       char Entitle_start_end_date[35];//频道授权起止日期
}hrabvca_ppvEntitles_t;


typedef struct{
	char Consume_Time[11];
	int32_t Consume_Tokens;
}hrabvca_consumeInfo_t;

typedef struct{
	uint8_t IPPV_Type;
	char  IPPV_Time_Price[7];
	char  IPPV_View_Price[7];
	char  IPPV_Name[24];
	char  Pro_Start_Time[17];
	char  Pro_End_Time[17];
	uint8_t  IPPV_ID;	//节目序号
}hrabvca_ippBuyInfo_t;


/*-----------------------------节目信息-------------------------------------------*/

//购买的节目总数
extern uint16_t abv_ServiceCount;
//购买的节目信
extern hrabvca_freeEntitles_t d_FreeEntitles_abvca[FREE_ENTITLE_COUNT_ABVCA];
extern hrabvca_ppcEntitles_t d_PPCEntitles_abvca[PPC_ENTITLE_COUNT_ABVCA];
extern hrabvca_ppvEntitles_t d_PPVEntitles_abvca[PPV_ENTITLE_COUNT_ABVCA];
//弹出框购买ipp节目
extern hrabvca_ippBuyInfo_t d_IppBuyInfo_abvca[2];
//运营商信息
extern uint8_t d_OperatorCount;
extern hrabvca_operatorInfo_t d_OperatorInfo_abvca[OPERATOR_COUNT_ABVCA];

/*-------------------------------邮件信息-----------------------------------------*/
//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;
//邮件头
extern hrabvca_emailInfo_t d_EmailInfo_abvca[EMAIL_COUNT_ABVCA];
//邮件内容
extern hrabvca_emailContent_t d_EmailContent_abvca;
/*------------------------------智能卡信息-------------------------------------*/
//观看级别
extern uint8_t d_ViewRating;
//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;
//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;
//智能卡基本信息
extern hrabvca_scBasicInfo_t d_ScBasicInfo_abvca;

extern uint16_t  d_ConsumeCount;
extern hrabvca_consumeInfo_t d_ConsumeHistory_abvca[CONSUME_MAX_COUNT];


#endif

