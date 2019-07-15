/** @file
* @brief 遥控器设备操作
* @author majy
* @date 2013-7-26 majy: 建立文件
* @date 2013-07-26 lc: 统一平台, 代码整理
*/

#ifndef _D_REMOTE_H_
#define _D_REMOTE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFP.h"


/** @brief 遥控器按键键值*/
typedef D_U32	D_RemoteKey;
typedef enum{
NEC = 1,
BESC,
DONGZHI,
RC_5
}D_RemoteCode;

/*typedef struct  
{
    D_U8   	RomoteSlaveAdd;   
    D_U32  	PulsePilot;
    D_U32  	PulseZero;
    D_U32  	PulseOne;
    D_U32  	RepeatTime;
    D_Float	ErrRange;
}D_REMOTE_Para;*/

typedef struct
{
	D_S8 repeat;
	D_U8 guid_code;
	D_U16 machine_code;
	D_U16 source_code;
}D_RemoteKeyParam;

typedef struct
{
	D_RemoteKeyParam *key;
	D_RemoteKey mapped_key;
}D_RemoteMapHookParam;

typedef struct
{   
    D_U8  remotetpye;
    D_U16  pulsepilot;
    D_U16  pulsesecondpilot;
    D_U16  pulselong;
    D_U16  pulseshort;
    D_U16  repeattime;
    D_U8  errorrange;
}D_IRDbgOpenParam;

/** @brief 遥控器初始化 
* 
*在调用遥控器函数时首先调用此函数 
* @retval D_OK	初始化成功 
* @retval D_ERR	初始化失败 
*/ 
D_Result 
d_remote_open (void) D_FUNCPOSTFIT;

D_Result d_remote_open_ex (void) D_FUNCPOSTFIT;

/** @brief 设置遥控器参数
* @param NecRemoteType
* @param BesconRemoteType
* @param DongzhiRemoteType
* @param Rc_5RemoteType
* @retval D_OK	设置成功
* @retval D_ERR	设置失败
*/
D_Result
d_set_remote_para(D_IRDbgOpenParam *irdbg_open_param) D_FUNCPOSTFIT;

/** @brief 设置支持遥控器的类型
*param code 遥控器类型
*param flag 1支持0不支持
* @retval D_OK	设置成功
* @retval D_ERR	设置失败
*/

D_Result  d_remote_poll_key (D_RemoteKeyParam *key) D_FUNCPOSTFIT;

/** @brief IR转发
*param code 遥控器类型
*param DVDHeadValue
*param DVDCmdValue
* @retval D_OK	设置成功
* @retval D_ERR	设置失败
*/
D_Result d_remote_send_dvdir (D_U8 type,D_U16 DVDHeadValue,D_U8 DVDCmdValue) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
