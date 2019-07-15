#ifndef _P_HAIER_PVR_H
#define _P_HAIER_PVR_H

#include "dTypes.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数*/
typedef D_Size (*D_HaierPvrDataDealCallback) (D_U32 dev_id, D_U8 *pbuf, D_Size dlen) D_FUNCPOSTFIT;

/** @brief 注册pvr录制后的数据处理回调
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_register(D_U32 dev_id, D_HaierPvrDataDealCallback callback) D_FUNCPOSTFIT;


/** @brief 初始化
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_open(void) D_FUNCPOSTFIT;


/** @brief 反初始化
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_close(void) D_FUNCPOSTFIT;


/** @brief 开始pvr录制
* @param[in] dev_id 设备号，可用于标识哪一路解复用
* @param[in] dbsrvid 录制的节目的dbsrvid
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_start(D_U32 dev_id, D_ID dbsrvid) D_FUNCPOSTFIT;


/** @brief pvrrec stop函数
* @param[in] dev_id 设备号，可用于标识哪一路解复用
* @return  成功返回D_OK,失败返回D_ERR
*/
D_Result p_haier_pvr_record_stop(D_U32 dev_id)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif
