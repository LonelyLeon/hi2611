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
#include "atv_smart_sound_window.c"

#define SMART_ROUND_BUTTON_NUM 1

typedef struct
{
    D_Bool   smart_round_flag, first_flag;
    D_Visual *vis_on, *vis_off;
} D_SmartRoundData;

static D_SmartRoundData *smart_round_data = NULL;
static D_DBSrvID  curr_srv_id = -1;

/*取得参数*/
static D_Bool atv_smart_round_get_param()D_FUNCPOSTFIT
{
    /*取得参数*/
    return p_conf_get_smart_voice_en();
}

/*保存参数*/
static D_Result atv_smart_round_save_param(D_Bool flag)D_FUNCPOSTFIT
{
    /*保存参数*/
    p_conf_set_smart_voice_en(flag);
    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_smart_round_set_param(D_Bool flag)D_FUNCPOSTFIT
{
#if 0
    D_DBSrvInfo info = {0};
    D_S8        vol = 0;
    D_S8    set_vol;
    D_S8    adapt_vol = 0;
    D_Bool  get_srv_flag = D_FALSE;


    curr_srv_id = p_stb_player_get_curr_srv(0);

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
        if(flag)
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

    p_stb_player_set_vol (0, set_vol);
#else
    d_av_avc_ctl(0, ((flag == D_FALSE) ? 0 : 1));
#endif
    return D_OK;
}


/** @brief 开按钮事件处理*/
static D_Result
button_smart_on_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if((!smart_round_data->first_flag)  && smart_round_data->smart_round_flag)
            {
                atv_smart_round_set_param(D_TRUE);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 关按钮事件处理*/
static D_Result
button_smart_off_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if((!smart_round_data->first_flag)  && (!smart_round_data->smart_round_flag))
            {
                atv_smart_round_set_param(D_FALSE);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 设置按钮是否可用和是否可聚焦*/
static D_Result
set_button_enable (D_Bool flag) D_FUNCPOSTFIT
{
    d_vis_enable(smart_round_data->vis_on, flag);
    d_vis_enable(smart_round_data->vis_off, flag);
    d_vis_set_focusable(smart_round_data->vis_on, flag);
    d_vis_set_focusable(smart_round_data->vis_off, flag);
    if(!flag)
    {
        if(smart_round_data->smart_round_flag  != D_TRUE)d_vis_enable(smart_round_data->vis_on, D_TRUE);
        if(smart_round_data->smart_round_flag  != D_FALSE)d_vis_enable(smart_round_data->vis_off, D_TRUE);
    }
    return D_OK;
}

/** @brief 设置按钮的焦点*/
static D_Result
set_vis_focus (D_Bool flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_vis_set_focus(smart_round_data->vis_off);
            break;
        case 1:
            d_vis_set_focus(smart_round_data->vis_on);
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_smart_sound_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_smart_round_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    if(smart_round_data->first_flag == D_TRUE)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        set_button_enable(D_TRUE);

                        set_vis_focus(smart_round_data->smart_round_flag);
                        smart_round_data->first_flag = D_FALSE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(smart_round_data->first_flag == D_FALSE)
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        set_button_enable(D_FALSE);
                        atv_smart_round_save_param(!smart_round_data->smart_round_flag);
                        smart_round_data->first_flag = D_TRUE;
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                    		d_gui_upper_menu();		//for exit Key 20190628
                        return d_gui_upper_menu();
                    }
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    if(smart_round_data->smart_round_flag)
                    {
                        smart_round_data->smart_round_flag = D_FALSE;
                    }
                    else
                    {
                        smart_round_data->smart_round_flag = D_TRUE;
                    }
                    set_vis_focus(smart_round_data->smart_round_flag);
                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if(smart_round_data->smart_round_flag)
                    {
                        smart_round_data->smart_round_flag = D_FALSE;
                    }
                    else
                    {
                        smart_round_data->smart_round_flag = D_TRUE;
                    }
                    set_vis_focus(smart_round_data->smart_round_flag);
                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(smart_round_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(smart_round_data->first_flag == D_TRUE)
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
            atv_smart_round_save_param(smart_round_data->smart_round_flag);
            if(smart_round_data)
            {
                //保存参数
                PROJECT_FREE(smart_round_data);
                smart_round_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_smart_round_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    smart_round_data = (D_SmartRoundData*)PROJECT_ALLOC(sizeof(D_SmartRoundData));
    if(!smart_round_data)
    {
        return D_ERR;
    }
    memset(smart_round_data, 0x00, sizeof(D_SmartRoundData));

    smart_round_data->smart_round_flag = atv_smart_round_get_param();
    smart_round_data->vis_on = d_frame_get_control(frm, ID_SMART_BUTTON_ON); //开
    smart_round_data->vis_off = d_frame_get_control(frm, ID_SMART_BUTTON_OFF);//关

    d_vis_set_handler (smart_round_data->vis_on, button_smart_on_handler);
    d_vis_set_handler (smart_round_data->vis_off, button_smart_off_handler);

    smart_round_data->first_flag = D_TRUE;
    set_vis_focus(smart_round_data->smart_round_flag);

    vis = d_frame_get_control(frm, ID_SMART_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        set_button_enable(D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_smart_sound_window_handler);
    }

    return D_OK;
}

/** @brief 显示智能音量菜单*/
D_Result
p_atv_smart_sound_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_smart_round_window, D_FALSE);
}

