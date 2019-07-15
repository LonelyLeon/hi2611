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
#include "atv_digit_timbre_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define DIGIT_TIMBRE_BUTTON_NUM 4

typedef struct
{
    D_U8  mode;
    D_U16 nfft;
    D_Bool first_flag;
    D_VidInput input;
    D_Visual *vis_user, *vis_standard, *vis_music, *vis_movie;
    D_AUDIO_Peq param[TV_AUDIO_FEQ];
} D_DigitalData;

static D_DigitalData *digital_data = NULL;

/*取得参数*/
static D_Result atv_digit_adjust_get_param(void)D_FUNCPOSTFIT
{
    p_tvconf_get_cur_audiomode(&digital_data->mode, p_vip_get_dbinput(digital_data->input));
    return D_OK;
}

/*保存参数*/
static D_Result atv_digit_adjust_save_param(D_U8 flag)D_FUNCPOSTFIT
{
    p_tvconf_set_cur_audiomode(&flag, p_vip_get_dbinput(digital_data->input));

    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_digit_adjust_set_param(void)D_FUNCPOSTFIT
{
	D_U8 i;

	for(i = 0; i < TV_AUDIO_FEQ ; i++)
	{
		p_tvconf_get_audio_peq_set_param(&digital_data->param[i],p_vip_get_dbinput(digital_data->input),digital_data->mode,i);

	}
	p_tvconf_get_cur_t_ffft(&digital_data->nfft, p_vip_get_dbinput(digital_data->input),digital_data->mode);
#ifdef D_TV_IAMGE_SOURCE	
	d_av_Audio_PEQ(0, digital_data->param, TV_AUDIO_FEQ, digital_data->nfft, D_Digital_Audio);
#else	
	if(digital_data->mode == 0)
	{
		d_av_Audio_PEQ(0, digital_data->param, 5, digital_data->nfft, D_PEQ);
	}
	else
	{
		d_av_Audio_PEQ(0, digital_data->param, 9, digital_data->nfft, D_Digital_Audio);	
	}
#endif	
	return D_OK;
}

/** @brief  用户事件处理*/
static D_Result
button_user_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i;
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!digital_data->first_flag && digital_data->mode == 1)
            {
                atv_digit_adjust_set_param();
            }
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
#if HI_P_TV_MENU_SHOW_EN
            p_tvconf_set_cur_audiomode(&digital_data->mode, p_vip_get_dbinput(digital_data->input));
            p_atv_digit_timbre_show(D_TRUE);
#endif
            break;

        default:
            break;
    }
    return D_OK;
}

/** @brief  音乐事件处理*/
static D_Result
button_music_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i;

    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!digital_data->first_flag && digital_data->mode == 2)
            {
                atv_digit_adjust_set_param();
            }
            break;
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
#if HI_P_TV_MENU_SHOW_EN
            p_tvconf_set_cur_audiomode(&digital_data->mode, p_vip_get_dbinput(digital_data->input));
            p_atv_digit_timbre_show(D_TRUE);
#endif
            break;

        default:
            break;
    }
    return D_OK;
}

/** @brief  电影事件处理*/
static D_Result
button_movie_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i;

    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!digital_data->first_flag && digital_data->mode == 3)
            {
                atv_digit_adjust_set_param();
            }
            break;
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
#if HI_P_TV_MENU_SHOW_EN
            p_tvconf_set_cur_audiomode(&digital_data->mode, p_vip_get_dbinput(digital_data->input));
            p_atv_digit_timbre_show(D_TRUE);
#endif
            break;

        default:
            break;
    }
    return D_OK;
}


/** @brief  标准事件处理*/
static D_Result
button_standard_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 i;

    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(!digital_data->first_flag && digital_data->mode == 0)
            {
                atv_digit_adjust_set_param();
            }
            break;
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
#if HI_P_TV_MENU_SHOW_EN
            p_tvconf_set_cur_audiomode(&digital_data->mode, p_vip_get_dbinput(digital_data->input));
            p_atv_digit_timbre_show(D_TRUE);
#endif        
            break;

        default:
            break;
    }
    return D_OK;
}


/** @brief 设置按钮是否可用和是否可聚焦*/
static D_Result
set_button_enable (D_Bool mode) D_FUNCPOSTFIT
{
    d_vis_enable(digital_data->vis_standard, mode);
    d_vis_enable(digital_data->vis_user, mode);
    d_vis_enable(digital_data->vis_music, mode);
    d_vis_enable(digital_data->vis_movie, mode);

    d_vis_set_focusable(digital_data->vis_standard, mode);
    d_vis_set_focusable(digital_data->vis_user, mode);
    d_vis_set_focusable(digital_data->vis_music, mode);
    d_vis_set_focusable(digital_data->vis_movie, mode);
    if(!mode)
    {
        if(digital_data->mode  != 0)d_vis_enable(digital_data->vis_standard, D_TRUE);
        if(digital_data->mode  != 1)d_vis_enable(digital_data->vis_user, D_TRUE);
        if(digital_data->mode  != 2)d_vis_enable(digital_data->vis_music, D_TRUE);
        if(digital_data->mode  != 3)d_vis_enable(digital_data->vis_movie, D_TRUE);
   }	
    return D_OK;
}

/** @brief 设置按钮的焦点*/
static D_Result
set_vis_focus (D_S16 mode) D_FUNCPOSTFIT
{
    switch(mode)
    {
        case 0:
            d_vis_set_focus(digital_data->vis_standard);
            break;
        case 1:
            d_vis_set_focus(digital_data->vis_user);
            break;
        case 2:
            d_vis_set_focus(digital_data->vis_music);
            break;
        case 3:
            d_vis_set_focus(digital_data->vis_movie);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_digit_timbre_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_digit_timbre_window;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_DIGIT_TIMBRE_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_DIGIT_TIMBRE_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
			{
				switch (evt->fp.key)
				{
					case D_KEY_OK:
					case D_KEY_PNL_SOURCE:
						if(digital_data->first_flag == D_TRUE)
						{
							d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
							d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
							d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));


							vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_GROUP_BG);
							if(vis)
							{
								d_vis_enable(vis, D_TRUE);
							}
							set_button_enable(D_TRUE);
							set_vis_focus(digital_data->mode);
							digital_data->first_flag = D_FALSE;
						}
						break;
					case D_KEY_BACK:
					case D_KEY_PNL_MENU:
						if(digital_data->first_flag == D_FALSE)
						{
							d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

							d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
							d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

							vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_GROUP_BG);
							if(vis)
							{
								d_vis_enable(vis, D_FALSE);
								set_button_enable(D_FALSE);
							}
							atv_digit_adjust_save_param(digital_data->mode);
							digital_data->first_flag = D_TRUE;
						}
						else //if(evt->fp.key != D_KEY_BACK)
						{
							d_gui_clear_menu();
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

							digital_data->mode = (digital_data->mode + DIGIT_TIMBRE_BUTTON_NUM - 1) % DIGIT_TIMBRE_BUTTON_NUM;
							set_vis_focus(digital_data->mode);

						}
						break;
					case D_KEY_RIGHT:
					case D_KEY_PNL_R:
						{
							d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
							d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

							digital_data->mode = (digital_data->mode + 1) % DIGIT_TIMBRE_BUTTON_NUM;
							set_vis_focus(digital_data->mode);
						}
						break;
					case D_KEY_UP:
	                case D_KEY_PNL_U:
					case D_KEY_DOWN:
	                case D_KEY_PNL_D:
						if(digital_data->first_flag == D_FALSE)
						{
							return D_OK;
						}
						else if(digital_data->first_flag == D_TRUE)
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
				if(digital_data)
				{
					//保存参数
					atv_digit_adjust_save_param(digital_data->mode);
					PROJECT_FREE(digital_data);
					digital_data = NULL;
				}
			}
			break;
        default:
            break;
    }
}

D_Result
atv_digit_timbre_window_init(D_Frame *frm)
{
    D_Visual *vis;

    digital_data = (D_DigitalData*)PROJECT_ALLOC(sizeof(D_DigitalData));
    if(!digital_data)
    {
        return D_ERR;
    }
    memset(digital_data, 0x00, sizeof(D_DigitalData));

    digital_data->input = p_conf_get_vid_input();

    atv_digit_adjust_get_param();
    digital_data->first_flag = D_TRUE;

    digital_data->vis_user = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_USER); //用户

    digital_data->vis_user = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_USER); //用户
    digital_data->vis_standard = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_STANDARD);//标准
    digital_data->vis_music = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_MUSIC); //音乐
    digital_data->vis_movie = d_frame_get_control(frm, ID_DIGIT_TIMBRE_BUTTON_MOVIE);//电影

    d_vis_set_handler (digital_data->vis_user, button_user_handler);
    d_vis_set_handler (digital_data->vis_standard, button_standard_handler);
    d_vis_set_handler (digital_data->vis_music, button_music_handler);
    d_vis_set_handler (digital_data->vis_movie, button_movie_handler);


    set_vis_focus(digital_data->mode);
    vis = d_frame_get_control(frm, ID_DIGIT_TIMBRE_GROUP_BG);
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
        d_vis_set_handler (vis, atv_digit_timbre_window_handler);
    }

    return D_OK;
}

/** @brief 数字音质菜单*/
D_Result
p_atv_digital_adjust_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_digit_timbre_window, D_FALSE);
}

