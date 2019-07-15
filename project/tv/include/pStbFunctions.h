/** @file
* @brief 应用里用到的一些共用接口函数
* @author 覃宜
* @date 2014-06-20 覃宜: 建立文件
*/

#ifndef _D_STB_FUNCTIONS_H_
#define _D_STB_FUNCTIONS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"

/** @brief 根据数据库需重新设定静音与否、声道、音量*/
D_Result p_stb_reset_mute_track_volume( void )D_FUNCPOSTFIT;

/** @brief 根据数据库重新设定静音状态*/
D_Result p_stb_reset_mute_status( void )D_FUNCPOSTFIT;

/**@brief 将空间大小换算为字符串*/
D_Result p_unit_converter( D_Double orisize , D_Char * output )D_FUNCPOSTFIT;


/** @brief 设置ca菜单(TV_STB)*/
D_Result p_stb_set_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT;

/** @brief 设置ca菜单(TV)*/
D_Result
p_stb_set_atv_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT;
/** @brief 电视切换源*/
D_Result p_sys_set_input_mode(D_VidInput lastinput,D_VidInput input) D_FUNCPOSTFIT;

void p_set_ratio_mode(D_U8 mode)D_FUNCPOSTFIT;

/** @brief 取得用户设置的背景色*/
D_U32 p_sys_get_user_background_color(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

