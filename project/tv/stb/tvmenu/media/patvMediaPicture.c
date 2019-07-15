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

#include "atv_media_picture_window.c"


#define MEDIA_PIC_FOLDER_PATH_LEN  D_PATH_LENGTH
#define MEDIA_PIC_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_PIC_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_PIC_MAX_NUM_CNT      (1000)
#define MEDIA_PIC_PARTITION_MAX_CNT (24)
#define MEDIA_PIC_FOLDER_LEVEL_MAX  (64)
#define MEDIA_PIC_REFRESH_TIME   (1000)
#define MEDIA_PIC_FILE_BUFF_SIZE (64)
#define MEDIA_PIC_ROW_CNT        (7)

/**@brief 多媒体用到的结构体*/
typedef struct
{
    D_Char  mediaPicCurrFolder_utf8[MEDIA_PIC_FOLDER_PATH_LEN];
    D_Char  mediaPicLastFolder_utf8[MEDIA_PIC_FOLDER_PATH_LEN];
    D_Char  mediaPicCurrPathName_utf8[MEDIA_PIC_FILE_NAME_LEN];
    D_Char  mediaPicCurrPathName[MEDIA_PIC_PATH_NAME_LEN];
    D_Char  mediaPicShowData[MEDIA_PIC_ROW_CNT][MEDIA_PIC_FILE_NAME_LEN];


    /**磁盘信息*/
    D_Int   mediaPicTotalPartition;                         /*总的磁盘数**/
    D_U8    mediaPicVolIndex[MEDIA_PIC_PARTITION_MAX_CNT];  /*总共的盘符数**/
    D_U8    mediaPicCurrPartition;                      /*当前的盘符**/

    D_U16   mediaPicFocuStack[MEDIA_PIC_FOLDER_LEVEL_MAX][2];/*焦点栈，记录各级文件夹焦点*/
    D_U32   mediaPicFocuLevel;  /*文件级数*/
    D_U16   mediaPicCurrListFocus;      /*当前行的聚焦号**/
    D_U16   mediaPicLastListFocus;      /*当前行的聚焦号**/

    D_U16   mediaPicCurrFile;
    D_U8    mediaPicSwitchValue;
    D_U8    mediaPicChangeIndex;
    D_U32   mediaPicCurrFocus;

    /*文件记录就指针**/
    D_FileScan mediaPicFileRset;

    D_PictureInfo    picture_info;

    D_HTimer mediaPicTimer;

    D_U8    mediaPicCurrLang;
    D_Handle pic_play_cb_handle;
    D_Char cb_pic_file_path[D_PATH_LENGTH];
    D_VidWindow    mediaPicPlayWin;

    D_Visual* vis_picture_logo, *vis_play_win, *vis_loading;
    D_Visual* vis_button_0, *vis_button_1, *vis_button_2, *vis_button_3, *vis_button_4, *vis_button_5, *vis_button_6;
    D_Visual* vis_label_0, *vis_label_1, *vis_label_2, *vis_label_3, *vis_label_4, *vis_label_5, *vis_label_6;
    D_Visual* vis_path_name, *vis_direction_left, *vis_direction_right;
} MediaPicData;

static MediaPicData* media_picture_data = NULL;
static D_U8 format_flag = 0;
static D_U8 preview_prompt_msg_flag = D_FALSE;/*记录当前是否有播放提示消息显示*/

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_nothing_normal = { -1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_nothing_focus = { -1, -1, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_disk_normal = { -1, atv_IMG_ID_FS_Media_disk_normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_disk_focus = { -1, atv_IMG_ID_FS_Media_disk_focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_updir_normal = { -1, atv_IMG_ID_FS_Media_Floder1_Normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_updir_focus = { -1, atv_IMG_ID_FS_Media_Folder1_Focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_dir_normal = { -1, atv_IMG_ID_FS_Media_Folder_Normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_dir_focus = { -1, atv_IMG_ID_FS_Media_Folder_Focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_picture_normal = { -1, atv_IMG_ID_FS_Media_Picture, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_picture_focus = { -1, atv_IMG_ID_FS_Media_Picture_Focus, -1, NULL, };

static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_disk = {{&GUID_disk_normal, &GUID_disk_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_updir = {{&GUID_updir_normal, &GUID_updir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_dir = {{&GUID_dir_normal, &GUID_dir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_picture = {{&GUID_picture_normal, &GUID_picture_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_nothing = {{&GUID_nothing_normal, &GUID_nothing_focus, NULL, }, 1, };
static void media_picture_play_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data);

//static D_Char *media_picture_type[] = {"jpeg", "jpg", "bmp", "gif", "png"};
static D_FILE_TYPE media_picture_type[] =
{
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
    D_FILE_TYPE_JPG,
    D_FILE_TYPE_BMP,
    //D_FILE_TYPE_GIF,
    //D_FILE_TYPE_PNG,
};

/* 设置窗口显示还是隐藏，当进入全屏播放时，应该把窗口隐藏，因为界面可能有滚动，会一直刷新绘制，
所以隐藏窗口的主体部分，减少cpu 对 gui绘制的负担，@add by qiny 2017.11.16*/
static D_Result
media_picture_window_show(D_Bool show)D_FUNCPOSTFIT
{
    d_vis_show(d_frame_get_control(&atv_media_picture_window, ID_PIC_GROUP_ALL), show);
    return D_OK;
}


static D_ID
media_picture_get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

/**@brief 得到图片的信息**/
static D_Result
media_picture_get_picture_info(void) D_FUNCPOSTFIT
{
    return d_media_picture_get_info(media_picture_data->mediaPicCurrPathName_utf8, &(media_picture_data->picture_info));
}

static D_Result
media_picture_set_direction(D_Bool show, D_Bool left) D_FUNCPOSTFIT
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

    d_image_box_set_image(media_picture_data->vis_direction_left, show ? img_left : NULL);
    d_image_box_set_image(media_picture_data->vis_direction_right, show ? img_right : NULL);

    return D_OK;
}

static D_Result
media_picture_left_show(D_Bool left) D_FUNCPOSTFIT
{
    D_Image* img_left = NULL;
    D_Image* img_right = NULL;


    if(left)
    {
        img_left =  d_gui_get_image(atv_IMG_ID_button_left);
        //d_vis_show(media_picture_data->vis_direction_right,D_FALSE);
        d_image_box_set_image(media_picture_data->vis_direction_left, img_left);
        d_image_box_set_image(media_picture_data->vis_direction_right,  NULL);
    }
    else
    {
        img_right =  d_gui_get_image(atv_IMG_ID_button_right);
        //d_vis_show(media_picture_data->vis_direction_left,D_FALSE);
        d_image_box_set_image(media_picture_data->vis_direction_right, img_right);
        d_image_box_set_image(media_picture_data->vis_direction_left,  NULL);
    }

    return D_OK;
}

/**@brief 得到当前路径**/
static D_Result
media_picture_get_currpath_name(void) D_FUNCPOSTFIT
{
    if(media_picture_data->mediaPicCurrFolder_utf8[0])
    {
        sprintf(media_picture_data->mediaPicCurrPathName_utf8, "%s/%s", media_picture_data->mediaPicCurrFolder_utf8, media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].path.filename);
    }
    else
    {
        sprintf(media_picture_data->mediaPicCurrPathName_utf8, "%s", media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].path.filename);
    }

#ifndef D_SYSTEM_WIN32
    p_cc_utf8_to_sys((D_U8*)media_picture_data->mediaPicCurrPathName, MEDIA_PIC_PATH_NAME_LEN, \
    (D_U8*)media_picture_data->mediaPicCurrPathName_utf8, strlen(media_picture_data->mediaPicCurrPathName_utf8));
#else
    strcpy(media_picture_data->mediaPicCurrPathName, media_picture_data->mediaPicCurrPathName_utf8);
#endif

    p_atv_media_device_name_map(media_picture_data->mediaPicCurrPathName);
    d_label_set_text(media_picture_data->vis_path_name, media_picture_data->mediaPicCurrPathName);

    return D_OK;
}

static D_Result
media_picture_show_info(void) D_FUNCPOSTFIT
{
    D_ID id, start;
    D_ID visual_id;
    D_FSAttr *fattr;
    D_Size file_length;
    D_Visual* button_my_vis[7];
    D_Visual* label_my_vis[7];

    memset(label_my_vis, 0x00, sizeof(label_my_vis));
    memset(button_my_vis, 0x00, sizeof(button_my_vis));

    start =  MEDIA_PIC_ROW_CNT * media_picture_data->mediaPicChangeIndex;

    for(id = start; id < start + MEDIA_PIC_ROW_CNT; id++)
    {
        visual_id = id % MEDIA_PIC_ROW_CNT;

        switch(visual_id)
        {
            case 0:
                button_my_vis[visual_id] = media_picture_data->vis_button_0;
                label_my_vis[visual_id] = media_picture_data->vis_label_0;
                break;
            case 1:
                button_my_vis[visual_id] = media_picture_data->vis_button_1;
                label_my_vis[visual_id] = media_picture_data->vis_label_1;
                break;
            case 2:
                button_my_vis[visual_id] = media_picture_data->vis_button_2;
                label_my_vis[visual_id] = media_picture_data->vis_label_2;
                break;
            case 3:
                button_my_vis[visual_id] = media_picture_data->vis_button_3;
                label_my_vis[visual_id] = media_picture_data->vis_label_3;
                break;
            case 4:
                button_my_vis[visual_id] = media_picture_data->vis_button_4;
                label_my_vis[visual_id] = media_picture_data->vis_label_4;
                break;
            case 5:
                button_my_vis[visual_id] = media_picture_data->vis_button_5;
                label_my_vis[visual_id] = media_picture_data->vis_label_5;
                break;
            case 6:
                button_my_vis[visual_id] = media_picture_data->vis_button_6;
                label_my_vis[visual_id] = media_picture_data->vis_label_6;
                break;
        }

        if(id >= media_picture_data->mediaPicFileRset.cnt)
        {
            d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_nothing);
            d_label_set_text(label_my_vis[visual_id], NULL);
            //d_vis_enable(button_my_vis[visual_id], D_FALSE);
        }
        else
        {

            fattr = &(media_picture_data->mediaPicFileRset.ids[id]);

            switch(fattr->class_type)
            {
                case D_FILE_SCAN_FMT_Dir:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_dir);
                    break;
                case D_FILE_SCAN_FMT_UpDir:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_updir);
                    break;
                case D_FILE_SCAN_FMT_Photo:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_picture);
                    break;
                case D_FILE_SCAN_FMT_Device:
                    d_vis_set_attribute(button_my_vis[visual_id], (D_Ptr)&GUID_disk);
                    break;
            }

#ifndef D_SYSTEM_WIN32
            file_length = strlen(fattr->path.filename);

            p_cc_utf8_to_sys((D_U8*)media_picture_data->mediaPicShowData[visual_id], MEDIA_PIC_FILE_NAME_LEN, \
                             (D_U8*)fattr->path.filename, file_length);
#else
            strcpy(media_picture_data->mediaPicShowData[visual_id], fattr->path.filename);
#endif
            p_atv_media_device_name_map(media_picture_data->mediaPicShowData[visual_id]);
            d_label_set_text(label_my_vis[visual_id], media_picture_data->mediaPicShowData[visual_id]);

        }
    }

    return D_OK;
}


/**@brief 得到路径下的文件列表*/
static D_Result
media_picture_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        memset(media_picture_data->mediaPicFileRset.ids, 0x00, sizeof(D_FSAttr) * media_picture_data->mediaPicFileRset.max);
        media_picture_data->mediaPicFileRset.max = MEDIA_PIC_MAX_NUM_CNT;
        media_picture_data->mediaPicFileRset.cnt = 0;

        p_file_scan_get_current_dir(curr_path, &media_picture_data->mediaPicFileRset, media_picture_type, sizeof(media_picture_type) / sizeof(media_picture_type[0]), D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        media_picture_data->mediaPicFileRset.cnt = 0;
        media_picture_data->mediaPicFileRset.max = MEDIA_PIC_PARTITION_MAX_CNT;
        media_picture_data->mediaPicTotalPartition = 0;
        d_fsm_get_volumes(media_picture_data->mediaPicVolIndex, &media_picture_data->mediaPicTotalPartition);
        memset(media_picture_data->mediaPicFileRset.ids, 0x00, sizeof(D_FSAttr) * media_picture_data->mediaPicFileRset.max);

        p_file_scan_get_all_partitons(&media_picture_data->mediaPicFileRset, media_picture_data->mediaPicVolIndex, media_picture_data->mediaPicTotalPartition);
    }

    media_picture_data->mediaPicSwitchValue = media_picture_data->mediaPicFileRset.cnt / MEDIA_PIC_ROW_CNT;
    if((media_picture_data->mediaPicFileRset.cnt % MEDIA_PIC_ROW_CNT))
    {
        media_picture_data->mediaPicSwitchValue++;
    }
    return D_OK;
}


/** @brief 进入下一级目录*/
static D_Result
media_picture_enter_next_folder( void )D_FUNCPOSTFIT
{
    D_U32 length;
    D_Visual* vis;

    if(media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].type == 0  &&  media_picture_data->mediaPicCurrFile < media_picture_data->mediaPicFileRset.cnt)
    {
        if(media_picture_data->mediaPicFocuLevel < MEDIA_PIC_FOLDER_LEVEL_MAX)
        {
            if(0 == media_picture_data->mediaPicFocuLevel)
            {
                media_picture_data->mediaPicCurrPartition = media_picture_data->mediaPicVolIndex[media_picture_data->mediaPicCurrFile];
            }

            media_picture_data->mediaPicFocuStack[media_picture_data->mediaPicFocuLevel][0] = media_picture_data->mediaPicCurrFile;
            media_picture_data->mediaPicFocuStack[media_picture_data->mediaPicFocuLevel][1] = media_picture_data->mediaPicChangeIndex;
            media_picture_data->mediaPicFocuLevel++;
        }

        strcpy(media_picture_data->mediaPicLastFolder_utf8, media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].path.filename);

        length = strlen(media_picture_data->mediaPicCurrFolder_utf8);
        if(length)
        {
            media_picture_data->mediaPicCurrFolder_utf8[length] = '/';
            media_picture_data->mediaPicCurrFolder_utf8[length + 1] = '\0';
            strcat(media_picture_data->mediaPicCurrFolder_utf8, media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].path.filename);
        }
        else
        {
            strcpy(media_picture_data->mediaPicCurrFolder_utf8, media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile].path.filename);
        }

        media_picture_get_files_list(media_picture_data->mediaPicCurrFolder_utf8);
        media_picture_data->mediaPicChangeIndex = 0;
        media_picture_data->mediaPicCurrFile = 0;
        media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_0;
        vis = d_frame_get_control(&atv_media_picture_window, media_picture_data->mediaPicCurrFocus);
        if(vis)
        {
            d_vis_set_focus(vis);
        }
        media_picture_show_info();
        media_picture_get_currpath_name();
        //media_picture_set_direction(D_TRUE, D_FALSE);
        if(media_picture_data->mediaPicFileRset.cnt > 7)
        {
            media_picture_left_show(D_FALSE);
        }
        else
        {
            media_picture_set_direction(D_FALSE, D_FALSE);
        }
        return D_OK;
    }

    return D_ERR;

}

static D_Result
media_picture_get_up_folder( void )D_FUNCPOSTFIT
{
    D_Char* temp;

    temp = strrchr(media_picture_data->mediaPicCurrFolder_utf8, '/');
    if(temp)
    {
        *temp = '\0';
        temp++;
        strcpy(media_picture_data->mediaPicLastFolder_utf8, temp);
        //media_picture_set_direction(D_TRUE, D_FALSE);
    }
    else
    {
        media_picture_data->mediaPicLastFolder_utf8[0] = '\0';
        media_picture_data->mediaPicCurrFolder_utf8[0] = '\0';
        media_picture_set_direction(D_FALSE, D_FALSE);

    }

    return D_OK;
}

/**@brief 查找返回上一级目录时焦点值*/
static D_ID
media_picture_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_picture_data->mediaPicFocuLevel)
    {
        media_picture_data->mediaPicFocuLevel--;
        media_picture_data->mediaPicCurrFile = media_picture_data->mediaPicFocuStack[media_picture_data->mediaPicFocuLevel][0];
        media_picture_data->mediaPicChangeIndex = media_picture_data->mediaPicFocuStack[media_picture_data->mediaPicFocuLevel][1];
    }

    return D_OK;
}

static D_Result
media_picture_set_curr_focus(void) D_FUNCPOSTFIT
{
    D_U32 focus;
    D_Visual* vis;

    focus = (media_picture_data->mediaPicCurrFile % MEDIA_PIC_ROW_CNT);
    switch(focus)
    {
        case 0:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_0;
            break;
        case 1:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_1;
            break;
        case 2:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_2;
            break;
        case 3:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_3;
            break;
        case 4:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_4;
            break;
        case 5:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_5;
            break;
        case 6:
            media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_6;
            break;
    }

    vis = d_frame_get_control(&atv_media_picture_window, media_picture_data->mediaPicCurrFocus);
    if(vis)
    {
        d_vis_set_focus(vis);
    }

    return D_OK;
}

/** @brief 返回上一级目录*/
static D_Result
media_picture_return_up_folder( void )D_FUNCPOSTFIT
{

    if(media_picture_data->mediaPicCurrFolder_utf8[0])
    {
        media_picture_get_up_folder();
        media_picture_get_files_list(media_picture_data->mediaPicCurrFolder_utf8);
        media_picture_get_last_focus();

        if(media_picture_data->mediaPicFocuLevel == 0)
        {
            media_picture_data->mediaPicCurrPartition = 0xFF;
        }
        
        if(media_picture_data->mediaPicChangeIndex == 0 && media_picture_data->mediaPicFileRset.cnt > 7)
        {
            media_picture_left_show(D_FALSE);
        }
        else if(media_picture_data->mediaPicChangeIndex == (media_picture_data->mediaPicSwitchValue - 1) && media_picture_data->mediaPicFileRset.cnt > 7)
        {
            media_picture_left_show(D_TRUE);
        }
        else if(media_picture_data->mediaPicFileRset.cnt <= 7  )
        {
            media_picture_set_direction(D_FALSE, D_FALSE);
        }
        else
        {
            media_picture_set_direction(D_TRUE, D_TRUE);
        }

        media_picture_set_curr_focus();
        media_picture_show_info();
        media_picture_get_currpath_name();
        return D_OK;
    }
    else
    {
        d_media_picture_stop();
		d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_ERR;
}


static D_Result
media_picture_preview_curr_picture(void) D_FUNCPOSTFIT
{
    D_FSAttr *fsattr;
    fsattr = &(media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile]);

    if(Judge_Photo_File(fsattr))
    {
        //if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
        {
        	d_vis_show(media_picture_data->vis_loading,D_TRUE);
            d_image_box_set_image(media_picture_data->vis_loading, d_gui_get_image(atv_IMG_ID_loading));
        }

        if(D_OK == media_picture_get_picture_info())
        {
            D_VidWindow    Win = media_picture_data->mediaPicPlayWin;

            if (media_picture_data->picture_info.height > 8000 || media_picture_data->picture_info.width > 8000)
            {
                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
				preview_prompt_msg_flag = D_TRUE;
                return D_ERR;
            }
			if(fsattr->file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
	        {
	        	if (media_picture_data->picture_info.height > 2000 || media_picture_data->picture_info.width > 2000)
	            {
	                /*该图片文件尺寸大于芯片解码能力不支持播放*/
	                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
	                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
					preview_prompt_msg_flag = D_TRUE;
	                return D_ERR;
	            }
	        }
            

            if(fsattr->file_type != D_FILE_TYPE_GIF)
            {
                p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            }

            if( D_OK == d_media_picture_play(media_picture_data->mediaPicCurrPathName_utf8, Win.x, Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_PREVIEW))
            {
				d_av_set_vid_blank(0, D_FALSE); /*退出黑屏*/
                return D_OK;
            }

        }
        else
        {
            /*该图片文件获取信息失败不能播放*/
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
			preview_prompt_msg_flag = D_TRUE;
            return D_ERR;

        }
    }

    return D_ERR;
}

/** @brief 供全屏播放退出后返回列表后更新小窗口*/
D_Result
update_picture_window (D_Char *path_name, D_ID cur_index)D_FUNCPOSTFIT
{
    D_Frame * frm = &atv_media_picture_window;
    D_Visual *vis_focus ;
    D_FSAttr *fsattr;

    if (!media_picture_data)
    {
        p_atv_media_picture_show();
        return D_OK;
    }
    
    media_picture_window_show(D_TRUE); // 退出图片全屏时，要恢复列表窗口的显示 @qiny 2017.11.16    
    fsattr = &(media_picture_data->mediaPicFileRset.ids[cur_index]);

    media_picture_data->mediaPicCurrFile = cur_index;
    //media_picture_data->mediaPicChangeIndex = fullscream_page;
    //if(media_picture_data->mediaPicCurrFile == ((media_picture_data->mediaPicChangeIndex+1)*MEDIA_PIC_ROW_CNT))
    //{
    //  fullscream_page = media_picture_data->mediaPicCurrFile%MEDIA_PIC_ROW_CNT+1;
    //}
    media_picture_data->mediaPicChangeIndex = media_picture_data->mediaPicCurrFile / MEDIA_PIC_ROW_CNT;
    media_picture_set_curr_focus();
    media_picture_show_info();
    media_picture_get_currpath_name();
	
	if ( media_picture_data->pic_play_cb_handle == D_INVALID_HANDLE )
	{
        media_picture_data->pic_play_cb_handle = d_cbman_subscribe(PL_MEDIA_PIC_PALY, D_INVALID_HANDLE, media_picture_play_cb, (D_Ptr)frm);
	}
    //if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
    {
    	d_vis_show(media_picture_data->vis_loading,D_TRUE);
        d_image_box_set_image(media_picture_data->vis_loading, d_gui_get_image(atv_IMG_ID_loading));
    }
    if(Judge_Photo_File(fsattr))
    {
        if(D_OK == media_picture_get_picture_info())
        {
            D_VidWindow    Win = media_picture_data->mediaPicPlayWin;

            if (media_picture_data->picture_info.height > 8000 || media_picture_data->picture_info.width > 8000)
            {
                d_image_box_set_image(media_picture_data->vis_loading, NULL);
                d_vis_show(media_picture_data->vis_loading, D_FALSE);
                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
				preview_prompt_msg_flag = D_TRUE;
                return D_ERR;
            }
			if(fsattr->file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
	        {
	        	if (media_picture_data->picture_info.height > 2000 || media_picture_data->picture_info.width > 2000)
	            {
	                d_image_box_set_image(media_picture_data->vis_loading, NULL);
	                d_vis_show(media_picture_data->vis_loading, D_FALSE);
	                /*该图片文件尺寸大于芯片解码能力不支持播放*/
	                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
	                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
					preview_prompt_msg_flag = D_TRUE;
	                return D_ERR;
	            }
	        }
            if(fsattr->file_type != D_FILE_TYPE_GIF)
            {
                p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            }

            if( D_OK == d_media_picture_play(path_name, Win.x, Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_PREVIEW))
            {
				d_av_set_vid_blank(0, D_FALSE); /*退出黑屏*/
                return D_OK;
            }

        }
        else
        {
            d_image_box_set_image(media_picture_data->vis_loading, NULL);
            d_vis_show(media_picture_data->vis_loading, D_FALSE);
            /*该图片文件获取信息失败不能播放*/
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
			preview_prompt_msg_flag = D_TRUE;
            return D_ERR;
        }
    }
    //d_media_picture_play(path_name, media_picture_data->mediaPicPlayWin.x,
    //media_picture_data->mediaPicPlayWin.y, media_picture_data->mediaPicPlayWin.w, media_picture_data->mediaPicPlayWin.h,
    //0, 0, PICTURE_OPEN_MODE_PREVIEW);
    return D_OK;
}

static D_Result
media_picture_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(Judge_Dir_Folder(&(media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile])))
                    {
                        media_picture_enter_next_folder();
                    }
                    else if(Judge_Up_Folder(&(media_picture_data->mediaPicFileRset.ids[media_picture_data->mediaPicCurrFile])))
                    {
                        media_picture_return_up_folder();
                    }
                    else
                    {
                        if (d_media_picture_get_status() == PICTURE_STATUS_RUN || d_media_picture_get_status() == PICTURE_STATUS_PAUSE)
                        {
                            d_media_picture_stop();
                        }
						d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
						d_cbman_unsubscribe(media_picture_data->pic_play_cb_handle);
						media_picture_data->pic_play_cb_handle = D_INVALID_HANDLE;
                        if(D_OK == p_pic_full_screen_menu_show(media_picture_data->mediaPicCurrPathName_utf8,
                                                    &media_picture_data->mediaPicFileRset, media_picture_data->mediaPicCurrFile, update_picture_window))
                        {
                        	media_picture_window_show(D_FALSE); // 图片全屏时，要隐藏列表窗口的显示 @qiny 2017.11.16
                        }
						else
						{	
							if ( media_picture_data->pic_play_cb_handle == D_INVALID_HANDLE )
							{
                                media_picture_data->pic_play_cb_handle = d_cbman_subscribe(PL_MEDIA_PIC_PALY, D_INVALID_HANDLE, media_picture_play_cb, (D_Ptr)(&atv_media_picture_window));
							}
						}
                    }
                    break;
                default:
                    break;
            }
            break;
    }
    return D_ERR;
}


static D_Result
media_picture_window_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame * frm = &atv_media_picture_window;
    D_Visual *vis_focus;
    switch(evt->type)
    {
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                media_picture_data->mediaPicCurrLang = evt->user.param2;
                if(D_LANG_CHN == evt->user.param2)
                {
                    d_image_box_set_image(media_picture_data->vis_picture_logo, d_gui_get_image(atv_IMG_ID_title_picture));
                }
                else
                {
                    d_image_box_set_image(media_picture_data->vis_picture_logo, d_gui_get_image(atv_IMG_ID_title_picture_en));
                }

                d_vis_update(media_picture_data->vis_picture_logo, NULL);
                d_gui_update();
            }
            break;
        case D_EVT_USER2:
            if((evt->user.handle == (D_Handle)frm) && (evt->user.param1 == USER_MSG_PARAM1_MEDIA_PIC_PLAY_END))
            {
                if(strcmp(media_picture_data->cb_pic_file_path, media_picture_data->mediaPicCurrPathName_utf8) == 0)
                {
                    D_U32 pic_decode_ret = (D_U32)evt->user.param2;

                    if(pic_decode_ret == 0)/*解码失败*/
                    {
                        /*该图片文件播放时解码出错 或者文件本身有错*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
						preview_prompt_msg_flag = D_TRUE;
                    }
                    else if (pic_decode_ret == 1)/*内存不足*/
                    {
                        /*该图片文件解码过程中内存空间不足*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
						preview_prompt_msg_flag = D_TRUE;
                    }
                    else if(pic_decode_ret == 2)
                    {
                        /* 成功*/
                    }

                    //无论失败成功都取消显示
                    d_image_box_set_image(media_picture_data->vis_loading, NULL);
                    d_vis_show(media_picture_data->vis_loading, D_FALSE);

                }
            }
            break;
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    /* 图片不再显示菜单*/
                    return D_OK;
                    break;
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
					if (preview_prompt_msg_flag)
					{
						d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
						preview_prompt_msg_flag = D_FALSE;
					}
					d_vis_show(media_picture_data->vis_loading,D_FALSE);
                    d_image_box_set_image(media_picture_data->vis_loading, NULL);
                    d_media_picture_stop();
					d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
                    media_picture_return_up_folder();
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
					if (preview_prompt_msg_flag)
					{
						d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
						preview_prompt_msg_flag = D_FALSE;
					}
					d_vis_show(media_picture_data->vis_loading,D_FALSE);
					d_image_box_set_image(media_picture_data->vis_loading, NULL);
                    if(media_picture_data->mediaPicChangeIndex > 0)
                    {
                        if(media_picture_data->mediaPicCurrFile == ((media_picture_data->mediaPicChangeIndex)*MEDIA_PIC_ROW_CNT))
                        {
                            media_picture_data->mediaPicChangeIndex--;
                            media_picture_show_info();
                        }
                    }
                    if(media_picture_data->mediaPicCurrFile == 0)
                    {
                        break;
                    }

                    media_picture_data->mediaPicCurrFile--;
                    if(media_picture_data->mediaPicCurrFocus == ID_PIC_BUTTON_0)
                    {
                        media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_6;
                    }
                    else
                    {
                        media_picture_data->mediaPicCurrFocus = media_picture_data->mediaPicCurrFocus - 1;
                    }

                    vis_focus = d_frame_get_control(frm, media_picture_data->mediaPicCurrFocus);
                    if(vis_focus)
                    {
                        d_vis_set_focus(vis_focus);
                    }

                    if(media_picture_data->mediaPicChangeIndex == 0 && media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_left_show(D_FALSE);
                    }
                    else if(media_picture_data->mediaPicChangeIndex == (media_picture_data->mediaPicSwitchValue - 1) && media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_left_show(D_TRUE);
                    }
                    else if(media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_set_direction(D_TRUE, D_TRUE);
                    }
                    else
                        media_picture_set_direction(D_FALSE, D_FALSE);
                    media_picture_get_currpath_name();

                    //if (d_media_picture_get_status() == PICTURE_STATUS_RUN || d_media_picture_get_status() == PICTURE_STATUS_PAUSE)
                    {
                        d_media_picture_stop();
                    }
					d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/

                    media_picture_preview_curr_picture();

                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
					if (preview_prompt_msg_flag)
					{
						d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
						preview_prompt_msg_flag = D_FALSE;
					}
					d_vis_show(media_picture_data->vis_loading,D_FALSE);
					d_image_box_set_image(media_picture_data->vis_loading, NULL);
                    if(media_picture_data->mediaPicCurrFile == media_picture_data->mediaPicFileRset.cnt - 1)
                    {
                        break;
                    }

                    media_picture_data->mediaPicCurrFile++;

                    if(media_picture_data->mediaPicChangeIndex < media_picture_data->mediaPicSwitchValue)
                    {
                        if(media_picture_data->mediaPicCurrFile == ((media_picture_data->mediaPicChangeIndex + 1)*MEDIA_PIC_ROW_CNT))
                        {
                            media_picture_data->mediaPicChangeIndex++;
                            media_picture_show_info();
                        }
                    }

                    if(media_picture_data->mediaPicCurrFocus == ID_PIC_BUTTON_6)
                    {
                        media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_0;
                    }
                    else
                    {
                        media_picture_data->mediaPicCurrFocus = media_picture_data->mediaPicCurrFocus + 1;
                    }

                    vis_focus = d_frame_get_control(frm, media_picture_data->mediaPicCurrFocus);
                    if(vis_focus)
                    {
                        d_vis_set_focus(vis_focus);
                    }
                    if(media_picture_data->mediaPicChangeIndex == 0 && media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_left_show(D_FALSE);
                    }
                    else if(media_picture_data->mediaPicChangeIndex == media_picture_data->mediaPicSwitchValue - 1 && media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_left_show(D_TRUE);
                    }
                    else if(media_picture_data->mediaPicFileRset.cnt > 7)
                    {
                        media_picture_set_direction(D_TRUE, D_FALSE);
                    }
                    else
                        media_picture_set_direction(D_FALSE, D_FALSE);
                    media_picture_get_currpath_name();

                    // if (d_media_picture_get_status() == PICTURE_STATUS_RUN || d_media_picture_get_status() == PICTURE_STATUS_PAUSE)
                    {
                        d_media_picture_stop();
                    }
					d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/

                    media_picture_preview_curr_picture();
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            break;
        case D_EVT_HOTPLUG_MSG:
            if (!evt->hotplug.plug)
            {
                /*拔出usb时判断是当前磁盘以退出菜单 @qiny 20150907*/
                if( (media_picture_data->mediaPicTotalPartition < 2) ||
                    ((int)media_picture_data->mediaPicCurrPartition == (int)evt->hotplug.arg))
                {
                    d_media_picture_stop();
					d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
                    if(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN)
                    {
                        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    }
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    break;
                }
            }

            /*磁盘界面时，插拔usb，刷新磁盘显示 @qiny 20150907*/
            if(media_picture_data->mediaPicFocuLevel == 0)
            {
                media_picture_data->mediaPicCurrPartition = 0xFF;
                media_picture_data->mediaPicCurrFolder_utf8[0] = '\0';
                media_picture_get_files_list(media_picture_data->mediaPicCurrFolder_utf8);
                
                media_picture_data->mediaPicCurrFile = D_MIN(media_picture_data->mediaPicCurrFile, (media_picture_data->mediaPicFileRset.cnt - 1));
                media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_0 + (media_picture_data->mediaPicCurrFile % MEDIA_PIC_ROW_CNT); 
                vis_focus = d_frame_get_control(frm, media_picture_data->mediaPicCurrFocus);
                if(vis_focus)
                {
                    d_vis_set_focus(vis_focus);
                }
                
                media_picture_show_info();
                media_picture_get_currpath_name();
            }
            
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_PHOTO;
            if(media_picture_data)
            {
	 			d_cbman_unsubscribe(media_picture_data->pic_play_cb_handle);
				media_picture_data->pic_play_cb_handle = D_INVALID_HANDLE;
               	PROJECT_FREE(media_picture_data->mediaPicFileRset.ids);
                PROJECT_FREE(media_picture_data);
                media_picture_data = NULL;
            }
            format_flag = 0;
			if (preview_prompt_msg_flag)
			{
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
				preview_prompt_msg_flag = D_FALSE;
			}
            d_media_picture_stop();
            d_av_set_vid_blank(0, D_TRUE); /* 黑屏*/
            d_media_picture_close();
            d_mediacodec_close();
        }
        break;
    }
    return D_ERR;
}

/** @brief 播放图片结果 的回调函数*/
static void media_picture_play_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_Pic_Cb *cb_ret = (D_Pic_Cb*)obj_data;
    D_Frame *frm = &atv_media_picture_window;

    if(media_picture_data && frm == (D_Frame *)cb_data)
    {
        if(strcmp(cb_ret->path, media_picture_data->mediaPicCurrPathName_utf8) == 0)
        {
            D_UserMsg msg;

            strcpy(media_picture_data->cb_pic_file_path, cb_ret->path);

            /* 由于此函数是图片播放相关任务调用，不是gui任务调用，
            因此不允许直接调用gui相关的显示函数，比如隐藏加载图标，
            显示图片播放失败等提示，gui通常不允多线程调用，因此
            因此这里通过消息的方式，在窗口handler里进行处理。 @qiny 20150923*/
            msg.type = D_MSG_USER2;
            msg.handle = (D_Handle)frm;
            msg.param1 = USER_MSG_PARAM1_MEDIA_PIC_PLAY_END;
            msg.param2 = (D_U32)cb_ret->pic_decode_ret;
            msg.param3 = (D_U32)media_picture_data->cb_pic_file_path;
            d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
            //D_DUMP("%s %d\n",__FUNCTION__,__LINE__);
        }
    }
}


D_Result
atv_media_picture_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_picture_data = (MediaPicData*)PROJECT_ALLOC(sizeof(MediaPicData));
    if(!media_picture_data)
    {
        return D_ERR;
    }

    memset(media_picture_data, 0x00, sizeof(MediaPicData));
	
	media_picture_data->pic_play_cb_handle = D_INVALID_HANDLE;
    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_PHOTO;
    media_picture_data->mediaPicCurrPartition = 0xFF;
    media_picture_data->mediaPicCurrFocus = ID_PIC_BUTTON_0;
    vis = d_frame_get_control(frm, media_picture_data->mediaPicCurrFocus);
    if(vis)
    {
        d_vis_set_focus(vis);
    }

    media_picture_data->vis_picture_logo = d_frame_get_control(frm, ID_PIC_IMG_LOGO);
    media_picture_data->vis_button_0 = d_frame_get_control(frm, ID_PIC_BUTTON_0);
    media_picture_data->vis_button_1 = d_frame_get_control(frm, ID_PIC_BUTTON_1);
    media_picture_data->vis_button_2 = d_frame_get_control(frm, ID_PIC_BUTTON_2);
    media_picture_data->vis_button_3 = d_frame_get_control(frm, ID_PIC_BUTTON_3);
    media_picture_data->vis_button_4 = d_frame_get_control(frm, ID_PIC_BUTTON_4);
    media_picture_data->vis_button_5 = d_frame_get_control(frm, ID_PIC_BUTTON_5);
    media_picture_data->vis_button_6 = d_frame_get_control(frm, ID_PIC_BUTTON_6);

    media_picture_data->vis_label_0 = d_frame_get_control(frm, ID_PIC_LABEL_0);
    media_picture_data->vis_label_1 = d_frame_get_control(frm, ID_PIC_LABEL_1);
    media_picture_data->vis_label_2 = d_frame_get_control(frm, ID_PIC_LABEL_2);
    media_picture_data->vis_label_3 = d_frame_get_control(frm, ID_PIC_LABEL_3);
    media_picture_data->vis_label_4 = d_frame_get_control(frm, ID_PIC_LABEL_4);
    media_picture_data->vis_label_5 = d_frame_get_control(frm, ID_PIC_LABEL_5);
    media_picture_data->vis_label_6 = d_frame_get_control(frm, ID_PIC_LABEL_6);

    media_picture_data->vis_path_name = d_frame_get_control(frm, ID_PIC_PATH_LABEL);
    media_picture_data->vis_direction_left = d_frame_get_control(frm, ID_PIC_MING_LEFT);
    media_picture_data->vis_direction_right = d_frame_get_control(frm, ID_PIC_IMGE_RIGHT);

    media_picture_data->vis_play_win = d_frame_get_control(frm, ID_PIC_LANEL_PLAY_VIDEO);
    media_picture_data->vis_loading = d_frame_get_control(frm, ID_PIC_LOADING);


    d_vis_get_pos(media_picture_data->vis_play_win, &media_picture_data->mediaPicPlayWin.x, &media_picture_data->mediaPicPlayWin.y);
    media_picture_data->mediaPicPlayWin.w = media_picture_data->vis_play_win->rect.w;
    media_picture_data->mediaPicPlayWin.h = media_picture_data->vis_play_win->rect.h;

    /*挂起DVB播放和SI监控*/
    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*黑屏*/

    /*停止fman对信号的监控*/
    d_fman_set_locked_detector(g_stb->player->hfman, D_INVALID_HANDLE);
    d_app_set_timeout(g_stb->player->hfman, -1);

    /*释放epg占用资源*/
    p_auxi_free_varstring();

    /*初始化多媒体音视频图片的各自的播放任务*/
    d_mediacodec_open();
    d_media_picture_open() ;

    /*重设静音/声道/音量*/
    p_stb_reset_mute_track_volume();

    d_media_picture_set_layer(D_GUI_LAYER_USER_0);

    media_picture_data->mediaPicFileRset.max = MEDIA_PIC_MAX_NUM_CNT;
    media_picture_data->mediaPicFileRset.cnt = 0;
    media_picture_data->mediaPicFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_picture_data->mediaPicFileRset.max));
    if(!media_picture_data->mediaPicFileRset.ids)
    {
        return D_ERR;
    }

    media_picture_data->mediaPicCurrLang = p_conf_get_lang();
    if(1 == media_picture_data->mediaPicCurrLang)
    {
        d_image_box_set_image(media_picture_data->vis_picture_logo, d_gui_get_image(atv_IMG_ID_title_picture));
    }
    else
    {
        d_image_box_set_image(media_picture_data->vis_picture_logo, d_gui_get_image(atv_IMG_ID_title_picture_en));
    }


    media_picture_get_files_list(media_picture_data->mediaPicCurrFolder_utf8);

    media_picture_show_info();
    media_picture_get_currpath_name();

    media_picture_data->pic_play_cb_handle = d_cbman_subscribe(PL_MEDIA_PIC_PALY, D_INVALID_HANDLE, media_picture_play_cb, (D_Ptr)frm);

    vis = d_frame_get_control(frm, ID_PIC_GROUP);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);

        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_picture_button_handler);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        //d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, media_picture_window_window_handler);
    }

    media_picture_set_direction(D_FALSE, D_FALSE);

    return D_OK;
}

D_Result
p_atv_media_picture_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_media_picture_window, D_CLEAR_ALL);
}


