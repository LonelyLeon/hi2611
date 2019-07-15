/** @file
*@brief ts2net投屏显示窗口
*@date
*/

#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "ptvConfig.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "atv_ts2net_window.c"

#define D_TS2NET_CHECK_TIMEOUT   (1000)

typedef struct
{
    D_Char dev_name[32];
    D_Char password[32];
    D_Char str_msg[128];
    D_Char prompt_msg[128];
    D_Char stop_msg[128];
    D_U8   menu_lang;
    D_HTimer htimer;
    D_Bool showflag;
} D_Ts2NetMenuDat;
static D_Ts2NetMenuDat* pts2netmenudat = NULL;
static D_Result (*user_handler) (D_U32 action) = NULL;

extern D_Result d_get_ap_name(char* dev_name, char* password);


static D_Result
stop_ts2net_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    D_Visual *vis;
    
    if(sel)
    {
        vis = d_frame_get_control( &atv_ts2net_window, ID_TS2NET_LABEL);
        if(vis)
        {
            d_label_set_text(vis, pts2netmenudat->stop_msg);
        }  
        d_gui_update();
        if(user_handler)
        {
            user_handler(0);
        }

        p_atv_ts2net_window_hide();
    }
    return D_OK;
}

static D_Result
atv_ts2net_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_RED:
                case D_KEY_ESC:
                case D_KEY_BACK:
                    if(g_stb->status == D_STB_ST_PLAYING)
                    {
                        d_atv_pop_select_show(4, D_GUI_LAYER_MESSAGE, NULL,
                        pts2netmenudat->prompt_msg, 5000, D_FALSE, stop_ts2net_callback, 0) ;
                        return D_OK;                        
                    }
                    break;
                default:
                    break;
            }
            return D_ERR;
            break;
        case D_EVT_TIMER:
            if(pts2netmenudat->htimer == evt->timer.htimer)
            {
                D_Visual *vis_img;
                pts2netmenudat->showflag = !pts2netmenudat->showflag;
                vis_img = d_frame_get_control( &atv_ts2net_window, ID_TS2NET_IMAGE);
                if(vis_img)
                {
                    d_vis_show(vis_img, pts2netmenudat->showflag);
                }
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(pts2netmenudat)
            {
                if(pts2netmenudat->htimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(pts2netmenudat->htimer);
                    pts2netmenudat->htimer = D_INVALID_HANDLE;
                }
                PROJECT_FREE(pts2netmenudat);
                pts2netmenudat = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


D_Result
atv_ts2net_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    pts2netmenudat = (D_Ts2NetMenuDat*)PROJECT_ALLOC(sizeof(D_Ts2NetMenuDat));
    memset(pts2netmenudat, 0x00, sizeof(D_Ts2NetMenuDat));

    pts2netmenudat->showflag = D_TRUE;
    pts2netmenudat->htimer = D_INVALID_HANDLE;
    pts2netmenudat->menu_lang = p_conf_get_lang();
    d_get_ap_name(pts2netmenudat->dev_name, pts2netmenudat->password);

    if(pts2netmenudat->menu_lang == D_LANG_ENG)
    {
        sprintf(pts2netmenudat->str_msg, "%s, wifi: %s, pwd: %s", d_gui_get_text(atv_IDS_DTV_SHAREING), pts2netmenudat->dev_name, pts2netmenudat->password);
        sprintf(pts2netmenudat->prompt_msg, "Stop %s ?", d_gui_get_text(atv_IDS_DTV_SHAREING));
        sprintf(pts2netmenudat->stop_msg, "Stop %s  ...", d_gui_get_text(atv_IDS_DTV_SHAREING));
    }
    else
    {
        sprintf(pts2netmenudat->str_msg, "%s, wifi: %s, pwd: %s", d_gui_get_text(atv_IDS_DTV_SHAREING), pts2netmenudat->dev_name, pts2netmenudat->password);
        sprintf(pts2netmenudat->prompt_msg, "是否结束%s ?", d_gui_get_text(atv_IDS_DTV_SHAREING));
        sprintf(pts2netmenudat->stop_msg, "正在关闭%s, 请稍候...", d_gui_get_text(atv_IDS_DTV_SHAREING));
    }

    vis = d_frame_get_control( frm, ID_TS2NET_LABEL);
    if(vis)
    {
        d_label_set_text(vis, pts2netmenudat->str_msg);
    }

    vis = d_frame_get_control( frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        pts2netmenudat->htimer = d_timer_create (NULL, D_TS2NET_CHECK_TIMEOUT, d_gui_get_queue ());
        if(pts2netmenudat->htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, pts2netmenudat->htimer);
        }
        d_vis_set_handler (vis, atv_ts2net_window_handler);
    }

    return D_OK;
}


/** @breif 显示窗口*/
D_Result
p_atv_ts2net_window_show (D_U32 x, D_U32 y, D_Result (*handler) (D_U32 action)) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded (&atv_ts2net_window))
    {
        D_FrameControlDescr *descrs = (D_FrameControlDescr *)atv_ts2net_window.ctrl_descrs;
        descrs[0].x = x;
        descrs[0].paly = y;
        descrs[0].ntscy = y;
        user_handler = handler;
        //d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_ts2net_window, D_CLEAR_ALL);
        d_gui_open_frame(&atv_ts2net_window, D_GUI_LAYER_USER_0);
    }
    return D_OK;
}

/** @breif 隐藏窗口*/
D_Result
p_atv_ts2net_window_hide (void) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_ts2net_window))
    {
        //d_gui_clear_menu_ext (ATV_MEDIA_MENU_ID);
        d_gui_close_frame(&atv_ts2net_window);
    }
    return D_OK;
}

