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
#include "atv_sleep_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;


#define SLEEP_BUTTON_NUM 5

typedef struct
{
    D_S16 sleep_flag;
    D_U32    menu_show_time;
	D_Visual *vis_off, *vis_15, *vis_30, *vis_60, *vis_120, * vis_240;
} D_TimeSleepData;

static D_TimeSleepData *sleep_data = NULL;

/*取得参数*/
static D_U8 atv_sleep_time_get_param(void)D_FUNCPOSTFIT
{
	/*取得参数*/
    return 0;
}

/*保存参数*/
static D_Result atv_sleep_time_save_param(D_S16 flag)D_FUNCPOSTFIT
{
	/*保存参数*/
    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_sleep_time_set_param()D_FUNCPOSTFIT
{
    if(sleep_data->sleep_flag == 0)
    {
        //关闭睡眠时间
    }
    else if(sleep_data->sleep_flag == 1)
    {
        //设置睡眠时间为15ms
    }
	else if(sleep_data->sleep_flag == 2)
    {
        //设置睡眠时间为30ms
    }
	else if(sleep_data->sleep_flag == 3)
    {
        //设置睡眠时间为60ms
    }
	else if(sleep_data->sleep_flag == 4)
    {
        //设置睡眠时间为120ms
    }
	else if(sleep_data->sleep_flag == 5)
    {
        //设置睡眠时间为240ms
    }
    return D_OK;
}

/** @brief 睡眠关事件处理*/
static D_Result
button_sleep_off_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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

/** @brief 15分钟睡眠事件处理*/
static D_Result
button_sleep_15minutes_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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

/** @brief 30分钟睡眠事件处理*/
static D_Result
button_sleep_30minutes_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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

/** @brief 60分钟睡眠事件处理*/
static D_Result
button_sleep_60minutes_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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

/** @brief 120分钟睡眠事件处理*/
static D_Result
button_sleep_120minutes_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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

/** @brief 240分钟睡眠事件处理*/
static D_Result
button_sleep_240minutes_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
			atv_sleep_time_set_param();
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
    d_vis_enable(sleep_data->vis_off, flag);
    d_vis_enable(sleep_data->vis_15, flag);
    d_vis_enable(sleep_data->vis_30, flag);
    d_vis_enable(sleep_data->vis_60, flag);
    d_vis_enable(sleep_data->vis_120, flag);
    d_vis_enable(sleep_data->vis_240, flag);
	
    d_vis_set_focusable(sleep_data->vis_off, flag);
    d_vis_set_focusable(sleep_data->vis_15, flag);
    d_vis_set_focusable(sleep_data->vis_30, flag);
    d_vis_set_focusable(sleep_data->vis_60, flag);
    d_vis_set_focusable(sleep_data->vis_120, flag);
    d_vis_set_focusable(sleep_data->vis_240, flag);

    return D_OK;
}

static D_Result
set_vis_focus (D_S16 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
    	case 0:
            d_vis_set_focus(sleep_data->vis_off);
            break;
        case 1:
            d_vis_set_focus(sleep_data->vis_15);
            break;
        case 2:
            d_vis_set_focus(sleep_data->vis_30);
            break;
        case 3:
            d_vis_set_focus(sleep_data->vis_60);
            break;
        case 4:
            d_vis_set_focus(sleep_data->vis_120);
            break;
        case 5:
            d_vis_set_focus(sleep_data->vis_240);
            break;
        
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_sleep_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_sleep_window;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_SLEEP_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_SLEEP_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {

            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                {
                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    set_button_enable(D_TRUE);

					set_vis_focus(sleep_data->sleep_flag);

                }
                break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                {
                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    set_button_enable(D_FALSE);
					//保存参数
                }
                break;
                case D_KEY_MENU:
                case D_KEY_ESC:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    sleep_data->sleep_flag --;
                    if(sleep_data->sleep_flag < 0)
                    {
                        sleep_data->sleep_flag = SLEEP_BUTTON_NUM;
                    }
                    set_vis_focus(sleep_data->sleep_flag);

                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

                    sleep_data->sleep_flag ++;
                    if(sleep_data->sleep_flag > SLEEP_BUTTON_NUM)
                    {
                        sleep_data->sleep_flag = 0;
                    }
                    set_vis_focus(sleep_data->sleep_flag);
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
			atv_sleep_time_save_param(sleep_data->sleep_flag);
            if(sleep_data)
            {
				//保存参数
                PROJECT_FREE(sleep_data);
                sleep_data = NULL;
            }
        }
        break;

        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_sleep_window_init(D_Frame *frm)
{
    D_Visual *vis;
	D_U32	time;

    sleep_data = (D_TimeSleepData*)PROJECT_ALLOC(sizeof(D_TimeSleepData));
    if(!sleep_data)
    {
        return D_ERR;
    }
    memset(sleep_data, 0x00, sizeof(D_TimeSleepData));
	sleep_data->sleep_flag = atv_sleep_time_get_param();

    sleep_data->vis_off = d_frame_get_control(frm, ID_SLEEP_BUTTON_OFF); //关
	sleep_data->vis_off = d_frame_get_control(frm, ID_SLEEP_BUTTON_OFF);//15分钟
    sleep_data->vis_15 = d_frame_get_control(frm, ID_SLEEP_BUTTON_MINUTE1);//15分钟
    sleep_data->vis_30 = d_frame_get_control(frm, ID_SLEEP_BUTTON_MINUTE2);//30分钟
    sleep_data->vis_60 = d_frame_get_control(frm, ID_SLEEP_BUTTON_MINUTE3);//60分钟
    sleep_data->vis_120 = d_frame_get_control(frm, ID_SLEEP_BUTTON_MINUTE4);//120分钟
    sleep_data->vis_240 = d_frame_get_control(frm, ID_SLEEP_BUTTON_MINUTE5);//240分钟
        
	d_vis_set_handler (sleep_data->vis_off, button_sleep_off_handler);
	d_vis_set_handler(sleep_data->vis_15, button_sleep_15minutes_handler);
	d_vis_set_handler(sleep_data->vis_30, button_sleep_30minutes_handler);
	d_vis_set_handler(sleep_data->vis_60, button_sleep_60minutes_handler);
	d_vis_set_handler(sleep_data->vis_120, button_sleep_120minutes_handler);
	d_vis_set_handler(sleep_data->vis_240, button_sleep_240minutes_handler);
	
    vis = d_frame_get_control(frm, ID_SLEEP_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        set_button_enable(D_FALSE);
    }
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK) & (~ D_EVT_UP_DOWN_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_sleep_window_handler);
    }

    return D_OK;
}

/** @brief 显示睡眠定时菜单*/
D_Result
p_atv_sleep_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_sleep_window, D_FALSE);
}

