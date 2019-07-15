/** @file
* @brief 窗口模块                            
* @author田青black
* @date 2009-7-9 田青: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pPopMsg.h"
#include "pGuiResource.h"
#include "pStbMenus.h"
#include "pMem.h"
#include "pPlayer.h"
#include "dFP.h"
#include "dtmb_chan_info_test_window.c"

#define DEF_FEND_TYPE D_FEND_DTMB

/*前端定期检查定时器*/
#define D_FEND_CHECK_TIME   (500)

#define PLAYER_ID       (0)
#define BUFFER_LEN      (16)
#define SELECT_CNT      (16)

typedef struct
{
    D_U32   val;
    D_Char  string_val[BUFFER_LEN];
} D_StringDate;

static D_StringDate fendMode[] =
{
    {(D_U32)D_FEND_QAM16, "QAM16"},
    {(D_U32)D_FEND_QAM32, "QAM32"},
    {(D_U32)D_FEND_QAM64, "QAM64"},
    {(D_U32)D_FEND_QAM128, "QAM128"},
    {(D_U32)D_FEND_QAM256, "QAM256"},
};

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

static D_StringDate  FormatType[] =
{
    {(D_U32)D_VID_FMT_PAL , "PAL(576I@50)"},
    {(D_U32)D_VID_FMT_NTSC, "NTSC(480I@60)"},
    {(D_U32)D_VID_FMT_480P_60, "480P@60"},
    {(D_U32)D_VID_FMT_576P_50, "576P@50"},
    {(D_U32)D_VID_FMT_720P_50, "720P@50"},
    {(D_U32)D_VID_FMT_720P_60, "720P@60"},
    {(D_U32)D_VID_FMT_1080I_50, "1080I@50"},
    {(D_U32)D_VID_FMT_1080I_60, "1080I@60"},
    {(D_U32)D_VID_FMT_1080P_50, "1080P@50"},
    {(D_U32)D_VID_FMT_1080P_60, "1080P@60"},
};


typedef struct
{
    D_HFMan     hfman;
    D_HTimer    fend_timer;
    D_FEndParam fendparam;
    D_FEndType   fendtype;

    D_Char Frequency[BUFFER_LEN];
    D_Char Symbol[BUFFER_LEN];
    D_Char *ModeContent[SELECT_CNT];
    D_U16   mode_cnt;
    D_Char VideoPID[BUFFER_LEN];
    D_Char AudioPID[BUFFER_LEN];
    D_Char PCRPID[BUFFER_LEN];

    D_Char *VideoTypeContent[SELECT_CNT];
    D_U16   VideoType_cnt;

    D_Char *AudioTypeContent[SELECT_CNT];
    D_U16   AudioType_cnt;

    D_Char *VidFormatContent[SELECT_CNT];
    D_U16   VidFormat_cnt;

    D_VidFormat format;

    D_DBSrvInfo srv_info;
    D_DBTSInfo  ts_info;

    D_Bool  edit_enale;

    D_Visual    *vis_freq;
    D_Visual    *vis_baud;
    D_Visual    *vis_mod;
    D_Visual    *vis_vpid;
    D_Visual    *vis_vtype;
    D_Visual    *vis_apid;
    D_Visual    *vis_atype;
    D_Visual    *vis_pcr;
    D_Visual    *vis_vout;
    D_Visual    *vis_strength;
    D_Visual    *vis_quality;

} D_ChanInfoData;

static D_ChanInfoData *chan_info = NULL;
static D_U8 comb_status = 0;




static D_Result
param_edit_enable(D_Bool enable)
{
    if(chan_info->edit_enale != enable)
    {
        d_vis_enable(chan_info->vis_freq, enable);
        d_vis_enable(chan_info->vis_baud, enable);
        d_vis_enable(chan_info->vis_mod, enable);
        d_vis_enable(chan_info->vis_vpid, enable);
        d_vis_enable(chan_info->vis_apid, enable);
        d_vis_enable(chan_info->vis_vtype, enable);
        d_vis_enable(chan_info->vis_atype, enable);
        d_vis_enable(chan_info->vis_vout, enable);
        d_vis_enable(chan_info->vis_pcr, enable);
        chan_info->edit_enale = enable;
    }

    if(chan_info->edit_enale)
    {
        /*因为有信号的锁定，要停播*/
        d_stb_stop_play();
        /*清除残留视频帧*/
        p_stb_player_clear_vid(PLAYER_ID);
    }

    return D_OK;
}

/*显示频点信息*/
static D_Result
show_init_param_info(D_DBTSInfo ts_info, D_DBSrvInfo srv_info)
{
    D_U16   pid, val = 0, i;
    D_U16   type;

    sprintf(chan_info->Frequency, "%03d.%01d", ts_info.param.freq, ts_info.param.dtmb.freq_k);
    d_input_box_set_text(chan_info->vis_freq, chan_info->Frequency, strlen(chan_info->Frequency));
	if(p_conf_get_scan_config())
	{
	    sprintf(chan_info->Symbol, "%04d", ts_info.param.dvbc.baud);
	    d_input_box_set_text(chan_info->vis_baud, chan_info->Symbol, strlen(chan_info->Symbol));

	    ts_info.param.dvbc.mod = D_MIN(ts_info.param.dvbc.mod, D_FEND_QAM256);
	    d_select_box_set_val(chan_info->vis_mod, (D_U16)ts_info.param.dvbc.mod);
	}
    sprintf(chan_info->VideoPID, "%04d", (D_U16)srv_info.vid_pid);
    d_input_box_set_text(chan_info->vis_vpid, chan_info->VideoPID, strlen(chan_info->VideoPID));

    d_select_box_set_val(chan_info->vis_vtype, (D_U16)srv_info.vid_codec);

    pid = D_DB_GET_SRV_AUD(&srv_info);
    sprintf(chan_info->AudioPID, "%04d", pid);
    d_input_box_set_text(chan_info->vis_apid, chan_info->AudioPID, strlen(chan_info->AudioPID));

    type = (D_U16)D_DB_GET_SRV_AUD_CODEC(&srv_info);
    for(i = 0; i < chan_info->AudioType_cnt; i++)
    {
        if(AudioType[i].val == type)
        {
            val = i;
            break;
        }
    }
    d_select_box_set_val(chan_info->vis_atype, val);

    sprintf(chan_info->PCRPID, "%04d", (D_U16)srv_info.pcr_pid);
    d_input_box_set_text(chan_info->vis_pcr, chan_info->PCRPID, strlen(chan_info->PCRPID));

    type = 0;
    for(pid = 0; pid < chan_info->VideoType_cnt; pid++)
    {
        if(chan_info->format == FormatType[pid].val)
        {
            type = pid;
            break;
        }
    }
    d_select_box_set_val(chan_info->vis_vout, type);

    return D_OK;
}

/*设置前端参数*/
static D_Result set_fend_param(D_Bool first, D_Visual *cvis)D_FUNCPOSTFIT
{
    D_FEndParam param = {0};

    param.freq = (D_U32)d_input_box_get_num(chan_info->vis_freq);
	if(p_conf_get_scan_config())
	{
		param.dvbc.baud = (D_U32)d_input_box_get_num(chan_info->vis_baud);
    	param.dvbc.mod = (D_U32)((D_U16)d_select_box_get_val(chan_info->vis_mod));
	}
    if (chan_info->edit_enale && (D_FALSE == d_fend_param_equal (chan_info->fendtype, &(chan_info->fendparam), &param)))
    {
        chan_info->fendparam = param;
        d_fman_set_param(chan_info->hfman, &chan_info->fendparam, D_FALSE, chan_info->fendtype, NULL, NULL);
        d_fman_get_status_req (chan_info->hfman, d_gui_get_queue ());
        d_timer_reset(chan_info->fend_timer, D_FEND_CHECK_TIME);
    }

    return D_OK;
}


/*显示信号信息(强度与质量)*/
static D_Result
show_signal_status(D_Bool locked, D_U8 strength, D_U8 quality)
{
    D_U16   frontcolourid;
	D_Char	led[5];

    strength = D_MIN(strength, 100);
    quality = D_MIN(quality, 100);
    frontcolourid = (locked) ? ((D_U16) - 1) : ID_COLOUR_RED;

    d_progress_bar_set_front_colour(chan_info->vis_strength, frontcolourid);
    d_progress_bar_set_val(chan_info->vis_strength, strength);

    d_progress_bar_set_front_colour(chan_info->vis_quality, frontcolourid);
    d_progress_bar_set_val(chan_info->vis_quality, quality);

	snprintf (led, sizeof(led), "P%03d", quality);
	d_fp_set_led (0, led);

    return D_OK;
}


static D_Result
try_to_play_handler(D_Bool sel,  D_U32 param)
{
    D_S16  val;
    D_DBID  dbid;
    D_DBSrvInfo srv_info;
    D_DBTSInfo ts_info;
    D_StbPlayer *player;
    D_Bool play_flag = D_FALSE;

    if(!sel)
    {
        return D_OK;
    }

    D_DB_SRV_INFO_INIT(&srv_info);

    val = (D_S16)d_input_box_get_num(chan_info->vis_vpid);
    srv_info.vid_pid = (D_U16)val;

    val = (D_S16)d_input_box_get_num(chan_info->vis_apid);
    srv_info.aud1_pid = (D_U16)val;

    val = (D_S16)d_input_box_get_num(chan_info->vis_pcr);
    srv_info.pcr_pid = (D_U16)val;

    val = (D_U16)d_select_box_get_val(chan_info->vis_vtype);
    srv_info.vid_codec = (D_VidCodecType)val;

    val = (D_U16)d_select_box_get_val(chan_info->vis_atype);
    srv_info.aud1_codec = (D_AudCodecType)AudioType[val].val;

    D_INFO("try to play srv: vpid %d type %d, apid %d type %d, pcr %d\n", srv_info.vid_pid,
           srv_info.vid_codec, srv_info.aud1_pid, srv_info.aud1_codec, srv_info.pcr_pid);

    dbid = d_dbase_get_ts_by_param(0, chan_info->fendtype, &(chan_info->fendparam));
    if(dbid == -1)
    {
        D_DB_TS_INFO_INIT(&ts_info);
        ts_info.param = chan_info->fendparam;
        ts_info.tuner_type = chan_info->fendtype;
        ts_info.db_net_id = 0;
        dbid = d_dbase_insert_ts_ex(&ts_info, D_TRUE);
    }

    if(dbid != -1)
    {
        srv_info.db_ts_id = dbid;
        srv_info.chan_num = 888;
        srv_info.srv_id = (D_U16)(-1);
        sprintf(srv_info.name, "%s", "Test channel");
        srv_info.srv_type = D_DB_SRV_TV;

        dbid = d_dbase_insert_srv_ex(&srv_info, D_TRUE);
    }

    if(dbid != -1)
    {
        player = p_stb_get_player(PLAYER_ID);
        if(player)
        {
            val = d_select_box_get_val(chan_info->vis_vout);
            d_tv_set_vid_format(player->htv, (D_VidFormat)FormatType[val].val);
            p_conf_set_vid_fmt((D_VidFormat)FormatType[val].val);
            if(D_OK == p_stb_player_play_srv(PLAYER_ID, dbid))
            {
                play_flag = D_TRUE;
            }
        }
    }
    if(play_flag == D_FALSE)
    {
        chan_info->edit_enale = D_FALSE;
    }
    d_gui_close_frame(&chan_info_test_window);

    return D_OK;

}

static D_Result
freq_param_change_handler(D_Visual *vis, D_Event *evt)
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
        case D_EVT_DATA_CHANGED:
            set_fend_param(D_FALSE, vis);
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 事件处理*/
static D_Result chan_info_test_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
   D_Char	led[5];
   
    switch (evt->type)
    {
        case D_EVT_FP:

            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                    return d_gui_close_frame(&chan_info_test_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(chan_info->edit_enale)
                    {
                        d_pop_select_show (D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_IME,
                        "", "Try to play the service ?", 0, D_TRUE, try_to_play_handler, 0);
                    }
                    else
                    {
                        d_gui_close_frame(&chan_info_test_window);
                    }
                    break;
                case D_KEY_2:
                    if(comb_status == 0)
                    {
                        comb_status += 0x01;
                    }
                    break;
                case D_KEY_3:
                    if(comb_status == 0x01)
                    {
                        comb_status += 0x02;
                    }
                    break;
                case D_KEY_0:
                    if(comb_status == 0x03)
                    {
                        comb_status += 0x04;
                    }
                    break;
                case D_KEY_9:
                    if(comb_status == 0x07)
                    {
                        comb_status += 0x08;
                        if((comb_status == 0x0f) && (chan_info->edit_enale == D_FALSE))
                        {
                            comb_status = 0;
                            param_edit_enable(D_TRUE);
                        }
                    }
                    break;
                default:
                    comb_status = 0;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(chan_info->fend_timer == evt->timer.htimer)
            {
                d_fman_get_status_req (chan_info->hfman, d_gui_get_queue ());
                return D_OK;
            }
            break;
        case D_EVT_FEND_STATUS:
            return show_signal_status(evt->fend.status.locked, evt->fend.status.strength, evt->fend.status.quanlity);
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);

		if(chan_info->srv_info.srv_type ==D_DB_SRV_TV)
			snprintf (led, sizeof(led), "C%03d",  chan_info->srv_info.chan_num);
		else if(chan_info->srv_info.srv_type ==D_DB_SRV_RADIO)
			snprintf (led, sizeof(led), "A%03d", chan_info->srv_info.chan_num);

		d_fp_set_led (0, led);
	
            if(chan_info->fend_timer != D_INVALID_HANDLE)
            {
                d_timer_destroy(chan_info->fend_timer);
                chan_info->fend_timer = D_INVALID_HANDLE;
                d_fman_set_param(chan_info->hfman, &chan_info->fendparam, D_TRUE, chan_info->fendtype, NULL, NULL);
                p_stb_player_play_valid (0);
                p_signal_faint_msg_reshow();
                d_fman_get_locked_req(chan_info->hfman, d_gui_get_queue());
            }
            PROJECT_FREE(chan_info);
            chan_info = NULL;
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result chan_info_test_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_DBSrvID   srv;
    D_U32 idx;

    chan_info = (D_ChanInfoData*)PROJECT_ALLOC(sizeof(D_ChanInfoData));
    if(!chan_info)
        return D_ERR;

    memset(chan_info, 0x00, sizeof(D_ChanInfoData));
    //chan_info->edit_enale = D_TRUE;
    chan_info->fendtype = DEF_FEND_TYPE;
    chan_info->format = p_conf_get_vid_fmt();

    D_DB_SRV_INFO_INIT(&(chan_info->srv_info));
    D_DB_TS_INFO_INIT(&(chan_info->ts_info));
    srv = p_stb_player_get_curr_srv(PLAYER_ID);
    if (d_dbase_get_srv_info (srv, &(chan_info->srv_info)) >= 0)
    {
        d_dbase_get_ts_info(chan_info->srv_info.db_ts_id, &(chan_info->ts_info));
        chan_info->fendtype = chan_info->ts_info.tuner_type;
        chan_info->fendparam = chan_info->ts_info.param;
    }
    chan_info->hfman = d_fman_get_handle_by_type(chan_info->fendtype, 0);

    chan_info->mode_cnt = sizeof(fendMode) / sizeof(fendMode[0]);
    for(idx = 0; idx < chan_info->mode_cnt; idx++)
    {
        chan_info->ModeContent[idx] = fendMode[idx].string_val;
    }

    chan_info->VideoType_cnt = sizeof(VideoType) / sizeof(VideoType[0]);
    for(idx = 0; idx < chan_info->VideoType_cnt; idx++)
    {
        chan_info->VideoTypeContent[idx] = VideoType[idx].string_val;
    }

    chan_info->AudioType_cnt = sizeof(AudioType) / sizeof(AudioType[0]);
    for(idx = 0; idx < chan_info->AudioType_cnt; idx++)
    {
        chan_info->AudioTypeContent[idx] = AudioType[idx].string_val;
    }

    chan_info->VidFormat_cnt = sizeof(FormatType) / sizeof(FormatType[0]);
    for(idx = 0; idx < chan_info->VidFormat_cnt; idx++)
    {
        chan_info->VidFormatContent[idx] = FormatType[idx].string_val;
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_FEND_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, chan_info_test_window_handler);
        /*创建前端定期检查定时器*/
        chan_info->fend_timer = d_timer_create (NULL, D_FEND_CHECK_TIME, d_gui_get_queue ());
        if(chan_info->fend_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, chan_info->fend_timer);
        }
    }

    chan_info->vis_freq = d_frame_get_control (frm, D_INPUT_FREQ);
    chan_info->vis_mod = d_frame_get_control (frm, ID_SELECT_MODE);
    chan_info->vis_vpid = d_frame_get_control (frm, ID_INPUT_VID_PID);
    chan_info->vis_vtype = d_frame_get_control (frm, ID_SELECT_VIDEO_TYPE);
    chan_info->vis_apid = d_frame_get_control (frm, ID_INPUT_AUD_PID);
    chan_info->vis_atype = d_frame_get_control (frm, ID_SELECT_AUDIO_TYPE);
    chan_info->vis_pcr = d_frame_get_control (frm, ID_INPUT_PCR_PID);
    //chan_info->vis_vout = d_frame_get_control (frm, ID_SELECT_VIDOUTPUT_TYPE);
    chan_info->vis_strength = d_frame_get_control (frm, ID_PROGRESS_STRENGTH);
    chan_info->vis_quality = d_frame_get_control (frm, ID_PROGRESS_QUALYTY);

	if(p_conf_get_scan_config())
	{   
		d_select_box_set_content(chan_info->vis_mod, chan_info->ModeContent, chan_info->mode_cnt);
	}
	else
	{
    	d_vis_set_focusable(chan_info->vis_mod, D_FALSE);
	}
    d_select_box_set_content(chan_info->vis_vtype, chan_info->VideoTypeContent, chan_info->VideoType_cnt);
    d_select_box_set_content(chan_info->vis_atype, chan_info->AudioTypeContent, chan_info->AudioType_cnt);
    d_select_box_set_content(chan_info->vis_vout, chan_info->VidFormatContent, chan_info->VidFormat_cnt);

    show_init_param_info(chan_info->ts_info, chan_info->srv_info);

    d_vis_set_handler(chan_info->vis_freq, freq_param_change_handler);
	if(p_conf_get_scan_config())
	{
	    d_vis_set_handler(chan_info->vis_baud, freq_param_change_handler);
	    d_vis_set_handler(chan_info->vis_mod, freq_param_change_handler);
	}
    chan_info->edit_enale = D_TRUE;
    param_edit_enable(D_FALSE);

    show_signal_status(D_FALSE, 0, 0);
    set_fend_param(D_TRUE, NULL);

    return D_OK;
}

/** @breif 显示节目相关信息窗口(用于测试)*/
D_Result d_dtmb_chan_info_test_window_show () D_FUNCPOSTFIT
{
    return d_gui_open_frame(&chan_info_test_window, D_GUI_LAYER_MESSAGE);
}

D_Result d_dtmb_chan_info_test_window_hide () D_FUNCPOSTFIT
{
    return d_gui_close_frame(&chan_info_test_window);
}

