/** @file
* @brief 多音频模块
* @author
* @date 2016-04-15 :  建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDate.h"
#include "dDebug.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pMem.h"
#include "dDBase.h"
#include "pPlayer.h"
#include "pStbMenus.h"
#include "dFileSystem.h"
#include "dMedia.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dPvrReplay.h"
#include "atv_multi_audio_window.c"


typedef struct
{
    D_S16 multi_audio_cnt;
    D_S16 multi_audio_val;
    D_S16 multi_audio_type[4];
    D_Visual *vis_audio;
    D_Visual *vis_audio_type;
} MultiAudio;
static MultiAudio *multi_audio = NULL;

static D_Char *content[4] = {"1", "2", "3", "4"};
static D_Char *aud_type[12] = {"MPEG2", "AC3", "AAC", "DRA", "DTS", "PCM", "ADPCM", "INTERPHONE", "MP3", "WMA", "AMR", "VORBIS"};


/** @brief 取得音频相关信息*/
static D_Result
multi_audio_show_curr_voice_info(void)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_multi_audio_window;
    D_DBSrvInfo srv_info;
    D_DBSrvID srv;
    D_S16 audio_type = 0;

    srv = p_stb_player_get_curr_srv (0);
    if (srv == -1)
    {
        return D_ERR;
    }
    multi_audio->multi_audio_cnt = 0;
    multi_audio->multi_audio_val = 0;
    /*取得当前的节目声道信息*/
    if (D_OK == d_dbase_get_srv_info (srv, &srv_info) )
    {
        multi_audio->multi_audio_cnt = (srv_info.aud2_pid != 0x1FFF) ? 2 : 1;
        multi_audio->multi_audio_val = (D_S16)srv_info.aud_acc;

        multi_audio->multi_audio_type[0] = (D_S16)srv_info.aud1_codec;
        multi_audio->multi_audio_type[1] = (D_S16)srv_info.aud2_codec;
#ifdef D_DB_SRV_SUPPORT_4AUDIO
        multi_audio->multi_audio_cnt = (srv_info.aud4_pid != 0x1FFF) ? 4 : ((srv_info.aud3_pid != 0x1FFF) ? 3 : multi_audio->multi_audio_cnt);
        multi_audio->multi_audio_type[2] = (D_S16)srv_info.aud3_codec;
        multi_audio->multi_audio_type[3] = (D_S16)srv_info.aud4_codec;
#endif
        multi_audio->multi_audio_val = D_MIN(multi_audio->multi_audio_val, (multi_audio->multi_audio_cnt - 1));
    }

    d_select_box_set_content (multi_audio->vis_audio, content, multi_audio->multi_audio_cnt);
    d_select_box_set_val(multi_audio->vis_audio, multi_audio->multi_audio_val);

    audio_type = multi_audio->multi_audio_type[multi_audio->multi_audio_val];
    d_label_set_text (multi_audio->vis_audio_type, aud_type[audio_type]);

    return D_OK;
}

/** @brief  声道确认回调函数
* @param    sel 是否选择确定
* @param    param参数
* @return   函数正确执行返回D_OK,失败返回D_ERR
*/
static D_Result
multi_audio_callback(void)D_FUNCPOSTFIT
{
    D_DBSrvInfo srv_info;
    D_DBSrvID srv;

    srv = p_stb_player_get_curr_srv (0);
    if (srv == -1)
    {
        return D_ERR;
    }

    if (multi_audio->vis_audio)
    {
        multi_audio->multi_audio_val = d_select_box_get_val(multi_audio->vis_audio);
    }

    if (D_OK == d_dbase_get_srv_info (srv, &srv_info))
    {
        /*设置多路音频*/
        if(srv_info.aud_acc != ((D_U8)multi_audio->multi_audio_val))
        {
            d_dbase_update_srv_aud_acc(srv, (D_U8)multi_audio->multi_audio_val);
            d_tv_set_aud_acc (g_stb->player->htv, (D_U8)multi_audio->multi_audio_val);
        }
    }

    return D_OK;
}

/** @brief 事件处理回调*/
static D_Result
multi_audio_selcet_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_S16 audio_type = 0;

    switch (evt->type)
    {
        case D_EVT_SELECTED:
            multi_audio->multi_audio_val = d_select_box_get_val(vis);
            audio_type = multi_audio->multi_audio_type[multi_audio->multi_audio_val];
            d_label_set_text (multi_audio->vis_audio_type, aud_type[audio_type]);
            multi_audio_callback();
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理回调*/
static D_Result
multi_audio_esc_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            //multi_audio_callback();
            p_atv_multi_audio_window_hide();
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief  主窗口事件处理
* @param    vis 控件指针
* @param    evt事件指针
* @return   函数正确执行返回D_OK,失败返回D_ERR
*/
static D_Result
multi_audio_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    //multi_audio_callback();
                    p_atv_multi_audio_window_hide();
                    break;
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                case D_KEY_MUTE:
                    return D_ERR;
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            if (multi_audio)
            {
                PROJECT_FREE(multi_audio);
                multi_audio = NULL;
            }
            d_vis_unsubscribe_evt (vis);
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief  窗口初始化
* @param    frm 初始化窗口指针
* @return   函数正确执行返回D_OK,失败返回D_ERR
*/
D_Result
atv_multi_audio_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;

    /*分配内存*/
    multi_audio = PROJECT_ALLOC(sizeof (MultiAudio));
    if (! multi_audio)
        return D_ERR;
    memset(multi_audio, 0, sizeof (MultiAudio));

    multi_audio->vis_audio = d_frame_get_control(frm, ID_MULTIAUDIO_SELECT_AUDIO);
    multi_audio->vis_audio_type = d_frame_get_control(frm, ID_MULTIAUDIO_LABEL_AUDIO_INFO);

    d_vis_set_handler(multi_audio->vis_audio, multi_audio_selcet_handler);

    vis = d_frame_get_control(frm, ID_MULTIAUDIO_BUTTON_ESC);
    if(vis)
    {
        d_vis_set_handler(vis, multi_audio_esc_handler);
    }

    multi_audio_show_curr_voice_info();
    /*注册默主窗口事件*/
    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, multi_audio_window_handler);
    }
    vis = d_frame_get_control (frm, ID_MULTIAUDIO_GROUP_INFO);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    return D_OK;
}

/** @brief  显示窗口
* @param    无
* @return   函数正确执行返回D_OK,失败返回D_ERR
*/
D_Result
p_atv_multi_audio_window_show (void) D_FUNCPOSTFIT
{
    D_DBSrvInfo srv_info;
    D_DBSrvID srv;
    srv = p_stb_player_get_curr_srv (0);

    /*取得当前的节目声道信息*/
    if ((srv != -1) && (d_dbase_get_srv_info (srv, &srv_info) >= 0))
    {
        /*设置多路音频*/
        if(srv_info.aud1_pid != 0x1fff && srv_info.aud2_pid != 0x1fff)
        {
            return d_gui_enter_menu (&atv_multi_audio_window, D_TRUE);
        }
    }

    return D_ERR;
}

/** @brief 清除信息窗口*/
D_Result
p_atv_multi_audio_window_hide (void) D_FUNCPOSTFIT
{
    return d_gui_upper_menu ();
}

