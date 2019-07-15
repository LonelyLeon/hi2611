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
#include "atv_menu_time_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define MENU_TIME_BUTTON_NUM 2

typedef struct
{
    D_S16 menu_time_flag;
    D_Visual *vis_1, *vis_2, *vis_3;
	D_Bool first_flag;
} D_MenuTimeData;

static D_MenuTimeData *menutime_data = NULL;

/*取得参数*/
static D_U8 atv_menu_time_get_param(void)D_FUNCPOSTFIT
{
	D_U8 time;
	
    /*取得参数*/
	time = p_conf_get_info_time();
	if(time <= 5)
	{
		return 0;		
	}
	else if((time > 5)&&(time <= 10))
	{
		return 1;		
	}
	else
	{
		return 2;				
	}
}

/*保存参数*/
static D_Result atv_menu_time_save_param(D_S16 flag)D_FUNCPOSTFIT
{
    /*保存参数*/
    if(flag == 0)
    {
		p_conf_set_info_time(5);		
        //设置菜单时间为5秒
    }
    else if(flag == 1)
    {
		p_conf_set_info_time(10);		
        //设置菜单时间为10秒
    }
    else if(flag == 2)
    {
		p_conf_set_info_time(15);		
        //设置菜单时间为15秒
    }

	return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_menu_time_set_param(void)D_FUNCPOSTFIT
{
    if(menutime_data->menu_time_flag == 0)
    {
		p_conf_set_info_time(5);		
		p_atv_menu_timer_reset(5);
			//设置菜单时间为5秒
    }
    else if(menutime_data->menu_time_flag == 1)
    {
		p_conf_set_info_time(10);		
		p_atv_menu_timer_reset(10);
        //设置菜单时间为10秒
    }
    else if(menutime_data->menu_time_flag == 2)
    {
		p_conf_set_info_time(15);		
		p_atv_menu_timer_reset(15);
        //设置菜单时间为15秒
    }

    return D_OK;
}

/** @brief 5秒事件处理*/
static D_Result
button_5seconds_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_menu_time_set_param();
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 10秒事件处理*/
static D_Result
button_10seconds_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_menu_time_set_param();
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 15秒事件处理*/
static D_Result
button_15seconds_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_menu_time_set_param();
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
        }
        break;

        default:
            break;
    }
    return D_OK;
}

static D_Result
set_button_enable (D_Bool flag) D_FUNCPOSTFIT
{
    d_vis_enable(menutime_data->vis_1, flag);
    d_vis_enable(menutime_data->vis_2, flag);
    d_vis_enable(menutime_data->vis_3, flag);

    d_vis_set_focusable(menutime_data->vis_1, flag);
    d_vis_set_focusable(menutime_data->vis_2, flag);
    d_vis_set_focusable(menutime_data->vis_3, flag);
    if(!flag)
    {
        if(menutime_data->menu_time_flag  != 0)d_vis_enable(menutime_data->vis_1, D_TRUE);
        if(menutime_data->menu_time_flag  != 1)d_vis_enable(menutime_data->vis_2, D_TRUE);
        if(menutime_data->menu_time_flag  != 2)d_vis_enable(menutime_data->vis_3, D_TRUE);
   }
    return D_OK;
}

static D_Result
set_vis_focus (D_S16 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_vis_set_focus(menutime_data->vis_1);
            break;
        case 1:
            d_vis_set_focus(menutime_data->vis_2);
            break;
        case 2:
            d_vis_set_focus(menutime_data->vis_3);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_menu_time_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_menu_time_window;

    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_MENUTIME_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_MENUTIME_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
					if(menutime_data->first_flag == D_TRUE)
	                {
	                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    set_button_enable(D_TRUE);
	                    set_vis_focus(menutime_data->menu_time_flag);
						menutime_data->first_flag = D_FALSE;
	                }
                	break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(menutime_data->first_flag == D_FALSE)
	                {
	                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    set_button_enable(D_FALSE);
						menutime_data->first_flag = D_TRUE;
	                }
					else //if(evt->fp.key != D_KEY_BACK)
					{
						return d_gui_clear_menu();
					}
                	break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
	                {
	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    menutime_data->menu_time_flag --;
	                    if(menutime_data->menu_time_flag < 0)
	                    {
	                        menutime_data->menu_time_flag = MENU_TIME_BUTTON_NUM;
	                    }
	                    set_vis_focus(menutime_data->menu_time_flag);

	                }
	                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
	                {
	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

	                    menutime_data->menu_time_flag ++;
	                    if(menutime_data->menu_time_flag > MENU_TIME_BUTTON_NUM)
	                    {
	                        menutime_data->menu_time_flag = 0;
	                    }
	                    set_vis_focus(menutime_data->menu_time_flag);
	                }
	                break;
				case D_KEY_UP:
                case D_KEY_PNL_U:
				case D_KEY_DOWN:
                case D_KEY_PNL_D:
					if(menutime_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(menutime_data->first_flag == D_TRUE)
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
            atv_menu_time_save_param(menutime_data->menu_time_flag);
            if(menutime_data)
            {
                PROJECT_FREE(menutime_data);
                menutime_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_menu_time_window_init(D_Frame *frm)
{
    D_Visual *vis;

    menutime_data = (D_MenuTimeData*)PROJECT_ALLOC(sizeof(D_MenuTimeData));
    if(!menutime_data)
    {
        return D_ERR;
    }
    memset(menutime_data, 0x00, sizeof(D_MenuTimeData));
    menutime_data->menu_time_flag = (D_S16)atv_menu_time_get_param();
    menutime_data->vis_1 = d_frame_get_control(frm, ID_MENUTIME_BUTTON_1); //5 秒
    menutime_data->vis_2 = d_frame_get_control(frm, ID_MENUTIME_BUTTON_2);//10 秒
    menutime_data->vis_3 = d_frame_get_control(frm, ID_MENUTIME_BUTTON_3);//15 秒

    d_vis_set_handler (menutime_data->vis_1, button_5seconds_handler);
    d_vis_set_handler (menutime_data->vis_2, button_10seconds_handler);
    d_vis_set_handler (menutime_data->vis_3, button_15seconds_handler);

	menutime_data->first_flag = D_TRUE;
    vis = d_frame_get_control(frm, ID_MENUTIME_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_enable(vis, D_FALSE);
        set_button_enable(D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_menu_time_window_handler);

    }

    return D_OK;
}

/** @brief 显示菜单时间菜单*/
D_Result
p_atv_menu_time_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_menu_time_window, D_FALSE);
}

