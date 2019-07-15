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
#include "pFp.h"
#include "atv_image_mode_window.c"


typedef struct
{
    D_VidInput input;
    D_U8   image_mode;
    D_Bool ntsc_flag;
    D_U8 image_mode_flag;
    D_HTimer timer;
    D_U32    menu_show_time;
} D_ImageModeData;

static D_Char* mode_str[4] =  {"standard","mild","user","light"};
static D_ImageModeData *image_mode_data = NULL;

/** @brief 复位显示定时器*/
static D_Result
image_mode_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(image_mode_data && image_mode_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(image_mode_data->timer, image_mode_data->menu_show_time);
    }

    return D_OK;
}

static D_Result
change_image_mode(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &image_mode_window;
    D_Visual *vis;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis,mode_str[image_mode_data->image_mode]);
        d_gui_update();
    }
    p_vip_set_ImageMode( image_mode_data->input,image_mode_data->image_mode,image_mode_data->ntsc_flag);
    p_tvconf_set_cur_imagemode(&image_mode_data->image_mode, p_vip_get_dbinput(image_mode_data->input));
    return D_OK;
}
/** @brief 事件处理*/
static D_Result
image_mode_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *label_vis;
    switch (evt->type)
    {
        case D_EVT_FP:
            {
                case D_KEY_IMAGE:
                    image_mode_reset_show_timer();
                    image_mode_data->image_mode_flag = (image_mode_data->image_mode + 1) % 4;
                    image_mode_data->image_mode = image_mode_data->image_mode_flag;
                    change_image_mode();
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == image_mode_data->timer)
            {  
               p_image_mode_win_hide(); 
            }
            break;
        case D_EVT_DESTROY:
            {
                d_vis_unsubscribe_evt (vis);
                if(image_mode_data)
                {
                    if(image_mode_data->timer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(image_mode_data->timer);
                    }
                    PROJECT_FREE(image_mode_data);
                    image_mode_data = NULL;
                }              
            }
        break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
image_mode_window_init(D_Frame *frm)
{
    D_Visual *vis;
    
    image_mode_data = (D_ImageModeData*)PROJECT_ALLOC(sizeof(D_ImageModeData));
    if(!image_mode_data)
    {
        return D_ERR;
    }
    memset(image_mode_data, 0, sizeof(D_ImageModeData));
    image_mode_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_imagemode(&image_mode_data->image_mode, p_vip_get_dbinput(image_mode_data->input));
    image_mode_data->image_mode_flag = image_mode_data->image_mode;
    image_mode_data->ntsc_flag = p_vip_get_ntscflag();

    image_mode_data->menu_show_time = 3 * 1000;

    vis = d_frame_get_control (frm, ID_LABEL_INFO);
    if(vis)
    {
        d_label_set_text(vis,mode_str[image_mode_data->image_mode]);
    }
    
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        image_mode_data->timer = d_timer_create (NULL, image_mode_data->menu_show_time, d_gui_get_queue ());
        if(image_mode_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, image_mode_data->timer);
        }
        
        d_vis_set_handler (vis, image_mode_window_handler);
        d_vis_subscribe_evt (vis, D_EVT_KEY_MASK, D_INVALID_HANDLE);
    }

    return D_OK;
}

/** @brief 菜单显示*/
D_Result
p_image_mode_win_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&image_mode_window, D_GUI_LAYER_VIDEO_MESSAGE);
}

/** @brief 菜单隐藏*/
D_Result
p_image_mode_win_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&image_mode_window);
}

