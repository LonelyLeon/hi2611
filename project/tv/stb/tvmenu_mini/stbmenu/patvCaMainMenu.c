/** @file patvCaMainMenu.c
* @brief ca菜单公用模块
* @author 刘军鸿
* @date 2015-12-29: liujh建立文件
*/
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

#include "atv_ca_main_window.c"

#define P_CA_ITEM_CNT   (6)
#define MAX_MENU_LEVEL  (6)
/*********************************ca主菜单项定义*******************************/
D_GUIMenu * ca_main_menu = NULL;

/******************************************************************************/
typedef struct
{
    D_U32       ca_main_item_cnt;
    D_U32       cur_focus;
    D_Char *title_caption;
    D_Char      *item_caption[P_CA_ITEM_CNT];
    D_Visual    *list_vis;
} D_ATVCAMainMenuData;


static D_ATVCAMainMenuData    *atv_ca_menu_data = NULL;

static D_GUIMenu    *cur_menu = NULL;
static D_GUIMenu *ca_main_menu_list[MAX_MENU_LEVEL];
static D_U8 cur_ca_menu_level = 0;

/** @brief 事件处理*/
static D_Result
atv_ca_main_menu_item_show () D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_ca_main_window;
    D_Visual *vis;
    D_GUIMenuItem   *item = NULL;
    D_Coord x, y;
    D_ID idx, focus, vis_id, imageid;
    D_Bool enable = D_TRUE;



    if(!cur_menu)
    {
        return D_ERR;
    }

    vis = d_frame_get_control (frm, ID_CA_LABEL_TITLE);
    if(vis)
    {
        atv_ca_menu_data->title_caption = d_gui_get_text(cur_menu->caption);
        d_label_set_text(vis, atv_ca_menu_data->title_caption);
    }

    item = cur_menu->items;

    /*设定焦点项*/
    if(cur_menu->focus < 0  || cur_menu->focus >= P_CA_ITEM_CNT)
    {
        cur_menu->focus = 0;
    }

    focus = cur_menu->focus;


    /*设定焦点项*/
    d_list_set_focus(atv_ca_menu_data->list_vis, cur_menu->focus, 0);

    /*显示文本*/
    for(idx = 0; idx < P_CA_ITEM_CNT; idx++)
    {
        if(item->action != D_GUI_MENU_END)
        {
            item->vis = NULL;
            d_list_set_show(atv_ca_menu_data->list_vis, D_CTRL_LIST_ROW, idx, 0, D_TRUE);
            //d_list_set_image(vis, idx, 1, ((item->icon >= 0)? d_gui_get_image(item->icon) : NULL));
            atv_ca_menu_data->item_caption[idx] = d_gui_get_text(item->caption);
            d_list_set_text(atv_ca_menu_data->list_vis, idx, 0, atv_ca_menu_data->item_caption[idx]);
            item++;
        }
        else
        {
            d_list_set_show(atv_ca_menu_data->list_vis, D_CTRL_LIST_ROW, idx, 0, D_FALSE);
            //d_list_set_image(vis, idx, 1, NULL);
            atv_ca_menu_data->item_caption[idx] = NULL;
            d_list_set_text(atv_ca_menu_data->list_vis, idx, 0, NULL);
        }


        /*设定焦点项*/
        d_list_set_focus(atv_ca_menu_data->list_vis, cur_menu->focus, 0);
    }
    return D_OK;
}

/*显示上一级菜单内容*/
static D_Result
show_upper_menu(void)
{
    if(cur_ca_menu_level > 1)
    {
        cur_ca_menu_level--;
        cur_menu = ca_main_menu_list[cur_ca_menu_level] = NULL;
        cur_menu = ca_main_menu_list[cur_ca_menu_level - 1];
        atv_ca_main_menu_item_show();
    }
    else
    {
        cur_ca_menu_level = 0;
        d_gui_upper_menu ();
    }

    return D_OK;
}

/*进入子菜单*/
static D_Result
atv_ca_main_menu_item_action(void) D_FUNCPOSTFIT
{

    D_Frame *frm = &atv_ca_main_window;
    D_GUIMenuItem *item = NULL;
    D_ID focusid;

    if (cur_menu)
    {

        focusid = d_list_get_focus(atv_ca_menu_data->list_vis, NULL, NULL);
        if(focusid >= 0)
        {
            item = cur_menu->items + focusid;
        }
        cur_menu->focus = focusid;
    }
    if (item->action == D_GUI_MENU_GOTO_SUB)
    {
        /*进入子菜单*/
        if (item->sub_menu)
        {
            if(cur_ca_menu_level < MAX_MENU_LEVEL)
            {
                ca_main_menu_list[cur_ca_menu_level++] = item->sub_menu;
            }

            item->sub_menu->focus = 0;
            if(item->sub_menu->clear)
            {
                d_gui_enter_sys_menu (item->sub_menu, item->sub_menu->clear);
            }
            else
            {
                cur_menu = item->sub_menu;
                atv_ca_main_menu_item_show();
            }
        }
    }
    else if (item->action == D_GUI_MENU_RUN_APP)
    {
        /*运行应用*/
        if (item->app)
        {
            item->app ();
        }
    }
}


/** @brief 事件处理*/
static D_Result
atv_ca_main_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    return d_gui_clear_menu();
                case D_KEY_BACK:
                    return show_upper_menu();
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    atv_ca_main_menu_item_action();
                    break;
                case D_KEY_MUTE:
                    return D_ERR;
                    break;
                default:
                    break;
            }
            //return D_OK;
            //break;
            break;
        case D_EVT_DESTROY:
            //g_stb->menu_status &= ~MAIN_MENU_STATUS;
            d_vis_unsubscribe_evt(vis);

            if(atv_ca_menu_data)
            {
                PROJECT_FREE(atv_ca_menu_data);
                atv_ca_menu_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
atv_ca_main_window_init(D_Frame *frm)D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_GUIMenuItem    *item;
    D_ID idx;
    D_TimerAttr timer_attr;

    atv_ca_menu_data = (D_ATVCAMainMenuData*)PROJECT_ALLOC(sizeof(D_ATVCAMainMenuData));
    if(!atv_ca_menu_data)
    {
        return D_ERR;
    }

    memset(atv_ca_menu_data, 0x00, sizeof(D_ATVCAMainMenuData));

    if(cur_ca_menu_level > 1)
    {
        cur_menu = ca_main_menu_list[cur_ca_menu_level - 1];
    }
    else
    {
        cur_menu = ca_main_menu;
        ca_main_menu_list[cur_ca_menu_level++] = cur_menu;
    }
    atv_ca_menu_data->cur_focus = cur_menu->focus;
    item = cur_menu->items;
    for(idx = 0; item->action != D_GUI_MENU_END; idx++)
    {
        item++;
        atv_ca_menu_data->ca_main_item_cnt++;
    }
    atv_ca_menu_data->list_vis = d_frame_get_control(frm, ID_CA_LIST);
    if(atv_ca_menu_data->list_vis)
    {
        d_vis_set_focus(atv_ca_menu_data->list_vis);
    }

    atv_ca_main_menu_item_show();

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_ca_main_window_handler);
    }
    return D_OK;

}

/** @brief 显示ca的公共菜单模块*/
D_Result
p_atv_ca_main_window_show(void)D_FUNCPOSTFIT
{
    D_VidInput      input;

    input = p_conf_get_vid_input ();
    if(input != D_VID_IUTPUT_DTV)
    {
        return D_OK;
    }
    if(ca_main_menu == NULL)
    {
        return D_OK;
    }
    ca_main_menu->focus = 0;
    ca_main_menu->frm = &atv_ca_main_window;
    return d_gui_enter_sys_menu (ca_main_menu, ca_main_menu->clear);
}

/** @brief 设置ca菜单*/
D_Result
p_stb_set_atv_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT
{
    ca_main_menu = camenu;
    return D_OK;
}

