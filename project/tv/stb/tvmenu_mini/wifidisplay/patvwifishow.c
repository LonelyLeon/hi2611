/** @file
*@brief wifiͶ����ʾ����
*@date
*/

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
#include "atv_wifi_show_window.c"
#include "pvr.h"
#include "mira.h"
#include "_helper.h"
#include "pTs2net.h"

static D_Char strWifiDevName[32] = {0};
extern void p_clear_wifi_ap_record(void);

static D_Result
atv_wifi_show_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:

                    break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                case D_KEY_SOURCE:

                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_WIFIDISPLAY_MENU)
            {
                d_vis_show (vis, (D_Bool)evt->user.param2);
            }
            break;
        case D_EVT_TIMER:

            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            p_mira_close();
            ts2net_check_enable = D_TRUE;
            d_av_set_vid_blank(0, D_TRUE); /*����*/
            d_av_set_switch_mode(D_Force_Screen);
            break;
        default:
            break;
    }

    return D_ERR;

}
D_Result
atv_wifi_show_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    p_clear_wifi_ap_record();

    if(strWifiDevName[0] == (D_Char)0)
    {
        snprintf(strWifiDevName, sizeof(strWifiDevName), "KeTing_haier");
    }

    /*����DVB���ź�SI���*/
    d_stb_stop_play();
    d_av_set_vid_input (0, D_VID_IUTPUT_DTV);
    d_av_set_switch_mode(D_Black_Screen);
    d_av_set_vid_blank(0, D_TRUE); /*����*/
    /*���農��/����/����*/
    p_stb_reset_mute_track_volume();

    vis = d_frame_get_control( frm, ID_WIFISHOW_LABEL);
    if(vis)
    {
        d_label_set_text( vis, d_gui_get_text(atv_IDS_WIFI_DISPLAY));
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_CONNECT);
    if(vis)
    {
        d_label_set_text( vis, "�ȴ�����...");
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_INFO);
    if(vis)
    {
        d_label_set_text( vis, d_gui_get_text(atv_IDS_DEVICE_NAME));
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_INFO2);
    if(vis)
    {
        d_label_set_text( vis, strWifiDevName);
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_BUTTON);
    if(vis)
    {
        d_button_set_text( vis, d_gui_get_text(atv_IDS_WIFI_SETTING));
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_INSTRUCTION);
    if(vis)
    {
        d_label_set_text( vis, "ʹ��˵��");
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_HINTINFO);
    if(vis)
    {
        d_label_set_text( vis, "��������Miracast��׼���豸,�밴�����²������:");
    }
    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_2);
    if(vis)
    {
        d_label_set_text( vis, " �����ֻ���������ʾ����\nһ�����ֻ� \"���� \"������,�����Ϊ \"�������� \", \"������ʾ \", \"WALNֱ�� \"�� \"Screen Mirroring \"��ѡ��������ֻ���������ʾ����\n        \n���ֻ����ҵ�����,������.��ʱ,�ֻ����潫ͬ����ʾ�ڵ��ӻ���");
    }

    vis = d_frame_get_control( frm, ID_WIFISHOW_LABLE_NOTICE);
    if(vis)
    {
        d_label_set_text( vis, "�������ʧ�ܻ����Ҳ�������,�����������ֻ���֧��Mirascast����.");
    }
    vis = d_frame_get_control( frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK , D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK , (D_Handle)(&atv_wifi_show_window));
        d_vis_set_handler (vis, atv_wifi_show_window_handler);
    }

#ifdef D_TV_SUPPORT_TS2NET
    ts2net_check_enable = D_FALSE;
    d_ts2net_close();
#endif

    p_mira_open(strWifiDevName);
    return D_OK;
}

/** @breif ��ʾ����*/
D_Result
p_atv_wifi_window_show (void) D_FUNCPOSTFIT
{
    if (D_FALSE == d_frame_is_loaded (&atv_wifi_show_window))
    {
        d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_wifi_show_window, D_CLEAR_ALL);
    }
    return D_OK;
}

/** @breif ���ش���*/
D_Result
p_atv_wifi_window_hide (D_Bool show) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_wifi_show_window))
    {
        D_UserMsg msg;
        msg.type = D_MSG_USER;
        msg.handle = (D_Handle)(&atv_wifi_show_window);
        msg.param1 = USER_MSG_PARAM1_WIFIDISPLAY_MENU;
        msg.param2 = (D_U32)show;
        msg.param3 = (D_U32)0;
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    }
    return D_OK;
}

