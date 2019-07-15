#ifndef _CAK_H
#define _CAK_H

#include "DVN_Type_def.h"

/**************************************************
* CAK implement																		*
**************************************************/
extern INT32	cak_Init(void);
extern void	    cak_SystemRun(void);
extern void	    cak_TimerTrigger(void);
extern INT32	cak_StopKernel(void);
extern INT32	cak_RestartKernel(void);
extern void	    cak_SetConfiguration(INT32 Mode);
extern INT32    CAKCALL_OSUpdate(void); // 保留接口-如果CAK调用 直接返回 1

//
extern INT32	cak_GetSTBAttribute(UINT8 *att);
extern INT32	cak_GetSmartCardID(UINT8* scid);
extern INT32	cak_GetAccountNo(UINT8* accountno);
extern INT32	cak_ReadSysDescriptor(UINT8 index, UINT8 *sys_descriptor);
extern INT16	cak_GetCASID(void);
extern void	    cak_GetSmartCardVersion(UINT8 *Version);
extern INT32	cak_GetUserType(void);
extern INT32	cak_PortingVendor(UINT8 *name);
extern INT32	cak_BuildDate(UINT8 *date);
extern INT32	cak_SmartCardPaired(void);
extern INT32	cak_VersionReport(UINT8 *cak_version);
extern INT32	cak_GetTwoCASID(void);
//
extern INT32	cak_GetSizeofSubscriptionRecord(INT32 select);
extern INT32	cak_GetSubscriptionRecord(INT8 select, UINT8* sub_record);
extern INT32	cak_CheckSubscription(INT32 Product_ID);
extern INT32	cak_CheckProductID(INT32 Product_ID);
//
extern INT32	cak_GetTokenValue(float* value);
extern INT32	cak_ConfirmChangeToken(UINT8 index);
extern INT32	cak_CancelChangeToken(UINT8 index);
extern INT32	cak_DeductToken(float value, UINT8 type, UINT32 id);
//
extern INT32	cak_GetSizeofTransactionRecord(void);
extern INT32	cak_GetTransactionRecord(INT16 no_of_record, UINT8* trans_record);
//
extern INT32	cak_StartGettingECM(INT16 PID, INT16 ECMPID, INT16 EventID);
extern INT32	cak_StopGettingECM(INT16 ECMPID);
//
extern INT32	cak_PerformPairing(UINT8 *temp_address);
//
extern INT32	cak_GetSmartCardUserData(UINT8 bankno, UINT8 *data);
extern INT32	cak_SetSmartCardUserData(UINT8 bankno, UINT8 *data);
extern INT32	cak_CryptoEngine(INT32 mode, UINT8 *sdata, INT32 slen, UINT8 *ddata, INT32 *dlen);
//
extern INT32	cak_SetPinCode(UINT8 *old_pin, UINT8 *new_pin);
extern INT32	cak_GetRating(UINT8 *rating);
extern INT32	cak_SetRating(UINT8 *pin, UINT8 rating);
//
typedef void	(*Func)(int code);
extern  void	cak_InstallMSCallBack(Func msgcode);
extern  INT32	cak_GetMSType(int *Type);
extern  INT32	cak_GetMasterSmartCardID(unsigned char *ID);
extern  INT32	cak_GetMasterSmartCardExpiryDate(unsigned char * DateTime);
extern	INT32	cak_GetSlaveSmartCardExpiryDate(unsigned char * DateTime);
//
typedef void (*IPPV_CBFUNC_STATUS)(UINT8 *Data);
extern	void	cak_InstallCallBackFunc(INT32 Type, void *CBFunc);
extern	INT32	cak_AddIPPVSubscription(INT32 productID, float price, UINT8 *startTime, UINT8 *endTime, UINT8 *transTime, UINT8 *Pin);
extern	INT32	cak_GetSizeofIPPVSubscriptionRecord(void);
extern	INT32	cak_GetIPPVSubscriptionRecord(UINT8* sub_record);
//
extern INT32   cak_GetWorktime(UINT8* sHour, UINT8* sMin, UINT8* sSec, UINT8* eHour, UINT8* eMin, UINT8* eSec);
extern INT32   cak_SetWorktime(UINT8 sHour, UINT8 sMin, UINT8 sSec, UINT8 eHour, UINT8 eMin, UINT8 eSec, UINT8 *pin);

/**************************************************
* STB implement																		*
**************************************************/
extern	DVN_RTOS_RESULT	DVN_RTOS_Initialize(void);
extern	DVN_RTOS_RESULT	DVN_RTOS_CreateSemaphore(BYTE* semaphoreName, DWORD tokenCount, DVN_RTOS_SEMAPHORE* semaphoreID);
extern	DVN_RTOS_RESULT	DVN_RTOS_DeleteSemaphore(DVN_RTOS_SEMAPHORE whichSemaphore);
extern	DVN_RTOS_RESULT	DVN_RTOS_AcquireSemaphore(DVN_RTOS_SEMAPHORE whichSemaphore, DWORD timeout);
extern	DVN_RTOS_RESULT	DVN_RTOS_ReleaseSemaphore(DVN_RTOS_SEMAPHORE whichSemaphore);
extern	DVN_RTOS_RESULT	DVN_RTOS_CreateQueue(BYTE* queueName, WORD maxElements, WORD elementSize, DVN_RTOS_MSG_QUEUE* queueID);
extern	DVN_RTOS_RESULT	DVN_RTOS_DeleteQueue(DVN_RTOS_MSG_QUEUE queueID);
extern	DVN_RTOS_RESULT	DVN_RTOS_EmptyQueue(DVN_RTOS_MSG_QUEUE queueID);
extern	DVN_RTOS_RESULT	DVN_RTOS_SendQueue(DVN_RTOS_MSG_QUEUE queueID, BYTE* messageData);
extern	DVN_RTOS_RESULT	DVN_RTOS_ReceiveQueue(DVN_RTOS_MSG_QUEUE queueID, DVN_RTOS_QUEUE_MODE mode,	DWORD timeout, BYTE* receiveData);
extern	DVN_RTOS_RESULT	DVN_RTOS_Sleep(DWORD delay);
//
extern	INT32	CAKCALL_SysInit( void );
extern	SC_RESULT_CODE 	SC_initialization ( UINT8 *ATR, UINT32 Clock_frequency );
typedef void ( *TypeCardEventCB )( SC_EVENT_TYPE EventFlag );
extern	SC_RESULT_CODE	RegisterEventNotification(TypeCardEventCB EventFunc );
extern	SC_RESULT_CODE	SC_send(UINT8*pBuf, UINT16 Len,UINT32 Timeout );
extern	SC_RESULT_CODE	SC_receive( UINT8 *pBuf, UINT16 *SC_bytecount, UINT16 Len, UINT32 Timeout );
//
extern	INT32	CAKCALL_StartSectionFilter (UINT8 FilterID, UINT16 PID, UINT16 TableID, UINT8 Period, UINT16 *SectByte, DVN_RTOS_MSG_QUEUE QueueID);
extern	INT32	CAKCALL_StopSectionFilter( UINT8 FilterID );
extern	INT32	CAKCALL_StartCAT(DVN_RTOS_MSG_QUEUE queueID );
//
extern	INT32 	CAKCALL_GetTotalDescrambler(void );
extern	INT32	CAKCALL_AllocDescrambler( UINT16 PID, INT32 descrambler_no );
extern	INT32	CAKCALL_FreeDescrambler( UINT16 PID, INT32 descrambler_no );
extern	INT32 	CAKCALL_InstallScramblingKey( UINT8 *Key, INT32 Index );
//
extern	INT32	CAKCALL_ReadEEPROM (UINT32 Address, UINT32 Size, UINT8 *Data );
extern	INT32	CAKCALL_WriteEEPROM( UINT32 Address, UINT32 Size, UINT8 *Data );
//
extern	void*	CAKCALL_MemAlloc( UINT32 Size );
extern	void	CAKCALL_FreeMemory( void * ptr );
extern	INT32	CAKCALL_Memcpy ( void *ptr1, void *ptr2, INT32 Len );
//
extern	INT32	CAKCALL_STBOn( void );
extern	INT32	CAKCALL_STBOff( void );
extern	INT32	CAKCALL_TokenChange( float p, INT32 Index );
extern	INT32	CAKCALL_UserDefinedAction( UINT8 *DataPtr,INT32 DataLen );
extern	void	CAKCALL_UploadTransactionRecord( void );
extern	void	CAKCALL_ReportStatus( INT32 ReportCode );
extern	INT32	CAKCALL_GetSystemDateAndTime(UINT8 *DateTime );
extern	void	CAK_DEBUG_PrintStr( INT8 *string );
extern	void	CAK_DEBUG_PrintHex( UINT32 data, INT32 size );
extern	void	CAK_DEBUG_PrintChar( INT8 data );
#endif

