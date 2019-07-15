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
#include "pConfig.h"

#include "atv_media_pvr_window.c"

#define MediaPvrFolder  "AVDATA"

#define MEDIA_PVR_FOLDER_LEVEL_MAX (10)
#define MEDIA_PVR_LIST_ROW_CNT  (6)
#define MEDIA_PVR_PARTITION_MAX_CNT (24)
#define MEDIA_PVR_BUFFER_SIZE  (64)
#define MEDIA_PVR_MAX_NUM_CNT  (1000)
#define MEDIA_PVR_FILE_NAME_LEN   D_PATH_LENGTH
#define MEDIA_PVR_FOLDER_PATH_LEN D_PATH_LENGTH

typedef struct
{
    D_Char  mediaPvrChannelNum[MEDIA_PVR_LIST_ROW_CNT][MEDIA_PVR_BUFFER_SIZE];
    D_Char  mediaPvrCurrFolder_utf8[MEDIA_PVR_FOLDER_PATH_LEN];
    D_Char  mediaPvrListShowData[MEDIA_PVR_LIST_ROW_CNT][MEDIA_PVR_FILE_NAME_LEN];
    D_Char  mediaPvrChannelName[MEDIA_PVR_LIST_ROW_CNT][MEDIA_PVR_FILE_NAME_LEN];
    D_Char  mediaPvrFolderShowName[MEDIA_PVR_LIST_ROW_CNT][MEDIA_PVR_FILE_NAME_LEN];//文件夹显示的名字
    D_Char  mediaPvrTempData[MEDIA_PVR_FILE_NAME_LEN];

    D_U16   mediaPvrFocuStack[MEDIA_PVR_FOLDER_LEVEL_MAX];/*焦点栈，记录各级文件夹焦点*/
    D_U32   mediaPvrFocuLevel;  /*文件级数*/

    /**磁盘信息*/
    D_Int   mediaPvrTotalPartition;                           /*总的磁盘数**/
    D_U8    mediaPvrVolIndex[MEDIA_PVR_PARTITION_MAX_CNT];  /*总共的盘符数**/
    D_U8    mediaPvrCurrPartition;                        /*当前的盘符**/

    /*文件记录就指针**/
    D_FileScan mediaPvrFileRset;

    D_U8    mediaPvrCurrLang;

    D_VidWindow  MediaPvrPrevieWin;
    D_PvrInfo    MediaPvrInfo;

    D_U16   mediaPvrCurrListFocus;        /*当前行的聚焦号**/
    D_Bool mediaPvrfullPlay;
    D_Visual* vis_list, *vis_pvr_logo, *vis_file_name, *vis_play_win;
} MediaPvrData;

static MediaPvrData* pvr_data = NULL;

static D_FILE_TYPE media_pvr_type[] =
{
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
    D_FILE_TYPE_HTS,
};



/**@brief 按时间排序pvr文件列表*/
D_Result sort_pvr_file(D_FileScan *fs)
{
    D_U32 i = 0, j = 0, k = 0;
    char * point_pos = NULL;
    D_FileScan temp_fs;
    D_FSAttr temp_ids;
    char temp_path[D_PATH_LENGTH];
    D_U32 cur_start_i = 1;
    if(fs->cnt <= 1)
    {
        D_DUMP("No pvr file !\n");
        return D_OK;
    }
    temp_fs.cnt = fs->cnt;
    temp_fs.max = fs->max;
    temp_fs.ids = (D_FSAttr*) PROJECT_ALLOC ( temp_fs.cnt * sizeof (D_FSAttr));
    memset(temp_fs.ids, 0x00, sizeof(D_FSAttr) * temp_fs.cnt);
    memcpy(temp_fs.ids, fs->ids, ( temp_fs.cnt * sizeof (D_FSAttr)));
    for(i = 1 ; i < temp_fs.cnt ; i ++)
    {
        cur_start_i = i;
        memset(temp_path, 0x00, sizeof(temp_path));
        memcpy(temp_path, temp_fs.ids[i].path.filename, sizeof(temp_path));
        point_pos = strchr(temp_path, '_');
        if(point_pos)
            point_pos++;
        else
            return D_ERR;
        memcpy(temp_path, point_pos, 15);
        temp_path[14] = '\0';
        sprintf(temp_fs.ids[i].path.filename , "%s", temp_path);
    }
    for(j = 1; j < temp_fs.cnt; j++) /* 气泡法要排序n次*/
    {
        for(i = 1; i < temp_fs.cnt - j; i++) /* 值比较大的元素沉下去后，只把剩下的元素中的最大值再沉下去就可以啦 */
        {
            if(strcmp(temp_fs.ids[i].path.filename , temp_fs.ids[i + 1].path.filename) < 0) /* 把值比较大的元素沉到底 */
            {
                /*temp_ids 交换*/
                temp_ids = temp_fs.ids[i];
                temp_fs.ids[i] = temp_fs.ids[i + 1];
                temp_fs.ids[i + 1] = temp_ids;

                /*fs 交换*/
                temp_ids = fs->ids[i];
                fs->ids[i] = fs->ids[i + 1];
                fs->ids[i + 1] = temp_ids;
            }
        }
    }
    PROJECT_FREE(temp_fs.ids);
    temp_fs.ids = NULL;
    return D_OK;
}


static D_Result
media_pvr_show_file_info(D_Bool show) D_FUNCPOSTFIT
{
    d_label_set_text(pvr_data->vis_file_name, (show ? (pvr_data->mediaPvrFolderShowName[pvr_data->mediaPvrCurrListFocus % MEDIA_PVR_LIST_ROW_CNT]) : NULL));
    return D_OK;
}

/**@brief 停止播放所有的资源*/
static D_Result
media_pvr_stop_play(void) D_FUNCPOSTFIT
{
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
    d_media_pvr_stop();
    media_pvr_show_file_info(D_FALSE);
    return D_OK;
}



/**@brief 得到路径下的文件列表*/
static D_Result
media_pvr_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        memset(pvr_data->mediaPvrFileRset.ids, 0x00, sizeof(D_FSAttr) * pvr_data->mediaPvrFileRset.max);
        pvr_data->mediaPvrFileRset.max = MEDIA_PVR_MAX_NUM_CNT;
        pvr_data->mediaPvrFileRset.cnt = 0;

        //p_file_scan_get_current_dir(curr_path, &pvr_data->mediaPvrFileRset, media_pvr_type, sizeof(media_pvr_type) / sizeof(media_pvr_type[0]), D_FILE_MATCH_MODE_FILETYPE);
        p_file_scan_get_files_by_type(curr_path, &pvr_data->mediaPvrFileRset, media_pvr_type, sizeof(media_pvr_type) / sizeof(media_pvr_type[0]), D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        pvr_data->mediaPvrFileRset.cnt = 0;
        pvr_data->mediaPvrFileRset.max = MEDIA_PVR_PARTITION_MAX_CNT;
        pvr_data->mediaPvrTotalPartition = 0;
        d_fsm_get_volumes(pvr_data->mediaPvrVolIndex, &pvr_data->mediaPvrTotalPartition);
        memset(pvr_data->mediaPvrFileRset.ids, 0x00, sizeof(D_FSAttr) * pvr_data->mediaPvrFileRset.max);

        p_file_scan_get_all_partitons(&pvr_data->mediaPvrFileRset, pvr_data->mediaPvrVolIndex, pvr_data->mediaPvrTotalPartition);
    }
    sort_pvr_file(&pvr_data->mediaPvrFileRset);

    return D_OK;
}

static D_Result
media_pvr_analyse_ts_name(D_ID row, char* file_name) D_FUNCPOSTFIT
{

    memset(pvr_data->mediaPvrTempData, 0x00, sizeof(pvr_data->mediaPvrTempData));
    memcpy(pvr_data->mediaPvrTempData, file_name, strlen(file_name));

    if((pvr_data->mediaPvrTempData != NULL) && (strlen(pvr_data->mediaPvrTempData) == 2))
    {
        memset(pvr_data->mediaPvrChannelName[row], 0x00, sizeof(pvr_data->mediaPvrChannelName[row]));
        memcpy(pvr_data->mediaPvrChannelName[row], pvr_data->mediaPvrTempData, sizeof(pvr_data->mediaPvrTempData));
        memset(pvr_data->mediaPvrFolderShowName[row], 0x00, sizeof(pvr_data->mediaPvrFolderShowName[row]));
        return D_OK;
    }


    if(pvr_data->mediaPvrTempData != NULL)
    {
        char* temp = NULL;
        char* ch_pos = NULL;
        D_Char str_year[8] = {0}, str_month[4] = {0}, str_date[4] = {0};
        D_Char str_hour[4] = {0}, str_min[4] = {0}, str_sec[4] = {0};

        ch_pos = strrchr(pvr_data->mediaPvrTempData, '/');
        if(ch_pos)
            ch_pos++;
        else
            return D_ERR;


        temp = strchr(ch_pos, '.');
        if(temp)
            *temp = '\0';
        else
            return D_ERR;

        memset(pvr_data->mediaPvrChannelName[row], 0x00, sizeof(pvr_data->mediaPvrChannelName[row]));
        memcpy(pvr_data->mediaPvrChannelName[row], ch_pos, strlen(ch_pos));

        ch_pos -= 1;
        *ch_pos = '\0';
        ch_pos = strrchr(pvr_data->mediaPvrTempData, '/');
        if(ch_pos)
        {
            ch_pos++;
            temp = strrchr(ch_pos, '_');
            if(temp && (strlen(temp) == 15))
            {
                *temp = '\0';
                temp++;
                memcpy(str_year, &temp[0], 4);
                memcpy(str_month, &temp[4], 2);
                memcpy(str_date, &temp[6], 2);
                memcpy(str_hour, &temp[8], 2);
                memcpy(str_min, &temp[10], 2);
                memcpy(str_sec, &temp[12], 2);
                /* 记录utf8的文件夹名*/
                sprintf(pvr_data->mediaPvrFolderShowName[row], "%s  %s.%s.%s %s:%s:%s",
                        ch_pos, str_year, str_month, str_date, str_hour, str_min, str_sec);
                /* 转换*/
#ifndef D_SYSTEM_WIN32
                memcpy(pvr_data->mediaPvrTempData, pvr_data->mediaPvrFolderShowName[row], sizeof(pvr_data->mediaPvrChannelName[row]));
                memset(pvr_data->mediaPvrFolderShowName[row], 0x00, sizeof(pvr_data->mediaPvrFolderShowName[row]));
                p_cc_utf8_to_sys((D_U8*)pvr_data->mediaPvrFolderShowName[row], MEDIA_PVR_FILE_NAME_LEN, \
                                 (D_U8*)pvr_data->mediaPvrTempData, strlen(pvr_data->mediaPvrTempData));
#endif
            }
        }
        return D_OK;
    }

    return D_ERR;
}

/**@brief 更新列表显示*/
static D_Result
media_pvr_list_info_show(void) D_FUNCPOSTFIT
{
    D_ID start, i, row;
    D_ImageID img_id;
    D_Image* img;
    D_Size   file_length;

    start = d_list_get_first_line_id(pvr_data->vis_list);
    for(i = start; i < start + MEDIA_PVR_LIST_ROW_CNT; i++)
    {
        if(i >= pvr_data->mediaPvrFileRset.cnt)
        {
            d_list_set_image(pvr_data->vis_list, i, 0, NULL);
            d_list_set_text(pvr_data->vis_list,  i, 0, NULL);
            d_list_set_text(pvr_data->vis_list,  i, 1, NULL);
        }
        else
        {
            row = i - start;

            if(pvr_data->mediaPvrFileRset.ids[i].class_type == D_FILE_SCAN_FMT_Device)
            {
                d_list_set_image(pvr_data->vis_list, i, 0, d_gui_get_image(atv_IMG_ID_media_disk));
            }
            else if(pvr_data->mediaPvrFileRset.ids[i].class_type == D_FILE_SCAN_FMT_UpDir)
            {
                d_list_set_text(pvr_data->vis_list, i, 0, NULL);
                d_list_set_image(pvr_data->vis_list, i, 0, d_gui_get_image(atv_IMG_ID_music_select_up_level));
            }
            else
            {
                sprintf(pvr_data->mediaPvrChannelNum[row], "%03d", i);
                d_list_set_image(pvr_data->vis_list, i, 0, NULL);
                d_list_set_text(pvr_data->vis_list, i, 0, pvr_data->mediaPvrChannelNum[row]);
            }

            media_pvr_analyse_ts_name(row, pvr_data->mediaPvrFileRset.ids[i].path.filename);

#ifndef D_SYSTEM_WIN32
            file_length = strlen(pvr_data->mediaPvrChannelName[row]);
            p_cc_utf8_to_sys((D_U8*)pvr_data->mediaPvrListShowData[row], MEDIA_PVR_FILE_NAME_LEN, \
                             (D_U8*)pvr_data->mediaPvrChannelName[row], file_length);
#else
            strcpy(pvr_data->mediaPvrListShowData[row], pvr_data->mediaPvrChannelName[row]);
#endif

            d_list_set_text(pvr_data->vis_list, i, 1, pvr_data->mediaPvrListShowData[row]);
        }
    }

    return D_OK;
}


/**@brief 查找返回上一级目录时焦点值*/
static D_ID
media_pvr_get_last_focus(void)D_FUNCPOSTFIT
{
    if(pvr_data->mediaPvrFocuLevel)
    {
        pvr_data->mediaPvrFocuLevel--;
        return pvr_data->mediaPvrFocuStack[pvr_data->mediaPvrFocuLevel];
    }

    return D_OK;
}

/** @brief 进入下一级目录*/
static D_Result
media_pvr_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;
    D_U32 length;
    D_Char curr_device[16] = "C:/AVDATA";

    focus = d_list_get_focus(pvr_data->vis_list, NULL, NULL);

    if(pvr_data->mediaPvrFileRset.ids[focus].type == 0  &&  focus < pvr_data->mediaPvrFileRset.cnt)
    {
        if(pvr_data->mediaPvrFocuLevel < MEDIA_PVR_FOLDER_LEVEL_MAX)
        {
            if(0 == pvr_data->mediaPvrFocuLevel)
            {
                pvr_data->mediaPvrCurrPartition = pvr_data->mediaPvrVolIndex[focus];
            }
            pvr_data->mediaPvrFocuStack[pvr_data->mediaPvrFocuLevel++] = focus;
        }

        curr_device[0] = pvr_data->mediaPvrCurrPartition + 'C';
        sprintf(pvr_data->mediaPvrCurrFolder_utf8, "%s", curr_device);

        media_pvr_get_files_list(pvr_data->mediaPvrCurrFolder_utf8);
        d_list_set_max_row(pvr_data->vis_list, pvr_data->mediaPvrFileRset.cnt);
        d_list_set_focus(pvr_data->vis_list, 0, (D_U16) - 1);
        media_pvr_list_info_show();
        return D_OK;
    }

    return D_ERR;
}

/** @brief 返回上一级目录*/
static D_Result
media_pvr_return_up_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;

    if(pvr_data->mediaPvrCurrFolder_utf8[0])
    {
        pvr_data->mediaPvrCurrFolder_utf8[0] = '\0';
        media_pvr_get_files_list(pvr_data->mediaPvrCurrFolder_utf8);

        d_list_set_max_row(pvr_data->vis_list, pvr_data->mediaPvrFileRset.cnt);

        focus = (D_S16)media_pvr_get_last_focus();
        d_list_set_focus(pvr_data->vis_list, focus, (D_U16) - 1);

        media_pvr_list_info_show();
        return D_OK;
    }
    else
    {
        media_pvr_stop_play();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_ERR;
}

static D_Result
media_pvr_preview_curr_pro(void) D_FUNCPOSTFIT
{
    D_FSAttr *fsattr;
    fsattr = &(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus]);

    if(Judge_PVR_File(fsattr))
    {
        /*设置视频位置*/
        d_av_set_vid_window(0, pvr_data->MediaPvrPrevieWin.x, pvr_data->MediaPvrPrevieWin.y, pvr_data->MediaPvrPrevieWin.w, pvr_data->MediaPvrPrevieWin.h);

        /*得到视频的信息*/
        //if (D_OK == (d_pvr_rep_get_pvr_info(fsattr->path.fullpath, &pvr_data->MediaPvrInfo)))
        {
            /*播放视频*/
            if(D_OK == d_media_pvr_play(fsattr->path.fullpath))
            {
                /*显示视频信息*/
//               d_av_set_vid_blank(0, D_FALSE); /*黑屏*/
                media_pvr_show_file_info(D_TRUE);
                return D_OK;
            }

        }
    }

    return D_ERR;
}

static D_Result
media_pvr_fullscreen_hide_handler(D_U16 focus)D_FUNCPOSTFIT
{
    if(pvr_data)
    {
        media_pvr_stop_play();
        pvr_data->mediaPvrfullPlay = D_FALSE;
        if(pvr_data->mediaPvrCurrListFocus != focus)
        {
            pvr_data->mediaPvrCurrListFocus = focus;
            d_list_set_focus(pvr_data->vis_list, focus, (D_U16) - 1);
        }
        media_pvr_preview_curr_pro();
    }
    return D_OK;
}


static D_Result
media_pvr_del_file_handler(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    D_ID focus;
    D_Result ret;
    char* point_pos = NULL;
    D_Char curr_device[16] = "C:/AVDATA";
    D_Char temp_path_name[MEDIA_PVR_FILE_NAME_LEN];

    if(!pvr_data)
    {
        return D_ERR;
    }

    pvr_data->mediaPvrfullPlay = D_FALSE;

    if(sel)
    {
        media_pvr_stop_play();

        /*先找到要删除的文件*/
        focus = d_list_get_focus(pvr_data->vis_list, NULL, NULL);
        if(focus < 0 || focus > pvr_data->mediaPvrFileRset.cnt)
        {
            return D_ERR;
        }

        memcpy(temp_path_name, pvr_data->mediaPvrFileRset.ids[focus].path.filename, sizeof(temp_path_name));

        point_pos = strrchr(temp_path_name, '/');
        if(point_pos)
            sprintf(point_pos , "%c", '\0');
        else
            return D_ERR;

        ret = d_fsm_dir_delete(temp_path_name);
        if(ret == 0)
        {
            curr_device[0] = pvr_data->mediaPvrCurrPartition + 'C';
            sprintf(pvr_data->mediaPvrCurrFolder_utf8, "%s", curr_device);

            media_pvr_get_files_list(pvr_data->mediaPvrCurrFolder_utf8);
            d_list_set_max_row(pvr_data->vis_list, pvr_data->mediaPvrFileRset.cnt);

            if(focus >= pvr_data->mediaPvrFileRset.cnt)
            {
                focus = (pvr_data->mediaPvrFileRset.cnt > 1)? 1 : 0;
            }
            
            d_list_set_focus(pvr_data->vis_list, focus, (D_U16) - 1);
            media_pvr_list_info_show();

            if(Judge_PVR_File(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus])))
            {
                d_gui_update();
                media_pvr_preview_curr_pro();
            }
        }

        return D_OK;
    }

    return D_ERR;
}


/** @brief 事件处理*/
static D_Result
media_pvr_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(Judge_Dir_Folder(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus])))
                    {
                        media_pvr_stop_play();
                        media_pvr_enter_next_folder();
                    }
                    else if(Judge_Up_Folder(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus])))
                    {
                        media_pvr_stop_play();
                        media_pvr_return_up_folder();
                    }
                    else if(Judge_PVR_File(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus])))
                    {
                        media_pvr_stop_play();
                        pvr_data->mediaPvrfullPlay = D_TRUE;
                        if(D_OK != p_media_pvr_full_screen_show(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus].path.filename, &pvr_data->mediaPvrFileRset , pvr_data->mediaPvrCurrListFocus, media_pvr_fullscreen_hide_handler))
                        {
                            pvr_data->mediaPvrfullPlay = D_FALSE;
                        }
                    }
                    return D_OK;
                case D_KEY_DOWN:
                case D_KEY_UP:
                case D_KEY_PNL_D:
                case D_KEY_PNL_U:
                    media_pvr_stop_play();
                    if(Judge_PVR_File(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus])))
                    {
                        media_pvr_preview_curr_pro();
                    }
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_DATA_CHANGED:
            media_pvr_list_info_show();
            break;
        case D_EVT_SELECTED:
            pvr_data->mediaPvrCurrListFocus = d_list_get_focus(vis, NULL, NULL);
            break;
    }
    return D_ERR;
}

static D_Result
media_pvr_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                pvr_data->mediaPvrCurrLang = evt->user.param2;
                if(D_LANG_CHN == evt->user.param2)
                {
                    d_image_box_set_image(pvr_data->vis_pvr_logo, d_gui_get_image(atv_IMG_ID_pvr_title_ch));
                }
                else
                {
                    d_image_box_set_image(pvr_data->vis_pvr_logo, d_gui_get_image(atv_IMG_ID_pvr_title_en));
                }


                d_vis_update(pvr_data->vis_pvr_logo, NULL);
                d_gui_update();
            }
            break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    media_pvr_stop_play();
                    media_pvr_return_up_folder();
                    return D_OK;
                case D_KEY_GREEN:
                    if(pvr_data->mediaPvrfullPlay == D_FALSE)
                    {
                        if(pvr_data->mediaPvrCurrFolder_utf8[0] && pvr_data->mediaPvrFileRset.cnt && (Judge_PVR_File(&(pvr_data->mediaPvrFileRset.ids[pvr_data->mediaPvrCurrListFocus]))))
                        {
                            d_atv_pop_select_center_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE,
                                                         NULL, d_gui_get_text(atv_IDS_DELETE_PVR_FILE), 0, D_FALSE,
                                                         media_pvr_del_file_handler, 0);
                        }
                    }
                    return D_OK;
                default:
                    break;
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
				d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
                p_media_pvr_full_screen_hide();
                media_pvr_stop_play();
                d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
            }
            break;
        case D_EVT_DESTROY:
        {
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_PVR;
            media_pvr_stop_play();
            d_vis_unsubscribe_evt (vis);
            d_av_set_vid_blank(0, D_TRUE); /*黑屏*/

            /*重设静音/声道/音量*/
            p_stb_reset_mute_track_volume();
            d_av_set_vid_window(0, 0, 0, -1, -1);
            d_av_set_vid_input (0, D_VID_IUTPUT_USB1);

            if(pvr_data)
            {
                PROJECT_FREE(pvr_data->mediaPvrFileRset.ids);
                PROJECT_FREE(pvr_data);
                pvr_data = NULL;
            }
        }
        break;
    }
    return D_ERR;
}

D_Result
atv_media_pvr_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual* vis;

    pvr_data = (MediaPvrData*)PROJECT_ALLOC(sizeof(MediaPvrData));
    if(!pvr_data)
    {
        return D_ERR;
    }

    memset(pvr_data, 0x00, sizeof(MediaPvrData));

    /*挂起DVB播放和SI监控*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/

    /*重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();


    pvr_data->vis_list = d_frame_get_control(frm, ID_MEDIA_PVR_LIST);
    pvr_data->vis_pvr_logo = d_frame_get_control(frm, ID_MEDIA_PVR_TITLE);
    pvr_data->vis_file_name = d_frame_get_control(frm, ID_MEIDA_LABEL_NAME);
    pvr_data->vis_play_win = d_frame_get_control(frm, ID_MEDIA_LABEL_SHOW);


    d_vis_get_pos(pvr_data->vis_play_win, &pvr_data->MediaPvrPrevieWin.x, &pvr_data->MediaPvrPrevieWin.y);
    pvr_data->MediaPvrPrevieWin.w = pvr_data->vis_play_win->rect.w;
    pvr_data->MediaPvrPrevieWin.h = pvr_data->vis_play_win->rect.h;

    pvr_data->mediaPvrFileRset.max = MEDIA_PVR_MAX_NUM_CNT;
    pvr_data->mediaPvrFileRset.cnt = 0;
    pvr_data->mediaPvrFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (pvr_data->mediaPvrFileRset.max));
    if(!pvr_data->mediaPvrFileRset.ids)
    {
        return D_ERR;
    }
    d_av_set_vid_input (0, D_VID_IUTPUT_DTV);

    pvr_data->mediaPvrCurrLang = p_conf_get_lang();

    if(1 == pvr_data->mediaPvrCurrLang)
    {
        d_image_box_set_image(pvr_data->vis_pvr_logo, d_gui_get_image(atv_IMG_ID_pvr_title_ch));
    }
    else
    {
        d_image_box_set_image(pvr_data->vis_pvr_logo, d_gui_get_image(atv_IMG_ID_pvr_title_en));
    }

    media_pvr_get_files_list(pvr_data->mediaPvrCurrFolder_utf8);

    vis = d_frame_get_control(frm, ID_MEDIA_PVR_LIST);
    if(vis)
    {
        d_vis_set_focus(vis);
        d_vis_subscribe_evt(vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_pvr_list_handler);
        d_list_set_max_row(vis, pvr_data->mediaPvrFileRset.cnt);
        d_list_set_focus(pvr_data->vis_list, 0, (D_U16) - 1);
        media_pvr_list_info_show();
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_pvr_window_handler);
    }


    media_pvr_stop_play();
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_PVR;

    return D_OK;
}

D_Result
p_atv_media_pvr_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_pvr_window, D_CLEAR_ALL);
}


