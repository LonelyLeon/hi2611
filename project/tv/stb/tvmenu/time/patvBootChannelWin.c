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
#include "atv_boot_ch_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

typedef struct
{
    D_Char strnum[10];
    D_S16   progress_val;
    D_S16   sub_chan;    
	D_U32   chan_cnt;
    D_U32    menu_show_time;
	D_Bool first_flag;
} D_BootChannelData;

static D_BootChannelData *bootchannel_data = NULL;

static D_S16 get_boot_ch_num(void)
{
	D_S16 num;

	p_tvconf_get_boot_chan(&num);
	return num;
}

static void set_boot_ch_num(D_S16 ch_num)
{
    ch_num = (ch_num <= 0) ? (-1) : ch_num;
	p_tvconf_set_boot_chan(&ch_num);	
}


/** @brief 事件处理*/
static D_Result
boot_ch_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            //实现功能
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_boot_ch_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_boot_ch_window;
    D_Visual *vis_button;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_BOOTCH_IMAGE_LEFT);
    right_vis = d_frame_get_control (frm, ID_BOOTCH_IMAGE_RIGHT);
    vis_button = d_frame_get_control(frm, ID_BOOTCH_BUTTON_CH);


    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
					if(bootchannel_data->first_flag == D_TRUE)
	                {
	                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    d_vis_enable(vis_button, D_TRUE);
	                    d_vis_set_focusable(vis_button, D_TRUE);
	                    d_vis_set_focus(vis_button);
						bootchannel_data->first_flag = D_FALSE;
	                }
                break;

                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
					if(bootchannel_data->first_flag == D_FALSE)
	                {
	                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

	                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
	                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

	                    d_vis_enable(vis_button, D_FALSE);
	                    d_vis_set_focusable(vis_button, D_FALSE);
	                	bootchannel_data->first_flag = D_TRUE;
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
					if(bootchannel_data->chan_cnt == 0)
					{
						break;
					}

                    if(bootchannel_data->progress_val <= 0)
                    {
                        bootchannel_data->progress_val = 0;
                        break;
                    }
                    
                    bootchannel_data->progress_val --;
                    //set_boot_ch_num(bootchannel_data->progress_val);

                    if(bootchannel_data->progress_val <= 0)
                    {
                        sprintf(bootchannel_data->strnum, "off");
                    }  
                    else     
                    {
                        sprintf(bootchannel_data->strnum, "%d", bootchannel_data->progress_val);
                    }
                    
                    vis = d_frame_get_control(frm, ID_BOOTCH_BUTTON_CH);
                    if(vis)
                    {
                        d_button_set_text (vis, bootchannel_data->strnum);
                    }
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));
					if(bootchannel_data->chan_cnt == 0)
					{
						break;
					}

					if(bootchannel_data->progress_val >= bootchannel_data->chan_cnt)
					{
					    bootchannel_data->progress_val = bootchannel_data->chan_cnt;
						break;
					}
					bootchannel_data->progress_val ++;
                    //set_boot_ch_num(bootchannel_data->progress_val);
                    sprintf(bootchannel_data->strnum, "%d", bootchannel_data->progress_val);
                    vis = d_frame_get_control(frm, ID_BOOTCH_BUTTON_CH); //预约频道
                    if(vis)
                    {
                        d_button_set_text (vis, bootchannel_data->strnum);
                    }
                }
                break;
				case D_KEY_UP:
                case D_KEY_PNL_U:
				case D_KEY_DOWN:
                case D_KEY_PNL_D:
					if(bootchannel_data->first_flag == D_FALSE)
					{
						return D_OK;
					}
					else if(bootchannel_data->first_flag == D_TRUE)
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
            if(bootchannel_data)
            {
                if(bootchannel_data->sub_chan != bootchannel_data->progress_val)
                {
                    set_boot_ch_num(bootchannel_data->progress_val);
                }
                PROJECT_FREE(bootchannel_data);
                bootchannel_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_boot_ch_window_init(D_Frame *frm)
{
    D_Visual *vis;

    bootchannel_data = (D_BootChannelData*)PROJECT_ALLOC(sizeof(D_BootChannelData));
    if(!bootchannel_data)
    {
        return D_ERR;
    }
    memset(bootchannel_data, 0x00, sizeof(D_BootChannelData));
	bootchannel_data->first_flag = D_TRUE;
    bootchannel_data->chan_cnt = d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_ATV);	
	if(bootchannel_data->chan_cnt == 0)
	{
		set_boot_ch_num(-1);
	}
    
    bootchannel_data->progress_val = get_boot_ch_num();
    if(bootchannel_data->progress_val <= 0)
    {
        bootchannel_data->progress_val = 0;
        sprintf(bootchannel_data->strnum, "off");
    }
    else
    {
        bootchannel_data->progress_val = D_MIN(bootchannel_data->chan_cnt, bootchannel_data->progress_val);
        sprintf(bootchannel_data->strnum, "%d", bootchannel_data->progress_val);
    }
    
	bootchannel_data->sub_chan = bootchannel_data->progress_val;
    
    vis = d_frame_get_control(frm, ID_BOOTCH_BUTTON_CH); //开机频道
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_button_set_text (vis, bootchannel_data->strnum);
        d_vis_set_handler (vis, boot_ch_button_handler);
    }

	vis = d_frame_get_control (frm, ID_BOOTCH_GROUP_BG);
	if(vis)
	{	
		d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
	}

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~ D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_boot_ch_window_handler);
    }
    return D_OK;
}

/** @brief 显示开机频道菜单*/
D_Result
p_atv_boot_ch_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_boot_ch_window, D_FALSE);
}

