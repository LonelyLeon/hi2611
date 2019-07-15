/*************************************************************************************************

File Name      :  xsmca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  haoxw

Notes          :  

History        :

Version    Date        	Author(s)      Description         Referrence

1.0        2015-11-02     haoxw          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _XSMCA_FUN_H_
#define _XSMCA_FUN_H_

#include <stdint.h>
#include "dCA.h"
#include "xsmca_internal.h"


/************************************End of Includes*********************************************/

/*****************************CA public function*****************************************/

extern unsigned char HRXSMCASTB_Init(void);
extern unsigned char HRXSMCASTB_Exit(void);
extern unsigned char HRXSMCASTB_SCInsert(void);
extern unsigned char HRXSMCASTB_SCRemove(void);
extern void HRXSMCASTB_ServiceClear(uint8_t flag);
extern unsigned char HRXSMCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRXSMCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRXSMCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRXSMCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRXSMCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRXSMCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State ,uint8_t u8Start);
extern void HRXSMCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRXSMCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRXSMCA_MonitorOSD(void);


/*****************************function in menu***************************************/

//--¿¨ÐÅÏ¢
extern uint16_t HRXSMCASTB_GetScNo(char* sc);
extern int32_t HRXSMCASTB_GetScBasicInfo(hrxsmca_scBasicInfo_t * tPBScInfo);
extern int32_t HRXSMCASTB_GetSCChildParentAttribute(uint8_t* type);
extern int32_t HRXSMCASTB_STBScReadFeedData(uint8_t *pu8FeedData, uint8_t *pu8Len);
extern int32_t HRXSMCASTB_STBScWriteFeedData(uint8_t* pu8FeedData, uint8_t u8Len);

//--ÓÊ¼þ
extern int32_t HRXSMCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRXSMCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrxsmca_emailInfo_t* tEmailInfo);
extern int32_t HRXSMCASTB_GetEmailHead_ByIndex(uint16_t u16EmailHeadIndex, hrxsmca_emailInfo_t* tEmailInfo);
extern int32_t HRXSMCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrxsmca_emailContent_t *tEmailContent);
extern int32_t HRXSMCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);

#endif


