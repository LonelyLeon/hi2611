/** @file
* @brief ��ý���Ӱ�б�ģ��
* @author ����
* @date 2017-07-31  ����: �����ļ�
*/
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
#include "pConfig.h"
#include "dCBMan.h"
#include "dPvrReplay.h"

#include "music_list_menu_window.c"


#define MEDIA_FOLDER_NAME_LEN  D_PATH_LENGTH
#define MEDIA_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_FILE_MAX_CNT      (800) /**@brief ��ʾ���ļ������Ŀ*/
#define MEDIA_PARTITION_MAX_CNT (24)
#define MEDIA_FOLDER_LEVEL_MAX  (64)
#define MEDIA_FILE_BUFF_SIZE (128)
#define MEDIA_LIST_ROW_CNT    (3)
#define MEDIA_LIST_COL_CNT    (5)
#define MEDIA_REFRESH_TIME   (1000)
#define MEDIA_LRC_LEN_BUFF   (512)
/**@brief ÿҳ��ʾ���ļ���*/
#define MEDIA_LIST_NUM_PER_PAGE (MEDIA_LIST_ROW_CNT * MEDIA_LIST_COL_CNT)

/*���ָ���ʱ�������״̬**/
#define MEDIA_MUSIC_TIME_UPDATE  (0)
#define MEDIA_MUSIC_TIME_START   (1)
#define MEDIA_MUSIC_TIME_RESET   (2)

#define MEDIA_MUSIC_START_STATUS   (0)
#define MEDIA_MUSIC_PAUSE_STATUS   (1)
#define MEDIA_MUSIC_STOP_STATUS    (2)
#define MEDIA_MUSIC_PLAYING_STATUS (3)

typedef enum
{
    MEDIA_MUSIC_LIST_LOOP = 0,      /*�б�ѭ��(���ŵ��б����һ������Ų��ŵ�һ��)*/
    MEDIA_MUSIC_SINGLE_LOOP,        /*����ѭ��*/
    MEDIA_MUSIC_RANDOM_PLAY,        /*�������*/
    MEDIA_MUSIC_LIST_PLAY,          /*�б���(���ŵ��б����һ����ֹͣ����)*/

} MEDIA_MUSIC_PLAY_MODE;


/**@brief ��ý���õ��Ľṹ��*/
typedef struct
{
    D_Char  mediaCurrFolder_utf8[MEDIA_FOLDER_NAME_LEN]; /**��ǰĿ¼��**/
    D_Char  mediaLastFolder_utf8[MEDIA_FOLDER_NAME_LEN]; /**��һĿ¼��**/
    D_Char  mediaCurrPathName_utf8[MEDIA_FILE_NAME_LEN]; /**��ǰ�ļ�·��ȫ��**/
    D_Char  mediaCurrPathName[MEDIA_PATH_NAME_LEN];      /**��ǰ�ļ�·��ȫ��**/
    D_Char  mediaListContent[MEDIA_LIST_NUM_PER_PAGE][MEDIA_FILE_NAME_LEN]; /**�б�ÿ���ļ���**/
    D_Char  mediaFileName[MEDIA_FILE_NAME_LEN];    /**��ǰ�ļ���**/
    D_Char  mediaFileName_temp[MEDIA_FILE_NAME_LEN];    /**��ʱ��ǰ�ļ���**/

    /** ������Ϣ*/
    D_Int   mediaTotalPartition;                           /**�ܵĴ�����**/
    D_U8    mediaVolIndexs[MEDIA_PARTITION_MAX_CNT];  /* �ܹ����̷���**/
    D_U8    mediaCurrPartition;                        /* ��ǰ���̷�**/
    D_U8    cur_rset_num;


    D_U16   mediaLastLevelFocus;/* ����ջ����¼�����ļ��н���*/
    D_U32   mediaFocuLevel;  /* Ŀ¼����*/

    D_U32   mediaCurrFocus;  /* ��ǰ����*/
    D_U32   mediaCurrPage; /* ��ǰҳ��*/

    /* �ļ���¼��ָ��**/
    D_FileScan mediaCatalogRset;
    TV_FILE_RSET_INFO *fileRsetInfo;
    D_U16 area_info[4000];
    D_U16 area_num;
    //D_FileScan * mediaFileRset; /* ��ǰĿ¼�µ��ļ���¼��*/
    D_U8    mediaMenuCurrLang; /* ��ǰ�˵�����*/
    D_Bool mediaFilePlayFlag; /* ����״̬*/
    D_Bool  mediaExitFullScreenFlag; /* ȫ������״̬*/

    D_U32  menuVisShowCnt; /* ��ǰ��ʾ���ļ��ؼ�����*/
    D_Bool  menuEditFlag; /* �˵���Ծ״̬*/
    D_U32  sysUsbStatus; /* USB״̬*/

    D_Frame* win_frm;
    D_Visual* vis_group_all;
    D_Visual* vis_file_name;
    D_Visual* vis_group_play;

    D_U16   mediaMusicCurrPlaying;
    D_Bool  mediaMusicPlayed;
    MEDIA_MUSIC_PLAY_MODE    mediaMusicPlayMode;

    D_MusicInfo mediaMusicFileInfo;         /*������Ϣ�Ľṹ��**/
    D_Char  mediaMusicPlayTime[MEDIA_FILE_BUFF_SIZE];
    D_Char  mediaMusicFileName[MEDIA_FILE_NAME_LEN];          /*�����ļ�������**/
    D_U32   mediaMusicTotalTime;
    D_U32   mediaMusicCurrTime;
    D_U32   mediaMusicProgTime;

    D_HTimer mediaMusicTimer;
    D_HTimer mediaListTimer;

    D_SubtitleInfo mediaMusicSubInfo;
    D_Handle mediaMusicLrCbmanHandle;
    D_Char      mediaMusicLrcBuff[MEDIA_LRC_LEN_BUFF];

    D_Visual* vis_play_status, *vis_show_status;
    D_Visual* vis_play_time;
    D_Visual* vis_lrc, *vis_music_name;
    D_Visual *vis_progress;
    D_Visual* vis_play_mode;
} D_MediaMuiseListMenuData;

static int play_mode_text[4] = {atv_IDS_LIST_LOOP, atv_IDS_SINGNAL_LOOP, atv_IDS_RANDOM_LOOP, atv_IDS_LIST_PLAY};

static D_MediaMuiseListMenuData* media_list_data = NULL;
static D_U32 uCurrentMenuTpe = 0;

/**@brief ͼ��ؼ��ļ�����ʾ����*/
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_disk_normal = { -1, atv_IMG_ID_media_folder_file, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_disk_focus = { -1, atv_IMG_ID_media_folder_file_focse, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_muise_normal = { -1, atv_IMG_ID_media_muise_play, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_muise_focus = { -1, atv_IMG_ID_media_muise_play_focse, -1, NULL, };

static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_muise = {{&GUID_Attr_muise_normal, &GUID_Attr_muise_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_disk = {{&GUID_Attr_disk_normal, &GUID_Attr_disk_focus, NULL, }, 1, };

/**@brief �������ļ������б�*/
static D_FILE_TYPE media_music_type[] =
{
    D_FILE_TYPE_MP3, D_FILE_TYPE_WMA,
    D_FILE_TYPE_WAV, D_FILE_TYPE_AAC, D_FILE_TYPE_AC3,
};

extern D_Result
p_media_main_menu_set_enable(D_Bool enable) D_FUNCPOSTFIT;
extern D_U32 AtvMediaMenuStatus;


/*���¸���ļ���ʾ*/
static D_Result
media_update_lrc_handler(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    int ret;
    D_SubtitleInfo* sub;

    if(media_list_data && media_list_data->vis_lrc)
    {
        ret = d_media_get_curr_subtitle(&media_list_data->mediaMusicSubInfo);
        if(ret < 0)
        {
            d_vis_show(media_list_data->vis_lrc, D_FALSE);
        }
        else if(ret > 0)
        {
            sub = &media_list_data->mediaMusicSubInfo;
            switch(sub->line_cnt)
            {
                case 1:
                    snprintf(media_list_data->mediaMusicLrcBuff, MEDIA_LRC_LEN_BUFF, "%s", sub->sub_text[0]);
                    break;
                case 2:
                    snprintf(media_list_data->mediaMusicLrcBuff, MEDIA_LRC_LEN_BUFF, "%s\n%s", sub->sub_text[0], sub->sub_text[1]);
                    break;
                case 3:
                    snprintf(media_list_data->mediaMusicLrcBuff, MEDIA_LRC_LEN_BUFF, "%s\n%s\n%s", sub->sub_text[0], sub->sub_text[1], sub->sub_text[2]);
                    break;
                default:
                    media_list_data->mediaMusicLrcBuff[0] = '\0';
                    break;
            }

            d_label_set_text(media_list_data->vis_lrc, media_list_data->mediaMusicLrcBuff);
            d_vis_show(media_list_data->vis_lrc, D_TRUE);
        }
    }

    return D_OK;
}



/**@brief ���ļ�ȫ·��������ȡ�ļ���
*@param[out] file_name: �ļ���
*@param[in] file_path:  �ļ���·����
*/
static D_Result
music_play_analyse_name(D_Char * file_name, D_Char * file_path)
{
    char * ch_pos = NULL;

    ch_pos = strrchr(file_path, '/');
    if(ch_pos)
        ch_pos++;
    else
        return D_ERR;

    strcpy(file_name, ch_pos);

    return D_OK;
}


/**@brief �������ֵ���ʾʱ��*/
static D_Result
media_show_curr_time(D_U8  action) D_FUNCPOSTFIT
{
    D_U8   total_hour, total_min, total_sec ;
    D_U8   curr_hour, curr_min, curr_sec ;

    media_list_data->mediaMusicTotalTime = media_list_data->mediaMusicFileInfo.totaltime;

    if(action == MEDIA_MUSIC_TIME_UPDATE)
    {
        media_list_data->mediaMusicCurrTime = d_media_music_get_curtime();
        media_list_data->mediaMusicCurrTime /= 1000;
    }
    else if(action == MEDIA_MUSIC_TIME_RESET)
    {
        media_list_data->mediaMusicCurrTime = 0;
        media_list_data->mediaMusicTotalTime = 0;
        media_list_data->mediaMusicProgTime = 0;
    }
    else if(action == MEDIA_MUSIC_TIME_START)
    {
        media_list_data->mediaMusicCurrTime = 0;
    }

    if(media_list_data->mediaMusicTotalTime)
    {
        media_list_data->mediaMusicProgTime = (media_list_data->mediaMusicCurrTime * 100) / media_list_data->mediaMusicTotalTime;
    }

    curr_hour = (D_U32)media_list_data->mediaMusicCurrTime / 3600;
    curr_min   = ((D_U32)media_list_data->mediaMusicCurrTime % 3600) / 60;
    curr_sec   = ((D_U32)media_list_data->mediaMusicCurrTime % 3600) % 60;


    total_hour = (D_U32)media_list_data->mediaMusicTotalTime / 3600;
    total_min   = ((D_U32)media_list_data->mediaMusicTotalTime % 3600) / 60;
    total_sec   = ((D_U32)media_list_data->mediaMusicTotalTime % 3600) % 60;


    sprintf(media_list_data->mediaMusicPlayTime, "%02d:%02d:%02d/%02d:%02d:%02d", curr_hour, curr_min, curr_sec, total_hour, total_min, total_sec);

    d_label_set_text(media_list_data->vis_play_time, media_list_data->mediaMusicPlayTime);
    d_progress_bar_set_val(media_list_data->vis_progress, media_list_data->mediaMusicProgTime);

    return D_OK;
}

static D_Result
media_find_next_by_play_mode(MEDIA_MUSIC_PLAY_MODE play_mode)D_FUNCPOSTFIT
{
    D_U32  idx, play_id = -1;

    switch(play_mode)
    {
        case MEDIA_MUSIC_SINGLE_LOOP:
            play_id = media_list_data->mediaMusicCurrPlaying;
            break;
        case MEDIA_MUSIC_LIST_LOOP:

            for(idx = media_list_data->mediaMusicCurrPlaying + 1; idx < media_list_data->area_num; idx++)
            {
                if(media_list_data->fileRsetInfo[media_list_data->area_info[idx]].class_type == D_FILE_SCAN_FMT_Music)
                {
                    play_id = idx;
                    break;
                }
            }

            if(play_id == -1)
            {
                for(idx = 0; idx <= media_list_data->mediaMusicCurrPlaying; idx++)
                {
                    if(media_list_data->fileRsetInfo[media_list_data->area_info[idx]].class_type == D_FILE_SCAN_FMT_Music)
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
                idx = rand() % (media_list_data->area_num);
                if(media_list_data->fileRsetInfo[media_list_data->area_info[idx]].class_type == D_FILE_SCAN_FMT_Music)
                {
                    play_id = idx;
                    break;
                }

            }
            break;
        case MEDIA_MUSIC_LIST_PLAY:
            for(idx = media_list_data->mediaMusicCurrPlaying + 1; idx < media_list_data->area_num; idx++)
            {
                if(media_list_data->fileRsetInfo[media_list_data->area_info[idx]].class_type == D_FILE_SCAN_FMT_Music)
                {
                    play_id = idx;
                    break;
                }
            }
            break;
    }

    return play_id;
}


/**@brief �������ֵĲ���״̬*/
static D_Result
media_set_play_status(D_U8 action) D_FUNCPOSTFIT
{
    if(action == MEDIA_MUSIC_STOP_STATUS)
    {
        d_media_music_stop();
        d_image_box_set_image(media_list_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_stop));
        d_label_set_text(media_list_data->vis_show_status, d_gui_get_text(atv_IDS_STOP));
    }
    else if(action == MEDIA_MUSIC_PLAYING_STATUS)
    {
        d_media_music_resume();
        d_image_box_set_image(media_list_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_pause));
        d_label_set_text(media_list_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
    }
    else if(action == MEDIA_MUSIC_PAUSE_STATUS)
    {
        d_media_music_pause();
        d_image_box_set_image(media_list_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_play));
        d_label_set_text(media_list_data->vis_show_status, d_gui_get_text(atv_IDS_PLAY));
    }
    else if(action == MEDIA_MUSIC_START_STATUS)
    {
        d_image_box_set_image(media_list_data->vis_play_status, d_gui_get_image(atv_IMG_ID_media_movie_pause));
        d_label_set_text(media_list_data->vis_show_status, d_gui_get_text(atv_IDS_PAUSE));
    }

    return D_OK;
}
/**@brief �õ�·���µ��ļ��б�*/
static D_Result
medialist_menu_get_catalog_list() D_FUNCPOSTFIT
{
    /**��ǰĿ¼��Ϊ�գ�˵�����̷�Ŀ¼��ȡ���̷�Ŀ¼�б�**/
    media_list_data->mediaCatalogRset.cnt = 0;
    media_list_data->mediaCatalogRset.max = MEDIA_PARTITION_MAX_CNT;
    media_list_data->mediaCatalogRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_list_data->mediaCatalogRset.max));
    if(!media_list_data->mediaCatalogRset.ids)
    {
        return D_ERR;
    }
    media_list_data->mediaTotalPartition = 0;
    d_fsm_get_volumes(media_list_data->mediaVolIndexs, &media_list_data->mediaTotalPartition);
    memset(media_list_data->mediaCatalogRset.ids, 0x00, sizeof(D_FSAttr) * media_list_data->mediaCatalogRset.max);

    p_file_scan_get_all_partitons(&media_list_data->mediaCatalogRset, media_list_data->mediaVolIndexs, media_list_data->mediaTotalPartition);
    return D_OK;
}


/**@brief �õ���ǰ·���ļ���**/
static D_Result
medialist_menu_show_file_name(void) D_FUNCPOSTFIT
{
    if(media_list_data->mediaCatalogRset.cnt != 0)
    {
        sprintf(media_list_data->mediaCurrPathName_utf8, "%s", media_list_data->mediaCatalogRset.ids[media_list_data->mediaCurrFocus].path.filename);
#ifndef D_SYSTEM_WIN32
        p_cc_utf8_to_sys((D_U8*)media_list_data->mediaCurrPathName, MEDIA_PATH_NAME_LEN, \
        (D_U8*)media_list_data->mediaCurrPathName_utf8, strlen(media_list_data->mediaCurrPathName_utf8));
#else
        strcpy(media_list_data->mediaCurrPathName, media_list_data->mediaCurrPathName_utf8);
#endif
    }
    else
    {
        if(media_list_data->area_num)
        {
            sprintf(media_list_data->mediaCurrPathName_utf8, "%s", media_list_data->fileRsetInfo[media_list_data->area_info[media_list_data->mediaCurrFocus]].path);
#ifndef D_SYSTEM_WIN32
            p_cc_utf8_to_sys((D_U8*)media_list_data->mediaCurrPathName, MEDIA_PATH_NAME_LEN, \
            (D_U8*)media_list_data->mediaCurrPathName_utf8, strlen(media_list_data->mediaCurrPathName_utf8));
#else
            strcpy(media_list_data->mediaCurrPathName, media_list_data->mediaCurrPathName_utf8);
#endif
        }
        else
        {
            sprintf(media_list_data->mediaCurrPathName, "");
        }
    }
    d_label_set_text(media_list_data->vis_file_name, media_list_data->mediaCurrPathName);

    return D_OK;
}

/**@brief �趨��ǰ����ؼ�*/
static D_Result
medialist_menu_set_curr_focus(void) D_FUNCPOSTFIT
{
    D_U32 focus;
    D_Visual * vis, *old_focus;

    focus = (media_list_data->mediaCurrFocus % MEDIA_LIST_NUM_PER_PAGE);
    vis = d_frame_get_control(media_list_data->win_frm, (ID_MOVIE_LIST_BUTTON_FILENAME_0 + focus));
    old_focus = d_vis_get_focus(media_list_data->vis_group_all);
    if(vis)
    {
        if(old_focus == vis)
        {
            /* ��Ϊbutton������һ��ͼ��ؼ���������õĽ���ؼ�������ǽ��㣬��ʱ���ټ�����ʾ���ԣ�
            ��ͼ��ؼ�Ҳ�������¼�����ʾ���ԣ�����ͼ����ʾ���ܻ������⣬������������������
            ���Ƚ��������ߣ�Ȼ�����л����� @qiny 20170731*/
            //d_vis_enable(vis, D_FALSE);
            d_vis_set_focusable(vis, D_FALSE);
        }
        d_vis_show(vis, D_TRUE);
        //d_vis_enable(vis, D_TRUE);
        d_vis_set_focusable(vis, D_TRUE);
        d_vis_set_focus(vis);
    }

    return D_OK;
}

/**@brief ��ʾ�б���Ϣ*/
static D_Result
medialist_menu_show_list_info(void) D_FUNCPOSTFIT
{
    D_ID id, start;
    D_FSAttr *fattr_catalog;
    D_Visual* vis_image;
    D_Visual* vis_button;

    /* ���㵱ǰҳ��*/
    media_list_data->mediaCurrPage = media_list_data->mediaCurrFocus / MEDIA_LIST_NUM_PER_PAGE;
    start = MEDIA_LIST_NUM_PER_PAGE * media_list_data->mediaCurrPage;
    media_list_data->menuVisShowCnt = 0;
    for(id = 0; id < MEDIA_LIST_NUM_PER_PAGE; id++)
    {
        vis_image = d_frame_get_control(media_list_data->win_frm, (ID_MOVIE_LIST_IMAGE_FILEICON_0 + id));
        vis_button = d_frame_get_control(media_list_data->win_frm, (ID_MOVIE_LIST_BUTTON_FILENAME_0 + id));

        if(media_list_data->mediaCatalogRset.cnt != 0)/**��ʾ�̷�Ŀ¼*/
        {
            if((id + start) >= media_list_data->mediaCatalogRset.cnt)
            {
                /* ���������������������ļ��Ŀؼ�*/
                d_vis_set_focusable(vis_button, D_FALSE);
                //d_vis_enable(vis_button, D_FALSE);
                d_vis_show(vis_button, D_FALSE);
                d_vis_show(vis_image, D_FALSE);
            }
            else
            {
                d_vis_show(vis_image, D_TRUE);
                d_vis_show(vis_button, D_TRUE);
                if(media_list_data->menuEditFlag)
                {
                    //d_vis_enable(vis_button, D_TRUE);
                    d_vis_set_focusable(vis_button, D_TRUE);
                }
                media_list_data->menuVisShowCnt++;

                /**����Ŀ¼���ļ����ͣ�������ʾ��Ӧ��ͼ��**/

                fattr_catalog = &(media_list_data->mediaCatalogRset.ids[id + start]);
                d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_disk);
#ifndef D_SYSTEM_WIN32
                {
                    D_Size file_length;
                    file_length = strlen(fattr_catalog->path.filename);
                    p_cc_utf8_to_sys((D_U8*)media_list_data->mediaListContent[id], MEDIA_FILE_NAME_LEN, (D_U8*)fattr_catalog->path.filename, file_length);
                }
#else
                strcpy(media_list_data->mediaListContent[id], fattr_catalog->path.filename);
#endif
            }
            d_button_set_text(vis_button, media_list_data->mediaListContent[id]);
        }
        else/**��ʾ�ļ�*/
        {
            if((id + start) >= media_list_data->area_num)
            {
                /* ���������������������ļ��Ŀؼ�*/
                d_vis_set_focusable(vis_button, D_FALSE);
                //d_vis_enable(vis_button, D_FALSE);
                d_vis_show(vis_button, D_FALSE);
                d_vis_show(vis_image, D_FALSE);
            }
            else
            {
                d_vis_show(vis_image, D_TRUE);
                d_vis_show(vis_button, D_TRUE);
                if(media_list_data->menuEditFlag)
                {
                    //d_vis_enable(vis_button, D_TRUE);
                    d_vis_set_focusable(vis_button, D_TRUE);
                }
                media_list_data->menuVisShowCnt++;

                /**������ʾ��Ӧ��ͼ��**/
                d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_muise);
                music_play_analyse_name(media_list_data->mediaFileName_temp, media_list_data->fileRsetInfo[media_list_data->area_info[id + start]].path);
#ifndef D_SYSTEM_WIN32
                {
                    D_Size file_length;
                    file_length = strlen(media_list_data->mediaFileName_temp);
                    p_cc_utf8_to_sys((D_U8*)media_list_data->mediaListContent[id], MEDIA_FILE_NAME_LEN, (D_U8*)media_list_data->mediaFileName_temp, file_length);
                }
#else
                strcpy(media_list_data->mediaListContent[id], media_list_data->mediaFileName_temp);
#endif
            }
            d_button_set_text(vis_button, media_list_data->mediaListContent[id]);
        }
    }
    return D_OK;
}

/**@brief �����������Ҳ����л��ļ�����*/
static D_Result
medialist_menu_change_focus(D_U32 action_key) D_FUNCPOSTFIT
{
    D_S32 new_focus = -1;
    D_U32 num_d, page_max;
    D_U16 cnt;

    if(media_list_data->mediaCatalogRset.cnt == 0)
    {
        cnt = media_list_data->area_num;
    }
    else
    {
        cnt = media_list_data->mediaCatalogRset.cnt ;
    }
    page_max = (cnt - 1) / MEDIA_LIST_COL_CNT;
    num_d = media_list_data->mediaCurrFocus / MEDIA_LIST_COL_CNT;
    if(action_key == D_KEY_LEFT && media_list_data->mediaCurrFocus)
    {
        new_focus = ((D_S32)media_list_data->mediaCurrFocus) - 1;
    }
    else if(action_key == D_KEY_RIGHT && media_list_data->mediaCurrFocus < (cnt - 1))
    {
        new_focus = ((D_S32)media_list_data->mediaCurrFocus) + 1;
    }
    else if(action_key == D_KEY_UP && media_list_data->mediaCurrFocus >= MEDIA_LIST_COL_CNT)
    {
        new_focus = ((D_S32)media_list_data->mediaCurrFocus) - MEDIA_LIST_COL_CNT;
    }
    else if(action_key == D_KEY_DOWN)
    {
        new_focus = ((D_S32)media_list_data->mediaCurrFocus) + MEDIA_LIST_COL_CNT;
        if(new_focus >= cnt && page_max != num_d)
        {
            new_focus = ((D_S32)cnt) - 1;
        }
    }

    /* ��Ч�����л�*/
    if(new_focus >= 0 && new_focus < cnt)
    {
        media_list_data->mediaCurrFocus = (D_U32)new_focus;

        /*���㵱ǰҳ��, ҳ��仯ʱ��Ҫ�����趨ҳ������*/
        num_d = media_list_data->mediaCurrFocus / MEDIA_LIST_NUM_PER_PAGE;
        if(num_d != media_list_data->mediaCurrPage)
        {
            medialist_menu_show_list_info();
        }
        /* �趨����ؼ�*/
        medialist_menu_set_curr_focus();
        /* ��ʾ�����ļ���*/
        medialist_menu_show_file_name();
        return D_OK;
    }
    return D_ERR;
}

/** @brief ������һ��Ŀ¼*/
static D_Result
medialist_menu_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_U32 length;
    D_Char filename[4];

    length = strlen(media_list_data->mediaCatalogRset.ids[media_list_data->mediaCurrFocus].path.filename);
    p_cc_utf8_to_sys((D_U8*)filename, MEDIA_PATH_NAME_LEN, (D_U8*)media_list_data->mediaCatalogRset.ids[media_list_data->mediaCurrFocus].path.filename,length);
    media_list_data->cur_rset_num = filename[0] - 'C';
    media_list_data->area_num = p_tv_file_scan_get_typefile_by_volumes(media_list_data->cur_rset_num, &(media_list_data->fileRsetInfo), media_list_data->area_info, D_FILE_SCAN_FMT_Music);
    media_list_data->mediaLastLevelFocus = media_list_data->mediaCurrFocus;
    media_list_data->mediaCurrPartition = media_list_data->mediaVolIndexs[media_list_data->mediaCurrFocus];
    if(media_list_data->area_num == 0)
    {
        p_atv_media_prompt_msg(atv_IDS_NO_SUCH_FILE);
                return D_OK;
    }

    memset(media_list_data->mediaCatalogRset.ids, 0x00, sizeof(D_FSAttr) * (media_list_data->mediaCatalogRset.max));
    media_list_data->mediaCatalogRset.cnt = 0;


    media_list_data->mediaCurrFocus = 0;
        media_list_data->mediaMusicCurrPlaying = 0;
    media_list_data->mediaMusicPlayed = D_FALSE;

    media_list_data->mediaFocuLevel = 1;
    /* �б�������ʾ*/
    medialist_menu_show_list_info();
    /* �趨����ؼ�*/
    medialist_menu_set_curr_focus();
    /* ��ʾ�����ļ���*/
    medialist_menu_show_file_name();

    return D_OK;
}

/**@brief ���ҷ�����һ��Ŀ¼ʱ����ֵ*/
static D_ID
medialist_menu_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_list_data->mediaFocuLevel)
    {
        media_list_data->mediaFocuLevel--;
        media_list_data->mediaCurrFocus = media_list_data->mediaLastLevelFocus;
    }
    return D_OK;
}

/** @brief ������һ��Ŀ¼*/
static D_Result
medialist_menu_return_up_folder( void )D_FUNCPOSTFIT
{
    media_music_stop_play();
    medialist_menu_get_last_focus();
    medialist_menu_get_catalog_list();
    media_list_data->cur_rset_num = 0xFF;
    media_list_data->mediaCurrPartition = 0xFF;
    media_list_data->mediaMusicCurrPlaying = 0;
    media_list_data->mediaMusicPlayed = D_FALSE;
    media_list_data->fileRsetInfo = NULL;
    /* �б�������ʾ*/
    medialist_menu_show_list_info();
    /* �趨����ؼ�*/
    medialist_menu_set_curr_focus();
    /* ��ʾ�����ļ���*/
    medialist_menu_show_file_name();
    return D_OK;

}

static D_Result
media_show_curr_info(D_Bool show) D_FUNCPOSTFIT
{
    if(show)
    {
        D_Size file_length;

#ifndef D_SYSTEM_WIN32
        file_length = strlen(media_list_data->fileRsetInfo[media_list_data->area_info[media_list_data->mediaCurrFocus]].path);
        p_cc_utf8_to_sys((D_U8*)media_list_data->mediaFileName, MEDIA_FILE_NAME_LEN, \
        (D_U8*)media_list_data->fileRsetInfo[media_list_data->area_info[media_list_data->mediaCurrFocus]].path, file_length);
#else
        strcpy(media_list_data->mediaFileName, media_list_data->fileRsetInfo[media_list_data->area_info[media_list_data->mediaCurrFocus]].path);
#endif
    }
    d_label_set_text(media_list_data->vis_music_name, show ? media_list_data->mediaFileName : NULL);
    return D_OK;
}


/**@brief ֹͣ�������е���Դ*/
static D_Result
media_music_stop_play(void) D_FUNCPOSTFIT
{
    d_vis_show(media_list_data->vis_group_play, D_FALSE);
    media_set_play_status(MEDIA_MUSIC_STOP_STATUS);
    media_show_curr_time(MEDIA_MUSIC_TIME_RESET);
    media_show_curr_info(D_FALSE);
    return D_OK;
}

/** @brief ����ָ���ļ����ĺ�׺�Ƿ�Ϊָ���ĺ�׺
* @retval D_TRUE:���ҳɹ���D_FALSE:����ʧ��û�ҵ�
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
        if (strcasecmp(file_fmt_prv, postfix) == 0)
        {
            return D_TRUE;
        }
    }
    return D_FALSE;
}

static D_Result
media_play_curr_music(D_U16 id) D_FUNCPOSTFIT
{
    media_music_stop_play();

    if(media_list_data->fileRsetInfo[media_list_data->area_info[id]].class_type == D_FILE_SCAN_FMT_Music)
    {
        media_list_data->mediaMusicCurrPlaying =  media_list_data->mediaCurrFocus;
#ifndef D_SYSTEM_WIN32
        if(D_OK == d_media_music_get_info(media_list_data->mediaCurrPathName_utf8, &media_list_data->mediaMusicFileInfo))
        {
            if(Judge_Music_postfix(media_list_data->mediaCurrPathName_utf8, "wav") && media_list_data->mediaMusicFileInfo.sample_rate == 192000)
            {
                p_atv_media_prompt_msg(atv_IDS_NOT_SUPPORT_FILE);
                return D_ERR;
            }
            if(D_OK == d_media_music_play(media_list_data->mediaCurrPathName_utf8, 0, NULL))
            {
                d_vis_show(media_list_data->vis_group_play, D_TRUE);
                media_set_play_status(MEDIA_MUSIC_START_STATUS);
                media_show_curr_time(MEDIA_MUSIC_TIME_START);
                media_show_curr_info(D_TRUE);
                media_list_data->mediaMusicPlayed = D_TRUE;
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


/** @brief ȷ�ϲ�������*/
static D_Result
medialist_menu_ok_action (void) D_FUNCPOSTFIT
{
    D_U8 status = 0;

    if(media_list_data->mediaCatalogRset.cnt != 0)
    {
        medialist_menu_enter_next_folder(); /* ������һ��*/
    }
    else
    {
        if(media_list_data->fileRsetInfo[media_list_data->area_info[media_list_data->mediaCurrFocus]].class_type == D_FILE_SCAN_FMT_Music)
        {
            status = d_media_music_get_status();
            if(media_list_data->mediaMusicCurrPlaying == media_list_data->mediaCurrFocus)
            {
                if(status == MUSIC_STATUS_RUN)
                {
                    media_set_play_status(MEDIA_MUSIC_PAUSE_STATUS);
                }
                else if(status == MUSIC_STATUS_PAUSE)
                {
                    media_set_play_status(MEDIA_MUSIC_PLAYING_STATUS);
                }
                else
                {
                    media_set_play_status(MEDIA_MUSIC_START_STATUS);
                    media_play_curr_music(media_list_data->mediaCurrFocus);
                }
            }
            else
            {
                media_play_curr_music(media_list_data->mediaCurrFocus);
            }
        }
    }
    return D_OK;
}

/** @brief USB������Ƴ�ʱ������̷���Ŀ¼ �б�*/
static D_Result
medialist_menu_check_disk(D_Bool plug, D_U32 vol) D_FUNCPOSTFIT
{
    D_U32 usb_status;

    medialist_menu_get_catalog_list();
    if (!plug)
    {
        /* �γ�usbʱ�ж��ǵ�ǰ�������˳��˵�*/
        if((D_U32)media_list_data->mediaCurrPartition == vol)
        {
            media_music_stop_play();
            d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
             p_media_main_menu_set_enable(D_TRUE);
            return D_OK;
        }
    }
    usb_status = (D_U32)p_get_curr_usb_status();
    if(media_list_data->sysUsbStatus == usb_status)
    {
        return D_OK;
    }
    media_list_data->sysUsbStatus = usb_status;

    /* ���̽���ʱ�����usb��ˢ�´�����ʾ*/
    if(media_list_data->mediaFocuLevel == 0)
    {
        //media_list_data->mediaCurrPartition = 0xFF;
        media_list_data->mediaCurrFolder_utf8[0] = '\0';
        media_list_data->mediaCurrFocus = D_MIN(media_list_data->mediaCurrFocus, (D_U32)(media_list_data->mediaCatalogRset.cnt - 1));
        /* û���̷�ʱ��������ʾ*/
        if(media_list_data->mediaTotalPartition == 0)
        {
            d_vis_show(media_list_data->vis_group_all, D_FALSE);
            medialist_menu_set_edit_status(D_FALSE);
            p_media_main_menu_set_enable(D_TRUE);
            return D_OK;
        }
        else
        {
            d_vis_show(media_list_data->vis_group_all, D_TRUE);
        }
        
        /* �б�������ʾ*/
        medialist_menu_show_list_info();
        /* �趨����ؼ�*/
        if(media_list_data->menuEditFlag)
        {
            medialist_menu_set_curr_focus();
        }
        /* ��ʾ�����ļ���*/
        medialist_menu_show_file_name();
    }
     else
    {
        if(((D_U32)media_list_data->mediaCurrPartition > vol) &&( !plug))
        {
            media_list_data->mediaLastLevelFocus--;
        }
    }
    return D_OK;
}

/** @brief �趨�˵��Ƿ��ѡ��״̬*/
static D_Result
medialist_menu_set_edit_status(D_Bool edit) D_FUNCPOSTFIT
{
    D_Visual* vis;
    D_ID id, cnt;

    if(media_list_data->menuEditFlag != edit)
    {
        media_list_data->menuEditFlag = edit;
        cnt = (edit) ? media_list_data->menuVisShowCnt : MEDIA_LIST_NUM_PER_PAGE;
        for(id = 0; id < cnt; id++)
        {
            vis = d_frame_get_control(media_list_data->win_frm, ID_MOVIE_LIST_BUTTON_FILENAME_0 + id);
            if(vis)
            {
                //d_vis_enable(vis, edit);
                d_vis_set_focusable(vis, edit);
            }
        }
        if(edit)
        {
            media_list_data->mediaCurrFocus  = 0;
            /* �趨����ؼ�*/
            medialist_menu_set_curr_focus();
        }
    }
    return D_OK;
}

/** @brief �����¼�����ص�*/
static D_Result
medialist_menu_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                media_list_data->mediaMenuCurrLang = evt->user.param2;
                d_gui_update();
            }
            break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    if(media_list_data->menuEditFlag)
                    {
                        if(media_list_data->mediaFocuLevel == 0)
                        {
                            /* �̷�Ŀ¼ʱ�����ؼ������������õ���ý�����˵���*/
                            medialist_menu_set_edit_status(D_FALSE);
                            p_media_main_menu_set_enable(D_TRUE);
                        }
                        else
                        {
                            medialist_menu_return_up_folder();
                        }
                    }
                    return D_OK;
                case D_KEY_GREEN:
                    media_list_data->mediaMusicPlayMode++;
                    if(media_list_data->mediaMusicPlayMode == 4)
                    {
                        media_list_data->mediaMusicPlayMode = 0;
                    }
                    d_label_set_text(media_list_data->vis_play_mode, d_gui_get_text(play_mode_text[media_list_data->mediaMusicPlayMode]));
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    if(media_list_data->menuEditFlag)
                    {
                        medialist_menu_change_focus(D_KEY_UP); /* �����ƶ�*/
                    }
                    else
                    {
                        /* δ��Ծʱ���ϼ������������õ��˲˵���*/
                        medialist_menu_set_edit_status(D_TRUE);
                        p_media_main_menu_set_enable(D_FALSE);
                    }
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(media_list_data->menuEditFlag)
                    {
                        if(D_OK != medialist_menu_change_focus(D_KEY_DOWN))/* �����ƶ�*/
                        {
                            /* �̷�Ŀ¼ʱ�������µ���ĩβ�����������õ���ý�����˵���*/
                            if(media_list_data->mediaFocuLevel == 0)
                            {
                                medialist_menu_set_edit_status(D_FALSE);
                                p_media_main_menu_set_enable(D_TRUE);
                            }
                        }
                    }
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(media_list_data->menuEditFlag)
                    {
                        medialist_menu_change_focus(D_KEY_LEFT);/* �����ƶ�*/
                    }
                    else
                    {
                        return D_ERR; /* �����ö�ý�����˵����մ˼�*/
                    }
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(media_list_data->menuEditFlag)
                    {
                        medialist_menu_change_focus(D_KEY_RIGHT);/* �����ƶ�*/
                    }
                    else
                    {
                        return D_ERR; /* �����ö�ý�����˵����մ˼�*/
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(media_list_data->menuEditFlag)
                    {
                        medialist_menu_ok_action(); /* ȷ�ϲ���*/
                    }
                    else
                    {
                        /* δ��Ծʱ��OK�������������õ��˲˵���*/
                        medialist_menu_set_edit_status(D_TRUE);
                        p_media_main_menu_set_enable(D_FALSE);
                    }
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == media_list_data->mediaMusicTimer)
            {
                status = d_media_music_get_status();
                if(status == MUSIC_STATUS_RUN)
                {
                    media_show_curr_time(MEDIA_MUSIC_TIME_UPDATE);
                }
                else if((status == MUSIC_STATUS_STOP) && (media_list_data->mediaMusicPlayed == D_TRUE))
                {
                    D_ID file_id;
                    file_id = media_find_next_by_play_mode(media_list_data->mediaMusicPlayMode);
                    if(file_id >= 0)
                    {
                        //media_music_data->mediaMusicCurrPlaying = file_id;
                        media_list_data->mediaCurrFocus = file_id;
                        medialist_menu_set_curr_focus();
                        medialist_menu_show_file_name();
                        media_play_curr_music(file_id);
                    }
                    else
                    {
                        //��Ϊ˳�򲥷���Ƶ�ʱ���ǵ����������һ���ǲ�����ѭ�����ŵ�һ���ġ�
                        //��ʱ���ֵ�״̬λSTOP�������ٰ���ʱ���޷����ŵ�ǰ��,���������⴦��
                    }
                }
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            medialist_menu_check_disk(evt->hotplug.plug, (D_U32)evt->hotplug.arg);
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            AtvMediaMenuStatus &= ~uCurrentMenuTpe;
            if(media_list_data->mediaMusicTimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(media_list_data->mediaMusicTimer);
                media_list_data->mediaMusicTimer = D_INVALID_HANDLE;
            }
            if(media_list_data)
            {
                PROJECT_FREE(media_list_data->mediaCatalogRset.ids);
                PROJECT_FREE(media_list_data);
                media_list_data = NULL;
            }
            d_media_music_stop() ;
            d_media_music_close();
        }
        break;
    }
    return D_ERR;
}

/** @brief ���ڳ�ʼ��*/
D_Result
music_list_menu_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_list_data = (D_MediaMuiseListMenuData*)PROJECT_ALLOC(sizeof(D_MediaMuiseListMenuData));
    if(!media_list_data)
    {
        return D_ERR;
    }

    memset(media_list_data, 0x00, sizeof(D_MediaMuiseListMenuData));
    media_list_data->mediaCurrPartition = 0xFF;
    media_list_data->cur_rset_num = 0xFF;
    media_list_data->mediaCurrFocus = 0;
    media_list_data->mediaCurrPage = 0;
    media_list_data->area_num  = 0;
    media_list_data->mediaCurrFocus = 0;
    media_list_data->menuEditFlag = D_TRUE;
    media_list_data->mediaExitFullScreenFlag = D_FALSE;
    media_list_data->mediaMenuCurrLang = p_conf_get_lang();
    media_list_data->win_frm = frm;
    media_list_data->vis_group_all = d_frame_get_control(frm, ID_MOVIE_LIST_GROUP_ALL);
    media_list_data->vis_file_name = d_frame_get_control(frm, ID_MOVIE_LIST_LABEL_FILENAME);

    media_list_data->mediaCatalogRset.max = MEDIA_PARTITION_MAX_CNT;
    media_list_data->mediaCatalogRset.cnt = 0;
    media_list_data->mediaCatalogRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_list_data->mediaCatalogRset.max));
    if(!media_list_data->mediaCatalogRset.ids)
    {
        return D_ERR;
    }
    /*��ʼ����ý������ƵͼƬ�ĸ��ԵĲ�������*/
    d_mediacodec_open();
    d_media_music_open() ;

    /*���農��/����/����*/
    p_stb_reset_mute_track_volume();

    media_list_data->mediaMusicLrCbmanHandle = D_INVALID_HANDLE;
    media_list_data->vis_play_status = d_frame_get_control(frm, ID_MUSIC_IMG_PLAY_STATUS);
    media_list_data->vis_show_status = d_frame_get_control(frm, ID_MUSIC_LABEL_STATUS);
    media_list_data->vis_play_time = d_frame_get_control(frm, ID_MUSIC_LABEL_TIME);
    media_list_data->vis_music_name = d_frame_get_control(frm, ID_MUSIC_LABEL_SONG_NAME);
    media_list_data->vis_progress = d_frame_get_control(frm, ID_MUSIC_PROGRESS);
    media_list_data->vis_lrc = d_frame_get_control(frm, ID_MUSIC_LABEL_LYRIC);
    media_list_data->vis_play_mode = d_frame_get_control(frm, ID_MUSIC_PLAY_MODE_0);
    media_list_data->vis_group_play = d_frame_get_control(frm, ID_MUSIC_GROUP_ALL);
    media_list_data->mediaMusicPlayMode = MEDIA_MUSIC_LIST_LOOP;
    media_list_data->mediaMusicPlayed = D_FALSE;

    d_vis_show(media_list_data->vis_group_play, D_FALSE);
    vis = d_frame_get_control(frm, ID_MOVIE_LIST_GROUP_ALL);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_group_set_focus_loop (vis, D_FALSE);
    }

    vis = d_frame_get_control(frm, ID_MOVIE_LIST_GROUP_FILES);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_group_set_focus_loop (vis, D_FALSE);
    }

    media_list_data->mediaMusicTimer = d_timer_create(NULL, MEDIA_REFRESH_TIME, d_gui_get_queue());

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        if(media_list_data->mediaMusicTimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, media_list_data->mediaMusicTimer);
        }
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt(vis, D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        //d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, medialist_menu_window_handler);
    }

    media_list_data->sysUsbStatus = p_get_curr_usb_status();
    /**�õ�Ŀ¼�б�*/
    medialist_menu_get_catalog_list();
    /* û���̷�ʱ��������ʾ*/
    if(media_list_data->mediaTotalPartition == 0)
    {
        d_vis_show(media_list_data->vis_group_all, D_FALSE);
    }
    media_list_data->mediaFocuLevel = 0;

    medialist_menu_set_edit_status(D_FALSE);
    medialist_menu_show_list_info();
    medialist_menu_show_file_name();

    if(media_list_data->mediaMusicLrCbmanHandle == D_INVALID_HANDLE)
    {
        media_list_data->mediaMusicLrCbmanHandle = d_cbman_subscribe(PL_GUI_IDLE, D_INVALID_HANDLE, media_update_lrc_handler, NULL);
    }

    d_label_set_text(media_list_data->vis_play_mode, d_gui_get_text(atv_IDS_LIST_LOOP));

    media_music_stop_play();

    AtvMediaMenuStatus |= uCurrentMenuTpe;
    return D_OK;
}


/** @brief ��ʾ��ý�������б�˵�*/
D_Result
p_atv_media_music_show (void) D_FUNCPOSTFIT
{
    if(d_frame_is_loaded(&music_list_menu_window))
    {
        return D_OK;
    }
    uCurrentMenuTpe = ATV_MEDIA_MENU_STATUS_MUSIC;
    D_DUMP("p_atv_media_music_show \n");
    return d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &music_list_menu_window, D_CLEAR_NONE);
}
