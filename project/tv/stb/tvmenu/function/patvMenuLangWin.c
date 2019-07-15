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
#include "atv_menu_lang_window.c"

extern D_Coord fun_menu_pos_x;
extern D_Coord fun_menu_pos_y;

#define MENU_LANG_BUTTON_NUM (2)

typedef struct
{
    D_S16 menu_old_lang_id;
    D_S16 menu_lang_id;
    D_Visual *vis_1, *vis_2;
    D_Bool first_flag;
} D_MenuLangData;

static D_MenuLangData *menulang_data = NULL;

/*发送更新语言事件*/
static D_Result
atv_send_update_language_evt(D_U32 curr_lang)D_FUNCPOSTFIT
{
    D_Msg user_msg = {0};

    user_msg.type = D_MSG_USER;
    user_msg.user.handle = D_INVALID_HANDLE;
    user_msg.user.param1 = USER_MSG_PARAM1_LANGUAGE_CHANGE;
    user_msg.user.param2 = curr_lang;
    d_queue_try_send(d_gui_get_queue(), (D_U8*)&user_msg, sizeof(user_msg));

    return D_OK;
}

/*取得参数*/
static D_U8 atv_menu_lang_get_param(void)D_FUNCPOSTFIT
{
    D_U8 lang;

    /*取得参数*/
    lang = p_conf_get_lang();
    if(lang == D_LANG_ENG)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*保存参数*/
static D_Result atv_menu_lang_save_param(D_S16 flag)D_FUNCPOSTFIT
{
    /*保存参数*/
    p_conf_set_lang((flag == 0) ? D_LANG_ENG : D_LANG_CHN);

    return D_OK;
}

/*设置参数到驱动*/
static D_Result atv_menu_lang_set_param(void)D_FUNCPOSTFIT
{
    if(menulang_data->menu_lang_id != menulang_data->menu_old_lang_id)
    {
        D_U8 lang;
        lang = (menulang_data->menu_lang_id == 0) ? D_LANG_ENG : D_LANG_CHN;
        p_conf_set_lang(lang);
        d_gui_lang_set(lang);
        d_gui_reload_string();
        atv_send_update_language_evt(lang);
        menulang_data->menu_old_lang_id = menulang_data->menu_lang_id;
    }

    return D_OK;
}

/** @brief 5秒事件处理*/
static D_Result
button_lang_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            atv_menu_lang_set_param();
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


static D_Result
set_lang_button_enable (D_Bool flag) D_FUNCPOSTFIT
{
    d_vis_enable(menulang_data->vis_1, flag);
    d_vis_enable(menulang_data->vis_2, flag);

    d_vis_set_focusable(menulang_data->vis_1, flag);
    d_vis_set_focusable(menulang_data->vis_2, flag);

    if(!flag)
    {
        if(menulang_data->menu_lang_id  != 0)d_vis_enable(menulang_data->vis_1, D_TRUE);
        if(menulang_data->menu_lang_id  != 1)d_vis_enable(menulang_data->vis_2, D_TRUE);
    }
    return D_OK;
}

static D_Result
set_lang_vis_focus (D_S16 flag) D_FUNCPOSTFIT
{
    switch(flag)
    {
        case 0:
            d_vis_set_focus(menulang_data->vis_1);
            break;
        case 1:
            d_vis_set_focus(menulang_data->vis_2);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
atv_menu_lang_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_menu_lang_window;

    D_Visual * left_vis, *right_vis;

    left_vis = d_frame_get_control (frm, ID_MENULANG_IMAGE_LEFT_ARROW);
    right_vis = d_frame_get_control (frm, ID_MENULANG_IMAGE_RIGHT_ARROW);

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                    if(menulang_data->first_flag == D_TRUE)
                    {
                        d_vis_subscribe_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
                        d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                        d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                        set_lang_button_enable(D_TRUE);
                        set_lang_vis_focus(menulang_data->menu_lang_id);
                        menulang_data->first_flag = D_FALSE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(menulang_data->first_flag == D_FALSE)
                    {
                        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);

                        d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                        d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                        set_lang_button_enable(D_FALSE);
                        menulang_data->first_flag = D_TRUE;
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
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_no_focus));

                    menulang_data->menu_lang_id = (menulang_data->menu_lang_id + MENU_LANG_BUTTON_NUM - 1) % MENU_LANG_BUTTON_NUM;
                    set_lang_vis_focus(menulang_data->menu_lang_id);

                }
                break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                {
                    d_image_box_set_image(left_vis, d_gui_get_image(atv_IMG_ID_left_arrow_no_focus));
                    d_image_box_set_image(right_vis, d_gui_get_image(atv_IMG_ID_right_arrow_focus));

                    menulang_data->menu_lang_id = (menulang_data->menu_lang_id + 1) % MENU_LANG_BUTTON_NUM;
                    set_lang_vis_focus(menulang_data->menu_lang_id);
                }
                break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(menulang_data->first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(menulang_data->first_flag == D_TRUE)
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
            if(menulang_data)
            {
                atv_menu_lang_save_param(menulang_data->menu_lang_id);
                PROJECT_FREE(menulang_data);
                menulang_data = NULL;
            }
        }
        break;
        default:
            break;
    }
}

D_Result
atv_menu_lang_window_init(D_Frame *frm)
{
    D_Visual *vis;

    menulang_data = (D_MenuLangData*)PROJECT_ALLOC(sizeof(D_MenuLangData));
    if(!menulang_data)
    {
        return D_ERR;
    }
    memset(menulang_data, 0x00, sizeof(D_MenuLangData));

    menulang_data->menu_old_lang_id = (D_S16)atv_menu_lang_get_param();
    menulang_data->menu_lang_id = menulang_data->menu_old_lang_id;
    menulang_data->vis_1 = d_frame_get_control(frm, ID_MENULANG_BUTTON_1);
    menulang_data->vis_2 = d_frame_get_control(frm, ID_MENULANG_BUTTON_2);

    d_vis_set_handler (menulang_data->vis_1, button_lang_handler);
    d_vis_set_handler (menulang_data->vis_2, button_lang_handler);

    menulang_data->first_flag = D_TRUE;

    vis = d_frame_get_control(frm, ID_MENULANG_GROUP_BG);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        //d_vis_enable(vis, D_FALSE);
        set_lang_button_enable(D_FALSE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_set_pos(vis, fun_menu_pos_x, fun_menu_pos_y, vis->rect.w, vis->rect.h);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK) & ( ~ D_EVT_LEFT_RIGHT_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_menu_lang_window_handler);
    }

    return D_OK;
}

/** @brief 显示菜单语言菜单*/
D_Result
p_atv_menu_lang_show (void) D_FUNCPOSTFIT
{
    if (D_FALSE == d_frame_is_loaded (&atv_menu_lang_window))
    {
        d_gui_enter_menu (&atv_menu_lang_window, D_FALSE);
    }
    return D_OK;
}

