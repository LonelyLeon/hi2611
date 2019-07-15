#ifndef _THTFCA_INTERNAL_H_
#define _THTFCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "../../ca/thtfca/include/p4vLibConfigs.h"

#define MAX_SLOT_COUNT            8

//�ʼ�
#define THTFCA_EMAIL_COUNT 		  30

//�ļ���Ŀ
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
//----------------����-------------------

//�洢�ļ��õĽṹ��
typedef struct
{
    char    Name[8];
    char    content[6000];
}hrthtfca_fileInfo_t;


//�ʼ����������ʼ���
typedef struct{
	uint16_t emailCount;
	uint16_t newEmail;
}hrthtfca_emailGeneral;

//�洢�ʼ��õĽṹ��
typedef struct{
	uint8_t	     state;			//���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	info_mail_t  email;			//�ʼ�
}THTFemail;

typedef struct{
    uint8_t   importance; 			 //��Ҫ�ԣ� 0����ͨ��1����Ҫ 
    uint8_t   newEmail;  			 //���ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
    char      deliveryTime[22];  	 //����ʱ�䣬��ʽΪ:2000-02-01 09:10:10
	char      title[102];            //�ʼ�������	
}hrthtfca_emailInfo_t;

typedef struct{
	char     emailContent[1024];           //��Ϣ����	
}hrthtfca_emailContent_t;


typedef struct
{
    char     userid[20];            //�û���
    char     systermid[12];         //��ϵͳ��
    uint8_t  defaultPINFlag;        //Ĭ��PIN���ʶ
    uint8_t  certificate;           //��ɳ��˼���
    uint8_t  userState;             //�û�״̬��1���ã���0���ã�
    char     area[22];              //������Ϣ
    char     casProviderName[22];   //CA����
    char     calibver[110];         //��汾
}hrthtfca_userBasicInfo_t;


typedef struct
{
    char     operatorName[22];       //��Ӫ����
    char     sub_systermid[12];      //��ǰCA��ϵͳ��
}hrthtfca_operatorInfo_t;

typedef struct
{
    char     id[6];
    uint8_t  type;
    char     name[23];
    char     expired[22];
}hrthtfca_serviceEntitles_t;



extern uint16_t NewstreamPID[2];//������PID
extern emm_pid_list_t EMMPidList;
extern hrthtfca_replyFalg_t thtfcaReply;

//��Ӫ����Ϣ
extern uint8_t d_OperatorCount;

//�ۿ�����
extern uint8_t d_ViewRating;

//���ܿ�������ʼʱ��
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//���ܿ���������ʱ��
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

#endif


