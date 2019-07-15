#ifndef _UDRM_SYSTEM_API_H_
#define _UDRM_SYSTEM_API_H_

#include "unitend.h"
/*------start OS API-----------------------*/

// memory API
extern void *UTIMalloc(UTI_UINT32 memSize);

extern void *UTIReallocMem(void *ptr, UTI_UINT32 memSize);

extern void UTIFree(void *memAddr);

extern void *UTIMemSet(void *ptr, UTI_UINT8 val, UTI_UINT32 len);

extern void *UTIMemCopy(void *dest, const void *src, UTI_UINT32 len);

extern UTI_SINT32 UTIMemCmp(const void *ptr1, const void *ptr2, UTI_UINT32 len);

// semaphore API
extern UTI_SINT32 UTISemaphoreCreate(UTI_UINT32 initialCount, UTI_UINT32 *semaphore);

extern UTI_SINT32 UTISemaphoreDestroy(UTI_UINT32 semaphore);

extern UTI_SINT32 UTISemaphoreWait(UTI_UINT32 semaphore,UTI_UINT32 ms);

extern UTI_SINT32 UTISemaphoreRelease(UTI_UINT32 semaphore);

// task API
extern UTI_SINT32 UTICreateTask(void *ppFunc, void *pID, UTI_UINT32 priority, UTI_UINT32 stackSize);


// message queue API
extern UTI_SINT32 UTIMessageQueueCreate(UTI_UINT32 msgNum, UTI_UINT32 msgUnitSize, UTI_UINT32 *messageQueue);

extern UTI_SINT32 UTIMessageQueueDestroy(UTI_UINT32 messageQueue);

extern UTI_SINT32 UTIMessageQueueReset(UTI_UINT32 messageQueue);

extern UTI_SINT32 UTIMessageClaim(UTI_UINT32 messageQueue, UTI_UINT32 waitMilliseconds, void **message);

extern UTI_SINT32 UTIMessageFree(UTI_UINT32 messageQueue, void *message);

extern UTI_SINT32 UTIMessageSendToQueue(UTI_UINT32 messageQueue, void *message);

extern UTI_SINT32 UTIMessageReceiveFromQueue(UTI_UINT32 messageQueue, UTI_UINT32 waitMilliseconds, void **message);


// other OS API
extern UTI_SINT32 UTISleep(UTI_UINT32 ms);
/*------end OS API-----------------------*/

extern UTI_SINT32 UDRMPrint(const UTI_CHAR * format, ...);

#endif

