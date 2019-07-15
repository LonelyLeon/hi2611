#ifndef _HRCA_API_H_
#define _HRCA_API_H_

#include "hrca_config.h"
#include "dSys.h"
#include "dScroll.h"

#if HR_CA_DEBUG_TIME_RECORD
extern uint32_t __ca_time_record_start;
extern CA_BOOL __ca_time_record_run;

#define CA_TIME_RECORD_START(_s)   {\
                                    __ca_time_record_start = d_sys_get_time();\
                                    __ca_time_record_run = D_TRUE;\
                                    HRCA_SerialPrint(_s "::CA start time record AT \"%s\"(%d)\n", __FILE__, __LINE__);\
                                }
#define CA_TIME_RECORD_ONE(_s)     if(__ca_time_record_run == D_TRUE)\
                                {\
                                    uint32_t __t = d_sys_get_time() - __ca_time_record_start;\
                                    HRCA_SerialPrint(_s "::CA Record time %d ms AT \"%s\"(%d)\n", __t, __FILE__, __LINE__);\
                                }
#define CA_TIME_RECORD_STOP(_s)    if(__ca_time_record_run == D_TRUE)\
                                {\
                                    uint32_t __t = d_sys_get_time() - __ca_time_record_start;\
                                    __ca_time_record_run = D_FALSE;\
                                    HRCA_SerialPrint(_s "::CA Stop time record %d ms AT \"%s\"(%d)\n", __t, __FILE__, __LINE__);\
                                }
#else
#define CA_TIME_RECORD_START(_s)
#define CA_TIME_RECORD_ONE(_s)
#define CA_TIME_RECORD_STOP(_s)
#endif

/******************************** api**********************************************/

extern void UrgencyBroadcast_Task(void *p_arg);
extern void HRCA_SetCWKey(uint8_t *CWKey, uint8_t Length, uint8_t OddOrEven,uint8_t AV_FLAG, uint8_t bycwe); 
extern void HRCA_TaskSuspend(void); 
extern void HRCA_TaskResume(void);
extern uint32_t HRCA_GetCurCAS(void);
extern CA_BOOL HRCA_SaveCurCAS(uint32_t currentCAS);
extern uint8_t HRCA_GetCurLan(void);
extern void HRCA_GetCAPrivateInfo(uint8_t **pcainfo);
extern void HRCA_SetCAPrivateInfo(uint8_t *pcainfo);
extern void HRCA_GetCASpecialFuncInfo(uint8_t *pcainfo);
extern D_Result HRCA_ScrollCallback(D_HScroll handle, D_ScrollUsrParas paras, D_ScrollState state);
extern uint32_t HRCA_GetCurTime (void);
extern void HRCA_StopOrRestart_Sync (uint8_t* pucOddKey, uint8_t* pucEvenKey);
extern D_Result HRCA_Burn_OTPInfo(uint8_t* potpinfo, uint16_t len, uint16_t addr);
extern D_Result HRCA_Read_OTPInfo(uint8_t* potpinfo, uint16_t len, uint16_t addr);
extern D_Result HRCA_Read_TVType(unsigned char *tvtype) ;

#endif
