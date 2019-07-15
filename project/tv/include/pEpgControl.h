/** @file
* @brief EPG控制api
* @author 李臣
* @date 2013-08-09 李臣: 建立文件
*/
#ifndef __P_EPG_CONTROL_H
#define __P_EPG_CONTROL_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 后台启动EPG
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_epg_start(D_U32 param) D_FUNCPOSTFIT;

/** @brief 关闭后台EPG
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result p_epg_stop(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

