/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2015-07-10    lim               created              ---

*************************************************************************************************/
#ifndef COLABLECA_FUNCTION_H_
#define COLABLECA_FUNCTION_H_

#ifndef COLABLECA_GLOBAL
#define COLABLECA_EXTERN extern
#else
#define COLABLECA_EXTERN
#endif 

#include <stdint.h>
#include "colableca_internal.h"
#include "../../ca/camid/include/hrca_config.h"
#include "../../ca/camid/include/hrca_display.h"
#include "dCA.h"

COLABLECA_EXTERN uint32_t HcnEmailCount;
COLABLECA_EXTERN uint32_t HcnNewEmailCount;
COLABLECA_EXTERN int8_t gHcnMail[256];
COLABLECA_EXTERN uint8_t hcnca_isPPTV;

COLABLECA_EXTERN uint8_t HRCOLABLECASTB_Init(void);
COLABLECA_EXTERN CA_BOOL HRCOLABLECASTB_Exit(void);
COLABLECA_EXTERN CA_BOOL HRCOLABLECASTB_SysIDCheck(uint16_t u16SysID);
COLABLECA_EXTERN void HRCOLABLECASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
COLABLECA_EXTERN void HRCOLABLECASTB_StopEcmpid(uint16_t u16EcmPID);
COLABLECA_EXTERN void HRCOLABLECASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
COLABLECA_EXTERN void HRCOLABLECASTB_StopEmmpid(uint16_t u16EmmPID);
COLABLECA_EXTERN CA_BOOL HRCOLABLECASTB_SCInsert(void);
COLABLECA_EXTERN CA_BOOL HRCOLABLECASTB_SCRemove(void);
COLABLECA_EXTERN void HRCOLABLECASTB_ServiceClear(uint8_t flag);
COLABLECA_EXTERN void HRCOLABLECASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint16_t u16SerId, uint8_t u8State);
COLABLECA_EXTERN void HRCOLABLECASTB_DataReadyNotify(int slot, uint8_t *u8Data, uint16_t u16DataLen);
COLABLECA_EXTERN void HRCOLABLECASTB_ShowBuyMessage(uint8_t bMessage);
COLABLECA_EXTERN void HRCOLABLECASTB_TimerShowBuyMessage(uint8_t bMessage,uint32_t time);

//---------------卡信息----------------------
COLABLECA_EXTERN uint16_t HRHCNCASTB_GetScNo(char *sc);
COLABLECA_EXTERN int32_t HRHCNCASTB_GetScBasicInfo(hcn_cardInfo_t *pCardInfo);

//---------------钱包信息--------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_SlotInfo(uint16_t u16TVSIdIndex, uint8_t* pu8SlotId, hcn_purse_t *tSlotInfo);

//---------------授权信息---------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_GetServiceEntitles(uint8_t* pu8Count, hcn_entitle_t *tServiceEntitles);

//---------------IPPV信息--------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_BuyIPPV(uint8_t *pu8PinCode, uint8_t buyIppType, hcn_ipptv_t *tIppvBuyInfo);
COLABLECA_EXTERN int32_t HRHCNCASTB_GetIPPV(uint16_t u16TVSIdIndex, uint16_t* pu16Count, hcn_ipptv_t* tViewedIpp);

//---------------级别设置----------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_GetRating(uint8_t *pu8Rating);
COLABLECA_EXTERN int32_t HRHCNCASTB_SetRating(uint8_t u8Rating/*, uint8_t *pu8Pin*/);

//---------------修改PIN码---------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len, uint8_t *pu8times);
COLABLECA_EXTERN int32_t HRHCNCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t oldPinLen, uint8_t *pu8NewPin, uint8_t newPinLen, uint8_t *pu8times);

//---------------工作时段设置------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_GetWorkTime(uint8_t* pu8StartHour, uint8_t* pu8StartMin, uint8_t* pu8EndHour, uint8_t* pu8EndMin);
COLABLECA_EXTERN int32_t HRHCNCASTB_SetWorkTime(uint8_t u8StartHour, uint8_t u8StartMin, uint8_t u8EndHour, uint8_t u8EndMin);

//---------------邮件-------------------------
COLABLECA_EXTERN int32_t HRHCNCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
COLABLECA_EXTERN int32_t HRHCNCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hcn_mail_head* tEmailInfo);
COLABLECA_EXTERN int32_t HRHCNCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hcn_mail_content *tEmailContent);
COLABLECA_EXTERN int32_t HRHCNCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
COLABLECA_EXTERN int32_t HRHCNCASTB_DelEmailTail(uint16_t u16EmailIdIndex);

#endif

