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
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pConfig.h"
#include "dCBMan.h"
#include "dPvrReplay.h"

#include "atv_media_movie_window.c"


#define MEDIA_MOVIE_FOLDER_PATH_LEN  D_PATH_LENGTH
#define MEDIA_MOVIE_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_MOVIE_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_MOVIE_MAX_NUM_CNT      (1000)
#define MEDIA_MOVIE_PARTITION_MAX_CNT (24)
#define MEDIA_MOVIE_FOLDER_LEVEL_MAX  (64)
#define MEDIA_MOVIE_REFRESH_TIME   (1000)
#define MEDIA_MOVIE_FILE_BUFF_SIZE (64)
#define MEDIA_MOVIE_ROW_CNT        (7)
#define MEDIA_MOVIE_PREVIEW_TIME   (500)
#define MEDIA_MOVIE_PREVIEW_PLAY_TIME   (4000)


typedef enum
{
    MEDIA_MOVIE_LIST_LOOP = 0,      /*�б�ѭ��(���ŵ��б����һ������Ų��ŵ�һ��)*/
    MEDIA_MOVIE_SINGLE_LOOP,        /*����ѭ��*/
    MEDIA_MOVIE_RANDOM_PLAY,        /*�������*/
    MEDIA_MOVIE_LIST_PLAY,          /*�б���(���ŵ��б����һ����ֹͣ����)*/

} MEDIA_MOVIE_PLAY_MODE;

/**@brief ��ý���õ��Ľṹ��*/
typedef struct
{
    D_Char  mediaMovieCurrFolder_utf8[MEDIA_MOVIE_FOLDER_PATH_LEN];
    D_Char  mediaMovieLastFolder_utf8[MEDIA_MOVIE_FOLDER_PATH_LEN];
    D_Char  mediaMovieCurrPathName_utf8[MEDIA_MOVIE_FILE_NAME_LEN];
    D_Char  mediaMovieCurrPathName[MEDIA_MOVIE_PATH_NAME_LEN];
    D_Char  mediaMovieShowData[MEDIA_MOVIE_ROW_CNT][MEDIA_MOVIE_FILE_NAME_LEN];
    D_Char  mediaMovieFileName[MEDIA_MOVIE_FILE_NAME_LEN];

    /**������Ϣ*/
    D_Int   mediaMovieTotalPartition;                           /*�ܵĴ�����**/
    D_U8    mediaMovieVolIndex[MEDIA_MOVIE_PARTITION_MAX_CNT];  /*�ܹ����̷���**/
    D_U8    mediaMovieCurrPartition;                        /*��ǰ���̷�**/

    D_U16   mediaMovieFocuStack[MEDIA_MOVIE_FOLDER_LEVEL_MAX][2];/*����ջ����¼�����ļ��н���*/
    D_U32   mediaMovieFocuLevel;  /*�ļ�����*/

    D_U16   mediaMovieCurrFile;
    D_U8    mediaMovieSwitchValue;
    D_U8    mediaMovieChangeIndex;
    D_U32   mediaMovieCurrFocus;

    D_Bool  mediaMovieExitFullScreenFlag;
    MEDIA_MOVIE_PLAY_MODE    mediaMoviePlayMode;
    D_HTimer mediaMoviePreviewTimer;
    D_Time  mediaMoviePreviewTimer_starttime;

    D_HTimer mediaMoviePreviewPauseTimer;
    
    /*�ļ���¼��ָ��**/
    D_FileScan mediaMovieFileRset;

    D_MovieInfo mediaMovieFileInfo;

    D_U8    mediaMovieCurrLang;

    D_VidWindow    mediaMoviePlayWin;
    D_Bool mediaMoviePlayFlag;
    D_Handle mediaMovie_pvr_tsparse_handle;
    D_Char cb_pic_file_path[D_PATH_LENGTH];
    
    D_Visual* vis_movie_logo, *vis_play_win, *vis_win;
    D_Visual* vis_button_0, *vis_button_1, *vis_button_2, *vis_button_3, *vis_button_4, *vis_button_5, *vis_button_6;
    D_Visual* vis_label_0, *vis_label_1, *vis_label_2, *vis_label_3, *vis_label_4, *vis_label_5, *vis_label_6;
    D_Visual* vis_path_name, *vis_direction_left, *vis_direction_right;
    D_Visual* vis_file_name, *vis_play_mode, *vis_play_mode_img;
} MediaMovieData;

static MediaMovieData* media_movie_data = NULL;

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_nothing_normal = { -1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_nothing_focus = { -1, -1, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_disk_normal = { -1, atv_IMG_ID_FS_Media_disk_normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_disk_focus = { -1, atv_IMG_ID_FS_Media_disk_focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_updir_normal = { -1, atv_IMG_ID_FS_Media_Floder1_Normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_updir_focus = { -1, atv_IMG_ID_FS_Media_Folder1_Focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_dir_normal = { -1, atv_IMG_ID_FS_Media_Folder_Normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_dir_focus = { -1, atv_IMG_ID_FS_Media_Folder_Focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_movie_normal = { -1, atv_IMG_ID_FS_Media_movie, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_movie_focus = { -1, atv_IMG_ID_FS_Media_Movie_Focus, -1, NULL, };

static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_disk = {{&GUID_disk_normal, &GUID_disk_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_updir = {{&GUID_updir_normal, &GUID_updir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_dir = {{&GUID_dir_normal, &GUID_dir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_movie = {{&GUID_movie_normal, &GUID_movie_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_nothing = {{&GUID_nothing_normal, &GUID_nothing_focus, NULL, }, 1, };

static int play_mode_text[4] = {atv_IDS_LIST_LOOP, atv_IDS_SINGNAL_LOOP, atv_IDS_RANDOM_LOOP, atv_IDS_LIST_PLAY};
static D_ID play_mode_img[4] = {atv_IMG_ID_music_list_loop, atv_IMG_ID_music_one_loop, atv_IMG_ID_music_random, atv_IMG_ID_music_list_play};


static D_FILE_TYPE media_movie_type[] =
{
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
    D_FILE_TYPE_AMR,
    D_FILE_TYPE_MP4,
    D_FILE_TYPE_AVI,
    D_FILE_TYPE_MOV,
    D_FILE_TYPE_MPG,
    D_FILE_TYPE_3GP,
    D_FILE_TYPE_DAT,
    D_FILE_TYPE_VOB,
    D_FILE_TYPE_FLV,
    D_FILE_TYPE_MKV,
    D_FILE_TYPE_TS,
};

static void media_movie_pvr_tsparse_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data);
static D_Result media_movie_stop_play(void) D_FUNCPOSTFIT;

/** @brief ·�����C/D/E��������ΪUSB��SD*/
D_Result 
p_atv_media_device_name_map(D_Char* pathname)D_FUNCPOSTFIT
{
#if 1
    if(pathname[1] == ':' && pathname[0] >= 'C' && pathname[0] <= 'Z')
    {
        D_Char tmpname[D_PATH_LENGTH] = {0};
        D_Char devtype[16] = {0};        
        D_U8  volidx;
        D_S32 type = 0, type_no = 0;

        volidx = (D_U8)(pathname[0] - 'C');
        d_fsm_get_volume_type_and_no(volidx, &type, &type_no);
        if(type == DEVICE_SD)
        {
            sprintf(devtype, "%s:", "SD");
        }
        else
        {
            if(type_no > 0)
            {
                sprintf(devtype, "USB%d:", type_no);
            }
            else
            {
                sprintf(devtype, "%s:", "USB");
            }
        }
        
        snprintf(tmpname, D_PATH_LENGTH, "%s%s", devtype, &pathname[2]);
        strcpy(pathname, tmpname);
    }
#endif
    return D_OK;
}

/** @brief ������һ����Ƶ�Ĳ�����Ϣ*/
static D_Char last_move_name[D_PATH_LENGTH] = {0};
static D_U32  last_move_playtime = 0;

D_Result 
p_atv_media_last_movie_save(D_Char* pathname, D_U32 play_time)D_FUNCPOSTFIT
{
    if(pathname)
    {
        snprintf(last_move_name, sizeof(last_move_name), "%s", pathname);
        //D_DUMP("Last name: %s\n", last_move_name);
    }
    last_move_playtime = play_time;
    //D_DUMP("Last time: %d\n", last_move_playtime);
}

D_U32
p_atv_media_last_movie_check(D_Char* pathname)D_FUNCPOSTFIT
{
    //D_DUMP("Last name: %s\n", last_move_name);
    //D_DUMP("cur  name: %s\n", pathname);
    //D_DUMP("Last time: %d\n", last_move_playtime);
    if(pathname && 0 == strcmp(pathname, last_move_name))
    {
        return last_move_playtime;
    }
    return 0;
}

/* ���ô�����ʾ�������أ�������ȫ������ʱ��Ӧ�ðѴ������أ���Ϊ��������й�������һֱˢ�»��ƣ�
�������ش��ڵ����岿�֣�����cpu �� gui���Ƶĸ�����@add by qiny 2017.11.16*/
static D_Result
media_movie_window_show(D_Bool show)D_FUNCPOSTFIT
{
    d_vis_show(d_frame_get_control(&atv_media_movie_window, ID_MOVIE_GROUP_ALL), show);
    return D_OK;
}

static D_Result
media_movie_preview_voice_mute(D_Bool mute)D_FUNCPOSTFIT
{
    if(mute)
    {
        d_tv_set_aud_mute (g_stb->player->htv, mute);        
    }
    else
    {
        mute = p_conf_get_aud_mute();
        d_tv_set_aud_mute (g_stb->player->htv, mute);
    }
    return D_OK;
}


static D_Result
media_movie_stop_preview_timer(void)D_FUNCPOSTFIT
{
    D_TimerAttr attr;

    if((!media_movie_data) || (!media_movie_data->vis_win))
    {
        return D_ERR;
    }

    if(media_movie_data->mediaMoviePreviewTimer != D_INVALID_HANDLE)
    {
        d_vis_unsubscribe_one_evt(media_movie_data->vis_win, D_EVT_TIMER_MASK, media_movie_data->mediaMoviePreviewTimer);
        d_timer_destroy(media_movie_data->mediaMoviePreviewTimer);
        media_movie_data->mediaMoviePreviewTimer = D_INVALID_HANDLE;
    }

    return D_OK;
}

static D_Result
media_movie_reset_preview_timer(void)D_FUNCPOSTFIT
{
    D_TimerAttr attr;

    if((!media_movie_data) || (!media_movie_data->vis_win))
    {
        return D_ERR;
    }

    if(media_movie_data->mediaMoviePreviewTimer == D_INVALID_HANDLE)
    {
        D_TIMER_ATTR_INIT(&attr);
        attr.one_shot = D_TRUE;
        media_movie_data->mediaMoviePreviewTimer = d_timer_create(&attr, MEDIA_MOVIE_PREVIEW_TIME, d_gui_get_queue());
        if(media_movie_data->mediaMoviePreviewTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(media_movie_data->vis_win, D_EVT_TIMER_MASK, media_movie_data->mediaMoviePreviewTimer);
        }
    }
    else
    {
        d_timer_reset(media_movie_data->mediaMoviePreviewTimer, MEDIA_MOVIE_PREVIEW_TIME);
    }
    media_movie_data->mediaMoviePreviewTimer_starttime = d_sys_get_time();
    return D_OK;
}

/*��ӰԤ��һ��ʱ�����ͣ*/
static D_Result
media_movie_preview_pause_timer_enable(D_Bool enable)D_FUNCPOSTFIT
{
    D_TimerAttr attr;

    if((!media_movie_data) || (!media_movie_data->vis_win))
    {
        return D_ERR;
    }

    if(enable)
    {
        if(media_movie_data->mediaMoviePreviewPauseTimer == D_INVALID_HANDLE)
        {
            D_TIMER_ATTR_INIT(&attr);
            attr.one_shot = D_TRUE;
            media_movie_data->mediaMoviePreviewPauseTimer = d_timer_create(&attr, MEDIA_MOVIE_PREVIEW_PLAY_TIME, d_gui_get_queue());
            if(media_movie_data->mediaMoviePreviewPauseTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(media_movie_data->vis_win, D_EVT_TIMER_MASK, media_movie_data->mediaMoviePreviewPauseTimer);
            }
        }
        else
        {
            d_timer_reset(media_movie_data->mediaMoviePreviewPauseTimer, MEDIA_MOVIE_PREVIEW_PLAY_TIME);
        }
    }
    else
    {
        if(media_movie_data->mediaMoviePreviewPauseTimer != D_INVALID_HANDLE)
        {
            d_vis_unsubscribe_one_evt(media_movie_data->vis_win, D_EVT_TIMER_MASK, media_movie_data->mediaMoviePreviewPauseTimer);
            d_timer_destroy(media_movie_data->mediaMoviePreviewPauseTimer);
            media_movie_data->mediaMoviePreviewPauseTimer = D_INVALID_HANDLE;
        }
    }

    return D_OK;
}


static D_ID
media_movie_get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

/**@brief �õ���Ƶ����Ϣ**/
static D_Result
media_movie_get_movie_info(void) D_FUNCPOSTFIT
{
    return d_media_movie_get_info(media_movie_data->mediaMovieCurrPathName_utf8, &media_movie_data->mediaMovieFileInfo, \
    media_movie_data->mediaMoviePlayWin.x, media_movie_data->mediaMoviePlayWin.y, media_movie_data->mediaMoviePlayWin.w, media_movie_data->mediaMoviePlayWin.h);
}

static D_Result
media_movie_show_curr_file_name(D_Bool show) D_FUNCPOSTFIT
{
    if(show)
    {
        D_Size file_length;

        memset(media_movie_data->mediaMovieFileName, 0x00, sizeof(media_movie_data->mediaMovieFileName));

#ifndef D_SYSTEM_WIN32
        file_length = strlen(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);

        p_cc_utf8_to_sys((D_U8*)media_movie_data->mediaMovieFileName, MEDIA_MOVIE_FILE_NAME_LEN, \
        (D_U8*)media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename, file_length);
#else
        strcpy(media_movie_data->mediaMovieFileName, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
#endif
    }

    d_label_set_text(media_movie_data->vis_file_name, show ? media_movie_data->mediaMovieFileName : NULL);

    return D_OK;
}


static D_Result
media_movie_set_direction(D_Bool show, D_Bool left) D_FUNCPOSTFIT
{
    D_Image* img_left = NULL;
    D_Image* img_right = NULL;

    if(show)
    {
        if(left)
        {
            img_left =  d_gui_get_image(atv_IMG_ID_button_left);
            img_right = d_gui_get_image(atv_IMG_ID_button_right);
        }
        else
        {
            img_left =  d_gui_get_image(atv_IMG_ID_button_left);
            img_right = d_gui_get_image(atv_IMG_ID_button_right);
        }
    }

    d_image_box_set_image(media_movie_data->vis_direction_left, show ? img_left : NULL);
    d_image_box_set_image(media_movie_data->vis_direction_right, show ? img_right : NULL);

    return D_OK;
}

static D_Result
media_movie_left_show(D_Bool left) D_FUNCPOSTFIT
{
    D_Image* img_left = NULL;
    D_Image* img_right = NULL;


    if(left)
    {
        img_left =  d_gui_get_image(atv_IMG_ID_button_left);
        d_image_box_set_image(media_movie_data->vis_direction_left, img_left);
        d_image_box_set_image(media_movie_data->vis_direction_right,  NULL);
    }
    else
    {
        img_right =  d_gui_get_image(atv_IMG_ID_button_right);
        d_image_box_set_image(media_movie_data->vis_direction_right, img_right);
        d_image_box_set_image(media_movie_data->vis_direction_left,  NULL);
    }

    return D_OK;
}

/**@brief �õ���ǰ·��**/
static D_Result
media_movie_get_currpath_name(void) D_FUNCPOSTFIT
{
    if(media_movie_data->mediaMovieCurrFolder_utf8[0])
    {
        sprintf(media_movie_data->mediaMovieCurrPathName_utf8, "%s/%s", media_movie_data->mediaMovieCurrFolder_utf8, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
    }
    else
    {
        sprintf(media_movie_data->mediaMovieCurrPathName_utf8, "%s", media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
    }

#ifndef D_SYSTEM_WIN32
    p_cc_utf8_to_sys((D_U8*)media_movie_data->mediaMovieCurrPathName, MEDIA_MOVIE_PATH_NAME_LEN, \
    (D_U8*)media_movie_data->mediaMovieCurrPathName_utf8, strlen(media_movie_data->mediaMovieCurrPathName_utf8));
#else
    strcpy(media_movie_data->mediaMovieCurrPathName, media_movie_data->mediaMovieCurrPathName_utf8);
#endif

    p_atv_media_device_name_map(media_movie_data->mediaMovieCurrPathName);
    d_label_set_text(media_movie_data->vis_path_name, media_movie_data->mediaMovieCurrPathName);

    return D_OK;
}

static D_Result
media_movie_show_info(void) D_FUNCPOSTFIT
{
    D_ID id, start;
    D_ID visual_id;
    D_FSAttr *fattr;
    D_Size file_length;
    D_Visual* button_my_vis[7];
    D_Visual* label_my_vis[7];

    memset(label_my_vis, 0x00, sizeof(label_my_vis));
    memset(button_my_vis, 0x00, sizeof(button_my_vis));

    start =  MEDIA_MOVIE_ROW_CNT * media_movie_data->mediaMovieChangeIndex;

    for(id = start; id < start + MEDIA_MOVIE_ROW_CNT; id++)
    {
        visual_id = id % MEDIA_MOVIE_ROW_CNT;

        switch(visual_id)
        {
            case 0:
                button_my_vis[visual_id] = media_movie_data->vis_button_0;
                label_my_vis[visual_id] = media_movie_data->vis_label_0;
                break;
            case 1:
                button_my_vis[visual_id] = media_movie_data->vis_button_1;
                label_my_vis[visual_id] = media_movie_data->vis_label_1;
                break;
            case 2:
                button_my_vis[visual_id] = media_movie_data->vis_button_2;
                label_my_vis[visual_id] = media_movie_data->vis_label_2;
                break;
            case 3:
                button_my_vis[visual_id] = media_movie_data->vis_button_3;
                label_my_vis[visual_id] = media_movie_data->vis_label_3;
                break;
            case 4:
                button_my_vis[visual_id] = media_movie_data->vis_button_4;
                label_my_vis[visual_id] = media_movie_data->vis_label_4;
                break;
            case 5:
                button_my_vis[visual_id] = media_movie_data->vis_button_5;
                label_my_vis[visual_id] = media_movie_data->vis_label_5;
                break;
            case 6:
                button_my_vis[visual_id] = media_movie_data->vis_button_6;
                label_my_vis[visual_id] = media_movie_data->vis_label_6;
                break;
        }

        if(id >= media_movie_data->mediaMovieFileRset.cnt)
        {
            d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_nothing);
            d_label_set_text(label_my_vis[visual_id], NULL);
        }
        else
        {

            fattr = &(media_movie_data->mediaMovieFileRset.ids[id]);

            switch(fattr->class_type)
            {
                case D_FILE_SCAN_FMT_Dir:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_dir);
                    break;
                case D_FILE_SCAN_FMT_UpDir:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_updir);
                    break;
                case D_FILE_SCAN_FMT_Movie:
                case D_FILE_SCAN_FMT_TS:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_movie);
                    break;
                case D_FILE_SCAN_FMT_Device:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_disk);
                    break;
            }

#ifndef D_SYSTEM_WIN32
            file_length = strlen(fattr->path.filename);
            p_cc_utf8_to_sys((D_U8*)media_movie_data->mediaMovieShowData[visual_id], MEDIA_MOVIE_FILE_NAME_LEN, \
                             (D_U8*)fattr->path.filename, file_length);
#else
            strcpy(media_movie_data->mediaMovieShowData[visual_id], fattr->path.filename);
#endif
            p_atv_media_device_name_map(media_movie_data->mediaMovieShowData[visual_id]);
            d_label_set_text(label_my_vis[visual_id], media_movie_data->mediaMovieShowData[visual_id]);

        }
    }

    return D_OK;
}


/**@brief �õ�·���µ��ļ��б�*/
static D_Result
media_movie_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        memset(media_movie_data->mediaMovieFileRset.ids, 0x00, sizeof(D_FSAttr) * media_movie_data->mediaMovieFileRset.max);
        media_movie_data->mediaMovieFileRset.max = MEDIA_MOVIE_MAX_NUM_CNT;
        media_movie_data->mediaMovieFileRset.cnt = 0;

        p_file_scan_get_current_dir(curr_path, &media_movie_data->mediaMovieFileRset, media_movie_type, sizeof(media_movie_type) / sizeof(media_movie_type[0]), D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        media_movie_data->mediaMovieFileRset.cnt = 0;
        media_movie_data->mediaMovieFileRset.max = MEDIA_MOVIE_PARTITION_MAX_CNT;
        media_movie_data->mediaMovieTotalPartition = 0;
        d_fsm_get_volumes(media_movie_data->mediaMovieVolIndex, &media_movie_data->mediaMovieTotalPartition);
        memset(media_movie_data->mediaMovieFileRset.ids, 0x00, sizeof(D_FSAttr) * media_movie_data->mediaMovieFileRset.max);

        p_file_scan_get_all_partitons(&media_movie_data->mediaMovieFileRset, media_movie_data->mediaMovieVolIndex, media_movie_data->mediaMovieTotalPartition);
    }

    media_movie_data->mediaMovieSwitchValue = media_movie_data->mediaMovieFileRset.cnt / MEDIA_MOVIE_ROW_CNT;

    return D_OK;
}


/** @brief ������һ��Ŀ¼*/
static D_Result
media_movie_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_U32 length;
    D_Visual* vis;

    if(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].type == 0  &&  media_movie_data->mediaMovieCurrFile < media_movie_data->mediaMovieFileRset.cnt)
    {
        if(media_movie_data->mediaMovieFocuLevel < MEDIA_MOVIE_FOLDER_LEVEL_MAX)
        {
            if(0 == media_movie_data->mediaMovieFocuLevel)
            {
                media_movie_data->mediaMovieCurrPartition = media_movie_data->mediaMovieVolIndex[media_movie_data->mediaMovieCurrFile];
            }

            media_movie_data->mediaMovieFocuStack[media_movie_data->mediaMovieFocuLevel][0] = media_movie_data->mediaMovieCurrFile;
            media_movie_data->mediaMovieFocuStack[media_movie_data->mediaMovieFocuLevel][1] = media_movie_data->mediaMovieChangeIndex;
            media_movie_data->mediaMovieFocuLevel++;
        }

        strcpy(media_movie_data->mediaMovieLastFolder_utf8, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);

        length = strlen(media_movie_data->mediaMovieCurrFolder_utf8);
        if(length)
        {
            media_movie_data->mediaMovieCurrFolder_utf8[length] = '/';
            media_movie_data->mediaMovieCurrFolder_utf8[length + 1] = '\0';
            strcat(media_movie_data->mediaMovieCurrFolder_utf8, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
        }
        else
        {
            strcpy(media_movie_data->mediaMovieCurrFolder_utf8, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
        }

        media_movie_get_files_list(media_movie_data->mediaMovieCurrFolder_utf8);
        media_movie_data->mediaMovieChangeIndex = 0;
        media_movie_data->mediaMovieCurrFile = 0;
        media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_0;
        vis = d_frame_get_control(&atv_media_movie_window, media_movie_data->mediaMovieCurrFocus);
        if(vis)
        {
            d_vis_set_focus(vis);
        }
        media_movie_show_info();
        media_movie_get_currpath_name();
        if(media_movie_data->mediaMovieFileRset.cnt > 7)
        {
            media_movie_left_show(D_FALSE);
        }
        else
        {
            media_movie_set_direction(D_FALSE, D_FALSE);
        }

        return D_OK;
    }

    return D_ERR;

}

static D_Result
media_movie_get_up_folder( void )D_FUNCPOSTFIT
{
    D_Char* temp;

    temp = strrchr(media_movie_data->mediaMovieCurrFolder_utf8, '/');
    if(temp)
    {
        *temp = '\0';
        temp++;
        strcpy(media_movie_data->mediaMovieLastFolder_utf8, temp);
        //media_movie_set_direction(D_TRUE, D_FALSE);
    }
    else
    {
        media_movie_data->mediaMovieLastFolder_utf8[0] = '\0';
        media_movie_data->mediaMovieCurrFolder_utf8[0] = '\0';
        media_movie_set_direction(D_FALSE, D_FALSE);

    }

    return D_OK;
}

/**@brief ���ҷ�����һ��Ŀ¼ʱ����ֵ*/
static D_ID
media_movie_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_movie_data->mediaMovieFocuLevel)
    {
        media_movie_data->mediaMovieFocuLevel--;
        media_movie_data->mediaMovieCurrFile = media_movie_data->mediaMovieFocuStack[media_movie_data->mediaMovieFocuLevel][0];
        media_movie_data->mediaMovieChangeIndex = media_movie_data->mediaMovieFocuStack[media_movie_data->mediaMovieFocuLevel][1];
    }

    return D_OK;
}

static D_Result
media_movie_set_curr_focus(void) D_FUNCPOSTFIT
{
    D_U32 focus;
    D_Visual* vis;

    focus = (media_movie_data->mediaMovieCurrFile % MEDIA_MOVIE_ROW_CNT);
    switch(focus)
    {
        case 0:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_0;
            break;
        case 1:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_1;
            break;
        case 2:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_2;
            break;
        case 3:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_3;
            break;
        case 4:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_4;
            break;
        case 5:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_5;
            break;
        case 6:
            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_6;
            break;
    }

    vis = d_frame_get_control(&atv_media_movie_window, media_movie_data->mediaMovieCurrFocus);
    if(vis)
    {
        d_vis_set_focus(vis);
    }

    return D_OK;
}

/** @brief ������һ��Ŀ¼*/
static D_Result
media_movie_return_up_folder( void )D_FUNCPOSTFIT
{

    if(media_movie_data->mediaMovieCurrFolder_utf8[0])
    {
        media_movie_get_up_folder();
        media_movie_get_files_list(media_movie_data->mediaMovieCurrFolder_utf8);
        media_movie_get_last_focus();

        if(media_movie_data->mediaMovieFocuLevel == 0)
        {
            media_movie_data->mediaMovieCurrPartition = 0xFF;
        }

        if(media_movie_data->mediaMovieChangeIndex == 0 && media_movie_data->mediaMovieFileRset.cnt > 7)
        {
            media_movie_left_show(D_FALSE);
        }
        else if(media_movie_data->mediaMovieChangeIndex == (media_movie_data->mediaMovieSwitchValue) && media_movie_data->mediaMovieFileRset.cnt > 7)
        {
            media_movie_left_show(D_TRUE);
        }
        else if(media_movie_data->mediaMovieFileRset.cnt <= 7  )
        {
            media_movie_set_direction(D_FALSE, D_FALSE);
        }
        else
        {
            media_movie_set_direction(D_TRUE, D_TRUE);
        }

        media_movie_set_curr_focus();
        media_movie_show_info();
        media_movie_get_currpath_name();
        return D_OK;
    }
    else
    {
        media_movie_stop_play();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_ERR;
}


static D_Result
media_movie_preview_curr_movie(void) D_FUNCPOSTFIT
{
    D_Result rest;
    D_FSAttr *fsattr;
    fsattr = &(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile]);

    media_movie_stop_play();
    media_movie_preview_pause_timer_enable(D_FALSE);
    media_movie_preview_voice_mute(D_TRUE);
    if(Judge_Movie_File(fsattr))
    {
        d_av_set_vid_input (0, D_VID_IUTPUT_USB1);
        d_mediacodec_open();
        /*���農��/����/����*/
        //p_stb_reset_mute_track_volume();
        rest = media_movie_get_movie_info();
        if(D_OK == rest) /*���۽����ȡ��Ƶ��Ϣ�Ƿ����֧�ֲ�������ʾ�û� by wangyuq*/
        {
            /*��֧�ֲ��Ŵ���оƬ��������֮�����Ƶ ������̫С�ߴ����ƵҲ��֧��*/
            if((media_movie_data->mediaMovieFileInfo.width == 0 && media_movie_data->mediaMovieFileInfo.height == 0) \
            || media_movie_data->mediaMovieFileInfo.width > D_Media_Movie_Codec_Width_Max || media_movie_data->mediaMovieFileInfo.height > D_Media_Movie_Codec_Height_Max \
            || media_movie_data->mediaMovieFileInfo.width <= D_Media_Movie_Codec_Width_Limit || media_movie_data->mediaMovieFileInfo.height <= D_Media_Movie_Codec_Height_LImit)
            {
                media_movie_data->mediaMoviePlayFlag = D_FALSE;
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                return D_ERR;
            }
            media_movie_data->mediaMoviePlayFlag = D_TRUE;
            if( D_OK == d_media_movie_play(media_movie_data->mediaMovieCurrPathName_utf8, media_movie_data->mediaMoviePlayWin.x, media_movie_data->mediaMoviePlayWin.y, media_movie_data->mediaMoviePlayWin.w, media_movie_data->mediaMoviePlayWin.h, 0, NULL))
            {
                media_movie_show_curr_file_name(D_TRUE);
                media_movie_preview_pause_timer_enable(D_TRUE);
               d_av_set_vid_blank(0, D_FALSE); /*�˳�����*/
                return D_OK;
            }
        }
        else
        {
            media_movie_data->mediaMoviePlayFlag = D_FALSE;
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            return D_ERR;
        }
    }
    else if(Judge_TS_File(fsattr))
    {
        d_mediacodec_close();
        d_av_set_vid_input (0, D_VID_IUTPUT_DTV);
        media_movie_data->mediaMoviePlayFlag = D_TRUE;
        //d_media_movie_preview(media_movie_data->mediaMovieCurrPathName_utf8, media_movie_data->mediaMoviePlayWin.x, media_movie_data->mediaMoviePlayWin.y, media_movie_data->mediaMoviePlayWin.w, media_movie_data->mediaMoviePlayWin.h);
        rest = media_movie_get_movie_info();
        D_DUMP("%s totaltime:%d ,filesize:%d \n", __FUNCTION__, media_movie_data->mediaMovieFileInfo.totaltime, media_movie_data->mediaMovieFileInfo.filesize);
        if (D_OK == rest && D_OK == d_media_movie_play(media_movie_data->mediaMovieCurrPathName_utf8, media_movie_data->mediaMoviePlayWin.x, media_movie_data->mediaMoviePlayWin.y, media_movie_data->mediaMoviePlayWin.w, media_movie_data->mediaMoviePlayWin.h, 0, NULL))
        {
            media_movie_show_curr_file_name(D_TRUE);
            media_movie_preview_pause_timer_enable(D_TRUE);
          d_av_set_vid_blank(0, D_FALSE); /*�˳�����*/
            return D_OK;
        }
        else
        {
            media_movie_data->mediaMoviePlayFlag = D_FALSE;
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            return D_ERR;
        }
    }
    else
    {
        D_DUMP("\n unkown video format . \n");
    }

    return D_ERR;
}

static D_Result
media_movie_fullscreen_hide_handler(D_U16 focus)D_FUNCPOSTFIT
{
    D_Frame * frm = &atv_media_movie_window;
    D_Visual *vis_focus;

    if(media_movie_data)
    {
        d_media_movie_stop();
        media_movie_window_show(D_TRUE); // �˳���Ӱȫ��ʱ��Ҫ�ָ��б��ڵ���ʾ @qiny 2017.11.16
        media_movie_data->mediaMoviePlayFlag = D_FALSE;
        media_movie_show_curr_file_name(D_FALSE);
        d_av_set_vid_blank(0, D_TRUE);

        media_movie_data->mediaMovieExitFullScreenFlag = D_FALSE;

        media_movie_data->mediaMovieCurrFile = focus;

        media_movie_data->mediaMovieChangeIndex = media_movie_data->mediaMovieCurrFile / MEDIA_MOVIE_ROW_CNT;
        media_movie_show_info();

        media_movie_data->mediaMovieCurrFocus = (media_movie_data->mediaMovieCurrFile) % MEDIA_MOVIE_ROW_CNT + ID_MOVIE_BUTTON_0;

        vis_focus = d_frame_get_control(frm, media_movie_data->mediaMovieCurrFocus);
        if(vis_focus)
        {
            d_vis_set_focus(vis_focus);
        }

        if(media_movie_data->mediaMovieCurrFolder_utf8[0])
        {
            sprintf(media_movie_data->mediaMovieCurrPathName_utf8, "%s/%s", media_movie_data->mediaMovieCurrFolder_utf8, media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
        }
        else
        {
            sprintf(media_movie_data->mediaMovieCurrPathName_utf8, "%s", media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile].path.filename);
        }

        if(media_movie_data->mediaMovie_pvr_tsparse_handle == D_INVALID_HANDLE)
        {
            media_movie_data->mediaMovie_pvr_tsparse_handle = d_cbman_subscribe(PL_MEDIA_PVR_PARSE_TS, D_INVALID_HANDLE, media_movie_pvr_tsparse_cb, (D_Ptr)frm);
        }
		media_movie_get_currpath_name();
        media_movie_preview_curr_movie();
    }

    return D_OK;
}


static D_Result
media_movie_stop_play(void) D_FUNCPOSTFIT
{
    d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
    d_media_movie_stop();
    d_av_set_vid_blank(0, D_TRUE); /*����*/
    media_movie_data->mediaMoviePlayFlag = D_FALSE;
    media_movie_show_curr_file_name(D_FALSE);
    return D_OK;
}


static D_Result
media_movie_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    media_movie_stop_play();
                    media_movie_preview_pause_timer_enable(D_FALSE);
                    if(Judge_Dir_Folder(&(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile])))
                    {
                        media_movie_enter_next_folder();
                        media_movie_reset_preview_timer();
                    }
                    else if(Judge_Up_Folder(&(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile])))
                    {
                        media_movie_return_up_folder();
                        media_movie_reset_preview_timer();
                    }
                    else if(Judge_Movie_File(&(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile]))\
                            || Judge_TS_File(&(media_movie_data->mediaMovieFileRset.ids[media_movie_data->mediaMovieCurrFile])))
                    {
                        media_movie_stop_preview_timer();
                        d_cbman_unsubscribe(media_movie_data->mediaMovie_pvr_tsparse_handle);
                        media_movie_data->mediaMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
                        media_movie_preview_voice_mute(D_FALSE);
                        if(D_OK == p_media_movie_full_screen_show(media_movie_data->mediaMovieCurrFolder_utf8, media_movie_data->mediaMovieCurrFile, &media_movie_data->mediaMovieFileRset,
                                media_movie_data->mediaMoviePlayMode, media_movie_fullscreen_hide_handler))
                        {
                            media_movie_data->mediaMovieExitFullScreenFlag = D_TRUE;
                            media_movie_window_show(D_FALSE); // ��Ӱȫ��ʱ��Ҫ�����б��ڵ���ʾ @qiny 2017.11.16
                        }
                        else
                        {
                            if(media_movie_data->mediaMovie_pvr_tsparse_handle == D_INVALID_HANDLE)
                            {
                                media_movie_data->mediaMovie_pvr_tsparse_handle = d_cbman_subscribe(PL_MEDIA_PVR_PARSE_TS, D_INVALID_HANDLE, media_movie_pvr_tsparse_cb, (D_Ptr)(&atv_media_movie_window));
                            }
                        }

                    }
                    return D_OK;
                default:
                    break;
            }
            break;
    }
    return D_ERR;
}


static D_Result
media_movie_window_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame * frm = &atv_media_movie_window;
    D_Visual *vis_focus;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                media_movie_data->mediaMovieCurrLang = evt->user.param2;
                if(D_LANG_CHN == evt->user.param2 )
                {
                    d_image_box_set_image(media_movie_data->vis_movie_logo, d_gui_get_image(atv_IMG_ID_title_movie));
                }
                else
                {
                    d_image_box_set_image(media_movie_data->vis_movie_logo, d_gui_get_image(atv_IMG_ID_title_movie_en));
                }
                d_vis_update(media_movie_data->vis_movie_logo, NULL);
                d_gui_update();
            }
            break;
        case D_EVT_USER2:
            if((evt->user.handle == (D_Handle)frm) && (evt->user.param1 == USER_MSG_PARAM1_MEDIA_PVR_PLAY_END))
            {
                if(strcmp(media_movie_data->cb_pic_file_path, media_movie_data->mediaMovieCurrPathName_utf8) == 0)
                {
                    D_U32 pvr_ts_parse_res = (D_U32)evt->user.param2;

                    if(pvr_ts_parse_res == 0)/*�����ļ�info ʧ��*/
                    {
                        media_movie_preview_pause_timer_enable(D_FALSE);
                        /*��ts�ļ����������ԭ��*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                    }
                    else if (pvr_ts_parse_res == 1)/*����ʧ�� û���ҵ�PAT�����Ϣ parse_ts_packet ���س���*/
                    {
                        media_movie_preview_pause_timer_enable(D_FALSE);
                        /*��ͼƬ�ļ�����������ڴ�ռ䲻��*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                    }
                }
            }
            break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    media_movie_stop_play();
                    media_movie_return_up_folder();
                    return D_OK;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    return D_OK;
                case D_KEY_GREEN:
                    media_movie_data->mediaMoviePlayMode++;
                    if(media_movie_data->mediaMoviePlayMode == 4)
                    {
                        media_movie_data->mediaMoviePlayMode = 0;
                    }
                    d_label_set_text(media_movie_data->vis_play_mode, d_gui_get_text(play_mode_text[media_movie_data->mediaMoviePlayMode]));
                    d_image_box_set_image(media_movie_data->vis_play_mode_img, d_gui_get_image(play_mode_img[media_movie_data->mediaMoviePlayMode]));
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(media_movie_data->mediaMovieExitFullScreenFlag == D_TRUE)
                    {
                        break;
                    }

                    media_movie_reset_preview_timer();

                    if(media_movie_data->mediaMovieChangeIndex > 0)
                    {
                        if(media_movie_data->mediaMovieCurrFile == ((media_movie_data->mediaMovieChangeIndex)*MEDIA_MOVIE_ROW_CNT))
                        {
                            media_movie_data->mediaMovieChangeIndex--;
                            media_movie_show_info();
                        }
                    }

                    if(media_movie_data->mediaMovieCurrFile)
                    {
                        media_movie_data->mediaMovieCurrFile--;
                        if(media_movie_data->mediaMovieCurrFocus == ID_MOVIE_BUTTON_0)
                        {
                            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_6;
                        }
                        else
                        {
                            media_movie_data->mediaMovieCurrFocus = media_movie_data->mediaMovieCurrFocus - 1;
                        }

                        vis_focus = d_frame_get_control(frm, media_movie_data->mediaMovieCurrFocus);
                        if(vis_focus)
                        {
                            d_vis_set_focus(vis_focus);
                        }

                        if(media_movie_data->mediaMovieChangeIndex == 0 && media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_left_show(D_FALSE);
                        }
                        else if(media_movie_data->mediaMovieChangeIndex == (media_movie_data->mediaMovieSwitchValue) && media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_left_show(D_TRUE);
                        }
                        else if(media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_set_direction(D_TRUE, D_TRUE);
                        }
                        else
                            media_movie_set_direction(D_FALSE, D_FALSE);

                        media_movie_get_currpath_name();

                        //media_movie_preview_curr_movie();
                    }
                    return D_OK;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(media_movie_data->mediaMovieExitFullScreenFlag == D_TRUE)
                    {
                        break;
                    }

                    media_movie_reset_preview_timer();
                    if(media_movie_data->mediaMovieCurrFile < media_movie_data->mediaMovieFileRset.cnt - 1)
                    {

                        media_movie_data->mediaMovieCurrFile++;
                        if(media_movie_data->mediaMovieChangeIndex < media_movie_data->mediaMovieSwitchValue)
                        {
                            if(media_movie_data->mediaMovieCurrFile == ((media_movie_data->mediaMovieChangeIndex + 1)*MEDIA_MOVIE_ROW_CNT))
                            {
                                media_movie_data->mediaMovieChangeIndex++;
                                media_movie_show_info();
                            }
                        }

                        if(media_movie_data->mediaMovieCurrFocus == ID_MOVIE_BUTTON_6)
                        {
                            media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_0;
                        }
                        else
                        {
                            media_movie_data->mediaMovieCurrFocus = media_movie_data->mediaMovieCurrFocus + 1;
                        }

                        vis_focus = d_frame_get_control(frm, media_movie_data->mediaMovieCurrFocus);
                        if(vis_focus)
                        {
                            d_vis_set_focus(vis_focus);
                        }

                        if(media_movie_data->mediaMovieChangeIndex == 0 && media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_left_show(D_FALSE);
                        }
                        else if(media_movie_data->mediaMovieChangeIndex == (media_movie_data->mediaMovieSwitchValue) && media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_left_show(D_TRUE);
                        }
                        else if(media_movie_data->mediaMovieFileRset.cnt > 7)
                        {
                            media_movie_set_direction(D_TRUE, D_FALSE);
                        }
                        else
                            media_movie_set_direction(D_FALSE, D_FALSE);

                        media_movie_get_currpath_name();
                        //media_movie_preview_curr_movie();
                    }
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_movie_data->mediaMoviePreviewTimer &&  media_movie_data->mediaMovieExitFullScreenFlag == D_FALSE)
            {
                /* ��ֹ��������һ���ѻ��Ķ�ʱ��Ϣ*/
                if(d_sys_get_time() > (media_movie_data->mediaMoviePreviewTimer_starttime + (MEDIA_MOVIE_PREVIEW_TIME - 100)))
                {
                    media_movie_preview_curr_movie();
                }
            }
            else if(evt->timer.htimer == media_movie_data->mediaMoviePreviewPauseTimer &&  media_movie_data->mediaMovieExitFullScreenFlag == D_FALSE)
            {
                media_movie_preview_pause_timer_enable(D_FALSE);
                d_media_movie_pause();
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
                /*�γ�usbʱ�ж��ǵ�ǰ�������˳��˵� @qiny 20150907*/
                if( (media_movie_data->mediaMovieTotalPartition < 2) ||
                    ((int)media_movie_data->mediaMovieCurrPartition == (int)evt->hotplug.arg))
                {
                    p_media_movie_full_screen_hide();
                    media_movie_stop_play();
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    break;
                }
            }

            /*���̽���ʱ�����usb��ˢ�´�����ʾ @qiny 20150907*/
            if(media_movie_data->mediaMovieFocuLevel == 0)
            {
                media_movie_data->mediaMovieCurrPartition = 0xFF;
                media_movie_data->mediaMovieCurrFolder_utf8[0] = '\0';
                media_movie_get_files_list(media_movie_data->mediaMovieCurrFolder_utf8);
                media_movie_data->mediaMovieCurrFile = D_MIN(media_movie_data->mediaMovieCurrFile, (media_movie_data->mediaMovieFileRset.cnt - 1));
                media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_0 + (media_movie_data->mediaMovieCurrFile % MEDIA_MOVIE_ROW_CNT);
                vis_focus = d_frame_get_control(frm, media_movie_data->mediaMovieCurrFocus);
                if(vis_focus)
                {
                    d_vis_set_focus(vis_focus);
                }
                media_movie_show_info();
                media_movie_get_currpath_name();
            }

            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_MOVIE;
            if(media_movie_data)
            {
                media_movie_preview_pause_timer_enable(D_FALSE);
                if(media_movie_data->mediaMoviePreviewTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(media_movie_data->mediaMoviePreviewTimer);
                    media_movie_data->mediaMoviePreviewTimer = D_INVALID_HANDLE;
                }

                if(media_movie_data->mediaMovie_pvr_tsparse_handle != D_INVALID_HANDLE)
                {
                    d_cbman_unsubscribe(media_movie_data->mediaMovie_pvr_tsparse_handle);
                    media_movie_data->mediaMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
                }
                PROJECT_FREE(media_movie_data->mediaMovieFileRset.ids);
                PROJECT_FREE(media_movie_data);
                media_movie_data = NULL;
            }
            d_av_set_vid_blank(0, D_TRUE); /*����*/
            d_media_movie_stop();
            d_media_movie_close();
            d_mediacodec_close();
            d_av_set_vid_input (0, D_VID_IUTPUT_USB1);
            /*���農��/����/����*/
            p_stb_reset_mute_track_volume();
        }
        break;
    }
    return D_ERR;
}

/** @brief ����ts��� �Ļص�����*/
static void media_movie_pvr_tsparse_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_Pvr_Cb *cb_ret = (D_Pvr_Cb*)obj_data;
    D_Frame *frm = &atv_media_movie_window;

    if(media_movie_data && frm == (D_Frame *)cb_data)
    {
        if(strcmp(cb_ret->path, media_movie_data->mediaMovieCurrPathName_utf8) == 0)
        {
            D_UserMsg msg;

            strcpy(media_movie_data->cb_pic_file_path, cb_ret->path);
            /* ���ڴ˺�����ts�������������ã�����gui������ã�
            ��˲�����ֱ�ӵ���gui��ص���ʾ�������������ؼ���ͼ�꣬
            ��ʾts����ʧ�ܵ���ʾ��guiͨ�����ʶ��̵߳��ã����
            �������ͨ����Ϣ�ķ�ʽ���ڴ���handler����д��� @qiny 20150923*/
            msg.type = D_MSG_USER2;
            msg.handle = (D_Handle)frm;
            msg.param1 = USER_MSG_PARAM1_MEDIA_PVR_PLAY_END;
            msg.param2 = (D_U32)cb_ret->pvr_ts_parse_res;
            msg.param3 = (D_U32)media_movie_data->cb_pic_file_path;
            d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
        }
    }

}

D_Result
atv_media_movie_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_movie_data = (MediaMovieData*)PROJECT_ALLOC(sizeof(MediaMovieData));
    if(!media_movie_data)
    {
        return D_ERR;
    }

    memset(media_movie_data, 0x00, sizeof(MediaMovieData));
    media_movie_data->mediaMovie_pvr_tsparse_handle = D_INVALID_HANDLE;
    media_movie_data->mediaMovieCurrPartition = 0xFF;
    media_movie_data->mediaMovieCurrFocus = ID_MOVIE_BUTTON_0;
    vis = d_frame_get_control(frm, media_movie_data->mediaMovieCurrFocus);
    if(vis)
    {
        d_vis_set_focus(vis);
    }

    media_movie_data->mediaMoviePreviewTimer = D_INVALID_HANDLE;
    media_movie_data->mediaMoviePreviewPauseTimer = D_INVALID_HANDLE;
    media_movie_data->mediaMovieExitFullScreenFlag = D_FALSE;
    media_movie_data->vis_movie_logo = d_frame_get_control(frm, ID_MOVIE_IMG_LOGO);
    media_movie_data->vis_button_0 = d_frame_get_control(frm, ID_MOVIE_BUTTON_0);
    media_movie_data->vis_button_1 = d_frame_get_control(frm, ID_MOVIE_BUTTON_1);
    media_movie_data->vis_button_2 = d_frame_get_control(frm, ID_MOVIE_BUTTON_2);
    media_movie_data->vis_button_3 = d_frame_get_control(frm, ID_MOVIE_BUTTON_3);
    media_movie_data->vis_button_4 = d_frame_get_control(frm, ID_MOVIE_BUTTON_4);
    media_movie_data->vis_button_5 = d_frame_get_control(frm, ID_MOVIE_BUTTON_5);
    media_movie_data->vis_button_6 = d_frame_get_control(frm, ID_MOVIE_BUTTON_6);

    media_movie_data->vis_label_0 = d_frame_get_control(frm, ID_MOVIE_LABEL_0);
    media_movie_data->vis_label_1 = d_frame_get_control(frm, ID_MOVIE_LABEL_1);
    media_movie_data->vis_label_2 = d_frame_get_control(frm, ID_MOVIE_LABEL_2);
    media_movie_data->vis_label_3 = d_frame_get_control(frm, ID_MOVIE_LABEL_3);
    media_movie_data->vis_label_4 = d_frame_get_control(frm, ID_MOVIE_LABEL_4);
    media_movie_data->vis_label_5 = d_frame_get_control(frm, ID_MOVIE_LABEL_5);
    media_movie_data->vis_label_6 = d_frame_get_control(frm, ID_MOVIE_LABEL_6);

    media_movie_data->vis_path_name = d_frame_get_control(frm, ID_MOVIE_PATH_LABEL);
    media_movie_data->vis_direction_left = d_frame_get_control(frm, ID_MOVIE_MING_LEFT);
    media_movie_data->vis_direction_right = d_frame_get_control(frm, ID_MOVIE_IMGE_RIGHT);

    media_movie_data->vis_play_win = d_frame_get_control(frm, ID_MOVIE_LANEL_PLAY_VIDEO);
    media_movie_data->vis_file_name = d_frame_get_control(frm, ID_MOVIE_LABEL_NAME);

    media_movie_data->vis_play_mode = d_frame_get_control(frm, ID_MOVIEW_PLAY_MODE);
    media_movie_data->vis_play_mode_img = d_frame_get_control(frm, ID_MOVIE_IMAGE_PLAY_MODE);

    media_movie_data->mediaMoviePlayMode = MEDIA_MOVIE_LIST_LOOP;

    d_vis_get_pos(media_movie_data->vis_play_win, &media_movie_data->mediaMoviePlayWin.x, &media_movie_data->mediaMoviePlayWin.y);
    media_movie_data->mediaMoviePlayWin.w = media_movie_data->vis_play_win->rect.w;
    media_movie_data->mediaMoviePlayWin.h = media_movie_data->vis_play_win->rect.h;

    /*����DVB���ź�SI���*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*����*/

    /*ֹͣfman���źŵļ��*/
    d_fman_set_locked_detector(g_stb->player->hfman, D_INVALID_HANDLE);
    d_app_set_timeout(g_stb->player->hfman, -1);

    /*�ͷ�epgռ����Դ*/
    p_auxi_free_varstring();

    /*��ʼ����ý������ƵͼƬ�ĸ��ԵĲ�������*/
    d_mediacodec_open();
    d_media_movie_set_version(MOVIE_FFMPEG_VER_OLD);
    d_media_movie_open() ;

    /*���農��/����/����*/
    p_stb_reset_mute_track_volume();

    media_movie_data->mediaMovieFileRset.max = MEDIA_MOVIE_MAX_NUM_CNT;
    media_movie_data->mediaMovieFileRset.cnt = 0;
    media_movie_data->mediaMovieFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_movie_data->mediaMovieFileRset.max));
    if(!media_movie_data->mediaMovieFileRset.ids)
    {
        return D_ERR;
    }

    media_movie_data->mediaMovieCurrLang = p_conf_get_lang();
    if(1 == media_movie_data->mediaMovieCurrLang)
    {
        d_image_box_set_image(media_movie_data->vis_movie_logo, d_gui_get_image(atv_IMG_ID_title_movie));
    }
    else
    {
        d_image_box_set_image(media_movie_data->vis_movie_logo, d_gui_get_image(atv_IMG_ID_title_movie_en));
    }


    media_movie_get_files_list(media_movie_data->mediaMovieCurrFolder_utf8);

    media_movie_show_info();
    media_movie_get_currpath_name();

    media_movie_data->mediaMovie_pvr_tsparse_handle = d_cbman_subscribe(PL_MEDIA_PVR_PARSE_TS, D_INVALID_HANDLE, media_movie_pvr_tsparse_cb, (D_Ptr)frm);

    vis = d_frame_get_control(frm, ID_MOVIE_GROUP);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);

        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_movie_button_handler);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        media_movie_data->vis_win = vis;

        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        //d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_movie_window_window_handler);
    }


    d_label_set_text(media_movie_data->vis_play_mode, d_gui_get_text(atv_IDS_LIST_LOOP));
    d_image_box_set_image(media_movie_data->vis_play_mode_img, d_gui_get_image(play_mode_img[media_movie_data->mediaMoviePlayMode]));


    media_movie_set_direction(D_FALSE, D_FALSE);
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_MOVIE;
    return D_OK;
}

D_Result
p_atv_media_movie_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &atv_media_movie_window, D_CLEAR_ALL);
}


