/*************************************************************************************************

File Name      :  trca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.05.10

Project Group  :  CA

Author(s)      :  lim

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-05-10     lim          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef TRCA_FUNCTION_H_
#define TRCA_FUNCTION_H_

#include <stdint.h>
#include "../../ca/camid/include/hrca_config.h"
#include "dCA.h"
#if ((EMBED_CA & TRCA) == TRCA)
#include "trca_internal.h"
#endif

/************************************End of Includes*********************************************/

typedef void(*pfCallBack_trca)(unsigned short param);
#define DMUX_INVALID_DESCRAMBLER_ID  0xffff 
extern void *NotifyAccess;  //Notify信号量
extern char  CaOsdInfoUp[880];
extern CA_BOOL SCInsertSuccess ;
extern CA_BOOL SCInsertFirstErrATR;
extern CA_BOOL SCFirstNotication;
extern CA_BOOL b_parentalfram_trca;
extern CA_BOOL IsPPTV_Trca;
extern CA_BOOL b_remind;

/*****************************CA public function*****************************************/

extern CA_BOOL HRTRCASTB_Init(void);
extern CA_BOOL HRTRCASTB_Exit(void);
extern CA_BOOL HRTRCASTB_SCInsert(void);
extern CA_BOOL HRTRCASTB_SCRemove(void);
extern void HRTRCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRTRCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRTRCA_Init_PMTData(void);
extern void HRTRCA_MonitorPMT(void);
extern void HRTRCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRTRCA_MonitorCAT(void);
extern void HRTRCASTB_UpdateFlash(void);
extern void HRTRCASTB_OsdMsgOver(uint16_t u16Time);
extern void HRTRCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRTRCASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRTRCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRTRCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);


/*****************************TR private function****************************************/

extern CA_BOOL HRTRCASTB_SCStatusNotify(uint8_t mStatus, uint8_t *pbATR); //插拔卡的时候调用
extern CA_BOOL HRTRCASTB_SaveBmail(hrtrca_email_t *MailInfo); 
extern void HRTRCASTB_ClearReadStatus(int16_t Index); 
extern void HRTRCASTB_SearchChannel(uint32_t dwFrequency)	;
extern CA_BOOL HRTRCASTB_NotificationIsExisted(void);


/*****************************TR menu function****************************************/
//--邮件8
extern int32_t HRTRCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRTRCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrtrca_emailInfo_t* tEmailInfo);
extern int32_t HRTRCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrtrca_emailInfo_t* tEmailInfo);
extern int32_t HRTRCASTB_GetEmailContent(uint32_t u32EmailID, hrtrca_emailContent_t *tEmailContent);
extern int32_t HRTRCASTB_DelEmail(uint32_t emailIndex, uint8_t u8All);
extern int32_t HRTRCASTB_DelEmailTail(uint32_t u16EmailID);
extern int32_t HRTRCASTB_EmailRead(uint16_t u16EmailIndex);
/*TRCA private api*/
extern int32_t HRTRCASTB_CheckNewAnnounce(uint16_t index);

//--授权信息11
extern int32_t HRTRCASTB_GetOperatorIds(uint16_t *pu16TVSID);
extern int32_t HRTRCASTB_GetOperatorInfo(uint16_t* pu16TVSID, uint8_t* pu8Count, hrtrca_operatorInfo_t* tOperatorInfo);
extern int32_t HRTRCASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIDIndex,hrtrca_operatorInfo_t *tOperatorInfo);
extern int32_t HRTRCASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *u32EntitleIds);
extern int32_t HRTRCASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrtrca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRTRCASTB_GetServiceEntitle_ByIndex(uint16_t u16EntitleIndex,hrtrca_serviceEntitles_t *tServiceEntitles);
extern int32_t HRTRCASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrtrca_detitleInfo_t *tDetitle);
extern int32_t HRTRCASTB_GetDetitle_ByIndex(uint16_t u16TVSIDIndex, hrtrca_detitleInfo_t *tDetitle);
extern int32_t HRTRCASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRTRCASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
/*TRCA private api*/
extern int32_t HRTRCASTB_EntitleInfoExpire(void);

//--PPV 9
extern int32_t HRTRCASTB_BuyIPPV(uint8_t *pinCode,  uint8_t buyIppType, hrtrca_ippBuyInfo_t *ippvBuyInfo);
extern int32_t HRTRCASTB_GetIPPV(uint16_t u16TVSIdIndex, uint16_t *pu16Count, hrtrca_viewedIpp_t *tViewedIpp);
extern int32_t HRTRCASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrtrca_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRTRCASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrtrca_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRTRCASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrtrca_viewedIpp_t *tViewedIpp);
extern int32_t HRTRCASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRTRCASTB_SetIpptPeriod(hrtrca_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
/*TRCA private api*/
extern int32_t HRTRCASTB_GetIPPV_Record(hrtrca_ippRecord_t * ippRecord, uint16_t *pu16Count);
extern int32_t HRTRCASTB_GetIPPV_Record_ByIndex(uint16_t u16IppIndex, hrtrca_ippRecord_t * ippRecord);

//--密码4
extern int32_t HRTRCASTB_VerifyPin(uint8_t* pu8Pin, uint8_t u8Len);
extern int32_t HRTRCASTB_ChangePin(uint8_t* pu8OldPin, uint8_t* pu8NewPin, uint8_t u8Len);
extern int32_t HRTRCASTB_GetIsPinPass(uint8_t* pu8IsPinPassed);
extern int32_t HRTRCASTB_GetIsPinLocked(uint8_t *pu8IsLock);

//--等级2
extern int32_t HRTRCASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRTRCASTB_SetRating(uint8_t u8Rating, uint8_t* pu8Pin);

//--卡信息11
extern uint16_t HRTRCASTB_GetScNo(char *sc);
extern int32_t HRTRCASTB_GetScBasicInfo(hrtrca_scBasicInfo_t *tPBScInfo);
extern int32_t HRTRCASTB_GetSCChildParentAttribute(hrtrca_scAddedInfo_t* tPAScInfo);
extern int32_t HRTRCASTB_GetScUpdateInfo(uint8_t* u8Time, uint8_t* u8Stat);
extern int32_t HRTRCASTB_STBScPaired(uint8_t* pNumber, uint8_t* pSTBIdList);	//机卡配对
extern int32_t HRTRCASTB_STBScReadFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t* pbyLen );
extern int32_t HRTRCASTB_STBScWriteFeedData(uint16_t tvSid, uint8_t* pbyFeedData, uint8_t pbyLen );
extern int32_t HRTRCASTB_GetScInfo(int8_t *pSc);
extern int32_t HRTRCASTB_GetScCosVer(uint32_t *pScCosVer);
extern int32_t HRTRCASTB_GetCAVer(uint8_t *pCAVer);
extern int32_t HRTRCASTB_GetCAManuName(int8_t *pCAMaunNameVer);
/*TRCA private api*/
extern int32_t HRTRCASTB_GetScNum(int8_t *pcString, uint8_t bMaxLen);

//--钱包3
extern int32_t HRTRCASTB_SlotId(uint16_t u16TVSIDIndex, uint8_t *pu8Count, uint8_t *slotId);
extern int32_t HRTRCASTB_SlotInfo(uint16_t u16TVSIDIndex, uint8_t* u8SlotId, hrtrca_slotInfo_t *slotInfo);
extern int32_t HRTRCASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrtrca_slotInfo_t *slotInfo);

//--工作时间2
extern int32_t HRTRCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8StartSec, uint8_t* pu8EndHour, uint8_t* pu8EndMin, uint8_t* pu8EndSec, uint8_t *pu8Pin);
extern int32_t HRTRCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8StartSec, uint8_t u8EndHour, uint8_t u8EndMin, uint8_t u8EndSec, uint8_t* pu8Pin);

//--其他2
/*------------------父母解锁--------------*/
extern int32_t HRTRCASTB_CtrlUnlock(uint8_t *pinCode);
#endif /*TRCA_FUNCTION_H_*/
