/*****************************************************************************
File name     : sc_api.h

Description   : Define the interface of SC API

Copyright (C) : ABV 2006

R&D Group	    : ABV_CA

Author(s)	    :  zhangxl

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_SC_API_H__
#define __ABV_SC_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"

typedef  enum 
{
	ABV_CARD_IN = 0,
	ABV_CARD_OUT = 1,
	CARD_INIT
}SC_STATUS;

typedef enum
{
	SMART_OPT_OK  = 0,
	SMART_OPT_TIMEOUT,
	SMART_OPT_BUSY,
	SMART_CARD_OUT,
	SMART_CARD_ABNORMAL
}ABV_CASTB_SMART_Err;



/*以下部分是需要STB 实现  ，    提供给CA 的函数接口*/


/*****************************************************************************************************
*************************Smart Card Driver ( 智能卡部分)*******************************************
******************************************************************************************************/

/****************************************************************************
name          	: 	ABV_STBCA_Smart_Reset
Description     :      warm reset smartcard
Parameters    : 	
Return Value  : 	ABV_FALSE : success to reset
				ABV_TRUE : fail to reset
NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Smart_Reset(void)FUNC_TYPE;
/****************************************************************************
Name          	: 	ABV_STBCA_Get_ATR
Description     :   Get smart card ATR
Parameters    : 	
Return Value  : 	ABV_FALSE : success to get atr
				ABV_TRUE : fail to get atr
NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Get_ATR(OUT ABV_UInt8 ATR[20])FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_CASTB_Smartcard_TransferDate()
Description     : 	read data from smartcard or write data to smartcard 
parameters	: 	message : pointer to command and data
			  	message_size : the length of command and data
			  	response_data : response buffer
			  	response_size : reply data size
returns		:	ABV_Boolean 	  	
****************************************************************************/
ABV_Boolean ABV_CASTB_Smartcard_TransferData(IN ABV_UInt8*  message, IN ABV_UInt8  message_size, 
 							    OUT  ABV_UInt8*  response_data, OUT ABV_UInt8*  response_size)FUNC_TYPE;


#ifdef __cplusplus
}
#endif
#endif

