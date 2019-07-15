/** @file
*@brief wifi投屏显示窗口
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
#include "ptvConfig.h"
#include "pConvCode.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pvr.h"
#include "mira.h"
#include "_helper.h"
#include "dNetwork.h"
#include "dlna_init.h"
#include "pTs2net.h"
#include "pConvCode.h"
#include "dMedia.h"
#include "dAirplay.h"

#include "atv_zhilian_tv_window.c"

#ifndef D_TV_MIRACAST_DEVNAME
#define D_TV_MIRACAST_DEVNAME "KeTing"
#endif

#ifndef D_TV_DLNA_DEVNAME
#define D_TV_DLNA_DEVNAME "hi2611dlna"
#endif

#ifndef D_TV_TS2NET_DEVNAME
#define D_TV_TS2NET_DEVNAME "hi2611ap"
#endif

#ifndef D_TV_AIRPLAY_DEVNAME
#define D_TV_AIRPLAY_DEVNAME "hi2611airplay"
#endif

#define D_ZHILIAN_CHECK_TIMEOUT   (2000)
#define USER_MSG_PARAM1_ZHILIAN_MENU_SHOW 0xf95a8901
#define USER_MSG_PARAM1_ZHILIAN_MENU_SWITCH 0xf95a8902
#define USER_MSG_PARAM1_ZHILIAN_MENU_STATUS 0xf95a8903
#define USER_MSG_PARAM1_ZHILIAN_MENU_START 0xf95a8904

typedef struct
{
    D_Char* strInstruction;
    D_Char* strInfo1;
    D_Char* strInfo2;
    D_Char* strNotice;
} D_ZhiLianInstructionInfo;

typedef struct
{
    D_ID  text_id;
    D_ID  icon_id;
    D_ID image_id;
    D_ID image_flag_id;
} D_ZhiLianFuncInfo;

static D_ZhiLianFuncInfo ZhiLianFuncInfo[] =
{
    {atv_IDS_WIFI_DISPLAY, -1, atv_IMG_ID_zhilian_main_mira_flag},
    {atv_IDS_NETWORK_SHARING, -1, atv_IMG_ID_zhilian_main_dlna_flag},
    {atv_IDS_DTV_SHAREING, -1, atv_IMG_ID_zhilian_main_tvweb_flag},
    {atv_IDS_AIRPLAY, -1, atv_IMG_ID_zhilian_main_dlna_flag},
    { -1, -1},
};

static D_ZhiLianInstructionInfo ZhiLianInstructionInfo_chn[] =
{
    {
        "使用说明",
        "请使用支持Miracast协议的手机设备",
        "1.打开手机中的同屏功能，参考如下:\n华为 : 设置->辅助功能->多屏互动或 从上下滑菜单按钮->多屏互动\n小米 : 设置->更多连接方式->无线显示\nOPPO / VIVO: 设置>更多连接方式->无线显示\n魅族/联想 : 设置->显示->投射屏幕\n三星 : 设定->Screenmirroring 或 屏幕共享设定->Screenmirroring 或 从上下滑菜单按钮-> Smart View \n \n2.找到\"%s\"并连接，连接成功后手机画面将同步显示在电视机上。",
        "注:如果连接失败或者找不到\"%s\"，可能是您的手机不支持Mirascast投屏功能。",
    },
    {
        "使用说明",
        "本机支持影音DLNA投屏功能，请参考以下步骤操作:",
        "1.请确保手机与本机连接着同一个Wi-Fi，启动手机上的影音播放器app(如 优酷、腾讯视频、爱奇艺、乐视视频芒果TV等)，视频资源播放状态下，通常点击右上角的投屏按钮或图标，找到本机设备\"%s\"并连接，成功后，此视频资源即会在本电视机上播放。",
        "注:如果连接失败或者找不到\"%s\"，可能是您的影音播放器APP不支持DLNA投屏功能。",
    },
    {
        "使用说明",
        "本机支持将数字电视频道共享到手机上进行播放，请参考以下步骤操作:",
        "1.请确保本机数字电视信号源下保存有电视或广播频道，如果没有，请先进行节目搜索。手机WiFi连接到本机的设备\"%s\"，密码:12345678，启动手机上具有此功能的app(如 VLC播放器)，找到有关本机的数字电视频道列表，点击即可在手机上免流量播放电视频道的内容。\n \n 2.如果app上找不到相应的频道列表信息，尝试重启app，也可能是此app不支持此功能。",
        "注:如果APP上找不到相应的频道列表，尝试重启APP，也可能是APP不支持此功能。\n如果连接失败或者找不到\"%s\"，可以尝试重启电视。",
    },
    {
        "使用说明",
        "Step1 : 将手机与本机连接同一个Wi-Fi.",
        "Step2 : 苹果手机打开控制中心，点击\"屏幕镜像\"，在设备列表中点击选择\"%s\"，连接成功后即可将手机屏幕投到电视屏幕上显示。",
        "",
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static D_ZhiLianInstructionInfo ZhiLianInstructionInfo_eng[] =
{
    {
        "Instructions",
        "The mobile devices with Miracast, refer to the following steps:",
        "1. Search \"Multi-screen\", \"Wireless display\", \"WLAN display\", \"Screenmirroring\", or \"Smart View\", and then run this function; \n \n2. Connect to \"%s\", then the mobile screan will display on the TV.",
        "If connect failed, or \"%s\" cannot be found, maybe the mobile not support miracast.",
    },
    {
        "Instructions",
        "This TV supports DLNA function, refer to the following steps:",
        "Make sure that the TV and mobile devices connect the same WiFi. Then run the app(Youku, Tecent Video, Igiyi and so on), play a movie and connect to \"%s\", after that the TV will play the movie.",
        "If connect failed, or \"%s\" cannot be found, maybe the app not support DLNA.",
    },
    {
        "Instructions",
        "This TV supports for sharing DTV to mobile devices, refer to the following steps:",
        "Make sure that some dtv programs stored in the TV dbase, if none, plase scan.  Then mobile devices conect the WiFi: \"%s\", password: 12345678,  after that you can watch the dtv channel with VLC app.",
        "If connect failed, or \"%s\" cannot be found, restart the TV and try again.",
    },
    {
        "Instructions",
        "Step1: Connect the phone to the same Wi-Fi.",
        "Step2: Iphone, in control center, Screen Mirriring,  select \"% s\", and click on the connection.",
        "",
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

typedef struct
{
    D_Char strWifiDevName[D_ZHILIAN_TYPE_MAX][48];  /*设备名称*/
    D_Char strLabelDevName[64];
    D_Char strInfoDetail[512];
    D_Char strInfoNotice[192];
    D_Char strLabelConnect[128];
    D_Char strCurrWifiName_utf8[36];
    D_Char strCurrWifiName[36];
    D_Char strHintOK[64];
    D_Char strConnectStatus[128];
    D_Char strUserName[64];
    D_HTimer htimer_check;
    D_U32  check_counter;
    D_Bool  dlna_open;
    D_U8    menu_lang;
    D_Char strLastWifiName_utf8[36];
    D_Bool     media_open_flag;
} D_ZhiLianTvMenuDat;


static D_U32 currRunFuncType = D_ZHILIAN_TYPE_MAX;      /*当前运行的功能*/
static D_U32 currFocusFuncType = 0;                     /*当前焦点的功能*/
static D_Bool currShowStatus = 0;                     /*当前界面是属于显示还是隐藏状态*/
static D_ZhiLianTvMenuDat *pZhiLianTvMenuDat = NULL;
static D_S32 connect_error_code = 0xFF;
static D_Bool autoStartEnable = D_FALSE;

static D_Result
atv_zhilian_get_devnames(void) D_FUNCPOSTFIT
{
    if(pZhiLianTvMenuDat)
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
                sprintf(pZhiLianTvMenuDat->strWifiDevName[idx], "%s_%04d", D_TV_MIRACAST_DEVNAME, devid);
            }
            else if(idx == D_ZHILIAN_DLNA)
            {
                sprintf(pZhiLianTvMenuDat->strWifiDevName[idx], "%s_%04d", D_TV_DLNA_DEVNAME, devid);
            }
            else if(idx == D_ZHILIAN_TS2NET)
            {
                sprintf(pZhiLianTvMenuDat->strWifiDevName[idx], "%s_%04d", D_TV_TS2NET_DEVNAME, devid);
            }
            else if(idx == D_ZHILIAN_AIRPLAY)
            {
                sprintf(pZhiLianTvMenuDat->strWifiDevName[idx], "%s_%04d", D_TV_AIRPLAY_DEVNAME, devid);
            }
        }
    }
    return D_OK;
}

static D_Result
atv_zhilian_timer_reset(D_Bool stop_or_reset) D_FUNCPOSTFIT
{
    if(pZhiLianTvMenuDat)
    {
        D_Visual *win;
        win = d_frame_get_control( &atv_zhilian_tv_window, 0);
        if(stop_or_reset == D_FALSE)
        {
            if(pZhiLianTvMenuDat->htimer_check != D_INVALID_HANDLE)
            {
                d_vis_unsubscribe_one_evt(win, D_EVT_TIMER_MASK, pZhiLianTvMenuDat->htimer_check);
                d_timer_destroy(pZhiLianTvMenuDat->htimer_check);
                pZhiLianTvMenuDat->htimer_check = D_INVALID_HANDLE;
            }
        }
        else
        {
            if(pZhiLianTvMenuDat->htimer_check == D_INVALID_HANDLE)
            {
                pZhiLianTvMenuDat->htimer_check = d_timer_create (NULL, D_ZHILIAN_CHECK_TIMEOUT, d_gui_get_queue ());
                if(pZhiLianTvMenuDat->htimer_check != D_INVALID_HANDLE)
                {
                    d_vis_subscribe_evt (win, D_EVT_TIMER_MASK, pZhiLianTvMenuDat->htimer_check);
                }
            }
            else
            {
                d_timer_reset(pZhiLianTvMenuDat->htimer_check, D_ZHILIAN_CHECK_TIMEOUT);
            }
        }
    }
    return D_OK;
}

static D_Result
atv_zhilian_window_show(D_Bool show) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_zhilian_tv_window))
    {
        D_Visual *vis;
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_GROUP);
        d_vis_show(vis, show);
        currShowStatus = show;
    }
    return D_OK;
}

static D_Result
atv_zhilian_connect_status_show(D_U32 status) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_U8  idx;

    if (pZhiLianTvMenuDat == NULL)
    {
        return D_ERR;
    }

    idx = (pZhiLianTvMenuDat->menu_lang == D_LANG_ENG) ? 0 : 1;
    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_STATUS);

#ifdef D_TV_MIRACAST_SOURCE
    if(currRunFuncType == D_ZHILIAN_MIRACAST)
    {
        D_Char *strStatus[7][2] =
        {
            {"\"%s\" , start connecting ...", "用户\"%s\"，开始连接 ..."},
            {"\"%s\" , allocate IP ...", "用户\"%s\"，正在分配IP地址 ..."},
            {"\"%s\" , allocate IP ...", "用户\"%s\"，正在分配IP地址 ..."},
            {"\"%s\" , IP ok ...", "用户\"%s\"，IP地址分配成功 ..."},
            {"\"%s\" , IP ok ...", "用户\"%s\"，IP地址分配成功 ..."},
            {"\"%s\" , connect ok !", "用户\"%s\"，连接成功!"},
            {"\"%s\" , connect failed !", "用户\"%s\"，连接失败 !"},
        };

        switch(status)
        {
            case MIRA_PHONE_STATUS_P2P_CONNECTING:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[0][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_P2P_CONNECTED:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[1][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_DHCPING:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[2][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_DHCPED:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[3][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_RTSPING:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[4][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_CONNECTED:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[5][idx], pZhiLianTvMenuDat->strUserName);
                break;
            case MIRA_PHONE_STATUS_FAIL:
                sprintf(pZhiLianTvMenuDat->strConnectStatus, strStatus[6][idx], pZhiLianTvMenuDat->strUserName);
                break;
            default:
                break;
        }

        if(status == 0xFFFF || status == MIRA_PHONE_STATUS_END)
        {
            d_vis_show(vis, D_FALSE);
        }
        else
        {
            d_label_set_text( vis, pZhiLianTvMenuDat->strConnectStatus);
            d_vis_show(vis, D_TRUE);
            d_gui_update();
        }
    }
#endif
#if (defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_AIRPLAY))
    if(currRunFuncType == D_ZHILIAN_DLNA || currRunFuncType == D_ZHILIAN_AIRPLAY)
    {
        D_Char *strDlnaStatus[1][2] =  {{"Connect ok ! Start play...", "连接成功! 准备播放..."}};

        if(status == 0xFFFF || status == 0)
        {
            d_vis_show(vis, D_FALSE);
        }
        else
        {
            sprintf(pZhiLianTvMenuDat->strConnectStatus, strDlnaStatus[0][idx]);
            d_label_set_text( vis, pZhiLianTvMenuDat->strConnectStatus);
            d_vis_show(vis, D_TRUE);
            d_gui_update();
        }
    }
#endif
    return D_OK;
}
#if 1
static D_Result
atv_zhilian_func_icon_draw(D_Visual *vis, D_U32 type) D_FUNCPOSTFIT
{
    D_U32 idx;
    D_Image *img;
    D_Rect sr, dr;
    D_Coord x = 0, x1, h, h1;

    img = d_gui_get_image(atv_IMG_ID_zhilian_main_phone_pic);
    if(img)
    {
        d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
        d_rect_set(&dr, 0, 55, img->buf.width, img->buf.height);
        d_vis_draw_image (vis, &dr, img, &sr);
    }
    img = d_gui_get_image(atv_IMG_ID_zhilian_main_wifi_pic);
    if(img)
    {
        d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
        d_rect_set(&dr, 127 , 93, img->buf.width, img->buf.height);
        d_vis_draw_image (vis, &dr, img, &sr);
    }
    img = d_gui_get_image(atv_IMG_ID_zhilian_main_tv_pic);
    if(img)
    {
        d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
        d_rect_set(&dr, 185, 0, img->buf.width, img->buf.height);
        d_vis_draw_image (vis, &dr, img, &sr);
    }
#if 0
    if(type == D_ZHILIAN_MIRACAST)
    {
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_tv_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - img->buf.width) / 2, 3, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
            x = img->buf.width;
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main__tv_progress_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 2 , 3 + 4, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_phone_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 240, 3 + 200, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_progress_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 255, 3 + 204, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_wifi_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 270, 180, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
    }
    else if(type == D_ZHILIAN_DLNA)
    {
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_tv_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - img->buf.width) / 2, 3, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
            x = img->buf.width;
            h = img->buf.height;
        }
        gui_tool_draw_fill_rect(vis, (vis->rect.w - x) / 2 + 1, 3, x - 2 , 15, 0xff000000);
        gui_tool_draw_fill_rect(vis, (vis->rect.w - x) / 2 + 1,  h - 15 - 9, x - 2, 15, 0xff000000);
        img = d_gui_get_image(atv_IMG_ID_zhilian_main__tv_progress_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 2 , 3 + 4, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_phone_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 240, 3 + 200, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
            x1 = img->buf.width;
            h1 =  img->buf.height;
        }
        gui_tool_draw_fill_rect(vis, (vis->rect.w - x) / 2 + 251, 5 + 200, x1 - 25, 8, 0xff000000);
        gui_tool_draw_fill_rect(vis, (vis->rect.w - x) / 2 + 251,  200 + h1 - 8, x1 - 25, 8, 0xff000000);
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_progress_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 255, 3 + 204, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_wifi_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 270, 180, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_phone_dlna_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 360, 187, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
    }
    else if(type == D_ZHILIAN_TS2NET)
    {
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_tv_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - img->buf.width) / 2, 3, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
            x = img->buf.width;
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_ts_tv_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 6 , 3 + 6, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_phone_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 240, 3 + 200, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_ts_phone_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 254, 3 + 269, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
        img = d_gui_get_image(atv_IMG_ID_zhilian_main_wifi_pic);
        if(img)
        {
            d_rect_set(&sr, 0, 0, img->buf.width, img->buf.height);
            d_rect_set(&dr, (vis->rect.w - x) / 2 + 252, 180, img->buf.width, img->buf.height);
            d_vis_draw_image (vis, &dr, img, &sr);
        }
    }
#endif
    return D_OK;
}

#endif
static D_Result
atv_zhilian_status_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_DRAW:
            if(vis->text)
            {
                D_Rect r;
                D_FontAttribute font;
                D_TextFormat form;
                D_Char *text = vis->text;

                d_rect_set(&r, 0, 0, vis->rect.w, vis->rect.h);
                gui_tool_draw_fill_round_rect(vis, r.x, r.y, r.w, r.h, 6,  0xff02d002);
                /* 画文字*/
                memset(&font, 0x00, sizeof(D_FontAttribute));
                memset(&form, 0x00, sizeof(D_TextFormat));
                font.fontSize = 24;
                font.fontType = D_FONT_DOT_MATRIX;
                font.fontColor = 0xff000000;//(vis_id == currRunFuncType) ? 0xff000000 : 0xffffffff;
                form.align = (D_U16)(D_ALIGN_CENTER | D_ALIGN_MIDDLE);
                form.multiple = D_FALSE;
                form.fullShow = D_TRUE;
                form.valid = D_TRUE;
                d_rect_set(&r, 0, 0, vis->rect.w, vis->rect.h);
                d_draw_text(vis, &r, text, strlen(text), &font, &form);
            }
            break;
        case D_EVT_TIMER:
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
atv_zhilian_function_open(D_U32 type)
{
    if(type == D_ZHILIAN_DLNA)
    {
#ifdef D_TV_DLNA_SOURCE
        d_dlna_open(pZhiLianTvMenuDat->strWifiDevName[currRunFuncType]);
#endif
    }
    else if(type == D_ZHILIAN_AIRPLAY)
    {
#ifdef D_TV_SUPPORT_AIRPLAY
        airplay_open(pZhiLianTvMenuDat->strWifiDevName[currRunFuncType]);
#endif
    }
    pZhiLianTvMenuDat->dlna_open = D_TRUE;
    return D_OK;
}

static D_Result
atv_zhilian_function_close(D_U32 type)
{
    pZhiLianTvMenuDat->dlna_open = D_FALSE;
    if(type == D_ZHILIAN_DLNA)
    {        
#ifdef D_TV_DLNA_SOURCE
        d_dlna_close();
#endif
    }
    else if(type == D_ZHILIAN_AIRPLAY)
    {
#ifdef D_TV_SUPPORT_AIRPLAY
        airplay_close();
#endif
    }
    
    return D_OK;
}

#ifdef D_TV_SUPPORT_AIRPLAY
static void
atv_zhilian_airplay_window_callback(D_U32 action)
{
    if (action && pZhiLianTvMenuDat && pZhiLianTvMenuDat->dlna_open)
    {
        atv_zhilian_function_close(D_ZHILIAN_AIRPLAY);
        pZhiLianTvMenuDat->dlna_open = D_FALSE;
    }        
}
#endif

static D_Result
atv_zhilian_notify_net_status(D_U32 type, D_U32 status)
{
    if(type == D_ZHILIAN_DLNA)
    {
#ifdef D_TV_DLNA_SOURCE
        p_atv_dlna_window_network_error(status);
#endif
    }
    else if(type == D_ZHILIAN_AIRPLAY)
    {
#ifdef D_TV_SUPPORT_AIRPLAY

#endif
    }
    
    return D_OK;
}

static D_Result
atv_zhilian_show_function(D_U32 type, D_U32 action) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Bool show = D_FALSE;
    D_ZhiLianInstructionInfo *ZhiLianInstructionInfo;

    ZhiLianInstructionInfo = (pZhiLianTvMenuDat->menu_lang == D_LANG_ENG) ? ZhiLianInstructionInfo_eng : ZhiLianInstructionInfo_chn;
    sprintf(pZhiLianTvMenuDat->strInfoDetail, ZhiLianInstructionInfo[type].strInfo2, pZhiLianTvMenuDat->strWifiDevName[type]);
    sprintf(pZhiLianTvMenuDat->strInfoNotice, ZhiLianInstructionInfo[type].strNotice, pZhiLianTvMenuDat->strWifiDevName[type]);
    sprintf(pZhiLianTvMenuDat->strLabelDevName, "%s %s",  d_gui_get_text(atv_IDS_DEVICE_NAME), pZhiLianTvMenuDat->strWifiDevName[type]);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
    d_label_set_text( vis, "");

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_INSTRUCTION);
    d_label_set_text( vis, d_gui_get_text(ZhiLianFuncInfo[type].text_id)); //ZhiLianInstructionInfo[type].strInstruction);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_HINTINFO_1);
    d_label_set_text( vis, ZhiLianInstructionInfo[type].strInfo1);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_HINTINFO_2);
    d_label_set_text( vis, pZhiLianTvMenuDat->strInfoDetail);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_NOTICE);
    d_label_set_text( vis, pZhiLianTvMenuDat->strInfoNotice);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_DEVICE);
    d_label_set_text( vis, pZhiLianTvMenuDat->strLabelDevName);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_HINT_OK);
    d_label_set_text( vis, d_gui_get_text(atv_IDS_OK));

    if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
    {
        sprintf(pZhiLianTvMenuDat->strHintOK, "Run %s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
    }
    else
    {
        sprintf(pZhiLianTvMenuDat->strHintOK, "启动%s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
    }
    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_OK);
    d_label_set_text( vis, pZhiLianTvMenuDat->strHintOK);

    if((currRunFuncType == D_ZHILIAN_DLNA && type == D_ZHILIAN_DLNA) || (currRunFuncType == D_ZHILIAN_AIRPLAY && type == D_ZHILIAN_AIRPLAY))
    {
        show = D_TRUE;
    }
    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_IMAGE_RED);
    d_vis_show( vis, show );

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_SET_WIFI);
    d_vis_show( vis, show );

    return D_OK;
}

static D_Result
atv_zhilian_stop_function(D_U32 type, D_U32 action) D_FUNCPOSTFIT
{
    D_Visual *vis;

    atv_zhilian_timer_reset(D_FALSE);
    p_clear_wifi_ap_record();
    if(action && pZhiLianTvMenuDat)
    {
        atv_zhilian_window_show(D_TRUE);
        atv_zhilian_connect_status_show(0xFFFF);
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
        if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
        {
            sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s , Stopping ...", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        else
        {
            sprintf(pZhiLianTvMenuDat->strLabelConnect, "正在停止%s功能，请稍候...", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
        d_gui_update();
    }

    if(type == D_ZHILIAN_MIRACAST)
    {
#ifdef D_TV_MIRACAST_SOURCE
        p_mira_close();
        d_av_set_switch_mode(D_Force_Screen);
#endif
    }
    else if(type == D_ZHILIAN_DLNA || type == D_ZHILIAN_AIRPLAY)
    {
        atv_zhilian_function_close(type);
#if 1 /* 菜单之外调用，避免频繁media与dtv的切换*/
        if(pZhiLianTvMenuDat && pZhiLianTvMenuDat->media_open_flag)
        {
            d_media_movie_close();
            d_mediacodec_close();
            pZhiLianTvMenuDat->media_open_flag = D_FALSE;
        }
        /*停止播放*/
        d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        /* 重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();
#endif 
    }
    else if(type == D_ZHILIAN_TS2NET)
    {
#ifdef D_TV_SUPPORT_TS2NET
        d_ts2net_close();
        ts2net_func_running = D_FALSE;
        p_atv_ts2net_window_hide();
#endif
    }

    if(action && pZhiLianTvMenuDat)
    {
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
        d_label_set_text( vis, "");

        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_IMAGE_RED);
        d_vis_show( vis, D_FALSE);

        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_SET_WIFI);
        d_vis_show( vis, D_FALSE);

        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_HINT_OK);
        d_label_set_text( vis, d_gui_get_text(atv_IDS_OK));
        if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
        {
            sprintf(pZhiLianTvMenuDat->strHintOK, "Run %s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        else
        {
            sprintf(pZhiLianTvMenuDat->strHintOK, "启动%s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_OK);
        d_label_set_text( vis, pZhiLianTvMenuDat->strHintOK);
    }

    currRunFuncType = D_ZHILIAN_TYPE_MAX;
    return D_OK;
}

static D_Result
atv_zhilian_run_function(D_U32 type, D_U32 action) D_FUNCPOSTFIT
{
    D_S32 idx, ret = D_OK;
    D_Bool show = D_FALSE;
    D_Visual *vis;
    D_U32 oldruntype;

    atv_zhilian_timer_reset(D_FALSE);
    oldruntype = currRunFuncType;
    currRunFuncType = type;

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);

    if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
    {
        sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s , Running ...", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
    }
    else
    {
        sprintf(pZhiLianTvMenuDat->strLabelConnect, "正在启动%s功能，请稍候...", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
    }
    d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
    d_gui_update();

    atv_zhilian_stop_function(oldruntype, 0);  /*停止之前的功能*/
    pZhiLianTvMenuDat->dlna_open = D_FALSE;
    pZhiLianTvMenuDat->check_counter = 0;

#ifdef D_TV_SUPPORT_WIFI
    /*检查一下wifi模块有效性*/
    d_wireless_open(0);
    d_task_wait(50);
    if(d_wireless_check_device("wlan0") < 0)
    {
        /*尝试卸载后重新加载*/
        D_DUMP("no wlan0 device, restart\n");
        d_wireless_close(1);
        d_wireless_open(1);
        d_task_wait(10);
        if(d_wireless_check_device("wlan0") < 0)
        {
            /*设备不存在或损坏*/
            currRunFuncType = D_ZHILIAN_TYPE_MAX;
            vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s , Run failed !Please check wifi device or restart TV", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
            }
            else
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "启动失败!本机Wi-Fi设备失联，请检查或断电重启本机!");
            }
            d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
            d_gui_update();
            return D_OK;
        }
    }
#endif

    if(type == D_ZHILIAN_MIRACAST)
    {
#ifdef D_TV_MIRACAST_SOURCE
        d_av_set_vid_input (0, D_VID_IUTPUT_DTV);
        d_av_set_switch_mode(D_Black_Screen);
        d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
        /*重设静音/声道/音量*/
        p_stb_reset_mute_track_volume();
        p_clear_wifi_ap_record();
        ret = p_mira_open(pZhiLianTvMenuDat->strWifiDevName[type]);
#endif
    }
    else if(type == D_ZHILIAN_DLNA || type == D_ZHILIAN_AIRPLAY)
    {
#if 1 /* 菜单之外调用，避免频繁media与dtv的切换*/
        if(pZhiLianTvMenuDat->media_open_flag == D_FALSE)
        {
            /* 释放epg占用资源*/
            p_auxi_free_varstring();
            d_av_set_vid_input (0, D_VID_IUTPUT_USB1);
            d_av_set_vid_blank(0, D_TRUE); /*黑屏*/
            /*重设静音/声道/音量*/
            p_stb_reset_mute_track_volume();
            d_mediacodec_open();
            d_media_movie_set_version(MOVIE_FFMPEG_VER_NEW_V34);
            d_media_movie_open() ;
            /*重设静音/声道/音量*/
            p_stb_reset_mute_track_volume();
            /*缩放模式选自动*/
            if(type == D_ZHILIAN_DLNA)
                d_av_set_tv_ratio_mode(0, D_NATURAL_RATIO);
            else
                d_av_set_tv_ratio_mode(0, D_NATURAL_RATIO_OVERALL_SCREEN);
            pZhiLianTvMenuDat->media_open_flag = D_TRUE;
        }
#endif
    
#ifdef D_TV_SUPPORT_WIFI
        d_network_init();
        d_network_test_communicate();
        connect_error_code = 0xFF;
        ret = d_wireless_start_check(&connect_error_code);
#endif
    }
    else if(type == D_ZHILIAN_TS2NET)
    {
#ifdef D_TV_SUPPORT_TS2NET
        pZhiLianTvMenuDat->check_counter = 0;
        p_clear_wifi_ap_record();
        ret = d_ts2net_open(pZhiLianTvMenuDat->strWifiDevName[type]);
        if(D_OK == ret)
        {
            ts2net_func_running = D_TRUE;
        }
#endif
    }

    currRunFuncType = type;

    if(type == D_ZHILIAN_DLNA || type == D_ZHILIAN_AIRPLAY)
    {
        if(ret < 0)
        {
            connect_error_code = 0xFF;
            vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "Please set wifi connect");
            }
            else
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "请设置Wi-Fi连接");
            }
            d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
        }
        ret = D_OK;
    }
    else if(type == D_ZHILIAN_TS2NET && ret < 0)
    {
        if(ret == D_ERR_EMPTY)
        {
            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s Run failed , \nNo dtv program in dbase, plase scan !", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
            }
            else
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s启动失败，\n数字电视无节目，请先进行节目搜索!", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
            }
        }
        else
        {
            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s Run failed, plase try again !", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
            }
            else
            {
                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s启动失败，请重新尝试!", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
            }
        }
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
        d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
        atv_zhilian_stop_function(type, 0);
        currRunFuncType = D_ZHILIAN_TYPE_MAX;
    }
    else
    {
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);

        if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
        {
            sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s Run ok, waiting for the user to connect  \"%s\"...", d_gui_get_text(ZhiLianFuncInfo[type].text_id), pZhiLianTvMenuDat->strWifiDevName[type]);
        }
        else
        {
            sprintf(pZhiLianTvMenuDat->strLabelConnect, "已启动%s，等待用户连接\"%s\"...", d_gui_get_text(ZhiLianFuncInfo[type].text_id), pZhiLianTvMenuDat->strWifiDevName[type]);
        }
        d_label_set_text( vis, pZhiLianTvMenuDat->strLabelConnect);
    }

    if(ret >= 0)
    {
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_HINT_OK);
        d_label_set_text( vis, d_gui_get_text(atv_IDS_BACK));
        if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
        {
            sprintf(pZhiLianTvMenuDat->strHintOK, "Stop %s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        else
        {
            sprintf(pZhiLianTvMenuDat->strHintOK, "停止%s", d_gui_get_text(ZhiLianFuncInfo[type].text_id));
        }
        vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_OK);
        d_label_set_text( vis, pZhiLianTvMenuDat->strHintOK);
    }

    if(currRunFuncType == D_ZHILIAN_DLNA || currRunFuncType == D_ZHILIAN_AIRPLAY)
    {
        show = D_TRUE;
    }

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_IMAGE_RED);
    d_vis_show( vis, show);

    vis = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_SET_WIFI);
    d_vis_show( vis, show);
    pZhiLianTvMenuDat->check_counter = 0;
    atv_zhilian_timer_reset(D_TRUE);
    return D_OK;
}

static D_Result
atv_zhilian_image_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_DRAW:
            atv_zhilian_func_icon_draw(vis, currFocusFuncType);
            break;
        default:
            break;

    }
    return D_OK;
}
#ifdef D_TV_SUPPORT_TS2NET
static D_Result
atv_zhilian_ts2net_back(D_U32 action) D_FUNCPOSTFIT
{
    atv_zhilian_stop_function(D_ZHILIAN_TS2NET, 0);
    currRunFuncType = D_ZHILIAN_TYPE_MAX;
    p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
    p_sys_set_input_mode(D_VID_IUTPUT_DTV, D_VID_IUTPUT_WIFIDISPLAY);
    //p_atv_zhilian_tv_window_show(2, D_FALSE);
    //p_atv_zhilian_menu_window_show(2);
    return D_OK;
}
#endif
static D_Result
atv_zhilian_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                    if(/*currShowStatus && */currRunFuncType != D_ZHILIAN_TYPE_MAX)
                    {
                        atv_zhilian_stop_function(currRunFuncType, 1);
                        p_atv_zhilian_tv_window_hide();
                        //p_atv_zhilian_menu_window_show(currFocusFuncType);
                        p_atv_zhilian_main_menu_window_show();
                    }
                    else
                    {
                        p_atv_zhilian_tv_window_hide();
                        //p_atv_zhilian_menu_window_show(currFocusFuncType);
                        p_atv_zhilian_main_menu_window_show();
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(currShowStatus && (currRunFuncType != currFocusFuncType))
                    {
                        atv_zhilian_run_function(currFocusFuncType, 1);
                    }
                    break;
                case D_KEY_RED:
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(currShowStatus && (currRunFuncType == D_ZHILIAN_DLNA || currRunFuncType == D_ZHILIAN_AIRPLAY))
                    {
#ifdef D_TV_SUPPORT_WIFI
                        p_atv_wifi_setting_window_show();
#endif
                    }
                    break;
#if 0
                case D_KEY_MIRACAST:
                    if(currShowStatus)
                    {
                        if(currRunFuncType != D_ZHILIAN_MIRACAST)
                        {
                            if(currRunFuncType != D_ZHILIAN_TYPE_MAX)
                            {
                                atv_zhilian_stop_function(currRunFuncType, 1);
                                d_gui_update();
                            }
                            currFocusFuncType =  D_ZHILIAN_MIRACAST;
                            atv_zhilian_set_focus(currFocusFuncType);
                            atv_zhilian_run_function(currFocusFuncType, 1);
                        }
                    }
                    break;
                case D_KEY_DLNA:
                    if(currShowStatus)
                    {
                        if(currRunFuncType != D_ZHILIAN_DLNA)
                        {
                            if(currRunFuncType != D_ZHILIAN_TYPE_MAX)
                            {
                                atv_zhilian_stop_function(currRunFuncType, 1);
                                d_gui_update();
                            }
                            currFocusFuncType =  D_ZHILIAN_DLNA;
                            atv_zhilian_set_focus(currFocusFuncType);
                            atv_zhilian_run_function(currFocusFuncType, 1);
                        }
                    }
                    break;
                case D_KEY_TS2NET:
                    if(currShowStatus)
                    {
                        if(currRunFuncType != D_ZHILIAN_TS2NET)
                        {
                            if(currRunFuncType != D_ZHILIAN_TYPE_MAX)
                            {
                                atv_zhilian_stop_function(currRunFuncType, 1);
                                d_gui_update();
                            }
                            currFocusFuncType =  D_ZHILIAN_TS2NET;
                            atv_zhilian_set_focus(currFocusFuncType);
                            atv_zhilian_run_function(currFocusFuncType, 1);
                        }
                    }
                    break;
#endif
                case D_KEY_HOME:
                    if(currRunFuncType == D_ZHILIAN_TYPE_MAX)
                    {
                        p_atv_zhilian_tv_window_hide();
                        return D_ERR;
                    }
                    return D_OK;
                    break;
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    return D_ERR;
                    break;
                default:
                    return D_ERR;
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(pZhiLianTvMenuDat->htimer_check == evt->timer.htimer)
            {
                pZhiLianTvMenuDat->check_counter++;
#if (defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_AIRPLAY))
                if(currRunFuncType == D_ZHILIAN_DLNA || currRunFuncType == D_ZHILIAN_AIRPLAY)
                {
                    D_Char currWifiName[36] = {0};
                    D_Char currWifiName_utf8[36] = {0};
                    D_Visual *vis_label;
                    D_Bool  set_flag = D_FALSE;
                    
                    vis_label = d_frame_get_control( &atv_zhilian_tv_window, ID_ZHILIANTV_LABEL_CONNECT);
                    
                    if(d_network_get_connect_status())
                    {
                        _net_cur_info_t curinfo = {0};
                        connect_error_code = 0xEE;
                        if(D_OK != d_network_get_curr_info("wlan0", &curinfo))
                        {
                            atv_zhilian_notify_net_status(currRunFuncType, 1);
                        }
                        else
                        {
                            atv_zhilian_notify_net_status(currRunFuncType, 0);
                        }
                        
                        //d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
                        strcpy(currWifiName_utf8, curinfo.name);
                        currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                        if(strcmp(pZhiLianTvMenuDat->strCurrWifiName_utf8, currWifiName_utf8) != 0)
                        {
                            set_flag = D_TRUE;
                            strncpy(pZhiLianTvMenuDat->strCurrWifiName_utf8, currWifiName_utf8, sizeof(pZhiLianTvMenuDat->strCurrWifiName_utf8));
                            strncpy(pZhiLianTvMenuDat->strLastWifiName_utf8, currWifiName_utf8, sizeof(pZhiLianTvMenuDat->strLastWifiName_utf8));
                            p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
                            strncpy(pZhiLianTvMenuDat->strCurrWifiName, currWifiName, sizeof(pZhiLianTvMenuDat->strCurrWifiName));
                            pZhiLianTvMenuDat->strCurrWifiName[sizeof(pZhiLianTvMenuDat->strCurrWifiName) - 1] = '\0';
                            /* 切换了wifi后，要重新启动dlna*/
                            if(pZhiLianTvMenuDat->dlna_open)
                            {
                                atv_zhilian_function_close(currRunFuncType);
                                pZhiLianTvMenuDat->dlna_open = D_FALSE;
                            }
                        }

                        if(pZhiLianTvMenuDat->dlna_open == D_FALSE)
                        {
                            Roc_IP_Config_t ipinfo;

                            /*有了网关即可启动dlna*/
                            memset(&ipinfo, 0, sizeof(ipinfo));
                            if(curinfo.connected && (0 == d_network_get_ip_gateway("wlan0", &ipinfo)) && (0 < strlen(ipinfo.gateway)))
                            {
                                set_flag = D_TRUE;
                                pZhiLianTvMenuDat->dlna_open = D_TRUE;
                                atv_zhilian_function_open(currRunFuncType);
                            }
                        }

                        if( pZhiLianTvMenuDat->dlna_open && set_flag)
                        {
                            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "%s Run ok, have connect Wi-Fi: %s, \nwaiting for the user to connect  \"%s\"...", d_gui_get_text(ZhiLianFuncInfo[currRunFuncType].text_id), pZhiLianTvMenuDat->strCurrWifiName, pZhiLianTvMenuDat->strWifiDevName[currRunFuncType]);
                            }
                            else
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "已启动%s，已连接Wi-Fi:  %s，\n等待用户投屏连接\"%s\"...", d_gui_get_text(ZhiLianFuncInfo[currRunFuncType].text_id), pZhiLianTvMenuDat->strCurrWifiName, pZhiLianTvMenuDat->strWifiDevName[currRunFuncType]);
                            }
                            d_label_set_text( vis_label, pZhiLianTvMenuDat->strLabelConnect);
                        }
                        else if( pZhiLianTvMenuDat->dlna_open== D_FALSE && set_flag)
                        {
                            d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
                            currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                            p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
                            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "Wi-Fi: %s, Network error, Please check !", currWifiName);
                            }
                            else
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "Wi-Fi:  %s，网络已断开，请检查!", currWifiName);
                            }
                            d_label_set_text( vis_label, pZhiLianTvMenuDat->strLabelConnect);
                        }
                    }
                    else
                    {
                        if(connect_error_code >= 0 && connect_error_code != 0xFF && D_FALSE == d_wireless_is_connecting())
                        {
                            d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
                            currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                            if(strcmp(pZhiLianTvMenuDat->strLastWifiName_utf8, currWifiName_utf8) != 0)
                            {
                                set_flag = D_TRUE;
                                pZhiLianTvMenuDat->strCurrWifiName_utf8[0] = '\0';
                                strncpy(pZhiLianTvMenuDat->strLastWifiName_utf8, currWifiName_utf8, sizeof(pZhiLianTvMenuDat->strLastWifiName_utf8));
                            }
                            connect_error_code = 0xEE;
                        }

                        if(connect_error_code < 0 || set_flag)
                        {
                            connect_error_code = 0xEE;
                            d_wireless_get_curr_wifi("wlan0", currWifiName_utf8, NULL);
                            currWifiName_utf8[sizeof(currWifiName_utf8) - 1] = '\0';
                            p_cc_utf8_to_sys(currWifiName, sizeof(currWifiName), currWifiName_utf8, strlen(currWifiName_utf8));
                            if(pZhiLianTvMenuDat->menu_lang == D_LANG_ENG)
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "Wi-Fi: %s, connect failed, please check !", currWifiName);
                            }
                            else
                            {
                                sprintf(pZhiLianTvMenuDat->strLabelConnect, "Wi-Fi:  %s，连接失败，请检查!", currWifiName);
                            }
                            d_label_set_text( vis_label, pZhiLianTvMenuDat->strLabelConnect);
                        }

                        if(pZhiLianTvMenuDat->dlna_open)
                        {
                            atv_zhilian_function_close(currRunFuncType);
                            pZhiLianTvMenuDat->dlna_open = D_FALSE;
                        }
                    }
                }
#endif
#ifdef D_TV_SUPPORT_TS2NET
                if(currRunFuncType == D_ZHILIAN_TS2NET && pZhiLianTvMenuDat->check_counter > 1)
                {
                    p_atv_zhilian_tv_window_hide();
                    p_conf_set_vid_input(D_VID_IUTPUT_DTV);
                    p_sys_set_input_mode(D_VID_IUTPUT_WIFIDISPLAY, D_VID_IUTPUT_DTV);
                    p_atv_ts2net_window_show(380, 16, atv_zhilian_ts2net_back);
                }
#endif
            }
            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_ZHILIAN_MENU_START)
            {
                if(currShowStatus && (currRunFuncType != currFocusFuncType))
                {
                    atv_zhilian_run_function(currFocusFuncType, 1);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_ZHILIAN_MENU_SHOW)
            {
                atv_zhilian_window_show((D_Bool)evt->user.param2);
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_ZHILIAN_MENU_SWITCH)
            {
                currFocusFuncType = evt->user.param2;
                atv_zhilian_run_function(currFocusFuncType, 1);
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_ZHILIAN_MENU_STATUS)
            {
#ifdef D_TV_MIRACAST_SOURCE
                atv_zhilian_connect_status_show((D_U32)evt->user.param2);
                if(evt->user.param2 == MIRA_PHONE_STATUS_FAIL)
                {
                    d_task_wait(100);
                    atv_zhilian_connect_status_show(0xFFFF);
                }
#endif
            }
            break;
        case D_EVT_USER1:
            if(evt->user.param1 == USER_MSG_PARAM1_DLNA_CONNECT)
            {
#if (defined(D_TV_DLNA_SOURCE))
                atv_zhilian_connect_status_show(1);
                atv_zhilian_window_show(D_FALSE);
                atv_zhilian_connect_status_show(0xFFFF);
                p_atv_dlna_window_show((D_Char *)evt->user.param2, (D_Char *)evt->user.param3, p_conf_get_vid_input());
#endif
            }
#ifdef D_TV_SUPPORT_AIRPLAY            
            if(evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_MOVIE_PLAY)
            {
                if(D_TRUE != p_atv_airplay_window_is_show())
                {
                    atv_zhilian_connect_status_show(1);
                    atv_zhilian_window_show(D_FALSE);
                    atv_zhilian_connect_status_show(0xFFFF);
                    p_atv_airplay_window_show((D_Char *)evt->user.param2, 2, atv_zhilian_airplay_window_callback);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_AIRPLAY_STATUS)
            {
                if(D_TRUE != p_atv_airplay_window_is_show())
                {
                    D_U32 status = evt->user.param2;
                    if(status == D_AIRPLAY_STATUS_START)
                    {
                        atv_zhilian_connect_status_show(1);
                        atv_zhilian_window_show(D_FALSE);
                        atv_zhilian_connect_status_show(0xFFFF);
                        p_atv_airplay_window_show(NULL, evt->user.param3, atv_zhilian_airplay_window_callback);
                    }
                    else if(status == D_AIRPLAY_STATUS_STOP)
                    {
                        //p_atv_airplay_window_hide();
                    }
                }
            }
#endif            
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(currRunFuncType != D_ZHILIAN_TS2NET)
            {
                atv_zhilian_stop_function(currRunFuncType, 0);
            }            
            if(pZhiLianTvMenuDat)
            {
                if(pZhiLianTvMenuDat->htimer_check != D_INVALID_HANDLE)
                {
                    d_timer_destroy(pZhiLianTvMenuDat->htimer_check);
                    pZhiLianTvMenuDat->htimer_check = D_INVALID_HANDLE;
                }
                PROJECT_FREE(pZhiLianTvMenuDat);
                pZhiLianTvMenuDat = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

D_Result
atv_zhilian_tv_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Image *img = NULL;

    if(currRunFuncType != D_ZHILIAN_TYPE_MAX)
    {
        atv_zhilian_stop_function(currRunFuncType, 0);
    }
    currRunFuncType = D_ZHILIAN_TYPE_MAX;
    currShowStatus = D_TRUE;
    pZhiLianTvMenuDat = (D_ZhiLianTvMenuDat*)PROJECT_ALLOC(sizeof(D_ZhiLianTvMenuDat));
    memset(pZhiLianTvMenuDat, 0x00, sizeof(D_ZhiLianTvMenuDat));
    pZhiLianTvMenuDat->htimer_check = D_INVALID_HANDLE;
    pZhiLianTvMenuDat->menu_lang = p_conf_get_lang();
    atv_zhilian_get_devnames();

    /*挂起DVB播放和SI监控*/
    d_stb_stop_play();

    /* group里不再响应按键，即要在window里处理左右切换焦点*/
    vis = d_frame_get_control( frm, ID_ZHILIANTV_GROUP);
    if(vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
    }

    vis = d_frame_get_control( frm, ID_ZHILIANTV_IMAGE_ICON);
    if(vis)
    {
        d_vis_set_solve_draw_evt(vis, D_TRUE);
        d_vis_unsubscribe_one_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_zhilian_image_handler);
    }

    vis = d_frame_get_control( frm, ID_ZHILIANTV_LABEL_STATUS);
    if(vis)
    {
        d_vis_set_solve_draw_evt(vis, D_TRUE);
        d_vis_set_handler (vis, atv_zhilian_status_handler);
    }

    vis = d_frame_get_control( frm, ID_ZHILIAN_LABEL_FLAG);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text(ZhiLianFuncInfo[currFocusFuncType].text_id));
    }

    vis = d_frame_get_control( frm, ID_ZHILIAN_IMAHE_FLAG);
    if(vis)
    {
        img = d_gui_get_image(ZhiLianFuncInfo[currFocusFuncType].image_id);
        d_image_box_set_image(vis, img);
    }

    vis = d_frame_get_control( frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_zhilian_window_handler);
    }

    atv_zhilian_connect_status_show(0xFFFF);
    atv_zhilian_show_function(currFocusFuncType, 0);

    if(autoStartEnable)
    {
        D_UserMsg msg;

        autoStartEnable = D_FALSE;
        msg.type = D_MSG_USER;
        msg.handle = (D_Handle)(&atv_zhilian_tv_window);
        msg.param1 = USER_MSG_PARAM1_ZHILIAN_MENU_START;
        msg.param2 = (D_U32)0;
        msg.param3 = (D_U32)0;
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    }

    return D_OK;
}

/** @breif 隐藏或重新显示窗口，但不释放窗口*/
D_Result
p_atv_zhilian_tv_window_show_enable (D_Bool show) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_zhilian_tv_window))
    {
        D_UserMsg msg;
        msg.type = D_MSG_USER;
        msg.handle = (D_Handle)(&atv_zhilian_tv_window);
        msg.param1 = USER_MSG_PARAM1_ZHILIAN_MENU_SHOW;
        msg.param2 = (D_U32)show;
        msg.param3 = (D_U32)0;
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
        currShowStatus = show;
    }
    return D_OK;
}

/** @breif 通知界面显示连接状态*/
D_Result
p_atv_zhilian_tv_window_show_status (D_U32 status, D_Char *name) D_FUNCPOSTFIT
{
    if (pZhiLianTvMenuDat && (D_TRUE == d_frame_is_loaded (&atv_zhilian_tv_window)))
    {
        D_UserMsg msg;

        /* 分配内存存储内容*/
        if(name)
        {
            //snprintf(pZhiLianTvMenuDat->strUserName, sizeof(pZhiLianTvMenuDat->strUserName), "%s", name);
            p_cc_utf8_to_sys(pZhiLianTvMenuDat->strUserName, sizeof(pZhiLianTvMenuDat->strUserName), name, strlen(name));
            pZhiLianTvMenuDat->strUserName[sizeof(pZhiLianTvMenuDat->strUserName) - 1] = '\0';
        }

        msg.type = D_MSG_USER;
        msg.handle = (D_Handle)(&atv_zhilian_tv_window);
        msg.param1 = USER_MSG_PARAM1_ZHILIAN_MENU_STATUS;
        msg.param2 = (D_U32)status;
        msg.param3 = (D_U32)0;
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));

    }
    return D_OK;
}

/** @breif 显示窗口*/
D_Result
p_atv_zhilian_tv_window_show (D_U32 type, D_Bool auto_start) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;
    D_VidInput      input;

    if (D_FALSE == d_frame_is_loaded (&atv_zhilian_tv_window))
    {
        currFocusFuncType = type;
        autoStartEnable = auto_start;
        input = p_conf_get_vid_input();
        p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
        p_sys_set_input_mode(input, D_VID_IUTPUT_WIFIDISPLAY);

        ret = d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_zhilian_tv_window, D_CLEAR_ALL);
    }
    return ret;
}

/** @breif 隐藏窗口*/
D_Result
p_atv_zhilian_tv_window_hide (void) D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_zhilian_tv_window))
    {
        d_gui_clear_menu_ext (ATV_MEDIA_MENU_ID); //d_gui_upper_menu_ext (ATV_MEDIA_MENU_ID);
    }
    return D_OK;
}

/** @breif 显示窗口*/
D_Result
p_atv_zhilian_tv_window_show_shortcut (D_U32 type) D_FUNCPOSTFIT
{
    if (D_FALSE == d_frame_is_loaded (&atv_zhilian_tv_window))
    {
        D_UserMsg msg;
        D_VidInput input;
        currFocusFuncType = type;
        input = p_conf_get_vid_input ();
        p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
        p_sys_set_input_mode(input, D_VID_IUTPUT_WIFIDISPLAY);
        d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_zhilian_tv_window, D_CLEAR_ALL);
        msg.type = D_MSG_USER;
        msg.handle = (D_Handle)(&atv_zhilian_tv_window);
        msg.param1 = USER_MSG_PARAM1_ZHILIAN_MENU_SWITCH;
        msg.param2 = (D_U32)type;
        msg.param3 = (D_U32)0;
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    }
    return D_OK;
}


