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
#include "atv_radio_icon_window.c"

#define BUFFER_LEN (64)
#define FLUSH_WIN (1000)
#define USER_WINDOW_W D_SCREEN_HOR_RESOLUTION
#define USER_WINDOW_H D_SCREEN_VER_RESOLUTION

static D_Coord menu_pos_x = 0;
static D_Coord menu_pos_y = 0;
static D_Bool flag_x = D_TRUE;
static D_Bool flag_y = D_TRUE;
static D_ID radio_db_srv_id = -1;

/** @brief 内部管理数据*/
typedef struct 
{
	D_HTimer	flush_timer;
    D_DBSrvInfo srvinfo;
	D_Char		chan_name[BUFFER_LEN];
} TvRadioInfoData;

static TvRadioInfoData *radio_icon = NULL;


static D_Result
atv_radio_icon_window_falsh_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_radio_icon_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, 0);

    if(flag_x)
    {
        menu_pos_x = menu_pos_x + 16;
        if((menu_pos_x + vis->rect.w) > USER_WINDOW_W)
        {
            flag_x = D_FALSE;
        }
    }
    else
    {
        menu_pos_x = menu_pos_x - 16;
        if(menu_pos_x < 0)
        {
            flag_x = D_TRUE;
        }
    }
    if(flag_y)
    {
        menu_pos_y = menu_pos_y + 16;
        if((menu_pos_y + vis->rect.h) > USER_WINDOW_H)
        {
            flag_y = D_FALSE;
        }
    }
    else
    {
        menu_pos_y = menu_pos_y - 16;
        if(menu_pos_y < 0)
        {
            flag_y = D_TRUE;
        }
    }

    d_vis_set_pos(vis, menu_pos_x, menu_pos_y, vis->rect.w, vis->rect.h);

    return D_OK;
}
/** @brief 事件处理*/
static D_Result
atv_radio_icon_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_TIMER:
            if(evt->timer.htimer == radio_icon->flush_timer)
            {
                atv_radio_icon_window_falsh_show();
                d_timer_reset(radio_icon->flush_timer, FLUSH_WIN);
            }
            break;
        case D_EVT_DESTROY:
			{
				d_vis_unsubscribe_evt (vis);
                if(radio_icon)
                {
                    if(radio_icon->flush_timer != D_INVALID_HANDLE)
                    {
                        d_timer_destroy(radio_icon->flush_timer);
    					radio_icon->flush_timer = D_INVALID_HANDLE;
                    }
                    PROJECT_FREE(radio_icon);
				    radio_icon = NULL;
                }
			}
			break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
atv_radio_icon_window_init(D_Frame *frm)
{
    D_Visual *vis;
    
    radio_icon = (TvRadioInfoData*) PROJECT_ALLOC (sizeof (TvRadioInfoData));
    if (! radio_icon)
    {
        return D_ERR;
    }

    memset(radio_icon, 0x00, sizeof (TvRadioInfoData));
    radio_icon->flush_timer = D_INVALID_HANDLE;

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        if(menu_pos_x == 0)
        {
            d_vis_get_pos(vis, &menu_pos_x, &menu_pos_y);
        }
        else
        {
            d_vis_set_pos(vis, menu_pos_x, menu_pos_y, vis->rect.w, vis->rect.h);
        }
        radio_icon->flush_timer = d_timer_create (NULL, FLUSH_WIN, d_gui_get_queue());
        if(radio_icon->flush_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, radio_icon->flush_timer);
        }

        d_vis_set_handler (vis, atv_radio_icon_window_handler);
    }

    d_dbase_get_srv_info(radio_db_srv_id, &(radio_icon->srvinfo));
    sprintf(radio_icon->chan_name, "A%03d %s", radio_icon->srvinfo.chan_num, radio_icon->srvinfo.name);

    vis = d_frame_get_control (frm, ID_LABEL_RADIO_NAME);
    if(vis)
    {
        d_label_set_text(vis, radio_icon->chan_name);
    }
    
    return D_OK;
}

/** @brief 广播提示菜单显示*/
D_Result
p_atv_radio_icon_win_show (D_ID dbsrvid) D_FUNCPOSTFIT
{
    D_DBSrvInfo info;
    if((D_OK == d_dbase_get_srv_info(dbsrvid, &info)) && info.srv_type == D_DB_SRV_RADIO)
    {
        radio_db_srv_id = dbsrvid;
        return d_gui_open_frame(&atv_radio_icon_window, D_GUI_LAYER_VIDEO);
    }
    return D_ERR;
}

/** @brief 广播提示菜单隐藏*/
D_Result
p_atv_radio_icon_win_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame (&atv_radio_icon_window);
}

