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
#include "atv_set_time_window.c"

typedef struct
{
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char  minute[10];
	D_Bool first_flag;
} D_SetTimeData;

static D_SetTimeData *settime_data = NULL;

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

static void update_time(void)
{
    D_Visual *vis;
    D_Frame *frm = &atv_set_time_window;
    D_U8     hour;
    D_U8     minute;

    vis = d_frame_get_control(frm, ID_SETTIME_LABLE_SHOWHOUR);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(settime_data->hour, "%02d", (D_U32)hour);
            d_label_set_text(vis, settime_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_SETTIME_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(settime_data->minute, "%02d", (D_U32)minute);
            d_label_set_text(vis, settime_data->minute);
        }
    }
    d_vis_update(NULL, NULL);

    return ;
}

/** @brief 事件处理*/
static D_Result
set_time_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_pop_set_time_show(update_time);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_set_time_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_set_time_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_SETTIME_BUTTON_SET);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
					if(settime_data->first_flag == D_TRUE)
					{
						d_vis_enable(vis_button, D_TRUE);
	                    d_vis_set_focusable(vis_button, D_TRUE);
	                    d_vis_set_focus(vis_button);

						settime_data->first_flag = D_FALSE;
					}
                    break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(settime_data->first_flag == D_FALSE)
	                {
	                    d_vis_enable(vis_button, D_FALSE);
	                    d_vis_set_focusable(vis_button, D_FALSE);

						settime_data->first_flag = D_TRUE;
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
					if(settime_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(settime_data->first_flag == D_TRUE)
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
            if(settime_data)
            {
                PROJECT_FREE(settime_data);
                settime_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}



D_Result
atv_set_time_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8     hour;
    D_U8     minute;

    settime_data = (D_SetTimeData*)PROJECT_ALLOC(sizeof(D_SetTimeData));
    if(!settime_data)
    {
        return D_ERR;
    }
    memset(settime_data, 0x00, sizeof(D_SetTimeData));

	settime_data->first_flag = D_TRUE;
    vis = d_frame_get_control(frm, ID_SETTIME_LABLE_SHOWDIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    vis = d_frame_get_control(frm, ID_SETTIME_LABLE_SHOWHOUR);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(settime_data->hour, "%02d", (D_U32)hour);
            d_label_set_text(vis, settime_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_SETTIME_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(get_cur_time(&hour, &minute) != D_OK)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(settime_data->minute, "%02d", (D_U32)minute);
            d_label_set_text(vis, settime_data->minute);
        }
    }


    vis = d_frame_get_control(frm, ID_SETTIME_BUTTON_SET); //调整
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_vis_set_handler (vis, set_time_button_handler);
    }

	vis = d_frame_get_control (frm, ID_SETTIME_GROUP_BG);
    if(vis)
    {	
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }
	
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_set_time_window_handler);
    }
    return D_OK;
}

/** @brief 显示当前时间菜单*/
D_Result
p_atv_set_time_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_set_time_window, D_FALSE);
}

