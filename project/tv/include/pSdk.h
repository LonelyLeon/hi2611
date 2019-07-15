/** @file
* @brief Sdk
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#ifndef __STB_SDK_H
#define __STB_SDK_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGDev.h"
#include "dGraph.h"
#include "dTV.h"
#include "dFP.h"
#include "dPowerOff.h"

extern D_HTV g_htv; 

D_Result p_port_init(void) D_FUNCPOSTFIT;
D_Result p_auxi_init(void) D_FUNCPOSTFIT;
D_Result p_gui_init(void) D_FUNCPOSTFIT;
D_Result p_cas_init(void) D_FUNCPOSTFIT;
D_Result p_tv_init(void) D_FUNCPOSTFIT;
D_Result p_fp_init(void) D_FUNCPOSTFIT;

D_HGDev p_gui_get_hgdev(void) D_FUNCPOSTFIT;
D_Result p_gui_set_format(D_VidFormat fmt) D_FUNCPOSTFIT;
D_GSurface *p_gui_get_dev_surface(void) D_FUNCPOSTFIT;

/** @brief 通过遥控器映射值获取对应的用户码和键值)
* @param[in] key 遥控器映射值
* @param[in] remote_size  获取的遥控器键值个数
* @param[out] key_buf  获取键值和用户的数组
* @retval 获取的遥控器值个数
*/
D_U8 d_get_remote_key(D_KeyCode key,P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT;

/** @brief 设定面板遥控器使能与否
* @param[in] enable 使能与否
* @retval D_OK
*/
D_Result p_fp_set_enable(D_Bool enable) D_FUNCPOSTFIT;

/** @brief 取得当前的按键
* @param[in] param 参数
* @retval D_OK
*/
D_KeyCode
p_fp_get_curr_key(D_U32 param) D_FUNCPOSTFIT;

/** @brief 设定面板遥控器过滤的按键值列表(列表之外的键值无效)
* @param[in] filter_keys 过滤键值表，暂定最多可过滤16个按键
* @param[in] keys_cnt 过滤键值表数目
(暂定最多为16，当为(D_U16)-1 或0xfffff时说明取消过滤操作)
* @retval D_OK
*/
D_Result p_fp_set_filter_keys(D_KeyCode *filter_keys, D_U16 keys_cnt) D_FUNCPOSTFIT;

/*根据当前制式自动匹配小窗口坐标*/
D_Result p_gui_auto_match_window_format(D_Coord* x, D_Coord* y, D_Coord* w, D_Coord* h)D_FUNCPOSTFIT;

/** @brief 设置视频背景色（黑屏、蓝屏等），project封装为解决视觉亮暗现象
direct 立即起作用，还是跟随osd重新绘制时起作用
*/
D_Result p_av_set_vid_background(D_HAV hav, D_VidBackGroundColor_t BackGround, D_Bool direct)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

