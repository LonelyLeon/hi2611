/** @file
* @brief STB�˵��ӿ�
* @author ����
* @date 2013-7-05 ����: �����ļ�
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


/** @brief �˵���ʼ��*/
D_Result
p_stb_menu_init (void) D_FUNCPOSTFIT;

/** @brief �˵�ж��*/
D_Result
p_stb_menu_deinit (void) D_FUNCPOSTFIT;

/** @brief ����ca�˵�*/
D_Result
p_stb_set_ca_menu_ex(D_GUIMenu *camenu) D_FUNCPOSTFIT;

/** @brief �ж��Ƿ����ca�˵�*/
D_Bool
p_stb_judge_ca_menu(void) D_FUNCPOSTFIT;

/** @breif ��ʾ����������*/
D_Result	
p_stb_player_win_show (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ȡ�����洰�ڶ�Ӧ�Ŀؼ�(��player win)*/
D_Visual*
p_desktop_get_control (void) D_FUNCPOSTFIT;

/** @brief �����Ƿ�������ʾ�ź��ж���ʾ
* @param[in] enable ʹ�����
* @param[in] lock ����ȫ��״̬��0��������1������2ȡ������
* @retval D_OK
*/
D_Result
p_set_signal_faint_msg_enable(D_Bool enable, D_U8 lock)D_FUNCPOSTFIT;

/** @brief �ź��ж���ʾ����ʾ�����*/
D_Result
p_signal_faint_msg(D_Bool show)D_FUNCPOSTFIT;

/** @brief ������ʾ�ź��ж���ʾ��Ϣ*/
D_Result
p_signal_faint_msg_reshow(void)D_FUNCPOSTFIT;

/** @brief û�б����Ŀ��ʾ����ʾ�����*/
D_Result
p_no_prog_msg(D_Bool show)D_FUNCPOSTFIT;

D_Result 
p_set_curr_menu(D_GUIMenu *curr, D_Bool init)D_FUNCPOSTFIT;

/** @breif ��ʾ���˵�*/
D_Result
p_stb_main_menu_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ�����˵�*/
D_Result
p_stb_scan_item_menu_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��Ϸ�˵�*/
D_Result
p_stb_game_item_menu_show (void) D_FUNCPOSTFIT;

/** @brief ��ݼ���ʾepg�˵�*/
D_Result
p_stb_k_epg_menu_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��������*/
D_Result
p_stb_scan_window_show (D_StbScanType type, D_ScanTaskConfig *scan_config) D_FUNCPOSTFIT;

/** @brief ��ʾ��ʾ���ò˵�����*/
D_Result
p_stb_picture_set_menu_show(void)D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ���������*/
D_Result
p_stb_auto_scan_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ֶ��������ô���*/
D_Result
p_stb_manual_scan_show(void) D_FUNCPOSTFIT;

D_Result
p_stb_dvbc_manual_scan_show(void) D_FUNCPOSTFIT;


/** @breif ��ʾȫ�����������ô���*/
D_Result
p_stb_full_scan_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�Զ���������*/
D_Result
p_stb_power_scan_show(D_U8 mode) D_FUNCPOSTFIT;

/** @breif ��ʾ��̨��������*/
D_Result
p_stb_bg_scan_window_show(D_ID dbtsid) D_FUNCPOSTFIT;

/** @breif �رպ�̨��������*/
D_Result
p_stb_bg_scan_window_close(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�źż�ⴰ��*/
D_Result
p_stb_signal_detect_show (void) D_FUNCPOSTFIT;

D_Result
p_stb_dvbc_signal_detect_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������ڴ���*/
D_Result
p_audio_adjust_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @breif ����������ڴ���*/
D_Result
p_audio_adjust_window_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾ����������*/
D_Result
p_stb_mute_window_show (void) D_FUNCPOSTFIT;


/*�������ͼ����ʾ*/
D_Result 
p_stb_mute_window_clear()D_FUNCPOSTFIT;

/*����״̬������ʾ����ͼ��*/
D_Result
p_stb_reshow_mute_flag(void)D_FUNCPOSTFIT;

/** @brief ��ʾƵ�������봰*/
D_Result
p_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;


/** @brief ���Ƶ�������봰*/
D_Result
p_chan_input_window_hide (void) D_FUNCPOSTFIT;


/** @breif ��ʾ����*/
D_Result
p_stb_tv_chan_edit_show (void) D_FUNCPOSTFIT;


/** @breif ��ʾ����*/
D_Result
p_stb_radio_chan_edit_show (void) D_FUNCPOSTFIT;


D_Result         
p_stb_tv_chan_list_show (void) D_FUNCPOSTFIT;
/** @breif ��ʾ����Ƶ����Ϣ*/
D_Result         
p_stb_chan_spectrum_show (void) D_FUNCPOSTFIT;

D_Result         
p_stb_radio_chan_list_show (void) D_FUNCPOSTFIT;


D_Result         
p_tv_chan_list_window_show_favor (void) D_FUNCPOSTFIT;

D_Result         
p_radio_chan_list_window_show_favor (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ŀָ�ϴ���*/
D_Result
p_stb_epg_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾԤԼ����*/
D_Result
p_stb_sub_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��������*/
D_Result
p_stb_audio_track_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾʱ�����ô���*/
D_Result 
p_stb_time_zone_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ�������ô���*/
D_Result
p_stb_password_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ  ��ʾ���ô���*/
D_Result 
p_stb_display_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ƶ�����ô���*/
D_Result
p_stb_main_tp_set_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ƶ�����ô���*/
D_Result
p_stb_dvbc_main_tp_set_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ������Ϣ����*/
D_Result         
p_stb_info_window_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��������Ϸ����*/
D_Result
p_game_trunck_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ�齫��Ϸ����*/
D_Result
p_game_mahjong_show (void) D_FUNCPOSTFIT;

/** @brief ��ʾ����˹������Ϸ����*/
D_Result
p_game_tetris_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾƵ����Ϣ����*/
D_Result
p_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif����Ƶ����Ϣ����*/
D_Result
p_chan_info_window_hide(void) D_FUNCPOSTFIT;

/** @breif ��ʾ�ָ����ô���*/


/*@breif ��ʾ¼�������*/
D_Result p_pvr_manage_window_show(void) D_FUNCPOSTFIT;

/*@brief �洢��Ϣ����*/
D_Result p_storage_info_menu_show(void) D_FUNCPOSTFIT;

D_Result 
p_stb_restore_setting_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ��Ŀ�����Ϣ����(���ڲ���)*/
D_Result d_dtmb_chan_info_test_window_show () D_FUNCPOSTFIT;

/** @breif ���ؽ�Ŀ�����Ϣ����(���ڲ���)*/
D_Result d_dtmb_chan_info_test_window_hide () D_FUNCPOSTFIT;

/** @breif ��ʾ��Ŀ�����Ϣ����(���ڲ���)*/
D_Result d_dvbc_chan_info_test_window_show () D_FUNCPOSTFIT;

/** @breif ���ؽ�Ŀ�����Ϣ����(���ڲ���)*/
D_Result d_dvbc_chan_info_test_window_hide () D_FUNCPOSTFIT;

/** @breif ��ʾ��Ŀ����ѡ�񴰿�*/
typedef D_Result (* FUNC)(D_U8 type) D_FUNCPOSTFIT;	//���庯��ָ��
D_Result
d_sort_select_box_window_show (FUNC func) D_FUNCPOSTFIT;


/*��ʾ��Ŀ�����������*/
D_Result p_show_prog_password_window(D_U32 param) D_FUNCPOSTFIT;
/*�����Ŀ�����������*/
D_Result p_clear_prog_password_window(void) D_FUNCPOSTFIT;

/*��ý���б���*/
D_Result
d_enter_media_list_menu(void)D_FUNCPOSTFIT;

/** @brief ���ڳ�ʼ��*/
D_Result
p_ebk_full_screen_window_show (D_Char *path) D_FUNCPOSTFIT;

/** @breif ��ʾ�ֶ�����ѡ�񴰿�*/
D_Result
p_stb_auto_scan_select_show(void)D_FUNCPOSTFIT;

/** @breif ��ʾ�������ô���*/
D_Result
p_stb_scan_config_window_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾEPG����*/
D_Result
p_stb_atv_epg_window_show (void) D_FUNCPOSTFIT;

/*��Ŀ�޷�������ʾ��Ϣ*/
D_Result
p_not_play_msg_show(D_Bool show)D_FUNCPOSTFIT;

/*��ʾû�н�Ŀ����ʾ��Ϣ*/
D_Result
p_no_es_stream_show(D_Bool show, D_Bool play_logo)D_FUNCPOSTFIT;

int p_set_curr_usb_status(D_Bool plug, D_Ptr arg);
#ifdef  __cplusplus
}
#endif
#endif

