/**@defgroup MonitorTable SI表监控
*@{*/
/** @file
* @brief 节目监控模块
* @author sunzy
* @date 2013-06-03 sunzy: 建立文件
* @date 2013-06-05 sunzy: 移动原模块相关代码
* @date 2013-07-25 hegx: 根据要求实现注册函数
*/
#ifndef _D_MONITORREGISTER_H_
#define _D_MONITORREGISTER_H_

#ifdef  __cplusplus

extern "C"
{
#endif

#include "pSIParse.h"

typedef enum {
	D_MSG_MON_NULL = -1,	
	D_MSG_MON_SW_UPDATE,				/**< 找到软件升级数据*/
	D_MSG_MON_SW_UPDATE_MUST,			/**< 找到软件升级数据, 强制升级*/
	D_MSG_MON_UMT_UPDATE,				/**< 找到UMT 软件升级数据*/
	D_MSG_MON_UMT_UPDATE_FORCE,		/**< 找到UMT 软件升级数据, 强制升级*/
	D_MSG_MON_CA_UPDATE,				/**< 找到联广 软件升级数据*/
	D_MSG_MON_CA_UPDATE_FORCE,		/**< 找到联广 软件升级数据, 强制升级*/
	D_MSG_MON_CHAN_UPDATE,				/**< 频道需要重新搜索*/
	D_MSG_MON_CHAN_CHANGE,				/**< 本频点节目变化*/
	D_MSG_MON_CHAN_UPDATE_MUST,		/**< 频道需要重新搜索*/
	D_MSG_MON_CAT_CHANGED,				/**< CAT信息变化*/
	D_MSG_MON_PMT_CHANGED,				/**< PMT信息变化*/
	D_MSG_MON_SDT_CHANGED,				/**< SDT信息变化*/
	D_MSG_MON_NETWORK_ID_CHANGED,		/**< network id变化*/
	D_MSG_MON_NETWORK_NAME_CHANGED,	/**< network name 变化*/	
} D_MONMsgType;


#define NET_NAME_MAX_LEN (32)

typedef struct
{
    D_U8 nit_version;
    D_U16 currNetworkId;
    D_Char currNetworkName[NET_NAME_MAX_LEN + 1];
    D_Loader_Descr  Loader_Descr;
    D_U8	delivery[64];
}D_PMonitorData;

typedef struct
{
	D_U8	download_table_id; 
	D_U16	download_pid;
	D_U8	upgrade_mode;
	D_U16	manufacturer_code;
	D_U32	software_version;
	D_U32	hardware_version;
	D_FEndFreq	freq;	/*单位100Hz*/
	D_FEndBaud	baud;	/*单位100symbol/s*/
	D_FEndMod	mod;	
	D_U8		download_flag;
	D_U8		 tag;
}D_CA_Loaderinfo;

/** @brief 表监控初始化
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_init()D_FUNCPOSTFIT;
/** @brief 进入其它通道时候关掉外挂的通道
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_close(void)D_FUNCPOSTFIT;

/** @brief 重新开启外挂通道
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_restart(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
/* @}*/

