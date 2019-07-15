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
#include "atv_pop_ordertime_window.c"


typedef struct
{
    D_Visual *vis_minute;
    D_Visual    *vis_hour;
    D_Visual    *vis_off;
    D_Visual    *vis_on;
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char      minute[10];
    D_S32       ihour;
    D_S32       iminute;
    D_U8                enable;
    D_DBID  ids[256];
} OrderTimeStruct;

typedef void (*OrderTimeCallback)(void);
static OrderTimeCallback CallbackpFunc = NULL;

static OrderTimeStruct *order_time_info;
static D_U8 order_time_enable = 0;
static D_S16 order_time_chan = -1;
static D_U8 order_time_hour = 0;
static D_U8 order_time_minute = 0;

D_S16 get_OrderTime_chan(void)
{
   return order_time_chan;
}
D_U8 get_OrderTime_enable(void)
{
   return order_time_enable;
}

D_Result get_OrderTime_time(D_U8 *hour, D_U8 *minute)
{
    *hour = order_time_hour;
    *minute = order_time_minute;
    if(order_time_enable)
        return D_OK;
    else
        return D_ERR;

}
D_Result set_OrderTime_chan(D_S16 chan)
{
    order_time_chan = chan;

    return D_OK;
}

D_S16 check_OrderTime_chan(D_U8 hour, D_U8 minute)
{
		if((order_time_enable)&&(order_time_chan != -1)&&(minute == order_time_minute)\
			&&(hour == order_time_hour))
		{
			return order_time_chan;
		}

    return -1;
}

D_Result set_Order_time(D_U8 enable, D_U8 hour, D_U8 minute)
{
    order_time_enable = enable;
    order_time_hour  = hour;
    order_time_minute  = minute;

    return D_OK;
}

static D_Result
set_order_time_minute_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_order_time_window;
    static D_U16 cusor_old = 0;
    D_S32   min_check;

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1 )
            {
                order_time_info->iminute = d_input_box_get_num(vis);
                if(order_time_info->iminute > 59)
                    order_time_info->iminute = 0;
                sprintf(order_time_info->minute, "%02d", (D_U32)order_time_info->iminute);
                d_input_box_set_text(order_time_info->vis_minute, order_time_info->minute, 2);
            }
        }
        break;

        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    if(cusor_old == 0 && vis->element.input.val1 == 0)
                    {
                        d_vis_set_focus(order_time_info->vis_hour);
                    }
                }
                break;
            }
        }

        break;
        default:
            break;
    }
    cusor_old = vis->element.input.val1;
    return D_OK;
}

static D_Result
set_order_time_hour_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_order_time_window;
    D_S32   hour_check;

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1)
            {
                order_time_info->ihour = d_input_box_get_num(vis);
                if(order_time_info->ihour > 23)
                    order_time_info->ihour = 0;
                sprintf(order_time_info->hour, "%02d", (D_U32)order_time_info->ihour);
                d_input_box_set_text(order_time_info->vis_hour, order_time_info->hour, 2);
            }
            else if(vis->element.input.val1 == 2)
            {
                d_vis_set_focus(order_time_info->vis_minute);
                order_time_info->ihour = d_input_box_get_num(vis);
                if(order_time_info->ihour > 23)
                    order_time_info->ihour = 0;
                sprintf(order_time_info->hour, "%02d", (D_U32)order_time_info->ihour);
                d_input_box_set_text(order_time_info->vis_hour, order_time_info->hour, 2);
            }
        }
        break;
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if( vis->element.input.val1 == 2)
                    {
                        d_vis_set_focus(order_time_info->vis_minute);
                    }
                }
                break;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    d_vis_set_focus(order_time_info->vis_on);
                }
                break;

            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_ID
get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

/** @brief 事件处理*/
static D_Result
atv_pop_order_time_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_order_time_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
                {
                    set_Order_time(order_time_info->enable, order_time_info->ihour, order_time_info->iminute);
                    if(CallbackpFunc)
                        CallbackpFunc();
                    return d_gui_upper_menu();
                }
                break;
                case D_KEY_MENU:
				case D_KEY_PNL_MENU:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC: 
                case D_KEY_BACK: 
                {
                    return d_gui_upper_menu();
                }
                break;
                //case D_KEY_ESC:
                //    return d_gui_clear_menu();
                //    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    D_DUMP("left\n");
                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if(ID_POPORDERTIME_BUTTON_OFF == get_focus_control_id(frm))
                        break;
                    order_time_info->enable = 1;
                    d_vis_set_focus(order_time_info->vis_hour);
                    D_DUMP("right\n");
                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                {
                    order_time_info->enable = 1;
                    d_vis_set_focus(order_time_info->vis_on);
                    D_DUMP("up\n");
                }
                break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                {
                    D_DUMP("down\n");
                    order_time_info->enable = 0;
                    d_vis_set_focus(order_time_info->vis_off);
                }
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

            if(order_time_info)
            {
                PROJECT_FREE(order_time_info);
                order_time_info = NULL;
            }
        }
        break;

        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_pop_order_time_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8     hour;
    D_U8     minute;

    order_time_info = PROJECT_ALLOC(sizeof (OrderTimeStruct));
    if (! order_time_info)
        return D_ERR;
    memset(order_time_info, 0, sizeof (OrderTimeStruct));

    vis = d_frame_get_control(frm, ID_POPORDERTIME_LABLE_DIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    order_time_info->vis_on = d_frame_get_control(frm, ID_POPORDERTIME_BUTTON_ON);
    if(order_time_info->vis_on)
    {
        d_button_set_text (order_time_info->vis_on, "on");
    }

    order_time_info->vis_off = d_frame_get_control(frm, ID_POPORDERTIME_BUTTON_OFF);
    if(order_time_info->vis_off)
    {
        d_button_set_text (order_time_info->vis_off, "off");
    }
		
    get_OrderTime_time(&order_time_info->ihour, &order_time_info->iminute);

    if(get_OrderTime_enable())
    {
        order_time_info->enable = 1;
        d_vis_set_focus(order_time_info->vis_on);
    }
    else
    {
        order_time_info->enable = 0;
        d_vis_set_focus(order_time_info->vis_off);
    }
    order_time_info->vis_hour = d_frame_get_control(frm, ID_POPORDERTIME_INPUT_HOUR);
    if(order_time_info->vis_hour)
    {
        sprintf(order_time_info->hour, "%02d", (D_U32)order_time_info->ihour);
        d_input_box_set_text(order_time_info->vis_hour, order_time_info->hour, 2);
        d_vis_set_handler (order_time_info->vis_hour, set_order_time_hour_handler);
    }

    order_time_info->vis_minute = d_frame_get_control(frm, ID_POPORDERTIME_INPUT_MINUTE);
    if(order_time_info->vis_minute)
    {
        sprintf(order_time_info->minute, "%02d", (D_U32)order_time_info->iminute);
        d_input_box_set_text(order_time_info->vis_minute, order_time_info->minute, 2);
        d_vis_set_handler (order_time_info->vis_minute, set_order_time_minute_handler);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_pop_order_time_window_handler);
    }
    return D_OK;
}

/** @brief 显示弹出框预定时间菜单*/
D_Result
p_atv_pop_order_time_show (void (*pFunc)()) D_FUNCPOSTFIT
{
    CallbackpFunc = pFunc;
    return d_gui_enter_menu (&atv_pop_order_time_window, D_FALSE);
}

