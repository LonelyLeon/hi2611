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
#include "atv_order_ch_window.c"

  
typedef struct
{
    D_Char strnum[10];
    D_S16   progress_val;
    D_U32   chan_cnt;
    D_U32    menu_show_time;
    D_DBID          ids[256];
    D_Bool first_flag;
} D_OrderChannelData;

static D_OrderChannelData *orderchannel_data = NULL;

static D_S16 get_order_ch_num(void)
{
    return get_OrderTime_chan();
}

static void set_order_ch_num(D_S16 ch_num)
{
    ch_num = (ch_num <= 0) ? (-1) : ch_num;
    set_OrderTime_chan(ch_num);
}

/** @brief 事件处理*/
static D_Result
order_ch_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            //实现功能
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_order_ch_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_order_ch_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_ORDERCH_BUTTON_CH);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                    if(orderchannel_data->first_flag == D_TRUE)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

                        d_vis_enable(vis_button, D_TRUE);
                        d_vis_set_focusable(vis_button, D_TRUE);
                        d_vis_set_focus(vis_button);

                        orderchannel_data->first_flag = D_FALSE;
                    }
                    break;

                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(orderchannel_data->first_flag == D_FALSE)
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        d_vis_enable(vis_button, D_FALSE);
                        d_vis_set_focusable(vis_button, D_FALSE);

                        orderchannel_data->first_flag = D_TRUE;
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                        return d_gui_clear_menu();
                    }
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    if(orderchannel_data->chan_cnt == 0)
                    {
                        break;
                    }

                    if(orderchannel_data->progress_val <= 0)
                    {
                        orderchannel_data->progress_val = 0;
                        break;
                    }

                    orderchannel_data->progress_val --;
                    set_order_ch_num(orderchannel_data->progress_val);

                    if(orderchannel_data->progress_val <= 0)
                    {
                        sprintf(orderchannel_data->strnum, "off");
                    }
                    else
                    {
                        sprintf(orderchannel_data->strnum, "%d", orderchannel_data->progress_val);
                    }

                    vis = d_frame_get_control(frm, ID_ORDERCH_BUTTON_CH);
                    if(vis)
                    {
                        d_button_set_text (vis, orderchannel_data->strnum);
                    }
                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if(orderchannel_data->chan_cnt == 0)
                    {
                        break;
                    }
                    if(orderchannel_data->progress_val >= orderchannel_data->chan_cnt)
                    {
                        orderchannel_data->progress_val = orderchannel_data->chan_cnt;
                        break;
                    }
                    orderchannel_data->progress_val ++;
                    set_order_ch_num(orderchannel_data->progress_val);
                    sprintf(orderchannel_data->strnum, "%d", orderchannel_data->progress_val);
                    vis = d_frame_get_control(frm, ID_ORDERCH_BUTTON_CH); //预约频道
                    if(vis)
                    {
                        d_button_set_text (vis, orderchannel_data->strnum);
                    }
                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(orderchannel_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(orderchannel_data->first_flag == D_TRUE)
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
            if(orderchannel_data)
            {
                PROJECT_FREE(orderchannel_data);
                orderchannel_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_order_ch_window_init(D_Frame *frm)
{
    D_Visual *vis;
    D_U32 time;

    orderchannel_data = (D_OrderChannelData*)PROJECT_ALLOC(sizeof(D_OrderChannelData));
    if(!orderchannel_data)
    {
        return D_ERR;
    }
    memset(orderchannel_data, 0x00, sizeof(D_OrderChannelData));
    orderchannel_data->chan_cnt = d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_ATV);
    if(orderchannel_data->chan_cnt == 0)
    {
        set_order_ch_num(-1);
    }
    orderchannel_data->progress_val = get_order_ch_num();
    orderchannel_data->first_flag = D_TRUE;

    if(orderchannel_data->progress_val <= 0)
    {
        orderchannel_data->progress_val = 0;
        sprintf(orderchannel_data->strnum, "off");
    }
    else
    {
        orderchannel_data->progress_val = D_MIN(orderchannel_data->chan_cnt, orderchannel_data->progress_val);
        sprintf(orderchannel_data->strnum, "%d", orderchannel_data->progress_val);
    }

    vis = d_frame_get_control(frm, ID_ORDERCH_BUTTON_CH); //预约频道
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_button_set_text (vis, orderchannel_data->strnum);
        d_vis_set_handler (vis, order_ch_button_handler);
    }

    vis = d_frame_get_control (frm, ID_ORDERCH_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & (~ D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_order_ch_window_handler);
    }
    return D_OK;
}

/** @brief 显示预约频道菜单*/
D_Result
p_atv_order_ch_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_order_ch_window, D_FALSE);
}

