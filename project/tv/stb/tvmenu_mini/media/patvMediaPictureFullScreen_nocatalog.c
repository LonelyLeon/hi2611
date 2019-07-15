/** @file
* @brief
* @author
* @date
*/
#include "dFP.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "dDebug.h"
#include "pMem.h"
#include "dTypes.h"
#include "pFile_Scan.h"
#include "dMedia.h"
#include "dCBMan.h"
#include "pPlayer.h"
#include "pPopMsg.h"
#include "pFile_Scan.h"
#include "pStbAtvMenus.h"
#include "pConvCode.h"
//#include "pSlidePlay.h"
//#include "pPhotoFullScreen_PlayMusic.h"
//#include "ptvShortCutKeyWin.h"
#include "patvMediaPictureFullMenu.h"
#include "atv_media_picture_full_screen_window.c"

#define PIC_FULL_X_ZOOM_LOCATION    0
#define PIC_FULL_Y_ZOOM_LOCATION    0
#define PIC_FULL_W_ZOOM_LOCATION    1280
#define PIC_FULL_H_ZOOM_LOCATION    720
typedef struct
{
    D_Char current_pic_file_path[D_PATH_LENGTH];
    D_Char next_pic_file_photo_name[D_PATH_LENGTH]; /*打印查找到的下一个文件名信息*/
    D_Char file_path[D_PATH_LENGTH];
    D_ID pic_index; /*记录当前播放图片在记录集中的序号*/
    D_PictureInfo    picture_info;
    D_VidWindow    pictureFullWin;
    D_Visual* vis_win, *vis_loading;
    D_Result (*handler)(D_U16 cur_index) D_FUNCPOSTFIT;
    D_Handle pic_play_cb_handle;
    D_Char cb_pic_file_path[D_PATH_LENGTH];
} D_PicFullScreenData;


static    D_U16 areanum;
static    D_U16 *areainfo;
static   D_Char  mediaFileName_temp[D_PATH_LENGTH];    /**临时当前文件名**/
static D_PicFullScreenData  *picture_full_data = NULL;
static TV_FILE_RSET_INFO           *picture_fs = NULL;
static D_HTimer             photo_timer = D_INVALID_HANDLE;
static D_Char               temp_data[D_PATH_LENGTH];
static D_U8         not_jpg_type;
static D_U8 fullscreen_prompt_msg_flag = D_FALSE;/*记录当前是否有播放提示消息显示*/

extern D_MSec get_media_pic_speed_flag(void);
extern void Is_show_rotate_icon(D_Bool flag, D_Bool Is_auto_play);

#if 0
/*根据图片类型来决定是否显示旋转和退出的图标。目前是只有jpeg jpg类型的支持，png gif和bmp暂时不支持旋转*/
static D_Result
full_screen_turn_icon(D_Char *fname)D_FUNCPOSTFIT
{
    D_Visual  *vis;
    D_U8 pic_type;
    D_Frame *frm = &picture_full_screen_window;

    pic_type = get_pic_type(fname);
    //vis = d_frame_get_control (frm, ID_PHOTO_FULL_IMAG_TURN);
    if (vis)
    {
        if ( pic_type == IMGTYPE_JPEG )
            d_vis_show(vis, D_TRUE);
        else
            d_vis_show(vis, D_FALSE);
    }
    return D_OK;
}
#endif

D_U8 get_not_jpg_type_flag(void)
{
    return not_jpg_type;
}

/**@brief 查找前一个或者后一个可播放的图片路径
*@param flag: D_TRUE 下一个 D_FALSE 上一个
*/
static D_Result
search_picture_next_or_prev(D_Bool flag)
{
    if (flag)
    {
        if (picture_full_data->pic_index < (areanum - 1))
            picture_full_data->pic_index++;
        else
            picture_full_data->pic_index = 0;
    }
    else
    {
        if (picture_full_data->pic_index >= 1)
            picture_full_data->pic_index--;
        else
            picture_full_data->pic_index = areanum - 1;
    }

    memset(picture_full_data->next_pic_file_photo_name, 0x00, sizeof(picture_full_data->next_pic_file_photo_name));
    strcpy(picture_full_data->next_pic_file_photo_name, picture_fs[areainfo[picture_full_data->pic_index]].path);

    p_cc_utf8_to_sys((D_U8*)picture_full_data->current_pic_file_path, sizeof(picture_full_data->current_pic_file_path),
                     (D_U8*)picture_full_data->next_pic_file_photo_name, strlen(picture_full_data->next_pic_file_photo_name));
    //D_DUMP("find next photo file:%s\n",picture_full_data->next_pic_file_photo_name);

    return D_OK;
}

void p_set_picture_rotate(D_U8 flag)
{
    D_PictureInfo  jpg_info;
  //  D_FSAttr *fsattr;
    D_VidWindow    Win = picture_full_data->pictureFullWin;

    d_timer_reset(photo_timer, get_media_pic_speed_flag());

    d_media_picture_stop();

  //  fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

    if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &jpg_info))
    {
        d_media_picture_stop();

        if (jpg_info.height > 8000 || jpg_info.width > 8000)
        {
            /*该图片文件获取信息失败不能播放*/
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            fullscreen_prompt_msg_flag = D_TRUE;
            return ;
        }
        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
        {
            if (jpg_info.height > 2000 || jpg_info.width > 2000)
            {
                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                fullscreen_prompt_msg_flag = D_TRUE;
                return ;
            }
        }
        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_JPG)
        {
            d_media_picture_stop();

            p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                 Win.y, Win.w, Win.h, 0, flag, PICTURE_OPEN_MODE_NORMAL);

        }
        else if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF && picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
        {
            // if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
            // {
            //     d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
            // }
            //  p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            // d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
            //                     Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
        }
        else
        {
            // d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
            //                      Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
        }
    }
    else
    {

        /*该图片文件获取信息失败不能播放*/
        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
        fullscreen_prompt_msg_flag = D_TRUE;
        return ;

    }

    return;
}

#if 0
void p_rotate_data(D_U8 *pic_data, D_U32 length)D_FUNCPOSTFIT
{
    memset(temp_data, 0x00, D_PATH_LENGTH);
    strncpy(temp_data, pic_data, length);
}

D_U8 *p_get_rotate_data(void)
{
    return temp_data;
}

void p_show_stop_icon(void)
{
    D_Frame *frm = &picture_full_screen_window;
    if(p_get_silde_play_flag() == 1)
    {
        p_set_silde_play_flag(0);
        d_vis_show(d_frame_get_control (frm, D_LABLE_PIC_FULL_STOP), D_TRUE);
    }
    else
    {
        p_set_silde_play_flag(1);
        d_vis_show(d_frame_get_control (frm, D_LABLE_PIC_FULL_STOP), D_FALSE);
    }
}

void p_show_stop_icon_ex(D_Bool Is_show)
{
    D_Frame *frm = &picture_full_screen_window;
    if(Is_show == D_TRUE)
    {
        d_vis_show(d_frame_get_control (frm, D_LABLE_PIC_FULL_STOP), D_TRUE);
    }
    else
    {
        d_vis_show(d_frame_get_control (frm, D_LABLE_PIC_FULL_STOP), D_FALSE);
    }
}
#endif

void p_browse_picture(D_Bool next_or_prev) //false 为上一张图片，true为下一张
{
    //D_FSAttr *fsattr;

    if (fullscreen_prompt_msg_flag)
    {
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
        fullscreen_prompt_msg_flag = D_FALSE;
    }
    if(next_or_prev)
    {
        d_media_picture_stop();
        search_picture_next_or_prev(D_TRUE);

        if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
        {
            D_VidWindow    Win = picture_full_data->pictureFullWin;
           // fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
                not_jpg_type = 1;
            else
                not_jpg_type = 0;

            if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
            {
                /*该图片文件获取信息失败不能播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                fullscreen_prompt_msg_flag = D_TRUE;
                return ;
            }
            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
            {
                if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                {
                    /*该图片文件尺寸大于芯片解码能力不支持播放*/
                    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                       d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                    fullscreen_prompt_msg_flag = D_TRUE;
                    return ;
                }
            }
            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
            {
                p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            }

            // if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
            {
                d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
				p_show_osd_window(D_TRUE);
            }
            d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                 Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
        }
        else
        {
            /*该图片文件获取信息失败不能播放*/
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE),2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            fullscreen_prompt_msg_flag = D_TRUE;
            return ;

        }


    }
    else
    {
        d_media_picture_stop();
        search_picture_next_or_prev(D_FALSE);

        if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
        {
            D_VidWindow    Win = picture_full_data->pictureFullWin;
           // fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
                not_jpg_type = 1;
            else
                not_jpg_type = 0;

            if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
            {
                /*该图片文件获取信息失败不能播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                fullscreen_prompt_msg_flag = D_TRUE;
                return ;
            }
            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
            {
                if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                {
                    /*该图片文件尺寸大于芯片解码能力不支持播放*/
                    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                       d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                    fullscreen_prompt_msg_flag = D_TRUE;
                    return ;
                }
            }
            if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
            {
                p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
            }
            //if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
            {
                d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
				p_show_osd_window(D_TRUE);
            }
            d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                 Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
        }
        else
        {
            /*该图片文件获取信息失败不能播放*/
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            fullscreen_prompt_msg_flag = D_TRUE;
            return ;

        }

    }
}

/** @brief 事件处理*/
static D_Result
pic_full_screen_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_media_picture_full_screen_window;
    D_FSAttr *fsattr;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                {
                    d_image_box_set_image(picture_full_data->vis_loading, NULL);
					p_show_osd_window(D_FALSE);
                    if(get_full_pic_play_state() == 1)
                        return D_OK;

                    if (fullscreen_prompt_msg_flag)
                    {
                        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                        fullscreen_prompt_msg_flag = D_FALSE;
                    }
                    d_media_picture_stop();
                    search_picture_next_or_prev(D_TRUE);

                    if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
                    {
                        D_VidWindow    Win = picture_full_data->pictureFullWin;
                        //fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
                            not_jpg_type = 1;
                        else
                            not_jpg_type = 0;

                        if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
                        {
                            /*该图片文件获取信息失败不能播放*/
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                               d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                            fullscreen_prompt_msg_flag = D_TRUE;
                            return D_ERR;
                        }
                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
                        {
                            if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                            {
                                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                                fullscreen_prompt_msg_flag = D_TRUE;
                                return D_ERR;
                            }
                        }

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
                        {
                            p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
                        }

                        // if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
                        {
                            d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
							p_show_osd_window(D_TRUE);
                        }
                        d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                             Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);

                        //d_media_picture_play(picture_full_data->next_pic_file_photo_name, picture_full_data->pictureFullWin.x,
                        //picture_full_data->pictureFullWin.y, picture_full_data->pictureFullWin.w,
                        //picture_full_data->pictureFullWin.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
                    }
                    else
                    {
                        //d_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
                        //D_GUI_LAYER_MESSAGE,D_POP_MSG_ERROR,
                        //d_gui_get_text(tv_IDS_PROMPT), d_gui_get_text(tv_IDS_PLAY_FAILED), 1500,
                        //D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
                        {
                            /*该图片文件获取信息失败不能播放*/
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                            fullscreen_prompt_msg_flag = D_TRUE;
                            return D_ERR;

                        }

                    }
                    //p_rotate_data(picture_full_data->next_pic_file_photo_name,sizeof(picture_full_data->next_pic_file_photo_name));
                }
                return D_OK;
                break;

                case D_KEY_UP:
                case D_KEY_PNL_U:
                {
                    d_image_box_set_image(picture_full_data->vis_loading, NULL);
					p_show_osd_window(D_FALSE);
                    if(get_full_pic_play_state() == 1)
                        return D_OK;

                    if (fullscreen_prompt_msg_flag)
                    {
                        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                        fullscreen_prompt_msg_flag = D_FALSE;
                    }
                    d_media_picture_stop();
                    search_picture_next_or_prev(D_FALSE);
                    if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
                    {
                        D_VidWindow    Win = picture_full_data->pictureFullWin;
                      //  fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
                            not_jpg_type = 1;
                        else
                            not_jpg_type = 0;

                        if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
                        {
                            /*该图片文件获取信息失败不能播放*/
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                               d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                            fullscreen_prompt_msg_flag = D_TRUE;
                            return D_ERR;
                        }
                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
                        {
                            if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                            {
                                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE),2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                                fullscreen_prompt_msg_flag = D_TRUE;
                                return D_ERR;
                            }
                        }

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
                        {
                            p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
                        }

                        //if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
                        {
                            d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
							p_show_osd_window(D_TRUE);
                        }
                        d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                             Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);

                        //d_media_picture_play(picture_full_data->next_pic_file_photo_name, picture_full_data->pictureFullWin.x,
                        //                    picture_full_data->pictureFullWin.y, picture_full_data->pictureFullWin.w,
                        //                    picture_full_data->pictureFullWin.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
                    }
                    else
                    {

                        /*该图片文件获取信息失败不能播放*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        fullscreen_prompt_msg_flag = D_TRUE;
                        return D_ERR;

                        //d_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
                        //D_GUI_LAYER_MESSAGE,D_POP_MSG_ERROR,
                        //d_gui_get_text(tv_IDS_PROMPT), d_gui_get_text(tv_IDS_PLAY_FAILED), 1500,
                        //D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL, 0);
                    }
                    //p_rotate_data(picture_full_data->next_pic_file_photo_name,sizeof(picture_full_data->next_pic_file_photo_name));
                }
                return D_OK;
                break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    return D_OK;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    p_atv_media_picture_menu_show();
                    return D_OK;
                    break;

                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                case D_KEY_ESC:
                {
                    if (fullscreen_prompt_msg_flag)
                    {
                        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                        fullscreen_prompt_msg_flag = D_FALSE;
                    }
                    d_image_box_set_image(picture_full_data->vis_loading, NULL);
					p_show_osd_window(D_FALSE);
                    d_media_picture_stop();

                    if (picture_full_data->handler)
                    {
                        picture_full_data->handler(picture_full_data->pic_index);
                    }

                    //p_photofullscreen_playmusic_destroy();
                    //set_full_pic_play_state(1);
                    //p_set_first_enter_flag(0);
                    //p_set_music_button_flag(1);
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                }
                return D_OK;
                break;

                default:
                    break;
            }
        }

        break;
        case D_EVT_TIMER:
        {
            if(evt->timer.htimer == photo_timer)
            {
                if(get_full_pic_play_state() == 1)
                {
                    d_timer_reset(photo_timer, 120 * 1000);
                    D_DUMP("\n time is  ok  \n");
                    //set_speed_timer();
                    if (fullscreen_prompt_msg_flag)
                    {
                        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                        fullscreen_prompt_msg_flag = D_FALSE;
                    }
                    d_media_picture_stop();

                    search_picture_next_or_prev(D_TRUE);
                    //p_rotate_data(picture_full_data->next_pic_file_photo_name,sizeof(picture_full_data->next_pic_file_photo_name));

                    if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
                    {
                        D_VidWindow    Win = picture_full_data->pictureFullWin;
                      //fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
                            not_jpg_type = 1;
                        else
                            not_jpg_type = 0;

                        Is_show_rotate_icon(not_jpg_type, D_TRUE);
                        if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
                        {
                            /*该图片文件获取信息失败不能播放*/
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                               d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                            d_timer_reset(photo_timer, get_media_pic_speed_flag());

                            fullscreen_prompt_msg_flag = D_TRUE;
                            return D_ERR;
                        }

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
                        {
                            if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                            {
                                /*该图片文件尺寸大于芯片解码能力不支持播放*/
                                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                                d_timer_reset(photo_timer, get_media_pic_speed_flag());
                                fullscreen_prompt_msg_flag = D_TRUE;
                                return D_ERR;
                            }
                        }

                        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
                        {
                            p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
                        }

                        // if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
                        {
                            d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
							p_show_osd_window(D_TRUE);
                        }
                        d_media_picture_play(picture_full_data->next_pic_file_photo_name, Win.x,
                                             Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
                    }
                    else
                    {
                        /*该图片文件获取信息失败不能播放*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE),2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);

                        d_timer_reset(photo_timer, get_media_pic_speed_flag());

                        fullscreen_prompt_msg_flag = D_TRUE;
                        return D_ERR;

                    }

                    //d_media_picture_play(picture_full_data->next_pic_file_photo_name, picture_full_data->pictureFullWin.x,
                    //                     picture_full_data->pictureFullWin.y, picture_full_data->pictureFullWin.w,
                    //                     picture_full_data->pictureFullWin.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
                }
            }

            D_DUMP("\n time come~~~  \n");
        }
        break;
        case D_EVT_USER2:
            if((evt->user.handle == (D_Handle)frm) && (evt->user.param1 == USER_MSG_PARAM1_MEDIA_PIC_PLAY_END))
            {
                if(strcmp(picture_full_data->cb_pic_file_path, picture_full_data->next_pic_file_photo_name) == 0)
                {
                    D_U32 pic_decode_ret = (D_U32)evt->user.param2;
                    if(pic_decode_ret == 0)/*解码失败*/
                    {
                        /*该图片文件播放时解码出错 或者文件本身有错*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        fullscreen_prompt_msg_flag = D_TRUE;
                    }
                    else if (pic_decode_ret == 1)/*内存不足*/
                    {
                        /*该图片文件解码过程中内存空间不足*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        fullscreen_prompt_msg_flag = D_TRUE;
                    }
                    else if(pic_decode_ret == 2)
                    {
                        /* 成功*/
                    }

                    /* 定时器恢复*/
                    if(photo_timer != D_INVALID_HANDLE)
                    {
                        d_timer_reset(photo_timer, get_media_pic_speed_flag());
                    }
                    /* 失败成功都取消转圈加载图标显示*/
                    d_image_box_set_image(picture_full_data->vis_loading, NULL);
					p_show_osd_window(D_FALSE);
                }
            }
            break;
        case D_EVT_DESTROY:
        {
            //p_tv_volume_window_hide();
            //p_photofullscreen_playmusic_destroy();
			p_gui_reset_vis_count();
            if (fullscreen_prompt_msg_flag)
            {
                d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                fullscreen_prompt_msg_flag = D_FALSE;
            }
            p_atv_media_picture_menu_hide();
            d_vis_unsubscribe_evt (vis);

            if(photo_timer != D_INVALID_HANDLE)
            {
                d_timer_destroy(photo_timer);
                photo_timer = D_INVALID_HANDLE;
            }
            if (picture_full_data)
            {
                d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
                picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
                PROJECT_FREE(picture_full_data);
                picture_full_data = NULL;
            }
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN;
        }
        break;

        default:
            break;
    }

    return D_ERR;
}
/** @brief 播放图片结果 的回调函数*/
static void media_picture_fullplay_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_Pic_Cb *cb_ret = (D_Pic_Cb*)obj_data;
    D_Frame *frm = &atv_media_picture_full_screen_window;

    if(picture_full_data && frm == (D_Frame *)cb_data)
    {
        if(strcmp(cb_ret->path, picture_full_data->next_pic_file_photo_name) == 0)
        {
            D_UserMsg msg;

            strcpy(picture_full_data->cb_pic_file_path, cb_ret->path);
            /* 由于此函数是图片播放相关任务调用，不是gui任务调用，
            因此不允许直接调用gui相关的显示函数，比如隐藏加载图标，
            显示图片播放失败等提示，gui通常不允多线程调用，因此
            因此这里通过消息的方式，在窗口handler里进行处理。 @qiny 20150923*/
            msg.type = D_MSG_USER2;
            msg.handle = (D_Handle)frm;
            msg.param1 = USER_MSG_PARAM1_MEDIA_PIC_PLAY_END;
            msg.param2 = (D_U32)cb_ret->pic_decode_ret;
            msg.param3 = (D_U32)picture_full_data->cb_pic_file_path;
            d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
        }
    }
}

/** @brief 窗口初始化*/
D_Result
atv_media_picture_full_screen_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual           *vis;
    D_S32  device_state = 0;
    D_Result    ret = D_ERR;
    D_FSAttr *fsattr;

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        picture_full_data->vis_win = vis;

        /*设置显示的坐标*/
        d_vis_get_pos(picture_full_data->vis_win , &(picture_full_data->pictureFullWin.x), &(picture_full_data->pictureFullWin.y));
        picture_full_data->pictureFullWin.w = picture_full_data->vis_win->rect.w;
        picture_full_data->pictureFullWin.h = picture_full_data->vis_win->rect.h;

        //fsattr = &(picture_fs->ids[picture_full_data->pic_index]);

        picture_full_data->vis_loading = d_frame_get_control(frm, ID_FULL_LOADING_IMAGE);

        picture_full_data->pic_play_cb_handle = d_cbman_subscribe(PL_MEDIA_PIC_PALY, D_INVALID_HANDLE, media_picture_fullplay_cb, (D_Ptr)frm);


        if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_JPG)
            not_jpg_type = 1;
        else
            not_jpg_type = 0;

        if(picture_fs[areainfo[picture_full_data->pic_index]].class_type == D_FILE_SCAN_FMT_Photo)
        {
            if(D_OK == d_media_picture_get_info(picture_full_data->next_pic_file_photo_name, &picture_full_data->picture_info))
            {
                D_VidWindow    Win = picture_full_data->pictureFullWin;
                if (picture_full_data->picture_info.height > 8000 || picture_full_data->picture_info.width > 8000)
                {
                    if (picture_full_data)
                    {
                        d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
                        picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
                        PROJECT_FREE(picture_full_data);
                        picture_full_data = NULL;
                    }
                    /*该图片文件获取信息失败不能播放*/
                    d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                       d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                    fullscreen_prompt_msg_flag = D_TRUE;
                    return D_ERR;
                }
                if(picture_fs[areainfo[picture_full_data->pic_index]].file_type == D_FILE_TYPE_PNG /*|| fsattr->file_type == D_FILE_TYPE_BMP*/)
                {
                    if (picture_full_data->picture_info.height > 2000 || picture_full_data->picture_info.width > 2000)
                    {
                        if (picture_full_data)
                        {
                            d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
                            picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
                            PROJECT_FREE(picture_full_data);
                            picture_full_data = NULL;
                        }
                        /*该图片文件尺寸大于芯片解码能力不支持播放*/
                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                           d_gui_get_text(atv_IDS_NOT_SUPPORT_PIC_SIZE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        fullscreen_prompt_msg_flag = D_TRUE;
                        return D_ERR;
                    }
                }

                if(picture_fs[areainfo[picture_full_data->pic_index]].file_type != D_FILE_TYPE_GIF)
                {
                    p_gui_auto_match_window_format(&(Win.x), &(Win.y), &(Win.w), &(Win.h));
                }

                //if(fsattr->file_type == D_FILE_TYPE_PNG || fsattr->file_type == D_FILE_TYPE_BMP)
                {
                    d_image_box_set_image(picture_full_data->vis_loading, d_gui_get_image(atv_IMG_ID_media_loading));
					p_show_osd_window(D_TRUE);
                }

                ret = d_media_picture_play(picture_full_data->current_pic_file_path, Win.x,
                                           Win.y, Win.w, Win.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);
            }
            else
            {
                d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
                picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
                /*该图片文件获取信息失败不能播放*/
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                fullscreen_prompt_msg_flag = D_TRUE;
                return D_ERR;

            }

        }
        // ret = d_media_picture_play(picture_full_data->current_pic_file_path, picture_full_data->pictureFullWin.x,
        //                            picture_full_data->pictureFullWin.y, picture_full_data->pictureFullWin.w,
        //                            picture_full_data->pictureFullWin.h, 0, 0, PICTURE_OPEN_MODE_NORMAL);

        if ( ret != D_OK )
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                               d_gui_get_text(atv_IDS_NOT_SUPPORT_FILE), 2000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);

            /*该图片文件获取信息失败不能播放*/
            if (picture_full_data)
            {
                d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
                picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
                PROJECT_FREE(picture_full_data);
                picture_full_data = NULL;
            }
            D_ERROR("p_picture_full_screen_menu_show get current_file_path fail.\n");
            fullscreen_prompt_msg_flag = D_TRUE;
            return D_ERR;
        }

        //p_photofullscreen_playmusic(picture_full_data->curr_paration);
        photo_timer = d_timer_create(NULL, get_media_pic_speed_flag(), d_gui_get_queue());
        if(photo_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, photo_timer);
        }
        /*设定窗口事件回调*/
        d_vis_subscribe_evt(vis, D_EVT_USER_MASK, (D_Handle)frm);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, pic_full_screen_window_handler);
    }
	p_gui_set_vis_count(34);
    set_full_pic_play_state(0);

    //vis = d_frame_get_control (frm, D_LABLE_PIC_FULL_STOP);  //停止播放图片图标
    //d_vis_show(vis, D_TRUE);

    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_PHOTO_FULLSCREEN;
	p_show_osd_window(D_TRUE);
    return D_OK;
}
/** @brief 全屏播放图片控制窗口显示*/
D_Result p_pic_full_screen_menu_show(D_Char *path , D_U16* area_info,  D_U16 area_num, TV_FILE_RSET_INFO* fs,D_ID index, D_Result (*handler) (D_U16 param)D_FUNCPOSTFIT)D_FUNCPOSTFIT
{
    D_Char *tok;
    D_Result ret = D_ERR;

    picture_full_data = (D_PicFullScreenData *) PROJECT_ALLOC ( sizeof (D_PicFullScreenData) );
    if (!picture_full_data)
        return D_ERR;

    memset(picture_full_data, 0x00, sizeof(D_PicFullScreenData));

    picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
    picture_fs = fs;
    picture_full_data->handler = handler;
    picture_full_data->pic_index = index;
    areainfo = area_info;
    areanum = area_num;

    memset(picture_full_data->current_pic_file_path, 0x00, sizeof(picture_full_data->current_pic_file_path));
    strncpy(picture_full_data->current_pic_file_path, path, sizeof(picture_full_data->current_pic_file_path));

    memset(picture_full_data->file_path, 0x00, sizeof(picture_full_data->file_path));
    strncpy(picture_full_data->file_path, path, sizeof(picture_full_data->file_path));
    strcpy(picture_full_data->next_pic_file_photo_name, path);
    tok = strrchr(picture_full_data->file_path, '/');
    if(tok)
    {
        tok ++;
        *tok = '\0';
    }
    //p_rotate_data(picture_full_data->current_pic_file_path,sizeof(picture_full_data->current_pic_file_path));
    ret = d_gui_enter_menu_new(ATV_MEDIA_MENU_ID, &atv_media_picture_full_screen_window, D_CLEAR_NONE);
    if(ret != D_OK && picture_full_data)
    {
        d_cbman_unsubscribe(picture_full_data->pic_play_cb_handle);
        picture_full_data->pic_play_cb_handle = D_INVALID_HANDLE;
        PROJECT_FREE(picture_full_data);
        picture_full_data = NULL;
    }
    return ret;
}


