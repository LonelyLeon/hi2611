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
#include "picture_optimize_setting_window.c"

static void (*reset_upper_menu_timer)(void) D_FUNCPOSTFIT;

typedef struct
{
    D_U8          value;
    D_U8          selet_val;
    D_VidInput input;
    D_U8          hdflag;
    D_U8          progflag;
} D_PictureOptimize;

static D_PictureOptimize *picture_optimize_info;


static void set_nr(D_U8 input, D_U8 val, D_U8 flag) D_FUNCPOSTFIT
{
    D_NR_SET param;

    if(flag)
    {
        if(p_tvconf_get_hdnr_set_param(&param, input, val) == D_OK)
        {
            d_vip_setNr((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_nr_set_param(&param, input, val) == D_OK)
        {
            d_vip_setNr((D_U8*)&param);
        }
    }
	if(picture_optimize_info->progflag)
		d_vip_setNr_Prog(val);
}
static D_Result
atv_picture_optimize_select_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            picture_optimize_info->selet_val = (D_U8)(D_U16)d_select_box_get_val(vis);
            set_nr(p_vip_get_dbinput(picture_optimize_info->input), picture_optimize_info->selet_val, picture_optimize_info->hdflag );

            break;
        default:
            break;
    }


    return D_ERR;
}



/** @brief 事件处理*/
static D_Result
atv_picture_optimize_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_MENU:
				case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                {
                    return d_gui_upper_menu();
                }
                break;
                case D_KEY_ESC:
                    return d_gui_clear_menu();

                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);

            if(picture_optimize_info)
            {
                if(picture_optimize_info->value != picture_optimize_info->selet_val )
                {
                    p_tvconf_set_cur_nrmode  (&picture_optimize_info->selet_val , p_vip_get_dbinput(picture_optimize_info->input) );
                }
                PROJECT_FREE(picture_optimize_info);
                picture_optimize_info = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
picture_optimize_setting_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U8 val;

    picture_optimize_info = (D_PictureOptimize*)PROJECT_ALLOC(sizeof(D_PictureOptimize));
    if(!picture_optimize_info)
    {
        return D_ERR;
    }
    memset(picture_optimize_info, 0x00, sizeof(D_PictureOptimize));
	
    picture_optimize_info->hdflag = 0; //高清还是标清标志
    picture_optimize_info->value = 0;
    picture_optimize_info->input = p_conf_get_vid_input();	
    if(picture_optimize_info->input == D_VID_IUTPUT_AV1|| picture_optimize_info->input == D_VID_IUTPUT_AV2 || picture_optimize_info->input == D_VID_IUTPUT_TV)
	{
		picture_optimize_info->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		picture_optimize_info->hdflag = p_vip_get_hdflag();
	}
    if(p_tvconf_get_cur_nrmode  (&val, p_vip_get_dbinput(picture_optimize_info->input) ) == D_OK )
    {
        picture_optimize_info->value = val;
    }
    picture_optimize_info->selet_val = picture_optimize_info->value;
	picture_optimize_info->progflag = p_vip_get_progflag();
    vis = d_frame_get_control (frm, ID_PICTURE_OPTIMIZE_SELECT_SPEED);
    if(vis)
    {
        d_vis_set_handler (vis, atv_picture_optimize_select_handler);
        d_select_box_set_val(vis, picture_optimize_info->selet_val);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_picture_optimize_window_handler);
    }

    return D_OK;
}

/** @brief 显示图像优化菜单*/
D_Result
p_atv_picture_optimize_show (void (*pFunc)()) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&picture_optimize_setting_window, D_FALSE);
}

