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
#include "ptvConfig.h"
#include "pFp.h"
#include "atv_video_mode_win.c"


typedef struct
{
    D_VidInput input;
    D_U8   video_mode;
    D_U16 nfft;
    D_U8 video_mode_flag;
    D_HTimer timer;
    D_U32    menu_show_time;
    D_AUDIO_Peq param[TV_AUDIO_FEQ];
} D_VideoModeData;

static D_Char* mode_str[4] =  {"standard", "theatre", "music", "movie"};
static D_VideoModeData *video_mode_data = NULL;

/** @brief 复位显示定时器*/
static D_Result
video_mode_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(video_mode_data && video_mode_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(video_mode_data->timer, video_mode_data->menu_show_time);
    }

    return D_OK;
}

static D_Result
change_video_mode(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &video_mode_window;
    D_Visual *vis;
    D_U8 i;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis, mode_str[video_mode_data->video_mode]);
        d_gui_update();
    }

    for(i = 0; i < TV_AUDIO_FEQ ; i++)
    {
        p_tvconf_get_audio_peq_set_param(&video_mode_data->param[i], p_vip_get_dbinput(video_mode_data->input), video_mode_data->video_mode, i);

    }
    p_tvconf_get_cur_t_ffft(&video_mode_data->nfft, p_vip_get_dbinput(video_mode_data->input), video_mode_data->video_mode);
#ifdef D_TV_IAMGE_SOURCE	
		d_av_Audio_PEQ(0, video_mode_data->param, TV_AUDIO_FEQ, video_mode_data->nfft, D_Digital_Audio);
#else	
	if(video_mode_data->video_mode == 0)
	{
		d_av_Audio_PEQ(0, video_mode_data->param, 5, video_mode_data->nfft, D_PEQ);
	}
	else
	{
		d_av_Audio_PEQ(0, video_mode_data->param, 9, video_mode_data->nfft, D_Digital_Audio);
	}
#endif	



    p_tvconf_set_cur_audiomode(&video_mode_data->video_mode, p_vip_get_dbinput(video_mode_data->input));
    return D_OK;
}
/** @brief 事件处理*/
static D_Result
video_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *label_vis;
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            case D_KEY_SOUND:
                video_mode_reset_show_timer();
                video_mode_data->video_mode_flag = (video_mode_data->video_mode + 1) % 4;
                video_mode_data->video_mode = video_mode_data->video_mode_flag;
                change_video_mode();
                break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == video_mode_data->timer)
            {
                p_video_mode_win_hide();
            }
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(video_mode_data)
            {
                if(video_mode_data->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(video_mode_data->timer);
                }
                PROJECT_FREE(video_mode_data);
                video_mode_data = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
video_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;

    video_mode_data = (D_VideoModeData*)PROJECT_ALLOC(sizeof(D_VideoModeData));
    if(!video_mode_data)
    {
        return D_ERR;
    }
    memset(video_mode_data, 0, sizeof(D_VideoModeData));
    video_mode_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_audiomode(&video_mode_data->video_mode, p_vip_get_dbinput(video_mode_data->input));
    video_mode_data->video_mode_flag = video_mode_data->video_mode;

    video_mode_data->menu_show_time = 3 * 1000;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis, mode_str[video_mode_data->video_mode]);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        video_mode_data->timer = d_timer_create (NULL, video_mode_data->menu_show_time, d_gui_get_queue ());
        if(video_mode_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, video_mode_data->timer);
        }

        d_vis_set_handler (vis, video_mode_window_handler);
        d_vis_subscribe_evt (vis, D_EVT_KEY_MASK, D_INVALID_HANDLE);
    }

    return D_OK;
}

/** @brief 菜单显示*/
D_Result
p_video_mode_win_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&video_mode_window, D_GUI_LAYER_VIDEO_MESSAGE);
}

/** @brief 菜单隐藏*/
D_Result
p_video_mode_win_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&video_mode_window);
}

