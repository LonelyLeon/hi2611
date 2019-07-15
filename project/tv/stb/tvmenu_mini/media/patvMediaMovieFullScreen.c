#include <stdio.h>
#include <string.h>
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFrame.h"
#include "dGui.h"
#include "pMenu.h"
#include "pPlayer.h"
#include "pMem.h"
#include "pFile_Scan.h"
#include "dMedia.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dCBMan.h"
#include "dPvrReplay.h"

#include "atv_media_movie_full_window.c"

#define MEDIA_FULL_MOVIE_PLAY_REFRESH_TIME (1000)
#define MEDIA_FULL_MOVIE_MENU_SHOW_TIME    (3000)
#define MEDIA_FULL_MOVIE_PATH_NAME_LEN     D_PATH_LENGTH
#define MEDIA_FULL_MOVIE_BUFF_SIZE         (64)

#define MEDIA_FULL_MOVIE_MENU_HIDE   (0)
#define MEDIA_FULL_MOVIE_MENU_SHOW   (1)

#define MEDIA_FULL_MOVIE_START_STATUS   (0)
#define MEDIA_FULL_MOVIE_PAUSE_STATUS   (1)
#define MEDIA_FULL_MOVIE_STOP_STATUS    (2)
#define MEDIA_FULL_MOVIE_PLAYING_STATUS (3)
#define MEDIA_FULL_MOVIE_SELECT_STATUS  (4)
#define MEDIA_FULL_MOVIE_UNKNOW_AUDIO_MAX  (3)//不支持的声音格式

#define MEDIA_FULL_MOVIE_FILE_SIZE    (64)
#define MAX__COUNTER     (0xffffffff / (d_rtc_timer_get_freq() / 1000))

typedef enum
{
    MEDIA_MOVIE_LIST_LOOP = 0,      /*列表循环(播放到列表最后一个会接着播放第一首)*/
    MEDIA_MOVIE_SINGLE_LOOP,        /*单曲循环*/
    MEDIA_MOVIE_RANDOM_PLAY,        /*随机播放*/
    MEDIA_MOVIE_LIST_PLAY,          /*列表播放(播放到列表最后一个会停止播放)*/

} MEDIA_FULL_MOVIE_PLAY_MODE;

typedef struct
{
    D_HTimer mediaFullMoviePlayTimer;
    D_HTimer mediaFullMovieMenuTimer;


    D_Char   mediaFullMoviePathName[MEDIA_FULL_MOVIE_PATH_NAME_LEN];
    D_Char   mediaFullMovieTotalTime[MEDIA_FULL_MOVIE_BUFF_SIZE];
    D_Char   mediaFullMoviePreName[MEDIA_FULL_MOVIE_PATH_NAME_LEN];

    D_Char   mediaFullMovieFileSize[MEDIA_FULL_MOVIE_FILE_SIZE];
    D_Char   mediaFullMovieName[MEDIA_FULL_MOVIE_PATH_NAME_LEN];
    D_Char   mediaFullMoviehw[MEDIA_FULL_MOVIE_FILE_SIZE];

    D_Double mediaFullMovieTotalTimeValue;
    D_Double mediaFullMovieCurrTimeValue;
    D_U32    mediaFullMovieProgressValue;
    D_U8     mediaFullMoviePlayStatus;
    D_U16    mediaFullMovieCurrIndex;
    D_Bool   mediaFullMovieSelectPos;

    D_U32   mediaFullMovieMenuPlayStartTime;

    D_U8     mediaFullMovieMenuEnable;
    D_U32   mediaFullMovieMenuShowStartTime;

    D_VidWindow mediaFullMovieWin;          /*电影全屏窗口*/
    D_MovieInfo mediaFullMovieInfo;

    D_Bool      mediaFullMovieTsFlag;
    D_Bool      mediaFullMovieInfoValid;

    D_Handle mediaFullMovie_pvr_tsparse_handle;
    D_Char cb_pic_file_path[D_PATH_LENGTH];

    D_U16       mediaStart_X;/*起始的x 坐标*/
    D_U16       mediaEnd_X;/*结束的x 坐标*/
    D_U16       mediaCur_X; /*离父控件的x 坐标*/

    D_Bool      mediaFullHasSet;

    D_FileScan*  mediaFileScan;
    MEDIA_FULL_MOVIE_PLAY_MODE  mediaFullPlayMode;

    /*全屏返回的handler*/
    D_Result (*mediaFullMovieHideHandler) (D_U16 param) D_FUNCPOSTFIT;

    D_Visual* vis_full_win, *vis_play_progress, *vis_play_pos;
    D_Visual* vis_time, *vis_play_group, *vis_info_group;
    D_Visual* vis_play_status, *vis_show_status;
    D_Visual* vis_name, *vis_hw, *vis_size;

} MediaFullMovieData;

static MediaFullMovieData* media_full_movie_data = NULL;

D_U32 movie_audio_select = 0;
D_S8 movie_ts_prog_select = 0;

/*关于视频流畅计数判断*/
#if 0
static D_Result last_status = D_OK;
static D_S32 last_time = 0;

static D_U32 get_time(void)
{
    D_U32 time = d_rtc_timer_get_counter();
    time = time / (d_rtc_timer_get_freq() / 1000);
    if (!time) time++;
    return time;
}

static D_U32 get_interval(D_U32 start)
{
    D_U32 time;
    time = get_time();
    if (time < start)
    {
        time = time + (MAX__COUNTER - start) + 1;
    }
    else
    {
        time = time - start;
    }
    return time;
}
#endif

//不支持的音频格式
static D_ID unknow_audio_id[MEDIA_FULL_MOVIE_UNKNOW_AUDIO_MAX] = { D_AUD_CODEC_DTS, D_AUD_CODEC_AC3, D_AUD_CODEC_VORBIS};
static char* unknow_audio_String[MEDIA_FULL_MOVIE_UNKNOW_AUDIO_MAX] =
{
    "不支持的音频格式:DTS",
    "不支持的音频格式:AC3",
    "不支持的音频格式:VORBIS",
};
static D_Result
media_full_movie_reset_show_timer(void) D_FUNCPOSTFIT;

static void media_full_movie_set_info(D_Bool TS, D_Bool valid)
{
    D_Char  file_size[32];
    D_Char  file_bps[64];
    D_U64 filesize = 0;
    D_U32 height = 0, width = 0;

    //name
    p_cc_utf8_to_sys((D_U8*)media_full_movie_data->mediaFullMovieName, D_PATH_LENGTH,
                     (D_U8*)media_full_movie_data->mediaFileScan->ids[media_full_movie_data->mediaFullMovieCurrIndex].path.filename, strlen(media_full_movie_data->mediaFileScan->ids[media_full_movie_data->mediaFullMovieCurrIndex].path.filename));
    d_label_set_text(media_full_movie_data->vis_name, media_full_movie_data->mediaFullMovieName);

    media_full_movie_data->mediaFullMovieTsFlag = TS;
    media_full_movie_data->mediaFullMovieInfoValid = valid;

    if(valid)
    {
        //size
        if(TS)
        {
            filesize = media_full_movie_data->mediaFullMovieInfo.filesize;
            d_av_get_cur_hw(&width, &height);
            media_full_movie_data->mediaFullMovieInfo.height = height;
            media_full_movie_data->mediaFullMovieInfo.width = width;
        }
        else
        {
            filesize = media_full_movie_data->mediaFullMovieInfo.filesize;
            height = media_full_movie_data->mediaFullMovieInfo.height;
            width = media_full_movie_data->mediaFullMovieInfo.width;
        }
    }

    p_unit_converter((D_Double)filesize, file_size);
    sprintf(media_full_movie_data->mediaFullMovieFileSize, "%s", file_size);
    d_label_set_text(media_full_movie_data->vis_size, media_full_movie_data->mediaFullMovieFileSize);
    if(width == 0 || height == 0)
    {
        sprintf(media_full_movie_data->mediaFullMoviehw, "");
    }
    else
    {
        sprintf(media_full_movie_data->mediaFullMoviehw, "%d x %d", width, height);
    }
    d_label_set_text(media_full_movie_data->vis_hw, media_full_movie_data->mediaFullMoviehw);

}

/*刷新ts视频分辨率*/
static media_full_movie_update_ts_wh(void)
{
    if(media_full_movie_data->mediaFullMovieTsFlag)
    {
        D_U32 height = 0, width = 0;
        d_av_get_cur_hw(&width, &height);
        if(media_full_movie_data->mediaFullMovieInfo.height != height || media_full_movie_data->mediaFullMovieInfo.width != width)
        {
            media_full_movie_data->mediaFullMovieInfo.height = height;
            media_full_movie_data->mediaFullMovieInfo.width = width;
            if(width == 0 || height == 0)
            {
                sprintf(media_full_movie_data->mediaFullMoviehw, "");
            }
            else
            {
                sprintf(media_full_movie_data->mediaFullMoviehw, "%dX%d", width, height);
            }
            d_label_set_text(media_full_movie_data->vis_hw, media_full_movie_data->mediaFullMoviehw);
            p_atv_media_movie_info_window_update_wh(&media_full_movie_data->mediaFullMovieInfo);
        }
    }
}

static char* atv_get_unknow_audiochar(D_ID audio) D_FUNCPOSTFIT
{
    D_U16 i;
    for(i = 0; i < MEDIA_FULL_MOVIE_UNKNOW_AUDIO_MAX; i ++)
    {
        if(unknow_audio_id[i] == audio)
        {
            return unknow_audio_String[i];
        }
    }
    return NULL;
}

static D_Result
media_full_movie_analyse_file_path(void)
{
    D_U32 length;

    length = strlen(media_full_movie_data->mediaFullMoviePathName);
    if(length)
    {
        media_full_movie_data->mediaFullMoviePathName[length] = '/';
        media_full_movie_data->mediaFullMoviePathName[length + 1] = '\0';
        strcat(media_full_movie_data->mediaFullMoviePathName, media_full_movie_data->mediaFileScan->ids[media_full_movie_data->mediaFullMovieCurrIndex].path.fullpath);
    }

    return D_OK;
}

static D_Result
media_full_movie_menu_show_en(D_Bool show)D_FUNCPOSTFIT
{
    media_full_movie_data->mediaFullMovieMenuEnable = show;
    d_vis_show(media_full_movie_data->vis_play_group, show);
    d_vis_show(media_full_movie_data->vis_info_group, show);
	p_show_osd_window(show);
    if(show)
    {
        media_full_movie_reset_show_timer();
    }
    return D_OK;
}

/** @brief 复位显示定时器*/
static D_Result
media_full_movie_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(media_full_movie_data)
    {
        if(media_full_movie_data->mediaFullMovieMenuTimer == D_INVALID_HANDLE)
        {
            media_full_movie_data->mediaFullMovieMenuTimer = d_timer_create(NULL, MEDIA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
            if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(media_full_movie_data->vis_full_win, D_EVT_TIMER_MASK, media_full_movie_data->mediaFullMovieMenuTimer);
            }
        }
        if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
        {
            d_timer_reset(media_full_movie_data->mediaFullMovieMenuTimer, MEDIA_FULL_MOVIE_MENU_SHOW_TIME);
            media_full_movie_data->mediaFullMovieMenuShowStartTime = d_sys_get_time();
        }
    }
    return D_OK;
}


static D_Result
media_full_movie_find_next_or_pre_by_play_mode(MEDIA_FULL_MOVIE_PLAY_MODE play_mode, D_U8 flag)D_FUNCPOSTFIT
{
    D_U32  idx, play_id = -1;

    if(flag)
    {
        switch(play_mode)
        {
            case MEDIA_MOVIE_SINGLE_LOOP:
                play_id = media_full_movie_data->mediaFullMovieCurrIndex;
                break;
            case MEDIA_MOVIE_LIST_LOOP:

                for(idx = media_full_movie_data->mediaFullMovieCurrIndex + 1; idx < media_full_movie_data->mediaFileScan->cnt; idx++)
                {
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                }

                if(play_id == -1)
                {
                    for(idx = 0; idx <= media_full_movie_data->mediaFullMovieCurrIndex; idx++)
                    {
                        if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                        {
                            play_id = idx;
                            break;
                        }
                        else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                        {
                            play_id = idx;
                            break;
                        }
                    }
                }
                break;
            case MEDIA_MOVIE_RANDOM_PLAY:
                srand(d_sys_get_time());
                while(1)
                {
                    idx = rand() % (media_full_movie_data->mediaFileScan->cnt);
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }

                }
                break;
            case MEDIA_MOVIE_LIST_PLAY:
                for(idx = media_full_movie_data->mediaFullMovieCurrIndex + 1; idx < media_full_movie_data->mediaFileScan->cnt; idx++)
                {
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                }
                break;
        }
    }
    else
    {
        switch(play_mode)
        {
            case MEDIA_MOVIE_SINGLE_LOOP:
                play_id = media_full_movie_data->mediaFullMovieCurrIndex;
                break;
            case MEDIA_MOVIE_LIST_LOOP:
                for(idx = media_full_movie_data->mediaFullMovieCurrIndex - 1; idx > 0; idx--)
                {
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                }

                if(play_id == -1)
                {
                    for(idx = media_full_movie_data->mediaFileScan->cnt - 1; idx >= media_full_movie_data->mediaFullMovieCurrIndex; idx--)
                    {
                        if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                        {
                            play_id = idx;
                            break;
                        }
                        else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                        {
                            play_id = idx;
                            break;
                        }
                    }
                }
                break;
            case MEDIA_MOVIE_RANDOM_PLAY:
                srand(d_sys_get_time());
                while(1)
                {
                    idx = rand() % (media_full_movie_data->mediaFileScan->cnt);
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }

                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }

                }
                break;
            case MEDIA_MOVIE_LIST_PLAY:
                for(idx = media_full_movie_data->mediaFullMovieCurrIndex - 1; idx > 0; idx--)
                {
                    if(Judge_Movie_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                    else if(Judge_TS_File(&(media_full_movie_data->mediaFileScan->ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                }
                break;
        }

    }
    return play_id;
}

static D_Result
media_full_mvoie_set_play_status(D_U8 status)D_FUNCPOSTFIT
{
    media_full_movie_data->mediaFullMoviePlayStatus = status;
    switch(status)
    {
        case MEDIA_FULL_MOVIE_START_STATUS:
            media_full_movie_data->mediaFullMoviePlayStatus = MEDIA_FULL_MOVIE_PLAYING_STATUS;
            d_image_box_set_image(media_full_movie_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_pause));
            d_label_set_text(media_full_movie_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
            break;
        case MEDIA_FULL_MOVIE_PAUSE_STATUS:
            if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_unsubscribe_one_evt(media_full_movie_data->vis_full_win, D_EVT_TIMER_MASK, media_full_movie_data->mediaFullMovieMenuTimer);
                d_timer_destroy(media_full_movie_data->mediaFullMovieMenuTimer);
                media_full_movie_data->mediaFullMovieMenuTimer = D_INVALID_HANDLE;
            }

            if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_HIDE)
            {
                media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_SHOW;
                media_full_movie_menu_show_en(media_full_movie_data->mediaFullMovieMenuEnable);
            }

            d_media_movie_pause();
            d_image_box_set_image(media_full_movie_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_play));
            d_label_set_text(media_full_movie_data->vis_show_status, d_gui_get_text(atv_IDS_PLAY));
            break;
        case MEDIA_FULL_MOVIE_PLAYING_STATUS:
            if(media_full_movie_data->mediaFullMovieMenuTimer == D_INVALID_HANDLE)
            {
                media_full_movie_data->mediaFullMovieMenuTimer = d_timer_create(NULL, MEDIA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
                if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_vis_subscribe_evt(media_full_movie_data->vis_full_win, D_EVT_TIMER_MASK, media_full_movie_data->mediaFullMovieMenuTimer);
                }
                media_full_movie_data->mediaFullMovieMenuShowStartTime = d_sys_get_time();
            }
            d_media_movie_resume();
            d_image_box_set_image(media_full_movie_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_pause));
            d_label_set_text(media_full_movie_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
            break;
        case MEDIA_FULL_MOVIE_STOP_STATUS:
            break;
        case MEDIA_FULL_MOVIE_SELECT_STATUS:
            d_vis_set_pos(media_full_movie_data->vis_play_pos, media_full_movie_data->mediaCur_X, media_full_movie_data->vis_play_pos->rect.y, media_full_movie_data->vis_play_pos->rect.w, media_full_movie_data->vis_play_pos->rect.h);
            d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_TRUE);
            d_vis_set_focus(media_full_movie_data->vis_play_pos);
            d_vis_update (media_full_movie_data->vis_play_pos, NULL);

            media_full_movie_data->mediaFullMovieSelectPos = D_TRUE;
            break;
        default:
            break;
    }
}

static D_Result
media_full_movie_update_show_time(D_Bool show, D_Bool reset) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;

    if(reset)
    {
        media_full_movie_data->mediaFullMovieTotalTimeValue = 0;
        media_full_movie_data->mediaFullMovieCurrTimeValue = 0;
        media_full_movie_data->mediaFullMovieProgressValue = 0;
        media_full_movie_data->mediaFullHasSet = D_FALSE;
        media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
        d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_FALSE);
    }
    else
    {
        media_full_movie_data->mediaFullMovieTotalTimeValue = media_full_movie_data->mediaFullMovieInfo.totaltime;
        media_full_movie_data->mediaFullMovieCurrTimeValue = d_media_movie_get_curtime();

        if(media_full_movie_data->mediaFullMovieTotalTimeValue)
        {
            media_full_movie_data->mediaFullMovieProgressValue = (media_full_movie_data->mediaFullMovieCurrTimeValue * 100) / media_full_movie_data->mediaFullMovieTotalTimeValue;
        }
    }

    total_hour = (D_U32)media_full_movie_data->mediaFullMovieTotalTimeValue / 3600;
    total_min   = ((D_U32)media_full_movie_data->mediaFullMovieTotalTimeValue % 3600) / 60;
    total_sec   = ((D_U32)media_full_movie_data->mediaFullMovieTotalTimeValue % 3600) % 60;

    cur_hour  = (D_U32)media_full_movie_data->mediaFullMovieCurrTimeValue / 3600;
    cur_min  = ((D_U32)media_full_movie_data->mediaFullMovieCurrTimeValue % 3600) / 60;
    cur_sec  = ((D_U32)media_full_movie_data->mediaFullMovieCurrTimeValue % 3600 ) % 60;

    /*设置进度显示*/
    d_progress_bar_set_val(media_full_movie_data->vis_play_progress, show ? media_full_movie_data->mediaFullMovieProgressValue : 0);
    //D_DUMP("progress:%d\n", media_full_movie_data->mediaFullMovieProgressValue);
    if(media_full_movie_data->mediaFullMovieSelectPos == D_FALSE)
    {
        if(0 == media_full_movie_data->mediaFullMovieTotalTimeValue)
        {
            sprintf(media_full_movie_data->mediaFullMovieTotalTime, "%s/%s", "--:--:--", "--:--:--");
        }
        else
        {
            sprintf(media_full_movie_data->mediaFullMovieTotalTime, "%02d:%02d:%02d/%02d:%02d:%02d", cur_hour, cur_min, cur_sec, total_hour, total_min, total_sec);
        }

        d_label_set_text(media_full_movie_data->vis_time, show ?    media_full_movie_data->mediaFullMovieTotalTime : NULL);
        media_full_movie_data->mediaCur_X = ((media_full_movie_data->mediaFullMovieProgressValue * (media_full_movie_data->mediaEnd_X - media_full_movie_data->mediaStart_X)) / 100) + media_full_movie_data->vis_play_progress->rect.x;
    }

    return D_OK;
}
static D_Result
media_full_movie_update_set_time(void) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;
    D_Double total_time_value;
    D_U32   cur_set_time;

    total_time_value = media_full_movie_data->mediaFullMovieInfo.totaltime;
    cur_set_time = (media_full_movie_data->mediaCur_X - media_full_movie_data->mediaStart_X) * total_time_value / (media_full_movie_data->mediaEnd_X - media_full_movie_data->mediaStart_X);

    total_hour = (D_U32)total_time_value / 3600;
    total_min   = ((D_U32)total_time_value % 3600) / 60;
    total_sec   = ((D_U32)total_time_value % 3600) % 60;

    cur_hour  = (D_U32)cur_set_time / 3600;
    cur_min  = ((D_U32)cur_set_time % 3600) / 60;
    cur_sec  = ((D_U32)cur_set_time % 3600 ) % 60;


    sprintf(media_full_movie_data->mediaFullMovieTotalTime, "%02d:%02d:%02d/%02d:%02d:%02d", cur_hour, cur_min, cur_sec, total_hour, total_min, total_sec);
    d_label_set_text(media_full_movie_data->vis_time, media_full_movie_data->mediaFullMovieTotalTime );

    return D_OK;
}



static D_Result
media_full_movie_play(D_Bool first)D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;

#if 0
    if(D_OK == d_media_movie_get_info(media_full_movie_data->mediaFullMoviePathName, &media_full_movie_data->mediaFullMovieInfo, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
    media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h))
    {
#if 0 /*ts流的情形下是获取不到高宽信息的*/
        /*不支持播放大于芯片解码能力之外的视频 或者是太小尺寸的视频也不支持*/
        if((media_full_movie_data->mediaFullMovieInfo.width == 0 && media_full_movie_data->mediaFullMovieInfo.height == 0) \
        || media_full_movie_data->mediaFullMovieInfo.width > 1920 || media_full_movie_data->mediaFullMovieInfo.height > 1080 \
        || media_full_movie_data->mediaFullMovieInfo.width <= 256 || media_full_movie_data->mediaFullMovieInfo.height <= 192 )
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
            d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            return D_ERR;
        }
#endif

        if(D_OK == d_media_movie_play(media_full_movie_data->mediaFullMoviePathName, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
                                      media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h, 0, NULL))
        {
            media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
            media_full_movie_update_show_time(D_TRUE, D_FALSE);
            media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_START_STATUS);
            return D_OK;
        }
    }
    else
    {
        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
        d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
        return D_ERR;
    }

    return D_ERR;
#endif

    D_FSAttr *fsattr;
    fsattr = &(media_full_movie_data->mediaFileScan->ids[media_full_movie_data->mediaFullMovieCurrIndex]);

    //last_time = 0;
    //last_status = D_OK;
    movie_audio_select = 0;
    media_full_movie_update_show_time(D_FALSE, D_TRUE);
    if(first == D_FALSE)
    {
        media_full_movie_reset_show_timer();
    }

    if(Judge_Movie_File(fsattr))
    {
        movie_ts_prog_select = 0;
        d_av_set_vid_input (0, D_VID_IUTPUT_USB1);
        d_mediacodec_open();
        /*重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();
        if(D_OK == d_media_movie_get_info(media_full_movie_data->mediaFullMoviePathName, &media_full_movie_data->mediaFullMovieInfo, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
        media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h))
        {
            /*不支持播放大于芯片解码能力之外的视频 或者是太小尺寸的视频也不支持*/
            if((media_full_movie_data->mediaFullMovieInfo.width == 0 && media_full_movie_data->mediaFullMovieInfo.height == 0) \
            || media_full_movie_data->mediaFullMovieInfo.width > D_Media_Movie_Codec_Width_Max || media_full_movie_data->mediaFullMovieInfo.height > D_Media_Movie_Codec_Height_Max \
            || media_full_movie_data->mediaFullMovieInfo.width <= D_Media_Movie_Codec_Width_Limit || media_full_movie_data->mediaFullMovieInfo.height <= D_Media_Movie_Codec_Height_LImit)
            {
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);

                media_full_movie_set_info(D_FALSE, D_TRUE);
                if(first == D_FALSE)
                {
                    media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
                }
                media_full_movie_data->mediaFullMovieInfo.totaltime = 0;

                goto _MOVIE_PLAY_END;
            }
            if(D_OK == d_media_movie_play(media_full_movie_data->mediaFullMoviePathName, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
                                          media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h, 0, NULL))
            {
                media_full_movie_set_info(D_FALSE, D_TRUE);
                if(first == D_FALSE)
                {
                    media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
                }
                media_full_movie_update_show_time(D_TRUE, D_FALSE);
                media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_START_STATUS);
				d_av_set_vid_blank(0, D_FALSE); /*退出黑屏*/
                ret = D_OK;
            }
        }
        else
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE),1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
            media_full_movie_set_info(D_FALSE, D_FALSE);
            if(first == D_FALSE)
            {
                media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
            }
            media_full_movie_data->mediaFullMovieInfo.totaltime = 0;
            goto _MOVIE_PLAY_END;
        }
    }
    else if(Judge_TS_File(fsattr))
    {
        D_Result rest;
        d_mediacodec_close();
        d_av_set_vid_input (0, D_VID_IUTPUT_DTV);
        memset(&media_full_movie_data->mediaFullMovieInfo, 0x00, sizeof(media_full_movie_data->mediaFullMovieInfo));
        rest = d_media_movie_get_info_ex(media_full_movie_data->mediaFullMoviePathName, &media_full_movie_data->mediaFullMovieInfo, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
                                  media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h, movie_ts_prog_select);
        D_DUMP("%s totaltime:%d ,filesize:%d \n", __FUNCTION__, media_full_movie_data->mediaFullMovieInfo.totaltime, media_full_movie_data->mediaFullMovieInfo.filesize);
        if(rest == D_OK)
        {
            rest =d_media_movie_play(media_full_movie_data->mediaFullMoviePathName, media_full_movie_data->mediaFullMovieWin.x, media_full_movie_data->mediaFullMovieWin.y, \
                           media_full_movie_data->mediaFullMovieWin.w, media_full_movie_data->mediaFullMovieWin.h, movie_ts_prog_select, NULL);
        }
        if(rest != D_OK || MOVIE_STATUS_STOP == d_media_movie_get_status())//hegx修改不支持的ts流不让全屏播放
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);

            media_full_movie_set_info(D_TRUE, D_FALSE);
            if(first == D_FALSE)
            {
                media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
            }
            media_full_movie_data->mediaFullMovieInfo.totaltime = 0;
            goto _MOVIE_PLAY_END;
        }
        else
        {
            //memset(&media_full_movie_data->mediaFullMovieInfo, 0x00, sizeof(media_full_movie_data->mediaFullMovieInfo));
            media_full_movie_set_info(D_TRUE, D_TRUE);
            if(first == D_FALSE)
            {
                media_full_movie_menu_show_en(MEDIA_FULL_MOVIE_MENU_SHOW);
            }
            media_full_movie_update_show_time(D_TRUE, D_FALSE);
            media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_START_STATUS);
			d_av_set_vid_blank(0, D_FALSE); /*退出黑屏*/
            ret = D_OK;
        }
    }
    else
    {
        D_DUMP("\n unkown video format . \n");
        media_full_movie_data->mediaFullMovieInfo.totaltime = 0;
    }

_MOVIE_PLAY_END:
    p_atv_media_movie_info_window_update(media_full_movie_data->mediaFullMovieName, &(media_full_movie_data->mediaFullMovieInfo), media_full_movie_data->mediaFullMovieInfoValid);
    media_full_movie_data->mediaFullMovieMenuPlayStartTime = d_sys_get_time();
    return ret;
}


static D_Result
media_full_movie_play_by_mode(D_U8 flag)D_FUNCPOSTFIT
{
    D_ID file_id;
    D_MovieAudioInfo audioinfo;

    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
    d_media_movie_stop();
    d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
    media_full_movie_update_show_time(D_FALSE, D_TRUE);
    file_id = media_full_movie_find_next_or_pre_by_play_mode(media_full_movie_data->mediaFullPlayMode, flag);
    if(media_full_movie_data->mediaFullMovieCurrIndex != file_id)
    {
        movie_ts_prog_select = 0;
    }

    if(file_id >= 0)
    {
        media_full_movie_data->mediaFullMovieCurrIndex = file_id;
        memset(media_full_movie_data->mediaFullMoviePathName, 0x00, MEDIA_FULL_MOVIE_PATH_NAME_LEN);
        strcpy(media_full_movie_data->mediaFullMoviePathName, media_full_movie_data->mediaFullMoviePreName);
        media_full_movie_analyse_file_path();

        if(D_OK != media_full_movie_play(D_FALSE))
        {
            //播放失败，接着找一个，直到所以的都播放失败就退出
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
            d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
            d_media_movie_stop();

            return D_ERR;
        }
    }
    else
    {
        if(media_full_movie_data->mediaFullMovieHideHandler)
        {
            media_full_movie_data->mediaFullMovieHideHandler(media_full_movie_data->mediaFullMovieCurrIndex);
        }

        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    audioinfo.codec_id = 0;
    d_media_movie_get_audio_info(&audioinfo, 1);
    if(atv_get_unknow_audiochar(audioinfo.codec_id) != NULL)
    {
        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, \
        atv_get_unknow_audiochar(audioinfo.codec_id), 2000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
    }

    return D_OK;
}

/*
* @brief 视频进度移动函数
* @param[in] key_value:LEFT 向后 RIGHT: 向前移动
*/
D_Result
media_full_movie_set_play_progress_value(D_U32  key_value, D_Bool repeat) D_FUNCPOSTFIT
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
            if(media_full_movie_data->mediaCur_X  > media_full_movie_data->mediaStart_X + (5 * ppos_add))
            {
                media_full_movie_data->mediaCur_X = media_full_movie_data->mediaCur_X - 5 * ppos_add;
            }
            else
            {
                media_full_movie_data->mediaCur_X = media_full_movie_data->mediaStart_X;
            }
        }
        break;
        case D_KEY_RIGHT:
        case D_KEY_PNL_R:
        {
            if(media_full_movie_data->mediaCur_X + (5 * ppos_add) < media_full_movie_data->mediaEnd_X)
            {
                media_full_movie_data->mediaCur_X = media_full_movie_data->mediaCur_X + 5 * ppos_add;
            }
            else
            {
                media_full_movie_data->mediaCur_X = media_full_movie_data->mediaEnd_X;
            }
        }
        break;
    }

    vis = d_frame_get_control (&atv_media_movie_full_window, ID_MOVIE_SELECT_POS);
    if(vis)
    {
        media_full_movie_update_set_time();
        d_vis_set_pos(vis, media_full_movie_data->mediaCur_X, vis->rect.y, vis->rect.w,  vis->rect.h);
        d_vis_update(vis, NULL);
    }

    return D_OK;
}

static D_Result
media_full_movie_set_progress(void)
{
    D_Double total_time_value;
    D_U32   cur_set_time;

    if(media_full_movie_data->mediaFullMovieInfo.totaltime)
    {
        total_time_value = media_full_movie_data->mediaFullMovieInfo.totaltime;
        cur_set_time = (media_full_movie_data->mediaCur_X - media_full_movie_data->mediaStart_X) * total_time_value / (media_full_movie_data->mediaEnd_X - media_full_movie_data->mediaStart_X);
        D_DUMP("full_movie seek %d\n", cur_set_time);
        d_media_movie_seek(cur_set_time);
        //last_time = 0;
        d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_FALSE);
        media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
        media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_START_STATUS);
        return D_OK;
    }

    return D_ERR;
}

/** @brief 调整进度控件事件处理*/
static D_Result
media_full_movie_set_progress_handle (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
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
                    media_full_movie_reset_show_timer();
                    if(media_full_movie_data->mediaFullMovieInfo.totaltime > 3)
                    {
                        media_full_movie_data->mediaFullHasSet = D_TRUE;
                        media_full_movie_set_play_progress_value((D_U32)(evt->fp.key), evt->fp.repeat);
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(media_full_movie_data->mediaFullHasSet == D_TRUE)
                    {
                        media_full_movie_set_progress();
                        media_full_movie_data->mediaFullHasSet = D_FALSE;
                        media_full_movie_reset_show_timer();
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


/** @brief 事件处理*/
static D_Result
media_full_movie_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status;

    switch(evt->type)
    {
        case D_EVT_FP:
        {
            media_full_movie_reset_show_timer();
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                    p_atv_media_movie_info_window_hide();
                    if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_SHOW)
                    {
                        media_full_movie_data->mediaFullHasSet = D_FALSE;
                        media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_HIDE;
                        media_full_movie_menu_show_en(media_full_movie_data->mediaFullMovieMenuEnable);
                        d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_FALSE);
                        media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
                    }
                    else
                    {
                        /*停止播放*/
                        d_media_movie_stop();

                        if(media_full_movie_data->mediaFullMovieHideHandler)
                        {
                            media_full_movie_data->mediaFullMovieHideHandler(media_full_movie_data->mediaFullMovieCurrIndex);
                        }

                        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    }
                    return D_OK;
#if 1
                case D_KEY_PNL_R:
                case D_KEY_RIGHT:
                case D_KEY_PNL_L:
                case D_KEY_LEFT:

                    if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_HIDE)
                    {
                        media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_SHOW;
                        media_full_movie_menu_show_en(media_full_movie_data->mediaFullMovieMenuEnable);
                        return D_OK;
                    }

                    if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_SHOW)
                    {
                        /* 时间太短，或播放失败时，不可能选时播放@qiny*/
                        if(media_full_movie_data->mediaFullMovieInfo.totaltime > 3)
                        {
                            media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_SELECT_STATUS);
                        }
                    }
                    return D_OK;
#endif
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_HIDE)
                    {
                        media_full_movie_set_info(media_full_movie_data->mediaFullMovieTsFlag, media_full_movie_data->mediaFullMovieInfoValid);
                        media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_SHOW;
                        media_full_movie_menu_show_en(media_full_movie_data->mediaFullMovieMenuEnable);
                        return D_OK;
                    }

                    /* 播放失败时不可以设定暂停与播放 @qiny*/
                    status = d_media_movie_get_status();
                    if(status == MOVIE_STATUS_PLAY || status == MOVIE_STATUS_PAUSE)
                    {
                        if(media_full_movie_data->mediaFullMoviePlayStatus == MEDIA_FULL_MOVIE_PLAYING_STATUS)
                        {
                            media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_PAUSE_STATUS);
                        }
                        else if(media_full_movie_data->mediaFullMoviePlayStatus == MEDIA_FULL_MOVIE_PAUSE_STATUS)
                        {
                            media_full_mvoie_set_play_status(MEDIA_FULL_MOVIE_PLAYING_STATUS);
                        }
                    }
                    return D_OK;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    media_full_movie_play_by_mode(D_FALSE);
                    return D_OK;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    media_full_movie_play_by_mode(D_TRUE);
                    return D_OK;
                case D_KEY_BLUE:
  //                  p_atv_media_movie_info_window_show(media_full_movie_data->mediaFullMovieName, &(media_full_movie_data->mediaFullMovieInfo), media_full_movie_data->mediaFullMovieInfoValid, 960, 32);
  //                  return D_OK;
                default:
                    break;
            }
        }
        break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_full_movie_data->mediaFullMovieMenuTimer)
            {
                if(media_full_movie_data->mediaFullMovieMenuEnable == MEDIA_FULL_MOVIE_MENU_SHOW)
                {
                    D_U32 cur_t;

                    /* 解决因定时器消息阻塞而导致菜单很快消失的问题 @qiny*/
                    cur_t = d_sys_get_time();
                    if((cur_t < media_full_movie_data->mediaFullMovieMenuShowStartTime) || (cur_t - media_full_movie_data->mediaFullMovieMenuShowStartTime > (MEDIA_FULL_MOVIE_MENU_SHOW_TIME - 500)))
                    {
                        media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_HIDE;
                        media_full_movie_menu_show_en(media_full_movie_data->mediaFullMovieMenuEnable);
                        d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_FALSE);
                        media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
                        media_full_movie_data->mediaFullMoviePlayStatus = MEDIA_FULL_MOVIE_PLAYING_STATUS;
                    }
                }

                if(media_full_movie_data->mediaFullHasSet == D_TRUE)
                {
                    media_full_movie_set_progress();
                    media_full_movie_data->mediaFullHasSet = D_FALSE;
                }
            }
            else if(evt->timer.htimer == media_full_movie_data->mediaFullMoviePlayTimer)
            {
                D_ID file_id;

                status = d_media_movie_get_status();

                if(status == MOVIE_STATUS_PLAY)
                {
                    media_full_movie_update_ts_wh();
                    media_full_movie_update_show_time(D_TRUE, D_FALSE);
                }
                else if(status == MOVIE_STATUS_STOP)
                {
                    D_U32 t_now;

                    /* 不支持的提示显示时间稍长些，即两个不支持的文件播放间隔时间长些 @qiny*/
                    t_now = d_sys_get_time();
                    if((t_now < media_full_movie_data->mediaFullMovieMenuPlayStartTime) || (t_now - media_full_movie_data->mediaFullMovieMenuPlayStartTime > (MEDIA_FULL_MOVIE_PLAY_REFRESH_TIME * 2 - 200)))
                    {
                        media_full_movie_play_by_mode(D_TRUE);
                    }

                    break;
                }

                /*视频监控流畅程度*/
#if 0
                if (status == MOVIE_STATUS_PLAY)
                {
                    D_Result ret, play_status;
                    D_U32 duration;
                    static D_S32 err_count, normal_count;

                    if(last_time == 0)
                    {
                        last_time =  get_time();//ms
                        last_status = d_media_movie_get_video_smooth();
                        err_count = 0;
                        normal_count = 0;
                    }

                    duration = get_interval(last_time);//ms
                    if(duration > 3 * 1000)
                    {
                        ret = d_media_movie_get_video_smooth();
                        D_DUMP("%s:%d  ret:%d \n", __FUNCTION__, __LINE__, ret);
                        if (ret != last_status)
                        {
                            last_status = ret;
                            err_count = 0;
                            normal_count = 0;
                        }
                        else if ((ret == last_status) && (ret == D_ERR))
                        {
                            err_count++;
                            D_DUMP("%s:%d  err_count:%d \n", __FUNCTION__, __LINE__, err_count);
                            if (err_count > 4)
                            {
                                err_count = 0;
                                /*播放文件不流畅提示信息*/
                                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                                   d_gui_get_text(atv_IDS_Bitrate_Excess), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                            }
                        }
                        else if ((ret == last_status) && (ret == D_OK))
                        {
                            normal_count++;
                            D_DUMP("%s:%d  normal_count:%d \n", __FUNCTION__, __LINE__, normal_count);
                            if (normal_count > 4)
                            {
                                normal_count = 0;
                                d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                            }
                        }
                        last_time =  get_time();//ms
                    }
                }
#endif
            }
            break;
        case D_EVT_USER2:
            if((evt->user.handle == (D_Handle)(&atv_media_movie_full_window)) && (evt->user.param1 == USER_MSG_PARAM1_MEDIA_PVR_PLAY_END))
            {
                if(strcmp(media_full_movie_data->cb_pic_file_path, media_full_movie_data->mediaFullMoviePathName) == 0)
                {
                    D_U32 pvr_ts_parse_res = (D_U32)evt->user.param2;

                    if(pvr_ts_parse_res == 0)/*解析文件info 失败*/
                    {
                        /*该ts文件解析出错的原因*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE),  1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
                    }
                    else if (pvr_ts_parse_res == 1)/*解码失败 没有找到PAT表等信息 parse_ts_packet 返回出错*/
                    {
                        /*该图片文件解码过程中内存空间不足*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE),  1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
                    }
                }
            }
            break;
        case D_EVT_DESTROY:
			p_gui_reset_vis_count();
			d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
            p_atv_media_movie_info_window_hide();
            d_vis_unsubscribe_evt(vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_MOVIE_FULLSCREEN;
            if(media_full_movie_data)
            {
                if(media_full_movie_data->mediaFullMoviePlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_full_movie_data->mediaFullMoviePlayTimer);
                    media_full_movie_data->mediaFullMoviePlayTimer = D_INVALID_HANDLE;
                }

                if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_full_movie_data->mediaFullMovieMenuTimer);
                    media_full_movie_data->mediaFullMovieMenuTimer = D_INVALID_HANDLE;
                }
                if(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle != D_INVALID_HANDLE)
                {
                    d_cbman_unsubscribe(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle );
                    media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
                }

                PROJECT_FREE(media_full_movie_data);
                media_full_movie_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 播放ts结果 的回调函数*/
static void media_fullmovie_pvr_tsparse_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_Pvr_Cb *cb_ret = (D_Pvr_Cb*)obj_data;
    D_Frame *frm = &atv_media_movie_full_window;

    if(media_full_movie_data && frm == (D_Frame *)cb_data)
    {
        if(strcmp(cb_ret->path, media_full_movie_data->mediaFullMoviePathName) == 0)
        {
            D_UserMsg msg;

            strcpy(media_full_movie_data->cb_pic_file_path, cb_ret->path);
            /* 由于此函数是ts播放相关任务调用，不是gui任务调用，
            因此不允许直接调用gui相关的显示函数，比如隐藏加载图标，
            显示ts播放失败等提示，gui通常不允多线程调用，因此
            因此这里通过消息的方式，在窗口handler里进行处理。 @qiny 20150923*/
            msg.type = D_MSG_USER2;
            msg.handle = (D_Handle)frm;
            msg.param1 = USER_MSG_PARAM1_MEDIA_PVR_PLAY_END;
            msg.param2 = (D_U32)cb_ret->pvr_ts_parse_res;
            msg.param3 = (D_U32)media_full_movie_data->cb_pic_file_path;
            d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
        }
    }
}

/** @brief 窗口初始化*/
D_Result
atv_media_movie_full_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual* vis;
    D_MovieAudioInfo audioinfo;

    //last_time = 0;
    //last_status = D_OK;
    movie_ts_prog_select = 0;
    media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
    media_full_movie_data->mediaFullMoviePlayTimer = D_INVALID_HANDLE;
    media_full_movie_data->mediaFullMovieMenuTimer = D_INVALID_HANDLE;
    media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
    media_full_movie_data->mediaFullMovieMenuEnable = MEDIA_FULL_MOVIE_MENU_SHOW;
    media_full_movie_data->vis_play_progress = d_frame_get_control(frm, ID_FULL_MOVIE_PROGRESS);
    media_full_movie_data->vis_play_pos = d_frame_get_control(frm, ID_MOVIE_SELECT_POS);
    media_full_movie_data->vis_time = d_frame_get_control(frm, ID_FULL_MOVIE_TOTAL_TIME);
    media_full_movie_data->vis_play_group = d_frame_get_control(frm, ID_FULL_MOVIE_CONTROL_GROUP);
    media_full_movie_data->vis_play_status = d_frame_get_control(frm, ID_FULL_MOVIE_STATUS);
    media_full_movie_data->vis_show_status = d_frame_get_control(frm, ID_FULL_MOVIE_STATUS_LABEL);
    media_full_movie_data->mediaFullHasSet = D_FALSE;
    media_full_movie_data->vis_info_group = d_frame_get_control(frm, ID_FULL_MOVIE_INFO_GROUP);
    media_full_movie_data->vis_name = d_frame_get_control(frm, ID_FULL_MOVIE_NAME);
    media_full_movie_data->vis_hw = d_frame_get_control(frm, ID_FULL_MOVIE_HW_1);
    media_full_movie_data->vis_size = d_frame_get_control(frm, ID_FULL_MOVIE_SIZE_1);

    media_full_movie_data->mediaStart_X = media_full_movie_data->vis_play_progress->rect.x;
    media_full_movie_data->mediaEnd_X = media_full_movie_data->vis_play_progress->rect.w + media_full_movie_data->vis_play_progress->rect.x;
    media_full_movie_data->mediaCur_X = media_full_movie_data->mediaStart_X;

    d_vis_set_pos(media_full_movie_data->vis_play_pos, media_full_movie_data->mediaStart_X, media_full_movie_data->vis_play_pos->rect.y, media_full_movie_data->vis_play_pos->rect.w, media_full_movie_data->vis_play_pos->rect.h);
    d_vis_update (media_full_movie_data->vis_play_pos, NULL);

    vis = d_frame_get_control (frm, ID_MOVIE_SELECT_POS);
    if (vis)
    {
        d_vis_set_focusable(media_full_movie_data->vis_play_pos, D_FALSE);
        media_full_movie_data->mediaFullMovieSelectPos = D_FALSE;
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_full_movie_set_progress_handle);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        media_full_movie_data->vis_full_win = vis;
        d_vis_get_pos(media_full_movie_data->vis_full_win, &media_full_movie_data->mediaFullMovieWin.x, &media_full_movie_data->mediaFullMovieWin.y);
        media_full_movie_data->mediaFullMovieWin.x = 0; //media_full_movie_data->vis_full_win->rect.w;
        media_full_movie_data->mediaFullMovieWin.y = 0; //media_full_movie_data->vis_full_win->rect.h;
        media_full_movie_data->mediaFullMovieWin.w = -1; //media_full_movie_data->vis_full_win->rect.w;
        media_full_movie_data->mediaFullMovieWin.h = -1; //media_full_movie_data->vis_full_win->rect.h;
 
        if(media_full_movie_data->mediaFileScan)
        {
            media_full_movie_analyse_file_path();
        }
        media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = d_cbman_subscribe(PL_MEDIA_PVR_PARSE_TS, D_INVALID_HANDLE, media_fullmovie_pvr_tsparse_cb, (D_Ptr)frm);
		d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        if(D_OK != media_full_movie_play(D_TRUE))
        {
            if(media_full_movie_data->mediaFullMoviePlayTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_full_movie_data->mediaFullMoviePlayTimer);
                media_full_movie_data->mediaFullMoviePlayTimer = D_INVALID_HANDLE;
            }

            if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_full_movie_data->mediaFullMovieMenuTimer);
                media_full_movie_data->mediaFullMovieMenuTimer = D_INVALID_HANDLE;
            }

            if(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle != D_INVALID_HANDLE)
            {
                d_cbman_unsubscribe(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle );
                media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
            }

            d_vis_unsubscribe_evt(vis);

            PROJECT_FREE(media_full_movie_data);
            media_full_movie_data = NULL;

            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 1000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);

            return D_ERR;
        }
		p_gui_set_vis_count(51);

        if(media_full_movie_data->mediaFullMoviePlayTimer == D_INVALID_HANDLE)
        {
            media_full_movie_data->mediaFullMoviePlayTimer = d_timer_create(NULL, MEDIA_FULL_MOVIE_PLAY_REFRESH_TIME, d_gui_get_queue());
            if(media_full_movie_data->mediaFullMoviePlayTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_full_movie_data->mediaFullMoviePlayTimer);
            }
        }
        if(media_full_movie_data->mediaFullMovieMenuTimer == D_INVALID_HANDLE)
        {
            media_full_movie_data->mediaFullMovieMenuTimer = d_timer_create(NULL, MEDIA_FULL_MOVIE_MENU_SHOW_TIME, d_gui_get_queue());
            if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_full_movie_data->mediaFullMovieMenuTimer);
            }
        }
        audioinfo.codec_id = 0;
        d_media_movie_get_audio_info(&audioinfo, 1);
        if(atv_get_unknow_audiochar(audioinfo.codec_id) != NULL)
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, \
                               atv_get_unknow_audiochar(audioinfo.codec_id), 2000, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);
        }
        /*设定窗口事件回调*/
        d_vis_subscribe_evt(vis, D_EVT_USER_MASK, (D_Handle)frm);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_full_movie_window_handler);
    }
    media_full_movie_data->mediaFullMovieMenuShowStartTime = d_sys_get_time();
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_MOVIE_FULLSCREEN;
	p_show_osd_window(media_full_movie_data->mediaFullMovieMenuEnable);
    return D_OK;
}



D_Result
p_media_movie_full_screen_show (D_Char* path_name, D_U16 movie_index, D_FileScan* fileScan, D_U8 play_mode, D_Result (*mediaFullMovieHideHandler) (D_U16 param)) D_FUNCPOSTFIT
{

    D_Result ret = D_ERR;

    if((path_name != NULL) && (fileScan != NULL) && (mediaFullMovieHideHandler != NULL))
    {
        media_full_movie_data = (MediaFullMovieData*)PROJECT_ALLOC(sizeof(MediaFullMovieData));
        if(!media_full_movie_data)
        {
            return D_ERR;
        }

        memset(media_full_movie_data, 0x00, sizeof(MediaFullMovieData));
        media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
        media_full_movie_data->mediaFullMovieCurrIndex = movie_index;
        strncpy(media_full_movie_data->mediaFullMoviePreName, path_name, sizeof(media_full_movie_data->mediaFullMoviePreName) - 1);
        strncpy(media_full_movie_data->mediaFullMoviePathName, path_name, sizeof(media_full_movie_data->mediaFullMoviePathName) - 1);
        media_full_movie_data->mediaFullMovieHideHandler = mediaFullMovieHideHandler;
        media_full_movie_data->mediaFileScan = fileScan;
        media_full_movie_data->mediaFullPlayMode = (MEDIA_FULL_MOVIE_PLAY_MODE)play_mode;
        ret = d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_movie_full_window, D_CLEAR_NONE);
        if(ret != D_OK && media_full_movie_data)
        {
            if(media_full_movie_data->mediaFullMoviePlayTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_full_movie_data->mediaFullMoviePlayTimer);
                media_full_movie_data->mediaFullMoviePlayTimer = D_INVALID_HANDLE;
            }

            if(media_full_movie_data->mediaFullMovieMenuTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_full_movie_data->mediaFullMovieMenuTimer);
                media_full_movie_data->mediaFullMovieMenuTimer = D_INVALID_HANDLE;
            }

            if(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle != D_INVALID_HANDLE)
            {
                d_cbman_unsubscribe(media_full_movie_data->mediaFullMovie_pvr_tsparse_handle );
                media_full_movie_data->mediaFullMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
            }
            PROJECT_FREE(media_full_movie_data);
            media_full_movie_data = NULL;
        }
    }

    return ret;
}

D_Result
p_media_movie_full_screen_hide(void) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_media_movie_full_window))
    {
        /*停止播放*/
		d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        d_media_movie_stop();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_OK;
}

D_Result
p_media_movie_full_screen_play_ts_prog(D_S8 id) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_media_movie_full_window) && media_full_movie_data)
    {
        movie_ts_prog_select = id;
		d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        d_media_movie_stop();
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
        media_full_movie_play(D_FALSE);
    }
    return D_OK;
}

