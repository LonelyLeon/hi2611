/** @file
* @brief 播放器窗口模块
* @author 龚克
* @date 2005-9-16 龚克: 建立文件
* @date 2006-5-19 刘勋: 修改文件（加入LOADER升级窗口）
* @date 2006-8-17 刘勋: 武汉项目增加功能
*        (频道列表更新/自动开关机)
*/


#include <stdio.h>
#include <string.h>

#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "dScan.h"
#include "dFMan.h"
#include "dTime.h"
#include "dDate.h"
#include "pStb.h"
#include "pPlayer.h"
#include "pStbAtvMenus.h"
#include "pStbCaMenus.h"
#include "dCA.h"
#include "pMonitorRegister.h"
#include "pSIParse.h"
#include "atv_player_window.c"
#include "pUmt.h"
#include "pFp.h"
#include "dadporting.h"
#include "patvGuiResource.h"
#include "pStbFunctions.h"
#include "pDBaseDefault.h"

#define USB_INSERT  1
#define USB_DISCNNT 0

/** @brief pvr录像status*/
#define PLAYER_IS_PVR_STATUS(_p)((_p)->playflags & D_PLAYER_FLAGS_PVR)

/** @brief USB设备是否插入*/
static int   usb_insert = 0;

/** @brief 当前播放器ID*/
static D_ID     curr_player_id = 0;

/** @brief 每隔一段时间检查一次预订节目*/
#define D_SUB_EVT_CHECK_TIME    (15000)

/** @brief 预订节目到时提示消息超时*/
#define D_SUB_EVT_MSG_TIMEOUT   (15000)

/** @brief 判断stb 是否处于播放状态*/
#define STB_STATUS_PLAYING()    (g_stb->status == D_STB_ST_PLAYING)

/** @brief 判断stb 是否处于菜单状态*/
#define STB_STATUS_MENU()   (g_stb->status == D_STB_ST_MENU)

/** @brief 判断stb 是否处于待机状态*/
#define STB_STATUS_STANDBY()    (g_stb->status == D_STB_ST_STANDBY)



/** @brief 判断是否能够进行频道切换*/
#define PLAYER_CAN_CHANNEL_CHANGE(_p) (input == D_VID_IUTPUT_DTV || input == D_VID_IUTPUT_TV)

/** @brief 预订节目检查定时器 */
static D_HTimer subscribe_check_htimer = D_INVALID_HANDLE;

/*信号是否中断*/
static D_Bool signal_is_not_good = D_FALSE;
/*是否允许显示信号中断消息*/
static D_Bool signal_faint_msg_show_enable = D_TRUE;
/*是否已经显示信号中断消息*/
static D_Bool signal_faint_msg_showing = D_FALSE;

/*是否已显示无节目信息*/
static D_U8 show_no_prog_info = 0;

/*无节目流计数与显示控制*/
#define     P_ES_MONITOR_TIME   (2000)
static D_U32 last_video_evt_cnt = 0, last_audio_evt_cnt = 0;
static D_HTimer es_monitor_timer = D_INVALID_HANDLE;
static D_U8 no_es_compare_times = 0;
static D_U8 show_no_es_stream = 0;
static D_U8 no_es_stream_status = 0;

static D_U8 powoff_enable = 0;
static D_U8 powoff_hour = 0;
static D_U8 powoff_minute = 0;
static D_Time no_signal_start_time = 0;

static D_VidInput last_screeninput = D_VID_IUTPUT_MAX;
static D_VidInputFormat last_screenfmt  = D_VID_INPUT_ENCODE_MAX;
D_Bool stand_by = D_FALSE;//D_TRUE  亮屏;D_FALSE 灭屏

#define ShowVidFormatMax D_VID_INPUT_ENCODE_MAX
#define ShowVidFormatMax_cvbs 2

//#define WYG_MENU_SET  //added by wangyg on 2015-08-31

#define ShowVidFormatMax_dvi (D_VID_INPUT_UNDEFINE - D_VID_INPUT_DVI_MIN)

char* VidFormat_String[ShowVidFormatMax] =
{
    "480I@60HZ", "480I@60HZ", "576I@50HZ", "576I@50HZ", "480P@60HZ", "480P_1440@60HZ", "576P@50HZ", "576P_1440@50HZ",
    "720P@50HZ", "720P@60HZ", "1080I@50HZ", "1080I@60HZ	", "1080P@24HZ", "1080P@25HZ", "1080P@30HZ", "1080P@50HZ", "1080P@60HZ",

    "640x480@60HZ", "800x600@56HZ", "800x600 60HZ", "848x480@60HZ", "1024x768@60HZ", "1280x768@60HZ", "1280x768@60HZ", "1280x960@60HZ",
    "1280x1024@60HZ", "1360x768@60HZ", "1366x768 60HZ", "1400x1050@60HZ", "1400x1050@60HZ", "1440x900@60HZ", "1440x900@60HZ",
    "1600x1200@60HZ", "1680x1050@60HZ", "1680x1050@60HZ",

};
static D_VidInputFormat VidFormat_Mode[ShowVidFormatMax] =
{
    D_VID_INPUT_480I,  //30HZ                        //720*480              (858*525)
    D_VID_INPUT_480I_1440,//30HZ
    D_VID_INPUT_576I,    //25HZ                          //720*576              (864*625)
    D_VID_INPUT_576I_1440,//25HZ
    D_VID_INPUT_480P,    //60HZ                          //720*480              (858*525)
    D_VID_INPUT_480P_1440, //60HZ        //1440*480             (1728*525)
    D_VID_INPUT_576P,    //50HZ                          //720*576              (864*625)
    D_VID_INPUT_576P_1440,//50HZ                        //1440*576   (1728*625)
    D_VID_INPUT_720P_50, //50HZ                          //1280*720             (1980*750)
    D_VID_INPUT_720P_60,    //60HZ                       //1280*720             (1650*750)
    D_VID_INPUT_1080I_25, //25HZ                         //1920*1088            (2640*1125)
    D_VID_INPUT_1080I_30, //30HZ                         //1920*1088            (2200*1125)
    D_VID_INPUT_1080P_24,//25HZ
    D_VID_INPUT_1080P_25,//25HZ
    D_VID_INPUT_1080P_30,//30HZ
    D_VID_INPUT_1080P_50,//50HZ                          //1920*1088            (2640*1125)
    D_VID_INPUT_1080P_60, //60HZ                         //1920*1088            (2200*1125)

    //HDMI VESA
    D_VID_INPUT_640_480_60,
    D_VID_INPUT_800_600_56,         //800*600       (1024*625)
    D_VID_INPUT_800_600_60,         //800*600       (1056*628)
    D_VID_INPUT_848_480_60,         //848*480   (1088*517)
    D_VID_INPUT_1024_768_60,            //1024*768  (1344*806)

    D_VID_INPUT_1280_768_60_RB,     //1280*768  (1440*790)
    D_VID_INPUT_1280_768_60,            //1280*768  (1664*798)

    D_VID_INPUT_1280_960_60,            //1280*960  (1800*1000)

    D_VID_INPUT_1280_1024_60,           //1280*1024 (1688*1066)

    D_VID_INPUT_1360_768_60,            //1360*768  (1792*795)
    D_VID_INPUT_1366_768_60,            //1366*768  (1792*798)

    D_VID_INPUT_1400_1050_60_RB,        //1400*1050 (1560*1080)
    D_VID_INPUT_1400_1050_60,       //1400*1050 (1864*1089)

    D_VID_INPUT_1440_900_60_RB,     //1440*900  (1600*926)
    D_VID_INPUT_1440_900_60,            //1440*900 (1904*934)

    D_VID_INPUT_1600_1200_60,           //1600*1200 (2160*1250)

    D_VID_INPUT_1680_1050_60_RB,        //1680*1050 (1840*1080)
    D_VID_INPUT_1680_1050_60,       //1680*1050 (2240*1089)

};

char* VidFormat_String_cvbs[ShowVidFormatMax_cvbs] =
{
    "NTSC", "PAL",
};
static D_VidInputFormat VidFormat_Mode_cvbs[ShowVidFormatMax_cvbs] =
{
    D_VID_INPUT_480I,  //30HZ                        //720*480              (858*525)
    D_VID_INPUT_576I,    //25HZ                          //720*576              (864*625)
};

char* VidFormat_String_dvi[ShowVidFormatMax_dvi] =
{
    "720x480I@60HZ", "1440x480I@60HZ", "720x576I@50HZ", "1440x576I@50HZ", "720x480@60HZ", "720x576@50HZ", "1440x480@60HZ", "1440x576@50HZ", "1280x720@50HZ", "1280x720@60HZ",
    "640x480@60HZ", "800x600@56HZ", "800x600 60HZ", "848x480@60HZ", "1024x768@60HZ", "1280x768@60HZ", "1280x768@60HZ", "1280x960@60HZ",
    "1280x1024@60HZ", "1360x768@60HZ", "1366x768 60HZ", "1400x1050@60HZ", "1400x1050@60HZ", "1440x900@60HZ", "1440x900@60HZ",
    "1600x1200@60HZ", "1680x1050@60HZ", "1680x1050@60HZ", "1920x1080@60HZ"

};
static D_VidInputFormat VidFormat_Mode_dvi[ShowVidFormatMax_dvi] =
{
    //VESA DVI mode
    D_VID_INPUT_VESA_720_480_I,                //720*480        (858*525)
    D_VID_INPUT_VESA_1440_480_I,
    D_VID_INPUT_VESA_720_576_I,                //720*576        (864*625)
    D_VID_INPUT_VESA_1440_576_I,


    D_VID_INPUT_VESA_720_480_60_P,
    D_VID_INPUT_VESA_720_576_50_P,
    D_VID_INPUT_VESA_1440_480_60_P,
    D_VID_INPUT_VESA_1440_576_50_P,
    D_VID_INPUT_VESA_1280_720_50_P,
    D_VID_INPUT_VESA_1280_720_60_P,


    D_VID_INPUT_VESA_640_480_60,            //640*480       (800*525)
    D_VID_INPUT_VESA_800_600_56,            //800*600       (1024*625)
    D_VID_INPUT_VESA_800_600_60,            //800*600       (1056*628)
    D_VID_INPUT_VESA_848_480_60,        //848*480   (1088*517)
    D_VID_INPUT_VESA_1024_768_60,       //1024*768  (1344*806)
    D_VID_INPUT_VESA_1280_768_60_RB,        //1280*768  (1440*790)
    D_VID_INPUT_VESA_1280_768_60,       //1280*768  (1664*798)
    D_VID_INPUT_VESA_1280_960_60,       //1280*960  (1800*1000)
    D_VID_INPUT_VESA_1280_1024_60,          //1280*1024 (1688*1066)
    D_VID_INPUT_VESA_1360_768_60,       //1360*768  (1792*795)
    D_VID_INPUT_VESA_1366_768_60,       //1366*768  (1792*798)
    D_VID_INPUT_VESA_1400_1050_60_RB,   //1400*1050 (1560*1080)
    D_VID_INPUT_VESA_1400_1050_60,      //1400*1050 (1864*1089)

    D_VID_INPUT_VESA_1440_900_60_RB,        //1400*900  (1600*926)
    D_VID_INPUT_VESA_1440_900_60,           //1400*900 (1904*934)

    D_VID_INPUT_VESA_1600_1200_60,          //1600*1200 (2160*1250)

    D_VID_INPUT_VESA_1680_1050_60_RB,       //1680*1050 (1840*1080)
    D_VID_INPUT_VESA_1680_1050_60,      //1680*1050 (2240*1089)
    D_VID_INPUT_VESA_1080P_60,         //1920*1088      (2200*1125)
};

int p_get_curr_usb_status(void)
{
    return usb_insert;
}
int p_set_curr_usb_status(D_Bool plug, D_Ptr arg)
{
    if (!plug)
    {
        usb_insert &= (~(USB_INSERT << ((int)arg)));
    }
    else
    {
        usb_insert |= (USB_INSERT << ((int)arg));
    }
}

/** @brief 开始待机倒计时处理*/
D_Result stand_by_timer_deal(VOID) D_FUNCPOSTFIT
{
    p_atv_power_off_msg_show();
    return D_OK;
}

/** @brief 播放预订消息回调,开始播放节目*/
static D_Result
play_sub_callback_atv (D_Bool sel, D_U32 param) D_FUNCPOSTFIT
{
    D_DBSrvInfo srv_info;
    D_S16 chan = param;
    D_DBSrvID   dbsrv;
    D_VidInput          input;
    D_StbPlayer *player;
    player = p_stb_get_player(0);

    if (! sel)
    {
        return D_OK;
    }
#ifdef D_TV_SUPPORT_PVR
    if(PLAYER_IS_PVR_STATUS(player))
    {
        atv_media_pvr_record_service_stop();
        p_atv_meida_pvr_record_menu_hide();
    }
#endif
    d_gui_clear_menu ();
    input = p_conf_get_vid_input ();
    dbsrv = d_dbase_get_srv_by_num (chan, D_DB_SRV_ATV);
    if (dbsrv == -1)
    {
        return D_ERR;
    }
    //模拟电视
    if(input == D_VID_IUTPUT_TV)
    {
        /*开始播放节目*/
        p_stb_player_play_srv (0, dbsrv);
    }
    else
    {
        player->atv_id = dbsrv;
        p_conf_set_vid_input(D_VID_IUTPUT_TV);
        p_sys_set_input_mode(input, D_VID_IUTPUT_TV);
    }
    return D_OK;
}


/** @brief 开始播放预订节目*/
static D_Result
play_subscribe_atv (D_S16 chan) D_FUNCPOSTFIT
{
#define BUF_SIZE    (256)
    static D_Char   buf[BUF_SIZE];
    D_DBSrvID dbsrv;
    D_DBSrvInfo srv_info;
    D_U8 hour;
    D_U8 minute;

    dbsrv = d_dbase_get_srv_by_num (chan, D_DB_SRV_ATV);
    if (dbsrv == -1)
    {
        return D_ERR;
    }
    if (d_dbase_get_srv_info (dbsrv, &srv_info) != D_OK)
    {
        return D_ERR;
    }
    get_OrderTime_time(&hour, &minute);
    snprintf (buf, sizeof (buf), d_gui_get_text(atv_IDS_SUB_START_CHAN), srv_info.chan_num, hour, minute);

    /*用户取消切换，需要删除此预定*/
    set_Order_time(0, 0, 0);
    set_OrderTime_chan(-1);

    d_atv_pop_select_center_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE, d_gui_get_text(atv_IDS_PROMPT_INFO), buf,
                                 D_SUB_EVT_MSG_TIMEOUT, D_TRUE, play_sub_callback_atv, chan);
    return D_OK;
}

/** @brief 播放预订消息回调,开始播放节目*/
static D_Result
play_sub_callback (D_Bool sel, D_U32 param) D_FUNCPOSTFIT
{
    D_DBSrvInfo sinfo;
    D_DBSrvID   srv = (D_DBSrvID) param;
    D_StbPlayer *player;
    D_VidInput          input;

    player = p_stb_get_player(0);

    if (! sel)
    {
        /*用户取消切换，需要删除此预定*/
        d_dbase_check_subscribe (D_TRUE, P_SUBSCRIBE_TIME, NULL);
        return D_OK;
    }
#ifdef D_TV_SUPPORT_PVR
    if(PLAYER_IS_PVR_STATUS(player))
    {
        atv_media_pvr_record_service_stop();
        p_atv_meida_pvr_record_menu_hide();
    }
#endif
    if (d_dbase_get_srv_info (srv, &sinfo) < 0)
        return D_ERR;

    /*清除菜单*/
    d_gui_clear_menu ();
    input = p_conf_get_vid_input ();

    /*开始播放节目*/
    if(input == D_VID_IUTPUT_DTV)
    {
        /*开始播放节目*/
        p_stb_player_play_srv (0, srv);
    }
    else
    {
        player->play_srv = srv;
        p_conf_set_vid_input(D_VID_IUTPUT_DTV);
        p_sys_set_input_mode(input, D_VID_IUTPUT_DTV);
    }
    return D_OK;
}

/** @brief 开始播放预订节目*/
static D_Result
play_subscribe (D_DBSubID sub) D_FUNCPOSTFIT
{
#define BUF_SIZE    (256)
    static D_Char   buf[BUF_SIZE];
    D_DBEvtInfo einfo;
    D_DBSrvInfo srv_info;
    D_ID start_time, end_time;
    D_Date start_date, end_date;


    if (d_dbase_get_subscribe_info (sub, &einfo) < 0)
    {
        return D_ERR;
    }

    if (d_dbase_get_srv_info (einfo.db_srv_id, &srv_info) < 0)
    {
        return D_ERR;
    }

    if (g_stb->status == D_STB_ST_PLAYING)
    {
        start_time = d_time_local_time (einfo.start);
        d_date (start_time, &start_date);
        end_time = d_time_local_time (einfo.start + einfo.duration);
        d_date (end_time, &end_date);

        snprintf (buf, sizeof (buf), d_gui_get_text(atv_IDS_SUB_START), srv_info.chan_num, srv_info.name,
                  einfo.name, start_date.hour, start_date.min, end_date.hour, end_date.min);

        d_atv_pop_select_center_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE, d_gui_get_text(atv_IDS_PROMPT_INFO), buf,
                                     D_SUB_EVT_MSG_TIMEOUT, D_TRUE, play_sub_callback, einfo.db_srv_id);
    }
    /*提示用户后删除该预订*/
    d_dbase_delete_subscribe(sub);
    return D_OK;
}

/** @brief 检查是否有节目到期*/
static D_Result
send_sub_msg (D_ID sub_id) D_FUNCPOSTFIT
{
    D_SubMsg    msg;

    if(!STB_STATUS_STANDBY())
    {
        msg.type = D_MSG_SUB_START;
        msg.sub_id = sub_id;

        D_DUMP("send_sub_msg(%d)", sub_id);
        d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
    }
    return  D_OK;
}

/** @brief 设置定时关机
* @param[in] enable 使能与否
* @param[in]
* @retval D_OK
*/
D_Result
p_set_poweroff_timer_enable(D_Bool enable, D_U8 hour, D_U8 minute)D_FUNCPOSTFIT
{
    if(enable)
    {
        powoff_enable = enable;
        powoff_hour = hour;
        powoff_minute = minute;
    }
    else
    {
        powoff_enable = 0;
        powoff_hour = 0;
        powoff_minute = 0;
    }
    return D_OK;
}
/** @brief 检查定时关机
* @param[in]
* @param[in]
* @retval D_OK 时间到
*/
D_Result
stand_by_timer_check(void) D_FUNCPOSTFIT
{
    if(powoff_enable)
    {
        D_Time utc_time = 0;
        D_Time  now = 0;
        D_Date  date = {0};

        now = d_time_get_local_time();
        now += 68; /*提前一分钟提示，15秒检查一次，所以68*/
        d_date (now, &date);
        if((date.hour == powoff_hour) && (date.min == powoff_minute))
        {
            powoff_enable = 0;
            powoff_hour = 0;
            powoff_minute = 0;
            return D_OK;
        }
    }
    return D_ERR;
}


/** @brief 设置是否允许显示信号中断提示
* @param[in] enable 使能与否
* @param[in] lock 锁定使能状态。0不锁定，1锁定，2取消锁定
* @retval D_OK
*/
D_Result
p_set_signal_faint_msg_enable(D_Bool enable, D_U8 lock)D_FUNCPOSTFIT
{
    static D_Bool lock_status = D_FALSE;

    if(lock > 1)
    {
        lock_status = D_FALSE;
    }

    if(lock_status)
    {
        return D_OK;
    }

    if(lock == 1)
    {
        lock_status = D_TRUE;
    }

    if(enable)
    {
        signal_faint_msg_show_enable = D_TRUE;
        if(signal_is_not_good && (!signal_faint_msg_showing))
        {
            signal_faint_msg_showing = D_TRUE;
            p_atv_no_signal_win_show();
        }
    }
    else
    {
        signal_faint_msg_show_enable = D_FALSE;
        if(signal_faint_msg_showing)
        {
            p_atv_no_signal_win_hide();
        }
        signal_faint_msg_showing = D_FALSE;
    }

    return D_OK;
}

/*信号中断提示的显示与清除*/
D_Result
p_signal_faint_msg(D_Bool show)D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_VidInput      input;

    input = p_conf_get_vid_input ();

    player = p_stb_get_player (curr_player_id);
    if (! player)
        return D_ERR;

    if (show)
    {
        if(!signal_is_not_good)
        {
            signal_is_not_good = D_TRUE;
            /*停止播放*/
            if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
            {
                p_stb_player_stop (curr_player_id);
                p_stb_player_clear_vid(curr_player_id); // 清除定帧
            }
        }

        /*提示信号中断*/
        if(signal_faint_msg_show_enable && (!signal_faint_msg_showing))
        {
            signal_faint_msg_showing = D_TRUE;
            p_atv_no_signal_win_show();
        }
    }
    else
    {
        if(signal_is_not_good)
        {
            if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
            {
                /*先恢复视频播放状态*/
                p_stb_player_stop (curr_player_id);
                /*清除开机画面显示*/
                /*恢复播放*/
                p_stb_player_play_valid (curr_player_id);
                d_tv_set_vid_blank (player->htv, D_FALSE);  // 取消黑屏
            }
            /*清除消息框*/
            if(signal_faint_msg_showing)
            {
                p_atv_no_signal_win_hide();
            }
            signal_faint_msg_showing = D_FALSE;
            signal_is_not_good = D_FALSE;

            /*取消黑屏*/
        }
    }

    return D_OK;
}

/*重新显示信号中断提示信息*/
D_Result
p_signal_faint_msg_reshow(void)D_FUNCPOSTFIT
{
    if(signal_is_not_good)
    {
        if(signal_faint_msg_showing)
        {
            p_atv_no_signal_win_hide();
        }

        if(signal_faint_msg_show_enable)
        {
            signal_faint_msg_showing = D_TRUE;
            p_atv_no_signal_win_show();
        }
    }
    return D_OK;
}
/*信号中断提示的显示与清除*/
D_Result
p_signal_faint_start(D_U8 ctrl)D_FUNCPOSTFIT
{
    if(ctrl == 0 )
    {
        if(no_signal_start_time == 0)
            return D_ERR;
        if(d_sys_get_time() - no_signal_start_time < 2000)
        {
            return D_ERR;
        }
        p_signal_faint_msg(D_TRUE);
        no_signal_start_time = 0;
    }
    else if(ctrl == 1 )
    {
        no_signal_start_time = d_sys_get_time();
    }
    else if(ctrl == 2 )
    {
        p_signal_faint_msg(D_FALSE);
        no_signal_start_time = 0;
    }
    return D_OK;
}

static D_Result
sw_update_handler (D_Bool sel, D_U32 param) D_FUNCPOSTFIT
{
    /*重新启动*/
    if(sel)
        d_sys_reboot();
    return D_OK;
}

static D_Result
force_sw_update_handler (D_U32 param) D_FUNCPOSTFIT
{
    d_sys_reboot();
    return D_OK;
}

static D_Result
solve_sw_update_evt(D_SiEvtparam param) D_FUNCPOSTFIT
{
    switch(param.montype)
    {
        case D_MSG_MON_SW_UPDATE:
        {
            d_pop_select_show(D_POP_MSG_PRIO_MSG_4, D_GUI_LAYER_MESSAGE,
                              d_gui_get_text(atv_IDS_NEW_SOFTWARE), d_gui_get_text(atv_IDS_SW_UPDATE), 0, D_TRUE, sw_update_handler, (D_U32)(param.pdata));
        }
        break;

        case D_MSG_MON_SW_UPDATE_MUST:
        {
            d_pop_msg_show(D_POP_MSG_PRIO_MSG_4,
                           D_GUI_LAYER_MESSAGE,
                           D_POP_MSG_ERROR,   d_gui_get_text(atv_IDS_NEW_SOFTWARE), d_gui_get_text(atv_IDS_SW_UPDATE_MUST),
                           3000, D_POP_MSG_RESPONSE_NOT, D_FALSE, force_sw_update_handler,  (D_U32)(param.pdata));

        }
        break;

        default:
            break;
    }

    return D_OK;
}

/*没有保存节目提示的显示与清除*/
D_Result
p_no_prog_msg(D_Bool show)D_FUNCPOSTFIT
{
    D_DBSrvType type;
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (0)))
    {
        return D_ERR;
    }

    if(show)
    {
        if (player->play_atv)
        {
            type = D_DB_SRV_ATV;
        }
        else if(player->play_radio)
        {
            type = D_DB_SRV_RADIO;
        }
        else
        {
            type = D_DB_SRV_TV;
        }
        if((type == D_DB_SRV_TV && (D_TRUE != d_dbase_has_any_srv(type)))
           || (type == D_DB_SRV_RADIO && (D_TRUE != d_dbase_has_any_srv(type)))
           || (type == D_DB_SRV_ATV && (D_TRUE != d_dbase_has_any_srv(type))))
        {
            if (player->status == D_STB_PLAYER_STATUS_PLAYING)
            {
                d_stb_stop_play();
            }
            p_atv_no_signal_win_show();
        }

    }
    else
    {
        p_atv_no_signal_win_hide();
    }

    return D_OK;
}
#define D_NO_ES_NONE 0
#define D_NO_ES_SHOW 1
#define D_NO_ES_CLEAR 2

static D_U32
judge_no_es_stream(void)
{
    D_U32 ret = D_NO_ES_NONE;
    D_U32 curr_video_evt_cnt = 0;
    D_U32 curr_audio_evt_cnt = 0;
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (0)))
    {
        return D_ERR;
    }

    d_av_get_evt_cnt(&curr_video_evt_cnt, &curr_audio_evt_cnt);

    /*停止播放状态无需要判断*/
    if(player->status == D_STB_PLAYER_STATUS_STOPPED)
    {
        last_audio_evt_cnt = curr_audio_evt_cnt;
        last_video_evt_cnt = curr_video_evt_cnt;
        no_es_compare_times = 0;
        return D_ERR;
    }

    if(player->play_radio)
    {
        if(last_audio_evt_cnt != curr_audio_evt_cnt)
        {
            ret = D_NO_ES_CLEAR;
            last_audio_evt_cnt = curr_audio_evt_cnt;
            no_es_compare_times = 0;
        }
        else
        {
            if(no_es_compare_times >= 1)
            {
                ret = D_NO_ES_SHOW;
                no_es_compare_times = 0;
            }
            else
            {
                no_es_compare_times++;
            }
        }
        last_video_evt_cnt = 0;
    }
    else
    {
        if((last_audio_evt_cnt != curr_audio_evt_cnt) || (last_video_evt_cnt != curr_video_evt_cnt))
        {
            ret = D_NO_ES_CLEAR;
            last_audio_evt_cnt = curr_audio_evt_cnt;
            last_video_evt_cnt = curr_video_evt_cnt;
        }
        else
        {
            if(no_es_compare_times >= 1)
            {
                ret = D_NO_ES_SHOW;
                no_es_compare_times = 0;
            }
            else
            {
                no_es_compare_times++;
            }
        }
    }

    return ret;
}
/*显示加密节目OSD*/
#define SHOW_PROG_NOT_PLAY_OSD(_textid_)\
{\
    d_atv_pop_msg_show(D_POP_MSG_PRIO_VIDEO_MSG_1, \
            D_GUI_LAYER_VIDEO/*D_GUI_LAYER_VIDEO_MESSAGE*/, \
            D_POP_MSG_MSG,\
            NULL,\
            d_gui_get_text(_textid_),\
            0, D_POP_MSG_RESPONSE_NOT, D_TRUE, NULL,0);\
    show_no_es_stream = 1;\
}
#define CLEAR_PROG_NOT_PLAY_OSD() if(show_no_es_stream){show_no_es_stream = 0;d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_1);}

/*节目无法播放显示信息*/
D_Result
p_not_play_msg_show(D_Bool show)D_FUNCPOSTFIT
{
    D_ID srv;
    D_DBSrvInfo srvinfo;

    /*播放不出处理*/
    if(show)
    {
        srv = p_stb_player_get_curr_srv(curr_player_id);
        if(srv >= 0)
        {
            d_dbase_get_srv_info(srv, &srvinfo);
            if(srvinfo.ca_flag)
            {
                if(STB_STATUS_PLAYING() )
                {
#if   D_CA_SUPPORT_DEF   //不带CA的软件提示"加密节目"
#else
                    SHOW_PROG_NOT_PLAY_OSD(atv_IDS_SCRAMBLED_PROG);
#endif
                }
            }
        }
    }
    else
    {
        CLEAR_PROG_NOT_PLAY_OSD();
    }

    return D_OK;
}

/*显示没有节目流提示信息*/
D_Result
p_no_es_stream_show(D_Bool show, D_Bool play_logo)D_FUNCPOSTFIT
{
    D_StbPlayer *player;


    if (! (player = p_stb_get_player (0)))
    {
        return D_ERR;
    }

    if(show)
    {
        if(!no_es_stream_status)
        {
            if(play_logo)
            {
                /*显示广播背景*/
                //p_stb_player_display_pic_I (0, DAD_STB_LOG,0);
            }
            else
            {
                p_stb_player_clear_vid(0);
            }
            d_tv_sync(player->htv);
            no_es_stream_status = 1;
            D_DUMP("no es stream\n");
        }

        if(!show_no_es_stream)
        {
            //show osd
            p_not_play_msg_show(D_TRUE);
        }
    }
    else
    {
        if (play_logo)
        {
            if (player->play_radio && STB_STATUS_PLAYING())
            {
                /*显示广播背景*/
                p_stb_player_display_pic_I (0, DAD_STB_RadioBackGround, 0);
            }
        }

        /*取消黑屏*/
        if(no_es_stream_status)
        {
            d_tv_set_vid_blank(player->htv, D_FALSE);
        }

        //hide osd
        p_not_play_msg_show(D_FALSE);

        no_es_stream_status = 0;
        show_no_es_stream = 0;
        no_es_compare_times = 0;
    }

    return D_OK;
}
/**得到当前的信号是否中断*/
D_Bool atv_player_get_curr_singnal() D_FUNCPOSTFIT
{
    return signal_is_not_good;
}

static char* atv_get_fmtchar(D_VidInputFormat fmt) D_FUNCPOSTFIT
{
    D_U16 i;
    for(i = 0; i < ShowVidFormatMax; i ++)
    {
        if(VidFormat_Mode[i] == fmt)
        {
            return VidFormat_String[i];
        }
    }
    return NULL;
}
static char* atv_get_fmtchar_cvbs(D_VidInputFormat fmt) D_FUNCPOSTFIT
{
    D_U16 i;
    for(i = 0; i < ShowVidFormatMax_cvbs; i ++)
    {
        if(VidFormat_Mode_cvbs[i] == fmt)
        {
            return VidFormat_String_cvbs[i];
        }
    }
    return NULL;
}

static char* atv_get_fmtchar_dvi(D_VidInputFormat fmt) D_FUNCPOSTFIT
{
    D_U16 i;
    for(i = 0; i < ShowVidFormatMax_dvi; i ++)
    {
        if(VidFormat_Mode_dvi[i] == fmt)
        {
            return VidFormat_String_dvi[i];
        }
    }

    return NULL;
}
D_Result atv_reset_screen(void) D_FUNCPOSTFIT
{
    last_screeninput = D_VID_IUTPUT_MAX;
    last_screenfmt  = D_VID_INPUT_ENCODE_MAX;

    return D_OK;
}

D_VidInputFormat atv_get_last_screenfmt(void) D_FUNCPOSTFIT
{
    return last_screenfmt;
}

static D_Result atv_show_scaninfo(D_VidInput input, D_VidInputFormat fmt) D_FUNCPOSTFIT
{
    switch(fmt)
    {
        case    D_VID_INPUT_480I:
        case    D_VID_INPUT_480I_1440:
        {
            p_vip_set_param(input, 0, 1, 0, 1); //标清NTSC
            break;
        }
        case    D_VID_INPUT_480P:
        case    D_VID_INPUT_480P_1440:
        {
            p_vip_set_param(input, 0, 1, 1, 1); //标清NTSC
            break;
        }
        case    D_VID_INPUT_576I:                            //720*576              (864*625)
        case    D_VID_INPUT_576I_1440:
        {
            p_vip_set_param(input, 0, 0, 0, 1); //标清PAL
            break;
        }
        case    D_VID_INPUT_576P:                        //720*576              (864*625)
        case    D_VID_INPUT_576P_1440:              //1440*576   (1728*625)
        {
            p_vip_set_param(input, 0, 0, 1, 1); //标清PAL
            break;
        }
        case    D_VID_INPUT_1080I_25:                //1920*1088            (2640*1125)
        case    D_VID_INPUT_1080I_30:                    //1920*1088            (2200*1125)
        {
            p_vip_set_param(input, 1, 0, 0, 1); //高清PAL
            break;
        }
        case    D_VID_INPUT_720P_50:                     //1280*720             (1980*750)
        case    D_VID_INPUT_720P_60:                         //1280*720             (1650*750)
        case    D_VID_INPUT_1080P_24:
        case    D_VID_INPUT_1080P_25:
        case    D_VID_INPUT_1080P_50:                    //1920*1088            (2640*1125)
        case    D_VID_INPUT_1080P_30:
        case    D_VID_INPUT_1080P_60:                //1920*1088            (2200*1125)
        {
            p_vip_set_param(input, 1, 0, 1, 1); //高清PAL
            break;
        }
        default:
        {
            p_vip_set_param(input, 0, 0, 0, 1); //标清PAL
            break;
        }
    }
    switch(input)
    {
        case D_VID_IUTPUT_AV1:
        case D_VID_IUTPUT_AV2:
        {
            p_atv_signal_input_show(input, atv_get_fmtchar_cvbs(fmt), NULL);
            last_screeninput = input;
            last_screenfmt  = fmt;
            break;
        }
        case D_VID_IUTPUT_S:
        case D_VID_IUTPUT_YPBPR:
        case D_VID_IUTPUT_VGA:
        {
            p_atv_signal_input_show(input, atv_get_fmtchar(fmt), NULL);
            last_screeninput = input;
            last_screenfmt  = fmt;
            break;
        }
        case D_VID_IUTPUT_HDMI1:
        {
            if( fmt > D_VID_INPUT_DVI_MIN)
            {
                p_atv_signal_input_show(D_VID_IUTPUT_DVI1, atv_get_fmtchar_dvi(fmt), NULL);
            }
            else
            {
                p_atv_signal_input_show(input, atv_get_fmtchar(fmt), NULL);
            }
            last_screeninput = input;
            last_screenfmt  = fmt;
            break;
        }
        case D_VID_IUTPUT_HDMI2:
        case D_VID_IUTPUT_HDMI3:
        {
            if( fmt > D_VID_INPUT_DVI_MIN)
            {
                p_atv_signal_input_show(D_VID_IUTPUT_DVI2, atv_get_fmtchar_dvi(fmt), NULL);
            }
            else
            {
                p_atv_signal_input_show(input, atv_get_fmtchar(fmt), NULL);
            }
            last_screeninput = input;
            last_screenfmt  = fmt;
            break;
        }
        default:
        {
            break;
        }
    }

    return D_OK;
}
static D_Result atv_show_screen(D_VidInput input) D_FUNCPOSTFIT
{
    if(input == D_VID_IUTPUT_TV)
    {
        p_atv_tv_chan_info_window_show(curr_player_id);
    }
    else if(input == D_VID_IUTPUT_DTV)
    {
        p_atv_channel_info_window_show(curr_player_id);
    }
    else if((last_screeninput == input) && (last_screenfmt != D_VID_INPUT_ENCODE_MAX))
    {
        switch(input)
        {
            case D_VID_IUTPUT_AV1:
            case D_VID_IUTPUT_AV2:
            {
                p_atv_signal_input_show(input, atv_get_fmtchar_cvbs(last_screenfmt), NULL);
                break;
            }
            default:
            {
                p_atv_signal_input_show(input, atv_get_fmtchar(last_screenfmt), NULL);
                break;
            }
        }
    }
    else
    {
        p_atv_signal_input_show(input, NULL, NULL);
    }
    return D_OK;
}


#ifndef D_TV_IAMGE_SOURCE
static D_Result onekey_Set_auto_adc(void)
{
    D_U8 hdflag;
    D_ADC_SET param;
    D_COMP_SET comp_param;
    D_COMP_SET hdcomp_param;
    D_COMP_SET temp_comp_param;
    D_VidInput input = p_conf_get_vid_input();

    if(input != D_VID_IUTPUT_YPBPR)
        return D_ERR;
    p_tvconf_get_comp_set_param(&comp_param, p_vip_get_dbinput(input));
    p_tvconf_get_hdcomb_set_param(&hdcomp_param, p_vip_get_dbinput(input));
    if(d_vip_AutoADC(&param, &temp_comp_param) == D_TRUE)
    {
        p_tvconf_set_hdadc_set_param(&param, p_vip_get_dbinput(input));
        p_tvconf_set_adc_set_param(&param, p_vip_get_dbinput(input));

        comp_param.comp_gain_r = temp_comp_param.comp_gain_r;
        comp_param.comp_gain_g = temp_comp_param.comp_gain_g;
        comp_param.comp_gain_b = temp_comp_param.comp_gain_b;
        comp_param.comp_vclamplevel_r = temp_comp_param.comp_vclamplevel_r;
        comp_param.comp_vclamplevel_g = temp_comp_param.comp_vclamplevel_g;
        comp_param.comp_vclamplevel_b = temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_comp_set_param(&comp_param, p_vip_get_dbinput(input));

        hdcomp_param.comp_gain_r = temp_comp_param.comp_gain_r;
        hdcomp_param.comp_gain_g = temp_comp_param.comp_gain_g;
        hdcomp_param.comp_gain_b = temp_comp_param.comp_gain_b;
        hdcomp_param.comp_vclamplevel_r = temp_comp_param.comp_vclamplevel_r;
        hdcomp_param.comp_vclamplevel_g = temp_comp_param.comp_vclamplevel_g;
        hdcomp_param.comp_vclamplevel_b = temp_comp_param.comp_vclamplevel_b;
        p_tvconf_set_hdcomb_set_param(&hdcomp_param, p_vip_get_dbinput(input));
        return D_OK;
    }
    else
    {
        return D_ERR;
    }
}
#endif

/** @brief 用于金锐显完成之后进行恢复设置*/
static D_Result
ctv_factory_reset(void) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_LoaderParam loader_param;
    D_VidInput input;
    D_U8 debug_en, logo_mode;

    player = p_stb_get_player(0);
    input = p_conf_get_vid_input();
    if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
    {
        /*停止所有播放*/
        d_stb_stop_play ();
    }

    d_sys_stand_by();

    /*关闭窗体*/
    d_gui_clear_menu ();
    d_gui_clear_layer (D_GUI_LAYER_VIDEO_OSD);
    d_gui_clear_layer (D_GUI_LAYER_MESSAGE);

    /*关闭GUI显示*/
    d_gui_show (D_FALSE);
    /*停止所有播放*/
    d_stb_stop_play ();

    d_dbase_set_rset_en(0);
    d_dbase_clear_srv ();
    d_dbase_clear_evt ();
    d_dbase_clear_ts ();
    d_dbase_clear_net ();
    //d_dbase_clear_nvod ();
    d_dbase_clear_bouq ();
    d_dbase_clear_subscribe ();
    //d_dbase_rset_add_ts();

    p_conf_restore(D_FALSE);
    p_tvconf_restore(D_FALSE);

    /*刷新数据库*/
    d_dbase_flush();

    //powermode模式恢复为开
    if(p_conf_get_loader_param(&loader_param) == D_OK)
    {
        loader_param.reserved2 = 1;
        p_conf_set_loader_param(&loader_param);
    }
    /* 工厂复位时，将调试模式关闭*/
    debug_en = 1;
    p_tvconf_set_debug_en(debug_en);
    logo_mode = 0;
    p_tvconf_set_logomode (&logo_mode);

    p_precast_program(0);//预制BOE的节目
    d_sys_reboot();
    return D_OK;
}

static D_VidInput       stand_by_input;

/** @brief 播放器事件处理*/
static D_Result
atv_player_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    //D_DBSrvType    type;
    //D_S16     num;
    D_StbPlayer *player;
    D_VidInput      input;

    player = p_stb_get_player (curr_player_id);
    if (! player)
        return D_ERR;

    input = p_conf_get_vid_input ();
    if(input == D_VID_IUTPUT_TV)
    {
        player->play_atv = D_TRUE;
    }
    else
    {
        player->play_atv = D_FALSE;
    }

    switch (evt->type)
    {
        case D_EVT_FP:
            /*待机/唤醒功能*/
            if(evt->fp.key == D_KEY_POWER || evt->fp.key == D_KEY_PNL_POWER)
            {
#if 0//def D_TV_PEOJECT_TOUYY
                if(stand_by == D_FALSE)
                {
                    stand_by_input = input;
                    p_vip_set_panel_close();
                    d_sys_stand_by();
                    lcd_1638_stand_by();
                    stand_by = D_TRUE;
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_TEST);
                    aging_Ctrl_close();
                    d_PowerOff_Led_Ctrl(1);
                }
                else
                {
                    d_PowerOff_Led_Ctrl(0);
                    p_sys_set_input_mode( D_VID_IUTPUT_TEST, p_conf_get_vid_input());
                    if(stand_by_input == D_VID_IUTPUT_USB1)
                    {
                        p_atv_media_main_menu_show();
                    }
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
                    else if(stand_by_input == D_VID_IUTPUT_WIFIDISPLAY)
                    {
                        p_atv_zhilian_main_menu_window_show();
                    }
#endif
                    p_vip_set_panel_open();
                    d_sys_wake_up();
                    lcd_1638_stand_wake_up();
                    stand_by = D_FALSE;
                }
#else
                if(evt->fp.key == D_KEY_PNL_POWER)
                {
                    D_U8 aging = 0;
                    p_tvconf_set_aging(&aging);
                    if(input == D_VID_IUTPUT_TEST)
                        p_conf_set_vid_input(D_VID_IUTPUT_DTV);
                }
                if(STB_STATUS_STANDBY())
                {
                    d_stb_wake_up();
                }
                else
                {
#ifdef D_TV_SUPPORT_PVR
                    p_atv_media_pvr_record_stop();
#endif
                    d_stb_stand_by();
                }
#endif
                break;
            }

            /*待机状态下不再响应按键*/
            if(STB_STATUS_STANDBY())
            {
                break;
            }

            if(d_ad_set_fpkey_ex(evt->fp.key) == D_OK)
            {
                break;
            }
            if(!STB_STATUS_PLAYING())
            {
                /*非全屏状态下，可以处理静音与音量加减键 @qiny 2015.08.20*/
                if(evt->fp.key != D_KEY_VOLUME_PLUS && evt->fp.key != D_KEY_VOLUME_MINUS && evt->fp.key != D_KEY_MUTE)
                {
                    break;
                }
            }
            switch (evt->fp.key)
            {
#ifdef WYG_MENU_SET
                case D_KEY_0:
                    p_atv_set_register_show (0);
                    break;
                case D_KEY_1:
                    p_atv_set_register_show (1);
                    break;
                case D_KEY_2:
                    p_atv_set_register_show (2);
                    break;
                case D_KEY_3:
                    p_atv_set_register_show (3);
                    break;
                case D_KEY_4:
                    p_atv_set_register_show (4);
                    break;
                case D_KEY_5:
                    p_atv_set_register_show (5);
                    break;
                case D_KEY_6:
                    p_atv_set_register_show (6);
                    break;
                case D_KEY_7:
                    p_atv_set_register_show (7);
                    break;
                case D_KEY_8:
                    p_atv_set_register_show(8);
                    break;
#endif
                case D_KEY_IMAGE:
                    p_image_mode_win_show();
                    break;
                case D_KEY_SOUND:
                    p_video_mode_win_show();
                    break;
                case D_KEY_ZOOM:
                    p_ratio_mode_win_show();
                    break;
                case D_KEY_SOURCE:
                case D_KEY_PNL_SOURCE:
                    p_atv_signal_select_show();
                    break;
                case D_KEY_RESTORE://CTV恢复
                {
                    ctv_factory_reset();
                    break;
                }
                case D_KEY_FACTORYSET://工厂复位
                {
                    tv_reset_factory_setting();
                    break;
                }
                case D_KEY_VIPMENU:
                {
                    p_atv_factory_setting_show();
                    break;
                }
                case D_KEY_DTV_ATV:
                {
                    if(p_conf_get_vid_input() == D_VID_IUTPUT_DTV)
                    {
                        p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_TV);
                        p_conf_set_vid_input(D_VID_IUTPUT_TV);
                    }
                    else
                    {
                        p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_DTV);
                        p_conf_set_vid_input(D_VID_IUTPUT_DTV);
                    }
                    break;
                }
                case D_KEY_AV1:
                {
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_AV1);
                    p_conf_set_vid_input(D_VID_IUTPUT_AV1);
                    break;
                }
                case D_KEY_AV2:
                {
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_AV2);
                    p_conf_set_vid_input(D_VID_IUTPUT_AV2);
                    break;
                }
                case D_KEY_YPBPR1:
                case D_KEY_YPBPR2:
                {
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_YPBPR);
                    p_conf_set_vid_input(D_VID_IUTPUT_YPBPR);
                    break;
                }
                case D_KEY_HDMI1:
                {
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_HDMI1);
                    p_conf_set_vid_input(D_VID_IUTPUT_HDMI1);
                    break;
                }
                case D_KEY_HDMI2:
                {
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_HDMI2);
                    p_conf_set_vid_input(D_VID_IUTPUT_HDMI2);
                    break;
                }
                case D_KEY_USB:
                {
                    if(p_conf_get_vid_input() != D_VID_IUTPUT_USB1)
                    {
                        p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_USB1);
                        p_conf_set_vid_input(D_VID_IUTPUT_USB1);
                        p_atv_media_main_menu_show();
                    }
                    break;
                }
                case D_KEY_OLDMODE:
                {
                    p_conf_set_vid_input(D_VID_IUTPUT_TEST);
                    p_sys_set_input_mode(input, D_VID_IUTPUT_TEST);

                    break;
                }
                case D_KEY_IMPORTPROM:
                    p_precast_program(0);
                    break;
                case D_KEY_EXITOLDMODE:
                {
                    if(input == D_VID_IUTPUT_TEST)
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_DTV);
                        p_sys_set_input_mode(D_VID_IUTPUT_TEST, D_VID_IUTPUT_DTV);
                    }

                    break;
                }
                case D_KEY_SCREEN:
                    atv_show_screen(input);
                    break;
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    if(input == D_VID_IUTPUT_USB1)
                    {
                        p_atv_media_menus_show(D_FALSE, 0);
                    }
                    p_atv_main_menu_show();
                    break;
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
                case D_KEY_HOME:
                    {
                        p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_WIFIDISPLAY);
                        p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
//                        p_atv_zhilian_main_menu_window_show();
                    }
                    break;
#endif
                case D_KEY_PNL_L:
                case D_KEY_PNL_R:
                    if(STB_STATUS_PLAYING())
                    {
                        p_atv_volume_window_show(curr_player_id, evt->fp.key);
                    }
                    break;
                case D_KEY_MUTE:
                    p_atv_mute_window_show();
                    break;
                case D_KEY_RECALL:
                    if (STB_STATUS_PLAYING() && PLAYER_CAN_CHANNEL_CHANGE(player))
                    {
                        p_stb_player_alt_srv(curr_player_id);
                    }
                    break;
                case D_KEY_BACK:
                    p_sys_set_input_mode(p_conf_get_vid_input(), D_VID_IUTPUT_WIFIDISPLAY);
                    p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
                    //p_atv_zhilian_main_menu_window_show();
                    break;
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                    p_atv_volume_window_show(curr_player_id, evt->fp.key);
                    break;
                case D_KEY_UP:
                case D_KEY_PROGRAM_PLUS:
                case D_KEY_PNL_U:
                    if(STB_STATUS_PLAYING() && PLAYER_CAN_CHANNEL_CHANGE(player))
                    {
                        if(input == D_VID_IUTPUT_DTV)
                        {
                            if(D_OK != p_stb_player_channel_up(curr_player_id))
                            {
                                p_atv_channel_info_window_show(curr_player_id);
                            }
                        }
                        else if(input == D_VID_IUTPUT_TV)
                        {
                            if(D_OK != p_stb_player_channel_up(curr_player_id))
                            {
                                p_atv_tv_chan_info_window_show(curr_player_id);
                            }
                        }
                    }
                    break;
                case D_KEY_RED:
                    if(STB_STATUS_PLAYING() && input == D_VID_IUTPUT_DTV)
                    {
                        p_stb_atv_epg_window_show();
                    }
                    break;
                case D_KEY_GREEN:
#ifdef D_TV_SUPPORT_PVR
                    if(STB_STATUS_PLAYING() && input == D_VID_IUTPUT_DTV)
                    {
                        p_atv_pvr_record_menu_show();
                    }
#endif
                    break;
#ifndef D_TV_IAMGE_SOURCE
                case D_KEY_ADC:
                    if(input == D_VID_IUTPUT_YPBPR)
                    {
                        D_Result ret;

                        d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, "校正中...", -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        d_gui_update();
                        ret = onekey_Set_auto_adc();
                        d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_2);
                        if(ret == D_OK)
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, "成功", 5000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                        else
                            d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, NULL, "失败", 5000, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);

                    }
                    break;
#endif
                case D_KEY_DOWN:
                case D_KEY_PROGRAM_MINUS:
                case D_KEY_PNL_D:
                    if (STB_STATUS_PLAYING() && PLAYER_CAN_CHANNEL_CHANGE(player))
                    {
                        if(input == D_VID_IUTPUT_DTV)
                        {
                            if(D_OK != p_stb_player_channel_down(curr_player_id))
                            {
                                p_atv_channel_info_window_show(curr_player_id);
                            }
                        }
                        else if(input == D_VID_IUTPUT_TV)
                        {
                            if(D_OK != p_stb_player_channel_down(curr_player_id))
                            {
                                p_atv_tv_chan_info_window_show(curr_player_id);
                            }
                        }
                    }
                    break;
                case D_KEY_TV_RADIO:
                case D_KEY_RADIO:
                    /*广播电视切换*/
                    if(input != D_VID_IUTPUT_DTV)
                        break;
                    if (STB_STATUS_PLAYING() && PLAYER_CAN_CHANNEL_CHANGE(player))
                    {
                        if (player->play_radio)
                        {
                            p_stb_player_switch_tv_radio (curr_player_id, D_TRUE);
                        }
                        else
                        {
                            p_stb_player_switch_tv_radio (curr_player_id, D_FALSE);
                        }
                    }
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(input != D_VID_IUTPUT_DTV)
                        break;
                    if (STB_STATUS_PLAYING())
                    {
                        if(player->play_radio)
                        {
                            p_atv_radio_chan_list_show();
                        }
                        else
                        {
                            p_atv_tv_chan_list_show();
                        }
                    }
                    break;
                case D_KEY_YELLOW:
#if (defined(HI_P_TV_TYPE_TV))
#if   D_CA_SUPPORT_DEF
                    if(input == D_VID_IUTPUT_DTV) //DTV下显示ca菜单
                    {
                        p_atv_ca_main_window_show();
                    }
#endif
#endif
                    break;
                case D_KEY_CAKEY:
#if   D_CA_SUPPORT_DEF
                    p_atv_serial_show();
#endif
                    break;
                case D_KEY_BLUE:
                    if(STB_STATUS_PLAYING() && input == D_VID_IUTPUT_DTV)
                    {
                        p_atv_multi_audio_window_show();
                    }
                    break;
                case D_KEY_SEARCH://搜台
                    if(input == D_VID_IUTPUT_DTV)
                    {
                        D_ScanTaskConfig scan_config = {0};
                        D_FULLSCAN_CONFIG fullscan_config;
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
                        p_full_search_window_show(STB_SCAN_TYPE_FULL, &scan_config);
                    }
                    else if(input == D_VID_IUTPUT_TV)
                    {
                        patv_auto_scan_analog_show();
                    }
                    break;
                case D_KEY_INFO:
                    if(input == D_VID_IUTPUT_DTV)
                    {
                        if (STB_STATUS_PLAYING())
                        {
                            if(p_conf_get_scan_config())
                            {
                                d_dvbc_chan_info_test_window_show();
                            }
                            else
                            {
                                d_dtmb_chan_info_test_window_show();
                            }
                        }
                    }
                    break;
                default:
                    if (STB_STATUS_PLAYING() && PLAYER_CAN_CHANNEL_CHANGE(player))
                    {
                        if ((evt->fp.key >= D_KEY_0) && (evt->fp.key <= D_KEY_9))
                        {
                            /*显示频道号输入窗口*/
                            p_atv_chan_input_window_show(0, evt->fp.key);
                        }
                    }
                    break;
            }

            break;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_LANGUAGE_CHANGE)
            {

            }
            else if(evt->user.param1 == USER_MSG_PARAM1_WINDOW_START && evt->user.handle == (D_Handle)(&atv_player_window))
            {
                p_atv_player_win_set_timers();
            }
            break;
        case D_EVT_USER1:
            if(evt->user.param1 == USER_MSG_PARAM1_INPUTFMT_CHANGE)
            {
                if((D_VidInputFormat)evt->user.param2 == D_VID_INPUT_UNDEFINE )
                {
                    p_atv_signal_input_show(D_VID_IUTPUT_MAX, d_gui_get_text(atv_IDS_UNKNOW_FORMAT), NULL);;
                }
                else
                {
                    if((input != D_VID_IUTPUT_TV) && (input != D_VID_IUTPUT_DTV))
                    {
                        p_signal_faint_start(2);
                    }
                    atv_show_scaninfo(input, (D_VidInputFormat)evt->user.param2);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_SCROLL_STATUS)
            {
                if(input == D_VID_IUTPUT_DTV)
                {
                    p_osd_show(evt->user.param2, evt->user.param3);
                }
            }

            else if(evt->user.param1 == USER_MSG_PARAM1_INPUT_STATUS)
            {
                if((input != D_VID_IUTPUT_TV) && (input != D_VID_IUTPUT_DTV))
                {
                    p_signal_faint_start(1);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_HP_STATUS)
            {
                if(evt->user.param2)
                {
                    //耳机插入
                    d_av_set_loudspeaker_mute (0, D_TRUE);
                    d_av_set_earphone_mute (0, D_FALSE);
                    p_atv_media_prompt_msg(atv_IDS_EARPHONE_IN);

                }
                else
                {
                    //耳机拔出
                    d_av_set_loudspeaker_mute (0, D_FALSE);
                    d_av_set_earphone_mute (0, D_TRUE);
                    p_atv_media_prompt_msg(atv_IDS_EARPHONE_OUT);
                }
            }
            else if(evt->user.param1 == USER_MSG_PARAM1_RS232_CHANGEINPUT)
            {
                D_VidInput lastinput;

                lastinput = p_conf_get_vid_input();
                switch(evt->user.param2)
                {
                    case 1:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_TV);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_TV);
                        break;
                    }
                    case 2:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_DTV);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_DTV);
                        break;
                    }
                    case 3:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_AV1);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_AV1);
                        break;
                    }
                    case 4:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_AV2);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_AV2);
                        break;
                    }
                    case 9:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_YPBPR);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_YPBPR);
                        break;
                    }
                    case 7:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_HDMI1);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_HDMI1);
                        break;
                    }
                    case 8:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_HDMI2);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_HDMI2);
                        break;
                    }
                    case 10:
                    {
                        p_conf_set_vid_input(D_VID_IUTPUT_USB1);
                        p_sys_set_input_mode(lastinput, D_VID_IUTPUT_USB1);
                        p_atv_media_main_menu_show();
                        break;
                    }
                }
            }
            break;
        case D_EVT_FEND_LOCKED:
        {
            D_DUMP("LOCKED !!!! freq: %d,  fendtype: %d\n", evt->fend.param.freq, evt->fend.fendtype);
#ifdef D_TV_IAMGE_SOURCE
            if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2))
                d_av_set_cvbs_adstatus(1);
            else
                p_signal_faint_msg(D_FALSE);
#else
            p_signal_faint_msg(D_FALSE);
#endif
        }
        break;
        case D_EVT_FEND_UNLOCKED:
        {
            D_DUMP("UNLOCKED !!!! freq: %d,  fendtype: %d\n", evt->fend.param.freq, evt->fend.fendtype);
#ifdef D_TV_IAMGE_SOURCE
            if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2))
                d_av_set_cvbs_adstatus(0);
            else
                p_signal_faint_msg(D_TRUE);
#else
            p_signal_faint_msg(D_TRUE);
#endif
        }
        break;
        case D_EVT_CA:
            /*CA事件*/
        {
#if   D_CA_SUPPORT_DEF
            //D_CRIT("gui solve ca_evt \n");
            p_ca_gui_solve_evt ((D_CAEventType)evt->ca.param1, (D_Ptr)evt->ca.param2);
#endif
        }
        break;
        case D_EVT_TIMER:
            if (evt->timer.htimer == subscribe_check_htimer)
            {
                if(input == D_VID_IUTPUT_DTV)
                {
                    /*检查是否有节目到期并清除过期预定节目*/
                    d_dbase_check_subscribe (D_FALSE, P_SUBSCRIBE_TIME, send_sub_msg);
                }

                /*检查是否有定时关机*/
                if(stand_by_timer_check() == D_OK)
                {
                    stand_by_timer_deal();
                }
                else if(input == D_VID_IUTPUT_TV)
                {
                    D_S16 chan;
                    D_Time  now = 0;
                    D_Date  date = {0};

                    now = d_time_get_local_time();
                    d_date (now, &date);

                    chan = check_OrderTime_chan(date.hour, date.min); //atv节目预约
                    if(chan != -1)
                    {
                        play_subscribe_atv(chan);
                    }
                }

                if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV) || (input == D_VID_IUTPUT_USB1))
                {
                    no_signal_start_time = 0; /* ATV,DTV,多媒体下不检查无输入信号*/
                }

                if(no_signal_start_time != 0)
                {
                    p_signal_faint_start(0);
                }
            }
            else if (evt->timer.htimer == es_monitor_timer)
            {
#ifdef D_TV_SUPPORT_TS2NET
                if(ts2net_func_running)
                {
                    if(ts2net_check_enable && input == D_VID_IUTPUT_DTV)
                    {
                        d_ts2net_open(NULL);
                    }
                }
#endif
                if(input == D_VID_IUTPUT_DTV)
                {
                    D_U32 es_ret;

                    es_ret = judge_no_es_stream();
                    if(es_ret == D_NO_ES_SHOW)
                    {
                        p_no_es_stream_show(D_TRUE, D_FALSE);
                    }
                    else if(es_ret == D_NO_ES_CLEAR)
                    {
                        p_no_es_stream_show(D_FALSE, D_TRUE);
                    }
                }
                if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
                {
//                    backlight_monitor(input);
                }
                d_timer_reset(evt->timer.htimer, P_ES_MONITOR_TIME);
            }
            break;
        case D_EVT_SI_SW_UPDATE:
            D_DUMP("====sw update ==mtype %d ==\n", evt->si.siparam.montype);
            solve_sw_update_evt(evt->si.siparam);
            break;
        case D_EVT_SUB_START:
            /*预订节目开始*/
            play_subscribe (evt->sub.sub_id);
            break;
        case D_EVT_TV_VID_FMT_CHANGED:
            p_gui_set_format(evt->tv.fmt);
            break;
        case D_EVT_HOTPLUG_MSG:
#ifdef D_MUTIMEDIA_NOCATALOG
            p_media_hotplug_rset((D_U8)evt->hotplug.plug, (D_U8)evt->hotplug.arg);
#endif
            if (!evt->hotplug.plug)
            {
                if((input == D_VID_IUTPUT_USB1) || (input == D_VID_IUTPUT_USB2) || (input == D_VID_IUTPUT_USB3))
                {
                    p_atv_media_prompt_msg(atv_IDS_USB_DIS_CONNECT);
                }
            }
            else
            {
                if((input == D_VID_IUTPUT_USB1) || (input == D_VID_IUTPUT_USB2) || (input == D_VID_IUTPUT_USB3))
                {
                    p_atv_media_prompt_msg(atv_IDS_USB_CONNECT);
                }
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(subscribe_check_htimer  != D_INVALID_HANDLE)
            {
                d_timer_destroy(subscribe_check_htimer );
                subscribe_check_htimer  = D_INVALID_HANDLE;
            }
            if(es_monitor_timer  != D_INVALID_HANDLE)
            {
                d_timer_destroy(es_monitor_timer );
                es_monitor_timer  = D_INVALID_HANDLE;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}



/** @brief 播放器窗口初始化*/
D_Result
atv_player_window_init (void) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_StbPlayer *player;
    D_TimerAttr attr;
    D_S32 device_state = 0;

    player = p_stb_get_player (curr_player_id);
    if (! player)
        return D_ERR;

    vis = d_frame_get_control (&atv_player_window, 0);
    if (vis)
    {
        /*设定窗口遥控器、面板按键事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK |
                             D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK | D_EVT_POWER_KEY_MASK | D_EVT_HOTPLUG_MSG_MASK, D_INVALID_HANDLE);

        /*视频事件*/
        d_vis_subscribe_evt (vis, D_EVT_TV_MASK, player->htv);

        /*设定预订信号不好处理回调*/
        d_vis_subscribe_evt (vis, D_EVT_FEND_MASK, D_INVALID_HANDLE);

        /*设定预订节目处理回调*/
        d_vis_subscribe_evt (vis, D_EVT_SUB_MASK, D_INVALID_HANDLE);

#if   D_CA_SUPPORT_DEF
        /*处理CA事件*/
        d_vis_subscribe_evt (vis, D_EVT_CA_MASK, D_INVALID_HANDLE);
#endif

        /*处理用户事件*/
        d_vis_subscribe_evt (vis, D_EVT_USER_MASK, D_INVALID_HANDLE);

#if 0   /* 为避免定时消息累积，现在窗口运行起来后再设定定时器@qiny 2017.11.30*/
        p_atv_player_win_set_timers();
#else
        {
            D_UserMsg umsg = {0};
            umsg.type = D_MSG_USER;
            umsg.handle = (D_Handle)(&atv_player_window);
            umsg.param1 = USER_MSG_PARAM1_WINDOW_START;
            d_queue_send(d_gui_get_queue(), (D_U8*)&umsg, sizeof(D_UserMsg));
        }
#endif
        d_vis_set_handler (vis, atv_player_handler);
    }

    /*开机检查静音状态*/
    p_atv_reshow_mute_flag();

    return D_OK;
}

/** @breif 设置playerwin的一些定时器*/
D_Result
p_atv_player_win_set_timers (void) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    vis = d_frame_get_control (&atv_player_window, 0);
    if (vis)
    {
        /*创建预订节目检查定时器*/
        subscribe_check_htimer = d_timer_create (NULL, D_SUB_EVT_CHECK_TIME, d_gui_get_queue ());
        if(subscribe_check_htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, subscribe_check_htimer);
        }
        /*创建监控ES流定时器*/
        es_monitor_timer = d_timer_create (NULL, P_ES_MONITOR_TIME, d_gui_get_queue ());
        if(es_monitor_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, es_monitor_timer);
        }

    }
    return D_OK;
}
/** @breif 显示播放器窗口*/
D_Result
p_atv_player_win_show (D_ID player_id) D_FUNCPOSTFIT
{
    d_gui_open_frame(&atv_player_window, D_GUI_LAYER_BACKGROUND);
    return atv_player_window_init ();
}


/** @brief 取得桌面窗口对应的控件*/
D_Visual*
p_atv_get_player_window (void) D_FUNCPOSTFIT
{
    return d_frame_get_control (&atv_player_window, 0);
}

/** @brief 清除全屏状态下的所有提示*/
D_Result
p_atv_player_window_clear_osd (D_U32 param) D_FUNCPOSTFIT
{
    p_not_play_msg_show(D_FALSE);
    p_no_prog_msg(D_FALSE);
    p_atv_no_signal_win_hide();

    no_es_compare_times = 0;
    show_no_es_stream = 0;
    no_es_stream_status = 0;
    show_no_prog_info = 0;
    signal_is_not_good = D_FALSE;
    signal_faint_msg_showing = D_FALSE;
    return D_OK;
}


