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
#include "user_ok_window.c"


typedef enum
{
    P_USER_OK_MENU_CHAN_EDIT = 0,
    P_USER_OK_MENU_AUTO_SCAN = 1,
    P_USER_OK_MENU_CHAN_SWAP = 2,
    P_USER_OK_MENU_OTHERS,
} P_UserOkMenuStatus;

typedef struct
{
    D_U32    menu_show_time;
} D_UserOkData;

static D_UserOkData *user_ok_data = NULL;
static P_UserOkMenuStatus user_ok_menu_status;
static D_Bool first_flag = D_TRUE;

static D_Result user_ok_action(void);
static D_Result (*userActionHandler)(void) = NULL;

/** @brief 确定复位事件处理*/
static D_Result
button_ok_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            if(evt->fp.key == D_KEY_OK || evt->fp.key == D_KEY_PNL_OK || evt->fp.key == D_KEY_PNL_SOURCE)
            {
                if(user_ok_menu_status == P_USER_OK_MENU_OTHERS)
                {
                    if(userActionHandler)
                    {
                        return userActionHandler();
                    }
                    return D_OK;
                }
                else
                {
                return user_ok_action();
            }
            }
            break;
        case D_EVT_FP:
            if(evt->fp.key == D_KEY_OK || evt->fp.key == D_KEY_PNL_OK || evt->fp.key == D_KEY_PNL_SOURCE)
            {
                return D_OK;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
user_ok_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &user_ok_window;
    D_Visual *vis_button;

    vis_button = d_frame_get_control(frm, ID_USER_OK_BUTTON);
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
                    if(first_flag == D_TRUE)
                    {
                        d_vis_enable(vis_button, D_TRUE);
                        d_vis_set_focusable(vis_button, D_TRUE);
                        d_vis_set_focus(vis_button);
                        first_flag = D_FALSE;
                    }
                    break;
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                    if(first_flag == D_FALSE)
                    {
                        d_vis_enable(vis_button, D_FALSE);
                        d_vis_set_focusable(vis_button, D_FALSE);
                        first_flag = D_TRUE;
                    }
                    else //if(evt->fp.key != D_KEY_BACK)
                    {
                        return d_gui_clear_menu();
                    }
                    break;
                case D_KEY_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(first_flag == D_FALSE)
                    {
                        return D_OK;
                    }
                    else if(first_flag == D_TRUE)
                    {
                        return D_ERR;
                    }
                case D_KEY_SOURCE:
                case D_KEY_SCREEN:
                    d_gui_clear_menu();
                    return D_ERR;
                case D_KEY_MUTE:
                case D_KEY_VOLUME_MINUS:
                case D_KEY_VOLUME_PLUS:
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
            first_flag = D_TRUE;
        }
        break;
        default:
            break;
    }
}

D_Result
user_ok_window_init(D_Frame *frm)
{
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_USER_OK_BUTTON); //确定复位
    if(vis)
    {
        d_vis_set_handler (vis, button_ok_handler);
        d_vis_enable(vis, D_FALSE);
        d_vis_set_focusable(vis, D_FALSE);
        d_vis_subscribe_evt (vis, D_EVT_KEY_MASK, D_INVALID_HANDLE);
    }
    vis = d_frame_get_control(frm, ID_USER_OK_GROUP);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_NUM_KEY_MASK), D_INVALID_HANDLE);
        d_vis_set_handler (vis, user_ok_window_handler);
    }
    return D_OK;
}


static D_Result
startScan_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    D_VidInput input;
    D_ScanTaskConfig scan_config = {0};
    D_FULLSCAN_CONFIG fullscan_config;

    input = p_conf_get_vid_input ();
    if(p_conf_get_scan_config())
    {
        scan_config.fend_type = D_FEND_DVBC;
    }
    else
    {
        scan_config.fend_type = D_FEND_DTMB;
    }
    p_tvconf_get_fullscan_config(&fullscan_config);
    scan_config.Reserved = (D_U32)fullscan_config.standard_freq_list_flag;
    scan_config.startfreq = fullscan_config.start_freq;
    scan_config.endfreq = fullscan_config.end_freq;
    scan_config.bandwitch = fullscan_config.bandwitch;

    if(sel)
    {
        if(input == D_VID_IUTPUT_DTV)
        {
            //d_gui_clear_menu();
            return p_full_search_window_show(STB_SCAN_TYPE_FULL, &scan_config);
        }
        else if(input == D_VID_IUTPUT_TV)
        {
            //d_gui_clear_menu();
            return patv_auto_scan_analog_show();
        }
    }
    else
    {
        p_atv_menu_timeout_timer_enable(D_TRUE);
        p_atv_menu_timeout_timer_reset();
    }
    return D_OK;
}

static D_Result
startautoscan_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    if(sel)
    {
        p_atv_auto_scan_window_show();
    }

    return D_OK;
}

static D_Result
user_ok_action(void)D_FUNCPOSTFIT
{
    D_VidInput input;
    D_ScanTaskConfig scan_config = {0};

    input = p_conf_get_vid_input ();
    if(user_ok_menu_status == P_USER_OK_MENU_CHAN_EDIT)
    {
        if(input == D_VID_IUTPUT_DTV)
        {
            p_atv_manual_scan_window_show();
        }
        else if(input == D_VID_IUTPUT_TV)
        {
            p_atv_search_show(NULL);
        }
    }
    else if(user_ok_menu_status == P_USER_OK_MENU_AUTO_SCAN)
    {
        if(input == D_VID_IUTPUT_TV)
        {
            p_atv_menu_timeout_timer_enable(D_FALSE);
            //p_atv_auto_scan_select_start_show(reset_show_timer);
            d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, NULL,
                                  d_gui_get_text(atv_IDS_START_AUTO_SCAN), 10000, D_FALSE, startScan_callback, 0) ;
        }
        else if(input == D_VID_IUTPUT_DTV)
        {
            d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, NULL,
                                  d_gui_get_text(atv_IDS_START_NET_SCAN), 10000, D_FALSE, startautoscan_callback, 0) ;
        }
    }
    else if(user_ok_menu_status == P_USER_OK_MENU_CHAN_SWAP)
    {
        if(input == D_VID_IUTPUT_DTV)
        {
            p_atv_menu_timeout_timer_enable(D_FALSE);
            //p_atv_auto_scan_select_start_show(reset_show_timer);
            d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, NULL,
                                  d_gui_get_text(atv_IDS_START_ALL_SCAN), 10000, D_FALSE, startScan_callback, 0) ;

        }
        else if(input == D_VID_IUTPUT_TV)
        {
            p_atv_exchange_show(NULL);
        }
    }

    return D_OK;
}


/** @brief 频道编辑菜单*/
D_Result
p_atv_channel_editor_show (void) D_FUNCPOSTFIT
{
    user_ok_menu_status = P_USER_OK_MENU_CHAN_EDIT;
    if(D_FALSE == d_frame_is_loaded(&user_ok_window))
    {
        return d_gui_enter_menu (&user_ok_window, D_FALSE);
    }
    return D_OK;
}


/** @brief 自动搜索菜单*/
D_Result
p_atv_auto_scan_show (void) D_FUNCPOSTFIT
{
    userActionHandler = NULL;
    user_ok_menu_status = P_USER_OK_MENU_AUTO_SCAN;
    if(D_FALSE == d_frame_is_loaded(&user_ok_window))
    {
        return d_gui_enter_menu (&user_ok_window, D_FALSE);
    }
    return D_OK;
}

/** @brief 交换频道菜单*/
D_Result
p_atv_channel_change_show (void) D_FUNCPOSTFIT
{
    userActionHandler = NULL;
    user_ok_menu_status = P_USER_OK_MENU_CHAN_SWAP;
    if(D_FALSE == d_frame_is_loaded(&user_ok_window))
    {
        return d_gui_enter_menu (&user_ok_window, D_FALSE);
    }
    return D_OK;
}


/** @brief 只有个确认键的菜单*/
D_Result
p_atv_user_ok_menu_show (D_Result (*userHandler)(void)) D_FUNCPOSTFIT
{
    if(userHandler && D_FALSE == d_frame_is_loaded(&user_ok_window))
    {
        userActionHandler = userHandler;
        user_ok_menu_status = P_USER_OK_MENU_OTHERS;
        return d_gui_enter_menu (&user_ok_window, D_FALSE);
    }
    return D_OK;
}


