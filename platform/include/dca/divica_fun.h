/*************************************************************************************************

File Name      :  Divica_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  lim

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-11-16     lim          created              ---

**************************************************************************************************/

/*******************************Includes************************************************/


#ifndef _DIVICA_FUN_H_
#define _DIVICA_FUN_H_

#ifdef GLOBAL_H
#define EXTERN 
#else
#define EXTERN extern
#endif

#include <stdint.h>
#include "divica_internal.h"

/***********************************************************************************/
extern uint32_t      DivicaTaskIdTable[DIVICA_MAX_TASK_NUMBER];

/*****************************CA public function*****************************************/

extern unsigned char HRDIVICASTB_Init(void);
extern unsigned char HRDIVICASTB_Exit(void);
extern unsigned char HRDIVICASTB_SCInsert(void);
extern unsigned char HRDIVICASTB_SCRemove(void);
extern void HRDIVICASTB_ServiceClear(uint8_t flag);
extern unsigned char HRDIVICASTB_SysIDCheck(uint16_t u16SysID);
extern void HRDIVICA_Init_PMTData(void);
extern void HRDIVICA_MonitorPMT(void);
extern void HRDIVICASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRDIVICASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRDIVICA_MonitorCAT(void) ;
extern void HRDIVICASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRDIVICASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRDIVICASTB_CADataGot(uint8_t u8ReqID, unsigned char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRDIVICASTB_MaskFlash(void);
extern void HRDIVICASTB_UpdateFlash(void);
extern void HRDIVICASTB_OsdMsgOver(uint16_t u16Time);
extern void HRDIVICASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRDIVICASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRDIVICASTB_ShowBuyMessage(uint8_t bMessage);
/*****************************Divi private function***************************************/

extern uint16_t DIVI_GetCurr_NetWorkId(void);   
extern uint16_t DIVI_GetCurr_TSID(void);

/*****************************function in menu******************************************/
//--邮件7
extern int32_t HRDIVICASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRDIVICASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrdivica_emailInfo_t *tEmailInfo);
extern int32_t HRDIVICASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrdivica_emailInfo_t *tEmailInfo);
extern int32_t HRDIVICASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrdivica_emailContent_t *tEmailContent);
extern int32_t HRDIVICASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRDIVICASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRDIVICASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRDIVICASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRDIVICASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrdivica_operatorInfo_t *tOperatorInfo);
extern int32_t HRDIVICASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrdivica_operatorInfo_t *tOperatorInfo);
extern int32_t HRDIVICASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRDIVICASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdivica_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDIVICASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrdivica_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDIVICASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdivica_detitleInfo_t *tDetitle);
extern int32_t HRDIVICASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrdivica_detitleInfo_t *tDetitle);
extern int32_t HRDIVICASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRDIVICASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//--PPV7
extern int32_t HRDIVICASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrdivica_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRDIVICASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrdivica_viewedIpp_t *tViewedIpp);
extern int32_t HRDIVICASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrdivica_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRDIVICASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrdivica_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRDIVICASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrdivica_viewedIpp_t *tViewedIpp);
extern int32_t HRDIVICASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRDIVICASTB_SetIpptPeriod(hrdivica_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
//--密码4
extern int32_t HRDIVICASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRDIVICASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRDIVICASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRDIVICASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--等级2
extern int32_t HRDIVICASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRDIVICASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);
//--卡信息10
extern uint16_t HRDIVICASTB_GetScNo(char *sc);
extern int32_t HRDIVICASTB_GetScBasicInfo(hrdivica_scBasicInfo_t *tPBScInfo);
extern int32_t HRDIVICASTB_GetSCChildParentAttribute(hrdivica_scAddedInfo_t* tPAScInfo);
extern int32_t HRDIVICASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRDIVICASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRDIVICASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRDIVICASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
extern int32_t HRDIVICASTB_STBScCancelFeed(void);
extern int32_t HRDIVICASTB_GetScInfo(int8_t *pSc);
extern int32_t HRDIVICASTB_GetScCosVer(uint32_t *pScCosVer);
extern int32_t HRDIVICASTB_GetCAVer(uint8_t *pCAVer);
extern int32_t HRDIVICASTB_GetCAManuName(int8_t *pCAMaunNameVer);
//--钱包7
extern int32_t HRDIVICASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRDIVICASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrdivica_slotInfo_t *tSlotInfo);
extern int32_t HRDIVICASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrdivica_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRDIVICASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRDIVICASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);

#endif


