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

#include "zhilian_menu_window.c"

typedef struct
{
    D_Char strWifiDevName[D_ZHILIAN_TYPE_MAX][48];  /*设备名称*/
    D_Char strInfoDetail[512];
    D_Char strInfoNotice[192];
    D_Visual *cur_focse_vis;
    D_Visual  *mira_vis, *tvweb_vis, *dlna_vis , *inof_vis, *inof1_vis, *inof2_vis, *inof3_vis;
    D_U32       focus;
    D_U8        gui_lang;
} D_ZhilianMenuData;



typedef struct
{
    D_Char* strInfo1;
    D_Char* strInfo2;
    D_Char* strInfo3;
} D_ZhiLianInfo;

static D_ZhilianMenuData *zhilianmenu_data = NULL;
static D_ID str_info1[] = {atv_IDS_WIFI_DISPLAY, atv_IDS_NETWORK_SHARING, atv_IDS_DTV_SHAREING};
static D_U8 Curtype = 0;


static D_ZhiLianInfo ZhiLianInfo_chn[] =
{
    {
        "请使用支持Miracast协议的手机设备",
        "1.打开手机中的同屏功能，参考如下:\n华为 : 设置->辅助功能->多屏互动或 从上下滑菜单按钮->多屏互动\n小米 : 设置->更多连接方式->无线显示\nOPPO / VIVO: 设置>更多连接方式->无线显示\n魅族/联想 : 设置->显示->投射屏幕\n三星 : 设定->Screenmirroring 或 屏幕共享设定->Screenmirroring 或 从上下滑菜单按钮-> Smart View \n \n2.找到\"%s\"并连接，连接成功后手机画面将同步显示在电视机上。",
        "注:如果连接失败或者找不到\"%s\"，可能是您的手机不支持Mirascast投屏功能。",
    },
    {
        "本机支持影音DLNA投屏功能，请参考以下步骤操作:",
        "1.请确保手机与本机连接着同一个WiFi，启动手机上的影音播放器app(如 优酷、腾讯视频、爱奇艺、乐视视频芒果TV等)，视频资源播放状态下，通常点击右上角的投屏按钮或图标，找到本机设备\"%s\"并连接，成功后，此视频资源即会在本电视机上播放。",
        "注:如果连接失败或者找不到\"%s\"，可能是您的影音播放器APP不支持DLNA投屏功能。",
    },
    {
        "本机支持将数字电视频道共享到手机上进行播放，请参考以下步骤操作:",
        "1.请确保本机数字电视信号源下保存有电视或广播频道，如果没有，请先进行节目搜索。手机WiFi连接到本机的设备\"%s\"，密码:12345678，启动手机上具有此功能的app(如 VLC播放器)，找到有关本机的数字电视频道列表，点击即可在手机上免流量播放电视频道的内容。\n \n 2.如果app上找不到相应的频道列表信息，尝试重启app，也可能是此app不支持此功能。",
        "注:如果APP上找不到相应的频道列表，尝试重启APP，也可能是APP不支持此功能。\n如果连接失败或者找不到\"%s\"，可以尝试重启电视。",
    },
    {
        NULL,
        NULL,
        NULL,
    },
};

static D_ZhiLianInfo ZhiLianInfo_eng[] =
{
    {
        "The mobile devices with Miracast, refer to the following steps:",
        "1. Search \"Multi-screen\", \"Wireless display\", \"WLAN display\", \"Screenmirroring\", or \"Smart View\", and then run this function; \n \n2. Connect to \"%s\", then the mobile screan will display on the TV.",
        "If connect failed, or \"%s\" cannot be found, maybe the mobile not support miracast.",
    },
    {
        "This TV supports DLNA function, refer to the following steps:",
        "Make sure that the TV and mobile devices connect the same WiFi. Then run the app(Youku, Tecent Video, Igiyi and so on), play a movie and connect to \"%s\", after that the TV will play the movie.",
        "If connect failed, or \"%s\" cannot be found, maybe the app not support DLNA.",
    },
    {
        "This TV supports for sharing DTV to mobile devices, refer to the following steps:",
        "Make sure that some dtv programs stored in the TV dbase, if none, plase scan.  Then mobile devices conect the WiFi: \"%s\", password: 12345678,  after that you can watch the dtv channel with VLC app.",
        "If connect failed, or \"%s\" cannot be found, restart the TV and try again.",
    },
    {
        NULL,
        NULL,
        NULL,
    },
};


static D_Result
atv_zhilian_menu_get_devnames(void) D_FUNCPOSTFIT
{
    if(zhilianmenu_data)
    {
        D_U32 idx, devid;

        devid = p_tvconf_get_device_id();
        devid = (devid % 10000);
        if(devid == 0)
        {
            /*暂时取随机数，后续可使用生产序列号或chipid*/
            while(devid == 0)
            {
                srand(d_sys_get_time());
                devid = (rand() % 10000);
            }
            p_tvconf_set_device_id(devid);
        }

        for(idx = 0; idx < D_ZHILIAN_TYPE_MAX; idx++)
        {
            if(idx == D_ZHILIAN_MIRACAST)
            {
                sprintf(zhilianmenu_data->strWifiDevName[idx], "%s_%04d", D_TV_MIRACAST_DEVNAME, devid);
            }
            else if(idx == D_ZHILIAN_DLNA)
            {
                sprintf(zhilianmenu_data->strWifiDevName[idx], "%s_%04d", D_TV_DLNA_DEVNAME, devid);
            }
            else if(idx == D_ZHILIAN_TS2NET)
            {
                sprintf(zhilianmenu_data->strWifiDevName[idx], "%s_%04d", D_TV_TS2NET_DEVNAME, devid);
            }
        }
    }
    return D_OK;
}



static D_Result
atv_zhilian_menu_window_ok_action(void) D_FUNCPOSTFIT
{
    D_VidInput      input;
    input = p_conf_get_vid_input ();

    if((zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->tvweb_vis))
    {
        p_atv_zhilian_menu_window_hide();
        p_atv_zhilian_tv_window_show(2, D_TRUE);
    }
    else if((zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->mira_vis))
    {
        p_atv_zhilian_menu_window_hide();
        p_atv_zhilian_tv_window_show(0, D_TRUE);
    }
    else if((zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->dlna_vis))
    {
        p_atv_zhilian_menu_window_hide();
        p_atv_zhilian_tv_window_show(1, D_TRUE);
    }
    return D_OK;
}

static D_Result
atv_zhilian_menu_info_show(D_U32 type)
{
    D_ZhiLianInfo *ZhiLianInfo_text;

    ZhiLianInfo_text = (zhilianmenu_data->gui_lang == D_LANG_ENG) ? ZhiLianInfo_eng : ZhiLianInfo_chn;
    sprintf(zhilianmenu_data->strInfoDetail, ZhiLianInfo_text[type].strInfo2, zhilianmenu_data->strWifiDevName[type]);
    sprintf(zhilianmenu_data->strInfoNotice, ZhiLianInfo_text[type].strInfo3, zhilianmenu_data->strWifiDevName[type]);
    d_label_set_text(zhilianmenu_data->inof_vis, d_gui_get_text(str_info1[type]));
    d_label_set_text(zhilianmenu_data->inof1_vis, ZhiLianInfo_text[type].strInfo1);
    d_label_set_text(zhilianmenu_data->inof2_vis, zhilianmenu_data->strInfoDetail);
    d_label_set_text(zhilianmenu_data->inof3_vis, zhilianmenu_data->strInfoNotice);
    return D_OK;
}


static D_Result
atv_zhilian_menu_window_focus_deal(D_FPKey key) D_FUNCPOSTFIT
{
    D_Frame *frm = &zhilian_menu_window;
    D_U8 type = 0xFF;

    switch (key)
    {
        case D_KEY_LEFT:
        case D_KEY_L:
            #if 0 
            if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmenu_data->tvweb_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->tvweb_vis;
                type = 2;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->mira_vis)
            {
                d_vis_set_focus(zhilianmenu_data->dlna_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->dlna_vis;
                type = 1;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->tvweb_vis)
            {
                d_vis_set_focus(zhilianmenu_data->mira_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->mira_vis;
                type = 0;
            }
            #else
            if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmenu_data->mira_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->mira_vis;
                type = 0;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->mira_vis)
            {
                d_vis_set_focus(zhilianmenu_data->dlna_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->dlna_vis;
                type = 1;
            }
            #endif
            break;
        case D_KEY_RIGHT:
        case D_KEY_R:
            #if 0
            if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmenu_data->mira_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->mira_vis;
                type = 0;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->mira_vis)
            {
                d_vis_set_focus(zhilianmenu_data->tvweb_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->tvweb_vis;
                type = 2;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->tvweb_vis)
            {
                d_vis_set_focus(zhilianmenu_data->dlna_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->dlna_vis;
                type = 1;
            }
            #else
            if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->dlna_vis)
            {
                d_vis_set_focus(zhilianmenu_data->mira_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->mira_vis;
                type = 0;
            }
            else if(zhilianmenu_data->cur_focse_vis ==  zhilianmenu_data->mira_vis)
            {
                d_vis_set_focus(zhilianmenu_data->dlna_vis);
                zhilianmenu_data->cur_focse_vis = zhilianmenu_data->dlna_vis;
                type = 1;
            }
            #endif 
            break;
        default:
            break;
    }

    if(type != 0xFF)
    {
        Curtype = type;
        atv_zhilian_menu_info_show(type);
    }

    return D_OK;
}

static D_Result
atv_zhilian_menu_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &zhilian_menu_window;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    return D_ERR;
                    break;
                case D_KEY_ESC:
                case D_KEY_BACK:
                    p_atv_zhilian_menu_window_hide();
                    p_atv_zhilian_main_menu_window_show();
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    atv_zhilian_menu_window_ok_action();
                    break;
                case D_KEY_R:
                case D_KEY_RIGHT:
                case D_KEY_LEFT:
                case D_KEY_L:
                    atv_zhilian_menu_window_focus_deal(evt->fp.key);
                    break;
                case D_KEY_HOME:
                {
                    p_atv_zhilian_menu_window_hide();
                    return D_ERR;
                }
                break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_TIMER:

            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
zhilian_menu_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID  vis_num;

    zhilianmenu_data = (D_ZhilianMenuData*)PROJECT_ALLOC(sizeof(D_ZhilianMenuData));
    if(!zhilianmenu_data)
    {
        return D_ERR;
    }
    memset(zhilianmenu_data, 0, sizeof(D_ZhilianMenuData));

    zhilianmenu_data->dlna_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_BUTTON_DLNA);
    zhilianmenu_data->mira_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_BUTTON_MIRA);
    zhilianmenu_data->tvweb_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_BUTTON_TSNET);
    zhilianmenu_data->inof_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_LABEL_TITLE);
    zhilianmenu_data->inof1_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_LABEL_INFO1);
    zhilianmenu_data->inof2_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_LABEL_INFO2);
    zhilianmenu_data->inof3_vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_LABEL_INFO3);
    zhilianmenu_data->gui_lang = p_conf_get_lang();

    atv_zhilian_menu_get_devnames();

    vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_GROUP);
    if(vis)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK | D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }
    if(Curtype == 0)
    {
        vis_num = ID_ZHILIAN_MENU_BUTTON_MIRA;
    }
    else if(Curtype == 1)
    {
        vis_num = ID_ZHILIAN_MENU_BUTTON_DLNA;
    }
    else
    {
        vis_num = ID_ZHILIAN_MENU_BUTTON_TSNET;
    }

    atv_zhilian_menu_info_show(Curtype);

    vis = d_frame_get_control(frm, vis_num);
    if(vis)
    {
        zhilianmenu_data->cur_focse_vis = vis;
        d_vis_set_focus(vis);
    }

    vis = d_frame_get_control(frm, ID_ZHILIAN_MENU_LABEL_OK);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_CHOICE));
    }
    d_vis_show(zhilianmenu_data->tvweb_vis,D_FALSE);
    d_vis_enable(zhilianmenu_data->tvweb_vis,D_TRUE);
    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, atv_zhilian_menu_window_handler);
    }
    return D_OK;
}

/** @brief  电视机安卓主菜单open*/
D_Result
p_atv_zhilian_menu_window_show (D_U32 type) D_FUNCPOSTFIT
{
    if (! d_frame_is_loaded (&zhilian_menu_window))
    {
        Curtype = (type < 3) ? type : Curtype;
        return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &zhilian_menu_window, D_CLEAR_ALL);
        //return d_gui_open_frame(&zhilian_menu_window, D_GUI_LAYER_USER_0);
    }
    return D_OK;
}

/** @brief  电视机安卓主菜单close*/
D_Result
p_atv_zhilian_menu_window_hide (void) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&zhilian_menu_window))
    {
        return d_gui_clear_menu_ext (ATV_MEDIA_MENU_ID); //d_gui_upper_menu_ext (ATV_MEDIA_MENU_ID);
        //return d_gui_close_frame(&zhilian_menu_window);
    }
    return D_OK;
}

