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
#include "atv_blue_screen_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define BLUE_SCREEN_BUTTON_NUM 1

typedef struct
{
    D_S16 blue_screen_flag;
    D_Visual *vis_1, *vis_2;
    D_Bool first_flag;
    D_VidInput  curinput;
} D_BlueScreenData;

static D_BlueScreenData *bluescreen_data = NULL;

/*取得参数*/
static D_U8 atv_blue_screen_get_param(void)D_FUNCPOSTFIT
{
    D_U8 flag;

	p_tvconf_get_blue_screen(&flag);
	return flag;
}

/*保存参数*/
static D_Result atv_blue_screen_save_param(D_S16 flag)D_FUNCPOSTFIT
{
    /*保存参数*/

    p_tvconf_set_blue_screen(&flag);

    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_blue_screen_set_param(void)D_FUNCPOSTFIT
{
    if(bluescreen_data->curinput == D_VID_IUTPUT_USB1 || bluescreen_data->curinput == D_VID_IUTPUT_USB2 \
       || bluescreen_data->curinput == D_VID_IUTPUT_USB3 || bluescreen_data->curinput == D_VID_IUTPUT_WIFIDISPLAY)
    {
        return D_OK;
    }
    
    if(bluescreen_data->blue_screen_flag == 0)
    {
        d_av_set_vid_background(0, D_VID_BackGround_Blue);
    }
    else if(bluescreen_data->blue_screen_flag == 1)
    {
        d_av_set_vid_background(0, D_VID_BackGround_BLack);
    }
    return D_OK;
}

static D_Result
button_bluescreen_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_blue_screen_set_param();
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
button_blackscreen_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_blue_screen_set_param();
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
    d_vis_enable(bluescreen_data->vis_1, flag);
    d_vis_enable(bluescreen_data->vis_2, flag);

    d_vis_set_focusable(bluescreen_data->vis_1, flag);
    d_vis_set_focusable(bluescreen_data->vis_2, flag);
    if(!flag)
    {
        if(bluescreen_data->blue_screen_flag != 0)d_vis_enable(bluescreen_data->vis_1, D_TRUE);
        if(bluescreen_data->blue_screen_flag != 1)d_vis_enable(bluescreen_data->vis_2, D_TRUE);
    }
    return D_OK;
}

static D_Result
set_vis_focus (D_S16 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_vis_set_focus(bluescreen_data->vis_1);
            break;
        case 1:
            d_vis_set_focus(bluescreen_data->vis_2);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_blue_screen_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_blue_screen_window;

    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_BLUESCREEN_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_BLUESCREEN_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                    if(bluescreen_data->first_flag == D_TRUE)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                        d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                        set_button_enable(D_TRUE);
                        set_vis_focus(bluescreen_data->blue_screen_flag);
                        bluescreen_data->first_flag = D_FALSE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(bluescreen_data->first_flag == D_FALSE)
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

                        d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                        d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                        set_button_enable(D_FALSE);
                        bluescreen_data->first_flag = D_TRUE;
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

                    bluescreen_data->blue_screen_flag --;
                    if(bluescreen_data->blue_screen_flag < 0)
                    {
                        bluescreen_data->blue_screen_flag = BLUE_SCREEN_BUTTON_NUM;
                    }
                    set_vis_focus(bluescreen_data->blue_screen_flag);

                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

                    bluescreen_data->blue_screen_flag ++;
                    if(bluescreen_data->blue_screen_flag > BLUE_SCREEN_BUTTON_NUM)
                    {
                        bluescreen_data->blue_screen_flag = 0;
                    }
                    set_vis_focus(bluescreen_data->blue_screen_flag);
                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(bluescreen_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(bluescreen_data->first_flag == D_TRUE)
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
            atv_blue_screen_save_param(bluescreen_data->blue_screen_flag);
            if(bluescreen_data)
            {
                PROJECT_FREE(bluescreen_data);
                bluescreen_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_blue_screen_window_init(D_Frame *frm)
{
    D_Visual *vis;

    bluescreen_data = (D_BlueScreenData*)PROJECT_ALLOC(sizeof(D_BlueScreenData));
    if(!bluescreen_data)
    {
        return D_ERR;
    }
    memset(bluescreen_data, 0x00, sizeof(D_BlueScreenData));
    bluescreen_data->curinput = p_conf_get_vid_input();
    bluescreen_data->blue_screen_flag = (D_S16)atv_blue_screen_get_param();
    bluescreen_data->vis_1 = d_frame_get_control(frm, ID_BLUESCREEN_BUTTON_1);
    bluescreen_data->vis_2 = d_frame_get_control(frm, ID_BLUESCREEN_BUTTON_2);

    d_vis_set_handler (bluescreen_data->vis_1, button_bluescreen_handler);
    d_vis_set_handler (bluescreen_data->vis_2, button_blackscreen_handler);

    bluescreen_data->first_flag = D_TRUE;
    vis = d_frame_get_control(frm, ID_BLUESCREEN_GROUP_BG);
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
        d_vis_set_handler (vis, atv_blue_screen_window_handler);

    }

    return D_OK;
}

/** @brief 显示菜单时间菜单*/
D_Result
p_atv_blue_screen_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_blue_screen_window, D_FALSE);
}

