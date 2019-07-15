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
#include "atv_bglight_progress_window.c"


typedef struct
{
    D_Char strnum[10];
    D_S16    progress_val;
    D_VidInput input;
    D_BLDIM_SET param;
    D_U8 backlight;
    D_Bool enable;
    D_Visual * vis_progress, *vis_label;
} D_BgLightData;

static D_BgLightData *bglight_data = NULL;

/*取得菜单显示的进度值*/
static D_U8 atv_bg_light_get_param(void)D_FUNCPOSTFIT
{
    p_tvconf_get_bldim_backlight(&(bglight_data->backlight), p_vip_get_dbinput(bglight_data->input));

    return bglight_data->backlight;
}
/*设置参数到驱动*/
static D_Result atv_bg_light_set_param(D_U8 val)D_FUNCPOSTFIT
{
    p_tvconf_get_bldim_set_param(&(bglight_data->param), p_vip_get_dbinput(bglight_data->input));
    d_vip_setBldim(&(bglight_data->param), val);
    return D_OK;
}
/*保存设置参数*/
static D_Result atv_bg_light_save_param(D_U8 val)D_FUNCPOSTFIT
{
    bglight_data->backlight = val;
    p_tvconf_set_bldim_backlight(&(bglight_data->backlight), p_vip_get_dbinput(bglight_data->input));
    return D_OK;
}



/** @brief 事件处理*/
static D_Result
atv_bglight_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_DRAW:
            p_vis_progress_draw(vis, bglight_data->enable);
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 更新显示*/
static D_Result
bglight_progress_update (D_FPKey key, D_Bool repeat) D_FUNCPOSTFIT
{
    D_S8 step = 0;

    if(repeat)
    {
        step = D_MIN((step + 1), 5);
    }
    else
    {
        step = 0;
    }

    switch (key)
    {
        case D_KEY_LEFT:
        case D_KEY_PNL_L:
            bglight_data->progress_val = (bglight_data->progress_val - 1 - step);
            if(bglight_data->progress_val < 0)
            {
                bglight_data->progress_val = 0;
            }
            break;
        case D_KEY_RIGHT:
        case D_KEY_PNL_R:
            bglight_data->progress_val = (bglight_data->progress_val + 1 + step);
            if(bglight_data->progress_val > 100)
            {
                bglight_data->progress_val = 100;
            }

            break;
        default:
            break;
    }

    d_progress_bar_set_val(bglight_data->vis_progress, bglight_data->progress_val);
    sprintf(bglight_data->strnum, "%d", bglight_data->progress_val);
    d_label_set_text(bglight_data->vis_label, bglight_data->strnum);
    atv_bg_light_set_param(bglight_data->progress_val);
}

/** @brief 事件处理*/
static D_Result
atv_bglight_progress_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    //按OK键进入滚动条后,显示黄色滚动条
                    d_vis_enable(bglight_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(bglight_data->vis_progress, bglight_data->progress_val);
                    d_vis_enable(bglight_data->vis_progress, D_TRUE);

                    if(!bglight_data->enable)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        bglight_data->enable = D_TRUE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    //按menu键返回后,显示蓝色滚动条
                    d_vis_enable(bglight_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(bglight_data->vis_progress, bglight_data->progress_val);
                    d_vis_enable(bglight_data->vis_progress, D_TRUE);

                    if(bglight_data->enable )
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        bglight_data->enable = D_FALSE;
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                    		d_gui_upper_menu();		//for exit Key Yin 20190628
                        return d_gui_upper_menu();
                    }
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(bglight_data->enable)
                    {
                        bglight_progress_update(evt->fp.key, evt->fp.repeat);
                    }
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(bglight_data->enable)
                    {
                        bglight_progress_update(evt->fp.key, evt->fp.repeat);
                    }
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(bglight_data->enable)
                    {
                        return D_OK;
                    }
                    else if(bglight_data->enable)
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
            if(bglight_data)
            {
                atv_bg_light_save_param(bglight_data->progress_val);
                PROJECT_FREE(bglight_data);
                bglight_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_bglight_progress_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    bglight_data = (D_BgLightData*)PROJECT_ALLOC(sizeof(D_BgLightData));
    if(!bglight_data)
    {
        return D_ERR;
    }
    memset(bglight_data, 0x00, sizeof(D_BgLightData));

    bglight_data->input = p_conf_get_vid_input();
    bglight_data->progress_val = D_MIN(atv_bg_light_get_param(),100);
    bglight_data->enable = D_FALSE;

    vis = d_frame_get_control (frm, ID_PROGRESS_PROGRESS_PUBLIC);
    if(vis)
    {
        bglight_data->vis_progress = vis;
        d_progress_bar_set_val(bglight_data->vis_progress, bglight_data->progress_val);
        d_vis_set_solve_draw_evt(bglight_data->vis_progress, D_TRUE);
        d_vis_set_handler(bglight_data->vis_progress, atv_bglight_progress_handler);
    }

    vis = d_frame_get_control (frm, ID_PROGRESS_LABLE_VAL);
    if(vis)
    {
        bglight_data->vis_label = vis;
        sprintf(bglight_data->strnum, "%d", bglight_data->progress_val);
        d_label_set_text(vis, bglight_data->strnum);
    }

    vis = d_frame_get_control(frm, ID_PROGRESS_GROUP_BACKGROUND);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK) & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_bglight_progress_window_handler);

    }
    return D_OK;
}

/** @brief 显示背光调整菜单*/
D_Result
p_atv_bglight_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_bglight_progress_window, D_FALSE);
}

