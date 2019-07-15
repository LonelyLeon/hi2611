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
#include "atv_pop_position_window.c"


typedef struct
{
    D_Visual *vis_hval;
    D_Visual *vis_vval;
    D_Visual *vis_up;
    D_Visual    *vis_down;
    D_Visual    *vis_left;
    D_Visual    *vis_right;
    D_Char  v_strnum[10];
    D_S8    v_progress_val;
    D_Char  h_strnum[10];
    D_S8    h_progress_val;
    D_U32    menu_show_time;
} PositionStruct;

static PositionStruct *position_info;


/** @brief 事件处理*/
static D_Result
atv_pop_position_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                {
                    return d_gui_clear_menu();
                }
                break;

                case D_KEY_MENU:
				case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                {
                    return d_gui_upper_menu();
                }
                break;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    d_vis_set_focus(position_info->vis_left);
                    d_vis_enable(position_info->vis_hval, D_TRUE);
                    d_vis_enable(position_info->vis_vval, D_FALSE);

                    position_info->h_progress_val --;
                    if(position_info->h_progress_val < 0)
                        position_info->h_progress_val = 0;

                    sprintf(position_info->h_strnum, "%d", position_info->h_progress_val);
                    d_label_set_text (position_info->vis_hval, position_info->h_strnum);
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_vis_set_focus(position_info->vis_right);
                    d_vis_enable(position_info->vis_hval, D_TRUE);
                    d_vis_enable(position_info->vis_vval, D_FALSE);

                    position_info->h_progress_val ++;
                    if(position_info->h_progress_val > 100)
                        position_info->h_progress_val = 100;

                    sprintf(position_info->h_strnum, "%d", position_info->h_progress_val);
                    d_label_set_text (position_info->vis_hval, position_info->h_strnum);
                }
                break;

                case D_KEY_UP:
                case D_KEY_PNL_U:
                {
                    d_vis_set_focus(position_info->vis_up);
                    d_vis_enable(position_info->vis_vval, D_TRUE);
                    d_vis_enable(position_info->vis_hval, D_FALSE);

                    position_info->v_progress_val --;
                    if(position_info->v_progress_val < 0)
                        position_info->v_progress_val = 0;

                    sprintf(position_info->v_strnum, "%d", position_info->v_progress_val);
                    d_label_set_text (position_info->vis_vval, position_info->v_strnum);
                }
                break;

                case D_KEY_DOWN:
                case D_KEY_PNL_D:    
                {
                    d_vis_set_focus(position_info->vis_down);
                    d_vis_enable(position_info->vis_vval, D_TRUE);
                    d_vis_enable(position_info->vis_hval, D_FALSE);

                    position_info->v_progress_val ++;
                    if(position_info->v_progress_val > 100)
                        position_info->v_progress_val = 100;

                    sprintf(position_info->v_strnum, "%d", position_info->v_progress_val);
                    d_label_set_text (position_info->vis_vval, position_info->v_strnum);
                }
                break;

                default:
                    break;
            }
        }
        return D_OK;
        break;
        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            if(position_info)
            {
                PROJECT_FREE(position_info);
                position_info = NULL;
            }
        }
        break;

        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_pop_position_window_init(D_Frame *frm)
{
    D_Visual *vis;
	D_U32 time;

    position_info = (PositionStruct*)PROJECT_ALLOC(sizeof (PositionStruct));
    if (! position_info)
        return D_ERR;
    memset(position_info, 0, sizeof (PositionStruct));
	
    position_info->v_progress_val = 50;
    position_info->h_progress_val = 50;

    position_info->vis_hval = d_frame_get_control(frm, ID_POSITION_LABLE_HVAL);
    if(position_info->vis_hval)
    {
        sprintf(position_info->h_strnum, "%d", position_info->h_progress_val);
        d_label_set_text (position_info->vis_hval, position_info->h_strnum);
    }

    position_info->vis_vval = d_frame_get_control(frm, ID_POSITION_LABLE_VVAL);
    if(position_info->vis_vval)
    {
        d_vis_enable(position_info->vis_vval, D_FALSE);
        sprintf(position_info->v_strnum, "%d", position_info->v_progress_val);
        d_label_set_text (position_info->vis_vval, position_info->v_strnum);
    }

    position_info->vis_left = d_frame_get_control(frm, ID_POSITION_BUTTON_LEFT);
    if(position_info->vis_vval)
    {
        d_vis_set_focus(position_info->vis_left);
    }

    position_info->vis_up = d_frame_get_control(frm, ID_POSITION_BUTTON_UP);
    position_info->vis_down = d_frame_get_control(frm, ID_POSITION_BUTTON_DOWN);
    position_info->vis_right = d_frame_get_control(frm, ID_POSITION_BUTTON_RIGHT);

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_pop_position_window_handler);
    }
    return D_OK;
}

/** @brief 显示弹出框图像位置菜单*/
D_Result
p_atv_pop_position_show (void (*pFunc)()) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_pop_position_window, D_FALSE);
}

