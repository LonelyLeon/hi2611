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
#include "atv_media_picture_menu_window.c"

#define BUTTON_NUM 5
#define MEDIA_FULL_PIC_MENU_SHOW_TIME (5000)
static D_U32 focus_flag = 1;

/**@brief 多媒体用到的结构体*/
typedef struct
{
    D_HTimer mediaPicFullMenuTimer;

    //D_S16 rotate_flag;
    D_Visual *vis_win, *vis_direction_left, *vis_direction_right, *vis_play, *vis_pause,
             *vis_play_text, *vis_pause_text, *vis_last, *vis_next, *vis_left_rotate, *vis_right_rotate, *vis_lr_text, *vis_rr_text;
} MediaFullPicMenuData;

static D_S16 rotate_flag = 0;

//static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_play={-1, atv_IMG_ID_FS_Media_PictureMenu_Play, -1, NULL, };
//static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_pause={-1, atv_IMG_ID_FS_Media_PictureMenu_Pause, -1, NULL, };
//static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_play_focus={-1, atv_IMG_ID_FS_Media_PictureMenu_Play_Focus, -1, NULL, };
//static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_pause_focus={-1, atv_IMG_ID_FS_Media_PictureMenu_Pause_Focus, -1, NULL, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_play = { -1, atv_IMG_ID_FS_Media_PictureMenu_Pause, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_pause = { -1, atv_IMG_ID_FS_Media_PictureMenu_Play, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_play_focus = { -1, atv_IMG_ID_FS_Media_PictureMenu_Pause_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_pic_pause_focus = { -1, atv_IMG_ID_FS_Media_PictureMenu_Play_Focus, -1, NULL, };


static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_picture_play = {{&GUID_pic_play, &GUID_pic_play_focus, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_picture_pause = {{&GUID_pic_pause, &GUID_pic_pause_focus, NULL, }, 1, };

static MediaFullPicMenuData *full_pic_menu;
static D_U8 full_pic_play_state = 0;
extern void p_browse_picture(D_Bool next_or_prev); //false 为上一张图片，true为下一张
extern void p_set_picture_rotate(D_U8 flag);
extern D_U8 get_not_jpg_type_flag(void);

static D_Result
set_vis_focus (D_U32 flag) D_FUNCPOSTFIT;

void set_full_pic_play_state(D_U8 flag)
{
    full_pic_play_state = flag;
}

void set_full_pic_play_rotate(D_U8 flag)
{
    rotate_flag = flag;
}

D_U8 get_full_pic_play_state(void)
{
    return full_pic_play_state;
}

void Is_show_rotate_icon(D_Bool flag, D_Bool Is_auto_play)
{
    if(Is_auto_play)
    {
        if(focus_flag > 3 && flag)
        {
            focus_flag = 3;
            if(full_pic_menu)
            {
                set_vis_focus(focus_flag);
            }
        }
    }

    if(full_pic_menu)
    {
        if(flag)
        {
            d_vis_show(full_pic_menu->vis_lr_text, D_FALSE);
            d_vis_show(full_pic_menu->vis_rr_text, D_FALSE);
            d_vis_show(full_pic_menu->vis_left_rotate, D_FALSE);
            d_vis_show(full_pic_menu->vis_right_rotate, D_FALSE);
        }
        else
        {

            d_vis_show(full_pic_menu->vis_lr_text, D_TRUE);
            d_vis_show(full_pic_menu->vis_rr_text, D_TRUE);
            d_vis_show(full_pic_menu->vis_left_rotate, D_TRUE);
            d_vis_show(full_pic_menu->vis_right_rotate, D_TRUE);
        }
    }
}

static D_Result
set_vis_focus (D_U32 flag) D_FUNCPOSTFIT
{
    if(!full_pic_menu)
    {
        return D_ERR;
    }

    switch(flag)
    {
        case 1:
            d_vis_set_focus(full_pic_menu->vis_play);
            break;
        case 2:
            d_vis_set_focus(full_pic_menu->vis_last);
            break;
        case 3:
            d_vis_set_focus(full_pic_menu->vis_next);
            break;
        case 4:
            d_vis_set_focus(full_pic_menu->vis_left_rotate);
            break;
        case 5:
            d_vis_set_focus(full_pic_menu->vis_right_rotate);
            break;
        default:
            break;
    }

    return D_OK;
}


static void play_icon_show(D_Bool show)
{
    if(get_full_pic_play_state() == show)
    {
        d_vis_set_attribute(full_pic_menu->vis_play, (D_Ptr)&GUID_picture_play);
        d_label_set_text(full_pic_menu->vis_play_text, d_gui_get_text(atv_IDS_PAUSE));
    }
    else
    {
        d_vis_set_attribute(full_pic_menu->vis_play, (D_Ptr)&GUID_picture_pause);
        d_label_set_text(full_pic_menu->vis_play_text, d_gui_get_text(atv_IDS_PLAY));
    }
}

#if 0
static D_Result
media_picture_menu_set_direction(D_Bool show, D_Bool left) D_FUNCPOSTFIT
{
    D_Image* img_left = NULL;
    D_Image* img_right = NULL;

    if(show)
    {
        if(left)
        {
            img_left =  d_gui_get_image(atv_IMG_ID_button_left_focus);
            img_right = d_gui_get_image(atv_IMG_ID_button_right);
        }
        else
        {
            img_left =  d_gui_get_image(atv_IMG_ID_button_left);
            img_right = d_gui_get_image(atv_IMG_ID_button_right_focus);
        }
    }

    d_image_box_set_image(full_pic_menu->vis_direction_left, show ? img_left : NULL);
    d_image_box_set_image(full_pic_menu->vis_direction_right, show ? img_right : NULL);

    return D_OK;
}
#endif

static D_Result
media_full_pic_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(full_pic_menu)
    {
        if(full_pic_menu->mediaPicFullMenuTimer == D_INVALID_HANDLE)
        {
            full_pic_menu->mediaPicFullMenuTimer = d_timer_create(NULL, MEDIA_FULL_PIC_MENU_SHOW_TIME, d_gui_get_queue());
            if(full_pic_menu->mediaPicFullMenuTimer != D_INVALID_HANDLE)
            {
                d_vis_subscribe_evt(full_pic_menu->vis_win, D_EVT_TIMER_MASK, full_pic_menu->mediaPicFullMenuTimer);
            }
        }

        if(full_pic_menu->mediaPicFullMenuTimer != D_INVALID_HANDLE)
        {
            d_timer_reset(full_pic_menu->mediaPicFullMenuTimer, MEDIA_FULL_PIC_MENU_SHOW_TIME);
        }
    }

    return D_OK;
}

static D_Result
set_media_picture_menu_play_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_media_picture_menu_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                {
                    media_full_pic_reset_show_timer();
                    if(full_pic_play_state == 0)
                    {
                        full_pic_play_state = 1;
                        d_vis_set_attribute(full_pic_menu->vis_play, (D_Ptr)&GUID_picture_play);
                        d_label_set_text(full_pic_menu->vis_play_text, d_gui_get_text(atv_IDS_PAUSE));
                    }
                    else
                    {
                        full_pic_play_state = 0;
                        d_vis_set_attribute(full_pic_menu->vis_play, (D_Ptr)&GUID_picture_pause);
                        d_label_set_text(full_pic_menu->vis_play_text, d_gui_get_text(atv_IDS_PLAY));
                    }
                }
                break;
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
set_media_picture_menu_last_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                {
					rotate_flag = 0;
                    media_full_pic_reset_show_timer();
                    p_browse_picture(D_FALSE);
                    Is_show_rotate_icon(get_not_jpg_type_flag(), D_FALSE);
                }
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
set_media_picture_menu_next_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                {
					rotate_flag = 0;
                    media_full_pic_reset_show_timer();
                    p_browse_picture(D_TRUE);
                    Is_show_rotate_icon(get_not_jpg_type_flag(), D_FALSE);
                }
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
set_media_picture_left_rotate_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                {
                    media_full_pic_reset_show_timer();
                    rotate_flag --;
                    if(rotate_flag < 0)
                    {
                        rotate_flag = 3;
                    }
                    p_set_picture_rotate(rotate_flag);
                }
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
set_media_picture_right_rotate_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                {
                    media_full_pic_reset_show_timer();
                    rotate_flag = (rotate_flag + 1) % 4;
                    p_set_picture_rotate(rotate_flag);
                }
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
media_picture_menu_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame * frm = &atv_media_picture_menu_window;

    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    d_gui_close_frame(&atv_media_picture_menu_window);
                    return D_OK;
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    media_full_pic_reset_show_timer();
                    //media_picture_menu_set_direction(D_TRUE, D_TRUE);
                    if(get_not_jpg_type_flag() == 1)
                    {
                        focus_flag --;
                        if(focus_flag == 0)
                        {
                            focus_flag = 3;
                        }
                        set_vis_focus(focus_flag);
                    }
                    else
                    {
                        focus_flag --;
                        if(focus_flag == 0)
                        {
                            focus_flag = BUTTON_NUM;
                        }
                        set_vis_focus(focus_flag);
                    }
                }
                return D_OK;
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    media_full_pic_reset_show_timer();
                    //media_picture_menu_set_direction(D_TRUE, D_FALSE);
                    if(get_not_jpg_type_flag() == 1)
                    {
                        focus_flag ++;
                        if(focus_flag > 3)
                        {
                            focus_flag = 1;
                        }
                        set_vis_focus(focus_flag);
                    }
                    else
                    {
                        focus_flag ++;
                        if(focus_flag > BUTTON_NUM)
                        {
                            focus_flag = 1;
                        }
                        set_vis_focus(focus_flag);
                    }
                }
                return D_OK;
                break;
                default:
                    break;
            }

            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == full_pic_menu->mediaPicFullMenuTimer)
            {
                p_atv_media_picture_menu_hide();
            }
            break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);

            if (full_pic_menu)
            {
                if(full_pic_menu->mediaPicFullMenuTimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(full_pic_menu->mediaPicFullMenuTimer);
                    full_pic_menu->mediaPicFullMenuTimer = D_INVALID_HANDLE;
                }

                PROJECT_FREE(full_pic_menu);
                full_pic_menu = NULL;
            }
        }
        break;
    }
    return D_ERR;
}



D_Result
atv_media_picture_menu_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual           *vis;

    full_pic_menu = (MediaFullPicMenuData*)PROJECT_ALLOC(sizeof(MediaFullPicMenuData));
    if(!full_pic_menu)
    {
        return D_ERR;
    }

    focus_flag = 1;

    memset(full_pic_menu, 0x00, sizeof(MediaFullPicMenuData));
    //full_pic_menu->rotate_flag = 0;
    full_pic_menu->mediaPicFullMenuTimer = D_INVALID_HANDLE;

    //full_pic_menu->vis_direction_left = d_frame_get_control(frm, ID_PICFULL_IMG_LEFT);
    //full_pic_menu->vis_direction_right = d_frame_get_control(frm, ID_PICFULL_IMG_RIGHT);
    full_pic_menu->vis_play = d_frame_get_control(frm, ID_PICFULL_BUTTON_PLAY);
    full_pic_menu->vis_play_text = d_frame_get_control(frm, ID_PICFULL_LABLE_PLAY);
    full_pic_menu->vis_last = d_frame_get_control(frm, ID_PICFULL_BUTTON_LAST);
    full_pic_menu->vis_next = d_frame_get_control(frm, ID_PICFULL_BUTTON_NEXT);
    full_pic_menu->vis_left_rotate = d_frame_get_control(frm, ID_PICFULL_BUTTON_LEFTROTATE);
    full_pic_menu->vis_right_rotate = d_frame_get_control(frm, ID_PICFULL_BUTTON_RIGHTROTATE);
    full_pic_menu->vis_lr_text = d_frame_get_control(frm, ID_PICFULL_LABEL_LEFTROTATE);
    full_pic_menu->vis_rr_text = d_frame_get_control(frm, ID_PICFULL_LABLE_RIGHTROTATE);

    Is_show_rotate_icon(get_not_jpg_type_flag(), D_FALSE);

    play_icon_show(D_TRUE);

    d_vis_set_handler (full_pic_menu->vis_play, set_media_picture_menu_play_handler);
    d_vis_set_handler (full_pic_menu->vis_last, set_media_picture_menu_last_handler);
    d_vis_set_handler (full_pic_menu->vis_next, set_media_picture_menu_next_handler);
    d_vis_set_handler (full_pic_menu->vis_left_rotate, set_media_picture_left_rotate_handler);
    d_vis_set_handler (full_pic_menu->vis_right_rotate, set_media_picture_right_rotate_handler);

    vis = d_frame_get_control (frm, ID_PICFULL_GROUP_MENU);
    if (vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK , D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        full_pic_menu->vis_win = vis;
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_picture_menu_handler);
        media_full_pic_reset_show_timer();
    }
    //media_picture_menu_set_direction(D_TRUE, D_FALSE);
    return D_OK;
}

D_Result
p_atv_media_picture_menu_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&atv_media_picture_menu_window, D_GUI_LAYER_IME);
}

D_Result
p_atv_media_picture_menu_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame(&atv_media_picture_menu_window);
}

