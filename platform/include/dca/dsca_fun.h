/*************************************************************************************************

File Name      :  dsca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/
#ifndef _DSCA_FUN_H_
#define _DSCA_FUN_H_

#ifdef GLOBAL_H_
#define DS_EXTERN
#else
#define DS_EXTERN extern
#endif

#include <stdint.h>
#include "../../ca/camid/include/hrca_config.h"
#include "../../ca/camid/include/hrca_display.h"
#include "dCA.h"

#if ((EMBED_CA & DSCA) == DSCA)
#include "dca/dsca_internal.h"		
#endif


/*****************************CA public function*****************************************/
extern CA_BOOL HRDSCASTB_Init(void);
extern CA_BOOL HRDSCASTB_Exit(void);
extern CA_BOOL HRDSCASTB_SCInsert(void);
extern CA_BOOL HRDSCASTB_SCRemove(void);
extern void HRDSCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRDSCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRDSCA_Init_PMTData(void);
extern void HRDSCA_MonitorPMT(void);
extern void HRDSCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRDSCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRDSCA_MonitorCAT(void);
extern void HRDSCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRDSCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRDSCASTB_CADataGot(uint8_t u8DataType, uint16_t u16Pid, uint8_t *u8ReceiveData, uint16_t u16Len);
extern void HRDSCASTB_MaskFlash(void);
extern void HRDSCASTB_UpdateFlash(void);
extern void HRDSCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRDSCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State ,uint8_t u8Start);
extern void HRDSCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRDSCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRDSCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);
extern void HRDSCASTB_setLan(uint8_t lanType);
extern void HRDSCASTB_updataMessageLan(uint8_t lanFlag);
extern void HRDSCASTB_setCwZero(void);
extern void HRDSCASTB_stopRightNow(void);
extern CA_BOOL HRDSCASTB_sendToSmartCart(uint8_t * pucSend, uint8_t *pucSendLen, uint8_t *pucReceive,
											uint8_t *pucReceiveLen, uint32_t uiTimeout, uint8_t *pucStatusWord );



/*****************************function in menu*****************************************/
//--邮件7
extern int32_t HRDSCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRDSCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrdsca_emailInfo_t *tEmailInfo);
extern int32_t HRDSCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrdsca_emailInfo_t *tEmailInfo);
extern int32_t HRDSCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrdsca_emailContent_t *tEmailContent);
extern int32_t HRDSCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRDSCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRDSCASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRDSCASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRDSCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrdsca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDSCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrdsca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDSCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRDSCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdsca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDSCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrdsca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDSCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdsca_detitleInfo_t *tDetitle);
extern int32_t HRDSCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrdsca_detitleInfo_t *tDetitle);
extern int32_t HRDSCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRDSCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//--PPV 7
extern int32_t HRDSCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrdsca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRDSCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrdsca_viewedIpp_t *tViewedIpp);
extern int32_t HRDSCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrdsca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRDSCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrdsca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRDSCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrdsca_viewedIpp_t *tViewedIpp);
extern int32_t HRDSCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRDSCASTB_SetIpptPeriod(hrdsca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
//--密码4
extern int32_t HRDSCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRDSCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRDSCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRDSCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--等级2
extern int32_t HRDSCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRDSCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);
//--卡信息6
extern uint16_t HRDSCASTB_GetScNo(char *sc);
extern int32_t HRDSCASTB_GetScBasicInfo(hrdsca_scBasicInfo_t *tPBScInfo);
extern int32_t HRDSCASTB_GetSCChildParentAttribute(hrdsca_scAddedInfo_t* tPAScInfo);
extern int32_t HRDSCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRDSCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRDSCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRDSCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
//--钱包3
extern int32_t HRDSCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRDSCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrdsca_slotInfo_t *tSlotInfo);
extern int32_t HRDSCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrdsca_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRDSCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRDSCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);
#endif


