#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dAV.h"
#include "pFp.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "signal_input_window.c"

typedef struct
{
    D_HTimer timer;
    D_U32    menu_show_time;
} D_SignaInputData;

static D_SignaInputData *signal_input_data = NULL;
static D_VidInput    signal_input;
static char video_lab[20] = {0};
static char audio_lab[20] = {0};

/** @brief 复位显示定时器*/
static D_Result
reset_show_timer(void) D_FUNCPOSTFIT
{
    if(signal_input_data && signal_input_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(signal_input_data->timer,  signal_input_data->menu_show_time * 1000);
    }

    return D_OK;
}

static D_ID
signal_input_label(void) D_FUNCPOSTFIT
{
    D_ID    id = atv_IDS_NULL;

    switch(signal_input)
    {
        case D_VID_IUTPUT_TV:
            id = atv_IDS_TV;
            break;
        case D_VID_IUTPUT_DTV:
            id = atv_IDS_DTV;
            break;
#if (defined(D_IUTPUT_SUPPORT_AV1)&&defined(D_IUTPUT_SUPPORT_AV2))
        case D_VID_IUTPUT_AV1:
            id = atv_IDS_AV1;
            break;
        case D_VID_IUTPUT_AV2:
            id = atv_IDS_AV2;
            break;
#else
		case D_VID_IUTPUT_AV1:
			id = atv_IDS_AV;
			break;
		case D_VID_IUTPUT_AV2:
			id = atv_IDS_AV;
			break;
#endif
        case D_VID_IUTPUT_YPBPR:
            id = atv_IDS_YPBPR;
            break;
			
#if (defined(D_IUTPUT_SUPPORT_HDMI1)&&defined(D_IUTPUT_SUPPORT_HDMI2))
        case D_VID_IUTPUT_HDMI1:
            id = atv_IDS_HDMI1;
            break;
        case D_VID_IUTPUT_HDMI2:
            id = atv_IDS_HDMI2;
            break;
#else
		case D_VID_IUTPUT_HDMI1:
			id = atv_IDS_HDMI;
			break;
		case D_VID_IUTPUT_HDMI2:
			id = atv_IDS_HDMI;
			break;
#endif

        case D_VID_IUTPUT_USB1:
            id = atv_IDS_USB;
            break;
        case D_VID_IUTPUT_VGA:
            id = atv_IDS_PC;
            break;
        case D_VID_IUTPUT_DVI1:
            id = atv_IDS_DVI1;
            break;
        case D_VID_IUTPUT_DVI2:
            id = atv_IDS_DVI2;
            break;
        case D_VID_IUTPUT_WIFIDISPLAY:
            id = atv_IDS_ZHILIAN_TV;
            break;
#ifdef D_TV_LIULINK_SOURCE
       case D_VID_IUTPUT_LIULINK:
            id = atv_IDS_LIULINK;
            break;
#endif
#ifdef D_TV_SUPPORT_IPTV
       case D_VID_IUTPUT_IPTV:
            id = atv_IDS_ZHILIAN_IPTV;
            break;
#endif
        default:			
            break;
    }

    return id;
}


static D_Result
signal_input_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_SCREEN:
                    return d_gui_close_frame (&signal_input_window);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == signal_input_data->timer)
            {
                return d_gui_close_frame(&signal_input_window);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(signal_input_data)
            {
                if(signal_input_data->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(signal_input_data->timer);
                }
                PROJECT_FREE(signal_input_data);
                signal_input_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;

}

D_Result
signal_input_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_ID  label_id;

    signal_input_data = (D_SignaInputData*)PROJECT_ALLOC(sizeof(D_SignaInputData));
    if(!signal_input_data)
    {
        return D_ERR;
    }

    memset(signal_input_data, 0x00, sizeof(D_SignaInputData));
#if 0
    signal_input_data->menu_show_time = (D_U32)p_conf_get_info_time();
    if(signal_input_data->menu_show_time < D_CONF_MIN_INFO_TIME)
    {
        signal_input_data->menu_show_time = D_CONF_MIN_INFO_TIME;
    }
    else if(signal_input_data->menu_show_time > D_CONF_MAX_INFO_TIME)
    {
        signal_input_data->menu_show_time = D_CONF_MAX_INFO_TIME;
    }
#else
    signal_input_data->menu_show_time = D_CONF_MIN_INFO_TIME;;
#endif
    label_id = signal_input_label();

    vis = d_frame_get_control(frm, ID_LABEL_INPUT);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text(label_id));
    }

    vis = d_frame_get_control(frm, ID_SIGNAL_INPUT_LABEL_VIDEO);
    if(vis)
    {
        if(video_lab[0] != 0)
        {
            d_label_set_text(vis, video_lab);
        }
        else
        {
            d_vis_show(vis, D_FALSE);
        }
    }

    vis = d_frame_get_control(frm, ID_SIGNAL_INPUT_LABEL_AUDIO);
    if(vis)
    {
        if(audio_lab[0] != 0)
        {
            d_label_set_text(vis, audio_lab);
        }
        else
        {
            d_vis_show(vis, D_FALSE);
        }
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_set_handler (vis, signal_input_window_handler);

        signal_input_data->timer = d_timer_create (NULL, signal_input_data->menu_show_time * 1000, d_gui_get_queue ());
        if(signal_input_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, signal_input_data->timer);
        }
        /*设定窗口遥控器、面板按键事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

    }

    return D_OK;
}


/** @breif 显示窗口*/
D_Result
p_atv_signal_input_show (D_VidInput input, char *video, char *audio) D_FUNCPOSTFIT
{
    signal_input = input;
    memset(video_lab, 0, sizeof(video_lab));
    memset(audio_lab, 0, sizeof(audio_lab));
    if(video)
    {
        sprintf(video_lab, "%s", video);
    }
    if(audio)
    {
        sprintf(audio_lab, "%s", audio);
    }
    return d_gui_open_frame (&signal_input_window, D_GUI_LAYER_HIGHEST);
}

