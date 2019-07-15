#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "atv_reset_window.c"


extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define P_SHOW_TIME (5000)
#define P_MSG_TIME (3000)

typedef struct
{
    D_U32    menu_show_time;
	D_Bool first_flag;
} D_ResetData;

static D_ResetData *reset_data = NULL;


extern D_Result set_OrderTime_chan(D_S16 chan);
extern D_Result
p_set_poweroff_timer_enable(D_Bool enable, D_U8 hour, D_U8 minute)D_FUNCPOSTFIT;
extern D_Result set_Order_time(D_U8 enable, D_U8 hour, D_U8 minute);

static D_VidFormat get_output_fmt(void)
{
    D_U8 *payload;
    D_U16 len;

    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_LVDS, &len);
    if(!payload || (len < 4))
    {
        return D_VID_FMT_1080P_50;
    }
    switch(payload[0])
    {
        case 0://BOE_32_768P_50
            return D_VID_FMT_768P_50;
        case 1://BOE_32_768P_60
        case 9://LC390TU1A屏
        case 10://奇美32寸v320BJ6-q01
        case 11://TLB315DF39-09
            return D_VID_FMT_768P_60;
        case 2://BOE_40_1080P_50
		case 12://M236HGE-L20
            return D_VID_FMT_1080P_50;
        case 3://BOE_40_1080P_60
            return D_VID_FMT_1080P_60;
        case 4://SANYO_46_1080P_50
            return D_VID_FMT_1080P_50;
        case 5://SANYO_46_1080P_60
            return D_VID_FMT_1080P_60;
        case 6://FMT_1440_900
            return D_VID_FMT_1440_900;
        case 7://
        case 8://
            return D_VID_FMT_1024_600;
        default:
            return D_VID_FMT_1080P_50;
    }
}

/** @brief 发送更新语言事件*/
static D_Result
atv_send_update_language_evt(D_U32 curr_lang)D_FUNCPOSTFIT
{
    D_Msg user_msg = {0};

    user_msg.type = D_MSG_USER;
    user_msg.user.handle = D_INVALID_HANDLE;
    user_msg.user.param1 = USER_MSG_PARAM1_LANGUAGE_CHANGE;
    user_msg.user.param2 = curr_lang;
    d_queue_try_send(d_gui_get_queue(), (D_U8*)&user_msg, sizeof(user_msg));

    return D_OK;
}


/** @brief 按下确定键后恢复出场设置*/
static D_Result
restore_factory_setting(void) D_FUNCPOSTFIT
{
    D_DBTSInfo ts_info;
    D_StbPlayer *player;
    D_VidInput input;
    D_U8 bdinput;
    D_VidOutput out_old, out;
    D_U8 lang_old, lang;
    D_VidPicRatio vid_ratio_old, vid_ratio;
    D_Bool  mute_old, mute;
    D_U8    change_mode_old, change_mode;
    D_U8 ratio_mode_old, ratio_mode;
    D_U8 balance_old, balance;
    D_U8 ntscflag;
    
    input = p_conf_get_vid_input();
    bdinput = p_vip_get_dbinput(input);
    player = p_stb_get_player(0);
    p_tvconf_get_cur_zoommode(&ratio_mode_old, bdinput);
    balance_old =  p_conf_get_balance ();
    
    if(input == D_VID_IUTPUT_TV)
    {
        /*禁止显示信号中断*/
        p_set_signal_faint_msg_enable(D_FALSE, 0);

        /*停止所有播放*/
        d_stb_stop_play ();
        /*清除残留视频帧*/
        p_stb_player_clear_vid(0);

#if 0    /*菜单复位功能，不清除节目 @qiny 2015.08.20*/   
        /*LED显示*/
        d_fp_set_led (0, "0000");
        /*重置播放器*/
        d_dbase_set_rset_en(0);

        d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_ATV);
        d_dbase_delete_ts_by_type(D_FEND_ANALOG);
        p_stb_player_reset (0);
#endif
    }
    else if(input == D_VID_IUTPUT_DTV)
    {
        /*禁止显示信号中断*/
        p_set_signal_faint_msg_enable(D_FALSE, 0);
        /*停止所有播放*/
        d_stb_stop_play ();
        /*清除残留视频帧*/
        p_stb_player_clear_vid(0);

#if 0    /*菜单复位功能，不清除节目 @qiny 2015.08.20*/   
        /*LED显示*/
        d_fp_set_led (0, "0000");
        /*重置播放器*/

        d_dbase_set_rset_en(0);

        d_dbase_clear_evt ();
        d_dbase_clear_bouq();

        /*可能也预定电视广播之外的节目，如atv，因此这里不能删除所有
        在clear srv，即删除节目时，会删除此节目的预定记录。qiny*/
        //d_dbase_clear_subscribe ();
        //clear srv
        d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_TV | D_DB_SRV_ACTION_RADIO);
        d_dbase_delete_ts_by_type(D_FEND_DTMB);
        d_dbase_delete_ts_by_type(D_FEND_DVBC);

        p_stb_player_reset (0);
#endif
    }
    else
    {
        //不处理
    }

    /*取得恢复操作之前的配置参数*/
    lang_old = p_conf_get_lang();
    out_old = p_conf_get_vid_output ();
    vid_ratio_old = p_conf_get_vid_pic_ratio ();
    mute_old = p_conf_get_aud_mute ();
    change_mode_old = p_conf_get_channel_change_mode();

    p_conf_restore (D_FALSE);
//输出制式
    p_conf_set_vid_fmt (get_output_fmt());

    /*恢复输入源*/
    p_conf_set_vid_input(input);
	
    p_tvconf_restore_input_usr(p_vip_get_dbinput(input));
    p_tvconf_restore_usr();

#if 1
    {
        D_Tv_Config_Poweron_Order   order = {0};
        D_Tv_Config_Poweron_Order   order1 = {0};
        D_S16 boot_num;
        
        boot_num = -1;
        p_tvconf_set_boot_chan(&boot_num); // 清除atv开机频道
        set_OrderTime_chan(-1);	// 清除atv预约频道
        set_Order_time(0,0,0); // 清除预约时间  
        
        // 清除开关机时间
        p_tvconf_set_poweron_order(&order);
        p_tvconf_set_poweroff_order(&order1);
        p_set_poweroff_timer_enable(0,0,0);
    }
#endif     
    
    /*刷新数据库*/
    d_dbase_flush();

    /*取得恢复操作之后的配置参数*/
    lang = p_conf_get_lang();
    out = p_conf_get_vid_output ();
    vid_ratio = p_conf_get_vid_pic_ratio ();
    mute = p_conf_get_aud_mute ();
    change_mode = p_conf_get_channel_change_mode();
    balance =  p_conf_get_balance();
    
    /*设置视频输出模式*/
    if(out != out_old)
    {
        d_tv_set_vid_output (player->htv, out);
    }

    /*设置视频宽高比*/
    if(vid_ratio != vid_ratio_old)
    {
        d_tv_set_pic_ratio(player->htv, vid_ratio);
    }

    /*设置静音与否状态*/
    if(mute != mute_old)
    {
        if(!mute)
        {
            /*清除静音图标*/
            p_atv_mute_window_clear();
        }
        d_tv_set_aud_mute (player->htv, mute);
    }
    
    /*设置换台黑屏静帧模式*/
    if(change_mode != change_mode_old)
    {
        d_tv_set_chan_change_blank(player->htv, (!change_mode) ? D_TRUE : D_FALSE);
    }

    /*设置声音平衡*/
    if(balance != balance_old)
    {
        d_av_set_balance (0, balance); 
    }        

    /*设置声音平衡*/
    p_stb_player_set_vol(0, p_conf_get_volume());

    /*设置菜单透明度*/
    {
        D_GSurface  *surf;
        D_U8    transp;
        D_U8 transparency[] = {128, 115, 90, 64, 38};

        transp = p_conf_get_transp ();
        transp = (transp > 4) ? 0 : transp;
#if 0
        surf = d_gui_get_surface ();
        if (surf)
        {
            d_gdev_set_global_alpha (surf->hgdev, transparency[transp]);
        }
#else
        d_gdev_set_global_alpha (p_gui_get_hgdev(), transparency[transp]);
#endif
    }
	
    if(lang_old != lang)
    {
        d_gui_lang_set(lang);
        d_gui_reload_string();
        atv_send_update_language_evt(lang);
    }

	ntscflag = p_vip_get_ntscflag();
    ntscflag = D_MIN(ntscflag, 1);
    p_vip_init(input, 0, ntscflag, 1);

    p_tvconf_get_cur_zoommode(&ratio_mode, bdinput);
    if(ratio_mode_old != ratio_mode)
    {
        p_set_ratio_mode (ratio_mode);
    }

    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, \
    d_gui_get_text(atv_IDS_RESTORE_OK), P_MSG_TIME, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);


    if(input == D_VID_IUTPUT_DTV)
    {
        if(d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_TV) == 0 && d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_RADIO) == 0)
        {
            p_no_prog_msg(D_TRUE);
            p_set_signal_faint_msg_enable(D_TRUE, 2);
        }
        else
        {
            p_stb_player_play_valid(0);
        }
    }
    else if(input == D_VID_IUTPUT_TV)
    {
        if(d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_ATV) == 0)
        {
            p_no_prog_msg(D_TRUE);
            p_set_signal_faint_msg_enable(D_TRUE, 2);
        }
        else
        {
            p_stb_player_play_valid(0);
        }
    }
    return D_OK;
}

static D_Result
restore_factory_setting_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    if(sel)
    {
        restore_factory_setting();
    }
    return D_OK;
}

/** @brief 确定复位事件处理*/
static D_Result
button_reset_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
/*            d_gui_clear_menu();*/
            return d_atv_pop_select_show(4, D_GUI_LAYER_MESSAGE, NULL,
            d_gui_get_text(atv_IDS_DEFAULT_SET), P_SHOW_TIME, D_FALSE, restore_factory_setting_callback, 0) ;
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_reset_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_reset_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_RESET_BUTTON_RESET);
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
					if(reset_data->first_flag == D_TRUE)
					{
						d_vis_enable(vis_button, D_TRUE);
                    	d_vis_set_focusable(vis_button, D_TRUE);
                    	d_vis_set_focus(vis_button);

						reset_data->first_flag = D_FALSE;
					}
                    else
                    {
                        d_gui_clear_menu();
                        return d_atv_pop_select_show(4, D_GUI_LAYER_MESSAGE, NULL,
                        d_gui_get_text(atv_IDS_DEFAULT_SET), P_SHOW_TIME, D_FALSE, restore_factory_setting_callback, 0) ;
                    }
                    break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(reset_data->first_flag == D_FALSE)
					{
	                    d_vis_enable(vis_button, D_FALSE);
	                    d_vis_set_focusable(vis_button, D_FALSE);

						reset_data->first_flag = D_TRUE;
					}
					else //if(evt->fp.key != D_KEY_BACK)
					{
						return d_gui_clear_menu();
					}
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
				case D_KEY_UP:
                case D_KEY_PNL_U:
				case D_KEY_DOWN:
                case D_KEY_PNL_D:
				case D_KEY_LEFT:
                case D_KEY_PNL_L:
				case D_KEY_RIGHT:
                case D_KEY_PNL_R:
					if(reset_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(reset_data->first_flag == D_TRUE)
					{
						return D_ERR;
					}
				case D_KEY_SOURCE:
				case D_KEY_SCREEN:
					d_gui_clear_menu();
					return D_ERR;
				case D_KEY_MUTE:
					return D_ERR;
                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(reset_data)
            {
                PROJECT_FREE(reset_data);
                reset_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_reset_window_init(D_Frame *frm)
{
    D_Visual *vis;

    reset_data = (D_ResetData*)PROJECT_ALLOC(sizeof(D_ResetData));
    if(!reset_data)
    {
        return D_ERR;
    }
    memset(reset_data, 0x00, sizeof(D_ResetData));

	reset_data->first_flag = D_TRUE;

    vis = d_frame_get_control(frm, ID_RESET_BUTTON_RESET); //确定复位
    if(vis)
    {
        d_vis_set_handler (vis, button_reset_handler);
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
    }
	vis = d_frame_get_control (frm, ID_RESET_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_reset_window_handler);
    }
    return D_OK;
}

/** @brief 复位菜单*/
D_Result
p_atv_reset_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_reset_window, D_FALSE);
}

