#ifndef _TX_API_H_
#define _TX_API_H_

#include "TX_Global.h"

/* User Configuration structure */
typedef struct _ST_INIT_CONFIG_
{
    uint16_t        video_cfg;
    uint16_t        audio_cfg;     
}INITCONFIG_T;

#ifdef __cplusplus
extern "C" {
#endif

TX_API  ATX_ERR TXAPI_Init(const INITCONFIG_T* pInitParam);
TX_API  ATX_ERR TXAPI_Get_Mode(uint8_t* VIndex);

TX_API  ATX_ERR TXAPI_Set_Video(uint8_t VIndex);
TX_API  ATX_ERR TXAPI_Set_Audio(void_t);
TX_API  ATX_ERR TXAPI_Tune_Quality(uint8_t VIndex);

TX_API  ATX_ERR TXAPI_Mute_All(uint8_t u8Mute);
TX_API  ATX_ERR TXAPI_Mute_Audio(uint8_t u8Mute);
TX_API  ATX_ERR TXAPI_Mute_Video(uint8_t u8Mute);

TX_API  ATX_ERR TXAPI_GetError(void_t);
TX_API  ATX_ERR TXAPI_IsHPDPresent(void_t);
    
TX_API  void_t  TXAPI_SetSinkDevice(uint8_t u8sink);
/* Note: before calling the function, you should call TXAPI_QueryEDIDInfo() firstly */
TX_API  uint8_t TXAPI_GetSinkDevice(void_t);
    
//#include "mw_hal_edid.h"
#ifdef  TX_SUPPORT_EDID_AUTO


typedef  enum _E_TX_EDID_QUERY_INFO
{
    QUERY_EDID_SINK_TYPE,
    QUERY_EDID_MON_NAME,
    QUERY_EDID_PREFER_TIMING,
    QUERY_EDID_VENDOR,
    QUERY_EDID_UNKNOWN
}eEDIDQUERYINFO;

TX_API  ATX_ERR TXAPI_QueryEDIDInfo(eEDIDQUERYINFO eID);

#endif 

#ifdef __cplusplus
}
#endif

#endif
