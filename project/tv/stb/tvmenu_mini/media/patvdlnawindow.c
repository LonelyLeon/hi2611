/** @file
* @brief tv DLNA Window
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
#include "dAirplay.h"

#include "atv_dlna_window.c"

#define DLNA_FULL_MOVIE_PLAY_REFRESH_TIME (1000)
#define DLNA_FULL_MOVIE_MENU_SHOW_TIME    (5000)

#define DLNA_FULL_MOVIE_PATH_NAME_LEN  (1024)
#define DLNA_FULL_MOVIE_TITLE_NAME_LEN  (256)
#define DLNA_FULL_MOVIE_BUFF_SIZE    (24)

#define DLNA_FULL_MOVIE_MENU_HIDE   (0)
#define DLNA_FULL_MOVIE_MENU_SHOW   (1)

#define DLNA_FULL_MOVIE_START_STATUS   (0)
#define DLNA_FULL_MOVIE_PAUSE_STATUS   (1)
#define DLNA_FULL_MOVIE_STOP_STATUS    (2)
#define DLNA_FULL_MOVIE_PLAYING_STATUS (3)
#define DLNA_FULL_MOVIE_SELECT_STATUS  (4)

#define CALC_TIME_EN (0)

/**计算时间间隔*/
#define DLNA_CALC_TIME_INTERVAL(_a, _b) ((_a <= _b) ? (_b - _a) : (0xFFFFFFFF - _a + _b))


typedef struct
{
    D_HTimer dlnaFullMoviePlayTimer;  /**播放视频的定时器*/
    D_HTimer dlnaFullMovieMenuTimer;  /**控制条菜单显示定时器*/

    D_Char   dlnaFullMovieTotalTime[DLNA_FULL_MOVIE_BUFF_SIZE];
    D_Char   dlnaFullMoviePathName[DLNA_FULL_MOVIE_PATH_NAME_LEN];

    D_Char   dlnaFullMovieName[DLNA_FULL_MOVIE_PATH_NAME_LEN]; /**视频源的地址URL*/
    D_Char   dlnaFullMoviehw[DLNA_FULL_MOVIE_BUFF_SIZE];

    D_Char   dlnaFullMovieTitle[DLNA_FULL_MOVIE_TITLE_NAME_LEN]; /**视频源的标题名称，用于显示*/
    //D_Char    dlnaFullMoviePromptMsg[DLNA_FULL_MOVIE_TITLE_NAME_LEN]; /**提示信息*/
    D_Double dlnaFullMovieTotalTimeValue;  /**电影的总时间*/
    D_Double dlnaFullMovieCurrTimeValue;    /**电影的当前时间*/
    D_U32    dlnaFullMovieProgressValue;    /**progress的值*/
    D_U8    dlnaFullMoviePlayStatus;    /**电影的播放状态*/
    D_U16    dlnaFullMovieCurrIndex;
    D_Bool   dlnaFullMovieSelectPos;    /**电影的快进的标志*/
    D_Bool      dlnaFullMovieInfoValid;
    D_U32 dlnaFullMovieCheckEndCounter;
    D_U32 dlnaFullMovieLastPlayTime;    /**时间记录*/
    D_U32 dlnaFullMovieMarkTime;    /**时间记录*/
    D_U32 strPlayWait_idx;
    D_U32 dlnaPlayWaitTime;
    D_U32   dlnaFullMovieMenuPlayStartTime;  /**电影的播放开始的时间*/

    D_U8     dlnaFullMovieMenuEnable;    /**播放菜单是否显示*/
    D_U32   dlnaFullMovieMenuShowStartTime;  /**开始的时间*/

    D_VidWindow dlnaFullMovieWin;          /**电影全屏窗口*/
    D_MovieInfo dlnaFullMovieInfo;        /**电影的信息*/

    D_U16       progressStart_X;/**起始的x 坐标*/
    D_U16       progressEnd_X;/**结束的x 坐标*/
    D_U16       progressCur_X; /**离父控件的x 坐标*/

    D_Bool      dlnaFullHasSet;  /**快进是否显示*/
    D_VidInput  lastinput;
    D_U8    menu_lang;
    D_S8        dlnavol;
    D_U32      dlnaseektime;
#if CALC_TIME_EN
    D_U32      dlnaseektime_start;
#endif
    D_Bool     media_open_flag;

    D_Bool      menu_auto_close;
    D_U32      timer_counter;

    D_U32      network_error;
    D_U32      network_error_counter;
    
    D_Bool      direct_movie; /*直播*/
    D_Bool      music_mode; /*播放音乐*/

    D_Visual* vis_full_win, *vis_play_progress, *vis_play_pos;
    D_Visual* vis_time, *vis_play_group, *vis_info_group;
    D_Visual* vis_play_status, *vis_show_status;
    D_Visual* vis_name, *vis_hw;
    D_Visual* vis_prompt;
    D_Visual* vis_music;
} DlnaWindowInfo;

static DlnaWindowInfo * dlna_window_info = NULL;
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

static D_HMutex dlna_menu_hmutex = D_INVALID_HANDLE;
static D_Bool  normal_destroy = D_FALSE;


#define DLNA_MENU_LOCK()      do{if(D_INVALID_HANDLE!=dlna_menu_hmutex)d_mutex_lock(dlna_menu_hmutex);}while(0);
#define DLNA_MENU_UNLOCK()    do{if(D_INVALID_HANDLE!=dlna_menu_hmutex)d_mutex_unlock(dlna_menu_hmutex);}while(0);

static void notify_protocol_playtime(D_U32 playtime)
{
#ifdef D_TV_DLNA_SOURCE
    d_dlna_set_playtime(playtime);
#endif
#ifdef D_TV_SUPPORT_AIRPLAY
    d_airplay_set_playtime(playtime);
#endif
}

static void notify_protocol_totaltime(D_U32 totaltime)
{
#ifdef D_TV_DLNA_SOURCE
    d_dlna_set_totaltime(totaltime);
#endif
#ifdef D_TV_SUPPORT_AIRPLAY
    d_airplay_set_totaltime(totaltime);
#endif
}

static void notify_protocol_status(PlayStatus status)
{
#ifdef D_TV_DLNA_SOURCE
    d_dlna_set_status(status);
#endif
#ifdef D_TV_SUPPORT_AIRPLAY
    d_airplay_set_status(status);
#endif
}

/** @brief 设置信息条*/
static void dlna_full_movie_set_info(void)
{
    D_U32 height = 0, width = 0;

    //name
    d_label_set_text(dlna_window_info->vis_name, dlna_window_info->dlnaFullMovieTitle);

    height = dlna_window_info->dlnaFullMovieInfo.height;
    width = dlna_window_info->dlnaFullMovieInfo.width;

    if(width == 0 || height == 0)
    {
        sprintf(dlna_window_info->dlnaFullMoviehw, "");
    }
    else
    {
        sprintf(dlna_window_info->dlnaFullMoviehw, "%d x %d", width, height);
    }
    d_label_set_text(dlna_window_info->vis_hw, dlna_window_info->dlnaFullMoviehw);

}


/** @brief 复位显示定时器*/
static D_Result
dlna_full_movie_reset_show_timer(D_Bool enable) D_FUNCPOSTFIT
{
    if(dlna_window_info)
    {
        if(enable)
        {
            if(dlna_window_info->dlnaFullMovieMenuTimer == D_INVALID_HANDLE)
            {
                dlna_window_info->dlnaFullMovieMenuTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
                if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_vis_subscribe_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
                }
            }
            if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_timer_reset(dlna_window_info->dlnaFullMovieMenuTimer, DLNA_FULL_MOVIE_MENU_SHOW_TIME);
                dlna_window_info->dlnaFullMovieMenuShowStartTime = d_sys_get_time();
            }
        }
        else
        {
            if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_unsubscribe_one_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
                d_timer_destroy(dlna_window_info->dlnaFullMovieMenuTimer);
                dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
            }
        }
    }
    return D_OK;
}

/** @brief 信息条是否显示*/
static D_Result
dlna_full_movie_menu_show_en(D_Bool show)D_FUNCPOSTFIT
{
    dlna_window_info->dlnaFullMovieMenuEnable = show;
    d_vis_show(dlna_window_info->vis_play_group, show);
    d_vis_show(dlna_window_info->vis_info_group, show);
    if(show)
    {
        dlna_full_movie_reset_show_timer(D_TRUE);
    }
    return D_OK;
}

/** @brief 设置播放状态*/
static D_Result
dlna_full_movie_set_play_status(D_U8 status)D_FUNCPOSTFIT
{
    dlna_window_info->dlnaFullMoviePlayStatus = status;
    switch(status)
    {
        case DLNA_FULL_MOVIE_START_STATUS:
            dlna_window_info->dlnaFullMoviePlayStatus = DLNA_FULL_MOVIE_PLAYING_STATUS;
            d_image_box_set_image(dlna_window_info->vis_play_status, d_gui_get_image(atv_IMG_ID_media_pause));
            d_label_set_text(dlna_window_info->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
            break;
        case DLNA_FULL_MOVIE_PAUSE_STATUS:
            if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_HIDE)
            {
                dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
            }
            
            if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_unsubscribe_one_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
                d_timer_destroy(dlna_window_info->dlnaFullMovieMenuTimer);
                dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
            }

            d_media_movie_pause();
            notify_protocol_status(PLAYER_STATUS_PAUSED);
            d_image_box_set_image(dlna_window_info->vis_play_status, d_gui_get_image(atv_IMG_ID_media_play));
            d_label_set_text(dlna_window_info->vis_show_status, d_gui_get_text(atv_IDS_PLAY));
            break;
        case DLNA_FULL_MOVIE_PLAYING_STATUS:
            if(dlna_window_info->dlnaFullMovieMenuTimer == D_INVALID_HANDLE)
            {
                dlna_window_info->dlnaFullMovieMenuTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
                if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_vis_subscribe_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
                }
                dlna_window_info->dlnaFullMovieMenuShowStartTime = d_sys_get_time();
            }
            d_media_movie_resume();
            notify_protocol_status(PLAYER_STATUS_PLAYING);
#if CALC_TIME_EN
            dlna_window_info->dlnaseektime = dlna_window_info->dlnaFullMovieCurrTimeValue;
            dlna_window_info->dlnaseektime_start = d_sys_get_time();
#endif
            d_image_box_set_image(dlna_window_info->vis_play_status, d_gui_get_image(atv_IMG_ID_media_pause));
            d_label_set_text(dlna_window_info->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
            break;
        case DLNA_FULL_MOVIE_STOP_STATUS:
            break;
        case DLNA_FULL_MOVIE_SELECT_STATUS:
            d_vis_set_pos(dlna_window_info->vis_play_pos, dlna_window_info->progressCur_X, dlna_window_info->vis_play_pos->rect.y, dlna_window_info->vis_play_pos->rect.w, dlna_window_info->vis_play_pos->rect.h);
            d_vis_set_focusable(dlna_window_info->vis_play_pos, D_TRUE);
            d_vis_set_focus(dlna_window_info->vis_play_pos);
            d_vis_update (dlna_window_info->vis_play_pos, NULL);

            dlna_window_info->dlnaFullMovieSelectPos = D_TRUE;
            break;
        default:
            break;
    }
}

/** @brief 更新显示时间*/
static D_Result
dlna_full_movie_update_show_time(D_Bool show, D_Bool reset) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;

    if(reset)
    {
        dlna_window_info->dlnaFullMovieTotalTimeValue = 0;
        dlna_window_info->dlnaFullMovieCurrTimeValue = 0;
        dlna_window_info->dlnaFullMovieProgressValue = 0;
        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
    }
    else
    {
        dlna_window_info->dlnaFullMovieTotalTimeValue = dlna_window_info->dlnaFullMovieInfo.totaltime;
#if CALC_TIME_EN == 0
        cur_sec = (D_U32)d_media_movie_get_curtime();
        if(cur_sec >= 360000)  // 100 h
        {
            D_DUMP("d_media_movie_get_curtime = %d\n", cur_sec);
        }
        else
        {
            dlna_window_info->dlnaFullMovieCurrTimeValue = (D_Double)cur_sec;
        }

        if(dlna_window_info->dlnaFullMovieCurrTimeValue < 1.0)
        {
            D_DUMP("d_media_movie_get_curtime = %0.0f\n", dlna_window_info->dlnaFullMovieCurrTimeValue);
            dlna_window_info->dlnaFullMovieCurrTimeValue =  ((D_Double)dlna_window_info->dlnaseektime);
        }
#else
        /* 目前播放器计算时间不正确，暂时自己计算@qiny 20180813*/
        cur_sec = d_sys_get_time();
        cur_sec = (cur_sec >= dlna_window_info->dlnaseektime_start) ? (cur_sec - dlna_window_info->dlnaseektime_start) : (cur_sec + ( 0xffffffff - dlna_window_info->dlnaseektime_start));
        dlna_window_info->dlnaFullMovieCurrTimeValue = dlna_window_info->dlnaseektime + cur_sec / 1000;
#endif
        if(dlna_window_info->dlnaFullMovieTotalTimeValue)
        {
            dlna_window_info->dlnaFullMovieProgressValue = (dlna_window_info->dlnaFullMovieCurrTimeValue * 100) / dlna_window_info->dlnaFullMovieTotalTimeValue;
        }
        else
        {
            dlna_window_info->dlnaFullMovieProgressValue = 0;
        }
    }

    total_hour = (D_U32)dlna_window_info->dlnaFullMovieTotalTimeValue / 3600;
    total_min   = ((D_U32)dlna_window_info->dlnaFullMovieTotalTimeValue % 3600) / 60;
    total_sec   = ((D_U32)dlna_window_info->dlnaFullMovieTotalTimeValue % 3600) % 60;

    cur_hour  = (D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue / 3600;
    cur_min  = ((D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue % 3600) / 60;
    cur_sec  = ((D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue % 3600 ) % 60;

    /*设置进度显示*/
    notify_protocol_playtime((D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue);
    d_progress_bar_set_val(dlna_window_info->vis_play_progress, show ? dlna_window_info->dlnaFullMovieProgressValue : 0);
    if(dlna_window_info->dlnaFullMovieSelectPos == D_FALSE)
    {
        if(0 == dlna_window_info->dlnaFullMovieTotalTimeValue)
        {
            sprintf(dlna_window_info->dlnaFullMovieTotalTime, "%s/%s", "--:--:--", "--:--:--");
        }
        else
        {
            sprintf(dlna_window_info->dlnaFullMovieTotalTime, "%02d:%02d:%02d/%02d:%02d:%02d", cur_hour, cur_min, cur_sec, total_hour, total_min, total_sec);
        }

        d_label_set_text(dlna_window_info->vis_time, show ?    dlna_window_info->dlnaFullMovieTotalTime : NULL);
        dlna_window_info->progressCur_X = ((dlna_window_info->dlnaFullMovieProgressValue * (dlna_window_info->progressEnd_X - dlna_window_info->progressStart_X)) / 100) + dlna_window_info->vis_play_progress->rect.x;
    }

    return D_OK;
}

/** @brief 更新设置时间*/
static D_Result
dlna_full_movie_update_set_time(void) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;
    D_Double total_time_value;
    D_U32   cur_set_time;

    total_time_value = dlna_window_info->dlnaFullMovieInfo.totaltime;
    cur_set_time = (dlna_window_info->progressCur_X - dlna_window_info->progressStart_X) * total_time_value / (dlna_window_info->progressEnd_X - dlna_window_info->progressStart_X);

    total_hour = (D_U32)total_time_value / 3600;
    total_min   = ((D_U32)total_time_value % 3600) / 60;
    total_sec   = ((D_U32)total_time_value % 3600) % 60;

    cur_hour  = (D_U32)cur_set_time / 3600;
    cur_min  = ((D_U32)cur_set_time % 3600) / 60;
    cur_sec  = ((D_U32)cur_set_time % 3600 ) % 60;


    sprintf(dlna_window_info->dlnaFullMovieTotalTime, "%02d:%02d:%02d/%02d:%02d:%02d", cur_hour, cur_min, cur_sec, total_hour, total_min, total_sec);
    d_label_set_text(dlna_window_info->vis_time, dlna_window_info->dlnaFullMovieTotalTime );

    return D_OK;
}

/** @brief 播放视频*/
static D_Result
dlna_full_movie_play(D_Bool first)D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;
    D_U32 t = d_sys_get_time();

    dlna_window_info->music_mode = D_FALSE;
    dlna_window_info->direct_movie = D_FALSE;
    dlna_window_info->menu_auto_close = D_FALSE;
    dlna_window_info->timer_counter = 0;
    dlna_window_info->dlnaseektime = 0;
#if CALC_TIME_EN
    dlna_window_info->dlnaseektime_start = d_sys_get_time();
#endif
    dlna_full_movie_update_show_time(D_FALSE, D_TRUE);
    if(first == D_FALSE)
    {
        dlna_full_movie_reset_show_timer(D_TRUE);
    }
    d_vis_show(dlna_window_info->vis_prompt, D_FALSE);
    D_DUMP("dlna_full_movie_play start\n");
#if 0
    if(D_OK == d_media_movie_get_info(dlna_window_info->dlnaFullMoviePathName, &dlna_window_info->dlnaFullMovieInfo, dlna_window_info->dlnaFullMovieWin.x,  \
    dlna_window_info->dlnaFullMovieWin.y, dlna_window_info->dlnaFullMovieWin.w, dlna_window_info->dlnaFullMovieWin.h))
    {
        D_DUMP("MovieInfo.width = %d, .height = %d\n", dlna_window_info->dlnaFullMovieInfo.width, dlna_window_info->dlnaFullMovieInfo.height);

        /* 时间小于等于0  或太大时，认为视频源为直播源*/
        if(dlna_window_info->dlnaFullMovieInfo.totaltime < 1 || dlna_window_info->dlnaFullMovieInfo.totaltime > 360000)  
        {
            dlna_window_info->direct_movie = D_TRUE;
            dlna_window_info->dlnaFullMovieInfo.totaltime = 360000 - 1;
        }
        
        notify_protocol_status(PLAYER_STATUS_PLAYING); /* 通知dlna，视频已经播放*/
        /*不支持播放大于芯片解码能力之外的视频 或者是太小尺寸的视频也不支持*/
        if((dlna_window_info->dlnaFullMovieInfo.width == 0 || dlna_window_info->dlnaFullMovieInfo.height == 0) \
        || dlna_window_info->dlnaFullMovieInfo.width > D_Media_Movie_Codec_Width_Max || dlna_window_info->dlnaFullMovieInfo.height > D_Media_Movie_Codec_Height_Max \
        || dlna_window_info->dlnaFullMovieInfo.width <= D_Media_Movie_Codec_Width_Limit || dlna_window_info->dlnaFullMovieInfo.height <= D_Media_Movie_Codec_Height_LImit)
        {
            D_DUMP("Not support !MovieInfo.width = %d, .height = %d\n", dlna_window_info->dlnaFullMovieInfo.width, dlna_window_info->dlnaFullMovieInfo.height);
            //d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
            //d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
            d_label_set_text(dlna_window_info->vis_prompt, strNotSupport[dlna_window_info->menu_lang]);
            d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
            dlna_full_movie_set_info();

            if(first == D_FALSE)
            {
                dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
            }
            dlna_window_info->dlnaFullMovieInfo.totaltime = 0;
            dlna_window_info->menu_auto_close = D_TRUE;
            goto _MOVIE_PLAY_END;
        }
        if(D_OK == d_media_movie_play(dlna_window_info->dlnaFullMoviePathName, dlna_window_info->dlnaFullMovieWin.x, dlna_window_info->dlnaFullMovieWin.y, \
                                      dlna_window_info->dlnaFullMovieWin.w, dlna_window_info->dlnaFullMovieWin.h, 0, NULL))
        {
            dlna_full_movie_set_info();
            if(first == D_FALSE)
            {
                dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
            }
            dlna_full_movie_update_show_time(D_TRUE, D_FALSE);
            dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_START_STATUS);
            ret = D_OK;
            notify_protocol_status(PLAYER_STATUS_PLAYING);
            notify_protocol_totaltime((D_U32)dlna_window_info->dlnaFullMovieInfo.totaltime);
        }
    }
    else
    {
        //d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
        //d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
        d_label_set_text(dlna_window_info->vis_prompt, strPlayFailed[dlna_window_info->menu_lang]);
        d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
        dlna_full_movie_set_info();
        if(first == D_FALSE)
        {
            dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
        }
        dlna_window_info->dlnaFullMovieInfo.totaltime = 0;
        dlna_window_info->menu_auto_close = D_TRUE;
        goto _MOVIE_PLAY_END;
    }
#else

    if(D_OK == d_media_movie_play(dlna_window_info->dlnaFullMoviePathName, dlna_window_info->dlnaFullMovieWin.x, dlna_window_info->dlnaFullMovieWin.y, \
    dlna_window_info->dlnaFullMovieWin.w, dlna_window_info->dlnaFullMovieWin.h, 0, NULL))
    {
        notify_protocol_status(PLAYER_STATUS_PLAYING); /* 通知dlna，视频已经播放*/
        d_media_movie_get_info(dlna_window_info->dlnaFullMoviePathName, &dlna_window_info->dlnaFullMovieInfo, dlna_window_info->dlnaFullMovieWin.x,  \
        dlna_window_info->dlnaFullMovieWin.y, dlna_window_info->dlnaFullMovieWin.w, dlna_window_info->dlnaFullMovieWin.h);
        D_DUMP("MovieInfo.width = %d, .height = %d\n", dlna_window_info->dlnaFullMovieInfo.width, dlna_window_info->dlnaFullMovieInfo.height);

        /* 时间小于等于0  或太大时，认为视频源为直播源*/
        if(dlna_window_info->dlnaFullMovieInfo.totaltime < 1 || dlna_window_info->dlnaFullMovieInfo.totaltime > 360000)  
        {
            dlna_window_info->direct_movie = D_TRUE;
            dlna_window_info->dlnaFullMovieInfo.totaltime = 360000 - 1;
        }

        /*不支持播放大于芯片解码能力之外的视频 或者是太小尺寸的视频也不支持*/
        if(dlna_window_info->dlnaFullMovieInfo.frame_rate < 0.1 || (dlna_window_info->dlnaFullMovieInfo.width == 0 && dlna_window_info->dlnaFullMovieInfo.height == 0))
        {
            //music
            dlna_window_info->music_mode = D_TRUE;
            d_vis_show(dlna_window_info->vis_music, D_TRUE);
        }
        else  if((dlna_window_info->dlnaFullMovieInfo.width == 0 || dlna_window_info->dlnaFullMovieInfo.height == 0) \
        || dlna_window_info->dlnaFullMovieInfo.width > D_Media_Movie_Codec_Width_Max || dlna_window_info->dlnaFullMovieInfo.height > D_Media_Movie_Codec_Height_Max \
        || dlna_window_info->dlnaFullMovieInfo.width <= D_Media_Movie_Codec_Width_Limit || dlna_window_info->dlnaFullMovieInfo.height <= D_Media_Movie_Codec_Height_LImit)
        {
            D_DUMP("Not support !MovieInfo.width = %d, .height = %d\n", dlna_window_info->dlnaFullMovieInfo.width, dlna_window_info->dlnaFullMovieInfo.height);
            //d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
            //d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
            d_label_set_text(dlna_window_info->vis_prompt, strNotSupport[dlna_window_info->menu_lang]);
            d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
            dlna_full_movie_set_info();

            if(first == D_FALSE)
            {
                dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
            }
            dlna_window_info->dlnaFullMovieInfo.totaltime = 0;
            dlna_window_info->menu_auto_close = D_TRUE;
            d_media_movie_stop();
            goto _MOVIE_PLAY_END;
        }

        {
            dlna_full_movie_set_info();
            if(first == D_FALSE)
            {
                dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
            }
            dlna_full_movie_update_show_time(D_TRUE, D_FALSE);
            dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_START_STATUS);
            ret = D_OK;
            notify_protocol_status(PLAYER_STATUS_PLAYING);
            notify_protocol_totaltime((D_U32)dlna_window_info->dlnaFullMovieInfo.totaltime);
        }

        if(dlna_window_info->music_mode)
        {
            dlna_full_movie_reset_show_timer(D_FALSE);
        }
    }
    else
    {
        //d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
        //d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
        d_label_set_text(dlna_window_info->vis_prompt, strPlayFailed[dlna_window_info->menu_lang]);
        d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
        dlna_full_movie_set_info();
        if(first == D_FALSE)
        {
            dlna_full_movie_menu_show_en(DLNA_FULL_MOVIE_MENU_SHOW);
        }
        dlna_window_info->dlnaFullMovieInfo.totaltime = 0;
        dlna_window_info->menu_auto_close = D_TRUE;
        goto _MOVIE_PLAY_END;
    }
#endif
_MOVIE_PLAY_END:
    dlna_window_info->dlnaFullMovieMenuPlayStartTime = d_sys_get_time();
    dlna_window_info->dlnaFullMovieMarkTime = dlna_window_info->dlnaFullMovieMenuPlayStartTime;
    dlna_window_info->dlnaFullMovieLastPlayTime = (D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue;
    dlna_window_info->dlnaFullMovieCheckEndCounter = 0;
    D_DUMP("dlna_full_movie_play end %d\n", (d_sys_get_time() - t));
    return ret;
}


/** @brief 视频进度移动函数
* @param[in] key_value:LEFT 向后 RIGHT: 向前移动
*/
static D_Result
dlna_full_movie_set_play_progress_value(D_U32  key_value, D_Bool repeat) D_FUNCPOSTFIT
{
    D_Visual *vis;

    static D_S8 ppos_add = 0;

    if(repeat)
    {
        ppos_add = D_MIN((ppos_add + 1), 6);
    }
    else
    {
        ppos_add = 1;
    }

    switch(key_value)
    {
        case D_KEY_LEFT:
        case D_KEY_PNL_L:
        {
            if(dlna_window_info->progressCur_X  > dlna_window_info->progressStart_X + (5 * ppos_add))
            {
                dlna_window_info->progressCur_X = dlna_window_info->progressCur_X - 5 * ppos_add;
            }
            else
            {
                dlna_window_info->progressCur_X = dlna_window_info->progressStart_X;
            }
        }
        break;
        case D_KEY_RIGHT:
        case D_KEY_PNL_R:
        {
            if(dlna_window_info->progressCur_X + (5 * ppos_add) < dlna_window_info->progressEnd_X)
            {
                dlna_window_info->progressCur_X = dlna_window_info->progressCur_X + 5 * ppos_add;
            }
            else
            {
                dlna_window_info->progressCur_X = dlna_window_info->progressEnd_X;
            }
        }
        break;
    }

    vis = d_frame_get_control (&atv_dlna_window, ID_MOVIE_SELECT_POS);
    if(vis)
    {
        dlna_full_movie_update_set_time();
        d_vis_set_pos(vis, dlna_window_info->progressCur_X, vis->rect.y, vis->rect.w,  vis->rect.h);
        d_vis_update(vis, NULL);
    }

    return D_OK;
}

/** @brief设置进度条*/
static D_Result
dlna_full_movie_set_progress(void)
{
    D_Double total_time_value;
    D_U32   cur_set_time;

    if(dlna_window_info->dlnaFullMovieInfo.totaltime)
    {
        total_time_value = dlna_window_info->dlnaFullMovieInfo.totaltime;
        cur_set_time = (dlna_window_info->progressCur_X - dlna_window_info->progressStart_X) * total_time_value / (dlna_window_info->progressEnd_X - dlna_window_info->progressStart_X);
        D_DUMP("full_movie seek %d\n", cur_set_time);
        d_media_movie_seek(cur_set_time);
        dlna_window_info->dlnaseektime = cur_set_time;
#if CALC_TIME_EN
        dlna_window_info->dlnaseektime_start = d_sys_get_time();
#endif
        notify_protocol_playtime(cur_set_time);
        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
        dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_START_STATUS);
        return D_OK;
    }

    return D_ERR;
}

/** @brief 调整进度控件事件处理*/
static D_Result
dlna_full_movie_set_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_PNL_R:
                case D_KEY_RIGHT:
                case D_KEY_PNL_L:
                case D_KEY_LEFT:
                    dlna_full_movie_reset_show_timer(D_TRUE);
                    if((dlna_window_info->direct_movie == D_FALSE) && (dlna_window_info->dlnaFullMovieInfo.totaltime > 3))
                    {
                        dlna_window_info->dlnaFullHasSet = D_TRUE;
                        dlna_full_movie_set_play_progress_value((D_U32)(evt->fp.key), evt->fp.repeat);
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if((dlna_window_info->direct_movie == D_FALSE) && (dlna_window_info->dlnaFullHasSet == D_TRUE))
                    {
                        dlna_full_movie_set_progress();
                        dlna_window_info->dlnaFullHasSet = D_FALSE;
                        dlna_full_movie_reset_show_timer(D_TRUE);
                    }
                    return D_OK;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 窗口事件处理*/
D_Result
atv_dlna_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status;
    D_Visual *pvis;

    switch(evt->type)
    {
        case D_EVT_FP:
        {
            dlna_full_movie_reset_show_timer(D_TRUE);
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_SHOW)
                    {
                        dlna_window_info->dlnaFullHasSet = D_FALSE;
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_HIDE;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
                        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
                    }
                    else
                    {
                        p_atv_dlna_window_hide();
                        notify_protocol_status(PLAYER_STATUS_STOP);
                    }
                    return D_OK;
                case D_KEY_PNL_R:
                case D_KEY_RIGHT:
                case D_KEY_PNL_L:
                case D_KEY_LEFT:
                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_HIDE)
                    {
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        return D_OK;
                    }

                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_SHOW)
                    {
                        /* 时间太短，或播放失败时，不可能选时播放@qiny*/
                        if((dlna_window_info->direct_movie == D_FALSE) && (dlna_window_info->dlnaFullMovieInfo.totaltime > 3))
                        {
                            dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_SELECT_STATUS);
                        }
                    }
                    return D_OK;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_HIDE)
                    {
                        dlna_full_movie_set_info();
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        return D_OK;
                    }

                    /* 播放失败时不可以设定暂停与播放 @qiny*/
                    status = d_media_movie_get_status();
                    if((dlna_window_info->direct_movie == D_FALSE) && (status == MOVIE_STATUS_PLAY || status == MOVIE_STATUS_PAUSE))
                    {
                        if(dlna_window_info->dlnaFullMoviePlayStatus == DLNA_FULL_MOVIE_PLAYING_STATUS)
                        {
                            dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_PAUSE_STATUS);
                        }
                        else if(dlna_window_info->dlnaFullMoviePlayStatus == DLNA_FULL_MOVIE_PAUSE_STATUS)
                        {
                            dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_PLAYING_STATUS);
                        }
                    }
                    return D_OK;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
        }
        break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == dlna_window_info->dlnaFullMovieMenuTimer)
            {
                if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_SHOW && dlna_window_info->menu_auto_close == D_FALSE && dlna_window_info->music_mode == D_FALSE)
                {
                    D_U32 cur_t;

                    /* 解决因定时器消息阻塞而导致菜单很快消失的问题 @qiny*/
                    cur_t = d_sys_get_time();
                    if((cur_t < dlna_window_info->dlnaFullMovieMenuShowStartTime) || (cur_t - dlna_window_info->dlnaFullMovieMenuShowStartTime > (DLNA_FULL_MOVIE_MENU_SHOW_TIME - 500)))
                    {
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_HIDE;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
                        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
                        dlna_window_info->dlnaFullMoviePlayStatus = DLNA_FULL_MOVIE_PLAYING_STATUS;
                    }
                }

                if(dlna_window_info->dlnaFullHasSet == D_TRUE && dlna_window_info->menu_auto_close == D_FALSE)
                {
                    dlna_full_movie_set_progress();
                    dlna_window_info->dlnaFullHasSet = D_FALSE;
                }
                dlna_window_info->timer_counter++;
                if(dlna_window_info->menu_auto_close && dlna_window_info->timer_counter == 6)
                {
                    dlna_window_info->menu_auto_close = D_FALSE;
                    p_atv_dlna_window_hide();
                    notify_protocol_status(PLAYER_STATUS_FINISHED);
                    break;
                }
            }
            else if(evt->timer.htimer == dlna_window_info->dlnaFullMoviePlayTimer && dlna_window_info->menu_auto_close == D_FALSE)
            {
                D_ID file_id;

                status = d_media_movie_get_status();

                if(status == MOVIE_STATUS_PLAY)
                {
                    dlna_full_movie_update_show_time(D_TRUE, D_FALSE);
#if 0
                    /*播放要结束时，显示时间轴菜单*/
                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_HIDE \
                        && dlna_window_info->dlnaFullMovieCurrTimeValue >= (dlna_window_info->dlnaFullMovieTotalTimeValue - 5))
                    {
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        dlna_full_movie_reset_show_timer(D_FALSE);
                    }
#endif
                    /*防止播放器播放完毕后却没有停播*/
                    if(dlna_window_info->dlnaFullMovieCurrTimeValue >= (dlna_window_info->dlnaFullMovieTotalTimeValue + 1))
                    {
                        D_DUMP("dlnaFullMovieCurrTimeValue > dlnaFullMovieTotalTimeValue\n");
                        dlna_window_info->dlnaFullMovieCheckEndCounter++;
                        if(dlna_window_info->dlnaFullMovieCheckEndCounter >= 5)
                        {
                            dlna_window_info->dlnaFullMovieCheckEndCounter = 0;
                            p_atv_dlna_window_hide();
                            notify_protocol_status(PLAYER_STATUS_FINISHED);
                            break;
                        }
                    }
                    else if(dlna_window_info->dlnaFullMovieCurrTimeValue < dlna_window_info->dlnaFullMovieTotalTimeValue)
                    {
                        D_U32 time_value, sys_time;
                        D_U32 textidx;
                        
                        sys_time = d_sys_get_time();
                        dlna_window_info->dlnaFullMovieCheckEndCounter = 0;
                        time_value = (D_U32)dlna_window_info->dlnaFullMovieCurrTimeValue;
                        if(dlna_window_info->dlnaFullMovieLastPlayTime == time_value && dlna_window_info->dlnaFullMoviePlayStatus == DLNA_FULL_MOVIE_PLAYING_STATUS)
                        {
                            dlna_window_info->dlnaPlayWaitTime++;
                            sys_time = DLNA_CALC_TIME_INTERVAL(dlna_window_info->dlnaFullMovieMarkTime, sys_time);
                            if(sys_time >= 2000)
                            {
                                if(dlna_window_info->network_error > 0)
                                    dlna_window_info->network_error_counter++;
                            
                                if(dlna_window_info->dlnaPlayWaitTime < 150 && dlna_window_info->network_error_counter < 120)
                                {
                                    dlna_window_info->strPlayWait_idx = (dlna_window_info->strPlayWait_idx >= 3) ? 0 : dlna_window_info->strPlayWait_idx;
                                    textidx = (dlna_window_info->network_error > 0) ? (dlna_window_info->strPlayWait_idx + 6) : dlna_window_info->strPlayWait_idx;
                                    d_label_set_text(dlna_window_info->vis_prompt, strPlayWait[textidx][dlna_window_info->menu_lang]);
                                    d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
                                    dlna_window_info->strPlayWait_idx = (dlna_window_info->strPlayWait_idx + 1) % 3;
                                }
                                else if(dlna_window_info->dlnaPlayWaitTime < 240 && dlna_window_info->network_error_counter < 120)
                                {
                                    dlna_window_info->strPlayWait_idx = (dlna_window_info->strPlayWait_idx >= 3) ? 0 : dlna_window_info->strPlayWait_idx;
                                    textidx = (dlna_window_info->network_error > 0) ? (dlna_window_info->strPlayWait_idx + 6) : (dlna_window_info->strPlayWait_idx + 3);
                                    d_label_set_text(dlna_window_info->vis_prompt, strPlayWait[textidx][dlna_window_info->menu_lang]);
                                    d_vis_show(dlna_window_info->vis_prompt, D_TRUE);
                                    dlna_window_info->strPlayWait_idx = (dlna_window_info->strPlayWait_idx + 1) % 3;
                                }
                                else
                                {
                                    p_atv_dlna_window_hide();
                                    notify_protocol_status(PLAYER_STATUS_FINISHED);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            dlna_window_info->dlnaFullMovieMarkTime = sys_time;
                            d_vis_show(dlna_window_info->vis_prompt, D_FALSE);
                            dlna_window_info->strPlayWait_idx = 0xFF;
                            dlna_window_info->dlnaPlayWaitTime = 0;
                        }
                        dlna_window_info->dlnaFullMovieLastPlayTime = time_value;
                    }
                }
                else if(status == MOVIE_STATUS_STOP)
                {
                    D_U32 t_now;
                    D_DUMP("status == MOVIE_STATUS_STOP\n");
                    /* 不支持的提示显示时间稍长些，即两个不支持的文件播放间隔时间长些 @qiny*/
                    t_now = d_sys_get_time();
                    if((t_now < dlna_window_info->dlnaFullMovieMenuPlayStartTime) || (t_now - dlna_window_info->dlnaFullMovieMenuPlayStartTime > (DLNA_FULL_MOVIE_PLAY_REFRESH_TIME * 2 - 200)))
                    {

                    }
                    if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_SHOW)
                    {
                        dlna_window_info->dlnaFullHasSet = D_FALSE;
                        dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_HIDE;
                        dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
                        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
                    }
                    else
                    {
                        p_atv_dlna_window_hide();
                        notify_protocol_status(PLAYER_STATUS_FINISHED);
                        break;
                    }
                    break;
                }
            }
            break;
        case D_EVT_USER1:
            if(evt->user.param1 == USER_MSG_PARAM1_DLNA_VOLUME || evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_VOLUME)
            {
                dlna_window_info->dlnavol = p_conf_get_volume();
                if(dlna_window_info->dlnavol != (D_S8)evt->user.param2)
                {
#if 0
                    if(dlna_window_info->dlnavol < (D_S8)evt->user.param2)
                    {
                        dlna_window_info->dlnavol = D_MIN(dlna_window_info->dlnavol + 2, (D_S8)evt->user.param2);
                    }
                    else if(dlna_window_info->dlnavol > (D_S8)evt->user.param2)
                    {
                        dlna_window_info->dlnavol = D_MAX(dlna_window_info->dlnavol - 2, (D_S8)evt->user.param2);
                    }
                    else
#endif
                    {
                        dlna_window_info->dlnavol = (D_S8)evt->user.param2;
                    }
                    if (p_conf_get_aud_mute())
                    {
                        d_tv_set_aud_mute (g_stb->player->htv, D_FALSE);
                        p_conf_set_aud_mute (D_FALSE);
                        p_atv_mute_window_clear();
                    }
                    p_conf_set_volume (dlna_window_info->dlnavol);
                    p_atv_volume_window_show(0, 0);
                }
            }
            else if((evt->user.param1 == USER_MSG_PARAM1_DLNA_SEEK || evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_MOVIE_SEEK) && dlna_window_info->menu_auto_close == D_FALSE && dlna_window_info->dlnaFullMovieTotalTimeValue > (D_U32)evt->user.param2)
            {
                if(dlna_window_info->dlnaFullMoviePlayStatus == DLNA_FULL_MOVIE_PAUSE_STATUS)
                {
                    dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_PLAYING_STATUS);
                }
                dlna_window_info->dlnaseektime = (D_U32)evt->user.param2;
                d_media_movie_seek((D_U64)dlna_window_info->dlnaseektime);
#if CALC_TIME_EN
                dlna_window_info->dlnaseektime_start = d_sys_get_time();
#endif
                dlna_window_info->progressCur_X = (dlna_window_info->dlnaseektime) * (dlna_window_info->progressEnd_X - dlna_window_info->progressStart_X) / (dlna_window_info->dlnaFullMovieInfo.totaltime);
                pvis = d_frame_get_control (&atv_dlna_window, ID_MOVIE_SELECT_POS);
                if(pvis)
                {
                    dlna_full_movie_update_set_time();
                    d_vis_set_pos(pvis, dlna_window_info->progressCur_X, pvis->rect.y, pvis->rect.w,  pvis->rect.h);
                    d_vis_update(pvis, NULL);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_DLNA_NO_CONNECT || evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_MOVIE_STOP)
            {
                if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_SHOW)
                {
                    dlna_window_info->dlnaFullHasSet = D_FALSE;
                    dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_HIDE;
                    dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                    d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
                    dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
                }
                d_gui_update();
                p_atv_dlna_window_hide();
                notify_protocol_status(PLAYER_STATUS_FINISHED);
                break;
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_DLNA_NEXT_MOVIE)
            {
                D_Char*  file_title = (D_Char *)evt->user.param3;
                D_Char*  path_name =  (D_Char *)evt->user.param2;

                /*停止播放*/
                d_media_movie_stop();
                memset(dlna_window_info->dlnaFullMoviePathName, 0x00, sizeof(dlna_window_info->dlnaFullMoviePathName));
                memset(dlna_window_info->dlnaFullMovieTotalTime, 0x00, sizeof(dlna_window_info->dlnaFullMovieTotalTime));
                memset(dlna_window_info->dlnaFullMovieName, 0x00, sizeof(dlna_window_info->dlnaFullMovieName));
                memset(dlna_window_info->dlnaFullMoviehw, 0x00, sizeof(dlna_window_info->dlnaFullMoviehw));
                //strncpy(dlna_window_info->dlnaFullMovieTitle, file_title, D_MIN((sizeof(dlna_window_info->dlnaFullMovieTitle) - 1), strlen(file_title)));
                p_cc_utf8_to_sys(dlna_window_info->dlnaFullMovieTitle, sizeof(dlna_window_info->dlnaFullMovieTitle), file_title, strlen(file_title));
                strncpy(dlna_window_info->dlnaFullMoviePathName, path_name, sizeof(dlna_window_info->dlnaFullMoviePathName) - 1);
                if(dlna_window_info->dlnaFullMoviePlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(dlna_window_info->dlnaFullMoviePlayTimer);
                    dlna_window_info->dlnaFullMoviePlayTimer = D_INVALID_HANDLE;
                    dlna_window_info->dlnaFullMoviePlayTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_PLAY_REFRESH_TIME, d_gui_get_queue());
                    if(dlna_window_info->dlnaFullMoviePlayTimer != D_INVALID_HANDLE)
                    {
                        d_vis_subscribe_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMoviePlayTimer);
                    }
                }

                if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(dlna_window_info->dlnaFullMovieMenuTimer);
                    dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
                    dlna_window_info->dlnaFullMovieMenuTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
                    if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                    {
                        d_vis_subscribe_evt(dlna_window_info->vis_full_win, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
                    }
                }
                dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
                dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                dlna_window_info->dlnaFullHasSet = D_FALSE;

                dlna_window_info->progressCur_X = dlna_window_info->progressStart_X;
                if(D_OK != dlna_full_movie_play(D_TRUE))
                {
                    return D_ERR;
                }
            }
            else if((evt->user.param1 == USER_MSG_PARAM1_DLNA_STATUS || evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_MOVIE_STATUS) && dlna_window_info->menu_auto_close == D_FALSE)
            {
                status = (D_U8)evt->user.param2;

                if(dlna_window_info->dlnaFullMovieMenuEnable == DLNA_FULL_MOVIE_MENU_HIDE)
                {
                    dlna_full_movie_set_info();
                    dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
                    dlna_full_movie_menu_show_en(dlna_window_info->dlnaFullMovieMenuEnable);
                }

                if(status == (D_U8)PLAYER_STATUS_PLAYING)
                {
                    dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_PLAYING_STATUS);
                }
                else if(status == (D_U8)PLAYER_STATUS_PAUSED)
                {
                    dlna_full_movie_set_play_status(DLNA_FULL_MOVIE_PAUSE_STATUS);
                }
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(dlna_window_info)
            {
                if(dlna_window_info->dlnaFullMoviePlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(dlna_window_info->dlnaFullMoviePlayTimer);
                    dlna_window_info->dlnaFullMoviePlayTimer = D_INVALID_HANDLE;
                }

                if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(dlna_window_info->dlnaFullMovieMenuTimer);
                    dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
                }

                d_media_movie_stop();
#if 0 /* 菜单之外调用，避免频繁media与dtv的切换*/
                if(dlna_window_info->media_open_flag)
                {
                    d_media_movie_close();
                    d_mediacodec_close();
                }
                d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
                /* 重设静音/声道/音量*/
                p_stb_reset_mute_track_volume();
#endif
                PROJECT_FREE(dlna_window_info);
                dlna_window_info = NULL;
                if(normal_destroy == D_FALSE)
                {
                    notify_protocol_status(PLAYER_STATUS_STOP);
                }
            }
            normal_destroy = D_FALSE;
            p_atv_zhilian_tv_window_show_enable(D_TRUE);
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_dlna_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    normal_destroy = D_FALSE;
    
#if 0 /* 菜单之外调用，避免频繁media与dtv的切换*/
    //d_av_set_vid_input (0, D_VID_IUTPUT_USB1);

    /* 释放epg占用资源*/
    p_auxi_free_varstring();

    d_mediacodec_open();
    d_media_movie_set_version(MOVIE_FFMPEG_VER_NEW_V34);
    d_media_movie_open() ;
    /*重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();
#endif    
    d_media_movie_open() ;
    /*缩放模式选自动*/
    d_av_set_tv_ratio_mode(0, D_NATURAL_RATIO);
    p_av_set_vid_background(0, D_VID_BackGround_BLack, D_FALSE);

    dlna_window_info->media_open_flag = D_TRUE;
    dlna_window_info->dlnaFullMoviePlayTimer = D_INVALID_HANDLE;
    dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
    dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
    dlna_window_info->dlnaFullMovieMenuEnable = DLNA_FULL_MOVIE_MENU_SHOW;
    dlna_window_info->menu_lang = (D_LANG_CHN == p_conf_get_lang()) ? 1 : 0;
    dlna_window_info->vis_play_progress = d_frame_get_control(frm, ID_FULL_MOVIE_PROGRESS);
    dlna_window_info->vis_play_pos = d_frame_get_control(frm, ID_MOVIE_SELECT_POS);
    dlna_window_info->vis_time = d_frame_get_control(frm, ID_FULL_MOVIE_TOTAL_TIME);
    dlna_window_info->vis_play_group = d_frame_get_control(frm, ID_FULL_MOVIE_CONTROL_GROUP);
    dlna_window_info->vis_play_status = d_frame_get_control(frm, ID_FULL_MOVIE_STATUS);
    dlna_window_info->vis_show_status = d_frame_get_control(frm, ID_FULL_MOVIE_STATUS_LABEL);
    dlna_window_info->vis_prompt = d_frame_get_control(frm, ID_FULL_MOVIE_PROMPT_MSG);
    d_vis_show(dlna_window_info->vis_prompt, D_FALSE);

    dlna_window_info->vis_music = d_frame_get_control(frm, ID_FULL_MUSIC_PROMPT_ICON);
    d_vis_show(dlna_window_info->vis_music, D_FALSE);
    
    dlna_window_info->dlnaFullHasSet = D_FALSE;

    dlna_window_info->progressStart_X = dlna_window_info->vis_play_progress->rect.x;
    dlna_window_info->progressEnd_X = dlna_window_info->vis_play_progress->rect.w + dlna_window_info->vis_play_progress->rect.x;
    dlna_window_info->progressCur_X = dlna_window_info->progressStart_X;

    dlna_window_info->vis_info_group = d_frame_get_control(frm, ID_FULL_MOVIE_INFO_GROUP);
    dlna_window_info->vis_name = d_frame_get_control(frm, ID_FULL_MOVIE_NAME);
    dlna_window_info->vis_hw = d_frame_get_control(frm, ID_FULL_MOVIE_HW_1);

    d_vis_set_pos(dlna_window_info->vis_play_pos, dlna_window_info->progressStart_X, dlna_window_info->vis_play_pos->rect.y, dlna_window_info->vis_play_pos->rect.w, dlna_window_info->vis_play_pos->rect.h);
    d_vis_update (dlna_window_info->vis_play_pos, NULL);

    vis = d_frame_get_control (frm, ID_MOVIE_SELECT_POS);
    if (vis)
    {
        d_vis_set_focusable(dlna_window_info->vis_play_pos, D_FALSE);
        dlna_window_info->dlnaFullMovieSelectPos = D_FALSE;
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, dlna_full_movie_set_progress_handler);
    }
    d_label_set_text(d_frame_get_control (frm, ID_FULL_MOVIE_NAME_1), "文件名");
    d_label_set_text(dlna_window_info->vis_name, dlna_window_info->dlnaFullMovieTitle);

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        dlna_window_info->vis_full_win = vis;
        d_vis_get_pos(dlna_window_info->vis_full_win, &dlna_window_info->dlnaFullMovieWin.x, &dlna_window_info->dlnaFullMovieWin.y);
        dlna_window_info->dlnaFullMovieWin.x = 0;
        dlna_window_info->dlnaFullMovieWin.y = 0;
        dlna_window_info->dlnaFullMovieWin.w = -1;
        dlna_window_info->dlnaFullMovieWin.h = -1;

        if(D_OK != dlna_full_movie_play(D_TRUE))
        {
#if 0
            d_vis_unsubscribe_evt(vis);
            PROJECT_FREE(dlna_window_info);
            dlna_window_info = NULL;
#endif
            d_media_movie_stop();
            //d_media_movie_close() ;
            //d_mediacodec_close();
            //dlna_window_info->media_open_flag = D_FALSE;
        }

        if(dlna_window_info->dlnaFullMoviePlayTimer == D_INVALID_HANDLE)
        {
            dlna_window_info->dlnaFullMoviePlayTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_PLAY_REFRESH_TIME, d_gui_get_queue());
            if(dlna_window_info->dlnaFullMoviePlayTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMoviePlayTimer);
            }
        }
        if(dlna_window_info->dlnaFullMovieMenuTimer == D_INVALID_HANDLE)
        {
            dlna_window_info->dlnaFullMovieMenuTimer = d_timer_create(NULL, DLNA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
            if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, dlna_window_info->dlnaFullMovieMenuTimer);
            }
        }
        /*处理用户事件*/
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_dlna_window_handler);
    }
    return D_OK;
}


/** @brief 显示dlna视频播放窗口*/
D_Result
p_atv_dlna_window_show(D_Char*  file_path , D_Char*  file_title, D_VidInput lastinput) D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;

    if(dlna_menu_hmutex == D_INVALID_HANDLE)
        dlna_menu_hmutex = d_mutex_create(NULL);

    DLNA_MENU_LOCK();

    D_DUMP("file_path(%s)\n", file_path);
    if(file_title)
    D_DUMP("file_title(%s)\n", file_title);
    if(file_path != NULL)
    {
        if (D_FALSE == d_frame_is_loaded (&atv_dlna_window))
        {
            dlna_window_info = (DlnaWindowInfo*)PROJECT_ALLOC(sizeof(DlnaWindowInfo));
            if(dlna_window_info)
            {
                memset(dlna_window_info, 0x00, sizeof(DlnaWindowInfo));
                dlna_window_info->dlnavol = -1;
                dlna_window_info->dlnaFullMoviePlayTimer = D_INVALID_HANDLE;
                dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
                dlna_window_info->lastinput = lastinput;
                //p_conf_set_vid_input(D_VID_IUTPUT_USB1);
                //p_sys_set_input_mode(dlna_window_info->lastinput, D_VID_IUTPUT_USB1);
                //d_gui_clear_menu_ext(ATV_MEDIA_MENU_ID);
                //p_gui_atv_media_resource_init();
                if(file_title)
                {
                    //strncpy(dlna_window_info->dlnaFullMovieTitle, file_title, D_MIN((sizeof(dlna_window_info->dlnaFullMovieTitle) - 1), strlen(file_title)));
                    p_cc_utf8_to_sys(dlna_window_info->dlnaFullMovieTitle, sizeof(dlna_window_info->dlnaFullMovieTitle), file_title, strlen(file_title));
                }
                strncpy(dlna_window_info->dlnaFullMoviePathName, file_path, D_MIN((sizeof(dlna_window_info->dlnaFullMoviePathName) - 1), strlen(file_path)));
#if 0
                {
                    D_U32 len = strlen(file_path);
                    if((len > 4) && (file_path[len - 4] == '.') && (file_path[len - 3] == 'm' || file_path[len - 3] == 'M') && (file_path[len - 2] == 'p' || file_path[len - 2] == 'P') && (file_path[len - 1] == '3'))
                    {
                        dlna_window_info->music_mode = D_TRUE;
                    }
                }
#endif
                ret = d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &atv_dlna_window, D_CLEAR_NONE);
                if(ret != D_OK && dlna_window_info)
                {
                    if(dlna_window_info->dlnaFullMoviePlayTimer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(dlna_window_info->dlnaFullMoviePlayTimer);
                        dlna_window_info->dlnaFullMoviePlayTimer = D_INVALID_HANDLE;
                    }

                    if(dlna_window_info->dlnaFullMovieMenuTimer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(dlna_window_info->dlnaFullMovieMenuTimer);
                        dlna_window_info->dlnaFullMovieMenuTimer = D_INVALID_HANDLE;
                    }

                    PROJECT_FREE(dlna_window_info);
                    dlna_window_info = NULL;
                }
            }
        }
    }
    DLNA_MENU_UNLOCK();
    return ret;
}

/** @brief 关闭dlna视频播放窗口*/
D_Result
p_atv_dlna_window_hide(void) D_FUNCPOSTFIT
{
    DLNA_MENU_LOCK();

    if (D_TRUE == d_frame_is_loaded (&atv_dlna_window))
    {
        D_VidInput  lastinput = dlna_window_info->lastinput;

        d_media_movie_stop();
        d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
#if 0 /* 菜单之外调用，避免频繁media与dtv的切换*/
        if(dlna_window_info->media_open_flag)
        {
            d_media_movie_close();
            d_mediacodec_close();
            dlna_window_info->media_open_flag = D_FALSE;
        }

        /*停止播放*/
        d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        /* 重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();
#endif 
        //p_conf_set_vid_input(lastinput);
        normal_destroy = D_TRUE;
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
        //notify_protocol_status(PLAYER_STATUS_FINISHED);
#if 0
        //p_sys_set_input_mode(D_VID_IUTPUT_USB1, lastinput);
        if(lastinput == D_VID_IUTPUT_USB1)
        {
            //p_atv_media_main_menu_show();
        }
#endif
    }
    DLNA_MENU_UNLOCK();
    return D_OK;
}

/** @brief 通知dlna视频播放窗口网络状态*/
D_Result
p_atv_dlna_window_network_error(D_U32 action) D_FUNCPOSTFIT
{
    if ((D_TRUE == d_frame_is_loaded (&atv_dlna_window)) && dlna_window_info)
    {
        if(action)
        {
            dlna_window_info->network_error = 1;
        }
        else
        {
            dlna_window_info->network_error = 0;
            dlna_window_info->network_error_counter = 0;
        }
    }
    return D_OK;
}

