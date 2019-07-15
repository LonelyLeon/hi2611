/** @file
@brief wifi���ô���wifi�б���
*@date qiny 2017.11. 15
@brief ���ʹ��list�ؼ������������϶࣬��Ҫ��ʵ�ʿؼ������϶�
@brief Ϊ����ϵͳ�ؼ����㣬��ʹ��button�ؼ����������Զ�����ơ�
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dTask.h"
#include "pConfig.h"
#include "dTimer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dNetwork.h"
#include "pConvCode.h"

#include "atv_wifi_setting_window.c"

#define WIFI_DEVICE_NAME  "wlan0"

#define WIFI_AP_MAX  (64)

#define WIFI_MENU_MODE_ON_OFF (0)
#define WIFI_MENU_MODE_LIST (1)

#define WIFI_LIST_ROW_CNT (8)
#define WIFI_NAME_LEN (64)

#define WIFI_DIR_LEFT (0)
#define WIFI_DIR_RIGHT (1)
#define WIFI_DIR_UP     (2)
#define WIFI_DIR_DOWN (3)
#define WIFI_DIR_PAGEUP     (4)
#define WIFI_DIR_PAGEDOWN (5)

typedef struct
{
    D_Char  str_num[WIFI_LIST_ROW_CNT][8];
    D_Char  str_name[WIFI_LIST_ROW_CNT][WIFI_NAME_LEN];
    D_Char  str_signal[WIFI_LIST_ROW_CNT][8];
    D_Char  str_info[128];
    D_Char  mac_info[20];
    D_U8   menu_lang;
    D_U32   menu_mode;
    _Wireless_AP_Info_t wifi_aps[64];
    D_S32   wifi_num;
    D_S32   wifi_start_line;
    D_S32   wifi_focus;
    D_Bool  wifi_on;
    D_HTimer htimer;
    D_Bool wifi_scanning;           /* �Ƿ�����ɨ�����*/
    D_HTask hTask_scan;
    D_HTask hTask_connect;
    D_Bool wifi_connecting;          /* �Ƿ��������ӹ���*/
    D_Bool network_connected;   /* ����������*/
    D_U32 communicate_status; /* �������磬����ͨ��״̬*/
    _net_cfg_t net_info;
    D_Char msg_title[64];
    D_Char def_passwd[32];
} D_WifiSetupData;
static D_WifiSetupData  *wifi_set_data = NULL;



static _Wireless_AP_Info_t wifi_ap_info[WIFI_AP_MAX] = {0};
static D_U32 wifi_ap_info_num = 0;
static D_Bool bWifiEnable = D_TRUE;
static _Wireless_Param_t connect_param = {0};
//extern D_Bool start_wifi_check_enable;

static D_Bool close_window_flag = D_FALSE;

/** @brief ������ܵ�wifi��¼���ⲿ����*/
void p_clear_wifi_ap_record(void)
{
    wifi_ap_info_num = 0;
}

/** @brief ���ź�����wifi*/
static int compare_apinfo(const void *elem1, const void *elem2)
{
    int val;
    _Wireless_AP_Info_t *ap1,  *ap2;

    ap1 = (_Wireless_AP_Info_t *)elem1;
    ap2 = (_Wireless_AP_Info_t *)elem2;
    if(ap1->connected != ap2->connected)
    {
        val = (int)ap2->connected - (int)ap1->connected;
    }
    else
    {
        val = (int)ap2->signal - (int)ap1->signal;
    }

    return val;
}

/** @brief ɨ��wifi, Ϊ��Ӱ���������������ʹ�õ���������*/
static void wifi_scan_proc(D_Ptr p) D_FUNCPOSTFIT
{
    int num, error;
    D_UserMsg umsg;

    wifi_ap_info_num = 0;
    num = WIFI_AP_MAX;
    memset(wifi_ap_info, 0x00, sizeof(wifi_ap_info));
    error = d_wireless_scan(WIFI_DEVICE_NAME, 10000,  wifi_ap_info, &num);
    if(num > 0 && num <= 64)
    {
        wifi_ap_info_num = num;
        qsort(wifi_ap_info, num, sizeof(_Wireless_AP_Info_t), compare_apinfo);
    }

    umsg.type = D_MSG_USER;
    umsg.handle = (D_Handle)(&atv_wifi_setting_window);
    umsg.param1 = USER_MSG_PARAM1_WIFIDISPLAY_SCAN;
    umsg.param2 = (D_U32)wifi_ap_info_num;
    umsg.param3 = (D_U32)0;
    d_queue_send(d_gui_get_queue(), (D_U8*)&umsg, sizeof(D_UserMsg));
}

/** @brief ����wifi, Ϊ��Ӱ���������������ʹ�õ���������*/
static void wifi_connect_proc(D_Ptr p) D_FUNCPOSTFIT
{
    D_UserMsg umsg;
    int error;
    error = d_wireless_connect(WIFI_DEVICE_NAME, (_Wireless_Param_t *)p);
    umsg.type = D_MSG_USER;
    umsg.handle = (D_Handle)(&atv_wifi_setting_window);
    umsg.param1 = USER_MSG_PARAM1_WIFIDISPLAY_CONNECT;
    umsg.param2 = (D_U32)error;
    umsg.param3 = (D_U32)0;
    d_queue_send(d_gui_get_queue(), (D_U8*)&umsg, sizeof(D_UserMsg));
}


/** @brief �����б���ʾ*/
static D_Result
atv_wifi_setting_list_update_show (void) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID id;

    for(id = 0; id < WIFI_LIST_ROW_CNT; id++)
    {
        vis = d_frame_get_control(&atv_wifi_setting_window, (id + ID_WIFISET_LIST_BUTTON_0));
        d_vis_update(vis, NULL);
    }

    return D_OK;
}

/** @brief �л�����*/
static D_Result
atv_wifi_setting_menu_change_focus (D_U32 direction) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID id;
    D_Bool list_update = D_FALSE;
    D_Bool scroll_update = D_FALSE;

    if(direction == WIFI_DIR_UP) /* �����ƶ�*/
    {
        if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST)
        {
            if(wifi_set_data->wifi_focus == 0)
            {
                wifi_set_data->menu_mode = WIFI_MENU_MODE_ON_OFF;
            }
            else
            {
                id = wifi_set_data->wifi_focus - wifi_set_data->wifi_start_line;
                wifi_set_data->wifi_focus -= 1;
                scroll_update = D_TRUE;
                if(id <= 0)  /* �����ڵ�һ�еĿؼ���*/
                {
                    wifi_set_data->wifi_start_line = wifi_set_data->wifi_focus;
                    list_update = D_TRUE;
                }
            }
        }
    }
    else if(direction == WIFI_DIR_DOWN) /* �����ƶ�*/
    {
        if((wifi_set_data->menu_mode == WIFI_MENU_MODE_ON_OFF) && wifi_set_data->wifi_on == D_TRUE)
        {
            wifi_set_data->menu_mode = WIFI_MENU_MODE_LIST;
            wifi_set_data->wifi_focus = 0;
            wifi_set_data->wifi_start_line = 0;
        }
        else if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST)
        {
            if(wifi_set_data->wifi_focus < (wifi_set_data->wifi_num - 1))
            {
                id = wifi_set_data->wifi_focus - wifi_set_data->wifi_start_line;
                wifi_set_data->wifi_focus += 1;
                scroll_update = D_TRUE;
                if(id >= (WIFI_LIST_ROW_CNT - 1)) /* ���������һ�еĿؼ���*/
                {
                    list_update = D_TRUE;
                    wifi_set_data->wifi_start_line = D_MAX(0, (wifi_set_data->wifi_focus - (WIFI_LIST_ROW_CNT - 1)));
                }
            }
        }
    }
    else if(direction == WIFI_DIR_PAGEUP) /* ���Ϸ�ҳ*/
    {
        if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST)
        {
            if(wifi_set_data->wifi_start_line)
            {
                list_update = D_TRUE;
                scroll_update = D_TRUE;
                wifi_set_data->wifi_focus -= D_MIN(wifi_set_data->wifi_start_line, WIFI_LIST_ROW_CNT);
                wifi_set_data->wifi_start_line -= D_MIN(wifi_set_data->wifi_start_line, WIFI_LIST_ROW_CNT);
            }
        }
    }
    else if(direction == WIFI_DIR_PAGEDOWN) /* ���·�ҳ*/
    {
        if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST)
        {
            if((wifi_set_data->wifi_start_line + WIFI_LIST_ROW_CNT) < wifi_set_data->wifi_num)
            {
                list_update = D_TRUE;
                scroll_update = D_TRUE;
                wifi_set_data->wifi_start_line += WIFI_LIST_ROW_CNT;
                wifi_set_data->wifi_focus += WIFI_LIST_ROW_CNT;
                wifi_set_data->wifi_focus = D_MIN((wifi_set_data->wifi_num - 1), wifi_set_data->wifi_focus);
            }
        }
    }

    if(wifi_set_data->menu_mode == WIFI_MENU_MODE_ON_OFF)
    {
        id = ID_WIFISET_BUTTON_ON_OFF;
    }
    else
    {
        id = ID_WIFISET_LIST_BUTTON_0 + (wifi_set_data->wifi_focus - wifi_set_data->wifi_start_line);
    }

    vis = d_frame_get_control(&atv_wifi_setting_window, id);
    d_vis_set_focus(vis);

    /* ������ҳ���л�������Ҫ���������б�*/
    if(list_update)
    {
        atv_wifi_setting_list_update_show();
    }

    /* ������ֵ���ı�ʱ������Ҫ����*/
    if(scroll_update)
    {
        vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_SCROLL_BAR);
        d_scroll_bar_set_val(vis, wifi_set_data->wifi_focus);
    }

    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LABEL_MSG);
    sprintf(wifi_set_data->str_info, "");
    d_label_set_text(vis, wifi_set_data->str_info);

    return D_OK;
}

/** @breif ÿһ�е���ʾ���Զ������*/
#define POS_X_NUM (50)
#define POS_X_OK (100)
#define POS_X_NAME (160)
#define POS_X_LOCK (560)
#define POS_X_INFO (615)
#define POS_X_SIGNAL (670)

static D_Result
atv_wifi_setting_button_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    if(evt->type == D_EVT_DRAW)
    {
        D_ID row, id;
        D_Image *img;
        _Wireless_AP_Info_t *ap;
        D_Coord x, y, w, h;
        D_Rect dr, sr;
        D_FontAttribute font;
        D_TextFormat form;
        D_Char *strtext = NULL;

        row = d_frame_get_control_id(&atv_wifi_setting_window, vis);
        row = row - ID_WIFISET_LIST_BUTTON_0;
        id = wifi_set_data->wifi_start_line + row;
        if(wifi_set_data->wifi_on == D_FALSE || id >= wifi_set_data->wifi_num)
        {
            return D_OK;
        }

        memset(&font, 0x00, sizeof(D_FontAttribute));
        memset(&form, 0x00, sizeof(D_TextFormat));

        font.fontSize = (D_U16)24;
        font.fontType = (D_U16)D_FONT_DOT_MATRIX;
        font.fontColor = (D_Color)0xFF000000;
        form.align = (D_U16)(D_ALIGN_LEFT | D_ALIGN_MIDDLE);
        form.valid = D_TRUE;

        ap = &wifi_set_data->wifi_aps[id];

        /* ��ʾ���*/
        sprintf (wifi_set_data->str_num[row],  "%d", (id + 1));
        strtext = wifi_set_data->str_num[row];
        d_rect_set (&dr, POS_X_NUM, 0, (POS_X_OK - POS_X_NUM), vis->rect.h);
        d_draw_text(vis, &dr, strtext, strlen(strtext), &font, &form);

        if(ap->connected)
        {
            /* ��ʾ������ͼ��*/
            img = d_gui_get_image(atv_IMG_ID_WIFI_CONNECT);
            d_rect_set (&sr, 0, 0, img->buf.width, img->buf.height);
            y = ((vis->rect.h - img->buf.height) >> 1);
            d_rect_set (&dr, POS_X_OK, y, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);

            /* ��ʾ�Ƿ��������ı�־*/
            if(wifi_set_data->communicate_status == 0)
            {
                x = POS_X_OK + 20;
                h = 10;
                y = y + 14;
                d_rect_set (&dr, x, y, 3, h);
                d_draw_fill_rect(vis, &dr, 0xff8f0000);

                y = y + h + 2;
                d_rect_set (&dr, x, y, 3, 3);
                d_draw_fill_rect(vis, &dr, 0xff8f0000);
            }
        }

        /* ��ʾwifi��*/
        memset(wifi_set_data->str_name[row], 0x00, sizeof(wifi_set_data->str_name[row]));
        //sprintf (wifi_set_data->str_name[row], "%s", ap->essid, sizeof (wifi_set_data->str_name[row]) - 1);
        p_cc_utf8_to_sys(wifi_set_data->str_name[row], sizeof(wifi_set_data->str_name[row]), ap->essid, strlen(ap->essid));
        strtext = wifi_set_data->str_name[row];
        d_rect_set (&dr, POS_X_NAME, 0, (POS_X_LOCK - POS_X_NAME), vis->rect.h);
        d_draw_text(vis, &dr, strtext, strlen(strtext), &font, &form);

        /* ��ʾ����ͼ��*/
        if(ap->privacy)
        {
            img = d_gui_get_image(atv_IMG_ID_WIFI_LOCK);
            d_rect_set (&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set (&dr, POS_X_LOCK, ((vis->rect.h - img->buf.height) >> 1), img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }

        /* ��ʾINFO ͼ��*/
        if(ap->connected)
        {
            img = d_gui_get_image(atv_IMG_ID_info);
            d_rect_set (&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set (&dr, POS_X_INFO, ((vis->rect.h - img->buf.height) >> 1) + 1, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }

        /* ��ʾǿ��*/
        sprintf (wifi_set_data->str_signal[row],  "%d", ap->signal);
        row = ap->signal / 10; /* signal:0-100, Ŀǰֵ�ϵͣ�������ʱ��10�ø���*/ // ap->signal / 20
        for(id = 0; id < 5; id++)
        {
            x = POS_X_SIGNAL + (id * (3 + 4));
            h = 3 + (id * 4);
            y = 32 - h;
            d_rect_set (&dr, x, y, 3, h);
            d_draw_fill_rect(vis, &dr, (id >= row) ? 0xffa7a7a8 : 0xff000000);
        }
    }

    return D_ERR;
}

/** @breif ��ʼɨ��wifi�б�*/
static D_Result
atv_wifi_setting_scan_all_wifi(D_U32 action)
{
    D_Visual *vis;
    D_TaskAttr TaskAttr;

    memset(wifi_set_data->wifi_aps, 0x00, sizeof(wifi_set_data->wifi_aps));
    wifi_set_data->wifi_num = 0;
    wifi_set_data->wifi_focus = 0;
    wifi_set_data->wifi_start_line = 0;
    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_SCROLL_BAR);
    d_scroll_bar_set_range(vis, 0, 1, 1, 0);
    atv_wifi_setting_list_update_show();

    if(action == 0)
    {
        sprintf(wifi_set_data->str_info, "���ڴ�WLAN ...");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Opening  WLAN ...");
        }
    }
    else
    {
        sprintf(wifi_set_data->str_info, "����ɨ�� ...");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Scanning ...");
        }
        if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST)
        {
            vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LIST_BUTTON_0);
            d_vis_set_focus(vis);
        }
    }

    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LABEL_MSG);
    d_label_set_text(vis, wifi_set_data->str_info);

    D_TASK_ATTR_INIT(&TaskAttr);
    TaskAttr.name = "ScanWifi";
    TaskAttr.priority = D_MAIN_TASK_PRIO - 1;
    TaskAttr.stack_size = 16 * 1024;

    wifi_set_data->wifi_scanning = D_TRUE;
    wifi_set_data->hTask_scan = d_task_create(&TaskAttr, wifi_scan_proc, NULL);
    if(wifi_set_data->hTask_scan == D_INVALID_HANDLE)
    {
        D_ERROR("scanwifi task create failed!\n");
        wifi_set_data->wifi_scanning = D_FALSE;
        return D_ERR;
    }

    return D_OK;
}

/** @breif ��ȡwifi�б�����ʾ*/
static D_Result
atv_wifi_setting_get_all_wifi(void)
{
    D_Visual *vis;
    D_U32 i;
    _Wireless_AP_Info_t *ap;

    wifi_set_data->wifi_num = wifi_ap_info_num;
    if(wifi_set_data->wifi_num)
    {
        memcpy(wifi_set_data->wifi_aps, wifi_ap_info, sizeof(wifi_ap_info));
        vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_SCROLL_BAR);
        d_scroll_bar_set_range(vis, (D_U16)(wifi_set_data->wifi_num - 1), 1, 1, 0);
        wifi_set_data->wifi_focus = D_MIN(wifi_set_data->wifi_focus, (wifi_set_data->wifi_num - 1));
        d_scroll_bar_set_val(vis, wifi_set_data->wifi_focus);
        atv_wifi_setting_list_update_show();
    }
    wifi_set_data->network_connected = D_FALSE;
    for(i = 0; i < wifi_set_data->wifi_num; i++)
    {
        ap = &wifi_set_data->wifi_aps[i];
        if(ap->connected)
        {
            wifi_set_data->network_connected = D_TRUE;
        }

        D_DUMP("ap[%-2d]: p %-2x wm %-2d br %-8d freq %-8d ch %-2d q %-3d  s %-2d n %-2d privacy %-2d alg %-2d c %-2d %02X%02X%02X%02X%02X%02X %s\n", \
               i, ap->protocol, ap->wireless_mode, ap->bit_rate, ap->freq, ap->channel_num, ap->quality, ap->signal, ap->noise, ap->privacy, ap->wireless_alg, ap->cipher, \
               ap->bssid[0], ap->bssid[1], ap->bssid[2], ap->bssid[3], ap->bssid[4], ap->bssid[5], ap->essid);
    }

    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LABEL_MSG);
    d_label_set_text(vis, "");

    return D_OK;
}

/** @breif ������е�wifi�б�*/
static D_Result
atv_wifi_setting_clear_all_wifi(void)
{
    D_Visual *vis;

    wifi_set_data->wifi_num = 0;
    wifi_set_data->wifi_focus = 0;
    wifi_set_data->wifi_start_line = 0;
    wifi_set_data->network_connected = D_FALSE;
    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_SCROLL_BAR);
    d_scroll_bar_set_range(vis, 0, 1, 1, 0);
    atv_wifi_setting_list_update_show();

    return D_OK;
}

/** @breif ����˵��Ļص�*/
static D_Result
wifi_passwd_input_ok (D_Char *text, D_U32 param, D_U32 action) D_FUNCPOSTFIT
{
    D_TaskAttr TaskAttr;
    D_Visual *vis;
    _Wireless_AP_Info_t *ap;
    D_U32 i;
    D_Char name_asi[36] = {0};

    if(wifi_set_data && action)
    {
        ap = &wifi_set_data->wifi_aps[param];

        memset(&connect_param, 0x00, sizeof(connect_param));
        memcpy(connect_param.essid, ap->essid, sizeof(ap->essid));
        memcpy(connect_param.bssid, ap->bssid, sizeof(ap->bssid));
        connect_param.key_len = -1;
        if(text)
        {
            connect_param.key_len = strlen(text);
            memcpy(connect_param.key, text, connect_param.key_len);
            snprintf(ap->password, sizeof(ap->password), "%s", connect_param.key);
        }

        D_TASK_ATTR_INIT(&TaskAttr);
        TaskAttr.name = "WifiConnect";
        TaskAttr.priority = D_MAIN_TASK_PRIO - 1;
        TaskAttr.stack_size = 16 * 1024;
        wifi_set_data->network_connected = D_FALSE;
        wifi_set_data->communicate_status = 0;
        wifi_set_data->wifi_connecting = D_TRUE;
        wifi_set_data->hTask_connect = d_task_create(&TaskAttr, wifi_connect_proc, &connect_param);
        if(wifi_set_data->hTask_connect == D_INVALID_HANDLE)
        {
            D_ERROR("scanwifi task create failed!\n");
            wifi_set_data->wifi_connecting = D_FALSE;
            return D_ERR;
        }

        vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LABEL_MSG);
        p_cc_utf8_to_sys(name_asi, sizeof(name_asi), ap->essid, strlen(ap->essid));
        sprintf(wifi_set_data->str_info, "��������%s ...", name_asi);
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Connecting %s  ...", name_asi);
        }
        d_label_set_text(vis, wifi_set_data->str_info);

        for(i = 0; i < wifi_set_data->wifi_num; i++)
        {
            ap = &wifi_set_data->wifi_aps[i];
            if(ap->connected)
            {
                ap->connected = 0;
                wifi_ap_info[i].connected = 0;
                atv_wifi_setting_list_update_show();
            }
        }
    }
    return D_OK;
}

/** @breif ������Ϣ���ڵĻص�*/
static D_Result
wifi_info_set_ok (_net_cfg_t *info, D_U32 param) D_FUNCPOSTFIT
{
    _Wireless_AP_Info_t *ap;

    if(wifi_set_data)
    {
        ap = &wifi_set_data->wifi_aps[param];
        memcpy(&(wifi_set_data->net_info), info, sizeof(_net_cfg_t));
        d_wireless_set_info(WIFI_DEVICE_NAME, &(wifi_set_data->net_info));
    }
    return D_OK;
}

/** @breif ���Ӻ���ʾ��Ӧ��ip��������Ϣ*/
static D_Result
atv_wifi_setting_show_connected_info(void)
{
    if(wifi_set_data->wifi_num && wifi_set_data->wifi_focus < wifi_set_data->wifi_num)
    {
        _Wireless_AP_Info_t *ap;

        ap = &wifi_set_data->wifi_aps[wifi_set_data->wifi_focus];
        if(ap->connected)
        {
            d_wireless_get_info(WIFI_DEVICE_NAME, &(wifi_set_data->net_info));
            p_atv_wifi_detail_info_window_show(&(wifi_set_data->net_info), wifi_info_set_ok, wifi_set_data->wifi_focus);
        }
    }
    return D_OK;
}

/** @breif ��ʼ����wifi����*/
static D_Result
atv_wifi_setting_start_connect(void)
{
    if(wifi_set_data->wifi_num && wifi_set_data->wifi_focus < wifi_set_data->wifi_num)
    {
        _Wireless_AP_Info_t *ap;
        D_Char name_asi[36] = {0};

        //start_wifi_check_enable = D_FALSE;
        ap = &wifi_set_data->wifi_aps[wifi_set_data->wifi_focus];

        if(ap->privacy)
        {
            D_U32 min_len = 0, max_len = 32; // 20;
            if(ap->wireless_alg == _IW_AUTH_WPA_PSK || ap->wireless_alg == _IW_AUTH_WPA2_PSK)
            {
                min_len = 8;
                max_len = 64;
            }

            p_cc_utf8_to_sys(name_asi, sizeof(name_asi), ap->essid, strlen(ap->essid));
            sprintf(wifi_set_data->msg_title, "Input wifi %s passwd", name_asi);
            if(wifi_set_data->menu_lang == D_LANG_CHN)
            {
                sprintf(wifi_set_data->msg_title, "������ %s ����", name_asi);
            }
            sprintf(wifi_set_data->def_passwd, "");
            if(ap->password[0] != '\0' && strcmp(ap->password, "NULL") != 0)
            {
                sprintf(wifi_set_data->def_passwd, "%s", ap->password);
            }
            else
            {
                //sprintf(wifi_set_data->def_passwd, "123QAZqaz");
            }
            p_atv_textinput_window_show(wifi_set_data->msg_title, wifi_set_data->def_passwd,  min_len, max_len, wifi_passwd_input_ok, wifi_set_data->wifi_focus );
        }
        else
        {
            wifi_passwd_input_ok(NULL, wifi_set_data->wifi_focus, 1);
        }
    }

    return D_OK;
}

/** @breif ��ʾ����״̬*/
static D_Result
atv_wifi_setting_connect_result(int result)
{
    D_Visual *vis;

    if(result == 0)
    {
        _Wireless_AP_Info_t *ap;
        ap = &wifi_set_data->wifi_aps[wifi_set_data->wifi_focus];
        ap->connected = 1;
        wifi_ap_info[wifi_set_data->wifi_focus].connected = 1;
        wifi_set_data->network_connected = D_TRUE;
        if(connect_param.key > 0)
        {
            /*���ӳɹ�����������*/
            snprintf(ap->password, sizeof(ap->password), "%s", connect_param.key);
        }
        atv_wifi_setting_list_update_show();
    }

    vis = d_frame_get_control(&atv_wifi_setting_window, ID_WIFISET_LABEL_MSG);
    if(result == ROC_NET_RET_SUCCESS)
    {
        sprintf(wifi_set_data->str_info, "���ӳɹ�");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Connect Ok");
        }
#ifdef D_TV_LIULINK_SOURCE
        d_label_set_text(vis, wifi_set_data->str_info);
        p_atv_wifi_setting_window_close();
        return D_OK;
#endif
    }
    else if(result == ROC_NET_RET_PWDERR)
    {
        sprintf(wifi_set_data->str_info, "����ʧ��! �����������.");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Connect failed ! Key may be incorrect.");
        }
    }
    else if(result == ROC_NET_RET_TIMEOUT)
    {
        sprintf(wifi_set_data->str_info, "��ʱ������ʧ��!");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Timeout, connect failed !");
        }
    }
    else
    {
        sprintf(wifi_set_data->str_info, "����ʧ��!");
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_set_data->str_info, "Connect failed !");
        }
    }
    d_label_set_text(vis, wifi_set_data->str_info);

    return D_OK;
}

/** @breif ȷ�ϲ���*/
static D_Result
atv_wifi_setting_ok_action(void) D_FUNCPOSTFIT
{
    D_Visual *vis;

    if(wifi_set_data->menu_mode == WIFI_MENU_MODE_ON_OFF)
    {
        if(wifi_set_data->wifi_on == D_TRUE && wifi_set_data->wifi_scanning == D_FALSE)
        {
            wifi_set_data->wifi_on = D_FALSE;
            bWifiEnable = wifi_set_data->wifi_on;
            atv_wifi_setting_clear_all_wifi();
            vis = d_frame_get_control( &atv_wifi_setting_window, ID_WIFISET_BUTTON_ON_OFF);
            if(wifi_set_data->menu_lang == D_LANG_ENG)
            {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "LIST ON" : "LIST OFF"));
            }
            else
            {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "�б��" : "�б�ر�"));
            }
        }
        else if(wifi_set_data->wifi_on == D_FALSE)
        {
            wifi_set_data->wifi_on = D_TRUE;
            bWifiEnable = wifi_set_data->wifi_on;
            atv_wifi_setting_scan_all_wifi(0);
            vis = d_frame_get_control( &atv_wifi_setting_window, ID_WIFISET_BUTTON_ON_OFF);
            if(wifi_set_data->menu_lang == D_LANG_ENG)
            {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "LIST ON" : "LIST OFF"));
            }
            else
            {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "�б��" : "�б�ر�"));
            }
        }
    }
    else if(wifi_set_data->menu_mode == WIFI_MENU_MODE_LIST && wifi_set_data->wifi_on == D_TRUE)
    {
        atv_wifi_setting_start_connect();
    }
    return D_OK;
}

/** @breif ��ʾ����״̬*/
static D_Result
atv_wifi_setting_show_communicate_status(D_Bool status) D_FUNCPOSTFIT
{
    D_Visual *vis;
    wifi_set_data->communicate_status = status;
    atv_wifi_setting_list_update_show();
    return D_OK;
}

/** @breif ���ڻص�*/
static D_Result
atv_wifi_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        p_atv_wifi_setting_window_close();
                    }
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_PGUP:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_menu_change_focus(WIFI_DIR_PAGEUP);
                    }
                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                case D_KEY_PGDOWN:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_menu_change_focus(WIFI_DIR_PAGEDOWN);
                    }
                    break;
                case D_KEY_INFO:
                case D_KEY_BLUE:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_show_connected_info();
                    }
                    break;
                case D_KEY_GREEN:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE && wifi_set_data->wifi_on == D_TRUE)
                    {
                        atv_wifi_setting_scan_all_wifi(1);
                    }
                    break;
                case D_KEY_UP:
                case D_KEY_PNL_U:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_menu_change_focus(WIFI_DIR_UP);
                    }
                    return D_OK;
                    break;
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_menu_change_focus(WIFI_DIR_DOWN);
                    }
                    return D_OK;
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(wifi_set_data->wifi_scanning == D_FALSE && wifi_set_data->wifi_connecting == D_FALSE)
                    {
                        atv_wifi_setting_ok_action();
                    }
                    return D_OK;
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == wifi_set_data->htimer) /* ��ʱ�����������״̬*/
            {
                if(wifi_set_data->wifi_connecting == D_FALSE && wifi_set_data->network_connected)
                {
                    D_U32 status = d_network_get_communicate_status();
                    if(status != wifi_set_data->communicate_status)
                    {
                        wifi_set_data->communicate_status = status;
                        atv_wifi_setting_show_communicate_status(status);
                    }
                }
            }
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_WIFIDISPLAY_SCAN)
            {
                d_task_join(wifi_set_data->hTask_scan);
                wifi_set_data->hTask_scan = D_INVALID_HANDLE;
                wifi_set_data->wifi_scanning = D_FALSE;
                atv_wifi_setting_get_all_wifi();
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_WIFIDISPLAY_CONNECT)
            {
                d_task_join(wifi_set_data->hTask_connect);
                wifi_set_data->hTask_connect = D_INVALID_HANDLE;
                wifi_set_data->wifi_connecting = D_FALSE;
                atv_wifi_setting_connect_result((int)evt->user.param2);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(wifi_set_data)
            {
                if(D_INVALID_HANDLE != wifi_set_data->htimer)
                {
                    d_timer_destroy(wifi_set_data->htimer);
                    wifi_set_data->htimer = D_INVALID_HANDLE;
                }

                if(D_INVALID_HANDLE != wifi_set_data->hTask_scan)
                {
                    //d_task_kill(wifi_set_data->hTask_scan);
                    d_task_join(wifi_set_data->hTask_scan);
                    wifi_set_data->hTask_scan = D_INVALID_HANDLE;
                }

                if(D_INVALID_HANDLE != wifi_set_data->hTask_connect)
                {
                    //d_task_kill(wifi_set_data->hTask_connect);
                    d_task_join(wifi_set_data->hTask_connect);
                    wifi_set_data->hTask_connect = D_INVALID_HANDLE;
                }

                PROJECT_FREE(wifi_set_data);
                wifi_set_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;

}

/** @breif ���ڼ���ʱ�ĳ�ʼ��*/
D_Result
atv_wifi_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID id;
    D_Char  *mac;
    wifi_set_data = (D_WifiSetupData *)PROJECT_ALLOC(sizeof(D_WifiSetupData));
    if(wifi_set_data == NULL)
    {
        return D_ERR;
    }

    memset(wifi_set_data, 0x00, sizeof(D_WifiSetupData));
    wifi_set_data->htimer = D_INVALID_HANDLE;
    wifi_set_data->hTask_scan = D_INVALID_HANDLE;
    wifi_set_data->hTask_connect = D_INVALID_HANDLE;
    wifi_set_data->wifi_on = bWifiEnable;
    wifi_set_data->menu_mode = WIFI_MENU_MODE_ON_OFF;
    wifi_set_data->menu_lang = p_conf_get_lang();
    wifi_set_data->communicate_status = d_network_get_communicate_status();

#ifdef D_TV_SUPPORT_IPTV
    vis = d_frame_get_control( frm, ID_WIFISET_LABEL_MAC);
    if(vis)
    {
        mac = _get_mac();
        sprintf(wifi_set_data->mac_info, "MAC : %s", mac);
        d_label_set_text( vis, wifi_set_data->mac_info);
        if(mac)
            g_free(mac);
    }
#endif

    vis = d_frame_get_control( frm, ID_WIFISET_LABEL_LISTHEAD);
    if(vis)
    {
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
            d_label_set_text( vis, "WLAN Set");
        }
        else
        {
            d_label_set_text( vis, "WLAN ����");
        }
    }

    vis = d_frame_get_control( frm, ID_WIFISET_BUTTON_ON_OFF);
    if(vis)
    {
        if(wifi_set_data->menu_lang == D_LANG_ENG)
        {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "LIST ON" : "LIST OFF"));
        }
        else
        {
                d_button_set_text( vis, ((wifi_set_data->wifi_on) ? "�б��" : "�б�ر�"));
        }
    }

    for(id = 0; id < WIFI_LIST_ROW_CNT; id++)
    {
        vis = d_frame_get_control( frm, (ID_WIFISET_LIST_BUTTON_0 + id));
        if(vis)
        {
            d_vis_set_handler( vis, atv_wifi_setting_button_handler );
            d_vis_set_solve_draw_evt(vis, D_TRUE); /* �ÿؼ������ػ��¼������Զ��ϻ���*/
        }
    }

    vis = d_frame_get_control( frm, ID_WIFISET_GROUP_LIST);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control( frm, 0);
    if(vis)
    {
        wifi_set_data->htimer = d_timer_create(NULL, 2000, d_gui_get_queue());
        if(wifi_set_data->htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, wifi_set_data->htimer);
        }
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, (D_Handle)(&atv_wifi_setting_window));
        d_vis_set_handler (vis, atv_wifi_setting_window_handler);
    }

    if(wifi_set_data->wifi_on)
    {
        if(wifi_ap_info_num == 0)
        {
            atv_wifi_setting_scan_all_wifi(1);
        }
        else
        {
            if(wifi_ap_info[0].connected != D_TRUE)
            {
                qsort(wifi_ap_info, wifi_ap_info_num, sizeof(_Wireless_AP_Info_t), compare_apinfo);
            }
            atv_wifi_setting_get_all_wifi();
        }
    }

    atv_wifi_setting_show_communicate_status(wifi_set_data->communicate_status);
    return D_OK;
}

/** @breif ��ʾwifi���ô���*/
D_Result
p_atv_wifi_setting_window_show (void) D_FUNCPOSTFIT
{
    if (D_FALSE == d_frame_is_loaded (&atv_wifi_setting_window))
    {
        close_window_flag = D_FALSE;
        d_gui_enter_menu(&atv_wifi_setting_window, D_CLEAR_ALL);
    }
    return D_OK;
}

/** @breif �ر�wifi���ô���*/
D_Result
p_atv_wifi_setting_window_close (void) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_wifi_setting_window))
    {
        close_window_flag = D_TRUE;
        d_gui_upper_menu();
    }
    return D_OK;
}

/** @breif ��ʾwifi���ô���*/
D_Result
p_atv_wlan_menu_show(void)D_FUNCPOSTFIT
{
    return p_atv_user_ok_menu_show (p_atv_wifi_setting_window_show) ;
}

/** @breif �ر�wifi���ô���*/
D_Result
p_atv_wifi_setting_window_is_close (void) D_FUNCPOSTFIT
{
    if (D_TRUE == close_window_flag)
    {
        return D_OK;
    }
    return D_ERR;
}


