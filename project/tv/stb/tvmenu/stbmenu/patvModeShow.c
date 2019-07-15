#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dAV.h"
#include "pFp.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "mode_input_window.c"


static D_Bool ps_mode_flag;
static D_U8 ps_mode;

typedef struct
{
    D_HTimer timer;
    D_U32    menu_show_time;
} D_ModeInputData;

static D_ModeInputData *mode_input_data = NULL;


D_U32 ps_mode_flag_show[] = {atv_IDS_PICTURE_MODE , atv_IDS_SOUND_MODE};
D_U32 ps_mode_show[2][4] = {{atv_IDS_STANDARD , atv_IDS_MILD , atv_IDS_USER , atv_IDS_LIGHT},{atv_IDS_STANDARD , atv_IDS_THEATRE , atv_IDS_MUSIC , atv_IDS_MOVIE}};

/** @brief 复位显示定时器*/
static D_Result
reset_show_timer(void) D_FUNCPOSTFIT
{
    if(mode_input_data && mode_input_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(mode_input_data->timer, mode_input_data->menu_show_time * 1000);
    }

    return D_OK;
}


static D_Result
mode_input_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_SCREEN:
                    return d_gui_close_frame (&mode_input_window);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == mode_input_data->timer)
            {
                return d_gui_close_frame(&mode_input_window);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(mode_input_data)
            {
                if(mode_input_data->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(mode_input_data->timer);
                }
                PROJECT_FREE(mode_input_data);
                mode_input_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;

}


D_Result
mode_input_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual * vis;

    mode_input_data = (D_ModeInputData*)PROJECT_ALLOC(sizeof(D_ModeInputData));
    if(!mode_input_data)
    {
        return D_ERR;
    }

    memset(mode_input_data, 0x00, sizeof(D_ModeInputData));

    mode_input_data->menu_show_time = 1;;

    vis = d_frame_get_control(frm, ID_LABEL_PS_MODE);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text(ps_mode_flag_show[ps_mode_flag]));
    }
	
    vis = d_frame_get_control(frm, ID_LABEL_MODE);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text(ps_mode_show[ps_mode_flag][ps_mode]));
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_set_handler (vis, mode_input_window_handler);

        mode_input_data->timer = d_timer_create (NULL, mode_input_data->menu_show_time * 1000, d_gui_get_queue ());
        if(mode_input_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, mode_input_data->timer);
        }
        /*设定窗口遥控器、面板按键事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

    }

}

/** @breif 图像声音模式显示窗口*/
D_Result
p_atv_mode_input_show (D_Bool p_mode_flag , D_U8 mode) D_FUNCPOSTFIT
{
	ps_mode_flag = p_mode_flag;
	ps_mode = mode;

    return d_gui_open_frame (&mode_input_window, D_GUI_LAYER_HIGHEST);
}




