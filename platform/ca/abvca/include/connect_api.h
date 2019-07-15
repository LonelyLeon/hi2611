/*****************************************************************************
File name     : connect_api.h

Description   : Define the interface of connect API

Copyright (C) : ABV 2008

R&D Group	    : ABV_CA 3.3

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
3.5.0.0			2008.09.02	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_CONNECT_API_H__
#define __ABV_CONNECT_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ABV_TCPIP_
{
	ABV_UInt8 IP_Addr [4];
	ABV_UInt8 Mac_Addr[6];
	ABV_UInt16 Prot;
}ABV_TCPIP_Connect_s;

typedef enum
{
	ABV_Success, //success
	ABV_Failed, //failed 
	ABV_TimeOut //timeout
}ABV_MSG_Return_State_e;

/*****************************************************************************************************
****************************Connect Driver ( ´æ´¢Æ÷²¿·Ö)***********************************************
******************************************************************************************************/

/*******************************************************************************************************
Function	:init one physical channel for CA send message to or reciver message from other STB .
Parameters	:NONE
return		:ABV_ FALSE£ºinit success.
		 ABV_TRUE£ºinit failed.
*******************************************************************************************************/
ABV_Boolean ABV_STBCA_Init_Physical_Channel(void)FUNC_TYPE;
/*******************************************************************************************************
Function	:Send Data info to other STB.
Parameters	:pBuffer:data,it will be send to other STB
return		:ABV_ FALSE£ºSend Message success.
		 ABV_TRUE£ºSend Message Failed.
*******************************************************************************************************/
ABV_Boolean ABV_STBCA_Send_MSG_CA2OtherSTB(ABV_UInt8 *pBuffer,ABV_UInt8 Length,ABV_UInt32 TimeOut)FUNC_TYPE;
/****************************************************************************
name          : 	ABV_CASTB_Connect_State()
Description   :   	STB connect provider server success or failed?
Parameters    : 	NONE
Return Value  :      	success: ABV_FALSE  failed: ABV_TRUE
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_STBCA_Connect_State(void)FUNC_TYPE;
/*******************************************************************************************************
Funtion		:Connect Provider Server
Parameters	:TCPIP_Struct:connect parameters,STB connect Provider server by this struct.
return 		:ABV_ FALSE£ºSet Connect Parameters suceess.
		 ABV_ TRUE£ºSet Connect Parameters failed.
*******************************************************************************************************/		  
ABV_Boolean ABV_STBCA_Connect_Provider(ABV_TCPIP_Connect_s TCPIP_Struct)FUNC_TYPE;
/*******************************************************************************************************
Function	:Send Data to provider
Parameters	:pBuffer:The data will be send to provider server
return 		:ABV_ FALSE£ºSend data to provider server success.
		 ABV_ TRUE£ºSend data to provider server failed.
*******************************************************************************************************/
ABV_Boolean ABV_STBCA_Send_Data_To_Provider(ABV_UInt8 *pBuffer,ABV_UInt8 Length)FUNC_TYPE;

/*****************************************************************************************************
*************************************Connect Driver END***********************************************
*****************************************************************************************************/


#ifdef __cplusplus
}
#endif
#endif

