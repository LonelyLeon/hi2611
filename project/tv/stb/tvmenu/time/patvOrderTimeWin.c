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
#include "atv_order_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

typedef struct
{
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char  minute[10];
    D_DBID          ids[256];
	D_Bool first_flag;
} D_OrderTimeData;

static D_OrderTimeData *ordertime_data = NULL;
static D_Result get_cur_time(D_U8 *hour, D_U8 *minute);
static D_Bool get_cur_switch_state(void);

static void update_time(void)D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Frame *frm = &atv_order_window;
    D_U8     hour;
    D_U8     minute;
		
    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWDIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWHOUR);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(ordertime_data->hour, "%02d", (D_U32)hour);
            d_label_set_text(vis, ordertime_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(ordertime_data->minute, "%02d", (D_U32)minute);
            d_label_set_text(vis, ordertime_data->minute);
        }
    }

    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SWITCH); //开关
    if(vis)
    {
        if(get_cur_switch_state())
            d_label_set_text (vis, "On");
        else
            d_label_set_text (vis, "Off");
    }
    d_vis_update(NULL, NULL);

    return ;
}

/** @brief 事件处理*/
static D_Result
order_time_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_pop_order_time_show(update_time);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_order_time_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_order_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_ORDER_BUTTON_SET);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
					if(ordertime_data->first_flag == D_TRUE)
					{

	                    d_vis_enable(vis_button, D_TRUE);
	                    d_vis_set_focusable(vis_button, D_TRUE);
	                    d_vis_set_focus(vis_button);
						ordertime_data->first_flag = D_FALSE;
					}
                    break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(ordertime_data->first_flag == D_FALSE)
	                {
						d_vis_enable(vis_button, D_FALSE);
                    	d_vis_set_focusable(vis_button, D_FALSE);
						ordertime_data->first_flag = D_TRUE;
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
					if(ordertime_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(ordertime_data->first_flag == D_TRUE)
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
            if(ordertime_data)
            {
                PROJECT_FREE(ordertime_data);
                ordertime_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

static D_Result get_cur_time(D_U8 *hour, D_U8 *minute)
{
    return get_OrderTime_time(hour,minute);
}

static D_Bool get_cur_switch_state(void)
{
    D_U8 en = get_OrderTime_enable();
    return ((en) ? D_TRUE : D_FALSE);
}	


D_Result
atv_order_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8     hour;
    D_U8     minute;

    ordertime_data = (D_OrderTimeData*)PROJECT_ALLOC(sizeof(D_OrderTimeData));
    if(!ordertime_data)
    {
        return D_ERR;
    }
    memset(ordertime_data, 0x00, sizeof(D_OrderTimeData));
	ordertime_data->first_flag = D_TRUE;
    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWDIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }
		
    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SWITCH); //开关
    if(vis)
    {
        if(get_cur_switch_state())
            d_label_set_text (vis, "On");
        else
            d_label_set_text (vis, "Off");
    }
    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWHOUR);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(ordertime_data->hour, "%02d", (D_U32)hour);
            d_label_set_text(vis, ordertime_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_ORDER_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(ordertime_data->minute, "%02d", (D_U32)minute);
            d_label_set_text(vis, ordertime_data->minute);
        }
    }

    vis = d_frame_get_control(frm, ID_ORDER_BUTTON_SET);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_vis_set_handler (vis, order_time_button_handler);
    }

	vis = d_frame_get_control (frm, ID_ORDER_GROUP_BG);
	if(vis)
	{	
		d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
	}

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_order_time_window_handler);
    }
    return D_OK;
}

/** @brief 显示预约时间菜单*/
D_Result
p_atv_order_time_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_order_window, D_FALSE);
}

