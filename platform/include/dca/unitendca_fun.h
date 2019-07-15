/*************************************************************************************************

File Name      :  unitendca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 

Project Group  :  CA

Author(s)      :  gaozh

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2013-11-13     gaozh          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _UNITENDCA_FUN_H_
#define _UNITENDCA_FUN_H_

#include <stdint.h>
#include "unitendca_internal.h"
#include "dCA.h"


/************************************End of Includes*********************************************/
extern uint32_t  utiTaskIdTable; //记录uit CA库的任务handle
/*****************************CA public function*****************************************/


extern unsigned char HRUNITENDCASTB_Init(void);
extern unsigned char HRUNITENDCASTB_Exit(void);
extern unsigned char HRUNITENDCASTB_SCInsert(void);
extern unsigned char HRUNITENDCASTB_SCRemove(void);
extern void HRUNITENDCASTB_ServiceClear(uint8_t flag);
extern void HRUNITENDCASTB_ShowBuyMessage(uint8_t bMessage);
extern void HRUNITENDCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);

//UDRM INFO
extern uint16_t HRUNITENDCASTB_GetScNo(char *sc);
extern int32_t HRUNITENDCASTB_GetScBasicInfo(hrunitendca_scBasicInfo_t * tPBdrmInfo);
//PPC INFO
extern int32_t HRUNITENDCASTB_GetOperatorNumber(unsigned long *pu16TVSId);
extern int32_t HRUNITENDCASTB_GetOperatorInfo(uint16_t *pu16TVSId, uint8_t pu8Count, hrunitendca_operatorInfo_t* tOperatorInfo);
//Email INFO
extern int32_t HRUNITENDCASTB_GetEmailCount(uint16_t *pu16EmailCount, uint16_t *pu16NewEmailCount, uint16_t *pu16EmptyEmailCount);
extern int32_t HRUNITENDCASTB_GetEmailHeads(uint16_t *pu16EmailCount, hrunitendca_emailInfo_t* tEmailInfo);
extern int32_t HRUNITENDCASTB_GetEmailContent(uint16_t u16EmailIdIndex, hrunitendca_emailContent_t *tEmailContent);
extern int32_t HRUNITENDCASTB_DelEmail(uint16_t u16EmailIdIndex, uint8_t u8All);
extern int32_t HRUNITENDCASTB_EmailRead(uint16_t u16EmailIndex);
//VIEW RATE
extern int32_t HRUNITENDCASTB_GetRating(unsigned long *pu8Rating);
extern int32_t HRUNITENDCASTB_SetRating(unsigned long u8Rating, uint8_t *pu8Pin);
extern uint16_t HRUNITENDCASTB_GetSevId(void);
extern int32_t HRUNITENDCASTB_DisableTempRating(uint16_t uService_id, uint8_t *pu8Pin);

//PIN SET
extern int32_t HRUNITENDCASTB_VerifyPin(uint8_t *pu8Pin, uint8_t u8Len);
extern int32_t HRUNITENDCASTB_ChangePin(uint8_t *pu8OldPin, uint8_t *pu8NewPin, uint8_t u8Len);

extern void HRUNITENDCASTB_DataReadyNotify(uint32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern uint8_t Unitendca_HREmail_Operater(UNITENDCA_EMAIL_OP_TYPE type, const unitendca_email_param_t *pIn, unitendca_email_param_t *pOut);

extern void Unitendca_Demux_StopCAT(void);

#endif


