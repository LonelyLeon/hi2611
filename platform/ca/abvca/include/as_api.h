/*****************************************************************************
File name     : as_api.h

Description   :  define Advanced security functions 

Copyright (C) : ABV 2012

R&D Group	    : ABV

Author(s)	    :  liuch 

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
1.0			2012,1012	      	liuch		Created
*****************************************************************************/

#ifndef _ABV_AS_API_H_
#define _ABV_AS_API_H_


#ifdef __cplusplus
extern "C" {
#endif      


typedef enum _encrypt_type_
{
	TDES_TYPE=0,
	AES_TYPE,
    DES_TYPE,

	MAX_ENCRYPT_TYPE
} ABV_Encrypt_Type_e;


/****************************************************************************
name          	: 	ABV_AS_Get_ChipID
Description  	:	get chip ID of  main chip
Parameters    : 	
chipID:chipID in byte.
len:byte number  of chipID
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			: 
****************************************************************************/
ABV_Boolean  ABV_AS_Get_ChipID(ABV_UInt8 chipID[6]);

/****************************************************************************
name          	: 	ABV_AS_ChipOTP_Read
Description  	:	chip OTP  memroy read function
Parameters    : 	
data: data buffer ,read data to this buffer.
len: byte number of read data.
pos: start position of read.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			: 
****************************************************************************/
ABV_Boolean ABV_AS_ChipOTP_Read(ABV_UInt8* data, ABV_UInt16 len, ABV_UInt16 pos);
/****************************************************************************
name          	: 	ABV_AS_ChipOTP_Wirte
Description  	:	chip OTP  memory write function
Parameters    : 	
data :pointer of data buffer ,which will be write to nvm memroy.
len: byte number of data .
pos:start position of write.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_AS_ChipOTP_Wirte(ABV_UInt8* data, ABV_UInt16 len, ABV_UInt16 pos);

/****************************************************************************
name          	: 	ABV_AS_SetKey1
Description  	:	set key1 to main chip
Parameters    : 	
key1: key1 data.
key1_type: encrypt type of key1
cw_type: encrypt type of CW.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_AS_SetKey1(ABV_UInt8 key1[16], ABV_Encrypt_Type_e key1_type,  ABV_Encrypt_Type_e cw_type);
/****************************************************************************
name          	: 	ABV_AS_SetKey2
Description  	:	set key2 to main chip
Parameters    : 	
key2: key2 data
type :encrypt type of key2.
index: root key index
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_AS_SetKey2(ABV_UInt8 key2[16], ABV_Encrypt_Type_e type, ABV_UInt8 index);


/****************************************************************************
name          	: 	ABV_set_ca_mod
Description  	:	switch SDK mode between advaced security and common scrambled.
Parameters    : 	
 param: 
 				true: set sdk mode tobe advaced security mode.
 				falsh:set sdk mode to be common scrambled mode.
Return Value  :void
NOTES			
****************************************************************************/
void ABV_set_ca_mod(ABV_Boolean  param);

/****************************************************************************
name          	: 	ABV_AS_SetKey
Description  	:	set as key to main chip
Parameters    : 	
				cwkey: the key used to encrypt CW
				rootkey_index:index of rootkey used to encrypted cwkey.
				rootkey_type: cipher type of cwkey.
				cwkey_type: cipher type of CW
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_AS_SetKey(ABV_UInt8 cwkey[16], ABV_UInt8 rootkey_index,ABV_Encrypt_Type_e rootkey_type,  ABV_Encrypt_Type_e cw_type);

/****************************************************************************
name          	: 	ABV_AS_GetPubKey
Description  	:	get RSA publick in OTP
Parameters    : 	
				pub_N:pointer to buffer to store N of public key.max size is 256 byte.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_AS_GetPubKey(ABV_UInt8* pub_N);

/****************************************************************************
name          	: 	ABV_AS_SendStatus
Description  	:	send out as status of ABV as init progress.
Parameters    : 	status : 0 set as key ok.
				
Return Value  : 	ABV_VOID
NOTES			
****************************************************************************/
void ABV_AS_SendStatus(ABV_UInt8 status);

#ifdef __cplusplus
}
#endif

#endif

