#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pFp.h"
#include "dTime.h"
#include "pPlayer.h"
#include "pMem.h"
#include "pStbMenus.h"
#include "tv_chan_info_window.c"
#include "dadporting.h"
#include "pAdvertisementShow.h"

#define BUFFER_LEN		(20)

/** @brief 内部管理数据*/
typedef struct 
{
	D_HTimer	htimer;
	D_U8		menu_lang;
	D_Char		chan_num[BUFFER_LEN];
	D_Char		video[BUFFER_LEN];
	D_Char		audio[BUFFER_LEN];
} TvChanInfoData;

/** @brief 定时隐藏定时器*/
static TvChanInfoData	*tvcinfo_data;

/** @brief 当前播放器ID*/
static D_ID	curr_player_id;


/** @brief 根据当前频道信息更新显示*/
static D_Result
get_audio_show(D_DBTSInfo *info) D_FUNCPOSTFIT
{
	if(info->param.atv.audioMode == D_AudioBG)
	{
		sprintf(tvcinfo_data->audio,"B/G");
	}
	else if(info->param.atv.audioMode == D_AudioDK)
	{
		sprintf(tvcinfo_data->audio,"D/K");
	}
	else if(info->param.atv.audioMode == D_AudioI)
	{
		sprintf(tvcinfo_data->audio,"I");
	}
	else if(info->param.atv.audioMode == D_AudioM)
	{
		sprintf(tvcinfo_data->audio,"M");
	}
	else if(info->param.atv.audioMode == D_AudioN)
	{
		sprintf(tvcinfo_data->audio,"N");
	}
	else if(info->param.atv.audioMode == D_AudioNc)
	{
		sprintf(tvcinfo_data->audio,"Nc");
	}
	else if(info->param.atv.audioMode == D_AudioMax)
	{
		sprintf(tvcinfo_data->audio,"Nc");
	}

	return D_OK;
}
/** @brief 根据当前频道信息更新显示*/
static D_Result
get_video_show(D_DBTSInfo *info) D_FUNCPOSTFIT
{
	if(info->param.atv.videoMode == D_VideoP)
	{
		sprintf(tvcinfo_data->video,"PAL");
	}
	else if(info->param.atv.videoMode == D_VideoN)
	{
		sprintf(tvcinfo_data->video,"NTSC");
	}
	else if(info->param.atv.videoMode == D_VideoSECAM)
	{
		sprintf(tvcinfo_data->video,"SECAM");
	}
	else if(info->param.atv.videoMode == D_VideoMax)
	{
		sprintf(tvcinfo_data->video,"SECAM");
	}
	
	return D_OK;
}



/** @brief 根据当前频道信息更新显示*/
static D_Result
update_channel_info(void) D_FUNCPOSTFIT
{
	D_DBSrvInfo	srv_info;
    D_DBTSInfo  ts_info;
	D_ID		srv = -1;
	D_S16		 num;
	D_Frame		*frm = &tv_chan_info_window;
	D_Visual	*vis;

	srv = p_stb_player_get_curr_srv (curr_player_id);

	/*取服务信息*/
	if (d_dbase_get_srv_info (srv, &srv_info) < 0)
	{
		return D_ERR;
	}	
	else 
	{
		if (d_dbase_get_ts_info (srv_info.db_ts_id, &ts_info) < 0)
		{
            return D_ERR;
		}
		else 
		{
			sprintf(tvcinfo_data->chan_num,"%d",srv_info.chan_num);
			
			vis = d_frame_get_control(frm, ID_TV_CHAN_INFO_LABEL_NUM);
			if(vis)
			{
				d_label_set_text(vis,tvcinfo_data->chan_num);
			}
			
			get_video_show(&ts_info);
			get_audio_show(&ts_info);
			
			vis = d_frame_get_control(frm, ID_TV_CHAN_INFO_LABEL_VIDEO);
			if(vis)
			{
				d_label_set_text(vis,tvcinfo_data->video);
			}
			vis = d_frame_get_control(frm, ID_TV_CHAN_INFO_LABEL_AUDIO);
			if(vis)
			{
				d_label_set_text(vis,tvcinfo_data->audio);
			}
		}
		
	}
	
	return D_OK;
}

/** @brief 事件处理*/
static D_Result
channel_info_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	switch (evt->type) 
	{
		case D_EVT_FP:
			switch (evt->fp.key) 
			{
				case D_KEY_SCREEN:
					return d_gui_close_frame (&tv_chan_info_window);
					break;
				default:
					break;
			}
			break;
		case D_EVT_TIMER:
			/*隐藏窗口*/
			return d_gui_close_frame (&tv_chan_info_window);
			break;
		case D_EVT_DESTROY:
			if (tvcinfo_data) 
			{
				if (tvcinfo_data->htimer != D_INVALID_HANDLE)
				{
					d_timer_destroy (tvcinfo_data->htimer);
				}
				d_vis_unsubscribe_evt (vis);
				PROJECT_FREE(tvcinfo_data);
				tvcinfo_data = NULL;
			}
			break;
		default:
			break;
	}

	return D_ERR;
}
/** @brief 窗口初始化*/
D_Result
tv_chan_info_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual		*vis;
    D_StbPlayer	*player;
    D_U32 menu_show_time;
	D_Result ad_check = D_ERR;

    player = p_stb_get_player (curr_player_id);
    if (! player)
        return D_ERR;

    tvcinfo_data = (TvChanInfoData*) PROJECT_ALLOC (sizeof (TvChanInfoData));
    if (! tvcinfo_data)
        return D_ERR;

    memset(tvcinfo_data, 0x00, sizeof (TvChanInfoData));

    tvcinfo_data->menu_lang = p_conf_get_lang();
	
    /*清除音量条*/
    p_atv_volume_window_hide();

	vis = d_frame_get_control(frm, ID_TV_CHAN_INFO_CH);
	if(vis)
	{
		d_label_set_text(vis,"CH.");
	}
	
	vis = d_frame_get_control(frm, ID_TV_CHAN_INFO_LABEL_NUM);
	if(vis)
	{
		d_label_set_text(vis,"00");
	}

	menu_show_time = D_CONF_MIN_INFO_TIME;
	
    vis = d_frame_get_control (frm, 0);
    if (vis) 	
    {
        /*创建隐藏定时器*/
        tvcinfo_data->htimer = d_timer_create (NULL, menu_show_time*1000, d_gui_get_queue());
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, tvcinfo_data->htimer);

        /*接收EIT事件更新显示*/
        d_vis_subscribe_evt (vis, D_EVT_SI_EIT_MASK, player->htv);

        /*接收TDT事件后重新显示PF*/
        d_vis_subscribe_evt (vis, D_EVT_SI_TDT_MASK, player->htv);

        /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

        /*注册事件回调*/
        d_vis_set_handler (vis, channel_info_window_handler);
    }

    /*更新显示*/
    update_channel_info();
	
    return D_OK;
}

/** @breif 显示频道信息窗口*/
D_Result
p_atv_tv_chan_info_window_show (D_ID player_id) D_FUNCPOSTFIT
{	
    p_atv_chan_input_window_hide();
	curr_player_id = player_id;
	return d_gui_open_frame(&tv_chan_info_window, D_GUI_LAYER_VIDEO_OSD);
}

/** @breif隐藏频道信息窗口*/
D_Result
p_atv_tv_chan_info_window_hide(void) D_FUNCPOSTFIT
{	
	return d_gui_close_frame (&tv_chan_info_window);
}


