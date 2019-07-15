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
#include "av_signal_select_window.c"

typedef struct
{
    D_HTimer    timer;
    D_U32    menu_show_time;
	D_U8	selet_val;
} D_AvSignalSelect;

static D_AvSignalSelect *av_signal_info;

/** @brief 复位显示定时器*/
static D_Result
reset_show_timer(void) D_FUNCPOSTFIT
{
    if(av_signal_info && av_signal_info->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(av_signal_info->timer, av_signal_info->menu_show_time);
    }

    return D_OK;
}

static D_Result
tv_signal_select_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
			reset_show_timer();
			
            av_signal_info->selet_val = d_select_box_get_val(vis);
			p_conf_set_scan_config(av_signal_info->selet_val);
            break;
        default:
            break;
    }


    return D_ERR;
}



/** @brief 事件处理*/
static D_Result
tv_signal_select_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            reset_show_timer();

            switch (evt->fp.key)
            {
                case D_KEY_MENU:
				case D_KEY_OK:
				case D_KEY_ESC:
                case D_KEY_BACK:
                {
                    return d_gui_upper_menu();
                }
                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == av_signal_info->timer)
            {
                return d_gui_clear_menu();
            }
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(av_signal_info)
            {
                if(av_signal_info->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(av_signal_info->timer);
					av_signal_info->timer == D_INVALID_HANDLE;
                }
                PROJECT_FREE(av_signal_info);
                av_signal_info = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
av_signal_select_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8 val;
	D_U32 time;

    av_signal_info = (D_AvSignalSelect*)PROJECT_ALLOC(sizeof(D_AvSignalSelect));
    if(!av_signal_info)
    {
        return D_ERR;
    }
    memset(av_signal_info, 0x00, sizeof(D_AvSignalSelect));
	
   	time = (D_U32)p_conf_get_info_time();
	if(time < D_CONF_MIN_INFO_TIME)
	{
		time = D_CONF_MIN_INFO_TIME;
	}
	else if(time > D_CONF_MAX_INFO_TIME)
	{
		time = D_CONF_MAX_INFO_TIME;
	}
	av_signal_info->menu_show_time = time * 1000;

	av_signal_info->selet_val = p_conf_get_scan_config();
	
    vis = d_frame_get_control (frm, ID_PICTURE_OPTIMIZE_SELECT_SPEED);
    if(vis)
    {
        d_vis_set_handler (vis, tv_signal_select_handler);
        d_select_box_set_val(vis, av_signal_info->selet_val);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, tv_signal_select_window_handler);

        av_signal_info->timer = d_timer_create (NULL, av_signal_info->menu_show_time, d_gui_get_queue ());
        if(av_signal_info->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, av_signal_info->timer);
        }
    }

    return D_OK;
}

/** @brief 显示图像优化菜单*/
D_Result
p_av_signal_select_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&av_signal_select_window, D_FALSE);
}

