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
#include "factory_setting_window.c"
#include "ver.h"

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

static D_Char sw_version[32];
static D_Char release_date[64];
static D_U8 debug_en;
static char svnVersion[64];

static void GetSvnVersion (char* pVer)
{
    if (pVer == NULL)
        return;
    snprintf(pVer, sizeof(char) * 32, "%s", REVISION);
}

/** @brief 解析编译时间*/
static D_Result get_standard_date(D_Date_Ext *date)
{
    D_Char *ptr;
    D_Char *mon[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    D_U32 idx;
    D_U32 tmp;

    if(!date)
        return D_ERR;

    memset(date, 0, sizeof(D_Date_Ext));

    ptr = __DATE__;
    for(idx = 0; idx < 12; idx++)
    {
        if(strstr(ptr, mon[idx]))
        {
            date->mon = idx + 1;
            break;
        }
    }

    while(*ptr != ' ')
        ptr ++;
    while(*ptr == ' ')
        ptr ++;
    if(ptr)
    {
        date->day = (D_U8)strtoul(ptr, NULL, 10);
    }

    while(*ptr != ' ')
        ptr ++;
    while(*ptr == ' ')
        ptr ++;
    if(ptr)
    {
        date->year = (D_U16)strtoul(ptr, NULL, 10) - 1900;
    }

    ptr = __TIME__;
    tmp = 0;
    sscanf(ptr, "%d", &tmp);
    date->hour = (D_U8)tmp;

    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;
        tmp = 0;
        sscanf(ptr, "%d", &tmp);
        date->min = (D_U8)tmp;
    }

    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;
        tmp = 0;
        sscanf(ptr, "%d", &tmp);
        date->sec = (D_U8)tmp;
    }

    return D_OK;
}
/** @brief 按下确定键后清EEP*/
D_Result
tv_restore_factory_setting(void) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_LoaderParam loader_param;
    D_VidInput input;
    D_U8  logo_mode;

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

    p_conf_restore_eep();
    p_tvconf_restore_eep();

    /*刷新数据库*/
    d_dbase_flush();

    //powermode模式恢复为开
    if(p_conf_get_loader_param(&loader_param) == D_OK)
    {
        loader_param.reserved2 = 1;
        p_conf_set_loader_param(&loader_param);
    }

    /* 清eep时，将调试模式打开*/
    debug_en = 0;
    p_tvconf_set_debug_en(debug_en);
    logo_mode = 1;
    p_tvconf_set_logomode (&logo_mode);

    d_tv_sync(player->htv);
    d_sys_reboot();

    return D_OK;
}

D_Result
tv_reset_factory_setting(void) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_LoaderParam loader_param;
    D_VidInput input;
    D_U8  logo_mode;

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
        loader_param.reserved2 = 0;
        p_conf_set_loader_param(&loader_param);
    }
    /* 工厂复位时，将调试模式关闭*/
    debug_en = 0;
    p_tvconf_set_debug_en(debug_en);
    logo_mode = 1;
    p_tvconf_set_logomode (&logo_mode);
    d_tv_sync(player->htv);
    d_sys_reboot();

    return D_OK;
}

static D_Result
set_label_focus_attribute(D_Visual *vis, D_Bool flag) D_FUNCPOSTFIT
{
    D_Ptr pattr;

    if(flag)
    {
        pattr = (D_Ptr)&GUID_label_focus;
        d_vis_set_attribute(vis, pattr);
    }
    else
    {
        pattr = (D_Ptr)&GUID_label_normal;
        d_vis_set_attribute(vis, pattr);
    }

    return D_OK;
}

static D_Result
set_burn_mode(void) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input();

	p_conf_set_vid_input(D_VID_IUTPUT_TEST);
	p_sys_set_input_mode(input,D_VID_IUTPUT_TEST);
}

static D_Result
eep_sel_handler (D_Bool sel, D_U32 param) D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    if (sel)
    {
        if(param == ID_FACTORY_BUTTON_1)
        {
            tv_restore_factory_setting();
        }
    }

    return D_OK;
}

/*显示选择框*/
D_Result show_user_select_window(D_Bool show, D_U32 param) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis = NULL;
    D_Rect rect = {0};

    if(show)
    {
        vis = d_frame_get_control(frm, 0);
        if(vis)
        {
            d_vis_get_pos(vis, &(rect.x), NULL);
            rect.x += vis->rect.w + 5;
        }

        vis = d_frame_get_control(frm, param);
        if(vis)
        {
            vis = vis->parent;
            d_vis_get_pos(vis, NULL, &(rect.y));
            rect.y -= 2;
        }

        d_atv_fc_selbox_window_show(D_FALSE, eep_sel_handler, param, (vis) ? &rect : NULL);
    }
    else
    {
        d_atv_fc_selbox_window_hide();
    }
    return D_OK;
}


static D_Result
init_tv_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;

    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            //tv_restore_factory_setting();
            show_user_select_window(D_TRUE, (D_U32)d_frame_get_control_id(frm, vis));
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            show_user_select_window(D_FALSE, 0);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
reset_tv_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;

    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_0);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            tv_reset_factory_setting();
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
general_setting_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
            p_atv_general_setting_show();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
init_fac_channel_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;

    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_10);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            p_atv_program_reset_show();
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
burn_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;

    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_11);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_burn_mode();
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}


static D_Result
image_setting_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_image_show();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
voice_setting_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_sound_setting_show();
            break;
        default:
            break;
    }
    return D_OK;
}


static D_Result
debug_setting_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;

    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            debug_en = (debug_en + 1) % 2;
            p_tvconf_set_debug_en(debug_en);
            d_label_set_text(vis_label, d_gui_get_text((debug_en) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
adc_adjust_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
#ifndef D_TV_IAMGE_SOURCE
            p_atv_adc_adjust_show();
#endif
            break;
        case D_EVT_LEAVE:
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
emc_setting_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
            p_atv_emc_setting_show();
            break;
        case D_EVT_LEAVE:
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
sw_infomation_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
            p_atv_info_window_show();
            break;
        case D_EVT_LEAVE:
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
software_update_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
            p_atv_software_update_show();
            break;
        case D_EVT_LEAVE:
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
scan_config_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis_label;
    D_VidInput input;

    input = p_conf_get_vid_input();
    vis_label = d_frame_get_control(frm, ID_FACTORY_LABEL_12);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            if(input == D_VID_IUTPUT_TV)
            {
                //进入模拟电视的菜单
                p_atv_tv_scan_config_show();
            }
            else if(input == D_VID_IUTPUT_DTV)
            {
                //进入数字电视的菜单
                p_atv_dtv_scan_config_show();
            }
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
label_vis_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis;
    D_LoaderParam loader_param;

    p_conf_get_loader_param(&loader_param);
    sprintf(sw_version, "%02X", (loader_param.stb_param_copy.sw_build_num) & 0xff);

    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_0);
    if(vis)
    {
        d_label_set_text(vis, ">>>");
    }
    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_1);
    if(vis)
    {
        d_label_set_text(vis, ">>>");
    }

    debug_en = p_tvconf_get_debug_en();
    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, d_gui_get_text((debug_en) ? atv_IDS_ON : atv_IDS_OFF));
    }

    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_10);
    if(vis)
    {
        d_label_set_text(vis, ">>>");
    }

    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_11);
    if(vis)
    {
        d_label_set_text(vis, ">>>");
    }

    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_12);
    if(vis)
    {
        d_label_set_text(vis, ">>>");
    }
    vis = d_frame_get_control(frm, ID_FACTORY_LABEL_VERSION);
    if(vis)
    {
        D_Date_Ext date;
        memset(svnVersion, 0, sizeof(svnVersion));
        GetSvnVersion(svnVersion);
		
        if(get_standard_date(&date) == D_OK)
        {
            sprintf(release_date, "%04d/%02d/%02d  %02d:%02d", date.year + 1900, date.mon, date.day, date.hour, date.min);
        }
        else
        {
            sprintf(release_date, "%s %s", __DATE__, __TIME__);
        }
        sprintf(&release_date[strlen(release_date)] , "  %s" , svnVersion);
        D_DUMP("%s\n", release_date);
        d_label_set_text(vis, release_date);
    }
    return D_OK;
}

static D_Result
set_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &factory_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_0);
    if(vis)
    {
        d_vis_set_handler(vis, reset_tv_handler);
    }
	
    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_1);
    if(vis)
    {
        //d_vis_set_focus(vis);
        d_vis_set_handler(vis, init_tv_handler);
    }
	
    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_2);
    if(vis)
    {
        d_vis_set_handler(vis, general_setting_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_3);
    if(vis)
    {
        d_vis_set_handler(vis, image_setting_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_4);
    if(vis)
    {
        d_vis_set_handler(vis, voice_setting_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_5);
    if(vis)
    {
        d_vis_set_handler(vis, debug_setting_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_6);
    if(vis)
    {
        d_vis_set_handler(vis, adc_adjust_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_7);
    if(vis)
    {
        d_vis_set_handler(vis, emc_setting_handler);
    }

    // vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_8);
    // if(vis)
    //  {
    //      d_vis_set_handler(vis, sw_infomation_handler);
    //  }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_9);
    if(vis)
    {
        d_vis_set_handler(vis, software_update_handler);
    }

    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_10);
    if(vis)
    {
        d_vis_set_handler(vis, init_fac_channel_handler);
    }
    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_11);
    if(vis)
    {
        d_vis_set_handler(vis, burn_mode_handler);
    }
    vis = d_frame_get_control(frm, ID_FACTORY_BUTTON_12);
    if(vis)
    {
        d_vis_set_handler(vis, scan_config_handler);
    }
    return D_OK;
}

static D_Result
factory_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                    return d_gui_clear_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            show_user_select_window(D_FALSE, 0);
        default:
            break;
    }
    return D_ERR;
}



D_Result
factory_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_VidInput input;

    input = p_conf_get_vid_input();
    label_vis_show();

    set_vis_handler();

    vis = d_frame_get_control(frm, ID_FACTORY_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
    }
    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, factory_setting_window_handler);
    }
#ifdef D_TV_IAMGE_SOURCE
    d_vis_enable(d_frame_get_control(frm, ID_FACTORY_BUTTON_6), D_FALSE);
#else
    d_vis_enable(d_frame_get_control(frm, ID_FACTORY_BUTTON_6), D_TRUE);
#endif
    return D_OK;
}

/** @brief 说*/
D_Result
p_atv_factory_setting_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&factory_setting_window, D_TRUE);
}
