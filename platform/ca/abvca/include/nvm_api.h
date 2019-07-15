/*****************************************************************************
File name     : nvm_api.h

Description   : Define the interface of NVM API

Copyright (C) : ABV 2006

R&D Group	    : ABV_CA

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_NVM_API_H__
#define __ABV_NVM_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"
 /*****************************************************************************************************
*************************NVM Driver ( 存储器部分)***********************************************
******************************************************************************************************/

/****************************************************************************
name       : 	ABV_STBCA_Nvm_Init
Description： get non-volatile memory
Parameters ： address: the address of nvram
	      size: the size of nvram
Returns	   ： Suc:ABV_FALSE Fail:ABV_TRUE
NOTES	   :      
****************************************************************************/
ABV_Boolean ABV_STBCA_Nvm_Init(ABV_UInt32 size )FUNC_TYPE; 
/****************************************************************************
name       : 	ABV_STBCA_Nvm_Read
Description： read data from nvram
Parameters ： data: pointer to buffer used to store data
	      len: the length of data to read
	      position: relative address to the initial address
Returns	   ： Suc:ABV_FALSE Fail:ABV_TRUE
NOTES	   :      
****************************************************************************/
ABV_Boolean ABV_STBCA_Nvm_Read(OUT ABV_UInt8* Rdata,ABV_UInt16 len,ABV_UInt16 position)FUNC_TYPE;
/****************************************************************************
name       : 	ABV_STBCA_Nvm_Write
Description： write data to nvram
Parameters ： data: pointer to buffer used to store data
	      len: the length of data to be written
	      position: relative address to the initial address
Returns	   ： Suc:ABV_FALSE Fail:ABV_TRUE
NOTES	   :      
****************************************************************************/ 
ABV_Boolean ABV_STBCA_Nvm_Write(IN ABV_UInt8* Wdata,ABV_UInt16 len,ABV_UInt16 position)FUNC_TYPE; 
/*****************************************************************************************************
*************************NVM Driver END***********************************************
******************************************************************************************************/


/*****************************************************************************************************
*************************STB info Driver ( 机顶盒信息)***********************************************
******************************************************************************************************/

/****************************************************************************
name          	: 	ABV_CASTB_Send_STB_Info
Description     :   	CA get manufactorcode hard version soft version from stb
Parameters    : 	NONE
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_STBCA_Send_STB_Info(ABV_UInt8 *Manucode,ABV_UInt32 *HardVer,ABV_UInt32 *SoftVer)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Send_Equipment_SerieNum
Description     :   Send Equipment Series Num to CA core
Parameters    : 	SeriesNum:Series Num , max byte number is 50u.
                   		 SeriesLength:Series Length
Return Value  :      success: ABV_FALSE  failed: ABV_TRUE	
NOTES	      : 	
****************************************************************************/
ABV_Boolean ABV_STBCA_Send_Equipment_SerieNum(ABV_UInt8 *SerialNum,ABV_UInt8 *SerialLength)FUNC_TYPE;

/****************************************************************************
name          	 : 	ABV_STBCA_Write_Equipment_SerieNum
Description      :     Get STBID from STB
Parameters     : 	SeriesNum:Series Num , max byte number is 50u.
				SeriesLength:Series Length
Return Value   : 	ABV_TRUE: failed, ABV_FALSE:succed.	
NOTES		 :      
****************************************************************************/
ABV_Boolean ABV_STBCA_Write_Equipment_SerieNum(ABV_UInt8 *SerialNum,ABV_UInt8 *SerialLength)FUNC_TYPE;

/*****************************************************************************************************
*************************STB info Driver END  ***********************************************
******************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif

