/*****************************************************************************
File name     : uart_api.h

Description   : Define the interface of UART API

Copyright (C) : ABV 2008

R&D Group	    : ABV_CA 3.3

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2008.05.12	       zhangxl		Created
2.1			2014.06.10		liuch			edit			edit uart api for comsc
*****************************************************************************/
#ifndef __ABV_UART_API_H__
#define __ABV_UART_API_H__

#ifdef __cplusplus
extern "C" {
#endif

 /*****************************************************************************************************
*************************UART Driver (´®¿ÚÍ¨Ñ¶)***********************************************
******************************************************************************************************/

/****************************************************************************
Name          	: 	ABV_STBCA_Uart_AllocateAndOpen
Description    	:	Open an exclusive UART 
Parameters   	:	void
Return Value 	:	handle of UART
NOTES		: 
****************************************************************************/
ABV_UInt32 ABV_STBCA_Uart_AllocateAndOpen(void)FUNC_TYPE; 
/****************************************************************************
Name          	: 	ABV_STBCA_Uart_Release
Description    	:	Close an UART
Parameters   	:	UartHandle: handle of uart that was allocated by STB when open UART
Return Value 	:	void
NOTES		: 
****************************************************************************/
void ABV_STBCA_Uart_Release(ABV_UInt32 UartHandle)FUNC_TYPE; 

/****************************************************************************
Name          	: 	ABV_STBCA_Uart_Read
Description    	:	read data from UART
Parameters   	:	UartHandle: handl of uart that was allocated by STB when open uart
				pBuffer: (IN_OUT) buffer to store data
				SizeToRead: (IN)len of data will be read.
				ActualRead:(OUT) Actual byte that was read.
				Timeout:(IN): Time out in ms. if the read action has'n finished in timeout return failed.
Return Value 	:	success:ABV_FALSE, failed:other value 
NOTES		:       ABV smart card's serial  baul rate is 9600
                        *ActualRead must get the real read data number, otherwise can not get right cw
****************************************************************************/
ABV_UInt8 ABV_STBCA_Uart_Read(ABV_UInt32 UartHandle, ABV_UInt8 *pBuffer, ABV_UInt16 SizeToRead, ABV_UInt16 *ActualRead, ABV_UInt32 Timeout)FUNC_TYPE;
/****************************************************************************
Name          	: 	ABV_STBCA_Uart_Write
Description    	:	write data to Uart
Parameters   	:	UartHandle: handl of uart that was allocated by STB when open uart
				pBuffer: (IN)pointer to bufffer stored data.
				NumToWrite: (IN)len of data will be write.
				ActualWritten:(OUT) Actual byte that was written.
				Timeout:(IN): Time out in ms. if the wirte action has'n finished in timeout return failed.
Returns	   £º success:ABV_FALSE, failed:other value
NOTES	   :      ABV smart card's serial  baul rate is 9600
                  *ActualWritten must get the real read data number, otherwise can not get right cw
                  after write the datas normally need 100ms waiting for getting all return back datas
****************************************************************************/
ABV_UInt8 ABV_STBCA_Uart_Write(ABV_UInt32 UartHandle, ABV_UInt8 *pBuffer, ABV_UInt16 NumToWrite, ABV_UInt16 *ActualWritten, ABV_UInt32 Timeout)FUNC_TYPE; 
/****************************************************************************
Name          	: 	ABV_STBCA_Uart_Flush
Description    	:	flush data to Uart
Parameters   	:	UartHandle: handl of uart that was allocated by STB when open uart
Return Value 	:	void
NOTES		: 
****************************************************************************/
void ABV_STBCA_Uart_Flush(ABV_UInt32 UartHandle)FUNC_TYPE; 
/*****************************************************************************************************
*************************UART Driver END***********************************************
******************************************************************************************************/


#ifdef __cplusplus
}
#endif
#endif

