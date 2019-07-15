
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
#include "dCBMan.h"
#include "pPvrPlay.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

#include "atv_media_pvr_full_window.c"

#define MEDIA_FULL_PVR_PATH_NAME_LEN            D_PATH_LENGTH
#define MEDIA_FULL_PVR_PLAY_REFRESH_TIME        (1000)
#define MEDIA_FULL_PVR_MENU_SHOW_TIME           (5000)
#define MEDIA_FULL_PVR_BUFF_SIZE   (64)


#define MEDIA_FULL_PVR_MENU_HIDE   (0)
#define MEDIA_FULL_PVR_MENU_SHOW   (1)

#define MEDIA_FULL_PVR_TIME_RESET  (0)
#define MEDIA_FULL_PVR_TIME_START  (1)
#define MEDIA_FULL_PVR_TIME_UPDATE (2)

#define MEDIA_FULL_PVR_PLAY_STOP   (0x01)
#define MEDIA_FULL_PVR_PLAY_PLAY   (0x02)
#define MEDIA_FULL_PVR_PLAY_PAUSE  (0x04)
#define MEDIA_FULL_PVR_PLAY_LAST   (0x08)
#define MEDIA_FULL_PVR_PLAY_NEXT   (0x10)

typedef struct
{
    D_HTimer mediaFullPvrPlayTimer;
    D_HTimer mediaFullPvrMenuTimer;

    D_Char      mediaFullPvrPathName[MEDIA_FULL_PVR_PATH_NAME_LEN];
    D_U16       mediaFullPvrCurrIndex;
    D_U8        mediaFullPvrCurrStatus;

    D_Result    (*mediaFullPvrHideHandler) (D_U16 param) D_FUNCPOSTFIT;
    D_VidWindow  mediaFullPvrWin;
    D_FileScan*  mediaFullPvrFileScan;

    D_PvrInfo  mediaFullPvrInfo;
    D_Double   mediaFullPvrTotalTimeValue;
    D_Double   mediaFullPvrCurrTimeValue;
    D_U32      mediaFullPvrProgressValue;
    D_Char     mediaFullPvrCurrTime[MEDIA_FULL_PVR_BUFF_SIZE];
    D_Char     mediaFullPvrTotalTime[MEDIA_FULL_PVR_BUFF_SIZE];

    D_U8     mediaFullPvrMenuEnable;
    D_U32    mediaFullPvrPlayStartTime;
    D_U32    mediaFullPvrPlayTime;

    D_Visual* vis_full_win, *vis_play_group;
    D_Visual* vis_play_progress;
    D_Visual* vis_curr_time, *vis_total_time;
    D_Visual* vis_play_or_pause;

} MediaPvrFullData;

static MediaPvrFullData* media_pvr_full_data = NULL;

static D_Result
media_full_pvr_set_curr_status(void) D_FUNCPOSTFIT;


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pause_normal = { -1, atv_IMG_ID_media_play, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pause_focus = { -1, atv_IMG_ID_FS_Media_Pause_Focus, -1, NULL, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_pause = {{&GUID_pause_normal, &GUID_pause_focus, NULL, }, 1, };


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_play_normal = { -1, atv_IMG_ID_media_pause, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_play_focus = { -1, atv_IMG_ID_FS_Media_Stop_Focus, -1, NULL, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_play = {{&GUID_play_normal, &GUID_play_focus, NULL, }, 1, };



static D_Result
media_full_pvr_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(media_pvr_full_data)
    {
        if(media_pvr_full_data->mediaFullPvrMenuTimer == D_INVALID_HANDLE)
        {
            media_pvr_full_data->mediaFullPvrMenuTimer = d_timer_create(NULL, MEDIA_FULL_PVR_MENU_SHOW_TIME, d_gui_get_queue());
            if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(media_pvr_full_data->vis_full_win, D_EVT_TIMER_MASK, media_pvr_full_data->mediaFullPvrMenuTimer);
            }
        }

        if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
        {
            d_timer_reset(media_pvr_full_data->mediaFullPvrMenuTimer, MEDIA_FULL_PVR_MENU_SHOW_TIME);
        }
    }

    return D_OK;
}

static D_Result
media_full_pvr_menu_show_en(D_Bool show)D_FUNCPOSTFIT
{
    media_pvr_full_data->mediaFullPvrMenuEnable = show;
    d_vis_show(media_pvr_full_data->vis_play_group, show);
	p_show_osd_window(show);
    if(show)
    {
        media_full_pvr_reset_show_timer();
    }

    return D_OK;
}

static D_Result
media_full_pvr_update_show_time(D_U8 action) D_FUNCPOSTFIT
{
    D_U32 total_hour, total_min, total_sec;
    D_U32 cur_hour, cur_min, cur_sec;

    media_pvr_full_data->mediaFullPvrTotalTimeValue = media_pvr_full_data->mediaFullPvrInfo.totaltime;

    if(action == MEDIA_FULL_PVR_TIME_UPDATE)
    {
#if 0
        media_pvr_full_data->mediaFullPvrCurrTimeValue = d_media_pvr_get_curtime();
#else
        /* 播放时间*/
        media_pvr_full_data->mediaFullPvrCurrTimeValue = d_sys_get_time();
        if(media_pvr_full_data->mediaFullPvrPlayStartTime > media_pvr_full_data->mediaFullPvrCurrTimeValue)
        {
            //时间溢出
            media_pvr_full_data->mediaFullPvrCurrTimeValue += (0xFFFFFFFF - media_pvr_full_data->mediaFullPvrPlayStartTime);
        }
        else
        {
            media_pvr_full_data->mediaFullPvrCurrTimeValue -= media_pvr_full_data->mediaFullPvrPlayStartTime;
        }
        media_pvr_full_data->mediaFullPvrCurrTimeValue /= 1000;
        media_pvr_full_data->mediaFullPvrCurrTimeValue += media_pvr_full_data->mediaFullPvrPlayTime;
        media_pvr_full_data->mediaFullPvrCurrTimeValue = D_MIN(media_pvr_full_data->mediaFullPvrCurrTimeValue, media_pvr_full_data->mediaFullPvrTotalTimeValue);
#endif
    }
    else if(action == MEDIA_FULL_PVR_TIME_RESET)
    {
        media_pvr_full_data->mediaFullPvrCurrTimeValue = 0;
        media_pvr_full_data->mediaFullPvrTotalTimeValue = 0;
        media_pvr_full_data->mediaFullPvrProgressValue = 0;
    }
    else if(action == MEDIA_FULL_PVR_TIME_START)
    {
        media_pvr_full_data->mediaFullPvrCurrTimeValue = 0;
    }

    if(media_pvr_full_data->mediaFullPvrTotalTimeValue > 0)
    {
        media_pvr_full_data->mediaFullPvrProgressValue = (media_pvr_full_data->mediaFullPvrCurrTimeValue * 100) / media_pvr_full_data->mediaFullPvrTotalTimeValue;
    }

    total_hour = (D_U32)media_pvr_full_data->mediaFullPvrTotalTimeValue / 3600;
    total_min   = ((D_U32)media_pvr_full_data->mediaFullPvrTotalTimeValue % 3600) / 60;
    total_sec   = ((D_U32)media_pvr_full_data->mediaFullPvrTotalTimeValue % 3600) % 60;

    cur_hour  = (D_U32)media_pvr_full_data->mediaFullPvrCurrTimeValue / 3600;
    cur_min  = ((D_U32)media_pvr_full_data->mediaFullPvrCurrTimeValue % 3600) / 60;
    cur_sec  = ((D_U32)media_pvr_full_data->mediaFullPvrCurrTimeValue % 3600 ) % 60;


    //set progress
    d_progress_bar_set_val(media_pvr_full_data->vis_play_progress, media_pvr_full_data->mediaFullPvrProgressValue);

    //set curr time
    sprintf(media_pvr_full_data->mediaFullPvrCurrTime, "%02d:%02d:%02d", cur_hour, cur_min, cur_sec);
    d_label_set_text(media_pvr_full_data->vis_curr_time, media_pvr_full_data->mediaFullPvrCurrTime);

    //set total time
    sprintf(media_pvr_full_data->mediaFullPvrTotalTime, "%02d:%02d:%02d", total_hour, total_min, total_sec);
    d_label_set_text(media_pvr_full_data->vis_total_time, media_pvr_full_data->mediaFullPvrTotalTime);

    return D_OK;
}


static D_Result
media_full_pvr_stop(void) D_FUNCPOSTFIT
{
    d_media_pvr_stop();
    media_pvr_full_data->mediaFullPvrCurrStatus = 0;
    media_pvr_full_data->mediaFullPvrCurrStatus |= MEDIA_FULL_PVR_PLAY_STOP;
    media_full_pvr_menu_show_en(MEDIA_FULL_PVR_MENU_HIDE);
    media_full_pvr_update_show_time(MEDIA_FULL_PVR_TIME_RESET);
}


static D_Result
media_full_pvr_play(void)D_FUNCPOSTFIT
{

    //set show window
    d_av_set_vid_window(0, media_pvr_full_data->mediaFullPvrWin.x, media_pvr_full_data->mediaFullPvrWin.y, media_pvr_full_data->mediaFullPvrWin.w, media_pvr_full_data->mediaFullPvrWin.h);

    d_pvr_rep_get_pvr_info(media_pvr_full_data->mediaFullPvrPathName,  &media_pvr_full_data->mediaFullPvrInfo);
    media_pvr_full_data->mediaFullPvrPlayStartTime = d_sys_get_time();
    media_pvr_full_data->mediaFullPvrPlayTime = 0;
    media_pvr_full_data->mediaFullPvrCurrTimeValue = 0;
    if(D_OK == d_media_pvr_play(media_pvr_full_data->mediaFullPvrPathName))
    {
//              d_av_set_vid_blank(0, D_FALSE); /*黑屏*/
        media_full_pvr_menu_show_en(MEDIA_FULL_PVR_MENU_SHOW);
        media_full_pvr_update_show_time(MEDIA_FULL_PVR_TIME_START);
        media_pvr_full_data->mediaFullPvrCurrStatus = 0;
        media_pvr_full_data->mediaFullPvrCurrStatus |= MEDIA_FULL_PVR_PLAY_PLAY;
        d_vis_set_attribute(media_pvr_full_data->vis_play_or_pause, (D_Ptr)&GUID_play);
    }

    return D_OK;
}

static D_Result
media_full_pvr_find_last_or_next(D_Bool flag) D_FUNCPOSTFIT
{
    if(flag)    //last
    {
        media_pvr_full_data->mediaFullPvrCurrIndex--;
        if(media_pvr_full_data->mediaFullPvrCurrIndex == 0)
        {
            media_pvr_full_data->mediaFullPvrCurrIndex = media_pvr_full_data->mediaFullPvrFileScan->cnt - 1;
        }
    }
    else //next
    {
        media_pvr_full_data->mediaFullPvrCurrIndex++;
        if(media_pvr_full_data->mediaFullPvrCurrIndex == media_pvr_full_data->mediaFullPvrFileScan->cnt)
        {
            media_pvr_full_data->mediaFullPvrCurrIndex = 1;
        }
    }

    strncpy(media_pvr_full_data->mediaFullPvrPathName, media_pvr_full_data->mediaFullPvrFileScan->ids[media_pvr_full_data->mediaFullPvrCurrIndex].path.filename,  \
    sizeof(media_pvr_full_data->mediaFullPvrPathName) - 1);

    return D_OK;

}

static D_Result
media_full_pvr_resume_play(void) D_FUNCPOSTFIT
{
    d_vis_set_attribute(media_pvr_full_data->vis_play_or_pause, (D_Ptr)&GUID_play);
    d_media_pvr_resume();
    return D_OK;
}

static D_Result
media_full_pvr_pause_play(void) D_FUNCPOSTFIT
{
    d_vis_set_attribute(media_pvr_full_data->vis_play_or_pause, (D_Ptr)&GUID_pause);
    d_media_pvr_pause();
    return D_OK;
}

static D_Result
media_full_pvr_last_play(void) D_FUNCPOSTFIT
{
    media_full_pvr_stop();
    media_full_pvr_find_last_or_next(D_TRUE);
    media_full_pvr_play();
    return D_OK;
}


static D_Result
media_full_pvr_next_play(void) D_FUNCPOSTFIT
{
    media_full_pvr_stop();
    media_full_pvr_find_last_or_next(D_FALSE);
    media_full_pvr_play();
    return D_OK;
}

static D_Result
media_full_pvr_set_curr_status(void) D_FUNCPOSTFIT
{
    switch(media_pvr_full_data->mediaFullPvrCurrStatus)
    {
        case MEDIA_FULL_PVR_PLAY_STOP:
            break;
        case MEDIA_FULL_PVR_PLAY_PLAY:
            media_full_pvr_resume_play();
            break;
        case MEDIA_FULL_PVR_PLAY_PAUSE:
            media_full_pvr_pause_play();
            break;
        case MEDIA_FULL_PVR_PLAY_LAST:
            media_full_pvr_last_play();
            break;
        case MEDIA_FULL_PVR_PLAY_NEXT:
            media_full_pvr_next_play();
            break;
        default:
            break;
    }

    return D_OK;
}


static D_Result
media_full_pvr_last_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            media_full_pvr_reset_show_timer();
            if(media_pvr_full_data->mediaFullPvrFileScan->cnt == 2)
            {
                break;
            }
            media_pvr_full_data->mediaFullPvrCurrStatus = 0;
            media_pvr_full_data->mediaFullPvrCurrStatus |= MEDIA_FULL_PVR_PLAY_LAST;
            media_full_pvr_set_curr_status();
            break;
        default:
            break;
    }
    return D_OK;
}
static D_Result
media_full_pvr_play_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            media_full_pvr_reset_show_timer();
            if(media_pvr_full_data->mediaFullPvrCurrStatus & MEDIA_FULL_PVR_PLAY_PAUSE)  //pause
            {
                media_pvr_full_data->mediaFullPvrCurrStatus &= ~MEDIA_FULL_PVR_PLAY_PAUSE;
                media_pvr_full_data->mediaFullPvrCurrStatus |=  MEDIA_FULL_PVR_PLAY_PLAY;
                media_pvr_full_data->mediaFullPvrPlayStartTime = d_sys_get_time();
            }
            else //play
            {
                media_pvr_full_data->mediaFullPvrCurrStatus &= ~MEDIA_FULL_PVR_PLAY_PLAY;
                media_pvr_full_data->mediaFullPvrCurrStatus |=  MEDIA_FULL_PVR_PLAY_PAUSE;
                media_pvr_full_data->mediaFullPvrPlayTime = media_pvr_full_data->mediaFullPvrCurrTimeValue;
            }
            media_full_pvr_set_curr_status();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
media_full_pvr_next_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            media_full_pvr_reset_show_timer();
            if(media_pvr_full_data->mediaFullPvrFileScan->cnt == 2)//其中一个是上一级
            {
                break;
            }
            media_pvr_full_data->mediaFullPvrCurrStatus = 0;
            media_pvr_full_data->mediaFullPvrCurrStatus |= MEDIA_FULL_PVR_PLAY_NEXT;
            media_full_pvr_set_curr_status();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
media_full_pvr_group_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            media_full_pvr_reset_show_timer();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
media_full_pvr_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
        {
            media_full_pvr_reset_show_timer();
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    if(media_pvr_full_data->mediaFullPvrMenuEnable == MEDIA_FULL_PVR_MENU_SHOW)
                    {
                        media_pvr_full_data->mediaFullPvrMenuEnable = MEDIA_FULL_PVR_MENU_HIDE;
                        media_full_pvr_menu_show_en(media_pvr_full_data->mediaFullPvrMenuEnable);
                    }
                    else
                    {
                        media_full_pvr_stop();
                        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    }
                    return D_OK;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(media_pvr_full_data->mediaFullPvrMenuEnable == MEDIA_FULL_PVR_MENU_HIDE)
                    {
                        media_pvr_full_data->mediaFullPvrMenuEnable = MEDIA_FULL_PVR_MENU_SHOW;
                        media_full_pvr_menu_show_en(media_pvr_full_data->mediaFullPvrMenuEnable);
                        return D_OK;
                    }
                    return D_OK;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    return D_OK;
                default:
                    break;
            }
        }
        break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_pvr_full_data->mediaFullPvrMenuTimer)
            {
                if(media_pvr_full_data->mediaFullPvrMenuEnable == MEDIA_FULL_PVR_MENU_SHOW)
                {
                    media_pvr_full_data->mediaFullPvrMenuEnable = MEDIA_FULL_PVR_MENU_HIDE;
                    media_full_pvr_menu_show_en(media_pvr_full_data->mediaFullPvrMenuEnable);
                }

                if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
                {
                    d_vis_unsubscribe_one_evt(media_pvr_full_data->vis_full_win, D_EVT_TIMER_MASK, media_pvr_full_data->mediaFullPvrMenuTimer);
                    d_timer_destroy(media_pvr_full_data->mediaFullPvrMenuTimer);
                    media_pvr_full_data->mediaFullPvrMenuTimer = D_INVALID_HANDLE;
                }
            }
            else if(evt->timer.htimer == media_pvr_full_data->mediaFullPvrPlayTimer)
            {
                D_U8 status;

                status = d_media_pvr_get_status();
                if(status == PVR_STATUS_STOP)
                {
                    media_full_pvr_stop();
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                }
                else if(status == PVR_STATUS_PLAY)
                {
                    media_full_pvr_update_show_time(MEDIA_FULL_PVR_TIME_UPDATE);
                }
            }
            break;
        case D_EVT_DESTROY:
			p_gui_reset_vis_count();
            media_full_pvr_stop();
            d_vis_unsubscribe_evt(vis);

            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_PVR_FULLSCREEN;
            if(media_pvr_full_data)
            {
                if(media_pvr_full_data->mediaFullPvrPlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_full_data->mediaFullPvrPlayTimer);
                    media_pvr_full_data->mediaFullPvrPlayTimer = D_INVALID_HANDLE;
                }

                if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_full_data->mediaFullPvrMenuTimer);
                    media_pvr_full_data->mediaFullPvrMenuTimer = D_INVALID_HANDLE;
                }

                if(media_pvr_full_data->mediaFullPvrHideHandler)
                {
                    media_pvr_full_data->mediaFullPvrHideHandler(media_pvr_full_data->mediaFullPvrCurrIndex);
                }
                PROJECT_FREE(media_pvr_full_data);
                media_pvr_full_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


D_Result
atv_media_pvr_full_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual* vis;

    media_pvr_full_data->mediaFullPvrPlayTimer = D_INVALID_HANDLE;
    media_pvr_full_data->mediaFullPvrMenuTimer = D_INVALID_HANDLE;
    media_pvr_full_data->vis_play_group = d_frame_get_control(frm, ID_MEDIA_PVR_GROUP);
    media_pvr_full_data->vis_curr_time = d_frame_get_control(frm, ID_MEDIA_PVR_CURR_TIME);
    media_pvr_full_data->vis_total_time = d_frame_get_control(frm, ID_MEDIA_PVR_TOTAL_TIME);
    media_pvr_full_data->vis_play_progress = d_frame_get_control(frm, ID_MEDIA_PVR_PROGRESS);
    media_pvr_full_data->vis_play_or_pause = d_frame_get_control(frm, ID_MEDIA_PVR_PLAY);
    media_pvr_full_data->mediaFullPvrCurrStatus = 0;


    vis = d_frame_get_control(frm, ID_MEDIA_PVR_LAST);
    if(vis)
    {
        d_vis_set_handler(vis, media_full_pvr_last_button_handler);
    }

    vis = d_frame_get_control(frm, ID_MEDIA_PVR_PLAY);
    if(vis)
    {
        d_vis_set_focus(vis);
        d_vis_set_handler(vis, media_full_pvr_play_button_handler);
    }

    vis = d_frame_get_control(frm, ID_MEDIA_PVR_NEXT);
    if(vis)
    {
        d_vis_set_handler(vis, media_full_pvr_next_button_handler);
    }

    vis = d_frame_get_control(frm, ID_MEDIA_PVR_CONTROL_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_set_handler(vis, media_full_pvr_group_handler);
    }


    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        media_pvr_full_data->vis_full_win = vis;
        d_vis_get_pos(media_pvr_full_data->vis_full_win, &media_pvr_full_data->mediaFullPvrWin.x, &media_pvr_full_data->mediaFullPvrWin.y);
        media_pvr_full_data->mediaFullPvrWin.w = media_pvr_full_data->vis_full_win->rect.w;
        media_pvr_full_data->mediaFullPvrWin.h = media_pvr_full_data->vis_full_win->rect.h;

        if(D_OK != media_full_pvr_play())
        {
            if(media_pvr_full_data)
            {
                if(media_pvr_full_data->mediaFullPvrPlayTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_full_data->mediaFullPvrPlayTimer);
                    media_pvr_full_data->mediaFullPvrPlayTimer = D_INVALID_HANDLE;
                }

                if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_full_data->mediaFullPvrMenuTimer);
                    media_pvr_full_data->mediaFullPvrMenuTimer = D_INVALID_HANDLE;
                }

                PROJECT_FREE(media_pvr_full_data);
                media_pvr_full_data = NULL;
            }
            d_vis_unsubscribe_evt(vis);
            p_atv_media_prompt_msg(atv_IDS_PLAY_FAILED);
            return D_ERR;
        }

        media_pvr_full_data->mediaFullPvrPlayTimer = d_timer_create(NULL, MEDIA_FULL_PVR_PLAY_REFRESH_TIME, d_gui_get_queue());
        media_pvr_full_data->mediaFullPvrMenuTimer = d_timer_create(NULL, MEDIA_FULL_PVR_MENU_SHOW_TIME, d_gui_get_queue());
        if(media_pvr_full_data->mediaFullPvrPlayTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_pvr_full_data->mediaFullPvrPlayTimer);
        }

        if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_pvr_full_data->mediaFullPvrMenuTimer);
        }

        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_full_pvr_window_handler);
    }
	p_gui_set_vis_count(43);

    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_PVR_FULLSCREEN;

    return D_OK;

}

D_Result
p_media_pvr_full_screen_show(D_Char* path_name, D_FileScan* fs, D_U16  pvr_index, D_Result (*mediaFullPvrHideHandler) (D_U16 param)) D_FUNCPOSTFIT
{
    D_Result ret = D_ERR;

    if((path_name != NULL) && (fs != NULL) && (mediaFullPvrHideHandler != NULL))
    {
        media_pvr_full_data = (MediaPvrFullData*)PROJECT_ALLOC(sizeof(MediaPvrFullData));
        if(!media_pvr_full_data)
        {
            return D_ERR;
        }

        memset(media_pvr_full_data, 0x00, sizeof(MediaPvrFullData));

        /*set param*/
        media_pvr_full_data->mediaFullPvrFileScan = fs;
        media_pvr_full_data->mediaFullPvrCurrIndex = pvr_index;
        strncpy(media_pvr_full_data->mediaFullPvrPathName, path_name, sizeof(media_pvr_full_data->mediaFullPvrPathName) - 1);
        media_pvr_full_data->mediaFullPvrHideHandler = mediaFullPvrHideHandler;


        ret = d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_pvr_full_window, D_CLEAR_NONE);
        if(ret != D_OK && media_pvr_full_data)
        {
            if(media_pvr_full_data->mediaFullPvrPlayTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_pvr_full_data->mediaFullPvrPlayTimer);
                media_pvr_full_data->mediaFullPvrPlayTimer = D_INVALID_HANDLE;
            }

            if(media_pvr_full_data->mediaFullPvrMenuTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_pvr_full_data->mediaFullPvrMenuTimer);
                media_pvr_full_data->mediaFullPvrMenuTimer = D_INVALID_HANDLE;
            }
            PROJECT_FREE(media_pvr_full_data);
            media_pvr_full_data = NULL;
        }
    }

    return ret;

}

D_Result
p_media_pvr_full_screen_hide(void) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_media_pvr_full_window))
    {
        /*停止播放*/
        media_full_pvr_stop();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_OK;
}


