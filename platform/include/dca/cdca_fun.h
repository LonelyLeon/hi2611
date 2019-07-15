/*************************************************************************************************

File Name      :  cdca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _CDCA_FUN_H_
#define _CDCA_FUN_H_

#include <stdint.h>
#include "cdca_internal.h"


/************************************End of Includes*********************************************/

/*****************************CA public function*****************************************/

extern unsigned char HRCDCASTB_Init(void);
extern unsigned char HRCDCASTB_Exit(void);
extern unsigned char HRCDCASTB_SCInsert(void);
extern unsigned char HRCDCASTB_SCRemove(void);
extern void HRCDCASTB_ServiceClear(uint8_t flag);
extern unsigned char HRCDCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRCDCA_Init_PMTData(void);
extern void HRCDCA_MonitorPMT(void);
extern void HRCDCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRCDCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRCDCA_MonitorCAT(void);
extern void HRCDCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRCDCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRCDCASTB_CADataGot(uint8_t u8ReqID, unsigned char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRCASTB_MaskFlash(void);
extern void HRCASTB_UpdateFlash(void);
extern void HRCDCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRCDCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRCDCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRCDCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRCDCASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);
extern void HRCDCASTB_ShowFinger(uint8_t bType);
extern void HRCDCASTB_ShowIPPV(uint16_t EcmPID, void *ippvBuyInfo);


/*****************************function in menu***************************************/

//--邮件7
extern int32_t HRCDCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRCDCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrcdca_emailInfo_t *tEmailInfo);
extern int32_t HRCDCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrcdca_emailInfo_t *tEmailInfo);
extern int32_t HRCDCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrcdca_emailContent_t *tEmailContent);
extern int32_t HRCDCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRCDCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRCDCASTB_EmailRead(uint16_t u16EmailIdIndex);

//--授权信息10
extern int32_t HRCDCASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRCDCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrcdca_operatorInfo_t *tOperatorInfo);
extern int32_t HRCDCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrcdca_operatorInfo_t *tOperatorInfo);
extern int32_t HRCDCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRCDCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrcdca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRCDCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrcdca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRCDCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrcdca_detitleInfo_t *tDetitle);
extern int32_t HRCDCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrcdca_detitleInfo_t *tDetitle);
extern int32_t HRCDCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRCDCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);

//--PPV7
extern int32_t HRCDCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrcdca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRCDCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrcdca_viewedIpp_t *tViewedIpp);
extern int32_t HRCDCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrcdca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRCDCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrcdca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRCDCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrcdca_viewedIpp_t *tViewedIpp);
extern int32_t HRCDCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRCDCASTB_SetIpptPeriod(hrcdca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

//--密码4
extern int32_t HRCDCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRCDCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRCDCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRCDCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);

//--等级2
extern int32_t HRCDCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRCDCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);

//--卡信息10
extern uint16_t HRCDCASTB_GetScNo(char* sc);
extern int32_t HRCDCASTB_GetScBasicInfo(hrcdca_scBasicInfo_t *tPBScInfo);
extern int32_t HRCDCASTB_GetSCChildParentAttribute(hrcdca_scAddedInfo_t* tPAScInfo);
extern int32_t HRCDCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRCDCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRCDCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRCDCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
extern int32_t HRCDCASTB_GetScInfo(int8_t *pSc);
extern int32_t HRCDCASTB_GetScCosVer(uint32_t *pScCosVer);
extern int32_t HRCDCASTB_GetCAVer(uint8_t *pCAVer);
extern int32_t HRCDCASTB_GetCAManuName(int8_t *pCAMaunNameVer);


//--钱包3
extern int32_t HRCDCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRCDCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrcdca_slotInfo_t *tSlotInfo);
extern int32_t HRCDCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrcdca_slotInfo_t *tSlotInfo);

//--工作时间2
extern int32_t HRCDCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRCDCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);

#endif


