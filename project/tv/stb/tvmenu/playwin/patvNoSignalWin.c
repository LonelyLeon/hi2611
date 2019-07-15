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
#include "atv_no_signal_window.c"

#define FLUSH_WIN 500
#define SHOW_TIME 15 * 60000

static D_HTimer flush_timer = D_INVALID_HANDLE;
static D_HTimer show_timer = D_INVALID_HANDLE;

static D_Coord menu_pos_x = 0;
static D_Coord menu_pos_y = 0;

static D_Coord frame_w = 0;
static D_Coord frame_h = 0;

static D_Bool flag_x = D_TRUE;
static D_Bool flag_y = D_TRUE;

static D_Result
atv_no_signal_falsh_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_no_signal_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_LABEL_NO_SIGNAL);

    if(flag_x)
    {
        menu_pos_x = menu_pos_x + 5;
        if((menu_pos_x + vis->rect.w) > frame_w)
        {
            flag_x = D_FALSE;
        }
    }
    else
    {
        menu_pos_x = menu_pos_x - 5;
        if(menu_pos_x < 0)
        {
            flag_x = D_TRUE;
        }
    }
    if(flag_y)
    {
        menu_pos_y = menu_pos_y + 5;
        if((menu_pos_y + vis->rect.h) > frame_h)
        {
            flag_y = D_FALSE;
        }
    }
    else
    {
        menu_pos_y = menu_pos_y - 5;
        if(menu_pos_y < 0)
        {
            flag_y = D_TRUE;
        }
    }

    d_vis_set_pos(vis, menu_pos_x, menu_pos_y, vis->rect.w, vis->rect.h);

    return D_OK;
}
/** @brief 事件处理*/
static D_Result
atv_no_signal_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
			{
				d_timer_reset(show_timer, SHOW_TIME);
				return D_ERR;
			}
        case D_EVT_TIMER:
            if(evt->timer.htimer == show_timer)
            {
				d_timer_reset(show_timer, SHOW_TIME);
				//添加一分钟后待机的功能
				p_atv_power_off_msg_show();
//                p_atv_no_signal_win_hide();
            }
            else if(evt->timer.htimer == flush_timer)
            {
                atv_no_signal_falsh_show();
                d_timer_reset(flush_timer, FLUSH_WIN);
            }

            break;
        case D_EVT_DESTROY:
			{
				d_vis_unsubscribe_evt (vis);
                if(flush_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(flush_timer);
					flush_timer = D_INVALID_HANDLE;
                }
                if(show_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(show_timer);
					show_timer = D_INVALID_HANDLE;
                }				
			}
			break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
atv_no_signal_window_init(D_Frame *frm)
{
    D_Visual *vis;

    frame_w = frm->ctrl_descrs->w;
    frame_h = frm->ctrl_descrs->palh;


    vis = d_frame_get_control(frm, ID_LABEL_NO_SIGNAL);
    {
        d_vis_get_pos(vis, &menu_pos_x, &menu_pos_y);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        flush_timer = d_timer_create (NULL, FLUSH_WIN, d_gui_get_queue());
        if(flush_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, flush_timer);
        }

        show_timer = d_timer_create (NULL, SHOW_TIME, d_gui_get_queue());
        if(show_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, show_timer);
        }
        d_vis_set_handler (vis, atv_no_signal_window_handler);
    }

    return D_OK;
}

/** @brief 无信号菜单显示*/
D_Result
p_atv_no_signal_win_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&atv_no_signal_window, D_GUI_LAYER_VIDEO_MESSAGE);
}

/** @brief 无信号菜单隐藏*/
D_Result
p_atv_no_signal_win_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&atv_no_signal_window);
}

