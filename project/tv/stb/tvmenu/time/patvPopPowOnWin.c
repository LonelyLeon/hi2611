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
#include "atv_pop_powon_window.c"


typedef struct
{
    D_Visual *vis_minute;
    D_Visual    *vis_hour;
    D_Visual    *vis_off;
    D_Visual    *vis_on;
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char      minute[10];
    D_U8    enable;
    D_S32       ihour;
    D_S32       iminute;
} PowerONStruct;

static PowerONStruct *powon_info;
typedef void (*PowerONCallback)(void);
static PowerONCallback CallbackpFunc = NULL;

static D_Result get_cur_time(D_U8 *en, D_U8 *hour, D_U8 *minute)
{
    D_Tv_Config_Poweron_Order   order;

    p_tvconf_get_poweron_order(&order);
    *en = order.en;
    *hour = order.hour;
    *minute = order.min;
    return D_OK;
}

static D_Result set_cur_time(D_U8 en, D_U8 hour, D_U8 minute)
{
    D_Tv_Config_Poweron_Order   order;

    order.en = en;
    order.hour = hour;
    order.min = minute;
    p_tvconf_set_poweron_order(&order);

    return D_OK;
}

static D_Result
set_powon_minute_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_power_on_window;
    static D_U16 cusor_old = 0;
    D_S32   min_check;

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1 )
            {
                powon_info->iminute = d_input_box_get_num(vis);
                if(powon_info->iminute > 59)
                    powon_info->iminute = 0;
                sprintf(powon_info->minute, "%02d", (D_U32)powon_info->iminute);
                d_input_box_set_text(powon_info->vis_minute, powon_info->minute, 2);
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
                        d_vis_set_focus(powon_info->vis_hour);
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
set_powon_hour_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_power_on_window;
    D_S32   hour_check;

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
        {
            if(vis->element.input.val1 == 1)
            {
                powon_info->ihour = d_input_box_get_num(vis);
                if(powon_info->ihour > 23)
                    powon_info->ihour = 0;
                sprintf(powon_info->hour, "%02d", (D_U32)powon_info->ihour);
                d_input_box_set_text(powon_info->vis_hour, powon_info->hour, 2);
            }
            else if(vis->element.input.val1 == 2)
            {
                d_vis_set_focus(powon_info->vis_minute);
                powon_info->ihour = d_input_box_get_num(vis);
                if(powon_info->ihour > 23)
                    powon_info->ihour = 0;
                sprintf(powon_info->hour, "%02d", (D_U32)powon_info->ihour);
                d_input_box_set_text(powon_info->vis_hour, powon_info->hour, 2);
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
                        d_vis_set_focus(powon_info->vis_minute);
                    }
                }
                break;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    d_vis_set_focus(powon_info->vis_on);
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
atv_pop_power_on_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_pop_power_on_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
				case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
                {
									set_cur_time(powon_info->enable, powon_info->ihour, powon_info->iminute);
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
               // break;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    D_DUMP("left\n");
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if(ID_POPON_BUTTON_OFF == get_focus_control_id(frm))
                        break;
                    d_vis_set_focus(powon_info->vis_hour);
                    D_DUMP("right\n");
                }
                break;

                case D_KEY_UP:
                case D_KEY_PNL_U:
                {
                    d_vis_set_focus(powon_info->vis_on);
										powon_info->enable = 1;
                    D_DUMP("up\n");
                }
                break;

                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                {
                    D_DUMP("down\n");
                    d_vis_set_focus(powon_info->vis_off);
										powon_info->enable = 0;
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

            if(powon_info)
            {
                PROJECT_FREE(powon_info);
                powon_info = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_pop_power_on_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    powon_info = PROJECT_ALLOC(sizeof (PowerONStruct));
    if (! powon_info)
        return D_ERR;
    memset(powon_info, 0, sizeof (PowerONStruct));

    get_cur_time(&powon_info->enable, &powon_info->ihour, &powon_info->iminute);
    vis = d_frame_get_control(frm, ID_POPON_LABLE_DIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    powon_info->vis_on = d_frame_get_control(frm, ID_POPON_BUTTON_ON);
    if(powon_info->vis_on)
    {
        d_button_set_text (powon_info->vis_on, "on");
    }

    powon_info->vis_off = d_frame_get_control(frm, ID_POPON_BUTTON_OFF);
    if(powon_info->vis_off)
    {
        d_button_set_text (powon_info->vis_off, "off");
    }
    if(powon_info->enable)
    {
        d_vis_set_focus(powon_info->vis_on);
    }
    else
    {
        d_vis_set_focus(powon_info->vis_off);
    }
    powon_info->vis_hour = d_frame_get_control(frm, ID_POPON_INPUT_HOUR);
    if(powon_info->vis_hour)
    {
        sprintf(powon_info->hour, "%02d", (D_U32)powon_info->ihour);
        d_input_box_set_text(powon_info->vis_hour, powon_info->hour, 2);
        d_vis_set_handler (powon_info->vis_hour, set_powon_hour_handler);
    }

    powon_info->vis_minute = d_frame_get_control(frm, ID_POPON_INPUT_MINUTE);
    if(powon_info->vis_minute)
    {
        sprintf(powon_info->minute, "%02d", (D_U32)powon_info->iminute);
        d_input_box_set_text(powon_info->vis_minute, powon_info->minute, 2);
        d_vis_set_handler (powon_info->vis_minute, set_powon_minute_handler);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_pop_power_on_window_handler);
    }
    return D_OK;
}

/** @brief 显示弹出框定时开机菜单*/
D_Result
p_atv_pop_power_on_show (void (*pFunc)()) D_FUNCPOSTFIT
{
    CallbackpFunc = pFunc;
    return d_gui_enter_menu (&atv_pop_power_on_window, D_FALSE);
}

