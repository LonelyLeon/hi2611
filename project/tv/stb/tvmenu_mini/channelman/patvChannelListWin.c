#include <stdio.h>
#include <string.h>
#include "pMem.h"
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pStbAtvMenus.h"
#include "dadporting.h"
#include "patvGuiResource.h"
#include "pPlayer.h"
#include "channel_list_window.c"


#define BUFFER_LEN  64

#define CHAN_LIST_ROW_CNT       10///16   目前显示列表的行数为6 
#define CHAN_NUM_BUF_LEN        4
#define CHAN_NAME_BUF_LEN       64
#define MAX_CHAN_CNT            1000


#define BOUQUET_ID_MIN              8700
#define BOUQUET_ID_MAX          8701

typedef struct
{
    D_Char          chan_num[CHAN_LIST_ROW_CNT][CHAN_NUM_BUF_LEN];
    D_Char          chan_name[CHAN_LIST_ROW_CNT][CHAN_NAME_BUF_LEN];
    D_Char          chan_info[BUFFER_LEN];
    D_DBRecset      rset;
    D_ID            chan_ids[MAX_CHAN_CNT];
} ChanListData;
static ChanListData  *list_data;

static D_DBBouqID curr_bouq_id;
static D_ID curr_play_srv = -1;///存储上一次聚焦的值。
static D_U16 get_list_num_by_srvid(D_DBSrvID srv_id)
{
    D_U16 i;
    D_U16 col = 0;

    for(i = 0; i < list_data->rset.cnt; i++)
    {
        if(srv_id == list_data->rset.ids[i])
        {
            col = i;
            break;
        }
    }

    return col;
}


/** @brief获取节目列表数据*/
static D_Result get_list_data(D_Visual *vis)
{
    D_DBSrvID srv_id;
    D_U16 col = 0;
    D_StbPlayer *player;
    player = p_stb_get_player (0);

    d_dbase_rset_empty(&list_data->rset);///如果rset为空将没有节目显示出来。

    if(curr_bouq_id == BOUQUET_ID_MIN)
    {
        if (d_dbase_has_any_srv (D_DB_SRV_TV))
        {
            D_DUMP ("HAVE TV \n");
            d_dbase_get_srvs_by_type (&list_data->rset, D_DB_SRV_TV, D_FALSE, 0);
            /** @brief 取得当前服务ID*/
            if(!player->play_radio)
            {
                col = get_list_num_by_srvid(player->tv_id);
            }
        }
        else
        {
            D_INFO ("NO HAVE TV\n");
        }

    }
    else if(curr_bouq_id == BOUQUET_ID_MAX)
    {
        if (d_dbase_has_any_srv (D_DB_SRV_RADIO))
        {
            D_DUMP ("HAVE RADIO \n");
            d_dbase_get_srvs_by_type (&list_data->rset, D_DB_SRV_RADIO, D_FALSE, 0);
            /** @brief 取得当前服务ID*/
            if(player->play_radio)
            {
                col = get_list_num_by_srvid(player->radio_id);
            }
        }
        else
        {
            D_INFO ("NO HAVE RADIO \n");
        }
    }

    d_list_set_max_row (vis, list_data->rset.cnt);///设置列表最大行数
    d_list_set_focus(vis, col, 0); ///第一行聚焦
    return D_OK;
}

/** @brief 更新列表显示*/
static D_Result
chanlist_update_list (D_Visual *vis) D_FUNCPOSTFIT
{
    D_ID                start, i;
    D_DBSrvInfo sinfo;
    D_DBSrvID   srv = -1;
    D_Image     *img;

    start = d_list_get_first_line_id (vis);
    for (i = start; i < start + CHAN_LIST_ROW_CNT; i++)
    {
        if (i >= list_data->rset.cnt)
        {
            /*清空显示*/

            d_list_set_text (vis, i, 0, NULL);
            d_list_set_text (vis, i, 1, NULL);
            if(i == 0) ///无节目，显示无节目。
            {

                if(curr_bouq_id == BOUQUET_ID_MIN)
                    strncpy (list_data->chan_name[0], "没有电视节目", sizeof (list_data->chan_name[0]) - 1);
                else
                    strncpy (list_data->chan_name[0], "没有广播节目", sizeof (list_data->chan_name[0]) - 1);

                d_list_set_text (vis, i, 1, list_data->chan_name[0]);
            }

        }
        else
        {
            D_ID    row = i - start;

            srv = list_data->rset.ids[i];
            if (d_dbase_get_srv_info (srv, &sinfo) >= 0)
            {
                /*显示频道号*/
                sprintf (list_data->chan_num[row],  "%03d", sinfo.chan_num);
                d_list_set_text (vis, i, 0, list_data->chan_num[row]);

                /*显示频道名*/
                if (strlen (sinfo.name))
                {
                    if(sinfo.ca_flag)
                    {
                        sprintf(list_data->chan_info, "%s  ($)", sinfo.name);
                    }
                    else
                    {
                        sprintf(list_data->chan_info, "%s", sinfo.name);
                    }
                    strncpy (list_data->chan_name[row], list_data->chan_info, sizeof (list_data->chan_name[row]) - 1);
                }
                d_list_set_text (vis, i, 1, list_data->chan_name[row]);
            }
        }
    }

    return D_OK;
}


static D_Result set_select_list_title(void)D_FUNCPOSTFIT
{
    D_Visual *vis = NULL;
    D_Frame *frm = &channel_list_window;
    D_Char *title = NULL;
    /*显示电视或广播节目列表标题*/
    vis = d_frame_get_control(frm, ID_CHANNEL_LIST_LABEL_LIST);
    if (vis)
    {
        if(curr_bouq_id == BOUQUET_ID_MIN) ///如果是电视节目列表
        {
            d_label_set_text(vis, "广播列表"); //设置成广播节目列表
            curr_bouq_id = BOUQUET_ID_MAX;
        }
        else  if(curr_bouq_id == BOUQUET_ID_MAX) ///curr_bouq_id的值是通过邋邋change_list_type改变的。
        {
            curr_bouq_id = BOUQUET_ID_MIN;
            d_label_set_text(vis, "电视列表");
        }
    }
    return D_OK;
}
/** @brie列表控件回调函数*/
static D_Result
program_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch (evt->type)
    {
        case D_EVT_DATA_CHANGED:
            chanlist_update_list(vis);
            break;
        default:
            break;
    }
    return D_ERR;
}
/** @brief 事件处理*/
static D_Result
channel_list_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &channel_list_window;
    D_Visual    *list;
    D_ID focus, srv;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_select_list_title();
                    list = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
                    get_list_data(list);
                    chanlist_update_list(list);
                    return D_OK;
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    list = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
                    focus = d_list_get_focus (list, NULL, NULL);
                    if ((focus >= 0) && (focus < list_data->rset.cnt))
                    {
                        srv = list_data->chan_ids[focus];

                        if(curr_play_srv != srv)
                        {
                            // 播放节目，不退出
                            curr_play_srv = srv;
                            p_stb_player_play_srv (0, srv);
                        }
                        else
                        {
                            // 节目已经在播放退出。
                            d_gui_clear_menu ();
                        }

                    }
                    return D_OK;
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            PROJECT_FREE(list_data);
            break;
        default:
            break;
    }

    return D_ERR;
}
/** @brief 设置列表*/
d_set_tv_radio_list(D_U8 id)
{
    if(id == 0)
    {
        curr_bouq_id = BOUQUET_ID_MIN;///初始化为电视节目列表
        return D_OK;
    }
    else if(id != 0)
    {
        curr_bouq_id = BOUQUET_ID_MAX;///初始化为广播节目列表
        return D_OK;

    }
    return D_ERR;
}

/** @brief 窗口初始化*/
D_Result
channel_list_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_Result ad_check = D_ERR;

    list_data = (ChanListData*) PROJECT_ALLOC (sizeof (ChanListData));
    memset(list_data, 0x00, sizeof(ChanListData));
    curr_play_srv = -1;
    
    d_dbase_rset_init (&list_data->rset, MAX_CHAN_CNT, list_data->chan_ids);

    vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LIST);
    if (vis)
    {
        d_vis_set_focus(vis);
        d_vis_set_handler(vis, program_list_handler);
        get_list_data(vis);
        chanlist_update_list(vis);
    }

    if(list_data->rset.cnt)
    {
        curr_play_srv = p_stb_player_get_curr_srv(0);
    }
    vis = d_frame_get_control (frm, ID_CHANNEL_LIST_LABEL_LIST);

    if(curr_bouq_id == BOUQUET_ID_MIN) ///如果是电视节目列表
    {
        d_label_set_text(vis, "电视列表"); ///设置成电视节目列表
    }
    else  if(curr_bouq_id == BOUQUET_ID_MAX)
    {
        d_label_set_text(vis, "广播列表");
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, channel_list_window_handler);
    }
    
    return D_OK;
}
/** @breif 显示窗口*/
D_Result
p_atv_tv_chan_list_show (void) D_FUNCPOSTFIT
{
    d_set_tv_radio_list(0);
    return d_gui_enter_menu (&channel_list_window, D_TRUE);
}


D_Result
p_atv_radio_chan_list_show (void) D_FUNCPOSTFIT
{
    d_set_tv_radio_list(1);
    return d_gui_enter_menu (&channel_list_window, D_TRUE);

}

