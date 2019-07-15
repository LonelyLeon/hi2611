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

#include "pic_list_menu_window.c"


#define MEDIA_FOLDER_NAME_LEN  D_PATH_LENGTH
#define MEDIA_PATH_NAME_LEN    D_PATH_LENGTH
#define MEDIA_FILE_NAME_LEN    D_PATH_LENGTH
#define MEDIA_FILE_MAX_CNT      (800) /**@brief ��ʾ���ļ������Ŀ*/
#define MEDIA_PARTITION_MAX_CNT (24)
#define MEDIA_FOLDER_LEVEL_MAX  (64)
#define MEDIA_FILE_BUFF_SIZE (64)
#define MEDIA_LIST_ROW_CNT    (3)
#define MEDIA_LIST_COL_CNT    (5)
/**@brief ÿҳ��ʾ���ļ���*/
#define MEDIA_LIST_NUM_PER_PAGE (MEDIA_LIST_ROW_CNT * MEDIA_LIST_COL_CNT)



/**@brief ��ý���õ��Ľṹ��*/
typedef struct
{
    D_Char  mediaCurrFolder_utf8[MEDIA_FOLDER_NAME_LEN]; /**��ǰĿ¼��**/
    D_Char  mediaLastFolder_utf8[MEDIA_FOLDER_NAME_LEN]; /**��һĿ¼��**/
    D_Char  mediaCurrPathName_utf8[MEDIA_FILE_NAME_LEN]; /**��ǰ�ļ�·��ȫ��**/
    D_Char  mediaCurrPathName[MEDIA_PATH_NAME_LEN];      /**��ǰ�ļ�·��ȫ��**/
    D_Char  mediaListContent[MEDIA_LIST_NUM_PER_PAGE][MEDIA_FILE_NAME_LEN]; /**�б�ÿ���ļ���**/
    //D_Char  mediaFileName[MEDIA_FILE_NAME_LEN];    /**��ǰ�ļ���**/

    /** ������Ϣ*/
    D_Int   mediaTotalPartition;                           /**�ܵĴ�����**/
    D_U8    mediaVolIndexs[MEDIA_PARTITION_MAX_CNT];  /* �ܹ����̷���**/
    D_U8    mediaCurrPartition;                        /* ��ǰ���̷�**/

    D_U16   mediaFocuStack[MEDIA_FOLDER_LEVEL_MAX];/* ����ջ����¼�����ļ��н���*/
    D_U32   mediaFocuLevel;  /* Ŀ¼����*/

    D_U32   mediaCurrFocus;  /* ��ǰ����*/
    D_U32   mediaCurrPage; /* ��ǰҳ��*/

    /* �ļ���¼��ָ��**/
    D_FileScan mediaFileRset; /* ��ǰĿ¼�µ��ļ���¼��*/
    D_U8    mediaMenuCurrLang; /* ��ǰ�˵�����*/
    D_Bool mediaFilePlayFlag; /* ����״̬*/
    D_Bool  mediaExitFullScreenFlag; /* ȫ������״̬*/

    D_U32  menuVisShowCnt; /* ��ǰ��ʾ���ļ��ؼ�����*/
    D_Bool  menuEditFlag; /* �˵���Ծ״̬*/
    D_U32  sysUsbStatus; /* USB״̬*/

    D_Frame* win_frm;
    D_Visual* vis_group_all;
    D_Visual* vis_file_name;
} D_MediaPicListMenuData;

static D_MediaPicListMenuData* media_list_data = NULL;
static D_U32 uCurrentMenuTpe = 0;

/**@brief ͼ��ؼ��ļ�����ʾ����*/
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_disk_normal = { -1, atv_IMG_ID_media_folder_file, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_disk_focus = { -1, atv_IMG_ID_media_folder_file_focse, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_updir_normal = { -1, atv_IMG_ID_media_folder_file, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_updir_focus = { -1, atv_IMG_ID_media_folder_file_focse, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_dir_normal = { -1, atv_IMG_ID_media_folder_file, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_dir_focus = { -1, atv_IMG_ID_media_folder_file_focse, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_pic_normal = { -1, atv_IMG_ID_media_pic_focse, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_Attr_pic_focus = { -1, atv_IMG_ID_media_pic, -1, NULL, };

static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_disk = {{&GUID_Attr_disk_normal, &GUID_Attr_disk_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_updir = {{&GUID_Attr_updir_normal, &GUID_Attr_updir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_dir = {{&GUID_Attr_dir_normal, &GUID_Attr_dir_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_Descr_pic = {{&GUID_Attr_pic_normal, &GUID_Attr_pic_focus, NULL, }, 1, };


/**@brief �������ļ������б�*/

static D_FILE_TYPE media_picture_type[] =
{
    D_FILE_TYPE_UPDIR,
    D_FILE_TYPE_DIR,
    D_FILE_TYPE_JPG,
    D_FILE_TYPE_BMP,
    //D_FILE_TYPE_GIF,
    //D_FILE_TYPE_PNG,
};
extern D_Result
p_media_main_menu_set_enable(D_Bool enable) D_FUNCPOSTFIT;
extern D_U32 AtvMediaMenuStatus;

static D_Result
medialist_menu_set_edit_status(D_Bool edit) D_FUNCPOSTFIT;

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

/**@brief �õ�·���µ��ļ��б�*/
static D_Result
medialist_menu_get_files_list(D_Char* curr_path) D_FUNCPOSTFIT
{
    if(curr_path[0])
    {
        D_FILE_TYPE *type;
        D_U32 cnt;

        /**��ǰĿ¼�²�����Ӧ��ý���ļ��б�**/
        memset(media_list_data->mediaFileRset.ids, 0x00, sizeof(D_FSAttr) * media_list_data->mediaFileRset.max);
        media_list_data->mediaFileRset.max = MEDIA_FILE_MAX_CNT;
        media_list_data->mediaFileRset.cnt = 0;
        if(uCurrentMenuTpe == ATV_MEDIA_MENU_STATUS_PHOTO)
        {
            type = media_picture_type;
            cnt = sizeof(media_picture_type) / sizeof(media_picture_type[0]);
        }
        p_file_scan_get_current_dir(curr_path, &media_list_data->mediaFileRset, type, cnt, D_FILE_MATCH_MODE_FILETYPE);
    }
    else
    {
        /**��ǰĿ¼��Ϊ�գ�˵�����̷�Ŀ¼��ȡ���̷�Ŀ¼�б�**/
        media_list_data->mediaFileRset.cnt = 0;
        media_list_data->mediaFileRset.max = MEDIA_PARTITION_MAX_CNT;
        media_list_data->mediaTotalPartition = 0;
        d_fsm_get_volumes(media_list_data->mediaVolIndexs, &media_list_data->mediaTotalPartition);
        memset(media_list_data->mediaFileRset.ids, 0x00, sizeof(D_FSAttr) * media_list_data->mediaFileRset.max);

        p_file_scan_get_all_partitons(&media_list_data->mediaFileRset, media_list_data->mediaVolIndexs, media_list_data->mediaTotalPartition);
    }

    return D_OK;
}

/**@brief �õ���ǰ·���ļ���**/
static D_Result
medialist_menu_show_file_name(void) D_FUNCPOSTFIT
{
    if(media_list_data->mediaFileRset.cnt)
    {
        if(media_list_data->mediaCurrFolder_utf8[0])
        {
            sprintf(media_list_data->mediaCurrPathName_utf8, "%s/%s", media_list_data->mediaCurrFolder_utf8, media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].path.filename);
        }
        else
        {
            sprintf(media_list_data->mediaCurrPathName_utf8, "%s", media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].path.filename);
        }

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

    p_atv_media_device_name_map(media_list_data->mediaCurrPathName);
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
    D_FSAttr *fattr;
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

        if((id + start) >= media_list_data->mediaFileRset.cnt)
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
            fattr = &(media_list_data->mediaFileRset.ids[id + start]);
            switch(fattr->class_type)
            {
                case D_FILE_SCAN_FMT_Dir:
                    d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_dir);
                    break;
                case D_FILE_SCAN_FMT_UpDir:
                    d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_updir);
                    break;
                case D_FILE_SCAN_FMT_Photo:
                    //  case D_FILE_SCAN_FMT_TS:
                    d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_pic);
                    break;
                case D_FILE_SCAN_FMT_Device:
                    d_vis_set_attribute(vis_image, (D_Ptr)&GUID_Descr_disk);
                    break;
            }

            /**������ʾ��Ӧ��Ŀ¼���ļ���**/
#ifndef D_SYSTEM_WIN32
            {
                D_Size file_length;
                file_length = strlen(fattr->path.filename);

                p_cc_utf8_to_sys((D_U8*)media_list_data->mediaListContent[id], MEDIA_FILE_NAME_LEN, \
                                 (D_U8*)fattr->path.filename, file_length);
            }
#else
            strcpy(media_list_data->mediaListContent[id], fattr->path.filename);
#endif

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

    page_max = (media_list_data->mediaFileRset.cnt - 1) / MEDIA_LIST_COL_CNT;
    num_d = media_list_data->mediaCurrFocus / MEDIA_LIST_COL_CNT;
    if(action_key == D_KEY_LEFT && media_list_data->mediaCurrFocus)
    {
        new_focus = ((D_S32)media_list_data->mediaCurrFocus) - 1;
    }
    else if(action_key == D_KEY_RIGHT && media_list_data->mediaCurrFocus < (media_list_data->mediaFileRset.cnt - 1))
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
        if(new_focus >= media_list_data->mediaFileRset.cnt && page_max != num_d)
        {
            new_focus = ((D_S32)media_list_data->mediaFileRset.cnt) - 1;
        }
    }

    /* ��Ч�����л�*/
    if(new_focus >= 0 && new_focus < media_list_data->mediaFileRset.cnt)
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

    if(media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].type == 0  &&  media_list_data->mediaCurrFocus < media_list_data->mediaFileRset.cnt)
    {
        if(media_list_data->mediaFocuLevel < MEDIA_FOLDER_LEVEL_MAX)
        {
            if(0 == media_list_data->mediaFocuLevel)
            {
                /**��¼�û�ѡ����̷�**/
                media_list_data->mediaCurrPartition = media_list_data->mediaVolIndexs[media_list_data->mediaCurrFocus];
            }

            /**��¼��һ���Ľ���**/
            media_list_data->mediaFocuStack[media_list_data->mediaFocuLevel] = media_list_data->mediaCurrFocus;
            media_list_data->mediaFocuLevel++;
        }

        /**��¼��һ����Ŀ¼**/
        //strcpy(media_list_data->mediaLastFolder_utf8, media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].path.filename);

        /**�����û�Ҫ�����Ŀ¼���������Ӧ��ý���ļ��б�**/
        length = strlen(media_list_data->mediaCurrFolder_utf8);
        if(length)
        {
            media_list_data->mediaCurrFolder_utf8[length] = '/';
            media_list_data->mediaCurrFolder_utf8[length + 1] = '\0';
            strcat(media_list_data->mediaCurrFolder_utf8, media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].path.filename);
        }
        else
        {
            strcpy(media_list_data->mediaCurrFolder_utf8, media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus].path.filename);
        }

        medialist_menu_get_files_list(media_list_data->mediaCurrFolder_utf8);
        media_list_data->mediaCurrFocus = 0;

        /* �б�������ʾ*/
        medialist_menu_show_list_info();
        /* �趨����ؼ�*/
        medialist_menu_set_curr_focus();
        /* ��ʾ�����ļ���*/
        medialist_menu_show_file_name();

        return D_OK;
    }

    return D_ERR;

}

/**@brief ȡ����һ��Ŀ¼��*/
static D_Result
medialist_menu_get_upper_folder( void )D_FUNCPOSTFIT
{
    D_Char* temp;

    temp = strrchr(media_list_data->mediaCurrFolder_utf8, '/');
    if(temp)
    {
        *temp = '\0';
        temp++;
        strcpy(media_list_data->mediaLastFolder_utf8, temp);
    }
    else
    {
        media_list_data->mediaLastFolder_utf8[0] = '\0';
        media_list_data->mediaCurrFolder_utf8[0] = '\0';
    }

    return D_OK;
}

/**@brief ���ҷ�����һ��Ŀ¼ʱ����ֵ*/
static D_ID
medialist_menu_get_last_focus(void)D_FUNCPOSTFIT
{
    if(media_list_data->mediaFocuLevel)
    {
        media_list_data->mediaFocuLevel--;
        media_list_data->mediaCurrFocus = media_list_data->mediaFocuStack[media_list_data->mediaFocuLevel];
    }

    return D_OK;
}

/** @brief ������һ��Ŀ¼*/
static D_Result
medialist_menu_return_up_folder( void )D_FUNCPOSTFIT
{
    if(media_list_data->mediaCurrFolder_utf8[0])
    {
        medialist_menu_get_upper_folder();
        medialist_menu_get_files_list(media_list_data->mediaCurrFolder_utf8);
        medialist_menu_get_last_focus();

        if(media_list_data->mediaFocuLevel == 0)
        {
            media_list_data->mediaCurrPartition = 0xFF;
        }

        /* �б�������ʾ*/
        medialist_menu_show_list_info();
        /* �趨����ؼ�*/
        medialist_menu_set_curr_focus();
        /* ��ʾ�����ļ���*/
        medialist_menu_show_file_name();
        return D_OK;
    }
    else
    {
        //return d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_ERR;
}

#if 0
static D_Result
medialist_menu_stop_play(void) D_FUNCPOSTFIT
{
    d_media_movie_stop();
    d_av_set_vid_blank(0, D_TRUE); /* ����*/
    media_list_data->mediaFilePlayFlag = D_FALSE;
    return D_OK;
}
#endif
/** @brief �˳�ȫ������ʱ�ص�*/
static D_Result
media_pic_fullscreen_hide_handler(D_U16 focus)D_FUNCPOSTFIT
{
    if(media_list_data)
    {
        //d_media_movie_stop();

        media_list_data->mediaFilePlayFlag = D_FALSE;
        // d_av_set_vid_blank(0, D_TRUE);

        media_list_data->mediaExitFullScreenFlag = D_FALSE;
        /* ����仯ʱ�������趨���㣬���ҳ��������ʾ*/
        if(media_list_data->mediaCurrFocus != focus)
        {
            D_U32 page_num;
            media_list_data->mediaCurrFocus = (D_U32)focus;

            /* ���㵱ǰҳ��, ҳ��仯ʱ��Ҫ�����趨ҳ������*/
            page_num = media_list_data->mediaCurrFocus / MEDIA_LIST_NUM_PER_PAGE;
            if(page_num != media_list_data->mediaCurrPage)
            {
                medialist_menu_show_list_info();
            }

            /* �趨����ؼ�*/
            medialist_menu_set_curr_focus();
            /* ��ʾ�����ļ���*/
            medialist_menu_show_file_name();
        }
    }

    return D_OK;
}

/** @brief ȷ�ϲ�������*/
static D_Result
medialist_menu_ok_action (void) D_FUNCPOSTFIT
{
    //medialist_menu_stop_play();
    if(Judge_Dir_Folder(&(media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus])))
    {
        medialist_menu_enter_next_folder(); /* ������һ��*/
    }
    else if(Judge_Up_Folder(&(media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus])))
    {
        medialist_menu_return_up_folder(); /* ������һ��*/
    }
    else if(Judge_Photo_File(&(media_list_data->mediaFileRset.ids[media_list_data->mediaCurrFocus])))
    {
        /* ����ý���ļ�*/
        if(D_OK == p_pic_full_screen_menu_show(media_list_data->mediaCurrPathName_utf8, &media_list_data->mediaFileRset, media_list_data->mediaCurrFocus, media_pic_fullscreen_hide_handler))
        {
            media_list_data->mediaExitFullScreenFlag = D_TRUE;
        }
    }

    return D_OK;
}

/** @brief USB������Ƴ�ʱ������̷���Ŀ¼ �б�*/
static D_Result
medialist_menu_check_disk(D_Bool plug, D_U32 vol) D_FUNCPOSTFIT
{
    D_U32 usb_status;

    if (!plug)
    {
        /* �γ�usbʱ�ж��ǵ�ǰ�������˳��˵�*/
        if( (media_list_data->mediaTotalPartition < 2) || ((D_U32)media_list_data->mediaCurrPartition == vol))
        {
            d_media_picture_stop();
           if(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN)
            {
                d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
            }
            d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
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
        media_list_data->mediaCurrPartition = 0xFF;
        media_list_data->mediaCurrFolder_utf8[0] = '\0';
        medialist_menu_get_files_list(media_list_data->mediaCurrFolder_utf8);
        media_list_data->mediaCurrFocus = D_MIN(media_list_data->mediaCurrFocus, (D_U32)(media_list_data->mediaFileRset.cnt - 1));

        /* û���̷�ʱ��������ʾ*/
        if(media_list_data->mediaTotalPartition == 0)
        {
            d_vis_show(media_list_data->vis_group_all, D_FALSE);
            medialist_menu_set_edit_status(D_FALSE);
            p_media_main_menu_set_enable(D_TRUE);
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
                            /* ������һ��Ŀ¼*/
                            //medialist_menu_stop_play();
                            medialist_menu_return_up_folder();
                        }
                    }
                    return D_OK;
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
            break;
        case D_EVT_HOTPLUG_MSG:
            medialist_menu_check_disk(evt->hotplug.plug, (D_U32)evt->hotplug.arg);
	     p_media_main_menu_set_enable(D_TRUE);
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            AtvMediaMenuStatus &= ~uCurrentMenuTpe;
            if(media_list_data)
            {
                PROJECT_FREE(media_list_data->mediaFileRset.ids);
                PROJECT_FREE(media_list_data);
                media_list_data = NULL;
            }
            d_media_picture_stop();
            d_media_picture_close();
        }
        break;
    }
    return D_ERR;
}

/** @brief ���ڳ�ʼ��*/
D_Result
pic_list_menu_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    media_list_data = (D_MediaPicListMenuData*)PROJECT_ALLOC(sizeof(D_MediaPicListMenuData));
    if(!media_list_data)
    {
        return D_ERR;
    }

    memset(media_list_data, 0x00, sizeof(D_MediaPicListMenuData));
    media_list_data->mediaCurrPartition = 0xFF;
    media_list_data->mediaCurrFocus = 0;
    media_list_data->mediaCurrPage = 0;
    media_list_data->menuEditFlag = D_TRUE;
    media_list_data->mediaExitFullScreenFlag = D_FALSE;
    media_list_data->mediaMenuCurrLang = p_conf_get_lang();
    media_list_data->win_frm = frm;
    media_list_data->vis_group_all = d_frame_get_control(frm, ID_MOVIE_LIST_GROUP_ALL);
    media_list_data->vis_file_name = d_frame_get_control(frm, ID_MOVIE_LIST_LABEL_FILENAME);

    media_list_data->mediaFileRset.max = MEDIA_FILE_MAX_CNT;
    media_list_data->mediaFileRset.cnt = 0;
    media_list_data->mediaFileRset.ids = (D_FSAttr*)PROJECT_ALLOC(sizeof(D_FSAttr) * (media_list_data->mediaFileRset.max));
    if(!media_list_data->mediaFileRset.ids)
    {
        return D_ERR;
    }

    /*��ʼ����ý������ƵͼƬ�ĸ��ԵĲ�������*/
    d_mediacodec_open();
    d_media_picture_open() ;
    d_media_picture_set_layer(D_GUI_LAYER_USER_0);

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

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);
        //d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, medialist_menu_window_handler);
    }

    media_list_data->sysUsbStatus = p_get_curr_usb_status();
    medialist_menu_get_files_list(media_list_data->mediaCurrFolder_utf8);

    /* û���̷�ʱ��������ʾ*/
    if(media_list_data->mediaTotalPartition == 0)
    {
        d_vis_show(media_list_data->vis_group_all, D_FALSE);
    }

    medialist_menu_set_edit_status(D_FALSE);
    medialist_menu_show_list_info();
    medialist_menu_show_file_name();

    AtvMediaMenuStatus |= uCurrentMenuTpe;
    return D_OK;
}

/** @brief ��ʾ��ý����Ƶ�б�˵�*/
D_Result
p_atv_media_picture_show (void) D_FUNCPOSTFIT
{
    if(d_frame_is_loaded(&pic_list_menu_window))
    {
        return D_OK;
    }
    uCurrentMenuTpe = ATV_MEDIA_MENU_STATUS_PHOTO;
    D_DUMP("p_atv_media_movie_show \n");
    return d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &pic_list_menu_window, D_CLEAR_NONE);
}
