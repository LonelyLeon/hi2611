/*************************************************************************************************

File Name      :  gosca_drv.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/
#ifndef _GOSCA_FUN_H_
#define _GOSCA_FUN_H_

#include <stdint.h>
#include "../../ca/camid/include/hrca_config.h"
#include "../../ca/camid/include/hrca_display.h"
#include "gosca_internal.h"


extern CA_BOOL HRGOSCASTB_Init(void);
extern CA_BOOL HRGOSCASTB_Exit(void);
extern CA_BOOL HRGOSCASTB_SCInsert(void);
extern CA_BOOL HRGOSCASTB_SCRemove(void);
extern void HRGOSCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRGOSCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRGOSCA_Init_PMTData(void);
extern void HRGOSCA_MonitorPMT(void);
extern void HRGOSCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRGOSCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRGOSCA_MonitorCAT(void);
extern void HRGOSCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRGOSCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRGOSCASTB_CADataGot(uint8_t u8ReqID, CA_BOOL u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRGOSCASTB_MaskFlash(void);
extern void HRGOSCASTB_UpdateFlash(void);
extern void HRGOSCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRGOSCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRGOSCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRGOSCASTB_ShowBuyMessage(uint8_t bMessage);

/*****************************GOSCA private function****************************************/
extern CA_BOOL HRGOSCASTB_GetCardState(void);
extern void HRGOSCASTB_InMenuToHideOSD(void);
extern void HRGOSCA_MonitorOSD(void);
extern void HRGOSCA_ShowOsdMessage(uint8_t u8Style, char* u8OsdData, uint32_t bg_clor, uint32_t font_clor, uint8_t font_size, uint8_t transparency, uint16_t u16Time, uint8_t u8JudgeValue);
extern void HRGOSCA_StartService(void* ChannelInfo, uint8_t flag);
extern void HRGOSCA_ReStartSTB(void);
/*********************************************function in menu***************************************/
//--邮件7
extern int32_t HRGOSCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRGOSCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrgosca_emailInfo_t *tEmailInfo);
extern int32_t HRGOSCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrgosca_emailInfo_t *tEmailInfo);
extern int32_t HRGOSCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrgosca_emailContent_t *tEmailContent);
extern int32_t HRGOSCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRGOSCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRGOSCASTB_DelALLEmail(void);
extern int32_t HRGOSCASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息11
//运营商信息、授权信息、反授权信息
extern int32_t HRGOSCASTB_GetOperatorIds(uint16_t *pu16TVSId);
extern int32_t HRGOSCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrgosca_operatorInfo_t *tOperatorInfo);
extern int32_t HRGOSCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrgosca_operatorInfo_t *tOperatorInfo);
extern int32_t HRGOSCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRGOSCASTB_GetEntitlesSum(uint32_t *pSum);
extern int32_t HRGOSCASTB_GetServiceEntitles(uint32_t pStartIndex, uint32_t* pu8Count, hrgosca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRGOSCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrgosca_detitleInfo_t *tDetitle);
extern int32_t HRGOSCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrgosca_detitleInfo_t* tDetitle);
extern int32_t HRGOSCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRGOSCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);

//--PPV7
extern int32_t HRGOSCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrgosca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRGOSCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrgosca_viewedIpp_t *tViewedIpp);
extern int32_t HRGOSCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrgosca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRGOSCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrgosca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRGOSCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrgosca_viewedIpp_t *tViewedIpp);
extern int32_t HRGOSCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRGOSCASTB_SetIpptPeriod(hrgosca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
//--密码4
extern int32_t HRGOSCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRGOSCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRGOSCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRGOSCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--卡信息8
extern uint16_t HRGOSCASTB_GetScNo(char *sc);
extern int32_t HRGOSCASTB_GetScBasicInfo(hrgosca_scBasicInfo_t *tPBScInfo);
extern int32_t HRGOSCASTB_GetSCChildParentAttribute(hrgosca_scAddedInfo_t* tPAScInfo);
extern int32_t HRGOSCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRGOSCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRGOSCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRGOSCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );

//--CA其他设置6
//CA 级别、到期天数、工作时段

extern int32_t HRGOSCASTB_SetWorkInfo(void *inWorkInfo);
extern int32_t HRGOSCASTB_GetWorkInfo(void *outWorkInfo);

extern int32_t HRGOSCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRGOSCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);

extern int32_t HRGOSCASTB_GetMatureDays(uint8_t *pu8MatureDays);
extern int32_t HRGOSCASTB_SetMatureDays(uint8_t u8MatureDays, uint8_t *pu8Pin);

extern int32_t HRGOSCASTB_GetWorkMode(uint8_t *pu8WorkMode);
extern int32_t HRGOSCASTB_SetWorkMode(uint8_t u8WorkMode, uint8_t *pu8Pin);
//--钱包3
extern int32_t HRGOSCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRGOSCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrgosca_slotInfo_t *tSlotInfo);
extern int32_t HRGOSCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrgosca_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRGOSCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec,uint8_t *pu8Pin);
extern int32_t HRGOSCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);
//--子母卡配对
extern int32_t HRGOSCASTB_GetMasterSlavePairInfo(Pair_Type cardtype);
//--机卡绑定
extern int32_t HRGOSCASTB_GetScBindInfo(hrgosca_scBindInfo_t *tpBindScInfo);
#endif


