/** @file ptvsignal_select_window.c
**@brief 信号源选择菜单menu
**@date
**/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "dAV.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

#include "signal_select_window.c"

typedef struct
{
    D_U32       focus;
    D_VidInput      lastinput;
    D_VidInput      input;
    D_HTimer timer;
    D_U32    menu_show_time;
    D_U8   combo_key[4];
} D_SignalSelectData;

static D_SignalSelectData *signal_select_data = NULL;

#if (defined(D_IUTPUT_SUPPORT_TV))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_TV
#elif (defined(D_IUTPUT_SUPPORT_DTV))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_DTV
#elif (defined(D_IUTPUT_SUPPORT_AV1))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_AV1
#elif (defined(D_IUTPUT_SUPPORT_AV2))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_AV2
#elif (D_IUTPUT_SUPPORT_YPBPR
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_YPBPR
#elif (defined(D_IUTPUT_SUPPORT_HDMI1))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_HDMI1
#elif (defined(D_IUTPUT_SUPPORT_HDMI2))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_HDMI2
#elif (defined(D_IUTPUT_SUPPORT_USB))
#define ID_SIGNAL_BUTTON_NUM ID_SIGNAL_BUTTON_USB
#endif

static D_VidInputType stbVidInputTypes[] =
{
#if (defined(D_IUTPUT_SUPPORT_TV))
    D_VID_IUTPUT_TV,
#endif    
#if (defined(D_IUTPUT_SUPPORT_DTV))
    D_VID_IUTPUT_DTV, 
#endif    
#if (defined(D_IUTPUT_SUPPORT_AV1))
    D_VID_IUTPUT_AV1,
#endif    
#if (defined(D_IUTPUT_SUPPORT_AV2))
    D_VID_IUTPUT_AV2, 
#endif    
#if (defined(D_IUTPUT_SUPPORT_YPBPR))
    D_VID_IUTPUT_YPBPR,
#endif
#if (defined(D_IUTPUT_SUPPORT_HDMI1))
    D_VID_IUTPUT_HDMI1, 
#endif    
#if (defined(D_IUTPUT_SUPPORT_HDMI2))
    D_VID_IUTPUT_HDMI2, 
#endif    
#if (defined(D_IUTPUT_SUPPORT_USB))
    D_VID_IUTPUT_USB1,
#endif    
#ifdef D_TV_MIRACAST_SOURCE
    D_VID_IUTPUT_WIFIDISPLAY,
#endif
#ifdef D_TV_LIULINK_SOURCE
    D_VID_IUTPUT_LIULINK,
#endif

};
#define SIGNAL_SELECT_CNT (sizeof(stbVidInputTypes)/sizeof(stbVidInputTypes[0]))




/** @brief 复位显示定时器*/
static D_Result
signal_reset_show_timer(void) D_FUNCPOSTFIT
{
    if(signal_select_data && signal_select_data->timer != D_INVALID_HANDLE)
    {
        d_timer_reset(signal_select_data->timer, signal_select_data->menu_show_time);
    }

    return D_OK;
}

/** @breif 信号源窗口设置焦点*/
static D_Result
signal_set_vis_focus(void) D_FUNCPOSTFIT
{
    D_Visual * vis;
    vis = d_frame_get_control(&signal_select_window, ID_SIGNAL_BUTTON_NUM+ signal_select_data->focus);
    signal_select_data->input = stbVidInputTypes[signal_select_data->focus];
    d_vis_set_focus(vis);
    return D_OK;
}

static D_Result switch_input(void) {

    p_conf_set_vid_input(signal_select_data->input);
    if (signal_select_data->lastinput == signal_select_data->input) {
        return ;
    }
    p_sys_set_input_mode(signal_select_data->lastinput, signal_select_data->input);
    
    if(signal_select_data->input == D_VID_IUTPUT_USB1)
    {
        p_atv_media_main_menu_show();
    }
#ifdef D_TV_MIRACAST_SOURCE
    else if(signal_select_data->input == D_VID_IUTPUT_WIFIDISPLAY) {
       //p_atv_zhilian_tv_window_show(0, D_FALSE);
       //p_atv_zhilian_menu_window_show(0);
    }
#endif
#ifdef D_TV_LIULINK_SOURCE
    else if (signal_select_data->input == D_VID_IUTPUT_LIULINK)
    {
        extern int Liulinkclient_load(void);
        Liulinkclient_load();
    }
#endif
   return D_OK;
}
/** @breif 信号源窗口按键处理函数*/
D_Result
signal_button_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            signal_reset_show_timer();
            break;
        case D_EVT_LEAVE:
            break;
        case D_EVT_PRESSED:
            if(evt->fp.key == D_KEY_OK || evt->fp.key == D_KEY_PNL_OK || evt->fp.key == D_KEY_PNL_SOURCE)
            {
                switch_input();
                d_gui_close_frame(&signal_select_window);
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
 
/** @breif 信号源窗口回调处理函数*/
D_Result
signal_select_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch(evt->type)
    {
        case D_EVT_FP:
            if(p_combo_key_input(evt->fp.key) == D_OK)
            {
                d_gui_close_frame(&signal_select_window);
                p_atv_factory_setting_show();
                p_combo_key_seq_dinit();
            }
            signal_reset_show_timer();
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    return d_gui_close_frame(&signal_select_window);
                // case D_KEY_LEFT:
                //   case D_KEY_PNL_L:
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    signal_select_data->focus = ( signal_select_data->focus + SIGNAL_SELECT_CNT - 1) % SIGNAL_SELECT_CNT;
                    signal_set_vis_focus();
                    p_combo_key_seq_init(signal_select_data->combo_key, 4);
                    break;
                //case D_KEY_RIGHT:
                //case D_KEY_PNL_R:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                case D_KEY_SOURCE:
                    signal_select_data->focus = (signal_select_data->focus + 1) % SIGNAL_SELECT_CNT;
                    signal_set_vis_focus();
                    p_combo_key_seq_init(signal_select_data->combo_key, 4);
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == signal_select_data->timer)
            {
                switch_input();
                return d_gui_close_frame(&signal_select_window);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            p_atv_media_menus_show(D_TRUE, 1);
            if(signal_select_data)
            {
                if(signal_select_data->timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(signal_select_data->timer);
                }
                PROJECT_FREE(signal_select_data);
                signal_select_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @breif 信号源窗口初始化*/
D_Result
signal_select_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_VidInput      input;
    D_ID  idx;

    signal_select_data = (D_SignalSelectData*)PROJECT_ALLOC(sizeof(D_SignalSelectData));
    if(!signal_select_data)
    {
        return D_ERR;
    }
    memset(signal_select_data, 0x00, sizeof(D_SignalSelectData));

    signal_select_data->combo_key[0] = D_KEY_2;
    signal_select_data->combo_key[1] = D_KEY_5;
    signal_select_data->combo_key[2] = D_KEY_8;
    signal_select_data->combo_key[3] = D_KEY_0;
    p_combo_key_seq_init(signal_select_data->combo_key, 4);

    input = p_conf_get_vid_input ();
    signal_select_data->lastinput = input;

    for(idx = 0; idx < SIGNAL_SELECT_CNT; idx++ )
    {
        vis = d_frame_get_control(frm, ID_SIGNAL_BUTTON_NUM+ idx);
        d_vis_set_handler(vis, signal_button_handler);
        d_vis_subscribe_evt (vis, D_EVT_KEY_MASK, D_INVALID_HANDLE);
    }

    for(idx = 0; idx < SIGNAL_SELECT_CNT; idx++ )
    {
        if(input == stbVidInputTypes[idx])
        {
            signal_select_data->focus = idx;
            break;
        }
    }

    p_atv_media_menus_show(D_FALSE, 1);
#if 0
    signal_select_data->menu_show_time = (D_U32)p_conf_get_info_time();
    if(signal_select_data->menu_show_time < D_CONF_MIN_INFO_TIME)
    {
        signal_select_data->menu_show_time = D_CONF_MIN_INFO_TIME;
    }
    else if(signal_select_data->menu_show_time > D_CONF_MAX_INFO_TIME)
    {
        signal_select_data->menu_show_time = D_CONF_MAX_INFO_TIME;
    }
#else
    signal_select_data->menu_show_time = 3 * 1000;
#endif

    vis = d_frame_get_control(frm, ID_SIGNAL_GROUP_BACKGROUD);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK | D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, signal_select_window_handler);

        signal_select_data->timer = d_timer_create (NULL, signal_select_data->menu_show_time, d_gui_get_queue ());
        if(signal_select_data->timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, signal_select_data->timer);
        }
    }
    signal_set_vis_focus();
    return D_OK;
}

/** @breif 显示窗口*/
D_Result
p_atv_signal_select_show (void) D_FUNCPOSTFIT
{
    if (! d_frame_is_loaded (&signal_select_window))
    {
        return d_gui_open_frame(&signal_select_window, D_GUI_LAYER_LOGO);
    }
    return D_OK;
}

#ifdef D_TV_LIULINK_SOURCE
/** @breif 显示窗口*/
D_Result
p_atv_enter_liulink(void)
{
	signal_select_data = (D_SignalSelectData*)PROJECT_ALLOC(sizeof(D_SignalSelectData));
	if(!signal_select_data)
	{
	    return D_ERR;
	}
	memset(signal_select_data, 0x00, sizeof(D_SignalSelectData));
	D_INFO("p_atv_enter_liulink : the lastinput is %d, input is %d\n", signal_select_data->lastinput, signal_select_data->input);
	signal_select_data->lastinput = p_conf_get_vid_input ();
	if( signal_select_data->lastinput==D_VID_IUTPUT_LIULINK )
	{
		return D_ERR;
	}
	signal_select_data->input = D_VID_IUTPUT_LIULINK;
	p_conf_set_vid_input(signal_select_data->input);
	p_sys_set_input_mode(signal_select_data->lastinput, signal_select_data->input);
	extern int Liulinkclient_load(void);
	Liulinkclient_load();
	return D_OK;
}

D_Result
p_atv_exit_liulink(void)
{
	if( signal_select_data==NULL )
	{
		return D_ERR;
	}
	D_INFO("p_atv_exit_liulink : the lastinput is %d, input is %d\n", signal_select_data->lastinput, signal_select_data->input);
	if( signal_select_data->lastinput==D_VID_IUTPUT_LIULINK )
	{
		return D_ERR;
	}
	signal_select_data->input = signal_select_data->lastinput;
	signal_select_data->lastinput = D_VID_IUTPUT_LIULINK;
	switch_input();
        PROJECT_FREE(signal_select_data);
        signal_select_data = NULL;
	return D_OK;
}

#endif


