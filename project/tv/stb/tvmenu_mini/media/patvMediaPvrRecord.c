#include <stdio.h>
#include <string.h>
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pMenu.h"
#include "pPlayer.h"
#include "dPvrRecord.h"
#include "pMem.h"
#include "pFile_Scan.h"
#include "dMedia.h"
#include "dCBMan.h"
#include "pPvrPlay.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

#include "atv_media_pvr_record_window.c"

#define MEDIA_RARTITION_MAX  (24)
#define MEDIA_PVR_RECORD_REFRESH_TIME   (1000)
#define MEDIA_PVR_RECORD_INPUT_TIME     (1000 * 30)


#define MEDIA_PVR_RECORD_BUFF   (64)
#define HaierPVRFolder "AVDATA"
#define MEDIA_PVR_RECORD_MAX_TIME  (7200)
#define MEDIA_PVR_RECORD_MIN_SPACE (10 * 1024 * 1024)

static D_U8   mediaPvrVolIndex[MEDIA_RARTITION_MAX];
static D_Int  mediaPvrTotalPartition = 0;
static D_FsVolumeInfo mediaPvrVolumeInfo = {0};
static D_Char mediaPvrStrVolume[16] = {0};

/*录像句柄*/
static D_HTask mediaPvrRecordHandle = D_INVALID_HANDLE;
static D_Time  mediaPVRRecordStartTime = 0;
static D_Time  mediaPVRRecordTotalTime = 3600;

typedef struct
{
    D_HTimer  mediaPvrRecordShowTimer;
    D_HTimer  mediaPvrRecordInputTimer;

    D_Bool    mediaPvrRecordShowImgFlag;
    D_Bool    mediaPvrRecordShowPromptFlag;
    D_Bool    mediaPvrRecordShowInputFlag;
    D_Bool    mediaPvrRecordShowGroupFlag;

    D_U32     mediaPvrRecordTotalTime;

    D_U32     mediaPvrRecordCurrTime;
    D_Char    mediaPvrRecordStrTime[MEDIA_PVR_RECORD_BUFF];

    D_U8      mediaPvrRecordStart;

    D_Visual *vis_img, *vis_time;
    D_Visual *vis_prompt, *vis_input, *vis_input_group;
} MediaPvrRecordData;

static MediaPvrRecordData* media_pvr_record_data = NULL;
static D_Result
atv_media_pvr_record_stop(void) D_FUNCPOSTFIT;

static D_Result
atv_pvr_check_disk_valid(void) D_FUNCPOSTFIT
{
    D_ID textid = -1;
    D_U8 id;

    memset(mediaPvrVolIndex, 0x00, sizeof(mediaPvrVolIndex));
    memset(mediaPvrStrVolume, 0x00, sizeof(mediaPvrStrVolume));

    if(D_OK == d_fsm_get_volumes(mediaPvrStrVolume, &mediaPvrTotalPartition))
    {
        if(mediaPvrTotalPartition == 0)
        {
            textid = atv_IDS_NO_FIND_DISK;
        }
        else
        {
            for(id = 0; id < mediaPvrTotalPartition; id++)
            {
                sprintf(mediaPvrStrVolume, "%c:", 'C' + mediaPvrStrVolume[id]);

                if(D_OK == d_fsm_volume_get_info(mediaPvrStrVolume, &mediaPvrVolumeInfo))
                {
                    if(mediaPvrVolumeInfo.formatno == FAT_12 || mediaPvrVolumeInfo.free_size <= 100000000)
                    {
                        textid = atv_IDS_NO_SPACE;
                    }
                    else
                    {
                        D_DUMP("ready ok!\n");
                        return D_OK;
                    }
                }
            }
        }
    }

    if(textid != -1)
    {
        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                           D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                           d_gui_get_text(atv_IDS_PROMPT_INFO), d_gui_get_text(textid), 1500,
                           D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);

        return D_ERR;
    }

    return D_ERR;

}


/**@brief 启动pvr录像任务*/
static D_Result
atv_media_pvr_record_service_start(D_DBSrvInfo *info) D_FUNCPOSTFIT
{
    str_pvr_rec_config_info *pvrconfig;
    D_Time  now;
    D_Date today;
    D_Char srv_name[64] = {0};
    PVR_REC_NAV_TYPE type;
    D_U32 flag, i;
	
    pvrconfig = PROJECT_ALLOC(sizeof(str_pvr_rec_config_info));
    if(!pvrconfig)
    {
        return D_ERR;
    }

    memset(pvrconfig, 0x00, sizeof(str_pvr_rec_config_info) );

    /*当前时间*/
    now = d_time_get_local_time();
    d_date (now, &today);

    pvrconfig->is_scrambled = info->ca_flag;
    d_cc_sys_to_utf8(srv_name, 64, info->name, strlen(info->name));
    strncpy(pvrconfig->pro_name, srv_name, sizeof(pvrconfig->pro_name) - 1);
    strncpy(pvrconfig->dir_name, HaierPVRFolder, sizeof(pvrconfig->dir_name) - 1);
    sprintf(pvrconfig->dir_path, "%s", mediaPvrStrVolume);

    // start time
    pvrconfig->start_time.year = ( today.year + 1900);
    pvrconfig->start_time.month = ( today.mon + 1);
    pvrconfig->start_time.day = today.mday;
    pvrconfig->start_time.hour = today.hour;
    pvrconfig->start_time.minute = today.min;
    pvrconfig->start_time.second = today.sec;
    // end time
    pvrconfig->end_time.year = 2014;
    pvrconfig->end_time.month = 12;
    pvrconfig->end_time.day = 12;
    pvrconfig->end_time.hour = 17;
    pvrconfig->end_time.minute = 1;
    pvrconfig->end_time.second = 10;
    // drt_time
    pvrconfig->drt_time = 0;

    //音视频的内容
    pvrconfig->video_stream_type = info->vid_codec;
    pvrconfig->audio_stream_type = D_DB_GET_SRV_AUD_CODEC(info);

    //初始化
    for(i = 0; i < 24; i++)
    {
        pvrconfig->pvr_rec_pid[i] = 0x000fL;//PID_RESERVED;
        //pvrconfig->pid_arr[i] = 0x00;/*初始化*/
        pvrconfig->pid_arr[i].pid_str.pid_valid = 0;
    }

    pvrconfig->pvr_rec_pid[0] = info->vid_pid;
    pvrconfig->pvr_rec_pid[4] = D_DB_GET_SRV_AUD(info);

    pvrconfig->pid_arr[0].pid_str.pid_valid = 1;
    pvrconfig->pid_arr[0].pid_str.pid_type = PVR_VEDIO_PID;
    pvrconfig->pid_arr[0].pid_str.pid_value = info->vid_pid;

    pvrconfig->pid_arr[4].pid_str.pid_valid = 1;
    pvrconfig->pid_arr[4].pid_str.pid_type = PVR_AUDIO_PID;
    pvrconfig->pid_arr[4].pid_str.pid_value = D_DB_GET_SRV_AUD(info);

    //测试其他数据   可以扩充、  支持加密加扰节目、
    //支持多种数据录取、甚至支持多视频录取我们可以四路产生导航
    //目前只做一路
    //pvrconfig->pvr_rec_pid[5] = 0x00;
    //pvrconfig->pvr_rec_pid[6] = 0x10;
    //pvrconfig->pvr_rec_pid[7] = 0x11;

    //Pvr_Rec_Para->pvr_rec_pid[1] = 0x3fc;
    //Pvr_Rec_Para->pvr_rec_pid[2] = 0x406;

    switch(pvrconfig->video_stream_type)
    {
        case D_VID_CODEC_MPEG:
            type = REC_MPEG_NAV_TYPE;
            break;
        case D_VID_CODEC_AVS:
            type = REC_AVS_NAV_TYPE;
            break;
        case D_VID_CODEC_H264:
            type = REC_H264_NAV_TYPE;
            break;
        default:
            type = REC_USER_DEFINE_NAV_TYPE;
            break;
    }

    for(i = 0; i < 4; i++)
    {
        pvrconfig->pvr_rec_nav_type[i] = type;
    }

    //初始化控制字
    for(i = 0; i < 8; i++)
    {
        pvrconfig->pvr_rec_cw[i]    = 0;
    }

    pvrconfig->rec_tv_num = TV1;
    pvrconfig->pvr_rec_support_max_duration_sec = MEDIA_PVR_RECORD_MAX_TIME;
    pvrconfig->pvr_rec_support_min_disk_space = MEDIA_PVR_RECORD_MIN_SPACE;

    D_DUMP("[PVR REC Menu]VolumeInfo.formatno = %u.\n", mediaPvrVolumeInfo.formatno);
    D_DUMP("[PVR REC Menu]VolumeInfo.free_size = %u.\n", mediaPvrVolumeInfo.free_size);
    D_DUMP("[PVR REC Menu]VolumeInfo.total_size = %u.\n", mediaPvrVolumeInfo.total_size);

    if( mediaPvrVolumeInfo.formatno == FAT_32 )
    {
        pvrconfig->pvr_rec_support_max_file_size = DEF_S64(4241280204);
        D_DUMP("[PVR REC Menu]FAT32!\n");
    }
    else if( mediaPvrVolumeInfo.formatno == FAT_16 )
    {
        pvrconfig->pvr_rec_support_max_file_size = DEF_S64(2093796556);
        D_DUMP("[PVR REC Menu]FAT16!\n");
    }
    else if( mediaPvrVolumeInfo.formatno == NTFS )
    {
        //仅仅赋一个初值   它没有文件大小限制
        pvrconfig->pvr_rec_support_max_file_size = DEF_S64(4241280204);
        D_DUMP("[PVR REC Menu]NTFS!\n");
    }

    mediaPvrRecordHandle = d_pvr_rec_create(d_gui_get_queue(), *pvrconfig);
    PROJECT_FREE(pvrconfig);

    if( mediaPvrRecordHandle == D_INVALID_HANDLE )
    {
        return D_ERR;
    }

    mediaPVRRecordStartTime = d_sys_get_time();
    flag = p_stb_player_get_flags(0);
    p_stb_player_set_flags(0, flag | D_PLAYER_FLAGS_PVR);

    return D_OK;
}

static D_Result
atv_media_pvr_record_show_input_group(void) D_FUNCPOSTFIT
{
    media_pvr_record_data->mediaPvrRecordShowGroupFlag = !(media_pvr_record_data->mediaPvrRecordShowGroupFlag );
    d_vis_show(media_pvr_record_data->vis_input_group, media_pvr_record_data->mediaPvrRecordShowGroupFlag);
    return D_OK;
}

static D_Result
atv_media_pvr_record_show_input_info(void) D_FUNCPOSTFIT
{
    media_pvr_record_data->mediaPvrRecordShowInputFlag = !(media_pvr_record_data->mediaPvrRecordShowInputFlag );
    d_vis_show(media_pvr_record_data->vis_input, media_pvr_record_data->mediaPvrRecordShowInputFlag);
    return D_OK;
}

static D_Result
atv_media_pvr_record_show_prompt_info(void) D_FUNCPOSTFIT
{
    media_pvr_record_data->mediaPvrRecordShowPromptFlag = !(media_pvr_record_data->mediaPvrRecordShowPromptFlag );
    d_vis_show(media_pvr_record_data->vis_prompt, media_pvr_record_data->mediaPvrRecordShowPromptFlag);
    return D_OK;
}

static D_Result
atv_media_pvr_record_change_img(void)D_FUNCPOSTFIT
{
    media_pvr_record_data->mediaPvrRecordShowImgFlag = !(media_pvr_record_data->mediaPvrRecordShowImgFlag );
    d_vis_show(media_pvr_record_data->vis_img, media_pvr_record_data->mediaPvrRecordShowImgFlag);
    return D_OK;
}

static D_Result
atv_media_pvr_record_update_time(void)D_FUNCPOSTFIT
{
    D_U32 curr_time, hour, min, sec;
    D_Time now;

    now = d_sys_get_time();
    media_pvr_record_data->mediaPvrRecordCurrTime = (now - mediaPVRRecordStartTime);
    curr_time = media_pvr_record_data->mediaPvrRecordCurrTime / 1000;

    hour = curr_time / 3600;
    min = (curr_time % 3600) / 60;
    sec = curr_time % 60;

    sprintf(media_pvr_record_data->mediaPvrRecordStrTime, "%02d:%02d:%02d", hour, min, sec);
    d_label_set_text(media_pvr_record_data->vis_time, media_pvr_record_data->mediaPvrRecordStrTime);

    return D_OK;
}


/** @brief 输入时间的handler*/
static D_Result
atv_media_pvr_record_time_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U32  Input_buff[4] = {0};
    D_Char  d_record_time[20] = {0};

    switch(evt->type)
    {
        case D_EVT_DATA_CHANGED:
            d_input_box_get_segment_val(vis, Input_buff, 3);
            Input_buff[0] = D_MIN(Input_buff[0], 2);
            Input_buff[1] = D_MIN(Input_buff[1], 59);
            Input_buff[2] = D_MIN(Input_buff[2], 59);
            if(Input_buff[0] == 2)
            {
                Input_buff[1] = 0;
                Input_buff[2] = 0;
            }
            sprintf(d_record_time, "%02d:%02d:%02d", Input_buff[0], Input_buff[1], Input_buff[2]);
            d_input_box_set_text(vis, d_record_time, 8);
            media_pvr_record_data->mediaPvrRecordTotalTime = Input_buff[0] * 3600 + Input_buff[1] * 60 + Input_buff[2];
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}

/**@brief 事件处理*/
static D_Result
atv_media_pvr_record_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_ESC:
                    return atv_media_pvr_record_stop();
                case D_KEY_RED:
                    media_pvr_record_data->mediaPvrRecordShowGroupFlag = 0;
                    media_pvr_record_data->mediaPvrRecordShowPromptFlag = 1;
                    media_pvr_record_data->mediaPvrRecordShowInputFlag = 0;
                    if(media_pvr_record_data->mediaPvrRecordInputTimer != D_INVALID_HANDLE)
                    {
                        d_vis_unsubscribe_one_evt (vis, D_EVT_TIMER_MASK, media_pvr_record_data->mediaPvrRecordInputTimer);
                        d_timer_destroy(media_pvr_record_data->mediaPvrRecordInputTimer);
                        media_pvr_record_data->mediaPvrRecordInputTimer = D_INVALID_HANDLE;
                    }
                    atv_media_pvr_record_show_input_group();
                    atv_media_pvr_record_show_prompt_info();
                    atv_media_pvr_record_show_input_info();
                    media_pvr_record_data->mediaPvrRecordStart = 1;
                    return D_OK;
                case D_KEY_OK:
                    if(media_pvr_record_data->mediaPvrRecordShowInputFlag == 0)
                    {
                        return D_OK;
                    }

                    if((media_pvr_record_data->mediaPvrRecordCurrTime / 1000) > media_pvr_record_data->mediaPvrRecordTotalTime)
                    {
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                                           D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                                           NULL, d_gui_get_text(atv_IDS_INPUT_TIME_ERROR), 1000,
                                           D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
                        return D_OK;
                    }

                    if(media_pvr_record_data->mediaPvrRecordStart)
                    {
                        mediaPVRRecordTotalTime = media_pvr_record_data->mediaPvrRecordTotalTime;
                        if(mediaPVRRecordTotalTime == 0)
                        {
                            mediaPVRRecordTotalTime = 7200;
                        }
                    }
                    else
                    {
                        mediaPVRRecordTotalTime = 7200;
                    }
                    d_pvr_rec_set_total_time(mediaPvrRecordHandle, mediaPVRRecordTotalTime);
                    media_pvr_record_data->mediaPvrRecordShowGroupFlag = 1;
                    media_pvr_record_data->mediaPvrRecordShowInputFlag = 1;
                    atv_media_pvr_record_show_input_group();
                    atv_media_pvr_record_show_input_info();
                    if(media_pvr_record_data->mediaPvrRecordInputTimer == D_INVALID_HANDLE)
                    {
                        media_pvr_record_data->mediaPvrRecordInputTimer  = d_timer_create (NULL, MEDIA_PVR_RECORD_INPUT_TIME, d_gui_get_queue());

                        if(media_pvr_record_data->mediaPvrRecordInputTimer != D_INVALID_HANDLE)
                        {
                            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, media_pvr_record_data->mediaPvrRecordInputTimer);
                        }
                    }
                    return D_OK;
                case D_KEY_RIGHT:
                case D_KEY_LEFT:
                case D_KEY_PNL_R:
                case D_KEY_PNL_L:
                case D_KEY_VOLUME_MINUS:
                case D_KEY_VOLUME_PLUS:
                case D_KEY_MUTE:
                case D_KEY_SCREEN:
                    break;
                case D_KEY_PROGRAM_MINUS:
                case D_KEY_PROGRAM_PLUS:
                case D_KEY_UP:
                case D_KEY_DOWN:
				case D_KEY_PNL_U:
				case D_KEY_PNL_D:
                    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                                       D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                                       NULL, d_gui_get_text(atv_IDS_RECORD_NOT_CHANGE_CHANNEL), 1500,
                                       D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
                    return D_OK;
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                                       D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                                       NULL, d_gui_get_text(atv_IDS_ACTION_INVALID), 1500,
                                       D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
                    return D_OK;
                default:
                    return D_OK;
                    break;
            }
        }
        break;
        case D_EVT_HOTPLUG_MSG:
        {
            /**清理资源*/
            atv_media_pvr_record_service_stop();
            p_atv_meida_pvr_record_menu_hide();

            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                               D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                               NULL, d_gui_get_text(atv_IDS_DEVICE_REMOVED), 1500,
                               D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
        }
        break;
        case D_EVT_FEND_UNLOCKED:
        {
            /**清理资源*/
            atv_media_pvr_record_service_stop();
            p_atv_meida_pvr_record_menu_hide();

            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                               D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                               d_gui_get_text(atv_IDS_PROMPT_INFO), d_gui_get_text(atv_IDS_BAD_SIGNAL_SAVING), 1500,
                               D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
        }
        break;
        case D_EVT_USER:
            if(evt->user.handle == mediaPvrRecordHandle)
            {
                D_Char* text_msg;
                switch(evt->user.param1)
                {
                    case USER_MSG_PARAM1_PVR_REC_TIME_FULL:
                        text_msg = d_gui_get_text(atv_IDS_RECORD_TIME_OUT);
                        break;
                    case USER_MSG_PARAM1_PVR_REC_DISK_FULL:
                        text_msg = d_gui_get_text(atv_IDS_NO_SPACE);
                        break;
                    case USER_MSG_PARAM1_PVR_REC_FILE_FULL:
                        text_msg = d_gui_get_text(atv_IDS_REICORD_FILE_LARGE);
                        break;
					case USER_MSG_PARAM1_PVR_REC_DATA_OVERFLOW:
						text_msg = d_gui_get_text(atv_IDS_DEVICE_BITRATE_BAD);
						break;																		
                    default:
                        break;
                }

                /**清理资源*/
                atv_media_pvr_record_service_stop();
                p_atv_meida_pvr_record_menu_hide();

                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                                   D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
                                   d_gui_get_text(atv_IDS_PROMPT_INFO), text_msg, 1500,
                                   D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
            }
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_pvr_record_data->mediaPvrRecordShowTimer)
            {
                atv_media_pvr_record_change_img();
                atv_media_pvr_record_update_time();
            }
            else if(evt->timer.htimer == media_pvr_record_data->mediaPvrRecordInputTimer)
            {
                atv_media_pvr_record_show_input_group();
                atv_media_pvr_record_show_prompt_info();
            }
            break;
        case D_EVT_DESTROY:
            atv_media_pvr_record_service_stop();
            d_vis_unsubscribe_evt(vis);
            if(media_pvr_record_data)
            {
                if(media_pvr_record_data->mediaPvrRecordInputTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_record_data->mediaPvrRecordInputTimer);
                    media_pvr_record_data->mediaPvrRecordInputTimer = D_INVALID_HANDLE;
                }

                if(media_pvr_record_data->mediaPvrRecordShowTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_pvr_record_data->mediaPvrRecordShowTimer);
                    media_pvr_record_data->mediaPvrRecordShowTimer = D_INVALID_HANDLE;
                }

                PROJECT_FREE( media_pvr_record_data );
                media_pvr_record_data = NULL;
            }
            break;
        default:
            break;

    }

    return D_ERR;
}


D_Result
atv_media_pvr_record_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual* vis;
    D_Char  d_record_time[20] = {0};

    /*将总时间设置*/
    //d_pvr_rec_set_total_time(mediaPvrRecordHandle, mediaPVRRecordTotalTime);

    media_pvr_record_data = (MediaPvrRecordData*)PROJECT_ALLOC(sizeof(MediaPvrRecordData));
    if(!media_pvr_record_data)
    {
        return D_ERR;
    }

    memset(media_pvr_record_data, 0x00, sizeof(MediaPvrRecordData));
    media_pvr_record_data->mediaPvrRecordTotalTime = MEDIA_PVR_RECORD_MAX_TIME;

    sprintf(d_record_time, "%s", "02:00:00");
    media_pvr_record_data->mediaPvrRecordShowImgFlag = D_FALSE;
    media_pvr_record_data->mediaPvrRecordShowPromptFlag = D_FALSE;
    media_pvr_record_data->mediaPvrRecordShowInputFlag = D_TRUE;
    media_pvr_record_data->mediaPvrRecordShowGroupFlag = D_FALSE;

    media_pvr_record_data->vis_img = d_frame_get_control(frm, ID_MEDIA_IMAGE);
    media_pvr_record_data->vis_time = d_frame_get_control(frm, ID_MEDIA_TIME_LABEL);
    media_pvr_record_data->vis_prompt = d_frame_get_control(frm, ID_MEDIA_LABEL_PROMPT);
    media_pvr_record_data->vis_input = d_frame_get_control(frm, ID_MEDIA_INPUT);
    media_pvr_record_data->vis_input_group = d_frame_get_control(frm, ID_MEDIA_GROUP_INPUT);

    media_pvr_record_data->mediaPvrRecordInputTimer = d_timer_create (NULL, MEDIA_PVR_RECORD_INPUT_TIME, d_gui_get_queue());
    media_pvr_record_data->mediaPvrRecordShowTimer  = d_timer_create (NULL, MEDIA_PVR_RECORD_REFRESH_TIME, d_gui_get_queue());

    vis = d_frame_get_control(frm, ID_MEDIA_INPUT);
    if(vis)
    {
        d_input_box_set_text(vis, d_record_time, 8);
        d_vis_set_handler(vis, atv_media_pvr_record_time_handler);

    }

    vis = d_frame_get_control(frm , 0);
    if(vis)
    {
        if(media_pvr_record_data->mediaPvrRecordInputTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, media_pvr_record_data->mediaPvrRecordInputTimer);
        }

        if(media_pvr_record_data->mediaPvrRecordShowTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, media_pvr_record_data->mediaPvrRecordShowTimer);
        }

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK | D_EVT_AUDIO_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_media_pvr_record_window_handler);

        d_vis_subscribe_evt(vis, D_EVT_FEND_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt(vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
    }

    atv_media_pvr_record_show_input_group();
    atv_media_pvr_record_show_input_info();
    atv_media_pvr_record_show_prompt_info();
    media_pvr_record_data->mediaPvrRecordStart = 0;

    return D_OK;
}

D_Result
p_atv_pvr_record_menu_show (void) D_FUNCPOSTFIT
{

    D_ID curr_srv;
    D_DBSrvInfo srvinfo;

    /*菜单是否显示*/
    if(d_frame_is_loaded(&atv_media_pvr_record_window))
    {
        return D_ERR;
    }

    /**信号是否中断检测*/
    if(atv_player_get_curr_singnal())
    {
        return D_ERR;
    }

    /*业务有效性检查*/
    curr_srv = p_stb_player_get_curr_srv(0);
    if(D_OK != d_dbase_get_srv_info(curr_srv, &srvinfo))
    {
        return D_ERR;
    }

    /*非电视不允许录制*/
    if(srvinfo.srv_type != D_DB_SRV_TV)
    {
        return D_ERR;
    }

    /*检查usb/sd的有效性*/
    if(D_OK !=  atv_pvr_check_disk_valid())
    {
        return D_ERR;
    }

    /*启动pvr录像任务*/
    if(D_OK != atv_media_pvr_record_service_start(&srvinfo))
    {
        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
        D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
        d_gui_get_text(atv_IDS_PROMPT_INFO), d_gui_get_text(atv_IDS_RECORD_FAILED), 1500,
        D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);

        return D_ERR;
    }

    d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_4);

    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
    D_GUI_LAYER_MESSAGE, D_POP_MSG_ERROR,
    d_gui_get_text(atv_IDS_PROMPT_INFO), d_gui_get_text(atv_IDS_ENTER_RECORD), 1500,
    D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);

    d_gui_update();

    return d_gui_open_frame(&atv_media_pvr_record_window, D_GUI_LAYER_USER);

}

/**@brief 停止录制节目的任务*/
D_Result
atv_media_pvr_record_service_stop(void) D_FUNCPOSTFIT
{
    D_U32 flag;
    D_Time total_time;

    if(D_INVALID_HANDLE != mediaPvrRecordHandle)
    {
        total_time = (d_sys_get_time() - mediaPVRRecordStartTime) / 1000;
        d_pvr_rec_set_total_time(mediaPvrRecordHandle, total_time);
        d_pvr_rec_stop( mediaPvrRecordHandle );
        d_pvr_rec_destroy( mediaPvrRecordHandle );
        mediaPvrRecordHandle = D_INVALID_HANDLE;
    }

    flag = p_stb_player_get_flags(0);
    p_stb_player_set_flags(0, (flag & (~D_PLAYER_FLAGS_PVR)));
    return D_OK;

}

/**@brief 选择框回调*/
static D_Result
atv_media_pvr_record_stop_handler(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    if(sel)
    {
		p_atv_media_pvr_record_stop();
    }

    return D_OK;
}

/**@brief 退出节目录制*/
static D_Result
atv_media_pvr_record_stop(void) D_FUNCPOSTFIT
{
    if(mediaPvrRecordHandle == D_INVALID_HANDLE)
    {
        return D_OK;
    }

    d_atv_pop_select_center_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE,
    NULL, d_gui_get_text(atv_IDS_STOP_RECORD), 0, D_FALSE,
    atv_media_pvr_record_stop_handler, 0);

    return D_OK;
}

/** @brief 关闭pvr录像菜单*/
D_Result
p_atv_meida_pvr_record_menu_hide(void)D_FUNCPOSTFIT
{
    return d_gui_close_frame(&atv_media_pvr_record_window);
}


D_Result
p_atv_media_pvr_record_stop(void)
{
	if(d_frame_is_loaded(&atv_media_pvr_record_window))
	{
		atv_media_pvr_record_service_stop();
		p_atv_meida_pvr_record_menu_hide();
	}

	return D_OK;
}

