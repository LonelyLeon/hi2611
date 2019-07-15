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
#include "atv_digital_noise_window.c"


extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

typedef struct
{
    D_U32    menu_show_time;
	D_Bool first_flag;
} D_DigitalNoiseData;

static D_DigitalNoiseData *digitalnoise_data = NULL;

/** @brief 确定降噪事件处理*/
static D_Result
button_digital_noise_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            p_atv_picture_optimize_show(NULL);
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_digital_noise_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_digital_noise_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_DIGNOISE_BUTTON_REDUCTION);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
					if(digitalnoise_data->first_flag == D_TRUE)
					{
						d_vis_enable(vis_button, D_TRUE);
                    	d_vis_set_focusable(vis_button, D_TRUE);
                    	d_vis_set_focus(vis_button);

						digitalnoise_data->first_flag = D_FALSE;
					}
                    else
                    {
                        p_atv_picture_optimize_show(NULL);
                    }
                   
                    break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(digitalnoise_data->first_flag == D_FALSE)
	                {
	                    d_vis_enable(vis_button, D_FALSE);
	                    d_vis_set_focusable(vis_button, D_FALSE);

						digitalnoise_data->first_flag = D_TRUE;
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
					if(digitalnoise_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(digitalnoise_data->first_flag == D_TRUE)
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
            if(digitalnoise_data)
            {
                PROJECT_FREE(digitalnoise_data);
                digitalnoise_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_digital_noise_window_init(D_Frame *frm)
{
    D_Visual *vis;

    digitalnoise_data = (D_DigitalNoiseData*)PROJECT_ALLOC(sizeof(D_DigitalNoiseData));
    if(!digitalnoise_data)
    {
        return D_ERR;
    }
    memset(digitalnoise_data, 0x00, sizeof(D_DigitalNoiseData));

	digitalnoise_data->first_flag = D_TRUE;
    vis = d_frame_get_control(frm, ID_DIGNOISE_BUTTON_REDUCTION); //确定降噪
    if(vis)
    {
        d_vis_set_handler (vis, button_digital_noise_handler);
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
    }

	vis = d_frame_get_control(frm, ID_DIGNOISE_GROUP_BG);
	if(vis)
	{
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
	}

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_digital_noise_window_handler);
    }
    return D_OK;
}

/** @brief 数字降噪菜单*/
D_Result
p_atv_digital_noise_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_digital_noise_window, D_FALSE);
}

