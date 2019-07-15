#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dFMan.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "atv_search_window.c"
#include "pStbScan.h"
#include "dAV.h"
#include "pStbScan.h"
#include "ptvConfig.h"

typedef struct
{
    D_Visual *manual_text_vis; //手动搜索
    D_Visual *tune_text_vis;      //微调搜索
    D_Visual *np_vis;     //NP制式
    D_Visual *sound_mode_vis;     //声音制式
    D_Visual *skip_vis;   //跳过
    D_Char     manual_strnum[16];
    D_FEndFreq     manual_val;
    D_Char     tune_strnum[16];
    D_FEndFreq tune_val;
    D_HScan   hscan;
    D_S16       video_mode;
    D_S16       audio_mode;
    D_S16       skip;
    D_HFMan hfman;
    D_FEndParam fparam;
    D_DBSrvInfo srvinfo;
    D_Bool first_flag;
    D_Bool save_flag;
    D_S16       audio_mode_P;
    D_S16       audio_mode_N;
    D_Bool      find_srv;
} SearchStruct;


static SearchStruct *search_info;

extern D_FEndFreq china_atv_freq_list[];
extern D_U32 china_atv_freq_cnt;
static D_AtvScanParam atv_scanparam = {0};
static D_Bool av_play_flag = D_FALSE;

static char* D_DisplayMode[] = {"PAL", "NTSC", "AUTO"};

static char* SoundMode_String[3][4] =
{
    {"BG", "DK", "I"},
    {"M"},
    {"BG", "DK", "I", "M"},
};
static char SoundMode[3][4] =
{
    {D_AudioBG, D_AudioDK, D_AudioI},
    {D_AudioM},
    {D_AudioBG, D_AudioDK, D_AudioI, D_AudioM},
};

#define SEARCH_START_FREQ		(44250) 		
#define SEARCH_END_FREQ 		(869250)

static D_U16 SoundModeCnt[3] = {3, 1, 4};
static D_Ptr AutoScan_Op = (D_Ptr)(&ATV_AutoScan_Op);

static D_ID
get_audio_id(D_VideoMode vmode, D_AudioMode amode)D_FUNCPOSTFIT
{
    D_ID aid = -1, vid = 0, i;

    vid = (vmode == D_VideoP) ? 0 : 1;

    for(i = 0; i < SoundModeCnt[vid]; i++)
    {
        if(SoundMode[vid][i] == amode)
        {
            aid = i;
            break;
        }
    }
    return aid;
}

static D_Bool
judge_current_focus(D_Visual *vis)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_search_window;
    D_Visual *fvis;

    fvis = d_frame_get_control (frm, 0);
    fvis = d_vis_get_focus(fvis);

    return ((vis == fvis) ? D_TRUE : D_FALSE);
}


/*控制是否允许切换焦点*/
static D_Result
focus_change_enable(D_Bool enable)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_search_window;
    D_Visual *vis;

    vis = d_frame_get_control (frm, ID_SEARCH_GROUP_BG);
    if(enable)
    {
        d_vis_subscribe_evt (vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }
    else
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    return D_OK;
}

static D_Result
set_param_of_tv_tune(void) D_FUNCPOSTFIT
{
    if(search_info->hfman == D_INVALID_HANDLE)
        return D_ERR;

    search_info->fparam.freq = search_info->tune_val;
    search_info->fparam.atv.videoMode = search_info->video_mode;
    search_info->fparam.atv.audioMode = search_info->audio_mode;
    d_fman_set_param (search_info->hfman, &search_info->fparam, D_FALSE, D_FEND_ANALOG, NULL, NULL);
    return D_OK;
}

static D_Result
save_param_of_tv_tune(void) D_FUNCPOSTFIT
{
    D_ID srv;
    D_DBSrvInfo srvinfo;
    D_DBTSInfo  tsinfo;

    srv = p_stb_player_get_curr_srv(0);
    if(srv != -1 && D_OK == d_dbase_get_srv_info(srv, &srvinfo))
    {
        if(srvinfo.srv_type == D_DB_SRV_ATV && D_OK == d_dbase_get_ts_info(srvinfo.db_ts_id, &tsinfo))
        {
            tsinfo.param.atv.freq = search_info->tune_val;
            tsinfo.param.atv.videoMode = search_info->video_mode;
            tsinfo.param.atv.audioMode = search_info->audio_mode;
            tsinfo.param.atv.SoundSys = SoundSys_FmMono;
            d_dbase_updata_ts_info(srvinfo.db_ts_id, &tsinfo);

            srvinfo.aud1_codec = search_info->audio_mode;
            srvinfo.vid_codec = search_info->video_mode;
            srvinfo.skip = search_info->skip;

            d_dbase_update_srv_param(srv, &srvinfo, D_TRUE);
        }
    }

    return D_OK;
}

/* 取得对应频点*/
static D_FEndFreq 
get_match_freq_from_list(D_FEndFreq freq)D_FUNCPOSTFIT
{
    D_FEndFreq f;
    D_ID i;

    if(freq <= china_atv_freq_list[0])
    {
        f = china_atv_freq_list[0];
    }
    else if(freq >= china_atv_freq_list[china_atv_freq_cnt - 1])
    {
        f = china_atv_freq_list[china_atv_freq_cnt - 1];
    }
    else
    {
        for(i = 0; i < (china_atv_freq_cnt - 1); i++)
        {
            if(freq > china_atv_freq_list[i] && freq <= china_atv_freq_list[i + 1])
            {
                if(D_ABS(freq - china_atv_freq_list[i]) < D_ABS(freq - china_atv_freq_list[i + 1]))
                {
                    f = china_atv_freq_list[i];
                }
                {
                    f = china_atv_freq_list[i + 1];
                }
                break;
            }
        }
    }
    
    return f;
}

/*开始节目搜索*/
static D_Result
start_atv_manual_scan(D_U32 ifFreq, D_VideoMode  videoMode, D_AudioMode audioMode,D_Bool up_flag)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_search_window;
    D_Visual *win;
    D_ScanTaskConfig config = {0};

    memset(&atv_scanparam, 0x00, sizeof(D_AtvScanParam));

    #ifndef D_TV_IAMGE_SOURCE //按照频率表
    /*避免当前无节目时，无法搜索到第一个频点*/
    if(search_info->find_srv == D_FALSE && ifFreq == china_atv_freq_list[0])
    {
        ifFreq = china_atv_freq_list[0] - 50;
    }
    else
    {
        ifFreq = get_match_freq_from_list(ifFreq);
    }
    
    search_info->find_srv = D_TRUE;
    #endif
	
    config.buf_size = 64 * 1024;
    config.hqueue = d_gui_get_queue();
    config.priority = D_MANUAL_SCAN_TASK_PRIO;

    config.fend_type = D_FEND_ANALOG;
    config.fend_param.freq = ifFreq;
    config.fend_param.atv.videoMode = videoMode;
    config.fend_param.atv.audioMode = audioMode;
    config.fend_param.atv.SoundSys = SoundSys_FmMono;
    config.pScanOp = AutoScan_Op;
    config.pReserved = (D_Ptr)&atv_scanparam;
    config.Reserved = up_flag;

    /*用于配置搜索哪些类型的音视频*/
    atv_scanparam.audiomode[0] = videoMode;
    atv_scanparam.videomode[0] = audioMode;
    /*cnt == 0 时，以config.fend_param里的为准*/
    atv_scanparam.audiomode_cnt = 1;
    atv_scanparam.videomode_cnt = 1;

#ifdef D_TV_IAMGE_SOURCE
    /**<盲扫>*/
    config.startfreq = 49750-8000;
    config.endfreq = 869750;//386000;//
#else
#if 1
    /*按频率表搜索*/
    atv_scanparam.freq_cnt = china_atv_freq_cnt;
    atv_scanparam.freq_list = china_atv_freq_list;
    config.scan_type = D_ATV_SCAN_TYPE_AUTO;
    config.bandwitch = 7000; //正负2000
    config.stepfreq = 1000;
#else
    /*全频段搜索*/
    config.scan_type = D_ATV_SCAN_TYPE_FULL;
    config.startfreq = 112250;
    config.endfreq = 869750;
    config.bandwitch = 8000;
    config.stepfreq = 250;
#endif
#endif

    d_stb_stop_play();//先停止，是为了搜索过程中静音
    d_fman_set_suspend(search_info->hfman, D_TRUE);
// if(g_stb->player->status != D_STB_PLAYER_STATUS_PLAYING)
    {
        D_AVPlayParam play_param;

        play_param.mode = D_AV_PLAY_TV;
        d_av_play_while_searching(0, &play_param);
        av_play_flag = D_TRUE;
    }
    d_av_set_aud_mute(0, D_TRUE);
    search_info->hscan = p_atv_manual_scan_create(config);
    if (search_info->hscan == D_INVALID_HANDLE)
    {
        d_fman_set_suspend(search_info->hfman, D_FALSE);
        return D_ERR;
    }

    p_atv_menu_timeout_timer_enable(D_FALSE);
    win = d_frame_get_control (frm, 0);
    if(win)
    {
        d_vis_subscribe_evt (win, D_EVT_SCAN_MASK, search_info->hscan);
    }
    focus_change_enable(D_FALSE);
    D_DUMP("start_scan\n");
    return D_OK;

}

static D_U8 gStop_search_flag = 0;
/** @brief 手动搜索事件处理*/
static D_Result
atv_manual_search_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    //if(search_info->hscan == D_INVALID_HANDLE)
                {
                    if( gStop_search_flag == 0 && search_info->hscan != D_INVALID_HANDLE )
                    {
                        d_vis_unsubscribe_one_evt (vis, D_EVT_SCAN_MASK, search_info->hscan);
                        p_atv_manual_scan_destroy (search_info->hscan, D_FALSE);
                        search_info->hscan = D_INVALID_HANDLE;
                        focus_change_enable(D_TRUE);
                        d_fman_set_suspend(search_info->hfman, D_FALSE);
                        d_av_stop_while_searching(0);//为了后面的静音效果
                        p_stb_reset_mute_status();
                        gStop_search_flag = 1;
                    }
                    else
                    {
                        if(search_info->hscan == D_INVALID_HANDLE)
                        {
                            start_atv_manual_scan(search_info->fparam.freq, search_info->video_mode, search_info->audio_mode, D_FALSE);
                            gStop_search_flag = 1;
                        }
                        //sprintf(search_info->manual_strnum, "%0.2f", search_info->tune_val);
                        //d_label_set_text(search_info->manual_text_vis, search_info->manual_strnum);
                    }
                }
                return D_OK;
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if( gStop_search_flag == 1 && search_info->hscan != D_INVALID_HANDLE )
                    {
                        d_vis_unsubscribe_one_evt (vis, D_EVT_SCAN_MASK, search_info->hscan);
                        p_atv_manual_scan_destroy (search_info->hscan, D_FALSE);
                        search_info->hscan = D_INVALID_HANDLE;
                        focus_change_enable(D_TRUE);
                        d_fman_set_suspend(search_info->hfman, D_FALSE);
                        d_av_stop_while_searching(0);//为了后面的静音效果
                        p_stb_reset_mute_status();
                        gStop_search_flag = 0;
                    }
                    else
                    {
                        if(search_info->hscan == D_INVALID_HANDLE)
                        {
                            start_atv_manual_scan(search_info->fparam.freq, search_info->video_mode, search_info->audio_mode, D_TRUE);
                            gStop_search_flag = 0;
                            // sprintf(search_info->manual_strnum, "%0.2f", search_info->tune_val);
                            // d_label_set_text(search_info->manual_text_vis, search_info->manual_strnum);
                        }
                    }
                }
                return D_OK;
                break;
                default:
                    break;
            }
        }
        default:
            break;
    }
    return D_ERR;
}
/*设置声音制式参数*/
static D_Result set_tune_search(D_Float  tune_val)D_FUNCPOSTFIT
{
    D_DUMP("\n tune_val :%d \n", tune_val);
    return D_OK;
}

/** @brief 微调搜索事件处理*/
static D_Result
atv_tune_search_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    search_info->tune_val -= 50;
                    if(search_info->tune_val < SEARCH_START_FREQ) 
                    {
                        search_info->tune_val = (SEARCH_END_FREQ-50); 
                    }
                    sprintf(search_info->tune_strnum, "%d.%02d", (search_info->tune_val / 1000), ((search_info->tune_val % 1000)/10));
                    d_label_set_text(search_info->tune_text_vis, search_info->tune_strnum);
                    d_label_set_text(search_info->manual_text_vis, search_info->tune_strnum);
                    set_tune_search(search_info->tune_val);
                    set_param_of_tv_tune();
                    save_param_of_tv_tune();
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    search_info->tune_val += 50;
                    if(search_info->tune_val > SEARCH_END_FREQ)
                    {
                        search_info->tune_val = (SEARCH_START_FREQ+50); 
                    }
                    sprintf(search_info->tune_strnum, "%d.%02d", (search_info->tune_val / 1000), ((search_info->tune_val % 1000)/10));
                    d_label_set_text(search_info->tune_text_vis, search_info->tune_strnum);
                    d_label_set_text(search_info->manual_text_vis, search_info->tune_strnum);
                    set_tune_search(search_info->tune_val);
                    set_param_of_tv_tune();
                    save_param_of_tv_tune();
                }
                break;
                default:
                    break;
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_ERR;
}

/*设置彩色制式参数*/
static D_Result set_np_param(D_Bool first, D_Visual *cvis)D_FUNCPOSTFIT
{
    search_info->video_mode = d_select_box_get_val(cvis);
    D_DUMP("\n search_info->video_mode :%d \n", search_info->video_mode);
    return D_OK;
}

//彩色制式
static D_Result
np_change_handler(D_Visual *vis, D_Event *evt)
{
#if 0
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            if(search_info->first_flag == D_FALSE)
            {
                set_np_param(D_FALSE, vis);
                set_param_of_tv_tune();
                save_param_of_tv_tune();
            }
            return D_OK;
        default:
            break;
    }
#else
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            if(search_info->first_flag == D_FALSE && judge_current_focus(vis))
            {
                D_ID val;

                if(vis->element.select.val == 0 ) // PAL
                {
                    search_info->video_mode = D_VideoP;
                    search_info->audio_mode = search_info->audio_mode_P;
                }
                else if(vis->element.select.val == 1 )  // N
                {
                    search_info->audio_mode  = search_info->audio_mode_N;
                    search_info->video_mode = D_VideoN;
                }
                else  // AUTO
                {
                    search_info->audio_mode = 0;
                    search_info->video_mode = 2;
                }

                val = get_audio_id(search_info->video_mode, search_info->audio_mode);
                val = D_MAX(val, 0);
                d_select_box_set_content(search_info->sound_mode_vis, SoundMode_String[search_info->video_mode], SoundModeCnt[search_info->video_mode]);
                d_select_box_set_val(search_info->sound_mode_vis, val);

                //set_np_param(D_FALSE, vis);
                set_param_of_tv_tune();
                save_param_of_tv_tune();
            }
            return D_OK;
        default:
            break;
    }
#endif
    return D_ERR;
}

/*设置声音制式参数*/
static D_Result set_sound_param(D_Bool first, D_Visual *cvis)D_FUNCPOSTFIT
{
    if(search_info->video_mode == 0)
    {
        search_info->audio_mode = d_select_box_get_val(cvis);
    }
    else if(search_info->video_mode == 1)
    {
        search_info->audio_mode = d_select_box_get_val(cvis);
        if( search_info->audio_mode == 2 )
        {
            search_info->audio_mode += 1;
        }
    }
    else if(search_info->video_mode == 2)
    {
        search_info->audio_mode = d_select_box_get_val(cvis);
    }
    D_DUMP("\n search_info->audio_mode :%d \n", search_info->audio_mode);
    return D_OK;
}

//声音制式
static D_Result
sound_change_handler(D_Visual *vis, D_Event *evt)
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            if(search_info->first_flag == D_FALSE && judge_current_focus(vis))
            {
                search_info->audio_mode = SoundMode[search_info->video_mode][d_select_box_get_val(vis)];

                if(search_info->video_mode == D_VideoP)
                {
                    search_info->audio_mode_P = search_info->audio_mode;
                }
                else if(search_info->video_mode == D_VideoN)
                {
                    search_info->audio_mode_N = search_info->audio_mode;
                }
                set_param_of_tv_tune();
                save_param_of_tv_tune();
            }
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}


//跳过
static D_Result
skip_change_handler(D_Visual *vis, D_Event *evt)
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            if(search_info->first_flag == D_FALSE && judge_current_focus(vis))
            {
                search_info->skip = d_select_box_get_val(vis);
                //set_param_of_tv_tune();
                save_param_of_tv_tune();
            }
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}

static D_Result
update_freq_info(D_FEndParam *fparam)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_search_window;
    D_Visual *vis;

    if(!fparam)
    {
        return D_ERR;
    }

    if(search_info->manual_text_vis)
    {
        search_info->manual_val = (D_FEndFreq)((D_Float)fparam->atv.freq);
        sprintf(search_info->manual_strnum, "%d.%02d", (search_info->manual_val / 1000), ((search_info->manual_val % 1000)/10));
        d_label_set_text(search_info->manual_text_vis, search_info->manual_strnum);
    }

    if(search_info->tune_text_vis)
    {
        search_info->tune_val = search_info->manual_val;
        sprintf(search_info->tune_strnum, "%d.%02d", (search_info->tune_val / 1000), ((search_info->tune_val % 1000)/10));
        d_label_set_text(search_info->tune_text_vis, search_info->tune_strnum);
    }
#if 0
    if(search_info->np_vis)
    {
        search_info->video_mode = fparam->atv.videoMode;
        d_select_box_set_val(search_info->np_vis, search_info->video_mode);
    }

    if(search_info->sound_mode_vis)
    {
        search_info->audio_mode = fparam->atv.audioMode;
        d_select_box_set_val(search_info->sound_mode_vis, search_info->audio_mode);
    }
#endif
    return D_OK;
}


static D_Result
show_channel_info(D_FEndParam *fparam)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_search_window;
    D_Visual *vis;

    if(!fparam)
    {
        return D_ERR;
    }

    if(search_info->manual_text_vis)
    {
        search_info->manual_val = (D_FEndFreq)fparam->atv.freq;
        sprintf(search_info->manual_strnum,  "%d.%02d", (search_info->manual_val / 1000), ((search_info->manual_val % 1000)/10));
        d_label_set_text(search_info->manual_text_vis, search_info->manual_strnum);
    }

    if(search_info->tune_text_vis)
    {
        search_info->tune_val = search_info->manual_val;
        sprintf(search_info->tune_strnum,  "%d.%02d", (search_info->tune_val / 1000), ((search_info->tune_val % 1000)/10));
        d_label_set_text(search_info->tune_text_vis, search_info->tune_strnum);
    }

    if(search_info->np_vis)
    {
        search_info->video_mode = fparam->atv.videoMode;
        d_select_box_set_val(search_info->np_vis, search_info->video_mode);
    }

    if(search_info->sound_mode_vis)
    {
        D_ID val;
        search_info->audio_mode = fparam->atv.audioMode;
        val = get_audio_id(search_info->video_mode, search_info->audio_mode);
        val = D_MAX(val, 0);
        d_select_box_set_content(search_info->sound_mode_vis, SoundMode_String[search_info->video_mode], SoundModeCnt[search_info->video_mode]);
        d_select_box_set_val(search_info->sound_mode_vis, val);
    }
    if(search_info->skip_vis)
    {
        d_select_box_set_val(search_info->skip_vis, search_info->skip);
    }

    return D_OK;
}

static D_Result
save_channel_info(void)D_FUNCPOSTFIT
{
    D_ID dbtsid, dbsrvid;
    D_DBSrvInfo srvinfo;
    D_DBTSInfo tsinfo;
    D_ATVSCAN_SET scan_set;

    p_tvconf_get_cur_atvscan(&scan_set);

    dbsrvid = p_stb_player_get_curr_srv(0);
    if(D_OK == d_dbase_get_srv_info(dbsrvid, &srvinfo) && srvinfo.srv_type == D_DB_SRV_ATV)
    {
        d_dbase_get_ts_info(srvinfo.db_ts_id, &tsinfo);
        tsinfo.param = search_info->fparam;
        tsinfo.param.atv.fltCenterAdj = scan_set.fltCenterAdj;
        tsinfo.param.atv.fltBwAdj = scan_set.fltBwAdj;
        d_dbase_update_ts_param(srvinfo.db_ts_id, &tsinfo, D_TRUE);
        
        srvinfo.aud1_codec = search_info->srvinfo.aud1_codec;
        srvinfo.vid_codec = search_info->srvinfo.vid_codec;
        srvinfo.skip = search_info->skip;
        d_dbase_update_srv_param(dbsrvid, &srvinfo, D_TRUE);
        
        goto _SAVEOK;
    }

    D_DB_TS_INFO_INIT(&tsinfo);
    tsinfo.tuner_type = D_FEND_ANALOG;
    tsinfo.db_net_id = 0;
    tsinfo.param = search_info->fparam;
    tsinfo.param.atv.fltCenterAdj = scan_set.fltCenterAdj;
    tsinfo.param.atv.fltBwAdj = scan_set.fltBwAdj;
    dbtsid = d_dbase_insert_ts(&tsinfo);
    if(dbtsid == -1)
    {
        return D_ERR;
    }
    
    srvinfo = search_info->srvinfo;
    srvinfo.db_ts_id = dbtsid;
    srvinfo.srv_type = D_DB_SRV_ATV;
    srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
    sprintf(srvinfo.name, "ATV-%02d", srvinfo.chan_num);
    dbsrvid = d_dbase_insert_srv(&srvinfo);
    
_SAVEOK:
    if(av_play_flag)
    {
        av_play_flag = D_FALSE;
    }
    d_av_stop_while_searching(0);//为了后面的静音效果
    p_stb_reset_mute_status();
    p_stb_player_play_srv(0, dbsrvid);

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_search_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {

            switch (evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                {
                    return d_gui_upper_menu();
                }
                break;
                case D_KEY_ESC:
                    return d_gui_clear_menu();
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                {
#if 0
                    D_S16 temp;

                    temp = search_info->cur_val;
                    search_info->cur_val = search_info->search_val;
                    search_info->search_val = temp;

                    sprintf(search_info->cur_strnum, "%d", search_info->cur_val);
                    d_label_set_text(search_info->cur_lable_vis, search_info->cur_strnum);

                    sprintf(search_info->search_strnum, "%d", search_info->search_val);
                    d_label_set_text(search_info->search_lable_vis, search_info->search_strnum);
#endif
                }
                break;
                case D_KEY_UP:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                case D_KEY_PNL_U:
                    search_info->first_flag == D_FALSE;
                    if (search_info->hscan != D_INVALID_HANDLE)
                    {
                        return D_OK;
                    }
                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_SCAN_FREQ:
            search_info->fparam.freq = evt->scan.fendparam.freq;
            update_freq_info(&(search_info->fparam));
            break;
        case D_EVT_SCAN_DATA:
            search_info->fparam = evt->scan.fendparam;
            search_info->srvinfo = evt->scan.srvinfo;
            show_channel_info(&(search_info->fparam));
            search_info->save_flag = D_TRUE;
            break;
        case D_EVT_SCAN_OK:
            /*搜索完毕*/
            if (search_info->hscan != D_INVALID_HANDLE)
            {
                d_vis_unsubscribe_one_evt (vis, D_EVT_SCAN_MASK, search_info->hscan);
                p_atv_manual_scan_destroy (search_info->hscan, D_TRUE);
                search_info->hscan = D_INVALID_HANDLE;
                if(av_play_flag)
                {
                    d_av_stop(0);
                    av_play_flag = D_FALSE;
                }
                
                focus_change_enable(D_TRUE);
                p_atv_menu_timeout_timer_enable(D_TRUE);
                d_fman_set_suspend(search_info->hfman, D_FALSE);
                d_av_stop_while_searching(0);//为了后面的静音效果
                p_stb_reset_mute_status();
            }
            if(av_play_flag)
            {
                d_av_stop(0);
                av_play_flag = D_FALSE;
            }            
            if(search_info->save_flag)
            {
                search_info->save_flag= D_FALSE;
                save_channel_info();
            }
            
            return D_OK;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(search_info)
            {
                if (search_info->hscan != D_INVALID_HANDLE)
                {
                    p_atv_manual_scan_destroy (search_info->hscan, D_TRUE);
                    search_info->hscan = D_INVALID_HANDLE;
                    p_atv_menu_timeout_timer_enable(D_TRUE);
                    d_fman_set_suspend(search_info->hfman, D_FALSE);
                    d_av_stop_while_searching(0);//为了后面的静音效果
                    p_stb_reset_mute_status();
                    p_stb_player_play_valid (0);
                }
                
                d_fman_set_monitor_mode(search_info->hfman, D_TRUE);
                PROJECT_FREE(search_info);
                search_info = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_search_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_StbPlayer *player;
    D_ID srv;
    D_DBSrvInfo srvinfo;
    D_DBTSInfo  tsinfo;

    search_info = PROJECT_ALLOC(sizeof (SearchStruct));
    if (! search_info)
        return D_ERR;

    memset(search_info, 0, sizeof (SearchStruct));
    search_info->hscan = D_INVALID_HANDLE;
    search_info->hfman = D_INVALID_HANDLE;
    search_info->first_flag = D_TRUE;

    vis = d_frame_get_control (frm, ID_SEARCH_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, ID_SEARCH_BUTTON_FUN1);
    if(vis)
    {
        //d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE); //注册消息等待搜索发过来频点
        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_manual_search_handler);
    }

    search_info->manual_text_vis = d_frame_get_control (frm, ID_SEARCH_LABLE_MANUAL_TEXT);
    search_info->tune_text_vis = d_frame_get_control (frm, ID_SEARCH_LABLE_TUNE_TEXT2);
    search_info->np_vis = d_frame_get_control (frm, ID_SEARCH_SELECT_NP);
    search_info->sound_mode_vis = d_frame_get_control (frm, ID_SEARCH_SECLECT_VOICE);

    vis = d_frame_get_control (frm, ID_SEARCH_LABLE_MHZ1);
    if(vis)
    {
        d_label_set_text(vis, "MHz");
    }

    vis = d_frame_get_control (frm, ID_SEARCH_BUTTON_FUN2);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_tune_search_handler);
    }

    vis = d_frame_get_control (frm, ID_SEARCH_LABLE_MHZ2);
    if(vis)
    {
        d_label_set_text(vis , "MHz");
    }

    if(search_info->np_vis)
    {
        //获取数据库的NP制式
        d_vis_set_handler (search_info->np_vis, np_change_handler);
    }

    if(search_info->sound_mode_vis)
    {
        d_vis_set_handler (search_info->sound_mode_vis, sound_change_handler);
    }

    search_info->skip_vis = d_frame_get_control (frm, ID_SEARCH_SELECT_ONOFF);
    {
        //获取数据库的跳过
        search_info->skip = 0;
        d_vis_set_handler (search_info->skip_vis, skip_change_handler);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_search_window_handler);
    }

    search_info->hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
    d_fman_set_monitor_mode(search_info->hfman, D_FALSE);

    srv = p_stb_player_get_curr_srv(0);
    if(srv != -1 && D_OK == d_dbase_get_srv_info(srv, &srvinfo))
    {
        search_info->skip = srvinfo.skip;
        if(srvinfo.srv_type == D_DB_SRV_ATV && D_OK == d_dbase_get_ts_info(srvinfo.db_ts_id, &tsinfo))
        {
            search_info->fparam = tsinfo.param;
            search_info->find_srv = D_TRUE;
        }
    }

    /*当前无节目时，取列表第一个频点*/
    if(search_info->fparam.freq == 0)
    {
        search_info->fparam.freq = china_atv_freq_list[0];
        search_info->fparam.atv.videoMode = D_VideoP;
        search_info->fparam.atv.audioMode = D_AudioDK;
        search_info->fparam.atv.SoundSys = SoundSys_FmMono;
    }
    search_info->tune_val = search_info->fparam.freq;
    search_info->video_mode = search_info->fparam.atv.videoMode;
    search_info->audio_mode = search_info->fparam.atv.audioMode;
    search_info->audio_mode_N = D_AudioM;
    search_info->audio_mode_P = D_AudioDK;

    if( search_info->fparam.atv.videoMode == D_VideoP)
    {
        if(search_info->fparam.atv.audioMode == D_AudioM)
        {
            search_info->audio_mode = D_AudioDK;
            set_param_of_tv_tune();
            save_param_of_tv_tune();
        }

        search_info->audio_mode_P = search_info->audio_mode;
    }
    else if( search_info->fparam.atv.videoMode == D_VideoN)
    {
        if(search_info->fparam.atv.audioMode != D_AudioM)
        {
            search_info->audio_mode = D_AudioM;
            set_param_of_tv_tune();
            save_param_of_tv_tune();
        }
        search_info->audio_mode_N = search_info->audio_mode;
    }
	else
	{
		search_info->fparam.atv.videoMode = D_VideoP;
		search_info->audio_mode = D_AudioDK;
	    search_info->audio_mode_P = search_info->audio_mode;		
        set_param_of_tv_tune();
        save_param_of_tv_tune();
	}
    if(search_info->find_srv == D_FALSE)
    {
        set_param_of_tv_tune();
    }

    show_channel_info(&(search_info->fparam));
    search_info->first_flag = D_FALSE;
    return D_OK;
}

/** @brief 显示频道搜索菜单*/
D_Result
p_atv_search_show ( void (*pFunc)()) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_search_window, D_FALSE);
}

