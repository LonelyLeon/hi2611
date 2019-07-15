/*************************************************************************************************

File Name      :  LXDTca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  GONGQ

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2014-04-22     GONGQ          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _LXDTCA_FUN_H_
#define _LXDTCA_FUN_H_

#include <stdint.h>
#include "lxdtca_internal.h"


/************************************End of Includes*********************************************/
extern uint32_t TaskIdTable_lxdtca[MAX_TASK_NUMBER_LXDTCA];
extern uint32_t SemIndex_lxdtca;
extern void     *pSemaRegisterTable_lxdtca[MAX_SEMA_NUMBER_LXDTCA];
extern uint8_t  EmmReqID_Lxdtca;
/*****************************CA public function*****************************************/

extern unsigned char HRLXDTCASTB_Init(void);
extern unsigned char HRLXDTCASTB_Exit(void);
extern unsigned char HRLXDTCASTB_SCInsert(void);
extern unsigned char HRLXDTCASTB_SCRemove(void);
extern void HRLXDTCASTB_ServiceClear(uint8_t flag);
extern unsigned char HRLXDTCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRLXDTCA_Init_PMTData(void);
extern void HRLXDTCA_MonitorPMT(void);
extern void HRLXDTCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRLXDTCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRLXDTCA_MonitorCAT(void);
extern void HRLXDTCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRLXDTCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRLXDTCASTB_CADataGot(uint8_t u8ReqID, unsigned char u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRLXDTCASTB_MaskFlash(void);
extern void HRLXDTCASTB_UpdateFlash(void);
extern void HRLXDTCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRLXDTCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRLXDTCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRLXDTCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRLXDTCASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);
extern void HRLXDTCASTB_ShowFinger(uint8_t bType);
extern void HRLXDTCASTB_ShowIPPV(uint16_t EcmPID, void *ippvBuyInfo);
extern uint8_t* HRLXDTCASTB_HexStringToBin(int8_t* name, uint32_t num);
/*****************************function in menu***************************************/

//--邮件7
extern int32_t HRLXDTCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRLXDTCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrlxdtca_emailInfo_t *tEmailInfo);
extern int32_t HRLXDTCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrlxdtca_emailInfo_t *tEmailInfo);
extern int32_t HRLXDTCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrlxdtca_emailContent_t *tEmailContent);
extern int32_t HRLXDTCASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRLXDTCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRLXDTCASTB_EmailRead(uint16_t u16EmailIdIndex);

//--授权信息10
extern int32_t HRLXDTCASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRLXDTCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrlxdtca_operatorInfo_t *tOperatorInfo);
extern int32_t HRLXDTCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrlxdtca_operatorInfo_t *tOperatorInfo);
extern int32_t HRLXDTCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRLXDTCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrlxdtca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRLXDTCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrlxdtca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRLXDTCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrlxdtca_detitleInfo_t *tDetitle);
extern int32_t HRLXDTCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrlxdtca_detitleInfo_t *tDetitle);
extern int32_t HRLXDTCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRLXDTCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);

//--PPV7
extern int32_t HRLXDTCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrlxdtca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRLXDTCASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrlxdtca_viewedIpp_t *tViewedIpp);
extern int32_t HRLXDTCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrlxdtca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRLXDTCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrlxdtca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRLXDTCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrlxdtca_viewedIpp_t *tViewedIpp);
extern int32_t HRLXDTCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRLXDTCASTB_SetIpptPeriod(hrlxdtca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

//--密码4
extern int32_t HRLXDTCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRLXDTCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRLXDTCASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRLXDTCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);

//--等级2
extern int32_t HRLXDTCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRLXDTCASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);

//--卡信息10
extern uint16_t HRLXDTCASTB_GetScNo(char *sc);
extern int32_t HRLXDTCASTB_GetScBasicInfo(hrlxdtca_scBasicInfo_t *tPBScInfo);
extern int32_t HRLXDTCASTB_GetSCChildParentAttribute(void);
extern int32_t HRLXDTCASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRLXDTCASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRLXDTCASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRLXDTCASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
extern int32_t HRLXDTCASTB_GetScInfo(int8_t *pSc);
extern int32_t HRLXDTCASTB_GetScCosVer(uint32_t *pScCosVer);
extern int32_t HRLXDTCASTB_GetCAVer(uint8_t *pCAVer);
extern int32_t HRLXDTCASTB_GetCAManuName(int8_t *pCAMaunNameVer);


//--钱包3
extern int32_t HRLXDTCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRLXDTCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* pu8Slotcount, hrlxdtca_slotInfo_t *tSlotInfo);
extern int32_t HRLXDTCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrlxdtca_slotInfo_t *tSlotInfo);

//--工作时间2
extern int32_t HRLXDTCASTB_GetWorkTime(uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint8_t *pu8StartSec, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint8_t *pu8EndSec, uint8_t* pu8Pin);
extern int32_t HRLXDTCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t *pu8Pin);
#endif


