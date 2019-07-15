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
#include "atv_video_mode_window.c"

#define VIDEO_MODE_BUTTON_NUM 4

typedef struct
{
    D_U8   video_mode_focus_flag;
    D_Bool first_flag, ntsc_flag;
    D_U8 video_mode;
    D_VidInput input;
    D_Visual *vis_standard, *vis_soft, *vis_user, *vis_bright;
} D_ImageVideoModeData;

static D_ImageVideoModeData *video_mode_data = NULL;


/** @brief 标准按钮事件处理*/
static D_Result
button_standard_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(video_mode_data->video_mode_focus_flag == 1 && !video_mode_data->first_flag)
            {
                p_vip_set_ImageMode( video_mode_data->input, 0, video_mode_data->ntsc_flag);
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

/** @brief 柔和按钮事件处理*/
static D_Result
button_soft_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(video_mode_data->video_mode_focus_flag == 2  && !video_mode_data->first_flag)
            {
                p_vip_set_ImageMode( video_mode_data->input, 1, video_mode_data->ntsc_flag);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            D_DUMP("\n rou he\n");
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 用户按钮事件处理*/
static D_Result
button_user_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(video_mode_data->video_mode_focus_flag == 3  && !video_mode_data->first_flag)
            {
                p_vip_set_ImageMode( video_mode_data->input, 2, video_mode_data->ntsc_flag);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            D_DUMP("\n yonghu\n");
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 明亮按钮事件处理*/
static D_Result
button_bright_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(video_mode_data->video_mode_focus_flag == 4  && !video_mode_data->first_flag)
            {
                p_vip_set_ImageMode( video_mode_data->input, 3, video_mode_data->ntsc_flag);
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            D_DUMP("\n mingliang\n");
        }
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
            d_vis_set_focus(video_mode_data->vis_standard);
            break;
        case 2:
            d_vis_set_focus(video_mode_data->vis_soft);
            break;
        case 3:
            d_vis_set_focus(video_mode_data->vis_user);
            break;
        case 4:
            d_vis_set_focus(video_mode_data->vis_bright);
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
    d_vis_enable(video_mode_data->vis_standard, flag);
    d_vis_enable(video_mode_data->vis_soft, flag);
    d_vis_enable(video_mode_data->vis_user, flag);
    d_vis_enable(video_mode_data->vis_bright, flag);

    d_vis_set_focusable(video_mode_data->vis_standard, flag);
    d_vis_set_focusable(video_mode_data->vis_soft, flag);
    d_vis_set_focusable(video_mode_data->vis_user, flag);
    d_vis_set_focusable(video_mode_data->vis_bright, flag);
    if(!flag)
    {
        if(video_mode_data->video_mode_focus_flag  != 1)d_vis_enable(video_mode_data->vis_standard, D_TRUE);
        if(video_mode_data->video_mode_focus_flag  != 2)d_vis_enable(video_mode_data->vis_soft, D_TRUE);
        if(video_mode_data->video_mode_focus_flag  != 3)d_vis_enable(video_mode_data->vis_user, D_TRUE);
        if(video_mode_data->video_mode_focus_flag  != 4)d_vis_enable(video_mode_data->vis_bright, D_TRUE);
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_video_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_video_mode_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    if(video_mode_data->first_flag == D_TRUE)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        video_mode_data->video_mode_focus_flag = video_mode_data->video_mode + 1;
                        video_mode_data->video_mode_focus_flag = D_MIN(video_mode_data->video_mode_focus_flag, VIDEO_MODE_BUTTON_NUM);
                        video_mode_data->video_mode_focus_flag = D_MAX(video_mode_data->video_mode_focus_flag, 1);
                        vis = d_frame_get_control(frm, ID_VIDEOMODE_GROUP_BACKGROUND);
                        if(vis)
                        {
                            d_vis_enable(vis, D_TRUE);
                        }
                        set_button_enable(D_TRUE);
                        set_vis_focus(video_mode_data->video_mode_focus_flag);
                        video_mode_data->first_flag = D_FALSE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(video_mode_data->first_flag == D_FALSE)
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        vis = d_frame_get_control(frm, ID_VIDEOMODE_GROUP_BACKGROUND);
                        if(vis)
                        {
                            d_vis_enable(vis, D_FALSE);
                            set_button_enable(D_FALSE);
                        }
                        if(video_mode_data->video_mode_focus_flag - 1 != video_mode_data->video_mode)
                        {
                            video_mode_data->video_mode = video_mode_data->video_mode_focus_flag - 1;
                            p_tvconf_set_cur_imagemode(&video_mode_data->video_mode, p_vip_get_dbinput(video_mode_data->input));
                        }
                        video_mode_data->first_flag = D_TRUE;
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
                    video_mode_data->video_mode_focus_flag --;
                    if(video_mode_data->video_mode_focus_flag == 0)
                    {
                        video_mode_data->video_mode_focus_flag = VIDEO_MODE_BUTTON_NUM;
                    }
                    set_vis_focus(video_mode_data->video_mode_focus_flag);
                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    video_mode_data->video_mode_focus_flag ++;
                    if(video_mode_data->video_mode_focus_flag > VIDEO_MODE_BUTTON_NUM)
                    {
                        video_mode_data->video_mode_focus_flag = 1;
                    }
                    set_vis_focus(video_mode_data->video_mode_focus_flag);

                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(video_mode_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(video_mode_data->first_flag == D_TRUE)
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
            if(video_mode_data)
            {
                if(video_mode_data->video_mode_focus_flag - 1 != video_mode_data->video_mode)
                {
                    video_mode_data->video_mode = video_mode_data->video_mode_focus_flag - 1;
                    p_tvconf_set_cur_imagemode(&video_mode_data->video_mode, p_vip_get_dbinput(video_mode_data->input));
                }

                PROJECT_FREE(video_mode_data);
                video_mode_data = NULL;
            }
        }
        break;


        default:
            break;
    }
}

D_Result
atv_video_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;

    video_mode_data = (D_ImageVideoModeData*)PROJECT_ALLOC(sizeof(D_ImageVideoModeData));
    if(!video_mode_data)
    {
        return D_ERR;
    }
    memset(video_mode_data, 0, sizeof(D_ImageVideoModeData));

    video_mode_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_imagemode(&video_mode_data->video_mode, p_vip_get_dbinput(video_mode_data->input));
    video_mode_data->video_mode_focus_flag = video_mode_data->video_mode + 1;
    video_mode_data->video_mode_focus_flag = D_MIN(video_mode_data->video_mode_focus_flag, VIDEO_MODE_BUTTON_NUM);
    video_mode_data->video_mode_focus_flag = D_MAX(video_mode_data->video_mode_focus_flag, 1);
    video_mode_data->first_flag = D_TRUE;
    video_mode_data->ntsc_flag = p_vip_get_ntscflag();
    vis = d_frame_get_control(frm, ID_VIDEOMODE_BUTTON_STANDARD); //标准
    if(vis)
    {
        video_mode_data->vis_standard = vis;
        d_vis_set_handler (video_mode_data->vis_standard, button_standard_handler);
    }

    vis = d_frame_get_control(frm, ID_VIDEOMODE_BUTTON_SOFT);//柔和
    if(vis)
    {
        video_mode_data->vis_soft = vis;
        d_vis_set_handler (video_mode_data->vis_soft, button_soft_handler);
    }

    vis = d_frame_get_control(frm, ID_VIDEOMODE_BUTTON_USER);//用户
    if(vis)
    {
        video_mode_data->vis_user = vis;
        d_vis_set_handler (video_mode_data->vis_user, button_user_handler);
    }

    vis = d_frame_get_control(frm, ID_VIDEOMODE_BUTTON_BRIGHT);//明亮
    if(vis)
    {
        video_mode_data->vis_bright = vis;
        d_vis_set_handler (video_mode_data->vis_bright, button_bright_handler);
    }

    vis = d_frame_get_control(frm, ID_VIDEOMODE_GROUP_BACKGROUND);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        set_button_enable(D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_video_mode_window_handler);
    }


    return D_OK;
}

/** @brief 显示图像模式菜单*/
D_Result
p_atv_video_mode_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_video_mode_window, D_FALSE);
}

