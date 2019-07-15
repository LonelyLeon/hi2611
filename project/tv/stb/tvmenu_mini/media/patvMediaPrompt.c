#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pPlayer.h"
#include "pStbAtvMenus.h"
#include "pMenu.h"

#include "atv_media_prompt_window.c"


#define MEDIA_PROMPT_SHOW_TIME (2000)

static D_HTimer mediaProHideTimer = D_INVALID_HANDLE;

static D_ID mediaProStrIid;

/** @brief 事件处理*/
static D_Result
media_prompt_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
    switch (evt->type) 
    {					
        case D_EVT_TIMER:
            if(evt->timer.htimer == mediaProHideTimer)
            {
                d_timer_destroy(mediaProHideTimer);
                mediaProHideTimer = D_INVALID_HANDLE;            
                d_gui_close_frame(&atv_media_prompt_window);
								return  p_atv_reshow_mute_flag();
            }
            break;            
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(mediaProHideTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(mediaProHideTimer);
                mediaProHideTimer = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_media_prompt_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual		*vis;

	mediaProHideTimer = d_timer_create(NULL, MEDIA_PROMPT_SHOW_TIME, d_gui_get_queue());
	if(mediaProHideTimer == D_INVALID_HANDLE)
	{
		return D_ERR;
	}

	vis = d_frame_get_control (frm, ID_MEDIA_CONTENT);
	if(vis)
	{
		d_label_set_text(vis, d_gui_get_text(mediaProStrIid));
	}

	vis = d_frame_get_control (frm, 0);
	if (vis) 
	{		
		/*设定窗口事件回调*/
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK ,D_INVALID_HANDLE);
		d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, mediaProHideTimer);
		d_vis_set_handler (vis, media_prompt_window_handler);		
	} 

	return D_OK;
}


/** @brief 显示多媒体提示窗口*/
D_Result
p_atv_media_prompt_msg(D_ID id)D_FUNCPOSTFIT
{
	mediaProStrIid = id;
	return d_gui_open_frame(&atv_media_prompt_window, D_GUI_LAYER_VOLUME);
}


