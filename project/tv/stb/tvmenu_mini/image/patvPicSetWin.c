#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "atv_pic_set_window.c"

typedef enum
{
    P_PICSET_MENU_CONTRAST = 0,
    P_PICSET_MENU_BRIGHT = 1,
    P_PICSET_MENU_COLOR = 2,
    P_PICSET_MENU_SHARPNESS = 3,
    P_PICSET_MENU_TINT = 4,
    P_PICSET_MENU_OTHERS,
} P_PicSetMenuStatus;

typedef struct
{
    D_Bool enable;
    D_Char strnum[10];
    D_S16    value;
    D_S16    progress_val;
    D_PMODE_SET param;
    D_VidInput input;
    D_Visual *vis_progress, *vis_label;
    D_U8 video_mode;
} D_PicSetData;

static D_PicSetData *pic_set_data = NULL;
static P_PicSetMenuStatus pic_set_menu_status;

static D_U32 atv_pic_get_param(D_PMODE_SET *param);
static D_Result atv_pic_set_param(D_VidInput input, D_U8 val);
static D_Result atv_pic_save_param(D_PMODE_SET *param, D_VidInput input, D_U8 val);


/** @brief 画进度条的进度图片*/
D_Result
p_vis_progress_draw (D_Visual *vis, D_Bool enable) D_FUNCPOSTFIT
{
    D_Coord w;

    if(vis->element.progress.val)
    {
        w = vis->element.progress.val * (vis->rect.w  - 4) / vis->element.progress.cnt;
        if(enable)
        {
            gui_tool_draw_fill_round_rect(vis, 2, 2, w, vis->rect.h - 4, 6, 0xfffaba00);
        }
        else
        {
            gui_tool_draw_fill_round_rect(vis, 2, 2, w, vis->rect.h - 4, 6, 0xff3372c9);
        }
    }
    return D_OK;
}

/** @brief 进度条事件处理*/
static D_Result
atv_pic_set_progress_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch (evt->type)
    {
        case D_EVT_DRAW:
            p_vis_progress_draw(vis,  pic_set_data->enable);
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 更新显示*/
static D_Result
pic_progress_update (D_FPKey key, D_Bool repeat) D_FUNCPOSTFIT
{
    D_S8 step = 0;

    if(repeat)
    {
        step = D_MIN((step + 1), 5);
    }
    else
    {
        step = 0;
    }

    switch (key)
    {
        case D_KEY_LEFT:
        case D_KEY_PNL_L:
            pic_set_data->progress_val = (pic_set_data->progress_val - 1 - step);
            if(pic_set_data->progress_val < 0)
            {
                pic_set_data->progress_val = 0;
            }
            break;
        case D_KEY_RIGHT:
        case D_KEY_PNL_R:
            pic_set_data->progress_val = (pic_set_data->progress_val + 1 + step);
            if(pic_set_data->progress_val > 100)
            {
                pic_set_data->progress_val = 100;
            }
            break;
        default:
            break;
    }
    d_progress_bar_set_val(pic_set_data->vis_progress, pic_set_data->progress_val);
    sprintf(pic_set_data->strnum, "%d", pic_set_data->progress_val);
    d_label_set_text(pic_set_data->vis_label, pic_set_data->strnum);
    atv_pic_set_param(pic_set_data->input, pic_set_data->progress_val);

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_pic_set_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    //按OK键进入滚动条后,显示黄色滚动条
                    d_vis_enable(pic_set_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(pic_set_data->vis_progress, pic_set_data->progress_val);
                    d_vis_enable(pic_set_data->vis_progress, D_TRUE);

                    if(! pic_set_data->enable)
                    {
                        pic_set_data->enable = D_TRUE;
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    //按menu键返回后,显示蓝色滚动条
                    d_vis_enable(pic_set_data->vis_progress, D_FALSE);
                    d_progress_bar_set_val(pic_set_data->vis_progress, pic_set_data->progress_val);
                    d_vis_enable(pic_set_data->vis_progress, D_TRUE);

                    if(pic_set_data->enable)
                    {
                        pic_set_data->enable = D_FALSE;
                        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                    		d_gui_upper_menu();		//FOR exit Key 20190628
                        return d_gui_upper_menu();
                    }
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(pic_set_data->enable)
                    {
                        pic_progress_update(evt->fp.key, evt->fp.repeat);
                    }
                    break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(pic_set_data->enable)
                    {
                        pic_progress_update(evt->fp.key, evt->fp.repeat);
                    }
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(pic_set_data->enable)
                    {
                        return D_OK;
                    }
                    else
                    {
                        return D_ERR;
                    }
                case D_KEY_SOURCE:
                case D_KEY_SCREEN:
                    d_gui_clear_menu();
                    return D_ERR;
                case D_KEY_MUTE:
                    return D_ERR;
                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(pic_set_data)
            {
                if(pic_set_data->progress_val != pic_set_data->value)
                {
                    pic_set_data->value = pic_set_data->progress_val;
                    atv_pic_save_param(&pic_set_data->param, pic_set_data->input, pic_set_data->value);
                }
                PROJECT_FREE(pic_set_data);
                pic_set_data = NULL;
            }
        }
        break;

        default:
            break;
    }
    return D_ERR;
}


/** @brief 对比度窗口初始化*/
D_Result
pic_set_window_init(D_Frame *frm)
{
    D_Visual *vis;

    pic_set_data = (D_PicSetData*)PROJECT_ALLOC(sizeof(D_PicSetData));
    if(!pic_set_data)
    {
        return D_ERR;
    }
    memset(pic_set_data, 0x00, sizeof(D_PicSetData));

    pic_set_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_imagemode(&pic_set_data->video_mode, p_vip_get_dbinput( pic_set_data->input));
    p_tvconf_get_pmodeset_param(&pic_set_data->param, p_vip_get_dbinput( pic_set_data->input), pic_set_data->video_mode);
    pic_set_data->value = (D_S16)atv_pic_get_param(&pic_set_data->param);
    pic_set_data->progress_val = D_MIN(pic_set_data->value, 100);
    pic_set_data->enable = D_FALSE;
    vis = d_frame_get_control (frm, ID_ATV_PROGRESS_PIC);
    if(vis)
    {
        pic_set_data->vis_progress = vis;
        d_progress_bar_set_val(vis, pic_set_data->progress_val);
        d_vis_set_solve_draw_evt(vis, D_TRUE);
        d_vis_set_handler(vis, atv_pic_set_progress_handler);
    }

    vis = d_frame_get_control(frm, ID_ATV_LABEL_PIC);
    if(vis)
    {
        sprintf(pic_set_data->strnum, "%d", pic_set_data->progress_val);
        pic_set_data->vis_label = vis;
        d_label_set_text(vis, pic_set_data->strnum);
    }

    vis = d_frame_get_control(frm, ID_ATV_GROUP_PICWIN);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        if(pic_set_data->video_mode != TV_USER_PMODE_NUM)
        {
//            d_vis_unsubscribe_one_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        }

        d_vis_set_handler (vis, atv_pic_set_window_handler);
    }
    return D_OK;
}

/*取得菜单显示的进度值*/
static D_U32 atv_pic_get_param(D_PMODE_SET *param)D_FUNCPOSTFIT
{
    D_U32 val = 0;

    if(pic_set_menu_status == P_PICSET_MENU_CONTRAST)
    {
        val = param->contrast;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_BRIGHT)
    {
        val = param->brightness;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_COLOR)
    {
        val = param->color;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_SHARPNESS)
    {
        val = param->sharpness;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_TINT)
    {
        val = param->tint;
    }

    return val;
}
/*设置参数到驱动*/
static D_Result atv_pic_set_param(D_VidInput input, D_U8 val)D_FUNCPOSTFIT
{
    if(pic_set_menu_status == P_PICSET_MENU_CONTRAST)
    {
        p_vip_set_Constrast(input, val);//对比度
    }
    else if(pic_set_menu_status == P_PICSET_MENU_BRIGHT)
    {
        p_vip_set_Brightness(input, val);//亮度
    }
    else if(pic_set_menu_status == P_PICSET_MENU_COLOR)
    {
        p_vip_set_Saturation(input, val);//饱和度
    }
    else if(pic_set_menu_status == P_PICSET_MENU_SHARPNESS)
    {
        p_vip_set_Sharpness(input, val);//清晰度
    }
    else if(pic_set_menu_status == P_PICSET_MENU_TINT)
    {
        p_vip_set_Hue(input, val);//清晰度
    }
    return D_OK;
}
/*保存设置参数*/
static D_Result atv_pic_save_param(D_PMODE_SET *param, D_VidInput input, D_U8 val)D_FUNCPOSTFIT
{
    D_U8 mode = TV_USER_PMODE_NUM;

    if(pic_set_menu_status == P_PICSET_MENU_CONTRAST)
    {
        param->contrast = val;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_BRIGHT)
    {
        param->brightness = val;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_COLOR)
    {
        param->color = val;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_SHARPNESS)
    {
        param->sharpness = val;
    }
    else if(pic_set_menu_status == P_PICSET_MENU_TINT)
    {
        param->tint = val;
    }
    if(pic_set_data->video_mode != TV_USER_PMODE_NUM)
    {
        p_tvconf_set_cur_imagemode(&mode, p_vip_get_dbinput( pic_set_data->input));
    }
    p_tvconf_set_pmodeset_param(param, p_vip_get_dbinput(input) , TV_USER_PMODE_NUM);//用户模式

    return D_OK;
}


/** @brief 显示对比度窗口*/
D_Result
p_atv_contrast_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&pic_set_window))
    {
        pic_set_menu_status = P_PICSET_MENU_CONTRAST;
        d_gui_enter_menu (&pic_set_window, D_FALSE);
    }
    return D_OK;
}

/** @brief 显示亮度菜单*/
D_Result
p_atv_bright_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&pic_set_window))
    {
        pic_set_menu_status = P_PICSET_MENU_BRIGHT;
        d_gui_enter_menu (&pic_set_window, D_FALSE);
    }
    return D_OK;
}

/** @brief 显示色度窗口*/
D_Result
p_atv_color_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&pic_set_window))
    {
        pic_set_menu_status = P_PICSET_MENU_COLOR;
        d_gui_enter_menu (&pic_set_window, D_FALSE);
    }
    return D_OK;
}

/** @brief 显示清晰度窗口*/
D_Result
p_atv_definition_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&pic_set_window))
    {
        pic_set_menu_status = P_PICSET_MENU_SHARPNESS;
        d_gui_enter_menu (&pic_set_window, D_FALSE);
    }
    return D_OK;
}
/** @brief 显示色调窗口*/
D_Result
p_atv_tint_show (void) D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&pic_set_window))
    {
        pic_set_menu_status = P_PICSET_MENU_TINT;
        d_gui_enter_menu (&pic_set_window, D_FALSE);
    }
    return D_OK;
}

