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
#include "adjust_reset_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

typedef struct
{
    D_U32    menu_show_time;
} D_AdjustResetData;

static D_AdjustResetData *reset_data = NULL;


/** @brief 确定复位事件处理*/
static D_Result
button_reset_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
        {
        }
        break;

        default:
            break;
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_reset_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &adjust_reset_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_RESET_BUTTON_RESET);
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
                    d_vis_enable(vis_button, D_TRUE);
                    d_vis_set_focusable(vis_button, D_TRUE);
                    d_vis_set_focus(vis_button);
                    break;
                case D_KEY_BACK:
				case D_KEY_PNL_MENU:
                    d_vis_enable(vis_button, D_FALSE);
                    d_vis_set_focusable(vis_button, D_FALSE);
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:    
                    return d_gui_clear_menu();
                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(reset_data)
            {
                PROJECT_FREE(reset_data);
                reset_data = NULL;
            }
        }
        break;

        default:
            break;
    }
}

D_Result
adjust_reset_window_init(D_Frame *frm)
{
    D_Visual *vis;

    reset_data = (D_AdjustResetData*)PROJECT_ALLOC(sizeof(D_AdjustResetData));
    if(!reset_data)
    {
        return D_ERR;
    }	
    memset(reset_data, 0x00, sizeof(D_AdjustResetData));
    vis = d_frame_get_control(frm, ID_RESET_BUTTON_RESET); //确定复位
    if(vis)
    {
        d_vis_set_handler (vis, button_reset_handler);
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK) & (~ D_EVT_UP_DOWN_KEY_MASK) & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_reset_window_handler);
    }
    return D_OK;
}

/** @brief 复位菜单*/
D_Result
p_atv_adjust_reset_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&adjust_reset_window, D_FALSE);
}

