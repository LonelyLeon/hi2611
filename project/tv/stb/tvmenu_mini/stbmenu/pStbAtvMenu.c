/** @file pStbAtvMenu.c
*@brief 主菜单menu
*@date 2014-7-20
*/

#include "pPlayer.h"
#include "pMenu.h"
#include "pPopMsg.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pStb.h"

extern D_Frame atv_main_menu_window;
extern D_Frame atv_sub_menu_window;

D_Coord sub_menu_pos_x = 0;
D_Coord sub_menu_pos_y = 0;
D_Coord fun_menu_pos_x = 0;
D_Coord fun_menu_pos_y = 0;

static D_GUIMenuItem
atv_image_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_contrast_show, D_FALSE, atv_IDS_CONTRAST, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_bright_show, D_FALSE, atv_IDS_BRIGHTNESS, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_color_show, D_FALSE, atv_IDS_COLOR, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_definition_show, D_FALSE, atv_IDS_SHARPNESS, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_tint_show, D_FALSE, atv_IDS_TINT, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_video_mode_show, D_FALSE, atv_IDS_PICTURE_MODE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_zoom_mode_show, D_FALSE, atv_IDS_ASPECT_RATIO, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_color_mode_show, D_FALSE, atv_IDS_COLOR_TEMP, -1),
    D_GUI_MENU_ITEM_END()
};

/*图像菜单*/
D_GUIMenu
atv_image_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_image_menu_items, atv_IDS_PICTURE, atv_IMG_ID_main_menu_pic, D_CLEAR_NONE);

static D_GUIMenuItem
atv_voice_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_voice_show, D_FALSE, atv_IDS_VOLUME, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_balance_show, D_FALSE, atv_IDS_BALANCE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_digital_adjust_show, D_FALSE, atv_IDS_DIGITAL_TONE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_round_show, D_FALSE, atv_IDS_SRS, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_smart_sound_show, D_FALSE, atv_IDS_AVL, -1),
    D_GUI_MENU_ITEM_END()
};

/*声音菜单*/
D_GUIMenu
atv_voice_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_voice_menu_items, atv_IDS_SOUND, atv_IMG_ID_main_menu_voice, D_CLEAR_NONE);

static D_GUIMenuItem
atv_tunning_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_channel_editor_show, D_FALSE, atv_IDS_PROGRAM_EDIT, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_channel_change_show, D_FALSE, atv_IDS_EXCHANGE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_auto_scan_show, D_FALSE, atv_IDS_AUTO_TUNING, -1),//atv_IDS_AUTO_TUNING atv_IDS_NET_SEARCH
    D_GUI_MENU_ITEM_END()
};

/*调谐菜单*/
D_GUIMenu
atv_tunning_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_tunning_menu_items, atv_IDS_CHANNEL, atv_IMG_ID_main_menu_turn, D_CLEAR_NONE);

static D_GUIMenuItem
atv_function_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_menu_time_show, D_FALSE, atv_IDS_MENU_TIMEOUT, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_digital_noise_show, D_FALSE, atv_IDS_PICTURE_OPTIMIZE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_bglight_show, D_FALSE, atv_IDS_BACKLIGHT, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_reset_show, D_FALSE, atv_IDS_RESET, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_menu_lang_show, D_FALSE, atv_IDS_OSD_LANGUAGE, -1),
    D_GUI_MENU_ITEM_END()
};

/*功能菜单*/
D_GUIMenu
atv_function_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_function_menu_items, atv_IDS_FUNCTION, atv_IMG_ID_main_menu_funtion, D_CLEAR_NONE);

#if 0 
static D_GUIMenuItem
atv_adjust_menu_items[] =
{
    D_GUI_MENU_ITEM_RUN(p_atv_picture_position_show, D_FALSE, atv_IDS_IMAGE_POSITION, -1),
    D_GUI_MENU_ITEM_RUN(NULL, D_FALSE, atv_IDS_HORIZONTAL_AMPLITUDE, -1),
    D_GUI_MENU_ITEM_RUN(NULL, D_FALSE, atv_IDS_VERTICAL_AMPLITUDE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_auto_adjust_show, D_FALSE, atv_IDS_AUTO_ADJUST, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_clock_show, D_FALSE, atv_IDS_CLOCK, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_phase_show, D_FALSE, atv_IDS_PHASE, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_adjust_reset_show, D_FALSE, atv_IDS_RESET, -1),
    D_GUI_MENU_ITEM_END()
};

/*调整菜单*/
D_GUIMenu
atv_adjust_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_adjust_menu_items, atv_IDS_ADJUST, atv_IMG_ID_adjust_icon_big, D_CLEAR_NONE);
#endif
static D_GUIMenuItem
atv_time_menu_items[] =
{
//    D_GUI_MENU_ITEM_RUN(p_atv_set_time_show, D_FALSE, atv_IDS_CURRENT_TIME, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_power_off_show, D_FALSE, atv_IDS_OFF_TIME, -1),
    D_GUI_MENU_ITEM_RUN(p_atv_power_on_show, D_FALSE, atv_IDS_ON_TIME, -1),
//    D_GUI_MENU_ITEM_RUN(p_atv_boot_ch_show, D_FALSE, atv_IDS_ON_CHANNEL, -1),
//    D_GUI_MENU_ITEM_RUN(p_atv_order_time_show, D_FALSE, atv_IDS_REMIND_TIME, -1),
//    D_GUI_MENU_ITEM_RUN(p_atv_order_ch_show, D_FALSE, atv_IDS_REMIND_CHANNEL, -1),
//    D_GUI_MENU_ITEM_RUN(p_atv_sleep_show, D_FALSE, atv_IDS_SLEEP_TIMER, -1),
    D_GUI_MENU_ITEM_END()
};

/*时间菜单*/
D_GUIMenu
atv_time_menu =
    D_GUI_DECL_MENU(&atv_sub_menu_window, atv_time_menu_items, atv_IDS_TIME, atv_IMG_ID_main_menu_time, D_CLEAR_NONE);


/*主菜单各子项*/
static D_GUIMenuItem
atv_main_menu_items[] =
{
    D_GUI_MENU_ITEM_SUB(&atv_image_menu, D_FALSE, atv_IDS_PICTURE, atv_IMG_ID_main_menu_pic),
    D_GUI_MENU_ITEM_SUB(&atv_voice_menu, D_FALSE, atv_IDS_SOUND, atv_IMG_ID_main_menu_voice),
//    D_GUI_MENU_ITEM_SUB(&atv_tunning_menu, D_FALSE, atv_IDS_CHANNEL, atv_IMG_ID_main_menu_turn),
    D_GUI_MENU_ITEM_SUB(&atv_function_menu, D_FALSE, atv_IDS_FUNCTION, atv_IMG_ID_main_menu_funtion),
//   D_GUI_MENU_ITEM_SUB(&atv_adjust_menu, D_FALSE, atv_IDS_ADJUST, atv_IMG_ID_adjust_icon_small),
    D_GUI_MENU_ITEM_SUB(&atv_time_menu, D_FALSE, atv_IDS_TIME, atv_IMG_ID_main_menu_time),
    D_GUI_MENU_ITEM_END()
};

/*主菜单*/
D_GUIMenu
atv_main_menu =
    D_GUI_DECL_MENU (&atv_main_menu_window, atv_main_menu_items, -1, -1, D_CLEAR_ALL);


/** @brief 菜单事件回调*/
static D_Result
atv_menu_callback (D_GUIMenuEvent evt, D_Visual *vis) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_Result ret = D_ERR;
    D_VidInput input;

    input = p_conf_get_vid_input();

    switch (evt)
    {
        case D_GUI_MENU_BEFORE_SHOW:
            break;
        case D_GUI_MENU_SHOW:
            /*清除频道信息等界面*/
            d_gui_clear_layer (D_GUI_LAYER_VIDEO_OSD);
            d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_3);
            d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_4);
            /*清除无信号的显示*/
            p_atv_no_signal_win_hide();
            /*清除音量和静音显示*/
            p_atv_volume_window_hide();
            /*清除频道号显示*/
            d_gui_clear_layer(D_GUI_LAYER_IME);
            /*禁止显示信号中断*/
            p_set_signal_faint_msg_enable(D_FALSE, 0);
            /*关闭广播节目提示*/
            p_atv_radio_icon_win_hide();
            g_stb->status = D_STB_ST_MENU;

            break;
        case D_GUI_MENU_HIDE:
        {
            g_stb->status = D_STB_ST_PLAYING;
            if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
            {
                p_stb_player_play_valid(0);
        		player = p_stb_get_player(0);
                p_no_prog_msg(D_TRUE);
                p_set_signal_faint_msg_enable(D_TRUE, 2);
                //p_signal_faint_msg_reshow();
                d_fman_get_locked_req(player->hfman, d_gui_get_queue());
            }
            else if(input == D_VID_IUTPUT_USB1)
            {
                p_atv_media_menus_show(D_TRUE, 0);
            }
		    else if((input == D_VID_IUTPUT_AV1)||(input == D_VID_IUTPUT_AV2)|| (input == D_VID_IUTPUT_S)\
		    || (input == D_VID_IUTPUT_YPBPR) || (input == D_VID_IUTPUT_VGA)\
		    || (input == D_VID_IUTPUT_HDMI1) || (input == D_VID_IUTPUT_HDMI2)\
		    || (input == D_VID_IUTPUT_HDMI3))
		    {
                p_set_signal_faint_msg_enable(D_TRUE, 2);
                p_signal_faint_msg_reshow();
		    }
        }
        break;
        case D_GUI_MENU_ENTER:
            break;
        case D_GUI_MENU_LEAVE:
            break;
        default:
            break;
    }

    return D_OK;
}


/** @brief 菜单初始化*/
D_Result
p_atv_menu_init (void) D_FUNCPOSTFIT
{
    return d_gui_register_menu_callback (atv_menu_callback, NULL);
}

/** @brief 菜单卸载*/
D_Result
p_atv_menu_deinit (void) D_FUNCPOSTFIT
{
    return d_gui_register_menu_callback (NULL, NULL);
}

/** @brief 显示主菜单*/
D_Result
p_atv_main_menu_show (void) D_FUNCPOSTFIT
{
    D_GUIMenuItem *item;

    atv_main_menu.focus = 0;
    d_gui_enter_sys_menu(&atv_main_menu, atv_main_menu.clear);
#if 0
    item = atv_main_menu.items + atv_main_menu.focus;
    if(item->sub_menu)
    {
        item->sub_menu->focus = 0;
        if(item->sub_menu->frm)
        {
            d_gui_enter_sys_menu(item->sub_menu, item->sub_menu->clear);
        }

        item = item->sub_menu->items + item->sub_menu->focus;
        if(item->app)
        {
            item->app();
        }
    }
#endif
    return D_OK;
}
