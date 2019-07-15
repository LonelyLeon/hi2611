#ifndef _THTFCA_INTERNAL_H_
#define _THTFCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "../../ca/thtfca/include/p4vLibConfigs.h"

#define MAX_SLOT_COUNT            8

//邮件
#define THTFCA_EMAIL_COUNT 		  30

//文件数目
#define THTFCA_FileCount          5

//----------------reply------------------

typedef struct{
    int32_t  resetpinReplayValue;
    int32_t  pinAvailabilityReplayValue;
    uint8_t  pinStateReplayValue;
    uint8_t  getCertificateReplayValue;
    int32_t  setCertificateReplayValue;
    int32_t  seeCertificateReplayValue;
    uint32_t setWorkPeriodReplayValue;
    int32_t  freeWorkPeriodReplayValue;
    uint8_t  setOverdueInfoReplayValue;
    uint8_t  getOverdueInfoReplayValue;

    uint8_t  userBasicInfoReplayFlag;
    uint8_t  operatorInfoReplayFlag;
    uint8_t  entitleInfoReplayFlag;
    uint8_t  resetpinReplayFlag;
    uint8_t  pinAvailabilityReplayFlag;
    uint8_t  pinStateReplayFlag;
    uint8_t  getCertificateReplayFlag;
    uint8_t  setCertificateReplayFlag;
    uint8_t  seeCertificateReplayFlag;
    uint8_t  setWorkPeriodReplayFlag;
    uint8_t  freeWorkPeriodReplayFlag;
    uint8_t  getWorkPeriodReplayFlag;
    uint8_t  setOverdueInfoReplayFlag;
    uint8_t  getOverdueInfoReplayFlag;
}hrthtfca_replyFalg_t;
//----------------结束-------------------

//存储文件用的结构体
typedef struct
{
    char    Name[8];
    char    content[6000];
}hrthtfca_fileInfo_t;


//邮件总数和新邮件数
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hrthtfca_emailGeneral;

//存储邮件用的结构体
typedef struct{
	uint8_t	     state;			//新邮件标记：0－已读邮件；1－新邮件
	info_mail_t  email;			//邮件
}THTFemail;

typedef struct{
    uint8_t   importance; 			 //重要性： 0－普通，1－重要 
    uint8_t   newEmail;  			 //新邮件标记：0－已读邮件；1－新邮件
    char      deliveryTime[22];  	 //发送时间，格式为:2000-02-01 09:10:10
	char      title[102];            //邮件短内容	
}hrthtfca_emailInfo_t;

typedef struct{
	char     emailContent[1024];           //消息内容	
}hrthtfca_emailContent_t;


typedef struct
{
    char     userid[20];            //用户号
    char     systermid[12];         //主系统号
    uint8_t  defaultPINFlag;        //默认PIN码标识
    uint8_t  certificate;           //许可成人级别
    uint8_t  userState;             //用户状态（1禁用）（0启用）
    char     area[22];              //区域信息
    char     casProviderName[22];   //CA厂商
    char     calibver[110];         //库版本
}hrthtfca_userBasicInfo_t;


typedef struct
{
    char     operatorName[22];       //运营商名
    char     sub_systermid[12];      //当前CA子系统号
}hrthtfca_operatorInfo_t;

typedef struct
{
    char     id[6];
    uint8_t  type;
    char     name[23];
    char     expired[22];
}hrthtfca_serviceEntitles_t;



extern uint16_t NewstreamPID[2];//基本流PID
extern emm_pid_list_t EMMPidList;
extern hrthtfca_replyFalg_t thtfcaReply;

//运营商信息
extern uint8_t d_OperatorCount;

//观看级别
extern uint8_t d_ViewRating;

//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//邮件总数
extern uint16_t d_EmailCount;
//未读邮件个数
extern uint16_t d_NewEmailCount;
//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

#endif


