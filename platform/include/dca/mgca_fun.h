/*************************************************************************************************

File Name      :  mgca_drv.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/

/*******************************Includes************************************************/
#ifndef _MGCA_FUN_H_
#define _MGCA_FUN_H_

#include <stdint.h>
#include "mgdef.h"
#include "mgca_internal.h"

/***********************************************************************************/
#define OSD_CONTENT_LEN						130
#define EMAIL_CONTENT_LEN_MGCA				520//513
#define EMAIL_TOPIC_LEN						(21)
#define EMAIL_ADDR_LEN						(21)
#define EMAIL_TIME_LEN						6
#define EMAIL_HEAD_LEN			(EMAIL_TOPIC_LEN + EMAIL_ADDR_LEN + EMAIL_TIME_LEN + 6)
#define EMAIL_BOOT_FLAG						0x55

typedef struct email_head_s
{
	uint8_t		topic[EMAIL_TOPIC_LEN];
	uint8_t		addr[EMAIL_ADDR_LEN];		//addresser
	uint8_t		time[EMAIL_TIME_LEN];		//0xYYYYMMDDHHMM
	uint8_t	bRead;

	uint16_t		length;						//content length
	uint16_t	id;
 } email_head_t;

	
typedef struct email_s
{
	email_head_t mailhead;
		
	uint8_t		pContent[EMAIL_CONTENT_LEN_MGCA];
	
 } email_t;

typedef struct email_boot_s
{
	uint8_t valid_flag;		//FALSH email 存储信息有效标志 0x55 表示flash中的email信息有效
	uint8_t nums;			//email 个数
	uint8_t reserved[14];	//保留备用
}email_boot_t;

typedef union email_param_s
{
	uint8_t nums;
	uint8_t index;
	uint16_t id;

	email_head_t head;
	
	struct
	{
		uint8_t *pHead;
		uint8_t *pBody;
	}email;
	
	struct
	{
		uint8_t *pContent;
	}msg;
	struct
	{
		uint8_t Mode;
		uint8_t Times;
		uint8_t remain;
		uint8_t *pContent;
	}osd;
 } email_param_t;

typedef enum
{
	EMAIL_ALL,
	EMAIL_READ,
	EMAIL_FIRST,
	EMAIL_ID,
	EMAIL_Index
}EMAIL_DEL_TYPE;

typedef enum
{
	ERR_SUCCESS = 0,
	ERR_FAILED,	
	ERR_NO_MSG,		//消息队列空
	ERR_NO_MEM,		//空间不足
	ERR_NOT_EXIST,		//邮件不存在
	ERR_DATA_LEN,		//邮件正文长度错误
	ERR_NULL_POINTER,	//空指针
	ERR_SAME_EMAIL	//重复的邮件
}EMAIL_ERR;

typedef enum
{
	EMAIL_DATA_INIT = 1,
	EMAIL_GET_NUM,
	EMAIL_GET_HEAD,
	EMAIL_GET_BODY,
	EMAIL_ADD_NEW,
	EMAIL_DEL_ALL,
	EMAIL_DEL_Index,
	EMAIL_DEL_FIRST,
	EMAIL_DEL_ID,	
	EMAIL_BACKUP,
	MSG_ADD,
	MSG_GET,
}EMAIL_OP_TYPE;



typedef enum
{
    SMARTCARD_INSERT,
    SMARTCARD_REMOVE
} sc_state_t;

typedef struct ca_ctrl_s
{
	unsigned char	bRegister;
	MG_STATUS   RegisterStatus;
	
	uint8_t		EcmState;
	uint8_t		EcmMdlSlot;
	uint8_t		EcmSecSlot;
	uint16_t		EcmPid;

	uint8_t		EmmState;
	uint8_t		EmmMdlSlot;	
	uint8_t		EmmSecSlot;
	uint16_t		EmmPid;

	uint16_t	CasID;
	uint8_t		CatVersion;
	uint8_t		CatSecSlot;
	uint8_t		PmtSecSlot;
 } ca_ctrl_t;

extern unsigned char bNowPreviewState;
extern unsigned char bLastPreviewState;
extern uint8_t Emailupd;//用于控制是否显示邮件图标
extern uint8_t hasShowIppv;

/*****************************CA public function*****************************************/

extern unsigned char HRMGCASTB_Init(void);
extern unsigned char HRMGCASTB_Exit(void);
extern unsigned char HRMGCASTB_SCInsert(void);
extern unsigned char HRMGCASTB_SCRemove(void);
extern void HRMGCASTB_ServiceClear(uint8_t lag);
extern unsigned char HRMGCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRMGCA_Init_PMTData(void);
extern void HRMGCA_MonitorPMT(void);
extern void HRMGCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRMGCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRMGCA_MonitorCAT(void);
extern void HRMGCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRMGCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRMGCASTB_CADataGot(uint8_t u8ReqID, unsigned char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRMGCASTB_MaskFlash(void);
extern void HRMGCASTB_UpdateFlash(void);
extern void HRMGCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRMGCASTB_ServiceChangeState(uint8_t u8Start, uint8_t u8State);
extern void HRMGCASTB_DataReadyNotify(uint8_t slot, uint8_t *u8Data, uint16_t u16DataLen); 		


/*****************************MG private function****************************************/

extern uint8_t HRCA_Compose_FilterValues(uint8_t byReqID, uint8_t* filter_t, uint8_t* mask_t, uint8_t *fmlenth);
extern uint8_t Email_GetNum(void);
extern void HRCA_GetOSD(char *Osd) ;
extern uint16_t HRCA_GetOSDTime(void) ;
extern void MGCA_GetSerial(uint8_t * buffer, uint8_t length);
extern void MGCA_StoreSerial(uint8_t * buffer, uint8_t length);
extern uint8_t HREmail_Operater(EMAIL_OP_TYPE type, const email_param_t *pIn, email_param_t *pOut);
extern uint16_t HRGet_RecentExpireDay(void);
extern uint32_t HRGet_ChargeAmount(void); 
extern void HRMGCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRMGCASTB_TimerShowBuyMessage(uint8_t bMessage, uint32_t time);
extern void HRMGCASTB_ShowIPPV(uint16_t EcmPID, void* ippvBuyInfo);

/*****************************MG menu function****************************************/
//--邮件7
extern int32_t HRMGCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);//----------邮件----------- 
extern int32_t HRMGCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrmgca_emailInfo_t *tEmailInfo);
extern int32_t HRMGCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrmgca_emailInfo_t *tEmailInfo);
extern int32_t HRMGCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrmgca_emailContent_t *tEmailContent);
extern int32_t HRMGCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);//emailIndex有效，只能单个删除，注意emailIndex从0开始
extern int32_t HRMGCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRMGCASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRMGCASTB_GetOperatorIds(uint16_t *pu16TVSId);
extern int32_t HRMGCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrmgca_operatorInfo_t *tOperatorInfo);
extern int32_t HRMGCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrmgca_operatorInfo_t *tOperatorInfo);
extern int32_t HRMGCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRMGCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrmgca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRMGCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrmgca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRMGCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrmgca_detitleInfo_t *tDetitle);
extern int32_t HRMGCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrmgca_detitleInfo_t *tDetitle);
extern int32_t HRMGCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRMGCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//--PPV4
extern int32_t HRMGCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrmgca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRMGCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrmgca_viewedIpp_t *tViewedIpp);
extern int32_t HRMGCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrmgca_viewedIpp_t *tViewedIpp);
extern int32_t HRMGCASTB_InquireBookIppOver(uint16_t ecmPid);
//--密码4
extern int32_t HRMGCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRMGCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRMGCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRMGCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--等级2
extern int32_t HRMGCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRMGCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);
//--卡信息6
extern uint16_t HRMGCASTB_GetScNo(char *sc);
extern int32_t HRMGCASTB_GetScBasicInfo(hrmgca_scBasicInfo_t *tPBScInfo);
extern int32_t HRMGCASTB_GetSCChildParentAttribute(hrmgca_scAddedInfo_t *tPAScInfo);
extern int32_t HRMGCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);//以下暂空
extern int32_t HRMGCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRMGCASTB_STBScReadFeedData(uint16_t u16TVSId, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRMGCASTB_STBScWriteFeedData(uint16_t u16TVSId, uint8_t* pu8FeedData, uint8_t u8Len );
//--钱包3
extern int32_t HRMGCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRMGCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t *u8SlotId, hrmgca_slotInfo_t *tSlotInfo);
extern int32_t HRMGCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrmgca_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRMGCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t* pu8EndMin, uint8_t *pu8EndSec,uint8_t* pu8Pin);
extern int32_t HRMGCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);



#endif


