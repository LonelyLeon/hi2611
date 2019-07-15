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
#include "atv_sub_menu_window.c"

#define P_SUBMENU_ITEM_CNT    (8)

typedef struct
{
    D_U32     menu_level;
    D_GUIMenu   *sub_menu;
    D_U32     sub_item_cnt;
    D_U32       sub_focus;
    D_Bool      item_disable[P_SUBMENU_ITEM_CNT];
    D_HTimer   sub_htimer;
    D_U32    menu_show_time;
} D_ATVSubMenuData;

static D_ATVSubMenuData *atv_submenu_data = NULL;


//extern D_U32 get_main_menu_focus(void);

/** @brief 复位显示定时器*/
static D_Result
submenu_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(atv_submenu_data && atv_submenu_data->sub_htimer != D_INVALID_HANDLE)
    {
        d_timer_reset(atv_submenu_data->sub_htimer, atv_submenu_data->menu_show_time);
    }

    return D_OK;
}


/** @brief 事件处理*/
static D_Result
atv_sub_menu_set_item_status(void) D_FUNCPOSTFIT
{
    D_VidInput input;
    D_ID idx;
    D_Frame *frm = &atv_sub_menu_window;
    D_Visual *vis;
    D_U8 flag;
    D_GUIMenuItem   *item = NULL;

    item = atv_submenu_data->sub_menu->items;
    input = p_conf_get_vid_input();
    flag = p_vip_get_ntscflag();

    for(idx = 0; idx < P_SUBMENU_ITEM_CNT; idx++)
    {
        if(item->action == D_GUI_MENU_END)
        {
            continue;
        }

        if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE && item->caption == atv_IDS_TINT)
        {
            if(!flag)
            {
                atv_submenu_data->item_disable[idx] = D_TRUE;

            }
        }
        if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
        {
            if(input != D_VID_IUTPUT_TV && item->caption != atv_IDS_SLEEP_TIMER)
            {
                //atv_submenu_data->item_disable[idx] = D_TRUE;
            }
        }


        if(input == D_VID_IUTPUT_TV)
        {
            if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE)
            {
                if(item->caption == atv_IDS_TINT)
                {
                    if(!flag)
                    {
                        atv_submenu_data->item_disable[idx] = D_TRUE;

                    }
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
            {
                if(item->caption == atv_IDS_SLEEP_TIMER)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
        }
        else if(input == D_VID_IUTPUT_DTV)
        {
            if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE)
            {
                if(item->caption == atv_IDS_TINT)
                {
//                   if(!flag)
                    {
                        atv_submenu_data->item_disable[idx] = D_TRUE;

                    }
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
            {
                if(item->caption == atv_IDS_SLEEP_TIMER)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }

        }
        else if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2))
        {
            if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE)
            {
                if(item->caption == atv_IDS_TINT)
                {
                    if(!flag)
                    {
                        atv_submenu_data->item_disable[idx] = D_TRUE;

                    }
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_CHANNEL)
            {
                if(item->caption == atv_IDS_PROGRAM_EDIT)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_SOUND)
            {
                if(item->caption == atv_IDS_AVL)
                {
                    //atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
            {
                if(item->caption == atv_IDS_SLEEP_TIMER)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
        }
        else if(input == D_VID_IUTPUT_VGA)
        {
            if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE)
            {
                if(item->caption == atv_IDS_TINT)
                {
//                   if(!flag)
                    {
                        atv_submenu_data->item_disable[idx] = D_TRUE;

                    }
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_SOUND)
            {
                if(item->caption == atv_IDS_AVL)
                {
                    //atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
            {
                if(item->caption == atv_IDS_SLEEP_TIMER)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
        }
        else
        {
            if(atv_submenu_data->sub_menu->caption == atv_IDS_PICTURE)
            {
                if(item->caption == atv_IDS_TINT)
                {
//                   if(!flag)
                    {
                        atv_submenu_data->item_disable[idx] = D_TRUE;

                    }
                }
            }
            if(atv_submenu_data->sub_menu->caption == atv_IDS_SOUND)
            {
                if(item->caption == atv_IDS_AVL)
                {
                    //atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
	    if(atv_submenu_data->sub_menu->caption == atv_IDS_FUNCTION)		//add for PICTURE_OPTIMIZE cannot use in photo... Yin 20190627
	    	{
			if((input == D_VID_IUTPUT_USB1)||(input == D_VID_IUTPUT_USB2)||(input == D_VID_IUTPUT_USB3))
		 	{
	 		        if(item->caption == atv_IDS_PICTURE_OPTIMIZE)
		                {
		                  	if((AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO )||(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_MUSIC)||(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_EBOOK))
		                     	atv_submenu_data->item_disable[idx] = D_TRUE;
		                }
		 	}
	    	}
            if(atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
            {
                if(item->caption == atv_IDS_SLEEP_TIMER)
                {
                    atv_submenu_data->item_disable[idx] = D_TRUE;
                }
            }
        }

        item++;
    }
    return D_OK;
}

static D_ID
atv_sub_menu_item_get_next_focus(D_Bool right, D_ID cur_focus)
{
    D_ID idx, focus = cur_focus;
    D_VidInput input;

    /*
        if(input != D_VID_IUTPUT_TV && atv_submenu_data->sub_menu->caption == atv_IDS_TIME)
        {
            atv_submenu_data->sub_menu->focus = atv_submenu_data->sub_item_cnt;
            return D_OK;
        }
    */
    if(right)
    {
        for(idx = 1; idx <= atv_submenu_data->sub_item_cnt; idx++)
        {
            focus = idx + cur_focus;
            focus = focus % atv_submenu_data->sub_item_cnt;
            if(atv_submenu_data->item_disable[focus] == D_FALSE)
            {
                break;
            }
        }
    }
    else
    {
        for(idx = 1; idx <= atv_submenu_data->sub_item_cnt; idx++)
        {
            focus = cur_focus - idx + atv_submenu_data->sub_item_cnt;
            focus = focus % atv_submenu_data->sub_item_cnt;
            if(atv_submenu_data->item_disable[focus] == D_FALSE)
            {
                break;
            }
        }
    }
    return focus;
}

/** @brief 事件处理*/
static D_Result
atv_sub_menu_item_show (void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_sub_menu_window;
    D_Visual * vis, *vis_enable;
    D_GUIMenuItem   *item = NULL;
    D_ID idx, focus;
    D_Bool enable = D_TRUE;
    D_VidInput input;
    D_Char *text;
    D_Coord w[P_SUBMENU_ITEM_CNT] = {0};
    D_Coord sw, max_w, real_w, interval, x;

    item = atv_submenu_data->sub_menu->items;
    focus = atv_submenu_data->sub_menu->focus;
    input = p_conf_get_vid_input();

    vis = d_frame_get_control(frm, ID_ATV_IMAGE_SUBPIC);
    d_image_box_set_image(vis, d_gui_get_image(atv_submenu_data->sub_menu->icon));

    vis = d_frame_get_control(frm, ID_ATV_GROUP_SUB1);
    max_w = vis->rect.w;
    real_w = 0;
    interval = 0;
    sw = 0;

    /*显示文本*/
    for(idx = 0; idx < P_SUBMENU_ITEM_CNT; idx++)
    {
        vis = d_frame_get_control(frm, ID_ATV_BUTTOB_SUBINFO1 + idx);
        if(idx >= atv_submenu_data->sub_item_cnt)
        {
            d_vis_show(vis, D_FALSE);
        }
        else
        {
            if(atv_submenu_data->item_disable[idx])
            {
                enable = D_FALSE;
            }
            else
            {
                enable = D_TRUE;
            }
            text = NULL;
            d_vis_enable(vis, enable);
            if(input == D_VID_IUTPUT_DTV && item->caption == atv_IDS_PROGRAM_EDIT)
            {
                text = d_gui_get_text(atv_IDS_MANUAL_SEARCH);
            }
            else if(input == D_VID_IUTPUT_DTV && item->caption == atv_IDS_EXCHANGE)
            {
                text = d_gui_get_text(atv_IDS_AUTO_TUNING);
            }
            else if(input == D_VID_IUTPUT_DTV && item->caption == atv_IDS_AUTO_TUNING)
            {
                //text = d_gui_get_text(atv_IDS_NET_SEARCH); //不显示网络搜索功能
            }
            else
            {
                text = d_gui_get_text(item->caption);
            }

            real_w += (max_w / P_SUBMENU_ITEM_CNT) ;
            if(text)
            {
                d_button_set_text(vis, text);
                d_font_text_size (text, strlen(text), &w[idx], NULL, NULL);  /*  计算文字长度*/
                sw += w[idx];
            }
        }

        item++;
    }

    /* 修改控件大小，平均间隔*/
    if(atv_submenu_data->sub_item_cnt)
    {
        real_w = D_MAX(real_w, (sw + (atv_submenu_data->sub_item_cnt - 1) * 24));
        real_w = D_MIN(real_w, max_w);
        interval = (real_w - sw) /  atv_submenu_data->sub_item_cnt;
        x = 0;
        for(idx = 0; idx < P_SUBMENU_ITEM_CNT; idx++)
        {
            vis = d_frame_get_control(frm, ID_ATV_BUTTOB_SUBINFO1 + idx);
            if(idx >= atv_submenu_data->sub_item_cnt)
            {
                d_vis_set_pos(vis, x, vis->rect.y, 1, vis->rect.h);
                x += 1;
            }
            else
            {
                w[idx] += interval;
                if(idx == (P_SUBMENU_ITEM_CNT - 1))
                {
                    w[idx] = (real_w - x);
                }
                d_vis_set_pos(vis, x, vis->rect.y, w[idx], vis->rect.h);
                x += w[idx];
            }
        }
    }
    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_sub_menu_set_focus(D_ID focus) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_sub_menu_window;
    D_Visual *vis;

    atv_submenu_data->sub_menu->focus = focus;
    vis = d_frame_get_control(frm, ID_ATV_BUTTOB_SUBINFO1 + focus);
    d_vis_set_focus(vis);

    return D_OK;
}

/*进入子菜单*/
static D_Result
atv_sub_menu_item_action(void) D_FUNCPOSTFIT
{
    D_GUIMenuItem   *item = NULL;
    D_S16 menu_level;
    D_VidInput input;

    input = p_conf_get_vid_input();


    menu_level = d_gui_get_menu_level();
    item = atv_submenu_data->sub_menu->items + atv_submenu_data->sub_menu->focus;
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
                    if (item->sub_menu->items->app)
                    {
                        item->sub_menu->items->app();
                    }
                }
            }
        }
        else if (item->action == D_GUI_MENU_RUN_APP)
        {
            if(atv_submenu_data->menu_level < menu_level)
            {
                d_gui_upper_menu();
            }
            if (item->app)
            {
                if(input == D_VID_IUTPUT_USB1 && item->caption == atv_IDS_ASPECT_RATIO)
                {
                    p_atv_media_zoom_mode_show();
                }
                /*运行应用*/
                else
                {
                    item->app();
                }
            }
        }
    }

    return D_OK;
}


/** @brief 事件处理*/
static D_Result
atv_sub_menu_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                    submenu_reset_show_timer();
                case D_KEY_BACK:
                    return d_gui_upper_menu ();
                    break;

                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    return d_gui_clear_menu ();
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    atv_submenu_data->sub_focus = atv_sub_menu_item_get_next_focus(D_FALSE, atv_submenu_data->sub_focus);
                    D_DUMP("atv_submenu_data->sub_focus = %d\n", atv_submenu_data->sub_focus);

                    if(atv_submenu_data->sub_focus == 2 && p_conf_get_vid_input() == D_VID_IUTPUT_DTV && atv_submenu_data->sub_menu->caption == atv_IDS_CHANNEL)//get_main_menu_focus() == 2)
                    {
                        atv_submenu_data->sub_focus = 1;
                        atv_sub_menu_set_focus(atv_submenu_data->sub_focus);
                        atv_sub_menu_item_action();
                        break;
                    }

                    atv_sub_menu_set_focus(atv_submenu_data->sub_focus);
                    atv_sub_menu_item_action();
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    atv_submenu_data->sub_focus = atv_sub_menu_item_get_next_focus(D_TRUE, atv_submenu_data->sub_focus);
                    D_DUMP("atv_submenu_data->sub_focus = %d\n", atv_submenu_data->sub_focus);

                    if(atv_submenu_data->sub_focus == 2 && p_conf_get_vid_input() == D_VID_IUTPUT_DTV && atv_submenu_data->sub_menu->caption == atv_IDS_CHANNEL)//get_main_menu_focus() == 2)
                    {
                        atv_submenu_data->sub_focus = 0;
                        atv_sub_menu_set_focus(atv_submenu_data->sub_focus);
                        atv_sub_menu_item_action();
                        break;
                    }

                    atv_sub_menu_set_focus(atv_submenu_data->sub_focus);
                    atv_sub_menu_item_action();
                    break;

                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    return D_ERR;
                case  D_KEY_OK:
                case  D_KEY_PNL_OK:
                    break;

                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if (0) //(evt->timer.htimer == atv_submenu_data->sub_htimer)
            {
                return d_gui_clear_menu();
            }
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {
                atv_sub_menu_item_show();
            }
            break;
        case D_EVT_DESTROY:
            g_stb->menu_status &= ~MAIN_MENU_STATUS;
            d_vis_unsubscribe_evt(vis);
            if(atv_submenu_data)
            {
                if(atv_submenu_data->sub_htimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(atv_submenu_data->sub_htimer);
                }
                PROJECT_FREE(atv_submenu_data);
                atv_submenu_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
atv_sub_menu_window_init(D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_GUIMenuItem    *item;
    D_ID idx;
    D_VidInput input;
    D_TimerAttr timer_attr;

    input = p_conf_get_vid_input();

    atv_submenu_data = (D_ATVSubMenuData*)PROJECT_ALLOC(sizeof(D_ATVSubMenuData));
    if(!atv_submenu_data)
    {
        return D_ERR;
    }

    memset(atv_submenu_data, 0x00, sizeof(D_ATVSubMenuData));
    atv_submenu_data->menu_show_time = 3 * 1000;
    g_stb->menu_status |= MAIN_MENU_STATUS;
    atv_submenu_data->sub_menu = d_gui_get_curr_menu();
    atv_submenu_data->sub_focus = atv_submenu_data->sub_menu->focus;
    item = atv_submenu_data->sub_menu->items;
    for(idx = 0; item->action != D_GUI_MENU_END; idx++)
    {
        item++;
        atv_submenu_data->sub_item_cnt++;
    }

    atv_sub_menu_set_item_status();
    atv_sub_menu_item_show();

    idx = atv_submenu_data->sub_focus + atv_submenu_data->sub_item_cnt - 1;
    idx = idx % atv_submenu_data->sub_item_cnt;
    atv_submenu_data->sub_focus = atv_sub_menu_item_get_next_focus(D_TRUE, idx);
    atv_submenu_data->sub_menu->focus = atv_submenu_data->sub_focus;
    atv_sub_menu_set_focus(atv_submenu_data->sub_focus);

    vis = d_frame_get_control(frm, ID_ATV_GROUP_SUB1);
    if(vis)
    {
        d_vis_unsubscribe_one_evt( vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }


    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        atv_submenu_data->sub_htimer = d_timer_create(&timer_attr, atv_submenu_data->menu_show_time, d_gui_get_queue());
        if(atv_submenu_data->sub_htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, atv_submenu_data->sub_htimer);
        }

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_UP_DOWN_KEY_MASK) & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_sub_menu_window_handler);
    }

    atv_submenu_data->menu_level = 1 + d_gui_get_menu_level();

    return D_OK;

}

