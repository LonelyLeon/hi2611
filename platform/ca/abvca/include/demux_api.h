/*****************************************************************************
File name     : demux_api.h

Description   : Define the interface of Dmux API

Copyright (C) : ABV 2006

R&D Group	    : ABV_CA

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_DEMUX_API_H__
#define __ABV_DEMUX_API_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"


/*CA 模块对DEMUX 的操作*/

typedef enum
{
	CA_DMX_OK,
	CA_DMX_ERR,
	CA_DMX_NO_FREE_CHANNEL,
	CA_DMX_NO_FREE_FILTER,
	CA_DMX_ERR_DATA
}CA_DMX_Return;



/*****************************************************************************************************
*************************Demux Driver ( 解服用部分)***********************************************
******************************************************************************************************/


/****************************************************************************
name          	: 	ABV_STBCA_Demux_SetChannelPID
Description     :      Allocate and set demux channel PID
Parameters    : 	bContReceive : ABV_FALSE//:单次搜索ABV_TRUE//连续搜索
				channelID : channel id
				Pid : PID	
Return Value  : 	CA_DMX_ERR_DATA : fail
				CA_DMX_OK : succeed
NOTES	    
****************************************************************************/
CA_DMX_Return ABV_STBCA_Demux_SetChannelPID(ABV_Boolean bContReceive,OUT ABV_UInt8 *channelID, ABV_UInt16 Pid)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Demux_StartChannel
Description     :      start or restart channel
Parameters    : 	channelID : channel id
Return Value  : 	CA_DMX_ERR : fail
				CA_DMX_OK : succeed
NOTES		:      
****************************************************************************/
 CA_DMX_Return ABV_STBCA_Demux_StartChannel(IN ABV_UInt8 channelID)FUNC_TYPE;
/****************************************************************************
name          	: 	ABV_STBCA_Demux_StopChannel
Description     :      stop a channel
Parameters    : 	channelID : channel id
Return Value  : 	CA_DMX_ERR : fail
				CA_DMX_OK : succeed
NOTES		:      
****************************************************************************/
 CA_DMX_Return ABV_STBCA_Demux_StopChannel(ABV_UInt8 channelID)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Demux_AllocateFilter
Description     :      allocate a free filter and associate it to a channel,set filter type
Parameters    : 	channelID : channel id
				filterslot : filter id
				filter : filter data
				mask : mask data
				len : datasize
Return Value  : 	CA_DMX_ERR : fail
				CA_DMX_OK : succeed
****************************************************************************/
CA_DMX_Return ABV_STBCA_Demux_SetFilter(ABV_UInt8 channelID, OUT ABV_UInt8 *filterslot,IN ABV_UInt8* filter, IN ABV_UInt8* mask,ABV_UInt8 len)FUNC_TYPE;

/****************************************************************************
name          	: 	ABV_STBCA_Demux_FreeChannel
Description     :      Free current slot
Parameters    : 	channelID:current slot num 	
Return Value  : 	CA_DMX_ERR : fail
				CA_DMX_OK : succeed
NOTES		:      
****************************************************************************/
CA_DMX_Return ABV_STBCA_Demux_FreeChannel(ABV_UInt8 channelID)FUNC_TYPE;
/****************************************************************************
name          	: 	ABV_STBCA_Data_Copy
Description     :   send the data that has been filted to CAS
Parameters    : 	channelID:channel ID 
					buffer:OUT data		
Return Value  : 	None
NOTES		:      
****************************************************************************/
ABV_Boolean ABV_STBCA_Data_Copy(ABV_UInt8 channelID,ABV_UInt16 size,OUT ABV_UInt8 *buffer)FUNC_TYPE;
/****************************************************************************
name          	: 	ABV_STBCA_Demux_FreeFilter
Description     :      Free current filter
Parameters    : 	channelID:current slot number 	
				filterslot: current filter number
Return Value  : 	CA_DMX_ERR : fail
				CA_DMX_OK : succeed
NOTES		:      
****************************************************************************/
CA_DMX_Return ABV_STBCA_Demux_FreeFilter(ABV_UInt8 channelID,ABV_UInt8 filterslot)FUNC_TYPE;
/****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif

