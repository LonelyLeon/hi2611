/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2015-02-26      lim            created              ---

*************************************************************************************************/
#ifndef SCCA_FUNCTION_H_
#define SCCA_FUNCTION_H_

#ifndef SCCA_GLOBAL
#define SCCA_EXTERN extern
#else
#define SCCA_EXTERN
#endif //SCCA_GLOBAL

#include <stdint.h>
#include "scca_internal.h"
#include "../../ca/camid/include/hrca_config.h"
#include "../../ca/camid/include/hrca_display.h"
#include "dCA.h"
//#include "../../ca/scca/include/sc_ca_api.h"

SCCA_EXTERN int8_t gSCcaMail[2048];

SCCA_EXTERN uint8_t HRSCCASTB_Init(void);
SCCA_EXTERN CA_BOOL HRSCCASTB_Exit(void);
SCCA_EXTERN CA_BOOL HRSCCASTB_SCInsert(void);
SCCA_EXTERN CA_BOOL HRSCCASTB_SCRemove(void);
SCCA_EXTERN void HRSCCASTB_ServiceClear(uint8_t flag);
SCCA_EXTERN CA_BOOL HRSCCASTB_SysIDCheck(uint16_t u16SysID);
SCCA_EXTERN void HRSCCA_Init_PMTData(void);
SCCA_EXTERN void HRSCCA_MonitorPMT(void);
SCCA_EXTERN void HRSCCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
SCCA_EXTERN void HRSCCASTB_StopEcmpid(uint16_t u16EcmPID);
SCCA_EXTERN void HRSCCA_MonitorCAT(void);
SCCA_EXTERN void HRSCCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
SCCA_EXTERN void HRSCCASTB_StopEmmpid(uint16_t u16EmmPID);
SCCA_EXTERN void HRSCCASTB_CADataGot(uint8_t u8ReqID, CA_BOOL u8Ok, uint16_t u16Pid, uint8_t *u8ReceiveData, uint16_t u16Len);
SCCA_EXTERN void HRSCCASTB_MaskFlash(void);
SCCA_EXTERN void HRSCCASTB_UpdateFlash(void);
SCCA_EXTERN void HRSCCASTB_OsdMsgOver(uint16_t u16Time);
SCCA_EXTERN void HRSCCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint16_t u16SerId, uint8_t u8State);
SCCA_EXTERN void HRSCCASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
SCCA_EXTERN CA_BOOL  HRSCCASTB_SetECMFilter(uint8_t *data, uint8_t *mask, uint8_t type);
SCCA_EXTERN CA_BOOL  HRSCCASTB_SetEMMFilter(uint8_t *data, uint8_t *mask);
SCCA_EXTERN void HRSCCASTB_SetCW(uint8_t *cw);
SCCA_EXTERN void HRSCCASTB_ShowBuyMessage(uint8_t bMessage);


//--------------------SC info--------------------------------
SCCA_EXTERN uint16_t HRSCCASTB_GetScNo(char *sc);
SCCA_EXTERN int32_t HRSCCASTB_GetScBasicInfo(hrscca_cardInfo_t *pCardInfo);
SCCA_EXTERN int32_t HRSCCASTB_GetSCChildParentAttribute(hrscca_scAddedInfo_t* tPAScInfo);
SCCA_EXTERN int32_t HRSCCASTB_GetScUpdateInfo(uint8_t* u8Time, uint8_t* u8Stat);
SCCA_EXTERN int32_t HRSCCASTB_STBScPaired(uint8_t* pNumber, uint8_t* pSTBIdList);    //»ú¿¨Åä¶Ô
SCCA_EXTERN int32_t HRSCCASTB_STBScReadFeedData(uint16_t u16TVSId, uint8_t* pbyFeedData, uint8_t* pbyLen );
SCCA_EXTERN int32_t HRSCCASTB_STBScWriteFeedData(uint16_t u16TVSId, uint8_t* pbyFeedData, uint8_t pbyLen );
SCCA_EXTERN int32_t HRSCCASTB_GetScInfo(int8_t *pSc);
SCCA_EXTERN int32_t HRSCCASTB_GetScCosVer(uint32_t *pScCosVer);
SCCA_EXTERN int32_t HRSCCASTB_GetCAVer(uint8_t *pCAVer);
SCCA_EXTERN int32_t HRSCCASTB_GetCAManuName(int8_t *pCAMaunNameVer);

//--------------------Slot Info--------------------------------
SCCA_EXTERN int32_t HRSCCASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *pu8SlotId);
SCCA_EXTERN int32_t HRSCCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* pu8SlotId, hrscca_slotInfo_t *tSlotInfo);
SCCA_EXTERN int32_t HRSCCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrscca_slotInfo_t *tSlotInfo); //u16SlotIndex :0~3

//--------------------Pin----------------------------------
SCCA_EXTERN int32_t HRSCCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
SCCA_EXTERN int32_t HRSCCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
SCCA_EXTERN int32_t HRSCCASTB_GetIsPinPass(uint8_t* pu8IsPinPassed);	
SCCA_EXTERN int32_t HRSCCASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);

//----------------------IPP-----------------------------------
SCCA_EXTERN int32_t HRSCCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrscca_ippBuyInfo_t *tIppvBuyInfo);
SCCA_EXTERN int32_t HRSCCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrscca_ippBuyInfo_t * tIppvBoughtInfo);
SCCA_EXTERN int32_t HRSCCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrscca_ippBuyInfo_t *tIppvBoughtInfo);
SCCA_EXTERN int32_t HRSCCASTB_GetIPPV(uint16_t u16TVSIdIndex, uint16_t* pu16Count, hrscca_viewedIpp_t* tViewedIpp);
SCCA_EXTERN int32_t HRSCCASTB_GetIPPV_ByIndex(uint16_t u16IppvIndex, hrscca_viewedIpp_t *ipp);
SCCA_EXTERN int32_t HRSCCASTB_InquireBookIppOver(uint16_t ecmPid);
SCCA_EXTERN int32_t HRSCCASTB_SetIpptPeriod(hrscca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

#endif //FUNCTION_H_



