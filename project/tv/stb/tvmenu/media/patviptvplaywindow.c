/** @file
* @brief iptv play Window
* @author
* @date 2018-01-24: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pMenu.h"
#include "pPlayer.h"
#include "pMem.h"
#include "pFile_Scan.h"
#include "dMedia.h"
#include "pConfig.h"
#include "pConvCode.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dCBMan.h"
#include "dPvrReplay.h"
#include "player_api.h"

#include "atv_iptv_play_window.c"

#define IPTV_FULL_MOVIE_PLAY_REFRESH_TIME (1000)
#define IPTV_FULL_MOVIE_MENU_SHOW_TIME    (5000)

#define IPTV_FULL_MOVIE_PATH_NAME_LEN  (1024)
#define IPTV_FULL_MOVIE_TITLE_NAME_LEN  (256)
#define IPTV_FULL_MOVIE_BUFF_SIZE    (24)

#define IPTV_FULL_MOVIE_MENU_HIDE   (0)
#define IPTV_FULL_MOVIE_MENU_SHOW   (1)

#define IPTV_FULL_MOVIE_START_STATUS   (0)
#define IPTV_FULL_MOVIE_PAUSE_STATUS   (1)
#define IPTV_FULL_MOVIE_STOP_STATUS    (2)
#define IPTV_FULL_MOVIE_PLAYING_STATUS (3)
#define IPTV_FULL_MOVIE_SELECT_STATUS  (4)

#define CALC_TIME_EN (0)

/**计算时间间隔*/
#define IPTV_CALC_TIME_INTERVAL(_a, _b) ((_a <= _b) ? (_b - _a) : (0xFFFFFFFF - _a + _b))


typedef struct
{
    D_HTimer iptvFullMoviePlayTimer;  /**播放视频的定时器*/
    D_HTimer iptvFullMovieMenuTimer;  /**控制条菜单显示定时器*/

    D_Char   iptvFullMovieTotalTime[IPTV_FULL_MOVIE_BUFF_SIZE];
    D_Char   iptvFullMoviePathName[IPTV_FULL_MOVIE_PATH_NAME_LEN];

    D_Char   iptvFullMovieName[IPTV_FULL_MOVIE_PATH_NAME_LEN]; /**视频源的地址URL*/
    D_Char   iptvFullMoviehw[IPTV_FULL_MOVIE_BUFF_SIZE];

    D_Char   iptvFullMovieTitle[IPTV_FULL_MOVIE_TITLE_NAME_LEN]; /**视频源的标题名称，用于显示*/
    //D_Char    iptvFullMoviePromptMsg[IPTV_FULL_MOVIE_TITLE_NAME_LEN]; /**提示信息*/
    D_Double iptvFullMovieTotalTimeValue;  /**电影的总时间*/
    D_Double iptvFullMovieCurrTimeValue;    /**电影的当前时间*/
    D_U32    iptvFullMovieProgressValue;    /**progress的值*/
    D_U8    iptvFullMoviePlayStatus;    /**电影的播放状态*/
    D_U16    iptvFullMovieCurrIndex;
    D_Bool   iptvFullMovieSelectPos;    /**电影的快进的标志*/
    D_Bool      iptvFullMovieInfoValid;
    D_U32 iptvFullMovieCheckEndCounter;
    D_U32 iptvFullMovieLastPlayTime;    /**时间记录*/
    D_U32 iptvFullMovieMarkTime;    /**时间记录*/
    D_U32 strPlayWait_idx;
    D_U32 iptvPlayWaitTime;
    D_U32   iptvFullMovieMenuPlayStartTime;  /**电影的播放开始的时间*/

    D_U8     iptvFullMovieMenuEnable;    /**播放菜单是否显示*/
    D_U32   iptvFullMovieMenuShowStartTime;  /**开始的时间*/

    D_VidWindow iptvFullMovieWin;          /**电影全屏窗口*/
    D_MovieInfo iptvFullMovieInfo;        /**电影的信息*/

    D_Bool      dlnaFullHasSet;  /**快进是否显示*/
    D_VidInput  lastinput;
    D_U8    menu_lang;
    D_S8        iptvvol;
    D_U32      dlnaseektime;
    D_Bool     media_open_flag;

    D_Bool      menu_auto_close;
    D_U32      timer_counter;

    D_U32      network_error;
    D_U32      network_error_counter;

    D_Bool      media_ts;
    D_Bool      direct_movie; /*直播*/


    D_Visual* vis_full_win, *vis_play_progress;
    D_Visual* vis_time, *vis_play_group, *vis_info_group;
    D_Visual* vis_name;
    D_Visual* vis_prompt;
} D_IptvPlayWindowInfo;

static D_IptvPlayWindowInfo * iptv_play_window_info = NULL;
static D_Char*strNotSupport[2] = {"Not support file !", "不支持此视频，播放失败!"};
static D_Char*strPlayFailed[2] = {"Play failed !", "播放失败!"};
static D_Char*strPlayWait[9][2] =
{
    {"Please Waiting...", "正在缓冲..."},
    {"Please Waiting.  ", "正在缓冲.  "},
    {"Please Waiting.. ", "正在缓冲.. "},
    {"Please Waiting... ", "网络不好，正在缓冲... "},
    {"Please Waiting. ", "网络不好，正在缓冲. "},
    {"Please Waiting.. ", "网络不好，正在缓冲.. "},
    {"Network disconnected, waiting...", "网络已断开，等待恢复..."},
    {"Network disconnected, waiting.", "网络已断开，等待恢复."},
    {"Network disconnected, waiting..", "网络已断开，等待恢复.."},
};

static D_HMutex iptv_menu_hmutex = D_INVALID_HANDLE;

#define IPTV_MENU_LOCK()      do{if(D_INVALID_HANDLE!=iptv_menu_hmutex)d_mutex_lock(iptv_menu_hmutex);}while(0);
#define DLNA_MENU_UNLOCK()    do{if(D_INVALID_HANDLE!=iptv_menu_hmutex)d_mutex_unlock(iptv_menu_hmutex);}while(0);

/** @brief 设置信息条*/
static void iptv_full_movie_set_info(void)
{
    //name
    //d_label_set_text(iptv_play_window_info->vis_name, iptv_play_window_info->iptvFullMovieTitle);
}


/** @brief 更新显示时间*/
static D_Result
iptv_full_movie_update_show_time(D_Bool show, D_Bool reset) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;

    if(reset)
    {
        iptv_play_window_info->iptvFullMovieTotalTimeValue = 0;
        iptv_play_window_info->iptvFullMovieCurrTimeValue = 0;
        iptv_play_window_info->iptvFullMovieProgressValue = 0;
        iptv_play_window_info->iptvFullMovieSelectPos = D_FALSE;
    }
    else
    {
        iptv_play_window_info->iptvFullMovieTotalTimeValue = iptv_play_window_info->iptvFullMovieInfo.totaltime;

        cur_sec = (D_U32)d_media_movie_get_curtime();
        if(cur_sec >= 360000)  // 100 h
        {
            D_DUMP("d_media_movie_get_curtime = %d\n", cur_sec);
        }
        else
        {
            iptv_play_window_info->iptvFullMovieCurrTimeValue = (D_Double)cur_sec;
        }

        if(iptv_play_window_info->iptvFullMovieCurrTimeValue < 1.0)
        {
            D_DUMP("d_media_movie_get_curtime = %0.0f\n", iptv_play_window_info->iptvFullMovieCurrTimeValue);
            iptv_play_window_info->iptvFullMovieCurrTimeValue =  ((D_Double)iptv_play_window_info->dlnaseektime);
        }

        if(iptv_play_window_info->iptvFullMovieTotalTimeValue)
        {
            iptv_play_window_info->iptvFullMovieProgressValue = (iptv_play_window_info->iptvFullMovieCurrTimeValue * 100) / iptv_play_window_info->iptvFullMovieTotalTimeValue;
        }
        else
        {
            iptv_play_window_info->iptvFullMovieProgressValue = 0;
        }
    }
#if 0
    total_hour = (D_U32)iptv_play_window_info->iptvFullMovieTotalTimeValue / 3600;
    total_min   = ((D_U32)iptv_play_window_info->iptvFullMovieTotalTimeValue % 3600) / 60;
    total_sec   = ((D_U32)iptv_play_window_info->iptvFullMovieTotalTimeValue % 3600) % 60;

    cur_hour  = (D_U32)iptv_play_window_info->iptvFullMovieCurrTimeValue / 3600;
    cur_min  = ((D_U32)iptv_play_window_info->iptvFullMovieCurrTimeValue % 3600) / 60;
    cur_sec  = ((D_U32)iptv_play_window_info->iptvFullMovieCurrTimeValue % 3600 ) % 60;

    /*设置进度显示*/
    d_progress_bar_set_val(iptv_play_window_info->vis_play_progress, show ? iptv_play_window_info->iptvFullMovieProgressValue : 0);
    if(iptv_play_window_info->iptvFullMovieSelectPos == D_FALSE)
    {
        if(0 == iptv_play_window_info->iptvFullMovieTotalTimeValue)
        {
            sprintf(iptv_play_window_info->iptvFullMovieTotalTime, "%s/%s", "--:--:--", "--:--:--");
        }
        else
        {
            sprintf(iptv_play_window_info->iptvFullMovieTotalTime, "%02d:%02d:%02d/%02d:%02d:%02d", cur_hour, cur_min, cur_sec, total_hour, total_min, total_sec);
        }

        d_label_set_text(iptv_play_window_info->vis_time, show ?    iptv_play_window_info->iptvFullMovieTotalTime : NULL);
        iptv_play_window_info->progressCur_X = ((iptv_play_window_info->iptvFullMovieProgressValue * (iptv_play_window_info->progressEnd_X - iptv_play_window_info->progressStart_X)) / 100) + iptv_play_window_info->vis_play_progress->rect.x;
    }
#endif
    return D_OK;
}

/** @brief 播放视频*/
static D_Result
iptv_full_movie_play(D_Bool first)D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;
    D_U32 t = d_sys_get_time();

    iptv_play_window_info->direct_movie = D_FALSE;
    iptv_play_window_info->menu_auto_close = D_FALSE;
    iptv_play_window_info->timer_counter = 0;
    iptv_play_window_info->dlnaseektime = 0;

    iptv_full_movie_update_show_time(D_FALSE, D_TRUE);
    d_vis_show(iptv_play_window_info->vis_prompt, D_FALSE);
    D_DUMP("iptv_full_movie_play start\n");

    if(iptv_play_window_info->media_ts)
    {
        iptv_play_window_info->media_open_flag = D_FALSE;
        d_av_set_vid_input (0, D_VID_IUTPUT_DTV);
    }
    else
    {
        d_av_set_vid_input (0, D_VID_IUTPUT_USB1);
        /* 释放epg占用资源*/
        p_auxi_free_varstring();

        d_mediacodec_open();
        d_media_movie_set_version(MOVIE_FFMPEG_VER_NEW_V34);
        d_media_movie_open() ;
        iptv_play_window_info->media_open_flag = D_TRUE;
        /*重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();
        /*缩放模式选自动*/
        d_av_set_tv_ratio_mode(0, D_NATURAL_RATIO);

        if(D_OK == d_media_movie_play(iptv_play_window_info->iptvFullMoviePathName, iptv_play_window_info->iptvFullMovieWin.x, iptv_play_window_info->iptvFullMovieWin.y, \
        iptv_play_window_info->iptvFullMovieWin.w, iptv_play_window_info->iptvFullMovieWin.h, 0, NULL))
        {
            d_media_movie_get_info(iptv_play_window_info->iptvFullMoviePathName, &iptv_play_window_info->iptvFullMovieInfo, iptv_play_window_info->iptvFullMovieWin.x,  \
            iptv_play_window_info->iptvFullMovieWin.y, iptv_play_window_info->iptvFullMovieWin.w, iptv_play_window_info->iptvFullMovieWin.h);
            D_DUMP("MovieInfo.width = %d, .height = %d\n", iptv_play_window_info->iptvFullMovieInfo.width, iptv_play_window_info->iptvFullMovieInfo.height);

            /* 时间小于等于0  或太大时，认为视频源为直播源*/
            if(iptv_play_window_info->iptvFullMovieInfo.totaltime < 1 || iptv_play_window_info->iptvFullMovieInfo.totaltime > 360000)
            {
                iptv_play_window_info->direct_movie = D_TRUE;
                iptv_play_window_info->iptvFullMovieInfo.totaltime = 360000 - 1;
            }

            /*不支持播放大于芯片解码能力之外的视频 或者是太小尺寸的视频也不支持*/
            if((iptv_play_window_info->iptvFullMovieInfo.width == 0 || iptv_play_window_info->iptvFullMovieInfo.height == 0) \
               || iptv_play_window_info->iptvFullMovieInfo.width > D_Media_Movie_Codec_Width_Max || iptv_play_window_info->iptvFullMovieInfo.height > D_Media_Movie_Codec_Height_Max \
               || iptv_play_window_info->iptvFullMovieInfo.width <= D_Media_Movie_Codec_Width_Limit || iptv_play_window_info->iptvFullMovieInfo.height <= D_Media_Movie_Codec_Height_LImit)
            {
                D_DUMP("Not support !MovieInfo.width = %d, .height = %d\n", iptv_play_window_info->iptvFullMovieInfo.width, iptv_play_window_info->iptvFullMovieInfo.height);
                d_label_set_text(iptv_play_window_info->vis_prompt, strNotSupport[iptv_play_window_info->menu_lang]);
                d_vis_show(iptv_play_window_info->vis_prompt, D_TRUE);
                iptv_full_movie_set_info();
                iptv_play_window_info->iptvFullMovieInfo.totaltime = 0;
                iptv_play_window_info->menu_auto_close = D_TRUE;
                d_media_movie_stop();
                goto _MOVIE_PLAY_END;
            }

            {
                iptv_full_movie_set_info();
                iptv_full_movie_update_show_time(D_TRUE, D_FALSE);
                ret = D_OK;
            }
        }
        else
        {
            d_label_set_text(iptv_play_window_info->vis_prompt, strPlayFailed[iptv_play_window_info->menu_lang]);
            d_vis_show(iptv_play_window_info->vis_prompt, D_TRUE);
            iptv_full_movie_set_info();
            iptv_play_window_info->iptvFullMovieInfo.totaltime = 0;
            iptv_play_window_info->menu_auto_close = D_TRUE;
            goto _MOVIE_PLAY_END;
        }
    }

_MOVIE_PLAY_END:
    iptv_play_window_info->iptvFullMovieMenuPlayStartTime = d_sys_get_time();
    iptv_play_window_info->iptvFullMovieMarkTime = iptv_play_window_info->iptvFullMovieMenuPlayStartTime;
    iptv_play_window_info->iptvFullMovieLastPlayTime = (D_U32)iptv_play_window_info->iptvFullMovieCurrTimeValue;
    iptv_play_window_info->iptvFullMovieCheckEndCounter = 0;
    D_DUMP("iptv_full_movie_play end %d\n", (d_sys_get_time() - t));
    return ret;
}


/** @brief 窗口事件处理*/
D_Result
atv_iptv_play_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status;
    D_Visual *pvis;

    switch(evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    p_atv_iptv_play_window_hide();
                    return D_OK;
                default:
                    return D_ERR;
                    break;
            }
            return D_ERR;
        }
        break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == iptv_play_window_info->iptvFullMoviePlayTimer)
            {
                D_ID file_id;

                status = d_media_movie_get_status();

                if(status == MOVIE_STATUS_PLAY)
                {
                    iptv_full_movie_update_show_time(D_TRUE, D_FALSE);
                    /*防止播放器播放完毕后却没有停播*/
                    if(iptv_play_window_info->iptvFullMovieCurrTimeValue >= (iptv_play_window_info->iptvFullMovieTotalTimeValue + 1))
                    {
                        D_DUMP("iptvFullMovieCurrTimeValue > iptvFullMovieTotalTimeValue\n");
                        iptv_play_window_info->iptvFullMovieCheckEndCounter++;
                        if(iptv_play_window_info->iptvFullMovieCheckEndCounter >= 5)
                        {
                            iptv_play_window_info->iptvFullMovieCheckEndCounter = 0;
                            p_atv_iptv_play_window_hide();
                            break;
                        }
                    }
                    else if(iptv_play_window_info->iptvFullMovieCurrTimeValue < iptv_play_window_info->iptvFullMovieTotalTimeValue)
                    {
                        D_U32 time_value, sys_time;
                        D_U32 textidx;

                        sys_time = d_sys_get_time();
                        iptv_play_window_info->iptvFullMovieCheckEndCounter = 0;
                        time_value = (D_U32)iptv_play_window_info->iptvFullMovieCurrTimeValue;
                        if(iptv_play_window_info->iptvFullMovieLastPlayTime == time_value)
                        {
                            iptv_play_window_info->iptvPlayWaitTime++;
                            sys_time = IPTV_CALC_TIME_INTERVAL(iptv_play_window_info->iptvFullMovieMarkTime, sys_time);
                            if(sys_time >= 2000)
                            {
                                if(iptv_play_window_info->network_error > 0)
                                    iptv_play_window_info->network_error_counter++;

                                if(1)
                                {
                                    iptv_play_window_info->strPlayWait_idx = (iptv_play_window_info->strPlayWait_idx >= 3) ? 0 : iptv_play_window_info->strPlayWait_idx;
                                    textidx = iptv_play_window_info->strPlayWait_idx;
                                    d_label_set_text(iptv_play_window_info->vis_prompt, strPlayWait[textidx][iptv_play_window_info->menu_lang]);
                                    d_vis_show(iptv_play_window_info->vis_prompt, D_TRUE);
                                    iptv_play_window_info->strPlayWait_idx = (iptv_play_window_info->strPlayWait_idx + 1) % 3;
                                }
                            }
                        }
                        else
                        {
                            iptv_play_window_info->iptvFullMovieMarkTime = sys_time;
                            d_vis_show(iptv_play_window_info->vis_prompt, D_FALSE);
                            iptv_play_window_info->strPlayWait_idx = 0xFF;
                            iptv_play_window_info->iptvPlayWaitTime = 0;
                        }
                        iptv_play_window_info->iptvFullMovieLastPlayTime = time_value;
                    }
                }
                else if(status == MOVIE_STATUS_STOP)
                {
                    D_DUMP("status == MOVIE_STATUS_STOP\n");
                    d_label_set_text(iptv_play_window_info->vis_prompt, strPlayFailed[iptv_play_window_info->menu_lang]);
                    d_vis_show(iptv_play_window_info->vis_prompt, D_TRUE);
                }
            }
            break;
        case D_EVT_USER1:
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(iptv_play_window_info)
            {
                if(iptv_play_window_info->iptvFullMoviePlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(iptv_play_window_info->iptvFullMoviePlayTimer);
                    iptv_play_window_info->iptvFullMoviePlayTimer = D_INVALID_HANDLE;
                }

                if(iptv_play_window_info->media_ts)
                {

                }
                else
                {
                    d_media_movie_stop();
                }

                if(iptv_play_window_info->media_open_flag)
                {
                    d_media_movie_close();
                    d_mediacodec_close();
                    iptv_play_window_info->media_open_flag = D_FALSE;
                }
                d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
                /* 重设静音/声道/音量*/
                p_stb_reset_mute_track_volume();

                PROJECT_FREE(iptv_play_window_info);
                iptv_play_window_info = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_iptv_play_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    p_av_set_vid_background(0, D_VID_BackGround_BLack, D_FALSE);

    iptv_play_window_info->media_open_flag = D_TRUE;
    iptv_play_window_info->iptvFullMoviePlayTimer = D_INVALID_HANDLE;
    iptv_play_window_info->iptvFullMovieMenuTimer = D_INVALID_HANDLE;
    iptv_play_window_info->iptvFullMovieSelectPos = D_FALSE;
    iptv_play_window_info->iptvFullMovieMenuEnable = IPTV_FULL_MOVIE_MENU_SHOW;
    iptv_play_window_info->menu_lang = (D_LANG_CHN == p_conf_get_lang()) ? 1 : 0;
    iptv_play_window_info->vis_prompt = d_frame_get_control(frm, ID_IPTV_PLAY_PROMPT_MSG);
    d_vis_show(iptv_play_window_info->vis_prompt, D_FALSE);

    //iptv_play_window_info->vis_name = d_frame_get_control(frm, ID_FULL_MOVIE_NAME);

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        iptv_play_window_info->vis_full_win = vis;
        d_vis_get_pos(iptv_play_window_info->vis_full_win, &iptv_play_window_info->iptvFullMovieWin.x, &iptv_play_window_info->iptvFullMovieWin.y);
        iptv_play_window_info->iptvFullMovieWin.x = 0;
        iptv_play_window_info->iptvFullMovieWin.y = 0;
        iptv_play_window_info->iptvFullMovieWin.w = -1;
        iptv_play_window_info->iptvFullMovieWin.h = -1;

        if(D_OK != iptv_full_movie_play(D_TRUE))
        {
            if(iptv_play_window_info->media_ts)
            {

            }
            else
            {
                d_media_movie_stop();
            }
        }

        if(iptv_play_window_info->iptvFullMoviePlayTimer == D_INVALID_HANDLE)
        {
            iptv_play_window_info->iptvFullMoviePlayTimer = d_timer_create(NULL, IPTV_FULL_MOVIE_PLAY_REFRESH_TIME, d_gui_get_queue());
            if(iptv_play_window_info->iptvFullMoviePlayTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, iptv_play_window_info->iptvFullMoviePlayTimer);
            }
        }

        /*处理用户事件*/
        //d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_iptv_play_window_handler);
    }
    return D_OK;
}


/** @brief 显示dlna视频播放窗口*/
D_Result
p_atv_iptv_play_window_show(D_Char*  file_path , D_Char*  file_title, D_VidInput lastinput) D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;

    if(iptv_menu_hmutex == D_INVALID_HANDLE)
        iptv_menu_hmutex = d_mutex_create(NULL);

    IPTV_MENU_LOCK();

    D_DUMP("file_path(%s)\n", file_path);
    D_DUMP("file_title(%s)\n", file_title);
    if(file_path != NULL)
    {
        if (D_FALSE == d_frame_is_loaded (&atv_iptv_play_window))
        {
            iptv_play_window_info = (D_IptvPlayWindowInfo*)PROJECT_ALLOC(sizeof(D_IptvPlayWindowInfo));
            if(iptv_play_window_info)
            {
                memset(iptv_play_window_info, 0x00, sizeof(D_IptvPlayWindowInfo));
                iptv_play_window_info->iptvvol = -1;
                iptv_play_window_info->iptvFullMoviePlayTimer = D_INVALID_HANDLE;
                iptv_play_window_info->iptvFullMovieMenuTimer = D_INVALID_HANDLE;
                iptv_play_window_info->lastinput = lastinput;
                //p_conf_set_vid_input(D_VID_IUTPUT_USB1);
                //p_sys_set_input_mode(iptv_play_window_info->lastinput, D_VID_IUTPUT_USB1);
                //d_gui_clear_menu_ext(ATV_MEDIA_MENU_ID);
                //p_gui_atv_media_resource_init();
                if(file_title)
                {
                    //strncpy(iptv_play_window_info->iptvFullMovieTitle, file_title, D_MIN((sizeof(iptv_play_window_info->iptvFullMovieTitle) - 1), strlen(file_title)));
                    p_cc_utf8_to_sys(iptv_play_window_info->iptvFullMovieTitle, sizeof(iptv_play_window_info->iptvFullMovieTitle), file_title, strlen(file_title));
                }
                strncpy(iptv_play_window_info->iptvFullMoviePathName, file_path, D_MIN((sizeof(iptv_play_window_info->iptvFullMoviePathName) - 1), strlen(file_path)));
                if(strstr(iptv_play_window_info->iptvFullMoviePathName, ".mp4") || strstr(iptv_play_window_info->iptvFullMoviePathName, ".m3u8"))
                {

                }
                else if(strstr(iptv_play_window_info->iptvFullMoviePathName, ".ts"))
                {
                    iptv_play_window_info->media_ts = D_TRUE;
                }

                ret = d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &atv_iptv_play_window, D_CLEAR_NONE);
                if(ret != D_OK && iptv_play_window_info)
                {
                    if(iptv_play_window_info->iptvFullMoviePlayTimer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(iptv_play_window_info->iptvFullMoviePlayTimer);
                        iptv_play_window_info->iptvFullMoviePlayTimer = D_INVALID_HANDLE;
                    }

                    if(iptv_play_window_info->iptvFullMovieMenuTimer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(iptv_play_window_info->iptvFullMovieMenuTimer);
                        iptv_play_window_info->iptvFullMovieMenuTimer = D_INVALID_HANDLE;
                    }

                    PROJECT_FREE(iptv_play_window_info);
                    iptv_play_window_info = NULL;
                }
            }
        }
    }
    DLNA_MENU_UNLOCK();
    return ret;
}

/** @brief 关闭dlna视频播放窗口*/
D_Result
p_atv_iptv_play_window_hide(void) D_FUNCPOSTFIT
{
    IPTV_MENU_LOCK();

    if (D_TRUE == d_frame_is_loaded (&atv_iptv_play_window))
    {
        D_VidInput  lastinput = iptv_play_window_info->lastinput;

        if(iptv_play_window_info->media_ts)
        {

        }
        else
        {
            d_media_movie_stop();
        }

        if(iptv_play_window_info->media_open_flag)
        {
            d_media_movie_close();
            d_mediacodec_close();
            iptv_play_window_info->media_open_flag = D_FALSE;
        }

        /*停止播放*/
        d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        /* 重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();

        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);

    }
    DLNA_MENU_UNLOCK();
    return D_OK;
}

/** @brief 通知dlna视频播放窗口网络状态*/
D_Result
p_atv_iptv_play_window_network_error(D_U32 action) D_FUNCPOSTFIT
{
    if ((D_TRUE == d_frame_is_loaded (&atv_iptv_play_window)) && iptv_play_window_info)
    {
        if(action)
        {
            iptv_play_window_info->network_error = 1;
        }
        else
        {
            iptv_play_window_info->network_error = 0;
            iptv_play_window_info->network_error_counter = 0;
        }
    }
    return D_OK;
}

