/*****************************************************************************
File name     : dsc_api.h

Description   : Define the interface of Dsc API

Copyright (C) : ABV 2006

R&D Group	    : ABV_CA

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_DSC_API_H__
#define __ABV_DSC_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"

typedef enum
{
	VIDEO_DSC,
	AUDIO_DSC	
}CA_DSC_TYPE;


/*****************************************************************************************************
*************************Descrambler Driver ( ½âÈÅÆ÷²¿·Ö)*******************************************
******************************************************************************************************/

/****************************************************************************
name          	: 	ABV_STBCA_Descrambler_SetOddKey
Description     :      set odd control word
Parameters    : 	dsc_id : descramble number
				even_key : odd key data buffer
				len : length of even data buffer
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Descrambler_SetOddKey(ABV_UInt8 dsc_id, IN ABV_UInt8* odd_key, ABV_UInt8  len)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Descrambler_SetEvenKey
Description     :      set even control word
Parameters    : 	dsc_id : descramble number
				even_key : even key data buffer
				len : length of even data buffer
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Descrambler_SetEvenKey(ABV_UInt8 dsc_id, IN ABV_UInt8* even_key, ABV_UInt8 len)FUNC_TYPE;


/****************************************************************************
Name          	: 	ABV_STBCA_Allocate_Descrambler
Description     :      allocate a free descrambler
Parameters    : 	dsc_id : descramble id
				tDSCType : descramble type
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Allocate_Descrambler(OUT ABV_UInt8 *dsc_id, CA_DSC_TYPE tDSCType)FUNC_TYPE ;

/****************************************************************************
Name          	: 	ABV_STBCA_Release_Descrambler
Description     :      release a already-allocated  descrambler
Parameters    : 	dsc_id : descramble id
				tDSCType : descramble type
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Release_Descrambler(ABV_UInt8 dsc_id, CA_DSC_TYPE tDSCType)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Descrambler_SetOddKey_UnScramble
Description     :      set odd control word
Parameters    : 	dsc_id : descramble number
				even_key : odd key data buffer
				len : length of even data buffer
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Descrambler_SetOddKey_UnScramble(ABV_UInt8 dsc_id, IN ABV_UInt8* odd_key, ABV_UInt8  len)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Descrambler_SetEvenKey_UnScramble
Description     :      set even control word
Parameters    : 	dsc_id : descramble number
				even_key : even key data buffer
				len : length of even data buffer
Return Value  : Suc:ABV_FALSE Fail :ABV_TRUE

NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Descrambler_SetEvenKey_UnScramble(ABV_UInt8 dsc_id, IN ABV_UInt8* even_key, ABV_UInt8 len)FUNC_TYPE;


#ifdef __cplusplus
}
#endif
#endif

