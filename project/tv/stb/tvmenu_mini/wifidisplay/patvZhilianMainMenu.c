/** @file
* @brief智联电视仿照安卓主界面
* @author
* @date 2018.07.25
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
#include "dNetwork.h"

#include "atv_zhilian_main_menu_window.c"

#define ZHILIAN_HOME_SOURCE (0)
#define ZHILIAN_HOME_SETTING (1)
#define ZHILIAN_HOME_MIRACAST (2)
#define ZHILIAN_HOME_TS2NET (3)
#define ZHILIAN_HOME_AIRPLAY (4)
#define ZHILIAN_HOME_DLNA (5)
#define ZHILIAN_HOME_IPTV (6)
#define ZHILIAN_HOME_MEDIA (7)

#define TEXT_BUFFER_LEN (64)

typedef struct
{
    D_Visual *cur_focse_vis;
    D_Visual *source_vis, *setting_vis, *mira_vis, *dlna_vis, *iptv_vis, *media_vis, *airplay_vis;
    D_U32       focus;
    D_U8        gui_lang;
    D_Char      curr_time[TEXT_BUFFER_LEN];
    D_Date      curr_date;
    D_U8   combo_key[4];
    D_U8   serial_key[4];
    
    D_Bool  wifi_status_ok;
    D_U32  change_cnt;
    D_U32  have_reset;
    D_U32  disconnet_time;  
    D_Char strPassword[16]; /*密码*/
    D_U8    last_signal;
    D_HTimer htimer_check;
    D_Char strCurrWifiName_utf8[36];
    D_Char strCurrWifiName[36]; 
} D_ZhilianMainData;

static D_ZhilianMainData *zhilianmain_data = NULL;
static D_U32 zhilianmain_lastfocus_id = ZHILIAN_HOME_SOURCE;

D_ID text_monthid[] = {atv_IDS_JANUARY, atv_IDS_FEBRUARY, atv_IDS_MARCH, atv_IDS_APRIL, atv_IDS_MAY, atv_IDS_JUNE, atv_IDS_JULY, atv_IDS_AUGUST, atv_IDS_SEPTEMBER, atv_IDS_OCTOBER, atv_IDS_NOVEMBER, atv_IDS_DECEMBER,};
D_ID text_weekid[] = {atv_IDS_SUNDAY, atv_IDS_MONDAY, atv_IDS_TUESDAY, atv_IDS_WENDSDAY, atv_IDS_THURSDAY, atv_IDS_FRIDAY, atv_IDS_SATURDAY,};
static D_U32 img_id[5] = {atv_IMG_ID_WIFI_1, atv_IMG_ID_WIFI_2, atv_IMG_ID_WIFI_3, atv_IMG_ID_WIFI_4, atv_IMG_ID_WIFI_bg};

/** @brief 取得日期时间字符串*/
D_Result
get_string_date_time(D_U8 lang, D_Date  date, D_Char *str_date, D_Size cnt)D_FUNCPOSTFIT
{
    if(str_date)
    {
        D_Char  *strmonth; /*某月份*/
        D_Char  *strweek;  /*星期几*/

        strmonth = d_gui_get_text(text_monthid[date.mon]);
        strweek = d_gui_get_text(text_weekid[date.wday]);
        if(lang == D_LANG_ENG)
        {
            snprintf (str_date, cnt, "%s, %s%d,%d, %02d:%02d", strweek, strmonth, date.mday, date.year + 1900, date.hour, date.min);
        }
        else
        {
            snprintf (str_date, cnt, "%04d年%02d月%02d日 %s %02d:%02d",
                      date.year + 1900, date.mon + 1, date.mday, strweek, date.hour, date.min);
        }
    }
    return D_OK;
}

/** @brief 显示日期与时间*/
/*static D_Result
atv_zhilian_main_menu_window_show_date_time(D_Bool first) D_FUNCPOSTFIT
{
    D_Time  now;
    D_Date  date;

    now = d_time_get_local_time();
    d_date (now, &date);
    date.sec = 0;
    zhilianmain_data->curr_date.sec = 0;

    if(first || (memcmp(&date, &zhilianmain_data->curr_date, sizeof(D_Date))))
    {
        get_string_date_time(zhilianmain_data->gui_lang, date, zhilianmain_data->curr_time, sizeof(zhilianmain_data->curr_time));
        d_label_set_text(zhilianmain_data->vis_time, zhilianmain_data->curr_time);
        zhilianmain_data->curr_date = date;
        return D_OK;
    }

    return D_ERR;
}*/


/*static D_Result
atv_zhilian_main_menu_window_get_input(void) D_FUNCPOSTFIT
{
    D_Image *img = NULL;
    D_VidInput   input;
    D_Frame *frm = &atv_zhilian_main_menu_window;
    D_Visual *vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_CUR_SOURCE);
    D_U32 text_id;
    input = p_conf_get_vid_input();

    if(input == D_VID_IUTPUT_TV)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_souce_tv);
        text_id = atv_IDS_TV;
    }
    else if(input == D_VID_IUTPUT_DTV)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_source_dtv);
        text_id = atv_IDS_DTV;
    }
    else if(input == D_VID_IUTPUT_HDMI1 || input == D_VID_IUTPUT_HDMI2)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_HDMI);
        text_id = atv_IDS_HDMI;
    }
    else if(input == D_VID_IUTPUT_AV1 || input == D_VID_IUTPUT_AV2 )
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_source_av);
        text_id = atv_IDS_AV;
    }
    else if(input == D_VID_IUTPUT_USB1)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_source_media);
        text_id = atv_IDS_USB;
    }
    else if(input == D_VID_IUTPUT_YPBPR)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_source_ypbpr);
        text_id = atv_IDS_YPBPR;
    }
    else if(input == D_VID_IUTPUT_WIFIDISPLAY)
    {
        img = d_gui_get_image(atv_IMG_ID_main_zhilian_source_ypbpr);
        text_id = atv_IDS_ZHILIAN_TV;
    }
    d_image_box_set_image(vis, img);
    return D_OK;
}*/

static D_Result
set_wifi_quality_param(D_U8 quality) D_FUNCPOSTFIT
{
    D_Visual * vis;
    D_Frame *frm = &atv_zhilian_main_menu_window;
    D_Char currWifiName[36] = {0};
    D_Char currWifiName_utf8[36] = {0};
    
    d_image_box_set_image(d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG), d_gui_get_image(img_id[4]));
    vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC);
    d_vis_show(vis, D_TRUE);
    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG), D_TRUE);
    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC), D_TRUE);
    // D_DUMP("quality = %d**************\n",quality);
    // 目前signal 的值比较小 @qiny 20190130
    if(quality >= 47) //(quality >= 80 && quality <= 100)
    {
        d_image_box_set_image( vis, d_gui_get_image(img_id[3]));
    }
    else if(quality >= 38) //(quality >= 60 && quality < 80)
    {
        d_image_box_set_image( vis, d_gui_get_image(img_id[2]));
    }
    else if(quality >= 30) //(quality >= 40 && quality < 60)
    {
        d_image_box_set_image( vis, d_gui_get_image(img_id[1]));
    }
    else if(quality >= 20) //(quality >= 20 && quality < 40)
    {
        d_image_box_set_image( vis, d_gui_get_image(img_id[0]));
    }
    else
    {
        d_image_box_set_image( vis, d_gui_get_image(img_id[4]));
        d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
        currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
        p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
        strncpy(zhilianmain_data->strCurrWifiName, currWifiName, sizeof(zhilianmain_data->strCurrWifiName));
    }
#if 1
    sprintf(zhilianmain_data->strPassword , "%d%%", quality);
#else
    //test
    if(pConnectMenuDat->wifi_status_ok)
    {
        sprintf(pConnectMenuDat->strPassword , "%d %d %d", quality, pConnectMenuDat->change_cnt, pConnectMenuDat->have_reset);
    }
    else
    {
        sprintf(pConnectMenuDat->strPassword , "-%d %d %d", quality, pConnectMenuDat->change_cnt, pConnectMenuDat->have_reset);
    }
#endif
    d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL), zhilianmain_data->strPassword);

    return D_OK;
}
static D_Result
get_wifi_quality_param(void) D_FUNCPOSTFIT
{
    _net_cur_info_t  info;
    D_Bool valid = D_TRUE;

    if(0 != d_network_get_curr_info("wlan0", &info))
    {
        info.signal = 0;
        valid = D_FALSE;
        
        zhilianmain_data->disconnet_time++;
        if((zhilianmain_data->disconnet_time & 0x0F) == 0x00)
        {
            int ret = d_wireless_sreset();
            zhilianmain_data->have_reset++;
            zhilianmain_data->have_reset %= 100;
            zhilianmain_data->disconnet_time = 0;
            D_DUMP("d_wireless_sreset() ret %d\n", ret);
        }
    }
    else
    {
        zhilianmain_data->disconnet_time = 0;
    }

    if(zhilianmain_data->wifi_status_ok != valid)
    {
        zhilianmain_data->change_cnt++;
    }

    /* 变化时再刷菜单*/
    if(zhilianmain_data->last_signal != info.signal || zhilianmain_data->wifi_status_ok != valid)
    {
        zhilianmain_data->last_signal = info.signal;
        zhilianmain_data->wifi_status_ok = valid;
        set_wifi_quality_param(info.signal);
    }
    return D_OK;
}


static D_Result
atv_zhilian_main_menu_connect_wifi(void) D_FUNCPOSTFIT
{
    if(d_network_get_connect_status() != 1) 
    {
#ifdef D_TV_SUPPORT_WIFI
        D_Bool wifi_ok = D_TRUE;
        /*检查一下wifi模块有效性*/
        //d_label_set_text(wifi_info_vis,"正在连接");
        d_wireless_open(0);
        d_task_wait(50);
        if(d_wireless_check_device("wlan0") < 0)
        {
            wifi_ok = D_FALSE;
            /*尝试卸载后重新加载*/
            D_DUMP("no wlan0 device, restart\n");
            d_wireless_close(1);
            d_wireless_open(1);
            d_task_wait(10);
            if(d_wireless_check_device("wlan0") < 0)
            {
                D_DUMP("no wlan0 device, restart\n");
                wifi_ok = D_FALSE;
            }
            else
            {
                wifi_ok = D_TRUE;
            }
        }
        if(wifi_ok)
        {
            d_network_init();
            d_network_test_communicate();
            d_wireless_start_check(NULL);
            D_DUMP("WIFI, ok!---------   %d \n", d_network_get_connect_status());
        }
#endif
    }
     return D_OK;
}

static D_Result
atv_zhilian_main_menu_window_ok_action(void) D_FUNCPOSTFIT
{
    D_VidInput      input;
    input = p_conf_get_vid_input ();

    if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->source_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_SOURCE;
        //p_atv_zhilian_main_menu_window_hide();
        p_atv_signal_select_show();
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->setting_vis)
    {
        d_vis_show(d_frame_get_control(&atv_zhilian_main_menu_window, ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP), D_FALSE);
        zhilianmain_lastfocus_id = ZHILIAN_HOME_SETTING;
#ifdef D_TV_SUPPORT_WIFI
        D_Bool wifi_ok = D_TRUE;
        /*检查一下wifi模块有效性*/
        d_wireless_open(0);
        d_task_wait(50);
        if(d_wireless_check_device("wlan0") < 0)
        {
            wifi_ok = D_FALSE;
            /*尝试卸载后重新加载*/
            D_DUMP("no wlan0 device, restart\n");
            d_wireless_close(1);
            d_wireless_open(1);
            d_task_wait(10);
            if(d_wireless_check_device("wlan0") < 0)
            {
                D_DUMP("no wlan0 device, restart\n");
                wifi_ok = D_FALSE;
            }
            else
            {
                wifi_ok = D_TRUE;
            }
        }
        if(wifi_ok)
        {
            d_network_init();
            d_network_test_communicate();
            p_atv_wifi_setting_window_show();
        }
        else
        {
            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                               D_GUI_LAYER_MESSAGE,
                               D_POP_MSG_ERROR, "", "Error ! Please check wifi device.",
                               3000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
        }
#endif
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->mira_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_MIRACAST;
#if defined( D_TV_MIRACAST_SOURCE)
        p_atv_zhilian_main_menu_window_hide();
        p_atv_zhilian_tv_window_show(0, D_TRUE);
#endif
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->dlna_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_DLNA;
#if defined(D_TV_DLNA_SOURCE)
        p_atv_zhilian_main_menu_window_hide();
        p_atv_zhilian_tv_window_show(1, D_TRUE);
#endif
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->iptv_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_IPTV;
#ifdef D_TV_SUPPORT_IPTV
	if(d_network_get_connect_status() != 1) 
	{
#ifdef D_TV_SUPPORT_WIFI
            D_Bool wifi_ok = D_TRUE;
            /*检查一下wifi模块有效性*/
            d_wireless_open(0);
            d_task_wait(50);
            if(d_wireless_check_device("wlan0") < 0)
            {
                wifi_ok = D_FALSE;
                /*尝试卸载后重新加载*/
                D_DUMP("no wlan0 device, restart\n");
                d_wireless_close(1);
                d_wireless_open(1);
                d_task_wait(10);
                if(d_wireless_check_device("wlan0") < 0)
                {
                    D_DUMP("no wlan0 device, restart\n");
                    wifi_ok = D_FALSE;
                }
                else
                {
                    wifi_ok = D_TRUE;
                }
            }
            if(wifi_ok)
            {
                d_network_init();
                d_network_test_communicate();
                d_wireless_start_check(NULL);
                D_DUMP("WIFI, ok!---------   %d \n", d_network_get_connect_status());
                //p_atv_wifi_setting_window_show();
				
               p_atv_zhilian_main_menu_window_hide();
               p_stb_enter_iptv();
            }
            else
            {
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                                   D_GUI_LAYER_MESSAGE,
                                   D_POP_MSG_ERROR, "", "Error ! Please check wifi device.",
                                   3000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
            }
#endif
        }
	else
	{
		D_DUMP("WIFI, ok!---------   \n");
               p_atv_zhilian_main_menu_window_hide();
               p_stb_enter_iptv();
	}
#endif
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->media_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_MEDIA;
        p_atv_zhilian_main_menu_window_hide();
        p_conf_set_vid_input(D_VID_IUTPUT_USB1);
        p_sys_set_input_mode(input, D_VID_IUTPUT_USB1);
        p_atv_media_main_menu_show();
    }
    else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->airplay_vis)
    {
        zhilianmain_lastfocus_id = ZHILIAN_HOME_AIRPLAY;
#ifdef D_TV_SUPPORT_AIRPLAY
        p_atv_zhilian_main_menu_window_hide();
        p_atv_zhilian_tv_window_show(3, D_TRUE);
#endif
    }
    return D_OK;
}

static D_Result
atv_zhilian_main_menu_window_focse_deal(D_FPKey key) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_zhilian_main_menu_window;

    switch (key)
    {
        case D_KEY_DOWN:
        case D_KEY_D:
        case D_KEY_PNL_D:
            if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->mira_vis)
            {
                d_vis_set_focus(zhilianmain_data->dlna_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->dlna_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmain_data->airplay_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->airplay_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->media_vis)
            {
                d_vis_set_focus(zhilianmain_data->source_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->source_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->iptv_vis)
            {
                d_vis_set_focus(zhilianmain_data->setting_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->setting_vis;
            }
            break;
        case D_KEY_UP:
        case D_KEY_U:
        case D_KEY_PNL_U:
            if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->setting_vis)
            {
                d_vis_set_focus(zhilianmain_data->iptv_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->iptv_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->source_vis)
            {
                d_vis_set_focus(zhilianmain_data->media_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->media_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->airplay_vis)
            {
                d_vis_set_focus(zhilianmain_data->dlna_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->dlna_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmain_data->mira_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->mira_vis;
            }
            break;
        case D_KEY_RIGHT:
        case D_KEY_R:
        case D_KEY_PNL_R:
            if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->mira_vis)
            {
                d_vis_set_focus(zhilianmain_data->media_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->media_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->media_vis)
            {
                d_vis_set_focus(zhilianmain_data->iptv_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->iptv_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->airplay_vis || zhilianmain_data->cur_focse_vis ==  zhilianmain_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmain_data->source_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->source_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->source_vis)
            {
                d_vis_set_focus(zhilianmain_data->setting_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->setting_vis;
            }
            break;
        case D_KEY_LEFT:
        case D_KEY_L:
        case D_KEY_PNL_L:
            if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->iptv_vis)
            {
                d_vis_set_focus(zhilianmain_data->media_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->media_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->media_vis)
            {
                d_vis_set_focus(zhilianmain_data->mira_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->mira_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->source_vis)
            {
                d_vis_set_focus(zhilianmain_data->airplay_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->airplay_vis;
            }
            else if(zhilianmain_data->cur_focse_vis ==  zhilianmain_data->setting_vis)
            {
                d_vis_set_focus(zhilianmain_data->source_vis);
                zhilianmain_data->cur_focse_vis = zhilianmain_data->source_vis;
            }
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
atv_zhilian_main_menu_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_zhilian_main_menu_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            if((p_combo_key_input(evt->fp.key) == D_OK) && (zhilianmain_data->cur_focse_vis == zhilianmain_data->setting_vis))
            {
                p_atv_factory_setting_show();
                p_combo_key_seq_dinit();
            }
            if((p_combo_key_input1(evt->fp.key) == D_OK) && (zhilianmain_data->cur_focse_vis == zhilianmain_data->setting_vis))
            {
                //p_atv_serial_show();
                p_combo_key_seq_dinit();
            }
            switch (evt->fp.key)
            {
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    return D_ERR;
                    break;
                case D_KEY_ESC:
                case D_KEY_BACK:
                case D_KEY_HOME:
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    atv_zhilian_main_menu_window_ok_action();
                    break;
                case D_KEY_DOWN:
                case D_KEY_D:
                case D_KEY_PNL_D:
                case D_KEY_UP:
                case D_KEY_U:
                case D_KEY_PNL_U:
                case D_KEY_LEFT:
                case D_KEY_L:
                case D_KEY_PNL_L:
                case D_KEY_RIGHT:
                case D_KEY_R:
                case D_KEY_PNL_R:
                    p_combo_key_seq_init(zhilianmain_data->combo_key, 4);
                    p_combo_key_seq_init1(zhilianmain_data->serial_key, 4);
                    atv_zhilian_main_menu_window_focse_deal(evt->fp.key);
                    break;
                default:
                    break;
            }
            return D_OK;
        }
        case D_EVT_TIMER:
            if (evt->timer.htimer == zhilianmain_data->htimer_check)
            {
                d_timer_reset(zhilianmain_data->htimer_check, 1000);
                D_Char currWifiName[36] = {0};
                D_Char currWifiName_utf8[36] = {0};
                
                if(p_atv_wifi_setting_window_is_close() == D_OK)
                {
                    d_vis_show(d_frame_get_control(&atv_zhilian_main_menu_window, ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP), D_TRUE);
                }
                
                if(d_network_get_connect_status() == 1)
                {
                    _net_cur_info_t curinfo = {0};
                    
                    d_network_get_curr_info("wlan0", &curinfo);
                    strcpy(currWifiName_utf8, curinfo.name);
                    currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                    if(strcmp(zhilianmain_data->strCurrWifiName_utf8, currWifiName_utf8) != 0)
                    {
                        strncpy(zhilianmain_data->strCurrWifiName_utf8, currWifiName_utf8, sizeof(zhilianmain_data->strCurrWifiName_utf8));
                        p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
                        strncpy(zhilianmain_data->strCurrWifiName, currWifiName, sizeof(zhilianmain_data->strCurrWifiName));
                        zhilianmain_data->strCurrWifiName[sizeof(zhilianmain_data->strCurrWifiName) - 1] = '\0';
                    } 
                    d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_INFO),d_gui_get_text(atv_IDS_WIFI_CONNECTED));
                    get_wifi_quality_param();
                    d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME),zhilianmain_data->strCurrWifiName);
                    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME), D_TRUE);
                    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL), D_TRUE);
                }
                else
                {
                    if(d_wireless_is_connecting())
                    {
                            d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
                            currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                            p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
                            strncpy(zhilianmain_data->strCurrWifiName, currWifiName, sizeof(zhilianmain_data->strCurrWifiName));
                            d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_INFO),d_gui_get_text(atv_IDS_WIFI_CONNECT));
                            d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME),zhilianmain_data->strCurrWifiName);
                            //d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME), D_TRUE);
                    }
                    else
                    {
                         d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_INFO),d_gui_get_text(atv_IDS_WIFI_NO_CONNECT));
                        d_label_set_text(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME),"                Wi-Fi");
                         //d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_NAME), D_FALSE);
                    }

                    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG), D_FALSE);
                    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC), D_FALSE);
                    d_vis_show(d_frame_get_control(frm, ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL), D_FALSE);
                }
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            p_stb_reset_mute_status();
            if(zhilianmain_data)
            {
                if(zhilianmain_data->htimer_check != D_INVALID_HANDLE)
                {
                    d_timer_destroy(zhilianmain_data->htimer_check);
                    zhilianmain_data->htimer_check = D_INVALID_HANDLE;
                }   
                PROJECT_FREE(zhilianmain_data);
                zhilianmain_data = NULL;
            }
            break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
atv_zhilian_main_menu_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    zhilianmain_data = (D_ZhilianMainData*)PROJECT_ALLOC(sizeof(D_ZhilianMainData));
    if(!zhilianmain_data)
    {
        return D_ERR;
    }
    memset(zhilianmain_data, 0, sizeof(D_ZhilianMainData));

    zhilianmain_data->setting_vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_SETTING);
    zhilianmain_data->source_vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_SOURCE);
    zhilianmain_data->iptv_vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_IPTV);
    zhilianmain_data->dlna_vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_DLNA);
    zhilianmain_data->mira_vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_MIRA);
    zhilianmain_data->media_vis =  d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_MEDIA);
    zhilianmain_data->airplay_vis =  d_frame_get_control(frm, ID_ZHILIAN_MAIN_BUTTON_AIRPLAY);
    zhilianmain_data->gui_lang = p_conf_get_lang();

    vis = d_frame_get_control(frm, ID_ZHILIAN_MAIN_GROUP_BUTTON);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        zhilianmain_data->htimer_check = d_timer_create (NULL, 500, d_gui_get_queue ());
        if(zhilianmain_data->htimer_check != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, zhilianmain_data->htimer_check);
        }
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, atv_zhilian_main_menu_window_handler);
    }
    //atv_zhilian_main_menu_window_get_input();
    //atv_zhilian_main_menu_window_show_date_time(D_TRUE);


    zhilianmain_data->combo_key[0] = D_KEY_8;
    zhilianmain_data->combo_key[1] = D_KEY_8;
    zhilianmain_data->combo_key[2] = D_KEY_9;
    zhilianmain_data->combo_key[3] = D_KEY_3;
    p_combo_key_seq_init(zhilianmain_data->combo_key, 4);

    zhilianmain_data->serial_key[0] = D_KEY_8;
    zhilianmain_data->serial_key[1] = D_KEY_8;
    zhilianmain_data->serial_key[2] = D_KEY_9;
    zhilianmain_data->serial_key[3] = D_KEY_4;
    p_combo_key_seq_init1(zhilianmain_data->serial_key, 4);

    /* 将背面静音*/
    d_tv_set_aud_mute (g_stb->player->htv, D_TRUE);

    /* 设定上一个焦点*/
    switch(zhilianmain_lastfocus_id)
    {
        case ZHILIAN_HOME_SETTING:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->setting_vis;
            break;
        case ZHILIAN_HOME_MIRACAST:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->mira_vis;
            break;
        case ZHILIAN_HOME_TS2NET:
            //zhilianmain_data->cur_focse_vis = zhilianmain_data->tvweb_vis;
            break;
        case ZHILIAN_HOME_AIRPLAY:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->airplay_vis;
            break;
        case ZHILIAN_HOME_DLNA:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->dlna_vis;
            break;
        case ZHILIAN_HOME_IPTV:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->iptv_vis;
            break;
        case ZHILIAN_HOME_MEDIA:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->media_vis;
            break;
        case ZHILIAN_HOME_SOURCE:
        default:
            zhilianmain_data->cur_focse_vis = zhilianmain_data->source_vis;
            break;
    }
    d_vis_set_focus(zhilianmain_data->cur_focse_vis);
    zhilianmain_data->last_signal = 0xFF;
    atv_zhilian_main_menu_connect_wifi();
    return D_OK;
}

/** @brief  电视机安卓主菜单open*/
D_Result
p_atv_zhilian_main_menu_window_show (void) D_FUNCPOSTFIT
{
    if (! d_frame_is_loaded (&atv_zhilian_main_menu_window))
    {
        //return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_zhilian_main_menu_window, D_CLEAR_ALL);
        return d_gui_open_frame(&atv_zhilian_main_menu_window, D_GUI_LAYER_USER_0);
    }
    return D_OK;
}

/** @brief  电视机安卓主菜单close*/
D_Result
p_atv_zhilian_main_menu_window_hide (void) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_zhilian_main_menu_window))
    {
        //return d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
        return d_gui_close_frame(&atv_zhilian_main_menu_window);
    }
    return D_OK;
}

