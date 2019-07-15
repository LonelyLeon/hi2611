/** @file
* @brief STB菜单接口
* @author 覃宜
* @date 2013-7-05 覃宜: 建立文件
*/

#ifndef _D_SYS_MENUS_H_
#define _D_SYS_MENUS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"
#include "dFrame.h"
#include "dControl.h"
#include "pPopMsg.h"
#include "pMenu.h"
#include "dScan.h"
#include "pStb.h"
#include "pStbScan.h"


/** @brief 菜单初始化*/
D_Result
p_stb_menu_init (void) D_FUNCPOSTFIT;

/** @brief 菜单卸载*/
D_Result
p_stb_menu_deinit (void) D_FUNCPOSTFIT;

/** @brief 设置ca菜单*/
D_Result
p_stb_set_ca_menu_ex(D_GUIMenu *camenu) D_FUNCPOSTFIT;

/** @brief 判断是否进入ca菜单*/
D_Bool
p_stb_judge_ca_menu(void) D_FUNCPOSTFIT;

/** @breif 显示播放器窗口*/
D_Result	
p_stb_player_win_show (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 取得桌面窗口对应的控件(即player win)*/
D_Visual*
p_desktop_get_control (void) D_FUNCPOSTFIT;

/** @brief 设置是否允许显示信号中断提示
* @param[in] enable 使能与否
* @param[in] lock 锁定全能状态。0不锁定，1锁定，2取消锁定
* @retval D_OK
*/
D_Result
p_set_signal_faint_msg_enable(D_Bool enable, D_U8 lock)D_FUNCPOSTFIT;

/** @brief 信号中断提示的显示与清除*/
D_Result
p_signal_faint_msg(D_Bool show)D_FUNCPOSTFIT;

/** @brief 重新显示信号中断提示信息*/
D_Result
p_signal_faint_msg_reshow(void)D_FUNCPOSTFIT;

/** @brief 没有保存节目提示的显示与清除*/
D_Result
p_no_prog_msg(D_Bool show)D_FUNCPOSTFIT;

D_Result 
p_set_curr_menu(D_GUIMenu *curr, D_Bool init)D_FUNCPOSTFIT;

/** @breif 显示主菜单*/
D_Result
p_stb_main_menu_show (void) D_FUNCPOSTFIT;

/** @brief 显示搜索菜单*/
D_Result
p_stb_scan_item_menu_show (void) D_FUNCPOSTFIT;

/** @brief 显示游戏菜单*/
D_Result
p_stb_game_item_menu_show (void) D_FUNCPOSTFIT;

/** @brief 快捷键显示epg菜单*/
D_Result
p_stb_k_epg_menu_show (void) D_FUNCPOSTFIT;

/** @breif 显示搜索界面*/
D_Result
p_stb_scan_window_show (D_StbScanType type, D_ScanTaskConfig *scan_config) D_FUNCPOSTFIT;

/** @brief 显示显示设置菜单窗口*/
D_Result
p_stb_picture_set_menu_show(void)D_FUNCPOSTFIT;

/** @breif 显示自动搜索窗口*/
D_Result
p_stb_auto_scan_show (void) D_FUNCPOSTFIT;

/** @breif 显示手动搜索设置窗口*/
D_Result
p_stb_manual_scan_show(void) D_FUNCPOSTFIT;

D_Result
p_stb_dvbc_manual_scan_show(void) D_FUNCPOSTFIT;


/** @breif 显示全屏段搜索设置窗口*/
D_Result
p_stb_full_scan_show (void) D_FUNCPOSTFIT;

/** @breif 显示自动搜索窗口*/
D_Result
p_stb_power_scan_show(D_U8 mode) D_FUNCPOSTFIT;

/** @breif 显示后台搜索窗口*/
D_Result
p_stb_bg_scan_window_show(D_ID dbtsid) D_FUNCPOSTFIT;

/** @breif 关闭后台搜索窗口*/
D_Result
p_stb_bg_scan_window_close(void) D_FUNCPOSTFIT;

/** @breif 显示信号检测窗口*/
D_Result
p_stb_signal_detect_show (void) D_FUNCPOSTFIT;

D_Result
p_stb_dvbc_signal_detect_show (void) D_FUNCPOSTFIT;

/** @breif 显示音量调节窗口*/
D_Result
p_audio_adjust_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @breif 清除音量调节窗口*/
D_Result
p_audio_adjust_window_hide (void) D_FUNCPOSTFIT;

/** @brief 显示静音调整窗*/
D_Result
p_stb_mute_window_show (void) D_FUNCPOSTFIT;


/*清除静音图标显示*/
D_Result 
p_stb_mute_window_clear()D_FUNCPOSTFIT;

/*根据状态重新显示静音图标*/
D_Result
p_stb_reshow_mute_flag(void)D_FUNCPOSTFIT;

/** @brief 显示频道号输入窗*/
D_Result
p_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;


/** @brief 清除频道号输入窗*/
D_Result
p_chan_input_window_hide (void) D_FUNCPOSTFIT;


/** @breif 显示窗口*/
D_Result
p_stb_tv_chan_edit_show (void) D_FUNCPOSTFIT;


/** @breif 显示窗口*/
D_Result
p_stb_radio_chan_edit_show (void) D_FUNCPOSTFIT;


D_Result         
p_stb_tv_chan_list_show (void) D_FUNCPOSTFIT;
/** @breif 显示窗口频谱信息*/
D_Result         
p_stb_chan_spectrum_show (void) D_FUNCPOSTFIT;

D_Result         
p_stb_radio_chan_list_show (void) D_FUNCPOSTFIT;


D_Result         
p_tv_chan_list_window_show_favor (void) D_FUNCPOSTFIT;

D_Result         
p_radio_chan_list_window_show_favor (void) D_FUNCPOSTFIT;

/** @breif 显示节目指南窗口*/
D_Result
p_stb_epg_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示预约窗口*/
D_Result
p_stb_sub_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示声道窗口*/
D_Result
p_stb_audio_track_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示时区设置窗口*/
D_Result 
p_stb_time_zone_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示密码设置窗口*/
D_Result
p_stb_password_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示  显示设置窗口*/
D_Result 
p_stb_display_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示主频点设置窗口*/
D_Result
p_stb_main_tp_set_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示主频点设置窗口*/
D_Result
p_stb_dvbc_main_tp_set_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示本机信息窗口*/
D_Result         
p_stb_info_window_show (void) D_FUNCPOSTFIT;

/** @brief 显示推箱子游戏窗口*/
D_Result
p_game_trunck_show(void) D_FUNCPOSTFIT;

/** @brief 显示麻将游戏窗口*/
D_Result
p_game_mahjong_show (void) D_FUNCPOSTFIT;

/** @brief 显示俄罗斯方块游戏窗口*/
D_Result
p_game_tetris_show (void) D_FUNCPOSTFIT;

/** @breif 显示频道信息窗口*/
D_Result
p_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif隐藏频道信息窗口*/
D_Result
p_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @breif 显示恢复设置窗口*/


/*@breif 显示录像管理窗口*/
D_Result p_pvr_manage_window_show(void) D_FUNCPOSTFIT;

/*@brief 存储信息窗口*/
D_Result p_storage_info_menu_show(void) D_FUNCPOSTFIT;

D_Result 
p_stb_restore_setting_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示节目相关信息窗口(用于测试)*/
D_Result d_dtmb_chan_info_test_window_show () D_FUNCPOSTFIT;

/** @breif 隐藏节目相关信息窗口(用于测试)*/
D_Result d_dtmb_chan_info_test_window_hide () D_FUNCPOSTFIT;

/** @breif 显示节目相关信息窗口(用于测试)*/
D_Result d_dvbc_chan_info_test_window_show () D_FUNCPOSTFIT;

/** @breif 隐藏节目相关信息窗口(用于测试)*/
D_Result d_dvbc_chan_info_test_window_hide () D_FUNCPOSTFIT;

/** @breif 显示节目排序选择窗口*/
typedef D_Result (* FUNC)(D_U8 type) D_FUNCPOSTFIT;	//定义函数指针
D_Result
d_sort_select_box_window_show (FUNC func) D_FUNCPOSTFIT;


/*显示节目锁密码输入框*/
D_Result p_show_prog_password_window(D_U32 param) D_FUNCPOSTFIT;
/*清除节目锁密码输入框*/
D_Result p_clear_prog_password_window(void) D_FUNCPOSTFIT;

/*多媒体列表窗体*/
D_Result
d_enter_media_list_menu(void)D_FUNCPOSTFIT;

/** @brief 窗口初始化*/
D_Result
p_ebk_full_screen_window_show (D_Char *path) D_FUNCPOSTFIT;

/** @breif 显示手动搜索选择窗口*/
D_Result
p_stb_auto_scan_select_show(void)D_FUNCPOSTFIT;

/** @breif 显示搜素配置窗口*/
D_Result
p_stb_scan_config_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示EPG窗口*/
D_Result
p_stb_atv_epg_window_show (void) D_FUNCPOSTFIT;

/*节目无法播放显示信息*/
D_Result
p_not_play_msg_show(D_Bool show)D_FUNCPOSTFIT;

/*显示没有节目流提示信息*/
D_Result
p_no_es_stream_show(D_Bool show, D_Bool play_logo)D_FUNCPOSTFIT;

int p_set_curr_usb_status(D_Bool plug, D_Ptr arg);
#ifdef  __cplusplus
}
#endif
#endif

