/** @file
* @brief 广告模块显示接口
* @author liuwf
* @date 2014-03-07 liuwf: 建立文件
*/

#ifndef _P_ADVERTISEMENT_SHOW_H_
#define _P_ADVERTISEMENT_SHOW_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dadporting.h"


/** @brief 初始化广告显示相关参�?
* @param[in] pos_type 广告类型
* @param[in] vis 主窗口控�?
* @param[in] x 主窗口起始x坐标
* @param[in] y 主窗口起始y坐标
* @param[in] width 主窗口宽�?
* @param[in] height 主窗口高�?
* @retval D_OK	成功
* @retval D_ERR	失败
*/
D_Result p_ad_show_open(D_Ad_Pos_Type pos_type, D_Visual *vis, D_U16 x, D_U16 y, D_U16 width, D_U16 height)D_FUNCPOSTFIT;

/** @brief 销毁广告显示参�?
* @param[in] pos_type 广告类型
* @retval D_OK	成功
* @retval D_ERR	失败
*/
D_Result p_ad_show_destroy(D_Ad_Pos_Type pos_type)D_FUNCPOSTFIT;

D_Result p_ad_check_fpkey(D_Ad_Pos_Type pos_type,D_U8 key)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
