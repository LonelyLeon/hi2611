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
#include "atv_power_on_window.c"


typedef struct
{
    D_U32    menu_show_time;
    D_Char  hour[10];
    D_Char      minute[10];
    D_U8    enable;
    D_S32       ihour;
    D_S32       iminute;
    D_Bool first_flag;

} D_PowerOnData;

static D_PowerOnData *poweron_data = NULL;


static D_Result get_cur_time(D_U8 *en, D_U8 *hour, D_U8 *minute)
{
    D_Tv_Config_Poweron_Order   order;

    p_tvconf_get_poweron_order(&order);
    *en = order.en;
    *hour = order.hour;
    *minute = order.min;
    return D_OK;
}

static void update_time(void)D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Frame *frm = &atv_power_on_window;

    get_cur_time(&poweron_data->enable, &poweron_data->ihour, &poweron_data->iminute);
    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SHOWHOUR);
    if(vis)
    {
        if(poweron_data->enable == 0)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(poweron_data->hour, "%02d", (D_U32)poweron_data->ihour);
            d_label_set_text(vis, poweron_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(poweron_data->enable == 0)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(poweron_data->minute, "%02d", (D_U32)poweron_data->iminute);
            d_label_set_text(vis, poweron_data->minute);
        }
    }

    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SWITCH); //开关
    if(vis)
    {
        if(poweron_data->enable == 1)
            d_label_set_text (vis, "On");
        else
            d_label_set_text (vis, "Off");
    }


    d_vis_update(NULL, NULL);

    return ;
}


/** @brief 事件处理*/
static D_Result
power_on_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_pop_power_on_show(update_time);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_power_on_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_power_on_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_POWERON_BUTTON_SET);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    if(poweron_data->first_flag == D_TRUE)
                    {
                        d_vis_enable(vis_button, D_TRUE);
                        d_vis_set_focusable(vis_button, D_TRUE);
                        d_vis_set_focus(vis_button);
                        poweron_data->first_flag = D_FALSE;
                    }

                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(poweron_data->first_flag == D_FALSE)
                    {
                        d_vis_enable(vis_button, D_FALSE);
                        d_vis_set_focusable(vis_button, D_FALSE);
                        poweron_data->first_flag = D_TRUE;
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                    		d_gui_upper_menu();	//for exit key 20190628
                        return d_gui_upper_menu();
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
                    if(poweron_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(poweron_data->first_flag == D_TRUE)
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
            if(poweron_data)
            {
                PROJECT_FREE(poweron_data);
                poweron_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_power_on_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8     hour;
    D_U8     minute;

    poweron_data = (D_PowerOnData*)PROJECT_ALLOC(sizeof(D_PowerOnData));
    if(!poweron_data)
    {
        return D_ERR;
    }
    memset(poweron_data, 0x00, sizeof(D_PowerOnData));
    poweron_data->first_flag = D_TRUE;

    get_cur_time(&poweron_data->enable, &poweron_data->ihour, &poweron_data->iminute);
    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SHOWDIAN);
    if(vis)
    {
        d_label_set_text (vis, ":");
    }

    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SHOWHOUR);
    if(vis)
    {
        if(poweron_data->enable == 0)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(poweron_data->hour, "%02d", (D_U32)poweron_data->ihour);
            d_label_set_text(vis, poweron_data->hour);
        }
    }

    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SHOWMINUTE);
    if(vis)
    {
        if(poweron_data->enable == 0)
        {
            d_label_set_text(vis, "--");
        }
        else
        {
            sprintf(poweron_data->minute, "%02d", (D_U32)poweron_data->iminute);
            d_label_set_text(vis, poweron_data->minute);
        }
    }

    vis = d_frame_get_control(frm, ID_POWERON_LABLE_SWITCH); //开关
    if(vis)
    {
        if(poweron_data->enable == 1)
            d_label_set_text (vis, "On");
        else
            d_label_set_text (vis, "Off");
    }

    vis = d_frame_get_control(frm, ID_POWERON_BUTTON_SET);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_vis_set_handler (vis, power_on_button_handler);
    }

    vis = d_frame_get_control (frm, ID_POWERON_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_power_on_window_handler);
    }
    return D_OK;
}

/** @brief 显示定时开机菜单*/
D_Result
p_atv_power_on_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_power_on_window, D_FALSE);
}

