/*************************************************************************************************

File Name      :  ctica_fun.h

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

#ifndef _CTICA_FUN_H_
#define _CTICA_FUN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "../../ca/ctica/include/ctidef.h"
#include "../../ca/ctica/include/ctiapi.h"
#include "../../ca/camid/include/hrca_config.h"

//#if ((EMBED_CA & CTICA) == CTICA)
//#include "ctiapi.h"
#include "ctica_internal.h"
//#endif

/************************************End of Includes*********************************************/

/************************************************************************************************/
/*************************************extern Variables*******************************************/
/************************************************************************************************/

extern CTI_ProgSkipNotify_t ProgSkipNotify;
extern uint16_t iCaSysID;

/***********************************End of extern Variables**************************************/

/*****************************CA public function*****************************************/

extern CA_BOOL HRCTICASTB_Init(void);
extern CA_BOOL HRCTICASTB_Exit(void);
extern CA_BOOL HRCTICASTB_SCInsert(void);
extern CA_BOOL HRCTICASTB_SCRemove(void);
extern void HRCTICASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRCTICASTB_SysIDCheck(uint16_t u16SysID);
extern void HRCTICA_MonitorPMT(void);
extern void HRCTICA_MonitorCAT(void);
extern void HRCTICASTB_OsdMsgOver(uint16_t u16Time);
extern void HRCTICASTB_ServiceChangeState(uint16_t u16SerId, uint8_t u8State);
extern void HRCTICASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);

/*****************************CTI private function****************************************/

extern void HRCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);  
extern CA_BOOL HRCTICASTB_CardReady(void);
extern void HRCASTB_do_cat_info_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_do_emm_status_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_do_pmt_info_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_do_ippv_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_do_bmail_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_do_allow_forbid_play_notify(CTI_CAInfoNotify_t type, BYTE* pparam, WORD len);
extern void HRCASTB_force_switch_channel(CTI_ProgSkipNotify_t * ProgSkipNotify);
extern void HRCASTB_do_save_scroll(CTI_CABmailInfo_t *pNew_info);

extern void HRCTICASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRCTICASTB_ShowFinger(uint8_t bType) ;
extern void HRCTICASTB_ShowIPPV(uint16_t EcmPID, void *ippvBuyInfo);
/*****************************function in menu******************************************/
//--邮件7
extern int32_t HRCTICASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRCTICASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrctica_emailInfo_t *tEmailInfo);
extern int32_t HRCTICASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrctica_emailInfo_t *tEmailInfo);
extern int32_t HRCTICASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrctica_emailContent_t *tEmailContent);
extern int32_t HRCTICASTB_DelEmail(uint16_t u16EmailIndex, uint8_t u8All);
extern int32_t HRCTICASTB_DelEmailTail(uint16_t u16EmailIdIndex);
extern int32_t HRCTICASTB_EmailRead(uint16_t u16EmailIdIndex);
//--授权信息10
extern int32_t HRCTICASTB_GetOperatorIds(uint16_t *pu16TVSId);//添声明liu
extern int32_t HRCTICASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t *pu8Count, hrctica_operatorInfo_t *tOperatorInfo);
extern int32_t HRCTICASTB_GetOperatorInfo_ByIndex(uint16_t u16TVSIdIndex,hrctica_operatorInfo_t *tOperatorInfo);
extern int32_t HRCTICASTB_GetEntitlesIds(uint16_t u16TVSIdIndex, uint32_t *pu32EntitleIds);
extern int32_t HRCTICASTB_GetServiceEntitles(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrctica_serviceEntitles_t *tServiceEntitles);
extern int32_t HRCTICASTB_GetServiceEntitle_ByIndex(uint16_t u16TVSIdIndex,uint8_t *pu8Pin, hrctica_serviceEntitles_t *tServiceEntitles);
extern int32_t HRCTICASTB_GetDetitle(uint16_t u16TVSIdIndex, uint8_t *pu8Count, hrctica_detitleInfo_t *tDetitle);
extern int32_t HRCTICASTB_GetDetitle_ByIndex(uint16_t u16TVSIdIndex, hrctica_detitleInfo_t *tDetitle);
extern int32_t HRCTICASTB_GetDetitleReaded(uint16_t u16TVSIdIndex);
extern int32_t HRCTICASTB_DelDetitle(uint16_t u16TVSIdIndex, uint32_t u32Detitle);
//--PPV7
extern int32_t HRCTICASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hrctica_ippBuyInfo_t *tIppvBuyInfo);
extern int32_t HRCTICASTB_GetIPPV(uint16_t u16TVSIdId, uint16_t *pu16Count, hrctica_viewedIpp_t *tViewedIpp, int cmd_type);
extern int32_t HRCTICASTB_GetBookedIpps(uint8_t * pu8Ippcount, hrctica_ippBuyInfo_t * tIppvBoughtInfo);
extern int32_t HRCTICASTB_GetBookedIpps_ByIndex(uint16_t u16IppvIndex, hrctica_ippBuyInfo_t *tIppvBoughtInfo);
extern int32_t HRCTICASTB_GetIPPV_ByIndex(uint16_t u16TVSIdIndex, hrctica_viewedIpp_t *tViewedIpp);
extern int32_t HRCTICASTB_InquireBookIppOver(uint16_t ecmPid);
extern int32_t HRCTICASTB_SetIpptPeriod(hrctica_ippBuyInfo_t *tIppvBuyInfo, uint16_t u16Period);
//--密码4
extern int32_t HRCTICASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRCTICASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);
extern int32_t HRCTICASTB_GetIsPinPass(uint8_t *pu8IsPinPassed);
extern int32_t HRCTICASTB_GetIsPinLocked(uint8_t *pu8IsPinLocked);
//--等级2
extern int32_t HRCTICASTB_GetRating(uint8_t *pu8Rating);
extern int32_t HRCTICASTB_SetRating(uint8_t u8Rating, uint8_t *pu8Pin);
//--卡信息6
extern uint16_t HRCTICASTB_GetScNo(char *sc);
extern int32_t HRCTICASTB_GetScBasicInfo(hrctica_scBasicInfo_t *tPBScInfo);
extern int32_t HRCTICASTB_GetSCChildParentAttribute(hrctica_scAddedInfo_t* tPAScInfo);
extern int32_t HRCTICASTB_GetScUpdateInfo(uint8_t *pu8Time, uint8_t *pu8Stat);
extern int32_t HRCTICASTB_STBScPaired(uint8_t* pu8Number, uint8_t* pu8STBIdList);
extern int32_t HRCTICASTB_STBScReadFeedData(uint16_t u16TVSIdIndex, uint8_t *pu8FeedData, uint8_t *pu8Len );
extern int32_t HRCTICASTB_STBScWriteFeedData(uint16_t u16TVSIdIndex, uint8_t* pu8FeedData, uint8_t u8Len );
//--钱包3
extern int32_t HRCTICASTB_SlotId(uint16_t u16TVSIdIndex, uint8_t *pu8Count, uint8_t *u8SlotId);
extern int32_t HRCTICASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* u8SlotId, hrctica_slotInfo_t *tSlotInfo);
extern int32_t HRCTICASTB_SlotInfo_ByIndex(uint16_t u16SlotIndex, hrctica_slotInfo_t *tSlotInfo);
//--工作时间2
extern int32_t HRCTICASTB_GetWorkTime(uint16_t *pu16StartYear, uint8_t *pu8StartMonth, uint8_t *pu8StartDay, uint8_t *pu8StartHour, uint8_t *pu8StartMin, uint16_t *pu16EndYear, uint8_t *pu8EndMonth, uint8_t *pu8EndDay, uint8_t *pu8EndHour, uint8_t *pu8EndMin, uint16_t *pu16StartSlot, uint16_t *pu16EndSlot, uint8_t *pu8Mode, uint8_t *pu8State, uint8_t *pu8Pin);
extern int32_t HRCTICASTB_SetWorkTime(uint16_t u16StartYear, uint8_t u8StartMonth, uint8_t u8StartDay, uint8_t u8StartHour, uint8_t u8StartMin, uint16_t u16EndYear, uint8_t u8EndMonth, uint8_t u8EndDay, uint8_t u8EndHour, uint8_t u8EndMin, uint16_t u16StartSlot, uint16_t u16EndSlot, uint8_t u8Mode, uint8_t u8State, uint8_t *pu8Pin);

#endif


