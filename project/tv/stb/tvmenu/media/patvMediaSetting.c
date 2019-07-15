#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "media_setting_window.c"
#include "pConfig.h"

#define SPEED_FAST       4*1000
#define SPEED_NORMAL     8*1000
#define SPEED_LOW        12*1000

static D_U16 select_flag = 0;
static D_U8 settingLang;

D_MSec get_media_pic_speed_flag(void)D_FUNCPOSTFIT
{
    if(select_flag == 2)//高
    {
        return SPEED_FAST;
    }
    else if(select_flag == 1)//中
    {
        return SPEED_NORMAL;
    }
    else if(select_flag == 0)//低
    {
		return SPEED_LOW;
    }
}

/** @brief 事件处理*/
static D_Result
atv_media_setting_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame * frm = &media_setting_window;
    D_Visual * left_vis, *right_vis, *select_vis, *vislang;

    left_vis = d_frame_get_control(frm, ID_SETTING_IMAGE_LEFT);
    right_vis = d_frame_get_control(frm, ID_SETTING_IMAGE_RIGHT);
    select_vis = d_frame_get_control(frm, ID_SETTING_SELECT_SPEED);

    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                vislang = d_frame_get_control(&media_setting_window, ID_SETTING_IMAGE_SETTING);
                if(vislang)
                {
                    if(D_LANG_CHN == evt->user.param1)
                    {
                        d_image_box_set_image(vislang, d_gui_get_image(atv_IMG_ID_title_setting));
                    }
                    else
                    {
                        d_image_box_set_image(vislang, d_gui_get_image(atv_IMG_ID_title_setting_en));
                    }
                }
                d_vis_update(vislang, NULL);
                d_gui_update();
            }
            break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    return D_OK;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_search_rightx));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_search_left));

                    if(select_flag == 0)
                    {
                        select_flag = 2;
                    }
                    else
                    {
                        select_flag = select_flag - 1;
                    }
                    d_select_box_set_val(select_vis, select_flag);
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_search_right));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_search_leftx));

                    if(select_flag == 2)
                    {
                        select_flag = 0;
                    }
                    else
                    {
                        select_flag = select_flag + 1;
                    }
                    d_select_box_set_val(select_vis, select_flag);
                    break;
                case  D_KEY_OK:
                case  D_KEY_PNL_OK:
                    break;
                default:
                    return D_ERR;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_SETUP;
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
media_setting_window_init(D_Frame *frm)
{
    D_Visual *vis;

    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_SETUP;

    vis = d_frame_get_control(frm, ID_SETTING_IMAGE_SETTING);
    if(vis)
    {
        settingLang = p_conf_get_lang();
        if(D_LANG_CHN == settingLang)
        {
            d_image_box_set_image(vis, d_gui_get_image(atv_IMG_ID_title_setting));
        }
        else
        {
            d_image_box_set_image(vis, d_gui_get_image(atv_IMG_ID_title_setting_en));
        }
    }

    vis = d_frame_get_control(frm, ID_SETTING_IMAGE_LEFT);
    if(vis)
    {
        d_image_box_set_image(vis, d_gui_get_image(atv_IMG_ID_search_rightx));
    }

    vis = d_frame_get_control(frm, ID_SETTING_SELECT_SPEED);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_select_box_set_val(vis, select_flag);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, atv_media_setting_window_handler);
    }

    return D_OK;
}



/** @brief 时钟菜单*/
D_Result
p_atv_media_setting_menu_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &media_setting_window, D_CLEAR_ALL);
}

