/*****************************************************************************
File name     	: abv_high_secrity_interface.h

Description   	: ����߰��Խӿ�

Copyright (C) 	: ABV 2012

R&D Group	: ABV_CA

Author(s)	    	:  liuch

Notes          	: 

History	    	: 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2011��3��24��	       liuch		Created 
2.1			2011��9��10��	       liuch		edit for ali
2.2			2012��10��28��	       liuch		edit for avit


*****************************************************************************/
#ifndef __ABV_HIGH_SECRITY_INTERFACE_H__
#define __ABV_HIGH_SECRITY_INTERFACE_H__


#ifdef __cplusplus
extern "C" {
#endif      


/****************************************************************************
name          	: 	ABV_Secrity_Nvm_Read
Description  	:	secrity nvm memroy read function
Parameters    : 	
data: data buffer ,read data to this buffer.
len: byte number of read data.
pos: start position of read.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			: 
****************************************************************************/
ABV_Boolean ABV_Secrity_Nvm_Read(ABV_UInt8* data, ABV_UInt16 len, ABV_UInt16 pos);

/****************************************************************************
name          	: 	ABV_Secrity_Nvm_Wirte
Description  	:	secrity nvm memory write function
Parameters    : 	
data :pointer of data buffer ,which will be write to nvm memroy.
len: byte number of data .
pos:start position of write.
Return Value  : 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			
****************************************************************************/
ABV_Boolean ABV_Secrity_Nvm_Wirte(ABV_UInt8* data, ABV_UInt16 len, ABV_UInt16 pos);

/****************************************************************************
name          	: 	ABV_Secrity_Get_MCode
Description  	:	get code of advanced security chip manufactory
Parameters    : 	code of main chip manufactory. 1:hair.2:gx.3:Mstar.4:ali.5:montage
Return Value  : 	ABV_VOID
NOTES			
****************************************************************************/
ABV_VOID ABV_Secrity_Get_MCode(ABV_UInt8* code);


#ifdef __cplusplus
}
#endif
#endif