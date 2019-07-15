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
#include "dCBMan.h"

#include "atv_main_menu_window.c"

#define P_MAINMENU_ITEM_CNT   (5)
#define P_MAINMENU_ITEM_POS_X (6)
#define P_MAINMENU_ITEM_POS_Y (6)
#define P_MAINMENU_ITEM_POS_BORDER (4)

typedef struct
{
    D_GUIMenu   *main_menu;
    D_U32       main_item_cnt;
    D_U32       main_focus;
    D_U32       disable_id0, disable_id1, disable_id2;
    D_Handle    handle_key_cb;
    D_U8   combo_key[4];
    D_U8   serial_key[4];
    D_U8   dingke_key[3];
} D_ATVMainMenuData;

static D_ATVMainMenuData    *atv_menu_data = NULL;

static D_HTimer atv_menu_htimer = D_INVALID_HANDLE;
static D_HTimer atv_menu_htimer_enable = D_TRUE;
static D_MSec atv_menu_timeout;

extern D_Coord sub_menu_pos_x;
extern D_Coord sub_menu_pos_y;


/*按键回调*/
static void
atv_menu_timeout_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data);

D_U32 get_main_menu_focus(void)
{
    return atv_menu_data->main_focus;
}

static D_Result
atv_main_menu_get_item_status(void)
{
    D_VidInput input;
    D_ID idx;
    D_GUIMenuItem   *item = NULL;

    input = p_conf_get_vid_input();

    atv_menu_data->disable_id0 = 0xFF;
    atv_menu_data->disable_id1 = 0xFF;
    atv_menu_data->disable_id2 = 0xFF;
    item = atv_menu_data->main_menu->items;

    for(idx = 0; idx < P_MAINMENU_ITEM_CNT; idx++)
    {
        if(item->action != D_GUI_MENU_END)
        {
            if(input == D_VID_IUTPUT_VGA)
            {
                if(item->icon == atv_IMG_ID_tuning_icon_small)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                if(item->icon == atv_IMG_ID_time_icon_small)
                {
                    atv_menu_data->disable_id2 = idx;
                }
            }
            else if(input == D_VID_IUTPUT_TV)
            {
                if(item->icon == atv_IMG_ID_adjust_icon_small)
                {
                    atv_menu_data->disable_id0 = idx;
                }

            }
            else if(input == D_VID_IUTPUT_DTV)
            {
                if(item->icon == atv_IMG_ID_adjust_icon_small)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                if(item->icon == atv_IMG_ID_time_icon_small)
                {
                    atv_menu_data->disable_id2 = idx;
                }
            }
            else
            {
                if(item->icon == atv_IMG_ID_tuning_icon_small)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                else if(item->icon == atv_IMG_ID_adjust_icon_small)
                {
                    atv_menu_data->disable_id1 = idx;
                }
                if(item->icon == atv_IMG_ID_time_icon_small)
                {
                    atv_menu_data->disable_id2 = idx;
                }
            }
            item++;
        }
    }

    return D_OK;
}

static D_ID
atv_main_menu_get_item_image_id(D_ID imageid, D_Bool enable)
{
    D_ID id = imageid;;

    if(!enable)
    {
        switch(imageid)
        {
            case atv_IMG_ID_tuning_icon_small:
                id = atv_IMG_ID_tuning_icon_small_forbidden;
                break;
            case atv_IMG_ID_adjust_icon_small:
                id = atv_IMG_ID_adjust_icon_small_forbidden;
                break;
            case atv_IMG_ID_time_icon_small:
                id = atv_IMG_ID_time_icon_small_forbidden;
                break;
            default:
                break;
        }
    }
    return id;
}


static D_Result
atv_main_menu_get_next_focus(D_Bool down)
{
    D_ID idx, focus = 0xFF;

    if(down)
    {
        for(idx = 1; idx <= atv_menu_data->main_item_cnt; idx++)
        {
            focus = idx + atv_menu_data->main_focus;
            focus = focus % atv_menu_data->main_item_cnt;
            if(focus != atv_menu_data->disable_id0 && focus != atv_menu_data->disable_id1 && focus != atv_menu_data->disable_id2)
            {
                break;
            }
        }
    }
    else
    {
        for(idx = 1; idx <= atv_menu_data->main_item_cnt; idx++)
        {
            focus = atv_menu_data->main_focus - idx + atv_menu_data->main_item_cnt;
            focus = focus % atv_menu_data->main_item_cnt;
            if(focus != atv_menu_data->disable_id0 && focus != atv_menu_data->disable_id1 && focus != atv_menu_data->disable_id2)
            {
                break;
            }
        }
    }

    if(focus != 0xFF)
    {
        atv_menu_data->main_focus = focus;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_main_menu_item_show (void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_main_menu_window;
    D_Visual *vis;
    D_GUIMenuItem   *item = NULL;
    D_Coord x, y;
    D_ID idx, focus, vis_id, imageid;
    D_Bool enable = D_TRUE;

    item = atv_menu_data->main_menu->items;
    focus = atv_menu_data->main_menu->focus;

    x = P_MAINMENU_ITEM_POS_X;
    y = P_MAINMENU_ITEM_POS_Y;

    /*显示文本*/
    for(idx = 0; idx < P_MAINMENU_ITEM_CNT; idx++)
    {
        if(item->action != D_GUI_MENU_END)
        {
            if(idx == focus)
            {
                vis = d_frame_get_control(frm, ID_MAINMENU_GROUP_ITEM_5);
                d_vis_set_pos(vis, x, y, vis->rect.w, vis->rect.h);
                d_vis_get_pos(vis, &sub_menu_pos_x, &sub_menu_pos_y);
                y += vis->rect.h + P_MAINMENU_ITEM_POS_BORDER;
            }
            else
            {
                if(idx == atv_menu_data->disable_id0 || idx == atv_menu_data->disable_id1 || idx == atv_menu_data->disable_id2)
                {
                    enable = D_FALSE;
                }
                else
                {
                    enable = D_TRUE;
                }

                vis_id  = (idx > focus) ? (idx - 1) : idx;

                vis = d_frame_get_control(frm, ID_MAINMENU_GROUP_ITEM_0 + vis_id);
                d_vis_set_pos(vis, x, y, vis->rect.w, vis->rect.h);
                y += vis->rect.h + P_MAINMENU_ITEM_POS_BORDER;

                vis = d_frame_get_control(frm, ID_MAINMENU_IMAGE_ICON_0 + vis_id);
                imageid = atv_main_menu_get_item_image_id(item->icon, enable);
                d_image_box_set_image(vis, d_gui_get_image(imageid));

                vis = d_frame_get_control(frm, ID_MAINMENU_LABEL_ITEM_TITLE_0 + vis_id);
                d_label_set_text(vis, d_gui_get_text(item->caption));
                d_vis_enable(vis, enable);

                vis = d_frame_get_control(frm, ID_MAINMENU_GROUP_SUB_0 + vis_id);
                d_vis_enable(vis, enable);

                vis = d_frame_get_control(frm, ID_MAINMENU_LABEL_ITEM_CONTENT_0 + vis_id);
                d_vis_enable(vis, enable);
            }

            item++;
        }
        else
        {
            d_vis_show(vis, D_FALSE);
        }
    }
    return D_OK;
}

/*进入子菜单*/
static D_Result
atv_main_menu_item_action(void) D_FUNCPOSTFIT
{
    D_GUIMenuItem   *item = NULL, *sub_item = NULL;
    D_S16 menu_level;

    menu_level = d_gui_get_menu_level();
    item = atv_menu_data->main_menu->items + atv_menu_data->main_menu->focus;

    while(menu_level > 1)
    {
        d_gui_upper_menu();
        menu_level--;
    }

    if(item)
    {
        if (item->action == D_GUI_MENU_GOTO_SUB)
        {
            /*进入子菜单*/
            if (item->sub_menu)
            {
                item->sub_menu->focus = 0;
                if(item->sub_menu->frm)
                {
                    d_gui_enter_sys_menu (item->sub_menu, item->sub_menu->clear);
                    sub_item = item->sub_menu->items + item->sub_menu->focus;
                    if (sub_item->app)
                    {
                        sub_item->app();
                    }
                }
            }
        }
        else if (item->action == D_GUI_MENU_RUN_APP)
        {
            /*运行应用*/
            if (item->app)
            {
                item->app();
            }
        }
    }

    return D_OK;
}


/** @brief 事件处理*/
static D_Result
atv_main_menu_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            if(p_combo_key_input(evt->fp.key) == D_OK)
            {
                p_atv_factory_setting_show();
                p_combo_key_seq_dinit();
            }
            if(p_combo_key_input1(evt->fp.key) == D_OK)
            {
                p_atv_serial_show();
                p_combo_key_seq_dinit1();
            }
            if(p_combo_key_input2(evt->fp.key) == D_OK)
            {
                p_atv_factory_setting_show();
                p_combo_key_seq_dinit2();
            }
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    return d_gui_clear_menu();
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    atv_main_menu_get_next_focus(D_FALSE);
                    atv_menu_data->main_menu->focus = atv_menu_data->main_focus;
                    atv_main_menu_item_show();
                    atv_main_menu_item_action();
                    p_combo_key_seq_init(atv_menu_data->combo_key, 4);
                    p_combo_key_seq_init1(atv_menu_data->serial_key, 4);
					p_combo_key_seq_init2(atv_menu_data->dingke_key, 3);
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    atv_main_menu_get_next_focus(D_TRUE);
                    atv_menu_data->main_menu->focus = atv_menu_data->main_focus;
                    atv_main_menu_item_show();
                    atv_main_menu_item_action();
                    p_combo_key_seq_init(atv_menu_data->combo_key, 4);
                    p_combo_key_seq_init1(atv_menu_data->serial_key, 4);
					p_combo_key_seq_init2(atv_menu_data->dingke_key, 3);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    break;
                case D_KEY_MUTE:
                    return D_ERR;
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == atv_menu_htimer && atv_menu_htimer_enable)
            {
                return d_gui_clear_menu();
            }
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                atv_main_menu_item_show();
                p_combo_key_seq_init(atv_menu_data->combo_key, 4);
                p_combo_key_seq_init1(atv_menu_data->serial_key, 4);
				p_combo_key_seq_init2(atv_menu_data->dingke_key, 3);
            }
            break;
        case D_EVT_DESTROY:
            g_stb->menu_status &= ~MAIN_MENU_STATUS;
            d_vis_unsubscribe_evt(vis);

            if(atv_menu_htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(atv_menu_htimer);
                atv_menu_htimer = D_INVALID_HANDLE;
            }

            if(atv_menu_data->handle_key_cb != D_INVALID_HANDLE)
            {
                d_cbman_unsubscribe(atv_menu_data->handle_key_cb);
                atv_menu_data->handle_key_cb = D_INVALID_HANDLE;
            }

            if(atv_menu_data)
            {
                PROJECT_FREE(atv_menu_data);
                atv_menu_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
atv_main_menu_window_init(D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_GUIMenuItem    *item;
    D_ID idx;
    D_TimerAttr timer_attr;

    atv_menu_data = (D_ATVMainMenuData*)PROJECT_ALLOC(sizeof(D_ATVMainMenuData));
    if(!atv_menu_data)
    {
        return D_ERR;
    }

    memset(atv_menu_data, 0x00, sizeof(D_ATVMainMenuData));
    g_stb->menu_status |= MAIN_MENU_STATUS;
    atv_menu_data->disable_id0 = 0xFF;
    atv_menu_data->disable_id1 = 0xFF;
    atv_menu_data->disable_id2 = 0xFF;
    atv_menu_data->main_menu = d_gui_get_curr_menu();
    atv_menu_data->main_focus = atv_menu_data->main_menu->focus;
    item = atv_menu_data->main_menu->items;
    for(idx = 0; item->action != D_GUI_MENU_END; idx++)
    {
        item++;
        atv_menu_data->main_item_cnt++;
    }

    atv_menu_data->combo_key[0] = D_KEY_8;
    atv_menu_data->combo_key[1] = D_KEY_8;
    atv_menu_data->combo_key[2] = D_KEY_9;
    atv_menu_data->combo_key[3] = D_KEY_3;
    p_combo_key_seq_init(atv_menu_data->combo_key, 4);

    atv_menu_data->serial_key[0] = D_KEY_8;
    atv_menu_data->serial_key[1] = D_KEY_8;
    atv_menu_data->serial_key[2] = D_KEY_9;
    atv_menu_data->serial_key[3] = D_KEY_4;
    p_combo_key_seq_init1(atv_menu_data->serial_key, 4);

    atv_menu_data->dingke_key[0] = D_KEY_1;
    atv_menu_data->dingke_key[1] = D_KEY_1;
    atv_menu_data->dingke_key[2] = D_KEY_4;
    p_combo_key_seq_init2(atv_menu_data->dingke_key, 3);


    atv_main_menu_get_item_status();
    atv_main_menu_item_show();

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        atv_menu_timeout = (D_MSec)p_conf_get_info_time();
        atv_menu_timeout = D_MAX(atv_menu_timeout, D_CONF_MIN_INFO_TIME);
        atv_menu_timeout = D_MIN(atv_menu_timeout, D_CONF_MAX_INFO_TIME);
        atv_menu_timeout *= 1000;
        atv_menu_htimer_enable = D_TRUE;
        timer_attr.id = 0;
        timer_attr.one_shot = D_TRUE;
        atv_menu_htimer = d_timer_create(&timer_attr, atv_menu_timeout, d_gui_get_queue());
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);

        if(atv_menu_htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, atv_menu_htimer);
        }
        d_vis_set_handler (vis, atv_main_menu_window_handler);
    }

    atv_menu_data->handle_key_cb = d_cbman_subscribe(PL_GUI_INPUT_POLL, D_INVALID_HANDLE, atv_menu_timeout_cb, NULL);

    return D_OK;

}

/*按键回调*/
static void
atv_menu_timeout_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_Event *evt = (D_Event *)obj_data;
    //p_atv_menu_timeout_timer_reset();

    if(atv_menu_htimer != D_INVALID_HANDLE)
    {
        d_timer_reset(atv_menu_htimer, (D_MSec) - 1);
    }
}


/** @brief 菜单超时时间使能*/
D_Result
p_atv_menu_timeout_timer_enable(D_Bool enable)D_FUNCPOSTFIT
{
    if(atv_menu_htimer_enable != enable)
    {
        atv_menu_htimer_enable = enable;
        if(enable && atv_menu_htimer != D_INVALID_HANDLE)
        {
            d_timer_reset(atv_menu_htimer, (D_MSec) - 1);
        }
    }
    return D_OK;
}

/** @brief 菜单超时时间定时器重新计时*/
D_Result
p_atv_menu_timeout_timer_reset(void)D_FUNCPOSTFIT
{
    if(atv_menu_htimer != D_INVALID_HANDLE)
    {
        d_timer_reset(atv_menu_htimer, (D_MSec) - 1);
    }

    return D_OK;
}

/** @brief 菜单时间定时器重新计时*/

D_Result
p_atv_menu_timer_reset(D_U8 new_time)D_FUNCPOSTFIT
{
    if(atv_menu_htimer != D_INVALID_HANDLE)
    {
        d_timer_reset(atv_menu_htimer, ((D_MSec) new_time) * 1000);
    }

    return D_OK;
}


