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

/*��ý��˵�״̬*/
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

/** @brief �˵���ʱʱ��ʹ��*/
D_Result p_atv_menu_timeout_timer_enable(D_Bool enable)D_FUNCPOSTFIT;

/** @brief �˵���ʱʱ�䶨ʱ�����¼�ʱ*/
D_Result p_atv_menu_timeout_timer_reset(void)D_FUNCPOSTFIT;

/** @brief �˵�ʱ�䶨ʱ�����¼�ʱ*/
D_Result
p_atv_menu_timer_reset(D_U8 new_time)D_FUNCPOSTFIT;


/** @brief ���˵�*/
D_Result
p_atv_main_menu_show (void) D_FUNCPOSTFIT;
/** @brief �˵���ʼ��*/
D_Result
p_atv_menu_init (void) D_FUNCPOSTFIT;

/** @brief �˵�ж��*/
D_Result
p_atv_menu_deinit (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ź�Դ�л�����*/
D_Result
p_atv_signal_select_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ���ȴ���*/
D_Result
p_atv_bright_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾɫ�´���*/
D_Result
p_atv_color_mode_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾɫ�ȴ���*/
D_Result
p_atv_color_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�Աȶȴ���*/
D_Result
p_atv_contrast_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����ȴ���*/
D_Result
p_atv_definition_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ����ģʽ�˵�*/
D_Result
p_atv_zoom_mode_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾͼ��ģʽ�˵�*/
D_Result
p_atv_video_mode_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����������˵�*/
D_Result
p_atv_round_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾƽ�����˵�*/
D_Result
p_atv_balance_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ���������˵�*/
D_Result
p_atv_smart_sound_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�������˵�*/
D_Result
p_atv_voice_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ������*/
D_Result
p_vis_progress_draw (D_Visual *vis, D_ID imgage_id) D_FUNCPOSTFIT;

/** @brief ��ʾ��������˵�*/
D_Result
p_atv_bglight_show (void) D_FUNCPOSTFIT;

/** @brief ���ֽ���˵�*/
D_Result
p_atv_digital_noise_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�˵�ʱ��˵�*/
D_Result
p_atv_menu_time_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�˵����Բ˵�*/
D_Result
p_atv_menu_lang_show (void) D_FUNCPOSTFIT;

/** @brief ��λ�˵�*/
D_Result
p_atv_reset_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����˵�*/
D_Result
p_atv_blue_screen_show (void) D_FUNCPOSTFIT;

/** @brief ֻ�и�ȷ�ϼ��Ĳ˵�*/
D_Result
p_atv_user_ok_menu_show (D_Result (*userHandler)(void)) D_FUNCPOSTFIT;

/** @briefת�����༭�����ӵ����򴰿�*/
D_Result
p_atv_add_edit_tp_menu_show(D_Bool edit, D_FEndParam *def_fparam,
                        D_Result (*handler) (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT,
                        D_U32 param)D_FUNCPOSTFIT;

/** @briefת�����༭�����ӵ����򴰿�*/
D_Result
p_atv_add_edit_tp_menu_close(void)D_FUNCPOSTFIT;

/** @brief dvbs�������ò˵�*/
D_Result
p_atv_set_antenna_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾDVBS��������*/
D_Result
p_atv_dvbs_scan_window_show (P_ScanConfig *pScanConf) D_FUNCPOSTFIT;

/** @brief Ƶ���༭�˵�*/
D_Result
p_atv_channel_editor_show (void) D_FUNCPOSTFIT;

/** @brief �Զ������˵�*/
D_Result
p_atv_auto_scan_show (void) D_FUNCPOSTFIT;

/** @brief ����Ƶ���˵�*/
D_Result
p_atv_channel_change_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ǰʱ��˵�*/
D_Result
p_atv_set_time_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ʱ�ػ��˵�*/
D_Result
p_atv_power_off_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ʱ�����˵�*/
D_Result
p_atv_power_on_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ����Ƶ���˵�*/
D_Result
p_atv_boot_ch_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾԤԼʱ��˵�*/
D_Result
p_atv_order_time_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾԤԼƵ���˵�*/
D_Result
p_atv_order_ch_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ˯�߶�ʱ�˵�*/
D_Result
p_atv_sleep_show (void) D_FUNCPOSTFIT;

/** @brief ��λ�˵�*/
D_Result
p_atv_adjust_reset_show (void) D_FUNCPOSTFIT;

/** @brief �Զ������˵�*/
D_Result
p_atv_auto_adjust_show (void) D_FUNCPOSTFIT;

/** @brief Ƶ���༭�˵�*/
D_Result
p_atv_picture_position_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��λ�˵�*/
D_Result
p_atv_phase_show (void) D_FUNCPOSTFIT;

/** @brief ʱ�Ӳ˵�*/
D_Result
p_atv_clock_show (void) D_FUNCPOSTFIT;

/** @brief ͼ��λ�ò˵�*/
D_Result
p_atv_pop_position_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief Ƶ�������˵�*/
D_Result
p_atv_exchange_show (void(*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief Ƶ�������˵�*/
D_Result
p_atv_search_show ( void (*pFunc)(void)) D_FUNCPOSTFIT;


/** @brief ���ػ���ʾ��ý��˵�*/
D_Result
p_atv_media_menus_show (D_Bool show, D_U32 param) D_FUNCPOSTFIT;

/** @brief ��ʾ��ý�����˵�*/
D_Result
p_atv_media_main_menu_show (void) D_FUNCPOSTFIT;

/** @brief ·�����C/D/E��������ΪUSB��SD*/
D_Result 
p_atv_media_device_name_map(D_Char* pathname)D_FUNCPOSTFIT;

/** @brief ��ʾ��ý�����ò˵�*/
D_Result
p_atv_media_setting_menu_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��������*/
D_Result
p_atv_volume_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief ���ֲ˵���ʾ*/
D_Result
p_atv_media_music_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ý����Ƶ�б�˵�*/
D_Result
p_atv_media_picture_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ý��������б�˵�*/
D_Result
p_atv_media_ebook_list_show (void) D_FUNCPOSTFIT;

/** @breif ����������ڴ���*/
D_Result
p_atv_volume_window_hide (void) D_FUNCPOSTFIT;

/** @brief ���ֲ˵�����*/
D_Result
p_atv_media_music_hide(void) D_FUNCPOSTFIT;

/** @brief ��Ƶ�˵���ʾ*/
D_Result
p_atv_media_movie_show (void) D_FUNCPOSTFIT;

/** @brief ��Ƶ�˵�����*/
D_Result
p_atv_media_movie_hide (void) D_FUNCPOSTFIT;

/** @brief ��Ƶȫ���˵���ʾ*/
D_Result
p_media_movie_full_screen_show (D_Char* path_name, D_U16 movie_index, D_FileScan* fs, D_U8 play_mode, D_Result (*mediaFullMovieHideHandler) (D_U16 param)) D_FUNCPOSTFIT;

/** @brief ��Ƶȫ���˵�����*/
D_Result
p_media_movie_full_screen_hide(void) D_FUNCPOSTFIT;

/** @brief  ebkȫ���˵���ʾ*/
D_Result
p_media_ebk_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT;

/** @brief ebkȫ���˵�����*/
D_Result
p_media_ebk_full_screen_window_hide(void) D_FUNCPOSTFIT;

/** @brief txtȫ���˵�����*/
D_Result
p_media_txt_full_screen_window_hide(void) D_FUNCPOSTFIT;

/** @brief �������б�˵���ʾ*/
D_Result
p_atv_media_ebook_show (void) D_FUNCPOSTFIT;

/** @brief ������ȫ����ʾ�˵�*/
D_Result
p_media_txt_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT;

/** @brief pvr��ʾ�˵�*/
D_Result
p_atv_media_pvr_show (void) D_FUNCPOSTFIT;

/** @brief pvrȫ����ʾ�˵�*/
D_Result
p_media_pvr_full_screen_show(D_Char* path_name, D_FileScan* fs, D_U16  pvr_index, D_Result (*mediaFullPvrHideHandler) (D_U16 param)) D_FUNCPOSTFIT;

/** @brief pvrȫ�����ز˵�*/
D_Result
p_media_pvr_full_screen_hide(void) D_FUNCPOSTFIT;

/** @brief pvr¼�Ʋ˵���ʾ*/
D_Result
p_atv_pvr_record_menu_show (void) D_FUNCPOSTFIT;

/** @brief pvr¼�Ʋ˵�����*/
D_Result
p_atv_meida_pvr_record_menu_hide(void)D_FUNCPOSTFIT;

/** @brief ��ʾ��ý����ʾ����*/
D_Result
p_atv_media_prompt_msg(D_ID id)D_FUNCPOSTFIT;

/** @brief ��ʾƵ����·��Ƶ����*/
D_Result
p_atv_multi_audio_window_show(void)D_FUNCPOSTFIT;


/** @brief ��ʾͼ���Ż��˵�*/
D_Result
p_atv_picture_optimize_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @breif ��ʾ��������*/
D_Result
p_full_search_window_show (D_StbScanType type,D_ScanTaskConfig *scan_config) D_FUNCPOSTFIT;

/** @breif ��ʾƵ����Ϣ����*/
D_Result
p_atv_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif����Ƶ����Ϣ����*/
D_Result
p_atv_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief  ѡ���Ƿ�ʼ�Զ������Ĳ˵�*/
D_Result
p_atv_auto_reset_select_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ���������*/
D_Result
p_atv_manual_scan_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��������*/
D_Result
p_full_search_window_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ǰʱ��˵�*/
D_Result
p_atv_pop_set_time_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief ��ʾ������ʱ�ػ��˵�*/
D_Result
p_atv_pop_power_off_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief ��ʾ������Ԥ��ʱ��˵�*/
D_Result
p_atv_pop_order_time_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief ��ʾ������ʱ�����˵�*/
D_Result
p_atv_pop_power_on_show (void (*pFunc)(void)) D_FUNCPOSTFIT;

/** @brief ��ʾƵ�������봰*/
D_Result
p_atv_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief ���Ƶ�������봰*/
D_Result
p_atv_chan_input_window_hide (void) D_FUNCPOSTFIT;

/** @brief ���������Ľ���ͼƬ*/
D_Result
p_vis_progress_draw (D_Visual *vis, D_ID imgage_id) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/
D_Result
p_atv_signal_input_show (D_VidInput input, char *video, char *audio) D_FUNCPOSTFIT;

/** @brief ��ʾ����������*/
D_Result
p_atv_mute_window_show (void) D_FUNCPOSTFIT;

/*�������ͼ����ʾ*/
D_Result 
p_atv_mute_window_clear()D_FUNCPOSTFIT;

/*����״̬������ʾ����ͼ��*/
D_Result
p_atv_reshow_mute_flag(void)D_FUNCPOSTFIT;

/** @breif ��ʾ����*/      
D_Result         
p_atv_tv_chan_list_show (void) D_FUNCPOSTFIT;

D_Result         
p_atv_radio_chan_list_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾƵ����Ϣ����*/
D_Result
p_atv_tv_chan_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif����Ƶ����Ϣ����*/
D_Result
p_atv_tv_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾͼ���Ż��˵�*/
D_Result
p_av_signal_select_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾɫ������*/
D_Result
p_atv_tint_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ֶ���������*/
D_Result
p_atv_auto_scan_window_show (void) D_FUNCPOSTFIT;

/** @brief �����˵�*/
D_Result
p_atv_factory_setting_show (void) D_FUNCPOSTFIT;

/** @brief ͨ�����ò˵�*/
D_Result
p_atv_general_setting_show (void) D_FUNCPOSTFIT;

/** @brief ͨ�����ò˵�*/
D_Result
p_atv_pwm_setting_show (void) D_FUNCPOSTFIT;

/** @brief �Ƶ�ģʽ�˵�*/
D_Result
p_atv_hotel_mode_setting_show (void) D_FUNCPOSTFIT;

/** @brief �������ò˵�*/
D_Result
p_atv_sound_setting_show (void) D_FUNCPOSTFIT;

/** @brief 	����ģʽ�˵�*/
D_Result
p_atv_sound_mode_show (void) D_FUNCPOSTFIT;

/** @brief 	�����˵�*/
D_Result
p_atv_volume_curve_show (void) D_FUNCPOSTFIT;

/** @brief audio output�˵�*/
D_Result
p_atv_audio_output_show (void) D_FUNCPOSTFIT;

/** @brief drc function�˵�*/
D_Result
p_atv_drc_function_show (void) D_FUNCPOSTFIT;

/** @brief peq�˵�*/
D_Result
p_atv_peq_set_show (void) D_FUNCPOSTFIT;

/** @brief 	����ģʽ�˵�*/
D_Result
p_atv_image_show (void) D_FUNCPOSTFIT;

/** @brief ��ƽ������˵�*/
D_Result
p_atv_wb_adjust_show (void) D_FUNCPOSTFIT;

/** @brief Ч���˵�*/
D_Result
p_atv_pq_nonlilnear_show (void) D_FUNCPOSTFIT;

/** @brief 	ͼ������˵�*/
D_Result
p_atv_setting_show (D_S16 flag) D_FUNCPOSTFIT;

/** @brief bl dim�˵�*/
D_Result
p_atv_bl_dim_show (void) D_FUNCPOSTFIT;

/** @brief ce�˵�*/
D_Result
p_atv_ce_set_show (void) D_FUNCPOSTFIT;

/** @brief ase�˵�*/
D_Result
p_atv_ase_show (void) D_FUNCPOSTFIT;

/** @brief gamma�˵�*/
D_Result
p_atv_gamma_show (void) D_FUNCPOSTFIT;

/** @brief 	DI/FM�˵�*/
D_Result
p_atv_difm_set_show (void) D_FUNCPOSTFIT;

/** @brief 	FTC�˵�*/
D_Result
p_atv_ftc_set_show (void) D_FUNCPOSTFIT;

/** @brief 	NR�˵�*/
D_Result
p_atv_nr_set_show (void) D_FUNCPOSTFIT;

/** @brief 	NR�˵�*/
D_Result
p_atv_de_set_show (void) D_FUNCPOSTFIT;

/** @brief 	ICM�˵�*/
D_Result
p_atv_icm_set_show (void) D_FUNCPOSTFIT;

/** @brief 	COMB�˵�*/
D_Result
p_atv_comb_set_show (void) D_FUNCPOSTFIT;

/** @brief 	COMP�˵�*/
D_Result
p_atv_comp_set_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ������Ϣ����*/      
D_Result         
p_atv_info_window_show (void) D_FUNCPOSTFIT;

/** @brief 	�����˵�*/
D_Result
p_atv_software_update_show (void) D_FUNCPOSTFIT;

/** @brief emc�˵�*/
D_Result
p_atv_emc_setting_show (void) D_FUNCPOSTFIT;

/** @brief adc adjust�˵�*/
D_Result
p_atv_adc_adjust_show (void) D_FUNCPOSTFIT;

/** @brief ��ʱ���˵�*/
D_Result
p_atv_timer_set_show (void) D_FUNCPOSTFIT;

/** @brief �������ʲ˵�*/
D_Result
p_atv_digital_adjust_show (void) D_FUNCPOSTFIT;

/** @brief 	DIGIT_TIMBRE�˵�*/
D_Result
p_atv_digit_timbre_show (D_Bool flag) D_FUNCPOSTFIT;

/** @brief tv�������ò˵�*/
D_Result
p_atv_tv_scan_config_show (void) D_FUNCPOSTFIT;

/** @brief dtv�������ò˵�*/
D_Result
p_atv_dtv_scan_config_show (void) D_FUNCPOSTFIT;

/** @brief ���źŲ˵���ʾ*/
D_Result
p_atv_no_signal_win_show (void) D_FUNCPOSTFIT;

/** @brief ���źŲ˵�����*/
D_Result
p_atv_no_signal_win_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾ������ʾ�˵�*/
D_Result
p_atv_power_off_msg_show (void) D_FUNCPOSTFIT;

/** @brief 	avc dac ctl�˵�*/
D_Result
p_atv_avc_dac_ctl_show (D_U32 param) D_FUNCPOSTFIT;

/** @brief ��ʾ����ģʽ�˵�*/
D_Result
p_atv_media_zoom_mode_show (void) D_FUNCPOSTFIT;

/** @brief set register�˵�*/
D_Result
p_atv_set_register_show (D_U8 val) D_FUNCPOSTFIT;

/** @brief ���ȫ��״̬�µ�������ʾ*/
D_Result
p_atv_player_window_clear_osd (D_U32 param) D_FUNCPOSTFIT;

/** @brief Ƶ��Ԥ�ò˵�*/
D_Result
p_atv_program_reset_show (void) D_FUNCPOSTFIT;

/** @brief �㲥��ʾ�˵���ʾ*/
D_Result
p_atv_radio_icon_win_show (D_ID dbsrvid) D_FUNCPOSTFIT;

/** @brief �㲥��ʾ�˵�����*/
D_Result
p_atv_radio_icon_win_hide (void) D_FUNCPOSTFIT;

/** @brief ������λ*/
D_Result
tv_reset_factory_setting(void) D_FUNCPOSTFIT;


/** @brief ��ʾ�������봰��
* @param prio           ��Ϣ������ȼ�
* @param layer      ��ʾ���ڵĲ�
* @param type       ���������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ
* @param len            �����ַ�����
* @param user_hide  �û��Ƿ�����ֶ��˳�
* @param handler    ѡ����ص�����ָ��
* @param param      �����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ������ʾ���û����봰��
* @param prio           ��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pwd_input_window_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ��ʾca�Ĺ��ò˵�ģ��*/
D_Result
p_atv_ca_main_window_show(void)D_FUNCPOSTFIT;

/** @brief ��ʾ���л�*/
D_Result
p_atv_serial_show (void) D_FUNCPOSTFIT;

/** @brief ��һ�����ڣ�Ϊ��������osd*/
D_Bool
p_osd_show (D_Bool show_en, D_U32 handle) D_FUNCPOSTFIT;

/** @brief ��һ������,Ϊ��ý�岥��*/
D_Result
p_show_osd_window (D_Bool show_en) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/
D_Result
p_atv_wifi_window_show (void) D_FUNCPOSTFIT;

/** @breif ���ش���*/
D_Result
p_atv_wifi_window_hide (D_Bool show) D_FUNCPOSTFIT;

/** @breif ��ʾwifi���ô���*/
D_Result
p_atv_wlan_menu_show(void)D_FUNCPOSTFIT;

/** @breif ��ʾwifi���ô���*/
D_Result
p_atv_wifi_setting_window_show (void) D_FUNCPOSTFIT;

/** @breif �ر�wifi���ô���*/
D_Result
p_atv_wifi_setting_window_close (void) D_FUNCPOSTFIT;

/** @brief wifi ״̬��Ϣ������ʾ*/
//D_Result
//p_atv_wifi_detail_info_window_show(void)D_FUNCPOSTFIT;

/** @brief wifi ״̬��Ϣ���ڹر�*/
D_Result
p_atv_wifi_detail_info_window_colse(void)D_FUNCPOSTFIT;

/** @brief �ı����� ������ʾ
* @param strtitle			Ҫ��ʾ�ı����ı�
* @param strdef			Ĭ���ı�
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
*/
D_Result
p_atv_textinput_window_show(D_Char *strtitle, D_Char *strdef, D_U32 min_len, D_U32 max_len, D_Result (*handler) (D_Char *text, D_U32 param, D_U32 action) D_FUNCPOSTFIT, D_U32 param )D_FUNCPOSTFIT;

/** @brief rename �ı����봰�ڹر�*/
D_Result
p_atv_textinput_window_colse(void)D_FUNCPOSTFIT;

/** @breif ��ʾ����*/
D_Result
p_atv_zhilian_tv_window_show (D_U32 type, D_Bool auto_start) D_FUNCPOSTFIT;

/** @breif ���ش���*/
D_Result
p_atv_zhilian_tv_window_hide (void) D_FUNCPOSTFIT;

/** @breif ֪ͨ������ʾ����״̬*/
D_Result
p_atv_zhilian_tv_window_show_status (D_U32 status, D_Char *name) D_FUNCPOSTFIT;

/** @breif ���ػ�������ʾ���ڣ������ͷŴ���*/
D_Result
p_atv_zhilian_tv_window_show_enable (D_Bool show) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/
D_Result
p_atv_zhilian_tv_window_show_shortcut (D_U32 type) D_FUNCPOSTFIT;

/** @breif ��ʾ����*/
D_Result
p_atv_ts2net_window_show (D_U32 x, D_U32 y, D_Result (*handler) (D_U32 action)) D_FUNCPOSTFIT;

/** @breif ���ش���*/
D_Result
p_atv_ts2net_window_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾdlna��Ƶ���Ŵ���*/
D_Result
p_atv_dlna_window_show(D_Char*  file_path , D_Char*  file_title, D_VidInput lastinput) D_FUNCPOSTFIT;

/** @brief �ر�dlna��Ƶ���Ŵ���*/
D_Result
p_atv_dlna_window_hide(void) D_FUNCPOSTFIT;

/** @brief ֪ͨdlna��Ƶ���Ŵ�������״̬*/
D_Result
p_atv_dlna_window_network_error(D_U32 action) D_FUNCPOSTFIT;

/** @brief ��ʾairplay��Ƶ���Ŵ���*/
D_Result
p_atv_airplay_window_show(D_Char*  file_path, D_U32 mode, void (*cb)(D_U32 action)) D_FUNCPOSTFIT;

/** @brief �ر�airplay��Ƶ���Ŵ���*/
D_Result
p_atv_airplay_window_hide(void) D_FUNCPOSTFIT;

/** @brief airplay��Ƶ���Ŵ����Ƿ�����ʾ*/
D_Bool
p_atv_airplay_window_is_show(void) D_FUNCPOSTFIT;

/** @brief ֪ͨairplay��Ƶ���Ŵ�������״̬*/
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
