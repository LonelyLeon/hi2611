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


/** @brief �˵���ʼ��*/
D_Result
p_tv_menu_init (void) D_FUNCPOSTFIT;

/** @brief �˵�ж��*/
D_Result
p_tv_menu_deinit (void) D_FUNCPOSTFIT;

/** @brief ��ʾ���˵�*/
D_Result
p_tv_main_menu_show (void) D_FUNCPOSTFIT;

/** @breif ��ʾ����������*/
D_Result
p_atv_player_win_show (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ȡ�����洰�ڶ�Ӧ�Ŀؼ�*/
D_Visual*
p_atv_get_player_window (void) D_FUNCPOSTFIT;

/** @brief �����Ƿ�������ʾ�ź��ж���ʾ
* @param[in] enable ʹ�����
* @param[in] lock ����ȫ��״̬��0��������1������2ȡ������
* @retval D_OK
*/
D_Result
p_tv_set_signal_faint_msg_enable(D_Bool enable, D_U8 lock)D_FUNCPOSTFIT;

/** @brief �ź��ж���ʾ����ʾ�����*/
D_Result
p_tv_signal_faint_msg(D_Bool show)D_FUNCPOSTFIT;

/** @brief ������ʾ�ź��ж���ʾ��Ϣ*/
D_Result
p_tv_signal_faint_msg_reshow(void)D_FUNCPOSTFIT;

/** @brief û�б����Ŀ��ʾ����ʾ�����*/
D_Result
p_tv_no_prog_msg(D_Bool show)D_FUNCPOSTFIT;

/** @breif ��ʾƵ����Ϣ����*/
D_Result
p_tv_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT;

/** @breif����Ƶ����Ϣ����*/
D_Result
p_tv_channel_info_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾƵ�������봰*/
D_Result
p_tv_chan_input_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @brief ���Ƶ�������봰*/
D_Result
p_tv_chan_input_window_hide (void) D_FUNCPOSTFIT;

/**@brief �����б���*/
D_Result
p_tv_channel_list_window_show(void) D_FUNCPOSTFIT;

/**@brief ��Ƶ�б���*/
D_Result
p_video_list_window_show(void) D_FUNCPOSTFIT;

/**@brief �����б���*/
D_Result
p_music_play_list_window_show(void) D_FUNCPOSTFIT;

/**@brief ͼƬ�б���*/
D_Result
p_tv_picture_menu_show(void)D_FUNCPOSTFIT;

/**@brief �������б���*/
D_Result
p_txt_menu_window_show(void) D_FUNCPOSTFIT;

/**@brief ��������ʾ����*/
D_Result
p_fm_menu_window_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ֱ����������*/
D_Result 
p_tv_vertical_progress_window_show(D_GUILayer layer,D_Coord x, D_Coord y, 
                                                                            D_U16 max_cnt, D_U16 def_val, 
                                                                            D_Result (*handler) (D_U16 val, D_U32 param),  D_U32 param) D_FUNCPOSTFIT;

/** @brief �رմ�ֱ����������*/
D_Result 
p_tv_vertical_progress_window_hide(void) D_FUNCPOSTFIT;

/** @brief �ļ�������*/
D_Result
p_tv_file_management_window_show(void)D_FUNCPOSTFIT;

/** @brief ��ʾ���ſ��Ʋ˵�����*/
D_Result 
p_tv_menu_list_window_show(void) D_FUNCPOSTFIT;

/** @brief ��ʾ��Ƶ���ſ��Ʋ˵�����*/
D_Result 
p_video_menu_list_window_show(D_Char *path , TV_MEDIA_D_FileScan *fs, D_ID index, D_MovieInfo    movie_info)D_FUNCPOSTFIT;

/** @brief ���ز��ſ��Ʋ˵�����*/
D_Result 
p_tv_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief ������Ƶ���ſ��Ʋ˵�����*/
D_Result 
p_video_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾ���ֲ��ſ��Ʋ˵�����*/
D_Result 
p_music_menu_list_window_show(D_U32 usb_sd_flag, D_U32 play_mode, D_Result (*handler)(D_U32 action_type, D_U32 param)D_FUNCPOSTFIT) D_FUNCPOSTFIT;

/** @brief ������Ƶ���ſ��Ʋ˵�����*/
D_Result 
p_music_menu_list_window_hide(void) D_FUNCPOSTFIT;

/** @brief ȫ������ͼƬ���ƴ�����ʾ*/
D_Result 
p_pic_full_screen_menu_show(D_Char *path , TV_MEDIA_D_FileScan *fs, D_ID index, D_U32 usb_or_sd, D_Result (*handler) (D_U16 focus_id)D_FUNCPOSTFIT)D_FUNCPOSTFIT;

/** @briefͼƬ�ļ�Ԥ������*/
D_Result
p_tv_picture_menu_show(void)D_FUNCPOSTFIT;

/** @brief������Ԥ������*/
D_Result
p_tv_calender_menu_show(void)D_FUNCPOSTFIT;


/** @brief ��ʾ�����ݼ�����*/
D_Result
p_tv_shortcut_key_window_show (void) D_FUNCPOSTFIT;

/** @brief ��������ݼ�����*/
D_Result
p_tv_shortcut_key_window_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��ؼ��ؼ�*/
D_Result
p_tv_battery_visual_show (D_Visual *vis_parent, D_Coord x, D_Coord y, D_U32 check_ms, D_U16 type) D_FUNCPOSTFIT;

/**@brief ���ÿ��Ʋ˵�����*/
D_Result
p_tv_set_up_window_show(void)D_FUNCPOSTFIT;

/** @brief pvr�˵�����*/
D_Result
p_pvr_list_menu_window_show(void) D_FUNCPOSTFIT;

/** @brief pvr¼�Ʋ˵�����*/
D_Result
p_pvr_record_menu_window_show(void) D_FUNCPOSTFIT;


/** @brief pvr¼������ʱ��˵�����*/
D_Result
p_pvr_input_time_window_show(void) D_FUNCPOSTFIT;


/** @breif ��ʾ��������*/
D_Result
p_tv_volume_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT;

/** @breif ����������ڴ���*/
D_Result
p_tv_volume_window_hide (void) D_FUNCPOSTFIT;

/** @brief ��ʾ��Ƶ���ſ���menu�˵�*/
D_Result 
p_video_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief ������Ƶ���ſ���menu�˵�����*/
D_Result 
p_video_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾͼƬ���ſ���menu�˵�*/
D_Result 
p_photo_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief ����ͼƬ���ſ���menu�˵�����*/
D_Result 
p_photo_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾpvr���ſ���menu�˵�*/
D_Result 
p_pvr_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief ����pvr���ſ���menu�˵�����*/
D_Result 
p_pvr_preview_menu_window_hide(void) D_FUNCPOSTFIT;

/** @brief ��ʾtxt���ſ���menu�˵�*/
D_Result 
p_txt_preview_menu_window_show(D_U32 usb_sd_flag,  D_Result (*handler)(D_U32 action_type, D_U32 param)) D_FUNCPOSTFIT;

/** @brief ����txt���ſ���menu�˵�����*/
D_Result 
p_txt_preview_menu_window_hide(void) D_FUNCPOSTFIT;


/** @brief ��ʾ�ֶ���������*/
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
