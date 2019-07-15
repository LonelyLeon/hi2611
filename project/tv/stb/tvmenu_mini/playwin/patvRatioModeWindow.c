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
#include "pFp.h"
#include "atv_ratio_mode_window.c"


typedef struct
{
    D_VidInput input;
    D_U8   ratio_mode;
    D_Bool ntsc_flag;
    D_U8 ratio_mode_flag;
    D_HTimer timer;
    D_U32    menu_show_time;
} D_RatioModeData;

static D_Char* mode_str[4] =  {"full screen", "4:3", "zoom", "panorama"};
static D_RatioModeData *ratio_mode_data = NULL;

/** @brief 复位显示定时器*/
static D_Result
ratio_mode_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(ratio_mode_data && ratio_mode_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(ratio_mode_data->timer, ratio_mode_data->menu_show_time);
    }

    return D_OK;
}

static D_Result
change_ratio_mode(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &ratio_mode_window;
    D_Visual *vis;
    D_tv_Display_Ratio_t ratio_mode;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis, mode_str[ratio_mode_data->ratio_mode]);
        d_gui_update();
    }
    if(ratio_mode_data->ratio_mode == 0)
    {
        ratio_mode = D_Full_Screen;
    }
    else if(ratio_mode_data->ratio_mode == 1)
    {
        ratio_mode = D_4_to_3;
    }
    else if(ratio_mode_data->ratio_mode == 2)
    {
        ratio_mode = D_ZOOM_1X;
    }
    else if(ratio_mode_data->ratio_mode == 3)
    {
        ratio_mode = D_Overall_Screen;
    }

    d_av_set_tv_ratio_mode(0, ratio_mode);
    p_tvconf_set_cur_zoommode(&ratio_mode_data->ratio_mode, p_vip_get_dbinput(ratio_mode_data->input));
    return D_OK;
}
/** @brief 事件处理*/
static D_Result
ratio_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *label_vis;
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            case D_KEY_ZOOM:
                ratio_mode_reset_show_timer();
                ratio_mode_data->ratio_mode_flag = (ratio_mode_data->ratio_mode + 1) % 4;
                ratio_mode_data->ratio_mode = ratio_mode_data->ratio_mode_flag;
                change_ratio_mode();
                break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == ratio_mode_data->timer)
            {
                p_ratio_mode_win_hide();
            }
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(ratio_mode_data)
            {
                if(ratio_mode_data->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(ratio_mode_data->timer);
                }
                PROJECT_FREE(ratio_mode_data);
                ratio_mode_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
ratio_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;

    ratio_mode_data = (D_RatioModeData*)PROJECT_ALLOC(sizeof(D_RatioModeData));
    if(!ratio_mode_data)
    {
        return D_ERR;
    }
    memset(ratio_mode_data, 0, sizeof(D_RatioModeData));
    ratio_mode_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_zoommode(&ratio_mode_data->ratio_mode, p_vip_get_dbinput(ratio_mode_data->input));
    ratio_mode_data->ratio_mode_flag = ratio_mode_data->ratio_mode;
    ratio_mode_data->ntsc_flag = p_vip_get_ntscflag();

    ratio_mode_data->menu_show_time = 3 * 1000;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis, mode_str[ratio_mode_data->ratio_mode]);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        ratio_mode_data->timer = d_timer_create (NULL, ratio_mode_data->menu_show_time, d_gui_get_queue ());
        if(ratio_mode_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, ratio_mode_data->timer);
        }

        d_vis_set_handler (vis, ratio_mode_window_handler);
        d_vis_subscribe_evt (vis, D_EVT_KEY_MASK, D_INVALID_HANDLE);
    }

    return D_OK;
}

/** @brief 菜单显示*/
D_Result
p_ratio_mode_win_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&ratio_mode_window, D_GUI_LAYER_VIDEO_MESSAGE);
}

/** @brief 菜单隐藏*/
D_Result
p_ratio_mode_win_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&ratio_mode_window);
}

