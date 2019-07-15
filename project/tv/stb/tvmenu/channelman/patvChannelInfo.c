#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "pFp.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "dTime.h"
#include "pPlayer.h"
#include "pMem.h"
#include "pStbMenus.h"
#include "atv_channel_info_window.c"
#include "dadporting.h"
#include "pAdvertisementShow.h"



#define BUFFER_LEN      (64)
#define SELECT_CNT      (16)
typedef struct
{
    D_U32   val;
    D_Char  string_val[BUFFER_LEN];
} D_StringDate;


/** @brief 内部管理数据*/
typedef struct
{
    D_HTimer    htimer;
    D_U8        menu_lang;
    D_Char      time[BUFFER_LEN];
    D_Char      chan_info[BUFFER_LEN];
    D_Char      pevt_time[BUFFER_LEN];
    D_Char      pevt_name[BUFFER_LEN];
    D_Char      fevt_time[BUFFER_LEN];
    D_Char      fevt_name[BUFFER_LEN];
    D_Char      freq_into[BUFFER_LEN];
    D_Visual    *vis_vtype;
    D_Visual    *vis_atype;
    D_Char *VideoTypeContent[SELECT_CNT];
    D_U16   VideoType_cnt;

    D_Char *AudioTypeContent[SELECT_CNT];
    D_U16   AudioType_cnt;

} ChanInfoData;

/** @brief 定时隐藏定时器*/
static ChanInfoData *cinfo_data;

/** @brief 当前播放器ID*/
static D_ID curr_player_id;

static D_ID week[7] = {atv_IDS_SUNDAY, atv_IDS_MONDAY, atv_IDS_TUESDAY, atv_IDS_WENDSDAY, atv_IDS_THURSDAY, atv_IDS_FRIDAY, atv_IDS_SATURDAY};
static D_StringDate VideoType[] =
{
    {(D_U32)D_VID_CODEC_MPEG2, "MPEG2"},
    {(D_U32)D_VID_CODEC_AVS, "AVS"},
    {(D_U32)D_VID_CODEC_H264, "H264"},
    {(D_U32)D_VID_CODEC_MPEG4, "MPEG4"},
    {(D_U32)D_VID_CODEC_VC1, "VC1"},
    {(D_U32)D_VID_CODEC_MJPEG, "MJPEG"},
};

static D_StringDate AudioType[] =
{
    {(D_U32)D_AUD_CODEC_MPEG2, "MPEG2"},
    {(D_U32)D_AUD_CODEC_AC3, "AC3"},
    {(D_U32)D_AUD_CODEC_AAC, "AAC"},
    {(D_U32)D_AUD_CODEC_DTS, "DTS"},
    {(D_U32)D_AUD_CODEC_DRA, "DRA"},
    {(D_U32)D_AUD_CODEC_MP3, "MP3"},
};
/** @brief 更新时间显示*/
static D_Result
update_time (void) D_FUNCPOSTFIT
{
    D_Time       now;
    D_Frame     *frm = &atv_channel_info_window;
    D_Visual    *vis;
    D_Date today;
    D_Char  *strweek;  /*星期几*/

    if(d_time_had_set_time())
    {
        /*显示当前时间*/
        now = d_time_get_local_time ();
        d_date (now, &today);
        strweek = d_gui_get_text(week[today.wday]);

        vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_DATA);
        if (vis)
        {
            sprintf (cinfo_data->time,
            "%02d:%02d   %s  %d-%d", today.hour, today.min, strweek, today.mon + 1, today.mday);
        }
        d_label_set_text (vis, cinfo_data->time);
    }

    return D_OK;
}


/** @brief 更新事件显示*/
static D_Result
update_evt_info (void) D_FUNCPOSTFIT
{
    D_ID        srv = -1;
    D_DBEvtID   evt = -1;
    D_DBEvtInfo evt_info;
    D_Time      now;
    D_Frame     *frm = &atv_channel_info_window;
    D_Visual        *vis;
    D_Time  start, end;

    srv = p_stb_player_get_curr_srv (curr_player_id);
    now = d_time_get_time ();

    /*取当前事件信息*/
    evt = d_dbase_get_present_evt (srv, now);

    if (evt != -1)
    {
        if (d_dbase_get_evt_info (evt, &evt_info) >= 0)
        {
            evt_info.start = d_time_local_time (evt_info.start);

            /*更新事件时间*/
            vis = d_frame_get_control (frm, ID_LABEL_NOW_PROGRAM_TIME);
            if (vis)
            {
                start = evt_info.start % (24 * 3600);
                end = (evt_info.start + evt_info.duration) % (24 * 3600);

                sprintf (cinfo_data->pevt_time,
                "%02d:%02d-%02d:%02d", start / 3600, (start % 3600) / 60, end / 3600, (end % 3600) / 60);
                d_label_set_text (vis, cinfo_data->pevt_time);
            }

            /*更新事件名*/
            vis = d_frame_get_control (frm, ID_LABEL_NOW_PRGRAM);
            if (vis)
            {
                strncpy (cinfo_data->pevt_name, evt_info.name, sizeof(cinfo_data->pevt_name));
                d_label_set_text (vis, cinfo_data->pevt_name);
            }
        }
    }
    else
    {
        vis = d_frame_get_control (frm, ID_LABEL_NOW_PROGRAM_TIME);
        if (vis)
        {
            d_label_set_text (vis, NULL);
        }
        vis = d_frame_get_control (frm, ID_LABEL_NOW_PRGRAM);
        if (vis)
        {
            if(cinfo_data->menu_lang == D_LANG_ENG)
            {
                sprintf(cinfo_data->pevt_name, "No program info");
            }
            else
            {
                sprintf(cinfo_data->pevt_name, "暂无节目信息");
            }
            d_label_set_text (vis, cinfo_data->pevt_name);
        }
    }

    /*取下一个事件信息*/
    evt = d_dbase_get_following_evt (srv, now);
    if (evt != -1)
    {
        if (d_dbase_get_evt_info (evt, &evt_info) >= 0)
        {
            evt_info.start = d_time_local_time (evt_info.start);

            /*更新事件时间*/
            vis = d_frame_get_control (frm, ID_LABEL_NEXT_PROGRAM_TIME);
            if (vis)
            {
                start = evt_info.start % (24 * 3600);
                end = (evt_info.start + evt_info.duration) % (24 * 3600);

                snprintf (cinfo_data->fevt_time, sizeof(cinfo_data->fevt_time),
                          "%02d:%02d-%02d:%02d", start / 3600, (start % 3600) / 60, end / 3600, (end % 3600) / 60);
                d_label_set_text (vis, cinfo_data->fevt_time);
            }

            /*更新事件名*/
            vis = d_frame_get_control (frm, ID_LABEL_NEXT_PROGRAM);
            if (vis)
            {
                strncpy (cinfo_data->fevt_name, evt_info.name, sizeof(cinfo_data->fevt_name));
                d_label_set_text (vis, cinfo_data->fevt_name);
            }
        }
    }
    else
    {
        vis = d_frame_get_control (frm, ID_LABEL_NEXT_PROGRAM_TIME);
        if (vis)
        {
            d_label_set_text (vis, NULL);
        }
        vis = d_frame_get_control (frm, ID_LABEL_NEXT_PROGRAM);
        if (vis)
        {
            d_label_set_text (vis, NULL);
        }
    }

    return D_OK;
}

/** @brief */
static D_Result update_dra_chn_info(D_U16   type,D_U16   val )D_FUNCPOSTFIT
{
      D_U32 normal_chn=0;
      D_U32   lfe_chn = 0;

     if(type != D_AUD_CODEC_DRA)
	 	return D_ERR;

	normal_chn = d_av_get_aud_dra_chn_info(D_AUD_DRA_NORMAL_CHN);
	lfe_chn = d_av_get_aud_dra_chn_info(D_AUD_DRA_LFE_CHN);

	if(normal_chn == 5 && lfe_chn == 1)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 5.1");       
	}
	else if(normal_chn == 5 && lfe_chn == 0)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 5.0");       
	}	
	else if(normal_chn == 4 && lfe_chn == 1)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 4.1");       
	}	
	else if(normal_chn == 4 && lfe_chn == 0)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 4.0");       
	}	
	else if(normal_chn == 3 && lfe_chn == 1)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 3.1");       
	}	
	else if(normal_chn == 3 && lfe_chn == 0)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 3.0");       
	}	
	else if(normal_chn == 2 && lfe_chn == 1)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 2.1");       
	}	
	else if(normal_chn == 2 && lfe_chn == 0)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 2.0");       
	}	
	else if(normal_chn == 1 && lfe_chn == 0)
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA 1.0");       
	}	
	else 
	{
	     sprintf(cinfo_data->AudioTypeContent[val] , "DRA");       
	}	
     d_select_box_set_content(cinfo_data->vis_atype, cinfo_data->AudioTypeContent, cinfo_data->AudioType_cnt);   	
	
     return D_OK;
}
/** @brief 根据当前频道信息更新显示*/
static D_Result
update_channel_info(void) D_FUNCPOSTFIT
{
    D_DBSrvInfo srv_info;
    D_DBTSInfo  ts_info;
    D_ID        srv = -1;
    D_S16        num;
    D_Frame     *frm = &atv_channel_info_window;
    D_Visual    *vis;
    D_U16   type;
    D_U16   val = 0, i;

    srv = p_stb_player_get_curr_srv (curr_player_id);

    /*取服务信息*/
    if (d_dbase_get_srv_info (srv, &srv_info) < 0)
    {
        D_ERROR ("Cannot get service information %d", srv);

        /*显示频道无效*/
        vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_INFO);
        if (vis)
        {
            if(cinfo_data->menu_lang == D_LANG_ENG)
            {
                sprintf(cinfo_data->chan_info, "channel not exit");
            }
            else
            {
                sprintf(cinfo_data->chan_info, "频道不存在");
            }
            d_label_set_text (vis, cinfo_data->chan_info);
        }
        return D_ERR;
    }

    /*显示频道名*/
    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_INFO);
    if (vis)
    {
        if(srv_info.ca_flag)
        {
            sprintf(cinfo_data->chan_info, "%s%03d %s  ($)", ((srv_info.srv_type == D_DB_SRV_RADIO) ? "A" : "C"), srv_info.chan_num, srv_info.name);
        }
        else
        {
            sprintf(cinfo_data->chan_info, "%s%03d %s", ((srv_info.srv_type == D_DB_SRV_RADIO) ? "A" : "C"), srv_info.chan_num, srv_info.name);
        }
        d_label_set_text (vis, cinfo_data->chan_info);
    }

    type = srv_info.vid_codec;
    for(i = 0; i < cinfo_data->VideoType_cnt; i++)
    {
        if(VideoType[i].val == type)
        {
            val = i;
            break;
        }
    }
    d_select_box_set_val(cinfo_data->vis_vtype, val);
    type = (D_U16)D_DB_GET_SRV_AUD_CODEC(&srv_info);
    for(i = 0; i < cinfo_data->AudioType_cnt; i++)
    {
        if(AudioType[i].val == type)
        {
            val = i;
            break;
        }
    }
    update_dra_chn_info(type, val );
    d_select_box_set_val(cinfo_data->vis_atype, val);

    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_VIDEO);
    if (vis)d_vis_show(vis, D_TRUE);
    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_AUDIO);
    if (vis)d_vis_show(vis, D_TRUE);

    if (cinfo_data->vis_vtype)d_vis_show(cinfo_data->vis_vtype, D_TRUE);
    if (cinfo_data->vis_atype)d_vis_show(cinfo_data->vis_atype, D_TRUE);

    if((srv_info.aud1_pid != D_INVALID_PID_VALUE) && (srv_info.aud2_pid != D_INVALID_PID_VALUE)) //有两路音频的时候显示切换提示
    {
        vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_ICON);
        if (vis)d_vis_show(vis, D_TRUE);
        vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_MULTIAUDIO);
        if (vis)d_vis_show(vis, D_TRUE);
    }

    /*显示频率信息*/
    sprintf(cinfo_data->freq_into, "");
    if(D_OK == d_dbase_get_ts_info (srv_info.db_ts_id, &ts_info))
    {
        if(ts_info.tuner_type == D_FEND_DTMB)
        {
            sprintf(cinfo_data->freq_into, "%s %d.%d MHz", d_gui_get_text(atv_IDS_FREQ), ts_info.param.dtmb.freq, ts_info.param.dtmb.freq_k);
        }
        else if(ts_info.tuner_type == D_FEND_DVBC)
        {
            sprintf(cinfo_data->freq_into, "%s %d.%d MHz", d_gui_get_text(atv_IDS_FREQ), ts_info.param.dvbc.freq, ts_info.param.dvbc.freq_k);
        }
        else if(ts_info.tuner_type == D_FEND_DVBS)
        {
            D_Char *strpol[] = {"H", "V", "L", "R", ""};
            sprintf(cinfo_data->freq_into, "%s %d %s %d", d_gui_get_text(atv_IDS_FREQ), ts_info.param.dvbs.freq, strpol[ts_info.param.dvbs.pol], ts_info.param.dvbs.baud);
        }
    }
    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_FREQ);
    if(vis)
    {
        d_label_set_text (vis, cinfo_data->freq_into);
    }

    update_evt_info ();

    return D_OK;
}

/** @brief 时间显示标签事件处理回调*/
static D_Result
time_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SI_GET_TDT:
            return update_time ();
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            break;
        default:
            break;
    }

    return D_ERR;
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
                case D_KEY_ESC:
                    return d_gui_close_frame (&atv_channel_info_window);
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            /*隐藏窗口*/
            return d_gui_close_frame (&atv_channel_info_window);
            break;
        case D_EVT_SI_GET_TDT:
        case D_EVT_SI_GET_EIT:
            return update_evt_info ();
            break;
        case D_EVT_DESTROY:
            if (cinfo_data)
            {
                if (cinfo_data->htimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy (cinfo_data->htimer);
                    cinfo_data->htimer == D_INVALID_HANDLE;
                }
                d_vis_unsubscribe_evt (vis);
                PROJECT_FREE(cinfo_data);
                cinfo_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}
/** @brief 窗口初始化*/
D_Result
atv_channel_info_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_StbPlayer *player;
    D_U32 menu_show_time;
    D_Result ad_check = D_ERR;
    D_U32 idx;

    player = p_stb_get_player (curr_player_id);
    if (! player)
        return D_ERR;

    cinfo_data = (ChanInfoData*) PROJECT_ALLOC (sizeof (ChanInfoData));
    if (! cinfo_data)
        return D_ERR;

    memset(cinfo_data, 0x00, sizeof (ChanInfoData));

    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_VIDEO);
    if (vis)d_vis_show(vis, D_FALSE);
    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_AUDIO);
    if (vis)d_vis_show(vis, D_FALSE);

    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_ICON);
    if (vis)d_vis_show(vis, D_FALSE);
    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_MULTIAUDIO);
    if (vis)d_vis_show(vis, D_FALSE);

    cinfo_data->vis_vtype = d_frame_get_control (frm, ID_SELECT_VIDEO_TYPE);
    cinfo_data->vis_atype = d_frame_get_control (frm, ID_SELECT_AUDIO_TYPE);

    if (cinfo_data->vis_vtype)
    {
        d_vis_show(cinfo_data->vis_vtype, D_FALSE);
        d_vis_set_focusable(cinfo_data->vis_vtype, D_FALSE);
    }
    if (cinfo_data->vis_atype)
    {
        d_vis_show(cinfo_data->vis_atype, D_FALSE);
        d_vis_set_focusable(cinfo_data->vis_atype, D_FALSE);
    }

    cinfo_data->menu_lang = p_conf_get_lang();

    cinfo_data->VideoType_cnt = sizeof(VideoType) / sizeof(VideoType[0]);
    for(idx = 0; idx < cinfo_data->VideoType_cnt; idx++)
    {
        cinfo_data->VideoTypeContent[idx] = VideoType[idx].string_val;
    }

    cinfo_data->AudioType_cnt = sizeof(AudioType) / sizeof(AudioType[0]);
    for(idx = 0; idx < cinfo_data->AudioType_cnt; idx++)
    {
        cinfo_data->AudioTypeContent[idx] = AudioType[idx].string_val;
    }
    d_select_box_set_content(cinfo_data->vis_vtype, cinfo_data->VideoTypeContent, cinfo_data->VideoType_cnt);
    d_select_box_set_content(cinfo_data->vis_atype, cinfo_data->AudioTypeContent, cinfo_data->AudioType_cnt);

    /*清除音量条*/
    p_atv_volume_window_hide();
#if 0
    menu_show_time = (D_U32)p_conf_get_info_time();
    if(menu_show_time < D_CONF_MIN_INFO_TIME)
    {
        menu_show_time = D_CONF_MIN_INFO_TIME;
    }
    else if(menu_show_time > D_CONF_MAX_INFO_TIME)
    {
        menu_show_time = D_CONF_MAX_INFO_TIME;
    }
#else
    menu_show_time = D_CONF_MIN_INFO_TIME;
#endif
    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*创建隐藏定时器*/
        cinfo_data->htimer = d_timer_create (NULL, menu_show_time * 1000, d_gui_get_queue());
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, cinfo_data->htimer);

        /*接收EIT事件更新显示*/
        d_vis_subscribe_evt (vis, D_EVT_SI_EIT_MASK, player->htv);

        /*接收TDT事件后重新显示PF*/
        d_vis_subscribe_evt (vis, D_EVT_SI_TDT_MASK, player->htv);

        /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

        /*注册事件回调*/
        d_vis_set_handler (vis, channel_info_window_handler);
    }

    vis = d_frame_get_control (frm, ID_CHANNEL_INFO_LABEL_DATA);
    if (vis)
    {
        /*根据TDT更新时间显示*/
        d_vis_subscribe_evt (vis, D_EVT_SI_TDT_MASK, player->htv);
        d_vis_set_handler (vis, time_handler);
    }

    /*显示时间*/
    update_time ();

    /*更新显示*/
    update_channel_info();


    return D_OK;
}

/** @breif 显示频道信息窗口*/
D_Result
p_atv_channel_info_window_show (D_ID player_id) D_FUNCPOSTFIT
{
    curr_player_id = player_id;
    return d_gui_open_frame(&atv_channel_info_window, D_GUI_LAYER_VIDEO_OSD);
}

/** @breif隐藏频道信息窗口*/
D_Result
p_atv_chan_info_window_hide(void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&atv_channel_info_window);
}

