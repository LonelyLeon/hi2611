/** @file patvmianmenu.c
**@brief   tv 主菜单menu
**@date
**/#include <stdio.h>
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


#define P_MAINMENU_ITEM_CNT   (4)

typedef struct
{
    D_GUIMenu   *main_menu;
    D_U32       main_item_cnt;
    D_U32       main_focus;
    D_U32       disable_id0, disable_id1, disable_id2;
    D_Handle    handle_key_cb;
    D_U8   combo_key[4];
    D_U8   serial_key[4];
} D_ATVMainMenuData;

static D_ATVMainMenuData    *atv_menu_data = NULL;

static D_HTimer atv_menu_htimer = D_INVALID_HANDLE;
static D_HTimer atv_menu_htimer_enable = D_TRUE;
static D_MSec atv_menu_timeout;

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

    for(idx = 0; idx < atv_menu_data->main_item_cnt; idx++)
    {
        if(item->action != D_GUI_MENU_END)
        {
            if(input == D_VID_IUTPUT_VGA)
            {
                if(item->icon == atv_IMG_ID_main_menu_turn)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                if(item->icon == atv_IMG_ID_main_menu_time)
                {
                    atv_menu_data->disable_id2 = idx;
                }
            }
	    else if(input == D_VID_IUTPUT_TV)
            {
               
            }
            else if(input == D_VID_IUTPUT_DTV)
            {
                if(item->icon == atv_IMG_ID_main_menu_time)
                {
                    atv_menu_data->disable_id2 = idx;
                }
            }
	     else if((input == D_VID_IUTPUT_USB1)||(input == D_VID_IUTPUT_USB2)||(input == D_VID_IUTPUT_USB3))		
            {
                if(item->icon == atv_IMG_ID_main_menu_turn)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                if((AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO )||(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_EBOOK))		//add for Photo  cannot use picture function and voice function by Yin 20190627
                {
			if(item->icon == atv_IMG_ID_main_menu_voice)
				atv_menu_data->disable_id1 = idx;
                }
		 if((AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_PHOTO )||(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_MUSIC)||(AtvMediaMenuStatus & ATV_MEDIA_MENU_STATUS_EBOOK))	//add for Music  cannot use picture function by Yin 20190627
                {
                	if(item->icon == atv_IMG_ID_main_menu_pic)
                    		atv_menu_data->disable_id2 = idx;
                }
            }
            
            else
            {
                if(item->icon == atv_IMG_ID_main_menu_turn)
                {
                    atv_menu_data->disable_id0 = idx;
                }
                /*if(item->icon == atv_IMG_ID_main_menu_time)
                {
                    atv_menu_data->disable_id2 = idx;
                }*/
            }
            item++;
        }
    }

    return D_OK;
}

static D_Result
atv_main_menu_set_next_focus(D_Bool left)
{
    D_ID idx;

    if(left)
    {
        for(idx = 1; idx <= atv_menu_data->main_item_cnt; idx++)
        {
            atv_menu_data->main_menu->focus = (atv_menu_data->main_menu->focus + P_MAINMENU_ITEM_CNT - 1) % P_MAINMENU_ITEM_CNT ;
            if(atv_menu_data->main_menu->focus != atv_menu_data->disable_id0 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id1 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id2)
            {
                break;
            }
        }
    }
    else
    {
        for(idx = 1; idx <= atv_menu_data->main_item_cnt; idx++)
        {
            atv_menu_data->main_menu->focus = (atv_menu_data->main_menu->focus + 1) % P_MAINMENU_ITEM_CNT ;
            if(atv_menu_data->main_menu->focus != atv_menu_data->disable_id0 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id1 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id2)
            {
                break;
            }
        }
    }
    d_vis_set_focus(d_frame_get_control(&atv_main_menu_window, ID_ATV_BUTTON_1 + atv_menu_data->main_menu->focus));
    atv_menu_data->main_focus = atv_menu_data->main_menu->focus;
    return D_OK;
}
 
/** @brief 事件处理*/
static D_Result
atv_main_menu_item_show (void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_main_menu_window;
    D_Visual * vis, *pvis;
    D_GUIMenuItem   *item = NULL;
    D_ID idx;
    D_Image *image;
    D_Char* text;
    D_Bool enable, disenable;

    item = atv_menu_data->main_menu->items;
    disenable = D_TRUE;
    /*显示文本*/
    for(idx = 0; idx < P_MAINMENU_ITEM_CNT; idx++)
    {
        text = NULL;
        image = NULL;
        enable = D_FALSE;
        if(item->action != D_GUI_MENU_END)
        {
            text = d_gui_get_text(item->caption);
            image = d_gui_get_image(item->icon);
            item++;
            enable = D_TRUE;
        }

        vis = d_frame_get_control(frm, ID_ATV_BUTTON_1 + idx);
        pvis = d_frame_get_control(frm, ID_ATV_IMAGE_1 + idx);
        if(vis)
        {
            d_button_set_text(vis, text);
            if(enable == D_FALSE)
            {
                d_vis_set_focusable(vis, D_FALSE);
            }
            if(idx == atv_menu_data->disable_id0 || idx == atv_menu_data->disable_id1 || idx == atv_menu_data->disable_id2)
            {
                disenable = D_FALSE;
            }
            else
            {
                disenable = D_TRUE;
            }
            d_vis_enable(vis, disenable);
        }

        if(pvis)
        {
            d_image_box_set_image(pvis, image);
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
                    d_gui_enter_sys_menu (item->sub_menu, D_CLEAR_ALL);// item->sub_menu->clear);
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
                p_combo_key_seq_dinit();
            }
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
		  case D_KEY_BACK:			//add for exit key 20190701 Yin
                    return d_gui_clear_menu();
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    atv_main_menu_set_next_focus(D_FALSE);
                    p_combo_key_seq_init(atv_menu_data->combo_key, 4);
                    p_combo_key_seq_init1(atv_menu_data->serial_key, 4);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    atv_main_menu_set_next_focus(D_TRUE);
                    p_combo_key_seq_init(atv_menu_data->combo_key, 4);
                    p_combo_key_seq_init1(atv_menu_data->serial_key, 4);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    atv_main_menu_item_action();
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
    item = atv_menu_data->main_menu->items;
    for(idx = 0; item->action != D_GUI_MENU_END; idx++)
    {
        item++;
        atv_menu_data->main_item_cnt++;
    }
    atv_menu_data->main_item_cnt = D_MIN(atv_menu_data->main_item_cnt, P_MAINMENU_ITEM_CNT);
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

    atv_main_menu_get_item_status();
    atv_main_menu_item_show();

    vis = d_frame_get_control(frm, ID_ATV_GROUP_MAINMENU);
    if(vis)
    {
        d_vis_unsubscribe_one_evt( vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

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
	for(idx = 1; idx <= atv_menu_data->main_item_cnt; idx++)	//add for Selection Error when first item is unselectable Yin 20190627
        {
            if(atv_menu_data->main_menu->focus != atv_menu_data->disable_id0 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id1 && atv_menu_data->main_menu->focus != atv_menu_data->disable_id2)
            {
                break;
            }
	     atv_menu_data->main_menu->focus = (atv_menu_data->main_menu->focus + 1) % P_MAINMENU_ITEM_CNT ;
        }
	//for exit from submenu Yin 20190628
	d_vis_set_focus(d_frame_get_control(&atv_main_menu_window, ID_ATV_BUTTON_1 + atv_menu_data->main_menu->focus));		
	//D_DUMP("main_menu->focus = %d\n", atv_menu_data->main_menu->focus);
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