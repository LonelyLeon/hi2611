/** @file
* @brief STB控制模块
* @author 覃宜
* @date 2013-7-16: 建立文件
*/

#include <stdio.h>
#include "pStb.h"
#include "pPlayer.h"
#include "dResource.h"
#include "dDebug.h"
#include "dTask.h"
#include "dTime.h"
#include "dGUI.h"
#include "dCBMan.h"
#include "pConfig.h"
#include "pPopMsg.h"
#include "pSdk.h"
#include "pGuiResource.h"
#include "pMonitorRegister.h"
#include "pCustomConfig.h"
#include "pSIParse.h"
#include "pEpgControl.h"
#include "pStbMenus.h"
#include "pStbCaMenus.h"
#include "pPowerOnCheck.h"
#include "pPowerOnLogoPlay.h"
#include "dPowerOff.h"
#include "dadporting.h"
#include "dFileSystem.h"
#include "pStbAtvMenus.h"
#include "pConfig.h"
#include "pBurnSerialNumber.h"
#include "dNetwork.h"
#include "dRemote.h"
#include "dCBMan.h"

#define GUI_NOTIFY(_a_, _b_) d_cbman_notify((_a_), (D_Handle)D_INVALID_HANDLE, (D_Ptr)(_b_))


#if ((EMBED_CA & ABVCA) == ABVCA)
#include "dca/abvca_fun.h"
#endif
/*机顶盒相关数据*/
static D_Stb    stb_data;
D_Stb   *g_stb = &stb_data;
static D_U8 panel_open_flag = 0;

static D_VidFormat get_output_fmt(void)
{
    D_U8 *payload;
    D_U16 len;

    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_LVDS, &len);
    if(!payload || (len < 4))
    {
        return D_VID_FMT_1080P_50;
    }
    switch(payload[0])
    {
        case 0://BOE_32_768P_50
            return D_VID_FMT_768P_50;
        case 1://BOE_32_768P_60
        case 9://LC390TU1A屏
        case 10://奇美32寸v320BJ6-q01
        case 11://TLB315DF39-09
            return D_VID_FMT_768P_60;
        case 2://BOE_40_1080P_50
        case 12://M236HGE-L20
            return D_VID_FMT_1080P_50;
        case 3://BOE_40_1080P_60
            return D_VID_FMT_1080P_60;
        case 4://SANYO_46_1080P_50
            return D_VID_FMT_1080P_50;
        case 5://SANYO_46_1080P_60
            return D_VID_FMT_1080P_60;
        case 6://FMT_1440_900
            return D_VID_FMT_1440_900;
        case 7://
        case 8://
            return D_VID_FMT_1024_600;
        default:
            return D_VID_FMT_1080P_50;
    }
}

/*搜索节目时因运营商播发的流里的sdt表里的srv type不标准，
因此要根据音视频PID对节目的类型进行修正，
根据不同运营商的具体要求进行修改。
放空时按标准处理，即无需修正。@qiny 2013-11-23*/
static void scan_parse_sdt_srv_type_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
#if 1
    D_SdtSrvInfo *sdtsrvinfo = (D_SdtSrvInfo *)obj_data;

    switch (sdtsrvinfo->type)
    {
        case 0x01:  //digital television service
            sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_TV;
            /*不标准，对节目类型进行校正*/
            if ((sdtsrvinfo->srvinfo->vid_pid == 0x1FFF) && (sdtsrvinfo->srvinfo->aud1_pid != 0x1FFF))
            {
                sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_RADIO;
            }
            else if ((sdtsrvinfo->srvinfo->vid_pid == 0x1FFF) && (sdtsrvinfo->srvinfo->aud1_pid == 0x1FFF))
            {
                sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_DATA;
            }

            break;
        case 0x02:  //digital radio sound service
            sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_RADIO;

            /*不标准，对节目类型进行校正*/
            if ((sdtsrvinfo->srvinfo->vid_pid == 0x1FFF) && (sdtsrvinfo->srvinfo->aud1_pid == 0x1FFF))
            {
                sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_DATA;
            }
            else if (sdtsrvinfo->srvinfo->vid_pid != 0x1FFF)
            {
                //sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_TV;
            }
            break;
        default:
            if(sdtsrvinfo->srvinfo->srv_type == D_DB_SRV_DATA)
            {
                if(sdtsrvinfo->srvinfo->vid_pid != 0x1FFF)
                {
                    sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_TV;
                }
                else if(sdtsrvinfo->srvinfo->aud1_pid != 0x1FFF)
                {
                    sdtsrvinfo->srvinfo->srv_type = D_DB_SRV_RADIO;
                }
            }
            break;
    }
#endif
}
/** @brief 密码输入判断*/
static D_Result
password_input_handler (D_Char* passwd, D_U32 param);

#if HI_P_MUTIMEDIA_EN
static void hotplug_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_FsHotPlugNotifyInfo *plug_info = (D_FsHotPlugNotifyInfo*)obj_data;
    D_Msg msg;

    msg.type = D_MSG_HOTPLUG_MSG;
    msg.hotplug.plug = plug_info->plug;
    msg.hotplug.arg = (D_Ptr)plug_info->logic_drv_no;
    p_set_curr_usb_status(plug_info->plug, (D_Ptr)plug_info->logic_drv_no);
    d_queue_try_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_Msg));
}
#endif
static void playlogo_cb(D_U32 cb_id) D_FUNCPOSTFIT
{
    if(cb_id == 0)
    {
        p_vip_set_panel_open();
        panel_open_flag = 1;
#ifdef D_TV_PEOJECT_TOUYY
    lcd_1638_stand_wake_up();
#endif
	}
}

#if (defined(HI_P_TV_TYPE_TV_STB))
/*显示密码输入框*/
static D_Result
show_power_on_passwd_win(D_U32 param)D_FUNCPOSTFIT
{
    d_pop_input_show_ex (D_POP_MSG_PRIO_MSG_2,
                         D_GUI_LAYER_MESSAGE,
                         D_POP_INPUT_POWER_ON,
                         d_gui_get_text(IDS_POWERON_PASSWD),
                         d_gui_get_text(IDS_PASSWD_INPUT_NUM),
                         (D_U16)(p_conf_get_passwd_len()), D_FALSE,
                         password_input_handler, 0);

    return D_OK;
}
/** @brief 密码输入判断*/
static D_Result
password_input_handler (D_Char* passwd, D_U32 param) D_FUNCPOSTFIT
{
    D_U8 check_passwd_result;

    check_passwd_result = p_conf_check_passwd (passwd);
    if (check_passwd_result)
    {
        d_stb_power_on(D_FALSE);
    }
    else
    {
        /*密码输入错误*/
        d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
                            D_GUI_LAYER_MESSAGE, D_POP_MSG_WARNING,
                            d_gui_get_text(IDS_POWERON_PASSWD),
                            d_gui_get_text(IDS_PASSWORD_ERRO),
                            3000, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, show_power_on_passwd_win, 0);
    }

    return D_OK;
}
#endif
static D_U16  fac_flag = 0;

D_Result p_gui_input_poll(D_FPKey *k, D_Bool *repeat)
{
    D_RemoteKeyParam key;
    D_FPKey fp_key;
#ifdef D_GUI_SUPPORT_MOUSE_TOUCHSCREEN
    D_TouchScreenPollData touch_poll_data;
    D_MousePollData mouse_poll_data;
#endif

    *repeat = D_FALSE;

    if(d_remote_poll_key(&key) == D_OK)
    {
        D_RemoteMapHookParam  RemoteMapHookParam;

        RemoteMapHookParam.key = &key;
        RemoteMapHookParam.mapped_key = D_KEY_NUL;

        GUI_NOTIFY(PL_GUI_IR_REMAP, &RemoteMapHookParam);

        if((RemoteMapHookParam.mapped_key != D_KEY_NUL) && k)
        {
            *k = RemoteMapHookParam.mapped_key;
            *repeat = (D_Bool)key.repeat;
            return D_OK;
        }
    }
    else if(d_fp_poll_key(&fp_key) == D_OK)
    {
        D_FPMapHookParam FPMapHookParam;

        FPMapHookParam.source_code = fp_key;
        FPMapHookParam.mapped_key = D_KEY_NUL;

        GUI_NOTIFY(PL_GUI_FP_REMAP, &FPMapHookParam);

        if((FPMapHookParam.mapped_key != D_KEY_NUL) && k)
        {
            *k = FPMapHookParam.mapped_key;
            return D_OK;
        }
    }
#ifdef D_GUI_SUPPORT_MOUSE_TOUCHSCREEN
#ifdef D_SYSTEM_WIN32
    /* 暂时只pc上支持鼠标功能 @qiny 2015-09-25*/
    else if(d_mouse_poll(&mouse_poll_data) == D_OK)
    {
        D_GUIInputPollHook hook;
        //D_DUMP("mouse_poll: %d, %02X, %u, %u, %d\n",
        //       mouse_poll_data.evt, mouse_poll_data.button, mouse_poll_data.x, mouse_poll_data.y, mouse_poll_data.z);

        hook.input_type = D_EVT_MOUSE;
        hook.ptr_param = (D_Ptr)(&mouse_poll_data);
        GUI_NOTIFY(PL_GUI_INPUT_POLL, &hook);

        d_vis_solve_mouse_event(&mouse_poll_data);
    }
#endif
    /* 支持触摸屏功能 @qiny 2015-09-25*/
    else if(d_touchscreen_poll(&touch_poll_data) == D_OK)
    {
        D_GUIInputPollHook hook;
        static D_MouseEvent last_evt_0 = D_MOUSE_EVENT_LBUTTON_UP;
        static D_MouseEvent last_evt_1 = D_MOUSE_EVENT_MOVE;

        /* 将触摸屏事件转换为鼠标事件*/
        mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_DOWN;
        if(touch_poll_data.evt == D_TOUCH_SCREEN_EVENT_DOWN)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_DOWN;
        }
        else if(touch_poll_data.evt == D_TOUCH_SCREEN_EVENT_UP)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_UP;
        }
        else if(touch_poll_data.evt == D_TOUCH_SCREEN_EVENT_MOVE)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_MOVE;
        }

        if(mouse_poll_data.evt == D_MOUSE_EVENT_MOVE && last_evt_0 == D_MOUSE_EVENT_LBUTTON_UP)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_DOWN;
        }
        else if(mouse_poll_data.evt == D_MOUSE_EVENT_LBUTTON_DOWN && last_evt_1 == D_MOUSE_EVENT_MOVE)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_UP;
        }
        else if(mouse_poll_data.evt == D_MOUSE_EVENT_LBUTTON_UP && last_evt_1 == D_MOUSE_EVENT_LBUTTON_UP)
        {
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_DOWN;
            mouse_poll_data.x   = touch_poll_data.x;
            mouse_poll_data.y   = touch_poll_data.y;
            mouse_poll_data.z   = 0;
            mouse_poll_data.button = MOUSE_BUTTON_LEFT;
            //D_DUMP("touch_poll: %d, (%u, %u), 0x%02x\n", mouse_poll_data.evt, mouse_poll_data.x, mouse_poll_data.y, mouse_poll_data.button);

            hook.input_type = D_EVT_MOUSE;
            hook.ptr_param = (D_Ptr)(&mouse_poll_data);
            GUI_NOTIFY(PL_GUI_INPUT_POLL, &hook);

            d_vis_solve_mouse_event(&mouse_poll_data);
            /*更新屏幕*/
            if (gui_show)
            {
                d_vis_redraw ();
            }
            mouse_poll_data.evt = D_MOUSE_EVENT_LBUTTON_UP;
        }

        last_evt_0 = mouse_poll_data.evt;
        last_evt_1 = mouse_poll_data.evt;
        mouse_poll_data.x   = touch_poll_data.x;
        mouse_poll_data.y   = touch_poll_data.y;
        mouse_poll_data.z   = 0;
        mouse_poll_data.button = MOUSE_BUTTON_LEFT;
        //D_DUMP("touch_poll: %d, (%u, %u), 0x%02x\n", mouse_poll_data.evt, mouse_poll_data.x, mouse_poll_data.y, mouse_poll_data.button);

        hook.input_type = D_EVT_MOUSE;
        hook.ptr_param = (D_Ptr)(&mouse_poll_data);
        GUI_NOTIFY(PL_GUI_INPUT_POLL, &hook);

        d_vis_solve_mouse_event(&mouse_poll_data);
    }
#endif
    else
    {
        if(k)
        {
            /* 查询是否有用户生成的键值 */
            *k = D_KEY_NUL;
            GUI_NOTIFY(PL_GUI_GENERATE_USER_KEY, k);
            if(*k != D_KEY_NUL)
                return D_OK;
        }
    }

    return D_ERR;
}

D_Result
d_stb_key_detection (void) D_FUNCPOSTFIT
{
    D_FPKey key;
    D_Bool repeat;
    D_Event evt;


    if(p_gui_input_poll(&key, &repeat) == D_OK)
    {
        D_GUIInputPollHook hook;

        evt.type = D_EVT_FP;
        evt.fp.key = key;
        evt.fp.repeat = repeat;

        hook.input_type = D_EVT_FP;
        hook.ptr_param = (D_Ptr)(&evt);


        if(evt.fp.key == D_KEY_POWER || evt.fp.key == D_KEY_PNL_POWER)
        {
            return D_OK;
        }
    }

    return D_ERR;
}

static void pl_audio_dac_ctl_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_audiodacctlNotifyInfo *info = (D_audiodacctlNotifyInfo*)obj_data;
    d_av_set_avc_ctrl_l((D_U32)(info->now_close_avc));
    d_av_set_avc_ctrl_r((D_U32)(info->now_close_avc));
    info->project_ctrl = 1;

}
extern D_Result
d_vga_open (void) ;
/** @brief 机顶盒库初始化*/
D_Result
d_stb_open (void) D_FUNCPOSTFIT
{
    D_HFMan     hfman = D_INVALID_HANDLE;
    D_HFMan     hfman1 = D_INVALID_HANDLE;
    D_HFMan     hfman2 = D_INVALID_HANDLE;
    D_HFMan     hfman3 = D_INVALID_HANDLE;
    D_VidFormat fmt;
    D_VidOutput video_output;
    D_VidPicRatio video_ratio;
    D_Bool power_on_monitor = D_FALSE;
    D_Bool  mute_flag;
    D_FEndAttr attr;
    D_LoaderParam tLoaderParam;
    D_U8 oldmodeflag;
    D_U8 logo_enable = 0;
    D_U8 standard_flag = 0;

    fac_flag = 0;
    panel_open_flag = 0;
    p_conf_get_loader_param(&tLoaderParam);
#ifndef D_TV_PEOJECT_TOUYY
    if(p_conf_get_vid_input() == D_VID_IUTPUT_TEST)
        p_conf_set_vid_input(D_VID_IUTPUT_DTV);

    if(tLoaderParam.reserved0  == 93)
    {
        //进入工厂模式
        if(tLoaderParam.reserved1 & 0x01)
        {
            //FacAutoTest.ctv
            fac_flag = 1;
        }
        if(tLoaderParam.reserved1 & 0x02)
        {

        }
        if(tLoaderParam.reserved1 & 0x04)
        {

        }
        if(tLoaderParam.reserved1 & 0x08)
        {
            //进入老化模式
            fac_flag = 0x10;
            p_conf_set_vid_input (D_VID_IUTPUT_TEST);
        }
    }
    else
    {
        p_tvconf_get_aging (&oldmodeflag);
        if(oldmodeflag)
        {
            //进入老化模式
            fac_flag = 0x10;
            p_conf_set_vid_input (D_VID_IUTPUT_TEST);
        }
    }
#else
    p_conf_set_vid_input(D_VID_IUTPUT_WIFIDISPLAY);
	
	p_conf_set_transp(0);

#endif
    //上电待机判断
    if((tLoaderParam.reserved2 == 0x0) && !fac_flag) //powermode 模式
    {
        if(tLoaderParam.reserved3 == 2)
        {
            D_U8 remote_num = 0;
            P_POWERKEY power_key[4] = {0};
            D_U32 mask[2] = {0};

            d_sys_stand_by();
            tLoaderParam.reserved3 = 1;
            p_conf_set_loader_param(&tLoaderParam);
            d_PowerOff_Led_Ctrl(1);
#ifndef HI_QINGDAO_HAIER_FUN
            remote_num = p_get_remote_key(D_KEY_POWER, power_key, 4);
            if(remote_num)
            {
                d_remote_power_off(power_key, remote_num, 0, 0);
            }
#else
            mask[0] = 0x00ff00;
            mask[1] = 0x00ff80;
            remote_num = p_get_multiple_remote_key(D_KEY_POWER, D_KEY_PROGRAM_PLUS, power_key, 2);
            if(remote_num)
            {
                d_multiple_remote_power_off(power_key, remote_num, 0, 0, mask);
            }
#endif
        }
    }
#ifdef D_TV_PEOJECT_TOUYY
    spi_gpio_init();
    d_PowerOff_Led_Ctrl(1);
    d_vga_open();
	d_vip_set_Hmdi_Dvi_Csc_Mode(0x01);
    while(tLoaderParam.reserved3 == 2)
    {
        if(d_stb_key_detection() == D_OK)
            break;
    }
#endif	
	d_av_audio_dac_gain_ctrl(6);
    /*LED显示*/
    d_fp_set_led (0, "Load");
    d_PowerOff_Led_Ctrl(0);
    tLoaderParam.reserved3 = 0;
    p_conf_set_loader_param(&tLoaderParam);
    audio_config_init();
    p_tvconf_get_standard (&standard_flag);
    d_av_set_atv_test_unstandard(standard_flag);
#if 1   /*定时开关机功能只执行一次，所以每次开机后将标志清除*/
    {
        D_Tv_Config_Poweron_Order   order;
        D_Tv_Config_Poweron_Order   order1;

        p_tvconf_get_poweron_order(&order);
        if(order.en)
        {
            order.en = 0;
            p_tvconf_set_poweron_order(&order);
        }

        p_tvconf_get_poweroff_order(&order1);
        if(order1.en)
        {
            order1.en = 0;
            p_tvconf_set_poweroff_order(&order1);
        }
    }
#endif
    p_conf_set_aud_mute (D_FALSE); /* 取消静音*/
    p_vip_set_sscg();
    p_vip_init(D_VID_IUTPUT_DTV, 1, 0, 1);
    d_av_avc_ctl(0, ((D_FALSE == p_conf_get_smart_voice_en()) ? 0 : 1));

    d_av_avc_ctl_whole_en(0, ((p_tvconf_get_avc_whole_en()) ? 1 : 0));
    d_av_peq_ctrl(0, ((p_tvconf_get_avc_peq_en()) ? 1 : 0));

    d_av_set_loudspeaker_mute (0, D_FALSE);
    d_av_set_earphone_mute (0, D_TRUE);
    d_av_set_balance (0, p_conf_get_balance());

    /*设置显示制式*/
    p_conf_set_vid_fmt (get_output_fmt());
    fmt =  p_conf_get_vid_fmt ();
    d_tv_set_vid_format (g_htv, fmt);

    /*设置视频输出类型*/
    video_output = p_conf_get_vid_output();
    d_tv_set_vid_output (g_htv, video_output);

    /*设置视频宽高比*/
    video_ratio = p_conf_get_vid_pic_ratio();
    d_tv_set_pic_ratio (g_htv, video_ratio);

    d_tv_set_queue (g_htv, d_gui_get_queue ());
    d_tv_set_vid_window(g_htv, 0, 0, -1, -1);

    //d_tv_sync(g_htv);
    p_gui_set_format(fmt);
    {
        d_ad_config adcfg;

        adcfg.type = DAD_STB_SD;
        adcfg.dstag = P_DESCR_DSAD_TAG;
        adcfg.mgtag = P_DESCR_MGAD_TAG;
        adcfg.ucPriority = D_AD_MODULE_TASK_PRIO;
        d_ad_modlue_Open(&adcfg);
    }
    p_vip_set_panel_init();


	d_av_spdif_en(1);

    //d_av_vdac_ctrl(1);
    /*显示开机LOGO*/
    p_tvconf_get_logomode(&logo_enable); /*logomode控制是否显示logo*/
    if(fac_flag == 0 && logo_enable)
    {
        p_power_on_logo_cb(playlogo_cb);
        p_power_on_logo_play_start(2000);
    }
#ifdef D_TV_PEOJECT_TOUYY
    /*ANALOG*/
    attr.id = 0;
    attr.type = D_FEND_CVBS;
    hfman = d_fman_create(D_FMAN_TASK_PRIO, &attr);
#else
#ifdef HI_SOFT_TYPE_DVBS
    /*DVBS*/
    attr.id = 0;
    attr.type = D_FEND_DVBS;
    hfman = d_fman_create(D_FMAN_TASK_PRIO, &attr);
    d_fman_set_lnb_power_enable(hfman, D_TRUE);
#else
    /*DTMB双模*/
    attr.id = 0;
    attr.type = D_FEND_DTMB;
    hfman = d_fman_create(D_FMAN_TASK_PRIO, &attr);
    /*DVBC*/
    attr.id = 1;
    attr.type = D_FEND_DVBC;
    hfman1 = d_fman_create(D_FMAN_TASK_PRIO, &attr);
//    p_conf_set_scan_config(0);//dtmb
    //  p_conf_set_scan_config(1);//dvbc
    /*ANALOG*/
    attr.id = 2;
    attr.type = D_FEND_ANALOG;
    hfman2 = d_fman_create(D_FMAN_TASK_PRIO, &attr);

#ifdef D_TV_IAMGE_SOURCE
    /*ANALOG*/
    attr.id = 3;
    attr.type = D_FEND_CVBS;
    hfman3 = d_fman_create(D_FMAN_TASK_PRIO, &attr);
#endif
#endif
#endif
    d_cbman_subscribe(PL_SI_PARSE_SRV_TYPE, D_INVALID_HANDLE, scan_parse_sdt_srv_type_cb, NULL);

#if HI_P_MUTIMEDIA_EN
    d_cbman_subscribe(PL_FILESYSTEM_HOTPLUG, D_INVALID_HANDLE, hotplug_cb, NULL);
    d_file_system_open();

#ifdef D_SYSTEM_WIN32
    d_fs_win32_open();
#elif defined(D_SYSTEM_LINUX)
    d_fs_linux_open();
#else
    d_fs_fat_open();
    d_fs_ntfs_open();
#endif
#endif
    d_head_phone_open();
#ifdef D_DBG_DISK_OPEN
    p_dbg_disk_create(1);
#endif

#ifdef D_GAMA_TEST
    HR_testGamm();
#endif
    d_cbman_subscribe(PL_AUDIO_DAC_CTL, D_INVALID_HANDLE, pl_audio_dac_ctl_cb, NULL);

    /*私有si表、描述符解析初始化*/
    p_private_si_parse_open();

    if(p_power_on_check_init() == D_OK)
    {
        power_on_monitor = D_TRUE;
        //   p_power_on_check_start(DEF_FEND_TYPE);
        if(p_conf_get_scan_config())
            p_power_on_check_start(D_FEND_DVBC);
        else
            p_power_on_check_start(D_FEND_DTMB);
    }
    if(!p_conf_get_channel_change_mode())
    {
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
    }

    /*设置静音*/
    mute_flag = p_conf_get_aud_mute ();
    d_tv_set_aud_mute (g_htv, (mute_flag ? D_TRUE : D_FALSE));

    d_time_set_time_offset(p_conf_get_time_offset());

    /*设置菜单透明度*/
    {
        D_GSurface  *surf;
        D_U8    transp;
        D_U8 transparency[] = {128, 115, 90, 64, 38};

        transp = p_conf_get_transp ();
        transp = (transp > 4) ? 0 : transp;

#if 0
        surf = d_gui_get_surface ();
        if (surf)
        {
            d_gdev_set_global_alpha (surf->hgdev, transparency[transp]);
        }
#else
        d_gdev_set_global_alpha (p_gui_get_hgdev(), transparency[transp]);
#endif
    }

    /*初始化播放器*/
    p_stb_player_init(0, hfman, g_htv);
    g_stb->player = p_stb_get_player(D_STB_MAIN_PLAYER);
#if (defined(HI_P_TV_TYPE_TV_STB))
    p_gui_stb_resource_open();
#endif
#if   D_CA_SUPPORT_DEF
    p_gui_ca_resource_open();
#endif
    p_gui_atv_resource_open();

    d_gui_resource_open();
    d_gui_lang_set(p_conf_get_lang());

#if D_CA_SUPPORT_DEF
    p_stb_ca_menu_init();
#endif

    p_atv_menu_init();
    p_atv_player_win_show (0);

    if(power_on_monitor)
    {
        D_PowerOnCheck power_on_check = {0};
        p_power_on_check(&power_on_check);
        //   p_power_on_check_stop(DEF_FEND_TYPE);
        if(p_conf_get_scan_config())
            p_power_on_check_stop(D_FEND_DVBC);
        else
            p_power_on_check_stop(D_FEND_DTMB);
        p_power_on_check_deinit();

        if(!power_on_check.network_match)
        {
            //d_tv_set_play_lock(g_htv, D_TRUE);
        }
    }
#ifdef D_BURNER_OTP
#ifdef D_BURN_OTP_MODE_B
    p_otp_monitor_usb();
#endif
#endif
    /*销毁显示开机LOGO 任务*/
    if(fac_flag == 0)
        p_power_on_logo_play_end();
    if(panel_open_flag == 0)
    {
        p_vip_set_panel_open();
#ifdef D_TV_PEOJECT_TOUYY
		lcd_1638_stand_wake_up();
#endif
    }
    /*开启广告数据的搜索*/
    {
        D_Ad_Start_Param param;
        param.attr.id = 0;
        //  param.attr.type = DEF_FEND_TYPE;
        if(p_conf_get_scan_config())
            param.attr.type = D_FEND_DVBC;
        else
            param.attr.type = D_FEND_DTMB;
        d_ad_modlue_start(&param);
    }

    if(p_monitor_init() != 0)
    {
        D_ERROR ("Si_init error\n");
    }

    d_fman_set_locked_detector (hfman, d_gui_get_queue ());
    d_fman_set_locked_detector (hfman1, d_gui_get_queue ());
    d_fman_set_locked_detector (hfman2, d_gui_get_queue ());
    d_fman_set_locked_detector (hfman3, d_gui_get_queue ());
#if HI_P_PVR_EN
    d_pvr_porting_open();
#endif

    //d_wakeup_open();
    return D_OK;
}

/** @brief 机顶盒关闭*/
D_Result
d_stb_close (void) D_FUNCPOSTFIT
{
    return D_OK;
}

/** @brief 进行机顶盒开机检查*/
D_Result
d_stb_power_on (D_Bool power_on) D_FUNCPOSTFIT
{
    D_DBSrvID       srv;
    D_SIParam       s_si_param, t_si_param;
    D_VidInput      input;
    D_HFMan hfman;
    D_StbPlayer *player;
    D_U8 ratio_mode;
    D_GSurface* psurface;
    D_DBSrvInfo srvinfo = {0};

    psurface = p_gui_get_dev_surface();
    d_g_lock(d_gui_get_surface());
    d_g_set_fg(psurface, d_g_map_pixel(psurface, D_RGBA(0, 0, 0, 0)));
    d_g_fill_rect(psurface, &(psurface->clip));
    d_g_unlock(d_gui_get_surface());

    /*关闭开机LOGO显示*/
    d_tv_clear_pic_I(g_htv);
    d_stb_stop_play();
    /*设定服务声道和音量*/
    d_tv_set_aud_mute(g_htv, p_conf_get_aud_mute());
    d_tv_set_aud_track(g_htv, p_conf_get_aud_track());
    p_stb_player_set_vol(0, p_conf_get_volume());
    d_tv_sync(g_htv);
    d_av_set_vid_blank(0, D_TRUE);
#ifdef HI_QINGDAO_HAIER_FUN
    d_av_cvbs_num_invert(1);
#endif
#if   D_CA_SUPPORT_DEF
#ifdef D_CA_SUPPORT_ABVCA
#ifdef D_CA_SUPPORT_COS
    HRABVCASTB_PrintScNoAndSTBID();
#endif
#endif
#endif

    /* 网络初始化*/
#ifdef D_TV_MIRACAST_SOURCE
    //d_network_init();
    //d_network_test_communicate();
    //d_wireless_start_check(NULL);  /* 刚初始化后立即连接，经常失败*/
#endif

//起机时候上一个状态当成DTV处理
    input = p_conf_get_vid_input ();

    /* 在切源set input 之前要先解图，防止切源后再解会有碎片*/
    if(input == D_VID_IUTPUT_USB1)
    {
        p_gui_atv_media_resource_init();
    }
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
    if(input == D_VID_IUTPUT_WIFIDISPLAY)
    {
        p_gui_atv_zhilian_resource_init();
    }
#endif

    p_tvconf_get_cur_zoommode(&ratio_mode, p_vip_get_dbinput(input));

    d_tv_set_vid_input (g_htv, input);

    if(input != D_VID_IUTPUT_DTV)
    {
        hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);

        p_monitor_close();
#if  D_CA_SUPPORT_DEF
        {
            p_Ca_BuyMsg_bak(); //备份CA提示信息
            p_Ca_osd_window_bak(); //备份邮件小图标数据

            d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_2); //清除CA提示信息
            p_Ca_osd_window_hide(); //清除邮件小图标

            d_ca_system_stop();  //停止ca任务运行
            d_gui_clear_layer(D_GUI_LAYER_USER_2);
            p_stb_ca_scroll_show(0);
            p_osd_show_reset();
            p_Ca_window_hide();
        }
#endif
    }

    if(input != D_VID_IUTPUT_TV)
    {
        hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
    }
#ifdef D_TV_IAMGE_SOURCE
    hfman = d_fman_get_handle_by_type(D_FEND_CVBS, 0);
    d_fman_set_suspend(hfman, D_TRUE);
    d_fman_release_dev(hfman);
#endif
    if((input == D_VID_IUTPUT_USB1)\
       || (input == D_VID_IUTPUT_USB2) || (input == D_VID_IUTPUT_USB3)
#ifdef D_TV_LIULINK_SOURCE
       || (input == D_VID_IUTPUT_LIULINK)
#endif
      )
    {
#ifdef D_DDR_SIZE_64M
        d_av_noise_bypass_en(1);
#endif
    }
    else
    {
#ifdef D_DDR_SIZE_64M
        d_av_noise_bypass_en(0);
#endif
    }
    
    p_av_set_vid_background(0, p_sys_get_user_background_color(), D_TRUE);
    p_vip_backlight_open();

    d_tv_sync(g_htv);

    if(input == D_VID_IUTPUT_DTV)
    {
        if(!p_conf_get_channel_change_mode())
        {
            d_tv_set_chan_change_blank(g_htv, D_TRUE);
        }
        else
        {
            d_tv_set_chan_change_blank(g_htv, D_FALSE);
        }
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);
        p_set_ratio_mode (ratio_mode );
        p_vip_init(input, 0, 0, 1);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE;

        hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
        d_fman_set_suspend(hfman, D_FALSE);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
        d_fman_set_suspend(hfman, D_FALSE);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
        d_fman_set_suspend(hfman, D_FALSE);

        /*菜单初始化*/
#if (defined(HI_P_TV_TYPE_TV_STB))
        p_atv_menu_deinit();
        p_stb_menu_init ();
        p_stb_player_win_show (0);
        if(power_on && p_conf_get_poweron_passwd_en())
        {
            return show_power_on_passwd_win(0);
        }
#endif
        /*取强制要播放的节目*/
        srv = p_conf_get_force_srv ();
        if((D_OK != d_dbase_get_srv_info(srv, &srvinfo)) || (srvinfo.srv_type != D_DB_SRV_TV && srvinfo.srv_type != D_DB_SRV_RADIO))
        {
            srv = -1;
        }

        /*取上次播放的节目*/
        srv = p_conf_get_curr_srv ();
        if((D_OK != d_dbase_get_srv_info(srv, &srvinfo)) || (srvinfo.srv_type != D_DB_SRV_TV && srvinfo.srv_type != D_DB_SRV_RADIO))
        {
            srv = -1;
        }

        if (srv >= 0)
        {
            if (p_stb_player_play_srv (0, srv) >= 0)
            {
                return D_OK;
            }
        }

        /*尝试播放各种可能的节目*/
        if (p_stb_player_play_valid (0) >= 0)
        {
            return D_OK;
        }

        /*没有存储节目，开始自动搜台*/
        D_DUMP ("Cannot get any tv program\n");
        p_no_prog_msg(D_TRUE);
        p_atv_channel_info_window_show(0);
    __END_OK:
        return D_OK;
    }
    else if(input == D_VID_IUTPUT_TV)
    {
        D_S16 chan_num;

        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);
        p_set_ratio_mode (ratio_mode );
        p_vip_init(input, 0, 0, 1);
        player = p_stb_get_player(0);
        player->play_atv = D_TRUE;
        hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
        d_fman_set_suspend(hfman, D_FALSE);

        /*释放epg占用资源*/
        p_auxi_free_varstring();

        p_tvconf_get_boot_chan(&chan_num);

        srv = -1;
        if(chan_num > 0)
        {
            srv = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_ATV);
        }

        if(srv < 0)
        {
            /*取上次播放的节目*/
            srv = p_conf_get_curr_atv_srv ();
        }

        if(srv >= 0)
        {
            if((D_OK == d_dbase_get_srv_info(srv, &srvinfo)) && (srvinfo.srv_type == D_DB_SRV_ATV))
            {
                srv = srv;
            }
            else
            {
                srv = -1;
            }
        }

        if(srv >= 0)
        {
            if (p_stb_player_play_srv (0, srv) >= 0)
            {
                return D_OK;
            }
        }

        /*尝试播放各种可能的节目*/
        if(p_stb_player_play_valid (0) == D_OK)
        {
            return D_OK;
        }

        p_no_prog_msg(D_TRUE);
        p_atv_tv_chan_info_window_show(0);
        return D_OK;
    }
    else if(input == D_VID_IUTPUT_TEST)
    {
        D_KeyCode tfilter_keys[] = {D_KEY_POWER, D_KEY_PNL_POWER, D_KEY_EXITOLDMODE};
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);

        p_set_ratio_mode (ratio_mode );
        p_vip_init(input, 0, 0, 1);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE;
        /*释放epg占用资源*/
        p_auxi_free_varstring();
        d_av_stop(0);//为了后面的静音效果
        d_gui_clear_menu();
        p_fp_set_filter_keys(&tfilter_keys, sizeof(tfilter_keys) / sizeof(tfilter_keys[0]));
        d_gdev_set_enable(p_gui_get_hgdev(), D_FALSE);

        p_signal_faint_msg(D_FALSE);
        p_set_signal_faint_msg_enable(D_FALSE, 0);
        p_signal_faint_start(2);

        p_atv_timer_set_show();
        return D_OK;
    }
    else
    {
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);
        p_set_ratio_mode (ratio_mode );
        p_vip_init(input, 0, 0, 1);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE;
        /*释放epg占用资源*/
        p_auxi_free_varstring();
        p_atv_signal_input_show(input, NULL, NULL);

        if(input == D_VID_IUTPUT_USB1)
        {
            p_signal_faint_start(2);
            p_atv_media_main_menu_show();
        }
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
        else if (input == D_VID_IUTPUT_WIFIDISPLAY)
        {
            p_signal_faint_start(2);
            //p_atv_zhilian_tv_window_show(0);
            //p_atv_zhilian_menu_window_show(0);
			p_atv_zhilian_main_menu_window_show();            
        }
#endif

#ifdef D_TV_LIULINK_SOURCE
        else if(input == D_VID_IUTPUT_LIULINK)
        {
            p_signal_faint_start(2);
            D_ERROR("*******input is LIULINK*******\n");
            extern int Liulinkclient_load(void);
            Liulinkclient_load();
        }
#endif
#ifdef D_TV_SUPPORT_IPTV
        else if(input == D_VID_IUTPUT_IPTV)
        {
            //          p_signal_faint_start(2);
            D_ERROR("*******input is iptv*******\n");
            p_stb_enter_iptv();
        }
#endif
        else if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2) || (input == D_VID_IUTPUT_S)\
                || (input == D_VID_IUTPUT_YPBPR) || (input == D_VID_IUTPUT_VGA)\
                || (input == D_VID_IUTPUT_HDMI1) || (input == D_VID_IUTPUT_HDMI2)\
                || (input == D_VID_IUTPUT_HDMI3))
        {
#ifdef D_TV_IAMGE_SOURCE
            if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2))
            {
                D_FEndParam fendparam;
                hfman = d_fman_get_handle_by_type(D_FEND_CVBS, 0);
                d_fman_set_suspend(hfman, D_FALSE);
                if((input == D_VID_IUTPUT_AV2))
                    fendparam.freq = 1;
                else
                    fendparam.freq = 0;

                d_fman_set_param (hfman, &fendparam, D_TRUE, (D_FEndType)D_FEND_CVBS, NULL, NULL);
            }
#endif
            d_av_set_vid_blank(0, D_FALSE);
            p_signal_faint_start(1);
        }
        return D_OK;
    }
}


/** @brief 机顶盒进入待机状态*/
D_Result
d_stb_stand_by (void) D_FUNCPOSTFIT
{
    D_HFMan     hfman;
    D_U8 remote_num = 0;
    D_U32 mask[2] = {0};
    P_POWERKEY power_key[4] = {0};
    D_LoaderParam loader_param;

    if(g_stb->status == D_STB_ST_STANDBY)
        return D_OK;

    D_DUMP("STB stand by...\n");

    if(p_conf_get_loader_param(&loader_param) == D_OK)
    {
        loader_param.reserved3 = 1;
        p_conf_set_loader_param(&loader_param);
    }
    /*关闭窗体*/
    d_gui_clear_menu ();

    d_gui_clear_layer (D_GUI_LAYER_VIDEO_OSD);
    d_gui_clear_layer (D_GUI_LAYER_MESSAGE);

    /*关闭GUI显示*/
    d_gui_show (D_FALSE);
    /*停止所有播放*/

    p_av_set_vid_background(0, D_VID_BackGround_BLack, D_TRUE);
    d_stb_stop_play ();
//  d_fp_set_led(0, " OFF");
    d_PowerOff_Led_Ctrl(1);

    g_stb->status = D_STB_ST_STANDBY;

    if(p_conf_get_scan_config())
        hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
    else
        hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);

    d_fman_set_stdby(hfman);
    d_app_set_timeout (hfman, -1);
    d_app_sync(hfman);

#ifdef D_TV_PEOJECT_TOUYY
    lcd_1638_stand_by();
#endif

    p_vip_set_panel_close();
    d_sys_stand_by();

#ifndef HI_QINGDAO_HAIER_FUN
    remote_num = p_get_remote_key(D_KEY_POWER, power_key, 4);
    if(remote_num)
    {
        D_Tv_Config_Poweron_Order   order;
        D_U16 wakeup_time;

        d_task_wait(3000);

        p_tvconf_get_poweron_order(&order);
        if(order.en)
        {
            D_U16   tmin = 0;
            D_Time  now = 0;
            D_Date  date = {0};
            D_U16   min = 0;
            D_U16   min1 = 0;

            now = d_time_get_local_time();
            d_date (now, &date);
            min = date.hour * 60 + date.min;
            min1 = order.hour * 60 + order.min;
            if(min1 > min)
            {
                tmin = min1 - min;
            }
            else
            {
                tmin = 24 * 60 + min1 - min;
            }
            d_remote_power_off(power_key, remote_num, tmin, 0);
        }
        else
        {
            d_remote_power_off(power_key, remote_num, 0, 0);
        }
    }
#else
    remote_num = p_get_multiple_remote_key(D_KEY_POWER, D_KEY_PROGRAM_PLUS, power_key, 2);
    if(remote_num)
    {
        D_Tv_Config_Poweron_Order   order;
        D_U16 wakeup_time;

        d_task_wait(3000);
        mask[0] = 0x00ff00;
        mask[1] = 0x00ff80;
        p_tvconf_get_poweron_order(&order);
        if(order.en)
        {
            D_U16   tmin = 0;
            D_Time  now = 0;
            D_Date  date = {0};
            D_U16   min = 0;
            D_U16   min1 = 0;

            now = d_time_get_local_time();
            d_date (now, &date);
            min = date.hour * 60 + date.min;
            min1 = order.hour * 60 + order.min;
            if(min1 > min)
            {
                tmin = min1 - min;
            }
            else
            {
                tmin = 24 * 60 + min1 - min;
            }

            d_multiple_remote_power_off(power_key, remote_num, tmin, 0, mask);
        }
        else
        {
            d_multiple_remote_power_off(power_key, remote_num, 0, 0, mask);
        }
    }
#endif
    return D_OK;
}

/** @brief 机顶盒从待机状态唤醒*/
D_Result
d_stb_wake_up (void) D_FUNCPOSTFIT
{
#if 1
    d_sys_reboot();
#else
    if(g_stb->status != D_STB_ST_STANDBY)
        return D_OK;

    g_stb->status = D_STB_ST_PLAYING;

    D_DUMP ("STB wake up...");

    d_fp_set_led(0, "0000");

    /*显示GUI*/
    d_gui_show (D_TRUE);

    //d_ca_standby(D_FALSE);
    d_sys_wake_up();
    /*设置视频输出类型*/
    d_tv_set_vid_output(g_htv, p_conf_get_vid_output());

    /*开始播放*/
    d_stb_power_on (D_FALSE);

    //d_nds_osd_reshow();/*重新显示ca OSD*/

    //d_pop_msg_reshow();/*重新显示弹出信息*/
#endif
    return D_OK;
}



/** @brief 提示用户保存数据*/
D_Result
d_stb_store (void) D_FUNCPOSTFIT
{

    /*刷新数据库*/
    d_dbase_flush ();

    return D_OK;
}

/** @brief 暂停所有播放器的播放和前端设备使用*/
D_Result
d_stb_stop_play (void) D_FUNCPOSTFIT
{
    p_stb_player_stop (0);
    p_epg_stop(); // 停止epg搜索
    d_tv_suspend (g_htv);
    d_tv_sync (g_htv);

    return D_OK;
}


