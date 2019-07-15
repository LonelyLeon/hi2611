/*************************************************************************************************

File Name      :  dvnca_drv.h

Description    :  

Copyright(C)   :  Haier_IC 2012.5

Project Group  :  CA

Author(s)      :  hanjf

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-05-14     hanjf          created              ---

**************************************************************************************************/
#ifndef _DVNCA_FUN_H_
#define _DVNCA_FUN_H_

#include <stdint.h>
#include "../../ca/camid/include/hrca_config.h"

#if ((EMBED_CA & DVNCA) == DVNCA)
//#include "../ca/dvnca/include/dvn_cak.h"
#include "../ca/dvnca/include/DVN_Type_def.h"
#include "dvnca_internal.h"
#include "dCA.h"
#endif


#define CAT_BUF_SIZE	    1024
#define CAK_BUF_SIZE	    1152
#define CAK_BUF_NUM		    23 //2个是ECM buffer 20个是EMM buffer,1个是Pairing buffer

#define GET_ONE_BIT(ch, n)  ((ch >> n) & 0x01)


#define DVNSEM 1
#if DVNSEM

#define DVN_MAX_SEM 5
typedef struct{
	void 	*sem;
	CA_BOOL	IsUsed;
}sem_t_dvn;

extern sem_t_dvn DVN_RTOS_SEM[DVN_MAX_SEM];
#endif
#define DVNQUEUE 1

#define DVN_MAX_MBOX 10

typedef	struct	dvnQ_s
{
	//reporting_module_t	from_which_module;
	uint16_t       msg_length;
	uint8_t		   *ptrdata;
}dvnQ_t;

typedef struct
{
	uint8_t Data[16];
	uint8_t	Mask[16];
}CAK_FILTER_DATA;

typedef struct
{
  	uint32_t 	msgQ;
	uint16_t 	pid;
 	uint16_t  	tid;
    int32_t     slot;
#if (defined(DVNCA_COS))
    uint8_t     *databuf;  //备份数据用，相同的emm数据不送CA库处理
#endif
}CAK_FILTER;

#define MAX_JET_FILTER	8   //  7   

typedef struct 
{
#if (defined(DVNCA_COS) || defined(D_CA_SUPPORT_DVNCA_COS)) //D_CA_SUPPORT_CDCA_COS宏定义是在project层定义的
    uint8_t	 postion;
    uint32_t duration;
    uint8_t  times;
    char     content[CA_OSD_LEN_DVNCA];
#else
    uint8_t  times;
    char     content[500+1];
#endif
} dvnca_osd_t;

enum
{
	MAIL_MSG=1,
	UPLOAD_MSG	
};


typedef struct
{
	uint8_t   Century;
	uint8_t   YearInCentury;
	uint8_t   Month;
	uint8_t   Day;
	uint8_t   Hour;
	uint8_t   Minute;
	uint8_t   Second;
	uint8_t   mSec;
} CAK_CATime;

//授权纪录
typedef struct
{
    uint8_t  ProductID[2];
    uint8_t  EventID[2];
    CAK_CATime StartTime;
    CAK_CATime EndTime;
} CAK_SubscriptionElement;

//充值纪录 
typedef struct
{
    uint8_t Type;
	uint8_t ID[3];
	float  Price;
	CAK_CATime StartTime;
	uint8_t ConfirmCode[8]; // 64 bit
} CAK_TracRecord;

//IPPV订购记录 
typedef struct {
	uint8_t Product_ID[2];    						//节目号
    uint8_t Reserved[2];							//预留
    uint8_t Price[4];								//价格
    uint8_t Start_Time[8];                          //开始时间
    uint8_t End_Time[8]; 						    //结束时间
} CAK_IPPVSubscriptionRecord;

extern void *CAS_CATQ;  //记录CAK中CAT 的Queue地址
extern  uint32_t KernelTaskId;   //任务索引
extern int32_t TokenChangeIndex; //钱包金额的变更index，默认为0
extern int32_t boolchange;
extern uint8_t g_U8Rating;
extern uint8_t g_NeedGetRating;
extern uint8_t g_DvncaRateMessage;

/*emm、ecm内容指针*/
extern D_CAOrdinaryFinger DVNcaEMMFinger;
extern D_CAOrdinaryFinger DVNcaECMFinger;

/*强制锁定*/
extern D_Ca_SwitchChannel_t dvnca_serviceInfo;
extern D_Ca_Channel_cancel_t dvnca_cType;
/*****************************CA public function*****************************************/

extern CA_BOOL HRDVNCASTB_Init(void);
extern CA_BOOL HRDVNCASTB_Exit(void);
extern CA_BOOL HRDVNCASTB_SCInsert(void);
extern CA_BOOL HRDVNCASTB_SCRemove(void);
extern CA_BOOL HRDVNCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRDVNCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRDVNCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRDVNCA_Init_PMTData(void);
extern void HRDVNCA_MonitorPMT(void);
extern void HRDVNCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRDVNCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRDVNCA_MonitorCAT(void);
extern void HRDVNCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRDVNCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRDVNCASTB_CADataGot(uint8_t u8ReqID, CA_BOOL u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRDVNCASTB_MaskFlash(void);
extern void HRDVNCASTB_UpdateFlash(void);
extern void HRDVNCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRDVNCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRDVNCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
//extern DVN_RTOS_RESULT DVNSTB_RTOS_SendQueue(DVN_RTOS_MSG_QUEUE queueID, UINT8 *messageData ,UINT16 messageSize);
extern void HRDVNCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRDVNCA_HideFinger(uint8_t state);
extern void HRDVNCASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);
extern void HRDVNCASTB_SelectShowBuyMessage(uint8_t bMessage);
//DVNCA 私有接口
extern void HRDVNCAFilter_init(uint8_t LibFilter);
extern void HRDNVCA_ShowImmobileOsdMessage(uint32_t u8Style, char* u8OsdData, uint32_t u32IntervalTime);


/*****************************Dvn private function****************************************/
extern CA_BOOL HRDVNCASTB_SaveBmail(CA_MAIL_T *pdata51);
extern CA_BOOL HRDVNCASTB_Restart(void);
extern uint8_t* HexStringToBin(int8_t* name, uint32_t num);
extern void DVNCA_KernelTask(void);
		
/*********************************************function in menu***************************************/
//--邮件7
extern int32_t HRDVNCASTB_GetEmailCount_Ex(uint16_t* pu16EmailCount, uint16_t* pu16NewEmailCount, uint16_t* pu16EmptyEmailCount);
extern int32_t HRDVNCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRDVNCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrdvnca_emailInfo_t *tEmailInfo);
extern int32_t HRDVNCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrdvnca_emailInfo_t *tEmailInfo);
extern int32_t HRDVNCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrdvnca_emailContent_t *tEmailContent);
extern int32_t HRDVNCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRDVNCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRDVNCASTB_EmailRead(uint16_t u16EmailIdIndex);

//--授权信息10
extern int32_t HRDVNCASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRDVNCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrdvnca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDVNCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrdvnca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDVNCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRDVNCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdvnca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDVNCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrdvnca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDVNCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdvnca_detitleInfo_t *tDetitle);
extern int32_t HRDVNCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrdvnca_detitleInfo_t *tDetitle);
extern int32_t HRDVNCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRDVNCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//DVNCA 私有接口
extern int32_t HRDVNCASTB_ExitEmailListMenu(void);
extern int32_t HRDVNCASTB_ExitServiceEntitlesMenu(void);
extern int32_t HRDVNCASTB_GetAccountRecords(uint16_t *pu16TVSID, uint8_t *pu8Count, hrdvnca_accountRecords_t *taccountRecords);
extern int32_t HRDVNCASTB_ExitAccountRecordsMenu(void);
extern int32_t HRDVNCASTB_ExitIPPVInfoMenu(void);
extern int32_t HRDVNCASTB_ConfirmChangeToken(uint8_t u8Index);
extern int32_t HRDVNCASTB_CancelChangeToken(uint8_t u8Index);
extern void HRDVNCASTB_ClearPromptMessageVariable(void);
extern void HRDVNCASTB_ReInitFilter(void);
extern void HRDVNCASTB_ReReqEmm(void);
extern void HRDVNCASTB_Data_Back(void);
extern void HRDVNCA_Hex64ToDec(uint8_t* ser, char* str);


//--PPV8
extern int32_t HRDVNCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrdvnca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRDVNCASTB_GetIPPVCount(uint16_t u16TVSIdIndex, uint16_t* pu16Count);
extern int32_t HRDVNCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrdvnca_viewedIpp_t *tViewedIpp);
extern int32_t HRDVNCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrdvnca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRDVNCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrdvnca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRDVNCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrdvnca_viewedIpp_t *tViewedIpp);
extern int32_t HRDVNCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRDVNCASTB_SetIpptPeriod(hrdvnca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

//--密码4
extern int32_t HRDVNCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRDVNCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRDVNCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRDVNCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);

//--等级2
extern int32_t HRDVNCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRDVNCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);

//--卡信息7
extern uint16_t HRDVNCASTB_GetScNo(char *sc);
extern int32_t HRDVNCASTB_GetScBasicInfo(hrdvnca_scBasicInfo_t *tPBScInfo);
extern int32_t HRDVNCASTB_GetSCChildParentAttribute(hrdvnca_scAddedInfo_t* tPAScInfo);
extern int32_t HRDVNCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRDVNCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRDVNCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRDVNCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
extern int32_t HRDVNCASTB_GetSTBAttribute(char* tPAScInfo);
//--钱包3
extern int32_t HRDVNCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRDVNCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrdvnca_slotInfo_t *tSlotInfo);
extern int32_t HRDVNCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrdvnca_slotInfo_t *tSlotInfo);

//--工作时间2
extern int32_t HRDVNCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRDVNCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);
/*子母卡信息*/
extern int32_t HRDVNCASTB_GetSmartCardType(int32_t* CardType);
extern int32_t HRDVNCASTB_GetSmartCardID(uint8_t* IDBuffer,uint8_t len);
extern int32_t HRDVNCASTB_GetSmartCardExpireTime(uint8_t u8CardType, uint8_t* DateBuffer,uint8_t len);



//--字母卡管理
extern void CAKCALL_GetMotherChildMsg(UINT32 code);

//--IPPV管理
extern void CAKCALL_GetIPPVStatusMsg(UINT8* Data);
#endif


