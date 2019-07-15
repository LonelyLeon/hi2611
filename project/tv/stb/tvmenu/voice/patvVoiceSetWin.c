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
#include "atv_voice_set_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

typedef enum
{
    P_VOICESET_MENU_VOICE = 0,
    P_VOICESET_MENU_BALANCE = 1,
    P_VOICESET_MENU_OTHERS,
} P_PicSetMenuStatus;

typedef struct
{
    D_Bool enable;
    D_Bool right;
    D_Char strnum[10];
    D_S16    value;
    D_S16    progress_val;
    D_VidInput input;
    D_Visual *vis_progress, *vis_label;
    D_Bool  smart_volume ;
    D_DBSrvID   curr_srv_id ;
    D_Bool  get_srv_flag;

} D_VoiceSetData;

static D_VoiceSetData *voice_set_data = NULL;
static P_PicSetMenuStatus voice_set_menu_status;

static D_U32 atv_voice_get_param(void);
static D_Result atv_voice_set_param(D_U8 val);
static D_Result atv_voice_save_param(D_U8 val);


/** @brief 设置左右箭头按键的可用状态和聚焦状态*/
static D_Result
atv_voice_set_vis_focusable(D_Bool enable, D_Bool focus_right)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_voice_set_window;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control(frm, ID_VOICESET_BUTTON_LEFT_ARROW);
    right_vis = d_frame_get_control(frm, ID_VOICESET_BUTTON_RIGHT_ARROW);

    if(enable != voice_set_data->enable)
    {
        d_vis_set_focusable(left_vis, (enable) ? D_TRUE : D_FALSE);
        d_vis_set_focusable(right_vis, (enable) ? D_TRUE : D_FALSE);
        if(enable)
        {
            d_vis_set_focus(((focus_right) ? right_vis : left_vis));
        }
    }
    else if(voice_set_data->right != focus_right && voice_set_data->enable)
    {
        d_vis_set_focus(((focus_right) ? right_vis : left_vis));
    }

    voice_set_data->enable = enable;
    voice_set_data->right = focus_right;

    return D_OK;
}

/** @brief 进度条事件处理*/
static D_Result
atv_voice_set_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_DRAW:
            p_vis_progress_draw(vis, atv_IMG_ID_COMB_scroll_focus);
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 进度条事件处理*/
static D_Result
atv_voice_set_enable_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch (evt->type)
    {
        case D_EVT_DRAW:
            p_vis_progress_draw(vis, atv_IMG_ID_COMB_scroll_enable);
            break;
        default:
            break;
    }
    return D_OK;
}


/** @brief 事件处理*/
static D_Result
atv_voice_set_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_MENU:
                    d_gui_clear_menu();
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                    //按OK键进入滚动条后,显示黄色滚动条
                    d_vis_enable(voice_set_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(voice_set_data->vis_progress, voice_set_data->progress_val);
                    d_vis_set_solve_draw_evt(voice_set_data->vis_progress, D_TRUE);
                    d_vis_set_handler(voice_set_data->vis_progress, atv_voice_set_progress_handler);
                    d_vis_enable(voice_set_data->vis_progress, D_TRUE);

                    if(! voice_set_data->enable)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        atv_voice_set_vis_focusable(D_TRUE, voice_set_data->right);
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    //按menu键返回后,显示蓝色滚动条
                    d_vis_enable(voice_set_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(voice_set_data->vis_progress, voice_set_data->progress_val);
                    d_vis_set_solve_draw_evt(voice_set_data->vis_progress, D_TRUE);
                    d_vis_set_handler(voice_set_data->vis_progress, atv_voice_set_enable_progress_handler);
                    d_vis_enable(voice_set_data->vis_progress, D_TRUE);

                    if(voice_set_data->enable)
                    {
                        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        atv_voice_set_vis_focusable(D_FALSE, voice_set_data->right);
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                        return d_gui_clear_menu();
                    }
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(voice_set_data->enable)
                    {
                        atv_voice_set_vis_focusable(D_TRUE, D_FALSE);
                        voice_set_data->progress_val--;
                        if(voice_set_data->progress_val < 0)
                        {
                            voice_set_data->progress_val = 0;
                        }
                        else
                        {
                            d_progress_bar_set_val(voice_set_data->vis_progress, voice_set_data->progress_val);
                            sprintf(voice_set_data->strnum, "%d", voice_set_data->progress_val);
                            d_label_set_text(voice_set_data->vis_label, voice_set_data->strnum);
                            atv_voice_set_param(voice_set_data->progress_val);
                        }
                    }
                    break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(voice_set_data->enable)
                    {
                        atv_voice_set_vis_focusable(D_TRUE, D_TRUE);
                        voice_set_data->progress_val++;
                        if(voice_set_data->progress_val > 100)
                        {
                            voice_set_data->progress_val = 100;
                        }
                        else
                        {
                            d_progress_bar_set_val(voice_set_data->vis_progress, voice_set_data->progress_val);
                            sprintf(voice_set_data->strnum, "%d", voice_set_data->progress_val);
                            d_label_set_text(voice_set_data->vis_label, voice_set_data->strnum);
                            atv_voice_set_param(voice_set_data->progress_val);
                        }

                        /*音量加时，取消静音状态*/
                        if((voice_set_menu_status == P_VOICESET_MENU_VOICE) && p_conf_get_aud_mute())
                        {
                            p_atv_mute_window_clear();
                            d_tv_set_aud_mute (g_stb->player->htv, D_FALSE);
                            p_conf_set_aud_mute (D_FALSE);
                        }
                    }
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(voice_set_data->enable)
                    {
                        return D_OK;
                    }
                    else
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
            if(voice_set_data)
            {
                if(voice_set_data->progress_val != voice_set_data->value)
                {
                    voice_set_data->value = voice_set_data->progress_val;
                    atv_voice_save_param(voice_set_data->value);
                }
                PROJECT_FREE(voice_set_data);
                voice_set_data = NULL;
            }
        }
        break;

        default:
            break;
    }
}


/** @brief 对比度窗口初始化*/
D_Result
atv_voice_set_window_init(D_Frame *frm)
{
    D_Visual *vis;

    voice_set_data = (D_VoiceSetData*)PROJECT_ALLOC(sizeof(D_VoiceSetData));
    if(!voice_set_data)
    {
        return D_ERR;
    }
    memset(voice_set_data, 0x00, sizeof(D_VoiceSetData));

    voice_set_data->input = p_conf_get_vid_input();
    if(voice_set_data->input == D_VID_IUTPUT_DTV)
    {
        /*原来机顶盒上的智能音量(每个频道单独存储音量)的方式不再使用*/
        //voice_set_data->smart_volume = p_conf_get_smart_voice_en();
        voice_set_data->curr_srv_id = p_stb_player_get_curr_srv(0);
    }
    else
    {
        voice_set_data->smart_volume = D_FALSE;
        voice_set_data->curr_srv_id = -1;
    }
    voice_set_data->get_srv_flag = D_FALSE;
    voice_set_data->value = atv_voice_get_param();
    voice_set_data->progress_val = D_MIN(voice_set_data->value, 100);


    vis = d_frame_get_control (frm, ID_VOICESET_PROGRESS_PUBLIC);
    if(vis)
    {
        voice_set_data->vis_progress = vis;
        d_progress_bar_set_val(vis, voice_set_data->progress_val);
        d_vis_set_solve_draw_evt(vis, D_TRUE);
        d_vis_set_handler(vis, atv_voice_set_enable_progress_handler);
    }

    vis = d_frame_get_control(frm, ID_VOICESET_LABLE_VAL);
    if(vis)
    {
        sprintf(voice_set_data->strnum, "%d", voice_set_data->progress_val);
        voice_set_data->vis_label = vis;
        d_label_set_text(vis, voice_set_data->strnum);
    }

    vis = d_frame_get_control(frm, ID_VOICESET_GROUP_BACKGROUND);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_voice_set_window_handler);
    }

    voice_set_data->enable = D_TRUE;
    atv_voice_set_vis_focusable(D_FALSE, D_FALSE);

    return D_OK;
}

/*取得菜单显示的进度值*/
static D_U32 atv_voice_get_param(void)D_FUNCPOSTFIT
{
    D_U32 val = 0;

    if(voice_set_menu_status == P_VOICESET_MENU_VOICE)
    {
        D_DBSrvInfo info = {0};
        D_S8        vol = 0;
        D_S8    set_vol;
        D_S8    adapt_vol = 0;


        /*是否使用音量补偿功能*/
        if(g_custom_config.sys_setup.vol_compensate)
        {
            vol = (D_S8)p_conf_get_volume ();

            if ((voice_set_data->curr_srv_id != -1) && (d_dbase_get_srv_info (voice_set_data->curr_srv_id, &info) >= 0))
            {
                voice_set_data->get_srv_flag = D_TRUE;
                adapt_vol = info.volume;
                /*防止补偿音量过小或过大*/
                adapt_vol = (adapt_vol < 0) ? D_MAX(adapt_vol, (0 - P_VOLUME_MAX)) : D_MIN(adapt_vol, P_VOLUME_MAX);
            }
        }
        else
        {
#if 0
            if(voice_set_data->smart_volume)
            {
                if ((voice_set_data->curr_srv_id != -1) && (d_dbase_get_srv_info (voice_set_data->curr_srv_id, &info) >= 0))
                {
                    voice_set_data->get_srv_flag = D_TRUE;
                    vol = info.volume;
                    adapt_vol = 0;
                }
                else
                {
                    voice_set_data->get_srv_flag = D_FALSE;
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
        vol = D_MIN(vol, P_VOLUME_MAX);
        vol = D_MAX(0, vol);
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
        val =  set_vol;
    }
    else if(voice_set_menu_status == P_VOICESET_MENU_BALANCE)
    {
        val =  p_conf_get_balance ();
    }

    return val;
}

/*设置参数到驱动*/
static D_Result atv_voice_set_param(D_U8 val)D_FUNCPOSTFIT
{
    if(voice_set_menu_status == P_VOICESET_MENU_VOICE)
    {
        p_stb_player_set_vol (0, val);
    }
    else if(voice_set_menu_status == P_VOICESET_MENU_BALANCE)
    {
        D_StbPlayer *player;

        if (! (player = p_stb_get_player (0)))
        {
            return D_ERR;
        }
        d_tv_set_balance (player->htv, (D_U8)val);
    }
    return D_OK;
}

/*保存设置参数*/
static D_Result atv_voice_save_param(D_U8 val)D_FUNCPOSTFIT
{
    if(voice_set_menu_status == P_VOICESET_MENU_VOICE)
    {
        D_DBSrvInfo info = {0};

        if(g_custom_config.sys_setup.vol_compensate)
        {
            p_conf_set_volume (val);
        }
        else
        {
#if 0
            if(voice_set_data->smart_volume)
            {
                if(voice_set_data->get_srv_flag && info.volume != val)
                {
                    d_dbase_update_srv_volume(voice_set_data->curr_srv_id, (D_U8)val);
                }
                else
                {
                    p_conf_set_volume (val);
                }
            }
            else
#endif
            {
                p_conf_set_volume (val);
            }
        }
    }
    else if(voice_set_menu_status == P_VOICESET_MENU_BALANCE)
    {
        p_conf_set_balance (val);
    }

    return D_OK;
}


/** @brief 显示音量条菜单*/
D_Result
p_atv_voice_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&atv_voice_set_window))
    {
        voice_set_menu_status = P_VOICESET_MENU_VOICE;
        d_gui_enter_menu (&atv_voice_set_window, D_FALSE);
    }
    return D_OK;
}

/** @brief 显示平衡条菜单*/
D_Result
p_atv_balance_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&atv_voice_set_window))
    {
        voice_set_menu_status = P_VOICESET_MENU_BALANCE;
        d_gui_enter_menu (&atv_voice_set_window, D_FALSE);
    }
    return D_OK;
}



