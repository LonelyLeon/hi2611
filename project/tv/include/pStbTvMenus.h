#ifndef _D_TV_MENUS_H_
#define _D_TV_MENUS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dDebug.h"  
#include "dFP.h" 
#include "dGUI.h"
#include "dFrame.h"
#include "dControl.h"
#include "pPopMsg.h"
#include "pMenu.h"
#include "pMem.h"
#include "pStb.h"
#include "pFp.h"
#include "dMedia.h"
#include "dSerial.h"
#include "pFile_Scan.h"
#include "pBurnSerialNumber.h"
#include "pStbFunctions.h"


/** @brief 菜单初始化*/
D_Result
p_tv_menu_init (void) D_FUNCPOSTFIT;

/** @brief 菜单卸载*/
D_Result
p_tv_menu_deinit (void) D_FUNCPOSTFIT;

/** @brief 显示主菜单*/
D_Result
p_tv_main_menu_show (void) D_FUNCPOSTFIT;

/** @breif 显示播放器窗口*/
D_Result
p_atv_player_win_show (D_ID player_id) D_FUNCPOSTFIT;

/** @brief 取得桌面窗口对应的控件*/
D_Visual*
p_atv_get_player_window (void) D_FUNCPOSTFIT;

/** @brief 设置是否允许显示信号中断提示
* @param[in] enable 使能与否
* @param[in] lock 锁定全能状态。0不锁定，1锁定，2取消锁定
* @retval D_OK
*/
D_Result
p_tv_set_signal_faint_msg_enable(D_Bool enable, D_U8 lock)D_FUNCPOSTFIT;

/** @brief 信号中断提示的显示与清除*/
D_Result
p_tv_signal_faint_msg(D_Bool show)D_FUNCPOSTFIT;

/** @brief 重新显示信号中断提示信息*/
D_Result
p_tv_signal_faint_msg_reshow(void)D_FUNCPOSTFIT;

/** @brief 没有保存节目提示的显示与清除*/
D_Result
p_tv_no_prog_msg(D_Bool show)D_FUNCPOSTFIT;

/** @breif 显示频道信息窗口*/
D_Result
p_tv_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif隐藏频道信息窗口*/
D_Result
p_tv_channel_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示频道号输入窗*/
D_Result
p_tv_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief 清除频道号输入窗*/
D_Result
p_tv_chan_input_window_hide (void) D_FUNCPOSTFIT;

/**@brief 电视列表窗口*/
D_Result
p_tv_channel_list_window_show(void) D_FUNCPOSTFIT;

/**@brief 视频列表窗口*/
D_Result
p_video_list_window_show(void) D_FUNCPOSTFIT;

/**@brief 音乐列表窗口*/
D_Result
p_music_play_list_window_show(void) D_FUNCPOSTFIT;

/**@brief 图片列表窗口*/
D_Result
p_tv_picture_menu_show(void)D_FUNCPOSTFIT;

/**@brief 电子书列表窗口*/
D_Result
p_txt_menu_window_show(void) D_FUNCPOSTFIT;

/**@brief 收音机显示窗口*/
D_Result
p_fm_menu_window_show(void) D_FUNCPOSTFIT;

/** @brief 显示垂直进度条窗口*/
D_Result 
p_tv_vertical_progress_window_show(D_GUILayer layer,D_Coord x, D_Coord y, 
                                                                            D_U16 max_cnt, D_U16 def_val, 
                                                                            D_Result (*handler) (D_U16 val, D_U32 param),  D_U32 param) D_FUNCPOSTFIT;

/** @brief 关闭垂直进度条窗口*/
D_Result 
p_tv_vertical_progress_window_hide(void) D_FUNCPOSTFIT;

/** @brief 文件管理窗口*/
D_Result
p_tv_file_management_window_show(void)D_FUNCPOSTFIT;

/** @brief 显示播放控制菜单窗口*/
D_Result 
p_tv_menu_list_window_show(void) D_FUNCPOSTFIT;

/** @brief 显示视频播放控制菜单窗口*/
D_Result 
p_video_menu_list_window_show(D_Char *path , TV_MEDIA_D_FileScan *fs, D_ID index, D_MovieInfo    movie_info)D_FUNCPOSTFIT;

/** @brief 隐藏播放控制菜单窗口*/
D_Result 
p_tv_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief 隐藏视频播放控制菜单窗口*/
D_Result 
p_video_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示音乐播放控制菜单窗口*/
D_Result 
p_music_menu_list_window_show(D_U32 usb_sd_flag, D_U32 play_mode, D_Result (*handler)(D_U32 action_type, D_U32 param)D_FUNCPOSTFIT) D_FUNCPOSTFIT;

/** @brief 隐藏视频播放控制菜单窗口*/
D_Result 
p_music_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief 全屏播放图片控制窗口显示*/
D_Result 
p_pic_full_screen_menu_show(D_Char *path , TV_MEDIA_D_FileScan *fs, D_ID index, D_U32 usb_or_sd, D_Result (*handler) (D_U16 focus_id)D_FUNCPOSTFIT)D_FUNCPOSTFIT;

/** @brief图片文件预览窗口*/
D_Result
p_tv_picture_menu_show(void)D_FUNCPOSTFIT;

/** @brief万年历预览窗口*/
D_Result
p_tv_calender_menu_show(void)D_FUNCPOSTFIT;


/** @brief 显示处理快捷键窗口*/
D_Result
p_tv_shortcut_key_window_show (void) D_FUNCPOSTFIT;

/** @brief 清除处理快捷键窗口*/
D_Result
p_tv_shortcut_key_window_hide (void) D_FUNCPOSTFIT;

/** @brief 显示电池检测控件*/
D_Result
p_tv_battery_visual_show (D_Visual *vis_parent, D_Coord x, D_Coord y, D_U32 check_ms, D_U16 type) D_FUNCPOSTFIT;

/**@brief 设置控制菜单窗口*/
D_Result
p_tv_set_up_window_show(void)D_FUNCPOSTFIT;

/** @brief pvr菜单窗口*/
D_Result
p_pvr_list_menu_window_show(void) D_FUNCPOSTFIT;

/** @brief pvr录制菜单窗口*/
D_Result
p_pvr_record_menu_window_show(void) D_FUNCPOSTFIT;


/** @brief pvr录制输入时间菜单窗口*/
D_Result
p_pvr_input_time_window_show(void) D_FUNCPOSTFIT;


/** @breif 显示音量窗口*/
D_Result
p_tv_volume_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @breif 清除音量调节窗口*/
D_Result
p_tv_volume_window_hide (void) D_FUNCPOSTFIT;

/** @brief 显示视频播放控制menu菜单*/
D_Result 
p_video_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief 隐藏视频播放控制menu菜单窗口*/
D_Result 
p_video_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示图片播放控制menu菜单*/
D_Result 
p_photo_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief 隐藏图片播放控制menu菜单窗口*/
D_Result 
p_photo_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示pvr播放控制menu菜单*/
D_Result 
p_pvr_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief 隐藏pvr播放控制menu菜单窗口*/
D_Result 
p_pvr_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示txt播放控制menu菜单*/
D_Result 
p_txt_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief 隐藏txt播放控制menu菜单窗口*/
D_Result 
p_txt_preview_menu_window_hide(void) D_FUNCPOSTFIT;


/** @brief 显示手动搜索窗口*/
D_Result 
p_manual_scan_window_show(void) D_FUNCPOSTFIT;

D_Result
p_atv_tv_chan_list_show (void) D_FUNCPOSTFIT;

D_Result
p_atv_iptv_login_show (D_ID flag) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
