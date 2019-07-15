/*************************************************************************************************

File Name      :  dvtca_drv.h

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
#ifndef _DVTCA_FUN_H_
#define _DVTCA_FUN_H_

#include <stdint.h>
#include "../ca/camid/include/hrca_config.h"
#include "dvtca_internal.h"

//#include "hrca_config.h"
/*
#if ((EMBED_CA & DVTCA) == DVTCA)
#include "DVTCAS_STBDataPublic.h"
#include "DVTCAS_STBInf.h"
#include "DVTSTB_CASInf.h"
#include "dvtca_internal.h"
#endif*/

/*******************************define************************************************/
extern unsigned char  g_SCInsert_Ready;
/*******************************end define************************************************/
/*****************************CA public function*****************************************/
extern unsigned char  HRDVTCASTB_Init(void);
extern unsigned char  HRDVTCASTB_Exit(void);
extern unsigned char  HRDVTCASTB_SCInsert(void);
extern unsigned char  HRDVTCASTB_SCRemove(void);
extern void HRDVTCASTB_ServiceClear(uint8_t flag);
extern unsigned char  HRDVTCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRDVTCA_Init_PMTData(void);
extern void HRDVTCA_MonitorPMT(void);
extern void HRDVTCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRDVTCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRDVTCA_MonitorCAT(void);
extern void HRDVTCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRDVTCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRDVTCASTB_CADataGot(uint8_t u8ReqID, unsigned char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRDVTCASTB_MaskFlash(void);
extern void HRDVTCASTB_UpdateFlash(void);
extern void HRDVTCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRDVTCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRDVTCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRDVTCASTB_DataReadyNotify(uint32_t slot, uint8_t *u8Data, uint16_t u16DataLen); 
		
/*****************************function in menu***************************************/
//--邮件7
extern int32_t HRDVTCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRDVTCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrdvtca_emailInfo_t *tEmailInfo);
extern int32_t HRDVTCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrdvtca_emailInfo_t *tEmailInfo);
extern int32_t HRDVTCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrdvtca_emailContent_t *tEmailContent);
extern int32_t HRDVTCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRDVTCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRDVTCASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRDVTCASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRDVTCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrdvtca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDVTCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrdvtca_operatorInfo_t *tOperatorInfo);
extern int32_t HRDVTCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRDVTCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdvtca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDVTCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrdvtca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRDVTCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrdvtca_detitleInfo_t *tDetitle);
extern int32_t HRDVTCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrdvtca_detitleInfo_t *tDetitle);
extern int32_t HRDVTCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRDVTCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//--PPV7
extern int32_t HRDVTCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrdvtca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRDVTCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrdvtca_viewedIpp_t *tViewedIpp);
extern int32_t HRDVTCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrdvtca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRDVTCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrdvtca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRDVTCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrdvtca_viewedIpp_t *tViewedIpp);
extern int32_t HRDVTCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRDVTCASTB_SetIpptPeriod(hrdvtca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
//--密码4
extern int32_t HRDVTCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRDVTCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRDVTCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRDVTCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--等级2
extern int32_t HRDVTCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRDVTCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);
//--卡信息6
extern uint16_t HRDVTCASTB_GetScNo(char *sc);
extern int32_t HRDVTCASTB_GetScBasicInfo(hrdvtca_scBasicInfo_t *tPBScInfo);
extern int32_t HRDVTCASTB_GetSCChildParentAttribute(hrdvtca_scAddedInfo_t* tPAScInfo);
extern int32_t HRDVTCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRDVTCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRDVTCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRDVTCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
//--钱包3
extern int32_t HRDVTCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRDVTCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrdvtca_slotInfo_t *tSlotInfo);
extern int32_t HRDVTCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrdvtca_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRDVTCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec,uint8_t *pu8Pin);
extern int32_t HRDVTCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);
#endif


