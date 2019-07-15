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
#include "atv_exchange_window.c"

#define MAX_CHAN_CNT            P_DB_MAX_SRV_CNT

typedef struct
{
    D_Visual *cur_lable_vis;
    D_Visual *exchange_lable_vis;
    D_Char  cur_strnum[10];
    D_S16   cur_val;
    D_Char  exchange_strnum[10];
    D_S16   exchange_val;
    D_DBRecset      rset;
    D_ID                chan_ids[MAX_CHAN_CNT];
    D_S16       position[MAX_CHAN_CNT]; //记录节目的chan_num
    D_U32 srvcnt;

} ExchangeStruct;

static ExchangeStruct *exchange_info;
/** @brief 事件处理*/
static D_Result exchange_chan_fun(D_S16 cur_val, D_S16 exchange_val)D_FUNCPOSTFIT
{
    D_U16 j = 0;
    D_ID id_temp;
    
    if((cur_val != -1) && (exchange_val != -1) && (exchange_val != cur_val))
    {
        cur_val -= 1;
        exchange_val -= 1;
        /* 交换而不是排序*/
        id_temp = exchange_info->rset.ids[cur_val];
        exchange_info->rset.ids[cur_val] = exchange_info->rset.ids[exchange_val];
        exchange_info->rset.ids[exchange_val] = id_temp;
        
        //d_dbase_program_move(&exchange_info->rset, cur_val, exchange_val);
        d_dbase_set_rset_en(0);
        for(j = D_MIN(cur_val, exchange_val); j <= D_MAX(cur_val, exchange_val); j++)
        {
            d_dbase_update_srv_num(exchange_info->rset.ids[j], exchange_info->position[j]); /*移动结束，更新频道号*/
        }
        d_dbase_flush ();
        memset((void *)(exchange_info->position), 0, (MAX_CHAN_CNT * sizeof(D_U16)));
        d_dbase_program_chnum_in_rset(&exchange_info->rset, exchange_info->position);
        //需要添加切换节目的功能
        return D_OK;
    }
    return D_ERR;
}
/** @brief 事件处理*/
static D_Result play_chan_fun(D_S16 chan_num)D_FUNCPOSTFIT
{
    D_DBSrvID db_srv_id;

    db_srv_id = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_ATV);
    if (db_srv_id != -1)
    {
        p_stb_player_play_srv(0, db_srv_id);
    }
    return D_ERR;
}


/** @brief 事件处理*/
static D_Result
atv_cur_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_exchange_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    if(exchange_info->srvcnt > 1)
                    {
                        exchange_info->cur_val --;
                        if(exchange_info->cur_val < 1)
                        {
                            exchange_info->cur_val = exchange_info->srvcnt;
                        }
                        sprintf(exchange_info->cur_strnum, "%d", exchange_info->cur_val);
                        d_label_set_text(exchange_info->cur_lable_vis, exchange_info->cur_strnum);
                        play_chan_fun(exchange_info->cur_val);
                    }
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {

                    if(exchange_info->srvcnt > 1)
                    {
                        exchange_info->cur_val ++;
                        if(exchange_info->cur_val > exchange_info->srvcnt)
                        {
                            exchange_info->cur_val = 1;
                        }
                        sprintf(exchange_info->cur_strnum, "%d", exchange_info->cur_val);
                        d_label_set_text(exchange_info->cur_lable_vis, exchange_info->cur_strnum);
                        play_chan_fun(exchange_info->cur_val);
                    }
                }
                break;

                default:
                    break;
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
atv_exchange_button_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_exchange_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                {
                    if(exchange_info->srvcnt > 1)
                    {
                        exchange_info->exchange_val--;
                        if(exchange_info->exchange_val < 1)
                        {
                            exchange_info->exchange_val = exchange_info->srvcnt;
                        }
                        sprintf(exchange_info->exchange_strnum, "%d", exchange_info->exchange_val);
                        d_label_set_text(exchange_info->exchange_lable_vis, exchange_info->exchange_strnum);
                    }
                }
                break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    if(exchange_info->srvcnt > 1)
                    {
                        exchange_info->exchange_val ++;
                        if(exchange_info->exchange_val > exchange_info->srvcnt)
                        {
                            exchange_info->exchange_val = 1;
                        }
                        sprintf(exchange_info->exchange_strnum, "%d", exchange_info->exchange_val);
                        d_label_set_text(exchange_info->exchange_lable_vis, exchange_info->exchange_strnum);
                    }
                }
                break;

                default:
                    break;
            }
        }
        return D_OK;
        break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
atv_exchange_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_MENU:
				case D_KEY_PNL_MENU:
                {
                    return d_gui_upper_menu();
                }
                break;
                case D_KEY_ESC:
                    return d_gui_clear_menu();
                case D_KEY_OK:
				case D_KEY_PNL_SOURCE:
                {
                    if(exchange_chan_fun(exchange_info->cur_val, exchange_info->exchange_val) == D_OK)
                    {
                        D_S16 temp;

                        temp = exchange_info->cur_val;
                        exchange_info->cur_val = exchange_info->exchange_val;
                        exchange_info->exchange_val = temp;

                        sprintf(exchange_info->cur_strnum, "%d", exchange_info->cur_val);
                        d_label_set_text(exchange_info->cur_lable_vis, exchange_info->cur_strnum);

                        sprintf(exchange_info->exchange_strnum, "%d", exchange_info->exchange_val);
                        d_label_set_text(exchange_info->exchange_lable_vis, exchange_info->exchange_strnum);
                    }
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
            if(exchange_info)
            {
                PROJECT_FREE(exchange_info);
                exchange_info = NULL;
            }
        }
        break;
        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_exchange_window_init(D_Frame *frm)
{
    D_Visual *vis;

    exchange_info = PROJECT_ALLOC(sizeof (ExchangeStruct));
    if (! exchange_info)
        return D_ERR;

    memset(exchange_info, 0, sizeof (ExchangeStruct));

    exchange_info->srvcnt = d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_ATV);

    d_dbase_rset_init (&exchange_info->rset, MAX_CHAN_CNT, exchange_info->chan_ids);
    d_dbase_get_srvs_by_type_ex(&exchange_info->rset, D_FALSE, D_DB_SRV_ATV, D_FALSE, 0);
    d_dbase_program_chnum_in_rset(&exchange_info->rset, exchange_info->position);

    vis = d_frame_get_control (frm, ID_EXCHANGE_GROUP_FUN);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, ID_EXCHANGE_BUTTON_FUN1);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_cur_button_handler);
    }

    exchange_info->cur_lable_vis = d_frame_get_control (frm, ID_EXCHANGE_LABLE_CUR_TEXT);
    if(exchange_info->cur_lable_vis)
    {
        exchange_info->cur_val = p_stb_player_get_curr_chan_num(0, NULL);
        exchange_info->cur_val = D_MAX(1, exchange_info->cur_val); /*避免无节目时显示-1*/
        sprintf(exchange_info->cur_strnum, "%d", exchange_info->cur_val);
        d_label_set_text(exchange_info->cur_lable_vis, exchange_info->cur_strnum);
    }

    vis = d_frame_get_control (frm, ID_EXCHANGE_BUTTON_FUN2);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_exchange_button_handler);
    }

    exchange_info->exchange_lable_vis = d_frame_get_control (frm, ID_EXCHANGE_LABLE_EXCHANGE_TEXT);
    if(exchange_info->exchange_lable_vis)
    {
        exchange_info->exchange_val = p_stb_player_get_curr_chan_num(0, NULL);
        exchange_info->exchange_val = D_MAX(1, exchange_info->exchange_val); /*避免无节目时显示-1*/
        sprintf(exchange_info->exchange_strnum, "%d", exchange_info->exchange_val);
        d_label_set_text(exchange_info->exchange_lable_vis, exchange_info->exchange_strnum);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_exchange_window_handler);
    }
    return D_OK;
}

/** @brief 显示频道交换菜单*/
D_Result
p_atv_exchange_show (void(*pFunc)(void)) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_exchange_window, D_FALSE);
}

