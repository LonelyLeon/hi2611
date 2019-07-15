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
#include "dTheme.h"
#include "dControl.h"
#include "pPopMsg.h"
#include "pMenu.h"
#include "pMem.h"
#include "pStb.h"
#include "pFp.h" 
#include "dMedia.h"
#include "pStbScan.h"
#include "dSerial.h"
#include "pFile_Scan.h"
#include "pBurnSerialNumber.h"
#include "pStbFunctions.h"
#include "patvGuiResource.h"
#include "dVipPorting.h"
#include "ptvConfig.h"


#define ATV_MEDIA_MENU_ID (0)

/*多媒体菜单状态*/
#define ATV_MEDIA_MENU_STATUS_MAIN (0x00000001)
#define ATV_MEDIA_MENU_STATUS_MOVIE (0x00000002)
#define ATV_MEDIA_MENU_STATUS_MUSIC (0x00000004)
#define ATV_MEDIA_MENU_STATUS_PHOTO (0x00000008)
#define ATV_MEDIA_MENU_STATUS_EBOOK (0x00000010)
#define ATV_MEDIA_MENU_STATUS_PVR   (0x00000020)
#define ATV_MEDIA_MENU_STATUS_SETUP (0x00000040)
#define ATV_MEDIA_MENU_STATUS_MOVIE_FULLSCREEN (0x00000080)
#define ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN (0x00000100)
#define ATV_MEDIA_MENU_STATUS_EBOOK_FULLSCREEN (0x00000200)
#define ATV_MEDIA_MENU_STATUS_TXT_FULLSCREEN       (0x00000400)
#define ATV_MEDIA_MENU_STATUS_PVR_FULLSCREEN       (0x00000800)

#define D_ZHILIAN_MIRACAST   (0)
#define D_ZHILIAN_DLNA          (1)
#define D_ZHILIAN_TS2NET        (2)
#define D_ZHILIAN_AIRPLAY        (3)
#define D_ZHILIAN_TYPE_MAX      (4)

extern D_U32 AtvMediaMenuStatus;
extern D_Bool ts2net_func_running;
extern D_Bool ts2net_check_enable;

/** @brief 菜单超时时间使能*/
D_Result p_atv_menu_timeout_timer_enable(D_Bool enable)D_FUNCPOSTFIT;

/** @brief 菜单超时时间定时器重新计时*/
D_Result p_atv_menu_timeout_timer_reset(void)D_FUNCPOSTFIT;

/** @brief 菜单时间定时器重新计时*/
D_Result
p_atv_menu_timer_reset(D_U8 new_time)D_FUNCPOSTFIT;


/** @brief 主菜单*/
D_Result
p_atv_main_menu_show (void) D_FUNCPOSTFIT;
/** @brief 菜单初始化*/
D_Result
p_atv_menu_init (void) D_FUNCPOSTFIT;

/** @brief 菜单卸载*/
D_Result
p_atv_menu_deinit (void) D_FUNCPOSTFIT;

/** @breif 显示信号源切换窗口*/
D_Result
p_atv_signal_select_show (void) D_FUNCPOSTFIT;

/** @breif 显示亮度窗口*/
D_Result
p_atv_bright_show (void) D_FUNCPOSTFIT;

/** @brief 显示色温窗口*/
D_Result
p_atv_color_mode_show (void) D_FUNCPOSTFIT;

/** @brief 显示色度窗口*/
D_Result
p_atv_color_show (void) D_FUNCPOSTFIT;

/** @brief 显示对比度窗口*/
D_Result
p_atv_contrast_show (void) D_FUNCPOSTFIT;

/** @brief 显示清晰度窗口*/
D_Result
p_atv_definition_show (void) D_FUNCPOSTFIT;

/** @brief 显示缩放模式菜单*/
D_Result
p_atv_zoom_mode_show (void) D_FUNCPOSTFIT;

/** @brief 显示图像模式菜单*/
D_Result
p_atv_video_mode_show (void) D_FUNCPOSTFIT;

/** @brief 显示声音环绕声菜单*/
D_Result
p_atv_round_show (void) D_FUNCPOSTFIT;

/** @brief 显示平衡条菜单*/
D_Result
p_atv_balance_show (void) D_FUNCPOSTFIT;

/** @brief 显示智能音量菜单*/
D_Result
p_atv_smart_sound_show (void) D_FUNCPOSTFIT;

/** @brief 显示音量条菜单*/
D_Result
p_atv_voice_show (void) D_FUNCPOSTFIT;

/** @brief 显示进度条*/
D_Result
p_vis_progress_draw (D_Visual *vis, D_ID imgage_id) D_FUNCPOSTFIT;

/** @brief 显示背光调整菜单*/
D_Result
p_atv_bglight_show (void) D_FUNCPOSTFIT;

/** @brief 数字降噪菜单*/
D_Result
p_atv_digital_noise_show (void) D_FUNCPOSTFIT;

/** @brief 显示菜单时间菜单*/
D_Result
p_atv_menu_time_show (void) D_FUNCPOSTFIT;

/** @brief 显示菜单语言菜单*/
D_Result
p_atv_menu_lang_show (void) D_FUNCPOSTFIT;

/** @brief 复位菜单*/
D_Result
p_atv_reset_show (void) D_FUNCPOSTFIT;

/** @brief 显示蓝屏菜单*/
D_Result
p_atv_blue_screen_show (void) D_FUNCPOSTFIT;

/** @brief 只有个确认键的菜单*/
D_Result
p_atv_user_ok_menu_show (D_Result (*userHandler)(void)) D_FUNCPOSTFIT;

/** @brief转发器编辑及增加弹出框窗口*/
D_Result
p_atv_add_edit_tp_menu_show(D_Bool edit, D_FEndParam *def_fparam,
                        D_Result (*handler) (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT,
                        D_U32 param)D_FUNCPOSTFIT;

/** @brief转发器编辑及增加弹出框窗口*/
D_Result
p_atv_add_edit_tp_menu_close(void)D_FUNCPOSTFIT;

/** @brief dvbs搜索设置菜单*/
D_Result
p_atv_set_antenna_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示DVBS搜索界面*/
D_Result
p_atv_dvbs_scan_window_show (P_ScanConfig *pScanConf) D_FUNCPOSTFIT;

/** @brief 频道编辑菜单*/
D_Result
p_atv_channel_editor_show (void) D_FUNCPOSTFIT;

/** @brief 自动搜索菜单*/
D_Result
p_atv_auto_scan_show (void) D_FUNCPOSTFIT;

/** @brief 交换频道菜单*/
D_Result
p_atv_channel_change_show (void) D_FUNCPOSTFIT;

/** @brief 显示当前时间菜单*/
D_Result
p_atv_set_time_show (void) D_FUNCPOSTFIT;

/** @brief 显示定时关机菜单*/
D_Result
p_atv_power_off_show (void) D_FUNCPOSTFIT;

/** @brief 显示定时开机菜单*/
D_Result
p_atv_power_on_show (void) D_FUNCPOSTFIT;

/** @brief 显示开机频道菜单*/
D_Result
p_atv_boot_ch_show (void) D_FUNCPOSTFIT;

/** @brief 显示预约时间菜单*/
D_Result
p_atv_order_time_show (void) D_FUNCPOSTFIT;

/** @brief 显示预约频道菜单*/
D_Result
p_atv_order_ch_show (void) D_FUNCPOSTFIT;

/** @brief 显示睡眠定时菜单*/
D_Result
p_atv_sleep_show (void) D_FUNCPOSTFIT;

/** @brief 复位菜单*/
D_Result
p_atv_adjust_reset_show (void) D_FUNCPOSTFIT;

/** @brief 自动调整菜单*/
D_Result
p_atv_auto_adjust_show (void) D_FUNCPOSTFIT;

/** @brief 频道编辑菜单*/
D_Result
p_atv_picture_position_show (void) D_FUNCPOSTFIT;

/** @brief 显示相位菜单*/
D_Result
p_atv_phase_show (void) D_FUNCPOSTFIT;

/** @brief 时钟菜单*/
D_Result
p_atv_clock_show (void) D_FUNCPOSTFIT;

/** @brief 图像位置菜单*/
D_Result
p_atv_pop_position_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 频道交换菜单*/
D_Result
p_atv_exchange_show (void(*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 频道搜索菜单*/
D_Result
p_atv_search_show ( void (*pFunc)(void)) D_FUNCPOSTFIT;


/** @brief 隐藏或显示多媒体菜单*/
D_Result
p_atv_media_menus_show (D_Bool show, D_U32 param) D_FUNCPOSTFIT;

/** @brief 显示多媒体主菜单*/
D_Result
p_atv_media_main_menu_show (void) D_FUNCPOSTFIT;

/** @brief 路径里的C/D/E等盘名改为USB或SD*/
D_Result 
p_atv_media_device_name_map(D_Char* pathname)D_FUNCPOSTFIT;

/** @brief 显示多媒体设置菜单*/
D_Result
p_atv_media_setting_menu_show (void) D_FUNCPOSTFIT;

/** @breif 显示音量窗口*/
D_Result
p_atv_volume_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief 音乐菜单显示*/
D_Result
p_atv_media_music_show (void) D_FUNCPOSTFIT;

/** @brief 显示多媒体视频列表菜单*/
D_Result
p_atv_media_picture_show (void) D_FUNCPOSTFIT;

/** @brief 显示多媒体电子书列表菜单*/
D_Result
p_atv_media_ebook_list_show (void) D_FUNCPOSTFIT;

/** @breif 清除音量调节窗口*/
D_Result
p_atv_volume_window_hide (void) D_FUNCPOSTFIT;

/** @brief 音乐菜单隐藏*/
D_Result
p_atv_media_music_hide(void) D_FUNCPOSTFIT;

/** @brief 视频菜单显示*/
D_Result
p_atv_media_movie_show (void) D_FUNCPOSTFIT;

/** @brief 视频菜单隐藏*/
D_Result
p_atv_media_movie_hide (void) D_FUNCPOSTFIT;

/** @brief 视频全屏菜单显示*/
D_Result
p_media_movie_full_screen_show (D_Char* path_name, D_U16 movie_index, D_FileScan* fs, D_U8 play_mode, D_Result (*mediaFullMovieHideHandler) (D_U16 param)) D_FUNCPOSTFIT;

/** @brief 视频全屏菜单隐藏*/
D_Result
p_media_movie_full_screen_hide(void) D_FUNCPOSTFIT;

/** @brief  ebk全屏菜单显示*/
D_Result
p_media_ebk_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT;

/** @brief ebk全屏菜单隐藏*/
D_Result
p_media_ebk_full_screen_window_hide(void) D_FUNCPOSTFIT;

/** @brief txt全屏菜单隐藏*/
D_Result
p_media_txt_full_screen_window_hide(void) D_FUNCPOSTFIT;

/** @brief 电子书列表菜单显示*/
D_Result
p_atv_media_ebook_show (void) D_FUNCPOSTFIT;

/** @brief 电子书全屏显示菜单*/
D_Result
p_media_txt_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT;

/** @brief pvr显示菜单*/
D_Result
p_atv_media_pvr_show (void) D_FUNCPOSTFIT;

/** @brief pvr全屏显示菜单*/
D_Result
p_media_pvr_full_screen_show(D_Char* path_name, D_FileScan* fs, D_U16  pvr_index, D_Result (*mediaFullPvrHideHandler) (D_U16 param)) D_FUNCPOSTFIT;

/** @brief pvr全屏隐藏菜单*/
D_Result
p_media_pvr_full_screen_hide(void) D_FUNCPOSTFIT;

/** @brief pvr录制菜单显示*/
D_Result
p_atv_pvr_record_menu_show (void) D_FUNCPOSTFIT;

/** @brief pvr录制菜单隐藏*/
D_Result
p_atv_meida_pvr_record_menu_hide(void)D_FUNCPOSTFIT;

/** @brief 显示多媒体提示窗口*/
D_Result
p_atv_media_prompt_msg(D_ID id)D_FUNCPOSTFIT;

/** @brief 显示频道多路音频窗口*/
D_Result
p_atv_multi_audio_window_show(void)D_FUNCPOSTFIT;


/** @brief 显示图像优化菜单*/
D_Result
p_atv_picture_optimize_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @breif 显示搜索界面*/
D_Result
p_full_search_window_show (D_StbScanType type,D_ScanTaskConfig *scan_config) D_FUNCPOSTFIT;

/** @breif 显示频道信息窗口*/
D_Result
p_atv_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif隐藏频道信息窗口*/
D_Result
p_atv_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief  选择是否开始自动搜索的菜单*/
D_Result
p_atv_auto_reset_select_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @breif 显示自动搜索界面*/
D_Result
p_atv_manual_scan_window_show (void) D_FUNCPOSTFIT;

/** @breif 显示搜索界面*/
D_Result
p_full_search_window_hide (void) D_FUNCPOSTFIT;

/** @brief 显示当前时间菜单*/
D_Result
p_atv_pop_set_time_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 显示弹出框定时关机菜单*/
D_Result
p_atv_pop_power_off_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 显示弹出框预定时间菜单*/
D_Result
p_atv_pop_order_time_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 显示弹出框定时开机菜单*/
D_Result
p_atv_pop_power_on_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief 显示频道号输入窗*/
D_Result
p_atv_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief 清除频道号输入窗*/
D_Result
p_atv_chan_input_window_hide (void) D_FUNCPOSTFIT;

/** @brief 画进度条的进度图片*/
D_Result
p_vis_progress_draw (D_Visual *vis, D_ID imgage_id) D_FUNCPOSTFIT;

/** @breif 显示窗口*/
D_Result
p_atv_signal_input_show (D_VidInput input, char *video, char *audio) D_FUNCPOSTFIT;

/** @brief 显示静音调整窗*/
D_Result
p_atv_mute_window_show (void) D_FUNCPOSTFIT;

/*清除静音图标显示*/
D_Result 
p_atv_mute_window_clear()D_FUNCPOSTFIT;

/*根据状态重新显示静音图标*/
D_Result
p_atv_reshow_mute_flag(void)D_FUNCPOSTFIT;

/** @breif 显示窗口*/      
D_Result         
p_atv_tv_chan_list_show (void) D_FUNCPOSTFIT;

D_Result         
p_atv_radio_chan_list_show (void) D_FUNCPOSTFIT;

/** @breif 显示频道信息窗口*/
D_Result
p_atv_tv_chan_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif隐藏频道信息窗口*/
D_Result
p_atv_tv_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief 显示图像优化菜单*/
D_Result
p_av_signal_select_show (void) D_FUNCPOSTFIT;

/** @brief 显示色调窗口*/
D_Result
p_atv_tint_show (void) D_FUNCPOSTFIT;

/** @breif 显示手动搜索界面*/
D_Result
p_atv_auto_scan_window_show (void) D_FUNCPOSTFIT;

/** @brief 工厂菜单*/
D_Result
p_atv_factory_setting_show (void) D_FUNCPOSTFIT;

/** @brief 通用设置菜单*/
D_Result
p_atv_general_setting_show (void) D_FUNCPOSTFIT;

/** @brief 通用设置菜单*/
D_Result
p_atv_pwm_setting_show (void) D_FUNCPOSTFIT;

/** @brief 酒店模式菜单*/
D_Result
p_atv_hotel_mode_setting_show (void) D_FUNCPOSTFIT;

/** @brief 声音设置菜单*/
D_Result
p_atv_sound_setting_show (void) D_FUNCPOSTFIT;

/** @brief 	声音模式菜单*/
D_Result
p_atv_sound_mode_show (void) D_FUNCPOSTFIT;

/** @brief 	音量菜单*/
D_Result
p_atv_volume_curve_show (void) D_FUNCPOSTFIT;

/** @brief audio output菜单*/
D_Result
p_atv_audio_output_show (void) D_FUNCPOSTFIT;

/** @brief drc function菜单*/
D_Result
p_atv_drc_function_show (void) D_FUNCPOSTFIT;

/** @brief peq菜单*/
D_Result
p_atv_peq_set_show (void) D_FUNCPOSTFIT;

/** @brief 	声音模式菜单*/
D_Result
p_atv_image_show (void) D_FUNCPOSTFIT;

/** @brief 白平衡调整菜单*/
D_Result
p_atv_wb_adjust_show (void) D_FUNCPOSTFIT;

/** @brief 效果菜单*/
D_Result
p_atv_pq_nonlilnear_show (void) D_FUNCPOSTFIT;

/** @brief 	图像调整菜单*/
D_Result
p_atv_setting_show (D_S16 flag) D_FUNCPOSTFIT;

/** @brief bl dim菜单*/
D_Result
p_atv_bl_dim_show (void) D_FUNCPOSTFIT;

/** @brief ce菜单*/
D_Result
p_atv_ce_set_show (void) D_FUNCPOSTFIT;

/** @brief ase菜单*/
D_Result
p_atv_ase_show (void) D_FUNCPOSTFIT;

/** @brief gamma菜单*/
D_Result
p_atv_gamma_show (void) D_FUNCPOSTFIT;

/** @brief 	DI/FM菜单*/
D_Result
p_atv_difm_set_show (void) D_FUNCPOSTFIT;

/** @brief 	FTC菜单*/
D_Result
p_atv_ftc_set_show (void) D_FUNCPOSTFIT;

/** @brief 	NR菜单*/
D_Result
p_atv_nr_set_show (void) D_FUNCPOSTFIT;

/** @brief 	NR菜单*/
D_Result
p_atv_de_set_show (void) D_FUNCPOSTFIT;

/** @brief 	ICM菜单*/
D_Result
p_atv_icm_set_show (void) D_FUNCPOSTFIT;

/** @brief 	COMB菜单*/
D_Result
p_atv_comb_set_show (void) D_FUNCPOSTFIT;

/** @brief 	COMP菜单*/
D_Result
p_atv_comp_set_show (void) D_FUNCPOSTFIT;

/** @breif 显示本机信息窗口*/      
D_Result         
p_atv_info_window_show (void) D_FUNCPOSTFIT;

/** @brief 	升级菜单*/
D_Result
p_atv_software_update_show (void) D_FUNCPOSTFIT;

/** @brief emc菜单*/
D_Result
p_atv_emc_setting_show (void) D_FUNCPOSTFIT;

/** @brief adc adjust菜单*/
D_Result
p_atv_adc_adjust_show (void) D_FUNCPOSTFIT;

/** @brief 定时器菜单*/
D_Result
p_atv_timer_set_show (void) D_FUNCPOSTFIT;

/** @brief 数字音质菜单*/
D_Result
p_atv_digital_adjust_show (void) D_FUNCPOSTFIT;

/** @brief 	DIGIT_TIMBRE菜单*/
D_Result
p_atv_digit_timbre_show (D_Bool flag) D_FUNCPOSTFIT;

/** @brief tv搜索配置菜单*/
D_Result
p_atv_tv_scan_config_show (void) D_FUNCPOSTFIT;

/** @brief dtv搜索配置菜单*/
D_Result
p_atv_dtv_scan_config_show (void) D_FUNCPOSTFIT;

/** @brief 无信号菜单显示*/
D_Result
p_atv_no_signal_win_show (void) D_FUNCPOSTFIT;

/** @brief 无信号菜单隐藏*/
D_Result
p_atv_no_signal_win_hide (void) D_FUNCPOSTFIT;

/** @brief 显示待机提示菜单*/
D_Result
p_atv_power_off_msg_show (void) D_FUNCPOSTFIT;

/** @brief 	avc dac ctl菜单*/
D_Result
p_atv_avc_dac_ctl_show (D_U32 param) D_FUNCPOSTFIT;

/** @brief 显示缩放模式菜单*/
D_Result
p_atv_media_zoom_mode_show (void) D_FUNCPOSTFIT;

/** @brief set register菜单*/
D_Result
p_atv_set_register_show (D_U8 val) D_FUNCPOSTFIT;

/** @brief 清除全屏状态下的所有提示*/
D_Result
p_atv_player_window_clear_osd (D_U32 param) D_FUNCPOSTFIT;

/** @brief 频道预置菜单*/
D_Result
p_atv_program_reset_show (void) D_FUNCPOSTFIT;

/** @brief 广播提示菜单显示*/
D_Result
p_atv_radio_icon_win_show (D_ID dbsrvid) D_FUNCPOSTFIT;

/** @brief 广播提示菜单隐藏*/
D_Result
p_atv_radio_icon_win_hide (void) D_FUNCPOSTFIT;

/** @brief 工厂复位*/
D_Result
tv_reset_factory_setting(void) D_FUNCPOSTFIT;


/** @brief 显示密码输入窗口
* @param prio           消息框的优先级
* @param layer      显示所在的层
* @param type       输入框类型
* @param str_title          要显示的标题文本
* @param msg            要显示的信息
* @param len            输入字符长度
* @param user_hide  用户是否可以手动退出
* @param handler    选择处理回调函数指针
* @param param      传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pwd_input_window_show (D_U16 prio,
                              D_GUILayer layer,
                              D_PopInputType type,
                              const D_Char *str_title,
                              const D_Char *msg,
                              D_U16 len, D_Bool user_hide,
                              D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
                              D_U32   param, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 隐藏显示的用户密码窗口
* @param prio           消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pwd_input_window_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 显示ca的公用菜单模块*/
D_Result
p_atv_ca_main_window_show(void)D_FUNCPOSTFIT;

/** @brief 显示序列化*/
D_Result
p_atv_serial_show (void) D_FUNCPOSTFIT;

/** @brief 画一个窗口，为滚动条打开osd*/
D_Bool
p_osd_show (D_Bool show_en, D_U32 handle) D_FUNCPOSTFIT;

/** @brief 画一个窗口,为多媒体播放*/
D_Result
p_show_osd_window (D_Bool show_en) D_FUNCPOSTFIT;

/** @breif 显示窗口*/
D_Result
p_atv_wifi_window_show (void) D_FUNCPOSTFIT;

/** @breif 隐藏窗口*/
D_Result
p_atv_wifi_window_hide (D_Bool show) D_FUNCPOSTFIT;

/** @breif 显示wifi设置窗口*/
D_Result
p_atv_wlan_menu_show(void)D_FUNCPOSTFIT;

/** @breif 显示wifi设置窗口*/
D_Result
p_atv_wifi_setting_window_show (void) D_FUNCPOSTFIT;

/** @breif 关闭wifi设置窗口*/
D_Result
p_atv_wifi_setting_window_close (void) D_FUNCPOSTFIT;

/** @brief wifi 状态信息窗口显示*/
//D_Result
//p_atv_wifi_detail_info_window_show(void)D_FUNCPOSTFIT;

/** @brief wifi 状态信息窗口关闭*/
D_Result
p_atv_wifi_detail_info_window_colse(void)D_FUNCPOSTFIT;

/** @brief 文本输入 窗口显示
* @param strtitle			要显示的标题文本
* @param strdef			默认文本
* @param handler		用户确认后调用的函数指针
* @param param			传给用户回调的参数
*/
D_Result
p_atv_textinput_window_show(D_Char *strtitle, D_Char *strdef, D_U32 min_len, D_U32 max_len, D_Result (*handler) (D_Char *text, D_U32 param, D_U32 action) D_FUNCPOSTFIT, D_U32 param )D_FUNCPOSTFIT;

/** @brief rename 文本输入窗口关闭*/
D_Result
p_atv_textinput_window_colse(void)D_FUNCPOSTFIT;

/** @breif 显示窗口*/
D_Result
p_atv_zhilian_tv_window_show (D_U32 type, D_Bool auto_start) D_FUNCPOSTFIT;

/** @breif 隐藏窗口*/
D_Result
p_atv_zhilian_tv_window_hide (void) D_FUNCPOSTFIT;

/** @breif 通知界面显示连接状态*/
D_Result
p_atv_zhilian_tv_window_show_status (D_U32 status, D_Char *name) D_FUNCPOSTFIT;

/** @breif 隐藏或重新显示窗口，但不释放窗口*/
D_Result
p_atv_zhilian_tv_window_show_enable (D_Bool show) D_FUNCPOSTFIT;

/** @breif 显示窗口*/
D_Result
p_atv_zhilian_tv_window_show_shortcut (D_U32 type) D_FUNCPOSTFIT;

/** @breif 显示窗口*/
D_Result
p_atv_ts2net_window_show (D_U32 x, D_U32 y, D_Result (*handler) (D_U32 action)) D_FUNCPOSTFIT;

/** @breif 隐藏窗口*/
D_Result
p_atv_ts2net_window_hide (void) D_FUNCPOSTFIT;

/** @brief 显示dlna视频播放窗口*/
D_Result
p_atv_dlna_window_show(D_Char*  file_path , D_Char*  file_title, D_VidInput lastinput) D_FUNCPOSTFIT;

/** @brief 关闭dlna视频播放窗口*/
D_Result
p_atv_dlna_window_hide(void) D_FUNCPOSTFIT;

/** @brief 通知dlna视频播放窗口网络状态*/
D_Result
p_atv_dlna_window_network_error(D_U32 action) D_FUNCPOSTFIT;

/** @brief 显示airplay视频播放窗口*/
D_Result
p_atv_airplay_window_show(D_Char*  file_path, D_U32 mode, void (*cb)(D_U32 action)) D_FUNCPOSTFIT;

/** @brief 关闭airplay视频播放窗口*/
D_Result
p_atv_airplay_window_hide(void) D_FUNCPOSTFIT;

/** @brief airplay视频播放窗口是否正显示*/
D_Bool
p_atv_airplay_window_is_show(void) D_FUNCPOSTFIT;

/** @brief 通知airplay视频播放窗口网络状态*/
D_Result
p_atv_airplay_window_network_error(D_U32 action) D_FUNCPOSTFIT;

#ifdef D_TV_SUPPORT_IPTV
void p_iptv_info_show( );
void p_iptv_info_close( );
D_U8 getIptvRunFlag( void );
void try_play_new_iptvchan(  D_U16 chno );

 #endif


#ifdef  __cplusplus
}
#endif
#endif
