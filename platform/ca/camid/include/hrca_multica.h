/*************************************************************************************************

File Name      :  hrca_multica.h

Description    :  

Copyright(C)   :  Haier_IC 2013

Project Group  :  CA

Author(s)      :  hanjf

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2013-02-21     hanjf          created              ---

**************************************************************************************************/

/*******************************Includes************************************************/

#ifndef _MULTICA_FUN_H_
#define _MULTICA_FUN_H_

#include <stdint.h>
#include "hrca_config.h"
#include "dCA.h"

#if ((EMBED_CA & CDCA) == CDCA)
#include "dca/cdca_fun.h"

#endif

#if ((EMBED_CA & DVTCA) == DVTCA)
#include "dca/dvtca_fun.h"

#endif

#if ((EMBED_CA & CTICA) == CTICA)
#include "dca/ctica_fun.h"

#endif

#if ((EMBED_CA & MGCA) == MGCA)
#include "dca/mgca_fun.h"

#endif

#if ((EMBED_CA & TRCA) == TRCA)
#include "dca/trca_fun.h"
#endif


#if ((EMBED_CA & WFCA) == WFCA)
#include "dca/wfca_fun.h"

#endif

#if ((EMBED_CA & QZCA) == QZCA)
#include "dca/qzca_fun.h"

#endif

#if ((EMBED_CA & XGCA) == XGCA)
#include "dca/xgca_fun.h"
#endif

#if ((EMBED_CA & DIVICA) == DIVICA)
#include "dca/divica_fun.h"
#endif

#if ((EMBED_CA & DSCA) == DSCA)
#include "dca/dsca_fun.h"
#endif

#if ((EMBED_CA & GOSCA) == GOSCA)
#include "dca/gosca_fun.h"

#endif

#if ((EMBED_CA & ABVCA) == ABVCA)
#include "dca/abvca_fun.h"

#endif

#if ((EMBED_CA & THTFCA) == THTFCA)
#include "dca/thtfca_fun.h"

#endif

#if ((EMBED_CA & LXDTCA) == LXDTCA)
#include "dca/lxdtca_fun.h"

#endif

#if ((EMBED_CA & YJCA) == YJCA)
#include "dca/yjca_fun.h"

#endif

#if ((EMBED_CA & SCCA) == SCCA)
#include "dca/scca_fun.h"

#endif

#if ((EMBED_CA & COLABLECA) == COLABLECA)
#include "dca/colableca_fun.h"
#include "../../colableca/include/cas_hcn.h"
extern int8_t hcnOsdMsg[10][256];
extern uint8_t hcnca_isPPTV;
#endif

/******************************Variable*******************************************/

/*****************************CA public function*****************************************/
extern uint32_t OSD_InNum;
extern uint32_t OSD_OutNum;
extern uint8_t  OSD_ShowNext;

extern char OsdMsg[MAX_OSD_NUM][MAX_OSD_LEN];

#if HR_CA_SCROLL_ON_OFF
extern int Scrollhandletop;
extern int Scrollhandlebottom;
//static D_HScroll Scrollhandlemiddle;
#endif

extern uint8_t CASpecialFunc;
/********************************multica api**********************************************/

extern CA_BOOL HRCASTB_Init(void);
extern CA_BOOL HRCASTB_Exit(uint32_t CASDEF);
extern CA_BOOL HRCASTB_SCInsert(void);
extern CA_BOOL HRCASTB_SCRemove(void);
extern void HRCASTB_ServiceClear(uint8_t flag);
extern CA_BOOL HRCASTB_SysIDCheck(uint16_t u16SysID);
extern void HRCA_Init_PMTData(void);
extern void HRCA_MonitorPMT(void);
extern void HRCASTB_SetEcmpid(uint16_t u16EcmPID, uint16_t u16ServiceID, uint16_t u16PID, uint8_t u8Type);
extern void HRCASTB_StopEcmpid(uint16_t u16EcmPID);
extern void HRCA_MonitorCAT(void);
extern void HRCASTB_SetEmmpid(uint16_t u16EmmPID, uint8_t u8Type);
extern void HRCASTB_StopEmmpid(uint16_t u16EmmPID);
extern void HRCASTB_ServiceChangeState(D_CASrvInfo* P_CAInfo, uint8_t u8State, uint8_t u8Start);
extern void HRCASTB_DataReadyNotify(int32_t slot, uint8_t *u8Data, uint16_t u16DataLen);
extern void HRCA_Monitor(uint32_t seconds);
extern void HRCA_ClearCATip(void);
extern void HRCA_ClearPmtTip(void);
extern void HRCA_AddCATip(void);
extern uint16_t HRCASTB_GetScNo(char* sc);
extern void HRCA_PurseSPUData(void);
extern void HRCA_SCPUInit_End(void);
extern void HRCA_ClearCOSTip(void);
extern void HRCA_ShowCOSMessage(void);
extern void HRCA_BackCOSFlashData(uint8_t type, uint8_t *buffer, uint8_t lenth);
extern void HRCA_GetSCNetID(uint8_t *pu8NetId);

#endif


