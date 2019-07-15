#include <stdio.h>
#include "dDBase.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pStb.h"
#include "atv_setmute_window.c"
#include "pStbCaMenus.h"


/*设置静音效果*/
static D_Result
audio_set_mute(D_Bool mute)D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (0)))
    {
        return D_ERR;
    }

    d_tv_set_aud_mute (player->htv, mute);
    p_conf_set_aud_mute (mute);

    return D_OK;
}

/** @brief 窗口事件处理*/
static D_Result
set_mute_handler (D_Visual *vis, D_Event *evt)D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_MUTE:
                    audio_set_mute(D_FALSE);
                    d_gui_close_frame (&atv_setmute_window);
                    if(g_stb->status == D_STB_ST_PLAYING)
                    {
                        p_atv_volume_window_show (0, evt->fp.key);
                    }
                    return D_OK;
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 窗口初始化*/
D_Result
atv_setmute_window_init (D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual    *vis;

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis,  D_EVT_AUDIO_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis,  D_EVT_NUM_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, set_mute_handler);
    }

    audio_set_mute(D_TRUE);

    return D_OK;
}

/** @brief 显示静音调整窗*/
D_Result
p_atv_mute_window_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame (&atv_setmute_window, D_GUI_LAYER_VOLUME_1);
}


/*清除静音图标显示*/
D_Result p_atv_mute_window_clear()D_FUNCPOSTFIT
{
    return d_gui_close_frame (&atv_setmute_window);
}


/*根据状态重新显示静音图标*/
D_Result
p_atv_reshow_mute_flag(void)D_FUNCPOSTFIT
{
    if (p_conf_get_aud_mute())
    {
        p_atv_mute_window_show();
    }
    else
    {
        p_atv_mute_window_clear();
    }

    return D_OK;
}

