#ifndef _P_HAIER_PVR_TS_H
#define _P_HAIER_PVR_TS_H

#include "dTypes.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数*/
typedef D_Size (*D_Ts2NetDataCBFunc) (D_U32 cb_data, D_U8 *pbuf, D_Size dlen) D_FUNCPOSTFIT;

/** @brief 初始化
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_open(void) D_FUNCPOSTFIT;


/** @brief 反初始化
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_close(void) D_FUNCPOSTFIT;


/** @brief 开始ts2net录制
* @param[in] user_id 用户标识号，用户自己维护。与stop时匹配
* @param[in] dbsrvid 录制的节目的dbsrvid
* @param[in] cb 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数
* @param cb_data 回调注册传入参数, 回调函数会带入此参数，可以是user_id
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_start(D_U32 user_id, D_ID dbsrvid, D_Ts2NetDataCBFunc cb, D_U32 cb_data) D_FUNCPOSTFIT;


/** @brief ts2net 停止录制函数
* @param[in] user_id 用户标识号，用户自己维护。与start时匹配
* @return  成功返回D_OK,失败返回D_ERR
*/
D_Result p_ts2net_record_stop(D_U32 user_id)D_FUNCPOSTFIT;


/** @brief 电视机切换频道时调用，判断电视要播放的频道是否与当前录制的频道相同，
以便处理，避免同一路demux过滤相同的pid而失败的问题
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_swich_channel(D_ID dbsrvid) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
