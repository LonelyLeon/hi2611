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
#include "media_main_menu_window.c"
#include "pConfig.h"

#define ATV_MEDIA_MENU_ITEM_CNT (6)

#if ((!defined(D_IUTPUT_SUPPORT_DTV)) ||(!defined(D_TV_SUPPORT_PVR)))
#define ACT_ATV_MEDIA_MENU_ITEM_CNT (3)
#else
#define ACT_ATV_MEDIA_MENU_ITEM_CNT (4)
#endif

#define ATV_MEDIA_MENU_ITEM_MOVIE (0)
#define ATV_MEDIA_MENU_ITEM_MUSIC (1)
#define ATV_MEDIA_MENU_ITEM_PHOTO (2)
#define ATV_MEDIA_MENU_ITEM_SETUP (3)
#define ATV_MEDIA_MENU_ITEM_EBOOK (4)
#define ATV_MEDIA_MENU_ITEM_PVR   (5)

#define BUTTON_POS_X_STEP (351)
#define BUTTON_POS_X (212)
#define BUTTON_POS_Y (442)
#define BUTTON_POS_W (152)
#define BUTTON_POS_H (112)

#define LABEL_POS_X_STEP (351)
#define LABEL_POS_X (252)
#define LABEL_POS_Y (569)
#define LABEL_POS_W (72)
#define LABEL_POS_H (26)

static D_U32 atv_meida_focus_id = 0;
D_U32 AtvMediaMenuStatus;
static D_U8 mediaLang;
static D_Visual * vis_item[ATV_MEDIA_MENU_ITEM_CNT];

#if ((!defined(D_IUTPUT_SUPPORT_DTV)) ||(!defined(D_TV_SUPPORT_PVR)))
D_U8 item_loop_order[ACT_ATV_MEDIA_MENU_ITEM_CNT] = {ATV_MEDIA_MENU_ITEM_MOVIE, ATV_MEDIA_MENU_ITEM_MUSIC, ATV_MEDIA_MENU_ITEM_PHOTO};
#else
D_U8 item_loop_order[ACT_ATV_MEDIA_MENU_ITEM_CNT] = {ATV_MEDIA_MENU_ITEM_MOVIE, ATV_MEDIA_MENU_ITEM_MUSIC, ATV_MEDIA_MENU_ITEM_PHOTO, ATV_MEDIA_MENU_ITEM_PVR};
#endif

/** @brief 事件处理*/
static D_Result
pvr_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            if(p_get_curr_usb_status())
            {
#if ((!defined(D_IUTPUT_SUPPORT_DTV)) ||(!defined(D_TV_SUPPORT_PVR)))
#else
                p_atv_media_pvr_show();
#endif
            }
            else
            {
                p_atv_media_prompt_msg(atv_IDS_NO_USB);
            }
        }
        break;

        default:
            break;
    }
    return D_OK;
}


/** @brief 事件处理*/
static D_Result
movie_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            if(p_get_curr_usb_status())
            {
                p_atv_media_movie_show();
            }
            else
            {
                p_atv_media_prompt_msg(atv_IDS_NO_USB);
            }
        }
        break;

        default:
            break;
    }
    return D_OK;
}


/** @brief 事件处理*/
static D_Result
music_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            if(p_get_curr_usb_status())
            {
                p_atv_media_music_show();
            }
            else
            {
                p_atv_media_prompt_msg(atv_IDS_NO_USB);
            }
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
picture_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            if(p_get_curr_usb_status())
            {
                p_atv_media_picture_show();
            }
            else
            {
                p_atv_media_prompt_msg(atv_IDS_NO_USB);
            }
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
ebook_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            if(p_get_curr_usb_status())
            {
                p_atv_media_ebook_show();
            }
            else
            {
                p_atv_media_prompt_msg(atv_IDS_NO_USB);
            }
        }
        break;

        default:
            break;
    }
    return D_OK;
}


/** @brief 事件处理*/
static D_Result
setting_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
            p_atv_media_setting_menu_show();
        }
        break;

        default:
            break;
    }
    return D_OK;
}


/** @brief 事件处理*/
static D_Result
media_main_menu_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    (atv_meida_focus_id == 0) ? (atv_meida_focus_id = ACT_ATV_MEDIA_MENU_ITEM_CNT - 1) : (atv_meida_focus_id--);
                    d_vis_set_focus(vis_item[item_loop_order[atv_meida_focus_id]]);
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    (atv_meida_focus_id == (ACT_ATV_MEDIA_MENU_ITEM_CNT - 1)) ? (atv_meida_focus_id = 0) : (atv_meida_focus_id++);
                    d_vis_set_focus(vis_item[item_loop_order[atv_meida_focus_id]]);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                D_Visual * vis1;

                vis1 = d_frame_get_control(&media_main_menu_window, ID_MAIN_MENU_IMAGE_MEDIA);
                if(vis1)
                {
                    if(D_LANG_CHN == evt->user.param2)
                    {
                        d_image_box_set_image(vis1, d_gui_get_image(atv_IMG_ID_title_usb));
                    }
                    else
                    {
                        d_image_box_set_image(vis1, d_gui_get_image(atv_IMG_ID_title_usb_en));
                    }
                    d_vis_update(vis1, NULL);
                    d_gui_update();
                }
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
                vis = d_frame_get_control(&media_main_menu_window, ID_MAINMENU_LABEL_USB_ICON);
                if(vis)
                {
                    d_vis_show(vis, D_FALSE );
                }
            }
            else
            {
                vis = d_frame_get_control(&media_main_menu_window, ID_MAINMENU_LABEL_USB_ICON);
                if(vis)
                {
                    d_vis_show(vis, D_TRUE);
                }
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_MAIN;
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
media_main_menu_window_init(D_Frame *frm)
{
    D_Visual * vis_movie, *vis_music, *vis_pic, *vis_pvr , *vis;

    vis = d_frame_get_control(frm, ID_MAIN_MENU_IMAGE_MEDIA);
    if(vis)
    {
        mediaLang = p_conf_get_lang();
        if(D_LANG_CHN == mediaLang)
        {
            d_image_box_set_image(vis, d_gui_get_image(atv_IMG_ID_title_usb));
        }
        else
        {
            d_image_box_set_image(vis, d_gui_get_image(atv_IMG_ID_title_usb_en));
        }
    }
    vis = d_frame_get_control(frm, ID_MAINMENU_LABEL_USB_ICON);
    if(vis)
    {
        if(p_get_curr_usb_status())
        {
            d_vis_show(vis, D_TRUE);
        }
        else
        {
            d_vis_show(vis, D_FALSE);
        }
    }
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_MAIN;

    vis_movie = d_frame_get_control(frm, ID_MAINMENU_BUTTON_MOVIE);
    if(vis_movie)
    {
        vis_item[ATV_MEDIA_MENU_ITEM_MOVIE] = vis_movie;
        d_vis_set_handler(vis_movie, movie_button_handler);
    }

    vis_music = d_frame_get_control(frm, ID_MAINMENU_BUTTON_MUSIC);
    if(vis_music)
    {
        vis_item[ATV_MEDIA_MENU_ITEM_MUSIC] = vis_music;
        d_vis_set_handler(vis_music, music_button_handler);
    }

    vis_pic = d_frame_get_control(frm, ID_MAINMENU_BUTTON_PICTURE);
    if(vis_pic)
    {
        vis_item[ATV_MEDIA_MENU_ITEM_PHOTO] = vis_pic;
        d_vis_set_handler(vis_pic, picture_button_handler);
    }

#if 0
    vis = d_frame_get_control(frm, ID_MAINMENU_BUTTON_EBOOK);
    if(vis)
    {
        vis_item[ATV_MEDIA_MENU_ITEM_EBOOK] = vis;
        d_vis_set_handler(vis, ebook_button_handler);
    }
#endif

    vis_pvr = d_frame_get_control(frm, ID_MAINMENU_BUTTON_PVR);
    if(vis_pvr)
    {
        vis_item[ATV_MEDIA_MENU_ITEM_PVR] = vis_pvr;
        d_vis_set_handler(vis_pvr, pvr_button_handler);
    }

#if ((!defined(D_IUTPUT_SUPPORT_DTV)) ||(!defined(D_TV_SUPPORT_PVR)))
    d_vis_show(vis_pvr, D_FALSE);
    vis = d_frame_get_control(frm, ID_MAINMENU_LABEL_PVR);
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    d_vis_set_pos(vis_movie, BUTTON_POS_X, BUTTON_POS_Y, BUTTON_POS_W, BUTTON_POS_H);
    d_vis_set_pos(vis_music, (BUTTON_POS_X + BUTTON_POS_X_STEP), BUTTON_POS_Y, BUTTON_POS_W, BUTTON_POS_H);
    d_vis_set_pos(vis_pic, (BUTTON_POS_X + BUTTON_POS_X_STEP * 2), BUTTON_POS_Y, BUTTON_POS_W, BUTTON_POS_H);

    d_vis_set_pos(d_frame_get_control(frm, ID_MAINMENU_LABEL_MOVIE), LABEL_POS_X, LABEL_POS_Y, LABEL_POS_W, LABEL_POS_H);
    d_vis_set_pos(d_frame_get_control(frm, ID_MAINMENU_LABEL_MUSIC), (LABEL_POS_X + LABEL_POS_X_STEP), LABEL_POS_Y, LABEL_POS_W, LABEL_POS_H);
    d_vis_set_pos(d_frame_get_control(frm, ID_MAINMENU_LABEL_PICTURE), (LABEL_POS_X + LABEL_POS_X_STEP * 2), LABEL_POS_Y, LABEL_POS_W, LABEL_POS_H);
#endif

    /*设定焦点*/
    d_vis_set_focus(vis_item[item_loop_order[atv_meida_focus_id]]);

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_OK_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_main_menu_window_handler);
    }

    return D_OK;
}


/** @brief 多媒体主菜单*/
D_Result
p_atv_media_main_menu_show (void) D_FUNCPOSTFIT
{
    p_gui_atv_media_resource_init();
    atv_meida_focus_id = 0;
    return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &media_main_menu_window, D_CLEAR_ALL);
}


/** @brief 隐藏或显示多媒体菜单*/
D_Result
p_atv_media_menus_show (D_Bool show, D_U32 param) D_FUNCPOSTFIT
{
    if(AtvMediaMenuStatus == 0)
    {
        return D_OK;
    }

    if(show == D_FALSE)
    {
        p_atv_media_picture_menu_hide();
        /* 多媒体全屏时，此时按菜单键时，不隐藏当前的多媒体菜单*/
        if(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_MOVIE_FULLSCREEN || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN
           || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_EBOOK_FULLSCREEN || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_TXT_FULLSCREEN
           || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PVR_FULLSCREEN)
        {
            return D_OK;
        }
        /* 多媒体预览时，此时按菜单键时，不隐藏当前的多媒体菜单*/
        if(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_MUSIC || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_MOVIE || AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PVR)
        {
            return D_OK;
        }
        return D_OK;

    }

    d_gui_show_menu(ATV_MEDIA_MENU_ID, show);
    return D_OK;
}



