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
#include "dTxt.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pConfig.h"

#include "atv_media_ebook_window.c"

#define MEDIA_EBOOK_LIST_ROW_CNT  (6)
#define MEDIA_EBOOK_FOLDER_PATH_LEN  D_PATH_LENGTH
#define MEDIA_EBOOK_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_EBOOK_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_EBOOK_MAX_NUM_CNT      (1000)
#define MEDIA_EBOOK_PARTITION_MAX_CNT (24)
#define MEDIA_EBOOK_FOLDER_LEVEL_MAX  (64)
#define MEDIA_EBOOK_FILE_BUFF_SIZE (64)

typedef struct
{
    D_Char  mediaEBookCurrFolder_utf8[MEDIA_EBOOK_FOLDER_PATH_LEN];
    D_Char  mediaEBookLastFolder_utf8[MEDIA_EBOOK_FOLDER_PATH_LEN];
    D_Char  mediaEBookCurrPathName_utf8[MEDIA_EBOOK_PATH_NAME_LEN];
    D_Char  mediaEBookCurrPathName[MEDIA_EBOOK_PATH_NAME_LEN];
    D_Char  mediaEBookListShowData[MEDIA_EBOOK_LIST_ROW_CNT][MEDIA_EBOOK_FILE_NAME_LEN];

    /**磁盘信息*/
    D_Int   mediaEBookTotalPartition;                           /*总的磁盘数**/
    D_U8    mediaEBookVolIndex[MEDIA_EBOOK_PARTITION_MAX_CNT];  /*总共的盘符数**/
    D_U8    mediaEBookCurrPartition;                        /*当前的盘符**/

    D_U16   mediaEBookFocuStack[MEDIA_EBOOK_FOLDER_LEVEL_MAX];/*焦点栈，记录各级文件夹焦点*/
    D_U32   mediaEBookFocuLevel;  /*文件级数*/
    D_U16   mediaEBookCurrListFocus;        /*当前行的聚焦号**/

    /*文件记录就指针**/
    D_FileScan mediaEBookFileRset;

    D_U8    mediaEBookCurrLang;

    D_Visual* vis_ebook_list, *vis_ebook_path_name;
} MediaEBookData;

static MediaEBookData* media_ebook_data = NULL;

static D_FILE_TYPE media_ebook_type[] =
{
    D_FILE_TYPE_EBK,
    D_FILE_TYPE_TXT,
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
};

/**@brief 停止播放所有的资源*/
static D_Result
media_ebook_stop_play(void) D_FUNCPOSTFIT
{
    d_media_ebk_stop();
    return D_OK;
}

/**@brief 根据文件类型设置相应的图片*/
static D_ImageID
media_ebook_get_img_id_by_filetype(D_FSAttr *fattr) D_FUNCPOSTFIT
{
    D_ImageID img_id = (D_ImageID) - 1;

    switch(fattr->class_type)
    {
        case D_FILE_SCAN_FMT_Dir:
            img_id = atv_IMG_ID_media_folder_file;
            break;
        case D_FILE_SCAN_FMT_UpDir:
            img_id = atv_IMG_ID_media_folder_file;
            break;
        case D_FILE_SCAN_FMT_EBK:
            img_id = atv_IMG_ID_mini_ebk;
            break;
        case D_FILE_SCAN_FMT_Txt:
            img_id = atv_IMG_ID_mini_txt;
            break;
        case D_FILE_SCAN_FMT_Device:
            img_id = atv_IMG_ID_media_folder_file;
            break;
        default:
            break;
    }

    return img_id;
}


/**@brief 更新列表显示*/
static D_Result
media_ebook_list_info_show(void) D_FUNCPOSTFIT
{
    D_ID start, i, row;
    D_ImageID img_id;
    D_Image* img;
    D_Size   file_length;

    start = d_list_get_first_line_id(media_ebook_data->vis_ebook_list);
    for(i = start; i < start + MEDIA_EBOOK_LIST_ROW_CNT; i++)
    {
        if(i >= media_ebook_data->mediaEBookFileRset.cnt)
        {
            d_list_set_image(media_ebook_data->vis_ebook_list, i, 1, NULL);
            d_list_set_text(media_ebook_data->vis_ebook_list,  i, 2, NULL);
            d_list_set_text(media_ebook_data->vis_ebook_list,  i, 3, NULL);
        }
        else
        {

            img_id = media_ebook_get_img_id_by_filetype(&(media_ebook_data->mediaEBookFileRset.ids[i]));

            img = d_gui_get_image(img_id);
            d_list_set_image(media_ebook_data->vis_ebook_list, i, 1, img);

            row = i - start;
#ifndef D_SYSTEM_WIN32
            file_length = strlen(media_ebook_data->mediaEBookFileRset.ids[i].path.filename);
            p_cc_utf8_to_sys((D_U8*)media_ebook_data->mediaEBookListShowData[row], MEDIA_EBOOK_FILE_NAME_LEN, \
                             (D_U8*)media_ebook_data->mediaEBookFileRset.ids[i].path.filename, file_length);
#else
            strcpy(media_ebook_data->mediaEBookListShowData[row], media_ebook_data->mediaEBookFileRset.ids[i].path.filename);
#endif
            d_list_set_text(media_ebook_data->vis_ebook_list, i, 2, media_ebook_data->mediaEBookListShowData[row]);
        }
    }

    return D_OK;
}

/**@brief 得到当前路径**/
static D_Result
media_ebook_get_currpath_name(void) D_FUNCPOSTFIT
{
    D_S16 focus;

    focus = d_list_get_focus(media_ebook_data->vis_ebook_list, NULL, NULL);
    if(focus < media_ebook_data->mediaEBookFileRset.cnt)
    {
        if(media_ebook_data->mediaEBookCurrFolder_utf8[0])
        {
            sprintf(media_ebook_data->mediaEBookCurrPathName_utf8, "%s/%s", media_ebook_data->mediaEBookCurrFolder_utf8, media_ebook_data->mediaEBookFileRset.ids[focus].path.filename);
        }
        else
        {
            sprintf(media_ebook_data->mediaEBookCurrPathName_utf8, "%s", media_ebook_data->mediaEBookFileRset.ids[focus].path.filename);
        }

#ifndef D_SYSTEM_WIN32
        p_cc_utf8_to_sys((D_U8*)media_ebook_data->mediaEBookCurrPathName, MEDIA_EBOOK_PATH_NAME_LEN, \
                         (D_U8*)media_ebook_data->mediaEBookCurrPathName_utf8, strlen(media_ebook_data->mediaEBookCurrPathName_utf8));
#else
        strcpy(media_ebook_data->mediaEBookCurrPathName, media_ebook_data->mediaEBookCurrPathName_utf8);
#endif

    }


    p_atv_media_device_name_map(media_ebook_data->mediaEBookCurrPathName);
    d_label_set_text(media_ebook_data->vis_ebook_path_name, media_ebook_data->mediaEBookCurrPathName);

    return D_OK;
}



/**@brief 得到路径下的文件列表*/
static D_Result
media_ebook_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        memset(media_ebook_data->mediaEBookFileRset.ids, 0x00, sizeof(D_FSAttr) * media_ebook_data->mediaEBookFileRset.max);
        media_ebook_data->mediaEBookFileRset.max = MEDIA_EBOOK_MAX_NUM_CNT;
        media_ebook_data->mediaEBookFileRset.cnt = 0;

        p_file_scan_get_current_dir(curr_path, &media_ebook_data->mediaEBookFileRset, media_ebook_type, sizeof(media_ebook_type) / sizeof(media_ebook_type[0]), D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        media_ebook_data->mediaEBookFileRset.cnt = 0;
        media_ebook_data->mediaEBookFileRset.max = MEDIA_EBOOK_PARTITION_MAX_CNT;
        media_ebook_data->mediaEBookTotalPartition = 0;
        d_fsm_get_volumes(media_ebook_data->mediaEBookVolIndex, &media_ebook_data->mediaEBookTotalPartition);
        memset(media_ebook_data->mediaEBookFileRset.ids, 0x00, sizeof(D_FSAttr) * media_ebook_data->mediaEBookFileRset.max);

        p_file_scan_get_all_partitons(&media_ebook_data->mediaEBookFileRset, media_ebook_data->mediaEBookVolIndex, media_ebook_data->mediaEBookTotalPartition);
    }

    return D_OK;
}

/** @brief取得上一文件夹路径全名utf8 与 文件夹名utf8*/
static D_Result
media_ebook_get_up_folder( void )D_FUNCPOSTFIT
{
    D_Char* temp;

    temp = strrchr(media_ebook_data->mediaEBookCurrFolder_utf8, '/');
    if(temp)
    {
        *temp = '\0';
        temp++;
        strcpy(media_ebook_data->mediaEBookLastFolder_utf8, temp);
    }
    else
    {
        media_ebook_data->mediaEBookCurrFolder_utf8[0] = '\0';
        media_ebook_data->mediaEBookLastFolder_utf8[0] = '\0';
    }

    return D_OK;
}

/**@brief 查找返回上一级目录时焦点值*/
static D_ID
media_ebook_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_ebook_data->mediaEBookFocuLevel)
    {
        media_ebook_data->mediaEBookFocuLevel--;
        return media_ebook_data->mediaEBookFocuStack[media_ebook_data->mediaEBookFocuLevel];
    }

    return D_OK;
}

/** @brief 返回上一级目录*/
static D_Result
media_ebook_return_up_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;
    if((media_ebook_data->mediaEBookCurrFolder_utf8[0] == 0x43) && (media_ebook_data->mediaEBookCurrFolder_utf8[1] == 0x3a) && (media_ebook_data->mediaEBookCurrFolder_utf8[2] == 0x00))
    {
        media_ebook_stop_play();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
        return D_ERR;
    }

    if(media_ebook_data->mediaEBookCurrFolder_utf8[0])
    {
        media_ebook_get_up_folder();
        media_ebook_get_files_list(media_ebook_data->mediaEBookCurrFolder_utf8);
        d_list_set_max_row(media_ebook_data->vis_ebook_list, media_ebook_data->mediaEBookFileRset.cnt);
        focus = (D_S16)media_ebook_get_last_focus();
        d_list_set_focus(media_ebook_data->vis_ebook_list, focus, (D_U16) - 1);
        media_ebook_list_info_show();
        media_ebook_get_currpath_name();
        if(media_ebook_data->mediaEBookFocuLevel == 0)
        {
            media_ebook_data->mediaEBookCurrPartition = 0xFF;
        }

        return D_OK;
    }
    else
    {
        media_ebook_stop_play();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_ERR;
}


/** @brief 进入下一级目录*/
static D_Result
media_ebook_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_S16 focus;
    D_U32 length;

    focus = d_list_get_focus(media_ebook_data->vis_ebook_list, NULL, NULL);
    if(media_ebook_data->mediaEBookFileRset.ids[focus].type == 0  &&  focus < media_ebook_data->mediaEBookFileRset.cnt)
    {
        if(media_ebook_data->mediaEBookFocuLevel < MEDIA_EBOOK_FOLDER_LEVEL_MAX)
        {
            if(0 == media_ebook_data->mediaEBookFocuLevel)
            {
                media_ebook_data->mediaEBookCurrPartition = media_ebook_data->mediaEBookVolIndex[focus];
            }

            media_ebook_data->mediaEBookFocuStack[media_ebook_data->mediaEBookFocuLevel++] = focus;
        }

        strcpy(media_ebook_data->mediaEBookLastFolder_utf8, media_ebook_data->mediaEBookFileRset.ids[focus].path.filename);

        length = strlen(media_ebook_data->mediaEBookCurrFolder_utf8);
        if(length)
        {
            media_ebook_data->mediaEBookCurrFolder_utf8[length] = '/';
            media_ebook_data->mediaEBookCurrFolder_utf8[length + 1] = '\0';
            strcat(media_ebook_data->mediaEBookCurrFolder_utf8, media_ebook_data->mediaEBookFileRset.ids[focus].path.filename);
        }
        else
        {
            strcpy(media_ebook_data->mediaEBookCurrFolder_utf8, media_ebook_data->mediaEBookFileRset.ids[focus].path.filename);
        }

        media_ebook_get_files_list(media_ebook_data->mediaEBookCurrFolder_utf8);
        d_list_set_max_row(media_ebook_data->vis_ebook_list, media_ebook_data->mediaEBookFileRset.cnt);
        d_list_set_focus(media_ebook_data->vis_ebook_list, 0, (D_U16) - 1);
        media_ebook_list_info_show();
        media_ebook_get_currpath_name();
        return D_OK;
    }

    return D_ERR;
}


static D_Result
media_ebook_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(Judge_Dir_Folder(&(media_ebook_data->mediaEBookFileRset.ids[media_ebook_data->mediaEBookCurrListFocus])))
                    {
                        media_ebook_stop_play();
                        media_ebook_enter_next_folder();
                    }
                    else if(Judge_Up_Folder(&(media_ebook_data->mediaEBookFileRset.ids[media_ebook_data->mediaEBookCurrListFocus])))
                    {
                        media_ebook_stop_play();
                        media_ebook_return_up_folder();
                    }
                    /*else if(Judge_EBK_File(&(media_ebook_data->mediaEBookFileRset.ids[media_ebook_data->mediaEBookCurrListFocus])))
                    {
                        p_media_ebk_full_screen_window_show(media_ebook_data->mediaEBookCurrPathName_utf8);
                    }*/
                    else if(Judge_TXT_File(&(media_ebook_data->mediaEBookFileRset.ids[media_ebook_data->mediaEBookCurrListFocus])))
                    {
                        p_media_txt_full_screen_window_show(media_ebook_data->mediaEBookCurrPathName_utf8);
                    }
                    return D_OK;
                default:
                    break;
            }
            break;
        case D_EVT_DATA_CHANGED:
            media_ebook_list_info_show();
            break;
        case D_EVT_SELECTED:
            media_ebook_data->mediaEBookCurrListFocus = d_list_get_focus(vis, NULL, NULL);
            media_ebook_get_currpath_name();
            break;
    }
    return D_ERR;
}


static D_Result
media_ebook_window_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_U8 status = 0;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)

                break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    /* 电子书不再显示菜单*/
                    return D_OK;
                    break;
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    p_media_txt_full_screen_window_hide();
                    //p_media_ebk_full_screen_window_hide();
                    media_ebook_stop_play();
                    media_ebook_return_up_folder();
                    return D_OK;
                default:
                    break;
            }
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
                /*拔出usb时判断是当前磁盘以退出菜单 @qiny 20150907*/
                if( (media_ebook_data->mediaEBookTotalPartition < 2) ||
                    ((int)media_ebook_data->mediaEBookCurrPartition == (int)evt->hotplug.arg))
                {
                    p_media_txt_full_screen_window_hide();
                    //p_media_ebk_full_screen_window_hide();
                    media_ebook_stop_play();
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    break;
                }
            }

            /*磁盘界面时，插拔usb，刷新磁盘显示 @qiny 20150907*/
            if(media_ebook_data->mediaEBookFocuLevel == 0)
            {
                media_ebook_data->mediaEBookCurrPartition = 0xFF;
                media_ebook_data->mediaEBookCurrFolder_utf8[0] = '\0';
                media_ebook_get_files_list(media_ebook_data->mediaEBookCurrFolder_utf8);
                d_list_set_max_row(media_ebook_data->vis_ebook_list, media_ebook_data->mediaEBookFileRset.cnt);
                media_ebook_list_info_show();
                media_ebook_get_currpath_name();
            }
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_EBOOK;
            if(media_ebook_data)
            {
                PROJECT_FREE(media_ebook_data->mediaEBookFileRset.ids);
                PROJECT_FREE(media_ebook_data);
                media_ebook_data = NULL;
            }
            d_media_ebk_close();
            d_mediacodec_close();
        }
        break;
    }

    return D_ERR;
}



D_Result
atv_media_ebook_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_ebook_data = (MediaEBookData*)PROJECT_ALLOC(sizeof(MediaEBookData));
    if(!media_ebook_data)
    {
        return D_ERR;
    }

    memset(media_ebook_data, 0x00, sizeof(MediaEBookData));
    media_ebook_data->mediaEBookCurrPartition = 0xFF;

    /*挂起DVB播放和SI监控*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/

    /*初始化多媒体音视频图片的各自的播放任务*/
    d_mediacodec_open();
    d_media_ebk_open() ;

    /*重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();

    media_ebook_data->vis_ebook_list = d_frame_get_control(frm, ID_EBOOK_LIST);
    media_ebook_data->vis_ebook_path_name = d_frame_get_control(frm, ID_EBOOK_LABEL_PATH);

    media_ebook_data->mediaEBookFileRset.max = MEDIA_EBOOK_MAX_NUM_CNT;
    media_ebook_data->mediaEBookFileRset.cnt = 0;
    media_ebook_data->mediaEBookFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_ebook_data->mediaEBookFileRset.max));
    if(!media_ebook_data->mediaEBookFileRset.ids)
    {
        return D_ERR;
    }

    media_ebook_data->mediaEBookCurrLang = p_conf_get_lang();

    media_ebook_get_files_list(media_ebook_data->mediaEBookCurrFolder_utf8);

    vis = d_frame_get_control(frm, ID_EBOOK_LIST);
    if(vis)
    {
        d_vis_set_focus(vis);
        d_vis_subscribe_evt(vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_ebook_list_handler);
        d_list_set_max_row(vis, media_ebook_data->mediaEBookFileRset.cnt);
        d_list_set_focus(media_ebook_data->vis_ebook_list, 0, (D_U16) - 1);
        media_ebook_list_info_show();
        media_ebook_get_currpath_name();
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_ebook_window_window_handler);
    }

    media_ebook_stop_play();
    media_ebook_enter_next_folder();//与上一级目录不重复临时添加(投影仪)
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_EBOOK;

    return D_OK;
}


D_Result
p_atv_media_ebook_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &atv_media_ebook_window, D_CLEAR_NONE);
}


