/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  hourn

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-02-01     hourn          created              ---

*************************************************************************************************/

/*******************************Includes************************************************/

#ifndef WFCA_FUNCTION_H
#define WFCA_FUNCTION_H

//#if ((EMBED_CA & WFCA) == WFCA)

#include "dca/wfca_internal.h"

extern uint8_t	wfca_isPPTV;     //0-no   1-yes
extern uint8_t 	wfca_cardStatus;
extern uint32_t  CAErrList[7];

/*****************************CA public function*****************************************/

extern uint8_t HRWFCASTB_Init(void);
extern uint8_t HRWFCASTB_Exit(void);
extern uint8_t HRWFCASTB_SCInsert(void);
extern uint8_t HRWFCASTB_SCRemove(void);
extern void HRWFCASTB_ServiceClear(uint8_t flag);
extern uint8_t HRWFCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRWFCA_Init_PMTData(void);
extern void HRWFCA_MonitorPMT(void);
extern void HRWFCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRWFCA_MonitorCAT(void);
extern void HRWFCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type) ;
extern void HRWFCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRWFCASTB_CADataGot(uint8_t u8ReqID, uint8_t u8Ok, uint16_t u16Pid, uint8_t* u8ReceiveData, uint16_t u16Len);
extern void HRWFCASTB_MaskFlash(void);
extern void HRWFCASTB_UpdateFlash(void);
extern void HRWFCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRWFCASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State, uint8_t u8Start);
extern void HRWFCASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRWFCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRWFCASTB_TimerShowBuyMessage(uint8_t bMessage, uint32_t time);
/*****************************WF private function****************************************/

extern void HRWFCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);
extern uint8_t HRWFCASTB_BookIpp(void);
//extern CA_BOOL HRCASTB_ProgramEntitle(uint16_t NetWorkId, uint16_t StreamId, uint16_t ProgramNo);
extern uint8_t HRWFCASTB_SetZone(uint8_t *zone);
extern uint8_t HRWFSmart_T0Transfer(const uint8_t* pbyCommand, uint16_t wCommandLen, uint8_t* pbyReply, uint16_t* pwReplyLen);  
extern void HRWFCASTB_DateTransform(WFCO_Date_t *To,uint16_t Mjd);
extern int HRWFCASTB_GetSlotState(void);


/*****************************WF menu function****************************************/
//--智能卡信息
extern uint16_t HRWFCASTB_GetScNo(char *sc);
extern int32_t HRWFCASTB_GetScBasicInfo(hrwfca_scBasicInfo_t *tPBScInfo);
extern int32_t HRWFCASTB_GetSCChildParentAttribute(hrwfca_scAddedInfo_t* tPAScInfo);
extern int32_t HRWFCASTB_GetScUpdateInfo(uint8_t* u8Time, uint8_t* u8Stat);
extern int32_t HRWFCASTB_STBScPaired(uint8_t* pNumber, uint8_t* pSTBIdList);	//机卡配对
extern int32_t HRWFCASTB_STBScReadFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t* pbyLen );
extern int32_t HRWFCASTB_STBScWriteFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t pbyLen );
extern int32_t HRWFCASTB_GetScInfo(int8_t *pSc);
extern int32_t HRWFCASTB_GetScCosVer(uint32_t *pScCosVer);
extern int32_t HRWFCASTB_GetCAVer(uint8_t *pCAVer);
extern int32_t HRWFCASTB_GetCAManuName(int8_t *pCAMaunNameVer);
extern void HRWFCASTB_GetCAErrorInfo(uint32_t *errList);
//--邮件7
extern int32_t HRWFCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRWFCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrwfca_emailInfo_t* tEmailInfo);
extern int32_t HRWFCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrwfca_emailInfo_t* tEmailInfo);
extern int32_t HRWFCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrwfca_emailContent_t *tEmailContent);
extern int32_t HRWFCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
extern int32_t HRWFCASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRWFCASTB_EmailRead(uint16_t u16EmailIndex);

//--授权信息10
extern int32_t HRWFCASTB_GetOperatorIds(uint16_t *pu16TVSId);
extern int32_t HRWFCASTB_GetOperatorInfo(uint16_t* pu16TVSId, uint8_t* pu8Count, hrwfca_operatorInfo_t* tOperatorInfo);
extern int32_t HRWFCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrwfca_operatorInfo_t *tOperatorInfo);
extern int32_t HRWFCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *u32EntitleIds);
extern int32_t HRWFCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrwfca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRWFCASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,hrwfca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRWFCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrwfca_detitleInfo_t *tDetitle);
extern int32_t HRWFCASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrwfca_detitleInfo_t *tDetitle);
extern int32_t HRWFCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRWFCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);

//--PPV 7
extern int32_t HRWFCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrwfca_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRWFCASTB_GetIPPV(uint16_t u16TVSIdIndex, uint16_t* pu16Count, hrwfca_viewedIpp_t* tViewedIpp);
extern int32_t HRWFCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrwfca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRWFCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrwfca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRWFCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrwfca_viewedIpp_t *tViewedIpp);
extern int32_t HRWFCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRWFCASTB_SetIpptPeriod(hrwfca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);

//--密码4
extern int32_t HRWFCASTB_VerifyPin(uint8_t* pu8Pin,uint8_t u8Len);
extern int32_t HRWFCASTB_ChangePin(uint8_t* pu8OldPin, uint8_t* pu8NewPin, uint8_t u8Len);
extern int32_t HRWFCASTB_GetIsPinPass(uint8_t* pu8IsPinPassed);
extern int32_t HRWFCASTB_GetIsPinLocked(uint8_t *pu8IsLock);

//--等级2
extern int32_t HRWFCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRWFCASTB_SetRating(uint8_t u8Rating, uint16_t timeInterval);

//--钱包3
extern int32_t HRWFCASTB_SlotId(uint16_t u16TVSIDIndex, uint8_t *pu8Count, uint8_t *slotId);
extern int32_t HRWFCASTB_SlotInfo(uint16_t u16TVSIDIndex, uint8_t* u8SlotId, hrwfca_slotInfo_t *slotInfo);
extern int32_t HRWFCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrwfca_slotInfo_t *slotInfo);

//--工作时间2
extern int32_t HRWFCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8StartSec, uint8_t* pu8EndHour, uint8_t* pu8EndMin, uint8_t* pu8EndSec,uint8_t* pu8Pin);
extern int32_t HRWFCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t* pu8Pin);

//--通知ca收看家长锁节目
extern int32_t HRWFCASTB_ParentalRatingOk(uint32_t StbTicks);
extern void WFSTB_ParentalRatingHide(void);

//#endif
#endif
