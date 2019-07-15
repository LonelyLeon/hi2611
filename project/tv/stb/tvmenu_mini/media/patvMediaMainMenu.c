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

#define ATV_MEDIA_MENU_ITEM_CNT (4)

#define ATV_MEDIA_MENU_ITEM_MOVIE (0)
#define ATV_MEDIA_MENU_ITEM_MUSIC (1)
#define ATV_MEDIA_MENU_ITEM_PHOTO (2)
#define ATV_MEDIA_MENU_ITEM_SETUP (3)
#define ATV_MEDIA_MENU_ITEM_EBOOK (4)
#define ATV_MEDIA_MENU_ITEM_PVR   (5)

/** @brief 多媒体菜单状态*/
D_U32 AtvMediaMenuStatus;
static D_U32 atv_meida_focus_id = 0;



/*多媒体主菜单各子项*/
static D_GUIMenuItem
atv_media_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_media_movie_show, D_FALSE, atv_IDS_MOVIE, atv_IMG_ID_media_main_movie),
    D_GUI_MENU_ITEM_RUN(p_atv_media_music_show, D_FALSE, atv_IDS_MUSIC, atv_IMG_ID_meida_main_muise),
    D_GUI_MENU_ITEM_RUN(p_atv_media_picture_show, D_FALSE, atv_IDS_PICTURE, atv_IMG_ID_media_main_pic),
    D_GUI_MENU_ITEM_RUN(p_atv_media_ebook_list_show, D_FALSE, atv_IDS_EBOOK, atv_IMG_ID_mini_ebook),
    //D_GUI_MENU_ITEM_RUN(p_atv_media_setting_menu_show, D_FALSE, atv_IDS_SETTING, atv_IMG_ID_media_main_set),
    D_GUI_MENU_ITEM_END()
};

/*多媒体主菜单*/
static D_GUIMenu
atv_main_media_menu =
    D_GUI_DECL_MENU (&media_main_menu_window, atv_media_menu_items, -1, -1, D_CLEAR_ALL);


typedef struct
{
    D_GUIMenu   *curr_menu;
    D_U32       item_cnt;
    D_U32       item_focus;
    D_Bool      menu_enable;
    D_U32  sysUsbStatus; /* USB状态*/
} D_MediaMainMenuData;

static D_MediaMainMenuData *media_menu_data = NULL;


/** @brief 显示菜单项*/
static D_Result
media_main_menu_item_show (void) D_FUNCPOSTFIT
{
    D_Frame *frm = &media_main_menu_window;
    D_Visual * vis, *pvis;
    D_GUIMenuItem   *item = NULL;
    D_ID idx;
    D_Image *image;
    D_Char* text;
    D_Bool enable;

    item = media_menu_data->curr_menu->items;

    /*显示文本*/
    for(idx = 0; idx < ATV_MEDIA_MENU_ITEM_CNT; idx++)
    {
        text = NULL;
        image = NULL;
        enable = D_FALSE;
        if(item->action != D_GUI_MENU_END)
        {
            text = d_gui_get_text(item->caption);
            image = d_gui_get_image(item->icon);
            item++;
            enable = D_TRUE;
        }

        vis = d_frame_get_control(frm, ID_ATV_MEDIA_BUTTON_1 + idx);
        pvis = d_frame_get_control(frm, ID_ATV_MEDIA_IMAGE_1 + idx);
        if(vis)
        {
            d_button_set_text(vis, text);
            if(enable == D_FALSE)
            {
                d_vis_set_focusable(vis, D_FALSE);
            }
        }

        if(pvis)
        {
            d_image_box_set_image(pvis, image);
        }
    }

    return D_OK;
}

/** @brief 菜单执行*/
static D_Result
media_main_menu_action (D_U32 action, D_Bool check) D_FUNCPOSTFIT
{
    D_GUIMenuItem *item;
    D_S16 menu_level;

    if(check)
    {
        menu_level = d_gui_get_menu_level_ext(ATV_MEDIA_MENU_ID);
        while(menu_level > 1)
        {
            d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
            menu_level--;
        }
    }

    item = media_menu_data->curr_menu->items + media_menu_data->item_focus;
    if(p_get_curr_usb_status())
    {
        atv_meida_focus_id = media_menu_data->item_focus;
        if(item && (item->action == D_GUI_MENU_RUN_APP) && item->app)
        {
            item->app();
        }
    }

    return D_OK;
}

/** @brief 切换焦点*/
static D_Result
media_main_menu_change_focus (D_Bool right) D_FUNCPOSTFIT
{
    D_Visual * vis;

    if(right)
    {
        media_menu_data->item_focus = (media_menu_data->item_focus + 1) % media_menu_data->item_cnt;
    }
    else
    {
        media_menu_data->item_focus = (media_menu_data->item_focus + media_menu_data->item_cnt - 1) % media_menu_data->item_cnt;
    }

    vis = d_frame_get_control(&media_main_menu_window, (ID_ATV_MEDIA_BUTTON_1 + media_menu_data->item_focus));
    if(vis)
    {
        d_vis_set_focus(vis);
    }
    return D_OK;
}

/** @brief 设定是否可选*/
D_Result
p_media_main_menu_set_enable(D_Bool enable) D_FUNCPOSTFIT
{
    if(media_menu_data && media_menu_data->menu_enable != enable)
    {
        D_Visual * vis;

        vis = d_frame_get_control(&media_main_menu_window, (ID_ATV_MEDIA_BUTTON_1 + media_menu_data->item_focus));
        if(vis)
        {
            d_vis_enable(vis, enable);
            if(enable)
            {
                d_vis_set_focus(vis);
            }
        }

        if(enable == D_FALSE)
        {
            vis = d_frame_get_control(&media_main_menu_window, ID_ATV_MEDIA_BUTTON_LEFT);
            if(vis)
            {
                d_vis_set_focus(vis);
            }
        }
        media_menu_data->menu_enable = enable;
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
                case D_KEY_HOME:
                case D_KEY_BACK:
                {
                    return D_ERR;
                }
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(media_menu_data->menu_enable)
                    {
                        media_main_menu_change_focus(D_FALSE);
                        media_main_menu_action(1, D_TRUE);
                    }
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(media_menu_data->menu_enable)
                    {
                        media_main_menu_change_focus(D_TRUE);
                        media_main_menu_action(1, D_TRUE);
                    }
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(media_menu_data->menu_enable == D_FALSE)
                    {
                        p_media_main_menu_set_enable(D_TRUE);
                    }
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    if(media_menu_data->menu_enable == D_TRUE)
                    {
                        p_media_main_menu_set_enable(D_FALSE);
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(media_menu_data->menu_enable == D_FALSE)
                    {
                        p_media_main_menu_set_enable(D_TRUE);
                    }
                    break;
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    p_atv_signal_select_show();
                    break;
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    p_atv_main_menu_show();
                    break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {

            }
            break;
        case D_EVT_HOTPLUG_MSG:
#ifdef D_MUTIMEDIA_NOCATALOG
            p_media_hotplug_rset((D_U8)evt->hotplug.plug, (D_U8)evt->hotplug.arg);
            p_media_usb_plug_msg_process((D_U8)evt->hotplug.plug, (D_U8)evt->hotplug.arg);
#endif

            if(evt->hotplug.plug)
            {
                media_main_menu_action(1, D_FALSE);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_MAIN;
            if(media_menu_data)
            {
                PROJECT_FREE(media_menu_data);
                media_menu_data = NULL;
            }

            d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
            d_mediacodec_close();

            /* 重设静音/声道/音量*/
            p_stb_reset_mute_track_volume();

            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 初始化*/
D_Result
media_main_menu_window_init(D_Frame *frm)
{
    D_Visual * vis;
    D_ID i;
    D_GUIMenuItem *item;

    media_menu_data = (D_MediaMainMenuData*)PROJECT_ALLOC(sizeof(D_MediaMainMenuData));
    if(media_menu_data == NULL)
    {
        return D_ERR;
    }
    memset(media_menu_data, 0x00, sizeof(D_MediaMainMenuData));
    media_menu_data->curr_menu = &atv_main_media_menu;
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_MAIN;

    item = media_menu_data->curr_menu->items;
    for(i = 0; item->action != D_GUI_MENU_END; i++)
    {
        item++;
        media_menu_data->item_cnt++;
    }

    /* 挂起DVB播放和SI监控*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/

    /* 停止fman对信号的监控*/
    d_fman_set_locked_detector(g_stb->player->hfman, D_INVALID_HANDLE);
    d_app_set_timeout(g_stb->player->hfman, -1);

    /* 释放epg占用资源*/
    p_auxi_free_varstring();

    /* 初始化多媒体音视频图片的各自的播放任务*/
    d_mediacodec_open();

    /* 重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();

    vis = d_frame_get_control(frm, ID_ATV_GROUP_MAINMENU);
    if(vis)
    {
        /* group 不响应任何按键, 切换焦点在window里操作*/
        d_vis_unsubscribe_one_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_group_set_focus_loop(vis, D_FALSE);
    }

    for(i = 0; i < ATV_MEDIA_MENU_ITEM_CNT; i++)
    {
        vis = d_frame_get_control(frm, (ID_ATV_MEDIA_BUTTON_1 + i));
        if(vis)
        {
            /* button 不响应任何按键*/
            d_vis_unsubscribe_one_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        }
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_main_menu_window_handler);
    }

    media_main_menu_item_show();
    media_menu_data->item_focus = D_MIN(atv_meida_focus_id, (media_menu_data->item_cnt - 1));
    p_media_main_menu_set_enable(D_TRUE);

    media_menu_data->sysUsbStatus = p_get_curr_usb_status();
#ifdef D_MUTIMEDIA_NOCATALOG
    p_media_begin_deal();
#endif
    return D_OK;
}


/** @brief 多媒体主菜单*/
D_Result
p_atv_media_main_menu_show (void) D_FUNCPOSTFIT
{
    D_Result ret;

    if(d_frame_is_loaded(&media_main_menu_window))
    {
        return D_OK;
    }

    p_gui_atv_media_resource_init();
    atv_meida_focus_id = 0;
    ret = d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &media_main_menu_window, D_CLEAR_ALL);
    if(ret == D_OK)
    {
        media_main_menu_action(1, D_TRUE);
    }
    return ret;
}


/** @brief 隐藏或显示多媒体菜单*/
D_Result
p_atv_media_menus_show (D_Bool show, D_U32 param) D_FUNCPOSTFIT
{
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



