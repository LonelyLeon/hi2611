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
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pConfig.h"

#include "atv_media_music_window.c"

/** @brief 多媒体用到的宏定义*/

#define MEDIA_MUSIC_LIST_ROW_CNT  (9)
#define MEDIA_MUSIC_FOLDER_PATH_LEN  D_PATH_LENGTH
#define MEDIA_MUSIC_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_MUSIC_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_MUSIC_MAX_NUM_CNT      (1000)
#define MEDIA_MUSIC_PARTITION_MAX_CNT (24)
#define MEDIA_MUSIC_FOLDER_LEVEL_MAX  (64)
#define MEDIA_MUSIC_REFRESH_TIME   (1000)
#define MEDIA_MUSIC_FILE_BUFF_SIZE (128)
#define MEDIA_MUSIC_LRC_LEN_BUFF   (512)

/*音乐更新时间的三种状态**/
#define MEDIA_MUSIC_TIME_UPDATE  (0)
#define MEDIA_MUSIC_TIME_START   (1)
#define MEDIA_MUSIC_TIME_RESET   (2)

#define MEDIA_MUSIC_START_STATUS   (0)
#define MEDIA_MUSIC_PAUSE_STATUS   (1)
#define MEDIA_MUSIC_STOP_STATUS    (2)
#define MEDIA_MUSIC_PLAYING_STATUS (3)


typedef enum
{
    MEDIA_MUSIC_LIST_LOOP = 0,      /*列表循环(播放到列表最后一个会接着播放第一首)*/
    MEDIA_MUSIC_SINGLE_LOOP,        /*单曲循环*/
    MEDIA_MUSIC_RANDOM_PLAY,        /*随机播放*/
    MEDIA_MUSIC_LIST_PLAY,          /*列表播放(播放到列表最后一个会停止播放)*/

} MEDIA_MUSIC_PLAY_MODE;


static int play_mode_text[4] = {atv_IDS_LIST_LOOP, atv_IDS_SINGNAL_LOOP, atv_IDS_RANDOM_LOOP, atv_IDS_LIST_PLAY};
static D_ID play_mode_img[4] = {atv_IMG_ID_music_list_loop, atv_IMG_ID_music_one_loop, atv_IMG_ID_music_random, atv_IMG_ID_music_list_play};

/**@brief 多媒体用到的结构体*/
typedef struct
{
    D_Char  mediaMusicCurrFolder_utf8[MEDIA_MUSIC_FOLDER_PATH_LEN];
    D_Char  mediaMusicLastFolder_utf8[MEDIA_MUSIC_FOLDER_PATH_LEN];
    D_Char  mediaMusicCurrPathName_utf8[MEDIA_MUSIC_PATH_NAME_LEN];
    D_Char  mediaMusicCurrPathName[MEDIA_MUSIC_PATH_NAME_LEN];
    D_Char  mediaMusicListShowData[MEDIA_MUSIC_LIST_ROW_CNT][MEDIA_MUSIC_FILE_NAME_LEN];

    /**磁盘信息*/
    D_Int   mediaMusicTotalPartition;                           /*总的磁盘数**/
    D_U8    mediaMusicVolIndex[MEDIA_MUSIC_PARTITION_MAX_CNT];  /*总共的盘符数**/
    D_U8    mediaMusicCurrPartition;                        /*当前的盘符**/

    D_U16   mediaMusicFocuStack[MEDIA_MUSIC_FOLDER_LEVEL_MAX];/*焦点栈，记录各级文件夹焦点*/
    D_U32   mediaMusicFocuLevel;  /*文件级数*/
    D_U16   mediaMusicCurrListFocus;        /*当前行的聚焦号**/

    /*文件记录就指针**/
    D_FileScan mediaMusicFileRset;

    D_U16   mediaMusicCurrPlaying;
    D_U16   mediaMusicLastPlaying;
    D_Bool  mediaMusicPlayed;
    D_Bool  mediaMusicCurrPage;
    MEDIA_MUSIC_PLAY_MODE    mediaMusicPlayMode;


    D_MusicInfo mediaMusicFileInfo;         /*音乐信息的结构体**/
    D_Char  mediaMusicPlayTime[MEDIA_MUSIC_FILE_BUFF_SIZE];
    D_Char  mediaMusicFileName[MEDIA_MUSIC_FILE_NAME_LEN];          /*音乐文件的名字**/
    D_U32   mediaMusicTotalTime;
    D_U32   mediaMusicCurrTime;
    D_U32   mediaMusicProgTime;

    D_HTimer mediaMusicTimer;

    D_U8    mediaMusicCurrLang;

    D_SubtitleInfo mediaMusicSubInfo;
    D_Handle mediaMusicLrCbmanHandle;
    D_Char      mediaMusicLrcBuff[MEDIA_MUSIC_LRC_LEN_BUFF];

    D_Visual* vis_list, *vis_path_name;
    D_Visual* vis_group_play;
    D_Visual* vis_play_status, *vis_show_status;
    D_Visual* vis_play_time;
    D_Visual* vis_music_icon, *vis_music_name;
    D_Visual* vis_music_logo, *vis_progress;
    D_Visual* vis_lrc, *vis_play_mode, *vis_play_mode_img;
} MediaMusicData;

static MediaMusicData* media_music_data = NULL;

static D_FILE_TYPE media_music_type[] =
{
    D_FILE_TYPE_MP3, D_FILE_TYPE_WMA,
    D_FILE_TYPE_WAV, D_FILE_TYPE_AAC, D_FILE_TYPE_AC3,
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
};

static D_Result media_music_stop_play(void) D_FUNCPOSTFIT;

/*更新歌词文件显示*/
static D_Result
media_music_update_lrc_handler(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    int ret;
    D_SubtitleInfo* sub;

    if(media_music_data && media_music_data->vis_lrc)
    {
        ret = d_media_get_curr_subtitle(&media_music_data->mediaMusicSubInfo);
        if(ret < 0)
        {
            d_vis_show(media_music_data->vis_lrc, D_FALSE);
        }
        else if(ret > 0)
        {
            sub = &media_music_data->mediaMusicSubInfo;
            switch(sub->line_cnt)
            {
                case 1:
                    snprintf(media_music_data->mediaMusicLrcBuff, MEDIA_MUSIC_LRC_LEN_BUFF, "%s", sub->sub_text[0]);
                    break;
                case 2:
                    snprintf(media_music_data->mediaMusicLrcBuff, MEDIA_MUSIC_LRC_LEN_BUFF, "%s\n%s", sub->sub_text[0], sub->sub_text[1]);
                    break;
                case 3:
                    snprintf(media_music_data->mediaMusicLrcBuff, MEDIA_MUSIC_LRC_LEN_BUFF, "%s\n%s\n%s", sub->sub_text[0], sub->sub_text[1], sub->sub_text[2]);
                    break;
                default:
                    media_music_data->mediaMusicLrcBuff[0] = '\0';
                    break;
            }

            d_label_set_text(media_music_data->vis_lrc, media_music_data->mediaMusicLrcBuff);
            d_vis_show(media_music_data->vis_lrc, D_TRUE);
        }
    }

    return D_OK;
}


static D_Result
media_music_find_next_by_play_mode(MEDIA_MUSIC_PLAY_MODE play_mode)D_FUNCPOSTFIT
{
    D_U32  idx, play_id = -1;

    switch(play_mode)
    {
        case MEDIA_MUSIC_SINGLE_LOOP:
            play_id = media_music_data->mediaMusicCurrPlaying;
            break;
        case MEDIA_MUSIC_LIST_LOOP:

            for(idx = media_music_data->mediaMusicCurrPlaying + 1; idx < media_music_data->mediaMusicFileRset.cnt; idx++)
            {
                if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[idx])))
                {
                    play_id = idx;
                    break;
                }
            }

            if(play_id == -1)
            {
                for(idx = 0; idx <= media_music_data->mediaMusicCurrPlaying; idx++)
                {
                    if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[idx])))
                    {
                        play_id = idx;
                        break;
                    }
                }
            }
            break;
        case MEDIA_MUSIC_RANDOM_PLAY:
            srand(d_sys_get_time());
            while(1)
            {
                idx = rand() % (media_music_data->mediaMusicFileRset.cnt);
                if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[idx])))
                {
                    play_id = idx;
                    break;
                }

            }
            break;
        case MEDIA_MUSIC_LIST_PLAY:
            for(idx = media_music_data->mediaMusicCurrPlaying + 1; idx < media_music_data->mediaMusicFileRset.cnt; idx++)
            {
                if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[idx])))
                {
                    play_id = idx;
                    break;
                }
            }
            break;
    }

    return play_id;
}


static D_Result
media_music_set_show_img(void) D_FUNCPOSTFIT
{
    if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrPlaying])))
    {
        media_music_data->mediaMusicLastPlaying = media_music_data->mediaMusicCurrPlaying;
        if(media_music_data->mediaMusicCurrPage == ((media_music_data->mediaMusicLastPlaying / MEDIA_MUSIC_LIST_ROW_CNT) + 1))
        {
            d_list_set_image(media_music_data->vis_list, media_music_data->mediaMusicLastPlaying, 1, d_gui_get_image(atv_IMG_ID_music_select_pane));
        }
    }

    media_music_data->mediaMusicCurrPlaying = media_music_data->mediaMusicCurrListFocus;
    d_list_set_image(media_music_data->vis_list, media_music_data->mediaMusicCurrListFocus, 1, d_gui_get_image(atv_IMG_ID_music_pitch_on));

    return D_OK;
}

/**@brief 设置音乐的播放状态*/
static D_Result
media_music_set_play_status(D_U8 action) D_FUNCPOSTFIT
{
    if(action == MEDIA_MUSIC_STOP_STATUS)
    {
        d_media_music_stop();
        d_image_box_set_image(media_music_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_stop));
        d_label_set_text(media_music_data->vis_show_status, d_gui_get_text(atv_IDS_STOP));
    }
    else if(action == MEDIA_MUSIC_PLAYING_STATUS)
    {
        d_media_music_resume();
        d_image_box_set_image(media_music_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_pause));
        d_label_set_text(media_music_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
    }
    else if(action == MEDIA_MUSIC_PAUSE_STATUS)
    {
        d_media_music_pause();
        d_image_box_set_image(media_music_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_play));
        d_label_set_text(media_music_data->vis_show_status, d_gui_get_text(atv_IDS_PLAY));
    }
    else if(action == MEDIA_MUSIC_START_STATUS)
    {
        d_image_box_set_image(media_music_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_pause));
        d_label_set_text(media_music_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
    }

    return D_OK;
}

/**@brief 设置音乐的显示时间*/
static D_Result
media_music_show_curr_time(D_U8  action) D_FUNCPOSTFIT
{
    D_U8   total_hour, total_min, total_sec ;
    D_U8   curr_hour, curr_min, curr_sec ;

    media_music_data->mediaMusicTotalTime = media_music_data->mediaMusicFileInfo.totaltime;

    if(action == MEDIA_MUSIC_TIME_UPDATE)
    {
        media_music_data->mediaMusicCurrTime = d_media_music_get_curtime();
        media_music_data->mediaMusicCurrTime /= 1000;
    }
    else if(action == MEDIA_MUSIC_TIME_RESET)
    {
        media_music_data->mediaMusicCurrTime = 0;
        media_music_data->mediaMusicTotalTime = 0;
        media_music_data->mediaMusicProgTime = 0;
    }
    else if(action == MEDIA_MUSIC_TIME_START)
    {
        media_music_data->mediaMusicCurrTime = 0;
    }

    if(media_music_data->mediaMusicTotalTime)
    {
        media_music_data->mediaMusicProgTime = (media_music_data->mediaMusicCurrTime * 100) / media_music_data->mediaMusicTotalTime;
    }

    curr_hour = (D_U32)media_music_data->mediaMusicCurrTime / 3600;
    curr_min   = ((D_U32)media_music_data->mediaMusicCurrTime % 3600) / 60;
    curr_sec   = ((D_U32)media_music_data->mediaMusicCurrTime % 3600) % 60;


    total_hour = (D_U32)media_music_data->mediaMusicTotalTime / 3600;
    total_min   = ((D_U32)media_music_data->mediaMusicTotalTime % 3600) / 60;
    total_sec   = ((D_U32)media_music_data->mediaMusicTotalTime % 3600) % 60;


    sprintf(media_music_data->mediaMusicPlayTime, "%02d:%02d:%02d/%02d:%02d:%02d",curr_hour, curr_min, curr_sec, total_hour, total_min, total_sec);

    d_label_set_text(media_music_data->vis_play_time, media_music_data->mediaMusicPlayTime);
    d_progress_bar_set_val(media_music_data->vis_progress, media_music_data->mediaMusicProgTime);

    return D_OK;
}


/**@brief 根据文件类型设置相应的图片*/
static D_ImageID
media_music_get_img_id_by_filetype(D_FSAttr *fattr) D_FUNCPOSTFIT
{
    D_ImageID img_id = (D_ImageID) - 1;

    switch(fattr->class_type)
    {
        case D_FILE_SCAN_FMT_Dir:
            img_id = atv_IMG_ID_music_select_file;
            break;
        case D_FILE_SCAN_FMT_UpDir:
            img_id = atv_IMG_ID_music_select_up_level;
            break;
        case D_FILE_SCAN_FMT_Music:
            img_id = atv_IMG_ID_music_select_pane;
            break;
        case D_FILE_SCAN_FMT_Device:
            img_id = atv_IMG_ID_media_disk;
            break;
        default:
            break;
    }

    return img_id;
}

/**@brief 更新列表显示*/
static D_Result
media_music_list_info_show(void) D_FUNCPOSTFIT
{
    D_ID start, i, row;
    D_ImageID img_id;
    D_Image* img;
    D_Size   file_length;

    start = d_list_get_first_line_id(media_music_data->vis_list);
    for(i = start; i < start + MEDIA_MUSIC_LIST_ROW_CNT; i++)
    {
        if(i >= media_music_data->mediaMusicFileRset.cnt)
        {
            d_list_set_image(media_music_data->vis_list, i, 1, NULL);
            d_list_set_text(media_music_data->vis_list,  i, 2, NULL);
            d_list_set_text(media_music_data->vis_list,  i, 3, NULL);
        }
        else
        {
            if((i == media_music_data->mediaMusicCurrPlaying) && (media_music_data->mediaMusicPlayed == D_TRUE))
            {
                img_id = atv_IMG_ID_music_pitch_on;
            }
            else
            {
                img_id = media_music_get_img_id_by_filetype(&(media_music_data->mediaMusicFileRset.ids[i]));
            }

            img = d_gui_get_image(img_id);
            d_list_set_image(media_music_data->vis_list, i, 1, img);

            row = i - start;
#ifndef D_SYSTEM_WIN32
            file_length = strlen(media_music_data->mediaMusicFileRset.ids[i].path.filename);
            p_cc_utf8_to_sys((D_U8*)media_music_data->mediaMusicListShowData[row], MEDIA_MUSIC_FILE_NAME_LEN, \
                             (D_U8*)media_music_data->mediaMusicFileRset.ids[i].path.filename, file_length);
#else
            strcpy(media_music_data->mediaMusicListShowData[row], media_music_data->mediaMusicFileRset.ids[i].path.filename);
#endif
            p_atv_media_device_name_map(media_music_data->mediaMusicListShowData[row]);
            d_list_set_text(media_music_data->vis_list, i, 2, media_music_data->mediaMusicListShowData[row]);
        }
    }

    return D_OK;
}

/**@brief 得到当前路径**/
static D_Result
media_music_get_currpath_name(void) D_FUNCPOSTFIT
{
    D_S16 focus;

    focus = d_list_get_focus(media_music_data->vis_list, NULL, NULL);
    if(focus < media_music_data->mediaMusicFileRset.cnt)
    {
        if(media_music_data->mediaMusicCurrFolder_utf8[0])
        {
            sprintf(media_music_data->mediaMusicCurrPathName_utf8, "%s/%s", media_music_data->mediaMusicCurrFolder_utf8, media_music_data->mediaMusicFileRset.ids[focus].path.filename);
        }
        else
        {
            sprintf(media_music_data->mediaMusicCurrPathName_utf8, "%s", media_music_data->mediaMusicFileRset.ids[focus].path.filename);
        }

#ifndef D_SYSTEM_WIN32
        p_cc_utf8_to_sys((D_U8*)media_music_data->mediaMusicCurrPathName, MEDIA_MUSIC_PATH_NAME_LEN, \
                         (D_U8*)media_music_data->mediaMusicCurrPathName_utf8, strlen(media_music_data->mediaMusicCurrPathName_utf8));
#else
        strcpy(media_music_data->mediaMusicCurrPathName, media_music_data->mediaMusicCurrPathName_utf8);
#endif

    }

    p_atv_media_device_name_map(media_music_data->mediaMusicCurrPathName);
    d_label_set_text(media_music_data->vis_path_name, media_music_data->mediaMusicCurrPathName);

    return D_OK;
}


/**@brief 得到路径下的文件列表*/
static D_Result
media_music_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        memset(media_music_data->mediaMusicFileRset.ids, 0x00, sizeof(D_FSAttr) * media_music_data->mediaMusicFileRset.max);
        media_music_data->mediaMusicFileRset.max = MEDIA_MUSIC_MAX_NUM_CNT;
        media_music_data->mediaMusicFileRset.cnt = 0;

        p_file_scan_get_current_dir(curr_path, &media_music_data->mediaMusicFileRset, media_music_type, sizeof(media_music_type) / sizeof(media_music_type[0]), D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        media_music_data->mediaMusicFileRset.cnt = 0;
        media_music_data->mediaMusicFileRset.max = MEDIA_MUSIC_PARTITION_MAX_CNT;
        media_music_data->mediaMusicTotalPartition = 0;
        d_fsm_get_volumes(media_music_data->mediaMusicVolIndex, &media_music_data->mediaMusicTotalPartition);
        memset(media_music_data->mediaMusicFileRset.ids, 0x00, sizeof(D_FSAttr) * media_music_data->mediaMusicFileRset.max);

        p_file_scan_get_all_partitons(&media_music_data->mediaMusicFileRset, media_music_data->mediaMusicVolIndex, media_music_data->mediaMusicTotalPartition);
    }

    return D_OK;
}

/** @brief取得上一文件夹路径全名utf8 与 文件夹名utf8*/
static D_Result
media_music_get_up_folder( void )D_FUNCPOSTFIT
{
    D_Char* temp;

    temp = strrchr(media_music_data->mediaMusicCurrFolder_utf8, '/');
    if(temp)
    {
        *temp = '\0';
        temp++;
        strcpy(media_music_data->mediaMusicLastFolder_utf8, temp);
    }
    else
    {
        media_music_data->mediaMusicCurrFolder_utf8[0] = '\0';
        media_music_data->mediaMusicLastFolder_utf8[0] = '\0';
    }

    return D_OK;
}

/**@brief 查找返回上一级目录时焦点值*/
static D_ID
media_music_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_music_data->mediaMusicFocuLevel)
    {
        media_music_data->mediaMusicFocuLevel--;
        return media_music_data->mediaMusicFocuStack[media_music_data->mediaMusicFocuLevel];
    }

    return D_OK;
}

/** @brief 返回上一级目录*/
static D_Result
media_music_return_up_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;

    if(media_music_data->mediaMusicCurrFolder_utf8[0])
    {
        media_music_get_up_folder();
        media_music_get_files_list(media_music_data->mediaMusicCurrFolder_utf8);
        d_list_set_max_row(media_music_data->vis_list, media_music_data->mediaMusicFileRset.cnt);
        focus = (D_S16)media_music_get_last_focus();
        d_list_set_focus(media_music_data->vis_list, focus, (D_U16) - 1);
        media_music_data->mediaMusicPlayed = D_FALSE;
        media_music_list_info_show();
        media_music_get_currpath_name();
				media_music_data->mediaMusicCurrPlaying = 0;	
        if(media_music_data->mediaMusicFocuLevel== 0)
        {
            media_music_data->mediaMusicCurrPartition = 0xFF;
        }
        return D_OK;
    }
		else
		{
        media_music_stop_play();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
		}

    return D_ERR;
}

/** @brief 进入下一级目录*/
static D_Result
media_music_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;
    D_U32 length;

    focus = d_list_get_focus(media_music_data->vis_list, NULL, NULL);
    if(media_music_data->mediaMusicFileRset.ids[focus].type == 0  &&  focus < media_music_data->mediaMusicFileRset.cnt)
    {
        if(media_music_data->mediaMusicFocuLevel < MEDIA_MUSIC_FOLDER_LEVEL_MAX)
        {
            if(0 == media_music_data->mediaMusicFocuLevel)
            {
                media_music_data->mediaMusicCurrPartition = media_music_data->mediaMusicVolIndex[focus];
            }

            media_music_data->mediaMusicFocuStack[media_music_data->mediaMusicFocuLevel++] = focus;
        }

        strcpy(media_music_data->mediaMusicLastFolder_utf8, media_music_data->mediaMusicFileRset.ids[focus].path.filename);

        length = strlen(media_music_data->mediaMusicCurrFolder_utf8);
        if(length)
        {
            media_music_data->mediaMusicCurrFolder_utf8[length] = '/';
            media_music_data->mediaMusicCurrFolder_utf8[length + 1] = '\0';
            strcat(media_music_data->mediaMusicCurrFolder_utf8, media_music_data->mediaMusicFileRset.ids[focus].path.filename);
        }
        else
        {
            strcpy(media_music_data->mediaMusicCurrFolder_utf8, media_music_data->mediaMusicFileRset.ids[focus].path.filename);
        }

        media_music_get_files_list(media_music_data->mediaMusicCurrFolder_utf8);
        d_list_set_max_row(media_music_data->vis_list, media_music_data->mediaMusicFileRset.cnt);
        d_list_set_focus(media_music_data->vis_list, 0, (D_U16) - 1);
        media_music_data->mediaMusicPlayed = D_FALSE;
        media_music_list_info_show();
        media_music_get_currpath_name();
        media_music_data->mediaMusicCurrPage = media_music_data->vis_list->element.list.current_page + 1;
				media_music_data->mediaMusicCurrPlaying = 0;	
        return D_OK;
    }

    return D_ERR;
}

static D_Result
media_music_show_curr_info(D_Bool show) D_FUNCPOSTFIT
{
    if(show)
    {
        D_Size file_length;

#ifndef D_SYSTEM_WIN32
        file_length = strlen(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus].path.filename);
        p_cc_utf8_to_sys((D_U8*)media_music_data->mediaMusicFileName, MEDIA_MUSIC_FILE_NAME_LEN, \
        (D_U8*)media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus].path.filename, file_length);
#else
        strcpy(media_music_data->mediaMusicFileName, media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus].path.filename);
#endif

    }

    d_image_box_set_image(media_music_data->vis_music_icon, show ? d_gui_get_image(atv_IMG_ID_icon_music_play) : NULL);
    d_label_set_text(media_music_data->vis_music_name, show ? media_music_data->mediaMusicFileName : NULL);

    return D_OK;
}

/**@brief 停止播放所有的资源*/
static D_Result
media_music_stop_play(void) D_FUNCPOSTFIT
{
    d_vis_show(media_music_data->vis_lrc, D_FALSE);
    d_vis_show(media_music_data->vis_group_play, D_FALSE);
    media_music_set_play_status(MEDIA_MUSIC_STOP_STATUS);
    media_music_show_curr_time(MEDIA_MUSIC_TIME_RESET);
    media_music_show_curr_info(D_FALSE);

    return D_OK;
}

/** @brief 查找指定文件名的后缀是否为指定的后缀
* @retval D_TRUE:查找成功，D_FALSE:查找失败没找到
*/
static D_Bool 
Judge_Music_postfix(D_Char *filename, D_Char *postfix) D_FUNCPOSTFIT
{
	D_U8 i = 0;
	char * file_fmt_prv = NULL;

    if(!postfix)
        return D_FALSE;
	file_fmt_prv = strrchr(filename, '.');
	if (file_fmt_prv)
	{
		file_fmt_prv++;
		if (strcasecmp(file_fmt_prv,postfix) == 0)
		{
			return D_TRUE;
		}
	}
	return D_FALSE;
}

static D_Result
media_music_play_curr_music(D_U16 id) D_FUNCPOSTFIT
{
    D_FSAttr *fsattr;

    media_music_stop_play();
    fsattr = &(media_music_data->mediaMusicFileRset.ids[id]);

    if(Judge_Music_File(fsattr))
    {
        media_music_set_show_img();
#ifndef D_SYSTEM_WIN32
        if(D_OK == d_media_music_get_info(media_music_data->mediaMusicCurrPathName_utf8, &media_music_data->mediaMusicFileInfo))
        {
/*			if(Judge_Music_postfix(media_music_data->mediaMusicCurrPathName_utf8,"wav") && media_music_data->mediaMusicFileInfo.sample_rate == 192000)
 - 			{
 - 				p_atv_media_prompt_msg(atv_IDS_NOT_SUPPORT_FILE);
 - 				return D_ERR;
 - 			}*/
            if((media_music_data->mediaMusicFileInfo.sample_rate >= 96000) && ((media_music_data->mediaMusicFileInfo.codec_id == D_AUD_CODEC_AAC)|| (media_music_data->mediaMusicFileInfo.codec_id == D_AUD_CODEC_DRA)) )
            {
               p_atv_media_prompt_msg(atv_IDS_NOT_SUPPORT_FILE);
               return D_ERR;
            }
	        if(D_OK == d_media_music_play(media_music_data->mediaMusicCurrPathName_utf8, 0, NULL))
	        {
	            d_vis_show(media_music_data->vis_group_play, D_TRUE);
	            media_music_set_play_status(MEDIA_MUSIC_START_STATUS);
	            media_music_show_curr_time(MEDIA_MUSIC_TIME_START);
	            media_music_show_curr_info(D_TRUE);
	            media_music_data->mediaMusicPlayed = D_TRUE;
	            return D_OK;
	        }
	        else
	        {
	        	p_atv_media_prompt_msg(atv_IDS_NOT_SUPPORT_FILE);
	        	return D_ERR;
	        }
        }
        else
        {
			p_atv_media_prompt_msg(atv_IDS_NOT_SUPPORT_FILE);
			return D_ERR;
        }
#endif
    }

    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
media_music_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_PLAY_STOP:
                    if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus])))
                    {
                        status = d_media_music_get_status();
                        if(media_music_data->mediaMusicCurrPlaying == media_music_data->mediaMusicCurrListFocus)
                        {
                            if(status == MUSIC_STATUS_RUN)
                            {
                                media_music_set_play_status(MEDIA_MUSIC_PAUSE_STATUS);
                            }
                            else if(status == MUSIC_STATUS_PAUSE)
                            {
                                media_music_set_play_status(MEDIA_MUSIC_PLAYING_STATUS);
                            }
                            else
                            {
                                media_music_set_play_status(MEDIA_MUSIC_START_STATUS);
                                media_music_play_curr_music(media_music_data->mediaMusicCurrListFocus);
                            }
                        }
                        else
                        {
                            media_music_play_curr_music(media_music_data->mediaMusicCurrListFocus);
                        }
                    }
                    return D_OK;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(Judge_Dir_Folder(&(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus])))
                    {
                        media_music_stop_play();
                        media_music_enter_next_folder();
                    }
                    else if(Judge_Up_Folder(&(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus])))
                    {
                        media_music_stop_play();
                        media_music_return_up_folder();
                    }
                    else if(Judge_Music_File(&(media_music_data->mediaMusicFileRset.ids[media_music_data->mediaMusicCurrListFocus])))
                    {
                        status = d_media_music_get_status();
                        if(media_music_data->mediaMusicCurrPlaying == media_music_data->mediaMusicCurrListFocus)
                        {
                            if(status == MUSIC_STATUS_RUN)
                            {
                                media_music_set_play_status(MEDIA_MUSIC_PAUSE_STATUS);
                            }
                            else if(status == MUSIC_STATUS_PAUSE)
                            {
                                media_music_set_play_status(MEDIA_MUSIC_PLAYING_STATUS);
                            }
                            else
                            {
                                media_music_set_play_status(MEDIA_MUSIC_START_STATUS);
                                media_music_play_curr_music(media_music_data->mediaMusicCurrListFocus);
                            }
                        }
                        else
                        {
                            media_music_play_curr_music(media_music_data->mediaMusicCurrListFocus);
                        }
                    }
                    return D_OK;
                default:
                    break;
            }
            break;
        case D_EVT_DATA_CHANGED:
            media_music_list_info_show();
            media_music_data->mediaMusicCurrPage = media_music_data->vis_list->element.list.current_page + 1;
            break;
        case D_EVT_SELECTED:
            media_music_data->mediaMusicCurrListFocus = d_list_get_focus(vis, NULL, NULL);
            media_music_get_currpath_name();
            break;
    }
    return D_ERR;
}

static D_Result
media_music_window_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                media_music_data->mediaMusicCurrLang = evt->user.param2;
                if(D_LANG_CHN == evt->user.param2)
                {
                    d_image_box_set_image(media_music_data->vis_music_logo, d_gui_get_image(atv_IMG_ID_title_music));
                }
                else
                {
                    d_image_box_set_image(media_music_data->vis_music_logo, d_gui_get_image(atv_IMG_ID_title_music_en));
                }

                d_vis_update(media_music_data->vis_music_logo, NULL);
                d_gui_update();
            }
            break;
				
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
									media_music_stop_play();
									media_music_return_up_folder();
                    return D_OK;
				case D_KEY_GREEN:
					media_music_data->mediaMusicPlayMode++;
					if(media_music_data->mediaMusicPlayMode == 4)
					{
						media_music_data->mediaMusicPlayMode = 0;
					}
					d_label_set_text(media_music_data->vis_play_mode, d_gui_get_text(play_mode_text[media_music_data->mediaMusicPlayMode]));
					d_image_box_set_image(media_music_data->vis_play_mode_img, d_gui_get_image(play_mode_img[media_music_data->mediaMusicPlayMode]));
					break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_music_data->mediaMusicTimer)
            {
                status = d_media_music_get_status();
                if(status == MUSIC_STATUS_RUN)
                {
                    media_music_show_curr_time(MEDIA_MUSIC_TIME_UPDATE);
                }
                else if((status == MUSIC_STATUS_STOP) && (media_music_data->mediaMusicPlayed == D_TRUE))
                {
                    D_ID file_id;
                    file_id = media_music_find_next_by_play_mode(media_music_data->mediaMusicPlayMode);
                    if(file_id >= 0)
                    {
                        //media_music_data->mediaMusicCurrPlaying = file_id;
                        d_list_set_focus(media_music_data->vis_list, file_id, (D_U16) - 1);
                        media_music_get_currpath_name();
                        media_music_play_curr_music(file_id);
                    }
                    else
                    {
                        //因为顺序播放设计的时候是当播放完最后一个是不会在循环播放第一个的。
                        //此时音乐的状态位STOP，导致再按的时候无法播放当前的,所以做特殊处理
                    }
                }
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
                /*拔出usb时判断是当前磁盘以退出菜单 @qiny 20150907*/
                if( (media_music_data->mediaMusicTotalPartition < 2) ||
                    ((int)media_music_data->mediaMusicCurrPartition == (int)evt->hotplug.arg))
                {
                    media_music_stop_play();
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    break;
                }
            }

            /*磁盘界面时，插拔usb，刷新磁盘显示 @qiny 20150907*/
            if(media_music_data->mediaMusicFocuLevel == 0)
            {
                media_music_data->mediaMusicCurrPartition = 0xFF;
                media_music_data->mediaMusicCurrFolder_utf8[0] = '\0';
                media_music_get_files_list(media_music_data->mediaMusicCurrFolder_utf8);
                d_list_set_max_row(media_music_data->vis_list, media_music_data->mediaMusicFileRset.cnt);
                media_music_list_info_show();
                media_music_get_currpath_name();
            }
 
            break;
        case D_EVT_DESTROY:
        {
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_MUSIC;
            d_vis_unsubscribe_evt (vis);
            if(media_music_data->mediaMusicTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_music_data->mediaMusicTimer);
                media_music_data->mediaMusicTimer = D_INVALID_HANDLE;
            }

            if(media_music_data)
            {
                PROJECT_FREE(media_music_data->mediaMusicFileRset.ids);
                PROJECT_FREE(media_music_data);
                media_music_data = NULL;
            }

            d_media_music_close();
            d_mediacodec_close();
        }
        break;
    }
    return D_ERR;
}



D_Result
atv_media_music_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_music_data = (MediaMusicData*)PROJECT_ALLOC(sizeof(MediaMusicData));
    if(!media_music_data)
    {
        return D_ERR;
    }

    memset(media_music_data, 0x00, sizeof(MediaMusicData));
    media_music_data->mediaMusicCurrPartition = 0xFF;

    /*挂起DVB播放和SI监控*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/

    /*初始化多媒体音视频图片的各自的播放任务*/
    d_mediacodec_open();
    d_media_music_open() ;

    /*重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();

    media_music_data->mediaMusicLrCbmanHandle = D_INVALID_HANDLE;
    media_music_data->vis_list = d_frame_get_control(frm, ID_MUSIC_LIST);
    media_music_data->vis_path_name = d_frame_get_control(frm, ID_MUSIC_LABEL_PATH);
    media_music_data->vis_play_status = d_frame_get_control(frm, ID_MUSIC_IMG_PLAY_STATUS);
    media_music_data->vis_show_status = d_frame_get_control(frm, ID_MUSIC_LABEL_STATUS);
    media_music_data->vis_play_time = d_frame_get_control(frm, ID_MUSIC_LABEL_TIME);
    media_music_data->vis_music_icon = d_frame_get_control(frm, ID_MUSIC_IMG_MUSIC_ICON);
    media_music_data->vis_music_name = d_frame_get_control(frm, ID_MUSIC_LABEL_SONG_NAME);
    media_music_data->vis_music_logo = d_frame_get_control(frm, ID_MUSIC_IMG_LOGO);
    media_music_data->vis_progress = d_frame_get_control(frm, ID_MUSIC_PROGRESS);
    media_music_data->vis_lrc = d_frame_get_control(frm, ID_MUSIC_LABEL_LYRIC);
	media_music_data->vis_play_mode = d_frame_get_control(frm, ID_MUSIC_PLAY_MODE_0);
	media_music_data->vis_play_mode_img = d_frame_get_control(frm, D_FRAMECONTROL_PLAY_MODE);
	media_music_data->vis_group_play = d_frame_get_control(frm, ID_MUSIC_GROUP_PLAY);
	
    media_music_data->mediaMusicPlayed = D_FALSE;
    media_music_data->mediaMusicPlayMode = MEDIA_MUSIC_LIST_LOOP;

    media_music_data->mediaMusicFileRset.max = MEDIA_MUSIC_MAX_NUM_CNT;
    media_music_data->mediaMusicFileRset.cnt = 0;
    media_music_data->mediaMusicFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_music_data->mediaMusicFileRset.max));
    if(!media_music_data->mediaMusicFileRset.ids)
    {
        return D_ERR;
    }

    d_vis_show(media_music_data->vis_group_play, D_FALSE);

    media_music_data->mediaMusicCurrLang = p_conf_get_lang();
    if(1 == media_music_data->mediaMusicCurrLang)
    {
        d_image_box_set_image(media_music_data->vis_music_logo, d_gui_get_image(atv_IMG_ID_title_music));
    }
    else
    {
        d_image_box_set_image(media_music_data->vis_music_logo, d_gui_get_image(atv_IMG_ID_title_music_en));
    }

    media_music_get_files_list(media_music_data->mediaMusicCurrFolder_utf8);

    vis = d_frame_get_control(frm, ID_MUSIC_LIST);
    if(vis)
    {
        d_vis_set_focus(vis);
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_music_list_handler);
        d_list_set_max_row(vis, media_music_data->mediaMusicFileRset.cnt);
        d_list_set_focus(media_music_data->vis_list, 0, (D_U16) - 1);
        media_music_list_info_show();
        media_music_get_currpath_name();
    }

    media_music_data->mediaMusicTimer = d_timer_create(NULL, MEDIA_MUSIC_REFRESH_TIME, d_gui_get_queue());
    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        if(media_music_data->mediaMusicTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_music_data->mediaMusicTimer);
        }
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_music_window_window_handler);
    }

    if(media_music_data->mediaMusicLrCbmanHandle == D_INVALID_HANDLE)
    {
        media_music_data->mediaMusicLrCbmanHandle = d_cbman_subscribe(PL_GUI_IDLE, D_INVALID_HANDLE, media_music_update_lrc_handler, NULL);
    }

	d_label_set_text(media_music_data->vis_play_mode, d_gui_get_text(atv_IDS_LIST_LOOP));
	d_image_box_set_image(media_music_data->vis_play_mode_img, d_gui_get_image(play_mode_img[media_music_data->mediaMusicPlayMode]));

    media_music_stop_play();
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_MUSIC;
    return D_OK;
}

D_Result
p_atv_media_music_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_music_window, D_CLEAR_ALL);
}


