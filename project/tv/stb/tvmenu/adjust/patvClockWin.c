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
#include "atv_clock_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;


typedef struct
{
    D_Char strnum[10];
    D_S16    progress_val;
		D_U32 	 menu_show_time;
} D_AdjustClockData;

static D_AdjustClockData *clock_data = NULL;

/*取得菜单显示的进度值*/
static D_U8 atv_clock_get_param(void)D_FUNCPOSTFIT
{
    return 35;
}
/*设置参数到驱动*/
static D_Result atv_clock_set_param(D_U8 val)D_FUNCPOSTFIT
{
    return D_OK;
}
/*保存设置参数*/
static D_Result atv_clock_save_param(D_U8 val)D_FUNCPOSTFIT
{
    return D_OK;
}

static D_Result
set_vis_focusable(D_Bool flag)
{
    D_Frame *frm = &atv_clock_window;
    D_Visual *left_vis, *right_vis;

    left_vis = d_frame_get_control(frm, ID_PROGRESS_BUTTON_LEFT_ARROW);
    right_vis = d_frame_get_control(frm, ID_PROGRESS_BUTTON_RIGHT_ARROW);

    if(flag)
    {
        d_vis_enable(left_vis, flag);
        d_vis_enable(right_vis, flag);
        d_vis_set_focusable(left_vis, flag);
        d_vis_set_focusable(right_vis, flag);

    }
    else
    {
        d_vis_enable(left_vis, flag);
        d_vis_enable(right_vis, flag);
        d_vis_set_focusable(left_vis, flag);
        d_vis_set_focusable(right_vis, flag);
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_clock_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
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

/** @brief 更新显示*/
static D_Result
clock_progress_update (D_FPKey key, D_Bool repeat) D_FUNCPOSTFIT
{
	D_Frame *frm = &atv_clock_window;
    D_Visual * pvis, *lvis;
	D_S8 step = 0;
    pvis = d_frame_get_control (frm, ID_PROGRESS_PROGRESS_PUBLIC);
	
	if(repeat)
	{
		step = D_MIN((step+1), 5);
	}
	else
	{
		step = 0;
	}

	switch (key)
    {
        case D_KEY_LEFT:
        case D_KEY_PNL_L:
            clock_data->progress_val = (clock_data->progress_val - 1 - step);
			if(clock_data->progress_val < 0)
		    {
		        clock_data->progress_val = 0;
		    }
            break;
        case D_KEY_RIGHT:
        case D_KEY_PNL_R:
            clock_data->progress_val = (clock_data->progress_val + 1 + step);
			if(clock_data->progress_val > 100)
            {
                clock_data->progress_val = 100;
            }
			
            break;
        default:
            break;
    }

    d_progress_bar_set_val(pvis, clock_data->progress_val);
	
    sprintf(clock_data->strnum, "%d", clock_data->progress_val);
    lvis = d_frame_get_control (frm, ID_PROGRESS_LABLE_VAL);
    {
        d_label_set_text(lvis, clock_data->strnum);
    }

	atv_clock_set_param(clock_data->progress_val);

	
}

/** @brief 事件处理*/
static D_Result
atv_clock_progress_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_clock_window;
    D_Visual * pvis, *lvis;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control(frm, ID_PROGRESS_BUTTON_LEFT_ARROW);
    right_vis = d_frame_get_control(frm, ID_PROGRESS_BUTTON_RIGHT_ARROW);

    pvis = d_frame_get_control (frm, ID_PROGRESS_PROGRESS_PUBLIC);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                {
                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    set_vis_focusable(D_TRUE);
                    d_vis_set_focus(left_vis);
                }
                break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
                {
                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    set_vis_focusable(D_FALSE);
                }
                break;
                case D_KEY_ESC:
                case D_KEY_MENU:    
                    return d_gui_clear_menu();
                 case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                	clock_progress_update(evt->fp.key, evt->fp.repeat);
                	break;
                default:
                    break;
            }
        }
        return D_OK;
        break;

        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
			atv_clock_save_param(clock_data->progress_val);
            if(clock_data)
            {
                PROJECT_FREE(clock_data);
                clock_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_clock_window_init(D_Frame *frm)
{
    D_Visual *vis;

    clock_data = (D_AdjustClockData*)PROJECT_ALLOC(sizeof(D_AdjustClockData));
    if(!clock_data)
    {
        return D_ERR;
    }
    memset(clock_data, 0x00, sizeof(D_AdjustClockData));
    clock_data->progress_val = atv_clock_get_param();

    vis = d_frame_get_control (frm, ID_PROGRESS_PROGRESS_PUBLIC);
    if(vis)
    {
        d_progress_bar_set_val(vis, clock_data->progress_val);
        d_vis_set_solve_draw_evt(vis, D_TRUE);
        d_vis_set_handler(vis, atv_clock_progress_handler);
    }

    sprintf(clock_data->strnum, "%d", clock_data->progress_val);
    vis = d_frame_get_control (frm, ID_PROGRESS_LABLE_VAL);
    if(vis)
    {
        d_label_set_text(vis, clock_data->strnum);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK) & (~ D_EVT_UP_DOWN_KEY_MASK) & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_clock_progress_window_handler);
    }

    set_vis_focusable(D_FALSE);

    return D_OK;
}

/** @brief 时钟菜单*/
D_Result
p_atv_clock_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_clock_window, D_FALSE);
}

