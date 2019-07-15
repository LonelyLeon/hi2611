/** @file
* @brief 窗口模块
* @author覃宜
* @date 2013-7-1 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pPlayer.h"
#include "pStbMenus.h"
#include "pCustomConfig.h"
#include "atv_voicebar_window.c"
#include "dadporting.h"
#include "pAdvertisementShow.h"

static D_U32 menu_show_time;
static D_Char strnum[4] = {0};
static D_HTimer  htimer = D_INVALID_HANDLE;
static D_U16    current_voice = 0;
static D_StbPlayer  *curr_player;
static D_Bool   smart_volume = D_TRUE;
static D_DBSrvID  curr_srv_id = -1;


/** @brief 更新显示*/
static D_Result
audio_adj_update (D_FPKey key, D_Bool repeat) D_FUNCPOSTFIT
{
    D_DBSrvInfo info = {0};
    D_S8        vol = 0;
    D_S8    set_vol;
    D_S8    adapt_vol = 0;
    D_Bool  get_srv_flag = D_FALSE;
    D_Bool  clear_mute = D_FALSE;
    static D_S8 vol_add = 0;

    if(repeat)
    {
        vol_add = 0;//D_MIN((vol_add + 1), 1);
    }
    else
    {
        vol_add = 0;
    }

    /*是否使用音量补偿功能*/
    if(g_custom_config.sys_setup.vol_compensate)
    {
        vol = (D_S8)p_conf_get_volume ();

        if ((curr_srv_id != -1) && (d_dbase_get_srv_info (curr_srv_id, &info) >= 0))
        {
            get_srv_flag = D_TRUE;
            adapt_vol = info.volume;
            /*防止补偿音量过小或过大*/
            adapt_vol = (adapt_vol < 0) ? D_MAX(adapt_vol, (0 - P_VOLUME_MAX)) : D_MIN(adapt_vol, P_VOLUME_MAX);
        }
    }
    else
    {
#if 0
        if(smart_volume)
        {
            if ((curr_srv_id != -1) && (d_dbase_get_srv_info (curr_srv_id, &info) >= 0))
            {
                get_srv_flag = D_TRUE;
                vol = info.volume;
                adapt_vol = 0;
            }
            else
            {
                get_srv_flag = D_FALSE;
                vol = (D_S8)p_conf_get_volume ();
                adapt_vol = 0;
            }
        }
        else
#endif
        {
            vol = (D_S8)p_conf_get_volume ();
            adapt_vol = 0;
        }
    }

    switch (key)
    {
        //case D_KEY_LEFT:
        case D_KEY_PNL_L:
        case D_KEY_VOLUME_MINUS:
            vol = (vol - 1 - vol_add);
            break;
        //case D_KEY_RIGHT:
        case D_KEY_PNL_R:
        case D_KEY_VOLUME_PLUS:
            vol = (vol + 1 + vol_add);
            clear_mute = D_TRUE;
            break;
        default:
            break;
    }

    vol = D_MIN(vol, P_VOLUME_MAX);
    vol = D_MAX(0, vol);

    current_voice = vol;

    /*音量加时，取消静音状态*/
    if (clear_mute && p_conf_get_aud_mute())
    {
        p_atv_mute_window_clear();
        d_tv_set_aud_mute (g_stb->player->htv, D_FALSE);
        p_conf_set_aud_mute (D_FALSE);
    }

    if(vol <= 0)
    {
        set_vol = 0;
    }
    else
    {
        /*音量值不为零时，补偿后的最小值为1*/
        set_vol = vol + adapt_vol;
        set_vol = D_MAX(set_vol, 1);
        set_vol = (set_vol < 1) ? 1 : D_MIN(set_vol, P_VOLUME_MAX);
    }

    p_stb_player_set_vol (0, set_vol);

    if(g_custom_config.sys_setup.vol_compensate)
    {
        p_conf_set_volume (vol);
    }
    else
    {
#if 0
        if(smart_volume)
        {
            if(get_srv_flag && info.volume != vol)
            {
                d_dbase_update_srv_volume(curr_srv_id, (D_U8)vol);
            }
            else
            {
                p_conf_set_volume (vol);
            }
        }
        else
#endif
        {
            p_conf_set_volume (vol);
        }
    }

    return D_OK;
}

static D_Result
audio_show_voice(void)
{
    D_Visual        *vis;

    vis = d_frame_get_control (&atv_voicebar_window, ID_VOICE_PROGRESS_BAR);
    {
        d_progress_bar_set_val(vis, current_voice);
    }

    sprintf(strnum, "%d", current_voice);
    vis = d_frame_get_control (&atv_voicebar_window, ID_VOICE_LABLE_VAL);
    {
        d_label_set_text(vis, strnum);
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
audio_adjust_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:

            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    return d_gui_close_frame(&atv_voicebar_window);
                    break;
                //case D_KEY_LEFT:
                //case D_KEY_RIGHT:
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                case D_KEY_PNL_L:
                case D_KEY_PNL_R:
                    if (htimer != D_INVALID_HANDLE)
                    {
                        /*重新设置定时器*/
                        d_timer_reset (htimer, menu_show_time);
                    }
                    p_ad_check_fpkey(DAD_STB_VOLUME, evt->fp.key);
                    audio_adj_update(evt->fp.key, evt->fp.repeat);
                    audio_show_voice();
                    break;
                case D_KEY_AUD_TRACK:
                    if (htimer != D_INVALID_HANDLE)
                    {
                        /*重新设置定时器*/
                        d_timer_reset (htimer, menu_show_time);
                    }
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == htimer)
            {
                return d_gui_close_frame(&atv_voicebar_window);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy (htimer);
                htimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}



/** @brief 窗口初始化*/
D_Result
atv_voicebar_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_DBSrvInfo info;
    D_Result ad_check = D_ERR;

    /*清除节目信息条*/
    p_atv_chan_info_window_hide();
    p_atv_tv_chan_info_window_hide();

    vis = d_frame_get_control (frm, ID_VOICE_PROGRESS_BAR);
    {
        d_progress_bar_set_cnt(vis, P_VOLUME_MAX);
    }

    audio_show_voice();
#if 0
    menu_show_time = (D_U32)p_conf_get_info_time();
    if(menu_show_time < D_CONF_MIN_INFO_TIME)
    {
        menu_show_time = D_CONF_MIN_INFO_TIME;
    }
    else if(menu_show_time > D_CONF_MAX_INFO_TIME)
    {
        menu_show_time = D_CONF_MAX_INFO_TIME;
    }
#else
    menu_show_time = D_CONF_MIN_INFO_TIME;
#endif
    menu_show_time = menu_show_time * 1000;
    htimer = d_timer_create (NULL, menu_show_time, d_gui_get_queue ());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ESC_KEY_MASK | D_EVT_OK_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK | \
        D_EVT_AUDIO_KEY_MASK | D_EVT_KEY_MASK , D_INVALID_HANDLE);
        if(htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);
        }
        d_vis_set_handler (vis, audio_adjust_window_handler);
    }

    return D_OK;
}

/** @breif 显示窗口*/
D_Result
p_atv_volume_window_show (D_ID player_id, D_FPKey key) D_FUNCPOSTFIT
{
    D_U8 count;

    curr_player = p_stb_get_player(player_id);
    if(!curr_player)
    {
        return D_ERR;
    }
    if(p_conf_get_vid_input () == D_VID_IUTPUT_DTV || p_conf_get_vid_input () == D_VID_IUTPUT_TV)
    {
        /*原来机顶盒上的智能音量(每个频道单独存储音量)的方式不再使用*/
        //smart_volume = p_conf_get_smart_voice_en();
        curr_srv_id = p_stb_player_get_curr_srv(player_id);
    }
    else
    {
        smart_volume = D_FALSE;
        curr_srv_id = -1;
    }
    audio_adj_update(key, D_FALSE);

    return d_gui_open_frame(&atv_voicebar_window, D_GUI_LAYER_VOLUME);
}


/** @breif 清除音量调节窗口*/
D_Result
p_atv_volume_window_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame(&atv_voicebar_window);
}
