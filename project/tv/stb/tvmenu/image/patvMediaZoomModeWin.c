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
#include "atv_media_zoom_mode_window.c"
#include "dAV.h"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define MDEIA_ZOOM_MODE_BUTTON_NUM 2

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_fulltrue_left_normal = { -1, atv_IMG_ID_COMB_button_menu, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_fulltrue_left_focus = { -1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_fulltrue_left_failure = { -1, atv_IMG_ID_COMB_button_menu, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_grey, };

static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_fulltrue_true = {{&GUID_fulltrue_left_normal, &GUID_fulltrue_left_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_fulltrue_false = {{&GUID_fulltrue_left_normal, &GUID_fulltrue_left_focus, &GUID_fulltrue_left_failure, }, 1, };

typedef struct
{
    D_S16 zoom_mode_focus_flag;
    D_Bool first_flag;
    D_S16    zoom_mode;
    D_Visual    *vis_fullscr, *vis_originality;
    D_VidInput input;
} D_ImageZoomModeData;

static D_ImageZoomModeData *zoom_mode_data = NULL;

/*取得参数*/
static D_U8 atv_zoom_round_get_param(void)D_FUNCPOSTFIT
{
    /*取得参数*/
    D_U8 mode;

    p_tvconf_get_cur_zoommode(&mode, p_vip_get_dbinput(zoom_mode_data->input));
    if(mode > 1)
        mode = 1;
    return mode;
}

/*保存参数*/
static D_Result atv_zoom_round_save_param(D_S16 mode)D_FUNCPOSTFIT
{
    /*保存参数*/
    p_tvconf_set_cur_zoommode(&mode, p_vip_get_dbinput(zoom_mode_data->input) );

    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_zoom_round_set_param(D_tv_Display_Ratio_t ratio_mode)D_FUNCPOSTFIT
{
    d_av_set_tv_ratio_mode(0, ratio_mode);

    return D_OK;
}
/** @brief 满屏按钮事件处理*/
static D_Result
button_fullscr_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(zoom_mode_data->zoom_mode_focus_flag == 1 && !zoom_mode_data->first_flag)
                atv_zoom_round_set_param(D_Full_Screen);
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

/** @brief 自动按钮事件处理*/
static D_Result
button_originality_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            if(zoom_mode_data->zoom_mode_focus_flag == 2  && !zoom_mode_data->first_flag)
                atv_zoom_round_set_param(D_NATURAL_RATIO);
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
    D_Ptr pattr;

    d_vis_enable(zoom_mode_data->vis_fullscr, flag);
    d_vis_set_focusable(zoom_mode_data->vis_fullscr, flag);

    d_vis_enable(zoom_mode_data->vis_originality, flag);
    d_vis_set_focusable(zoom_mode_data->vis_originality, flag);
    if(!flag)
    {
        if(zoom_mode_data->zoom_mode_focus_flag != 1)d_vis_enable(zoom_mode_data->vis_fullscr, D_TRUE);
        if(zoom_mode_data->zoom_mode_focus_flag != 2)d_vis_enable(zoom_mode_data->vis_originality, D_TRUE);
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
            d_vis_set_focus(zoom_mode_data->vis_fullscr);
            break;
        case 2:
            d_vis_set_focus(zoom_mode_data->vis_originality);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_media_zoom_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_media_zoom_mode_window;
    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_MDEIA_ZOOM_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_MDEIA_ZOOM_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                if(zoom_mode_data->first_flag == D_TRUE)
                {
                    d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    vis = d_frame_get_control(frm, ID_MDEIA_ZOOM_GROUP_BG);
                    if(vis)
                    {
                        d_vis_enable(vis, D_TRUE);
                    }

                    set_button_enable(D_TRUE);
                    set_vis_focus(zoom_mode_data->zoom_mode_focus_flag);
                    zoom_mode_data->first_flag = D_FALSE;
                }
                break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                if(zoom_mode_data->first_flag == D_FALSE)
                {
                    d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    vis = d_frame_get_control(frm, ID_MDEIA_ZOOM_GROUP_BG);
                    if(vis)
                    {
                        d_vis_enable(vis, D_FALSE);
                        set_button_enable(D_FALSE);
                    }
                    if(zoom_mode_data->zoom_mode_focus_flag - 1 != zoom_mode_data->zoom_mode)
                    {
                        zoom_mode_data->zoom_mode = zoom_mode_data->zoom_mode_focus_flag - 1;
                        atv_zoom_round_save_param(zoom_mode_data->zoom_mode);
                    }
                    zoom_mode_data->first_flag = D_TRUE;
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

                    zoom_mode_data->zoom_mode_focus_flag --;
                    if(zoom_mode_data->zoom_mode_focus_flag == 0)
                    {
                        zoom_mode_data->zoom_mode_focus_flag = MDEIA_ZOOM_MODE_BUTTON_NUM;
                    }
                    set_vis_focus(zoom_mode_data->zoom_mode_focus_flag);
                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

                    zoom_mode_data->zoom_mode_focus_flag ++;
                    if(zoom_mode_data->zoom_mode_focus_flag > MDEIA_ZOOM_MODE_BUTTON_NUM)
                    {
                        zoom_mode_data->zoom_mode_focus_flag = 1;
                    }
                    set_vis_focus(zoom_mode_data->zoom_mode_focus_flag);
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
            if(zoom_mode_data)
            {
                if(zoom_mode_data->zoom_mode_focus_flag - 1 != zoom_mode_data->zoom_mode)
                {
                    zoom_mode_data->zoom_mode = zoom_mode_data->zoom_mode_focus_flag - 1;
                    atv_zoom_round_save_param(zoom_mode_data->zoom_mode);
                }
                PROJECT_FREE(zoom_mode_data);
                zoom_mode_data = NULL;
            }
        }
        break;

        default:
            break;
    }
}

D_Result
atv_media_zoom_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;

    zoom_mode_data = (D_ImageZoomModeData*)PROJECT_ALLOC(sizeof(D_ImageZoomModeData));
    if(!zoom_mode_data)
    {
        return D_ERR;
    }
    memset(zoom_mode_data, 0, sizeof(D_ImageZoomModeData));

    zoom_mode_data->input = p_conf_get_vid_input();
    zoom_mode_data->zoom_mode = atv_zoom_round_get_param();
    zoom_mode_data->zoom_mode_focus_flag = zoom_mode_data->zoom_mode + 1;
    zoom_mode_data->first_flag = D_TRUE;

    zoom_mode_data->vis_fullscr = d_frame_get_control(frm, ID_MDEIA_ZOOM_BUTTON_FULL_SCREEN); //满屏
    zoom_mode_data->vis_originality = d_frame_get_control(frm, ID_MDEIA_ZOOM_BUTTON_AUTO); //自动

    d_vis_set_handler (zoom_mode_data->vis_fullscr, button_fullscr_handler);
    d_vis_set_handler (zoom_mode_data->vis_originality, button_originality_handler);


    vis = d_frame_get_control(frm, ID_MDEIA_ZOOM_GROUP_BG);
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
        d_vis_set_handler (vis, atv_media_zoom_mode_window_handler);
    }

    return D_OK;
}

/** @brief 显示缩放模式菜单*/
D_Result
p_atv_media_zoom_mode_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_media_zoom_mode_window, D_FALSE);
}
