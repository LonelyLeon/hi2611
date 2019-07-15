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
#include "atv_color_mode_window.c"

#define COLOR_MODE_BUTTON_NUM 3

typedef struct
{
    D_U8   color_mode_focus_flag;
    D_Bool first_flag;
    D_VidInput input;
    D_U8   color_mode;
    D_Visual *vis_warm, *vis_standard, *vis_cool;
} D_ImageColorModeData;

static D_ImageColorModeData *color_mode_data = NULL;


/** @brief 暖色按钮事件处理*/
static D_Result
button_warm_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(color_mode_data->color_mode_focus_flag == 1 && !color_mode_data->first_flag)
            {
                p_vip_set_Temperature(color_mode_data->input, 0, 0);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 标准按钮事件处理*/
static D_Result
button_color_standard_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(color_mode_data->color_mode_focus_flag == 2 && !color_mode_data->first_flag)
            {
                p_vip_set_Temperature(color_mode_data->input, 1, 0);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 冷色按钮事件处理*/
static D_Result
button_cool_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(color_mode_data->color_mode_focus_flag == 3 && !color_mode_data->first_flag)
            {
                p_vip_set_Temperature(color_mode_data->input, 2, 0);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 设置按钮的焦点*/
static D_Result
set_vis_focus (D_U32 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 1:
            d_vis_set_focus(color_mode_data->vis_warm);
            break;
        case 2:
            d_vis_set_focus(color_mode_data->vis_standard);
            break;
        case 3:
            d_vis_set_focus(color_mode_data->vis_cool);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 设置按钮是否可用和是否可聚焦*/
static D_Result
set_button_enable (D_Bool flag) D_FUNCPOSTFIT
{
    d_vis_set_focusable(color_mode_data->vis_warm, flag);
    d_vis_set_focusable(color_mode_data->vis_standard, flag);
    d_vis_set_focusable(color_mode_data->vis_cool, flag);

    d_vis_enable(color_mode_data->vis_warm, flag);
    d_vis_enable(color_mode_data->vis_standard, flag);
    d_vis_enable(color_mode_data->vis_cool, flag);
    if(!flag)
    {
        if(color_mode_data->color_mode_focus_flag != 1)d_vis_enable(color_mode_data->vis_warm, D_TRUE);
        if(color_mode_data->color_mode_focus_flag != 2)d_vis_enable(color_mode_data->vis_standard, D_TRUE);
        if(color_mode_data->color_mode_focus_flag != 3)d_vis_enable(color_mode_data->vis_cool, D_TRUE);
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_color_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_color_mode_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
					if(color_mode_data->first_flag == D_TRUE)
                	{
	                    d_vis_subscribe_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	                    color_mode_data->color_mode_focus_flag = color_mode_data->color_mode + 1;

	                    vis = d_frame_get_control(frm, ID_COLORMODE_GROUP_BACKGROUND);
	                    if(vis)
	                    {
	                        d_vis_enable(vis, D_TRUE);
	                    }
	                    set_button_enable(D_TRUE);
	                    set_vis_focus(color_mode_data->color_mode_focus_flag);
	                    color_mode_data->first_flag = D_FALSE;
					
                	}
                break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(color_mode_data->first_flag == D_FALSE)
                	{
	                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	                    vis = d_frame_get_control(frm, ID_COLORMODE_GROUP_BACKGROUND);
	                    if(vis)
	                    {
	                        d_vis_enable(vis, D_FALSE);
	                        set_button_enable(D_FALSE);
	                    }
	                    if(color_mode_data->color_mode_focus_flag - 1 != color_mode_data->color_mode)
	                    {
	                        color_mode_data->color_mode = color_mode_data->color_mode_focus_flag - 1;
	                        p_tvconf_set_cur_colormode(&color_mode_data->color_mode, p_vip_get_dbinput(color_mode_data->input));
	                    }
	                    color_mode_data->first_flag = D_TRUE;
                	}
			else //if(evt->fp.key != D_KEY_BACK)
			{
				d_gui_upper_menu();		//for exit Key 20190628
				return d_gui_upper_menu();
			}
                	break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
	                {
	                    color_mode_data->color_mode_focus_flag --;
	                    if(color_mode_data->color_mode_focus_flag == 0)
	                    {
	                        color_mode_data->color_mode_focus_flag = COLOR_MODE_BUTTON_NUM;
	                    }
	                    set_vis_focus(color_mode_data->color_mode_focus_flag);
	                }
                	break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
	                {
	                    color_mode_data->color_mode_focus_flag ++;
	                    if(color_mode_data->color_mode_focus_flag > COLOR_MODE_BUTTON_NUM)
	                    {
	                        color_mode_data->color_mode_focus_flag = 1;
	                    }
	                    set_vis_focus(color_mode_data->color_mode_focus_flag);
	                }
                	break;
				case D_KEY_UP:
                case D_KEY_PNL_U:
				case D_KEY_DOWN:
                case D_KEY_PNL_D:
					if(color_mode_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(color_mode_data->first_flag == D_TRUE)
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
            if(color_mode_data)
            {
                if(color_mode_data->color_mode_focus_flag - 1 != color_mode_data->color_mode)
                {
                    color_mode_data->color_mode = color_mode_data->color_mode_focus_flag - 1;
                    p_tvconf_set_cur_colormode(&color_mode_data->color_mode, p_vip_get_dbinput(color_mode_data->input));
                }

                PROJECT_FREE(color_mode_data);
                color_mode_data = NULL;
            }
        }
        break;


        default:
            break;
    }
}


/** @brief 色温窗口初始化*/
D_Result
atv_color_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;

    color_mode_data = (D_ImageColorModeData*)PROJECT_ALLOC(sizeof(D_ImageColorModeData));
    if(!color_mode_data)
    {
        return D_ERR;
    }
    memset(color_mode_data, 0, sizeof(D_ImageColorModeData));
    color_mode_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_colormode(&color_mode_data->color_mode, p_vip_get_dbinput(color_mode_data->input));
    color_mode_data->color_mode_focus_flag = color_mode_data->color_mode + 1;
    color_mode_data->color_mode_focus_flag = D_MIN(color_mode_data->color_mode_focus_flag, COLOR_MODE_BUTTON_NUM);
    color_mode_data->color_mode_focus_flag = D_MAX(color_mode_data->color_mode_focus_flag, 1);
    color_mode_data->first_flag = D_TRUE;

    vis = d_frame_get_control(frm, ID_COLORMODE_BUTTON_WARM); //暖色
    if(vis)
    {
        color_mode_data->vis_warm = vis;
        d_vis_set_handler (color_mode_data->vis_warm, button_warm_handler);
    }

    vis = d_frame_get_control(frm, ID_COLORMODE_BUTTON_STANDARD);//标准
    if(vis)
    {
        color_mode_data->vis_standard = vis;
        d_vis_set_handler (color_mode_data->vis_standard, button_color_standard_handler);
    }

    vis = d_frame_get_control(frm, ID_COLORMODE_BUTTON_COOL);//冷色
    if(vis)
    {
        color_mode_data->vis_cool = vis;
        d_vis_set_handler (color_mode_data->vis_cool, button_cool_handler);
    }

    vis = d_frame_get_control(frm, ID_COLORMODE_GROUP_BACKGROUND);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_color_mode_window_handler);
    }

    set_button_enable(D_FALSE);

    return D_OK;
}

/** @brief 显示色温窗口*/
D_Result
p_atv_color_mode_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_color_mode_window, D_FALSE);
}

