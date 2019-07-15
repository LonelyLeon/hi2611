/*************************************************************************************************

File Name      :  hrca_os.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-01-12     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_OS_H_
#define _HRCA_OS_H_

#include <stdint.h>
#include "hrca_config.h"

#define HRCA_ALWAYS_WAIT  (-1)
#define HRCA_IMMEDIATE_RETURN  (0)

/********************************os api**********************************************/

extern void HRCA_SerialPrint(char* pu8Format, ...);

extern void HRCA_SerialFakePrint(char* pu8Format, ...);
extern void HRCA_ErrPrint(char* pu8Format, ...);
extern CA_BOOL HRCA_TaskCreate(char* szName, void *pTaskFun, uint8_t u32Prio, uint32_t *pu32Stack, uint32_t u32StackSize, uint32_t *pu32TaskId);
extern CA_BOOL HRCA_TaskDelete(uint32_t u32TaskId);
extern CA_BOOL HRCA_TaskDelay(uint32_t u32Millisecond);
extern 	void HRCA_TaskLock(void);
extern 	void HRCA_TaskUnLock(void);
extern void* HRCA_MemoryAllocate(uint32_t u32Size);
extern void* HRCA_MemoryReallocate(void* ptr, uint32_t u32Size);
extern void HRCA_MemoryFree(void* pBuf);
extern void* HRCA_MemoryAllocate_Extend(uint32_t u32Size);
extern void HRCA_MemoryFree_Extend(void* pBuf);
extern void* HRCA_MemoryMap_Address(void* addr, uint32_t u32Size);
extern void* HRCA_SemaphoreCreate(uint8_t u8Init);
extern CA_BOOL HRCA_SemaphoreDelete(void* pSem);
extern CA_BOOL HRCA_SemaphoreWait(void* pSem, int32_t Timeout);
extern CA_BOOL HRCA_SemaphoreSignal(void* pSem);
extern CA_BOOL HRCA_QueueCreate(void **msgBox, uint32_t msgSize, uint32_t msgCount, uint32_t msgType);
extern CA_BOOL HRCA_QueueEmpty(void *msgBox);
extern CA_BOOL HRCA_QueueDelete(void *msgBox);
extern CA_BOOL HRCA_QueueClaim(void *msgBox, int32_t Timeout, void **msgPtr);
extern CA_BOOL HRCA_QueueRelease(void *msgBox, void *msgPtr);
extern CA_BOOL HRCA_QueueSendToQueue(void *msgBox, void *msgData);
extern CA_BOOL HRCA_QueueReceiveToQueue(void *msgBox, void **msgPtr, int32_t Timeout);
extern CA_BOOL HRCA_QueueSend(void *msgBox, void *msgData, uint32_t u32MsgLen, int32_t Timeout);
extern CA_BOOL HRCA_QueueReceive(void *msgBox, void **msgPtr, int32_t Timeout, uint8_t *pu8Data, uint32_t u32DataLen);
extern void HRCA_TimeDelayMs(uint32_t milliseconds);
extern uint32_t HRCA_TimeGetTicks(void);
extern uint32_t HRCA_GetTicks_NO(void);
extern void* HRCA_MutexCreate(void);
extern CA_BOOL HRCA_MutexDelete(void* pMutex);
extern CA_BOOL HRCA_MutexWait(void *pMutex);
extern CA_BOOL HRCA_MutexSignal(void* pMutex);
                              
#endif
