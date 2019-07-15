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
#include "atv_round_sound_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define ROUND_BUTTON_NUM 2

#define ID_ROUND_BUTTON_ON  2
#define ID_ROUND_BUTTON_OFF 3

typedef struct
{
    D_S16   round_flag;
    D_Bool  first_flag;
    D_VidInput input;
    D_Visual *vis_on, *vis_off;

} D_VoiceRoundData;

static D_VoiceRoundData *round_data = NULL;

/*取得参数*/
static D_U8 atv_round_get_param(void)D_FUNCPOSTFIT
{
    D_U8        round;//环绕声
    /*取得参数*/
    p_tvconf_get_cur_round(&round, p_vip_get_dbinput(round_data->input));
    return round;
}

/*保存参数*/
static D_Result atv_round_save_param(D_S16 flag)D_FUNCPOSTFIT
{
    D_U8        round = flag;//环绕声
    /*取得参数*/
    p_tvconf_set_cur_round(&round, p_vip_get_dbinput(round_data->input));
    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_round_set_param(D_S16 flag)D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_av_audio_srs(0,D_Surround_open);
            break;
        case 1:
            d_av_audio_srs(0,D_Surround_close);
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 开按钮事件处理*/
static D_Result
button_on_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i;
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!round_data->first_flag && round_data->round_flag == 0)
            {
                atv_round_set_param(round_data->round_flag);
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

/** @brief 关按钮事件处理*/
static D_Result
button_off_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i, max;
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!round_data->first_flag && round_data->round_flag == 1)
            {
                atv_round_set_param(round_data->round_flag);
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

/** @brief 设置按钮是否可用和是否可聚焦*/
static D_Result
set_button_enable (D_Bool flag) D_FUNCPOSTFIT
{
    d_vis_enable(round_data->vis_on, flag);
    d_vis_enable(round_data->vis_off, flag);

    d_vis_set_focusable(round_data->vis_on, flag);
    d_vis_set_focusable(round_data->vis_off, flag);
    if(!flag)
    {
        if(round_data->round_flag  != 0)d_vis_enable(round_data->vis_on, D_TRUE);
        if(round_data->round_flag  != 1)d_vis_enable(round_data->vis_off, D_TRUE);
    }
    return D_OK;
}

/** @brief 设置按钮的焦点*/
static D_Result
set_vis_focus (D_S16 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_vis_set_focus(round_data->vis_on);
            break;
        case 1:
            d_vis_set_focus(round_data->vis_off);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_round_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_round_window;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_ROUND_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_ROUND_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
					if(round_data->first_flag == D_TRUE)
	                {
	                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    vis = d_frame_get_control(frm, ID_ROUND_GROUP_BG);
	                    if(vis)
	                    {
	                        d_vis_enable(vis, D_TRUE);
	                    }
	                    set_button_enable(D_TRUE);
	                    set_vis_focus(round_data->round_flag);
	                    round_data->first_flag = D_FALSE;
	                }
	                break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(round_data->first_flag == D_FALSE)
	                {
	                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    vis = d_frame_get_control(frm, ID_ROUND_GROUP_BG);
	                    if(vis)
	                    {
	                        d_vis_enable(vis, D_FALSE);
	                        set_button_enable(D_FALSE);
	                    }

	                    atv_round_save_param(!round_data->round_flag);
	                    round_data->first_flag = D_TRUE;
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

                    round_data->round_flag = (round_data->round_flag + ROUND_BUTTON_NUM - 1) % ROUND_BUTTON_NUM;
                    set_vis_focus(round_data->round_flag);

                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

                    round_data->round_flag = (round_data->round_flag + 1) % ROUND_BUTTON_NUM;
                    set_vis_focus(round_data->round_flag);
                }
                break;
				case D_KEY_UP:
                case D_KEY_PNL_U:
				case D_KEY_DOWN:
                case D_KEY_PNL_D:
					if(round_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(round_data->first_flag == D_TRUE)
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
            atv_round_save_param(!round_data->round_flag);
            if(round_data)
            {
                //保存参数
                PROJECT_FREE(round_data);
                round_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_round_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    round_data = (D_VoiceRoundData*)PROJECT_ALLOC(sizeof(D_VoiceRoundData));
    if(!round_data)
    {
        return D_ERR;
    }
    memset(round_data, 0x00, sizeof(D_VoiceRoundData));
    round_data->input = p_conf_get_vid_input();

    //取出参数的设置
    round_data->round_flag = !(D_S16)atv_round_get_param();
    round_data->first_flag = D_TRUE;

    round_data->vis_on = d_frame_get_control(frm, ID_ROUND_BUTTON_ON); //开
    round_data->vis_off = d_frame_get_control(frm, ID_ROUND_BUTTON_OFF);//关

    d_vis_set_handler (round_data->vis_on, button_on_handler);
    d_vis_set_handler (round_data->vis_off, button_off_handler);

    vis = d_frame_get_control(frm, ID_ROUND_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        set_button_enable(D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_round_window_handler);
    }

    return D_OK;
}

/** @brief 显示声音环绕声菜单*/
D_Result
p_atv_round_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_round_window, D_FALSE);
}

