/*****************************************************************************
File name     : os_api.h

Description   : Define the interface of OS API

Copyright (C) : ABV 2006

R&D Group     : ABV_CA

Author(s)     :  zhangxl    

Notes         : 

History	      : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_OS_API_H__
#define __ABV_OS_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"


/*****************************************************************************************************
*************************OS ( 操作系统部分)*****************************************************
******************************************************************************************************/

/****************************************************************************
Name          	: 	ABV_STBCA_OS_Task_Create
Description     :      create a new task
Parameters    : 	task_fun : task function pointer
                            param : task function parameter point
                            priority : task priority 
                            stack_size : task stack size 
Return Value  : 	ABV_FALSE : success to create a new task
				ABV_TRUE : fail to create a new task
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Task_Create(IN void (*task_fun)(void), IN ABV_Pointer param, IN ABV_Int32  priority, IN ABV_Int32 stack_size)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Task_Sleep
Description     :      task suspend for a regular time
Parameters    : 	sleep_time : task suspend time(xxms)
Return Value  : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Task_Sleep(IN ABV_Int32  sleep_time)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Semaphore_Create
Description     :      create a semaphore
Parameters    : 	semaphore : pointer to a semaphore
				init_value : initial value  
Return Value  : 	ABV_FALSE : success to create a semaphore
				ABV_TRUE : fail to create a semaphore
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Semaphore_Create(OUT ABV_Semaphore_Handle* semaphore,IN ABV_UInt32  init_value )FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Semaphore_Signal
Description     :      Signal a semaphore
Parameters    : 	semaphore : pointer to a semaphore				
Return Value  : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Semaphore_Signal(IN ABV_Semaphore_Handle  semaphore)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Semaphore_Wait
Description     :      wait for a semaphore
Parameters    : 	semaphore : pointer to a semaphore				
Return Value  : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Semaphore_Wait(INOUT ABV_Semaphore_Handle  semaphore )FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Semaphore_Wait
Description     :      wait for a semaphore
Parameters    : 	semaphore : pointer to a semaphore				
Return Value  : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Semaphore_WaitTimeOut(INOUT ABV_Semaphore_Handle  semaphore , ABV_UInt32 time_out)FUNC_TYPE;


/****************************************************************************
name          	: 	ABV_STBCA_OS_Message_Create
Description     :      create a Message queue
Parameters    : 	queue : pointer to a queue		
				max_size : maxium size of every message
				message_count : the number of message
Return Value  : 	ABV_FALSE : success to create a mail quequ
				ABV_TRUE : fail to create a mail quequ
NOTES		: 
****************************************************************************/
ABV_Boolean  ABV_STBCA_OS_Message_Create(OUT ABV_Queue_Handle* queue, ABV_UInt32  max_size, ABV_UInt32 message_count)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Message_Receive
Description     :      receive messages coming from a Message queue
Parameters    : 	queue : point to a Message queue
				msg :  point to the message data
				size : the size of the message
Return Value  : 	ABV_FALSE : success to send message
				ABV_TRUE : fail to send message
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Message_Receive(IN ABV_Queue_Handle queue, OUT ABV_Pointer msg, ABV_UInt32 size)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Message_Receive_TimeOUT
Description     :      receive messages coming from a Message queue
Parameters    : 	queue : point to a Message queue
				msg :  point to the message data
				size : the size of the message
				timeout:(ms)
Return Value  : 	ABV_FALSE : success to send message
				ABV_TRUE : fail to send message
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Message_Receive_TimeOUT(IN ABV_Queue_Handle queue, OUT ABV_Pointer msg, ABV_UInt32 size ,ABV_UInt32 timeout)FUNC_TYPE;


/****************************************************************************
Name          	: 	ABV_STBCA_OS_Message_Send
Description     :      send message to a Message queue
Parameters    : 	queue : point to a Message queue
				msg :  point to the message to be sent
				size : the size of the message to be sent
Return Value  : 	ABV_FALSE : success to send message
				ABV_TRUE : fail to send message
NOTES		: 
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Message_Send(IN ABV_Queue_Handle  queue,IN ABV_Pointer msg, ABV_UInt32  size)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Memory_Alloc
Description     :      allocate memory for CA
Parameters    : 	buffer_size : buffer size   
Return Value  : 	ABV_Pointer : point to memory allocated to CA 
NOTES		:      if it returns ABV_NULL, no enough memory to use 
****************************************************************************/
ABV_Pointer ABV_STBCA_OS_Memory_Alloc(ABV_UInt32  buffer_size)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Memory_Free
Description     :      release memory
Parameters    : 	buff : point to the buffer to be released 
Return Value  : 	Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Memory_Free(ABV_Pointer buff)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Memory_Set
Description     :      set a memory region to a regular value
Parameters    : 	buff : point to the buffer to be set
				c : the value to be set
				size : size to be set
Return Value  : point to the buffer to be set
NOTES		:      
****************************************************************************/
ABV_Pointer ABV_STBCA_OS_Memory_Set(IN ABV_Pointer buff, ABV_UInt8 c, ABV_UInt32 size )FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_OS_Memory_Copy
Description     :      copy data from a region to another region
Parameters    : 	target : target memory address
				source : source memory address
				size : memory size to be copied
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE
NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_OS_Memory_Copy(IN ABV_Pointer target, IN ABV_Pointer source, ABV_UInt32 size)FUNC_TYPE;


/****************************************************************************
name          	: 	ABV_STBCA_OS_Printf
Description     :      Print format information
Parameters    : 	message Debug information
Return Value  :      NONE
NOTES		:      
****************************************************************************/
void ABV_STBCA_OS_Printf(ABV_Char *format, ...);


/*******************************************************************************************************
Function	:Send Data info to other STB.
Parameters	:pBuffer:data,it will be send to other STB
return		:ABV_ FALSE：Send Message success.
		 ABV_TRUE：Send Message Failed.
*******************************************************************************************************/
ABV_Boolean ABV_STBCA_Send_MSG_CA2OtherSTB(ABV_UInt8 *pBuffer,ABV_UInt8 Length,ABV_UInt32 TimeOut)FUNC_TYPE;

void GPRS_DISP(ABV_Char*format,...) ;


/****************************************************************************
name          		: 	ABV_STBCA_Get_StbTime
Description  		:	Get local time
Parameters    		: 	year,month, month, day, hour, minutesecond,(OUT):local time
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	
****************************************************************************/

ABV_Boolean ABV_STBCA_Get_StbTime(ABV_UInt32 *year,ABV_UInt8 *month,ABV_UInt8 *day,ABV_UInt8 *hour,ABV_UInt8 *minute,ABV_UInt8 *second)FUNC_TYPE;


/****************************************************************************
name          	: 	ABV_Send_COSStatus
Description     :      send Cos status to STB
Parameters    : 	status: 
				0:cos worked ok.
				1:configration failed.
				2:issuer init failed
				3: entitle init failed
Return Value  : void
NOTES		:      
****************************************************************************/
ABV_VOID ABV_Send_COSStatus(ABV_UInt8 status);
/*********************************end***************************************/
#ifdef __cplusplus
}
#endif
#endif

