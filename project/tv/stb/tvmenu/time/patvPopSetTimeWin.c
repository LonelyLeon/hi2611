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
#include "atv_pop_time_window.c"


typedef struct
{
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char      minute[10];
    D_S32       ihour;
    D_S32       iminute;
} D_PopSetTimeData;

typedef void (*Callback)(void);
static Callback CallbackpFunc = NULL;
static D_PopSetTimeData *popsettime_data = NULL;

static D_Result get_cur_time(D_U8 *hour, D_U8 *minute)
{
    D_Time  now = 0;
    D_Date  date = {0};

    if(d_time_had_set_time())
    {
        //now = d_time_get_time ();
        //now = d_time_local_time (now);
        //d_date (now, &date);
        now = d_time_get_local_time();
        d_date (now, &date);

        *hour = date.hour;
        *minute = date.min;
        return D_OK;
    }
    return D_ERR;
}

static D_Result set_cur_time(D_U8 hour, D_U8 minute)
{
    D_Time utc_time = 0;
    D_Time  now = 0;
    D_Date  date = {0};

    now = d_time_get_local_time();
    d_date (now, &date);

    date.min = minute;
    date.hour = hour;

    utc_time = d_time_utc_time(d_date_anti(&date));
    d_time_set_time(utc_time);

    return D_OK;
}

static D_Result
set_minute_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *vis_hour;
    D_Frame *frm = &atv_pop_time_window;
    static D_U16 cusor_old = 0;

    vis_hour = d_frame_get_control(frm, ID_POPTIME_INPUT_HOUR);

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1 )
            {
                popsettime_data->iminute = d_input_box_get_num(vis);
                if( popsettime_data->iminute > 59)
                    popsettime_data->iminute = 0;
                sprintf(popsettime_data->minute, "%02d", popsettime_data->iminute);
                d_input_box_set_text(vis, popsettime_data->minute, 2);
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
                        d_vis_set_focus(vis_hour);
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

/** @brief 冷色按钮事件处理*/
static D_Result
set_hour_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *vis_minute;
    D_Frame *frm = &atv_pop_time_window;

    vis_minute = d_frame_get_control(frm, ID_POPTIME_INPUT_MINUTE);

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1)
            {
                //d_vis_set_focus(vis_minute);
                popsettime_data->ihour = d_input_box_get_num(vis);
                if(popsettime_data->ihour > 23)
                    popsettime_data->ihour = 0;
                sprintf(popsettime_data->hour, "%02d", popsettime_data->ihour);
                d_input_box_set_text(vis, popsettime_data->hour, 2);
            }
            if(vis->element.input.val1 == 2)
            {
                d_vis_set_focus(vis_minute);
                popsettime_data->ihour = d_input_box_get_num(vis);
                if(popsettime_data->ihour > 23)
                    popsettime_data->ihour = 0;
                sprintf(popsettime_data->hour, "%02d", popsettime_data->ihour);
                d_input_box_set_text(vis, popsettime_data->hour, 2);
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
                        d_vis_set_focus(vis_minute);
                    }
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
/** @brief 事件处理*/
static D_Result
atv_pop_set_time_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_time_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
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
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
                {
                    set_cur_time(popsettime_data->ihour, popsettime_data->iminute);
                    if(CallbackpFunc)
                        CallbackpFunc();
                    return d_gui_upper_menu();
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

            if(popsettime_data)
            {
                PROJECT_FREE(popsettime_data);
                popsettime_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_pop_time_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    popsettime_data = (D_PopSetTimeData*)PROJECT_ALLOC(sizeof(D_PopSetTimeData));
    if(!popsettime_data)
    {
        return D_ERR;
    }
    memset(popsettime_data, 0, sizeof(D_PopSetTimeData));
    vis = d_frame_get_control(frm, ID_POPTIME_LABLE_DIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    get_cur_time(&popsettime_data->ihour, &popsettime_data->iminute);

    sprintf(popsettime_data->hour, "%02d", (D_U32)popsettime_data->ihour);
    sprintf(popsettime_data->minute, "%02d", (D_U32)popsettime_data->iminute);

    vis = d_frame_get_control(frm, ID_POPTIME_INPUT_HOUR);
    if(vis)
    {
        d_input_box_set_text(vis, popsettime_data->hour, 2);
        d_vis_set_handler (vis, set_hour_handler);
    }

    vis = d_frame_get_control(frm, ID_POPTIME_INPUT_MINUTE);
    if(vis)
    {
        d_input_box_set_text(vis, popsettime_data->minute, 2);
        d_vis_set_handler (vis, set_minute_handler);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_pop_set_time_window_handler);
    }
    return D_OK;
}

/** @brief 显示当前时间菜单*/
D_Result
p_atv_pop_set_time_show (void (*pFunc)()) D_FUNCPOSTFIT
{
    CallbackpFunc = pFunc;
    return d_gui_enter_menu (&atv_pop_time_window, D_FALSE);
//  return d_gui_open_frame(&atv_pop_time_window, D_GUI_LAYER_VIDEO);
}

